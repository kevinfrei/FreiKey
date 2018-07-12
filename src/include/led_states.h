#if !defined(LED_STATES_H)
#define LED_STATES_H

#include "hardware.h"

namespace state {

struct led {
  uint64_t left_state;
  uint64_t right_state;
  uint32_t (*get_led_value)(const state::hw& switches, uint32_t time_offset);
  uint32_t time;
  static const led* get(const state::hw& switches, uint8_t layer = 0);
};

} // namespace state
#endif
