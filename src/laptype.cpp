#include "EEPROM.h"
#include "sysstuff.h"
#include <array>

#include "Adafruit_ST7789.h"
#include "Calculator.h"
#include "boardio.h"
#include "display.h"
#include "editline.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "generalstate.h"
#include "image.h"
#include "keymap.h"
#include "scanning.h"

constexpr uint8_t BACKLIGHT_PIN = 17;
constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;

Adafruit_ST7789* BoardIO::tft = nullptr;
uint32_t BoardIO::lastShownLayerTime = 0;
layer_num BoardIO::lastShownLayer = layer_num::Base;
BoardMode BoardIO::mode = BoardMode::Normal;

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

void BoardIO::Configure() {
  ConfigMatrix();
  tft = disp::Init(135, 240, 60, 1, TFT_CS, TFT_DC, TFT_RST, BACKLIGHT_PIN);
  disp::SetBacklight(true, millis());
  ShowImage(tft, gfx_amy);
  edit::Initialize();
  calc::Initialize();
}

void resetTheWorld();

disp::rect_t lastPos = {0, 0, 135, 240};

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
  disp::CenteredText(&loc[0], lastPos);
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

void BoardIO::SaveLayer() {
  uint8_t lyr = value_cast(getCurrentLayer());
  if (lyr >= 0 && lyr < value_cast(layer_num::ValidSaves)) {
    DBG2(dumpVal(lyr, "Saving layer to eeprom "));
    EEPROM.update(0, lyr);
  } else {
    DBG2(dumpVal(lyr, "Not saving this to eeprom "));
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
    disp::SetBacklight(true, now);
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
    disp::Tick(now);
    // This is a *really* slow debounce of layer switches :D
    // Only save a layer if we've had it set > 10 seconds
    SaveLayer();
  }
}

KeyboardMode BoardIO::Mode(uint32_t now, KeyboardMode mode) {
  // This should transition the board into whatever other mode you may
  // want to
  switch (mode) {
    case KeyboardMode::Calculator:
      // EnterCalculator();
      break;
    case KeyboardMode::Menu:
      // return menu::Select(KeyboardMode::Calculator, KeybaordMode::Tetris);
      break;
    default:
      break;
  }
  return KeyboardMode::Normal;
}

void BoardIO::ShowScanCode(uint16_t sc) {}
