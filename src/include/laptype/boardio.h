#pragma once

#include "editline.h"
#include "enumtypes.h"
#include "generalstate.h"
#include "keymatrix.h"
#include "keystate.h"
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

enum class BoardMode { Normal, Waiting, Calculator };

struct BoardIO : public LaptypeMatrix {
  static Adafruit_ST7789* tft;
  static bool backlightOn;
  static uint32_t lastShownLayerTime;
  static layer_num lastShownLayer;
  static BoardMode mode;
  static void Backlight(bool on = true);
  static void Configure();
  // static bool Override(scancode_t sc, bool pressed, uint32_t now);
  static void Changed(uint32_t now, GeneralState &state);
  static void Tick(uint32_t now);
  static void ShowScanCode(uint16_t now);
  static void DrawText(const edit::editline& ln);
  static void SaveLayer();
  static uint16_t Mode(uint32_t now, uint16_t mode);
  static void Reset(GeneralState&);
};

using MatrixBits = LaptypeMatrix::bits;