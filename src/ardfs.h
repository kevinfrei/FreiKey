#pragma once
#if !defined(__ARDUINO_CPPFILESYSTEM)
#define __ARDUINO_CPPFILESYSTEM

#include "fs/dir.h"
#include "fs/path.h"

namespace ard {
namespace filesystem {

path current_path();
void current_path(const ard::filesystem::path& p);

bool remove(const ard::filesystem::path& p);
bool remove(const ard::filesystem::path& p, std::error_code& ec) noexcept;

std::uintmax_t remove_all(const ard::filesystem::path& p);
std::uintmax_t remove_all(const ard::filesystem::path& p, std::error_code& ec);

} // namespace filesystem
} // namespace ard

#endif // __ARDUINO_CPPFILESYSTEM