#include "sysstuff.h"

#include "dbgcfg.h"
#include "helpers.h"

#if defined(DEBUG)

void dumpVal(uint32_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v);
}

void dumpHex(uint32_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v, HEX);
}

void dumpHex(uint16_t v, const char* header) {
  dumpHex(static_cast<unsigned long>(v), header);
}

void dumpHex(uint8_t v, const char* header) {
  dumpHex(static_cast<unsigned long>(v), header);
}

void dumpHex(bool v, const char* header) {
  dumpHex(static_cast<unsigned long>(v), header);
}

void dumpHex(uint64_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.printf("0x%08x|0x%08x\n",
                static_cast<uint32_t>(v >> 32),
                static_cast<uint32_t>(v));
}

#endif

