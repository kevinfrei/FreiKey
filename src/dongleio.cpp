#include "mybluefruit.h"

#include "dbgcfg.h"
#include "dongleio.h"
#include "globals.h"

Adafruit_NeoPixel DongleIO::neopix{1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800};

void DongleIO::Configure() {
  // This is the user switch
  pinMode(7, INPUT_PULLUP);
  // Blink the RGB light on the board
  neopix.begin();
  setRGB(7, 5, 0);
  delay(125);
  setRGB(0, 0, 0);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void DongleIO::setRed(bool on) {
  digitalWrite(LED_RED, on ? HIGH : LOW);
}

void DongleIO::setBlue(bool on) {
  digitalWrite(LED_BLUE, on ? HIGH : LOW);
}

void DongleIO::setRGB(uint8_t r, uint8_t g, uint8_t b) {
  neopix.setPixelColor(0, r, g, b);
  neopix.show();
}
