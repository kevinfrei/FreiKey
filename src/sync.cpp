#include "sync.h"
#include "dongle.h"

// I need to build a damn state machine for this
// External inputs:
//  Time
//  Side connection/Disconnection
//  Sync response(s)
//  Keypresses
// States:
// "Less than 2 sides connected":
//    no state transition, return
// "Two sides just connected" =>
//    go to "Start full sync" state
// "Start full sync" state =>
//    send a sync on a side, go to "waiting for a full sync"
// "Waiting for a full sync" =>
//
// "Both sides connected" =>
//    Every X seconds, go to "Single sync begin"
//    if no keys hit for X seconds, go to 'pause syncing'
// Single sync begin =>
//    send a sync on a side, go to "waiting for a single sync"
// Waiting for a single sync =>
//    if it's been too long, go to "cancel a single sync"
//

void Sync::Buffer(uint32_t time, state::hw& left, state::hw& right) {
  // We're called for every loop
  // If we're just waiting for a sync return, do nothing
}

void Sync::ReportSync(bool isLeft, uint8_t latency) {
}

#if 0
// We need to delay the master by a little bit to prevent mis-timing
bool dataWaiting = false;
uint32_t dataTime;
uint64_t switchData;
// # of milliseconds to delay the local keyboard before reporting
// It's kind of surprising how annoying the latency is when I get typing fast...
constexpr uint32_t DELAY = 8;

  // This is the master-side buffering code
  if (downRight.switches != rightSide.switches) {
    // There's a change: put it in the delay buffer
    if (dataWaiting) {
      if (switchData != downRight.switches) {
        // We already have a different change buffered, report it early :/
        std::swap(switchData, downRight.switches);
        dataTime = now;
      } else if (now - dataTime > DELAY) {
        // There's no change from what we're reading, but it's time to report
        dataWaiting = false;
      } else {
        // No changes from the buffered data
        // Sit on this change (i.e. revert to previous)
        downRight.switches = rightSide.switches;
      }
    } else {
      // We have no pending change: Just queue up this one
      dataWaiting = true;
      dataTime = now;
      switchData = downRight.switches;
      downRight.switches = rightSide.switches;
    }
  } else {
    // We've observed the same thing we've already reported
    if (dataWaiting && now - dataTime > DELAY) {
      // we have waiting data ready to report
      std::swap(downRight.switches, switchData);
    dataWaiting = false;
    }
 }
#endif
