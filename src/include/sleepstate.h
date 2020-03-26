#pragma once

#include "boardio.h"
#include "hardware.h"

struct SleepState {
  uint32_t lastPressTime;
  bool sleeping;
  bool forced;
  // This updates the SleepState object to reflect the current sleep state
  // It also sets (or clears) the LED to indicate sleep
  bool CheckForSleeping(MatrixBits &switches,
                        uint32_t time);
  void BeginForcedSleepMode();
  void EndForcedSleepMode();
};
