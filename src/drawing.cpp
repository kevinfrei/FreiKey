#include "sysstuff.h"

#include "dongle.h"
#include "drawing.h"

namespace drawing {

uint8_t encodeBatteryValue(uint8_t chargeRemaining,
                           bool isCharging,
                           bool isPresent) {
  return isPresent ? 0xFF : (chargeRemaining + (isCharging ? 100 : 0));
}

void drawBattery(uint8_t rate, uint8_t x, uint8_t y) {
  bool charge = (rate > 100);
  rate = rate - (charge ? 100 : 0);
  bool error = (rate > 100);
  Dongle::display.drawRect(x, y, 30, 18, WHITE);
  Dongle::display.drawRect(x + 30, y + 6, 2, 6, WHITE);
  if (!error) {
    Dongle::display.fillRect(x + 2, y + 2, 26 * rate / 100, 14, WHITE);
    if (charge) {
      for (uint32_t i = 0; i < 4; i++) {
        Dongle::display.drawFastHLine(
            x + 15 - i * 3, y + i + 4, i * 3 + 2, INVERSE);
        Dongle::display.drawFastHLine(x + 14, y - i + 12, i * 3 + 2, INVERSE);
      }
      // Draw the middle line
      // If I did this in the above loop, it has a few
      // double inversion pixels
      Dongle::display.drawFastHLine(x + 3, y + 8, 25, INVERSE);
    }
  } else {
    Dongle::display.setCursor(x + 6, y + 5);
    Dongle::display.setTextColor(INVERSE);
    Dongle::display.print("???");
  }
}

void drawWin(uint8_t x, uint8_t y) {
  Dongle::display.fillRect(x, y + 3, 5, 15, WHITE);
  Dongle::display.fillRect(x + 5, y + 2, 5, 17, WHITE);
  Dongle::display.fillRect(x + 11, y + 1, 5, 19, WHITE);
  Dongle::display.fillRect(x + 16, y, 5, 21, WHITE);
  Dongle::display.drawFastHLine(x, y + 10, 21, BLACK);
}

// clang-format off
constexpr uint8_t apple[] = {
  0b0000'0000, 0b0001'0000,
  0b0000'0000, 0b0011'0000,
  0b0000'0000, 0b0111'0000,
  0b0000'0000, 0b1110'0000,
  0b0000'0000, 0b1100'0000,
  0b0000'0000, 0b1100'0000,
  0b0000'0000, 0b1000'0000,
  0b0001'1110, 0b0011'1100,
  0b0011'1111, 0b1111'1110,
  0b0111'1111, 0b1111'1111,
  0b0111'1111, 0b1111'1110,
  0b1111'1111, 0b1111'1100,
  0b1111'1111, 0b1111'1100,
  0b1111'1111, 0b1111'1100,
  0b1111'1111, 0b1111'1100,
  0b0111'1111, 0b1111'1110,
  0b0111'1111, 0b1111'1111,
  0b0111'1111, 0b1111'1111,
  0b0011'1111, 0b1111'1111,
  0b0011'1111, 0b1111'1110,
  0b0001'1111, 0b1111'1110,
  0b0000'1110, 0b0011'1000,
};

constexpr uint8_t linux[] = {
  0b0000'0000, 0b0000'0000, 0b1110'0000,
  0b0000'0000, 0b0000'0001, 0b1111'0000,
  0b0000'0000, 0b0001'1101, 0b1111'0000,
  0b0000'0000, 0b0111'1101, 0b1111'0000,
  0b0000'0001, 0b1011'1100, 0b1110'0000,
  0b0000'0011, 0b1011'1110, 0b0000'0000,
  0b0000'0111, 0b1101'0011, 0b1111'0000,
  0b0000'0111, 0b1100'0000, 0b1111'0000,
  0b0111'0011, 0b1000'0000, 0b0111'1000,
  0b1111'1011, 0b0000'0000, 0b0111'1000,
  0b1111'1011, 0b0000'0000, 0b0000'0000,
  0b1111'1011, 0b0000'0000, 0b0111'1000,
  0b0111'0011, 0b1000'0000, 0b0111'1000,
  0b0000'0111, 0b1100'0000, 0b1111'0000,
  0b0000'0111, 0b1101'0011, 0b1111'0000,
  0b0000'0011, 0b1011'1110, 0b0000'0000,
  0b0000'0001, 0b1011'1100, 0b1110'0000,
  0b0000'0000, 0b0111'1101, 0b1111'0000,
  0b0000'0000, 0b0001'1101, 0b1111'0000,
  0b0000'0000, 0b0000'0001, 0b1111'0000,
  0b0000'0000, 0b0000'0000, 0b1110'0000,
};

constexpr uint8_t func[] = {
  0b0000'1100, 0b0000'0000,
  0b0001'1100, 0b0000'0000,
  0b0011'1000, 0b0000'0000,
  0b0011'0000, 0b0000'0000,
  0b0011'0000, 0b0000'0000,
  0b0011'0000, 0b0000'0000,
  0b0011'0000, 0b0000'0000,
  0b0011'0000, 0b0000'0000,
  0b1111'1101, 0b1011'1100,
  0b1111'1101, 0b1111'1110,
  0b0011'0001, 0b1110'0111,
  0b0011'0001, 0b1100'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
  0b0011'0001, 0b1000'0011,
};

constexpr uint8_t blueicon[] = {
  0b0000'0110, 0b0000'0000,
  0b0000'0111, 0b0000'0000,
  0b0000'0111, 0b1000'0000,
  0b0000'0110, 0b1100'0000,
  0b0110'0110, 0b0110'0000,
  0b0011'0110, 0b1100'0000,
  0b0001'1111, 0b1000'0000,
  0b0000'1111, 0b0000'0000,
  0b0001'1111, 0b1000'0000,
  0b0011'0110, 0b1100'0000,
  0b0110'0110, 0b0110'0000,
  0b0000'0110, 0b1100'0000,
  0b0000'0111, 0b1000'0000,
  0b0000'0111, 0b0000'0000,
  0b0000'0110, 0b0000'0000,
};

constexpr uint8_t noblue[] = {
  0b1100'0110, 0b0000'0000,
  0b1100'0111, 0b0000'0000,
  0b0110'0111, 0b1000'0000,
  0b0011'0110, 0b1100'0000,
  0b0111'1110, 0b0110'0000,
  0b0011'1110, 0b1100'0000,
  0b0001'1111, 0b1000'0000,
  0b0000'1111, 0b0000'0000,
  0b0001'1111, 0b1000'0000,
  0b0011'0111, 0b1100'0000,
  0b0110'0110, 0b1110'0000,
  0b0000'0110, 0b1100'0000,
  0b0000'0111, 0b1110'0000,
  0b0000'0111, 0b0011'0000,
  0b0000'0110, 0b0011'0000,
};

// clang-format on

struct layer {
  union {
    void (*render)(uint8_t x, uint8_t y);
    const uint8_t* buffer;
  };
  uint8_t w, h, xo, yo;

  layer(void (*r)(uint8_t x, uint8_t o))
      : render(r), w(0), h(0), xo(0), yo(0) {}
  layer(
      const uint8_t* buf, uint8_t w, uint8_t h, uint8_t xo = 0, uint8_t yo = 0)
      : buffer(buf), w(w), h(h), xo(xo), yo(yo) {}
  void draw(uint8_t x, uint8_t y) {
    if (w) {
      Dongle::display.drawBitmap(x + xo, y + yo, buffer, w, h, WHITE, BLACK);
    } else {
      render(x, y);
    }
  }
};

layer layers[] = {layer(&apple[0], 16, 21, 1),
                  layer(drawWin),
                  layer(&linux[0], 21, 21),
                  layer(&func[0], 16, 21),
                  layer(&blueicon[0], 12, 15),
                  layer(&noblue[0], 12, 15)};

void drawThing(Thing lyr, uint8_t x, uint8_t y) {
  layers[static_cast<size_t>(lyr)].draw(x, y);
}

/*void battery() {
  drawBattery(leftBattery, 0, 7);
  drawBattery(rightBattery, 96, 7);
}*/
} // namespace drawing
