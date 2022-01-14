#pragma once

#include "sysstuff.h"

struct Teensy {
  // This configuration make sit so the Teensy LED (on pin 13)
  // doesn't stay lit 99.999% of the time...
  static void configOutputPin(uint8_t pin) {
    pinMode(pin, INPUT);
  }
  static void configInputPin(uint8_t pin) {
    pinMode(pin, INPUT_PULLUP);
  }
  static void prepPinForRead(uint8_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(200);
  }
  static void completePin(uint8_t pin) {
    pinMode(pin, INPUT);
  }
};
