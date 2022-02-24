#pragma once

#if defined(NEW_CONFIG)
#include "hwconfig.h"
#include "mpusys.h"
#else
#if defined(MOCK)
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

#include "mock.h"
#else
#if defined(ARDUINO_NRF52_ADAFRUIT)

#if defined(BTLE_HOST)
#include "Adafruit_NeoPixel.h"
#include "Adafruit_TinyUSB.h"
#endif

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

#if defined(HAS_DISPLAY)
#include <Adafruit_GFX.h>
#if defined(DISPLAY_OLED)
#include <Adafruit_SSD1306.h>
#elif defined(DISPLAY_ST7789)
#include <Adafruit_ST7789.h>
#else
#error Unrecognized display
#endif
#include <SPI.h>
#include <Wire.h>
#endif

#endif

#endif