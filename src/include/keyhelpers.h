#pragma once
#include "sysstuff.h"

#include "action.h"
#include "dbgcfg.h"

using layer_t = uint8_t;
constexpr layer_t kPushLayer = 1;
constexpr layer_t kPopLayer = 2;
constexpr layer_t kToggleLayer = 3;
constexpr layer_t kRotateLayer = 4;

#define ___ 0
#define PASTE(a, b) a##b

#if defined(TEENSY)

#define PK(a) ((PASTE(KEY_, a)) & 0x1ff)
#define PM(a) ((PASTE(MODIFIERKEY_, a)) & 0x1ff)
#define PK_(a) PASTE(KEY_, a)
#define PM_(a) PASTE(MODIFIERKEY_, a)

#define LEFTALT LEFT_ALT
#define RIGHTALT RIGHT_ALT
#define LEFTGUI LEFT_GUI
#define RIGHTGUI RIGHT_GUI
#define LEFTCTRL LEFT_CTRL
#define RIGHTCTRL RIGHT_CTRL
#define LEFTSHIFT LEFT_SHIFT
#define RIGHTSHIFT RIGHT_SHIFT
#define KEY_ESCAPE KEY_ESC
#define KEY_GRAVE KEY_TILDE
#define KEY_BRACKET_LEFT KEY_LEFT_BRACE
#define KEY_BRACKET_RIGHT KEY_RIGHT_BRACE
#define KEY_APOSTROPHE KEY_QUOTE
#define KEY_ARROW_UP KEY_UP
#define KEY_ARROW_DOWN KEY_DOWN
#define KEY_ARROW_LEFT KEY_LEFT
#define KEY_ARROW_RIGHT KEY_RIGHT
#define KEY_APPLICATION KEY_MENU

#else

#define PK(a) PASTE(HID_KEY_, a)
#define PM(a) PASTE(KEYBOARD_MODIFIER_, a)
#define PK_(a) PASTE(HID_KEY_, a)
#define PM_(a) PASTE(KEYBOARD_MODIFIER_, a)

#endif

#define KEY(a) keyPress(PK(a))
#define MOD(a) modPress(PM(a))
//#define TMOD(a) kToggleMod | PM(a)
#define CONS(a) consPress(PK(a))

#define TAPH(a, b) tapAndHold(a, b)
#define KMOD(a, b) keyAndModifiers(PK(a), PM(b))
#define MOD1(a, b) keyAndModifiers(a, PM(b))
#define KMOD2(a, b, c) keyAndModifiers(PK(a), PM(b), PM(c))
#define MOD2(a, b, c) keyAndModifiers(a, PM(b), PM(c))
#define KMOD3(a, b, c, d) keyAndModifiers(PK(a), PM(b), PM(c), PM(d))
#define MOD3(a, b, c, d) keyAndModifiers(a, PM(b), PM(c), PM(d))
#define KMOD4(a, b, c, d, e) keyAndModifiers(PK(a), PM(b), PM(c), PM(d), PM(e))
#define MOD4(a, b, c, d, e) keyAndModifiers(a, PM(b), PM(c), PM(d), PM(e))

#define LYR_TOG(n) layerToggle(n)
#define LYR_SHIFT(n) layerShift(n)
#define LYR_ROTATE(i, j, k) layerRotate(i, j, k)

// Some missing keycodes from the Arduino/AdaFruit API's that I need. You can
// find these from the QMK firmware HIDClassCommon.h file. I also find them in
// https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-1446.11.12/IOHIDFamily/IOHIDUsageTables.h.auto.html
// I'm 100% certain that stuff is available for Windows, too, somewhere in
// MSDN, cuz MSFT documents their stuff, unlike Apple...

#define DK(a, v) constexpr action_t PK_(a) = v
#define DM(a, v) constexpr action_t PM_(a) = PM(v)
DK(M_PLAY, 0xCD);
DK(M_PREVIOUS_TRACK, 0xB6);
DK(M_NEXT_TRACK, 0xB5);
DK(M_VOLUME_UP, 0xE9);
DK(M_VOLUME_DOWN, 0xEA);
DK(M_MUTE, 0x7F);

DK(M_BACKWARD, 0xF1);
DK(M_FORWARD, 0xF2);
DK(M_SLEEP, 0xF8);
DK(M_LOCK, 0xF9);

// Let's mac-friendly-ify this stuff:

#define LEFTOPTION LEFTALT
#define RIGHTOPTION RIGHTALT
#define LEFTCOMMAND LEFTGUI
#define RIGHTCOMMAND RIGHTGUI

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
#define ENTER_ KEY(ENTER)
#define UP_ KEY(ARROW_UP)
#define DOWN_ KEY(ARROW_DOWN)
#define LEFT_ KEY(ARROW_LEFT)
#define RIGHT_ KEY(ARROW_RIGHT)
#define SPACE_ KEY(SPACE)
#define MUTE_ KEY(M_MUTE)
#define VOLUP_ CONS(M_VOLUME_UP)
#define VOLDN_ CONS(M_VOLUME_DOWN)

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
#define GUK(a) KMOD(a, LEFTGUI)
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
#define CM_ENT CM(ENTER_)
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
#define CT_ENT CTK(ENTER)
#define WIN_WNL GU(LEFT_)
#define WIN_WNR GU(RIGHT_)
#define WIN_WNMX GU(UP_)

#if defined(FREIKEY)
#define LAYER_MAC_BASE 0
#define LAYER_WIN_BASE 1
#define LAYER_FUNC 2
#define LAYER_MAC_CAP 3
#define LAYER_WIN_CAP 4
#define LAYER_WIN_CTL 5
#elif defined(KARBON) || defined(LAPTYPE) || defined(THREEPIECE) || defined(MOCK)
#define LAYER_MAC_BASE 0
#define LAYER_WIN_BASE 1
#define LAYER_LIN_BASE 2
#define LAYER_FUNC 3
#define LAYER_MAC_CAP 4
#define LAYER_WIN_CAP 5
#define LAYER_WIN_CTL 6
#define LAYER_LIN_CAP 7
#else
#error You probably want to define your keymap here...
#endif

#define LYR_MAC LYR_TOG(LAYER_WIN_BASE)
#define LYR_FN LYR_TOG(LAYER_FUNC)
#define MAC_CAP LYR_SHIFT(LAYER_MAC_CAP)
#define WIN_CAP LYR_SHIFT(LAYER_WIN_CAP)
#define LIN_CAP LYR_SHIFT(LAYER_LIN_CAP)
#define WIN_CTL LYR_SHIFT(LAYER_WIN_CTL)
#define SHFT_FN LYR_SHIFT(LAYER_FUNC)
#define LYR_MWL LYR_ROTATE(LAYER_MAC_BASE, LAYER_WIN_BASE, LAYER_LIN_BASE)