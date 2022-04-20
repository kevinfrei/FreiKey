#pragma once

#include "generalstate.h"
#include "keymatrix.h"
#include "keystate.h"
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

struct BoardIO : public MockMatrix {
  static uint32_t lastShownLayerTime;
  static uint32_t lastShownLayerVal;
  static void Configure();
  static bool Override(scancode_t sc, bool pressed, uint32_t now);
  static void Changed(uint32_t now, GeneralState &);
  static void Reset(GeneralState&);
  static uint16_t Mode(uint32_t now, uint16_t mode);
  static void Tick(uint32_t now);
};

constexpr uint8_t BAD_PIN = 0xFF;
constexpr uint8_t pinToCol[24] = {
  0xFF, 0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,
  11,   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

constexpr uint8_t pinToRow[24] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0,    1,    2,    3,    4,    5,    0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

using MatrixBits = MockMatrix::bits;
