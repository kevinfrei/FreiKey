#if !defined(STATE_HARDWARE_H)
#define STATE_HARDWARE_H

#include <bluefruit.h>

#include "dbgcfg.h"

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the physical pin numbers...
constexpr uint64_t numcols = 7;
constexpr uint64_t numrows = 6;
struct PinData {
  uint8_t cols[numcols];
  uint8_t rows[numrows];
  uint8_t led;
};
constexpr PinData LeftPins = {
    {15, 2, 16, 7, 30, 27, 11}, {5, 12, 13, 28, 4, 3}, 29};
constexpr PinData RightPins = {
    {29, 16, 15, 7, 27, 11, 30}, {13, 4, 2, 3, 5, 12}, 28};

namespace state {
// This struct is to encapsulate the complete hardware state, including both
// which switches are down, as well as the current battery level.
struct hw {
  uint64_t switches;
  uint8_t battery_level;

  // This is just a dump constructor
  hw(uint8_t bl = 0);

  // This is for reading the data from the hardware
  hw(uint32_t now, const hw& prev, const PinData& pd);

  // This is for reading the data from the left hand side over the UART
  hw(BLEClientUart& clientUart, const hw& prev);

  // Generic copy constructor...
  hw(const hw& c);

  // Just reads the switches...
  void readSwitches(const PinData& pd);

  // Send the relevant data over the wire
  void send(BLEUart& bleuart, const hw& prev) const;

  // Try to receive any relevant switch data from the wire.
  // Returns true if something was received
  bool receive(BLEClientUart& clientUart, const hw& prev);

  bool operator==(const hw& o) const;
  bool operator!=(const hw& o) const;

  // A little helper for serial port dumping...
  DBG(void dump() const);
};
} // namespace state
#endif
