#include <Arduino.h>
#include <stdint.h>

#include "Adafruit_DotStar.h"

// This runs on Adafruit nRF52840 devices

const uint8_t ROWS = 6;
const uint8_t COLS = 6;
const uint32_t debounce_time = 15;

#include "CoreCapability.hpp"


/*
 13 12 11 10  9  7    21 22
 C5 R2 R0 R5 R4 R3 __ C4 C3
|=============================|
          C0 R1 __ __ __ C2 C1
          16 17          24 23
*/

// C0:16 C1:23 C2:24 C3:22 C4:21 C5:13
// R0:11 R1:17 R2:12 R3: 7 R4: 9 R5:10

uint8_t colPins[COLS] = {16, 23, 24, 22, 21, 13};
uint8_t rowPins[ROWS] = {11, 17, 12, 7, 9, 10};

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
  // delay(1);
  return digitalRead(rowPins[rowIdx]) == LOW;
}

void sendData(uint8_t val) {
  Serial1.write(val);
	// Serial.print("Sending data:");
	// Serial.println(val);
}

void indicateChange(uint8_t r, uint8_t c, uint8_t p, uint32_t now) {
  analogWrite(BLUE_LED, p ? 10 : 0);
	/*
	Serial.print("Got row ");
	Serial.print(r);
	Serial.print(" col ");
	Serial.print(c);
	Serial.println(p ? " pressed": " released");
	*/
}

void endColumn(uint8_t colIdx) {
  digitalWrite(colPins[colIdx], HIGH);
	// delay(1);
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
