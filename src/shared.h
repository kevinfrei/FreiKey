#include <bluefruit.h>

#include "hwstate.h"

#define MANUFACTURER "FreikyStuff"
#define MODEL "FreiKeyboard"
#define BT_NAME "FreiKeys"
#define HW_REV "0001"
#define LHS_NAME BT_NAME "-LHS"

using scancode_t = uint8_t;

void shared_setup(const PinData &pd);
