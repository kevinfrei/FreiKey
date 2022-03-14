#pragma once

#include "bitmap.h"
#include <Adafruit_ST7789.h>

void drawImage(image_descriptor* id,
               uint8_t x,
               uint8_t y,
               Adafruit_ST7789* tft);