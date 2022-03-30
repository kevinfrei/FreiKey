#include "sysstuff.h"
#include <bitset>
#include <stdarg.h>
#include <vector>

#include "boardio.h"
#include "general.h"
#include "mock.h"
#include "scanner.h"

extern "C" {
void setup();
void loop();
}

std::bitset<BoardIO::numcols * BoardIO::numrows> switches;
std::vector<pin_mode> pinModes;
std::vector<pin_status> pinValue;

const char* pmName[4] = {"invalid", "ouput", "input", "pullup"};

void pinMode(uint16_t pin, pin_mode mode) {
  // TODO: Check to make sure we're using the pins right in
  // digital/analog/read/write
  if (pin > pinModes.size() || pin > pinValue.size()) {
    printf("Pin out of range\n");
  } else {
    if (pinModes[pin] == pin_mode::invalid) {
      printf("Configure pin %d to state %d (%s)\n",
             pin,
             mode,
             pmName[static_cast<int>(mode)]);
    }
    pinModes[pin] = mode;
  }
}

void digitalWrite(uint16_t pin, pin_status val) {
  if (pin > 23) {
    printf("Pin out of range\n");
  } else if (pinModes[pin] != OUTPUT) {
    printf("Trying to write %d to pin #%d\n", val, pin);
  } else {
    pinValue[pin] = val;
  }
}

pin_status digitalRead(uint16_t pin) {
  uint8_t col = pinToCol[pin];
  if (col == BAD_PIN) {
    return LOW;
  }
  for (uint8_t row = 0; row < BoardIO::numrows; row++) {
    uint8_t rowOfs = row * BoardIO::numcols;
    if (switches[rowOfs + col]) {
      if (pinModes[pin] == INPUT_PULLUP) {
        return pinValue[rowOfs];
      } else {
        return pinValue[rowOfs] == LOW ? HIGH : LOW;
      }
    }
  }
  return (pinModes[pin] == INPUT_PULLUP) ? HIGH : LOW;
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

void MockBoard::Configure() {
  switches.reset();
  // printf("%zu switches\n", switches.size());
  for (uint8_t i = 0; i < 24; i++) {
    pinModes.push_back(pin_mode::invalid);
    pinValue.push_back(pin_status::invalid);
  }
  ConfigMatrix();
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
