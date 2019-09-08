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

keystate keyStates[6];
constexpr layer_t layer_max = 7;
layer_t layer_stack[layer_max + 1];
layer_t layer_pos = 0;

// Look for a slot that is either already in use for this scan code, or vacant.
// If we don't have a vacant slot, return the oldest, but still in use, slot,
// but only for key-up states, as we're probably through with them anyway.
struct keystate* findStateSlot(scancode_t scanCode) {
  keystate *vacant = nullptr, *reap = nullptr;
  for (auto& s : keyStates) {
    // If we have the same scan code, huzzah!
    if (s.scanCode == scanCode) {
      return &s;
    }
    // If we found a vacancy, potentially use it. We have to keep looking to see
    // if we have the same scan code, though.
    if (s.scanCode == not_a_scancode) {
      vacant = &s;
    } else if (!s.down) {
      if (!reap) {
        reap = &s;
      } else if (s.lastChange < reap->lastChange) {
        // Idle longer than the other reapable candidate; choose
        // the eldest of them
        reap = &s;
      }
    }
  }
  if (vacant) {
    return vacant;
  }
  return reap;
}

// Find the first specified action in the layer stack
action_t resolveActionForScanCodeOnActiveLayer(uint8_t scanCode) {
  layer_t s = layer_pos;
  while (s > 0 && keymap[layer_stack[s]][scanCode] == ___) {
    --s;
  }
  return keymap[layer_stack[s]][scanCode];
}

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
scancode_t getNextScanCode(BoardIO::bits& delta,
                           BoardIO::bits curState,
                           bool& pressed) {
  scancode_t sc = delta.pull_a_bit();
  pressed = curState.get_bit(sc);
  return sc;
}

#if defined(DEBUG)
void dumpScanCode(uint8_t sc, bool pressed) {
  Serial.print("Scan Code ");
  Serial.print(sc, HEX);
  Serial.print(" was ");
  Serial.println(pressed ? "pressed" : "released");
}
void dumpLayers() {
  Serial.print("Layer stack: ");
  for (int i = 0; i <= layer_pos; i++) {
    Serial.print(layer_stack[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
#endif

void layer_push(layer_t layer) {
  DBG(dumpVal(layer, "Push "));
  if (layer_pos < layer_max)
    layer_stack[++layer_pos] = layer;
  DBG(dumpLayers());
}

void layer_pop(layer_t layer) {
  DBG(dumpVal(layer, "Pop "));
  if (layer_pos > 0)
    --layer_pos;
  DBG(dumpLayers());
}

void layer_toggle(layer_t layer) {
  // Toggling a layer: If it exists *anywhere* in the layer stack, turn it
  // off (and fold the layer stack down) If it's *not* in the layer stack,
  // add it.
  for (layer_t l = layer_pos; l != 0; l--) {
    if (layer_stack[l] == layer) {
      DBG(dumpVal(layer, "Turning off layer "));
      DBG(dumpVal(l, "at location "));
      if (layer_pos != l) {
        DBG(dumpVal(layer_pos - l, "Shifting by "));
        memmove(&layer_stack[l], &layer_stack[l + 1], layer_pos - l);
      }
      layer_pos--;
      DBG(dumpLayers());
      return;
    }
  }
  DBG(Serial.print("(For Toggle) "));
  layer_push(layer);
}

void layer_switch(layer_t layer) {
  DBG(dumpVal(layer_stack[layer_pos], "Switching layer "));
  DBG(dumpVal(layer, "to layer "));
  layer_stack[layer_pos] = layer;
  DBG(dumpLayers());
}

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
