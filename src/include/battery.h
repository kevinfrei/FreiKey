#if !defined(BATTERY_H)
#define BATTERY_H

#include <cstdint>

uint8_t readBattery(uint32_t now, uint8_t prev);

#endif