#pragma once

#if defined(BETTERFLY)
#include "betterfly-keymap.h"
#elif defined(ARDUINO_NRF52_ADAFRUIT)
#include "freikeys-keymap.h"
#elif defined(MOCKING)
#include "mock-keymap.h"
#else
#error Please define a keymap header
#endif