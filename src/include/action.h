#pragma once

#include "layers.h"

// This needs to fit in 4 bits
enum class KeyAction : uint8_t {
  KeyPress,
  Modifier,
  TapHold,
  Consumer,
  KeyAndMods,
  LayerShift,
  LayerToggle,
  LayerSwitch
};

enum class Keystroke : uint8_t {
  None = 0,
  A = 4,
  B = 5,
  C = 6,
  D = 7,
  E = 8,
  F = 9,
  G = 10,
  H = 11,
  I = 12,
  J = 13,
  K = 14,
  L = 15,
  M = 16,
  N = 17,
  O = 18,
  P = 19,
  Q = 20,
  R = 21,
  S = 22,
  T = 23,
  U = 24,
  V = 25,
  W = 26,
  X = 27,
  Y = 28,
  Z = 29,
  _1 = 30,
  _2 = 31,
  _3 = 32,
  _4 = 33,
  _5 = 34,
  _6 = 35,
  _7 = 36,
  _8 = 37,
  _9 = 38,
  _0 = 39,
  Enter = 40,
  Return = 40,
  Esc = 41,
  Escape = 41,
  Backspace = 42,
  Tab = 43,
  Space = 44,
  Minus = 45,
  Equal = 46,
  LeftBrace = 47,
  OpenBrace = 47,
  LeftBracket = 47,
  OpenBrackey = 47,
  BraceLeft = 47,
  BraceOpen = 47,
  BracketLeft = 47,
  BracketOpen = 47,
  RightBrace = 48,
  CloseBrace = 48,
  RightBracket = 48,
  CloseBracket = 48,
  BraceRight = 48,
  BraceClose = 48,
  BracketRight = 48,
  BracketClose = 48,
  Backslash = 49,
  NonUsNum = 50,
  Semicolon = 51,
  Quote = 52,
  Apostrophe = 52,
  Tilde = 53,
  Grave = 53,
  Comma = 54,
  Period = 55,
  Dot = 55,
  Slash = 56,
  CapsLock = 57,
  F1 = 58,
  F2 = 59,
  F3 = 60,
  F4 = 61,
  F5 = 62,
  F6 = 63,
  F7 = 64,
  F8 = 65,
  F9 = 66,
  F10 = 67,
  F11 = 68,
  F12 = 69,
  PrintScreen = 70,
  ScrollLock = 71,
  Pause = 72,
  Insert = 73,
  Home = 74,
  PageUp = 75,
  PgUp = 75,
  Delete = 76,
  Del = 76,
  End = 77,
  PageDown = 78,
  PgDn = 78,
  Right = 79,
  Left = 80,
  Down = 81,
  Up = 82,
  NunLock = 83,
  Pad_Slash = 84,
  Pad_Asterix = 85,
  Pad_Minux = 86,
  Pad_Plus = 87,
  Pad_Enter = 88,
  Pad_Return = 88,
  Pad_1 = 89,
  Pad_2 = 90,
  Pad_3 = 91,
  Pad_4 = 92,
  Pad_5 = 93,
  Pad_6 = 94,
  Pad_7 = 95,
  Pad_8 = 96,
  Pad_9 = 97,
  Pad_0 = 98,
  Pad_Period = 99,
  Pad_Dot = 99,
  Pad_Decimal = 99,
  NonUsBackspace3 = 100,
  Menu = 101,
  Application = 101,
  Power = 102,
  Pad_Equal = 103,
  F13 = 104,
  F14 = 105,
  F15 = 106,
  F16 = 107,
  F17 = 108,
  F18 = 109,
  F19 = 110,
  F20 = 111,
  F21 = 112,
  F22 = 113,
  F23 = 114,
  F24 = 115,
};

inline uint8_t getUSBCode(Keystroke k) {
  // I think this is correct :)
  return static_cast<uint8_t>(k);
}

