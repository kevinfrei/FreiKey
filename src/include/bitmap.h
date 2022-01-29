#pragma once

#if !defined(COMPRESSOR)
#include <avr/pgmspace.h>
#else
#define PROGMEM 
#endif
#include <stdint.h>

/*
NQRLE:
A list of stop-bit encoded values (Thus 0 - 2M in range), followed by data:
An odd value means N / 2 bytes to repeat the next single encoded value
An even value means N / 2 bytes to read in as unique string of pixels

PAL_RAW: (NYI)
First two bytes: little endian palette size (always less than 32768, or it's
dumb) (palette_size) Next palette_size * 2 bytes: the palette entries
log(palette_size) * width * height bits: pixel data

PAL_NQRLE: (NYI)
Same as PAL_RAW, but the pixel data is encoded as NQRLE,
where data is log(palette_size) bits, with the end trimmed
*/

enum class image_compression : uint8_t {
  RAW = 0,
  NQRLE, // 16 bit NQRLE encoding
  PAL_RAW, // Palette encoding
  PAL_NQRLE, // Palette encoded as NQRLE data
#if defined(COMPRESSOR)
  FIND_BEST,
  INVALID
#endif
};

struct image_descriptor {
  uint16_t width, height;
  uint32_t byte_count : 24;
  image_compression compression : 8;
  const uint8_t* image_data;
};

using bytestream = const uint8_t*;
using sender = void (*)(bytestream, uint16_t);
using decoder = void (*)(bytestream, uint32_t, sender);

void decode_rle(bytestream cmpStrm, uint32_t len, sender send);
void decode_pal(bytestream cmpStrm, uint32_t len, sender send);
void decode_prle(bytestream cmpStrm, uint32_t len, sender send);

// Helpers
uint8_t log2ish(uint16_t n);
uint16_t readBits(uint8_t numBits,
                  bytestream cmpStrm,
                  uint32_t* i,
                  uint8_t* curBit);
uint16_t read16b(bytestream stream, uint32_t* ofs);
uint32_t readStopBitNumber(bytestream cmpStrm, uint32_t* i);