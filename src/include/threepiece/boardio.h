#pragma once
#include "sysstuff.h"

#include "enumtypes.h"
#include "generalstate.h"
#include "keystate.h"

struct BoardIO {
  static const uint8_t matrix_size = 72;
  typedef uint8_t bits;
  static Adafruit_ST7789* tft;
  static bool backlightOn;
  static uint32_t lastShownLayerTime;
  static layer_num lastShownLayer;
  static void Configure();
  static void SaveLayer();
  static void Changed(uint32_t now, GeneralState&);
  static void Tick(uint32_t now);
  static void ShowScanCode(uint16_t sc);
  static KeyboardMode Mode(uint32_t now, KeyboardMode mode);
  static void Reset(GeneralState&);
};

using MatrixBits = BoardIO::bits;
