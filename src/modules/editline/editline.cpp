#if defined(STANDALONE)
#include <cstring>
#include <iostream>
#define DBG(a)
#else
#include "dbgcfg.h"
#include <Arduino.h>

#endif

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <map>

#include "editline.h"
#include "usbenums.h"

namespace edit {

/*
struct KeyPress {
  Modifiers m;
  Keystroke k;
  const KeyPress* nxt;
  constexpr KeyPress(Modifiers mod,
                     Keystroke key,
                     const KeyPress* next = nullptr)
    : m(mod), k(key), nxt(next) {}
  constexpr KeyPress(Keystroke key)
    : m(Modifiers::None), k(key), nxt(nullptr) {}
  constexpr KeyPress() : m(Modifiers::None), k(Keystroke::None), nxt(nullptr) {}
};

constexpr KeyPress alternates[] = {
  {Keystroke::Home}, // 0
  {Keystroke::Up}, // 1
  {Keystroke::Down}, // 2
  {Keystroke::Left}, // 3
  {Keystroke::Right}, // 4
  {Keystroke::End}, // 5
  {Keystroke::PgUp}, // 6
  {Keystroke::PgDn}, // 7
  {Keystroke::Backspace}, // 8
  {Keystroke::Delete}, // 9
  {Keystroke::Enter}, // 10
  {Keystroke::Tab} // 11
};

constexpr KeyPress charToKey[] = {
  {},
  {Modifiers::Ctl, Keystroke::A, &alternates[0]}, // Home
  {Modifiers::Ctl, Keystroke::B, &alternates[3]}, // Left
  {Modifiers::Ctl, Keystroke::C},
  {Modifiers::Ctl, Keystroke::D, &alternates[9]}, // Delete
  {Modifiers::Ctl, Keystroke::E, &alternates[5]}, // End
  {Modifiers::Ctl, Keystroke::F, &alternates[4]}, // Right
  {Modifiers::Ctl, Keystroke::G},
  {Modifiers::Ctl, Keystroke::H, &alternates[8]}, // Backspace
  {Modifiers::Ctl, Keystroke::I, &alternates[11]}, // Tab
  {Modifiers::Ctl, Keystroke::J, &alternates[2]}, // Down
  {Modifiers::Ctl, Keystroke::K, &alternates[1]}, // Up
  {Modifiers::Ctl, Keystroke::L},
  {Modifiers::Ctl, Keystroke::M, &alternates[10]}, // Enter
  {Modifiers::Ctl, Keystroke::N, &alternates[7]}, // PgDn
  {Modifiers::Ctl, Keystroke::O},
  {Modifiers::Ctl, Keystroke::P, &alternates[6]}, // PgUp
  {Modifiers::Ctl, Keystroke::Q},
  {Modifiers::Ctl, Keystroke::R},
  {Modifiers::Ctl, Keystroke::S},
  {Modifiers::Ctl, Keystroke::T},
  {Modifiers::Ctl, Keystroke::U},
  {Modifiers::Ctl, Keystroke::V},
  {Modifiers::Ctl, Keystroke::W},
  {Modifiers::Ctl, Keystroke::X},
  {Modifiers::Ctl, Keystroke::Y},
  {Modifiers::Ctl, Keystroke::Z},
  {Keystroke::Escape},
  {},
  {},
  {},
  {},

  {Keystroke::Space},
  {Modifiers::Shift, Keystroke::_1}, // !
  {Modifiers::Shift, Keystroke::Quote}, // "
  {Modifiers::Shift, Keystroke::_3}, // #
  {Modifiers::Shift, Keystroke::_4}, // $
  {Modifiers::Shift, Keystroke::_5}, // %
  {Modifiers::Shift, Keystroke::_7}, // &
  {Keystroke::Quote},
  {Modifiers::Shift, Keystroke::_9}, // (
  {Modifiers::Shift, Keystroke::_0}, // )
  {Modifiers::Shift, Keystroke::Equal}, // +
  {Keystroke::Comma},
  {Keystroke::Minus},
  {Keystroke::Period},
  {Keystroke::Slash},
  {Keystroke::_0},
  {Keystroke::_1},
  {Keystroke::_2},
  {Keystroke::_3},
  {Keystroke::_4},
  {Keystroke::_5},
  {Keystroke::_6},
  {Keystroke::_7},
  {Keystroke::_8},
  {Keystroke::_9},
  {Modifiers::Shift, Keystroke::Semicolon}, // :
  {Keystroke::Semicolon},
  {Modifiers::Shift, Keystroke::Comma}, // <
  {Keystroke::Equal},
  {Modifiers::Shift, Keystroke::Period}, // >
  {Modifiers::Shift, Keystroke::Slash}, // ?

  {Modifiers::Shift, Keystroke::_2}, // @
  {Modifiers::Shift, Keystroke::A},
  {Modifiers::Shift, Keystroke::B},
  {Modifiers::Shift, Keystroke::C},
  {Modifiers::Shift, Keystroke::D},
  {Modifiers::Shift, Keystroke::E},
  {Modifiers::Shift, Keystroke::F},
  {Modifiers::Shift, Keystroke::G},
  {Modifiers::Shift, Keystroke::H},
  {Modifiers::Shift, Keystroke::I},
  {Modifiers::Shift, Keystroke::J},
  {Modifiers::Shift, Keystroke::K},
  {Modifiers::Shift, Keystroke::L},
  {Modifiers::Shift, Keystroke::M},
  {Modifiers::Shift, Keystroke::N},
  {Modifiers::Shift, Keystroke::O},
  {Modifiers::Shift, Keystroke::P},
  {Modifiers::Shift, Keystroke::Q},
  {Modifiers::Shift, Keystroke::R},
  {Modifiers::Shift, Keystroke::S},
  {Modifiers::Shift, Keystroke::T},
  {Modifiers::Shift, Keystroke::U},
  {Modifiers::Shift, Keystroke::V},
  {Modifiers::Shift, Keystroke::W},
  {Modifiers::Shift, Keystroke::X},
  {Modifiers::Shift, Keystroke::Y},
  {Modifiers::Shift, Keystroke::Z},
  {Keystroke::OpenBracket},
  {Keystroke::Backslash},
  {Keystroke::CloseBracket},
  {Modifiers::Shift, Keystroke::_6}, // ^
  {Modifiers::Shift, Keystroke::Minus}, // _

  {Keystroke::Grave}, // @
  {Keystroke::A},
  {Keystroke::B},
  {Keystroke::C},
  {Keystroke::D},
  {Keystroke::E},
  {Keystroke::F},
  {Keystroke::G},
  {Keystroke::H},
  {Keystroke::I},
  {Keystroke::J},
  {Keystroke::K},
  {Keystroke::L},
  {Keystroke::M},
  {Keystroke::N},
  {Keystroke::O},
  {Keystroke::P},
  {Keystroke::Q},
  {Keystroke::R},
  {Keystroke::S},
  {Keystroke::T},
  {Keystroke::U},
  {Keystroke::V},
  {Keystroke::W},
  {Keystroke::X},
  {Keystroke::Y},
  {Keystroke::Z},
  {Modifiers::Shift, Keystroke::OpenBracket}, // {
  {Modifiers::Shift, Keystroke::Backslash}, // |
  {Modifiers::Shift, Keystroke::CloseBracket}, // }
  {Modifiers::Shift, Keystroke::Grave}, // ~
  {Keystroke::Del}};
*/

const std::map<Keystroke, std::array<char, 3>> strokeToChar = {
  {Keystroke::A, {'a', 'A', 1}},
  {Keystroke::B, {'b', 'B', 2}},
  {Keystroke::C, {'c', 'C', 3}},
  {Keystroke::D, {'d', 'D', 4}},
  {Keystroke::E, {'e', 'E', 5}},
  {Keystroke::F, {'f', 'F', 6}},
  {Keystroke::G, {'g', 'G', 7}},
  {Keystroke::H, {'h', 'H', 8}},
  {Keystroke::I, {'i', 'I', 9}},
  {Keystroke::J, {'j', 'J', 10}},
  {Keystroke::K, {'k', 'K', 11}},
  {Keystroke::L, {'l', 'L', 12}},
  {Keystroke::M, {'m', 'M', 13}},
  {Keystroke::N, {'n', 'N', 14}},
  {Keystroke::O, {'o', 'O', 15}},
  {Keystroke::P, {'p', 'P', 16}},
  {Keystroke::Q, {'q', 'Q', 17}},
  {Keystroke::R, {'r', 'R', 18}},
  {Keystroke::S, {'s', 'S', 19}},
  {Keystroke::T, {'t', 'T', 20}},
  {Keystroke::U, {'u', 'U', 21}},
  {Keystroke::V, {'v', 'V', 22}},
  {Keystroke::W, {'w', 'W', 23}},
  {Keystroke::X, {'x', 'X', 24}},
  {Keystroke::Y, {'y', 'Y', 25}},
  {Keystroke::Z, {'z', 'Z', 26}},
  {Keystroke::Esc, {27, 27, 27}},
  {Keystroke::_0, {'0', ')', 0}},
  {Keystroke::_1, {'1', '!', 0}},
  {Keystroke::_2, {'2', '@', 0}},
  {Keystroke::_3, {'3', '#', 0}},
  {Keystroke::_4, {'4', '$', 0}},
  {Keystroke::_5, {'5', '%', 0}},
  {Keystroke::_6, {'6', '^', 0}},
  {Keystroke::_7, {'7', '&', 0}},
  {Keystroke::_8, {'8', '*', 0}},
  {Keystroke::_9, {'9', '(', 0}},
  {Keystroke::Enter, {13, 0, 0}},
  {Keystroke::Backspace, {8, 0, 0}},
  {Keystroke::Tab, {9, 0, 0}},
  {Keystroke::Space, {' ', 0, 0}},
  {Keystroke::Minus, {'-', '_', 0}},
  {Keystroke::Equal, {'=', '+', 0}},
  {Keystroke::OpenBrace, {'[', '{', 0}},
  {Keystroke::CloseBrace, {']', '}', 0}},
  {Keystroke::Backslash, {'\\', '|', 0}},
  {Keystroke::Semicolon, {';', ':', 0}},
  {Keystroke::Quote, {'\'', '\"', 0}},
  {Keystroke::Grave, {'`', '~', 0}},
  {Keystroke::Comma, {',', '<', 0}},
  {Keystroke::Period, {'.', '>', 0}},
  {Keystroke::Slash, {'/', '?', 0}},
  {Keystroke::Home, {1, 0, 0}}, // ctrl-a
  {Keystroke::Up, {10, 0, 0}}, // ctrl-j
  {Keystroke::Down, {12, 0, 0}}, // ctrl-l
  {Keystroke::Left, {2, 0, 0}}, // ctrl-b
  {Keystroke::Right, {6, 0, 0}}, // ctrl-f
  {Keystroke::End, {5, 0, 0}}, // ctrl-e
  {Keystroke::PgUp, {16, 0, 0}}, // ctrl-p
  {Keystroke::PgDn, {14, 0, 0}}, // ctrl-n
  {Keystroke::Delete, {4, 0, 0}}, // ctrl-d
  {Keystroke::Enter, {13, 0, 0}}, // ctrl-m
  {Keystroke::Tab, {9, 0, 0}} // ctrl-i
};

// For a keyboard line editor, 128 bytes, yeah?
char buffer[128];
uint8_t bufLen = 0;
editline curLine;

void Initialize() {
  buffer[0] = 0;
  curLine.buf = &buffer[0];
  curLine.pos = 0;
  bufLen = 1;
}

char getChar(Keystroke k, Modifiers m) {
  bool alt = (m && Modifiers::RAlt) || (m && Modifiers::LAlt);
  bool ctl = (m && Modifiers::RCtl) || (m && Modifiers::LCtl);
  bool gui = (m && Modifiers::RGui) || (m && Modifiers::LGui);
  bool shf = (m && Modifiers::RShf) || (m && Modifiers::LShf);
  if (alt || gui) {
    // For now, don't report anything back...
    return 0;
  }
  const auto& iter = strokeToChar.find(k);
  if (iter != strokeToChar.end()) {
    int index = ctl ? 2 : !!shf;
    return iter->second[index];
  }
  return 0;
}

void setline(const char* buf, int16_t pos) {
  for (bufLen = 0; buf[bufLen]; bufLen++) {
    if (bufLen > 126)
      break;
  }
  bufLen++;
  memcpy(buffer, buf, bufLen);
  curLine.pos = (pos < 0 ? (bufLen - 1) : pos);
}

const editline& readline(Keystroke k, Modifiers m, bool pressed, uint32_t now) {
  // This should basically handle all the keyboard malarkey:
  // General text input first (with shift) from a base keymap
  // Arrows to navigate within the line, plus unix stuff:
  // ctl-a-e-f-b-h-d-t
  // Next add support for ctl-k/y for copy/paste
  // Maybe enable some sort of tab-to-autocomplete interface,
  // and eventually, add support for history navigation?
  if (k == Keystroke::None) {
    return curLine;
  }
  if (!pressed) {
    return curLine;
  }
  char c = getChar(k, m);
  // TODO: Handle ctrl chars && the like, inserting, generally doing stuff

  if (c >= ' ' && c < 127) {
    // We're inserting a character at the current position
    // and moving the current position forward one character
    if (bufLen == 127) {
      return curLine;
    }
    std::memmove(
      &buffer[curLine.pos + 1], &buffer[curLine.pos], bufLen - curLine.pos + 1);
    buffer[curLine.pos++] = c;
    bufLen++;
  } else {
    switch (c) {
      case 1:
        // Home/Ctrl-a
        curLine.pos = 0;
        break;
      case 2:
        // Left/Ctrl-b
        curLine.pos = (curLine.pos > 0) ? (curLine.pos - 1) : 0;
        break;
      case 4:
        // Del/Ctrl-d
        if (bufLen > 0 && curLine.pos < bufLen - 1) {
          std::memmove(&buffer[curLine.pos],
                       &buffer[curLine.pos + 1],
                       bufLen - curLine.pos);
          bufLen--;
        }
        break;
      case 5:
        // End/Ctrl-e
        curLine.pos = bufLen - 1;
        break;
      case 6:
        // Right/Ctrl-f
        if (curLine.pos < bufLen - 1) {
          curLine.pos++;
        }
        break;
      case 8:
        // Backspace/Ctrl-h
        if (curLine.pos > 0) {
          std::memmove(&buffer[curLine.pos - 1],
                       &buffer[curLine.pos],
                       bufLen - curLine.pos);
          bufLen--;
          curLine.pos--;
        }
        break;
      case 20:
        // Ctrl-t: Transpose!
        if (curLine.pos < bufLen - 1) {
          char cur = buffer[curLine.pos];
          buffer[curLine.pos] = buffer[curLine.pos - 1];
          buffer[curLine.pos - 1] = cur;
          curLine.pos++;
        }
        break;
      default:
        break;
    }
  }
  return curLine;
}

} // namespace edit

