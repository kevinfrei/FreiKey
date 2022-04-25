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

struct BoardIO : public LaptypeMatrix {

  /*
    static Adafruit_ST7789* tft;
    static uint32_t lastShownLayerTime;
    static layer_num lastShownLayer;
  */

  static void Configure();
  static void Changed(uint32_t now, GeneralState& state);
  static void Tick(uint32_t now);
  static KeyboardMode Mode(uint32_t now, KeyboardMode mode);
  static void Reset(GeneralState&);
  static void ReturnFromMode();

  static void ShowScanCode(uint16_t sc);
  static void SaveLayer(uint32_t now);
};

using MatrixBits = LaptypeMatrix::bits;