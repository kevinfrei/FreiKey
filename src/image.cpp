#include "image.h"
#include "bitmap.h"
#include "dbgcfg.h"
#include <Adafruit_ST7789.h>

uint8_t* buffer = nullptr;
uint32_t curOffset = 0;

void append_bytes(bytestream buf, uint16_t bytes) {
  memcpy(&buffer[curOffset], buf, bytes);
  curOffset += bytes;
}

void drawImage(const image_descriptor* id,
               uint16_t x,
               uint16_t y,
               Adafruit_ST7789* tft) {
  uint32_t size = id->width * id->height * sizeof(uint16_t);
  buffer = (uint8_t*)malloc(size);
  if (buffer) {
    curOffset = 0;
    switch (id->compression) {
      case image_compression::NQRLE:
        decode_rle(id->image_data, id->byte_count, append_bytes);
        break;
      case image_compression::PAL_NQRLE:
        decode_prle(id->image_data, id->byte_count, append_bytes);
        break;
      case image_compression::PAL_RAW:
        decode_pal(id->image_data, id->byte_count, append_bytes);
        break;
      case image_compression::RAW:
        free(buffer);
        buffer = const_cast<uint8_t*>(id->image_data);
        break;
      default:
        break;
    }
    if (curOffset != size) {
      DBG(
        Serial.printf("Invalid output: Erp %d bytes instead of %d (from %d)\n",
                      curOffset,
                      size,
                      id->byte_count));
    } else {
      tft->drawRGBBitmap(x, y, (uint16_t*)buffer, id->width, id->height);
    }
    if (id->compression != image_compression::RAW) {
      free(buffer);
    }
  }
  buffer = nullptr;
  curOffset = 0;
}