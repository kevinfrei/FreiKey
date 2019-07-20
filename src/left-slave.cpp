#include "mybluefruit.h"

#include "client.h"

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the physical pin numbers...
constexpr BoardIO LeftBoard = {
    {15, 2, 16, 7, 30, 27, 11}, {5, 12, 13, 28, 4, 3}, 29};

Client LeftClient{LeftBoard};

void setup() {
  LeftClient.setup(LHS_NAME);
}

void loop() {
  LeftClient.loop();
}
