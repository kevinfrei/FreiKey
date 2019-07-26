#if !defined(LED_STATES_H)
#define LED_STATES_H

#include "hardware.h"
#include "boardio.h"

namespace state {

struct led {
  BoardIO::bits left_state;
  BoardIO::bits right_state;
  uint32_t (*get_led_value)(const state::hw& switches, uint32_t time_offset);
  uint32_t time;
  static const led* get(const state::hw& switches, uint8_t layer = 0);
};

} // namespace state
#endif
