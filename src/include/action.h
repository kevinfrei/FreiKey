#pragma once

#include "enumtypes.h"
#include "usbenums.h"

class action_t {
  // 4 bits of action, 1 bit 'is consumer', 11 bits of 'data'
  uint16_t data;
  /*
  uint8_t action : 4;
  uint16_t LayerOrKeyOrMods : 11;
  */
  uint16_t moreData;

  void setKeyAction(KeyAction ka) {
    data = static_cast<uint16_t>(ka) << 12 | (data & 0xFFF);
  }
  void setLayer(uint8_t layerNum) {
    data = (data & 0xF000) | layerNum;
  }
  void setMods(Modifiers mods) {
    data = (data & 0xFF00) | static_cast<uint8_t>(mods);
  }
  void setKeyPress(uint16_t keycode) {
    // TODO: Should I try to detect consumer code here?
    data = (data & 0xF800) | (keycode & 0x7ff);
  }

  constexpr action_t(KeyAction kp, uint16_t otherData)
    : data(otherData), moreData(0) {
    setKeyAction(KeyAction::KeyPress);
  }

  constexpr action_t() : data(0), moreData(0) {}
  // combine keys
  constexpr action_t(action_t a, action_t b) : data(a.data), moreData(b.data) {}
  constexpr action_t(uint16_t d, uint16_t m) : data(d), moreData(m) {}

 public:
  constexpr action_t(Modifiers mods)
    : data(static_cast<uint16_t>(mods)), moreData(0) {
    setKeyAction(KeyAction::Modifier);
  }
  static constexpr action_t Keypress(uint16_t keyPress) {
    return action_t{KeyAction::KeyPress, keyPress};
  }
  static constexpr action_t Keypress(Keystroke keyPress) {
    return action_t{KeyAction::KeyPress, static_cast<uint16_t>(keyPress)};
  }
  static constexpr action_t Keypress(action_t keyPress) {
    return action_t{KeyAction::KeyPress, keyPress.data};
  }
  static constexpr action_t Modifier(Modifiers mod1,
                                     Modifiers mod2 = Modifiers::None,
                                     Modifiers mod3 = Modifiers::None,
                                     Modifiers mod4 = Modifiers::None) {
    return action_t{static_cast<Modifiers>(
      static_cast<uint8_t>(mod1) | static_cast<uint8_t>(mod2) |
      static_cast<uint8_t>(mod3) | static_cast<uint8_t>(mod4))};
  }
  static constexpr action_t Modifier(action_t mods) {
    return action_t{static_cast<Modifiers>(mods.data & 0xFF)};
  }
  static constexpr action_t Modifier(Modifiers mods) {
    return action_t{mods};
  }
  static constexpr action_t ConsumerPress(Consumer keyPress) {
    return action_t{KeyAction::Consumer, static_cast<uint16_t>(keyPress)};
  }
  static constexpr action_t Layer(KeyAction ka, uint8_t layerNum = 0) {
    return action_t{ka, static_cast<uint16_t>(layerNum)};
  }
  static constexpr action_t Combine(action_t a, action_t b) {
    return action_t{a, b};
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
    return action_t{action_t{KeyAction::KeyAndMods, static_cast<uint16_t>(key)},
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
    return static_cast<KeyAction>(data >> 12);
  }
  Keystroke getKeystroke() const {
    return static_cast<Keystroke>(data & 0xff);
  }
  Consumer getConsumer() const {
    return static_cast<Consumer>(data & 0xfff);
  }
  // This is for flagging consumer keycodes, as I have to handle them
  // differently
  Modifiers getModifiers() const {
    return static_cast<Modifiers>(data & 0xFF);
  }
  Modifiers getExtraMods() const {
    return static_cast<Modifiers>(moreData & 0xFF);
  }
  layer_num getLayer() const {
    return static_cast<layer_num>(data & 0xF);
  }
#if defined(DEBUG)
  void dump() const {
    Serial.print("data:");
    Serial.print(data, HEX);
    if (moreData != 0) {
      Serial.print("|");
      Serial.print(moreData, HEX);
    }
  }
#endif
};

static constexpr action_t no_action = action_t::NoAction();

inline constexpr action_t keyPress(Keystroke ks) {
  return action_t::Keypress(ks);
}

inline constexpr action_t layerToggle(uint8_t n) {
  return action_t::Layer(KeyAction::LayerToggle, n);
}

inline constexpr action_t layerShift(uint8_t n) {
  return action_t::Layer(KeyAction::LayerShift, n);
}

inline constexpr action_t layerSwitch(uint8_t n) {
  return action_t::Layer(KeyAction::LayerSwitch, n);
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