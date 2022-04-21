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

RelativeAlignment GetRelX(TextAlignment a) {
  switch (a) {
    case TextAlignment::LeftTop:
    case TextAlignment::LeftMiddle:
    case TextAlignment::LeftBottom:
      return RelativeAlignment::Start;
    case TextAlignment::CenterTop:
    case TextAlignment::CenterMiddle:
    case TextAlignment::CenterBottom:
      return RelativeAlignment::Middle;
    case TextAlignment::RightTop:
    case TextAlignment::RightMiddle:
    case TextAlignment::RightBottom:
      return RelativeAlignment::End;
  }
  return RelativeAlignment::Middle;
}

RelativeAlignment GetRelY(TextAlignment a) {
  switch (a) {
    case TextAlignment::LeftTop:
    case TextAlignment::CenterTop:
    case TextAlignment::RightTop:
      return RelativeAlignment::Start;
    case TextAlignment::LeftMiddle:
    case TextAlignment::CenterMiddle:
    case TextAlignment::RightMiddle:
      return RelativeAlignment::Middle;
    case TextAlignment::LeftBottom:
    case TextAlignment::CenterBottom:
    case TextAlignment::RightBottom:
      return RelativeAlignment::End;
  }
  return RelativeAlignment::Middle;
}

uint16_t getAligned(
  RelativeAlignment rel, uint16_t sz, uint16_t st, uint8_t pad, uint16_t max) {
  return 0;
}

void DrawText(const char* loc,
              rect_t& prv,
              TextAlignment align,
              uint8_t padding,
              uint16_t color,
              uint16_t bgColor) {
  tft->fillRect(prv.x, prv.y, prv.w, prv.h, bgColor);
  tft->getTextBounds(loc, 0, 0, &prv.x, &prv.y, &prv.w, &prv.h);
  uint16_t x = getAligned(GetRelX(align), prv.w, prv.x, padding, tft->width());
  uint16_t y = getAligned(GetRelY(align), prv.h, prv.y, padding, tft->height());
  tft->getTextBounds(loc, x, y, &prv.x, &prv.y, &prv.w, &prv.h);
  // Erase the old text
  tft->setTextColor(color);
  tft->setCursor(x, y);
  tft->print(loc);
}

void SetTimeout(uint16_t seconds) {
  timeout = seconds * 10000;
}

void Tick(uint32_t now) {
  if (backlightOnTime && backlightOnTime + timeout > now) {
    SetBacklight(false, now);
  }
}

constexpr int8_t yoffs[12] = {3, 2, 1, 0, 2, 3, 3, 2, 0, 1, 2, 3};
constexpr int8_t yloffs[12] = {3, 3, 2, 4, 3, 3, 3, 3, 4, 2, 3, 3};
constexpr int8_t xoffs[12] = {-4, -4, -4, -3, 0, 1, -2, -1, 2, 3, 3, 3};
constexpr int8_t xloffs[12] = {0, 0, -3, -3, -3, 3, -5, 2, 2, 2, 0, 0};

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
