// This include is to work around an issue with linking with some Adafruit
// libraries
#include "Adafruit_TinyUSB.h"

#include <Arduino.h>
#include <stdint.h>

#include "Adafruit_DotStar.h"
#include "Adafruit_NeoPixel.h"

// This runs on Adafruit nRF52840 devices

const uint8_t ROWS = 6;
const uint8_t COLS = 6;
const uint32_t debounce_time = 15;

#include "CoreCapability.hpp"

#if defined(ARDUINO_NRF52480_ITSYBITSY)
uint8_t colPins[COLS] = {A4, MISO, 2, 7, 22, 21}; // ItsyBitsy
uint8_t rowPins[ROWS] = {11, 12, 10, 25, A5, A3}; // ItsyBitsy
const uint8_t BLUE_LED = 3;

const uint8_t NumDotStarPixels = 1;
const uint8_t DotStarData = 8;
const uint8_t DotStarClock = 6;

Adafruit_DotStar pixel(NumDotStarPixels,
                       DotStarData,
                       DotStarClock,
                       DOTSTAR_GBR);

#elif defined(ARDUINO_NRF52840_FEATHER)

uint8_t colPins[COLS] = {12, 6, 5, A4, SCK, MOSI}; // Feather
uint8_t rowPins[ROWS] = {A1, A0, A2, 10, 11, 13}; // Feather

const uint8_t BLUE_LED = 4;

Adafruit_NeoPixel pixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

#else 
#error Sorry: unsupported hardware
#endif


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
    uint32_t hsv = makeHSV(now % 360, (now / 360) & 0xFF, 20);
    uint32_t col = getColor(hsv);
    pixel.setPixelColor(0, (col >> 16) & 0xFF, (col >> 8) & 0xFF, col & 0xFF);
    pixel.show();
  }
}
