#include "image.h"
#include "bitmap.h"
#include "dbgcfg.h"
#include <Adafruit_ST7789.h>
// Note to self: Using the Adafruit_GFX header/display instead is *visibly*
// slower

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

uint16_t prevX = 0, prevWidth = 0, prevY = 0, prevHeight = 0;

constexpr uint8_t ST77XX_VSCRDEF = 0x33;
constexpr uint8_t ST77XX_VSCSAD = 0x37;
constexpr uint8_t hi(uint16_t a) {
  return (a >> 8) & 0xFF;
}
constexpr uint8_t lo(uint16_t a) {
  return a & 0xFF;
}
void ShowImage(Adafruit_ST7789* tft, const image_descriptor* img) {
  tft->fillRect(prevX, prevY, prevWidth, prevHeight, ST77XX_BLACK);
  uint16_t w = img->width;
  uint16_t h = img->height;
  uint16_t sw = tft->width();
  uint16_t sh = tft->height();
  prevX = ((sw - w) > 0) ? micros() % (sw - w + 1) : 0;
  prevY = ((sh - h) > 0) ? (sh * micros()) % (sh - h + 1) : 0;
  drawImage(img, prevX, prevY, tft);
  prevHeight = h;
  prevWidth = w;
#if false
  uint16_t TFA = 40, BFA = 40; // Top/Bottom Fixed Areas
  uint16_t VSA = 320 - TFA - BFA; // Vertical Scroll Area
  // TFA + VSA + BFA should == tft->height()
  uint8_t buf[6] = {
    hi(TFA), // Top Fixed Area high byte
    lo(TFA), // Top Fixed area low byte
    hi(VSA), // Vertial Scroll area high byte
    lo(VSA), // Vertical Scroll area low byte
    hi(BFA), // Bottom Fixed Area high byte
    lo(BFA), // Bottom Fixed Area low byte
  };
  tft->sendCommand(ST77XX_VSCRDEF, buf, 6);
  int16_t topLine = TFA + VSA;
  while (false) {
    // There's the ability to do "non-rolling" scrolling that I should look
    // into... See pkage 203 of the spec sheet for the 7789S
    uint8_t newTopLine[2] = {hi(topLine),
                             lo(topLine)}; // This should be between TFA
                                           // and BFA, big-endian
    tft->sendCommand(ST77XX_VSCSAD, newTopLine, 2);
    topLine--;
        if (topLine < TFA)
      topLine = TFA + VSA;
    yield();
    delay(16);
  }
#endif
}
