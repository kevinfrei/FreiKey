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
  Dbg2 << "Resetting the world!" << sfmt::endl;
  curState.reset();
  memset(keyStates, null_scan_code, sizeof(keyStates));
  Scanner::Reset();
  Dbg2 << "World reset!" << sfmt::endl;
  BoardIO::Reset(curState);
}

extern "C" void setup() {
  // Wait for 2 seconds in case we are trying to attach a serial monitor
  DBG(for (uint16_t iter = 0; !Serial && iter < 2000; iter++) delay(1););
  DBG(Serial.begin(115200));
  Dbg << "SETUP!" << sfmt::endl;
  BoardIO::Configure();
  resetTheWorld();
}

extern "C" void loop() {
  bool keysChanged = false, pressed = false;
  uint32_t now = millis();
  Scanner scanner{now};
  for (scancode_t sc = scanner.getNextCode(pressed); sc != 0xFF;
       sc = scanner.getNextCode(pressed)) {
    Dbg2 << "Got scan code 0x" << sfmt::hex << sc << sfmt::endl;
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
    auto newmode = BoardIO::Mode(now, mode);
    Dbg2 << "Mode handler returned " << newmode;
    // If we're going back to normal mode
    // Just reset the world: it's easier this way...
    if (newmode != mode) {
      resetTheWorld();
      BoardIO::ReturnFromMode();
    }
    mode = newmode;
  }
}