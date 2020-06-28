#pragma once

#include "sysstuff.h"

// A key action consists of a few things:
// Action when pressed (0 -> 1)
// Action while held (1 -> 1)
// Action when released (1 -> 0)

// Actions:
// press/hold/release a keycode
// layer manipulation
// perform another action

class GeneralAction {
  GeneralAction* nextAction;

 public:
  GeneralAction(GeneralAction* next = nullptr);
  virtual void Execute(state::hw&) = 0;
};

class PressKey : public GeneralAction {
  uint8_t keyCode;

 public:
  PressKey(uint8_t keycode, GeneralAction* next = nullptr);
  virtual void Execute(state::hw&) override;
};

// You can press or release a key
class ReleaseKey : public GeneralAction {
  uint8_t keyCode;

 public:
  ReleaseKey(uint8_t keycode, GeneralAction* next = nullptr);
  virtual void Execute(state::hw&) override;
};

class PushLayer : public GeneralAction {
  uint8_t layer;

 public:
  PushLayer(uint8_t layer, GeneralAction* next = nullptr);
  virtual void Execute(state::hw&) override;
};

class PopLayer : public GeneralAction {
  uint8_t layer;

 public:
  PopLayer(GeneralAction* next = nullptr);
  virtual void Execute(state::hw&) override;
};

// This is for a latching, maybe other stuff?
// class Register : public GeneralAction {};

// A hold action maybe should be a bit different:
// We might want a 'start threshold' and a 'repeat every' option
struct ScanAction {
  GeneralAction* press;
  GeneralAction* release;
};

// And a layer is a set of modifications of *selected* base_key entries
ScanAction keyPress(uint8_t code) {
  return ScanAction{new PressKey(code), new ReleaseKey(code)};
}

ScanAction layerShift(uint8_t l) {
  return ScanAction{new PushLayer(l), new PopLayer()};
}

ScanAction layerChange(uint8_t l) {
  return ScanAction{new PopLayer(new PushLayer(l)), nullptr};
}
