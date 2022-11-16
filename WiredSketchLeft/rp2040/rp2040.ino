#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

// This runs on Adafruit ItsyBitsy RP2040 devices

constexpr uint8_t ROWS = 6;
constexpr uint8_t COLS = 6;

// Left wire schematic from key matrix:

// Top left to right (viewed from above)
// C3, C4, R3_R3, R4, C5, R5
// Bottom left to right
// C0, C1, C2_C2, R2_R2, R0, R1 

// On the ItsyBitys rp2040:
// Top pins
// C3 = D2/GPIO12, C4 = MISO/GPIO20, R3x = MOSI/GPIO19,
// R3y = SCK/GPIO18, R4 = D25/GPIO25, C5 = D24/GPIO24, R5 = A3/GPIO29
// Bottom pins
// C0 = SDA/GPIO2, C1 = SCL/GPIO3, C2x = D13/GPIO11, C2y = D7, GPIO6
// R2x = D9/GPIO7, R2y = D10/GPIO8, R0 = D11/GPIO9, R1 = D12/GPIO10

// And now, I have to reverse the columns: C0 is the *center* column, so oops:
constexpr uint8_t colPins[COLS] = {24, 20, 12, 6, 3, 2}; // ItsyBitsy RP2040
constexpr uint8_t rowPins[ROWS] = {9, 10, 7, 18, 25, 29}; // ItsyBitsy RP2040

uint32_t last_change[COLS * ROWS] = {0};
bool pressed[COLS * ROWS] = {0};
constexpr uint32_t debounce_time = 15;
constexpr uint8_t NORMAL_LED = PIN_LED;

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  // If you don't use the debug serial port
  // you have to double-click the reset button to get the device
  // to a flashable state
  // Serial.begin(9600);
  // Run at 1Mbps, which seems both plenty fast, and is also reliable
  Serial1.begin(1 << 20);

  // Configure the pins
  for (uint8_t r : rowPins) {
    pinMode(r, INPUT_PULLUP);
  }
  for (uint8_t c : colPins) {
    pinMode(c, OUTPUT);
    digitalWrite(c, HIGH);
  }

  // Configure the neopixel for silly debug info
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  pixels.begin();
}

void loop() {
  uint32_t now = millis();
  for (uint8_t c = 0; c < COLS; c++) {
    digitalWrite(colPins[c], LOW);
    delayMicroseconds(250); // This is irritating, but it seems to take a little while to stabilize...
    for (uint8_t r = 0; r < ROWS; r++) {
      bool p = digitalRead(rowPins[r]) == LOW;
      if (p != pressed[r * 6 + c] &&
          last_change[r * 6 + c] < now + debounce_time) {
        uint8_t val = r * 6 + c + (p ? 0 : 36);
        Serial1.write((unsigned char)(val * 3 + val % 3 + 1));
        pixels.clear();
        pixels.setPixelColor(0, p ? pixels.Color(0xFF, 42 + r * 42, 42 + c * 42) : pixels.Color(0,0,0));
        pixels.show();

        pressed[r * 6 + c] = p;
        last_change[r * 6 + c] = now;
      }
    }
    digitalWrite(colPins[c], HIGH);
  }
}
