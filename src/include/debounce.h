#pragma once

#include <array>
#include <bitset>

#include "bitstuff.h"
#include "boardio.h"

template <size_t SIZE>
class Debouncer {
  typedef std::bitset<SIZE> BITS;

 private:
  // The last set of switches we reported
  std::bitset<SIZE> last_reported_switches;
  // This is just the set of report times for switches
  std::array<uint32_t, SIZE> last_reported_time;
  // This is the # of msec to delay after reporting a change before reporting
  // another one. Rumor has it that Cherry claims a debounce period of 5ms, but
  // I still sometimes see a bounce or two, so I've increased it a bit.
  // 25ms translates to a typing speed of about 400 WPM, which seems plenty
  // fast...
  static const uint8_t debounce_delay = 15;

 public:
  Debouncer() : last_reported_switches{}, last_reported_time{} {}
  void reset() {
    last_reported_switches.reset();
    last_reported_time.fill(0);
  }
  BITS update(BITS cur_switches, uint32_t now) {
    // If we've read the same thing we last reported, there's nothing to do
    if (last_reported_switches == cur_switches)
      return cur_switches;
    // This gets us a set of bits that are different between last report &
    // the current read
    BITS change = last_reported_switches ^ cur_switches;
    while (change.any()) {
      // pull_a_bit yoinks a bit number and clears it from the bit array
      uint8_t bit_num = pull_a_bit(change);
      if (bit_num >= cur_switches.size())
        break;
      // For each change, check if we're in a debounce period for that switch
      if (now - last_reported_time[bit_num] < debounce_delay) {
        // Let's clear the change from cur_switches
        // If it's on, this will turn it off, if it's off, this will turn it on
        cur_switches.flip(bit_num);
        DBG(dumpVal(bit_num, "Bounce ignored "));
        DBG(dumpVal(now - last_reported_time[bit_num],
                    "milleseconds since initial flip: "));
      } else {
        // We're not in the debounce period: leave the change intact, and start
        // the timer
        last_reported_time[bit_num] = now;
      }
    }
    // Save off the things we're reporting
    last_reported_switches = cur_switches;
    return cur_switches;
  }
};

MatrixBits debounce(MatrixBits cur_switches, uint32_t now);
