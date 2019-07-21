#include "mybluefruit.h"

#include "boardio.h"
#include "callbacks.h"
#include "dbgcfg.h"
#include "globals.h"
#include "hardware.h"
#include "helpers.h"
#include "keymap.h"
#include "keystate.h"
#include "led_states.h"
#include "scanner.h"
#include "sleepstate.h"
#include "status_dump.h"

// I'm going to update this to keep track of additional state.
// Each key 'previously' pressed should have a 'time last pressed'
// Maybe keep track of whether other keys have been pressed since?
//  Perhaps have a flag for something that's a "Normal" key?
// The core idea:
//  I want to be able to trigger something off of both the "key pressed"
//  as well as the "key released". In addition, I want to do things that
//  'cancel out' the key state if something specific occurs

// Kind of things I want to do:
// #1: Better, intentional debouncing
// #2: Key-up triggering
// #3: Cancellation
// #4: Key-state back & forth (caps as a real cmd/ctrl, instead of a layer
// shift)

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the physical pin numbers...
constexpr BoardIO RightBoard = {
    {29, 16, 15, 7, 27, 11, 30}, {13, 4, 2, 3, 5, 12}, 28};

state::hw leftSide{};
state::hw rightSide{};

// The are the top left & right keys, plus the lowest 'outer' key
constexpr uint64_t status_clear_bonds_left = 0x10000000042ULL;
constexpr uint64_t status_clear_bonds_right = 0x1000000021ULL;

// Declarations

keystate keyStates[16];
constexpr layer_t layer_max = 7;
layer_t layer_stack[layer_max + 1];
layer_t layer_pos = 0;

