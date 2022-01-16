#include "sysstuff.h"

#include "Fonts/FreeSans12pt7b.h"
#include "boardio.h"
#include "general.h"
#include "keymap.h"
#include "scanner.h"

constexpr uint8_t BACKLIGHT_PIN = 17;
constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;

Adafruit_ST7789* LaptypeBoard::tft = nullptr;
boolean LaptypeBoard::backlightOn = false;
uint32_t LaptypeBoard::lastShownLayerTime = 0;
uint32_t LaptypeBoard::lastShownLayerVal = 0;

void LaptypeBoard::Backlight(bool turnOn) {
  if (backlightOn != turnOn) {
    digitalWrite(BACKLIGHT_PIN, turnOn ? HIGH : LOW);
    backlightOn = turnOn;
  }
}

void LaptypeBoard::Configure() {
  ConfigMatrix();
  tft = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
  pinMode(BACKLIGHT_PIN, OUTPUT);

  Backlight(true);
  tft->init(135, 240);
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same speed)
  tft->setSPISpeed(60000000);
  tft->setRotation(1);
  tft->fillScreen(ST77XX_BLACK);
  tft->setFont(&FreeSans12pt7b);
}

void LaptypeBoard::Changed(uint32_t now) {
  uint32_t col = getColorForCurrentLayer();
  if (col != lastShownLayerVal) {
    Backlight(true);
    tft->fillScreen(ST77XX_BLACK);
    lastShownLayerVal = col;
    lastShownLayerTime = now;
    int16_t x, y;
    uint16_t w, h;
    tft->setCursor(0, 0);
    const char* str = layer_names[curState.getLayer()];
    tft->getTextBounds(str, 0, 0, &x, &y, &w, &h);
    uint16_t xx = (tft->width() - w) / 2;
    uint16_t yy = (tft->height() + h) / 2;
    tft->setCursor(xx, yy);
    tft->fillRoundRect(xx + x - 10, yy + y - 10, w + 21, h + 21, 5, col);
    tft->fillRoundRect(xx + x - 3, yy + y - 3, w + 6, h + 6, 2, ST77XX_BLACK);
    tft->setTextColor(ST77XX_WHITE);
    tft->print(str);
    // tft->setCursor(10,120);
    // tft->printf("%d,%d,%d,%d, [%d,%d]", x, y, w, h, xx, yy);
  }
}

void LaptypeBoard::Tick(uint32_t now) {
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}
