#include "EEPROM.h"
#include "sysstuff.h"
#include <HardwareSerial.h>
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

#define right Serial2
#define left Serial4

// Display stuff
static constexpr uint8_t TFT_BL = 18;
static constexpr uint8_t TFT_CS = 10;
static constexpr uint8_t TFT_DC = 20;
static constexpr uint8_t TFT_RST = 21;

// And, I now have a speaker :D
static constexpr uint8_t SPKR_GND = 0;
static constexpr uint8_t SPKR_SIGNAL = 4;

// Finally, the data for the SD card on the back of the Adafruit display
static constexpr uint8_t SD_CS = 19;

static uint32_t lastShownLayerTime = 0;
static layer_num lastShownLayer = layer_num::Base;

static const std::array<const image_descriptor*, 7> reaccs = {
  gfx_like, gfx_love, gfx_hug, gfx_haha, gfx_sad, gfx_mad, gfx_wow};

static const enum_array<layer_num, const image_descriptor*> layer_to_image = {
  {layer_num::MacBase, gfx_mac},
  {layer_num::WinBase, gfx_win},
  {layer_num::LinBase, gfx_linux},
  {layer_num::Func, gfx_amy},
  {layer_num::MacCap, nullptr},
  {layer_num::WinCap, nullptr},
  {layer_num::WinCtl, gfx_batman},
  {layer_num::LinCap, nullptr},
  {layer_num::Apple, gfx_apple_ii}};

void BoardIO::Configure() {
  right.begin(1 << 20);
  left.begin(1 << 20);
  disp::Init(
    240, 320, 60, 1, TFT_CS, TFT_DC, TFT_RST, TFT_BL, SD_CS, SPKR_SIGNAL);
  disp::SetBacklight(true, millis());
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same speed)
  Dbg2 << "Attempting first image render" << sfmt::endl;
  ShowImage(gfx_amy);
  Dbg2 << "Screen Initialized" << sfmt::endl;
  // Backlight(false);
  pinMode(SPKR_GND, OUTPUT);
  digitalWrite(SPKR_GND, LOW);
  // pinMode(SPKR_SIGNAL, OUTPUT);
  // digitalWrite(SPKR_SIGNAL, LOW);
  edit::Initialize();
  calc::Initialize();
}

void BoardIO::SaveLayer() {
  uint8_t lyr = value_cast(getCurrentLayer());
  if (lyr >= 0 && lyr < value_cast(layer_num::ValidSaves)) {
    Dbg << "Saving layer to eeprom " << lyr << sfmt::endl;
    EEPROM.update(0, lyr);
  } else {
    Dbg << "Not saving this to eeprom " << lyr << sfmt::endl;
  }
}

void BoardIO::Reset(GeneralState& curState) {
  uint8_t lyr = EEPROM.read(0);
  if (lyr > 0 && lyr < value_cast(layer_num::ValidSaves)) {
    Dbg << "Turning this layer on:" << lyr << sfmt::endl;
    curState.toggle_layer(enum_cast<layer_num>(lyr));
  } else {
    Dbg << "Not setting this layer:" << lyr << sfmt::endl;
  }
}

void BoardIO::Changed(uint32_t now, GeneralState&) {
  layer_num lyr = getCurrentLayer();
  if (lyr != lastShownLayer) {
    disp::SetBacklight(true, now);
    lastShownLayer = lyr;
    lastShownLayerTime = now;
    const image_descriptor* img = layer_to_image[lyr];
    if (img == nullptr) {
      // Show a random image from the reaccs array
      img = reaccs[now % reaccs.size()];
    }
    Dbg << "Trying to show the image for layer " << lyr << sfmt::endl;
    ShowImage(img);
  }
}

void BoardIO::Tick(uint32_t now) {
  if (now & 0x10) {
    // digitalWrite(SPKR_SIGNAL, (now & 0x20) ? HIGH : LOW);
  }
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
    case KeyboardMode::Calculator:
      return ModuleKeyboardHandler(KeyboardMode::Calculator, calc::Handler);
      break;
    case KeyboardMode::Menu:
      menu::SetupModeList(KeyboardMode::Calculator, KeyboardMode::Tetris);
      return ModuleKeyboardHandler(KeyboardMode::Menu, menu::Handler);
      break;
    default:
      break;
  }
  return KeyboardMode::Normal;
}

void BoardIO::ShowScanCode(uint16_t scancode) {
  if (false) {
    disp::SetBacklight(true, millis());
    lastShownLayerTime = millis();
    // This is good stuff for debugging:
    disp::DrawKeyboard(scancode, 112, 2);
  }
}

void BoardIO::ReturnFromMode() {
  ShowImage(gfx_keyb);
}