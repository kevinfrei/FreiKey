#pragma once

#include "sysstuff.h"

#include "dbgcfg.h"
#include "hardware.h"

class KBClient {
  static BLEDis bledis;
  static uint32_t stateTime;
  static state::hw lastRead;
  static uint16_t noChanges;
  static constexpr uint16_t CHANGE_COUNT_BEFORE_SLEEP = 2500;

  static volatile bool interruptsEnabled;
  static volatile bool interruptTriggered;

  static void enableInterrupts();
  static void disableInterrupts();
  static void interruptHandler();

 public:
  static BLEUart bleuart;

  static void setup(const char* name);
  static void loop();
};
