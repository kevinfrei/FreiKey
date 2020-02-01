#pragma once

#if defined(MOCKING)
#include "mock.h"
#elif defined(ARDUINO_NRF52_ADAFRUIT)
#define ADAFRUIT
#include <bluefruit.h>

#include "Adafruit_NeoPixel.h"
#include "Adafruit_TinyUSB.h"

#undef min
#undef max
#elif defined(TEENSY)
#include "core_pins.h"
#include "usb_keyboard.h"
#include "usb_serial.h"
#include <stddef.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif