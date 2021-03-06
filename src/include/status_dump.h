#pragma once

#if defined(STATUS_DUMP)
#include "hardware.h"

// Types the "str" string (with lots of limitations)
void type_string(const char* str);

// Types the number
void type_number(uint32_t val);

// Checks to see if the user is pushing magic keys. If so, do something with it.
// return true to onot report the keys to the HID...
bool status_dump_check(const state::hw& rightSide, const state::hw& leftSide);

#endif
