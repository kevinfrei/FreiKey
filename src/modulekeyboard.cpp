#include "dbgcfg.h"

#include "action.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "keymap.h"
#include "keystate.h"
#include "modulekeyboard.h"
#include "scanner.h"
#include "usbenums.h"

// This is used to let us not be a USB keyboard, but use the board "locally"
// for something like a calculator or a game, etc...
KeyboardMode ModuleKeyboardHandler(KeyboardMode curMode,
                                   KeystrokeHandler handler,
                                   Spinner spin) {
  Modifiers localMods = Modifiers::None;
  KeyboardMode mode = curMode;
  Dbg << "Entering Module Keyboard handler" << sfmt::endl;
  do {
    scancode_t sc;
    bool pressed = false;
    uint32_t now = millis();
    Scanner scanner{now};
    while ((sc = scanner.getNextCode(pressed)) != 0xFF) {
      // Get the keystroke & modifier based on the scan code:
      action_t a = moduleKeyMap[sc];
      switch (a.getAction()) {
        case KeyAction::KeyPress:
          mode = handler(a.getKeystroke(), localMods, pressed, now);
          Dbg2 << "Mode handler KeyPress returned " << value_cast(mode)
               << sfmt::endl;
          break;
        case KeyAction::Modifier:
          if (pressed) {
            localMods |= a.getModifiers();
          } else {
            localMods &= ~a.getModifiers();
          }
          mode = handler(Keystroke::None, localMods, pressed, now);
          Dbg2 << "Mode handler Modifier returned " << value_cast(mode)
               << sfmt::endl;
          break;
        case KeyAction::Mode:
          if (pressed) {
            mode = a.getMode();
          }
          Dbg2 << "Got raw Mode action " << value_cast(mode) << sfmt::endl;
          break;
        default:
          Dbg << "Unsupported action type for raw keyboard: " << a.getAction()
              << sfmt::endl;
      }
    }
    scanner.Done();
    if (mode == curMode && spin != nullptr) {
      mode = spin(mode, now);
    }
  } while (mode == curMode);
  Dbg << "Exiting Module Keyboard Handler" << sfmt::endl;
  return mode;
}
/*
if (a.getAction() == KeyAction::Modifier) {
  if (pressed) {
    menuMods |= a.getModifiers();
  } else {
    // This should turn them off, right?
    menuMods &= ~a.getModifiers();
  }
} else if (a.getAction() == KeyAction::KeyPress) {
  // Send the keystroke to the Edit Line module
  // Then print the results of the Edit Line modules on the screen

  // If the user hits "enter" trigger the calculator
  auto ln = edit::readline(a.getKeystroke(), menuMods, pressed, millis());
  if (a.getKeystroke() == Keystroke::Enter && pressed) {
    const char* val = calc::Parse(ln.buf);
    if (val) {
      edit::setline(val);
      ln = edit::readline(a.getKeystroke(), menuMods, pressed, millis());
    }
  }
  DrawText(ln);
  if (a.getKeystroke() == Keystroke::Tab && pressed) {
    Keyboard.print(ln.buf);
  }
  // And if they hit whatever "paste" should be, type the calculator value
}
*/