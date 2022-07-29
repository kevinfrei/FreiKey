#include "sysstuff.h"

#include <array>
#include <stddef.h>

#include "newActionResult.h"
#include "newKeyInput.h"
#include "newKeyState.h"
#include "newSystemState.h"

// New 'thing'

void reportInput(const KeyboardInput&) {
  // TODO
}

void resumeNormalMode(const SystemState&) {
  // TODO
}

SystemState normalLoop(const SystemState& systemState) {
  KeyState keyState = KeyState::acquire();
  ActionResult actionResult =
    ActionResult::determineAction(keyState, systemState);
  if (actionResult.input.needsReported()) {
    reportInput(actionResult.input);
  }
  return actionResult.state;
}

SystemState modeLoop(const SystemState& systemState) {
  SystemState res = systemState.executeMode();
  if (res.isNormalMode()) {
    resumeNormalMode(res);
  }
  return res;
}

SystemState state;
void newMasterLoop() {
  state = normalLoop(state);
  while (!state.isNormalMode()) {
    state = modeLoop(state);
  }
}

/*
ActionResult determineAction(SystemState) {
  LayerState layerState = determineLayer(keyState, &systemState);
  ActionList actionList = calculateActions(keyState, layerState, &systemState);
  OutputActions outputActions = aggregateActions(actionList, &systemState);
  performLocalActions(outputActions.local, &systemState);
  reportKeyboardActions(outputActions.keyboard);
  return systemState;
}
*/