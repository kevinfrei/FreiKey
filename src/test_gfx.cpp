#include "Adafruit_GFX.h"
#include <SPI.h>
#include <algorithm>

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

bool shouldDraw() {
  return true;
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

bool shouldDraw() {
  return true;
}

#elif defined(ASYNC)
#include "ST7735_t3.h"
#include "ST7789_t3.h"

SPISettings settings(60000000, MSBFIRST, SPI_MODE0);

typedef ST7789_t3 display_t;

display_t display = display_t(TFT_CS, TFT_DC, TFT_RESET);

void configure() {
  pinMode(TFT_RESET, OUTPUT);
  digitalWrite(TFT_RESET, LOW);
  delay(1);
  digitalWrite(TFT_RESET, HIGH);
  delay(50);
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
    /*while (!Serial) {
      delay(25);
    }*/
    Serial.println("Use Frame Buffer succeeded!");
  }
}

uint32_t reported = 0;

uint8_t show() {
  return display.updateScreenAsync();
}

bool shouldDraw() {
  return !display.asyncUpdateActive();
}
// TODO
// This is a completely different library. I'll need to build out a thin
// wrapper/abstraction layer so I can use the three things interchangeably

#else

#error Sorry: You need to define one of BUFFER, NORMAL, or ASYNC

#endif

bool initSerial = false;

uint16_t color(uint16_t angle) {
  byte red, green, blue;
  angle = angle % 360;
  if (angle < 60) {
    red = 255;
    green = round(angle * 4.25 - 0.01);
    blue = 0;
  } else if (angle < 120) {
    red = round((120 - angle) * 4.25 - 0.01);
    green = 255;
    blue = 0;
  } else if (angle < 180) {
    red = 0, green = 255;
    blue = round((angle - 120) * 4.25 - 0.01);
  } else if (angle < 240) {
    red = 0, green = round((240 - angle) * 4.25 - 0.01);
    blue = 255;
  } else if (angle < 300) {
    red = round((angle - 240) * 4.25 - 0.01), green = 0;
    blue = 255;
  } else {
    red = 255, green = 0;
    blue = round((360 - angle) * 4.25 - 0.01);
  }
  return ((red << 8) & 0xF800) | ((green << 3) & 0x07E0) | (blue >> 3);
}

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
uint16_t angle = 0;
uint32_t elapsed = 0;

uint16_t getColor(uint8_t ofs) {
  if (millis() - elapsed > 2) {
    angle = (angle + 1) % 360;
    elapsed = millis();
  }
  return color(angle + ofs * 3);
}

void drawDisplay() {
  display.fillScreen(0);
  for (uint8_t j = 0; j < std::min(display.height(), display.width()) / 3;
       j++) {
    uint8_t sz =
      25 + j + ((totals & 31) < 16 ? (totals & 31) : 31 - (totals & 31));
    display.drawCircle(
      display.width() / 2, display.height() / 2, sz, getColor(j + 32));
    display.drawLine(
      0, j, display.width() - j - 1, display.height() - 1, getColor(j));
    display.drawLine(
      j, 0, display.width() - 1, display.height() - j - 1, getColor(j));
    display.drawLine(
      display.width() - j - 1, 0, 0, display.height() - j - 1, getColor(j));
    display.drawLine(
      display.width() - 1, j, j, display.height() - 1, getColor(j));
  }
  totals += show();
}

uint32_t count = 0;

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
  if (shouldDraw()) {
    drawDisplay();
    uint32_t after = micros();
    if (totals > beforeTotals) {
      time += after - before;
    }
    if (/*count < 5 &&*/ Serial) {
      Serial.print(after - before);
      Serial.println(" microseconds elapsed");
      Serial.print(time / 1000000.0f);
      Serial.println(" total seconds elapsed");
      Serial.print(1000000.0f * static_cast<float>(totals) / time);
      Serial.println(" Frames per second");
      count++;
    }
  }
}
