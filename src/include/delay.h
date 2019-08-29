#pragma once

#include "mybluefruit.h"

#include <array>

#include "hardware.h"

class Delay {
  static constexpr size_t sampleSize = 5;
  std::array<uint8_t, sampleSize> lsamples;
  std::array<uint8_t, sampleSize> rsamples;
  uint8_t lLoc, rLoc;
  bool firstCheck;
  bool waiting;
  bool bothSides;

 public:
  Delay()
      : lLoc(0), rLoc(0), firstCheck(true), waiting(false), bothSides(false) {}
  void Buffer(uint32_t time, state::hw& left, state::hw& right);
  void ReportSync(bool isLeft, uint8_t latency);
};