#if defined(STANDALONE)

std::ostream& operator<<(std::ostream& o, const edit::editline& ln) {
  o << "'" << ln.buf << "'@" << static_cast<uint32_t>(ln.pos);
  return o;
}

uint32_t count = 0;
void check(Keystroke ks, Modifiers md, const char* str, uint8_t pos) {
  const auto& ln = edit::readline(ks, md, true, count++);
  if (std::strcmp(ln.buf, str) || ln.pos != pos) {
    std::cout << "Expected '" << str << "'@" << static_cast<uint32_t>(pos)
              << " but got " << ln << " at time " << count << std::endl;
  }
}

int main(int argc, const char* argv[]) {
  edit::Initialize();
  check(Keystroke::Space, Modifiers::None, " ", 1); // 1
  check(Keystroke::A, Modifiers::None, " a", 2); // 2
  check(Keystroke::A, Modifiers::Shift, " aA", 3); // 3
  check(Keystroke::A, Modifiers::Ctrl, " aA", 0); // 4
  check(Keystroke::B, Modifiers::None, "b aA", 1); // 5
  check(Keystroke::D, Modifiers::Ctrl, "baA", 1); // 6
  check(Keystroke::T, Modifiers::Ctrl, "abA", 2); // 7
  check(Keystroke::T, Modifiers::Ctrl, "aAb", 3); // 8
  check(Keystroke::A, Modifiers::Ctrl, "aAb", 0); // 9
  check(Keystroke::E, Modifiers::Ctrl, "aAb", 3); // 10
  check(Keystroke::B, Modifiers::Ctrl, "aAb", 2); // 11
  check(Keystroke::C, Modifiers::None, "aAcb", 3); // 12
  check(Keystroke::H, Modifiers::Ctrl, "aAb", 2); // 13
  check(Keystroke::F, Modifiers::Ctrl, "aAb", 3); // 14
  // Now, normal keys instead of ctrl-modifiers:
  check(Keystroke::Home, Modifiers::None, "aAb", 0); // 15
  check(Keystroke::End, Modifiers::None, "aAb", 3); // 16
  check(Keystroke::Left, Modifiers::None, "aAb", 2); // 17
  check(Keystroke::Backspace, Modifiers::None, "ab", 1); // 18
  check(Keystroke::Right, Modifiers::None, "ab", 2); // 19
  check(Keystroke::Home, Modifiers::None, "ab", 0); // 20
  check(Keystroke::Delete, Modifiers::None, "b", 0); // 21
  check(Keystroke::Delete, Modifiers::None, "", 0); // 22
  // I should test out all the things, right?
  check(Keystroke::_1, Modifiers::None, "1", 1);
  check(Keystroke::_1, Modifiers::Shift, "1!", 2);
  check(Keystroke::_2, Modifiers::None, "1!2", 3);
  check(Keystroke::_2, Modifiers::Shift, "1!2@", 4);
  check(Keystroke::_3, Modifiers::None, "1!2@3", 5);
  check(Keystroke::_3, Modifiers::Shift, "1!2@3#", 6);
  check(Keystroke::_4, Modifiers::None, "1!2@3#4", 7);
  check(Keystroke::_4, Modifiers::Shift, "1!2@3#4$", 8);
  check(Keystroke::_5, Modifiers::None, "1!2@3#4$5", 9);
  check(Keystroke::_5, Modifiers::Shift, "1!2@3#4$5%", 10);
  check(Keystroke::_6, Modifiers::None, "1!2@3#4$5%6", 11);
  check(Keystroke::_6, Modifiers::Shift, "1!2@3#4$5%6^", 12);
  check(Keystroke::_7, Modifiers::None, "1!2@3#4$5%6^7", 13);
  check(Keystroke::_7, Modifiers::Shift, "1!2@3#4$5%6^7&", 14);
  check(Keystroke::_8, Modifiers::None, "1!2@3#4$5%6^7&8", 15);
  check(Keystroke::_8, Modifiers::Shift, "1!2@3#4$5%6^7&8*", 16);
  check(Keystroke::_9, Modifiers::None, "1!2@3#4$5%6^7&8*9", 17);
  check(Keystroke::_9, Modifiers::Shift, "1!2@3#4$5%6^7&8*9(", 18);
  check(Keystroke::_0, Modifiers::None, "1!2@3#4$5%6^7&8*9(0", 19);
  check(Keystroke::_0, Modifiers::Shift, "1!2@3#4$5%6^7&8*9(0)", 20);
  std::cout << "Testing complete" << std::endl;
  return 0;
}
#endif