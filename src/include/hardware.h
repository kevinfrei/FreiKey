#pragma once

#include "sysstuff.h"
#include <queue>

#include "boardio.h"
#include "dbgcfg.h"

using scancode_t = uint8_t;
constexpr scancode_t null_scan_code = 0xff;
constexpr uint16_t null_consumer_code = 0x8000;

#if defined(ADAFRUIT)
constexpr const char* MANUFACTURER = "FreikyStuff";
constexpr const char* MODEL = "FreiKeyboard";
constexpr const char* BT_NAME = "FreiKeys";
constexpr const char* HW_REV = "0001";
constexpr const char* LHS_NAME = "FreiKeys-Slave";
constexpr const char* LTCL_NAME = "FreiKeys-LClient";
constexpr const char* RTCL_NAME = "FreiKeys-RClient";
#endif

namespace state {
#if defined(USB_MASTER)
struct incoming {
  BLEClientUart* which;
  // TODO: Tag it with 'when' to synchronize the sides better
  struct hw* what;
};
extern std::queue<incoming> data_queue;
#endif

// This struct is to encapsulate the complete hardware state, including both
// which switches are down, as well as the current battery level.
struct hw {
  BoardIO::bits switches;
#if !defined(TEENSY)
  uint8_t battery_level;
#endif
  static constexpr std::size_t data_size = BoardIO::byte_size + 1;
  // This is just a dumb constructor
  hw(uint8_t bl = 0);

#if !defined(USB_MASTER)
  // This is for reading the data from the hardware
  hw(uint32_t now, const hw& prev, const BoardIO& pd);
#endif
#if defined(UART_CLIENT)
  // Send the relevant data over the wire
  void send(BLEUart& bleuart, const hw& prev) const;
#endif

#if defined(USB_MASTER)
  // This is for reading the data from remote pieces over the UART
  hw(BLEClientUart& clientUart, const hw& prev);
  // Try to receive any relevant switch data from the wire.
  // Returns true if something was received
  bool receive(BLEClientUart& clientUart, const hw& prev);
#else
  // Just reads the switches...
  void readSwitches(const BoardIO& pd, uint32_t now);
#endif

  // Generic copy constructor...
  hw(const hw& c);

  bool operator==(const hw& o) const;
  bool operator!=(const hw& o) const;

// A little helper for serial port dumping...
#if defined(DEBUG)
  void dump() const;
#endif
};
} // namespace state
