#if !defined(COMPRESSOR)
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdint.h>
#include "bitmap.h"

// Not-Quite-Run-Length-Encoding 16 bit decoder, with byte swapping

// This reads a unsigned integer value encoded with high "stop" bit
// which allows you to encode 0-127 in 1 byte, 128-16383 in 2 bytes, and
// 16384-2M in 3. For NQRLE, odd means "repeat" and even means "unique"
// so we can encode runs of 63 bytes in 1 byte, and runs of 8191 bytes in 2,
// which
uint32_t readStopBitNumber(const uint8_t* compressedStream, uint32_t* i) {
  uint32_t val = 0;
  uint8_t curByte = 0;
  uint32_t shift = 0;
  do {
    curByte = compressedStream[(*i)++];
    val = val | ((curByte & 0x7f) << shift);
    shift += 7;
  } while ((curByte & 0x80) == 0);
  return val;
}

void decode_nqrle16(const uint8_t* compressedStream,
                    uint32_t streamLength,
                    void (*send)(const uint8_t* buf, uint16_t len)) {
  const uint16_t bufSize = 1024;
  uint8_t buffer[1024];
  uint32_t offs = 0;
  for (uint32_t i = 0; i < streamLength;) {
    uint32_t length = readStopBitNumber(compressedStream, &i);
    uint8_t repeat = length % 2 == 1;
    length /= 2;
    if (repeat) {
      // repeat the next pair of bytes N times
      uint8_t byte1 = compressedStream[i++];
      uint8_t byte2 = compressedStream[i++];
      for (uint32_t j = 0; j < length; j++) {
        if (offs + j * 2 == bufSize) {
          send(buffer, offs + j * 2);
          offs = -(j * 2);
        }
        buffer[offs + j * 2] = byte2;
        buffer[offs + j * 2 + 1] = byte1;
      }
      offs += length * 2;
    } else {
      // copy the next N pair of bytes
      for (uint32_t j = 0; j < length; j++) {
        if (offs + j * 2 == bufSize) {
          send(buffer, offs + j * 2);
          offs = -(j * 2);
        }
        buffer[offs + j * 2 + 1] = compressedStream[i++];
        buffer[offs + j * 2] = compressedStream[i++];
      }
      offs += length * 2;
    }
  }
  if (offs) {
    send(buffer, offs);
  }
}

#if defined(COMPRESSOR)

/*
This should spit out the encoded source array
*/
void dumpCount(bool repeat, uint32_t count, void (*print)(uint8_t byte)) {
  if (count == 0 || count > UINT32_MAX / 2) {
    fprintf(stderr, "Derp\n");
    return;
  }
  // A count instruction is a number encoded with a high stop bit
  // The low bit is true if it's a repeat
  count = count * 2 + !!repeat;
  while (count) {
    uint8_t byte = count & 0x7f;
    count = count >> 7;
    print(byte | (count ? 0 : 0x80));
  }
}

uint16_t getVal(uint8_t* data, uint32_t pos) {
  return (data[pos] << 8) | data[pos + 1];
}

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool not_quite_rle_encode_16bit(uint8_t* data,
                                uint32_t bytes,
                                void (*print)(uint8_t byte)) {
  if (bytes & 1) {
    return false;
  }
  for (uint32_t pos = 0; pos < bytes;) {
    // First, check to see if this is unique, or dupe:
    uint16_t val = getVal(data, pos);
    if (pos + 2 == bytes) {
      // Special case last unique word
      dumpCount(false, 1, print);
      print(data[pos++]);
      print(data[pos++]);
      break;
    }
    uint16_t nxt = getVal(data, pos + 2);
    if (val == nxt) {
      // Scan forward to see how long the repeat goes
      uint32_t count = 2;
      while (pos + count * 2 < bytes) {
        nxt = getVal(data, pos + 2 * count);
        if (nxt != val) {
          break;
        } else {
          count++;
        }
      }
      // We've got the count, dump the sequence
      dumpCount(true, count, print);
      print(data[pos]);
      print(data[pos + 1]);
      pos += count * 2;
    } else {
      // Scan forward to see how long the uniqueness goes
      uint32_t count = 1;
      val = nxt;
      while (pos + count * 2 < bytes) {
        nxt = getVal(data, pos + 2 * count + 2);
        if (nxt == val) {
          break;
        }
        count++;
        val = nxt;
      }
      dumpCount(false, count, print);
      while (count--) {
        print(data[pos++]);
        print(data[pos++]);
      }
    }
  }
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