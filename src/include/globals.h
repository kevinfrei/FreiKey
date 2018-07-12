#if !defined(GLOBALS_H)
#define GLOBALS_H

#include <bluefruit.h>

#include "hardware.h"

extern BLEDis dis;
extern BLEHidAdafruit hid;
extern BLEClientUart clientUart;
extern BLEBas battery;

extern state::hw leftSide;
extern state::hw rightSide;

#endif
