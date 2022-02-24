#pragma once

#include <stdint.h>
#include <stdio.h>
#include <memory.h>

// General Arduino stuff
class SerialMock {
 public:
  void print(const char*);
  void print(uint32_t, int format = 0);
  void println(uint32_t, int format = 0);
  void println(const char* str = nullptr);
  void printf(const char*, ...);
  void begin(uint32_t bps);
  operator bool();
};
constexpr int HEX = 16;

extern SerialMock Serial;

void delayMicroseconds(uint32_t s);
void delay(uint32_t);
uint32_t millis();
uint32_t micros();

void digitalWrite(uint16_t pin, uint32_t val);
uint8_t digitalRead(uint16_t pin);
void pinMode(uint16_t pin, uint8_t mode);

void waitForEvent();

constexpr uint32_t HIGH = 255;
constexpr uint32_t LOW = 0;
constexpr uint8_t OUTPUT = 1;
constexpr uint8_t INPUT = 2;
constexpr uint8_t INPUT_PULLUP = 3;

// Board specific stuff (should eventually be moved)
constexpr uint16_t LED_BLUE = 1;
constexpr uint16_t LED_RED = 2;
constexpr uint16_t PIN_NEOPIXEL = 3;
constexpr uint16_t LED_BUILTIN = 4;
constexpr uint8_t KEYBOARD_LED_CAPSLOCK = 0x1;

// BluetoothLE/Bluefruit stuff
class ble_gap_evt_adv_report_t {};

class CentralMock {
 public:
  void setConnectCallback(void (*)(uint16_t));
  void setDisconnectCallback(void (*)(uint16_t, uint8_t));
  void connect(bool);
};
class ScannerMock {
 public:
  void setRxCallback(void (*)(ble_gap_evt_adv_report_t*));
  void restartOnDisconnect(bool);
  void setInterval(uint16_t, uint16_t);
  void filterUuid(const uint8_t*);
  void useActiveScan(bool);
  void start(uint8_t);
};
class ConnectionMock {
 public:
 void getPeerName(char *, size_t);
 void disconnect();
};
class BluefruitMock {
 public:
  void begin(uint32_t, uint32_t);
  void autoConnLed(bool);
  void setTxPower(uint8_t);
  void setName(const char*);
  void printInfo();
  ConnectionMock* Connection(uint16_t);
  CentralMock Central;
  ScannerMock Scanner;
};
extern BluefruitMock Bluefruit;

class BLEClientUart {
 public:
  void write(const char* buffer, size_t size);
  void write(char c);
  char read();
  void begin();
  void setRxCallback(void (*)(BLEClientUart&));
  void enableTXD();
  bool available();
  bool discover(uint16_t);
};

constexpr uint16_t BLE_CONN_HANDLE_INVALID = 0;
constexpr uint8_t BLEUART_UUID_SERVICE[] = {1, 2, 3, 4};

// NeoPixel
struct Adafruit_NeoPixel {
  int which;
  int pin;
  int dir;
  void begin();
  void setPixelColor(uint8_t, uint8_t, uint8_t, uint8_t);
  void show();
};
constexpr int NEO_GRB = 0;
constexpr int NEO_KHZ800 = 1;

// Tiny USB stuff
using hid_report_type_t = uint32_t;
constexpr hid_report_type_t HID_REPORT_TYPE_OUTPUT = 1;
struct Adafruit_USBD_HID {
  void setPollInterval(uint32_t);
  void setReportDescriptor(const uint8_t*, size_t);
  void begin();
  bool ready();
  void keyboardRelease(uint8_t);
  void keyboardReport(uint8_t, uint8_t, uint8_t*);
  void sendReport(uint8_t, uint16_t*, size_t);
  void setReportCallback(
      const char*,
      void (*func)(uint8_t, hid_report_type_t, const uint8_t*, uint16_t));
};
#define HID_REPORT_ID(a) a
#define TUD_HID_REPORT_DESC_KEYBOARD(...) __VA_ARGS__ '0'
#define TUD_HID_REPORT_DESC_CONSUMER(...) __VA_ARGS__ '1'

// GFX stuff
class WireMock {};
extern WireMock Wire;
class Adafruit_SSD1306 {
  public:
  Adafruit_SSD1306(uint16_t width, uint16_t height, void *, uint8_t resetPin);
  void begin(uint32_t, uint8_t);
  void display();
};
constexpr uint32_t SSD1306_SWITCHCAPVCC = 0;
#define SSD1306_LCDHEIGHT 32

// Teensy stuff
class KeyboardMock {
  public:
  void press(uint16_t);
  void release(uint16_t);
  void set_key1(uint8_t);
  void set_key2(uint8_t);
  void set_key3(uint8_t);
  void set_key4(uint8_t);
  void set_key5(uint8_t);
  void set_key6(uint8_t);
  void set_modifier(uint8_t);
  void send_now();
};
extern KeyboardMock Keyboard;
