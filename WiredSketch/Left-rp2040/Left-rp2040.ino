#include <Arduino.h>
#include <stdint.h>

#include <Adafruit_NeoPixel.h>

// This runs on Adafruit Feather RP2040 devices

constexpr byte ROWS = 6;
constexpr byte COLS = 6;

/*
 26 27 28 29 24 25 __ 18 19
 C5 R2 R0 R5 R4 R3 __ C4 C3
|=============================|
          C0 R1 __ __ __ C2 C1
          13 12 __ __ __  8  7
*/

// C0:13 C1: 7 C2: 8 C3:20 C4:19 C5:26
// R0:28 R1:12 R2:27 R3:25 R4:24 R5:29

uint8_t colPins[COLS] = {12, 8, 7, 24, 18, 19};
uint8_t rowPins[ROWS] = {27, 26, 28, 10, 11, 13};

constexpr uint32_t debounce_time = 25;

uint32_t last_change[COLS * ROWS] = {0};
bool pressed[COLS * ROWS] = {0};

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setupComms() {
  // Run at 1Mbps, which seems both plenty fast, and is also reliable
  Serial1.begin(1 << 20);
  Serial.begin(115200);
}

void setupMatrix() {
  // Configure the pins
  for (uint8_t r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  for (uint8_t c : colPins) {
    pinMode(c, OUTPUT);
    digitalWrite(c, HIGH);
  }
}

void setupIndicators() {
  // Configure the neopixel for silly debug info
  // pinMode(NEOPIXEL_POWER, OUTPUT);
  // digitalWrite(NEOPIXEL_POWER, HIGH);
  pixels.begin();
}

uint8_t index(uint8_t row, uint8_t col) {
  return row * 6 + col;
}

uint8_t encodeValue(uint8_t row, uint8_t col, bool pressed) {
  uint8_t code = index(row, col) + (pressed ? 0 : 36);
  // Now add some miniscule amount of error resilience:
  return code * 3 + code % 3 + 1;
}

void indicateChange(uint8_t r, uint8_t c, uint8_t p) {
  pixels.clear();
  pixels.setPixelColor(
    0, p ? pixels.Color(16, 45 + r * 42, 45 + c * 42) : pixels.Color(0, 0, 0));
  pixels.show();
}

void reportChange(uint8_t r, uint8_t c, uint8_t p) {
  Serial1.write(encodeValue(r, c, p));
  indicateChange(r, c, p);
  Serial.print("r:");
  Serial.print(r);
  Serial.print(" c:");
  Serial.print(c);
  Serial.print(" p:");
  Serial.println(p ? "presseed" : "released");
}

bool debouncedChange(uint8_t r, uint8_t c, bool p, uint32_t now) {
  uint8_t idx = index(r, c);
  return p != pressed[idx] && last_change[idx] < now - debounce_time;
}

// Record the state & the last-change time
void recordChange(uint8_t r, uint8_t c, bool p, uint32_t now) {
  uint8_t idx = index(r, c);
  pressed[idx] = p;
  last_change[idx] = now;
}

void setup() {
  setupComms();
  setupMatrix();
  setupIndicators();
}

void loop() {
  for (uint8_t c = 0; c < COLS; c++) {
    digitalWrite(colPins[c], LOW);
    // This looks arbitrary but it seems to take
    // the output change a little while to stabilize on the input pins
    delay(1);
    uint32_t now = millis();
    for (uint8_t r = 0; r < ROWS; r++) {
      bool p = digitalRead(rowPins[r]) == LOW;
      if (debouncedChange(r, c, p, now)) {
        // Report the change up the wire
        reportChange(r, c, p);
        recordChange(r, c, p, now);
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
}
