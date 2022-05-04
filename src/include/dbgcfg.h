#pragma once
#if !defined __DBGCFG_H_HEADER
#define __DBGCFG_H_HEADER

#if defined(ARDUINO)
#include "Arduino.h"
#else
#include <iostream>
#endif

#include <bitset>
#include <cstdint>

#include "enumtypes.h"
#include "usbenums.h"

// This is just a couple of dumpers that show stuff on the AdaFruit serial port,
// and a couple of macros to do stuff when the system is build with DEBUG=1 (or
// 2). Set the DEBUG flag in the Makefile :)

enum class sfmt : int { endl = 0, dec = 10, hex = 16, bin = 2, oct = 8 };
class SerialStream {
#if defined(DEBUG)
  const bool yup;
  sfmt mode;
#if defined(ARDUINO)
  void printNum(const char* s) {
    Serial.print(s);
  }
  template <typename T>
  void printNum(T s) {
    Serial.print(s, static_cast<int>(mode));
  }
#endif
#endif
 public:
#if defined(DEBUG)
  SerialStream(int dbg) : yup(dbg <= DEBUG), mode(sfmt::endl) {}
#else
  SerialStream(int dbg) {}
#endif
  SerialStream& operator<<(sfmt op) {
#if defined(DEBUG)
    if (!yup)
      return *this;
    if (op == sfmt::endl) {
#if defined(ARDUINO)
      Serial.println();
#else
      std::cerr << std::endl;
#endif
    } else {
      mode = op;
    }
#endif
    return *this;
  }
  template <typename T>
  SerialStream& operator<<(T s) {
#if defined(DEBUG)
    if (!yup)
      return *this;
    if (mode == sfmt::endl) {
#if defined(ARDUINO)
      Serial.print(s);
#else
      std::cerr << s;
#endif
    } else {
#if defined(ARDUINO)
      printNum(s);
#else
      switch (mode) {
        case sfmt::bin:
          std::cerr << std::bitset<sizeof(T)>(s);
          break;
        case sfmt::dec:
          std::cerr << std::dec << s;
          break;
        case sfmt::hex:
          std::cerr << std::hex << s << std::dec;
          break;
        case sfmt::oct:
          std::cerr << std::oct << s << std::dec;
          break;
        default:
          break;
      }
#endif
    }
    mode = sfmt::endl;
#endif
    return *this;
  }
};

extern SerialStream Dbg, Dbg2;

#if defined(DEBUG)
#define DBG(a) a
#endif

#if defined(DEBUG) && DEBUG == 2
#define DBG2(a) a
#else
#define DBG2(a)
#endif

#if !defined(DEBUG)
#define DBG(a)
#define DBG2(a)
#endif
#define DBG3(a)

#if defined(__VSCODE_ONLY_)
// Stuff to make VSCode IntelliSense happy
// Don't seem to need this stuff now, which is helpful
#endif

inline SerialStream& operator<<(SerialStream& o, KeyboardMode km) {
  o << "KeyboardMode::";
  switch (km) {
    case KeyboardMode::Normal:
      return o << "Normal";
    case KeyboardMode::Menu:
      return o << "Menu";
    case KeyboardMode::Calculator:
      return o << "Calculator";
    case KeyboardMode::Tetris:
      return o << "Tetris";
    case KeyboardMode::Snake:
      return o << "Snake";
    case KeyboardMode::MediaBrowse:
      return o << "MediaBrowse";
    case KeyboardMode::Apple2:
      return o << "Apple2";
    case KeyboardMode::Diagnostics:
      return o << "Diagnostics";
    default:
      return o << "INVALID!";
  }
}

inline SerialStream& operator<<(SerialStream& o, layer_num ln) {
  switch (ln) {
    case layer_num::Base:
      return o << "Mac [Base]";
    case layer_num::WinBase:
      return o << "Windows";
    case layer_num::LinBase:
      return o << "Linux";
    case layer_num::Func:
      return o << "Fn";
    case layer_num::MacCap:
      return o << "Mac Cmd";
    case layer_num::WinCap:
      return o << "Win Caps";
    case layer_num::WinCtl:
      return o << "Win Ctrl";
    case layer_num::LinCap:
      return o << "Linux Caps";
    default:
      return o << "Unknown Layer!";
  }
}

inline SerialStream& operator<<(SerialStream& o, KeyAction ka) {
  switch (ka) {
    case KeyAction::KeyPress:
      return o << "Keypress";
    case KeyAction::Modifier:
      return o << "Modifier";
      break;
    case KeyAction::TapHold:
      return o << "TapHold";
      break;
    case KeyAction::Consumer:
      return o << "Consumer";
      break;
    case KeyAction::KeyAndMods:
      return o << "KeyAndMods";
    case KeyAction::LayerShift:
      return o << "LayerShift";
    case KeyAction::LayerToggle:
      return o << "LayerToggle";
    case KeyAction::LayerSwitch:
      return o << "LayerSwitch";
    case KeyAction::Mode:
      return o << "Mode Switch";
    default:
      return o << "Unknown KeyAction:" << sfmt::hex
               << static_cast<uint32_t>(ka);
  }
}
#endif // !defined __DBGCFG_H_HEADER
