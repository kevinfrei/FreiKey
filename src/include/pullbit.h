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