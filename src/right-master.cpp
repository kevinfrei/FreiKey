#include <bluefruit.h>

#include "dbgcfg.h"
#include "globals.h"
#include "hwstate.h"
#include "shared.h"
#include "status_dump.h"

#include "keyhelpers.h"
#include "keymap.h"
#include "keystate.h"

hwstate leftSide{};
hwstate rightSide{};

constexpr uint8_t status_clear_bonds_left[] = {0x82, 0, 0, 0x80, 0};
constexpr uint8_t status_clear_bonds_right[] = {0x41, 0, 0, 1, 0};

// Declarations

uint16_t core_handle = 0xFFFF;

keystate keyStates[16];
constexpr layer_t layer_max = 7;
layer_t layer_stack[layer_max + 1];
layer_t layer_pos = 0;

// This is called when the LHS connects, disconnects, and when the system is
// initialized.  The idea is that it should just wipe everything clean.
void resetKeyMatrix() {
  layer_pos = 0;
  layer_stack[0] = 0;
  memset(&leftSide, 0, sizeof(leftSide));
  memset(&rightSide, 0, sizeof(rightSide));
  memset(keyStates, 0xff, sizeof(keyStates));

  hid.keyRelease();
}

// Look for a slot that is either already in use for this scan code, or vacant.
// If we don't have a vacant slot, return the oldest, but still in use, slot,
// but only for key-up states, as we're probably through with them anyway.
struct keystate* findStateSlot(uint8_t scanCode) {
  keystate *vacant = nullptr, *reap = nullptr;
  for (auto& s : keyStates) {
    // If we have the same scan code, huzzah!
    if (s.scanCode == scanCode) {
      return &s;
    }
    // If we found a vacancy, potentially use it. We have to keep looking to see
    // if we have the same scan code, though.
    if (s.scanCode == 0xff) {
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

// Find last bit set in a long (BSD function, not available in Arduino)
uint8_t flsl(uint64_t val) {
  // GCC builtin function seems to work on Arduino :)
  return static_cast<uint8_t>(63 - __builtin_clzll(val));
}

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
scancode_t getNextScanCode(uint64_t& delta, uint64_t curState, bool& pressed) {
  scancode_t sc = flsl(delta);
  uint64_t mask = ((uint64_t)1) << sc;
  pressed = curState & mask;
  delta ^= mask;
  return sc;
}

#if DEBUG
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

void loop() {
  uint32_t now = millis();

  // Get the hardware state for the two sides...
  hwstate downRight{now, rightSide};
  hwstate downLeft{clientUart, leftSide};

  // Update the combined battery level
  if (downRight.battery_level != rightSide.battery_level ||
      downLeft.battery_level != leftSide.battery_level) {
    // We only get the battery level from the left side once you hit a key, so
    // only report it if we have something to actually report
    if (downLeft.battery_level) {
      battery.notify((downRight.battery_level + downLeft.battery_level) / 2);
      DBG(dumpVal((downRight.battery_level + downLeft.battery_level) / 2,
                  "battery avg: "));
    } else {
      DBG(dumpVal(downRight.battery_level, "right only battery: "));
      battery.notify(downRight.battery_level);
    }
    rightSide.battery_level = downRight.battery_level;
    leftSide.battery_level = downLeft.battery_level;
  }

  // Get the before & after of each side into a 64 bit value
  uint64_t beforeLeft = leftSide.toUI64(), afterLeft = downLeft.toUI64();
  uint64_t beforeRight = rightSide.toUI64(), afterRight = downRight.toUI64();
  uint64_t deltaLeft = beforeLeft ^ afterLeft;
  uint64_t deltaRight = beforeRight ^ afterRight;
  bool keysChanged = deltaLeft || deltaRight;

  while (deltaLeft || deltaRight) {
    scancode_t sc;
    bool pressed;
    if (deltaLeft) {
      sc = getNextScanCode(deltaLeft, afterLeft, pressed);
    } else {
      // Add offset to the right scan code...
      sc = getNextScanCode(deltaRight, afterRight, pressed) + numcols * numrows;
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
      if (state.scanCode == 0xff)
        continue;
      if ((state.action & kConsumer) == kConsumer) {
        // For a consumer control button, there are no modifiers, it's
        // just a simple call. So just call it directly:
        if (state.down) {
          DBG(dumpHex(state.action & 0xff, "Consumer key press: "));
          hid.consumerKeyPress(state.action & 0xff);
        } else {
          DBG(dumpHex(state.action & 0xff, "Consumer key release: "));
          hid.consumerKeyRelease();
          // We have to clear this thing out when we're done, because we take
          // action on the key release as well. We don't do this for the normal
          // keyboardReport.
          state.scanCode = 0xff;
        }
      } else if (state.down) {
        switch (state.action & kMask) {
          case kTapHold:
            if (now - state.lastChange > 200) {
              // Holding
              mods |= (state.action >> 16) & 0xff;
            } else {
              // Tapping
              auto key = state.action & 0xff;
              if (key != 0 && repsize < 6) {
                report[repsize++] = key;
              }
            }
            break;
          case kKeyAndMod: {
            mods |= (state.action >> 16) & 0xff;
            auto key = state.action & 0xff;
            if (key != 0 && repsize < 6) {
              report[repsize++] = key;
            }
          } break;
          case kKeyPress: {
            auto key = state.action & 0xff;
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
#if DEBUG > 1
    Serial.print("mods=");
    Serial.print(mods, HEX);
    Serial.print(" repsize=");
    Serial.print(repsize);
    for (int i = 0; i < repsize; i++) {
      Serial.print(" ");
      Serial.print(report[i], HEX);
    }
    Serial.println("");
#endif

    // Update the hardware previous state
    rightSide = downRight;
    leftSide = downLeft;

#if STATUS_DUMP
    // If we do a status dump, don't pass the keys pressed on to the computer...
    status_dump_check(rightSide, leftSide);
#endif
    hid.keyboardReport(mods, report);
    DBG2(Serial.println("============================="));
    DBG2(Serial.print("Left side "));
    DBG2(sw::dmp(downLeft.switches));
    DBG2(Serial.print("Right side "));
    DBG2(sw::dmp(downRight.switches));

    if (!sw::cmp(rightSide.switches, status_clear_bonds_right) &&
        !sw::cmp(leftSide.switches, status_clear_bonds_left)) {
      DBG(Serial.println("CLEARING BLUETOOTH BONDS!"));
      Bluefruit.clearBonds();
    }
  }
  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}

void core_connect_callback(uint16_t handle) {
  DBG(dumpHex(handle, "Core Connected: "));
  core_handle = handle;
  char buf[501];
  Bluefruit.Gap.getPeerName(handle, buf, 500);
  DBG(Serial.println("Peer Name:"));
  DBG(Serial.println(buf));
  if (!strstr(buf, "mac")) {
    // If we're not on a mac, set the keyboard in Windows mode
    // This is *incredibly* low-tech, but it works for my purposes :/
    layer_push(LAYER_WIN_BASE);
  }
}

void core_disconnect_callback(uint16_t handle, uint8_t reason) {
  DBG(dumpHex(handle, "Core Disconnected: "));
  DBG(dumpHex(reason, "Reason: 0x"));
  core_handle = 0xFFFF;
}
