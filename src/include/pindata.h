#if !defined(PINDATA_H)
#define PINDATA_H
#include <bluefruit.h>

struct PinData {
  static const uint8_t numcols = 7;
  static const uint8_t numrows = 6;
  static const uint8_t matrix_size = numcols * numrows;
  uint8_t cols[numcols];
  uint8_t rows[numrows];
  uint8_t led;
  uint64_t Read() const;
};

#endif