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
               uint8_t x,
               uint8_t y,
               Adafruit_ST7789* tft) {
  uint32_t size = id->width * id->height * sizeof(uint16_t);
  buffer = (uint8_t*)malloc(size);
  curOffset = 0;
  decode_rle(id->image_data, id->byte_count, append_bytes);
  if (curOffset != size) {
    DBG(Serial.printf("Invalid output: Erp %d bytes instead of %d (from %d)\n",
                      curOffset,
                      size,
                      id->byte_count));
  } else {
    tft->drawRGBBitmap(x, y, (uint16_t*)buffer, id->width, id->height);
  }
  free(buffer);
  buffer = nullptr;
  curOffset = 0;
}