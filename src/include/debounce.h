#if !defined(DEBOUNCE_H)
#define DEBOUNCE_H

#include "boardio.h"

BoardIO::bits debounce(BoardIO::bits cur_switches, uint32_t now);

#endif
