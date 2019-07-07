#if !defined(HELPERS_H)
#define HELPERS_H

// Find last bit set in a long (BSD function, not available in Arduino)
/* inline uint8_t flsl(uint64_t val) {
  // GCC builtin function seems to work on Arduino :)
  return static_cast<uint8_t>(64 - __builtin_clzll(val));
}
*/
#endif