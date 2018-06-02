#include <bluefruit.h>

#include "dbgcfg.h"

#if DEBUG

void dumpVal(unsigned long v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v);
}

void dumpHex(unsigned long v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v, HEX);
}

#endif
