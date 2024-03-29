#pragma once

#include "sysstuff.h"
#include <queue>

#include "boardio.h"
#include "dbgcfg.h"
#include "debounce.h"

#if !defined(TEENSY)
constexpr const char* MANUFACTURER = "FreikyStuff";

#if defined(KARBON)
constexpr const char* MODEL = "Karbon";
constexpr const char* BT_NAME = "Karbon";
constexpr const char* HW_REV = "0001";
constexpr const char* LHS_NAME = "Karbon";
constexpr const char* LTCL_NAME = "Karbon-Left";
constexpr const char* RTCL_NAME = "Karbon-Right";
#elif defined(FREIKEYS)
constexpr const char* MODEL = "FreiKeyboard";
constexpr const char* BT_NAME = "FreiKeys";
constexpr const char* HW_REV = "0001";
constexpr const char* LHS_NAME = "FreiKeys-Slave";
constexpr const char* LTCL_NAME = "FreiKeys-LClient";
constexpr const char* RTCL_NAME = "FreiKeys-RClient";
#else
#error You need to create a bluetooth name setup
#endif

#if defined(BTLE_CLIENT)
#if defined(LEFT)
constexpr const char* BTLE_CLIENT_NAME = LTCL_NAME;
#elif defined(RIGHT)
constexpr const char* BTLE_CLIENT_NAME = RTCL_NAME;
#else
#error For a client build, you need to pick left or right
#endif
#endif
#endif

namespace state {
#if defined(BTLE_HOST)
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
  MatrixBits switches;
#if !defined(TEENSY)
  uint8_t battery_level;
#endif
  static constexpr std::size_t data_size = MatrixBits::num_bytes + 1;
  // This is just a dumb constructor
  hw(uint8_t bl = 0);

#if defined(BTLE_HOST)
  // This is for reading the data from remote pieces over the UART
  hw(BLEClientUart& clientUart, const hw& prev);
  // Try to receive any relevant switch data from the wire.
  // Returns true if something was received
  bool receive(BLEClientUart& clientUart, const hw& prev);
#else
  Debouncer<MatrixBits> debouncer;
  // This is for reading the data from the hardware
  hw(uint32_t now, const hw& prev);
  // Just reads the switches...
  void readSwitches(uint32_t now);
#endif

#if defined(BTLE_CLIENT)
  // Send the relevant data over the wire
  void send(BLEUart& bleuart, const hw& prev) const;
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
