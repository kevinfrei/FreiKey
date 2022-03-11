#include "sysstuff.h"

#include "boardio.h"
#include "debounce.h"
#include "keystate.h"
#include "scanner.h"
// #include "hardware.h"
// #include "wired-client.h"

MatrixBits prevBits{0};
Debouncer<MatrixBits> debouncer{};

MatrixBits key_scan(uint32_t now) {
  auto res = BoardIO::Read();
  return debouncer.update(res, now);
}

extern "C" void setup() {
  BoardIO::Configure();
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

extern "C" void loop() {
  uint32_t now = millis();
  // Get the before & after
  MatrixBits before = prevBits;
  MatrixBits after = key_scan(now);
  MatrixBits delta = before.delta(after);
  bool keysChanged = delta.any();
  while (delta.any()) {
    bool pressed;
    scancode_t sc = getNextScanCode(delta, after, pressed);
    if (!pressed) {
      sc += 36;
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_BLUE, HIGH);
    } else {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_BLUE, LOW);
    }
    // The % 3 is a little bit of validation...
    Serial1.write(sc * 3 + sc % 3);
  }
}

void RightModule::Configure() {
  Serial1.begin(1 << 20);
}
