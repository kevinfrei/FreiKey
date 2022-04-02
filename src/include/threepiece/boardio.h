#pragma once
#include "sysstuff.h"

#include "enumtypes.h"
#include "keystate.h"

struct BoardIO {
  static const uint8_t matrix_size = 72;
  typedef uint8_t bits;
  static Adafruit_ST7789* tft;
  static bool backlightOn;
  static uint32_t lastShownLayerTime;
  static layer_num lastShownLayer;
  static void Backlight(bool on = true);
  static void Configure();
  static bool Override(scancode_t sc, bool pressed, uint32_t now);
  static void Changed(uint32_t now, uint16_t menuInfo);
  static void Tick(uint32_t now);
  static void ShowScanCode(uint16_t sc);
};

using MatrixBits = BoardIO::bits;
