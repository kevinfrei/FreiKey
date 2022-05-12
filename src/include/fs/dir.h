#pragma once
#if !defined(__ARDUINO_CPPFILESYSTEM_DIR)
#define __ARDUINO_CPPFILESYSTEM_DIR

#include <cstddef>
#include <memory>
#include <system_error>
#include <vector>

#include "path.h"

// Hide this, to allow desktop testing
#if defined(ARDUINO)
#include <SD.h>
#endif

namespace ard {
namespace filesystem {

#if defined(ARDUINO)
using file_time_type = DateTimeFields;
#else
using file_time_type = uint64_t;
#endif

enum class directory_options {
  none,
  follow_directory_symlink,
  skip_permission_denied
};

class directory_entry {
  ard::filesystem::path location;
  file_time_type mod_time;
  bool is_dir;
  bool is_file;
  size_t size;
#if defined(ARDUINO)
  File& file;
  void refresh_nofile() {
    // Called from refresh, or from anywhere else that wants to re-open the file
    // we're looking;
    // Something should have already done this:
    // file = SD.open(location.c_str());
    if (!file) {
      is_dir = false;
      is_file = false;
      size = 0;
    } else {
      is_dir = file.isDirectory();
      is_file = !is_dir;
      if (is_file) {
        size = file.size();
        DateTimeFields datetime;
        if (file.getModifyTime(datetime)) {
          mod_time = datetime;
        }
      }
      file.close();
    }
  }

 protected:
  directory_entry(const ard::filesystem::path& p, File& f) noexcept
    : location(p / f.name()), file(f) {
    refresh_nofile();
  }
  friend class dir_container;
  friend class directory_iterator;
  friend class recursive_directory_iterator;
#endif

 public:
  directory_entry() noexcept = default;
  directory_entry(const directory_entry&) = default;
  directory_entry(directory_entry&&) noexcept = default;
  explicit directory_entry(const ard::filesystem::path& p) : location(p) {
    refresh();
  }
  directory_entry(const ard::filesystem::path& p, std::error_code& ec) noexcept
    : location(p) {
    refresh();
  }
  directory_entry& operator=(const directory_entry& other) = default;
  directory_entry& operator=(directory_entry&& other) noexcept = default;
  void assign(const ard::filesystem::path& p) {
    location = p;
    refresh();
  }
  void assign(const ard::filesystem::path& p, std::error_code& ec) {
    location = p;
    refresh();
  }
  void replace_filename(const ard::filesystem::path& p) {
    location = location.parent_path() / p;
    refresh();
  }
  void replace_filename(const ard::filesystem::path& p, std::error_code& ec) {
    location = location.parent_path() / p;
    refresh();
  }
  void refresh() noexcept {
#if defined(ARDUINO)
    file = SD.open(location.c_str());
    refresh_nofile();
#endif
  }
  void refresh(std::error_code& ec) noexcept {
    refresh();
    // TODO: Deal with error codes
  }

  const ard::filesystem::path& path() const noexcept {
    return location;
  }
  operator const ard::filesystem::path&() const noexcept {
    return location;
  }
  bool exists() const {
    // TODO: Get this implemented using SD.h stuff
    return is_dir || is_file;
  }
  bool exists(std::error_code& ec) const noexcept {
    // TODO: Get this implemented using SD.h stuff
    return is_dir || is_file;
  }
  bool is_regular_file() const {
    // TODO: Get this implemented using SD.h stuff
    return is_file;
  }
  bool is_regular_file(std::error_code& ec) const noexcept {
    // TODO: Get this implemented using SD.h stuff
    return is_file;
  }
  bool is_directory() const {
    // TODO: Get this implemented using SD.h stuff
    return is_dir;
  }
  bool is_directory(std::error_code& ec) const noexcept {
    // TODO: Get this implemented using SD.h stuff
    return is_dir;
  }
  std::uintmax_t file_size() const {
    // TODO: Get this implemented using SD.h stuff
    return size;
  }
  std::uintmax_t file_size(std::error_code& ec) const noexcept {
    // TODO: Get this implemented using SD.h stuff
    return size;
  }
  ard::filesystem::file_time_type last_write_time() const {
    // TODO:
    return mod_time;
  }
  ard::filesystem::file_time_type last_write_time(
    std::error_code& ec) const noexcept {
    // TODO:
    return mod_time;
  }
  bool operator==(const directory_entry& rhs) const noexcept {
    return this->path() == rhs.path();
  }
  bool operator!=(const directory_entry& rhs) const noexcept {
    return this->path() != rhs.path();
  }
  bool operator<(const directory_entry& rhs) const noexcept {
    return this->path() < rhs.path();
  }
  bool operator<=(const directory_entry& rhs) const noexcept {
    return this->path() <= rhs.path();
  }
  bool operator>(const directory_entry& rhs) const noexcept {
    return this->path() > rhs.path();
  }
  bool operator>=(const directory_entry& rhs) const noexcept {
    return this->path() >= rhs.path();
  }
  template <class CharT, class Traits>
  friend std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os, const directory_entry& d);
};
template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(
  std::basic_ostream<CharT, Traits>& os, const directory_entry& d) {
  return os << d.path();
}

class dir_container {
#if defined(ARDUINO)
  File dir_file;
#endif
  ard::filesystem::path dir_path;
  size_t cur_pos;
  bool done;
  // This should grow to contain all the directories
  std::vector<directory_entry> files;

