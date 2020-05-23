#pragma once

#include "sysstuff.h"

#include <array>

#include "bit_array.h"

template <uint8_t pinLED>
struct Analog_LED {
  static void ConfigLED() {
    pinMode(pinLED, OUTPUT);
    delay(1);
    analogWrite(pinLED, 0);
  }
  static void setLED(uint32_t brightness) {
    analogWrite(pinLED, brightness);
  }
};

struct No_Analog_LED {
  static void setLED(uint32_t brightness) {
    // Do nothing: Maybe in the future do something else?
  }
};

template <uint8_t tRED, uint8_t tBLUE>
struct Digital_LEDs {
  static void ConfigLEDs() {
    pinMode(tRED, OUTPUT);
    pinMode(tBLUE, OUTPUT);
  }
  static void setRed(bool on) {
    digitalWrite(tRED, on ? HIGH : LOW);
  }
  static void setBlue(bool on) {
    digitalWrite(tBLUE, on ? HIGH : LOW);
  }
};

template <uint8_t batPin>
struct Battery {
  // pin 31 on the 832, pin 30 on the 840, is available for sampling the battery
  static constexpr uint8_t VBAT_PIN = batPin;

  // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
  static constexpr uint32_t VBAT_NUM = 3000;
  static constexpr uint32_t VBAT_DEN = 4096;

  static void ConfigBattery() {
    analogReference(AR_INTERNAL_3_0);
    analogReadResolution(12);
    delay(1);
  }

  // This stuff shamelessly stolen from the AdaFruit example
  static uint8_t getBatteryPercent() {
    uint32_t bat = analogRead(VBAT_PIN) * VBAT_NUM / VBAT_DEN;
    if (bat >= 3000) {
      return 100;
    } else if (bat > 2900) {
      return 100 - ((3000 - bat) * 58) / 100;
    } else if (bat > 2740) {
      return 42 - ((2900 - bat) * 24) / 160;
    } else if (bat > 2440) {
      return 18 - ((2740 - bat) * 12) / 300;
    } else if (bat > 2100) {
      return 6 - ((2440 - bat) * 6) / 340;
    } else {
      return 0;
    }
  }
};

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

#include "mpu.h"

#include "board-instance.h"


#if defined(CLIENT)

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
using MatrixBits = bit_array<RemoteBoard::numcols * RemoteBoard::numrows>;
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
