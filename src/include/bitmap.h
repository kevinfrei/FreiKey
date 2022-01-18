#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

enum class image_compression : uint8_t {
  RAW = 0,
  NQRLE, // 16 bit NQRLE encoding
  PAL_RAW, // Palette encoding
  PAL_NQRLE, // Palette encoded as NQRLE data
};

/*
NQRLE:
A list of stop-bit encoded values (Thus 0 - 2M in range), followed by data:
An odd value means N / 2 bytes to repeat the next single encoded value
An even value means N / 2 bytes to read in as unique string of pixels

PAL_RAW: (NYI)
First two bytes: little endian palette size (always less than 32768, or it's dumb) (palette_size)
Next palette_size * 2 bytes: the palette entries
log(palette_size) * width * height bits: pixel data

PAL_NQRLE: (NYI)
Same as PAL_RAW, but the pixel data is encoded as NQRLE,
where data is log(palette_size) bits, with the end trimmed
*/

struct image_descriptor {
  image_compression compression;
  uint16_t width, height;
  uint32_t byte_count;
  const uint8_t* image_data;
};

void decode_nqrle16(const uint8_t* compressedStream,
                    uint32_t streamLength,
                    void (*send)(const uint8_t* buf, uint16_t len));
