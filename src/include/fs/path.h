#pragma once
#if !defined(__ARDUINO_CPPFILESYSTEM_PATH)
#define __ARDUINO_CPPFILESYSTEM_PATH

#include <string>
#include <unordered_set>

namespace ard {
namespace filesystem {

enum class file_type {
  none,
  not_found,
  regular,
  directory,
  symlink,
  block,
  character,
  fifo,
  socket,
  unknown
};

class path {
 public:
  using value_type = char;
  using string_type = std::string;

  // TODO: Fix these things
  using const_iterator = const char*;
  using iterator = const_iterator;

  enum format { // Not an enum class: Dumb-ass standard...
    native_format,
    generic_format,
    auto_format
  };
  static constexpr value_type preferred_separator = '/';
  path() noexcept;
  path(const path& p);
  path(path&& p) noexcept;
  path(string_type&& source, format fmt = auto_format);
  template <class Source>
  path(const Source& source, format fmt = auto_format);
  ~path();
  path& operator=(const path& p);
  path& operator=(path&& p) noexcept;
  path& operator=(string_type&& source);
  template <class Source>
  path& operator=(const Source& source);
  path& assign(string_type&& source);
  template <class Source>
  path& assign(const Source& source);
  template <class InputIt>
  path& assign(InputIt first, InputIt last);

  // Path element append operations:
  path& operator/=(const path& p);
  template <class Source>
  path& operator/=(const Source& source);
  template <class Source>
  path& append(const Source& source);
  template <class InputIt>
  path& append(InputIt first, InputIt last);

  // String/text append operations:
  path& operator+=(const path& p);
  path& operator+=(const string_type& str);
  // path& operator+=(std::basic_string_view<value_type> str);
  path& operator+=(const value_type* ptr);
  path& operator+=(value_type x);
  template <class CharT>
  path& operator+=(CharT x);
  template <class Source>
  path& operator+=(const Source& source);
  template <class Source>
  path& concat(const Source& source);
  template <class InputIt>
  path& concat(InputIt first, InputIt last);

  // Random path modifications
  void clear() noexcept;
  path& make_preferred();
  path& remove_filename();
  path& replace_filename(const path& replacement);
  path& replace_extension(const path& replacement = path());
  void swap(path& other) noexcept;

  // Conversions/data values
  const value_type* c_str() const noexcept;
  const string_type& native() const noexcept;
  operator string_type() const;
  template <class CharT,
            class Traits = std::char_traits<CharT>,
            class Alloc = std::allocator<CharT> >
  std::basic_string<CharT, Traits, Alloc> string(
    const Alloc& a = Alloc()) const;
  std::string string() const;
  template <class CharT,
            class Traits = std::char_traits<CharT>,
            class Alloc = std::allocator<CharT> >
  std::basic_string<CharT, Traits, Alloc> generic_string(
    const Alloc& a = Alloc()) const;
  std::string generic_string() const;

  // Comparators:
  int compare(const path& p) const noexcept;
  int compare(const string_type& str) const;
  int compare(const value_type* s) const;

  // Decomposition:
  path root_name() const;
  path root_directory() const;
  path root_path() const;
  path relative_path() const;
  path parent_path() const;
  path filename() const;
  path stem() const;
  path extension() const;

  // Queries:
  bool empty() const noexcept;
  bool has_root_path() const;
  bool has_root_name() const;
  bool has_root_directory() const;
  bool has_relative_path() const;
  bool has_parent_path() const;
  bool has_filename() const;
  bool has_stem() const;
  bool has_extension() const;
  bool is_absolute() const;
  bool is_relative() const;

  // Iterators:
  iterator begin() const;
  iterator end() const;
};

// helper functions:
std::size_t hash_value(const path& p) noexcept;
inline void swap(path& lhs, path& rhs) noexcept {
  lhs.swap(rhs);
}
inline bool operator==(const path& lhs, const path& rhs) noexcept {
  return lhs.compare(rhs) == 0;
}
inline bool operator!=(const path& lhs, const path& rhs) noexcept {
  return lhs.compare(rhs) != 0;
}
inline bool operator<(const path& lhs, const path& rhs) noexcept {
  return lhs.compare(rhs) < 0;
}
inline bool operator<=(const path& lhs, const path& rhs) noexcept {
  return lhs.compare(rhs) <= 0;
}
inline bool operator>(const path& lhs, const path& rhs) noexcept {
  return lhs.compare(rhs) > 0;
}
inline bool operator>=(const path& lhs, const path& rhs) noexcept {
  return lhs.compare(rhs) >= 0;
}
inline path operator/(const path& lhs, const path& rhs) {
  path res{lhs};
  return res /= rhs;
}
template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(
  std::basic_ostream<CharT, Traits>& os, const path& p) {
  os << p.c_str();
}
template <class CharT, class Traits>
std::basic_istream<CharT, Traits>& operator>>(
  std::basic_istream<CharT, Traits>& is, path& p) {
  std::string str;
  is >> str;
  p.assign(str);
}
// C++20 can't get supported soon enough...
// friend std::strong_ordering operator<=>(const path& lhs, const path& rhs)
// noexcept;

} // namespace filesystem
} // namespace ard

#endif // __ARDUINO_CPPFILESYSTEM_PATH