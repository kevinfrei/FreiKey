#include "sysstuff.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "generalstate.h"
#include "keystate.h"
#include "scanner.h"
#include "scanning.h"

GeneralState curState{};

// This is called when the system is initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  DBG2(Serial.println("Resetting the world!"));
  curState.reset();
  memset(keyStates, null_scan_code, sizeof(keyStates));
  Scanner::Reset();
  DBG2(Serial.println("World reset!"));
  BoardIO::Reset(curState);
}

extern "C" void setup() {
  // Wait for 2 seconds in case we are trying to attach a serial monitor
  DBG(for (uint16_t iter = 0; !Serial && iter < 2000; iter++) delay(1););
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  BoardIO::Configure();
  resetTheWorld();
}

extern "C" void loop() {
  bool keysChanged = false, pressed = false;
  uint32_t now = millis();
  Scanner scanner{now};
  for (scancode_t sc = scanner.getNextCode(pressed); sc != 0xFF;
       sc = scanner.getNextCode(pressed)) {
    DBG2(dumpHex(sc, "Got scan code 0x"));
    preprocessScanCode(sc, pressed, now);
    keysChanged = true;
  }
  KeyboardMode mode = KeyboardMode::Normal;
  if (keysChanged) {
    kb_reporter rpt;
    mode = ProcessKeys(now, rpt);
    BoardIO::Changed(now, curState);
  }
  scanner.Done();
  BoardIO::Tick(now);
  while (mode != KeyboardMode::Normal) {
    mode = BoardIO::Mode(now, mode);
    DBG2(dumpVal(value_cast(mode), "Mode handler returned "));
    // If we're going back to normal mode
    // Just reset the world: it's easier this way...
    if (mode == KeyboardMode::Normal) {
      resetTheWorld();
      BoardIO::ReturnFromMode();
    }
  }
}