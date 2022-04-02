#pragma once
#include "sysstuff.h"

#include "action.h"
#include "dbgcfg.h"
#include "enumtypes.h"

#define ___ no_action
#define PASTE(a, b) a##b

#if defined(TEENSY)

#else

#endif

#define PK(k) (Keystroke::k)
#define PN(n) (Keystroke::_##n)
#define PM(m) (Modifiers::m)
#define PC(c) (Consumer::c)

#define KEY(a) keyPress(PK(a))
#define NUM(a) keyPress(PN(a))
#define MOD(a) modPress(PM(a))
#define CONS(a) consPress(PC(a))

//#define TMOD(a) kToggleMod | PM(a)
#define TAPH(a, b) tapAndHold(a, b)
#define KMOD(a, b) keyAndModifiers(PK(a), PM(b))
#define NMOD(a, b) keyAndModifiers(PN(a), PM(b))
#define MOD1(a, b) keyAndModifiers(a, PM(b))
#define KMOD2(a, b, c) keyAndModifiers(PK(a), PM(b), PM(c))
#define MOD2(a, b, c) keyAndModifiers(a, PM(b), PM(c))
#define KMOD3(a, b, c, d) keyAndModifiers(PK(a), PM(b), PM(c), PM(d))
#define MOD3(a, b, c, d) keyAndModifiers(a, PM(b), PM(c), PM(d))
#define KMOD4(a, b, c, d, e) keyAndModifiers(PK(a), PM(b), PM(c), PM(d), PM(e))
#define MOD4(a, b, c, d, e) keyAndModifiers(a, PM(b), PM(c), PM(d), PM(e))

#define LYR_TOG(n) layerToggle(n)
#define LYR_SHIFT(n) layerShift(n)
#define LYR_SET(n) layerSwitch(n)
#define MNU(n) menuKey(n)

// Some missing keycodes from the Arduino/AdaFruit API's that I need. You can
// find these from the QMK firmware HIDClassCommon.h file. I also find them in
// https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-1446.11.12/IOHIDFamily/IOHIDUsageTables.h.auto.html
// I'm 100% certain that stuff is available for Windows, too, somewhere in
// MSDN, cuz MSFT documents their stuff, unlike Apple...

#if 0
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
#endif

// Some stuff to make the action maps prettier. I use Clang Format, and it
// messes up the keymaps badly if they're over 80 characters on any individual
// line...
#define LCMD MOD(LCmd)
#define LSHFT MOD(LShft)
#define LCTL MOD(LCtrl)
#define LOPT MOD(LOpt)
#define RCMD MOD(RCmd)
#define RSHFT MOD(RShft)
#define RCTL MOD(RCtrl)
#define ROPT MOD(ROpt)

#define LGUI MOD(LGui)
#define LALT MOD(LAlt)
#define RGUI MOD(RGui)
#define RALT MOD(RAlt)

#define GRV Grave
#define OBRC OpenBrace
#define CBRC CloseBrace
#define BKSP Backspace
#define DEL Delete
#define PGUP PageUp
#define PGDN PageDown
#define EQ_ KEY(Equal)
#define SEMI_ KEY(Semicolon)
#define COMMA_ KEY(Comma)
#define DOT_ KEY(Period)
#define QUOTE_ KEY(Quote)
#define ENTER_ KEY(Enter)
#define UP_ KEY(Up)
#define DOWN_ KEY(Down)
#define LEFT_ KEY(Left)
#define RIGHT_ KEY(Right)
#define SPACE_ KEY(Space)
#define MUTE_ KEY(M_MUTE)
#define VOLUP_ CONS(VolumeUp)
#define VOLDN_ CONS(VolumeDown)

#define PLAY_ CONS(PlayPause)
#define PRVT_ CONS(PrevTrack)
#define NXTT_ CONS(NextTrack)

