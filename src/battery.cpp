#include <stdint.h>

#include "battery.h"
#include "boardio.h"
#include "dbgcfg.h"

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
