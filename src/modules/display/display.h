#pragma once

#include <cstdint>

/*
class Adafruit_ST7789;
class Adafruit_SPITFT;
*/

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

/*Adafruit_ST7789* */
void Init(uint16_t w,
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
void ClearScreen(uint16_t color);
void DrawText(
  const char* str, uint8_t size, uint16_t color, int16_t x, int16_t y);
void FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void FillRoundRect(
  int16_t x, int16_t y, int16_t w, int16_t h, uint16_t r, uint16_t color);
void DrawLine(int16_t sx, int16_t sy, int16_t ex, int16_t ey, uint16_t color);
void GetTextBounds(const char* str,
                   int16_t x,
                   int16_t y,
                   int16_t& xp,
                   int16_t& yp,
                   uint16_t& w,
                   uint16_t& h,
                   uint8_t fontSize = 1);
uint16_t GetWidth();
uint16_t GetHeight();
void Draw16BitBitmap(
  const uint16_t* buffer, int16_t x, int16_t y, uint16_t w, uint16_t h);
// Adafruit_SPITFT* raw();

} // namespace disp