#include "sysstuff.h"

#include "Adafruit_ST7789.h"
#include "Fonts/FreeSans12pt7b.h"
#include "display.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "image.h"
#include "keymap.h"

namespace disp {

Adafruit_ST7789* tft;
uint32_t backlightOnTime = 0;
uint32_t timeout = 10000;
uint8_t backlightPin = 0;

Adafruit_ST7789* Init(uint16_t w,
                      uint16_t h,
                      uint8_t mhz,
                      uint8_t rotation,
                      uint8_t TFT_CS,
                      uint8_t TFT_DC,
                      uint8_t TFT_Reset,
                      uint8_t TFT_Backlight,
                      uint8_t SD_CS,
                      uint8_t SPKR) {
  tft = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_Reset);
  pinMode(TFT_Backlight, OUTPUT);
  tft->init(w, h);
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same observable speed)
  tft->setSPISpeed(mhz * 1000000);
  tft->setRotation(rotation);
  tft->fillScreen(ST77XX_BLACK);
  tft->setFont(&FreeSans12pt7b);

  if (SD_CS != 0) {
    // TODO: Configure the SD card here, probably?
  }
  if (SPKR != 0) {
    pinMode(SPKR, OUTPUT);
  }
  SetBacklight(true, millis());
  return tft;
}

void SetBacklight(bool turnOn, uint32_t now) {
  // Only write if we're changing the setting
  if (!!backlightOnTime != turnOn) {
    digitalWrite(backlightPin, turnOn ? HIGH : LOW);
  }
  backlightOnTime = turnOn ? now : 0;
}

rect_t CenteredText(const char* loc,
                    rect_t& prv,
                    uint16_t color = ST77XX_WHITE,
                    uint16_t bgColor = ST77XX_BLACK) {
  rect_t reg;
  tft->getTextBounds(loc, 0, 0, &reg.x, &reg.y, &reg.w, &reg.h);
  uint16_t x = (tft->width() - reg.w) / 2 + reg.x;
  uint16_t y = (tft->height() - reg.h) / 2 + reg.y;
  tft->getTextBounds(loc, x, y, &reg.x, &reg.y, &reg.w, &reg.h);
  if (prv.x < reg.x || prv.y < reg.y || prv.x + prv.w > reg.x + prv.w ||
      prv.y + prv.h > reg.y + reg.h) {
    tft->fillRect(prv.x, prv.y, prv.w, prv.h, bgColor);
  }
  tft->setTextColor(color);
  tft->setCursor(x, y);
  tft->print(loc);
  return reg;
}

void SetTimeout(uint16_t seconds) {
  timeout = seconds * 10000;
}

void Tick(uint32_t now) {
  if (backlightOnTime && backlightOnTime + timeout > now) {
    SetBacklight(false, now);
  }
}

int8_t yoffs[12] = {3, 2, 1, 0, 2, 3, 3, 2, 0, 1, 2, 3};
int8_t yloffs[12] = {3, 3, 2, 4, 3, 3, 3, 3, 4, 2, 3, 3};
int8_t xoffs[12] = {-4, -4, -4, -3, 0, 1, -2, -1, 2, 3, 3, 3};
int8_t xloffs[12] = {0, 0, -3, -3, -3, 3, -5, 2, 2, 2, 0, 0};

void DrawKeyboard(uint16_t scancode, uint16_t l, uint16_t t) {
  uint16_t x = (scancode & 0xFF) % 12;
  uint16_t y = (scancode & 0xFF) / 12;
  uint16_t w = 7;
  int8_t yo = 0, xo = 0;
  bool left = x < 6;
  if (y < 4) {
    // Rows 1 through 4
    yo = yoffs[x];
    if (x == 0 || x == 11) {
      w = 11;
      xo = x ? 0 : -4;
    }
  } else if (y == 4) {
    // Row 5
    yo = yloffs[x];
    xo = xoffs[x];
  } else {
    // Row 6
    yo = 4;
    xo = xloffs[x];
  }
  uint16_t c = (scancode > 0xFF) ? 0xC000 : 0x200;
  tft->fillRect(l + xo + x * 8 + (left ? -8 : 8), t + y * 7 + yo, w, 6, c);
}

} // namespace disp