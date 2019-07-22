#if !defined(GLOBALS_H)
#define GLOBALS_H

#include "mybluefruit.h"

#if defined(USB_MASTER)
#include "Adafruit_TinyUSB.h"
#include "Adafruit_NeoPixel.h"
#endif

#include "sleepstate.h"
#include "hardware.h"

#if defined(USB_MASTER)
extern BLEClientUart leftUart;
extern BLEClientUart rightUart;
extern Adafruit_USBD_HID usb_hid;
extern Adafruit_NeoPixel neopix;
extern uint16_t leftHandle, rightHandle;

#elif defined(BLUETOOTH_ONLY)
extern BLEClientUart clientUart;
extern BLEDis dis;
extern BLEHidAdafruit hid;

#endif
#if !defined(USB_MASTER)
extern BLEBas battery;
#endif

extern state::hw leftSide;
extern state::hw rightSide;

extern uint16_t core_handle;
extern SleepState sleepState;

#endif
