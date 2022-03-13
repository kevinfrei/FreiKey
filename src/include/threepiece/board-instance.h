#pragma once
#include "sysstuff.h"

struct ThreePieceBoard {
  static const uint8_t matrix_size = 72;
  typedef uint8_t bits;
  static Adafruit_ST7789* tft;
  static bool backlightOn;
  static uint32_t lastShownLayerTime;
  static uint32_t lastShownLayerVal;
  static void Backlight(bool on = true);
  static void Configure();
  static void Changed(uint32_t now);
  static void Tick(uint32_t now);
};
