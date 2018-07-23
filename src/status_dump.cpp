#if defined(STATUS_DUMP)

#include "mybluefruit.h"
#include <algorithm>

#include "globals.h"
#include "hardware.h"
#include "keyhelpers.h"
#include "status_dump.h"

// TODO: Expose this stuff somehow. This is a disgusting hack to get at some
// necessary state, and it makes me slightly queasy

extern BLEHidAdafruit hid;
extern layer_t* layer_stack;
extern layer_t layer_pos;
extern const char* layer_names[];

// If you hold this configuration down, it types out status
// Lowest out, and the key directly above it
constexpr uint64_t status_keys_left = 0x10200000000ULL;
// Thumb low edge and right most bottom row
constexpr uint64_t status_keys_right = 0x1020000000ULL;
// If you hold this down, just on the right keyboard, it shows RHS status only
// Sameas above, just add the rightmost key on the second to bottom row
constexpr uint64_t just_right_stat = 0x1030000000ULL;

// I used to implement this all myself, but then I discovered it was alread in
// the hid class :)
void type_string(const char* str) {
  hid.keySequence(str);
}

// Interview question ahead!
void type_number(uint32_t val) {
  char buffer[25];
  int curPos = sizeof(buffer) - 1;
  buffer[curPos] = 0;
  do {
    buffer[--curPos] = val % 10 + '0';
    val = val / 10;
  } while (val && curPos);
  type_string(&buffer[curPos]);
}
const layer_t maxLayers = 5;
bool status_dump_check(const state::hw& rightSide, const state::hw& leftSide) {
  bool justRight = rightSide.switches == just_right_stat;
  bool leftCheck = leftSide.switches == status_keys_left;
  bool rightCheck = rightSide.switches == status_keys_right;
  // Check for hardware request thingamajig:
  // This is hard coded, mostly because I'm just hacking
  if (justRight || (leftCheck && rightCheck)) {
    if (!justRight) {
      type_string("Lbat:");
      type_number(leftSide.battery_level);
      type_string("% ");
    }
    type_string("Rbat: ");
    type_number(rightSide.battery_level);
    type_string("% Layer: ");
    for (uint8_t i = 0; i <= std::min(layer_pos, maxLayers); i++) {
      uint8_t layerLoc = std::min(layer_stack[i], maxLayers);
      type_string(layer_names[layerLoc]);
      type_string(" (");
      type_number(i);
      type_string(i == layer_pos ? ")" : "), ");
    }
    DBG(Bluefruit.printInfo());
    DBG(dumpHex(Bluefruit.connHandle(), "Connection handle: "));
    DBG(dumpHex(Bluefruit.connPaired(), "Connection paired: "));
    DBG(dumpHex(core_handle, "Core Connection handle: "));
    return true;
  }
  return false;
}

#endif
