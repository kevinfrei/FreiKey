#include <vector>

#include "scanner.h"

std::vector<scancode_t> GetScanCodesForSwitchStates(uint64_t beforeLeft,
                                                    uint64_t afterLeft,
                                                    uint64_t beforeRight,
                                                    uint64_t afterRight) {
  return std::vector<scancode_t>{};
}
void PerformActionsForScanCodes(const std::vector<scancode_t>& scanCodes) {
  return;
}
#if 0
void otherStuff() {

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
}
#endif
