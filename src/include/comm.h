#pragma once

#include "sysstuff.h"

#include <array>

#include "boardio.h"

namespace comm {

constexpr uint8_t LEFT_SIDE = 0;
constexpr uint8_t RIGHT_SIDE = 1;
#if defined(LEFT)
constexpr uint8_t WHICH_SIDE = LEFT_SIDE;
#elif defined(RIGHT)
constexpr uint8_t WHICH_SIDE = RIGHT_SIDE;
#endif
namespace types {
#if defined(DEBUG) && DEBUG > 1
constexpr char* COMM_TYPE_NAME[] =
    { "Scan", "Battery", "Time", "Sync", "SetLed", "SetRed", "SetBlue", "ERROR!" };
#endif
constexpr uint8_t SCAN = 0;
constexpr uint8_t BATTERY = 1;
constexpr uint8_t TIME = 2;
constexpr uint8_t SYNC = 3;
constexpr uint8_t SETLED = 4;
constexpr uint8_t SETRED = 5;
constexpr uint8_t SETBLUE = 6;
constexpr uint8_t count = 7;
} // namespace types

constexpr std::array<uint8_t, types::count> sizes{
    MatrixBits::num_bytes, 1, sizeof(uint32_t), 0, 1, 1, 1};
struct header {
  uint8_t side : 1;
  uint8_t type : 3;
  uint8_t size : 4;
};

} // namespace comm

template <typename UART>
uint8_t getSide(UART& uart) {
#if defined(BTLE_HOST)
  return comm::LEFT_SIDE; // TODO: Fix this
#else
  return comm::WHICH_SIDE;
#endif
}

template <uint8_t VAL, typename T, typename UART>
void send_packet(UART& uart, const T& v) {
  comm::header h;
  char buffer[sizeof(h) + sizeof(T)];
  h.side = getSide(uart);
  h.type = VAL;
  h.size = comm::sizes[VAL];
  memcpy(&buffer[0], reinterpret_cast<char*>(&h), sizeof(h));
  memcpy(&buffer[sizeof(h)], reinterpret_cast<const char*>(&v), sizeof(T));
#if defined(DEBUG) && DEBUG > 1
  for (int i = 0; i < sizeof(buffer); i++) {
    dumpHex((uint32_t)buffer[i], "S:");
  }
  Serial.println("---");
#endif
  uart.write(buffer, sizeof(buffer));
};

template <uint8_t VAL, typename UART>
void send_packet(UART& uart) {
  comm::header h;
  h.side = getSide(uart);
  h.type = VAL;
  h.size = comm::sizes[VAL];
  DBG2(dumpHex((uint8_t)(*(reinterpret_cast<char*>(&h))), "SB:"));
  uart.write(*reinterpret_cast<char*>(&h));
};

template <typename UART>
uint8_t waitForByte(UART& uart) {
  while (!uart.available()) {
    delayMicroseconds(5);
  }
  return uart.read();
}
