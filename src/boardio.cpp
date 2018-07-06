#include <bluefruit.h>

#include "dbgcfg.h"
#include "boardio.h"

void BoardIO::Configure() const {
  static_assert(
      BoardIO::matrix_size <= 64,
      "Pervasive assumptions that the switch matrix fits in 64 bits.");

  analogReference(AR_INTERNAL_3_0);
  analogReadResolution(12);
  delay(1);

  // For my wiring, the columns are output, and the rows are input...
  for (auto pin : cols) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  for (auto pin : rows) {
    pinMode(pin, INPUT_PULLUP);
  }
  pinMode(led, OUTPUT);

  analogWrite(led, 0);
}

uint64_t BoardIO::Read() const {
  uint64_t switches = 0;
  for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
    uint64_t val = 1ULL << colNum;
    digitalWrite(cols[colNum], LOW);
    for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
      if (!digitalRead(rows[rowNum])) {
        switches |= val << (rowNum * numcols);
      }
    }
    digitalWrite(cols[colNum], HIGH);
  }
  return switches;
}

void BoardIO::setLED(uint32_t brightness) const {
  analogWrite(led, brightness);
}
