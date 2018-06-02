using action_t = uint32_t;

constexpr action_t kMask = 0xf00;
constexpr action_t kKeyPress = 0x100;
constexpr action_t kModifier = 0x200;
constexpr action_t kTapHold = 0x300;
constexpr action_t kToggleMod = 0x400;
constexpr action_t kKeyAndMod = 0x500;
// This works like a shift key for a layer
constexpr action_t kLayerShift = 0x600;
// This turns the layer on or off
constexpr action_t kLayerToggle = 0x700;
// This switches the current layer to the new one
constexpr action_t kLayerSwitch = 0x800;

// This is for flagging consumer keycodes, as I have to handle them differently
constexpr action_t kConsumer = 0x8000;

using layer_t = uint8_t;
constexpr layer_t kPushLayer = 1;
constexpr layer_t kPopLayer = 2;
constexpr layer_t kToggleLayer = 3;
constexpr layer_t kSwitchLayer = 4;

#define ___ 0
#define PASTE(a, b) a##b
#define KEY(a) kKeyPress | PASTE(HID_KEY_, a)
#define MOD(a) kModifier | PASTE(KEYBOARD_MODIFIER_, a)
#define TMOD(a) kToggleMod | PASTE(KEYBOARD_MODIFIER_, a)
#define CONS(a) kConsumer | PASTE(HID_KEY_, a)

#define TAPH(a, b) \
  kTapHold | PASTE(HID_KEY_, a) | (PASTE(KEYBOARD_MODIFIER_, b) << 16)
#define KMOD(a, b) \
  kKeyAndMod | PASTE(HID_KEY_, a) | (PASTE(KEYBOARD_MODIFIER_, b) << 16)
#define MOD1(a, b) kKeyAndMod | a | (PASTE(KEYBOARD_MODIFIER_, b) << 16)
#define KMOD2(a, b, c)              \
  kKeyAndMod | PASTE(HID_KEY_, a) | \
      ((PASTE(KEYBOARD_MODIFIER_, b) | PASTE(KEYBOARD_MODIFIER_, c)) << 16)
#define MOD2(a, b, c) \
  kKeyAndMod | a |    \
      ((PASTE(KEYBOARD_MODIFIER_, b) | PASTE(KEYBOARD_MODIFIER_, c)) << 16)
#define KMOD3(a, b, c, d)                                             \
  kKeyAndMod | PASTE(HID_KEY_, a) |                                   \
      ((PASTE(KEYBOARD_MODIFIER_, b) | PASTE(KEYBOARD_MODIFIER_, c) | \
        PASTE(KEYBOARD_MODIFIER_, d))                                 \
       << 16)
#define MOD3(a, b, c, d)                                              \
  kKeyAndMod | a |                                                    \
      ((PASTE(KEYBOARD_MODIFIER_, b) | PASTE(KEYBOARD_MODIFIER_, c) | \
        PASTE(KEYBOARD_MODIFIER_, d))                                 \
       << 16)
#define KMOD4(a, b, c, d, e)                                          \
  kKeyAndMod | PASTE(HID_KEY_, a) |                                   \
      ((PASTE(KEYBOARD_MODIFIER_, b) | PASTE(KEYBOARD_MODIFIER_, c) | \
        PASTE(KEYBOARD_MODIFIER_, d) | PASTE(KEYBOARD_MODIFIER_, e))  \
       << 16)
#define MOD4(a, b, c, d, e)                                           \
  kKeyAndMod | a |                                                    \
      ((PASTE(KEYBOARD_MODIFIER_, b) | PASTE(KEYBOARD_MODIFIER_, c) | \
        PASTE(KEYBOARD_MODIFIER_, d) | PASTE(KEYBOARD_MODIFIER_, e))  \
       << 16)

#define LYR_TOG(n) kLayerToggle | n
#define LYR_SHIFT(n) kLayerShift | n
#define LYR_SET(n) kLayerSwitch | n

#define LROW1(l00, l01, l02, l03, l04, l05) \
  ___, l05, l04, l03, l02, l01, l00
#define LROW2(l10, l11, l12, l13, l14, l15) \
  ___, l15, l14, l13, l12, l11, l10
#define LROW3(l20, l21, l22, l23, l24, l25) \
  ___, l25, l24, l23, l22, l21, l20
#define LROW4(l30, l31, l32, l33, l34, l35) \
  ___, l35, l34, l33, l32, l31, l30
#define LROW5(l40, l41, l42, l43, l44, l45, lt56) \
  lt56, l45, l44, l43, l42, l41, l40
#define LROW6(l51, l52, l53, l54, lt65, lt66) \
  lt66, lt65, l54, l53, l52, l51, ___

#define RROW1(r00, r01, r02, r03, r04, r05) \
  r05, r04, r03, r02, r01, r00, ___
#define RROW2(r10, r11, r12, r13, r14, r15) \
  r15, r14, r13, r12, r11, r10, ___
#define RROW3(r20, r21, r22, r23, r24, r25) \
  r25, r24, r23, r22, r21, r20, ___
#define RROW4(r30, r31, r32, r33, r34, r35) \
  r35, r34, r33, r32, r31, r30, ___
#define RROW5(rt40, r40, r41, r42, r43, r44, r45) \
  r45, r44, r43, r42, r41, r40, rt40
#define RROW6(rt50, rt51, r51, r52, r53, r54) \
  ___, r54, r53, r52, r51, rt51, rt50

// Some missing keycodes from the Arduino/AdaFruit API's that I need. You can
// find these from the QMK firmware HIDClassCommon.h file. I also find them in
// IOHIDUsageTable.h from the IOHIDFamily source code available at
// www.opensource.apple.com. I'm pretty sure similar stuff is available for
// Windows, too, somewhere (probably in MSDN docs)

#define HID_KEY_M_PLAY 0xCD
#define HID_KEY_M_PREVIOUS_TRACK 0xB6
#define HID_KEY_M_NEXT_TRACK 0xB5
#define HID_KEY_M_VOLUME_UP 0x80
#define HID_KEY_M_VOLUME_DOWN 0x81
#define HID_KEY_M_MUTE 0x7F

#define HID_KEY_M_BACKWARD 0xF1
#define HID_KEY_M_FORWARD 0xF2
#define HID_KEY_M_SLEEP 0xF8
#define HID_KEY_M_LOCK 0xF9

// Let's mac-friendly-ify this stuff:
#define KEYBOARD_MODIFIER_LEFTOPTION KEYBOARD_MODIFIER_LEFTALT
#define KEYBOARD_MODIFIER_RIGHTOPTION KEYBOARD_MODIFIER_RIGHTALT
#define KEYBOARD_MODIFIER_LEFTCOMMAND KEYBOARD_MODIFIER_LEFTGUI
#define KEYBOARD_MODIFIER_RIGHTCOMMAND KEYBOARD_MODIFIER_RIGHTGUI
