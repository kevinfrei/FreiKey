#include "EEPROM.h"
#include "sysstuff.h"
#include <HardwareSerial.h>
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
  right.begin(1 << 20);
  left.begin(1 << 20);
  tft = disp::Init(240,
                   320,
                   60,
                   1,
                   TFT_CS,
                   TFT_DC,
                   TFT_RST,
                   BACKLIGHT_PIN,
                   SD_CS,
                   SPKR_SIGNAL);
  disp::SetBacklight(true, millis());
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same speed)
  DBG2(Serial.println("Attempting first image render"));
  ShowImage(tft, gfx_amy);
  DBG2(Serial.println("Screen Initialized"));
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


void BoardIO::Changed(uint32_t now, GeneralState&) {
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
      return ModuleKeyboardHandler(calc::Handler);
      break;
    case KeyboardMode::Menu:
      // return menu::Select(KeyboardMode::Calculator, KeybaordMode::Tetris);
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
