#include "keystate.h"

class Scanner {

 public:
  // This is the interface that needs filled in:

  // Called during setup, and maybe in response to something else?
  // It should reset all global state
  static void Reset();

  // Constructs the scan-loop-invoke local state for this time through
  Scanner(uint32_t now);
  // Gets the next scan code to be (pre)processed
  scancode_t getNextCode(bool& pressed);
  // Called once we've completed processing the keys (prep for next loop)
  void Done();
};