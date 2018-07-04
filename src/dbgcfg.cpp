#include <bluefruit.h>

#include "dbgcfg.h"

#if defined(DEBUG) || defined(LOGGING)

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

void dumpHex(uint16_t v, const char *header) {
  dumpHex(static_cast<unsigned long>(v), header);
}

void dumpHex(uint8_t v, const char *header) {
  dumpHex(static_cast<unsigned long>(v), header);
}

void dumpHex(bool v, const char *header) {
  dumpHex(static_cast<unsigned long>(v), header);
}

void dumpHex(uint64_t v, const char *header) {
  if (header) 
    Serial.print(header);
  Serial.print(static_cast<unsigned long>(v >> 32), HEX);
  Serial.print("|");
  Serial.println(static_cast<unsigned long>(v), HEX);
}

#endif
