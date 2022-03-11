#pragma once

#include "keymatrix.h"
#include "mpu.h"

// clang-format off

using LeftModuleMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  6, 6,
  // Column pins:
  // 52832 pins: 15, 30, 27, A4, SCK, MOSI, // From 'outer' to 'inner'
  // 52840 pins:
  12, 6, 5, A4, SCK, MOSI, // From 'outer' to 'inner'
  // Row pins:
  // 52832 pins: A1, A0, A2, 11, 7, 16>;
  // 52840 pins:
  A1, A0, A2, 10, 11, 13>;

using RightModuleMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  6, 6,
  // Column pins:
  // 52832 pins: 16, 27, 30, MOSI, SCK, A0, // from 'inner' to 'outer'
  // 52840 pins:
  13, 5, 6, MOSI, SCK, A0, // from 'inner' to 'outer'
  // Row pins:
  // 52832 pins: A2, 15, A1, A5, A4, A3>;
  // 52840 pins:
  A2, 12, A1, A5, A4, A3>;

// clang-format on

struct LeftModule: public LeftModuleMatrix {
  static void Configure();
};

struct RightModule: public RightModuleMatrix {
  static void Configure();
};
