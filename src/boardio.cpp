#include "mybluefruit.h"

#include "boardio.h"
#include "dbgcfg.h"

void BoardIO::Configure() const {
  analogReference(AR_INTERNAL_3_0);
  analogReadResolution(12);
#if !defined(USB_MASTER)
  static_assert(
      BoardIO::matrix_size <= 64,
      "Pervasive assumptions that the switch matrix fits in 64 bits.");
  delay(1);

  // For my wiring, the columns are output, and the rows are input...
  for (auto pin : cols) {
    DBG(dumpVal(pin, "Output Pin "));
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  for (auto pin : rows) {
    DBG(dumpVal(pin, "Input Pullup "));
    pinMode(pin, INPUT_PULLUP);
  }
#endif

  pinMode(led, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  analogWrite(led, 0);
}

#if !defined(USB_MASTER)
uint64_t BoardIO::Read() const {
  uint64_t switches = 0;
  for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
    digitalWrite(cols[colNum], LOW);
    delay(1); // Seems slow, here
    for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
      if (!digitalRead(rows[rowNum])) {
        switches |= 1ULL << (rowNum * numcols + colNum);
      }
    }
    digitalWrite(cols[colNum], HIGH);
  }
  return switches;
}
#endif

void BoardIO::setLED(uint32_t brightness) const {
  analogWrite(led, brightness);
}

// pin 31 on the 832, pin 30 on the 840, is available for sampling the battery
constexpr uint8_t VBAT_PIN = PIN_VBAT;

// 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
constexpr uint32_t VBAT_NUM = 3000;
constexpr uint32_t VBAT_DEN = 4096;

// This stuff shamelessly stolen from the AdaFruit example
uint8_t BoardIO::getBatteryPercent() {
  uint32_t bat = analogRead(VBAT_PIN) * VBAT_NUM / VBAT_DEN;
  if (bat >= 3000) {
    return 100;
  } else if (bat > 2900) {
    return 100 - ((3000 - bat) * 58) / 100;
  } else if (bat > 2740) {
    return 42 - ((2900 - bat) * 24) / 160;
  } else if (bat > 2440) {
    return 18 - ((2740 - bat) * 12) / 300;
  } else if (bat > 2100) {
    return 6 - ((2440 - bat) * 6) / 340;
  } else {
    return 0;
  }
}
