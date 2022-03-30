#include "sleepstate.h"
#include "boardio.h"
#include "hardware.h"

bool SleepState::CheckForSleeping(MatrixBits& switches, uint32_t time) {
  // If we're in forced sleep mode, don't wake up
  if (!forced) {
    // First, handle sleeping states
    if (switches.any()) {
      // We detected a keypress!
      if (sleeping) {
        // Turn off the LED if we were sleeping
        BoardIO::setLED(0);
        DBG(dumpVal(lastPressTime, "Exiting sleep from "));
      }
      sleeping = false;
      lastPressTime = time;
    } else if (!sleeping && (time - lastPressTime > 300000)) {
      // 5 minutes before we sleep
      // Do other stuff to get into low power mode, here!
      sleeping = true;
      DBG(dumpVal(time, "Entering sleep from "));
    }
  }
  if (sleeping || forced) {
    // Blink the LED a little bit
    uint8_t brightness = !((time >> 9) & 3);
    BoardIO::setLED(brightness);
  }
  return sleeping;
}

void SleepState::BeginForcedSleepMode() {
  DBG(dumpVal(lastPressTime, "Forced sleep at "));
  forced = true;
}

void SleepState::EndForcedSleepMode() {
  DBG(dumpVal(lastPressTime, "Forced sleep stopped at "));
  forced = false;
  sleeping = true;
}
