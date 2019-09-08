#include "sysstuff.h"

#include "Adafruit_NeoPixel.h"

#include "comm.h"
#include "dbgcfg.h"
#include "dongle.h"
#include "hardware.h"
#include "helpers.h"
#include "keymap.h"
#include "keystate.h"
#include "scanner.h"
#include "sync.h"

// I'm going to update this to keep track of additional state.
// Each key 'previously' pressed should have a 'time last pressed'
// Maybe keep track of whether other keys have been pressed since?
//  Perhaps have a flag for something that's a "Normal" key?
// The core idea:
//  I want to be able to trigger something off of both the "key pressed"
//  as well as the "key released". In addition, I want to do things that
//  'cancel out' the key state if something specific occurs

// Kind of things I want to do:
// #0: Consumer keys, dammit!
// #1: Some sort of time-sync capability
// #2: Key-up triggering
// #3: Cancellation
// #4: Key-state back & forth (caps as a real cmd/ctrl, instead of a layer
// shift)

state::hw leftSide{};
state::hw rightSide{};

// Declarations

keystate keyStates[6];
constexpr layer_t layer_max = 7;
layer_t layer_stack[layer_max + 1];
layer_t layer_pos = 0;

// This is called when a device connects, disconnects, and when the system is
// initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  layer_pos = 0;
  layer_stack[0] = 0;
  leftSide = state::hw{};
  rightSide = state::hw{};
  memset(keyStates, not_a_scancode, sizeof(keyStates));
  Dongle::Reset();
}

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
    if (s.scanCode == not_a_scancode) {
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
    return vacant;
  }
  return reap;
}

// Find the first specified action in the layer stack
action_t resolveActionForScanCodeOnActiveLayer(uint8_t scanCode) {
  layer_t s = layer_pos;
  while (s > 0 && keymap[layer_stack[s]][scanCode] == ___) {
    --s;
  }
  return keymap[layer_stack[s]][scanCode];
}

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
scancode_t getNextScanCode(BoardIO::bits& delta,
                           BoardIO::bits curState,
                           bool& pressed) {
  scancode_t sc = delta.pull_a_bit();
  pressed = curState.get_bit(sc);
  return sc;
}

