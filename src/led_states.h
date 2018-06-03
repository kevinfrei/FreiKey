#if !defined(LED_STATES_H)
#define LED_STATES_H

#include "hwstate.h"

struct led_state {
  uint64_t left_state;
  uint64_t right_state;
  uint32_t (*get_led_value)(const hwstate &switches, uint32_t time_offset);
  uint32_t time;
};

const led_state *getState(const hwstate &switches, uint8_t layer = 0);

#endif