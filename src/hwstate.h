#if !defined(HWSTATE_H)
#define HWSTATE_H

#include <bluefruit.h>

#include "dbgcfg.h"

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the physical pin numbers...

constexpr uint8_t colPins[] = {16, 15, 7, 11, 30, 27, 26, 25};
constexpr uint8_t rowPins[] = {2, 3, 4, 5, 28};
constexpr uint8_t numcols = sizeof(colPins) / sizeof(*colPins);
constexpr uint8_t numrows = sizeof(rowPins) / sizeof(*rowPins);

// A set of helpers for compilers/copying/clearing the switch-matrix array
namespace sw {
bool cmp(const uint8_t (&swa)[numrows], const uint8_t (&swb)[numrows]);
void cpy(uint8_t (&swdst)[numrows], const uint8_t (&swsrc)[numrows]);
void clr(uint8_t (&sw)[numrows]);
DBG(void dmp(const uint8_t (&sw)[numrows]));
} // namespace sw

// This struct is to encapsulate the complete hardware state, including both
// which switches are down, as well as the current battery level.
struct hwstate {
  uint8_t switches[numrows];
  uint8_t battery_level;

  // This is just a dump constructor
  hwstate(uint8_t bl = 0);
  // This is for reading the data from the hardware
  hwstate(uint32_t now, const hwstate& prev);
  // This is for reading the data from the left hand side over the UART
  hwstate(BLEClientUart& clientUart, const hwstate& prev);
  // Generic copy constructor...
  hwstate(const hwstate& c);
  // Just reads the switches...
  void readSwitches();
  // Send the relevant data over the wire
  void send(BLEUart& bleuart, const hwstate& prev) const;
  // Try to receive any relevant switch data from the wire.
  // Returns true if something was received
  bool receive(BLEClientUart& clientUart, const hwstate& prev);

  bool operator==(const hwstate& o) const;
  bool operator!=(const hwstate& o) const;
  // This converts the switch values to a single 64 bit uint.
  uint64_t toUI64() const;
  // A little helper for serial port dumping...
  DBG(void dump() const);
};

#endif
