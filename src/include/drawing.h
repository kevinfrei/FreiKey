#pragma once

#include "sysstuff.h"

// The keyboard can send three messages, each of which also includes a
// length of time (in seconds) to display the message
// Status:
//  Layer State, Left/Right battery values. Charging status
//  Slave state, bluetooth host name
// String: print something out (45 bytes max)
//  Primarily useful for debugging, right?
// Prefixed number: a string (41 bytes max), a format (hex, uns, signed)
//  and a 32 bit value

namespace drawing {
void updateState();
} // namespace drawing
