#pragma once

#include "sysstuff.h"

// Bit 1/1 == num lock, Bit 2/2 == caps lock, Bit 3/4 == scroll lock
extern volatile uint8_t keyboard_leds;
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
    delayMicroseconds(250);
  }
  static void completePin(uint8_t pin) {
    pinMode(pin, INPUT);
  }
  static bool isNumLocked() {
    return keyboard_leds & 1;
  }
  static bool isCapsLocked() {
    return keyboard_leds & 2;
  }
  static bool isScrollLocked() {
    return keyboard_leds & 4;
  }
};
