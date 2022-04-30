#pragma once

#include "usbenums.h"
#include "enumtypes.h"

namespace tetris {

void Initialize();
KeyboardMode Handler(Keystroke ks, Modifiers m, bool pressed, uint32_t now);
KeyboardMode Spin(KeyboardMode curMode, uint32_t now);

} // namespace tetris