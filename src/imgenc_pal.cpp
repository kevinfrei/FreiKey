#include <ctype.h>
#include <iostream>
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

uint16_t getVal(uint8_t* data, uint32_t pos) {
  return (data[pos] << 8) | data[pos + 1];
}

uint16_t countBits(const uint64_t* bits) {
  uint16_t count = 0;
  for (uint16_t pos = 0; pos < 1024; pos++) {
    uint64_t val = bits[pos];
    while (val) {
      count++;
      val &= (val - 1);
    }
  }
  return count;
}

uint64_t getBitMask(uint8_t val) {
  return static_cast<uint64_t>(static_cast<uint64_t>(1)
                               << static_cast<uint64_t>(val));
}

constexpr uint8_t bpl = sizeof(uint64_t) * 8;

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
  // Lazy man's set: it's just bits :D
  uint64_t which[0x10000 / bpl];
  memset(&which[0], 0, sizeof(uint64_t) * (0x10000 / bpl));
  uint16_t paletteSize = 0;
  for (uint32_t pos = 0; pos < cbytes; pos++) {
    uint16_t color = colors[pos];
    uint64_t bitSet = getBitMask(color & 63);
    ;
    if (!(which[color / 64] & bitSet)) {
      which[color / 64] |= bitSet;
      paletteSize++;
    }
  }
  const uint32_t bitCount = countBits(which);
  if (paletteSize != bitCount) {
    std::cerr << "Derpy: " << paletteSize << " but " << bitCount << " counted"
              << std::endl;
    return false;
  }
  uint8_t numBits = log2ish(paletteSize);
  // This is the size of the thing, when we're done.
  if (numBits * bytes / (2 * 8) + paletteSize * 2 + 2 >= bytes) {
    // Don't 'compress' it if it's going to be larger...
    return false;
  }
  // Okay, start encoding
  // First, the palette size
  print(paletteSize & 0xFF);
  print(paletteSize >> 8);
  // Next, encode and build the palette (at the same time...)
  // This is just to check correctness...
  std::vector<uint16_t> palette(paletteSize, 0);
  // Efficient! :D Initialize it to FFFF for error detection
  std::vector<uint16_t> reverse(65536, 0xFFFF);

  uint16_t curBit = 0xFFFF;
  uint16_t palOfs = 0;
  // encode the bit numbers that are set in a list
  do {
    curBit++;
    // If this bit number is set, add it to the palette

    if (which[curBit / 64] & getBitMask(curBit & 63)) {
      reverse[curBit] = palOfs;
      palette[palOfs++] = curBit;
      print(curBit & 0xFF);
      print(curBit >> 8);
    }
  } while (curBit != 0xFFFF);
  if (palOfs != paletteSize) {
    std::cerr << "Derp" << std::endl;
    return false;
  }
  // Okay, now walk the pixels, reading the values and finding their palette
  // index, then write the index in numBits number of bits
  uint16_t info = 0;
  for (uint32_t pos = 0; pos < cbytes; pos++) {
    uint16_t color = colors[pos];
    uint16_t pIndex = reverse[color];
    if (pIndex >= paletteSize || palette[pIndex] != color) {
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
