#include "globals.h"

// Global variables in need of instantiation

#if defined(BLUETOOTH_ONLY)
BLEClientUart clientUart;
BLEHidAdafruit hid;
BLEDis dis;
#endif
#if !defined(USB_MASTER)
BLEBas battery;
uint16_t core_handle = 0xFFFF;
SleepState sleepState = {0, false, true};
#endif
