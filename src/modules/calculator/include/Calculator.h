#pragma once

#include "enumtypes.h"
#include "usbenums.h"
#include <cstdint>

namespace calc {

void Initialize();

const char* Parse(const char*);

KeyboardMode Handler(Keystroke ks, Modifiers mods, bool pressed, uint32_t now);

} // namespace calc
