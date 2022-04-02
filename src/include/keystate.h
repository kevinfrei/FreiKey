#pragma once

#include "action.h"
#include "dbgcfg.h"
#include "enumtypes.h"

using scancode_t = uint8_t;
constexpr scancode_t null_scan_code = 0xff;
constexpr uint16_t null_consumer_code = 0x8000;
action_t resolveActionForScanCodeOnActiveLayer(uint8_t scanCode);

struct keystate {
  // The time this keystate was changed (using millis())
  uint32_t lastChange;
  // The action this key state is referring to.
  // This comes from the keymap when the key is pressed.
  action_t action = no_action;
  // The scan code of the key this action is about
  scancode_t scanCode;
  // Is this a press or release?
  bool down;

  layer_num get_layer() const {
    return action.getLayer();
  }

  layer_t update(scancode_t sc, bool pressed, uint32_t now) {
    if (scanCode == sc) {
      // Update the transition time, if any
      if (down != pressed) {
        lastChange = now;
        down = pressed;
        if (pressed) {
          action = resolveActionForScanCodeOnActiveLayer(scanCode);
        }
      }
    } else {
      // We claimed a new slot, so set the transition
      // time to the current time.
      down = pressed;
      scanCode = sc;
      lastChange = now;
      if (pressed) {
        action = resolveActionForScanCodeOnActiveLayer(scanCode);
      } else {
        action = no_action;
      }
    }
    switch (action.getAction()) {
      case KeyAction::LayerShift:
        return down ? layer_t::Push : layer_t::Pop;
      case KeyAction::LayerToggle:
        return down ? layer_t::Toggle : layer_t::None;
      case KeyAction::LayerSwitch:
        return down ? layer_t::Switch : layer_t::None;
      default:
        return layer_t::None;
    }
  };
#if defined(DEBUG)
  void dump() const {
    Serial.print("ScanCode=");
    Serial.print(scanCode, HEX);
    Serial.print(" down=");
    Serial.print(down);
    DBG3(Serial.print(" lastChange="));
    DBG3(Serial.print(lastChange));
    Serial.print(" action=");
    action.dump();
    Serial.println("");
  };
#endif
};
