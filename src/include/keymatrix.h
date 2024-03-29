#pragma once

#include "sysstuff.h"

#include <array>
#include <bitset>

#include "dbgcfg.h"

enum DIODE_DIR { ROW_TO_COL, COL_TO_ROW };

template <typename T,
          DIODE_DIR dDir,
          uint8_t nCols,
          uint8_t nRows,
          uint8_t... cols_then_rows>
class KeyMatrix {
 public:
  static constexpr uint8_t numcols = nCols;
  static constexpr uint8_t numrows = nRows;
  static constexpr uint8_t matrix_size = numcols * numrows;

  typedef std::bitset<matrix_size> bits;

  static constexpr uint8_t byte_size = (matrix_size + 7) / 8;

 private:
  typedef std::array<uint8_t, nCols + nRows> ColsRows;

  static inline uint8_t colPin(uint8_t col) {
    constexpr ColsRows c_r{cols_then_rows...};
    return c_r[col];
  }
  static inline uint8_t rowPin(uint8_t row) {
    constexpr ColsRows c_r{cols_then_rows...};
    return c_r[nCols + row];
  }

 public:
  static void ConfigMatrix() {
    if (dDir == DIODE_DIR::COL_TO_ROW) {
      // For my wiring, the columns are output, and the rows are input...
      for (uint8_t cn = 0; cn < nCols; cn++) {
        Dbg2 << "Output Pin " << colPin(cn) << sfmt::endl;
        T::configOutputPin(colPin(cn));
      }
      for (uint8_t rn = 0; rn < nRows; rn++) {
        Dbg2 << "Input Pullup " << rowPin(rn) << sfmt::endl;
        T::configInputPin(rowPin(rn));
      }
    } else {
      // For my wiring, the columns are output, and the rows are input...
      for (uint8_t cn = 0; cn < nCols; cn++) {
        Dbg2 << "Column Pin " << colPin(cn) << sfmt::endl;
        T::configInputPin(colPin(cn));
      }
      for (uint8_t rn = 0; rn < nRows; rn++) {
        Dbg2 << "Row Pullup " << rowPin(rn) << sfmt::endl;
        T::configOutputPin(rowPin(rn));
      }
    }
  };

  // This is the core place to simulate the keyboard for mocking,
  static bits Read() {
    bits switches{};
    if (dDir == DIODE_DIR::COL_TO_ROW) {
      for (uint8_t colNum = 0; colNum < numcols; ++colNum) {
        T::prepPinForRead(colPin(colNum));
        for (uint8_t rowNum = 0; rowNum < numrows; ++rowNum) {
          if (digitalRead(rowPin(rowNum)) == LOW) {
            switches.set(rowNum * numcols + colNum);
          }
        }
        T::completePin(colPin(colNum));
      }
    } else {
      for (uint8_t rowNum = 0; rowNum < numrows; ++rowNum) {
        T::prepPinForRead(rowPin(rowNum));
        for (uint8_t colNum = 0; colNum < numcols; ++colNum) {
          if (digitalRead(colPin(colNum)) == LOW) {
            switches.set(rowNum * numcols + colNum);
          }
        }
        T::completePin(rowPin(rowNum));
      }
    }
    return switches;
  }

#if defined(ADAFRUIT_NRF52_ARDUINO) && defined(USE_INTERRUPTS)
  // TODO: This stuff isn't DIODE_DIRECTION aware
  static void setInterrupts(void (*handler)()) {
    for (uint8_t colNum = 0; colNum < numcols; colNum++) {
      T::prepForInterrupt(colPin(colNum));
    }
    // I hate this sort of crap, but it seems necessary...
    delay(1);
    for (uint8_t rowNum = 0; rowNum < numrows; rowNum++) {
      attachInterrupt(
        digitalPinToInterrupt(rowPin(rowNum)), handler, ISR_DEFERRED | CHANGE);
    }
  }

  static void clearInterrupts() {
    for (uint8_t rowNum = 0; rowNum < numrows; rowNum++) {
      detachInterrupt(digitalPinToInterrupt(rowPin(rowNum)));
    }
    // I hate this sort of crap, but it seems necessary :/
    delay(1);
    for (uint8_t colNum = 0; colNum < numcols; colNum++) {
      T::restoreFromInterrupt(colPin(colNum));
    }
  }
#endif
};
