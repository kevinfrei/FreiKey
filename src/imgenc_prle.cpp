#include <ctype.h>
#include <iostream>
#include <vector>

#include "bitmap.h"

/*
This should spit out the encoded source array

It's designed to run on a PC, so it's a memory hog (relatively speaking),
because why not?
*/

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool encode_prle(uint8_t* data, uint32_t bytes, void (*print)(uint8_t byte)) {
  return false;
}
