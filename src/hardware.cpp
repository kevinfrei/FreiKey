#include "hardware.h"
#include "boardio.h"
#include "debounce.h"
#include "battery.h"

namespace state {

#if defined(DEBUG)
uint32_t scans_since_last_time = 0;
#endif

hw::hw(uint8_t bl) : switches(0), battery_level(bl) {}

hw::hw(uint32_t now, const hw& prev, const BoardIO& pd)
    : switches(prev.switches),
      battery_level(readBattery(now, prev.battery_level)) {
  readSwitches(pd, now);
}

hw::hw(BLEClientUart& clientUart, const hw& prev) {
  if (!receive(clientUart, prev))
    memcpy(reinterpret_cast<uint8_t*>(this),
           reinterpret_cast<const uint8_t*>(&prev),
           sizeof(hw));
}

hw::hw(const hw& c) : switches(c.switches), battery_level(c.battery_level) {}

void hw::readSwitches(const BoardIO& pd, uint32_t now) {
#if defined(DEBUG)
  scans_since_last_time++;
#endif
  // Read & debounce the current key matrix
  this->switches = debounce(pd.Read(), now);
}

// Send the relevant data over the wire
void hw::send(BLEUart& bleuart, const hw& prev) const {
  bleuart.write((uint8_t*)&switches, sizeof(switches) + 1);
}

// Try to receive any relevant switch data from the wire.
// Returns true if something was received
bool hw::receive(BLEClientUart& clientUart, const hw& prev) {
  if (clientUart.available()) {
    uint8_t buffer[sizeof(switches) + 1];
    int size = clientUart.read(buffer, sizeof(switches) + 1);
    if (size == sizeof(switches) + 1) {
      memcpy(reinterpret_cast<uint8_t*>(this), buffer, sizeof(switches) + 1);
    } else {
#if defined(DEBUG)
      // NOTE: This fires occasionally when button mashing on the left, so
      // perhaps I shouldn't have changed this just on a whim. Wez clearly
      // knew what he was doing :)
      Serial.print("Incorrect datagram size:");
      Serial.print(" expected ");
      Serial.print(static_cast<uint8_t>(sizeof(hw)));
      Serial.print(" got ");
      Serial.println(size);
#endif
    }
    return true;
  }
  return false;
}

bool hw::operator==(const hw& o) const {
  return o.battery_level == battery_level && o.switches == switches;
}

bool hw::operator!=(const hw& o) const {
  return !((*this) == o);
}

#if defined(DEBUG)
void hw::dump() const {
  dumpVal(battery_level, "Battery Level:");
  dumpHex(switches, "Integer value: ");
  Serial.println("");
  for (int64_t r = 0; r < BoardIO::numrows; r++) {
    for (int64_t c = BoardIO::numcols - 1; c >= 0; c--) {
      uint64_t mask = 1ULL << (r * BoardIO::numcols + c);
      if (switches & mask) {
        Serial.print("X ");
      } else {
        Serial.print("- ");
      }
    }
    Serial.println("");
  }
}
#endif
} // namespace state

void rtos_idle_callback(void) {}
