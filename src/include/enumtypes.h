#pragma once
#include <stdint.h>

enum class layer_num : uint8_t {
  Base = 0,
  MacBase = 0,
  WinBase = 1,
  LinBase = 2,
  Func = 3,
  MacCap = 4,
  WinCap = 5,
  WinCtl = 6,
  LinCap = 7
};

// This needs to fit in 4 bits
enum class KeyAction : uint8_t {
  KeyPress = 0,
  Modifier = 1,
  TapHold = 2,
  Consumer = 3,
  KeyAndMods = 4,
  LayerShift = 5,
  LayerToggle = 6,
  LayerSwitch = 7,
  MaxActions = 15
};
