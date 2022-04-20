#include "enumtypes.h"

namespace menu {
  std::vector<KeyboardMode> modes;

  KeyboardMode Select() {
    // display the menu, navigate it, and return the selected item
    std::vector<KeyboardMode> m{modes};
    // Clear the list so we can be invoked again
    modes.clear();

    return KeyboardMode::Normal;
  }

  template <KeyboardMode k, typename... R>
  KeyboardMode Select(KeyboardMode k, R... r) {
    // add k to the list
    modes.push_back(k);
    return Select(...r);
  }
}