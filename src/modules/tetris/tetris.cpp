#include "Adafruit_ST7789.h"
#include <array>
#include <cstring>

#include "board.h"
#include "display.h"
#include "enumtypes.h"
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

enum class Button {
  RotateLeft,
  RotateRight,
  Down,
  Left,
  Right,
  Drop,
  Quit,
  Pause
};

GameFlowState gameState = GameFlowState::FirstTime;
Board* brd = nullptr;

void Initialize() {
  // Don't think I need anything here...
  gameState = GameFlowState::FirstTime;
  // calcDisplayValues();
  if (brd) {
    delete brd;
  }
  brd = new Board(*disp::raw(), 5, 5);
}

void KeyDown(Button k, uint32_t now) {
  switch (gameState) {
    case GameFlowState::FirstTime:
      brd->splash();
      delay(1000);
      gameState = GameFlowState::NotPlaying;
      break;
    case GameFlowState::NotPlaying:
      brd->draw(now);
      gameState = GameFlowState::JustStarting;
      break;
    case GameFlowState::JustStarting:
      brd->start(now);
      gameState = GameFlowState::InProgress;
      break;
    case GameFlowState::InProgress:
      switch (k) {
        case Button::Left:
          brd->left();
          break;
        case Button::Right:
          brd->right();
          break;
        case Button::RotateRight:
          brd->rotCW();
          break;
        case Button::RotateLeft:
          brd->rotCCW();
          break;
        case Button::Down:
          brd->down(now);
          break;
        case Button::Quit:
          gameState = GameFlowState::NotPlaying;
          break;
          // TODO: case Button::Pause:
          // TODO: case Button::Drop:
      }
      break;
    case GameFlowState::Completed:
      gameState = GameFlowState::NotPlaying;
      break;
  }
}

KeyboardMode Handler(Keystroke ks, Modifiers m, bool pressed, uint32_t now) {
  if (!pressed) {
    return KeyboardMode::Tetris;
  }
  if (ks != Keystroke::None) {
    switch (ks) {
      case Keystroke::Up:
      case Keystroke::W:
      case Keystroke::PageUp:
      case Keystroke::I:
      case Keystroke::U:
      case Keystroke::Q:
        KeyDown(Button::RotateLeft, now);
        break;
      case Keystroke::E:
      case Keystroke::O:
        KeyDown(Button::RotateRight, now);
        break;
      case Keystroke::Down:
      case Keystroke::S:
      case Keystroke::PageDown:
      case Keystroke::K:
        KeyDown(Button::Down, now);
        break;
      case Keystroke::Left:
      case Keystroke::A:
      case Keystroke::Home:
      case Keystroke::J:
        KeyDown(Button::Left, now);
        break;
      case Keystroke::Right:
      case Keystroke::D:
      case Keystroke::End:
      case Keystroke::L:
        KeyDown(Button::Right, now);
        break;
      case Keystroke::Enter:
      case Keystroke::Space:
        KeyDown(Button::Drop, now);
        break;
      case Keystroke::Esc:
        KeyDown(Button::Quit, now);
        return KeyboardMode::Normal;
      default:
        break;
    }
  } else if (m != Modifiers::None) {
    KeyDown(Button::Pause, now);
  }
  return KeyboardMode::Tetris;
}

KeyboardMode Spin(KeyboardMode curMode, uint32_t now) {
  brd->draw(now);
  return curMode;
}

} // namespace tetris
