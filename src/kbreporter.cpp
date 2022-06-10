#include "sysstuff.h"

#include "kbreporter.h"

#if defined(ADAFRUIT)

#include "dongle.h"

kb_reporter::kb_reporter() : mods(0), repsize(0) {
  std::fill(std::begin(report), std::end(report), 0);
}

void kb_reporter::set_modifier(uint8_t m) {
  mods = m;
}

void kb_reporter::add_key_press(uint8_t key) {
  if (repsize < 6)
    report[repsize++] = key;
}

void kb_reporter::consumer_press(uint16_t key) {
  Dongle::ConsumerPress(key);
}

void kb_reporter::consumer_release(uint16_t) {
  Dongle::ConsumerRelease();
}

void kb_reporter::send_keys() {
  Dongle::ReportKeys(mods, &report[0]);
}

#elif defined(TEENSY) || defined(MOCK)

kb_reporter::kb_reporter() : mods(0), repsize(0) {
  std::fill(std::begin(report), std::end(report), 0);
}

void kb_reporter::set_modifier(Modifiers mod) {
  mods = getUSBCode(mod);
}

void kb_reporter::add_key_press(Keystroke key) {
  if (repsize < 6) {
    report[repsize++] = getUSBCode(key);
  }
}

void kb_reporter::consumer_press(Consumer kc) {
  // Handle these things in real-time
  Keyboard.press(getConsumerUSBCode(kc));
}

void kb_reporter::consumer_release(Consumer kc) {
  // Handle these things in real-time
  Keyboard.release(getConsumerUSBCode(kc));
}

void kb_reporter::send_keys() {
  Keyboard.set_key1(report[0]);
  Keyboard.set_key2(report[1]);
  Keyboard.set_key3(report[2]);
  Keyboard.set_key4(report[3]);
  Keyboard.set_key5(report[4]);
  Keyboard.set_key6(report[5]);
  Keyboard.set_modifier(mods);
  Keyboard.send_now();
}
#endif
