#include "Adafruit_GFX.h"

// #define BUFFER
// #define NORMAL
#define ASYNC

constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RESET = 21;

#if defined(BUFFER)
#include "Adafruit_GFX_Buffer.h"
#include "Adafruit_ST7789.h"

typedef Adafruit_ST7789 display_t;

typedef Adafruit_GFX_Buffer<display_t> GFXBuffer;
GFXBuffer display = GFXBuffer(240, 320, display_t(TFT_CS, TFT_DC, TFT_RESET));

void configure() {
  display.setSPISpeed(60000000);
  display.setRotation(1);
    display.init(240, 320);

}

uint8_t show() {
  return !!display.display();
}

#elif defined(NORMAL)
#include "Adafruit_ST7789.h"

typedef Adafruit_ST7789 display_t;

display_t display = display_t(TFT_CS, TFT_DC, TFT_RESET);

void configure() {
  display.setSPISpeed(60000000);
  display.setRotation(1);
    display.init(240, 320);
}

uint8_t show() {
  return 1;
}

#elif defined(ASYNC)
#include "ST7789_t3.h"

typedef ST7789_t3 display_t;

display_t display = display_t(TFT_CS, TFT_CS, TFT_RESET);

void configure() {
  pinMode(TFT_RESET, OUTPUT);
  digitalWrite(TFT_RESET, LOW);  delay(1);
  digitalWrite(TFT_RESET, HIGH); delay(50);
  display.init(240, 320);
  display.fillScreen(ST77XX_BLUE);
  if (!display.useFrameBuffer(true)) {
    while (!Serial) {
      delay(25);
    }
    Serial.println("Frame Buffer creation failed");
    while (true) {
      delay(500);
    }
  } else {
    while (!Serial) {
      delay(25);
    }
    Serial.println("Use Frame Buffer succeeded!");
  }
}

uint8_t show() {
  if (display.updateScreenAsync()) {
    return 1;
  }
  while (!Serial) {
    delay(25);
  }
  Serial.print("updateScreenAsync failed: ");
  Serial.println(millis());
  return 0;
}

// TODO
// This is a completely different library. I'll need to build out a thin
// wrapper/abstraction layer so I can use the three things interchangeably

#else

#error Sorry: You need to define one of BUFFER, NORMAL, or ASYNC

#endif

bool initSerial = false;

extern "C" void setup() {
  if (Serial) {
    Serial.begin(115200);
    initSerial = true;
  }
  configure();
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
    display.drawLine(0,
                     j,
                     display.width() - j - 1,
                     display.height() - 1,
                     0xC618 | ((totals + j) & 0xFFFF));
    display.drawLine(j,
                     0,
                     display.width() - 1,
                     display.height() - j - 1,
                     0xC618 | ((totals + j) & 0xFFFF));
    display.drawLine(display.width() - j - 1,
                     0,
                     0,
                     display.height() - j - 1,
                     0xC618 | ((totals + j) & 0xFFFF));
    display.drawLine(display.width() - 1,
                     j,
                     j,
                     display.height() - 1,
                     0xC618 | ((totals + j) & 0xFFFF));
  }
  totals += show();
}

extern "C" void loop() {
  if (Serial && !initSerial) {
    Serial.begin(115200);
    initSerial = true;
  }
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
