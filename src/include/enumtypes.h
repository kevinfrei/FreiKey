#pragma once
#include <stdint.h>

enum class layer_num : uint8_t {
  Base = 0,
  MacBase = 0,
  WinBase = 1,
  LinBase = 2,
  ValidSaves = 3,
  Func = 3,
  MacCap = 4,
  WinCap = 5,
  WinCtl = 6,
  LinCap = 7,
  Apple = 8,
  NumElems = 9
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
  Mode = 8, // "mode switch"
  Macro = 9,
  LayerRotate3 = 10,
  // LayerRotate4 (or more) requires 'moreData' in a single blob
  LayerRotate4 = 11,
  // Could make more LayerRotate actions
  // MaxActions = 15 << MUST FIT IN 4 BITS!
};

// Layer changing stuff
enum class layer_t : uint8_t {
  None = 0,
  Push = 1,
  Pop = 2,
  Toggle = 3,
  Switch = 4,
  Rotate3 = 5,
  Rotate4 = 6
};

enum class KeyboardMode : uint8_t {
  Normal = 0,
  Menu, // To pick from other modes :D
  Calculator, // Done
  Tetris, // This is close enough
  Snake, // Definitely going to code this at some point
  BubbleBreaker, // Maybe
  Bejeweled, // Maybe
  MediaBrowse, // Sure, why not?
  Apple2, // Eventually :)
  Diagnostics, // Maybe?
  NumElems
};

enum class ModuleId : uint8_t {
  // These are all the random modules that are available
  LineEditor,
  Display, // Maybe different displays?
  Calculator,
  Image,
  Menu,
  Snake,
  Tetris
};
