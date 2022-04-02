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
}

extern "C" void setup() {
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  BoardIO::Configure();
  resetTheWorld();
}

extern "C" void loop() {
  scancode_t sc;
  bool keysChanged = false, pressed = false;
  uint32_t now = millis();
  Scanner scanner{now};
  while ((sc = scanner.getNextCode(pressed)) != 0xFF) {
    DBG2(dumpHex(sc, "Got scan code 0x"));
    if (!BoardIO::Override(sc, pressed, now)) {
      preprocessScanCode(sc, pressed, now);
      keysChanged = true;
    }
  }
  if (keysChanged) {
    kb_reporter rpt;
    uint16_t menuInfo = ProcessKeys(now, rpt);
    BoardIO::Changed(now, menuInfo);
  }
  scanner.Done();
  BoardIO::Tick(now);
}
