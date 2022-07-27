#include "sysstuff.h"

#include <bitset>
#include <iostream>
#include <stdarg.h>
#include <vector>

#include "boardio.h"
#include "enumhelpers.h"
#include "generalstate.h"
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
    std::cerr << "Pin out of range" << std::endl;
  } else {
    if (pinModes[pin] == pin_mode::invalid) {
      std::cout << "Configure pin " << pin << " to state " << value_cast(mode)
                << " (" << pmName[value_cast(mode)] << ")" << std::endl;
    }
    pinModes[pin] = mode;
  }
}

void digitalWrite(uint16_t pin, pin_status val) {
  if (pin > 23) {
    std::cerr << "Pin out of range" << std::endl;
  } else if (pinModes[pin] != OUTPUT) {
    std::cerr << "Trying to write " << value_cast(val) << " to pin #" << pin
              << std::endl;
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
  std::cout << str;
}

void SerialMock::print(uint32_t val, int base) {
  if (base == 10 || base == 0) {
    std::cout << val;
  } else if (base == 16) {
    std::cout << std::hex << val << std::dec;
  } else {
    std::cout << val << " (not in base " << base << ")";
  }
}

void SerialMock::printf(const char* fmt, ...) {
  char buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsprintf(&buffer[0], fmt, args);
  va_end(args);
  std::cout << &buffer[0];
}

void SerialMock::println(char const* str) {
  std::cout << str << std::endl;
}

void SerialMock::println(uint32_t val, int base) {
  print(val, base);
  std::cout << std::endl;
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
void KeyboardMock::print(const char*) {}
void KeyboardMock::print(char) {}
void KeyboardMock::print(int) {}

void BoardIO::Configure() {
  switches.reset();
  std::cout << switches.size() << " switches" << std::endl;
  for (uint8_t i = 0; i < 24; i++) {
    pinModes.push_back(pin_mode::invalid);
    pinValue.push_back(pin_status::invalid);
  }
  ConfigMatrix();
}
void BoardIO::Reset(GeneralState&) {}
void BoardIO::Changed(uint32_t, GeneralState&) {
  // Do nothing for now...
}
void BoardIO::Tick(uint32_t now) {
  // Do nothing for now...
}

KeyboardMode BoardIO::Mode(uint32_t now, KeyboardMode mode) {
  return KeyboardMode::Normal;
}

void BoardIO::ReturnFromMode() {}

void BoardIO::ShowScanCode(uint16_t sc) {}

// This where I should run some tests, right?
int main(int argc, const char* argv[]) {
  setup();
  while (1) {
    loop();
  }
}

void Scanner::Reset() {}

Scanner::Scanner(uint32_t now) {}
scancode_t Scanner::getNextCode(bool& pressed) {
  pressed = false;
  return null_scan_code;
}
void Scanner::Done() {}
