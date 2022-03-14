#include "sysstuff.h"

#include "Fonts/FreeSans12pt7b.h"
#include "bitmaps/amy.h"
#include "bitmaps/batman.h"
#include "bitmaps/linux.h"
#include "bitmaps/mac.h"
#include "bitmaps/win.h"
#include "boardio.h"
#include "general.h"
#include "image.h"
#include "keymap.h"
#include "scanner.h"

constexpr uint8_t BACKLIGHT_PIN = 18;
constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RST = 21;

Adafruit_ST7789* ThreePieceBoard::tft = nullptr;
boolean ThreePieceBoard::backlightOn = false;
uint32_t ThreePieceBoard::lastShownLayerTime = 0;
uint32_t ThreePieceBoard::lastShownLayerVal = 0;
const image_descriptor* images[5] = {
  gfx_amy, gfx_batman, gfx_mac, gfx_win, gfx_linux};

const int layer_to_image[8] = {
  2, // "Base/Mac",
  3, // "Win"
  4, // "Linux",
  1, // "Fn",
  0, // "MacCaps",
  0, // "WinCaps",
  1, // "WinCtrl",
  0 // "LinuxCaps"};
};

void ThreePieceBoard::Backlight(bool turnOn) {
  if (backlightOn != turnOn) {
    digitalWrite(BACKLIGHT_PIN, turnOn ? HIGH : LOW);
    backlightOn = turnOn;
  }
}

void ThreePieceBoard::Configure() {
  tft = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
  pinMode(BACKLIGHT_PIN, OUTPUT);

  Backlight(true);
  tft->init(240, 320);
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same speed)
  tft->setSPISpeed(60000000);
  tft->setRotation(1);
  tft->fillScreen(ST77XX_BLACK);
  tft->setFont(&FreeSans12pt7b);
  drawImage(images[0], 0, 0, tft);
}

void ThreePieceBoard::Changed(uint32_t now) {
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

void ThreePieceBoard::Tick(uint32_t now) {
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}