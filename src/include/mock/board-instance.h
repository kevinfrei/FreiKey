#pragma once

#include "keymatrix.h"
#include "mpu.h"

// clang-format off
using MockMatrix = KeyMatrix<MockMPU, 
  // Cols, Rows
  12, 6,
  // Column Pins:
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
  // Row Pins:
  13, 14, 15, 16, 17, 18>;
// clang-format on

struct MockBoard : public MockMatrix {
  static uint32_t lastShownLayerTime;
  static uint32_t lastShownLayerVal;
  static void Configure();
  static void Changed(uint32_t now);
  static void Tick(uint32_t now);
};
