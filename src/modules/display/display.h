#pragma once

#include <cstdint>

class Adafruit_ST7789;
class Adafruit_SPITFT;
namespace disp {

struct rect_t {
  int16_t x, y = 0;
  uint16_t w, h;
};

enum class RelativeAlignment : uint8_t { Start, Middle, End };
enum class TextAlignment : uint8_t {
  LeftTop,
  LeftMiddle,
  LeftBottom,
  CenterTop,
  CenterMiddle,
  CenterBottom,
  RightTop,
  RightMiddle,
  RightBottom
};

Adafruit_ST7789* Init(uint16_t w,
                      uint16_t h,
                      uint8_t mhz,
                      uint8_t rotation,
                      uint8_t TFT_CS,
                      uint8_t TFT_DC,
                      uint8_t TFT_Reset,
                      uint8_t TFT_Backlight,
                      uint8_t SD_CS = 0,
                      uint8_t SPKR = 0);
void SetBacklight(bool turnOn, uint32_t now);
void SetTimeout(uint16_t seconds);
void Tick(uint32_t time);
void DrawKeyboard(uint16_t scancode, uint16_t x, uint16_t y);
void DrawText(const char* loc,
              rect_t& prv,
              TextAlignment align = TextAlignment::CenterMiddle,
              uint8_t padding = 2,
              uint16_t color = 0xFFFF,
              uint16_t bgColor = 0);
Adafruit_SPITFT *raw();

} // namespace disp