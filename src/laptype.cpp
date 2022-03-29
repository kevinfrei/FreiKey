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

constexpr uint8_t BACKLIGHT_PIN = 17;
constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;

Adafruit_ST7789* LaptypeBoard::tft = nullptr;
boolean LaptypeBoard::backlightOn = false;
uint32_t LaptypeBoard::lastShownLayerTime = 0;
uint32_t LaptypeBoard::lastShownLayerVal = 0;
const image_descriptor* images[5] = {
  gfx_amy, gfx_batman, gfx_mac, gfx_win, gfx_linux};

const int layer_to_image[8] = {
  2, // "Base/Mac",
  3, // "Win"
  4, // "Linux",
  0, // "Fn",
  1, // "MacCaps",
  1, // "WinCaps",
  1, // "WinCtrl",
  1 // "LinuxCaps"};
};

uint16_t prevWidth = 0;
uint16_t prevHeight = 0;
void ShowImage(Adafruit_ST7789* tft, uint8_t num) {
  uint16_t h = images[num]->height;
  uint16_t w = images[num]->width;
  uint16_t sw = tft->width();
  uint16_t sh = tft->height();
  if (h < prevHeight || w < prevWidth) {
    tft->fillRect((sw - prevWidth) / 2,
                  (sh - prevHeight) / 2,
                  prevWidth,
                  prevHeight,
                  ST77XX_BLACK);
  }
  drawImage(images[num], (sw - w) / 2, (sh - h) / 2, tft);
  prevHeight = h;
  prevWidth = w;
}

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
  ShowImage(tft, 0);
}

void LaptypeBoard::Changed(uint32_t now) {
  layer_num lyr = getCurrentLayer();
  if (static_cast<uint8_t>(lyr) != lastShownLayerVal) {
    Backlight(true);
    tft->fillScreen(ST77XX_BLACK);
    lastShownLayerVal = static_cast<uint8_t>(lyr);
    lastShownLayerTime = now;
    uint8_t imageNum = layer_to_image[static_cast<uint8_t>(lyr)];
    drawImage(images[imageNum],
              (tft->width() - images[imageNum]->width) / 2,
              (tft->height() - images[imageNum]->height) / 2,
              tft);
  }
}

void LaptypeBoard::Tick(uint32_t now) {
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}

void LaptypeBoard::ShowScanCode(uint16_t sc) {}