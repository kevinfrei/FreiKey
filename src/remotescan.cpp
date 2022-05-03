#include "sysstuff.h"

#include "dbgcfg.h"
#include "keystate.h"
#include "scanner.h"

#define right Serial2
#define left Serial4

void Scanner::Reset() {}

Scanner::Scanner(uint32_t now) {}

scancode_t validate(uint8_t b, bool& pressed) {
  Dbg2 << "Validating Scan code 0x" << sfmt::hex << b << sfmt::endl;
  b--;
  uint8_t sc = b / 3;
  uint8_t chk = b % 3;
  if (sc % 3 != chk) {
    // Error!
    Dbg2 << "Invalid scan code received 0x" << sfmt::hex << b << sfmt::endl;
    return 0xFF;
  } else {
    pressed = (sc < 36); // TODO: Encode all this shit somewhere?
    Dbg2 << "Pressed: " << (pressed ? 1 : 0) << sfmt::endl;
    Dbg2 << "Raw scan code 0x" << sfmt::hex << sc << sfmt::endl;
    if (!pressed) {
      sc -= 36;
    }
    Dbg2 << "Validated scan code 0x" << sfmt::hex << sc << sfmt::endl;
    return sc;
  }
}

// Template specialization for remote modules
scancode_t Scanner::getNextCode(bool& pressed) {
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
  Dbg2 << "Pressed: " << (pressed ? 1 : 0) << sfmt::endl;
  return sc;
}

void Scanner::Done() {}