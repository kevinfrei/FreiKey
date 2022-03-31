#pragma once

#include "core_pins.h"
#include "usb_keyboard.h"
#include "usb_serial.h"
#include <stddef.h>

#if defined(HAS_DISPLAY)
#include <Adafruit_GFX.h>
#if defined(DISPLAY_OLED)
#include <Adafruit_SSD1306.h>
#elif defined(DISPLAY_ST7789)
#include <Adafruit_ST7789.h>
#else
#error Unrecognized display
#endif
#define NEEDS_SPI
#endif

#if defined(NEEDS_SPI)
#include <SPI.h>
#include <Wire.h>
#endif

#if defined(NEEDS_SERIAL)
#include <HardwareSerial.h>
#endif

#define TEENSY 1
