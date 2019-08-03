#pragma once

#include "boardio.h"

BoardIO::bits debounce(BoardIO::bits cur_switches, uint32_t now);
