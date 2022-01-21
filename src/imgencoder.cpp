#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "imgencoder.h"
#define COMPRESSOR 1
#include "bitmap.h"
#include "bitmaps/amy.h"
#include "bitmaps/batman.h"
#include "bitmaps/linux.h"
#include "bitmaps/mac.h"
#include "bitmaps/win.h"

const image_descriptor* builtins[] = {
  gfx_amy, gfx_batman, gfx_mac, gfx_win, gfx_linux};
constexpr uint32_t builtin_count = sizeof(builtins) / sizeof(*builtins);

std::vector<uint8_t> outBuf;
std::vector<uint8_t> chkBuf;

int linePos = 0;
void appendToOut(uint8_t val) {
  int width = val < 10 ? 2 : (val < 100) ? 3 : 4;
  if (linePos + width > 80) {
    printf("\n");
    linePos = 0;
  }
  linePos += width;
  outBuf.push_back(val);
  printf("%d,", val);
}

void appendToChk(const uint8_t* buf, uint16_t len) {
  while (len--) {
    chkBuf.push_back(*buf++);
  }
}

std::string makeVarName(const std::string& name) {
  std::string::size_type last = name.find_last_of('/');
  if (last == std::string::npos)
    last = name.find_last_of('\\');
  std::string piece =
    (last == std::string::npos) ? name : name.substr(last + 1);
  std::string res = "";
  if (!isalpha(piece[0])) {
    res.push_back('_');
  }
  for (const char c : piece) {
    res.push_back(isalnum(c) ? c : '_');
  }
  return res;
}

void decode_raw(const uint8_t* data,
                uint32_t len,
                void (*send)(const uint8_t* b, uint16_t l)) {
  while (len) {
    uint16_t l = std::min(0x8000u, len);
    send(data, l);
    data += l;
    len -= l;
  }
}

int decode(int number, const char* filename) {
  // TODO: Spit out image number into the file name
  printf("Dumping image %d into %s\n", number, filename);
  const image_descriptor* id = builtins[number];
  decoder func;
  switch (id->compression) {
    case image_compression::NQRLE:
      func = decode_nqrle16;
      break;
    case image_compression::RAW:
      func = decode_raw;
      break;
    case image_compression::PAL_RAW:
    case image_compression::PAL_NQRLE:
    default:
      fprintf(stderr, "Format unrecognized!\n");
      return 1;
  }
  func(id->image_data, id->byte_count, &appendToChk);
  std::ofstream file{filename, std::ios_base::out | std::ios_base::binary};
  std::copy(
    chkBuf.cbegin(), chkBuf.cend(), std::ostream_iterator<uint8_t>{file});
  return 0;
}

#define MAX_SIZE 1048576

struct cmdLine {
  image_compression cmpType;
  uint8_t imageToDecode;
  std::string filename;
  uint16_t width;
  uint16_t height;
};

int parseCodec(const std::string& name, cmdLine* ln) {
  if (name.find("rle") == 0) {
    ln->cmpType = image_compression::NQRLE;
  } else if (name.find("prle") == 0) {
    ln->cmpType = image_compression::PAL_NQRLE;
  } else if (name.find("pal") == 0) {
    ln->cmpType = image_compression::PAL_RAW;
  } else if (name.find("raw") == 0) {
    ln->cmpType = image_compression::RAW;
  } else
    return 1;
  return 0;
}

int32_t readPosNumber(const std::string& maybeNum) {
  int32_t res = 0;
  for (auto ci = maybeNum.rbegin(); ci != maybeNum.rend(); ci++) {
    char c = *ci;
    if (!isdigit(c)) {
      return -1;
    }
    res = res * 10 + c - '0';
  }
  return res;
}

int parseHeight(const std::string& height, cmdLine* ln) {
  int val = readPosNumber(height);
  if (val < 0) {
    return 1;
  } else {
    ln->height = val;
    return 0;
  }
}

int parseWidth(const std::string& width, cmdLine* ln) {
  int val = readPosNumber(width);
  if (val < 0) {
    return 1;
  } else {
    ln->width = val;
    return 0;
  }
}

int parseImageNum(const std::string& num, cmdLine* ln) {
  int val = readPosNumber(num);
  if (val < 0) {
    return 1;
  } else {
    ln->imageToDecode = val;
    return 0;
  }
}

