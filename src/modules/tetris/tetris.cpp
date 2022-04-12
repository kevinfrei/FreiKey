#include "tetris.h"
#include "Adafruit_ST7789.h"
#include "usbenums.h"


namespace tetris {
void Initialize() {
  // Don't think I need anything here...
}
Adafruit_ST7789 *dsp=nullptr;
void Begin(Adafruit_ST7789* tft) {
  dsp = tft;
}
void KeyDown(Keystroke k) {}
void Tick() {}
} // namespace tetris