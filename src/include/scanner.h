#pragma once

#include "sysstuff.h"
#include <vector>

#include "bit_array.h"
#include "boardio.h"
#include "dbgcfg.h"
#include "hardware.h"
#include "kbreporter.h"
#include "keyhelpers.h"
#include "keystate.h"

// variable declarations
constexpr uint8_t num_keystates = 10;
extern keystate keyStates[num_keystates];
constexpr layer_t layer_max = 7;
extern layer_t layer_stack[layer_max + 1];
extern layer_t layer_pos;

// Functions
void layer_switch(layer_t layer);
void layer_toggle(layer_t layer);
void layer_pop(layer_t layer);
void layer_push(layer_t layer);
scancode_t getNextScanCode(MatrixBits& delta,
                           MatrixBits& curState,
                           bool& pressed);
uint32_t getColorForCurrentLayer();
keystate* findStateSlot(scancode_t scanCode);
void preprocessScanCode(scancode_t sc, bool pressed, uint32_t now);
void ProcessKeys(uint32_t now, kb_reporter& rpt);
