#include "Adafruit_ST7789.h"
#include "SD.h"
#include <algorithm>
#include <cmath>

#include "ardfs.h"

constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 20;
constexpr uint8_t TFT_RESET = 21;
constexpr uint8_t SD_CS = 19;

typedef Adafruit_ST7789 display_t;

display_t display = display_t(TFT_CS, TFT_DC, TFT_RESET);
bool failed = true;
void configure() {
  display.setSPISpeed(60000000);
  display.init(240, 320);
  display.setRotation(1);
  display.fillScreen(0x3000);
  if (!SD.begin(SD_CS)) {
    display.fillRect(50, 50, 100, 100, 0xFF00);
  } else {
    failed = false;
  }
  display.setCursor(0, 7);
  display.setTextColor(0xFFFF);
}

bool initSerial = false;

extern "C" void setup() {
  if (Serial) {
    Serial.begin(115200);
    initSerial = true;
  }
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
    display.print('0');
  display.print(tm.hour);
  display.print(':');
  if (tm.min < 10)
    display.print('0');
  display.print(tm.min);
  display.print(' ');
  display.print(tm.mday);
  display.print(' ');
  display.print(tm.mon < 12 ? months[tm.mon] : "?*?");
  display.print(' ');
  display.print((tm.year + 1900) % 100);
}

void printDir(File dir, int numSpaces) {
  for (File entry = dir.openNextFile(); entry; entry = dir.openNextFile()) {
    // printSpaces(numSpaces);
    display.print(entry.name());
    if (entry.isDirectory()) {
      display.println("/");
      // printDir(entry, numSpaces + 2);
    } else {
      // files have sizes, directories do not
      unsigned int n = log10(entry.size());
      if (n > 10)
        n = 10;
      // printSpaces(50 - numSpaces - strlen(entry.name()) - n);
      display.print(": ");
      display.print(entry.size(), DEC);
      DateTimeFields datetime;
      if (entry.getModifyTime(datetime)) {
        display.print(" (");
        printTime(datetime);
        display.print(")");
      }
      display.println("");
    }
    entry.close();
  }
}

unsigned short toUpcase(uint16_t v) {
  return toupper(v);
}

extern "C" void loop() {
  if (Serial && !initSerial) {
    Serial.begin(115200);
    initSerial = true;
  }
  if (failed) {
    return;
  }
  for (const ard::filesystem::directory_entry& de :
       ard::filesystem::directory_iterator("/")) {
    display.print(de.path().c_str());
    if (de.is_directory()) {
      display.println(" <DIR>");
    } else {
      display.print(": ");
      display.print(de.file_size());
      ard::filesystem::file_time_type mod_time = de.last_write_time();
      display.print(" (");
      printTime(mod_time);
      display.println(")");
    }
  }
  /*
  File root = SD.open("/");
  printDir(root, 0);
  */
  failed = true;
}
