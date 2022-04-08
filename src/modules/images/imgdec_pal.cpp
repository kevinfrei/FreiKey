#include <stdint.h>

#include "bitmap.h"

// This file must compile both for Arduino and for Windows/Mac.
// That means be careful with the C++, unfortunately...

uint8_t log2ish(uint16_t n) {
  uint8_t count = 0;
  // This handles 2 ^ n exactly.
  uint8_t rounded = !!((n > 1) && !(n & (n - 1)));
  while (n != 0) {
    n >>= 1;
    count += 1;
  }

  return count - rounded;
}

bool rdbit(bytestream strm, uint32_t* ofs, uint8_t* bit) {
  uint8_t mask = 1 << *bit;
  bool res = (strm[*ofs] & mask) != 0;
  if (*bit == 7) {
    *bit = 0;
    (*ofs)++;
  } else {
    (*bit)++;
  }
  return res;
}

uint16_t readBits(uint8_t numBits,
                  bytestream cmpStrm,
                  uint32_t* i,
                  uint8_t* curBit) {
  uint16_t res = 0;
  uint16_t val = 1;
  while (numBits--) {
    if (rdbit(cmpStrm, i, curBit)) {
      res |= val;
    }
    val <<= 1;
  }
  return res;
}

uint16_t read16b(bytestream stream, uint32_t* ofs) {
  *ofs += 2;
  return stream[*ofs - 2] + (stream[*ofs - 1] << 8);
}

// Palette encoded image

// The first 2 bytes are the # of palette entries (must be less than 16 bits)
// followed by the palette entries

// Next is a stop-bit number of entries, and finally the list of palette indices
// encoded in bit-little-endian order. The # of bits is the number required to
// encode all palette locations, so if it's 488 palette entries, we'll have 9
// bit palette entries:
// clang-format off
// 8765 4321 7654 3219 6543 2198 5432 1987 4321 9876.... << bit number
// 1111 1111 2222 2221 3333 3322 4444 4333 5555 4444.... << digit number 
// 1101.0110 1010.1000 1101.0000 1011.1101 1111.0001 << values (MSB->LSB)
// clang-format on
// the first number is 0.1101.0110, next number is 0.0101.0100

void decode_pal(bytestream cmpStrm, uint32_t strmLen, sender send) {
  const uint16_t bufSize = 1024;
  uint8_t buffer[1024];
  uint32_t offs = 0;
  uint32_t i = 0;
  // Read the size of the palette
  uint16_t paletteSize = read16b(cmpStrm, &i);
  uint16_t* palette = new uint16_t[paletteSize];
  // Read the palette
  for (uint16_t j = 0; j < paletteSize; j++) {
    palette[j] = read16b(cmpStrm, &i);
    if (i > strmLen) {
      // ARG!
    }
  }
  // Now read the pixel data
  uint8_t bit = 0;
  uint8_t numBits = log2ish(paletteSize);
  while (i < strmLen) {
    uint16_t paletteIndex = readBits(numBits, cmpStrm, &i, &bit);
    uint16_t color = palette[paletteIndex];
    if (offs == bufSize) {
      send(buffer, offs);
      offs = 0;
    }
    // I need to byte-swap here
    buffer[offs++] = color >> 8;
    buffer[offs++] = color & 0xFF;
  }
  if (offs) {
    send(buffer, offs);
  }
  delete[] palette;
}
