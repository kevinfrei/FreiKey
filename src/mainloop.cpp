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
    preprocessScanCode(sc, pressed, now);
    keysChanged = true;
  }
  uint16_t mode = 0;
  if (keysChanged) {
    kb_reporter rpt;
    mode = ProcessKeys(now, rpt);
    BoardIO::Changed(now, curState);
  }
  scanner.Done();
  BoardIO::Tick(now);
  while (mode != 0) {
    mode = BoardIO::Mode(now, mode);
  }
}