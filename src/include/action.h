#pragma once

#include "enumtypes.h"
#include "usbenums.h"

#if defined(DEBUG) && defined(ARDUINO)
#include "Arduino.h"
#endif

class action_t {
  // 4 bits of action, 1 bit 'is consumer', 11 bits of 'data'
  uint16_t data;
  /*
  uint8_t action : 4;
  uint16_t LayerOrKeyOrMods : 11;
  */
  uint16_t moreData;

  constexpr void setKeyAction(KeyAction ka) {
    data = value_cast(ka) << 12 | (data & 0xFFF);
  }
  constexpr void setLayer(uint8_t layerNum) {
    data = (data & 0xF000) | layerNum;
  }
  constexpr void setMods(Modifiers mods) {
    data = (data & 0xFF00) | value_cast(mods);
  }
  void setKeyPress(uint16_t keycode) {
    // TODO: Should I try to detect consumer code here?
    data = (data & 0xF800) | (keycode & 0x7ff);
  }

  constexpr action_t(KeyAction ka, uint16_t otherData)
    : data(otherData), moreData(0) {
    setKeyAction(ka);
  }

  constexpr action_t() : data(0), moreData(0) {}
  // combine keys
  constexpr action_t(action_t a, action_t b) : data(a.data), moreData(b.data) {}
  constexpr action_t(uint16_t d, uint16_t m) : data(d), moreData(m) {}

 public:
  constexpr action_t(Modifiers mods) : data(value_cast(mods)), moreData(0) {
    setKeyAction(KeyAction::Modifier);
  }
  static constexpr action_t Keypress(uint16_t keyPress) {
    return action_t{KeyAction::KeyPress, keyPress};
  }
  static constexpr action_t Keypress(Keystroke keyPress) {
    return action_t{KeyAction::KeyPress, value_cast(keyPress)};
  }
  static constexpr action_t Keypress(action_t keyPress) {
    return action_t{KeyAction::KeyPress, keyPress.data};
  }
  static constexpr action_t Modifier(Modifiers mod1,
                                     Modifiers mod2 = Modifiers::None,
                                     Modifiers mod3 = Modifiers::None,
                                     Modifiers mod4 = Modifiers::None) {
    return action_t{mod1 | mod2 | mod3 | mod4};
  }
  static constexpr action_t Modifier(action_t mods) {
    return action_t{enum_cast<Modifiers>(mods.data & 0xFF)};
  }
  static constexpr action_t Modifier(Modifiers mods) {
    return action_t{mods};
  }
  static constexpr action_t ConsumerPress(Consumer keyPress) {
    return action_t{KeyAction::Consumer, value_cast(keyPress)};
  }
  static constexpr action_t Layer(KeyAction ka,
                                  layer_num layerNum = layer_num::Base) {
    return action_t{ka, value_cast(layerNum)};
  }
  static constexpr action_t LayerRotate(layer_num a, layer_num b, layer_num c) {
    return action_t{KeyAction::LayerRotate,
                    static_cast<uint16_t>(value_cast(a) | (value_cast(b) << 4) |
                                          (value_cast(c) << 8))};
  }
  static constexpr action_t Combine(action_t a, action_t b) {
    return action_t{a, b};
  }
  static constexpr action_t Mode(uint16_t info) {
    return action_t{KeyAction::Mode, info};
  }
  static constexpr action_t NoAction() {
    return action_t{};
  }
  static constexpr action_t TapAndHold(action_t tap, action_t hold) {
    return action_t{action_t{KeyAction::TapHold, tap.data}, hold};
  }
  static constexpr action_t KeyAndMods(Keystroke key,
                                       Modifiers mod1,
                                       Modifiers mod2 = Modifiers::None,
                                       Modifiers mod3 = Modifiers::None,
                                       Modifiers mod4 = Modifiers::None) {
    return action_t{action_t{KeyAction::KeyAndMods, value_cast(key)},
                    action_t::Modifier(mod1, mod2, mod3, mod4)};
  }
  static constexpr action_t KeyAndMods(action_t key,
                                       Modifiers mod1,
                                       Modifiers mod2 = Modifiers::None,
                                       Modifiers mod3 = Modifiers::None,
                                       Modifiers mod4 = Modifiers::None) {
    return action_t{action_t{KeyAction::KeyAndMods, key.data},
                    action_t::Modifier(mod1, mod2, mod3, mod4)};
  }
  bool isNoAction() const {
    return data == 0 && moreData == 0;
  }

  KeyAction getAction() const {
    return enum_cast<KeyAction>(data >> 12);
  }

  Keystroke getKeystroke() const {
    return enum_cast<Keystroke>(data & 0xff);
  }

  Consumer getConsumer() const {
    return enum_cast<Consumer>(data & 0xfff);
  }

  KeyboardMode getMode() const {
    return enum_cast<KeyboardMode>(data & 0xff);
  }

  // This is for flagging consumer keycodes, as I have to handle them
  // differently
  Modifiers getModifiers() const {
    return enum_cast<Modifiers>(data & 0xFF);
  }

  Modifiers getExtraMods() const {
    return enum_cast<Modifiers>(moreData & 0xFF);
  }

  layer_num getLayer() const {
    return enum_cast<layer_num>(data & 0xF);
  }

  layer_num getLayer1() const {
    return enum_cast<layer_num>(data & 0xF);
  }

  layer_num getLayer2() const {
    return enum_cast<layer_num>((data >> 4) & 0xF);
  }

  layer_num getLayer3() const {
    return enum_cast<layer_num>((data >> 8) & 0xF);
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

inline constexpr action_t layerRotate(layer_num a, layer_num b, layer_num c) {
  return action_t::LayerRotate(a, b, c);
}

inline constexpr action_t keyPress(action_t a) {
  return action_t::Keypress(a);
}

inline constexpr action_t modPress(action_t a) {
  return action_t::Modifier(a);
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
  return action_t::KeyAndMods(key, mod1, mod2, mod3, mod4);
}

inline constexpr action_t modeKey(uint16_t info) {
  return action_t::Mode(info);
}

inline SerialStream& operator<<(SerialStream& s, const action_t& a) {
  s << a.getAction() << ":" << sfmt::hex << (a.data & 0xFFF);
  if (a.moreData != 0) {
    s << "|" << sfmt::hex << a.moreData;
  }
  return s;
}