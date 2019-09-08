#include "sysstuff.h"

#include "boardio.h"
#include "dbgcfg.h"
#include "globals.h"

#if defined(TEENSY)

// This configuration make sit so the Teensy LED (on pin 13)
// doesn't stay lit 99.999% of the time...
#define configPin(pin) pinMode(pin, INPUT)
#define prepPinForRead(pin) \
  pinMode(pin, OUTPUT);     \
  digitalWrite(pin, LOW)
#define completePin(pin) pinMode(pin, INPUT)

#else

#define configPin(pin)  \
  pinMode(pin, OUTPUT); \
  digitalWrite(pin, HIGH)
#define prepPinForRead(pin) digitalWrite(pin, LOW)
#define completePin(pin) digitalWrite(pin, HIGH)

#endif

void BoardIO::Configure() const {
#if defined(HAS_LED)
  analogReference(AR_INTERNAL_3_0);
  analogReadResolution(12);
  delay(1);
#endif

  // For my wiring, the columns are output, and the rows are input...
  for (auto pin : cols) {
    DBG(dumpVal(pin, "Output Pin "));
    configPin(pin);
  }
  for (auto pin : rows) {
    DBG(dumpVal(pin, "Input Pullup "));
    pinMode(pin, INPUT_PULLUP);
  }
#if defined(HAS_LED)
  pinMode(led, OUTPUT);
  delay(1);
  analogWrite(led, 0);
#endif
#if defined(ADAFRUIT)
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
#endif
}

BoardIO::bits BoardIO::Read() const {
  BoardIO::bits switches{};
  for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
    prepPinForRead(cols[colNum]);
    delay(1); // TODO: Make this faster (which it microseconds)
    for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
      if (!digitalRead(rows[rowNum])) {
        switches.set_bit(rowNum * numcols + colNum);
      }
    }
    completePin(cols[colNum]);
  }
  return switches;
}

#if defined(HAS_LED)
void BoardIO::setLED(uint32_t brightness) const {
  analogWrite(led, brightness);
}
#endif

#if defined(HAS_BATTERY)
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
#endif

#if defined(ADAFRUIT)
void BoardIO::setRed(bool on) {
  digitalWrite(LED_RED, on ? HIGH : LOW);
}

void BoardIO::setBlue(bool on) {
  digitalWrite(LED_BLUE, on ? HIGH : LOW);
}
#endif
