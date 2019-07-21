#if !defined(HELPERS_H)
#define HELPERS_H

// This doesn't guarantee that the result is the highest/lowest bit.
// It just guarantees that it will be a set bit (or 0xFF if none are set)
inline uint8_t get_a_set_bit(uint64_t val) {
  // GCC builtin function seems to work on Arduino :)
  if (!val) {
    return 0xFF;
  } else if (val > 0xFFFFFFFF) {
    return 31 + static_cast<uint8_t>(__builtin_ffs(0xFFFFFFFF & (val >> 32)));
  } else {
    return static_cast<uint8_t>(__builtin_ffs(val & 0xFFFFFFFF) - 1);
  }
}

#endif