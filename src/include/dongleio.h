#if !defined(DONGLEIO_H)
#define DONGLEIO_H

#include "mybluefruit.h"

#include <array>

#include "Adafruit_NeoPixel.h"

class DongleIO {
  static uint32_t connect_time;
  static bool black;
  static Adafruit_NeoPixel neopix;

 public:
  static void Configure();
  static void setRGB(uint8_t r, uint8_t g, uint8_t b);
  static void setRed(bool on);
  static void setBlue(bool on);
  static void updateClientStatus();
  // Callbacks from the Bluefruit runtime
  static void cent_connect(uint16_t conn_handle);
  static void cent_disconnect(uint16_t conn_handle, uint8_t reason);
  static void scan(ble_gap_evt_adv_report_t* report);
  static void hid_report_callback(uint8_t report_id,
                                  hid_report_type_t report_type,
                                  uint8_t const* buffer,
                                  uint16_t bufsize);
  static void leftuart_rx_callback(BLEClientUart& uart_svc);
  static void rightuart_rx_callback(BLEClientUart& uart_svc);
};

#endif
