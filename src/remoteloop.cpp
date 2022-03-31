#include "sysstuff.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "generalstate.h"
#include "keystate.h"
#include "scanner.h"

GeneralState curState{};

#define right Serial2
#define left Serial4

// This is called when the system is initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  DBG2(Serial.println("Resetting the world!"));
  curState.reset();
  // memset(keyStates, null_scan_code, sizeof(keyStates));
  DBG2(Serial.println("World reset!"));
}

extern "C" void setup() {
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  DBG2(dumpVal(115200, "Debugging Serial port configured to "));
  right.begin(1 << 20);
  left.begin(1 << 20);
  BoardIO::Configure();
  resetTheWorld();
}

extern "C" void loop() {
  uint32_t now = millis();
  bool keysChanged = false;
  bool pressed = false;
  for (scancode_t sc = getNextScanCode(left, right, pressed); sc != 0xFF;
       sc = getNextScanCode(left, right, pressed)) {
    DBG2(dumpHex(sc, "Got scan code 0x"));
    preprocessScanCode(sc, pressed, now);
    keysChanged = true;
  }
  if (keysChanged) {
    kb_reporter rpt;
    ProcessKeys(now, rpt);
    BoardIO::Changed(now);
  }
  BoardIO::Tick(now);
}
