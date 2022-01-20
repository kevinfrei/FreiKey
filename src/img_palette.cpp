#if defined(COMPRESSOR)
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#endif

#include "bitmap.h"
#include <stdint.h>

bool rdbit(const uint8_t* const strm, uint32_t* ofs, uint8_t* bit) {
  uint8_t mask = 1 << *bit;
  bool res = (strm[*ofs] & mask) != 0;
  if (*bit == 7) {
    *bit = 0;
    ofs++;
  } else {
    (*bit)++;
  }
  return res;
}

uint16_t readBits(uint8_t numBits,
                  const uint8_t* const compressedStream,
                  uint32_t* i,
                  uint8_t* curBit) {
  uint16_t res = 0;
  uint16_t val = 1;
  while (numBits) {
    if (rdbit(compressedStream, i, curBit)) {
      res |= val;
    }
    val <<= 1;
  }
  return res;
}

uint16_t read16b(const uint8_t* const stream, uint32_t* ofs) {
  ofs += 2;
  return stream[*ofs - 2] + (stream[*ofs - 1] << 8);
}

uint8_t log2ish(uint16_t n) {
  uint8_t count = 0;
  // This handles 2 ^ n exactly.
  uint8_t rounded = !!((n > 1) & !(n & (n - 1)));
  while (n != 0) {
    n >>= 1;
    count += 1;
  }

  return count - rounded;
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

void decode_palette(const uint8_t* compressedStream,
                    uint32_t streamLength,
                    void (*send)(const uint8_t* buf, uint16_t len)) {
  const uint16_t bufSize = 1024;
  uint8_t buffer[1024];
  uint32_t offs = 0;
  uint32_t i = 0;
  // Read the size of the palette
  uint16_t paletteSize = read16b(compressedStream, &i);
  uint16_t* palette = new uint16_t[paletteSize];
  // Read the palette
  for (uint16_t j = 0; j < paletteSize; j++) {
    palette[j] = read16b(compressedStream, &i);
    if (i > streamLength) {
      // ARG!
    }
  }
  // Now read the pixel data
  uint8_t bit = 0;
  uint8_t numBits = log2ish(paletteSize);
  for (uint32_t i = 0; i < streamLength;) {
    uint16_t paletteIndex = readBits(numBits, compressedStream, &i, &bit);
    uint16_t color = palette[paletteIndex];
    if (offs == bufSize) {
      send(buffer, offs);
      offs = 0;
    }
    // Do I need to byte-swap here?
    buffer[offs++] = color & 0xFF;
    buffer[offs++] = color >> 8;
  }
  if (offs) {
    send(buffer, offs);
  }
  delete[] palette;
}
#if 1 || defined(COMPRESSOR)

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
  while (numBits) {
    if (value & 1) {
      curValue |= 1 << curBitPos;
    }
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

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool compress_palette(uint8_t* data,
                      uint32_t bytes,
                      void (*print)(uint8_t byte)) {
  if (bytes & 1) {
    // It must be 16 bit values, yeah?
    return false;
  }
  // First, build the palette
  uint16_t* colors = reinterpret_cast<uint16_t*>(data);
  uint32_t cbytes = bytes / 2;
  // Lazy man's set: it's just bits :D
  uint64_t which[1024];
  memset(&which[0], 0, 8192);
  for (uint32_t pos = 0; pos < cbytes; pos++) {
    uint16_t color = colors[pos];
    which[color / 64] |= (1 << (color & 63));
  }
  uint16_t paletteSize = countBits(which);
  uint8_t numBits = log2ish(paletteSize);
  // This is the size of the thing, when we're done.
  if (numBits * bytes / 2 + paletteSize * 2 + 2 >= bytes) {
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
  std::vector<uint16_t> reverse(65536,0xFFFF);

  uint16_t curBit = 0xFFFF;
  uint16_t palOfs = 0;
  // encode the bit numbers that are set in a list
  do {
    curBit++;
    // If this bit number is set, add it to the palette
    if (which[curBit / 64] & (1 << (curBit & 63))) {
      reverse[curBit] = palOfs;
      palette[palOfs++] = curBit;
      print(curBit & 0xFF);
      print(curBit >> 8);
    }
  } while (curBit != 0xFFFF);
  if (palOfs != paletteSize) {
    fprintf(stderr, "Derp\n");
    return false;
  }
  // Okay, now walk the pixels, reading the values and finding their palette
  // index, then write the index in numBits number of bits
  uint16_t info = 0;
  for (uint32_t pos = 0; pos < cbytes; pos++) {
    uint16_t color = colors[pos];
    uint16_t pIndex = reverse[color];
    if (pIndex > paletteSize || palette[pIndex] != color) {
      fprintf(stderr, "Derpy\n");
      return false;
    }
    info = writeBits(pIndex, numBits, info, print);
  }
  delete[] reverse;
  delete[] palette;
  return true;
}

uint8_t* outBuf;
uint32_t outSize = 0;
uint8_t* chkBuf;
uint32_t chkSize = 0;

void appendToOut(uint8_t val) {
  if ((outSize & 0xf) == 0) {
    printf("\n");
  }
  outBuf[outSize++] = val;
  printf("0x%02x, ", val);
}

void appendToChk(const uint8_t* buf, uint16_t len) {
  while (len--) {
    chkBuf[chkSize++] = *buf++;
  }
}

char* makeVarName(const char* name) {
  const char* last = strrchr(name, '/');
  if (last == NULL) {
    last = strrchr(name, '\\');
  }
  last = (last == NULL) ? name : (last + 1);
  char* res = (char*)malloc(strlen(last) + 5);
  char* val = res;
  if (!isalpha(*last)) {
    *val++ = '_';
  }
  while (*last) {
    *val++ = isalnum(*last) ? *last : '_';
    last++;
  }
  return res;
}

#define MAX_SIZE 1048576

// I used https://lvgl.io/tools/imageconverter to convert to 565 format
// This takes .bin files and spits out the list of bytes
int main(int argc, const char* argv[]) {
  FILE* in = fopen(argv[1], "rb");
  uint8_t* buf = (uint8_t*)malloc(MAX_SIZE);
  size_t sz = fread(buf, 1, MAX_SIZE - 1, in);
  fclose(in);
  uint8_t* inBuf = &buf[4];
  if ((buf[0] != 4 && buf[0] != 5) || buf[sz - 1] != 0xa) {
    fprintf(stderr, "Unrecognized format\n");
  }
  // No idea if this is correct, but it works for my collection of pictures
  uint32_t width = (buf[1] | ((buf[2] & 0xF) << 8)) >> 2;
  uint32_t height = (buf[3] << 4 | ((buf[2] & 0xF0) >> 4)) >> 1;
  sz -= 5;
  outBuf = (uint8_t*)malloc(MAX_SIZE);
  chkBuf = (uint8_t*)malloc(MAX_SIZE);
  char* varName = makeVarName(argv[1]);
  // Byte swap the buffer
  for (int i = 0; i < sz; i += 2) {
    uint8_t n1 = inBuf[i];
    uint8_t n0 = inBuf[i + 1];
    inBuf[i] = n0;
    inBuf[i + 1] = n1;
  }
  printf("#include \"bitmap.h\"\n");
  printf("\nuint8_t %s_data[] PROGMEM = {", varName);
  if (!not_quite_rle_encode_16bit(inBuf, sz, &appendToOut)) {
    fprintf(stderr, "Failed to encode\n");
    return -1;
  }
  decode_nqrle16(outBuf, outSize, &appendToChk);
  if (chkSize != sz) {
    fprintf(stderr,
            "Sizes are wrong %d decoded, %d original\n",
            chkSize,
            (uint32_t)sz);
    return -1;
  }
  for (int i = 0; i < chkSize; i += 2) {
    if (chkBuf[i] != inBuf[i] || chkBuf[i + 1] != inBuf[i + 1]) {
      fprintf(stderr, "Different at offset %d\n", i);
      return -1;
    }
  }
  printf("\n};\n");
  printf("image_descriptor %s = {\n", varName);
  printf("  .compression  = IMAGE_NQRLE16\n");
  printf("  .width        = %d,\n", width);
  printf("  .height       = %d,\n", height);
  printf("  .byte_count = %d,\n", outSize);
  printf("  .image_data = %s_data,\n", varName);
  printf("}; // %1.3f compression rate\n", (double)chkSize / (double)outSize);
  return 0;
}

#endif