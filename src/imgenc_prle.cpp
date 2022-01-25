#include <ctype.h>
#include <iostream>
#include <vector>

#include "bitmap.h"
#include "imgencoder.h"

/*
This should spit out the encoded source array

It's designed to run on a PC, so it's a memory hog (relatively speaking),
because why not?
*/

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool encode_prle(uint8_t* data, uint32_t bytes, byte_printer print) {
  if (bytes & 1) {
    // It must be 16 bit values, yeah?
    return false;
  }
  // First, build the palette
  const uint16_t* colors = reinterpret_cast<const uint16_t*>(data);
  uint32_t cbytes = bytes / 2;
  std::pair<std::vector<uint16_t>, std::vector<uint16_t>> pal_and_rev =
    calculate_palette(colors, cbytes);

  // Okay, start encoding
  // First, the palette size
  const uint32_t paletteSize = static_cast<uint32_t>(pal_and_rev.first.size());
  print(paletteSize & 0xFF);
  print((paletteSize >> 8) & 0xFF);

  // Now we use the rle engine, but use bit emission instead of word emission
  // to try to buy back more savings
  return false;
}
