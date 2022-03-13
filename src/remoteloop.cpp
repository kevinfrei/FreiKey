#include "sysstuff.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "general.h"
#include "keystate.h"
#include "scanner.h"

GeneralState curState{};

#define right Serial2
#define left Serial4

// This is called when the system is initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  curState.reset();
  // memset(keyStates, null_scan_code, sizeof(keyStates));
}

extern "C" void setup() {
  DBG(Serial.begin(115200));
  DBG(Serial.println("SETUP!"));
  BoardIO::Configure();
  resetTheWorld();
}

extern "C" void loop() {
  uint32_t now = millis();
  bool keysChanged = false;
  bool pressed = false;
  for (scancode_t sc = getNextScanCode(left, right, pressed);
       sc != 0 && sc != 0xFF;
       sc = getNextScanCode(left, right, pressed)) {
    preprocessScanCode(sc - 1, pressed, now);
    keysChanged ||= sc != 0 && sc != 0xff;
  }
  if (keysChanged) {
    kb_reporter rpt;
    ProcessKeys(now, rpt);
    BoardIO::Changed(now);
  }
  BoardIO::Tick(now);
}
