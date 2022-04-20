#pragma once

#include "sysstuff.h"
#include <bitset>

#include "kbreporter.h"
#include "keystate.h"
#include "enumtypes.h"

// variable declarations
constexpr uint8_t num_keystates = 10;
extern keystate keyStates[num_keystates];

// Functions
void layer_switch(layer_t layer);
void layer_toggle(layer_t layer);
void layer_pop(layer_t layer);
void layer_push(layer_t layer);
uint32_t getColorForCurrentLayer();
layer_num getCurrentLayer();
keystate* findStateSlot(scancode_t scanCode);
void preprocessScanCode(scancode_t sc, bool pressed, uint32_t now);
KeyboardMode ProcessKeys(uint32_t now, kb_reporter& rpt);
