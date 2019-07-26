#include "hardware.h"
#include "boardio.h"
#include "debounce.h"

// Some globals used by each half
// The last time we reported the battery
uint32_t last_bat_time = 0;
constexpr uint8_t num_reads = 8;
uint8_t last_8_reads[num_reads] = {0};
int8_t cur_bat_loc = -1 - num_reads;

uint8_t readBattery(uint32_t now, uint8_t prev) {
  if (prev && now - last_bat_time <= 30000) {
    // There's a lot of variance in the reading, so no need to over-report it.
    return prev;
  }
  uint8_t bat_percentage = BoardIO::getBatteryPercent();
#if defined(DEBUG)
  dumpVal(bat_percentage, "Battery level: ");
#endif
  last_bat_time = now;
  cur_bat_loc++;
  uint8_t bounds = num_reads;
  if (cur_bat_loc < 0) {
    bounds = 8 + cur_bat_loc + 1;
    last_8_reads[bounds - 1] = bat_percentage;
  } else {
    cur_bat_loc = cur_bat_loc % bounds;
    last_8_reads[cur_bat_loc] = bat_percentage;
  }
  uint32_t total = 0;
  for (uint8_t i = 0; i < bounds; i++)
    total += last_8_reads[i];
  return total / bounds;
}

namespace state {

#if defined(DEBUG)
uint32_t scans_since_last_time = 0;
#endif

hw::hw(uint8_t bl) : switches(0), battery_level(bl) {}

#if !defined(USB_MASTER)
hw::hw(uint32_t now, const hw& prev, const BoardIO& pd)
    : switches(prev.switches),
      battery_level(readBattery(now, prev.battery_level)) {
  readSwitches(pd, now);
}
#endif

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

// Send the relevant data over the wire
void hw::send(BLEUart& bleuart, const hw& prev) const {
  bleuart.write((uint8_t*)&switches, sizeof(switches) + 1);
}
#endif

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
