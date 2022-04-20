#include "EEPROM.h"
#include "sysstuff.h"
#include <array>

#include "Calculator.h"
#include "Fonts/FreeSans12pt7b.h"
#include "boardio.h"
#include "editline.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "generalstate.h"
#include "image.h"
#include "keymap.h"
#include "scanning.h"


Adafruit_ST7789 *tft;
uint32_t backlightOnTime = 0;

void InitDisplay(uint16_t w, uint16_t h, uint8_t mhz, uint8_t rotation, uint8_t TFT_CS, uint8_t TFT_DC, uint8_t TFT_Reset, uint8_t TFT_Backlight, uint8_t SD_CS = 0, uint8_t SPKR = 0){
  tft = new Adafruit_ST7787(TFT_CS, TFT_DC, TFT_Reset);
  pinMode(TFT_Backlight, OUTPUT);
    tft->init(w, h);
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same observable speed)
  tft->setSPISpeed(mhz * 1000000);
  tft->setRotation(rotation));
  tft->fillScreen(ST77XX_BLACK);
  tft->setFont(&FreeSans12pt7b);

  if (SD_CS != 0){
    // TODO: Configure the SD card here
  }
  if (SPKR != 0) {
    pinMode(SPKR, OUTPUT);
  }
  SetBacklight(true, millis());
}

void SetBacklight(bool turnOn, uint32_t now) {
  if (backlightOn == 0) {
    digitalWrite(BACKLIGHT_PIN, turnOn ? HIGH : LOW);
  }
  backlightOnTime = now;
}

int16_t px = 0, py = 0;
uint16_t pw = 240, ph = 135;

void BoardIO::DrawText(const edit::editline& ln) {
  // Add the 'cursor'
  char loc[129];
  int after = 0;
  size_t s;
  DBG(Serial.println("Buffer:"));
  DBG(Serial.println(ln.buf));
  for (s = 0; ln.buf[s]; s++) {
    if (after == 0 && ln.pos == s) {
      loc[s] = '|';
      after = 1;
    }
    loc[s + after] = ln.buf[s];
  }
  if (!after) {
    loc[s] = '|';
    after++;
  }
  loc[s + after] = 0;
  // Now let's erase & redraw the text:
  tft->fillScreen(ST77XX_BLACK);
  tft->getTextBounds(&loc[0], 10, 10, &px, &py, &pw, &ph);
  uint16_t x = (tft->width() - pw) / 2 - 10 + px;
  uint16_t y = (tft->height() - ph) / 2 - 10 + py;
  tft->setTextColor(ST77XX_GREEN);
  tft->setCursor(x, y);
  tft->print(&loc[0]);
}

Modifiers menuMods = Modifiers ::None;
void MenuModeKeyHandler(bool pressed, action_t a) {
  if (a.getAction() == KeyAction::Modifier) {
    if (pressed) {
      menuMods |= a.getModifiers();
    } else {
      // This should turn them off, right?
      menuMods &= ~a.getModifiers();
    }
  } else if (a.getAction() == KeyAction::KeyPress) {
    // Send the keystroke to the Edit Line module
    // Then print the results of the Edit Line modules on the screen

    // If the user hits "enter" trigger the calculator
    auto ln = edit::readline(a.getKeystroke(), menuMods, pressed, millis());
    if (a.getKeystroke() == Keystroke::Enter && pressed) {
      const char* val = calc::Parse(ln.buf);
      if (val) {
        edit::setline(val);
        ln = edit::readline(a.getKeystroke(), menuMods, pressed, millis());
      }
    }
    BoardIO::DrawText(ln);
    if (a.getKeystroke() == Keystroke::Tab && pressed) {
      Keyboard.print(ln.buf);
    }
    // And if they hit whatever "paste" should be, type the calculator value
  }
}

/*
bool BoardIO::Override(scancode_t sc, bool pressed, uint32_t now) {
  if (mode == BoardMode::Normal) {
    return false;
  }
  Backlight(true);
  lastShownLayerTime = now;
  action_t a = moduleKeyMap[sc];
  if (mode == BoardMode::Waiting) {
    if (a.getAction() == KeyAction::Modifier &&
        a.getModifiers() == Modifiers::ROpt && !pressed) {
      mode = BoardMode::Normal;
      resetTheWorld();
    }
  } else {
    // If we pres right-option, that gets us back to normal mode
    if (pressed && a.getAction() == KeyAction::Modifier &&
        a.getModifiers() == Modifiers::ROpt) {
      mode = BoardMode::Waiting;
      tft->fillScreen(ST77XX_BLACK);
      ShowImage(tft, gfx_keyb);
    } else if (a.getAction() == KeyAction::KeyPress ||
               a.getAction() == KeyAction::Modifier) {
      MenuModeKeyHandler(pressed, a);
    }
  }
  return true;
}
*/

