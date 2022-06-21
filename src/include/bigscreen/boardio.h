#pragma once
#include "sysstuff.h"

#include "enumtypes.h"
#include "generalstate.h"
#include "keystate.h"

struct BoardIO {
  // These two are necessary for 3piece because it doesn't
  // inhereit from a Matrix
  static constexpr uint8_t matrix_size = 72;
  typedef uint8_t bits;

  static void Configure();
  static void Changed(uint32_t now, GeneralState&);
  static void Tick(uint32_t now);
  static KeyboardMode Mode(uint32_t now, KeyboardMode mode);
  static void ReturnFromMode();
  static void Reset(GeneralState&);

  static void ShowScanCode(uint16_t sc);
  static void SaveLayer();
};

using MatrixBits = BoardIO::bits;
