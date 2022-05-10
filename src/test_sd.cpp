#include "Adafruit_ST7789.h"
#include <algorithm>
#include <cmath>

#include "ardfs.h"

constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RESET = 21;
constexpr uint8_t SD_CS = 19;

typedef Adafruit_ST7789 display_t;

display_t display = display_t(TFT_CS, TFT_DC, TFT_RESET);

void configure() {
  display.setSPISpeed(60000000);
  display.setRotation(1);
  display.init(240, 320);
}

bool initSerial = false;

extern "C" void setup() {
  if (Serial) {
    Serial.begin(115200);
    initSerial = true;
  }
  configure();
}

extern "C" void loop() {
  if (Serial && !initSerial) {
    Serial.begin(115200);
    initSerial = true;
  }
  //
}
