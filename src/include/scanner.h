#pragma once

#include <array>

#include "boardio.h"
#include "hardware.h"

std::array<scancode_t, 6> GetScanCodesForSwitchStates(BoardIO::bits beforeLeft,
                                                      BoardIO::bits afterLeft,
                                                      BoardIO::bits beforeRight,
                                                      BoardIO::bits afterRight);
void PerformActionsForScanCodes(const std::array<scancode_t, 6>& scanCodes);
