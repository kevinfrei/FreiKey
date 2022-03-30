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

inline Modifiers operator|(Modifiers a, Modifiers b) {
  return static_cast<Modifiers>(static_cast<uint8_t>(a) |
                                static_cast<uint8_t>(b));
}