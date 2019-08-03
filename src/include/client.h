#pragma once

#include "mybluefruit.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "hardware.h"
#include "led_states.h"
#include "sleepstate.h"

class Client {
  BLEDis bledis;
  BLEUart bleuart;
  uint32_t stateTime;
  SleepState sleepState;
  state::hw lastRead;
  const state::led* curState = nullptr;
  const BoardIO theBoard;

 public:
  Client(const BoardIO& board)
      : lastRead{}, theBoard(board), stateTime{0}, sleepState{0, false} {}
  void setup(const char* name);
  void loop();
};
