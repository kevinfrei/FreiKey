#pragma once
#include <array>
#include <initializer_list>
#include <stdint.h>

enum class layer_num : uint8_t {
  Base = 0,
  MacBase = 0,
  WinBase = 1,
  LinBase = 2,
  Func = 3,
  MacCap = 4,
  WinCap = 5,
  WinCtl = 6,
  LinCap = 7
};

// This needs to fit in 4 bits
enum class KeyAction : uint8_t {
  KeyPress,
  Modifier,
  TapHold,
  Consumer,
  KeyAndMods,
  LayerShift,
  LayerToggle,
  LayerSwitch,
  MaxActions = 15
};

template <class IndexType, class ValueType>
class enum_array {
  std::array<ValueType, static_cast<size_t>(IndexType::MaxValue)> array_;

 public:
  enum_array() {}
  enum_array(std::initializer_list<std::pair<IndexType, ValueType>> vals) {
    for (auto& i : vals) {
      array_[i.first] = i.second;
    }
  }
  // TODO: Flesh this out into a real array with types & iterators & initializer
  // lists & stuff
  ValueType& operator[](IndexType i) {
    return array_[static_cast<size_t>(i)];
  }

  const ValueType& operator[](IndexType i) const {
    return array_[static_cast<size_t>(i)];
  }

  int size() const {
    return array_.size();
  }
};