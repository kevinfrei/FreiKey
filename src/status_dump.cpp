#include <bluefruit.h>

#include "keyhelpers.h"
#include "status_dump.h"

#if STATUS_DUMP

extern BLEHidAdafruit hid;
extern layer_t* layer_stack;
extern layer_t layer_pos;
extern const char* layer_names[];
extern uint16_t core_handle;

// If you hold this configuration down, it types out status
constexpr uint8_t status_keys_left[] = {0, 0, 0, 0x80, 0x80};
constexpr uint8_t status_keys_right[] = {0, 0, 0, 1, 1};
// If you hold this down, just on the right keyboard, it should RHS status only
// (might be made helpful in the future...)
constexpr uint8_t just_right_stat[] = {0, 0, 0, 3, 3};
// Hit these six keys, and the bluetooth bonds get removed... (Both Shifts, the
// keys 3 rows above the shifts, and the 'innermost' keys logically  between the
// 5 & the 6 keys)

// A very limited version of typing the string. It dumps lower case, nubmers,
// a few other things, defaults to '.' for everything else.
void type_string(const char* str) {
  uint8_t console[6] = {0, 0, 0, 0, 0, 0};
  char p = 0;
  bool shift;
  while (*str) {
    shift = false;
    char c = *str++;
    char n = 0;
    if (c >= 'a' && c <= 'z')
      n = HID_KEY_A + c - 'a';
    else if (c >= 'A' && c <= 'Z') {
      n = HID_KEY_A + c - 'A';
      shift = true;
    } else if (c >= '1' && c <= '9')
      n = HID_KEY_1 + c - '1';
    else {
      switch (c) {
        case '0':
          n = HID_KEY_0;
          break;
        case ' ':
          n = HID_KEY_SPACE;
          break;
        case '\n':
        case '\r':
          n = HID_KEY_RETURN;
          break;
        case ':':
          shift = true;
        case ';':
          n = HID_KEY_SEMICOLON;
          break;
        case ',':
          n = HID_KEY_COMMA;
          break;
        case '(':
          n = HID_KEY_9;
          shift = true;
          break;
        case ')':
          n = HID_KEY_0;
          shift = true;
          break;
        case '-':
          n = HID_KEY_MINUS;
          break;
        case '%':
          n = HID_KEY_5;
          shift = true;
          break;
        default:
          n = HID_KEY_PERIOD;
      }
    }
    if (n == p) {
      console[0] = 0;
      hid.keyboardReport(0, console);
    }
    console[0] = n;
    hid.keyboardReport(shift ? 2 : 0, console);
    p = n;
  }
  // Clear any final key out, just to be safe
  console[0] = 0;
  hid.keyboardReport(0, console);
}

void type_number(uint32_t val) {
  int p = -1;
  char buffer[25];
  int curPos = 0;
  do {
    int v;
    int digit = val % 10;
    val = val / 10;
    if (digit == 0) {
      v = HID_KEY_0;
    } else {
      v = HID_KEY_1 - 1 + digit;
    }
    if (v == p) {
      buffer[curPos++] = 0;
    }
    buffer[curPos++] = v;
    p = v;
  } while (val);
  uint8_t console[6] = {0, 0, 0, 0, 0, 0};
  do {
    console[0] = buffer[--curPos];
    hid.keyboardReport(0, console);
  } while (curPos);
  // Clear any final key out, just to be safe
  console[0] = 0;
  hid.keyboardReport(0, console);
}

bool status_dump_check(const hwstate& rightSide, const hwstate& leftSide) {
  bool justRight = !sw::cmp(rightSide.switches, just_right_stat);
  bool leftCheck = !sw::cmp(leftSide.switches, status_keys_left);
  bool rightCheck = !sw::cmp(rightSide.switches, status_keys_right);
  // Check for hardware request thingamajig:
  // This is hard coded, mostly because I'm just hacking
  if (justRight || (leftCheck && rightCheck)) {
    if (!justRight) {
      type_string("Left battery level: ");
      type_number(leftSide.battery_level);
      type_string("%\n");
    }
    type_string("Right battery level: ");
    type_number(rightSide.battery_level);
    type_string("%\nLayer stack: ");
    for (int i = 0; i <= layer_pos; i++) {
      type_string(layer_names[layer_stack[i]]);
      type_string(" (");
      type_number(i);
      type_string(i == layer_pos ? ")" : "), ");
    }
    type_string("\n");
    DBG(Bluefruit.printInfo());
    DBG(dumpHex(Bluefruit.connHandle(), "Connection handle: "));
    DBG(dumpHex(Bluefruit.connPaired(), "Connection paired: "));
    DBG(dumpHex(core_handle, "Core Connection handle: "));
    return true;
  }
  return false;
}

#endif
