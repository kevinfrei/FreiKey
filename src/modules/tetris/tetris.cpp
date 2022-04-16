#include "Adafruit_ST7789.h"
#include <array>
#include <cstring>

#include "include/board.h"
#include "include/tetris_details.h"
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
