#include "hwstate.h"

constexpr uint8_t VBAT_PIN = 31; // pin 31 is available for sampling the battery
// I had this set to 10, but would still occasionally see bounces. Let's try 15.
constexpr uint8_t DEBOUNCE_COUNT = 15;

// Some globals used by both halves
uint32_t last_bat_time = 0;
uint8_t stableCount = 0;
uint8_t recordedChange[numrows];

uint8_t getBatteryPercent() {
  float measuredvbat = analogRead(VBAT_PIN) * 6.6 / 1024;
  uint8_t bat_percentage = (uint8_t)round((measuredvbat - 3.7) * 200);
  return min(bat_percentage, 100);
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

namespace sw {
bool cmp(const uint8_t (&swa)[numrows], const uint8_t (&swb)[numrows]) {
  return memcmp(swa, swb, numrows);
}
void cpy(uint8_t (&swdst)[numrows], const uint8_t (&swsrc)[numrows]) {
  memcpy(swdst, swsrc, numrows);
}
void clr(uint8_t (&sw)[numrows]) {
  memset(sw, 0, numrows);
}
#if DEBUG
void dmp(const uint8_t (&sw)[numrows]) {
  Serial.print("Sw: ");
  for (uint8_t i : sw) {
    Serial.print(i, HEX);
  }
  Serial.println("");
}
#endif
} // namespace sw

hwstate::hwstate(uint8_t bl) : battery_level(bl) {
  sw::clr(switches);
}
hwstate::hwstate(uint32_t now, const hwstate& prev)
    : battery_level(readBattery(now, prev.battery_level)) {
  sw::cpy(switches, prev.switches);
  readSwitches();
}
hwstate::hwstate(BLEClientUart& clientUart, const hwstate& prev) {
  if (!receive(clientUart, prev))
    memcpy(reinterpret_cast<uint8_t*>(this),
           reinterpret_cast<const uint8_t*>(&prev),
           sizeof(hwstate));
}
hwstate::hwstate(const hwstate& c) : battery_level(c.battery_level) {
  sw::cpy(switches, c.switches);
}
void hwstate::readSwitches() {
  uint8_t newSwitches[numrows];
  sw::clr(newSwitches);
  for (uint8_t colNum = 0; colNum < numcols; ++colNum) {
    uint8_t val = 1 << colNum;
    digitalWrite(colPins[colNum], LOW);
    for (uint8_t rowNum = 0; rowNum < numrows; ++rowNum) {
      if (!digitalRead(rowPins[rowNum])) {
        newSwitches[rowNum] |= val;
      }
    }
    digitalWrite(colPins[colNum], HIGH);
  }
  // Debouncing: This just waits for stable DEBOUNCE_COUNT reads before
  // reporting
  if (sw::cmp(newSwitches, stableCount ? recordedChange : switches)) {
    // We've observed a change (in either the delta or the reported: doesn't
    // matter which) record the change and (re)start the timer
    DBG2(if (stableCount) dumpVal(stableCount, "Resetting Debouncer!"));
    stableCount = 1;
    sw::cpy(recordedChange, newSwitches);
  } else if (stableCount > DEBOUNCE_COUNT) {
    // We've had a stable reading for long enough: report it & clear the timer
    // If the micros() timer wraps around while waiting for stable readings,
    // we just wind up with a shorter debounce timer, which shouldn't really
    // hurt anything
    sw::cpy(switches, newSwitches);
    stableCount = 0;
  } else if (stableCount) {
    stableCount++;
  }
}

// Send the relevant data over the wire
void hwstate::send(BLEUart& bleuart, const hwstate& prev) const {
  bleuart.write((uint8_t*)&switches, sizeof(switches) + 1);
}

// Try to receive any relevant switch data from the wire.
// Returns true if something was received
bool hwstate::receive(BLEClientUart& clientUart, const hwstate& prev) {
  if (clientUart.available()) {
    uint8_t buffer[sizeof(switches) + 1];
    int size = clientUart.read(buffer, sizeof(switches) + 1);
    if (size == sizeof(switches) + 1) {
      memcpy(reinterpret_cast<uint8_t*>(this), buffer, sizeof(switches) + 1);
    } else {
#if DEBUG
      // NOTE: This fires occasionally when button mashing on the left, so
      // perhaps I shouldn't have changed this just on a whim. Wez clearly
      // knew what he was doing :)
      Serial.print("Incorrect datagram size:");
      Serial.print(" expected ");
      Serial.print(sizeof(hwstate));
      Serial.print(" got ");
      Serial.println(size);
#endif
    }
    return true;
  }
  return false;
}

bool hwstate::operator==(const hwstate& o) const {
  return o.battery_level == battery_level && !sw::cmp(o.switches, switches);
}

bool hwstate::operator!=(const hwstate& o) const {
  return !((*this) == o);
}

uint64_t hwstate::toUI64() const {
  uint64_t res = 0;
  for (int i = numrows - 1; i >= 0; i--)
    res = (res * 256) + switches[i];
  return res;
}

#if DEBUG
void hwstate::dump() const {
  Serial.print("Battery Level:");
  Serial.println(battery_level);
  for (int r = 0; r < numrows; r++) {
    for (int c = numcols - 1; c >= 0; c--) {
      unsigned int mask = 1 << c;
      if (switches[r] & mask) {
        Serial.print("X ");
      } else {
        Serial.print("- ");
      }
    }
    Serial.println("");
  }
}
#endif
