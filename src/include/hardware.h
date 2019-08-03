#pragma once

#include "mybluefruit.h"

#include "boardio.h"
#include "dbgcfg.h"

using scancode_t = uint8_t;
constexpr scancode_t not_a_scancode = 0xff;

constexpr char* MANUFACTURER = "FreikyStuff";
constexpr char* MODEL = "FreiKeyboard";
constexpr char* BT_NAME = "FreiKeys";
constexpr char* HW_REV = "0001";
constexpr char* LHS_NAME = "FreiKeys-Slave";
constexpr char* LTCL_NAME = "FreiKeys-LClient";
constexpr char* RTCL_NAME = "FreiKeys-RClient";

namespace state {

// This struct is to encapsulate the complete hardware state, including both
// which switches are down, as well as the current battery level.
struct hw {
  BoardIO::bits switches;
  uint8_t battery_level;

  // This is just a dumb constructor
  hw(uint8_t bl = 0);

#if !defined(USB_MASTER)
  // This is for reading the data from the hardware
  hw(uint32_t now, const hw& prev, const BoardIO& pd);
#endif

  // This is for reading the data from the left hand side over the UART
  hw(BLEClientUart& clientUart, const hw& prev);

  // Generic copy constructor...
  hw(const hw& c);

#if !defined(USB_MASTER)
  // Just reads the switches...
  void readSwitches(const BoardIO& pd, uint32_t now);

  // Send the relevant data over the wire
  void send(BLEUart& bleuart, const hw& prev) const;
#endif

  // Try to receive any relevant switch data from the wire.
  // Returns true if something was received
  bool receive(BLEClientUart& clientUart, const hw& prev);

  bool operator==(const hw& o) const;
  bool operator!=(const hw& o) const;

// A little helper for serial port dumping...
#if defined(DEBUG)
  void dump() const;
#endif
};
} // namespace state

