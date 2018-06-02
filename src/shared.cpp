#include <bluefruit.h>

#include "dbgcfg.h"
#include "hwstate.h"
#include "shared.h"

void shared_setup() {
  static_assert(numcols <= 8, "No more than 8 columns, please.");

  // For my wiring, the columns are output, and the rows are input...
  for (auto pin : colPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  for (auto pin : rowPins) {
    pinMode(pin, INPUT_PULLUP);
  }

  DBG(Serial.begin(115200));
}

void rtos_idle_callback(void) {}
