#include <ctype.h>
#include <iostream>
#include <vector>

#include "bitmap.h"
#include "imgencoder.h"

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool encode_prle(bytestream data, uint32_t bytes, byte_printer print) {
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

  // Now emit the palette
  for (const uint16_t val : pal_and_rev.first) {
    print(val & 0xFF);
    print(val >> 8);
  }

  uint8_t numBits = log2ish(pal_and_rev.first.size());

  bool success = true;
  uint16_t bitBuffer = 0;
  // This is used to print the RLE counts, so it shows up between
  // groups of palette encoded numbers
  byte_printer printheader = [&](uint8_t val) {
    flushBits(bitBuffer, print);
    bitBuffer = 0;
    print(val);
  };
  // This is called to emit a palette encoded value
  // So, in here, we have to look up the value and emit just the bits
  // bitBuffer is updated to contain anything that hasn't been finished
  word_printer printblobs = [&](uint16_t val) {
    uint16_t palIndex = pal_and_rev.second[val];
    if (palIndex >(1 << numBits))
    {
      std::cerr << "Bad bad bad" << std::endl;
      success = false;
    } 
    bitBuffer = writeBits(palIndex, numBits, bitBuffer, print);
  };
  // Now we use the rle engine, but use bit emission instead of word emission
  // to try to buy back more savings
  success = dump_rle(data, bytes, printheader, printblobs) && success;
  // Pick up any final blob of data
  flushBits(bitBuffer, print);
  return success;
}
