#pragma once
#if !defined(TETRIS_DETAILS_H)
#define TETRIS_DETAILS_H

#include <cstdint>

namespace tetris {
extern class Adafruit_ST7789 *dsp;
void calcDisplayValues();
uint16_t getDispX(uint8_t x);
uint16_t getDispY(uint8_t y);
uint16_t getDispW();
uint16_t getDispH();
uint16_t getPrevX(uint8_t x);
uint16_t getPrevY(uint8_t y);
uint16_t getPrevW();
uint16_t getPrevH();
uint16_t getColor(uint8_t blk);
} // namespace tetris

#endif