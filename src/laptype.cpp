#include "sysstuff.h"

#include "Fonts/FreeSans12pt7b.h"
#include "boardio.h"
#include "dbgcfg.h"
#include "general.h"
#include "globals.h"
#include "hardware.h"
#include "helpers.h"
#include "keymap.h"
#include "keystate.h"
#include "led_states.h"
#include "scanner.h"

GeneralState curState{};
MatrixBits prevBits{0};
Debouncer<MatrixBits> debouncer{};
#if defined(DISPLAY_ST7789)
const uint8_t BACKLIGHT_PIN = 17;
constexpr uint8_t TFT_CS = 8;
constexpr uint8_t TFT_DC = 15;
constexpr uint8_t TFT_RST = 6;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
#endif

MatrixBits key_scan(uint32_t now) {
  auto res = LaptypeBoard::Read();
  return debouncer.update(res, now);
}

// This is called when the LHS connects, disconnects, and when the system is
// initialized.  The idea is that it should just wipe everything clean.
void resetTheWorld() {
  curState.reset();
  memset(keyStates, null_scan_code, sizeof(keyStates));
}

uint32_t lastShownLayerTime = 0;
uint32_t lastShownLayerVal = ST77XX_BLACK;

void Backlight(bool on = true) {
  static bool backlightOn = false;
  if (backlightOn != on) {
    digitalWrite(BACKLIGHT_PIN, on ? HIGH : LOW);
    backlightOn = on;
  }
}

extern "C" void setup() {
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  LaptypeBoard::Configure();
  pinMode(BACKLIGHT_PIN, OUTPUT);
  delay(1);
  Backlight(true);
  tft.init(135, 240);
  // This is the fastest speed that worked
  // (72mhz also worked, but seemed to be the same speed)
  tft.setSPISpeed(60000000);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
  tft.setFont(&FreeSans12pt7b);
  resetTheWorld();
}

uint32_t last = 0;
extern "C" void loop() {
  uint32_t now = millis();
  // Get the before & after of each side into a 64 bit value
  MatrixBits before = prevBits;
  MatrixBits after = key_scan(now);
  MatrixBits delta = before.delta(after);
  bool keysChanged = delta.any();
  // Pseudo-code for what I'm looking to clean up:
  while (delta.any()) {
    bool pressed;
    scancode_t sc = getNextScanCode(delta, after, pressed);
    preprocessScanCode(sc, pressed, now);
  }
  if (keysChanged) {
    kb_reporter rpt;
    ProcessKeys(now, rpt);
    // Update the hardware previous state
    prevBits = after;
    DBG2(after.dumpHex("State: "));
    uint32_t col = getColorForCurrentLayer();
    if (col != lastShownLayerVal) {
      Backlight(true);
      tft.fillScreen(ST77XX_BLACK);
      lastShownLayerVal = col;
      lastShownLayerTime = now;
      int16_t x, y;
      uint16_t w, h;
      tft.setCursor(0, 0);
      const char* str = layer_names[curState.getLayer()];
      tft.getTextBounds(str, 0, 0, &x, &y, &w, &h);
      uint16_t xx = (tft.width() - w) / 2;
      uint16_t yy = (tft.height() + h) / 2;
      tft.setCursor(xx, yy);
      tft.fillRoundRect(xx + x - 10, yy + y - 10, w + 21, h + 21, 5, col);
      tft.fillRoundRect(xx + x - 3, yy + y - 3, w + 6, h + 6, 2, ST77XX_BLACK);
      tft.setTextColor(ST77XX_WHITE);
      tft.print(str);
      // tft.setCursor(10,120);
      // tft.printf("%d,%d,%d,%d, [%d,%d]", x, y, w, h, xx, yy);
    }
  }
  if (now - lastShownLayerTime > 10000) {
    Backlight(false);
  }
}
