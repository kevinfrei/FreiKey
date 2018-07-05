#include "hardware.h"
#include "pindata.h"

namespace state {
// pin 31 is available for sampling the battery
constexpr uint8_t VBAT_PIN = 31;

// 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
constexpr uint32_t VBAT_NUM = 3000;
constexpr uint32_t VBAT_DEN = 4096;

// Some globals used by each half
// The last time we reported the battery
uint32_t last_bat_time = 0;
uint32_t scans_since_last_time = 0;

// The last set of switches we reported
uint64_t last_reported_switches = 0;
// This is just the set of report times for switches
uint32_t last_reported_time[PinData::matrix_size];
// This is the # of msec to delay after reporting a change before reporting
// another one. Rumor has it that Cherry claims a debounce period of 5ms, but
// I still sometimes see a bounce or two, so I've increased it a bit.
constexpr uint8_t debounce_delay = 12;

void shared_setup(const PinData& pd) {
  static_assert(
      PinData::matrix_size <= 64,
      "Pervasive assumptions that the switch matrix fits in 64 bits.");

  analogReference(AR_INTERNAL_3_0);
  analogReadResolution(12);
  delay(1);

  // For my wiring, the columns are output, and the rows are input...
  for (auto pin : pd.cols) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  for (auto pin : pd.rows) {
    pinMode(pin, INPUT_PULLUP);
  }
  pinMode(pd.led, OUTPUT);

  analogWrite(pd.led, 0);
  DBG(Serial.begin(115200));
  memset(&last_reported_time[0], 0, sizeof(uint32_t) * PinData::matrix_size);
}

uint8_t getBatteryPercent() {
  uint32_t bat = analogRead(VBAT_PIN) * VBAT_NUM / VBAT_DEN;
  if (bat >= 3000) {
    return 100;
  } else if (bat > 2900) {
    return 100 - ((3000 - bat) * 58) / 100;
  } else if (bat > 2740) {
    return 42 - ((2900 - bat) * 24) / 160;
  } else if (bat > 2440) {
    return 18 - ((2740 - bat) * 12) / 300;
  } else if (bat > 2100) {
    return 6 - ((2440 - bat) * 6) / 340;
  } else {
    return 0;
  }
}

uint8_t readBattery(uint32_t now, uint8_t prev) {
  if (prev && now - last_bat_time <= 30000) {
    // There's a lot of variance in the reading, so no need to over-report it.
    return prev;
  }
  uint8_t bat_percentage = getBatteryPercent();
  last_bat_time = now;
  DBG(dumpVal(bat_percentage, "Battery level: "));
  DBG(dumpVal(scans_since_last_time, "# of scans in the past 30 seconds:"));
  scans_since_last_time = 0;
  return bat_percentage;
}

hw::hw(uint8_t bl) : switches(0), battery_level(bl) {}

hw::hw(uint32_t now, const hw& prev, const PinData& pd)
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

uint64_t debounce(uint64_t cur_switches, uint32_t now) {
  // If we've read the same thing we last reported, there's nothing to do
  if (last_reported_switches == cur_switches)
    return cur_switches;
  // This gets us a set of bits that are different between last report &
  // the current read
  uint64_t change = last_reported_switches ^ cur_switches;
  while (change) {
    uint8_t bit_num = flsl(change);
    uint64_t mask = ((uint64_t)1) << bit_num;
    change ^= mask;
    // For each change, check if we're in a debounce period for that switch
    if (now - last_reported_time[bit_num] < debounce_delay) {
      // Let's clear the change from cur_switches
      // If it's on, this will turn it off, if it's off, this will turn it on
      cur_switches ^= mask;
      DBG(dumpVal(bit_num, "Bounce ignored "));
    } else {
      // We're not in the debounce period: leave the change intact, and start
      // the timer
      last_reported_time[bit_num] = now;
    }
  }
  return cur_switches;
}

void hw::readSwitches(const PinData& pd, uint32_t now) {
  uint64_t new_switches = pd.Read();
  scans_since_last_time++;
  // Okay, we have the current state of switches: debounce them
  uint64_t switches_to_report = debounce(new_switches, now);
  // Save off the things we're reporting
  last_reported_switches = switches_to_report;
  this->switches = switches_to_report;
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
  Serial.print("Battery Level:");
  Serial.println(battery_level);
  Serial.print("Integer value:");
  Serial.print(static_cast<unsigned int>(switches >> 32), 16);
  Serial.print("|");
  Serial.println(static_cast<unsigned int>(switches), 16);
  for (int64_t r = 0; r < PinData::numrows; r++) {
    for (int64_t c = PinData::numcols - 1; c >= 0; c--) {
      uint64_t mask = 1ULL << (r * PinData::numcols + c);
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
