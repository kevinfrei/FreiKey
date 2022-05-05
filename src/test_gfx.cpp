#include "Adafruit_GFX.h"
#include "Adafruit_GFX_Buffer.h"
#include "Adafruit_ST7789.h"

typedef Adafruit_ST7789 display_t;

#define BUFFER
// #define NORMAL
// #define ASYNC

constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RESET = 21;

#if defined(BUFFER)

typedef Adafruit_GFX_Buffer<display_t> GFXBuffer;
GFXBuffer display = GFXBuffer(240, 320, display_t(TFT_CS, TFT_DC, TFT_RESET));

uint8_t show() {
  return !!display.display();
}

#elif defined(NORMAL)

display_t display = display_t(TFT_CS, TFT_DC, TFT_RESET);

uint8_t show() {
  return 1;
}

#elif defined(ASYNC)

// TODO
// This is a completely different library. I'll need to build out a thin
// wrapper/abstraction layer so I can use the three things interchangeably

#else

#error Sorry: You need to define one of BUFFER, NORMAL, or ASYNC

#endif

extern "C" void setup() {
  while (!Serial) {
    delay(25);
  }
  Serial.begin(115200);
  display.init(240, 320);
  display.setSPISpeed(60000000);
  display.setRotation(1);
}

uint32_t totals = 0;
uint32_t start = 0;
float fps;
float time = 0.0f;

void drawDisplay() {
  display.fillScreen(0);
  for (uint8_t j = 0; j < 15; j++) {
    display.drawRect(display.width() / 2 - (60 + j * 2 + (totals & 0xf)),
                     display.height() / 2 - (60 + j / 2 + (totals & 0xf)),
                     2 * (40 + j * 3 + (totals & 0xf)),
                     2 * (30 + j / 3 + (totals & 0xf)),
                     0x8410 | ((totals + j) & 0xFFFF));

    display.drawLine(j,
                     j,
                     display.width() - j - 1,
                     display.height() - j - 1,
                     0xC618 | ((totals + j) & 0xFFFF));
    display.drawLine(j,
                     display.height() - j - 1,
                     display.width() - j - 1,
                     j,
                     0xC618 | ((totals + j) & 0xFFFF));
  }
  totals += show();
}

extern "C" void loop() {
  if (start == 0) {
    start = millis();
  }
  uint32_t before = micros();
  uint32_t beforeTotals = totals;
  drawDisplay();
  uint32_t after = micros();
  if (totals > beforeTotals) {
    time += after - before;
  }
  Serial.print(after - before);
  Serial.println(" microseconds elapsed");
  Serial.print(time / 1000000.0f);
  Serial.println(" total seconds elapsed");
  Serial.print(1000000.0f * static_cast<float>(totals) / time);
  Serial.println(" Frames per second");
}