enum class Consumer : uint16_t {
  PlayPause = 0xCD,
  NextTrack = 0xB5,
  PrevTrack = 0xB6,
  Stop = 0xB7,
  VolumeUp = 0xE9,
  VolumeDown = 0xEA,
  Mute = 0xE2,
  BrowserBack = 0x224,
  BrowserForward = 0x225,
  Sleep = 0x82
};

inline uint16_t getConsumerCode(Consumer a) {
  return static_cast<uint16_t>(a);
}

enum class Modifiers : uint8_t {
  None = 0,
  LShf = 1,
  LShft = 1,
  LShift = 1,
  Shift = 1,
  LCtl = 2,
  LCtrl = 2,
  LControl = 2,
  Control = 2,
  Ctrl = 2,
  Ctl = 2,
  LAlt = 4,
  Alt = 4,
  LCmd = 4,
  LCommand = 4,
  Cmd = 4,
  Command = 4,
  LGui = 8,
  Gui = 8,
  LOpt = 8,
  LOption = 8,
  Opt = 8,
  Option = 8,
  RShf = 16,
  RShft = 16,
  RShift = 16,
  RCtl = 32,
  RCtrl = 32,
  RControl = 32,
  RAlt = 64,
  RCmd = 64,
  RCommand = 64,
  RGui = 128,
  ROpt = 128,
  ROption = 128
};

class action_t {
  // 4 bits of action, 1 bit 'is consumer', 11 bits of 'data'
  uint16_t data;
  /*
  uint8_t action : 4;
  uint16_t LayerOrKeyOrMods : 11;
  */
  uint16_t moreData;

  void setKeyAction(KeyAction ka) {
    data = static_cast<uint16_t>(ka) << 12 | (data & 0xFFF);
  }
  void setLayer(uint8_t layerNum) {
    data = (data & 0xF000) | layerNum;
  }
  void setMods(Modifiers mods) {
    data = (data & 0xFF00) | static_cast<uint8_t>(mods);
  }
  void setKeyPress(uint16_t keycode) {
    // TODO: Should I try to detect consumer code here?
    data = (data & 0xF800) | (keycode & 0x7ff);
  }

  constexpr action_t(KeyAction kp, uint16_t otherData)
    : data(otherData), moreData(0) {
    setKeyAction(KeyAction::KeyPress);
  }

  constexpr action_t() : data(0), moreData(0) {}
  // combine keys
  constexpr action_t(action_t a, action_t b) : data(a.data), moreData(b.data) {}
  constexpr action_t(uint16_t d, uint16_t m) : data(d), moreData(m) {}

 public:
  constexpr action_t(Modifiers mods)
    : data(static_cast<uint16_t>(mods)), moreData(0) {
    setKeyAction(KeyAction::Modifier);
  }
  static constexpr action_t Keypress(uint16_t keyPress) {
    return action_t{KeyAction::KeyPress, keyPress};
  }
  static constexpr action_t Keypress(Keystroke keyPress) {
    return action_t{KeyAction::KeyPress, static_cast<uint16_t>(keyPress)};
  }
  static constexpr action_t Keypress(action_t keyPress) {
    return action_t{KeyAction::KeyPress, keyPress.data};
  }
  static constexpr action_t Modifier(Modifiers mod1,
                                     Modifiers mod2 = Modifiers::None,
                                     Modifiers mod3 = Modifiers::None,
                                     Modifiers mod4 = Modifiers::None) {
    return action_t{static_cast<Modifiers>(
      static_cast<uint8_t>(mod1) | static_cast<uint8_t>(mod2) |
      static_cast<uint8_t>(mod3) | static_cast<uint8_t>(mod4))};
  }
  static constexpr action_t Modifier(action_t mods) {
    return action_t{static_cast<Modifiers>(mods.data & 0xFF)};
  }
  static constexpr action_t Modifier(Modifiers mods) {
    return action_t{mods};
  }
  static constexpr action_t ConsumerPress(Consumer keyPress) {
    return action_t{KeyAction::Consumer, static_cast<uint16_t>(keyPress)};
  }
  static constexpr action_t Layer(KeyAction ka, uint8_t layerNum = 0) {
    return action_t{ka, static_cast<uint16_t>(layerNum)};
  }
  static constexpr action_t Combine(action_t a, action_t b) {
    return action_t{a, b};
  }
  static constexpr action_t NoAction() {
    return action_t{};
  }
  static constexpr action_t TapAndHold(action_t tap, action_t hold) {
    return action_t{action_t{KeyAction::TapHold, tap.data}, hold};
  }
  static constexpr action_t KeyAndMods(Keystroke key,
                                       Modifiers mod1,
                                       Modifiers mod2 = Modifiers::None,
                                       Modifiers mod3 = Modifiers::None,
                                       Modifiers mod4 = Modifiers::None) {
    return action_t{action_t{KeyAction::KeyAndMods, static_cast<uint16_t>(key)},
                    action_t::Modifier(mod1, mod2, mod3, mod4)};
  }
  static constexpr action_t KeyAndMods(action_t key,
                                       Modifiers mod1,
                                       Modifiers mod2 = Modifiers::None,
                                       Modifiers mod3 = Modifiers::None,
                                       Modifiers mod4 = Modifiers::None) {
    return action_t{action_t{KeyAction::KeyAndMods, key.data},
                    action_t::Modifier(mod1, mod2, mod3, mod4)};
  }
  bool isNoAction() const {
    return data == 0 && moreData == 0;
  }

