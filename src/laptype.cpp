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

const enum_array<layer_num, const image_descriptor*, 8> layer_to_image = {
  {layer_num::MacBase, gfx_mac},
  {layer_num::WinBase, gfx_win},
  {layer_num::LinBase, gfx_linux},
  {layer_num::Func, gfx_amy},
  {layer_num::MacCap, gfx_batman},
  {layer_num::WinCap, gfx_batman},
  {layer_num::WinCtl, gfx_batman},
  {layer_num::LinCap, gfx_batman}};

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
  ShowImage(tft, gfx_amy);
}

void BoardIO::Changed(uint32_t now) {
  layer_num lyr = getCurrentLayer();
  if (lyr != lastShownLayer) {
    Backlight(true);
    tft->fillScreen(ST77XX_BLACK);
    lastShownLayer = lyr;
    lastShownLayerTime = now;
    ShowImage(tft, layer_to_image[lyr]);
  }
}

void BoardIO::Tick(uint32_t now) {
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}

void BoardIO::ShowScanCode(uint16_t sc) {}
