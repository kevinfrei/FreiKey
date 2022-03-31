#include "sysstuff.h"

#include "Fonts/FreeSans12pt7b.h"
#include "bitmaps/amy.h"
#include "bitmaps/batman.h"
#include "bitmaps/linux.h"
#include "bitmaps/mac.h"
#include "bitmaps/win.h"
#include "boardio.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "generalstate.h"
#include "image.h"
#include "scanner.h"

constexpr uint8_t BACKLIGHT_PIN = 17;
constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;

Adafruit_ST7789* BoardIO::tft = nullptr;
boolean BoardIO::backlightOn = false;
uint32_t BoardIO::lastShownLayerTime = 0;
layer_num BoardIO::lastShownLayer = layer_num::Base;
const image_descriptor* images[5] = {
  gfx_amy, gfx_batman, gfx_mac, gfx_win, gfx_linux};

const enum_array<layer_num, uint8_t, 8> layer_to_image{
  {layer_num::Base, 2}, // "Base/Mac",
  {layer_num::WinBase, 3}, // "Win"
  {layer_num::LinBase, 4}, // "Linux",
  {layer_num::Func, 0}, // "Fn",
  {layer_num::MacCap, 1}, // "MacCaps",
  {layer_num::WinCap, 1}, // "WinCaps",
  {layer_num::WinCtl, 1}, // "WinCtrl",
  {layer_num::LinCap, 1} // "LinuxCaps"};
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

void BoardIO::Backlight(bool turnOn) {
  if (backlightOn != turnOn) {
    digitalWrite(BACKLIGHT_PIN, turnOn ? HIGH : LOW);
    backlightOn = turnOn;
  }
}

void BoardIO::Configure() {
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

void BoardIO::Changed(uint32_t now) {
  layer_num lyr = getCurrentLayer();
  if (lyr != lastShownLayer) {
    Backlight(true);
    tft->fillScreen(ST77XX_BLACK);
    lastShownLayer = lyr;
    lastShownLayerTime = now;
    uint8_t imageNum = layer_to_image[lyr];
    drawImage(images[imageNum],
              (tft->width() - images[imageNum]->width) / 2,
              (tft->height() - images[imageNum]->height) / 2,
              tft);
  }
}

void BoardIO::Tick(uint32_t now) {
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}

void BoardIO::ShowScanCode(uint16_t sc) {}
