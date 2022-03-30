#pragma once

#include "enumtypes.h"
#include "keymatrix.h"
#include "mpu.h"

// clang-format off
using LaptypeMatrix = KeyMatrix<Teensy, 
  // Cols, Rows
  12, 6,
  // Column Pins:
  19, 21, 23, 14, 22, 20, 9, 10, 3, 2, 7, 4,
  // Row Pins:
  16, 12, 18, 5, 1, 0>;
// clang-format on

struct LaptypeBoard : public LaptypeMatrix {
  static Adafruit_ST7789* tft;
  static bool backlightOn;
  static uint32_t lastShownLayerTime;
  static layer_num lastShownLayer;
  static void Backlight(bool on = true);
  static void Configure();
  static void Changed(uint32_t now);
  static void Tick(uint32_t now);
  static void ShowScanCode(uint16_t now);
};
