#include <bluefruit.h>

#include "boardio.h"
#include "dbgcfg.h"
#include "hardware.h"
#include "led_states.h"

BLEDis bledis;
BLEUart bleuart;
state::hw lastRead{};

// These numbers correspond to the *port pin* numbers in the nRF52 documentation
// not the physical pin numbers...
constexpr BoardIO LeftBoard = {
    {15, 2, 16, 7, 30, 27, 11}, {5, 12, 13, 28, 4, 3}, 29};

void setup() {
  state::shared_setup(LeftBoard);
  Bluefruit.begin();
  // Turn off the Bluetooth LED
  Bluefruit.autoConnLed(false);
  // I had turned this all the way down. Given that my receiver is less than 20
  // cm away, I didn't know if it would be enough. I bumped it up to 20, because
  // it seemed like I was occasionally seeing weirdness that I wasn't when it
  // was set at 0. If you spread your keyboards apart greater distance, you may
  // want to try higher power. Acceptable values are -40, -30, -20, -16, -12,
  // -8, -4, 0, 4
  Bluefruit.setTxPower(0);
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

const state::led* curState = nullptr;
uint32_t stateTime = 0;
uint32_t lastPressTime = 0;
bool sleeping = false;

bool checkForSleeping(bool sleeping,
                      const state::hw& down,
                      uint32_t time,
                      uint32_t& lastPressTime) {
  // First, handle sleeping states
  if (down.switches) {
    // We detected a keypress!
    lastPressTime = time;
    return false;
  } else if (!sleeping && (time - lastPressTime > 300000)) {
    // 5 minutes before we sleep
    // Do other stuff to get into low power mode, here!
    return true;
  }
  return sleeping;
}

// TODO: Add bidirectional communication, so the master can ask for info or set
// an LED state somehow
void loop() {
  uint32_t time = millis();
  state::hw down{time, lastRead, LeftBoard};

  bool oldSleeping = sleeping;
  sleeping = isSleeping(sleeping, down, time, lastPressTime);
  if (sleeping) {
    // This should make the LED 'breathe' a bit
    uint8_t brightness = (time >> 9) & 0x1F;
    if (brightness > 0x10)
      brightness = 0x20 - brightness;
    LeftBoard.setLED(brightness);
    // I'm assuming this saves power. If it doesn't, there's no point...
    delay(250);
    waitForEvent();
    return;
  }
  if (oldSleeping) {
    LeftBoard.setLED(0);
  }

  if (down != lastRead) {
    lastRead = down;
    DBG2(down.dump());
    down.send(bleuart, lastRead);
    if (!curState) {
      // if we're not already in a state, check to see if we're transitioning
      // into one
      curState = state::led::get(down);
      if (curState) {
        stateTime = time;
      }
    }
  }
  if (curState) {
    // We're in "Check if battery is getting kinda low" mode
    if (time - curState->time < stateTime) {
      LeftBoard.setLED(curState->get_led_value(down, time - stateTime));
    } else {
      LeftBoard.setLED(0);
      curState = nullptr;
    }
  }
  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}
