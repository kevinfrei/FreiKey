#include <stdint.h>

uint32_t last_change[COLS * ROWS] = {0};
bool pressed[COLS * ROWS] = {0};

uint32_t hsvToRgb(float h, float s, float v) {
  float r = 0, g = 0, b = 0;
  int i = int(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);
  switch (i % 6) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    case 5:
      r = v;
      g = p;
      b = q;
      break;
  }
  return (int(r * 255) << 16) | (int(g * 255) << 8) | int(b * 255);
}

void setupComms();
void setupMatrix();
void setupIndicators();
// Called when starting a column (probably write low, with delay)
void startColumn(uint8_t colIdx);
// Called when ending a column (probably a write high, no delay?)
void endColumn(uint8_t colIdx);
// Returns true if the cur column + row is pressed (probably read == LOW)
bool readRow(uint8_t rowIdx);
// Called for every loop: Indicate the passage of time
void timeIndication(uint32_t now);
// This sends the data over the comms channel
void sendData(uint8_t value);
// You can indiate a key change in here:
void indicateChange(uint8_t r, uint8_t c, uint8_t p, uint32_t now);

uint32_t makeHSV(uint16_t hue, uint8_t sat, uint8_t val) {
  return hue << 16 | sat << 8 | val;
}

uint32_t getColor(uint32_t number) {
  float val = (float)(number & 0xFF) / 255.0f;
  float sat = (float)((number >> 8) & 0xFF) / 255.0f;
  float hue = ((number >> 16) % 360) / 360.0f;
  return hsvToRgb(hue, sat, val);
}

uint8_t index(uint8_t row, uint8_t col) {
  return row * 6 + col;
}

uint8_t encodeValue(uint8_t row, uint8_t col, bool pressed) {
  uint8_t code = index(row, col) + (pressed ? 0 : 36);
  // Now add some miniscule amount of error resilience:
  return code * 3 + code % 3 + 1;
}

// Record the state & the last-change time, and report it to the controller
void reportChange(uint8_t r, uint8_t c, uint8_t p, uint32_t now) {
  uint8_t idx = index(r, c);
  pressed[idx] = p;
  last_change[idx] = now;
  sendData(encodeValue(r, c, p));
  indicateChange(r, c, p, now);
}

bool debouncedChange(uint8_t r, uint8_t c, bool p, uint32_t now) {
  uint8_t idx = index(r, c);
  return p != pressed[idx] && last_change[idx] < now - debounce_time;
}

void setup() {
  setupComms();
  setupMatrix();
  setupIndicators();
}

void loop() {
  for (uint8_t c = 0; c < COLS; c++) {
    startColumn(c);
    uint32_t now = millis();
    for (uint8_t r = 0; r < ROWS; r++) {
      bool p = readRow(r);
      if (debouncedChange(r, c, p, now)) {
        // Report the change up the wire
        reportChange(r, c, p, now);
      }
    }
    endColumn(c);
  }
  timeIndication(millis());
}
