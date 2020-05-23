#pragma once

#include "sysstuff.h"

template <uint8_t pinLED>
struct Analog_LED {
  static void ConfigLED() {
    pinMode(pinLED, OUTPUT);
    delay(1);
    analogWrite(pinLED, 0);
  }
  static void setLED(uint32_t brightness) {
    analogWrite(pinLED, brightness);
  }
};

struct No_Analog_LED {
  static void setLED(uint32_t brightness) {
    // Do nothing: Maybe in the future do something else?
  }
};

template <uint8_t tRED, uint8_t tBLUE>
struct Digital_LEDs {
  static void ConfigLEDs() {
    pinMode(tRED, OUTPUT);
    pinMode(tBLUE, OUTPUT);
  }
  static void setRed(bool on) {
    digitalWrite(tRED, on ? HIGH : LOW);
  }
  static void setBlue(bool on) {
    digitalWrite(tBLUE, on ? HIGH : LOW);
  }
};