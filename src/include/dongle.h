#pragma once

#include "sysstuff.h"

#if defined(HAS_DISPLAY)
#include <Adafruit_SSD1306.h>
#endif

#include <array>

class Dongle {

  static const uint32_t ScreenWidth = 128;
  static const uint32_t ScreenHeight = 32;
  static const uint8_t OledResetPin = 13;

  static uint32_t connect_time;
  static bool black;
  static Adafruit_NeoPixel neopix;
  static Adafruit_USBD_HID usb_hid;
  static uint16_t leftHandle;
  static uint16_t rightHandle;

 public:
#if defined(HAS_DISPLAY)
  static Adafruit_SSD1306 display;
#endif
  static BLEClientUart leftUart;
  static BLEClientUart rightUart;

  static void Configure();
  static void StartListening();
  static void Reset();
  static bool Ready();
  static bool BothSides();
  static void ReportKeys(uint8_t mods, uint8_t* report);
  static void ConsumerPress(uint16_t keycode);
  static void ConsumerRelease();

  static void setRGB(uint8_t r, uint8_t g, uint8_t b);
  static void setRGB(uint32_t rgb);
  static void setRed(bool on);
  static void setBlue(bool on);
  static void blinkRGB(uint8_t r, uint8_t g, uint8_t b, uint16_t length = 250);

  static void updateClientStatus(uint32_t now,
                                 uint8_t batLeft,
                                 uint8_t batRight);

  // Callbacks from the Bluefruit runtime
  static void cent_connect(uint16_t conn_handle);
  static void cent_disconnect(uint16_t conn_handle, uint8_t reason);
  static void scan(ble_gap_evt_adv_report_t* report);
  static void hid_report_callback(uint8_t report_id,
                                  hid_report_type_t report_type,
                                  uint8_t const* buffer,
                                  uint16_t bufsize);
  static void receive_callback(BLEClientUart& uart_svc);
};
