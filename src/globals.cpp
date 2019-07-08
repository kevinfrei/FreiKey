#include "globals.h"

// Global variables in need of instantiation

#if defined(USB_MASTER)
BLEClientUart leftUart;
BLEClientUart rightUart;
Adafruit_USBD_HID usb_hid;
#elif defined(BLUETOOTH_ONLY)
BLEClientUart clientUart;
BLEHidAdafruit hid;
BLEDis dis;
#endif
BLEBas battery;
uint16_t core_handle = 0xFFFF;
SleepState sleepState = {0, false, true};
