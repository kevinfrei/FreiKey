#pragma once

#include "sysstuff.h"

struct ClientState {
  uint8_t battery;
  uint8_t latency;
  bool connected;
  ClientState() : battery(0xff), latency(0), connected(false) {}
  ClientState(const ClientState& cs)
      : battery(cs.battery), latency(cs.latency), connected(cs.connected) {}
  bool operator!=(const ClientState& cs) const {
    return battery != cs.battery || latency != cs.latency ||
           connected != cs.connected;
  }
};

struct GeneralState {
  ClientState left, right;
  char* debugString;
  uint8_t layers[8];
  GeneralState() : left(), right(), debugString(nullptr) {
    memset(&layers[0], 0, sizeof(layers));
  }
  GeneralState(const GeneralState& gs)
      : left(gs.left), right(gs.right), debugString(gs.debugString) {
    memcpy(&layers[0], &gs.layers[0], sizeof(layers));
  }
  bool operator!=(const GeneralState& gs) const {
    if (left != right)
      return true;
    if (memcmp(&layers[0], &gs.layers[0], sizeof(layers)) != 0)
      return true;
    if (debugString == gs.debugString)
      return false;
    if (!debugString || !gs.debugString)
      return true;
    return !strcmp(debugString, gs.debugString);
  }
};

extern GeneralState curState;