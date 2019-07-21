#if !defined(BOARDIO_H)
#define BOARDIO_H

#include "mybluefruit.h"

#include <array>

class BoardIO {
 public:
  static const uint8_t numcols = 7;
  static const uint8_t numrows = 6;
  static const uint8_t matrix_size = numcols * numrows;

#if !defined(USB_MASTER)
  const std::array<uint8_t, numcols> cols;
  const std::array<uint8_t, numrows> rows;
#endif
  uint8_t led;

  uint64_t Read() const;
  void Configure() const;
  void setLED(uint32_t brightness) const;
  static uint8_t getBatteryPercent();
};

#endif
