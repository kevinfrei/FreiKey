#include <stdint.h>

#include "bitmap.h"

// This file must compile both for Arduino and for Windows/Mac.
// That means be careful with the C++, unfortunately...

void decode_prle(bytestream cmpStrm, uint32_t strmLen, sender send) {
  const uint16_t bufSize = 1024;
  uint8_t buffer[1024];
  int32_t offs = 0;
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
    uint32_t length = readStopBitNumber(cmpStrm, &i);
    bool repeat = length % 2 == 1;
    length /= 2;
    if (repeat) {
      // Read the value and repeat it
      uint16_t paletteIndex = readBits(numBits, cmpStrm, &i, &bit);
      uint16_t color = palette[paletteIndex];
      for (int32_t j = 0; j < length; j++) {
        if (offs + j * 2 == bufSize) {
          send(buffer, bufSize);
          offs = -(j * 2);
        }
        buffer[offs + j * 2] = color & 0xFF;
        buffer[offs + j * 2 + 1] = (color >> 8) & 0xFF;
      }
      offs += length * 2;
    } else {
      // Read the next 'length' palette entries into the buffer
      for (uint16_t j = 0; j < length; j++) {
        uint16_t paletteIndex = readBits(numBits, cmpStrm, &i, &bit);
        uint16_t color = palette[paletteIndex];
        if (offs + j * 2 == bufSize) {
          send(buffer, bufSize);
          offs = -(j * 2);
        }
        // Do I need to byte-swap here?
        buffer[offs + j * 2] = color & 0xFF;
        buffer[offs + j * 1 + 1] = (color >> 8) & 0xFF;
      }
      offs += length * 2;
    }
    // Increment i if we had any bits left to read in the current byte
    if (bit > 0) {
      i++;
    }
  }
  if (offs) {
    send(buffer, offs);
  }
  delete[] palette;
}
