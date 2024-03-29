#include "sysstuff.h"

#include "EEPROM.h"
#include <array>

#include "Calculator.h"
#include "boardio.h"
#include "display.h"
#include "editline.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "generalstate.h"
#include "image.h"
#include "keymap.h"
#include "menu.h"
#include "modulekeyboard.h"
#include "scanning.h"
#include "tetris.h"

constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;
constexpr uint8_t TFT_BL = 17;

static uint32_t lastShownLayerTime = 0;
static layer_num lastShownLayer = layer_num::Base;

const std::array<const image_descriptor*, 7> reaccs = {
  gfx_like, gfx_love, gfx_hug, gfx_haha, gfx_sad, gfx_mad, gfx_wow};

const enum_array<layer_num, const image_descriptor*> layer_to_image = {
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
  disp::Init(135, 240, 60, 1, TFT_CS, TFT_DC, TFT_RST, TFT_BL);
  disp::SetBacklight(true, millis());
  ShowImage(gfx_amy);
  edit::Initialize();
  calc::Initialize();
  tetris::Initialize();
}

void resetTheWorld();

/*
  if (Switch to normal)
    mode = BoardMode::Normal;
    resetTheWorld();
    tft->fillScreen(ST77XX_BLACK);
    ShowImage(tft, gfx_keyb);
*/

uint8_t lastSavedLayer = 0xFF;

void BoardIO::SaveLayer(uint32_t now) {
  if (now - lastShownLayerTime > 10000 && now - lastShownLayerTime < 10100) {
    uint8_t lyr = value_cast(getCurrentLayer());
    if (lyr >= 0 && lyr < value_cast(layer_num::ValidSaves) &&
        lyr != lastSavedLayer) {
      Dbg2 << "Saving layer to eeprom " << lyr << sfmt::endl;
      EEPROM.update(0, lyr);
      lastSavedLayer = lyr;
    }
  }
}

void BoardIO::Reset(GeneralState& curState) {
  uint8_t lyr = EEPROM.read(0);
  if (lyr > 0 && lyr < value_cast(layer_num::ValidSaves)) {
    Dbg << "Turning this layer on:" << lyr << sfmt::endl;
    curState.toggle_layer(enum_cast<layer_num>(lyr));
    lastSavedLayer = lyr;
  } else {
    Dbg << "Not setting this layer:" << lyr << sfmt::endl;
  }
}

void BoardIO::Changed(uint32_t now, GeneralState& state) {
  layer_num lyr = getCurrentLayer();
  if (lyr != lastShownLayer) {
    Dbg << "Layer Change:" << lyr << sfmt::endl;
    disp::SetBacklight(true, now);
    lastShownLayer = lyr;
    lastShownLayerTime = now;
    const image_descriptor* img = layer_to_image[lyr];
    if (img == nullptr) {
      img = reaccs[now % 7];
    }
    ShowImage(img);
  }
}

void BoardIO::Tick(uint32_t now) {
  disp::Tick(now);
  SaveLayer(now);
}

KeyboardMode BoardIO::Mode(uint32_t now, KeyboardMode mode) {
  // This should transition the board into whatever other mode you may
  // want to
  switch (mode) {
    case KeyboardMode::Menu:
      menu::SetupModeList(KeyboardMode::Calculator, KeyboardMode::Tetris);
      return ModuleKeyboardHandler(KeyboardMode::Menu, menu::Handler);
    case KeyboardMode::Calculator:
      ShowImage(gfx_calcpic);
      return ModuleKeyboardHandler(KeyboardMode::Calculator, calc::Handler);
      break;
    case KeyboardMode::Tetris:
      return ModuleKeyboardHandler(
        KeyboardMode::Tetris, tetris::Handler, tetris::Spin);
    default:
      break;
  }
  return KeyboardMode::Normal;
}

void BoardIO::ShowScanCode(uint16_t sc) {}

void BoardIO::ReturnFromMode() {
  ShowImage(gfx_keyb);
}