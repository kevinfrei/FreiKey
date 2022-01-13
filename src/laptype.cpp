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

constexpr BoardIO Laptype = {{19, 21, 23, 14, 22, 20, 9, 10, 3, 2, 7, 4},
                               {16, 12, 18, 5, 1, 0}};

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
  // Blink a bit, just for funsies...
  pinMode(13, OUTPUT);
  for (int i = 0; i < 64; i++) {
    digitalWrite(13, ((i & 7) == 7) ? HIGH : LOW);
    delay(8);
  }
  Laptype.Configure();
  resetTheWorld();
}

extern "C" void loop() {
  uint32_t now = millis();

  // Get the hardware state for the two sides...
  state::hw down{now, bfState, Laptype};

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
