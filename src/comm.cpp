#include "mybluefruit.h"

#include "comm.h"
#if defined(USB_MASTER)
#include "dongle.h"
#include "hardware.h"
#else
#include "boardio.h"
#include "kbclient.h"
#endif

template <uint8_t VAL, typename T, typename UART>
void send_packet(UART& uart, const T& v) {
  comm::header h;
  char buffer[sizeof(h) + sizeof(T)];
  h.side = comm::LEFT_SIDE; // TODO: Fix This
  h.type = VAL;
  h.size = comm::sizes[VAL];
  memcpy(&buffer[0], reinterpret_cast<char*>(&h), sizeof(h));
  memcpy(&buffer[sizeof(h)], reinterpret_cast<const char*>(&v), sizeof(T));
  for (int i = 0; i < sizeof(buffer); i++) {
    DBG3(dumpHex((uint32_t)buffer[i], "S:"));
  }
  uart.write(buffer, sizeof(buffer));
  DBG3(Serial.println("---"));
};

template <uint8_t VAL, typename UART>
void send_packet(UART& uart) {
  comm::header h;
  h.side = comm::LEFT_SIDE; // TODO: Fix This
  h.type = VAL;
  h.size = comm::sizes[VAL];
  DBG3(dumpHex((uint8_t)(*(reinterpret_cast<char*>(&h))), "SB:"));
  uart.write(*reinterpret_cast<char*>(&h));
};

template <typename UART>
uint8_t waitForByte(UART& uart) {
  while (!uart.available()) {
    delayMicroseconds(5);
  }
  return uart.read();
}

#if !defined(USB_MASTER)

void comm::send::scan(BLEUart& uart, const BoardIO::bits& b) {
  send_packet<comm::types::SCAN>(uart, b);
}

void comm::send::battery(BLEUart& uart, uint8_t pct) {
  send_packet<comm::types::BATTERY>(uart, pct);
}

void comm::send::time(BLEUart& uart, uint32_t time) {
  send_packet<comm::types::TIME>(uart, time);
}

#else
bool waiting;
uint32_t locTime;
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
#endif

#if defined(USB_MASTER)
uint8_t whichOne(BLEClientUart& uart) {
  return (&uart == &Dongle::leftUart) ? comm::LEFT_SIDE : comm::RIGHT_SIDE;
}

void comm::recv::data(BLEClientUart& uart) {
  comm::header h;
  uint8_t buf[15];
  buf[0] = waitForByte(uart);
  DBG3(dumpHex(buf[0], "R:"));
  memcpy(reinterpret_cast<char*>(&h), &buf, 1);
  for (uint8_t i = 0; i < h.size; i++) {
    buf[i] = waitForByte(uart);
    DBG3(dumpHex(buf[i], "RB:"));
  }
  switch (h.type) {
    case comm::types::SCAN: {
      BoardIO::bits b;
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

void comm::recv::scan(uint8_t which, const BoardIO::bits& b) {
  // Put the data in the queue
  state::hw* newData = new state::hw;
  DBG3(b.dumpHex((which == comm::LEFT_SIDE) ? "Left Scan " : "Right Scan "));
  newData->switches = b;
  newData->battery_level = 50;
  state::data_queue.push(
      {(which == comm::LEFT_SIDE) ? &Dongle::leftUart : &Dongle::rightUart,
       newData});
#if defined(LOTSA_BLINKING)
  if (which == comm::LEFT_SIDE) {
    Dongle::setRGB(0, 0, 250);
  } else {
    Dongle::setRGB(250, 0, 0);
  }
  if (b.any())
    digitalWrite(LED_RED, HIGH);
  else
    digitalWrite(LED_BLUE, HIGH);
  delay(5);
  Dongle::setRGB(0, 0, 0);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);
#endif
}
void comm::recv::battery(uint8_t which, uint8_t pct) {
  // TODO: Update the battery level
}
void comm::recv::time(uint8_t which, uint32_t time) {
  waiting = false;
  uint32_t locUpdate = millis();
  if (which == comm::LEFT_SIDE) {
    DBG2(dumpVal(time, "Left time "));
    digitalWrite(LED_BLUE, HIGH);
  } else {
    DBG2(dumpVal(time, "Right time "));
    digitalWrite(LED_RED, HIGH);
  }
  DBG2(dumpVal(locUpdate, "Local time "));
  DBG2(dumpVal(locUpdate - locTime, "Latency: "));
}
#else
void comm::recv::data(uint16_t handle) {
  comm::header h;
  uint8_t buf[15];
  buf[0] = waitForByte(theClient.bleuart);
  DBG3(dumpHex(buf[0], "r:"));
  memcpy(reinterpret_cast<char*>(&h), &buf, 1);
  for (uint8_t i = 0; i < h.size; i++) {
    buf[i] = waitForByte(theClient.bleuart);
    DBG3(dumpHex(buf[i], "r:"));
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
  DBG3(Serial.println("Sync received"));
  comm::send::time(theClient.bleuart, millis());
}
void comm::recv::set_led(uint8_t brightness) {
  theClient.theBoard.setLED(brightness);
}
void comm::recv::set_red(bool on) {
  theClient.theBoard.setRed(on);
}
void comm::recv::set_blue(bool on) {
  theClient.theBoard.setBlue(on);
}
#endif
