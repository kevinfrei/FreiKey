#include "sysstuff.h"

#include "dbgcfg.h"
#include "generalstate.h"
#include "keymap.h"
#include "keystate.h"
#include "scanning.h"

#include "secrets.h"

// Declarations
constexpr uint32_t TapAndHoldTimeLimit = 100;

keystate keyStates[num_keystates];

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
  return keymap[value_cast(curState.layer_stack[layerPos])][scancode];
}

// Find the first specified action in the layer stack
action_t resolveActionForScanCodeOnActiveLayer(uint8_t scanCode) {
  uint8_t s = curState.layer_pos;
  Dbg << "Layer position: " << s << sfmt::endl;
  while (s > 0 && resolve(s, scanCode).isNoAction()) {
    --s;
  }
  Dbg << "Resolving scancode " << scanCode << " on layer "
      << curState.layer_stack[s] << ":"
      << keymap[curState.getLayerVal(s)][scanCode] << sfmt::endl;
  return resolve(s, scanCode);
}

layer_num getCurrentLayer() {
  return curState.layer_stack[curState.layer_pos];
}

// Called immediately after seeing the scan code:
// Find a slot for the key, and deal with layer "stuff"
void preprocessScanCode(scancode_t sc, bool pressed, uint32_t now) {
  Dbg2 << "Scan Code " << sfmt::hex << sc
       << (pressed ? " was pressed" : " was released") << sfmt::endl;
  BoardIO::ShowScanCode(sc + (pressed ? 0xFF00 : 0));
  // Get a state slot for this scan code
  keystate* state = findStateSlot(sc);
  if (!state) {
    // If this is a keydown and we don't have an available state slot just
    // ignore it. If we chose to toss out older keydowns instead, things could
    // get pretty weird. If this is a keyup, and we still don't have a state
    // slot, that's a little bonkers, but there's not much we can do about it.
    Dbg << "Unable to find an unused keystat slot!" << sfmt::endl;
    return;
  }
  Dbg2 << *state << sfmt::endl;
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
    case layer_t::Rotate3:
      curState.rotate_layers(
        state->get_layer1(), state->get_layer2(), state->get_layer3());
      break;
    case layer_t::Rotate4:
      curState.rotate_layers(state->get_layer1(),
                             state->get_layer2(),
                             state->get_layer3(),
                             state->get_layer4());
      break;
    case layer_t::None:
      break;
  }
}

void ProcessConsumer(keystate& state, kb_reporter& rpt) {
  // For a consumer control button, there are no modifiers, it's
  // just a simple call. So just call it directly:
  if (state.down) {
    Dbg << "Consumer key press: " << sfmt::hex
        << value_cast(state.action.getConsumer()) << sfmt::endl;
    // See all the codes in all their glory here:
    // https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
    // (And if that doesn't work, check here: https://www.usb.org/hid)
    rpt.consumer_press(state.action.getConsumer());
  } else {
    Dbg << "Consumer key release: " << sfmt::hex
        << value_cast(state.action.getConsumer()) << sfmt::endl;
    rpt.consumer_release(state.action.getConsumer());
    // We have to clear this thing out when we're done, because we take
    // action on the key release as well. We don't do this for the normal
    // keyboardReport.
    state.scanCode = null_scan_code;
  }
}

char rotr(char c, int num) {
  if (num > 7 || num < 1)
    return 0;
  return static_cast<char>((static_cast<uint8_t>(c) >> num) |
                           (static_cast<uint8_t>(c) << (8 - num)));
}

// Dump the secrets in a header file that has a silly "just don't have this
// stuff sitting around in plain text" cypher (use make_secrets.cpp to generate
// the data) just don't add it to the repo: Put it somewhere else (like in
// SyncThing :D )
void TypeMacro(uint16_t macroNumber) {
  if (macroNumber < secrets.size()) {
    const char* sec = secrets[macroNumber];
    int r = 1;
    for (char s = *sec++; s; s = *sec++) {
      char c = rotr(s, r);
      r = (r + c) % 6 + 1;
      Keyboard.print(c);
      // Add a little randomness in to the typing, for shiggles, I guess...
      delay(r * (c & 7));
    }
  } else {
    Keyboard.print("Unrecognized macro number ");
    Keyboard.print(macroNumber);
  }
}

KeyboardMode ProcessKeys(uint32_t now, kb_reporter& rpt) {
  Modifiers mods = Modifiers::None;
  KeyboardMode mode = KeyboardMode::Normal;
  for (auto& state : keyStates) {
    if (state.scanCode == null_scan_code)
      continue;
    KeyAction actions = state.action.getAction();
    switch (actions) {
      case KeyAction::TapHold: {
        // TODO: I don't think this quite works...

        // If we've exceeded the time limit, set the modifier
        // If we're under the time limit, and it's a key *down* we shouldn't
        // do anything, because we won't know what to do until after the time
        // limit is hit, or a key-up occurs.
        if (now - state.lastChange > TapAndHoldTimeLimit) {
          // Holding
          mods = mods | state.action.getExtraMods();
          Dbg << " (Holding)" << sfmt::bin << value_cast(mods) << sfmt::endl;
          rpt.set_modifier(mods);
        } else if (state.down) {
          continue;
        }
        // We've had it for less than the time allotted, so send the tapping key
        // TODO: Make sure we send the key up immediate after this!
        if (state.action.getAction() == KeyAction::Consumer) {
          Dbg << "Tapping consumer key: " << sfmt::hex
              << value_cast(state.action.getConsumer()) << sfmt::endl;
          state.down = true;
          ProcessConsumer(state, rpt);
          state.down = false;
          ProcessConsumer(state, rpt);
        } else {
          Keystroke key = state.action.getKeystroke();
          if (key != Keystroke::None) {
            rpt.add_key_press(key);
            Dbg << " Tapping" << sfmt::hex << value_cast(key) << sfmt::endl;
          }
        }
        break;
      }
      case KeyAction::Consumer: {
        ProcessConsumer(state, rpt);
        break;
      }
      case KeyAction::KeyAndMods: {
        if (state.down) {
          mods = mods | state.action.getExtraMods();
          rpt.set_modifier(mods);
          Keystroke key = state.action.getKeystroke();
          if (key != Keystroke::None) {
            rpt.add_key_press(key);
          }
        }
        break;
      }
      case KeyAction::KeyPress: {
        if (state.down) {
          Keystroke key = state.action.getKeystroke();
          if (key != Keystroke::None) {
            rpt.add_key_press(key);
          }
        }
        break;
      }
      case KeyAction::Modifier: {
        if (state.down) {
          mods = mods | state.action.getModifiers();
          rpt.set_modifier(mods);
        }
        break;
      }
      case KeyAction::Mode: {
        if (state.down) {
          Dbg2 << state << sfmt::endl;
          mode = state.action.getMode();
        }
        break;
      }
      case KeyAction::LayerShift:
      case KeyAction::LayerSwitch:
      case KeyAction::LayerToggle:
      case KeyAction::LayerRotate3:
      case KeyAction::LayerRotate4:
        // These are all handled during preprocessing
        break;
      case KeyAction::Macro:
        if (state.down)
          TypeMacro(state.action.getMacro());
        break;
    }
  }
  rpt.send_keys();
  return mode;
}
