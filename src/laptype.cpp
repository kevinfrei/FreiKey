#include "sysstuff.h"

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

MatrixBits key_scan(uint32_t now) {
  auto res = LaptypeBoard::Read();
  return debouncer.update(res, now);
}

// This is called when the system is initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  curState.reset();
  memset(keyStates, null_scan_code, sizeof(keyStates));
}

extern "C" void setup() {
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  LaptypeBoard::Configure();
  resetTheWorld();
}

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
    LaptypeBoard::Changed(now);
  }
  LaptypeBoard::Tick(now);
}
