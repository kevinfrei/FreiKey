#if !defined(DONGLEIO_H)
#define DONGLEIO_H

#include "mybluefruit.h"

#include "Adafruit_NeoPixel.h"

#include <array>

class DongleIO {
  static Adafruit_NeoPixel neopix;
 public:
  static void Configure();
  static void setRGB(uint8_t r, uint8_t g, uint8_t b);
  static void setRed(bool on);
  static void setBlue(bool on);
};

#endif