/*
void BoardIO::Changed(uint32_t now, uint16_t menuInfo) {
  if (menuInfo) {
    mode = BoardMode::Calculator;
    menuMods = Modifiers::None;
    Backlight(true);
    lastShownLayerTime = now;
    tft->fillScreen(ST77XX_BLACK);
    ShowImage(tft, gfx_calcpic);
    // Save the layer, so that it can get updated when we come back out
    SaveLayer();
  } else {
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
}
*/

void BoardIO::Changed(uint32_t now, GeneralState& state) {
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
    // This is a *really* slow debounce of layer switches :D
    // Only save a layer if we've had it set > 10 seconds
    SaveLayer();
  }
}

void BoardIO::ShowScanCode(uint16_t sc) {}



#include "EEPROM.h"
#include "sysstuff.h"
#include <HardwareSerial.h>

#include "Fonts/FreeSans12pt7b.h"
#include "boardio.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "image.h"
#include "scanning.h"

#define right Serial2
#define left Serial4

// Display stuff
constexpr uint8_t BACKLIGHT_PIN = 18;
constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RST = 21;

// And, I now have a speaker :D
constexpr uint8_t SPKR_GND = 0;
constexpr uint8_t SPKR_SIGNAL = 4;

// Finally, the data for the SD card on the back of the Adafruit display
constexpr uint8_t SD_CS = 19;

Adafruit_ST7789* BoardIO::tft = nullptr;
boolean BoardIO::backlightOn = false;
uint32_t BoardIO::lastShownLayerTime = 0;
layer_num BoardIO::lastShownLayer = layer_num::Base;

void MenuTrigger(uint16_t);

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
  right.begin(1 << 20);
  left.begin(1 << 20);
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
  ShowImage(tft, gfx_amy);
  DBG2(Serial.println("Screen Initialized"));
  //      Backlight(false);
  pinMode(SPKR_GND, OUTPUT);
  pinMode(SPKR_SIGNAL, OUTPUT);
  digitalWrite(SPKR_GND, LOW);
  digitalWrite(SPKR_SIGNAL, LOW);
}

KeyboardMode BoardIO::Mode(uint32_t now, KeyboardMode mode) {
  return KeyboardMode::Normal;
}

void BoardIO::SaveLayer() {
  uint8_t lyr = value_cast(getCurrentLayer());
  if (lyr >= 0 && lyr < value_cast(layer_num::ValidSaves)) {
    DBG(dumpVal(lyr, "Saving layer to eeprom "));
    EEPROM.update(0, lyr);
  } else {
    DBG(dumpVal(lyr, "Not saving this to eeprom "));
  }
}

void BoardIO::Reset(GeneralState& curState) {
  uint8_t lyr = EEPROM.read(0);
  if (lyr > 0 && lyr < value_cast(layer_num::ValidSaves)) {
    DBG(dumpVal(lyr, "Turning this layer on:"));
    curState.toggle_layer(enum_cast<layer_num>(lyr));
  } else {
    DBG(dumpVal(lyr, "Not setting this layer:"));
  }
}

void BoardIO::Changed(uint32_t now, GeneralState &) {
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
  /*
  if (menuInfo != 0) {
    MenuTrigger(menuInfo);
  }
  */
}

void BoardIO::Tick(uint32_t now) {
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

void DrawKeyboard(uint16_t scancode,
                  uint16_t l,
                  uint16_t t,
                  Adafruit_ST7789* tft) {
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
  tft->fillRect(l + xo + x * 8 + (left ? -8 : 8), t + y * 7 + yo, w, 6, c);
#if defined(DISPLAY_CODE)
  tft->fillRect(0, 0, 50, 25, ST77XX_BLACK);
  tft->setCursor(0, 25);
  tft->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft->print(scancode & 0xFF, HEX);
  tft->fillRect(5, 26, 5, 5, (scancode > 0xFF) ? ST77XX_RED : ST77XX_GREEN);
#endif
}

void BoardIO::ShowScanCode(uint16_t scancode) {
  if (false) {
    Backlight(true);
    lastShownLayerTime = millis();
    // This is good stuff for debugging:
    DrawKeyboard(scancode, 112, 2, tft);
  }
}

void MenuTrigger(uint16_t val) {
  // The menu was triggers (with value val, if we care)
  // Shift into calculator mode until we see the
}