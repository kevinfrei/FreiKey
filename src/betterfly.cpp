#include "sysstuff.h"
#include "usb_keyboard.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "boardio.h"
#include "dbgcfg.h"
#include "globals.h"
#include "hardware.h"
#include "helpers.h"
#include "keymap.h"
#include "keystate.h"
#include "led_states.h"
#include "scanner.h"

constexpr BoardIO Betterfly = {{1, 0, 13, 2, 10, 11, 9, 20, 3, 14, 5, 4},
                               {23, 22, 21, 17, 16, 15}};
Adafruit_SSD1306 display(128, 32, &Wire, 12); // The reset switch on the OLED is pin 12
#if (SSD1306_LCDHEIGHT != 32)
#error "OLED height is wrong: ARGH!"
#endif

state::hw bfState;

// This is called when the LHS connects, disconnects, and when the system is
// initialized.  The idea is that it should just wipe everything clean.
void resetTheWorld() {
  layer_pos = 0;
  layer_stack[0] = 0;
  memset(&bfState, 0, sizeof(bfState));
  memset(keyStates, 0xff, sizeof(keyStates));
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

  // Pseudo-code for what I'm looking to clean up:
  for (BoardIO::bits delta = before.delta(after); delta.any();) {
    bool pressed;
    scancode_t sc = getNextScanCode(delta, after, pressed);
    action_t action = keymap[0][sc];
    action_t keyCode = getKeystroke(action);
    if (pressed) {
      DBG(dumpHex(keyCode, "Pressing  code  #"));
      Keyboard.press(keyCode);
    } else {
      DBG(dumpHex(keyCode, "Releasing code #"));
      Keyboard.release(keyCode);
    }
    // preprocessScanCode(sc, pressed, now);
  }
  // Update the hardware previous state
  bfState = down;

#if false
  if (keysChanged) {
    usb_report r = getUSBData(now);
#if defined(DEBUG) && DEBUG > 1
    Serial.print("mods=");
    Serial.print(r.mods, HEX);
    Serial.print(" repsize=");
    Serial.print(r.repsize);
    for (int i = 0; i < r.repsize; i++) {
      Serial.print(" ");
      Serial.print(r.report[i], HEX);
    }
    dumpHex(r.consumer, "Consumer:");
#endif

    // Handle the consumer stuff:
    if (r.consumer) {
      if (r.consumer > 0) {
        DBG2(dumpHex(r.consumer, "Consumer key press: "));
        // Keyboard.press(r.consumer);
      } else {
        DBG2(dumpHex(r.consumer, "Consumer key release: "));
        // Keyboard.release(-r.consumer);
      }
    }
    if (r.repsize) {
      // memcpy(keyboard_keys, r.report, sizeof(keyboard_keys));
      // keyboard_modifier_keys = r.mods;
      // usb_keyboard_send();
      DBG2(Serial.println("============================="));
      DBG2(down.dump());
    }
  }
#endif
}
