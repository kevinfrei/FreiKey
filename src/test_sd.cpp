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
  display.PWM1out(128);
  display.fillScreen(RA8875_GREEN);
  if (!SD.begin(SD_CS)) {
    display.fillRect(50, 50, 100, 100, RA8875_WHITE);
  } else {
    failed = false;
  }
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

void showDir(const ard::filesystem::path& p) {
  uint8_t count = 0;
  for (const ard::filesystem::directory_entry& de :
       ard::filesystem::directory_iterator(p)) {
    display.print(de.path().filename().c_str());
    if (de.is_directory()) {
      display.println(" <DIR>");
      if (de.path().filename().string().size() < 15)
        showDir(de.path());
    } else {
      display.print(":");
      display.print(de.file_size());
      ard::filesystem::file_time_type mod_time = de.last_write_time();
      display.print("|");
      printTime(mod_time);
      display.println();
    }
    if (++count > 3)
      break;
  }
}

extern "C" void loop() {
  if (Serial && !initSerial) {
    Serial.begin(115200);
    initSerial = true;
  }
  if (failed) {
    return;
  }
  showDir("/");
  /*
  File root = SD.open("/");
  printDir(root, 0);
  */
  failed = true;
}