  KeyAction getAction() const {
    return static_cast<KeyAction>(data >> 12);
  }
  Keystroke getKeystroke() const {
    return static_cast<Keystroke>(data & 0xff);
  } 
  Consumer getConsumer() const {
    return static_cast<Consumer>(data & 0xfff);
  }
  // This is for flagging consumer keycodes, as I have to handle them
  // differently
  Modifiers getModifiers() const {
    return static_cast<Modifiers>(data & 0xFF);
  }
  Modifiers getExtraMods() const {
    return static_cast<Modifiers>(moreData & 0xFF);
  }
  layer_num getLayer() const {
    return static_cast<layer_num>(data & 0xF);
  }
};

static constexpr action_t no_action = action_t::NoAction();

inline constexpr action_t keyPress(Keystroke ks) {
  return action_t::Keypress(ks);
}

inline constexpr action_t layerToggle(uint8_t n) {
  return action_t::Layer(KeyAction::LayerToggle, n);
}

inline constexpr action_t layerShift(uint8_t n) {
  return action_t::Layer(KeyAction::LayerShift, n);
}

inline constexpr action_t layerSwitch(uint8_t n) {
  return action_t::Layer(KeyAction::LayerSwitch, n);
}

inline constexpr action_t keyPress(action_t a) {
  return action_t::Keypress(a);
}

inline constexpr action_t modPress(action_t a) {
  return action_t::Modifier(a);
}
inline constexpr action_t modPress(Modifiers mod1,
                                   Modifiers mod2 = Modifiers::None,
                                   Modifiers mod3 = Modifiers::None,
                                   Modifiers mod4 = Modifiers::None) {
  return action_t::Modifier(mod1, mod2, mod3, mod4);
}

inline constexpr action_t consPress(Consumer a) {
  return action_t::ConsumerPress(a);
}

inline constexpr action_t keyAndModifiers(Keystroke key,
                                          Modifiers mod1,
                                          Modifiers mod2 = Modifiers::None,
                                          Modifiers mod3 = Modifiers::None,
                                          Modifiers mod4 = Modifiers::None) {
  return action_t::KeyAndMods(key, mod1, mod2, mod3, mod4);
}
inline constexpr action_t keyAndModifiers(action_t key,
                                          Modifiers mod1,
                                          Modifiers mod2 = Modifiers::None,
                                          Modifiers mod3 = Modifiers::None,
                                          Modifiers mod4 = Modifiers::None) {
  return action_t::KeyAndMods(key, mod1, mod2, mod3, mod4);
}