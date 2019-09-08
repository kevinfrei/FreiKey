#include "globals.h"

// Global variables in need of instantiation

#if defined(UART_ONLY)
BLEBas battery;
uint16_t core_handle = 0xFFFF;
SleepState sleepState = {0, false, true};
#endif
