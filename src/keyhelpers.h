#if !defined(KEYHELPERS_H)
#define KEYHELPERS_H

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

// Some stuff to make the action maps prettier. I use Clang Format, and it
// messes up the keymaps badly if they're over 80 characters on any individual
// line...
#define LCMD MOD(LEFTCOMMAND)
#define LSHFT MOD(LEFTSHIFT)
#define LCTL MOD(LEFTCTRL)
#define LOPT MOD(LEFTOPTION)
#define RCMD MOD(RIGHTCOMMAND)
#define RSHFT MOD(LEFTSHIFT)
#define RCTL MOD(RIGHTSHIFT)
#define ROPT MOD(RIGHTOPTION)

#define LGUI MOD(LEFTGUI)
#define LALT MOD(LEFTALT)
#define RGUI MOD(RIGHTGUI)
#define RALT MOD(RIGHTALT)

#define GRV GRAVE
#define OBRC BRACKET_LEFT
#define CBRC BRACKET_RIGHT
#define BKSP BACKSPACE
#define DEL DELETE
#define PGUP PAGE_UP
#define PGDN PAGE_DOWN
#define EQ_ KEY(EQUAL)
#define SEMI_ KEY(SEMICOLON)
#define COMMA_ KEY(COMMA)
#define DOT_ KEY(PERIOD)
#define QUOTE_ KEY(APOSTROPHE)
#define ENTER_ KEY(RETURN)
#define UP_ KEY(ARROW_UP)
#define DOWN_ KEY(ARROW_DOWN)
#define LEFT_ KEY(ARROW_LEFT)
#define RIGHT_ KEY(ARROW_RIGHT)
#define SPACE_ KEY(SPACE)
#define MUTE_ KEY(M_MUTE)
#define VOLUP_ KEY(M_VOLUME_UP)
#define VOLDN_ KEY(M_VOLUME_DOWN)

#define PLAY_ CONS(M_PLAY)
#define PRVT_ CONS(M_PREVIOUS_TRACK)
#define NXTT_ CONS(M_NEXT_TRACK)

#define SHFTCM LSHFT | LCMD
#define CTLCM LCTL | LCMD
#define OPTCM LOPT | LCMD
#define SHFTCT LSHFT | LCMD
#define GUICT LGUI | LCMD
#define ALTCT LALT | LCMD

// Some shortcuts for modifiers & stuff
#define CMK(a) KMOD(a, LEFTCOMMAND)
#define CM(a) MOD1(a, LEFTCOMMAND)
#define CTK(a) KMOD(a, LEFTCTRL)
#define CT(a) MOD1(a, LEFTCTRL)
#define OPK(a) KMOD(a, LEFTOPTION)
#define OP(a) MOD1(a, LEFTOPTION)
#define AL(a) MOD1(a, LEFTALT)
#define ALK(a) KMOD(a, LEFTALT)
#define GU(a) MOD1(a, LEFTGUI)
#define GUK(a) KMOD((a, LEFTGUI)
#define COSK(a) KMOD3(a, LEFTCTRL, LEFTSHIFT, LEFTOPTION)
#define COS(a) MOD3(a, LEFTCTRL, LEFTSHIFT, LEFTOPTION)
#define ALLK(a) KMOD4(a, LEFTCTRL, LEFTSHIFT, LEFTOPTION, LEFTCOMMAND)
#define ALL(a) MOD4(a, LEFTCTRL, LEFTSHIFT, LEFTOPTION, LEFTCOMMAND)

// CM == Command, OP = Option
#define CM_EQ CM(EQ_)
#define CM_SEMI CM(SEMI_)
#define CM_QUOTE CM(QUOTE_)
#define CM_CMA CM(COMMA_)
#define CM_DOT CM(DOT_)
#define CM_SLSH CMK(SLASH)
#define CM_SPC CMK(SPACE)
#define CM_PUP CMK(PGUP)
#define CM_PDN CMK(PGDN)
#define CM_RET CMK(RETURN)
#define OP_LEFT OP(LEFT_)
#define OP_RIGHT OP(RIGHT_)
#define CM_OBRC CMK(OBRC)
#define CM_CBRC CMK(CBRC)
#define CM_UP CM(UP_)
#define CM_DN CM(DOWN_)
#define MAC_WNL COS(LEFT_)
#define MAC_WNR COS(RIGHT_)
#define MAC_WNMX COS(UP_)

// CT = Control
#define CT_OBRC CTK(OBRC)
#define CT_CBRC CTK(CBRC)
#define CT_QUOTE CT(QUOTE_)
#define CT_SEMI CT(SEMI_)
#define CT_EQ CTK(EQUAL)
#define CT_SLSH CTK(SLASH)
#define CT_CMA CT(COMMA_)
#define CT_DOT CT(DOT_)
#define CT_PUP CTK(PGUP)
#define CT_PDN CTK(PGDN)
#define CT_UP CT(UP_)
#define CT_DN CT(DOWN_)
#define CT_LEFT CT(LEFT_)
#define CT_RIGHT CT(RIGHT_)
#define CT_SPC CT(SPACE_)
#define CT_RET CTK(RETURN)
#define WIN_WNL GU(LEFT_)
#define WIN_WNR GU(RIGHT_)
#define WIN_WNMX GU(UP_)

#define LAYER_MAC_BASE 0
#define LAYER_WIN_BASE 1
#define LAYER_FUNC 2
#define LAYER_MAC_CAP 3
#define LAYER_WIN_CAP 4
#define LAYER_WIN_CTL 5

#define LYR_WIN LYR_TOG(LAYER_WIN_BASE)
#define LYR_MAC LYR_TOG(LAYER_WIN_BASE)
#define LYR_FN LYR_TOG(LAYER_FUNC)
#define MAC_CAP LYR_SHIFT(LAYER_MAC_CAP)
#define WIN_CAP LYR_SHIFT(LAYER_WIN_CAP)
#define WIN_CTL LYR_SHIFT(LAYER_WIN_CTL)

#endif