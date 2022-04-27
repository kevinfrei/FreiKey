#pragma once

#include "sysstuff.h"

#include <array>

#include "dbgcfg.h"
#include "keyhelpers.h"

struct GeneralState {
  static constexpr uint8_t layer_max = 7;
  uint8_t layer_pos;
  std::array<layer_num, layer_max + 1> layer_stack;
  GeneralState() : layer_pos(0) {
    layer_stack.fill(layer_num::Base);
  }
  GeneralState(const GeneralState& gs)
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
  bool operator!=(const GeneralState& gs) const {
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
    DBG2(dumpLayers());
  }
  void toggle_layer(layer_num layer) {
    // Toggling a layer: If it exists *anywhere* in the layer stack, turn it
    // off (and fold the layer stack down) If it's *not* in the layer stack,
    // add it.
    for (uint8_t l = layer_pos; l != 0; l--) {
      if (layer_stack[l] == layer) {
        DBG2(dumpVal(layer, "Turning off layer "));
        DBG2(dumpVal(l, "at location "));
        if (layer_pos != l) {
          DBG2(dumpVal(layer_pos - l, "Shifting by "));
          for (int i = l; i < layer_max; i++) {
            layer_stack[i] = layer_stack[i + 1];
          }
        }
        layer_pos--;
        DBG2(dumpLayers());
        DBG(dumpVal(layer, "Toggled off "));
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
          DBG2(dumpVal(layer, "Turning off layer "));
          DBG2(dumpVal(l, "at location "));
          if (layer_pos != l) {
            DBG2(dumpVal(layer_pos - l, "Shifting by "));
            for (int i = l; i < layer_max; i++) {
              layer_stack[i] = layer_stack[i + 1];
            }
          }
          layer_pos--;
          DBG2(dumpLayers());
          break;
        }
      }
    }
    DBG2(dumpLayers());
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
    DBG2(dumpLayers());
  }
  void rotate_layers(layer_num a, layer_num b, layer_num c) {
    // assumes that if you're rotating through the base layer,
    // it's the first one. This should be asserted in the ctor...
    DBG(Serial.print("Rotate: "));
    if (find_layer(c) >= 0) {
      toggle_layer(c);
      toggle_layer(a);
    } else if (find_layer(b) >= 0) {
      toggle_layer(b);
      toggle_layer(c);
    } else if (find_layer(a) >= 0) {
      toggle_layer(a);
      toggle_layer(b);
    }
  }

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

extern GeneralState curState;