#include <bitset>
#include <ctype.h>
#include <iostream>
#include <utility>
#include <vector>

#include "bitmap.h"

/*
This should spit out the encoded source array

It's designed to run on a PC, so it's a memory hog (relatively speaking),
because why not?
*/

uint16_t writeBits(uint16_t value,
                   uint8_t numBits,
                   uint16_t info,
                   void (*print)(uint8_t byte)) {
  uint8_t curBitPos = info & 0xff;
  uint8_t curValue = info >> 8;
  while (numBits--) {
    if (value & 1) {
      curValue |= 1 << curBitPos;
    }
    value /= 2;
    curBitPos++;
    if (curBitPos == 8) {
      print(curValue);
      curBitPos = 0;
      curValue = 0;
    }
  }
  return curValue << 8 | curBitPos;
}

std::pair<std::vector<uint16_t>, std::vector<uint16_t>> calculate_palette(
  const uint16_t* colors, uint32_t cbytes) {
  // Lazy man's set: it's just bits :D
  std::bitset<65536> which;
  uint16_t paletteSize = 0;
  for (uint32_t pos = 0; pos < cbytes; pos++) {
    uint16_t color = colors[pos];
    if (!which.test(color)) {
      which.set(color);
      paletteSize++;
    }
  }
  const uint32_t bitCount = which.count();
  if (paletteSize != bitCount) {
    std::cerr << "Derpy: " << paletteSize << " but " << bitCount << " counted"
              << std::endl;
    return std::make_pair(std::vector<uint16_t>{}, std::vector<uint16_t>{});
  }
  uint8_t numBits = log2ish(paletteSize);
  // This is the size of the thing, when we're done.
  if (numBits * cbytes / 8 + paletteSize + 1 >= cbytes) {
    // Don't 'compress' it if it's going to be larger, right?
    // return false;
  }
  // Next, encode and build the palette (at the same time...)
  // This is just to check correctness...
  std::pair<std::vector<uint16_t>, std::vector<uint16_t>> pal_and_rev =
    make_pair(std::vector<uint16_t>(static_cast<std::size_t>(paletteSize), 0),
              // Efficient! :D Initialize it to FFFF for error detection
              std::vector<uint16_t>(static_cast<std::size_t>(65536), 0xFFFF));

  uint16_t curBit = 0xFFFF;
  uint16_t palOfs = 0;
  // encode the bit numbers that are set in a list
  do {
    curBit++;
    // If this bit number is set, add it to the palette

    if (which.test(curBit)) {
      pal_and_rev.second[curBit] = palOfs;
      pal_and_rev.first[palOfs++] = curBit;
      // print(curBit & 0xFF);
      // print(curBit >> 8);
    }
  } while (curBit != 0xFFFF);
  if (palOfs != paletteSize) {
    std::cerr << "Derp" << std::endl;
    return std::make_pair(std::vector<uint16_t>{}, std::vector<uint16_t>{});
  }
  return pal_and_rev;
}

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool encode_pal(const uint8_t* data,
                uint32_t bytes,
                void (*print)(uint8_t byte)) {
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
  // Okay, now walk the pixels, reading the values and finding their palette
  // index, then write the index in numBits number of bits
  uint16_t info = 0;
  for (uint32_t pos = 0; pos < cbytes; pos++) {
    uint16_t color = colors[pos];
    uint16_t pIndex = pal_and_rev.second[color];
    if (pIndex >= paletteSize || pal_and_rev.first[pIndex] != color) {
      std::cerr << "Derpy" << std::endl;
      return false;
    }
    info = writeBits(pIndex, numBits, info, print);
  }
  // Make sure we get the last few bits
  if (info) {
    print(info >> 8);
  }
  return true;
}
