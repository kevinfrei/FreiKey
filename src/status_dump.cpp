#if STATUS_DUMP

#include <bluefruit.h>

#include "hardware.h"
#include "keyhelpers.h"
#include "status_dump.h"

// TODO: Expose this stuff somehow. This is a disgusting hack to get at some
// necessary state, and it makes me slightly queasy

extern BLEHidAdafruit hid;
extern layer_t* layer_stack;
extern layer_t layer_pos;
extern const char* layer_names[];
extern uint16_t core_handle;

// If you hold this configuration down, it types out status
// Lower left two keys on the edge
constexpr uint64_t status_keys_left = 0x10400000000ULL;
// Lower right two keys on the edge
constexpr uint64_t status_keys_right = 0x1010000000ULL;
// If you hold this down, just on the right keyboard, it shows RHS status only
// Right-most keys on the bottom 3 rows
// (might be made helpful in the future...)
constexpr uint64_t just_right_stat = 0x1000200000ULL;

// A very limited version of typing the string. It dumps lower case, nubmers,
// a few other things, defaults to '.' for everything else.
void type_string(const char* str) {
  hid.keySequence(str);
}

void type_number(uint32_t val) {
  char buffer[25];
  int curPos = sizeof(buffer)-1;
  buffer[curPos] = 0;
  do {
    int digit = val % 10;
    val = val / 10;
    buffer[--curPos] = digit;
  } while (val && curPos);
  type_string(&buffer[curPos]);
}

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
    for (uint8_t i = 0; i <= min(layer_pos, 5); i++) {
      uint8_t layerLoc = min(layer_stack[i], 5);
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
