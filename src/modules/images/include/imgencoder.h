#pragma once

#if !defined(STANDALONE)
#error This is only meant to be used in the stand-alone image encoder/decoder thing
#endif

#include <ctype.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "bitmap.h"

using byte_printer = std::function<void(uint8_t)>;
using word_printer = std::function<void(uint16_t)>;
bool encode_rle(bytestream data, uint32_t bytes, byte_printer print);
bool encode_prle(bytestream data, uint32_t bytes, byte_printer print);
bool encode_pal(bytestream data, uint32_t bytes, byte_printer print);
using encoder = bool (*)(bytestream, uint32_t, byte_printer);

struct cmdLine {
  image_compression cmpType;
  uint8_t imageToDecode;
  std::string filename;
  uint16_t width;
  uint16_t height;
};

uint16_t writeBits(uint16_t value,
                   uint8_t numBits,
                   uint16_t bitBuffer,
                   byte_printer print);
void flushBits(uint16_t bitBuffer, byte_printer print);
void dumpRLECount(bool repeat, uint32_t count, byte_printer print);
bool dump_rle(bytestream data,
              uint32_t bytes,
              byte_printer print,
              word_printer print2);
std::pair<std::vector<uint16_t>, std::vector<uint16_t>> calculate_palette(
  const uint16_t* colors, uint32_t cbytes);

extern const uint32_t builtin_count;
bool validateArgs(cmdLine& ln);
int usage(const std::string& name);
int parseArgs(int argc, const char* argv[], cmdLine* ln);
