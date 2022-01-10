#pragma once

#if defined(MOCKING)
# include "mock.h"
#else 
# if defined(ARDUINO_NRF52_ADAFRUIT)

#  if defined(BTLE_HOST)
#   include "Adafruit_TinyUSB.h"
#   include "Adafruit_NeoPixel.h"
#  endif

#  define ADAFRUIT
#  include <bluefruit.h>

#  undef min
#  undef max

# elif defined(TEENSY)
#  include "core_pins.h"
#  include "usb_keyboard.h"
#  include "usb_serial.h"
#  include <stddef.h>
# endif

# if defined(HAS_DISPLAY)
#  include <Adafruit_GFX.h>
#  include <Adafruit_SSD1306.h>
#  include <SPI.h>
#  include <Wire.h>
# endif

#endif