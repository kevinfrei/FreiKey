#include "Adafruit_RA8875.h"
#include "SD.h"
#include <algorithm>
#include <cmath>

#include "ardfs.h"

constexpr uint8_t RA8875_CS = 10;
constexpr uint8_t RA8875_RESET = 0;
constexpr uint8_t SD_CS = BUILTIN_SDCARD;

typedef Adafruit_RA8875 display_t;

display_t display = display_t(RA8875_CS, RA8875_RESET);

bool failed = true;

void configure() {
  if (!display.begin(RA8875_800x480)) {
    Serial.println("RA8875 Not Found!");
    while (1) {
    }
  }
  display.displayOn(true);
  display.touchEnable(false);
  display.GPIOX(true); // Enable TFT - display enable tied to GPIOX
  display.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  display.PWM1out(255);
  display.fillScreen(RA8875_GREEN);
  if (!SD.begin(SD_CS)) {
    display.fillRect(50, 50, 100, 100, RA8875_WHITE);
  } else {
    failed = false;
  }
}

bool initSerial = false;

extern "C" void setup() {
  while (!Serial) {
    delay(10);
  }
  Serial.begin(115200);
  initSerial = true;

  configure();
}

const char* months[12] = {"Jan",
                          "Feb",
                          "Mar",
                          "Apr",
                          "May",
                          "Jun",
                          "Jul",
                          "Aug",
                          "Sep",
                          "Oct",
                          "Nov",
                          "Dec"};

void printTime(const DateTimeFields tm) {
  if (tm.hour < 10)
    Serial.print('0');
  Serial.print(tm.hour);
  Serial.print(':');
  if (tm.min < 10)
    Serial.print('0');
  Serial.print(tm.min);
  Serial.print(' ');
  if (tm.mday < 10)
    Serial.print('0');
  Serial.print(tm.mday);
  Serial.print(' ');
  Serial.print(tm.mon < 12 ? months[tm.mon] : "?*?");
  Serial.print(' ');
  if ((tm.year + 1900) % 100 < 10)
    Serial.print('0');
  Serial.print((tm.year + 1900) % 100);
}

void printNum(std::uintmax_t val) {
  char buffer[16];
  int pos = 15;
  buffer[pos--] = 0;
  int dig = 0;
  do {
    buffer[pos--] = '0' + (val % 10);
    val /= 10;
    if (dig == 2 && pos >= 0) {
      buffer[pos--] = ',';
      dig = 0;
    } else {
      dig++;
    }
  } while (val != 0 && pos >= 0);
  if (buffer[pos + 1] == ',') {
    pos++;
  }
  while (pos >= 0) {
    buffer[pos--] = ' ';
  }
  Serial.print(&buffer[0]);
}

void printDir(File dir, int numSpaces) {
  for (File entry = dir.openNextFile(); entry; entry = dir.openNextFile()) {
    // printSpaces(numSpaces);
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      // printDir(entry, numSpaces + 2);
    } else {
      // files have sizes, directories do not
      unsigned int n = log10(entry.size());
      if (n > 10)
        n = 10;
      // printSpaces(50 - numSpaces - strlen(entry.name()) - n);
      Serial.print(": ");
      Serial.print(entry.size(), DEC);
      DateTimeFields datetime;
      if (entry.getModifyTime(datetime)) {
        Serial.print(" (");
        printTime(datetime);
        Serial.print(")");
      }
      Serial.println("");
    }
    entry.close();
  }
}

unsigned short toUpcase(uint16_t v) {
  return toupper(v);
}

void showDir(const ard::filesystem::path& p) {
  uint8_t count = 0;
  Serial.print("Showing Directory: ");
  Serial.println(p.c_str());
  for (const ard::filesystem::directory_entry& de :
       ard::filesystem::directory_iterator(p)) {
    // First, the date & size or <DIR>
    if (de.is_directory()) {
      Serial.print("                           <DIR> | ");
      Serial.println(de.path().filename().c_str());
      showDir(de.path());
    } else {
      ard::filesystem::file_time_type mod_time = de.last_write_time();
      printTime(mod_time);
      Serial.print("  ");
      printNum(de.file_size());
      Serial.print(" | ");
      Serial.println(de.path().filename().c_str());
    }
  }
}

float fclamp(float a) {
  return (a < 0.0f) ? 0.0f : (a > 1.0f) ? 1.0f : a;
}

uint16_t calcHue(float hue, float br) {
  // vec3 rgb = clamp(abs(mod(hue*6.0+vec3(0,4,2),6) - 3) - 1, 0, 1);
  float r = fclamp(fabsf(fmodf(hue * 6.0f + 0.0f, 6.0f) - 3.0f) - 1.0f);
  float g = fclamp(fabsf(fmodf(hue * 6.0f + 4.0f, 6.0f) - 3.0f) - 1.0f);
  float b = fclamp(fabsf(fmodf(hue * 6.0f + 2.0f, 6.0f) - 3.0f) - 1.0f);
  r = r * r * r * (r * (r * 6.0f - 15.0f) + 10.0f);
  g = g * g * g * (g * (g * 6.0f - 15.0f) + 10.0f);
  b = b * b * b * (b * (b * 6.0f - 15.0f) + 10.0f);
  uint16_t redPart = 31 * r * br;
  uint16_t grnPart = 31 * g * br;
  uint16_t bluPart = 31 * b * br;
  grnPart = ((grnPart >> 2) << 3) | (grnPart & 3);
  return (redPart << 11) | (grnPart << 5) | bluPart;
}

uint16_t color(uint16_t angle, uint8_t br) {
  return calcHue(static_cast<float>(angle) / 359.0f,
                 static_cast<float>(br) / 255.0f);
}

uint16_t fixGreen(uint8_t g) {
  return (((g >> 2) << 3) | (g & 3)) << 5;
}

void drawThing1() {
  /*
  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 33; x++) {
      display.fillRect(
        x * 800 / 33, y * 480 / 32, 1 + 800 / 33, 1 + 480 / 32, (x + y) << 5);
    }
  }
  */
  for (int i = 0; i < 480; i++) {
    display.drawRect(
      i, i, (800 - i * 3 / 2), (480 - i * 3 / 2), color(i % 360, 255));
  }
}

void drawThing2() {
  for (int i = 0; i < 480; i++) {
    display.drawRect(
      i, i, (800 - i * 2), (480 - i * 2), color((479 - i) % 360, 191));
  }
}

uint32_t last = 0;
uint32_t count = 0;
bool shown = false;
// This was fun to slowly reverse engineer...
// uint16_t greenVals[] = {0, 4, 1, 5, 2, 6, 3, 7};
extern "C" void loop() {
  if (failed) {
    Serial.println("Failed, so not trying...");
  }
  if (!shown) {
    // showDir("/");
    drawThing1();
  } else {
    drawThing2();
  }
  shown = !shown;
  /*
  File root = SD.open("/");
  printDir(root, 0);
  */
}