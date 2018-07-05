#include <bluefruit.h>

#include "pindata.h"


uint64_t PinData::Read() const {
  uint64_t switches = 0;
  for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
    uint64_t val = 1ULL << colNum;
    digitalWrite(cols[colNum], LOW);
    for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
      if (!digitalRead(rows[rowNum])) {
        switches |= val << (rowNum * numcols);
      }
    }
    digitalWrite(cols[colNum], HIGH);
  }
  return switches;
}
