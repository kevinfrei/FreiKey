#include "sysstuff.h"

#include "dbgcfg.h"
#include "dongle.h"
#include "general.h"
#include "hardware.h"
#include "helpers.h"
#include "kbreporter.h"
#include "keymap.h"
#include "keystate.h"
#include "host-comm.h"
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

state::hw prevLeftSide{};
state::hw prevRightSide{};
MacroBits prevMacroPad{0};

// This is called when a device connects, disconnects, and when the system is
// initialized.
// The idea is that it should just wipe everything clean.
void resetTheWorld() {
  curState.reset();
  prevLeftSide = state::hw{};
  prevRightSide = state::hw{};
  prevMacroPad = MacroBits{0};
  memset(keyStates, null_scan_code, sizeof(keyStates));
  Dongle::Reset();
}

// Check to see if we should update the battery level and if so, do so
void updateBatteryLevel(const state::hw& downLeft, const state::hw& downRight) {
  if (downRight.battery_level != prevRightSide.battery_level ||
      downLeft.battery_level != prevLeftSide.battery_level) {
    // We only get the battery level from the left side once you hit a key, so
    // only report it if we have something to actually report
    // TODO: Update something here.
    prevRightSide.battery_level = downRight.battery_level;
    prevLeftSide.battery_level = downLeft.battery_level;
  }
}

uint32_t lastTime;
Sync timeSync{};

void loop() {
  uint32_t now = millis();
  Dongle::updateClientStatus(
      now, prevLeftSide.battery_level, prevRightSide.battery_level);
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
  state::hw downRight{Dongle::rightUart, prevRightSide};
  state::hw downLeft{Dongle::leftUart, prevLeftSide};

  // Deal with synchonization
  timeSync.Process(now, downLeft, prevLeftSide, downRight, prevRightSide);

  // Update the combined battery level
  updateBatteryLevel(downLeft, downRight);

  // Get the before & after of each side into the bit array
  MatrixBits beforeLeft{prevLeftSide.switches};
  MatrixBits afterLeft{downLeft.switches};
  MatrixBits beforeRight{prevRightSide.switches};
  MatrixBits afterRight{downRight.switches};
  MacroBits macro = Dongle::key_scan(now);

  MacroBits deltaPad = prevMacroPad.delta(macro);
  MatrixBits deltaLeft = beforeLeft.delta(afterLeft);
  MatrixBits deltaRight = beforeRight.delta(afterRight);
  bool keysChanged = deltaLeft.any() || deltaRight.any() || deltaPad.any();

  while (deltaLeft.any() || deltaRight.any() || deltaPad.any()) {
    scancode_t sc = 0xFF;
    bool pressed = false;
    if (deltaLeft.any()) {
      sc = getNextScanCode(deltaLeft, afterLeft, pressed);
    } else if (deltaRight.any()) {
      // Add offset to the right scan code...
      sc = getNextScanCode(deltaRight, afterRight, pressed) +
           MatrixBits::num_bits;
    } else if (deltaPad.any()) {
      sc = getNextScanCode(deltaPad, macro, pressed) + MatrixBits::num_bits * 2;
    } else {
      DBG(Serial.println("Unexpectedly still in this loop"));
      continue;
    }
    preprocessScanCode(sc, pressed, now);
  }

  if (keysChanged) {
    kb_reporter rpt;
    ProcessKeys(now, rpt);

    // Update the hardware previous state
    prevRightSide = downRight;
    prevLeftSide = downLeft;
    prevMacroPad = macro;
    DBG2(Serial.println("============================="));
    DBG2(Serial.print("Left side "));
    DBG2(downLeft.dump());
    DBG2(Serial.print("Right side "));
    DBG2(downRight.dump());

    // Update the layer color on the dongle
    uint32_t color = getColorForCurrentLayer();
    Dongle::setRGB(color);
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
