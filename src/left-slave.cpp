#include <bluefruit.h>

#include "dbgcfg.h"
#include "hwstate.h"
#include "shared.h"

BLEDis bledis;
BLEUart bleuart;
hwstate lastRead{};

void setup() {
  shared_setup();
  Bluefruit.begin();
  Bluefruit.autoConnLed(false);
  // I had turned this all the way down. Given that my receiver is less than 20
  // cm away, I didn't know if it would be enough. I bumped it up to 30, because
  // it seemed like I was occasionally seeing weirdness that I wasn't when it
  // was set at 0. If you spread your keyboards apart greater distance, you may
  // want to try higher power. Acceptable values are -40, -30, -20, -16, -12,
  // -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName(LHS_NAME);

  bledis.setManufacturer(MANUFACTURER);
  bledis.setModel(MODEL);
  bledis.begin();

  bleuart.begin();

  // Start Advertising the UART service to talk to the other half...
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30); // number of seconds in fast mode
  // I should probably stop advertising after a while if that's possible. I have
  // switches now, so if I need it to advertise, I can just punch the power.
  Bluefruit.Advertising.start(0); // 0 = Don't stop advertising after n seconds
}

void loop() {
  hwstate down{millis(), lastRead};

  if (down != lastRead) {
    lastRead = down;
    DBG2(down.dump());
    down.send(bleuart, lastRead);
  }
  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}
