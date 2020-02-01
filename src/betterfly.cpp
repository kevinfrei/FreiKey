#include "sysstuff.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "globals.h"
#include "hardware.h"
#include "helpers.h"
#include "keymap.h"
#include "keystate.h"
#include "led_states.h"
#include "scanner.h"

#if !defined(MOCKING)
constexpr BoardIO Betterfly = {{1, 0, 13, 2, 10, 11, 9, 20, 3, 14, 5, 4},
                               {23, 22, 21, 17, 16, 15}};
#else
constexpr BoardIO Betterfly = {{0}, {1, 2, 3, 4, 5, 6}};
#endif
Adafruit_SSD1306 display(128, 32, &Wire, 12); // The reset switch on the OLED is
                                              // pin 12
#if (SSD1306_LCDHEIGHT != 32)
#error "OLED height is wrong: ARGH!"
#endif

state::hw bfState;

// This is called when the LHS connects, disconnects, and when the system is
// initialized.  The idea is that it should just wipe everything clean.
void resetTheWorld() {
  layer_pos = 0;
  layer_stack[0] = 0;
  bfState = state::hw{};
  memset(keyStates, null_scan_code, sizeof(keyStates));
}

extern "C" void setup() {
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  // Blink a bit, just for funsies...
  pinMode(13, OUTPUT);
  for (int i = 0; i < 64; i++) {
    digitalWrite(13, ((i & 7) == 7) ? HIGH : LOW);
    delay(8);
  }
  Betterfly.Configure();
  resetTheWorld();
}

extern "C" void loop() {
  uint32_t now = millis();

  // Get the hardware state for the two sides...
  state::hw down{now, bfState, Betterfly};

  // Get the before & after of each side into a 64 bit value
  BoardIO::bits before = bfState.switches;
  BoardIO::bits after = down.switches;

  BoardIO::bits delta = before.delta(after);
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
    bfState = down;
    DBG2(Serial.println("State: "));
    DBG2(down.dump());
  }
}
