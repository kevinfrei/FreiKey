#if !defined(SLEEPSTATE_H)
#define SLEEPSTATE_H

#include "boardio.h"
#include "hardware.h"

struct SleepState {
  uint32_t lastPressTime;
  bool sleeping;
  // This updates the SleepState object to reflect the current sleep state
  // It also sets (or clears) the LED to indicate sleep
  bool CheckForSleeping(uint64_t swtiches, uint32_t time, const BoardIO& board);
};

#endif
