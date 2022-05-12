#pragma once
#if !defined(__ARDUINO_CPPFILESYSTEM_PATH)
#define __ARDUINO_CPPFILESYSTEM_PATH

#include <iomanip>
#include <ostream>
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

  using const_iterator = std::string::const_iterator;
  using iterator = const_iterator;

 private:
  string_type value;

  bool trailing() const {
    return (value.size() > 1) && *value.crbegin() == '/';
  }

 public:
  enum format { // Not an enum class: Dumb-ass standard...
    native_format,
    generic_format,
    auto_format
  };
  static constexpr value_type preferred_separator = '/';
  path() noexcept : value() {}
  path(const path& p) : value(p.value) {}
  path(path&& p) noexcept : value(std::move(p.value)) {}
  path(string_type&& source) noexcept : value(std::move(source)) {}
  template <class Source>
  path(const Source& source) : value(source) {}
  template <class InputIt>
  path(InputIt first, InputIt last) : value(first, last) {}
  ~path() = default;
  path& operator=(const path& p) {
    this->value = p.value;
    return *this;
  }
  path& operator=(path&& p) noexcept {
    this->value = std::move(p.value);
    return *this;
  }
  path& operator=(string_type&& source) {
    this->value = std::move(source);
    return *this;
  }
  template <class Source>
  path& operator=(const Source& source) {
    this->value = source;
    return *this;
  }
  path& assign(string_type&& source) {
    this->value = std::move(source);
    return *this;
  }
  template <class Source>
  path& assign(const Source& source) {
    this->value = source;
    return *this;
  }
  template <class InputIt>
  path& assign(InputIt first, InputIt last) {
    this->value.assign(first, last);
    return *this;
  }

  // Path element append operations:
  path& operator/=(const path& p) {
    if (!this->trailing()) {
      this->value.push_back('/');
    }
    this->value.append(p.value);
    return *this;
  }
  template <class Source>
  path& operator/=(const Source& source) {
    return *this /= path{source};
  }
  template <class Source>
  path& append(const Source& source) {
    return *this /= source;
  }
  template <class InputIt>
  path& append(InputIt first, InputIt last) {
    this->value.append(first, last);
    return *this;
  }

  // String/text append operations:
  path& operator+=(const path& p) {
    this->value.append(p.value);
    return *this;
  }
  path& operator+=(const string_type& str) {
    this->value.append(str);
    return *this;
  }
  // path& operator+=(std::basic_string_view<value_type> str);
  path& operator+=(const value_type* ptr) {
    this->value.append(ptr);
    return *this;
  }
  path& operator+=(value_type x) {
    this->value.push_back(x);
    return *this;
  }
  template <class CharT>
  path& operator+=(CharT x) {
    this->value.push_back(x);
    return *this;
  }
  template <class Source>
  path& operator+=(const Source& source) {
    this->value += source;
    return *this;
  }
  template <class Source>
  path& concat(const Source& source) {
    this->value += source;
    return *this;
  }
  template <class InputIt>
  path& concat(InputIt first, InputIt last) {
    this->value.append(first, last);
    return *this;
  }

  // Random path modifications
  void clear() noexcept {
    this->value.clear();
  }
  path& make_preferred() {
    // TODO: make this clean up the path: No trailing /'s, no duplicate /'s,
    // etc...
    if (this->trailing()) {
      size_t end = this->value.find_last_not_of('/');
      this->value.resize(end);
    }
    return *this;
  }
  path& remove_filename() {
    make_preferred();
    size_t end = this->value.find_last_of('/');
    if (end != std::string::npos && end != 0) {
      // If we found a slash, and it's not at the beginning, yank it, and
      // everything trailing, off
      this->value.resize(end);
    } else if (end == std::string::npos) {
      // If we didn't find any slash, just clear the whole thing
      this->value.clear();
    }
    return *this;
  }
  path& replace_filename(const path& replacement) {
    remove_filename();
    *this /= replacement;
    return *this;
  }
  path& replace_extension(const path& replacement = path()) {
    // TODO: Deal with corner cases as documented here:
    // https://en.cppreference.com/w/cpp/filesystem/path/replace_extension
    make_preferred();
    size_t last = this->value.find_last_of("/.");
    if (last != std::string::npos && this->value[last] == '.') {
      this->value.resize(last);
    }
    *this += replacement;
    return *this;
  }
  void swap(path& other) noexcept {
    std::swap(this->value, other.value);
  }

  // Conversions/data values
  const value_type* c_str() const noexcept {
    return this->value.c_str();
  }
  const string_type& native() const noexcept {
    return this->value;
  }
  operator string_type() const {
    return this->value;
  }
  template <class CharT,
            class Traits = std::char_traits<CharT>,
            class Alloc = std::allocator<CharT> >
  std::basic_string<CharT, Traits, Alloc> string(
    const Alloc& a = Alloc()) const {
    return std::basic_string<CharT, Traits, Alloc>(this->value);
  }
  std::string string() const {
    return this->value;
  }
  template <class CharT,
            class Traits = std::char_traits<CharT>,
            class Alloc = std::allocator<CharT> >
  std::basic_string<CharT, Traits, Alloc> generic_string(
    const Alloc& a = Alloc()) const {
    return std::basic_string<CharT, Traits, Alloc>(this->value);
  }
  std::string generic_string() const {
    return this->value;
  }

  // Comparators:
  int compare(const value_type* s) const {
    return this->value.compare(s);
  }
  int compare(const string_type& str) const {
    return this->value.compare(str);
  }
  int compare(const path& p) const noexcept {
    return this->value.compare(p.value);
  }

  // Decomposition:
  path root_name() const {
    // TODO: Maybe the "root name" should be some string identifier to support
    // potential mulitple SPI channel & CS pins, or I2C or some other bus
    // as well as supporting multiple SD cards on the same SPI channel?
    // Something like "<SPI2:19>/dir/file.txt" so that things are extensible?
    // I like using <> as delimeters just to make it likely not easy to do
    // stupid stuff... Not initially, but maybe in the future, just for
    // shiggles...
    return path{};
  }
  path root_directory() const {
    if (empty() || *this->begin() != '/') {
      return path{};
    } else {
      return path{"/"};
    }
  }
  path root_path() const {
    return root_directory();
  }
  path relative_path() const {
    if (empty() || *this->begin() != '/') {
      return *this;
    }
    return path{++this->begin(), this->end()};
  }
  path parent_path() const {
    // ""
    if (empty()) {
      return *this;
    }
    // "/"
    if (this->value.size() == 1 && *this->begin() == '/') {
      return *this;
    }
    size_t e = this->value.find_last_of('/');
    // "/justOnePathPiece"
    if (e == 0) {
      return path{"/"};
    }
    // "/more/than/one"
    if (e != std::string::npos) {
      return path{this->value.substr(0, e)};
    }
    // "noSlashes.txt"
    return path{};
  }
  path filename() const {
    size_t e = this->value.find_last_of('/');
    if (e == std::string::npos) {
      return *this;
    }
    return path{this->value.substr(e+1)};
  }
  path extension() const {
    path p = filename();
    if (empty()) {
      return p;
    }
    // Handle '.' & '..'
    if (p.value.size() == 1 && p.value[0] == '.') {
      return path{};
    }
    // Handle '..'
    if (p.value.size() == 2 && p.value[0] == '.' && p.value[1] == '.') {
      return path{};
    }
    size_t lastDot = p.value.find_last_of('.');
    // No extension, or it's a hidden [dot] file
    if (lastDot == std::string::npos || lastDot == 0) {
      return path{};
    }
    // Everything else, return the suffix:
    return path{p.value.substr(lastDot)};
  }
  // AKA "basename"
  path stem() const {
    // Filename, minus extension
    path fn = filename();
    path ext = fn.extension();
    return path{fn.begin(), fn.end() - ext.value.size()};
  }

  // Queries:
  bool empty() const noexcept {
    return this->value.empty();
  }
  bool has_root_path() const {
    return !this->empty() && this->value[0] == '/';
  }
  bool has_root_name() const {
    return false;
  }
  bool has_root_directory() const {
    return this->has_root_path();
  }
  bool has_relative_path() const {
    return !this->empty() && !this->has_root_path();
  }
  bool has_parent_path() const {
    return !parent_path().empty();
  }
  bool has_filename() const{
    return !filename().empty();
  }
  bool has_stem() const{
    return !stem().empty();
  }
  bool has_extension() const {
    return !extension().empty();
  }
  bool is_absolute() const {
    return this->has_root_path();
  }
  bool is_relative() const {
    return !is_absolute();
  }

  // Iterators:
  iterator begin() const {
    return this->value.cbegin();
  }
  iterator end() const {
    return this->value.cend();
  }

  template <class CharT, class Traits>
  friend std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os, const path& p);
  template <class CharT, class Traits>
  friend std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is, path& p);
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
  return os << std::quoted(p.string<CharT, Traits>());
}

template <class CharT, class Traits>
std::basic_istream<CharT, Traits>& operator>>(
  std::basic_istream<CharT, Traits>& is, path& p) {
  std::basic_string<CharT, Traits> t;
  is >> std::quoted(t);
  p = t;
  return is;
}

// C++20 can't get supported soon enough...
// friend std::strong_ordering operator<=>(const path& lhs, const path& rhs)
// noexcept;

} // namespace filesystem
} // namespace ard

#endif // __ARDUINO_CPPFILESYSTEM_PATH