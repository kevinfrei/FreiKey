#pragma once

#include "sysstuff.h"
#include <bitset>

template <size_t SZ>
uint8_t pull_a_bit(std::bitset<SZ>& bits) {
  for (uint8_t i = 0; i < bits.size(); i++) {
    if (bits.test(i)) {
      bits.reset(i);
      return i;
    }
  }
  return 0xFF;
}

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
template <size_t T>
uint8_t getNextBitSet(std::bitset<T>& delta,
                      std::bitset<T>& curState,
                      bool& pressed) {
  uint8_t sc = pull_a_bit(delta);
  pressed = curState.test(sc);
  return sc;
}