#pragma once

#include "enumtypes.h"
#include "usbenums.h"
#include <cassert>

#if defined(DEBUG) && defined(ARDUINO)
#include "Arduino.h"
#endif

class action_t {
  // 4 bits of action, 1 bit 'is consumer', 11 bits of 'data'
  // Logically data is this:
  // uint8_t action : 4;
  // uint16_t LayerOrKeyOrMods : 11;
  // uint16_t data;
  // uint16_t moreData;
  uint8_t _action : 4;
  uint16_t _data : 12;
  uint16_t _moreData;

  constexpr static uint8_t ka(KeyAction a) {
    assert(value_cast(a) < (1 << 4)); // KeyAction must fit in 4 bits
    return value_cast(a);
  }
  constexpr static uint16_t ks(Keystroke k) {
    assert(value_cast(k) < (1 << 12)); // Keystroke must fit in 12 bits
    return value_cast(k);
  }
  constexpr static uint16_t mod(Modifiers m) {
    assert(value_cast(m) < (1 << 12)); // Modifiers must fit in 12 bits
    return value_cast(m);
  }
  constexpr static uint16_t cns(Consumer c) {
    assert(value_cast(c) < (1 << 12)); // Consumer keycode must fit in 12 bits
    return value_cast(c);
  }
  constexpr static uint16_t lyr(layer_num l) {
    assert(value_cast(l) < (1 << 12)); // Layer numbers must fit in 12 bits for
                                       // normal usage
    return value_cast(l);
  }
  constexpr static uint16_t rl(layer_num l, uint8_t pos) {
    assert(value_cast(l) < (1 << 4)); // Layer numbers must fit in 4 bits for
                                      // Layer Rotation usage
    return value_cast(l) << (pos * 4);
  }
  constexpr static uint16_t mode(KeyboardMode m) {
    assert(value_cast(m) < (1 << 12)); // KeyboardMode must fit in 12 bits
    return value_cast(m);
  }

  constexpr action_t() : _action(0), _data(0), _moreData(0) {}

  // combine simple actions:
  // TODO: Should have a static assert that there's no moreData!
  constexpr action_t(action_t a, action_t b)
    : _action(a._action),
      _data(a._data),
      _moreData((b._action << 12) | b._data) {
    // Combined actions can't already be compound actions
    assert(a._moreData == 0 && b._moreData == 0);
  }
  constexpr action_t(KeyAction a, Keystroke k)
    : _action(ka(a)), _data(ks(k)), _moreData(0) {
    // Keystrokes can't be combined with non-Keystroke actions
    assert(a == KeyAction::KeyPress || a == KeyAction::TapHold ||
           a == KeyAction::KeyAndMods);
  }
  constexpr action_t(KeyAction a, Modifiers m)
    : _action(ka(a)), _data(mod(m)), _moreData(0) {
    // Modifiers can only be used with Modifier, TapHold, and KeyAndMods
    // KeyActions
    assert(a == KeyAction::Modifier || a == KeyAction::TapHold ||
           a == KeyAction::KeyAndMods);
  }

  constexpr action_t(KeyAction a, Consumer m)
    : _action(ka(a)), _data(cns(m)), _moreData(0) {
    // Consumer keys can only be used with TapHold, and Consumer KeyActions
    assert(a == KeyAction::Consumer || a == KeyAction::TapHold);
  }

  constexpr action_t(KeyAction a, layer_num l)
    : _action(ka(a)), _data(lyr(l)), _moreData(0) {
    // Layer_num actions can only be used with Shift, Switch, and Toggle
    // KeyActions
    assert(a == KeyAction::LayerShift || a == KeyAction::LayerSwitch ||
           a == KeyAction::LayerToggle);
  }
  constexpr action_t(layer_num a, layer_num b, layer_num c)
    : _action(ka(KeyAction::LayerRotate3)),
      _data(rl(a, 0) | rl(b, 1) | rl(c, 2)),
      _moreData(0) {}

