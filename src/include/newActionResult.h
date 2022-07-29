#pragma once
#if !defined(_GUARD_ACTIONRESULT_H)
#define _GUARD_ACTIONRESULT_H

#include "newKeyState.h"
#include "newKeyboardInput.h"
#include "newSystemState.h"

struct ActionResult {
  KeyboardInput input;
  SystemState state;
  static ActionResult determineAction(const KeyState&, const SystemState&) {
    // TODO
    return ActionResult{};
  }
};

#endif