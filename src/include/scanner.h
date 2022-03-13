#pragma once

#include "sysstuff.h"

#include "kbreporter.h"
#include "keystate.h"

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
  scancode_t sc = delta.pull_a_bit();
  pressed = curState.get_bit(sc);
  return sc;
}

inline scancode_t validate(uint8_t b, bool &pressed) {
    b--;
    uint8_t sc = b / 3;
    uint8_t chk = b % 3;
    if (sc % 3 != chk) {
      // Error!
      return 0xFF;
    } else {
      pressed = (sc > 35); // TODO: Encode all this shit somewhere?
      if (pressed) {
        sc -= 36;
      }
      return sc + 1;
    }
}

// Template specialization for remote modules
template<>
inline scancode_t getNextScanCode<HardwareSerial>(HardwareSerial& left,
                                           HardwareSerial& right,
                                           bool &pressed) {
  if (left.available()) {
    return validate(left.read(), pressed);
  } else if (right.available()) {
    scancode_t sc = validate(right.read(), pressed);
    return (sc != 0 && sc != 0xFF) ? sc + 36 : sc;
  }
  return 0;
}