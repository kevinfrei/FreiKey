#pragma once

#include "mybluefruit.h"

#include <array>

#include "bit_array.h"

class BoardIO {
 public:
  static const uint8_t numcols = 7;
  static const uint8_t numrows = 6;
  static const uint8_t matrix_size = numcols * numrows;
  typedef bit_array<matrix_size> bits;
  static constexpr uint8_t byte_size = bits::num_bytes;

  const std::array<uint8_t, numcols> cols;
  const std::array<uint8_t, numrows> rows;
  uint8_t led;

  void Configure() const;
  bits Read() const;
  void setLED(uint32_t brightness) const;
  static uint8_t getBatteryPercent();
  static void setRed(bool on);
  static void setBlue(bool on);
};
