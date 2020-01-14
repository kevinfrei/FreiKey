#pragma once

#include "sysstuff.h"

#include "boardio.h"
#include <array>

namespace comm {

constexpr uint8_t LEFT_SIDE = 0;
constexpr uint8_t RIGHT_SIDE = 1;

namespace types {
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
    BoardIO::byte_size, 1, sizeof(uint32_t), 0, 1, 1, 1};
struct header {
  uint8_t side : 1;
  uint8_t type : 3;
  uint8_t size : 4;
};

namespace send {
#if !defined(USB_MASTER)
void scan(BLEUart& uart, const BoardIO::bits&);
void battery(BLEUart& uart, uint8_t pct);
void time(BLEUart& uart, uint32_t time);
#else
void sync(BLEClientUart& uart);
void set_led(BLEClientUart& uart, uint8_t brightness);
void set_red(BLEClientUart& uart, bool on);
void set_blue(BLEClientUart& uart, bool on);
#endif
} // namespace send

namespace recv {

#if defined(USB_MASTER)
void data(BLEClientUart& uart);
void scan(uint8_t which, const BoardIO::bits&);
void battery(uint8_t which, uint8_t pct);
void time(uint8_t which, uint32_t time);
#else
void data(uint16_t handle); // BLEUart& uart);
void sync();
void set_led(uint8_t brightness);
void set_red(bool on);
void set_blue(bool on);
#endif

} // namespace recv

} // namespace comm
