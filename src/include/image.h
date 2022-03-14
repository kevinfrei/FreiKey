#pragma once

#include "bitmap.h"
#include <Adafruit_ST7789.h>

void drawImage(const image_descriptor* id,
               uint8_t x,
               uint8_t y,
               Adafruit_ST7789* tft);
