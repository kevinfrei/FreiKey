#pragma once

#include "keymatrix.h"
#include "mpu.h"

// clang-format off

using LeftModuleMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  6, 6,
  // Column pins:
  15, 30, 27, A4, SCK, MOSI, // From 'outer' to 'inner'
  // Row pins:
  A1, A0, A2, 11, 7, 16>;

using RightModuleMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  6, 6,
  // Column pins:
  16, 27, 30, MOSI, SCK, A0, // from 'inner' to 'outer'
  // Row pins:
  A2, 15, A1, A5, A4, A3>;

// clang-format on

struct LeftModule: public LeftModuleMatrix {
  static void Configure();
  static void Changed(uint32_t now);
  static void Tick(uint32_t now);
};

struct RightModule: public RightModuleMatrix {
  static void Configure();
  static void Changed(uint32_t now);
  static void Tick(uint32_t now);
};
