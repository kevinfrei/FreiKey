#include "hardware.h"

namespace state {
// pin 31 is available for sampling the battery
constexpr uint8_t VBAT_PIN = 31;
// I had set this as high as 24, but I added logging, and I think
// the high bounce count is making the keyboard behave weirdly :/
constexpr uint8_t DEBOUNCE_COUNT = 10;
// 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
constexpr uint32_t VBAT_NUM = 3000;
constexpr uint32_t VBAT_DEN = 4096;

// Some globals used by both halves
uint32_t last_bat_time = 0;
uint8_t stableCount = 0;
uint64_t recordedChange;
#if !NO_WATCH_BOUNCINESS
uint32_t bouncing = 0;
uint32_t maxBounce = 0;
#endif

void shared_setup(const PinData& pd) {
  static_assert(
      numcols * numrows <= 64,
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
  return bat_percentage;
}

hw::hw(uint8_t bl) : switches(0), battery_level(bl) {}

hw::hw(uint32_t now, const hw& prev, const PinData& pd)
    : switches(prev.switches),
      battery_level(readBattery(now, prev.battery_level)) {
  readSwitches(pd);
}

hw::hw(BLEClientUart& clientUart, const hw& prev) {
  if (!receive(clientUart, prev))
    memcpy(reinterpret_cast<uint8_t*>(this),
           reinterpret_cast<const uint8_t*>(&prev),
           sizeof(hw));
}

hw::hw(const hw& c) : switches(c.switches), battery_level(c.battery_level) {}

uint64_t justRead(const PinData &pd) {
 uint64_t switches = 0;
  for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
    uint64_t val = 1ULL << colNum;
    digitalWrite(pd.cols[colNum], LOW);
    for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
      if (!digitalRead(pd.rows[rowNum])) {
        switches |= val << (rowNum * numcols);
      }
    }
    digitalWrite(pd.cols[colNum], HIGH);
  }
  return switches;
}

void hw::readSwitches(const PinData& pd) {
  uint64_t newSwitches = justRead(pd);
  // Debouncing: This just waits for stable DEBOUNCE_COUNT reads before
  // reporting
  if (newSwitches != (stableCount ? recordedChange : switches)) {
    // We've observed a change (in either the delta or the reported: doesn't
    // matter which) record the change and (re)start the timer
    stableCount = 1;
    recordedChange = newSwitches;
#if !NO_WATCH_BOUNCINESS
    bouncing++;
#endif
  } else if (stableCount > DEBOUNCE_COUNT) {
    // We've had a stable reading for long enough: report it & clear the count
    switches = newSwitches;
    stableCount = 0;
#if !NO_WATCH_BOUNCINESS
    LOG(if (bouncing > 1) dumpVal(bouncing, "Bounced #"));
    if (bouncing > maxBounce) {
      maxBounce = bouncing;
      LOG(dumpVal(maxBounce, "Max Bounce #"));
    }
    bouncing = 0;
#endif
  } else if (stableCount) {
    stableCount++;
  }
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
  for (int64_t r = 0; r < numrows; r++) {
    for (int64_t c = numcols - 1; c >= 0; c--) {
      uint64_t mask = 1ULL << (r * numcols + c);
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