#define SHFTCM action_t::Modifier(Modifiers::Shift, Modifiers::Command)
#define CTLCM action_t::Modifier(Modifiers::Control, Modifiers::Command)
#define OPTCM action_t::Modifier(Modifiers::Option, Modifiers::Command)
#define SHFTCT action_t::Modifier(Modifiers::Shift, Modifiers::Control)
#define GUICT action_t::Modifier(Modifiers::Gui, Modifiers::Control)
#define ALTCT action_t::Modifier(Modifiers::Alt, Modifiers::Control)
#define RSHFCT action_t::Modifier(Modifiers::RShf, Modifiers::LControl)

// Some shortcuts for modifiers & stuff
#define CMK(a) KMOD(a, LCmd)
#define CMN(a) NMOD(a, LCmd)
#define CM(a) MOD1(a, LCmd)
#define CTK(a) KMOD(a, LCtl)
#define CTN(a) NMOD(a, LCtl)
#define CT(a) MOD1(a, LCtl)
#define OPK(a) KMOD(a, LOpt)
#define OP(a) MOD1(a, LOpt)
#define AL(a) MOD1(a, LAlt)
#define ALK(a) KMOD(a, LAlt)
#define GU(a) MOD1(a, LGui)
#define GUK(a) KMOD(a, LGui)
#define COSK(a) KMOD3(a, LCtrl, LShift, LOpt)
#define COS(a) MOD3(a, LCtrl, LShift, LOpt)
#define ALLK(a) KMOD4(a, LCtrl, LShift, LOpt, LCmd)
#define ALL(a) MOD4(a, LCtrl, LShift, LOpt, LCmd)

// CM == Command, OP = Option
#define CM_EQ CMK(Equal)
#define CM_SEMI CMK(Semicolon)
#define CM_QUOTE CMK(Quote)
#define CM_CMA CMK(Comma)
#define CM_DOT CMK(Dot)
#define CM_SLSH CMK(Slash)
#define CM_SPC CMK(Space)
#define CM_PUP CMK(PgUp)
#define CM_PDN CMK(PgDn)
#define CM_ENT CMK(Enter)
#define OP_LEFT OPK(Left)
#define OP_RIGHT OPK(Right)
#define CM_OBRC CMK(OpenBrace)
#define CM_CBRC CMK(CloseBrace)
#define CM_UP CMK(Up)
#define CM_DN CMK(Down)
#define MAC_WNL COSK(Left)
#define MAC_WNR COSK(Right)
#define MAC_WNMX COSK(Up)

// CT = Control
#define CT_OBRC CTK(OpenBrace)
#define CT_CBRC CTK(CloseBrace)
#define CT_QUOTE CTK(Quote)
#define CT_SEMI CTK(Semicolon)
#define CT_EQ CTK(Equal)
#define CT_SLSH CTK(Slash)
#define CT_CMA CTK(Comma)
#define CT_DOT CTK(Dot)
#define CT_PUP CTK(PgUp)
#define CT_PDN CTK(PgDn)
#define CT_UP CTK(Up)
#define CT_DN CTK(Down)
#define CT_LEFT CTK(Left)
#define CT_RIGHT CTK(Right)
#define CT_SPC CTK(Space)
#define CT_ENT CTK(Enter)
#define WIN_WNL GUK(Left)
#define WIN_WNR GUK(Right)
#define WIN_WNMX GUK(Up)

#define LYR_WIN LYR_TOG(layer_num::WinBase)
#define LYR_LIN LYR_TOG(layer_num::LinBase)
#define LYR_MAC LYR_TOG(layer_num::WinBase)
#define LYR_FN LYR_TOG(layer_num::Func)
#define MAC_CAP LYR_SHIFT(layer_num::MacCap)
#define WIN_CAP LYR_SHIFT(layer_num::WinCap)
#define LIN_CAP LYR_SHIFT(layer_num::LinCap)
#define WIN_CTL LYR_SHIFT(layer_num::WinCtl)
#define SHFT_FN LYR_SHIFT(layer_num::Func)
// #define LYR_MWL LYR_ROTATE(LAYER_MAC_BASE, LAYER_WIN_BASE, LAYER_LIN_BASE)