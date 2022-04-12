#pragma once

#include "usbenums.h"

class Adafruit_ST7789;

namespace tetris {
void Initialize();
void Begin(Adafruit_ST7789* tft);
void KeyDown(Keystroke k);
void Tick();
} // namespace tetris