#pragma once

#include "sysstuff.h"

#include "dbgcfg.h"
#include "hardware.h"
#include "sleepstate.h"

class KBClient {
  BLEDis bledis;
  uint32_t stateTime;
  SleepState sleepState;
  state::hw lastRead;

 public:
  BLEUart bleuart;

  KBClient()
      : lastRead{}, stateTime{0}, sleepState{0, false} {}
  void setup(const char* name);
  void loop();
};

extern KBClient theClient;
