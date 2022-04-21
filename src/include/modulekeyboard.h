#pragma once
#include "action.h"
#include "usbenums.h"
#include "enumtypes.h"
#include <cstdint>

typedef KeyboardMode (*KeystrokeHandler)(Keystroke ks,
                                         Modifiers m,
                                         bool pressed,
                                         uint32_t now);
typedef KeyboardMode (*Spinner)(KeyboardMode mode, uint32_t now);
KeyboardMode ModuleKeyboardHandler(KeystrokeHandler handler,
                                   Spinner spin = nullptr);
