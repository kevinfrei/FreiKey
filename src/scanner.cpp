#include <vector>

#include "dbgcfg.h"
#include "general.h"
#include "keymap.h"
#include "keystate.h"
#include "scanner.h"

// Declarations
constexpr uint32_t TapAndHoldTimeLimit = 100;

keystate keyStates[num_keystates];

#if defined(DEBUG)
void dumpScanCode(uint8_t sc, bool pressed) {
  Serial.print("Scan Code ");
  Serial.print(sc, HEX);
  Serial.println(pressed ? " was pressed" : " was released");
#if defined(DISPLAY)
  BoardIO::ShowScanCode(sc + (pressed ? 0xFF00 : 0));
#endif
}
#endif

// Look for a slot that is either already in use for this scan code, or vacant.
// If we don't have a vacant slot, return the oldest, but still in use, slot,
// but only for key-up states, as we're probably through with them anyway.
struct keystate* findStateSlot(scancode_t scanCode) {
  keystate *vacant = nullptr, *reap = nullptr;
  for (auto& s : keyStates) {
    // If we have the same scan code, huzzah!
    if (s.scanCode == scanCode) {
      return &s;
    }
    // If we found a vacancy, potentially use it. We have to keep looking to see
    // if we have the same scan code, though.
    if (s.scanCode == null_scan_code) {
      vacant = &s;
    } else if (!s.down) {
      if (!reap) {
        reap = &s;
      } else if (s.lastChange < reap->lastChange) {
        // Idle longer than the other reapable candidate; choose
        // the eldest of them
        reap = &s;
      }
    }
  }
  if (vacant) {
    reap = vacant;
  }
  return reap;
}

action_t resolve(uint8_t layerPos, uint8_t scancode) {
  return keymap[curState.getLayerVal()][scancode];
}

// Find the first specified action in the layer stack
action_t resolveActionForScanCodeOnActiveLayer(uint8_t scanCode) {
  uint8_t s = curState.layer_pos;
  DBG(dumpVal(s, "Layer position: "));
  while (s > 0 && resolve(s, scanCode).isNoAction()) {
    --s;
  }
#if defined(DEBUG)
  Serial.printf("Resolving scancode %d on layer %d to action ",
                scanCode,
                curState.layer_stack[s]);
  keymap[curState.getLayerVal(s)][scanCode].dump();
#endif
  return resolve(s, scanCode);
}

layer_num getCurrentLayer() {
  return curState.layer_stack[curState.layer_pos];
}

// Called immediately after seeing the scan code:
// Find a slot for the key, and deal with layer "stuff"
void preprocessScanCode(scancode_t sc, bool pressed, uint32_t now) {
  DBG2(dumpScanCode(sc, pressed));
  // Get a state slot for this scan code
  keystate* state = findStateSlot(sc);
  if (!state) {
    // If this is a keydown and we don't have an available state slot just
    // ignore it. If we chose to toss out older keydowns instead, things could
    // get pretty weird. If this is a keyup, and we still don't have a state
    // slot, that's a little bonkers, but there's not much we can do about it.
    DBG(Serial.println("Unable to find an unused keystat slot!"));
    return;
  }
  DBG2(state->dump());
  // State update returns a layer action to perform...
  switch (state->update(sc, pressed, now)) {
    case layer_t::Push:
      curState.push_layer(state->get_layer());
      break;
    case layer_t::Pop:
      curState.pop_layer(state->get_layer());
      break;
    case layer_t::Toggle:
      curState.toggle_layer(state->get_layer());
      break;
    case layer_t::Switch:
      curState.switch_layer(state->get_layer());
      break;
    case layer_t::None:
      break;
  }
}
void ProcessConsumer(keystate& state, kb_reporter& rpt) {
  // For a consumer control button, there are no modifiers, it's
  // just a simple call. So just call it directly:
  if (state.down) {
    DBG(dumpHex(getConsumerUSBCode(state.action.getConsumer()),
                "Consumer key press: "));
    // See all the codes in all their glory here:
    // https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
    // (And if that doesn't work, check here: https://www.usb.org/hid)
    rpt.consumer_press(getConsumerUSBCode(state.action.getConsumer()));
  } else {
    DBG(dumpHex(getConsumerUSBCode(state.action.getConsumer()),
                "Consumer key release: "));
    rpt.consumer_release(getConsumerUSBCode(state.action.getConsumer()));
    // We have to clear this thing out when we're done, because we take
    // action on the key release as well. We don't do this for the normal
    // keyboardReport.
    state.scanCode = null_scan_code;
  }
}

void ProcessKeys(uint32_t now, kb_reporter& rpt) {
  uint8_t mods = 0;

  for (auto& state : keyStates) {
    if (state.scanCode == null_scan_code)
      continue;
    KeyAction actions = state.action.getAction();
    if (actions == KeyAction::TapHold) {
      // TODO: I don't think this quite works...
      
      // If we've exceeded the time limit, set the modifier
      // If we're under the time limit, and it's a key *down* we shouldn't
      // do anything, because we won't know what to do until after the time
      // limit is hit, or a key-up occurs.
      if (now - state.lastChange > TapAndHoldTimeLimit) {
        // Holding
        mods |= static_cast<uint8_t>(state.action.getExtraMods());
        DBG(dumpHex(mods, " (Holding)"));
        rpt.set_modifier(mods);
      } else if (state.down) {
        continue;
      }
      // We've had it for less than the time allotted, so send the tapping key
      // TODO: Make sure we send the key up immediate after this!
      if (state.action.getAction() == KeyAction::Consumer) {
        DBG(dumpHex(static_cast<uint16_t>(state.action.getConsumer()), " Tapping Consumer Key"));
        state.down = true;
        ProcessConsumer(state, rpt);
        state.down = false;
        ProcessConsumer(state, rpt);
      } else {
        Keystroke key = state.action.getKeystroke();
        if (key != Keystroke::None) {
          rpt.add_key_press(getUSBCode(key));
          DBG(dumpHex(static_cast<uint8_t>(key), " Tapping"));
        }
      }
    } else if (actions == KeyAction::Consumer) {
      ProcessConsumer(state, rpt);
    } else if (actions == KeyAction::KeyAndMods) {
      if (state.down) {
        mods |= static_cast<uint8_t>(state.action.getExtraMods());
        rpt.set_modifier(mods);
        Keystroke key = state.action.getKeystroke();
        if (key != Keystroke::None) {
          rpt.add_key_press(getUSBCode(key));
        }
      }
    } else if (actions == KeyAction::KeyPress) {
      if (state.down) {
        Keystroke key = state.action.getKeystroke();
        if (key != Keystroke::None) {
          rpt.add_key_press(getUSBCode(key));
        }
      }
    } else if (actions == KeyAction::Modifier) {
      if (state.down) {
        mods |= static_cast<uint8_t>(state.action.getModifiers());
        rpt.set_modifier(mods);
      }
    }
    /*
  This doesn't work, and I don't use it anyway
  case kToggleMod:
    mods ^= state.action & 0xff;
    rpt.set_modifier(mods);
    break;
  */
  }
  rpt.send_keys();
}
