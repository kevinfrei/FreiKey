#pragma once

#include "comm.h"

namespace comm {
namespace send {
void scan(BLEUart& uart, const MatrixBits&);
void battery(BLEUart& uart, uint8_t pct);
void time(BLEUart& uart, uint32_t time);
} // namespace send

namespace recv {
void data(uint16_t handle); // BLEUart& uart);
void sync();
void set_led(uint8_t brightness);
void set_red(bool on);
void set_blue(bool on);

} // namespace recv

} // namespace comm
