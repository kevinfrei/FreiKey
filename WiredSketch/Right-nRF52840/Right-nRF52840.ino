// This include is to work around an issue with linking with some Adafruit
// libraries
#include "Adafruit_DotStar.h"
#include "Adafruit_TinyUSB.h"

#include <Arduino.h>
#include <stdint.h>

// This runs on Adafruit nRF52840 devices

const uint8_t ROWS = 6;
const uint8_t COLS = 6;
const uint32_t debounce_time = 15;

#include "CoreCapability.hpp"

// 5 => D2, 6 => MISO[D23], D13 => A3, D12 => A4, D11 => A5, D10 => SCK[D25]
// MOSI[25] => SDA[D21], SCK[26] => SCL[D22], A5 => 5(!), A4 => 7, A3 => 9, A2
// => 10, A1 => 11, A0 => 12

byte colPins[COLS] = {A3, 2, 23, 21, 22, 12}; // Itsy Bitsy
byte rowPins[ROWS] = {10, A4, 11, /*5*/ A1, 7, 9}; // connect to the row pinouts
                                                   // of the keypad

const uint8_t BLUE_LED = 3;

const uint8_t NumDotStarPixels = 1;
const uint8_t DotStarData = 8;
const uint8_t DotStarClock = 6;

Adafruit_DotStar pixel(NumDotStarPixels,
                       DotStarData,
                       DotStarClock,
                       DOTSTAR_GBR);

void setupComms() {
  // If you don't use the debug serial port
  // you have to double-click the reset button to get the device
  // to a flashable state
  Serial.begin(9600);
  // Run at 1Mbps, which seems both plenty fast, and is also reliable
  Serial1.begin(1 << 20);
}

void setupMatrix() {
  digitalWrite(BLUE_LED, HIGH);
  for (uint8_t r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  for (uint8_t c : colPins) {
    pinMode(c, OUTPUT);
    digitalWrite(c, HIGH);
  }
}

void setupIndicators() {
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, LOW);
  pixel.begin();
  pixel.setPixelColor(0, 0x10, 0x10, 0x10);
  pixel.show();
  delay(50);
  pixel.setPixelColor(0, 0, 0, 0);
  pixel.show();
}

void startColumn(uint8_t colIdx) {
  digitalWrite(colPins[colIdx], LOW);
  delay(1);
}

bool readRow(uint8_t rowIdx) {
  return digitalRead(rowPins[rowIdx]) == LOW;
}

void sendData(uint8_t val) {
  Serial1.write(val);
}

void indicateChange(uint8_t r, uint8_t c, uint8_t p, uint32_t now) {
  analogWrite(BLUE_LED, p ? 10 : 0);
}

void endColumn(uint8_t colIdx) {
  digitalWrite(colPins[colIdx], HIGH);
}

uint32_t lastCol = 0;
// Called for every loop: Indicate the passage of time
void timeIndication(uint32_t now) {
  now = now >> 7;
  if (now != lastCol) {
    lastCol = now;
    uint32_t hsv = makeHSV(now % 360, (now / 360) & 0xFF, 50);
    uint32_t col = getColor(hsv);
    pixel.setPixelColor(0, (col >> 16) & 0xFF, (col >> 8) & 0xFF, col & 0xFF);
    pixel.show();
  }
}
