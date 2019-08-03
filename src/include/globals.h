#pragma once

#if !defined(USB_MASTER)
#include "mybluefruit.h"

#include "sleepstate.h"
#endif

#include "hardware.h"

#if defined(BLUETOOTH_ONLY)

extern BLEClientUart clientUart;
extern BLEDis dis;
extern BLEHidAdafruit hid;

#endif

#if !defined(USB_MASTER)

extern BLEBas battery;
extern uint16_t core_handle;
extern SleepState sleepState;

#endif

#if !defined(UART_ONLY)

void resetTheWorld();
extern state::hw leftSide;
extern state::hw rightSide;

#endif
