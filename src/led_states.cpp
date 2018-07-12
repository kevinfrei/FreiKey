#include "led_states.h"

namespace state {

uint32_t batteryFlasher(const state::hw& sw, uint32_t time_offset) {
  if (sw.battery_level > 15) {
    return abs(16 - (time_offset / 4) & 31);
  } else {
    return 10;
  }
}

// TODO: make some blinky states to indicate what mode the keyboard is in
uint32_t macMode(const state::hw& sw, uint32_t time_offset) {
  return (time_offset & 0x40) ? 10 : 0;
}

// TODO: make some blinky states to indicate what mode the keyboard is in
uint32_t winMode(const state::hw& sw, uint32_t time_offset) {
  return (time_offset & 0x20) ? 10 : 0;
}

constexpr led key_states[] = {
    // These are the lower & outer 3 keys to get the battery status
    {0x10408000000ULL, 0x1010200000ULL, batteryFlasher, 1000}};

const led* led::get(const state::hw& sw, uint8_t layer) {
  for (auto& st : key_states) {
    if (sw.switches == ((!layer) ? st.left_state : st.right_state)) {
      return &st;
    }
  }
  return nullptr;
}

}