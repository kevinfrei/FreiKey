#include "hardware.h"
#include "boardio.h"
#include "debounce.h"

namespace state {

// Some globals used by each half
// The last time we reported the battery
uint32_t last_bat_time = 0;
uint8_t last_8_reads[8] = {0};
int8_t cur_bat_loc = -9;

#if defined(DEBUG)
uint32_t scans_since_last_time = 0;
#endif

uint8_t readBattery(uint32_t now, uint8_t prev) {
  if (prev && now - last_bat_time <= 30000) {
    // There's a lot of variance in the reading, so no need to over-report it.
    return prev;
  }
  uint8_t bat_percentage = BoardIO::getBatteryPercent();
#if defined(DEBUG)
  dumpVal(bat_percentage, "Battery level: ");
  dumpVal(scans_since_last_time / ((now - last_bat_time) / 1000),
          "Scans/second: ~");
  scans_since_last_time = 0;
#endif
  last_bat_time = now;
  cur_bat_loc++;
  if (cur_bat_loc < 0) {
    // Don't average the reads until we have 8 of them.
    last_8_reads[8 - cur_bat_loc] = bat_percentage;
    return bat_percentage;
  }
  cur_bat_loc &= 7;
  last_8_reads[cur_bat_loc] = bat_percentage;
  uint32_t total = 0;
  for (uint8_t i = 0; i < 8; i++)
    total += last_8_reads[i];
  return total / 8;
}

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
