#include "tetris.h"
#include "Adafruit_ST7789.h"
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

uint8_t pieces[7][8] =
  {
    {-1, 0, 1, 0, 0, -1}, // T
    {-1, 0, 1, 0, 0, -1}, // S
    {-1, 0, 1, 0, 0, -1}, // Z
    {-1, 0, 1, 0, 0, -1}, // O
    {-1, 0, 1, 0, 0, -1}, // L
    {-1, 0, 1, 0, 0, -1}, // J
    {-1, 0, 1, 0, 0, -1}, // I
}

struct GameState {
  uint8_t curPiece;
  uint8_t nextPiece;
  uint8_t cx, cy;
  uint32_t score;
  uint32_t level;
  uint8_t board[10 * 24];
};

void Initialize() {
  // Don't think I need anything here...
  gameState = GameFlowState::FirstTime
}

void Begin(Adafruit_ST7789* tft) {
  gamesState = GameFlowState::JustStarting;
  dsp = tft;
}

void KeyDown(Keystroke k) {
  switch (gameState) { case GameFlowState::NotPlaying: }
}

void Tick() {}

} // namespace tetris