#pragma once

#include "sysstuff.h"

// The keyboard can send three messages, each of which also includes a
// length of time (in seconds) to display the message
// Status:
//  Layer State, Left/Right battery values. Charging status
//  Slave state, bluetooth host name
// String: print something out (45 bytes max)
//  Primarily useful for debugging, right?
// Prefixed number: a string (41 bytes max), a format (hex, uns, signed)
//  and a 32 bit value

namespace drawing {
enum class Thing : uint8_t {
  Apple = 0,
  Windows = 1,
  Linux = 2,
  Func = 3,
  Bluetooth = 4,
  NoBlue = 5
};

uint8_t encodeBatteryValue(uint8_t chargeRemaining,
                           bool isCharging,
                           bool isPresent);
void drawBattery(uint8_t rate, uint8_t x, uint8_t y);
void drawThing(Thing lyr, uint8_t x, uint8_t y);

void updateState();
} // namespace drawing
