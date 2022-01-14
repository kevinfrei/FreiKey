#pragma once

#include "sysstuff.h"

#include <array>

#include "dbgcfg.h"
#include "keyhelpers.h"

#if defined(BTLE_HOST)
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
#endif

struct State {
  static constexpr uint8_t layer_max = 7;
  char* debugString;
  uint8_t layer_pos;
  std::array<uint8_t, layer_max + 1> layer_stack;
  State() : debugString(nullptr), layer_pos(0) {
    layer_stack.fill(0);
  }
  State(const State& gs)
      : debugString(gs.debugString),
        layer_pos(gs.layer_pos),
        layer_stack(gs.layer_stack) {}
  void reset() {
    layer_pos = 0;
    layer_stack[0] = 0;
  }
  bool operator!=(const State& gs) const {
    if (gs.layer_pos != layer_pos)
      return true;
    if (layer_stack != gs.layer_stack)
      return true;
    if (debugString == gs.debugString)
      return false;
    if (!debugString || !gs.debugString)
      return true;
    return !strcmp(debugString, gs.debugString);
  }
  void push_layer(layer_t layer) {
    DBG(dumpVal(layer, "Push "));
    if (layer_pos < layer_max)
      layer_stack[++layer_pos] = layer;
    DBG(dumpLayers());
  }
  void toggle_layer(layer_t layer) {
    // Toggling a layer: If it exists *anywhere* in the layer stack, turn it
    // off (and fold the layer stack down) If it's *not* in the layer stack,
    // add it.
    for (uint8_t l = layer_pos; l != 0; l--) {
      if (layer_stack[l] == layer) {
        DBG(dumpVal(layer, "Turning off layer "));
        DBG(dumpVal(l, "at location "));
        if (layer_pos != l) {
          DBG(dumpVal(layer_pos - l, "Shifting by "));
          for (int i = l; i < layer_max; i++) {
            layer_stack[i] = layer_stack[i + 1];
          }
        }
        layer_pos--;
        DBG(dumpLayers());
        return;
      }
    }
    DBG(Serial.print("(For Toggle) "));
    push_layer(layer);
  }
  void pop_layer(layer_t layer) {
    DBG(dumpVal(layer, "Pop "));
    if (layer_pos > 0 && layer_stack[layer_pos] == layer) {
      // Easy-peasy
      --layer_pos;
    } else {
      for (uint8_t l = layer_pos; l != 0; l--) {
        if (layer_stack[l] == layer) {
          DBG(dumpVal(layer, "Turning off layer "));
          DBG(dumpVal(l, "at location "));
          if (layer_pos != l) {
            DBG(dumpVal(layer_pos - l, "Shifting by "));
            for (int i = l; i < layer_max; i++) {
              layer_stack[i] = layer_stack[i + 1];
            }
          }
          layer_pos--;
          DBG(dumpLayers());
          break;
        }
      }
    }
    DBG(dumpLayers());
  }
  void switch_layer(layer_t layer) {
    DBG(dumpVal(layer_stack[layer_pos], "Switching layer "));
    DBG(dumpVal(layer, "to layer "));
    layer_stack[layer_pos] = layer;
    DBG(dumpLayers());
  }
#if defined(DEBUG)
  void dumpLayers() {
    Serial.print("Layer stack: ");
    for (int i = 0; i <= layer_pos; i++) {
      Serial.print(layer_stack[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
#endif
};

#if defined(BTLE_HOST)
class KarbonState : public State {
  ClientState left, right;
  public:
  KarbonState() : left(), right(), State() {}
  KarbonState(const KarbonState &ks) : left(ks.left), right(ks.right), State(ks) {}
  bool operator !=(const KarbonState &ks) const {
    if (gs.left != left || gs.right != right)
      return true;
    return State::operator!=(ks);
  }
};
using GeneralState = KarbonState;
#else
using GeneralState = State;
#endif

extern GeneralState curState;
