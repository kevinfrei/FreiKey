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
  layer_num get_layer1() const {
    return action.getLayer1();
  }
  layer_num get_layer2() const {
    return action.getLayer2();
  }
  layer_num get_layer3() const {
    return action.getLayer3();
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
      Dbg2 << "Updated transition time for scancode " << sc << sfmt::endl;
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
      Dbg2 << "Set lastChange for new scancode " << sc << sfmt::endl;
    }
    Dbg2 << (pressed ? "(Pressed)" : "(Released)");
    switch (action.getAction()) {
      case KeyAction::LayerShift:
        return down ? layer_t::Push : layer_t::Pop;
      case KeyAction::LayerToggle:
        return down ? layer_t::Toggle : layer_t::None;
      case KeyAction::LayerSwitch:
        return down ? layer_t::Switch : layer_t::None;
      case KeyAction::LayerRotate:
        return down ? layer_t::Rotate : layer_t::None;
      default:
        return layer_t::None;
    }
  };
};

inline SerialStream& operator<<(SerialStream& s, const keystate& ks) {
  s << "ScanCode=" << sfmt::hex << ks.scanCode << " down=" << ks.down
    << " lastChange=" << ks.lastChange << " action=" << ks.action << sfmt::endl;
    return s;
}
