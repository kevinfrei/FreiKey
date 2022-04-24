#include "Adafruit_GFX.h"
#include "Adafruit_GFX_Buffer.h"
#include "Adafruit_ST7789.h"

typedef Adafruit_ST7789 display_t;

#if 1
typedef Adafruit_GFX_Buffer<display_t> GFXBuffer;
GFXBuffer display = GFXBuffer(240, 320, display_t(10, 20, 21));
#define show() display.display()
#else
display_t display = display_t(10, 20, 21);
#define show() 1
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
