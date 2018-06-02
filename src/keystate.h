action_t resolveActionForScanCodeOnActiveLayer(uint8_t scanCode);

struct keystate {
  // The time this keystate was changed (using millis())
  uint32_t lastChange;
  // The action this key state is referring to.
  // This comes from the keymap when the key is pressed.
  action_t action;
  // The scan code of the key this action is about
  scancode_t scanCode;
  // Is this a press or release?
  bool down;

  layer_t get_layer() const {
    return action & 0xff;
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
      }
    }
    switch (action & kMask) {
      case kLayerShift:
        return down ? kPushLayer : kPopLayer;
      case kLayerToggle:
        return down ? kToggleLayer : 0;
      case kLayerSwitch:
        return down ? kLayerSwitch : 0;
    }
    return 0;
  };
#if DEBUG
  void dump() const {
    Serial.print("ScanCode=");
    Serial.print(scanCode, HEX);
    Serial.print(" down=");
    Serial.print(down);
    Serial.print(" lastChange=");
    Serial.print(lastChange);
    Serial.print(" action=");
    Serial.print(action, HEX);
    Serial.println("");
  };
#endif
};
