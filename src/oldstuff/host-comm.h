#pragma once

#include "comm.h"

namespace comm {
namespace send {
void sync(BLEClientUart& uart);
void set_led(BLEClientUart& uart, uint8_t brightness);
void set_red(BLEClientUart& uart, bool on);
void set_blue(BLEClientUart& uart, bool on);
} // namespace send

namespace recv {
void data(BLEClientUart& uart);
void scan(uint8_t which, const MatrixBits&);
void battery(uint8_t which, uint8_t pct);
void time(uint8_t which, uint32_t time);
} // namespace recv

} // namespace comm
