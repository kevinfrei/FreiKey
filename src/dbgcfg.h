#if !defined(DBGCFG_H)
#define DBGCFG_H

// This is just a couple of dumpers that show stuff on the AdaFruit serial port,
// and a couple of macros to do stuff when the system is build with DEBUG=1 (or
// 2). Set the DEBUG flag in the Makefile :)

#if DEBUG
#define DBG(a) a

void dumpVal(unsigned long v, const char* header = nullptr);
void dumpHex(unsigned long v, const char* header = nullptr);

#if DEBUG == 2
#define DBG2(a) a
#else
#define DBG2(a)
#endif
#else
#define DBG(a)
#define DBG2(a)
#endif

#endif
