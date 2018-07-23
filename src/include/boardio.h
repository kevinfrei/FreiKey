#if !defined(BOARDIO_H)
#define BOARDIO_H

#include "mybluefruit.h"

class BoardIO {
 public:
  static const uint8_t numcols = 7;
  static const uint8_t numrows = 6;
  static const uint8_t matrix_size = numcols * numrows;

  uint8_t cols[numcols];
  uint8_t rows[numrows];
  uint8_t led;

  void Configure() const;
  uint64_t Read() const;
  void setLED(uint32_t brightness) const;
  static uint8_t getBatteryPercent();
};

#endif
