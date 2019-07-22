#include "globals.h"

// Global variables in need of instantiation

#if defined(USB_MASTER)
BLEClientUart leftUart;
BLEClientUart rightUart;
Adafruit_USBD_HID usb_hid;
Adafruit_NeoPixel neopix(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
uint16_t leftHandle = BLE_CONN_HANDLE_INVALID;
uint16_t rightHandle = BLE_CONN_HANDLE_INVALID;

#elif defined(BLUETOOTH_ONLY)
BLEClientUart clientUart;
BLEHidAdafruit hid;
BLEDis dis;
#endif
#if !defined(USB_MASTER)
BLEBas battery;
#endif
uint16_t core_handle = 0xFFFF;
SleepState sleepState = {0, false, true};
