#if !defined(BOARDIO_H)
#define BOARDIO_H

#include "mybluefruit.h"

#include <array>

class BoardIO {
 public:
  static const uint8_t numcols = 7;
  static const uint8_t numrows = 6;
  static const uint8_t matrix_size = numcols * numrows;

  const std::array<uint8_t, numcols> cols;
  const std::array<uint8_t, numrows> rows;
  uint8_t led;

  void Configure() const;
  uint64_t Read() const;
  void setLED(uint32_t brightness) const;
  static uint8_t getBatteryPercent();
  static void setRed(bool on);
  static void setBlue(bool on);
};

#endif
