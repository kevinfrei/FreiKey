#include <cstddef>
#include <cstdint>

#include "usbenums.h"

namespace edit {
struct editline {
  const char* buf;
  uint8_t pos;
};
void Initialize();
const editline& readline(Keystroke k, Modifiers m, bool pressed, uint32_t now);
} // namespace edit