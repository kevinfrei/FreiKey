#include "sysstuff.h"

#include "dbgcfg.h"

#if defined(DEBUG)

void dumpVal(uint32_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v);
}

void dumpVal(layer_num l, const char* header) {
  dumpVal(static_cast<uint32_t>(l), header);
}

void dumpHex(uint32_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v, HEX);
}

void dumpHex(uint16_t v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(Modifiers v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(Keystroke v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(Consumer v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(uint8_t v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(bool v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(uint64_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.printf("0x%08x|0x%08x\n",
                static_cast<uint32_t>(v >> 32),
                static_cast<uint32_t>(v));
}

#endif
