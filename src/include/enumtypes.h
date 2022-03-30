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
  KeyPress,
  Modifier,
  TapHold,
  Consumer,
  KeyAndMods,
  LayerShift,
  LayerToggle,
  LayerSwitch,
  MaxActions = 15
};
