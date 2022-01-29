#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <iterator>
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
const uint32_t builtin_count = static_cast<uint32_t>(std::size(builtins));

std::vector<uint8_t> outBuf;
std::vector<uint8_t> chkBuf;

int linePos = 0;
int lineWidth = 100;
bool dump = false;

void appendByteToOut(uint8_t val) {
  int width = val < 10 ? 2 : (val < 100) ? 3 : 4;
  if (linePos + width > lineWidth) {
    std::cout << std::endl;
    linePos = 0;
  }
  linePos += width;
  outBuf.push_back(val);
  std::cout << static_cast<uint32_t>(val) << ",";
}

void appendToOut(bytestream buf, uint16_t len) {
  for (uint16_t i = 0; i < len; i++) {
    appendByteToOut(buf[i]);
  }
}

int nums = 0;
void show(uint8_t val) {
  if (dump) {
    std::cout << static_cast<uint32_t>(val);
    if (nums == 16) {
      std::cout << std::endl;
      nums = 0;
    } else {
      std::cout << ",";
      nums = 0;
    }
  }
}

void appendByteToChk(uint8_t val) {
  chkBuf.push_back(val);
  show(val);
}

void appendToChk(bytestream buf, uint16_t len) {
  for (uint16_t i = 0; i < len; i++) {
    chkBuf.push_back(buf[i]);
    show(buf[i]);
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

void decode_raw(bytestream data, uint32_t len, sender send) {
  for (uint32_t i = 0; i < len;) {
    uint16_t l = std::min(0x8000u, len);
    send(&data[i], l);
    i += l;
  }
}

int decode(int number, const std::string& filename) {
  // TODO: Spit out image number into the file name
  std::cout << "Dumping image " << number << " into " << filename << std::endl;
  const image_descriptor* id = builtins[number];
  decoder func;
  switch (id->compression) {
    case image_compression::NQRLE:
      func = decode_rle;
      break;
    case image_compression::RAW:
      func = decode_raw;
      break;
    case image_compression::PAL_RAW:
      func = decode_pal;
      break;
    case image_compression::PAL_NQRLE:
      func = decode_prle;
      break;
    default:
      std::cerr << "Format unrecognized!" << std::endl;
      return 1;
  }
  func(id->image_data, id->byte_count, appendToChk);
  std::ofstream file{filename, std::ios_base::out | std::ios_base::binary};
  std::copy(
    chkBuf.cbegin(), chkBuf.cend(), std::ostream_iterator<uint8_t>{file});
  return 0;
}

std::string name(image_compression c) {
  switch (c) {
    case image_compression::NQRLE:
      return "NQRLE";
    case image_compression::PAL_NQRLE:
      return "PAL_NQRLE";
    case image_compression::PAL_RAW:
      return "PAL_RAW";
    case image_compression::RAW:
      return "RAW";
    default:
      return "INVALID";
  }
}

uint32_t check_roundtrip(
  const char* name, encoder enc, decoder dec, uint8_t* inBuf, uint32_t sz) {
  if (!enc(inBuf, sz, appendByteToChk)) {
    return 0;
  }
  std::vector<uint8_t> outputCopy{chkBuf};
  chkBuf.clear();
  dec(outputCopy.data(), static_cast<uint32_t>(outputCopy.size()), appendToChk);
  const uint32_t encSize = static_cast<uint32_t>(outputCopy.size());
  outputCopy.clear();
  if (chkBuf.size() != sz) {
    std::cerr << name << " sizes are wrong " << chkBuf.size() << " decoded, "
              << sz << " original" << std::endl;
    return 0;
  }
  for (int i = 0; i < chkBuf.size(); i += 2) {
    if (chkBuf[i] != inBuf[i] || chkBuf[i + 1] != inBuf[i + 1]) {
      std::cerr << name << " different at offset " << i << std::endl;
      return 0;
    }
  }
  chkBuf.clear();
  return encSize;
}

image_compression enc_and_dec(uint8_t* inBuf, uint32_t sz) {
  // First, do the "simple" RLE encoding
  const uint32_t rleSize =
    check_roundtrip("rle", encode_rle, decode_rle, inBuf, sz);
  // Okay, now try the palette encoding
  const uint32_t palSize =
    check_roundtrip("pal", encode_pal, decode_pal, inBuf, sz);
  // Finish what is *probably* smallest: Palette RLE encoding
  const uint32_t prleSize =
    check_roundtrip("prle", encode_prle, decode_prle, inBuf, sz);
  const uint32_t smallest = std::min({rleSize, palSize, prleSize});
  if (smallest == rleSize) {
    return image_compression::NQRLE;
  }
  if (smallest == palSize) {
    return image_compression::PAL_RAW;
  }
  return image_compression::PAL_NQRLE;
}

// I used https://lvgl.io/tools/imageconverter to convert to 565 format
// This takes .bin files and spits out the list of bytes
int main(int argc, const char* argv[]) {
  cmdLine ln{.cmpType = image_compression::FIND_BEST};
  if (parseArgs(argc, argv, &ln) || !validateArgs(ln)) {
    return usage(argv[0]);
  }
  if (ln.imageToDecode > 0) {
    return decode(ln.imageToDecode - 1, ln.filename);
  }
  // If we're here, we're encoding an image, right?
  std::ifstream stream(argv[argc - 1], std::ios::in | std::ios::binary);
  std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)),
                                std::istreambuf_iterator<char>());

  uint8_t* buf = contents.data();
  uint32_t sz = static_cast<uint32_t>(contents.size()), width, height;
  uint8_t* inBuf;
  if (ln.width) {
    // Raw image: get the data from the command line
    width = ln.width;
    height = ln.height;
    inBuf = buf;
    if (sz != width * height * 2) {
      std::cerr << "Size is " << sz << " but is expected to be " << width
                << " * " << height << " * 2 (" << width * height * 2 << ")"
                << std::endl;
      return 1;
    }
  } else {
    // Image came from the converter thing. Pull data from the file
    inBuf = &buf[4];
    if ((buf[0] != 4 && buf[0] != 5) || buf[sz - 1] != 0xa) {
      std::cerr << "Unrecognized format" << std::endl;
      return 1;
    }
    // No idea if this is correct, but it works for my collection of pictures
    width = (buf[1] | ((buf[2] & 0xF) << 8)) >> 2;
    height = (buf[3] << 4 | ((buf[2] & 0xF0) >> 4)) >> 1;
    if (sz != width * height * 2 + 6) {
      std::cerr << "Size is " << sz << " but is expected to be " << width
                << " * " << height << " * 2 + 6 (" << width * height * 2 + 6
                << ")" << std::endl;
      return 1;
    }
    sz -= 5;
  }
  std::string varName = makeVarName(ln.filename);
  // Byte swap the buffer
  // TODO: make this optional
  for (uint32_t i = 0; i < sz; i += 2) {
    uint8_t n1 = inBuf[i];
    uint8_t n0 = inBuf[i + 1];
    inBuf[i] = n0;
    inBuf[i + 1] = n1;
  }

  image_compression cmp = enc_and_dec(inBuf, sz);
  if (cmp == image_compression::INVALID) {
    std::cerr << "Failed to encode" << std::endl;
    return -1;
  }

  std::cout << "#include \"bitmap.h\"" << std::endl
            << std::endl
            << "// clang-format off" << std::endl
            << "uint8_t " << varName << "_data[] PROGMEM = {" << std::endl;
  // TODO: Spit out the actual encoding
  switch (cmp) {
    case image_compression::NQRLE:
      encode_rle(inBuf, sz, appendByteToOut);
      break;
    case image_compression::PAL_RAW:
      encode_pal(inBuf, sz, appendByteToOut);
      break;
    case image_compression::PAL_NQRLE:
      encode_prle(inBuf, sz, appendByteToOut);
      break;
    default:
      std::cout << "UNSUPPORTED TARGET FORMAT!" << std::endl;
  }
  std::cout << std::endl
            << "};" << std::endl
            << "// clang-format on" << std::endl
            << std::endl
            << "image_descriptor " << varName << " = {" << std::endl
            << "  .width = " << width << "," << std::endl
            << "  .height = " << height << "," << std::endl
            << "  .byte_count = " << outBuf.size() << "," << std::endl
            << "  .compression = image_compression::" << name(cmp)
            << ", " // TODO Update
            << std::endl
            << "  .image_data = " << varName << "_data" << std::endl
            << "}; // "
            << static_cast<float>(sz) / static_cast<float>(outBuf.size())
            << " compression rate" << std::endl;
  return 0;
}
