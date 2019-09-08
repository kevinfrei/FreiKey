#pragma once

#include "sysstuff.h"

namespace state {
  class kb {
    // Active layer
    // Current 'down' keys?

    // Operations:
    // Not sure the right return type yet
    // Possible results:
    //  A HID keyreport (mods + keys)
    //  A consumer key press
    //  An "LED state" change
    //  An *internal only* state change (i.e. nothing)
    //  A list of most everything above
    void resolveChanges(uint64_t beforeLeft, uint64_t afterleft, uint64_t beforeRight, uint64_t afterRight);
  };
}
