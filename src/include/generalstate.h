#pragma once

#include "sysstuff.h"

#include <array>

#include "dbgcfg.h"
#include "keyhelpers.h"

enum class layerStack { LS };
static constexpr layerStack LayerStack = layerStack::LS;

SerialStream& operator<<(SerialStream& s, layerStack ls);
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
    Dbg << "Push " << layer << sfmt::endl;
    if (layer_pos < layer_max)
      layer_stack[++layer_pos] = layer;
    Dbg2 << LayerStack;
  }
  void toggle_layer(layer_num layer) {
    // Toggling a layer: If it exists *anywhere* in the layer stack, turn it
    // off (and fold the layer stack down) If it's *not* in the layer stack,
    // add it.
    for (uint8_t l = layer_pos; l != 0; l--) {
      if (layer_stack[l] == layer) {
        Dbg2 << "Turning off layer " << layer << " at location " << l
             << sfmt::endl;
        if (layer_pos != l) {
          Dbg2 << "Shifting by " << layer_pos - l << sfmt::endl;
          for (int i = l; i < layer_max; i++) {
            layer_stack[i] = layer_stack[i + 1];
          }
        }
        layer_pos--;
        Dbg2 << LayerStack;
        Dbg << "Toggled off " << layer << sfmt::endl;
        return;
      }
    }
    Dbg << "(For Toggle) ";
    push_layer(layer);
  }
  void pop_layer(layer_num layer) {
    Dbg << "Pop " << layer << sfmt::endl;
    if (layer_pos > 0 && layer_stack[layer_pos] == layer) {
      // Easy-peasy
      --layer_pos;
    } else {
      for (uint8_t l = layer_pos; l != 0; l--) {
        if (layer_stack[l] == layer) {
          Dbg2 << "Turning off layer " << layer << " at location " << l
               << sfmt::endl;
          if (layer_pos != l) {
            Dbg2 << "Shifting by " << layer_pos - l << sfmt::endl;
            for (int i = l; i < layer_max; i++) {
              layer_stack[i] = layer_stack[i + 1];
            }
          }
          layer_pos--;
          break;
        }
      }
    }
    Dbg2 << LayerStack;
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
    Dbg << "Switching layer " << layer_stack[layer_pos] << " to layer " << layer
        << sfmt::endl;
    layer_stack[layer_pos] = layer;
    Dbg2 << LayerStack;
  }
  void rotate_layers(layer_num a, layer_num b, layer_num c) {
    // assumes that if you're rotating through the base layer,
    // it's the first one. This should be asserted in the ctor...
    Dbg << "Rotate: ";
    layer_num which = b;
    while (find_layer(a) > 0) {
      toggle_layer(a);
    }
    while (find_layer(b) > 0) {
      which = c;
      toggle_layer(b);
    }
    while (find_layer(c) > 0) {
      which = a;
      toggle_layer(c);
    }
    // At this point, we have no layers a,b,c unless one is the base layer
    if (find_layer(which) != 0) {
      toggle_layer(which);
    }
  }
};

extern GeneralState curState;

inline SerialStream& operator<<(SerialStream& s, layerStack ls) {
  s << "Layer Stack:";
  for (int i = 0; i <= curState.layer_pos; i++) {
    s << " " << curState.layer_stack[i];
  }
  return s << sfmt::endl;
}
