#pragma once

#include "sysstuff.h"

#include <array>
#include "bit_array.h"


template <typename T, uint8_t nCols, uint8_t nRows, uint8_t... cols_then_rows>
struct KeyMatrix {
  static constexpr uint8_t numcols = nCols;
  static constexpr uint8_t numrows = nRows;
  static constexpr uint8_t matrix_size = numcols * numrows;
  typedef bit_array<matrix_size> bits;
  static constexpr uint8_t byte_size = bits::num_bytes;

  static void ConfigMatrix() {
    // For my wiring, the columns are output, and the rows are input...
    std::array<uint8_t, nCols + nRows> c_r{cols_then_rows...};
    for (uint8_t pn = 0; pn < nCols + nRows; pn++) {
      if (pn < nCols) {
        DBG(dumpVal(c_r[pn], "Output Pin "));
        T::configOutputPin(c_r[pn]);
      } else {
        DBG(dumpVal(c_r[pn], "Input Pullup "));
        T::configInputPin(c_r[pn]);
      }
    }
  };

  // This is the core place to simulate the keyboard for mocking
  // (at least in the betterfly config)
  static bits Read() {
    std::array<uint8_t, nCols + nRows> c_r{cols_then_rows...};
    bits switches{};
    for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
      T::prepPinForRead(c_r[colNum]);
      delay(1); // TODO: Make this faster (which it microseconds)
      for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
        if (!digitalRead(c_r[nCols + rowNum])) {
          switches.set_bit(rowNum * numcols + colNum);
        }
      }
      T::completePin(c_r[colNum]);
    }
    return switches;
  }
};