#pragma once

#include "sysstuff.h"
#include <vector>

#include "boardio.h"
#include "dbgcfg.h"
#include "hardware.h"
#include "kbreporter.h"
#include "keyhelpers.h"
#include "keystate.h"

// variable declarations
constexpr uint8_t num_keystates = 10;
extern keystate keyStates[num_keystates];

// Functions
void layer_switch(layer_t layer);
void layer_toggle(layer_t layer);
void layer_pop(layer_t layer);
void layer_push(layer_t layer);
uint32_t getColorForCurrentLayer();
keystate* findStateSlot(scancode_t scanCode);
void preprocessScanCode(scancode_t sc, bool pressed, uint32_t now);
void ProcessKeys(uint32_t now, kb_reporter& rpt);

// Given a delta mask, get the scan code, update the delta mask and set pressed
// while we're at it.
template <typename T>
scancode_t getNextScanCode(T& delta, T& curState, bool& pressed) {
  scancode_t sc = delta.pull_a_bit();
  pressed = curState.get_bit(sc);
  return sc;
}
