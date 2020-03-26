#include "sysstuff.h"

#include "boardio.h"
#include "client-comm.h"
#include "kbclient.h"

void comm::send::scan(BLEUart& uart, const MatrixBits& b) {
  send_packet<comm::types::SCAN>(uart, b);
}

void comm::send::battery(BLEUart& uart, uint8_t pct) {
  send_packet<comm::types::BATTERY>(uart, pct);
}

void comm::send::time(BLEUart& uart, uint32_t time) {
  send_packet<comm::types::TIME>(uart, time);
}

void comm::recv::data(uint16_t handle) {
  comm::header h;
  uint8_t buf[15];
  buf[0] = waitForByte(theClient.bleuart);
  DBG2(dumpHex(buf[0], "r:"));
  memcpy(reinterpret_cast<char*>(&h), &buf, 1);
  for (uint8_t i = 0; i < h.size; i++) {
    buf[i] = waitForByte(theClient.bleuart);
    DBG2(dumpHex(buf[i], "r:"));
  }
  switch (h.type) {
    case comm::types::SYNC:
      comm::recv::sync();
      break;
    case comm::types::SETLED:
      comm::recv::set_led(buf[0]);
      break;
    case comm::types::SETRED:
      comm::recv::set_red(buf[0]);
      break;
    case comm::types::SETBLUE:
      comm::recv::set_blue(buf[0]);
      break;
    default:
      // TODO: ERROR!
      break;
  }
}
void comm::recv::sync() {
  DBG2(Serial.println("Sync received"));
  comm::send::time(theClient.bleuart, millis());
}
void comm::recv::set_led(uint8_t brightness) {
  BoardIO::setLED(brightness);
}
void comm::recv::set_red(bool on) {
  BoardIO::setRed(on);
}
void comm::recv::set_blue(bool on) {
  BoardIO::setBlue(on);
}