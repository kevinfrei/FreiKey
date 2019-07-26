#if !defined(SWITCH_MATRIX_H)
#define SWITCH_MATRIX_H

#include <initializer_list>

#include "dbgcfg.h"
#include "helpers.h"

template <int T>
struct bit_array {
  constexpr static uint32_t num_bits = T;
  constexpr static uint32_t num_bytes = (T + 7) / 8;
  std::array<uint8_t, num_bytes> value;
  bit_array() {}
  bit_array(std::initializer_list<uint8_t> init) : value{0} {
    size_t i = 0;
    for (auto& v : init) {
      value[i++] = v;
      if (i >= value.size())
        break;
    }
  }
  bit_array(const bit_array& m) : value{m.value} {}
  bool operator==(const bit_array& m) const {
    return value == m.value;
  }
  bool operator!=(const bit_array& m) const {
    return value != m.value;
  }
  bit_array<T> delta(const bit_array& compare) const {
    bit_array<T> v{};
    for (size_t i = 0; i < sizeof(value); i++) {
      v.value[i] = value[i] ^ compare.value[i];
    }
    return v;
  }
  bool any() const {
    for (uint8_t i : value) {
      if (i)
        return true;
    }
    return false;
  }
  uint8_t pull_a_bit() {
    for (int i = 0; i < sizeof(value); i++) {
      if (value[i]) {
        uint8_t bit_num = get_a_set_bit(value[i]);
        value[i] ^= (1 << bit_num);
        return bit_num + i * 8;
      }
    }
  }
  void flip_bit(uint8_t bitnum) {
    value[bitnum >> 3] ^= 1 << (bitnum & 7);
  }
  void set_bit(uint8_t bitnum) {
    value[bitnum >> 3] |= 1 << (bitnum & 7);
  }
  void clear_bit(uint8_t bitnum) {
    value[bitnum >> 3] &= ~(1 << (bitnum & 7));
  }
  bool get_bit(uint8_t bitnum) const {
    return !!(value[bitnum >> 3] & (1 << (bitnum & 7)));
  }
#if defined(DEBUG)
  void dumpHex(const char* prf) const {
    Serial.print(prf);
    for (uint8_t i : this->value) {
      Serial.printf("%02X", i);
    }
    Serial.println();
  }
#endif
};

#endif
