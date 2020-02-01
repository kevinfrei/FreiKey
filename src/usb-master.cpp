#include "sysstuff.h"

#include "comm.h"
#include "dbgcfg.h"
#include "dongle.h"
#include "hardware.h"
#include "helpers.h"
#include "kbreporter.h"
#include "keymap.h"
#include "keystate.h"
#include "scanner.h"
#include "sync.h"

// I'm going to update this to keep track of additional state.
// Each key 'previously' pressed should have a 'time last pressed'
// Maybe keep track of whether other keys have been pressed since?
//  Perhaps have a flag for something that's a "Normal" key?
// The core idea:
//  I want to be able to trigger something off of both the "key pressed"
//  as well as the "key released". In addition, I want to do things that
//  'cancel out' the key state if something specific occurs

// Kind of things I want to do:
// #2: Key-up triggering
// #3: Cancellation
// #4: Key-state back & forth (caps as a real cmd/ctrl, instead of a layer
// shift)

state::hw leftSide{};
state::hw rightSide{};

// This is called when a device connects, disconnects, and when the system is
// initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  layer_pos = 0;
  layer_stack[0] = 0;
  leftSide = state::hw{};
  rightSide = state::hw{};
  memset(keyStates, null_scan_code, sizeof(keyStates));
  Dongle::Reset();
}

// Check to see if we should update the battery level and if so, do so
void updateBatteryLevel(const state::hw& downLeft, const state::hw& downRight) {
  if (downRight.battery_level != rightSide.battery_level ||
      downLeft.battery_level != leftSide.battery_level) {
    // We only get the battery level from the left side once you hit a key, so
    // only report it if we have something to actually report
    // TODO: Update something here.
    rightSide.battery_level = downRight.battery_level;
    leftSide.battery_level = downLeft.battery_level;
  }
}

uint32_t lastTime;
Sync timeSync{};

void loop() {
  uint32_t now = millis();
  Dongle::updateClientStatus(now);
  if (!Dongle::Ready())
    return;
  //  // Remote wakeup
  //  if ( tud_suspended() && btn )
  //  {
  //    // Wake up host if we are in suspend mode
  //    // and REMOTE_WAKEUP feature is enabled by host
  //    tud_remote_wakeup();
  //  }

  // Get the hardware state for the two sides...
  state::hw downRight{Dongle::rightUart, rightSide};
  state::hw downLeft{Dongle::leftUart, leftSide};

  // Deal with synchonization
  timeSync.Process(now, downLeft, leftSide, downRight, rightSide);

  // Update the combined battery level
  updateBatteryLevel(downLeft, downRight);

  // Get the before & after of each side into the bit array
  BoardIO::bits beforeLeft{leftSide.switches};
  BoardIO::bits afterLeft{downLeft.switches};
  BoardIO::bits beforeRight{rightSide.switches};
  BoardIO::bits afterRight{downRight.switches};

  BoardIO::bits deltaLeft = beforeLeft.delta(afterLeft);
  BoardIO::bits deltaRight = beforeRight.delta(afterRight);
  bool keysChanged = deltaLeft.any() || deltaRight.any();

  while (deltaLeft.any() || deltaRight.any()) {
    scancode_t sc;
    bool pressed;
    if (deltaLeft.any()) {
      sc = getNextScanCode(deltaLeft, afterLeft, pressed);
    } else {
      // Add offset to the right scan code...
      sc = getNextScanCode(deltaRight, afterRight, pressed) +
           BoardIO::matrix_size;
    }
    preprocessScanCode(sc, pressed, now);
  }

  if (keysChanged) {
    kb_reporter rpt;
    ProcessKeys(now, rpt);

    // Update the hardware previous state
    rightSide = downRight;
    leftSide = downLeft;
    DBG2(Serial.println("============================="));
    DBG2(Serial.print("Left side "));
    DBG2(downLeft.dump());
    DBG2(Serial.print("Right side "));
    DBG2(downRight.dump());

    // Update the layer color on the dongle
    uint32_t color = getColorForCurrentLayer();
    Dongle::setRGB((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
  }

  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}

// In Arduino world the 'setup' function is called to initialize the device.
// The 'loop' function is called over & over again, after setup completes.
void setup() {
  Dongle::Configure();
  resetTheWorld();
  Dongle::StartListening();
  lastTime = millis();
}