  constexpr action_t(layer_num a, layer_num b, layer_num c, layer_num d)
    : _action(ka(KeyAction::LayerRotate4)),
      _data(rl(a, 0) | rl(b, 1) | rl(c, 2)),
      _moreData(rl(d, 0)) {
    // 4th rotation layer cannot be layer 0 to prevent combining
    assert(rl(d, 0) > 0);
  }

  constexpr action_t(KeyboardMode m)
    : _action(ka(KeyAction::Mode)), _data(mode(m)), _moreData(0) {}
  constexpr action_t(Modifiers m) : action_t(KeyAction::Modifier, m) {}
  constexpr action_t(Consumer c) : action_t(KeyAction::Consumer, c) {}
  constexpr action_t(Keystroke keyPress)
    : action_t(KeyAction::KeyPress, keyPress) {}
  constexpr action_t(uint16_t macro)
    : _action(ka(KeyAction::Macro)), _data(macro), _moreData(0) {
    assert(macro < (1 << 12)); // macros have to fit in 12 bits
  }
  constexpr action_t(KeyAction a, uint16_t data)
    : _action(ka(a)), _data(data), _moreData(0) {
    // Only allow this constructor for TapHold creations
    assert(a == KeyAction::TapHold);
    assert(data < (1 << 12)); // Bit fit
  }

 public:
  static constexpr action_t Keypress(Keystroke keyPress) {
    return action_t{keyPress};
  }

  static constexpr action_t Modifier(Modifiers mod1,
                                     Modifiers mod2 = Modifiers::None,
                                     Modifiers mod3 = Modifiers::None,
                                     Modifiers mod4 = Modifiers::None) {
    return action_t{mod1 | mod2 | mod3 | mod4};
  }
  // static constexpr action_t Modifier(action_t mods) {
  //   return action_t{enum_cast<Modifiers>(mods.data & 0xFF)};
  // }
  static constexpr action_t ConsumerPress(Consumer keyPress) {
    return action_t{keyPress};
  }
  static constexpr action_t Layer(KeyAction ka, layer_num layerNum) {
    return action_t{ka, layerNum};
  }
  static constexpr action_t LayerRotate3(layer_num a,
                                         layer_num b,
                                         layer_num c) {
    return action_t{a, b, c};
  }
  static constexpr action_t LayerRotate4(layer_num a,
                                         layer_num b,
                                         layer_num c,
                                         layer_num d) {
    return action_t{a, b, c, d};
  }
  static constexpr action_t Combine(action_t a, action_t b) {
    return action_t{a, b};
  }
  static constexpr action_t Mode(KeyboardMode mode) {
    return action_t{mode};
  }
  static constexpr action_t NoAction() {
    return action_t{};
  }
  static constexpr action_t Macro(uint16_t num) {
    // TODO: Make sure this macro exists?
    return action_t{num};
  }
  static constexpr action_t TapAndHold(action_t tap, action_t hold) {
    // TODO: validate that tap._action is compatible, yeah?
    return action_t{action_t{KeyAction::TapHold, tap._data}, hold};
  }
  static constexpr action_t KeyAndMods(Keystroke key,
                                       Modifiers mod1,
                                       Modifiers mod2 = Modifiers::None,
                                       Modifiers mod3 = Modifiers::None,
                                       Modifiers mod4 = Modifiers::None) {
    return action_t{action_t{KeyAction::KeyAndMods, key},
                    action_t::Modifier(mod1, mod2, mod3, mod4)};
  }
  static constexpr action_t KeyAndMods(action_t key,
                                       Modifiers mod1,
                                       Modifiers mod2 = Modifiers::None,
                                       Modifiers mod3 = Modifiers::None,
                                       Modifiers mod4 = Modifiers::None) {
    // TODO: Make sure this is only a Consumer or normal key, yeah?
    return action_t{action_t{KeyAction::KeyAndMods, key.getKeystroke()},
                    action_t::Modifier(mod1, mod2, mod3, mod4)};
  }
  constexpr bool isNoAction() const {
    return _action == 0 && _data == 0 && _moreData == 0;
  }

  constexpr KeyAction getAction() const {
    return enum_cast<KeyAction>(_action);
  }

  constexpr Keystroke getKeystroke() const {
    return enum_cast<Keystroke>(_data);
  }

