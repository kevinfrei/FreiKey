#include <array>

#include "scanner.h"

std::array<scancode_t, 6> GetScanCodesForSwitchStates(
    BoardIO::bits beforeLeft,
    BoardIO::bits afterLeft,
    BoardIO::bits beforeRight,
    BoardIO::bits afterRight) {
  return std::array<scancode_t, 6>{};
}
void PerformActionsForScanCodes(const std::array<scancode_t, 6>& scanCodes) {
  return;
}
