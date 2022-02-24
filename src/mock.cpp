#include "sysstuff.h"
#include <stdarg.h>
#include <bitset>

#include "boardio.h"
#include "general.h"
#include "keymap.h"
#include "mock.h"
#include "scanner.h"

extern "C" {
void setup();
void loop();
}

std::bitset<72> switches{};

void pinMode(uint16_t pin, uint8_t mode) {
  // TODO: Check to make sure we're using the pins right in
  // digital/analog/read/write
}

void digitalWrite(uint16_t pin, uint32_t val) {
  // TODO: check, record, report?
}

uint8_t digitalRead(uint16_t pin) {
  // TODO: Make this do some stuff?
  return 0;
}

void waitForEvent() {}

static uint64_t curClock = 0;

void delayMicroseconds(uint32_t us) {
  // Update the 'clock' and add a little extra, for fun
  curClock += us + (us & 1) * ((us >> 4) & 0x7F);
}

void delay(uint32_t ms) {
  delayMicroseconds(ms * 1000);
}

// TODO: Make this work for real?
uint32_t millis() {
  return curClock / 995; // Skewed to add a little extra 'fun'
}

uint32_t micros() {
  return curClock & 0xFFFFFFFF;
}

SerialMock Serial;
void SerialMock::begin(uint32_t) {}
void SerialMock::print(const char* str) {
  printf(str);
}

void SerialMock::print(uint32_t val, int base) {
  if (base == 10 || base == 0) {
    printf("%d", val);
  } else if (base == 16) {
    printf("%x", val);
  } else {
    printf("%d (not in base %d)", val, base);
  }
}
void SerialMock::printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}
void SerialMock::println(char const* str) {
  printf("%s\n", str);
}

void SerialMock::println(uint32_t val, int base) {
  print(val, base);
  printf("\n");
}

SerialMock::operator bool() {
  return true;
}

// Teensy stuff
KeyboardMock Keyboard;
void KeyboardMock::press(uint16_t) {}
void KeyboardMock::release(uint16_t) {}
void KeyboardMock::set_key1(uint8_t) {}
void KeyboardMock::set_key2(uint8_t) {}
void KeyboardMock::set_key3(uint8_t) {}
void KeyboardMock::set_key4(uint8_t) {}
void KeyboardMock::set_key5(uint8_t) {}
void KeyboardMock::set_key6(uint8_t) {}
void KeyboardMock::set_modifier(uint8_t) {}
void KeyboardMock::send_now() {}

/*
BoardIO::bits BoardIO::Read() const {
  BoardIO::bits switches{};
  return switches;
}
*/

void MockBoard::Configure() {
  // Do nothing for now...
}
void MockBoard::Changed(uint32_t) {
  // Do nothing for now...
}
void MockBoard::Tick(uint32_t now) {
  // Do nothing for now...
}

// This where I should run some tests, right?
int main(int argc, const char* argv[]) {
  setup();
  while (1) {
    loop();
  }
}
