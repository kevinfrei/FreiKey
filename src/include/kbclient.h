#pragma once

#include "sysstuff.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "hardware.h"
#include "sleepstate.h"

class KBClient {
  BLEDis bledis;
  uint32_t stateTime;
  SleepState sleepState;
  state::hw lastRead;

 public:
  const BoardIO theBoard;
  BLEUart bleuart;

  KBClient(const BoardIO& board)
      : lastRead{}, theBoard(board), stateTime{0}, sleepState{0, false} {}
  void setup(const char* name);
  void loop();
};

extern KBClient theClient;
