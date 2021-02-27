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

// Message types (only 3 bits, currently)
enum class types : uint8_t {
  SCAN = 0,
  BATTERY = 1,
  TIME = 2,
  SYNC = 3,
  SETLED = 4,
  SETRED = 5,
  SETBLUE = 6,
};

// Get the packet size of the different messages above
constexpr uint8_t types_size(types t) {
  switch (t) {
    case types::SCAN:
      return MatrixBits::num_bytes;
    case types::BATTERY:
    case types::SETLED:
    case types::SETRED:
    case types::SETBLUE:
      return 1;
    case types::TIME:
      return sizeof(uint32_t);
    case types::SYNC:
      return 0;
  };
}

#if defined(DEBUG) && DEBUG > 1
// String name for diagnostics...
constexpr char* get_type_name(types t) {
  switch (t) {
    case types::SCAN:
      return "Scan";
    case types::BATTERY:
      return "Battery";
    case types::SETLED:
      return "SetLED";
    case types::SETRED:
      return "SetRed";
    case types::SETBLUE:
      return "SetBlue";
    case types::TIME:
      return "Time";
    case types::SYNC:
      return "Sync";
  }
}
#endif

struct header {
  uint8_t side : 1;
  types type : 3;
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

template <comm::types VAL, typename T, typename UART>
void send_packet(UART& uart, const T& v) {
  comm::header h;
  char buffer[sizeof(h) + sizeof(T)];
  h.side = getSide(uart);
  h.type = VAL;
  h.size = comm::types_size(VAL);
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

template <comm::types VAL, typename UART>
void send_packet(UART& uart) {
  comm::header h;
  h.side = getSide(uart);
  h.type = VAL;
  static_assert(comm::types_size(VAL) == 0);
  h.size = 0;
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
