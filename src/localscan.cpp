#include "scanner.h"

MatrixBits Scanner::prevBits{0};
Debouncer<BoardIO::matrix_size> Scanner::debouncer{};

MatrixBits Scanner::key_scan(uint32_t now) {
  auto res = BoardIO::Read();
  return Scanner::debouncer.update(res, now);
}

void Scanner::Reset() {
  Scanner::prevBits.reset();
  Scanner::debouncer.reset();
}

Scanner::Scanner(uint32_t tm)
  // Get the before & after of each side into a 64 bit value
  : before{Scanner::prevBits}, after{key_scan(tm)}, delta{0} {
  // Calculate the delta
  delta = before ^ after;
}

scancode_t Scanner::getNextCode(bool& pressed) {
  if (!delta.any()) {
    return null_scan_code;
  }
  return getNextBitSet(delta, after, pressed);
}

void Scanner::Done() {
  Scanner::prevBits = after;
}
