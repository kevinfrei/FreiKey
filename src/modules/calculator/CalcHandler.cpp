#include "Calculator.h"
#include "display.h"
#include "editline.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "keymap.h"
#include "modulekeyboard.h"
#include "scanning.h"

namespace calc {

disp::rect_t lastPos = {0, 0, 0, 0};

void DrawText(const edit::editline& ln) {
  // Add the 'cursor'
  char loc[129];
  int after = 0;
  size_t s;
  DBG(Serial.println("Buffer:"));
  DBG(Serial.println(ln.buf));
  for (s = 0; ln.buf[s]; s++) {
    if (after == 0 && ln.pos == s) {
      loc[s] = '|';
      after = 1;
    }
    loc[s + after] = ln.buf[s];
  }
  if (!after) {
    loc[s] = '|';
    after++;
  }
  loc[s + after] = 0;
  disp::DrawText(&loc[0], lastPos);
}

KeyboardMode Handler(Keystroke ks, Modifiers mods, bool pressed, uint32_t now) {
  // Send the keystroke to the Edit Line module
  // Then print the results of the Edit Line modules on the screen
  auto ln = edit::readline(ks, mods, pressed, now);
  if (pressed) {
    if (ks == Keystroke::Enter) {
      // If the user hit "enter" trigger the calculator
      const char* val = calc::Parse(ln.buf);
      if (val) {
        edit::setline(val);
        ln = edit::readline(ks, mods, pressed, now);
      } else if (ks == Keystroke::Tab) {
        // If they hit "Tab", type the calculator value
        Keyboard.print(ln.buf);
      }
    }
  }
  DrawText(ln);
  KeyboardMode result =
    (!pressed && ks == Keystroke::None && mods == Modifiers::ROpt)
      ? KeyboardMode::Normal
      : KeyboardMode::Calculator;
  if (result == KeyboardMode::Normal) {
    lastPos = {0, 0, 0, 0};
  }
  return result;
}
} // namespace calc