#if defined(DEBUG)
void dumpScanCode(uint8_t sc, bool pressed) {
  Serial.print("Scan Code ");
  Serial.print(sc, HEX);
  Serial.print(" was ");
  Serial.println(pressed ? "pressed" : "released");
}
void dumpLayers() {
  Serial.print("Layer stack: ");
  for (int i = 0; i <= layer_pos; i++) {
    Serial.print(layer_stack[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
#endif

void layer_push(layer_t layer) {
  DBG(dumpVal(layer, "Push "));
  if (layer_pos < layer_max)
    layer_stack[++layer_pos] = layer;
  DBG(dumpLayers());
}

void layer_pop(layer_t layer) {
  DBG(dumpVal(layer, "Pop "));
  if (layer_pos > 0)
    --layer_pos;
  DBG(dumpLayers());
}

void layer_toggle(layer_t layer) {
  // Toggling a layer: If it exists *anywhere* in the layer stack, turn it
  // off (and fold the layer stack down) If it's *not* in the layer stack,
  // add it.
  for (layer_t l = layer_pos; l != 0; l--) {
    if (layer_stack[l] == layer) {
      DBG(dumpVal(layer, "Turning off layer "));
      DBG(dumpVal(l, "at location "));
      if (layer_pos != l) {
        DBG(dumpVal(layer_pos - l, "Shifting by "));
        memmove(&layer_stack[l], &layer_stack[l + 1], layer_pos - l);
      }
      layer_pos--;
      DBG(dumpLayers());
      return;
    }
  }
  DBG(Serial.print("(For Toggle) "));
  layer_push(layer);
}

void layer_switch(layer_t layer) {
  DBG(dumpVal(layer_stack[layer_pos], "Switching layer "));
  DBG(dumpVal(layer, "to layer "));
  layer_stack[layer_pos] = layer;
  DBG(dumpLayers());
}

// Check to see if we should update the battery level and if so, do so
void updateBatteryLevel(const state::hw& downLeft, const state::hw& downRight) {
  if (downRight.battery_level != rightSide.battery_level ||
      downLeft.battery_level != leftSide.battery_level) {
    // We only get the battery level from the left side once you hit a key, so
    // only report it if we have something to actually report
    // TODO: Update something here.
    rightSide.battery_level = downRight.battery_level;
    leftSide.battery_level = downLeft.battery_level;
  }
}

uint32_t lastTime;
Sync timeSync{};

void loop() {
  uint32_t now = millis();
  Dongle::updateClientStatus(now);
  if (!Dongle::Ready())
    return;
  //  // Remote wakeup
  //  if ( tud_suspended() && btn )
  //  {
  //    // Wake up host if we are in suspend mode
  //    // and REMOTE_WAKEUP feature is enabled by host
  //    tud_remote_wakeup();
  //  }

  // Get the hardware state for the two sides...
  state::hw downRight{Dongle::rightUart, rightSide};
  state::hw downLeft{Dongle::leftUart, leftSide};

  if (timeSync.Buffer(now, downLeft, downRight)) {
    timeSync.Delay(now, downLeft, leftSide);
  } else {
    timeSync.Delay(now, downRight, rightSide);
  }
  // Update the combined battery level
  updateBatteryLevel(downLeft, downRight);

  // Get the before & after of each side into a 64 bit value
  BoardIO::bits beforeLeft{leftSide.switches};
  BoardIO::bits afterLeft{downLeft.switches};
  BoardIO::bits beforeRight{rightSide.switches};
  BoardIO::bits afterRight{downRight.switches};

  BoardIO::bits deltaLeft = beforeLeft.delta(afterLeft);
  BoardIO::bits deltaRight = beforeRight.delta(afterRight);
  bool keysChanged = deltaLeft.any() || deltaRight.any();

  while (deltaLeft.any() || deltaRight.any()) {
    scancode_t sc;
    bool pressed;
    if (deltaLeft.any()) {
      sc = getNextScanCode(deltaLeft, afterLeft, pressed);
    } else {
      // Add offset to the right scan code...
      sc = getNextScanCode(deltaRight, afterRight, pressed) +
           BoardIO::matrix_size;
    }
    DBG2(dumpScanCode(sc, pressed));

    // Get a state slot for this scan code
    keystate* state = findStateSlot(sc);
    if (!state) {
      // If this is a keydown and we don't have an available state slot just
      // ignore it. If we chose to toss out older keydowns instead, things could
      // get pretty weird. If this is a keyup, and we still don't have a state
      // slot, that's a little bonkers, but there's not much we can do about it.
      continue;
    }
    // State update returns a layer action to perform...
    switch (state->update(sc, pressed, now)) {
      case kPushLayer:
        layer_push(state->get_layer());
        break;
      case kPopLayer:
        layer_pop(state->get_layer());
        break;
      case kToggleLayer:
        layer_toggle(state->get_layer());
        break;
      case kSwitchLayer:
        layer_switch(state->get_layer());
        break;
    }
  }

  if (keysChanged) {
    uint8_t report[6] = {0, 0, 0, 0, 0, 0};
    uint8_t repsize = 0;
    uint8_t mods = 0;

    for (auto& state : keyStates) {
      if (state.scanCode == not_a_scancode)
        continue;
      if ((state.action & kConsumer) == kConsumer) {
        // For a consumer control button, there are no modifiers, it's
        // just a simple call. So just call it directly:
        if (state.down) {
          DBG2(dumpHex(state.action & kConsumerMask, "Consumer key press: "));
          // See all the codes in all their glory here:
          // https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
          // (And if that doesn't work, check here: https://www.usb.org/hid)
          Dongle::ConsumerPress(state.action & kConsumerMask);
        } else {
          DBG2(dumpHex(state.action & kConsumerMask, "Consumer key release: "));
          Dongle::ConsumerRelease();
          // We have to clear this thing out when we're done, because we take
          // action on the key release as well. We don't do this for the normal
          // keyboardReport.
          state.scanCode = not_a_scancode;
        }
      } else if (state.down) {
        switch (state.action & kActionMask) {
          case kTapHold:
            if (now - state.lastChange > 200) {
              // Holding
              mods |= (state.action >> 16) & 0xff;
            } else {
              // Tapping
              uint8_t key = state.action & 0xff;
              if (key != 0 && repsize < 6) {
                report[repsize++] = key;
              }
            }
            break;
          case kKeyAndMod: {
            mods |= (state.action >> 16) & 0xff;
            uint8_t key = state.action & 0xff;
            if (key != 0 && repsize < 6) {
              report[repsize++] = key;
            }
          } break;
          case kKeyPress: {
            uint8_t key = state.action & 0xff;
            if (key != 0 && repsize < 6) {
              report[repsize++] = key;
            }
          } break;
          case kModifier:
            mods |= state.action & 0xff;
            break;
          case kToggleMod:
            mods ^= state.action & 0xff;
            break;
        }
      }
    }

    // Update the hardware previous state
    rightSide = downRight;
    leftSide = downLeft;

    Dongle::ReportKeys(mods, report);
    DBG2(Serial.println("============================="));
    DBG2(Serial.print("Left side "));
    DBG2(downLeft.dump());
    DBG2(Serial.print("Right side "));
    DBG2(downRight.dump());
  }

  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}

// In Arduino world the 'setup' function is called to initialize the device.
// The 'loop' function is called over & over again, after setup completes.
void setup() {
  Dongle::Configure();
  resetTheWorld();
  Dongle::StartListening();
  lastTime = millis();
}
