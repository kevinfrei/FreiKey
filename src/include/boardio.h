#pragma once

#include "sysstuff.h"

#include <array>

#include "bit_array.h"

class BoardIO {
 public:
#if defined(MOCKING)
  static const uint8_t numcols = 1;
#elif defined(ADAFRUIT)
  static const uint8_t numcols = 7;
#elif defined(TEENSY)
  static const uint8_t numcols = 12;
#elif defined(MOCKING)
  static const uint8_t numcols = 1;
#endif

  static const uint8_t numrows = 6;
  static const uint8_t matrix_size = numcols * numrows;
  typedef bit_array<matrix_size> bits;
  static constexpr uint8_t byte_size = bits::num_bytes;

  const std::array<uint8_t, numcols> cols;
  const std::array<uint8_t, numrows> rows;
  uint8_t led;

  void Configure() const;
  bits Read() const;
#if defined(HAS_LED)
  void setLED(uint32_t brightness) const;
#endif
#if defined(HAS_BATTERY)
  static uint8_t getBatteryPercent();
#endif
#if defined(ADAFRUIT)
  static void setRed(bool on);
  static void setBlue(bool on);
#endif
};
