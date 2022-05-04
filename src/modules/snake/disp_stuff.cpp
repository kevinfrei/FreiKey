#include <algorithm>
#include <cstdint>

namespace tetris {

uint8_t xW, xO, yW, yO;
uint8_t xN, yN;

void calcDisplayValues(uint16_t height, uint16_t width) {
  yW = (height - 1) / 24;
  xW = (width - 1) / 10;
  yW = std::min(xW, yW);
  xW = yW;
  xO = std::min(10, (width - xW * 10) / 2);
  yO = std::min(10, height - yW * 24);
  // This is only going to work for a landscape oriented display:
  xN = xO * 5 + (xW * 23) / 2;
  yN = (yW * 5) / 2;
}

uint16_t getDispX(uint8_t x) {
  return xO + xW * x;
}

uint16_t getDispY(uint8_t y) {
  return yO + yW * y;
}

uint16_t getDispW() {
  return xW;
}

uint16_t getDispH() {
  return yW;
}

uint16_t getPrevX(uint8_t x) {
  return xN + xW * x;
}

uint16_t getPrevY(uint8_t y) {
  return yN + yW * y;
}

uint16_t getPrevW() {
  return xW * 3;
}

uint16_t getPrevH() {
  return yW * 4;
}

uint16_t getColor(uint8_t blk) {
  switch (blk) {
    case 0:
      return 0x0000; // Black
    case 1:
      return 0xF800; // Red
    case 2:
      return 0x001F; // Blue
    case 3:
      return 0x07E0; // Green
    case 4:
      return 0xFFE0; // Yellow
    case 5:
      return 0x07FF; // Cyan
    case 6:
      return 0xF81F; // Magenta
    case 7:
      return 0xFC00; // Orange
    default:
      return 0xFFFF; // White
  }
}

} // namespace tetris