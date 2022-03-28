#include <stdint.h>
#include <stdio.h>

#include "bitmap.h"

// Not-Quite-Run-Length-Encoding 16 bit decoder, with byte swapping

// This reads a unsigned integer value encoded with high "stop" bit
// which allows you to encode 0-127 in 1 byte, 128-16383 in 2 bytes, and
// 16384-2M in 3. For NQRLE, odd means "repeat" and even means "unique"
// so we can encode runs of 63 bytes in 1 byte, and runs of 8191 bytes in 2,
// which
uint32_t readStopBitNumber(bytestream cmpStrm, uint32_t* i) {
  uint32_t val = 0;
  uint8_t curByte = 0;
  uint32_t shift = 0;
  do {
    curByte = cmpStrm[(*i)++];
    val = val | ((curByte & 0x7f) << shift);
    shift += 7;
  } while ((curByte & 0x80) == 0);
  return val;
}

void decode_rle(bytestream cmpStrm, uint32_t strmLen, sender send) {
  const uint16_t bufSize = 1024;
  uint8_t buffer[1024];
  int32_t offs = 0;
  for (uint32_t i = 0; i < strmLen;) {
    uint32_t length = readStopBitNumber(cmpStrm, &i);
    bool repeat = length % 2 == 1;
    length /= 2;
    if (repeat) {
      // repeat the next pair of bytes N times
      uint8_t byte1 = cmpStrm[i++];
      uint8_t byte2 = cmpStrm[i++];
      for (uint32_t j = 0; j < length; j++) {
        if (offs + j * 2 == bufSize) {
          send(buffer, offs + j * 2);
          offs = -(j * 2);
        }
        buffer[offs + j * 2] = byte1;
        buffer[offs + j * 2 + 1] = byte2;
      }
      offs += length * 2;
    } else {
      // copy the next N pair of bytes
      for (uint32_t j = 0; j < length; j++) {
        if (offs + j * 2 == bufSize) {
          send(buffer, offs + j * 2);
          offs = -(j * 2);
        }
        buffer[offs + j * 2] = cmpStrm[i++];
        buffer[offs + j * 2 + 1] = cmpStrm[i++];
      }
      offs += length * 2;
    }
  }
  if (offs) {
    send(buffer, offs);
  }
}