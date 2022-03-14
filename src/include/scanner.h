#pragma once

#include "sysstuff.h"

#include "kbreporter.h"
#include "keystate.h"
#include "pullbit.h"

// variable declarations
constexpr uint8_t num_keystates = 10;
extern keystate keyStates[num_keystates];

// Functions
void layer_switch(layer_t layer);
void layer_toggle(layer_t layer);
void layer_pop(layer_t layer);
void layer_push(layer_t layer);
uint32_t getColorForCurrentLayer();
keystate* findStateSlot(scancode_t scanCode);
void preprocessScanCode(scancode_t sc, bool pressed, uint32_t now);
void ProcessKeys(uint32_t now, kb_reporter& rpt);

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
template <typename T>
scancode_t getNextScanCode(T& delta, T& curState, bool& pressed) {
  scancode_t sc = pull_a_bit(delta);
  pressed = curState.test(sc);
  return sc;
}

inline scancode_t validate(uint8_t b, bool& pressed) {
  DBG2(dumpHex(b, "Validating Scan code 0x"));
  b--;
  uint8_t sc = b / 3;
  uint8_t chk = b % 3;
  if (sc % 3 != chk) {
    // Error!
    DBG(dumpHex(b, "Invalid scan code received 0x"));
    return 0xFF;
  } else {
    pressed = (sc < 36); // TODO: Encode all this shit somewhere?
    DBG2(dumpVal(pressed ? 1 : 0, "Pressed: "));
    DBG2(dumpHex(sc, "Raw scan code 0x"));
    if (!pressed) {
      sc -= 36;
    }
    DBG2(dumpHex(sc, "Validated scan code 0x"));
    return sc;
  }
}

// Template specialization for remote modules
template <>
inline scancode_t getNextScanCode<HardwareSerial>(HardwareSerial& left,
                                                  HardwareSerial& right,
                                                  bool& pressed) {
  scancode_t sc = 0xFF;
  if (left.available()) {
    sc = validate(left.read(), pressed);
    if (sc != 0xFF) {
      sc = (sc / 6) * 12 + 5 - sc % 6;
    }
  } else if (right.available()) {
    sc = validate(right.read(), pressed);
    if (sc != 0xFF) {
      sc = (sc / 6) * 12 + 11 - sc % 6;
    }
  } else {
    return 0xFF;
  }
  DBG2(dumpVal(pressed ? 1 : 0, "Pressed: "));
  return sc;
}