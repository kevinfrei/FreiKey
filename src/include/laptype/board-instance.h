#pragma once

#include "teensy/mpu.h"
#include "keymatrix.h"

// clang-format off

using LaptypeMatrix = KeyMatrix<Teensy, 
  // Cols, Rows
  12, 6,
  // Column Pins:
  19, 21, 23, 14, 22, 20, 9, 10, 3, 2, 7, 4,
  // Row Pins:
  16, 12, 18, 5, 1, 0>;

struct LaptypeBoard: public LaptypeMatrix {
  static void Configure() {
    ConfigMatrix();
  }
}