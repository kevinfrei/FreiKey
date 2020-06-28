#include "sysstuff.h"

#include "boardio.h"
#include "dongle.h"
#include "general.h"
#include "hardware.h"
#include "host-comm.h"
#include "sync.h"

bool waiting;
uint32_t locTime;
GeneralState curState{};

void comm::send::sync(BLEClientUart& uart) {
  waiting = true;
  locTime = millis();
  DBG2(dumpVal(locTime, "Local time at sync(1) send"));
  send_packet<comm::types::SYNC>(uart);
}

void comm::send::set_led(BLEClientUart& uart, uint8_t brightness) {
  send_packet<comm::types::SETLED>(uart, brightness);
}

void comm::send::set_red(BLEClientUart& uart, bool on) {
  send_packet<comm::types::SETRED>(uart, on);
}

void comm::send::set_blue(BLEClientUart& uart, bool on) {
  send_packet<comm::types::SETBLUE>(uart, on);
}

uint8_t whichOne(BLEClientUart& uart) {
  return (&uart == &Dongle::leftUart) ? comm::LEFT_SIDE : comm::RIGHT_SIDE;
}

void comm::recv::data(BLEClientUart& uart) {
  comm::header h;
  uint8_t buf[15];
  buf[0] = waitForByte(uart);
  DBG2(dumpHex(buf[0], "R:"));
  memcpy(reinterpret_cast<char*>(&h), &buf, 1);
  for (uint8_t i = 0; i < h.size; i++) {
    buf[i] = waitForByte(uart);
    DBG2(dumpHex(buf[i], "RB:"));
  }
  switch (h.type) {
    case comm::types::SCAN: {
      MatrixBits b;
      b.write(buf);
      comm::recv::scan(whichOne(uart), b);
    } break;
    case comm::types::BATTERY:
      comm::recv::battery(whichOne(uart), buf[0]);
      break;
    case comm::types::TIME: {
      uint32_t time;
      memcpy(reinterpret_cast<char*>(&time), buf, sizeof(time));
      comm::recv::time(whichOne(uart), time);
    } break;
    default:
      // TODO: ERROR!
      break;
  }
}

void comm::recv::scan(uint8_t which, const MatrixBits& b) {
  // Put the data in the queue
  state::hw* newData = new state::hw;
  bool isLeft = which == comm::LEFT_SIDE;
  DBG2(b.dumpHex(isLeft ? "Left Scan " : "Right Scan "));
  newData->switches = b;
  newData->battery_level =
      isLeft ? curState.left.battery : curState.right.battery;
  state::data_queue.push(
      {isLeft ? &Dongle::leftUart : &Dongle::rightUart, newData});
}

void comm::recv::battery(uint8_t which, uint8_t pct) {
  if (which == comm::LEFT_SIDE) {
    curState.left.battery = pct;
  } else {
    curState.right.battery = pct;
  }
}

void comm::recv::time(uint8_t which, uint32_t time) {
  waiting = false;
  timeSync.ReportSync(which == comm::LEFT_SIDE);
  uint32_t locUpdate = millis();
  if (which == comm::LEFT_SIDE) {
    DBG2(dumpVal(time, "Left time "));
    // digitalWrite(LED_BLUE, HIGH);
  } else {
    DBG2(dumpVal(time, "Right time "));
    // digitalWrite(LED_RED, HIGH);
  }
  DBG2(dumpVal(locUpdate, "Local time "));
  DBG2(dumpVal(locUpdate - locTime, "Latency: "));
}
