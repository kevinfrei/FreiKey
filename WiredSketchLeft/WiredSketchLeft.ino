// This include is to work around an issue with linking with some Adafruit
// libraries

// #include "Adafruit_TinyUSB.h"

// This one is actually *used*

// #include <Adafruit_DotStar.h>

#include <Arduino.h>
#include <stdint.h>

// This runs on Adafruit nRF52840 devices

const uint8_t ROWS = 6;
const uint8_t COLS = 6;

// 5 => D2, 6 => MISO[D23], D13 => A3, D12 => A4, D11 => A5, D10 => SCK[D25]
// MOSI[25] => SDA[D21], SCK[26] => SCL[D22], A5 => 5(!), A4 => 7, A3 => 9, A2
// => 10, A1 => 11, A0 => 12

// uint8_t colPins[COLS] = {12, 6, 5, A4, SCK, MOSI}; // Feather
uint8_t colPins[COLS] = {A4, MISO, 2, 7, 22, 21}; // ItsyBitsy
// uint8_t rowPins[ROWS] = {A1, A0, A2, 10, 11, 13}; // Feather
uint8_t rowPins[ROWS] = {11, 12, 10, 25, A5, A3}; // ItsyBitsy

uint32_t last_change[COLS * ROWS] = {0};
bool pressed[COLS * ROWS] = {0};
const uint32_t debounce_time = 15;
const uint8_t BLUE_LED = 3;

const uint8_t NumDotStarPixels = 1;
const uint8_t DotStarData = 8;
const uint8_t DotStarClock = 6;
/*
Adafruit_DotStar pixel(NumDotStarPixels,
                       DotStarData,
                       DotStarClock,
                       DOTSTAR_GBR);
*/
void setup() {
  // If you don't use the debug serial port
  // you have to double-click the reset button to get the device
  // to a flashable state
  Serial.begin(9600);
  // Run at 1Mbps, which seems both plenty fast, and is also reliable
  Serial1.begin(1 << 20);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, HIGH);
  for (uint8_t r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  for (uint8_t c : colPins) {
    pinMode(c, OUTPUT);
    digitalWrite(c, HIGH);
  }
  digitalWrite(BLUE_LED, LOW);
  /*  pixel.begin();
    pixel.setPixelColor(0, 0x10, 0x10, 0x10);
    pixel.show();
    delay(50);
    pixel.setPixelColor(0, 0, 0, 0);
    pixel.show();*/
}

void loop() {
  uint32_t now = millis();
  for (uint8_t c = 0; c < COLS; c++) {
    digitalWrite(colPins[c], LOW);
    delay(1);
    for (uint8_t r = 0; r < ROWS; r++) {
      delay(1);
      bool p = digitalRead(rowPins[r]) == LOW;
      if (p != pressed[r * 6 + c] &&
          last_change[r * 6 + c] < now + debounce_time) {
        uint8_t val = r * 6 + c + (p ? 0 : 36);
        Serial1.write((unsigned char)(val * 3 + val % 3 + 1));
        analogWrite(BLUE_LED, p ? 10 : 0);
        pressed[r * 6 + c] = p;
        last_change[r * 6 + c] = now;
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
}
