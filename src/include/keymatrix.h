#pragma once

#include "sysstuff.h"

#include "bit_array.h"
#include <array>

template <typename T, uint8_t nCols, uint8_t nRows, uint8_t... cols_then_rows>
struct KeyMatrix {
  static constexpr uint8_t numcols = nCols;
  static constexpr uint8_t numrows = nRows;
  static constexpr uint8_t matrix_size = numcols * numrows;
  typedef bit_array<matrix_size> bits;
  static constexpr uint8_t byte_size = bits::num_bytes;
  typedef std::array<uint8_t, nCols + nRows> ColsRows;

  static inline uint8_t colPin(uint8_t col) {
    constexpr ColsRows c_r{cols_then_rows...};
    return c_r[col];
  }
  static inline uint8_t rowPin(uint8_t row) {
    constexpr ColsRows c_r{cols_then_rows...};
    return c_r[nCols + row];
  }

  static void ConfigMatrix() {
    // For my wiring, the columns are output, and the rows are input...
    for (uint8_t cn = 0; cn < nCols; cn++) {
      DBG(dumpVal(colPin(cn), "Output Pin "));
      T::configOutputPin(colPin(cn));
    }
    for (uint8_t rn = 0; rn < nRows; rn++) {
      DBG(dumpVal(rowPin(rn), "Input Pullup "));
      T::configInputPin(rowPin(rn));
    }
  };

  // This is the core place to simulate the keyboard for mocking
  // (at least in the betterfly config)
  static bits Read() {
    bits switches{};
    for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
      T::prepPinForRead(colPin(colNum));
      for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
        if (!digitalRead(rowPin(rowNum))) {
          switches.set_bit(rowNum * numcols + colNum);
        }
      }
      T::completePin(colPin(colNum));
    }
    return switches;
  }

  static void setInterrupts(void (*handler)()) {
    DBG(Serial.println("Enabling HW Interrupts"));
    for (uint8_t colNum = 0; colNum < numcols; colNum++) {
      T::prepForInterrupt(colPin(colNum));
    }
    // I hate this sort of crap, but it seems necessary...
    delay(1);
    for (uint8_t rowNum = 0; rowNum < numrows; rowNum++) {
      attachInterrupt(digitalPinToInterrupt(rowPin(rowNum)), handler, CHANGE);
    }
    DBG(Serial.println("HW Interrupts Enabled"));
  }

  static void clearInterrupts() {
    DBG(Serial.println("Disabling HW Interrupts"));
    for (uint8_t rowNum = 0; rowNum < numrows; rowNum++) {
      detachInterrupt(digitalPinToInterrupt(rowPin(rowNum)));
    }
    // I hate this sort of crap, but it seems necessary :/
    delay(1);
    for (uint8_t colNum = 0; colNum < numcols; colNum++) {
      T::restoreFromInterrupt(colPin(colNum));
    }
    DBG(Serial.println("HW Interrupts Disabled"));
  }
};