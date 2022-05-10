#pragma once
#if !defined(__ARDUINO_CPPFILESYSTEM_DIR)
#define __ARDUINO_CPPFILESYSTEM_DIR

#include <system_error>

namespace ard {
namespace filesystem {

class path;
class directory_entry {
 public:
  directory_entry() noexcept = default;
  directory_entry(const directory_entry&) = default;
  directory_entry(directory_entry&&) noexcept = default;
  explicit directory_entry(const path& p);
  directory_entry(const path& p, std::error_code& ec);
  directory_entry& operator=(const directory_entry& other) = default;
  directory_entry& operator=(directory_entry&& other) noexcept = default;
  void assign(const ard::filesystem::path& p);
  void assign(const ard::filesystem::path& p, std::error_code& ec);
  void replace_filename(const ard::filesystem::path& p);
  void replace_filename(const ard::filesystem::path& p, std::error_code& ec);
  void refresh();
  void refresh(std::error_code& ec) noexcept;

  const std::filesystem::path& path() const noexcept;
  operator const std::filesystem::path&() const noexcept;
  bool exists() const;
  bool exists(std::error_code& ec) const noexcept;
  bool is_regular_file() const;
  bool is_regular_file(std::error_code& ec) const noexcept;
  bool is_directory() const;
  bool is_directory(std::error_code& ec) const noexcept;
  std::uintmax_t file_size() const;
  std::uintmax_t file_size(std::error_code& ec) const noexcept;
  bool operator==(const directory_entry& rhs) const noexcept;
  bool operator!=(const directory_entry& rhs) const noexcept;
  bool operator<(const directory_entry& rhs) const noexcept;
  bool operator<=(const directory_entry& rhs) const noexcept;
  bool operator>(const directory_entry& rhs) const noexcept;
  bool operator>=(const directory_entry& rhs) const noexcept;
  template <class CharT, class Traits>
  friend std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os, const directory_entry& d);
};
template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(
  std::basic_ostream<CharT, Traits>& os, const directory_entry& d);

enum class directory_options {
  none, /* unspecified */
  follow_directory_symlink, /* unspecified */
  skip_permission_denied /* unspecified */
};

class directory_iterator {
 public:
  using value_type = ard::filesystem::directory_entry;
  using difference_type = std::ptrdiff_t;
  using pointer = const ard::filesystem::directory_entry*;
  using reference = const ard::filesystem::directory_entry&;
  directory_iterator() noexcept;
  explicit directory_iterator(const ard::filesystem::path& p);
  directory_iterator(const ard::filesystem::path& p,
                     ard::filesystem::directory_options options);
  directory_iterator(const ard::filesystem::path& p, std::error_code& ec);
  directory_iterator(const ard::filesystem::path& p,
                     ard::filesystem::directory_options options,
                     std::error_code& ec);
  directory_iterator(const directory_iterator&) = default;
  directory_iterator(directory_iterator&&) = default;
  ~directory_iterator() = default;
  directory_iterator& operator=(const directory_iterator&) = default;
  directory_iterator& operator=(directory_iterator&&) = default;
  const ard::filesystem::directory_entry& operator*() const;
  const ard::filesystem::directory_entry* operator->() const;
  directory_iterator& operator++();
  directory_iterator& increment(std::error_code& ec);
};
directory_iterator begin(directory_iterator iter) noexcept;
directory_iterator end(directory_iterator) noexcept;

} // namespace filesystem
} // namespace ard

#endif // __ARDUINO_CPPFILESYSTEM_DIR`