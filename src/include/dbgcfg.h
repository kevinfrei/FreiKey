#pragma once

#include <cstdint>

// This is just a couple of dumpers that show stuff on the AdaFruit serial port,
// and a couple of macros to do stuff when the system is build with DEBUG=1 (or
// 2). Set the DEBUG flag in the Makefile :)
#if defined(DEBUG)
void dumpVal(uint32_t v, const char* header = nullptr);
void dumpHex(uint8_t v, const char* header = nullptr);
void dumpHex(uint16_t v, const char* header = nullptr);
void dumpHex(uint32_t v, const char* header = nullptr);
void dumpHex(uint64_t v, const char* header = nullptr);
void dumpHex(bool b, const char* header = nullptr);
#define DBG(a) a
#endif

#if defined(DEBUG) && DEBUG == 2
#define DBG2(a) a
#else
#define DBG2(a)
#endif

#if !defined(DEBUG)
#define DBG(a)
#define DBG2(a)
#endif
#define DBG3(a)

#if defined(__VSCODE_ONLY_)
// Stuff to make VSCode IntelliSense happy
// Don't seem to need this stuff now, which is helpful
#endif
