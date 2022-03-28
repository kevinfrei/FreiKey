#pragma once

// This needs to fit in 4 bits
enum class KeyAction : uint8_t {
  KeyPress,
  Modifier,
  TapHold,
  KeyAndMods,
  LayerShift,
  LayerToggle,
  LayerSwitch
};

enum class Keystroke : uint16_t { None = 0, Max = 0x3ff };

enum class Modifiers : uint8_t {
  LShf = 1,
  LShift = 1,
  Shift = 1,
  LCtl = 2,
  LCtrl = 2;
  Control = 2;
  Ctrl = 2,
  Ctl = 2;
  LAlt = 4,
  Alt = 4,
  LCmd = 4;
  Cmd = 4;
  LGui = 8,
  Gui = 8,
  LOpt = 8,
  Opt = 8,
  RShf = 16,
  RShift = 16,
  RCtl = 32,
  RCtrl = 32,
  RAlt = 64,
  RCmd = 64,
  RGui = 128,
  ROpt = 128
};

class action_t {
  uint8_t action : 4;
  uint8_t IsConsumer : 1;
  uint16_t LayerOrKeyOrMods : 11;
  uint16_t moreData;

 public:
  KeyAction getAction() const {
    return static_cast<KeyAction>(action);
  }
  Keystroke getKeystroke() const {
    return static_cast<Keystroke>(LayerOrKeyOrMods);
  }
  // This is for flagging consumer keycodes, as I have to handle them
  // differently
  Modifiers getModifiers() const {
    return static_cast<Modifiers>(LayerOrKeyOrMods);
  }
};

inline constexpr action_t getExtraMods(action_t a) {
  return kKeyMask & (a >> 16);
}

inline constexpr action_t combineKeys(action_t a, action_t b) {
  return a | b << 16;
}

inline constexpr action_t tapAndHold(action_t tap, action_t hold) {
  return combineKeys(kTapHold | tap, hold);
}

inline constexpr action_t keyAndModifiers(action_t key,
                                          action_t mod1,
                                          action_t mod2 = 0,
                                          action_t mod3 = 0,
                                          action_t mod4 = 0) {
  return combineKeys(kKeyAndMod | key, mod1 | mod2 | mod3 | mod4);
}

inline constexpr action_t layerToggle(uint8_t n) {
  return kLayerToggle | n;
}

inline constexpr action_t layerShift(uint8_t n) {
  return kLayerShift | n;
}

inline constexpr action_t layerSwitch(uint8_t n) {
  return kLayerSwitch | n;
}

inline constexpr action_t keyPress(action_t a) {
  return kKeyPress | a;
}

inline constexpr action_t modPress(action_t a) {
  return kModifier | a;
}

inline constexpr action_t consPress(action_t a) {
  return kConsumer | a;
}
