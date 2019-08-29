#pragma once

#include "mybluefruit.h"

#include <array>

#include "hardware.h"

class Sync {
  enum class State : uint8_t { Initial };
  static constexpr size_t sampleSize = 5;
  std::array<uint8_t, sampleSize> lsamples;
  std::array<uint8_t, sampleSize> rsamples;
  uint8_t lLoc, rLoc;
  State state;

 public:
  Sync() : lLoc(0), rLoc(0), state(State::Initial) {}
  void Buffer(uint32_t time, state::hw& left, state::hw& right);
  void ReportSync(bool isLeft, uint8_t latency);
};
