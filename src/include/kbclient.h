#pragma once

#include "sysstuff.h"

#include "dbgcfg.h"
#include "hardware.h"
#include "sleepstate.h"

class KBClient {
  static BLEDis bledis;
  static uint32_t stateTime;
  static SleepState sleepState;
  static state::hw lastRead;
  static volatile bool interruptsEnabled;
  static volatile bool interruptTriggered;
  static uint32_t lastDelta;
  static bool notified;

  static void enableInterrupts();
  static void disableInterrupts();
  static void interruptHandler();

 public:
  static BLEUart bleuart;

  static void setup(const char* name);
  static void loop();
};
