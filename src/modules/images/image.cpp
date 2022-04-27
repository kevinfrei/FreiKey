#include "image.h"
#include "bitmap.h"
#include "dbgcfg.h"
#include <Adafruit_ST7789.h>
#include <cmath>
#include <vector>

// Note to self: Using the Adafruit_GFX header/display instead is *visibly*
// slower

uint8_t interp(
  double dx, double dy, uint8_t lu, uint8_t ru, uint8_t ld, uint8_t rd) {
  // use the relative distances to decide this color value
  double u = (1 - dx) * lu + dx * ru;
  double l = (1 - dx) * ld + dx * rd;
  double v = (1 - dy) * u + dy * l;
  return static_cast<uint8_t>(v + 0.5);
}

uint16_t rgb16(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0x1F) << 11) | ((g & 0x3f) << 5) | (b & 0x1f);
}

uint16_t getp(const std::vector<uint16_t>& pixels,
              uint16_t x,
              uint16_t y,
              uint16_t w,
              uint8_t def) {
  size_t pos = y * w + x;
  return ((x >= w) || (pos >= pixels.size())) ? def : pixels[pos];
}

uint8_t getr(const std::vector<uint16_t>& pixels,
             uint16_t x,
             uint16_t y,
             uint16_t w,
             uint8_t def = 0) {
  return 0x1f & (getp(pixels, x, y, w, def) >> 11);
}

uint8_t getg(const std::vector<uint16_t>& pixels,
             uint16_t x,
             uint16_t y,
             uint16_t w,
             uint8_t def = 0) {
  return 0x3f & (getp(pixels, x, y, w, def) >> 5);
}

uint8_t getb(const std::vector<uint16_t>& pixels,
             uint16_t x,
             uint16_t y,
             uint16_t w,
             uint8_t def = 0) {
  return 0x1f & getp(pixels, x, y, w, def);
}

std::vector<uint16_t> bilinearExpand(const std::vector<uint16_t>& pixels,
                                     uint16_t srcw,
                                     uint16_t srch,
                                     uint16_t dstw,
                                     uint16_t dsth) {
  if (dstw == 0) {
    dstw = srcw * dsth / srch;
  } else if (dsth == 0) {
    dsth = srch * dstw / srcw;
  }
  if (dstw < srcw || dsth < srch) {
    return pixels;
  }
  std::vector<uint16_t> res;
  res.reserve(dstw * dsth);
  double dw = dstw, sw = srcw, dh = dsth, sh = srch;
  for (uint16_t y = 0; y < dsth; y++) {
    double yd = y * sh / dh;
    uint16_t yo = static_cast<uint16_t>(std::floor(yd) + 0.01);
    double dy = yd - yo;
    for (uint16_t x = 0; x < dstw; x++) {
      double xd = x * sw / dw;
      uint16_t xo = static_cast<uint16_t>(std::floor(xd) + 0.01);
      double dx = xd - xo;
      // Linear interpolation is pretty easy:
      uint8_t rul = getr(pixels, xo, yo, srcw);
      uint8_t gul = getg(pixels, xo, yo, srcw);
      uint8_t bul = getb(pixels, xo, yo, srcw);
      uint8_t rur = getr(pixels, xo + 1, yo, srcw, rul);
      uint8_t gur = getg(pixels, xo + 1, yo, srcw, gul);
      uint8_t bur = getb(pixels, xo + 1, yo, srcw, bul);
      uint8_t rll = getr(pixels, xo, yo + 1, srcw, rul);
      uint8_t gll = getg(pixels, xo, yo + 1, srcw, gul);
      uint8_t bll = getb(pixels, xo, yo + 1, srcw, bul);
      uint8_t rlr = getr(pixels, xo + 1, yo + 1, srcw, rul);
      uint8_t glr = getg(pixels, xo + 1, yo + 1, srcw, gul);
      uint8_t blr = getb(pixels, xo + 1, yo + 1, srcw, bul);
      uint8_t r = interp(dx, dy, rul, rur, rll, rlr);
      uint8_t g = interp(dx, dy, gul, gur, gll, glr);
      uint8_t b = interp(dx, dy, bul, bur, bll, blr);
      res.push_back(rgb16(r, g, b));
    }
  }
  return res;
}

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
