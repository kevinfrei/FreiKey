#pragma once

#include "boardio.h"
#include "hardware.h"

namespace state {

struct led {
  MatrixBits left_state;
  MatrixBits right_state;
  uint32_t (*get_led_value)(const state::hw& switches, uint32_t time_offset);
  uint32_t time;
  static const led* get(const state::hw& switches, uint8_t layer = 0);
};

} // namespace state
