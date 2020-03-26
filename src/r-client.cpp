#include "sysstuff.h"

#include "kbclient.h"

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the physical pin numbers...
/*constexpr BoardIO RightBoard = {
    {29, 16, 15, 7, 27, 11, 30}, {13, 4, 2, 3, 5, 12}, 28};*/
KBClient theClient{};

void setup() {
  theClient.setup(RTCL_NAME);
}

void loop() {
  theClient.loop();
}
