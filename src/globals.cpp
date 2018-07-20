#include "globals.h"
#include "sleepstate.h"

// Global variables in need of instantiation

BLEDis dis;
BLEHidAdafruit hid;
BLEClientUart clientUart;
BLEBas battery;
uint16_t core_handle = 0xFFFF;
SleepState sleepState = {0, false, true};
