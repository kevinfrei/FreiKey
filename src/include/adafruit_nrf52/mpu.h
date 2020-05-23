#pragma once

#include "sysstuff.h"


struct AdafruitNRF52 {
  static void configOutputPin(uint8_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  static void configInputPin(uint8_t pin) {
    pinMode(pin, INPUT_PULLUP);
  }
  static void prepPinForRead(uint8_t pin) {
    digitalWrite(pin, LOW);
  }
  static void completePin(uint8_t pin) {
    digitalWrite(pin, HIGH);
  }
};
