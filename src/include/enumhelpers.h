#pragma once
#include <algorithm>
#include <array>
#include <initializer_list>
#include <type_traits>

namespace detail {
template <typename E>
using underlying_type = typename std::underlying_type<E>::type;
template <typename E>
using enum_types_only =
  typename std::enable_if<std::is_enum<E>::value, E>::type;
} // namespace detail

template <typename E, typename = detail::enum_types_only<E>>
constexpr detail::underlying_type<E> value_cast(E e) {
  return static_cast<detail::underlying_type<E>>(e);
}

template <typename E, typename = detail::enum_types_only<E>>
constexpr E enum_cast(detail::underlying_type<E> v) {
  return static_cast<E>(v);
}

/*
C++20 :'(
template <class EnumType,
          class ValueType,
          size_t Size = value_cast(EnumType::NumElems),
          typename = detail::enum_types_only<EnumType>>
constexpr std::array<ValueType, Size> init_array(
  std::initializer_list<std::pair<EnumType, ValueType>> vals) {
  std::array<ValueType, Size> res{};
  std::for_each(vals.begin(), vals.end(), [&](const std::pair<EnumType,
ValueType> &i){ res[value_cast(i.first)] = i.second;
  });
  return res;
};
*/

template <class EnumType,
          class ValueType,
          size_t Size = value_cast(EnumType::NumElems),
          typename = detail::enum_types_only<EnumType>>
class enum_array {
  std::array<ValueType, Size> array_;

 public:
  enum_array() {}
  enum_array(std::initializer_list<std::pair<EnumType, ValueType>> vals)
    : array_() {
    std::for_each(
      vals.begin(), vals.end(), [&](const std::pair<EnumType, ValueType>& i) {
        array_[value_cast(i.first)] = i.second;
      });
  }
  // TODO: Flesh this out into a real array with types & iterators & initializer
  // lists & stuff
  ValueType& operator[](EnumType i) {
    return array_[static_cast<size_t>(i)];
  }

  const ValueType& operator[](EnumType i) const {
    return array_[static_cast<size_t>(i)];
  }

  int size() const {
    return array_.size();
  }
};

// Boolean operators for Enums with a MASK member
template <typename E, typename = detail::enum_types_only<E>>
inline constexpr E operator|(E a, E b) {
  return enum_cast<E>((value_cast(a) | value_cast(b)) & value_cast(E::MASK));
}

template <typename E, typename = detail::enum_types_only<E>>
inline constexpr E operator&(E a, E b) {
  return enum_cast<E>(value_cast(a) & value_cast(b) & value_cast(E::MASK));
}

template <typename E, typename = detail::enum_types_only<E>>
inline constexpr E operator^(E a, E b) {
  return enum_cast<E>((value_cast(a) ^ value_cast(b)) & value_cast(E::MASK));
}

template <typename E, typename = detail::enum_types_only<E>>
inline constexpr E operator~(E a) {
  return enum_cast<E>(~value_cast(a) & value_cast(E::MASK));
}

template <typename E, typename = detail::enum_types_only<E>>
inline const E& operator|=(E& a, E b) {
  a = a | b;
  return a;
}

template <typename E, typename = detail::enum_types_only<E>>
inline const E& operator&=(E& a, E b) {
  a = a & b;
  return a;
}

template <typename E, typename = detail::enum_types_only<E>>
inline const E& operator^=(E& a, E b) {
  a = (a ^ b);
  return a;
}

template <typename E, typename = detail::enum_types_only<E>>
constexpr inline bool operator&&(E a, E b) {
  return (a & b) == b;
}
