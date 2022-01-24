#include <stdint.h>

#include "bitmap.h"

// This file must compile both for Arduino and for Windows/Mac.
// That means be careful with the C++, unfortunately...

void decode_prle(const uint8_t* compressedStream,
                 uint32_t streamLength,
                 void (*send)(const uint8_t* buf, uint16_t len)) {
  return;
}