  constexpr Consumer getConsumer() const {
    return enum_cast<Consumer>(_data);
  }

  constexpr KeyboardMode getMode() const {
    return enum_cast<KeyboardMode>(_data);
  }

  constexpr uint16_t getMacro() const {
    return _data;
  }

  // ?? TODO: I don't grok this comment above this function.
  // This is for flagging consumer keycodes, as I have to handle them
  // differently
  constexpr Modifiers getModifiers() const {
    return enum_cast<Modifiers>(_data);
  }

  // TODO: This is only used for TapHold, and is broken...
  constexpr Modifiers getExtraMods() const {
    return enum_cast<Modifiers>(_moreData);
  }

  layer_num getLayer() const {
    return enum_cast<layer_num>(_data);
  }

  layer_num getLayer1() const {
    return enum_cast<layer_num>(_data & 0xF);
  }

  layer_num getLayer2() const {
    return enum_cast<layer_num>((_data >> 4) & 0xF);
  }

  layer_num getLayer3() const {
    return enum_cast<layer_num>((_data >> 8) & 0xF);
  }

  layer_num getLayer4() const {
    return enum_cast<layer_num>(_moreData & 0xF);
  }

  friend SerialStream& operator<<(SerialStream& s, const action_t& a);
};

static constexpr action_t no_action = action_t::NoAction();

inline constexpr action_t keyPress(Keystroke ks) {
  return action_t::Keypress(ks);
}

inline constexpr action_t layerToggle(layer_num n) {
  return action_t::Layer(KeyAction::LayerToggle, n);
}

inline constexpr action_t layerShift(layer_num n) {
  return action_t::Layer(KeyAction::LayerShift, n);
}

inline constexpr action_t layerSwitch(layer_num n) {
  return action_t::Layer(KeyAction::LayerSwitch, n);
}

inline constexpr action_t layerRotate3(layer_num a, layer_num b, layer_num c) {
  return action_t::LayerRotate3(a, b, c);
}

inline constexpr action_t layerRotate4(layer_num a,
                                       layer_num b,
                                       layer_num c,
                                       layer_num d) {
  return action_t::LayerRotate4(a, b, c, d);
}

inline constexpr action_t keyPress(action_t a) {
  assert(a.getAction() == KeyAction::KeyPress);
  return action_t::Keypress(a.getKeystroke());
}

inline constexpr action_t modPress(action_t a) {
  assert(a.getAction() == KeyAction::Modifier);
  return action_t::Modifier(a.getModifiers());
}
inline constexpr action_t modPress(Modifiers mod1,
                                   Modifiers mod2 = Modifiers::None,
                                   Modifiers mod3 = Modifiers::None,
                                   Modifiers mod4 = Modifiers::None) {
  return action_t::Modifier(mod1, mod2, mod3, mod4);
}

inline constexpr action_t consPress(Consumer a) {
  return action_t::ConsumerPress(a);
}

inline constexpr action_t keyAndModifiers(Keystroke key,
                                          Modifiers mod1,
                                          Modifiers mod2 = Modifiers::None,
                                          Modifiers mod3 = Modifiers::None,
                                          Modifiers mod4 = Modifiers::None) {
  return action_t::KeyAndMods(key, mod1, mod2, mod3, mod4);
}

inline constexpr action_t keyAndModifiers(action_t key,
                                          Modifiers mod1,
                                          Modifiers mod2 = Modifiers::None,
                                          Modifiers mod3 = Modifiers::None,
                                          Modifiers mod4 = Modifiers::None) {
  assert(key.getAction() == KeyAction::KeyPress);
  return action_t::KeyAndMods(key.getKeystroke(), mod1, mod2, mod3, mod4);
}

inline constexpr action_t modeKey(KeyboardMode mode) {
  return action_t::Mode(mode);
}

inline SerialStream& operator<<(SerialStream& s, const action_t& a) {
  s << a.getAction() << ":" << sfmt::hex << a._data;
  if (a._moreData != 0) {
    s << "|" << sfmt::hex << a._moreData;
  }
  return s;
}