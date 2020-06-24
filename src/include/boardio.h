#pragma once

#include "bit_array.h"
#include "board-instance.h"

#if defined(BTLE_CLIENT)

#if defined(RIGHT)
using BoardIO = RightBoard;
#elif defined(LEFT)
using BoardIO = LeftBoard;
#else
#error You must select a left or right client
#endif

#else

#if defined(FREIKEYS)
struct RemoteBoard {
  static constexpr uint8_t numcols = 7;
  static constexpr uint8_t numrows = 6;
};
using BoardIO = RemoteBoard;
#elif defined(KARBON)
struct RemoteBoard {
  static constexpr uint8_t numcols = 6;
  static constexpr uint8_t numrows = 6;
};
using BoardIO = RemoteBoard;
#elif defined(BETTERFLY)
using BoardIO = BoardIOBase<12>;
#else
#error You must define a target for the number of columns on the board
#endif

#endif

using MatrixBits = bit_array<BoardIO::numcols * BoardIO::numrows>;
