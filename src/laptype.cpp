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
#include "modulekeyboard.h"
#include "scanning.h"

constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;
constexpr uint8_t BACKLIGHT_PIN = 17;

Adafruit_ST7789* BoardIO::tft = nullptr;
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

void BoardIO::Configure() {
  ConfigMatrix();
  tft = disp::Init(135, 240, 60, 1, TFT_CS, TFT_DC, TFT_RST, BACKLIGHT_PIN);
  disp::SetBacklight(true, millis());
  ShowImage(tft, gfx_amy);
  edit::Initialize();
  calc::Initialize();
}

void resetTheWorld();

/*
  if (Switch to normal)
    mode = BoardMode::Normal;
    resetTheWorld();
    tft->fillScreen(ST77XX_BLACK);
    ShowImage(tft, gfx_keyb);
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

void BoardIO::Changed(uint32_t now, GeneralState& state) {
  layer_num lyr = getCurrentLayer();
  if (lyr != lastShownLayer) {
    DBG(dumpVal(lyr, "Layer Change: "));
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
  disp::Tick(now);
  if (now - lastShownLayerTime > 10000 && now - lastShownLayerTime < 10100) {
    // This is a *really* slow debounce of layer switches :D
    // Only save a layer if we've had it set > 10 seconds
    SaveLayer();
  }
}

KeyboardMode BoardIO::Mode(uint32_t now, KeyboardMode mode) {
  // This should transition the board into whatever other mode you may
  // want to
  switch (mode) {
    case KeyboardMode::Menu:
    case KeyboardMode::Calculator:
      return ModuleKeyboardHandler(calc::Handler);
      break;
      // return menu::Select(KeyboardMode::Calculator, KeybaordMode::Tetris);
      // break;
    default:
      break;
  }
  return KeyboardMode::Normal;
}

void BoardIO::ShowScanCode(uint16_t sc) {}
