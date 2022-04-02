#include "sysstuff.h"
#include <array>

#include "Fonts/FreeSans12pt7b.h"
#include "bitmaps/amy.h"
#include "bitmaps/batman.h"
#include "bitmaps/haha.h"
#include "bitmaps/hug.h"
#include "bitmaps/like.h"
#include "bitmaps/linux.h"
#include "bitmaps/love.h"
#include "bitmaps/mac.h"
#include "bitmaps/mad.h"
#include "bitmaps/sad.h"
#include "bitmaps/win.h"
#include "bitmaps/wow.h"
#include "boardio.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "generalstate.h"
#include "image.h"
#include "scanning.h"

constexpr uint8_t BACKLIGHT_PIN = 17;
constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;

Adafruit_ST7789* BoardIO::tft = nullptr;
boolean BoardIO::backlightOn = false;
uint32_t BoardIO::lastShownLayerTime = 0;
layer_num BoardIO::lastShownLayer = layer_num::Base;

const std::array<const image_descriptor*, 7> reaccs = {
  gfx_like, gfx_love, gfx_hug, gfx_haha, gfx_sad, gfx_mad, gfx_wow};

const enum_array<layer_num, const image_descriptor*, 8> layer_to_image = {
  {layer_num::MacBase, gfx_mac},
  {layer_num::WinBase, gfx_win},
  {layer_num::LinBase, gfx_linux},
  {layer_num::Func, gfx_amy},
  {layer_num::MacCap, nullptr},
  {layer_num::WinCap, nullptr},
  {layer_num::WinCtl, gfx_batman},
  {layer_num::LinCap, nullptr}};

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

bool BoardIO::Override(scancode_t sc, bool pressed, uint32_t now) {
  return false;
}

void BoardIO::Changed(uint32_t now, uint16_t menuInfo) {
  layer_num lyr = getCurrentLayer();
  if (lyr != lastShownLayer) {
    Backlight(true);
    lastShownLayer = lyr;
    lastShownLayerTime = now;
    const image_descriptor* img = layer_to_image[lyr];
    if (img == nullptr) {
      img = reaccs[now % 7];
    }
    ShowImage(tft, img);
  }
}

void BoardIO::Tick(uint32_t now) {
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}

void BoardIO::ShowScanCode(uint16_t sc) {}
