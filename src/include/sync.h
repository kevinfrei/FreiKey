#pragma once

#include "mybluefruit.h"

#include <array>

#include "hardware.h"

class Sync {
  enum class State : uint8_t {
    BothNotConnected,
    BothSidesFirstConnected,
    StartFullSync,
    LeftSent,
    LeftReceived,
    RightSent,
    RightReceived,
    EndFullSync,
    BothSidesConnectedBoring,
    BothSidesConnectedPing,
    StartPing,
    LRSent,
    LRReceived,
    EndPing
  };
  static constexpr size_t sampleSize = 10;
  // Circular buffers of recent latencies
  std::array<uint8_t, sampleSize> lsamples;
  std::array<uint8_t, sampleSize> rsamples;
  uint8_t lLoc, rLoc;
  State state;
  bool isLeft;
  bool leftPacketReceived, rightPacketReceived;
  uint32_t lastTapOrPing;
  uint32_t sendTime;
  int8_t lLatency, rLatency;

  bool dataWaiting;
  uint32_t dataTime;
  BoardIO::bits delayData;
  uint8_t DELAY;

 public:
  Sync()
      : lLoc(0),
        rLoc(0),
        state(State::BothNotConnected),
        rightPacketReceived(false),
        leftPacketReceived(false),
        lastTapOrPing(0),
        lLatency(0),
        rLatency(0),
        DELAY(0),
        dataWaiting(false) {}
  bool Buffer(uint32_t time, state::hw& left, state::hw& right);
  void ReportSync(bool isLeft);
  void UpdateLatency();
  void Delay(uint32_t time, state::hw& down, state::hw& prev);
};

extern Sync timeSync;