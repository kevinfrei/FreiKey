#pragma once
#if !defined(_GUARD_SYSTEMSTATE_H)
#define _GUARD_SYSTEMSTATE_H

#include "enumtypes.h"
#include <array>
#include <stddef.h>

// TODO: Fix these, as they aren't correct
constexpr uint8_t num_switches = 76;
constexpr uint8_t max_layers = 16;

using LayerStates = std::array<layer_num, max_layers>;
using SwitchStates = std::array<uint32_t, num_switches>;

class SystemState {
  uint32_t curMillis; // Time, for lack of anything better I guess
  uint8_t capslock : 1; // LED's and what-not
  uint8_t numlock : 1;
  uint8_t scrollLock : 1;
  KeyboardMode mode; // Current 'mode'
  LayerStates layers;
  SwitchStates switches;

 public:
  static SystemState makeFreshState() {
    // TODO
    return SystemState{};
  }
  SystemState executeMode() const {
    // TODO
    return *this;
  }
  bool isNormalMode() const {
    return mode == KeyboardMode::Normal;
  }
};

#endif