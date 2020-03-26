#include "sync.h"
#include "dongle.h"
#include "master-comm.h"

// I need to build a damn state machine for this
// External inputs:
//  Time
//  Side connection/Disconnection
//  Sync response(s)
//  Keypresses
//  States:
// "Less than 2 sides connected": Do nothing
// "Two sides just connected" : Start Full Sync
//   "Start Full Sync"
//    "Left Sent"
//    "Left Received"
//    "Right Sent"
//    "Right Received"
//   "End Full Sync"
// "Both sides connected (not new)": Do nothing
// "Both sides connected, check sync": Try a Sync
//  "Start a Sync": Pick a side (and flip it)
//   "L/R Sent"
//   "L/R Received"
//  "End the Sync"
#if DEBUG
const char* stateNames[] = {"BothNotConnected",
                            "BothSidesFirstConnected",
                            "StartFullSync",
                            "LeftSent",
                            "LeftReceived",
                            "RightSent",
                            "RightReceived",
                            "EndFullSync",
                            "BothSidesConnectedBoring",
                            "BothSidesConnectedPing",
                            "StartPing",
                            "LRSent",
                            "LRReceived",
                            "EndPing"};
#endif

bool Sync::Buffer(uint32_t time, state::hw& left, state::hw& right) {
  // Check for transitionary details
#if DEBUG == 2
  static Sync::State last = State::EndPing;
  static uint32_t lastTime = 0;
#endif
  bool done;
  do {
#if DEBUG == 2
    if (last != this->state || time - lastTime > 1000) {
      lastTime = time;
      last = this->state;
      Serial.println(stateNames[static_cast<uint32_t>(this->state)]);
    }
#endif
    done = true;
    switch (this->state) {
      case State::BothNotConnected:
        if (Dongle::BothSides()) {
          /* State Optimization */
          this->state = State::BothSidesFirstConnected;
          done = false;
        }
        break;
      case State::BothSidesFirstConnected:
        this->state = State::StartFullSync;
        done = false;
        break;
      case State::StartFullSync: /**/
        comm::send::sync(Dongle::leftUart);
        sendTime = time;
        this->state = State::LeftSent;
        isLeft = true;
        leftPacketReceived = false;
        //} // State Opt addition
        break;
      case State::LeftSent:
        if (leftPacketReceived) {
          /* State Optimization*/
          this->state = State::LeftReceived;
          done = false;
        }
        break;
      case State::LeftReceived: /**/
        comm::send::sync(Dongle::rightUart);
        sendTime = time;
        this->state = State::RightSent;
        isLeft = false;
        rightPacketReceived = false;
        //} // State Opt addition
        break;
      case State::RightSent:
        if (rightPacketReceived) {
          /* State Optimization*/
          this->state = State::RightReceived;
          done = false;
        }
        break;
      case State::RightReceived:
        this->state = State::EndFullSync;
        done = false;
        break;
      case State::EndFullSync: /**/
        if (!lLoc && !rLoc) {
          this->UpdateLatency();
          this->state = State::BothSidesConnectedBoring;
        } else {
          this->state = State::StartFullSync;
        }
        done = false;
        //} // State Opt addition
        break;
      case State::BothSidesConnectedBoring:
        if (lastTapOrPing && ((time - lastTapOrPing) > 5000)) {
          lastTapOrPing = 0;
          /* State Optimization*/
          this->state = State::BothSidesConnectedPing;
          done = false;
        }
        break;
      case State::BothSidesConnectedPing:
        this->state = State::StartPing;
        /**/
        isLeft = !isLeft;
        /* State Optimization*/
        done = false;
        break;
      case State::StartPing: /**/
        comm::send::sync(isLeft ? Dongle::leftUart : Dongle::rightUart);
        sendTime = time;
        this->state = State::LRSent;
        //} // State Opt Addition
        break;
      case State::LRSent:
        if (isLeft ? leftPacketReceived : rightPacketReceived) {
          /* State Optimization*/
          this->state = State::LRReceived;
          done = false;
        }
        break;
      case State::LRReceived:
        this->state = State::EndPing;
        done = false;
        break;
      case State::EndPing:
        /**/
        this->state = State::BothSidesConnectedBoring;
        this->UpdateLatency();
        lastTapOrPing = 0;
        //} // State Opt Addition
        break;
      default:
        break;
    }
  } while (!done);
  if (left.switches.any() || right.switches.any()) {
    lastTapOrPing = time;
  }
  return lLatency < rLatency;
}

