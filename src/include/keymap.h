#pragma once

#if defined(BETTERFLY)
#include "betterfly-keymap.h"
#elif defined(ADAFRUIT)
#include "freikeys-keymap.h"
#else
#error Please define a keymap header
#endif