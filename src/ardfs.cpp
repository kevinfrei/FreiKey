#include "ardfs.h"

namespace ard {
namespace filesystem {

namespace {

// File-local stuff

path cur("/");

} // namespace

path current_path() {
  return cur;
}

void current_path(const path& p) {
  cur = p;
}

bool remove(const ard::filesystem::path& p) {
  // TODO
  return false;
}

bool remove(const ard::filesystem::path& p, std::error_code& ec) noexcept {
  // TODO
  return false;
}

std::uintmax_t remove_all(const ard::filesystem::path& p) {
  return 0;
}

std::uintmax_t remove_all(const ard::filesystem::path& p, std::error_code& ec) {
  return 0;
}

} // namespace filesystem
} // namespace ard
