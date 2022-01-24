#pragma once

#include <ctype.h>
#include <string>

#include "bitmap.h"

bool encode_rle(const uint8_t* data,
                uint32_t bytes,
                void (*print)(uint8_t byte));
bool encode_prle(const uint8_t* data,
                uint32_t bytes,
                void (*print)(uint8_t byte));
bool encode_pal(const uint8_t* data,
                uint32_t bytes,
                void (*print)(uint8_t byte));

struct cmdLine {
  image_compression cmpType;
  uint8_t imageToDecode;
  std::string filename;
  uint16_t width;
  uint16_t height;
};

extern uint32_t builtin_count;
bool validateArgs(cmdLine& ln);
int usage(const std::string& name);
int parseArgs(int argc, const char* argv[], cmdLine* ln);
