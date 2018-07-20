#include "boardio.h"
#include "dbgcfg.h"
#include "helpers.h"

// The last set of switches we reported
uint64_t last_reported_switches = 0;
// This is just the set of report times for switches
uint32_t last_reported_time[BoardIO::matrix_size] = {0};
// This is the # of msec to delay after reporting a change before reporting
// another one. Rumor has it that Cherry claims a debounce period of 5ms, but
// I still sometimes see a bounce or two, so I've increased it a bit.
// 25ms translates to a typing speed of about 400 WPM, which seems plenty fast...
constexpr uint8_t debounce_delay = 25;

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
  // Save off the things we're reporting
  last_reported_switches = cur_switches;
  return cur_switches;
}