#pragma once

#include "sysstuff.h"

#include <array>

#include "dbgcfg.h"
#include "keyhelpers.h"

struct State {
  static constexpr uint8_t layer_max = 7;
  uint8_t layer_pos;
  std::array<layer_num, layer_max + 1> layer_stack;
  State() : layer_pos(0) {
    layer_stack.fill(layer_num::Base);
  }
  State(const State& gs)
    : layer_pos(gs.layer_pos), layer_stack(gs.layer_stack) {}
  void reset() {
    layer_pos = 0;
    layer_stack[0] = layer_num::Base;
  }
  layer_num getLayer(uint8_t index = 0xFF) const {
    return layer_stack[index == 0xFF ? layer_pos : index];
  }
  uint8_t getLayerVal(uint8_t index = 0xFF) const {
    return value_cast(getLayer(index));
  }
  bool operator!=(const State& gs) const {
    if (gs.layer_pos != layer_pos)
      return true;
    for (uint8_t idx = 0; idx <= layer_pos; idx++) {
      if (layer_stack[idx] != gs.layer_stack[idx])
        return true;
    }
    return false;
  }
  void push_layer(layer_num layer) {
    DBG(dumpVal(layer, "Push "));
    if (layer_pos < layer_max)
      layer_stack[++layer_pos] = layer;
    DBG(dumpLayers());
  }
  void toggle_layer(layer_num layer) {
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
  void pop_layer(layer_num layer) {
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
  int8_t find_layer(layer_num lyr) {
    for (int8_t l = layer_pos; l >= 0; l--) {
      if (layer_stack[l] == lyr) {
        return l;
      }
    }
    return -1;
  }
  void switch_layer(layer_num layer) {
    DBG(dumpVal(layer_stack[layer_pos], "Switching layer "));
    DBG(dumpVal(layer, "to layer "));
    layer_stack[layer_pos] = layer;
    DBG(dumpLayers());
  }

  /*
  void rotate_layer(action_t action) {
    // Check to see if any of the layers specified (except base?)
    layer_t lyr0 = getRot0(action);
    layer_t lyr1 = getRot1(action);
    layer_t lyr2 = getRot2(action);
    int8_t lp0 = find_layer(lyr0);
    int8_t lp1 = find_layer(lyr1);
    int8_t lp2 = find_layer(lyr2);
    int8_t top = std::max(std::max(lp0, lp1), lp2);
    layer_t active = layer_stack[top];
    pop_layer(active);
    if (active == lp2) {
      if (lp0 < 0) {
        push_layer(lp0);
      }
    } else if (active == lp1) {
      if (lp2 < 0) {
        push_layer(lp2);
      }
    } else if (active == lp0) {
      if (lp1 < 0) {
        push_layer(lp1);
      }
    }
  }
  */
#if defined(DEBUG)
  void dumpLayers() {
    Serial.print("Layer stack:");
    for (int i = 0; i <= layer_pos; i++) {
      dumpVal(layer_stack[i], " ");
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
  KarbonState(const KarbonState& ks)
    : left(ks.left), right(ks.right), State(ks) {}
  bool operator!=(const KarbonState& ks) const {
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
