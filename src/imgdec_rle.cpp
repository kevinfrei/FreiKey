#include <stdint.h>
#include <stdio.h>

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

void decode_rle(const uint8_t* compressedStream,
                uint32_t streamLength,
                void (*send)(const uint8_t* buf, uint16_t len)) {
  const uint16_t bufSize = 1024;
  uint8_t buffer[1024];
  uint32_t offs = 0;
  for (uint32_t i = 0; i < streamLength;) {
    uint32_t length = readStopBitNumber(compressedStream, &i);
    uint8_t repeat = length % 2 == 1;
    length /= 2;
    // fprintf(stderr, ">> %d (%s)\n", length, repeat ? "repeat" : "unique");
    if (repeat) {
      // repeat the next pair of bytes N times
      uint8_t byte1 = compressedStream[i++];
      uint8_t byte2 = compressedStream[i++];
      // fprintf(stderr, ">>> %02x %02x\n", (uint32_t)byte1, (uint32_t)byte2);
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
        /*
        fprintf(stderr,
                ">>> %02x %02x\n",
                (uint32_t)compressedStream[i],
                (uint32_t)compressedStream[i + 1]);
        */
        buffer[offs + j * 2] = compressedStream[i++];
        buffer[offs + j * 2 + 1] = compressedStream[i++];
      }
      offs += length * 2;
    }
  }
  if (offs) {
    send(buffer, offs);
  }
}