#include "sysstuff.h"

#include "boardio.h"
#include "hardware"
#include "wired-client.h"

MatrixBits prevBits{0};
Debouncer<MatrixBits> debouncer{};

MatrixBits key_scan(uint32_t now) {
  auto res = BoardIO::Read();
  return debouncer.update(res, now);
}

extern "C" void setup() {
  Serial1.begin(1 << 20); // 1Mbps
  BoardIO::Configure();
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
    }
    // The % 3 is a little bit of validation...
    Serial1.write(sc * 3 + sc % 3);
  }
}