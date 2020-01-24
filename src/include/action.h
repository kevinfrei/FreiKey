#pragma once

using action_t = uint32_t;

constexpr action_t kActionMask = 0xF000;
constexpr action_t kKeyPress = 0x1000;
constexpr action_t kModifier = 0x2000;
constexpr action_t kTapHold = 0x3000;
// This one doesn't work, and I don't use it, so...
// constexpr action_t kToggleMod = 0x4000;
constexpr action_t kKeyAndMod = 0x5000;
// This works like a shift key for a layer
constexpr action_t kLayerShift = 0x6000;
// This turns the layer on or off
constexpr action_t kLayerToggle = 0x7000;

// This switches the current layer to the new one
constexpr action_t kLayerSwitch = 0x8000;

// This is for flagging consumer keycodes, as I have to handle them differently
constexpr action_t kConsumer = 0x800;
constexpr action_t kConsumerMask = 0x3FF;
constexpr action_t kKeyMask = 0xFF;

inline constexpr action_t getModifiers(action_t a) {
  return a & kActionMask;
}

inline constexpr action_t getKeystroke(action_t a) {
  return a & 0x7FF;
}

inline constexpr action_t getExtraMods(action_t a) {
  return kKeyMask & (a >> 16);
}

inline constexpr action_t combineKeys(action_t a, action_t b) {
  return a | b << 16;
}

inline constexpr action_t tapAndHold(action_t tap, action_t hold) {
  return combineKeys(kTapHold | tap, hold);
}

inline constexpr action_t keyAndModifiers(action_t key,
                                           action_t mod1,
                                           action_t mod2 = 0,
                                           action_t mod3 = 0,
                                           action_t mod4 = 0) {
  return combineKeys(kKeyAndMod | key, mod1 | mod2 | mod3 | mod4);
}

inline constexpr action_t layerToggle(uint8_t n) {
  return kLayerToggle | n;
}

inline constexpr action_t layerShift(uint8_t n) {
  return kLayerShift | n;
}

inline constexpr action_t layerSwitch(uint8_t n) {
  return kLayerSwitch | n;
}

inline constexpr action_t keyPress(action_t a) {
  return kKeyPress | a;
}

inline constexpr action_t modPress(action_t a) {
  return kModifier | a;
}

inline constexpr action_t consPress(action_t a) {
  return kConsumer | a;
}