 public:
  dir_container(const path& p)
    :
#if defined(ARDUINO)
      dir_file(SD.open(p.c_str())),
#endif
      dir_path(p),
      cur_pos(0),
      done(false) {
#if defined(ARDUINO)
    done = !dir_file;
#endif
  }
  const ard::filesystem::path& get_path() const {
    return dir_path;
  }
  directory_entry* get_entry(size_t pos) {
    if (pos < cur_pos) {
      return &files[pos];
    }
    while (cur_pos <= pos && !done) {
#if defined(ARDUINO)
      File nxt = dir_file.openNextFile();
      if (nxt) {
        files.push_back(directory_entry{dir_path, nxt});
        cur_pos++;
      } else {
        done = true;
      }
#else
      done = true;
#endif
    }
    return (cur_pos <= pos) ? nullptr : &files[pos];
  }
  ~dir_container() {
#if defined(ARDUINO)
    dir_file.close();
#endif
  }
};

class directory_iterator {
  std::shared_ptr<dir_container> the_dir;
  size_t cur_file_index;
  bool the_end;
  bool err;

 protected:
  void rewind() {
    cur_file_index = 0;
  }
  friend directory_iterator begin(directory_iterator iter) noexcept;

 public:
  using value_type = directory_entry;
  using difference_type = std::ptrdiff_t;
  using pointer = const directory_entry*;
  using reference = const directory_entry&;
  using iterator_category = std::input_iterator_tag;

  directory_iterator() noexcept
    : the_dir(nullptr),
      cur_file_index(~static_cast<size_t>(0)),
      the_end(true),
      err(false) {}
  explicit directory_iterator(const ard::filesystem::path& p)
    : the_dir(new dir_container(p)),
      cur_file_index(0),
      the_end(false),
      err(false) {}
  directory_iterator(const ard::filesystem::path& p, directory_options options)
    : the_dir(new dir_container(p)),
      cur_file_index(0),
      the_end(false),
      err(false) {}
  directory_iterator(const ard::filesystem::path& p, std::error_code& ec)
    : the_dir(new dir_container(p)),
      cur_file_index(0),
      the_end(false),
      err(false) {}
  directory_iterator(const ard::filesystem::path& p,
                     directory_options options,
                     std::error_code& ec)
    : the_dir(new dir_container(p)),
      cur_file_index(0),
      the_end(false),
      err(false) {}
  directory_iterator(const directory_iterator&) = default;
  directory_iterator(directory_iterator&&) = default;
  ~directory_iterator() = default;
  directory_iterator& operator=(const directory_iterator&) = default;
  directory_iterator& operator=(directory_iterator&&) = default;
  const directory_entry& operator*() const {
    return *the_dir->get_entry(cur_file_index);
  }
  const directory_entry* operator->() const {
    return the_dir->get_entry(cur_file_index);
  }
  directory_iterator& operator++() {
    the_end = the_dir->get_entry(++this->cur_file_index) == nullptr;
    return *this;
  }
  directory_iterator& increment(std::error_code& ec) {
    the_end = the_dir->get_entry(++this->cur_file_index) == nullptr;
    return *this;
  }
  bool operator==(const directory_iterator& iter) const {
    if (this->the_end && iter.the_end) {
      return true;
    }
    return this->cur_file_index == iter.cur_file_index &&
           this->the_dir->get_path() == iter.the_dir->get_path();
  }
  bool operator!=(const directory_iterator& iter) const {
    return !(*this == iter);
  }
};

inline directory_iterator begin(directory_iterator iter) noexcept {
  directory_iterator res{iter};
  res.rewind();
  return res;
}

inline directory_iterator end(directory_iterator iter) noexcept {
  return directory_iterator{};
}

class recursive_directory_iterator {
 public:
  using value_type = directory_entry;
  using difference_type = std::ptrdiff_t;
  using pointer = const directory_entry*;
  using reference = const directory_entry&;
  using iterator_category = std::input_iterator_tag;

  recursive_directory_iterator() noexcept;
  recursive_directory_iterator(const recursive_directory_iterator& rhs);
  recursive_directory_iterator(recursive_directory_iterator&& rhs) noexcept;
  explicit recursive_directory_iterator(const path& p);
  recursive_directory_iterator(const ard::filesystem::path& p,
                               directory_options options);
  recursive_directory_iterator(const ard::filesystem::path& p,
                               directory_options options,
                               std::error_code& ec);
  recursive_directory_iterator(const ard::filesystem::path& p,
                               std::error_code& ec);
  ~recursive_directory_iterator() = default;
  const directory_entry& operator*() const;
  const directory_entry* operator->() const;
  directory_options options() const;
  int depth() const;
  bool recursion_pending() const;
  recursive_directory_iterator& operator=(
    const recursive_directory_iterator& other) = default;
  recursive_directory_iterator& operator=(
    recursive_directory_iterator&& other) = default;
  recursive_directory_iterator& operator++();
  recursive_directory_iterator& increment(std::error_code& ec);
  void pop();
  void pop(std::error_code& ec);
  void disable_recursion_pending();
};
recursive_directory_iterator begin(recursive_directory_iterator iter) noexcept;
recursive_directory_iterator end(recursive_directory_iterator) noexcept;

} // namespace filesystem
} // namespace ard

#endif // __ARDUINO_CPPFILESYSTEM_DIR