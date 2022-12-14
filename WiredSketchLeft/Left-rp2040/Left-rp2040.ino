#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

// This runs on Adafruit ItsyBitsy RP2040 devices

constexpr uint8_t RP2040_LED = 11;
constexpr uint8_t RP2040_NEOPIXEL = 17;
constexpr uint8_t RP2040_NEOPIXEL_POWER = 16;

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

constexpr uint8_t ROWS = 6;
constexpr uint8_t COLS = 6;
// And now, I have to reverse the columns: C0 is the *center* column, so oops:
constexpr uint8_t colPins[COLS] = {24, 20, 12, 6, 3, 2}; // ItsyBitsy RP2040
constexpr uint8_t rowPins[ROWS] = {9, 10, 7, 18, 25, 29}; // ItsyBitsy RP2040
constexpr uint32_t debounce_time = 25;

uint32_t last_change[COLS * ROWS] = {0};
bool pressed[COLS * ROWS] = {0};

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

uint32_t hsvToRgb(float h, float s, float v) {
  float r=0, g=0, b=0;
  int i = int(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);
  switch(i % 6){
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }

  return (int(r * 255) << 16) | (int(g * 255) << 8) | int(b * 255);
}

void setupComms() {
  // Run at 1Mbps, which seems both plenty fast, and is also reliable
  Serial1.begin(1 << 20);  
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
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  pixels.begin();
  pixels.setPixelColor(0, 0x404040);
  pixels.show();
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

float sat = 0.8f;

uint32_t getColor(uint32_t number) {
  float hue = (number % 360) / 360.0f; 
  return hsvToRgb(hue, .9f, .3f);
}

uint8_t index(uint8_t row, uint8_t col) {
  return row * 6 + col;
}

uint8_t encodeValue(uint8_t row, uint8_t col, bool pressed) {
  uint8_t code = index(row, col) + (pressed ? 0 : 36);
  // Now add some miniscule amount of error resilience:
  return code * 3 + code % 3 + 1;
}

void indicateChange(uint8_t r, uint8_t c, uint8_t p, uint32_t now) {
  sat = (sat < .5f) ? .8f : .2f;
}

void reportChange(uint8_t r, uint8_t c, uint8_t p) {
  Serial1.write(encodeValue(r, c, p));
}

bool debouncedChange(uint8_t r, uint8_t c, bool p, uint32_t now) {
  uint8_t idx = index(r, c);
  return p != pressed[idx] && last_change[idx] < now + debounce_time;
}

// Record the state & the last-change time
void recordChange(uint8_t r, uint8_t c, bool p, uint32_t now) {
  uint8_t idx = index(r, c);
  pressed[idx] = p;
  last_change[idx] = now;
  indicateChange(r, c, p, now);
}

void setup() {
  setupComms();
  setupMatrix();
  setupIndicators();
}

void loop() {
  uint32_t now = millis();
  for (uint8_t c = 0; c < COLS; c++) {
    digitalWrite(colPins[c], LOW);
    // This looks arbitrary but it seems to take
    // the output change a little while to stabilize on the input pins
    delayMicroseconds(1250);
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
  digitalWrite(PIN_LED, (now & 0x200) ? LOW : HIGH);
  pixels.clear();
  pixels.setPixelColor(0, getColor(now>>4));
  pixels.show();
}
