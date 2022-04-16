#include "Adafruit_ST7789.h"
#include <array>
#include <cstring>

#include "include/board.h"
#include "tetris.h"
#include "usbenums.h"

namespace tetris {
enum class GameFlowState {
  FirstTime,
  JustStarting,
  NotPlaying,
  InProgress,
  Completed
};

GameFlowState gameState = GameFlowState::FirstTime;
Adafruit_ST7789* dsp = nullptr;

uint8_t xW, xO, yW, yO;
uint8_t xN, yN;

void calcDisplayValues() {
  uint16_t height = dsp->height();
  uint16_t width = dsp->width();
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
      return ST77XX_BLACK;
    case 1:
      return ST77XX_RED;
    case 2:
      return ST77XX_BLUE;
    case 3:
      return ST77XX_GREEN;
    case 4:
      return ST77XX_YELLOW;
    case 5:
      return ST77XX_CYAN;
    case 6:
      return ST77XX_MAGENTA;
    case 7:
      return ST77XX_ORANGE;
    default:
      return blk << 8 | blk;
  }
}

class GameState {
  uint8_t curPiece;
  uint8_t nextPiece;
  uint8_t cx, cy, cr;
  uint32_t score;
  uint32_t level;
  Board board;

 public:
  void reset() {
    level = 0;
    score = 0;
  }
  void drawFullBoard() {
    dsp->fillScreen(ST77XX_BLACK);
    //
  }
};

void Initialize() {
  // Don't think I need anything here...
  gameState = GameFlowState::FirstTime;
}

void Begin(Adafruit_ST7789* tft) {
  gameState = GameFlowState::JustStarting;
  dsp = tft;
  calcDisplayValues();
}

void KeyDown(Keystroke k) {
  switch (gameState) {
    case GameFlowState::FirstTime:
      break;
    case GameFlowState::NotPlaying:
      break;
    case GameFlowState::JustStarting:
      break;
    case GameFlowState::InProgress:
      break;
    case GameFlowState::Completed:
      break;
  }
}

void Tick() {}

} // namespace tetris
