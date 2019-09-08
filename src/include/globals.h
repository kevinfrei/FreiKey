#pragma once

#if !defined(USB_MASTER)
#include "sysstuff.h"

#include "sleepstate.h"
#endif

#include "hardware.h"

#if defined(UART_ONLY)

extern BLEBas battery;
extern uint16_t core_handle;
extern SleepState sleepState;

#endif

#if !defined(UART_ONLY)

void resetTheWorld();
extern state::hw leftSide;
extern state::hw rightSide;

#endif
