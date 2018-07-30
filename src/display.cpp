#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#include "disp_uart.h"

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// uint32_t lastMillis = 0, maxMillis = 0, minMillis = 9999999999;
// uint64_t totalMillis = 0, countMillis = 0;
Adafruit_SSD1306 display = Adafruit_SSD1306();

void setup() {
  Serial.begin(115200);

  Serial.println("OLED FeatherWing test");
  // initialize with the I2C addr 0x3C (for the 128x32 OLED)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // init done
  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // display.display();
  // delay(100);

  // Clear the buffer.
  display.clearDisplay();
  display.fillRect(0,0,128,32,WHITE);
  display.display(); // actually display all of the above
}

void showValue(uint32_t val, uint16_t y) {
  for (uint16_t x = 0; x < 32; x++) {
    display.drawPixel(x, y, (val & (1 << x)) ? WHITE : BLACK);
  }
}

// Design:
uint8_t count = 0;
uint32_t lastFrameRender = 0;
constexpr uint32_t renderTime = 100;

void loop() {
  // return;
  uint32_t time = millis();
  if (time - lastFrameRender < renderTime) {
    delay(renderTime + lastFrameRender - time - 1);
    return;
  }
  lastFrameRender = time;
  display.clearDisplay();
  if (false) {
    /*   display.setTextSize(1);
       display.setTextColor(WHITE);
       display.setCursor(0, 1);
       uint32_t avg = totalMillis / countMillis;
       display.print(avg);
       display.print(" + ");
       display.print(maxMillis - avg);
       display.print(" - ");
       display.println(avg - minMillis);
  */
  }
  disp_uart::drawBattery(count, 0, 2);
  disp_uart::drawLayer((count / 50) % 5, 37, 0);
  disp_uart::drawLayer((count / 40 + 57) % 5, 66, 0);
  disp_uart::drawBattery(count * 4, 96, 2);
  count++;
  display.display();
  // yield();
}