int usage(const char* name) {
  fprintf(stderr,
          "Usage:\n%s <flags> <--codec:XXX> <filename>\n"
          "Where <filename> is (probably) a file produced from "
          "https://lvgl.io/tools/imageconverter in the 565 format\n"
          "and XXX is optionally raw, rle, pal, or prle\n"
          "OR\n"
          "%s --decode:# <filename>\n"
          "Spit out the internal image # into <filename>\n"
          "OR\n"
          "%s --width:# --height:# <filename.raw>\n"
          /*
          "<flags> are:\n\t-d:/--decode:<num> to decode from the internal "
          "image <num> and spit it into <filename>\n\t-c:/--codec:<id> force
          output " "of that codec (don't find best): raw, pal, rle, rpal\n"*/
          ,
          name,
          name,
          name);
  return 1;
}

struct flags {
  std::string name;
  int (*parser)(const std::string&, cmdLine*);
};

flags parser[] = {
  {.name = std::string("--decode:"), .parser = parseImageNum},
  {.name = std::string("--codec:"), .parser = parseCodec},
  {.name = std::string("--width:"), .parser = parseWidth},
  {.name = std::string("--height:"), .parser = parseHeight},
};

int parseArgs(int argc, const char* argv[], cmdLine* ln) {
  // Argument parsing really does suck...
  for (int curArg = 1; curArg < argc; curArg++) {
    std::string arg{argv[curArg]};
    if (arg[0] != '-') {
      if (curArg != argc - 1) {
        return -1;
      }
      ln->filename = arg;
    } else {
      for (auto& flag : parser) {
        if (arg.size() > flag.name.size() &&
            arg.substr(0, flag.name.size()) == flag.name) {
          int res = flag.parser(arg.substr(flag.name.size()), ln);
          if (res != 0)
            return res;
          else
            break;
        }
      }
    }
  }
  return 0;
}

bool validateArgs(cmdLine &ln) {
  if (!!ln.height != !!ln.width) {
    return false;
  }
  if (ln.imageToDecode > builtin_count) {
    return false;
  }
  return true;
}

// I used https://lvgl.io/tools/imageconverter to convert to 565 format
// This takes .bin files and spits out the list of bytes
int main(int argc, const char* argv[]) {
  cmdLine ln;
  if (parseArgs(argc, argv, &ln) || !validateArgs(ln)) {
    return usage(argv[0]);
  }
// Resume here
  std::ifstream stream(argv[argc - 1], std::ios::in | std::ios::binary);
  std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)),
                                std::istreambuf_iterator<char>());

  uint8_t* buf = contents.data();
  uint32_t sz = contents.size();
  uint8_t* inBuf = &buf[4];
  if ((buf[0] != 4 && buf[0] != 5) || buf[sz - 1] != 0xa) {
    fprintf(stderr, "Unrecognized format\n");
  }
  // No idea if this is correct, but it works for my collection of pictures
  uint32_t width = (buf[1] | ((buf[2] & 0xF) << 8)) >> 2;
  uint32_t height = (buf[3] << 4 | ((buf[2] & 0xF0) >> 4)) >> 1;
  sz -= 5;

  std::string varName = makeVarName(argv[1]);
  // Byte swap the buffer
  for (int i = 0; i < sz; i += 2) {
    uint8_t n1 = inBuf[i];
    uint8_t n0 = inBuf[i + 1];
    inBuf[i] = n0;
    inBuf[i + 1] = n1;
  }

  printf("#include \"bitmap.h\"\n");
  printf("\nuint8_t %s_data[] PROGMEM = {", varName.c_str());
  if (!encode_nqrle16(inBuf, sz, &appendToOut)) {
    fprintf(stderr, "Failed to encode\n");
    return -1;
  }
  decode_nqrle16(outBuf.data(), (uint32_t)outBuf.size(), &appendToChk);
  if (chkBuf.size() != sz) {
    fprintf(stderr,
            "Sizes are wrong %llu decoded, %d original\n",
            chkBuf.size(),
            (uint32_t)sz);
    return 1;
  }
  for (int i = 0; i < chkBuf.size(); i += 2) {
    if (chkBuf[i] != inBuf[i] || chkBuf[i + 1] != inBuf[i + 1]) {
      fprintf(stderr, "Different at offset %d\n", i);
      return 1;
    }
  }
  printf("\n};\n");
  printf("image_descriptor %s = {\n", varName.c_str());
  printf("  .width = %d,\n", width);
  printf("  .height = %d,\n", height);
  printf("  .byte_count = %llu,\n", outBuf.size());
  printf("  .compression = IMAGE_NQRLE16\n");
  printf("  .image_data = %s_data,\n", varName.c_str());
  printf("}; // %1.3f compression rate\n",
         (double)chkBuf.size() / (double)outBuf.size());
  return 0;
}