// This is called when the LHS connects, disconnects, and when the system is
// initialized.  The idea is that it should just wipe everything clean.
void resetTheWorld() {
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

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
scancode_t getNextScanCode(uint64_t& delta, uint64_t curState, bool& pressed) {
  scancode_t sc = get_a_set_bit(delta);
  uint64_t mask = ((uint64_t)1) << sc;
  pressed = curState & mask;
  delta ^= mask;
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

const state::led* curState = nullptr;
uint32_t stateTime = 0;

// Check to see if we should update the battery level and if so, do so
void updateBatteryLevel(const state::hw& downLeft, const state::hw& downRight) {
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
}

// We need to delay the master by a little bit to prevent mis-timing
bool dataWaiting = false;
uint32_t dataTime;
uint64_t switchData;
// # of milliseconds to delay the local keyboard before reporting
// It's kind of surprising how annoying the latency is when I get typing fast...
constexpr uint32_t DELAY = 8;

void loop() {
  uint32_t now = millis();

  // Get the hardware state for the two sides...
  state::hw downRight{now, rightSide, RightBoard};
  state::hw downLeft{clientUart, leftSide};

  // This is the master-side buffering code
  if (downRight.switches != rightSide.switches) {
    // There's a change: put it in the delay buffer
    if (dataWaiting) {
      if (switchData != downRight.switches) {
        // We already have a different change buffered, report it early :/
        std::swap(switchData, downRight.switches);
        dataTime = now;
      } else if (now - dataTime > DELAY) {
        // There's no change from what we're reading, but it's time to report
        dataWaiting = false;
      } else {
        // No changes from the buffered data
        // Sit on this change (i.e. revert to previous)
        downRight.switches = rightSide.switches;
      }
    } else {
      // We have no pending change: Just queue up this one
      dataWaiting = true;
      dataTime = now;
      switchData = downRight.switches;
      downRight.switches = rightSide.switches;
    }
  } else {
    // We've observed the same thing we've already reported
    if (dataWaiting && now - dataTime > DELAY) {
      // we have waiting data ready to report
      std::swap(downRight.switches, switchData);
      dataWaiting = false;
    }
  }

  // For sleeping, look at both sides of the keyboard
  uint64_t down = downRight.switches | downLeft.switches;
  if (sleepState.CheckForSleeping(down, now, RightBoard)) {
    // I'm assuming this saves power. If it doesn't, there's no point...
    delay(250);
    waitForEvent();
    return;
  }

  // Update the combined battery level
  updateBatteryLevel(downLeft, downRight);

  // Get the before & after of each side into a 64 bit value
  uint64_t beforeLeft = leftSide.switches, afterLeft = downLeft.switches;
  uint64_t beforeRight = rightSide.switches, afterRight = downRight.switches;

  // Pseudo-code for what I'm looking to clean up:
#if 0
  std::vector<scancode_t> scanCodes = GetScanCodesForSwitchStates(
      beforeLeft, afterLeft, beforeRight, afterRight);
  PerformActionsForScanCodes(scanCodes);
#endif
  uint64_t deltaLeft = beforeLeft ^ afterLeft;
  uint64_t deltaRight = beforeRight ^ afterRight;
  bool keysChanged = deltaLeft || deltaRight;
  if (deltaRight && !curState) {
    // if we're not already in a state, check to see if we're transitioning
    // into one
    curState = state::led::get(downRight, layer_pos + 1);
    if (curState) {
      stateTime = now;
    }
  }

  if (curState) {
    // We're in some random LED display state. Do something...
    if (now - curState->time < stateTime) {
      RightBoard.setLED(curState->get_led_value(downRight, now - stateTime));
    } else {
      RightBoard.setLED(0);
      curState = nullptr;
    }
  }

  while (deltaLeft || deltaRight) {
    scancode_t sc;
    bool pressed;
    if (deltaLeft) {
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
      if (state.scanCode == 0xff)
        continue;
      if ((state.action & kConsumer) == kConsumer) {
        // For a consumer control button, there are no modifiers, it's
        // just a simple call. So just call it directly:
        if (state.down) {
          DBG2(dumpHex(state.action & 0xff, "Consumer key press: "));
          hid.consumerKeyPress(state.action & 0xff);
        } else {
          DBG2(dumpHex(state.action & 0xff, "Consumer key release: "));
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
              // Tapsg
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
#if defined(DEBUG) && DEBUG > 1
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

#if defined(STATUS_DUMP)
    // If we do a status dump, don't pass the keys pressed on to the computer...
    if (!status_dump_check(rightSide, leftSide))
#endif
      hid.keyboardReport(mods, report);
    DBG2(Serial.println("============================="));
    DBG2(Serial.print("Left side "));
    DBG2(downLeft.dump());
    DBG2(Serial.print("Right side "));
    DBG2(downRight.dump());

    if (rightSide.switches == status_clear_bonds_right &&
        leftSide.switches == status_clear_bonds_left) {
      DBG(Serial.println("CLEARING BLUETOOTH BONDS!"));
      Bluefruit.clearBonds();
    }
  }

  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}

// In Arduino world the 'setup' function is called to initialize the device.
// The 'loop' function is called over & over again, after setup completes.
void setup() {
  DBG(Serial.begin(115200));
  RightBoard.Configure();
  resetTheWorld();

  // Central and peripheral
  Bluefruit.begin(true, true);
  // Bluefruit.clearBonds();
  Bluefruit.autoConnLed(true);

  battery.begin();

  // I'm assuming that by dropping this power down, I'll save some battery life.
  // I should experiment to see how low I can get it and still communicate with
  // both my Mac and my PC reliably. They're each within a meter of the
  // keyboard... Acceptable values: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName(BT_NAME);

  Bluefruit.Central.setConnectCallback(callback::cent_connect);
  Bluefruit.Central.setDisconnectCallback(callback::cent_disconnect);

  dis.setManufacturer(MANUFACTURER);
  dis.setModel(MODEL);
  dis.setHardwareRev(HW_REV);
  dis.setSoftwareRev(__DATE__);
  dis.begin();

  clientUart.begin();
  Bluefruit.Central.setConnectCallback(callback::core_connect);
  Bluefruit.Central.setDisconnectCallback(callback::core_disconnect);
  // clientUart.setRxCallback(cent_bleuart_rx_callback);

  /* Start Central Scanning
   * - Enable auto scan if disconnected
   * - Interval = 100 ms, window = 80 ms
   * - Filter only accept bleuart service
   * - Don't use active scan
   * - Start(timeout) with timeout = 0 will scan forever (until connected)
   */
  Bluefruit.Scanner.setRxCallback(callback::scan);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.filterUuid(BLEUART_UUID_SERVICE);
  Bluefruit.Scanner.useActiveScan(false);
  // I should probably stop advertising after a while if that's possible. I have
  // switches now, so if I need it to advertise, I can just punch the power.
  Bluefruit.Scanner.start(0); // 0 = Don't stop scanning after n seconds

  hid.begin();
  // delay(5000);
  // Bluefruit.printInfo();

  // This gets Advertising going...
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(hid);

  Bluefruit.ScanResponse.addService(battery); // This doesn't seem to work :(

  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30); // number of seconds in fast mode
  Bluefruit.Advertising.start(0); // 0 = Don't stop advertising after n seconds
}
