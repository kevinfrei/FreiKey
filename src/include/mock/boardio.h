#pragma once

#include "enumtypes.h"
#include "generalstate.h"
#include "keymatrix.h"
#include "keystate.h"
#include "mpu.h"

// clang-format off
using MockMatrix = KeyMatrix<MockMPU, 
  DIODE_DIR::ROW_TO_COL,
  // Cols, Rows
  12, 6,
  // Column Pins:
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
  // Row Pins:
  13, 14, 15, 16, 17, 18>;
// clang-format on

struct BoardIO : public MockMatrix {
  static void Configure();
  static void Reset(GeneralState&);
  static void Changed(uint32_t now, GeneralState&);
  static void Tick(uint32_t now);
  static KeyboardMode Mode(uint32_t now, KeyboardMode mode);
  static void ReturnFromMode();

  static void ShowScanCode(uint16_t sc);
};

constexpr uint8_t BAD_PIN = 0xFF;
constexpr uint8_t pinToCol[24] = {
  0xFF, 0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,
  11,   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

constexpr uint8_t pinToRow[24] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0,    1,    2,    3,    4,    5,    0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

using MatrixBits = MockMatrix::bits;
