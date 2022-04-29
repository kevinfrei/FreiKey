#include "Adafruit_ST7789.h"
#include <array>
#include <cstring>

#include "board.h"
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
Board *brd = nullptr;

void Initialize() {
  // Don't think I need anything here...
  gameState = GameFlowState::FirstTime;
}

void Begin(Adafruit_ST7789* tft) {
  gameState = GameFlowState::JustStarting;
  // calcDisplayValues();
  if (brd) {
    delete brd;
  }
  brd = new Board(*tft, 5, 5);
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
