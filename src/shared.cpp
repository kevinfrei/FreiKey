#include <bluefruit.h>

#include "dbgcfg.h"
#include "hardware.h"
#include "shared.h"

void shared_setup(const PinData &pd) {
  static_assert(numcols <= 8, "No more than 8 columns, please.");

  // For my wiring, the columns are output, and the rows are input...
  for (auto pin : pd.cols) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  for (auto pin : pd.rows) {
    pinMode(pin, INPUT_PULLUP);
  }
  pinMode(pd.led, OUTPUT);
  analogWrite(pd.led, 0);
  DBG(Serial.begin(115200));
}

void rtos_idle_callback(void) {}
