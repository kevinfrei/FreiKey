#pragma once

#if !defined(MENU_MODULE_H)
#define MENU_MODULE_H

#include <vector>

#include "enumtypes.h"
#include "usbenums.h"

namespace menu {

namespace impl {

extern std::vector<KeyboardMode> modes;

void SelectHelper();

template <typename KM, typename... R>
void SelectHelper(KM km, R... rest) {
  modes.push_back(km);
  SelectHelper(rest...);
}

} // namespace impl

// This configures, then displays the initial menu
template <typename... Modes>
void SetupModeList(Modes... r) {
  // add k to the list
  impl::modes.clear();
  impl::SelectHelper(r...);
}

// This runs until a selection is made...
KeyboardMode Handler(Keystroke ks, Modifiers mods, bool pressed, uint32_t now);

} // namespace menu

#endif