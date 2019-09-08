#pragma once

#if defined(ARDUINO_NRF52_ADAFRUIT)
#define ADAFRUIT
#include <bluefruit.h>
#undef min
#undef max
#elif defined(TEENSY)
#include "core_pins.h"
#include "usb_keyboard.h"
#include "usb_serial.h"
#include <stddef.h>
#endif