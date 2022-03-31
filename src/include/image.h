#pragma once

#include "bitmap.h"
#include <Adafruit_ST7789.h>

void drawImage(const image_descriptor* id,
               uint16_t x,
               uint16_t y,
               Adafruit_ST7789* tft);
void ShowImage(Adafruit_ST7789* tft, const image_descriptor* img);