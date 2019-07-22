#include "hardware.h"
#include "battery.h"
#include "boardio.h"
#include "debounce.h"

namespace state {

#if defined(DEBUG)
uint32_t scans_since_last_time = 0;
#endif

hw::hw(uint8_t bl) : switches(0), battery_level(bl) {}

hw::hw(uint32_t now, const hw& prev, const BoardIO& pd)
    : switches(prev.switches),
      battery_level(readBattery(now, prev.battery_level)) {
#if !defined(USB_MASTER)
  readSwitches(pd, now);
#endif
}

hw::hw(BLEClientUart& clientUart, const hw& prev) {
  if (!receive(clientUart, prev))
    memcpy(reinterpret_cast<uint8_t*>(this),
           reinterpret_cast<const uint8_t*>(&prev),
           sizeof(hw));
}

hw::hw(const hw& c) : switches(c.switches), battery_level(c.battery_level) {}

#if !defined(USB_MASTER)
void hw::readSwitches(const BoardIO& pd, uint32_t now) {
#if defined(DEBUG)
  scans_since_last_time++;
#endif
  // Read & debounce the current key matrix
  this->switches = debounce(pd.Read(), now);
}
#endif

// Send the relevant data over the wire
void hw::send(BLEUart& bleuart, const hw& prev) const {
  bleuart.write((uint8_t*)&switches, sizeof(switches) + 1);
}

#if !defined(UART_CLIENT)
// Try to receive any relevant switch data from the wire.
// Returns true if something was received
bool hw::receive(BLEClientUart& clientUart, const hw& prev) {
  if (clientUart.available()) {
    uint8_t size = sizeof(switches) + 1;
    uint8_t buffer[size];
    uint8_t pos = 0;
    while (pos < size) {
      if (clientUart.available()) {
        buffer[pos++] = clientUart.read();
      } else {
        delayMicroseconds(25);
      }
    };
    memcpy(reinterpret_cast<uint8_t*>(this), buffer, size);
    return true;
  } else {
    return false;
  }
}
#endif

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
