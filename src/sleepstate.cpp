#include "sleepstate.h"
#include "boardio.h"
#include "hardware.h"

bool SleepState::CheckForSleeping(uint64_t switches,
                                  uint32_t time,
                                  const BoardIO& board) {
  // If we're in forced sleep mode, don't wake up
  if (!forced) {
    // First, handle sleeping states
    if (switches) {
      // We detected a keypress!
      if (sleeping) {
        // Turn off the LED if we were sleeping
        board.setLED(0);
      }
      sleeping = false;
      lastPressTime = time;
    } else if (!sleeping && (time - lastPressTime > 300000)) {
      // 5 minutes before we sleep
      // Do other stuff to get into low power mode, here!
      sleeping = true;
    }
  }
  if (sleeping || forced) {
    // This should make the LED 'breathe' a bit
    uint8_t brightness = (time >> 9) & 0x1F;
    if (brightness > 0x10)
      brightness = 0x20 - brightness;
    board.setLED(brightness);
  }
  return sleeping;
}

void SleepState::BeginForcedSleepMode() {
  forced = true;
}

void SleepState::EndForcedSleepMode() {
  forced = false;
}
