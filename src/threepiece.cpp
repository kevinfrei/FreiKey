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

// Display stuff
constexpr uint8_t BACKLIGHT_PIN = 18;
constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RST = 21;

// And, I now have a speaker :D
constexpr uint8_t SPKR_GND = 0;
constexpr uint8_t SPKR_SIGNAL = 4;

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
  DBG2(Serial.println("TFT init complete"));
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same speed)
  tft->setSPISpeed(60000000);
  tft->setRotation(1);
  tft->setFont(&FreeSans12pt7b);
  DBG2(Serial.println("Attempting first image render"));
  tft->fillScreen(ST77XX_BLACK);
  drawImage(images[0],
            (320 - images[0]->width) / 2,
            (240 - images[0]->height) / 2,
            tft);
  DBG2(Serial.println("Screen Initialized"));
  //      Backlight(false);
  pinMode(SPKR_GND, OUTPUT);
  pinMode(SPKR_SIGNAL, OUTPUT);
  digitalWrite(SPKR_GND, LOW);
  digitalWrite(SPKR_SIGNAL, LOW);
}

void ThreePieceBoard::Changed(uint32_t now) {
  uint8_t lyr = getCurrentLayer();
  if (lyr != lastShownLayerVal && false) {
    Backlight(true);
    tft->fillScreen(ST77XX_BLACK);
    lastShownLayerVal = lyr;
    lastShownLayerTime = now;
    uint8_t imageNum = layer_to_image[lyr];
    drawImage(images[imageNum],
              (320 - images[imageNum]->width) / 2,
              (240 - images[imageNum]->height) / 2,
              tft);
  }
}

void ThreePieceBoard::Tick(uint32_t now) {
  if (now & 0x10) {
    // digitalWrite(SPKR_SIGNAL, (now & 0x20) ? HIGH : LOW);
  }
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}

int8_t yoffs[12] = {3, 2, 1, 0, 2, 3, 3, 2, 0, 1, 2, 3};
int8_t yloffs[12] = {3, 3, 2, 4, 3, 3, 3, 3, 4, 2, 3, 3};
int8_t xoffs[12] = {-4, -4, -4, -3, 0, 1, -2, -1, 2, 3, 3, 3};
int8_t xloffs[12] = {0, 0, -3, -3, -3, 3, -5, 2, 2, 2, 0, 0};
void ThreePieceBoard::ShowScanCode(uint16_t scancode) {
  Backlight(true);
  lastShownLayerTime = millis();
  uint16_t x = (scancode & 0xFF) % 12;
  uint16_t y = (scancode & 0xFF) / 12;
  uint16_t w = 7;
  int8_t yo = 0;
  int8_t xo = 0;
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
  tft->fillRect(112 + xo + x * 8 + (left ? -8 : 8), y * 7 + yo + 2, w, 6, c);
#if defined(DISPLAY_CODE)
  tft->fillRect(0, 0, 50, 25, ST77XX_BLACK);
  tft->setCursor(0, 25);
  tft->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft->print(scancode & 0xFF, HEX);
  tft->fillRect(5, 26, 5, 5, (scancode > 0xFF) ? ST77XX_RED : ST77XX_GREEN);
#endif
}