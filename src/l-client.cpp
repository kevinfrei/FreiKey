#include "sysstuff.h"

#include "kbclient.h"

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the "physical" pin numbers...
constexpr BoardIO LeftBoard = {
    {15, A0, 16, 7, A6, 27, 11}, {A3, 12, 13, A4, A2, A1}, A5};
KBClient theClient{LeftBoard};
void setup() {
  theClient.setup(LTCL_NAME);
}

void loop() {
  theClient.loop();
}