void Sync::ReportSync(bool isReportLeft) {
  uint32_t time = millis();
  uint32_t delta = time - sendTime;
  if (delta > 255)
    // TODO: Handle timeouts/response too slow scenarios
    delta = 255;
  if (isReportLeft) {
    lLoc = (lLoc + 1) % sampleSize;
    lsamples[lLoc] = delta & 0xFF;
    leftPacketReceived = true;
  } else {
    rLoc = (rLoc + 1) % sampleSize;
    rsamples[rLoc] = delta & 0xFF;
    rightPacketReceived = true;
  }
#if DEBUG == 2
  Serial.println("Sample Recevied:");
  for (int i = 0; i < sampleSize; i++) {
    Serial.printf("Left: %3d\t Right %3d\n",
                  (uint32_t)lsamples[i],
                  (uint32_t)rsamples[i]);
  }
#endif
}

void Sync::UpdateLatency() {
  uint8_t maxL = 0, maxR = 0;
  uint8_t minL = 255, minR = 255;
  uint32_t sumL = 0, sumR = 0;
  for (uint8_t i = 0; i < sampleSize; i++) {
    auto l = lsamples[i];
    auto r = rsamples[i];
    if (l < minL)
      minL = l;
    if (r < minR)
      minR = r;
    if (l > maxL)
      maxL = l;
    if (r > maxR)
      maxR = r;
    sumL += l;
    sumR += r;
  }
  lLatency = (sumL - minL - maxL) / ((sampleSize - 2) * 2);
  rLatency = (sumR - minR - maxR) / ((sampleSize - 2) * 2);
  DELAY = abs(lLatency - rLatency);
  DBG(dumpVal(lLatency, "Left latency: "));
  DBG(dumpVal(rLatency, "Right latency: "));
}

void Sync::Delay(uint32_t now, state::hw& down, state::hw& prev) {
  // We need to delay the master by a little bit to prevent mis-timing
  // bool dataWaiting = false;
  // uint32_t dataTime;
  // uint64_t switchData;
  // # of milliseconds to delay the local keyboard before reporting
  // It's kind of surprising how annoying the latency is when I get typing
  // fast...
  // constexpr uint32_t DELAY = 8;

  // This is the master-side buffering code

  if (down.switches != prev.switches) {
    // There's a change: put it in the delay buffer
    if (dataWaiting) {
      if (delayData != down.switches) {
        // We already have a different change buffered, report it early :/
        std::swap(delayData, down.switches);
        dataTime = now;
      } else if (now - dataTime > DELAY) {
        // There's no change from what we're reading, but it's time to report
        dataWaiting = false;
      } else {
        // No changes from the buffered data
        // Sit on this change (i.e. revert to previous)
        down.switches = prev.switches;
      }
    } else {
      // We have no pending change: Just queue up this one
      dataWaiting = true;
      dataTime = now;
      delayData = down.switches;
      down.switches = prev.switches;
    }
  } else {
    // We've observed the same thing we've already reported
    if (dataWaiting && now - dataTime > DELAY) {
      // we have waiting data ready to report
      std::swap(down.switches, delayData);
      dataWaiting = false;
    }
  }
}

void Sync::Process(uint32_t now,
                   state::hw& left,
                   state::hw& prevL,
                   state::hw& right,
                   state::hw& prevR) {
  if (timeSync.Buffer(now, left, right)) {
    timeSync.Delay(now, left, prevL);
  } else {
    timeSync.Delay(now, right, prevR);
  }
}
