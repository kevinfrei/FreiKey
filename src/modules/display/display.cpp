#include "sysstuff.h"

#include "Adafruit_ST7789.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "dbgcfg.h"
#include "display.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "keymap.h"

namespace disp {

Adafruit_ST7789* tft;
uint32_t backlightOnTime = 0;
uint32_t timeout = 10000;
uint8_t backlightPin = 0;

/*Adafruit_ST7789* */
void Init(uint16_t w,
          uint16_t h,
          int mhz,
          uint8_t rotation,
          uint8_t TFT_CS,
          uint8_t TFT_DC,
          uint8_t TFT_Reset,
          uint8_t TFT_Backlight,
          uint8_t SD_CS,
          uint8_t SPKR) {
  Dbg << "Initializing Display Module" << sfmt::endl;
  tft = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_Reset);
  backlightPin = TFT_Backlight;
  pinMode(TFT_Backlight, OUTPUT);
  tft->init(w, h);
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same observable speed)
  tft->setSPISpeed(mhz << 20);
  tft->setRotation(rotation);
  tft->fillScreen(ST77XX_BLACK);
  tft->setFont(&FreeSansBold12pt7b);

  if (SD_CS != 0) {
    // TODO: Configure the SD card here, probably?
  }
  if (SPKR != 0) {
    pinMode(SPKR, OUTPUT);
  }
  SetBacklight(true, millis());
}

void SetBacklight(bool turnOn, uint32_t now) {
  // Only write if we're changing the setting
  if (turnOn ? (backlightOnTime == 0) : (backlightOnTime != 0)) {
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

uint16_t getAlignedX(
  TextAlignment rel, uint16_t sz, int16_t st, uint8_t pad, uint16_t max) {
  switch (GetRelX(rel)) {
    case RelativeAlignment::Start:
      return (st > 0) ? (st + pad) : pad;
    case RelativeAlignment::Middle:
      return (max - (sz + st)) / 2;
    case RelativeAlignment::End:
      return max - (sz + st) - pad;
    default:
      return 0;
  }
}

uint16_t getAlignedY(
  TextAlignment rel, uint16_t sz, int16_t st, uint8_t pad, uint16_t max) {
  switch (GetRelY(rel)) {
    case RelativeAlignment::Start:
      return pad - st;
    case RelativeAlignment::Middle:
      return (max - st) / 2;
    case RelativeAlignment::End:
      return max - (sz + st) - pad;
    default:
      return 0;
  }
}

void DrawText(const char* loc,
              rect_t& prv,
              TextAlignment align,
              uint8_t padding,
              uint16_t color,
              uint16_t bgColor) {
  if (prv.w && prv.h) {
    tft->fillRect(prv.x, prv.y, prv.w, prv.h, bgColor);
  } else {
    tft->fillScreen(bgColor);
  }
  tft->getTextBounds(loc, 0, 0, &prv.x, &prv.y, &prv.w, &prv.h);
  uint16_t x = getAlignedX(align, prv.w, prv.x, padding, tft->width());
  uint16_t y = getAlignedY(align, prv.h, prv.y, padding, tft->height());
  tft->getTextBounds(loc, x, y, &prv.x, &prv.y, &prv.w, &prv.h);
  // Erase the old text
  tft->setTextColor(color);
  tft->setCursor(x, y);
  tft->print(loc);
#if defined(DEBUG) && DEBUG > 1
  tft->drawPixel(x, y, ST77XX_RED);
  tft->drawRect(prv.x, prv.y, prv.w, prv.h, ST77XX_CYAN);
#endif
}

void SetTimeout(uint16_t seconds) {
  timeout = seconds * 10000;
}

void Tick(uint32_t now) {
  if (backlightOnTime && backlightOnTime + timeout < now) {
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

void ClearScreen(uint16_t color) {
  tft->fillScreen(color);
}

void GetTextBounds(const char* str,
                   int16_t x,
                   int16_t y,
                   int16_t& xp,
                   int16_t& yp,
                   uint16_t& w,
                   uint16_t& h,
                   uint8_t fontSize) {
  tft->setTextSize(fontSize);
  tft->getTextBounds(str, x, y, &xp, &yp, &w, &h);
}

void DrawText(
  const char* str, uint8_t size, uint16_t color, int16_t x, int16_t y) {
  tft->setTextSize(size);
  tft->setTextColor(color);
  tft->setCursor(x, y);
  tft->print(str);
}

void FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  tft->fillRect(x, y, w, h, color);
}

void FillRoundRect(
  int16_t x, int16_t y, int16_t w, int16_t h, uint16_t r, uint16_t color) {
  tft->fillRoundRect(x, y, w, h, r, color);
}

void DrawLine(int16_t sx, int16_t sy, int16_t ex, int16_t ey, uint16_t color) {
  if (sx == ex) {
    tft->drawFastVLine(sx, sy, ey - sy, color);
  } else if (sy == ey) {
    tft->drawFastHLine(sx, sy, ex - ey, color);
  } else {
    tft->drawLine(sx, sy, ex, ey, color);
  }
}

void Draw16BitBitmap(
  uint16_t* buffer, int16_t x, int16_t y, uint16_t w, uint16_t h) {
  tft->drawRGBBitmap(x, y, buffer, w, h);
}

uint16_t GetWidth() {
  return tft->width();
}

uint16_t GetHeight() {
  return tft->height();
}

/*
Adafruit_SPITFT* raw() {
  return tft;
}
*/

} // namespace disp
