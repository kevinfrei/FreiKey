#pragma once

#include <vector>

#include "hardware.h"

std::vector<scancode_t> GetScanCodesForSwitchStates(uint64_t beforeLeft,
                                                    uint64_t afterLeft,
                                                    uint64_t beforeRight,
                                                    uint64_t afterRight);
void PerformActionsForScanCodes(const std::vector<scancode_t>& scanCodes);

