#pragma once

#include "boardio.h"
#include "keyhelpers.h"

// clang-format off
#define LROW1(l0, l1, l2, l3, l4, l5) action_t{l0}, action_t{l1}, action_t{l2}, action_t{l3}, action_t{l4}, action_t{l5}
#define LROW2(l0, l1, l2, l3, l4, l5) action_t{l0}, action_t{l1}, action_t{l2}, action_t{l3}, action_t{l4}, action_t{l5}
#define LROW3(l0, l1, l2, l3, l4, l5) action_t{l0}, action_t{l1}, action_t{l2}, action_t{l3}, action_t{l4}, action_t{l5}
#define LROW4(l0, l1, l2, l3, l4, l5) action_t{l0}, action_t{l1}, action_t{l2}, action_t{l3}, action_t{l4}, action_t{l5}
#define LROW5(l0, l1, l2, l3, l4, l5) action_t{l0}, action_t{l1}, action_t{l2}, action_t{l3}, action_t{l4}, action_t{l5}
#define LROW6(l2, l3, l4, lt5) no_action, no_action, action_t{l2}, action_t{l3}, action_t{l4}, action_t{lt5}

#define RROW1(r0, r1, r2, r3, r4, r5) action_t{r0}, action_t{r1}, action_t{r2}, action_t{r3}, action_t{r4}, action_t{r5}
#define RROW2(r0, r1, r2, r3, r4, r5)  action_t{r0}, action_t{r1}, action_t{r2}, action_t{r3}, action_t{r4}, action_t{r5}
#define RROW3(r0, r1, r2, r3, r4, r5)  action_t{r0}, action_t{r1}, action_t{r2}, action_t{r3}, action_t{r4}, action_t{r5}
#define RROW4(r0, r1, r2, r3, r4, r5)  action_t{r0}, action_t{r1}, action_t{r2}, action_t{r3}, action_t{r4}, action_t{r5}
#define RROW5(r0, r1, r2, r3, r4, r5)  action_t{r0}, action_t{r1}, action_t{r2}, action_t{r3}, action_t{r4}, action_t{r5}
#define RROW6(rt0, r1, r2, r3)  action_t{rt0}, action_t{r1}, action_t{r2}, action_t{r3}, no_action, no_action
// clang-format on

#if defined(STATUS_DUMP) || defined(HAS_DISPLAY)
// For the status dumper thingamajig
constexpr const char* layer_names[] = {"Base/Mac",
                                       "Win",
                                       "Linux",
                                       "Fn",
                                       "MacCaps",
                                       "WinCaps",
                                       "WinCtrl",
                                       "LinuxCaps"};
#endif

// TODO: I'm not happy that in order to override "modifier + key" it requires
// that I create an entire layer. I want to be able to make caps+shift+volup
// do something, but not cause the caps+shift thing to be a full layer.
//

// Instead, maybe look at something like the KLL stuff from the InputClub
// a key-action:
// Default action: key, modifier, other
// A key is just what it says.
// A modifier is something like shift/cmd/ctrl/win/alt
// other:
//  Trigger, action
//  Trigger: on Key down, or key up
//  Action: keypress (either with exist modifiers, or 'unique')
//          Layer change (latch, lock, or shift)

// clang-format off
const action_t keymap[][BoardIO::matrix_size] = {
{// LAYER_MAC_BASE (0)
LROW1(KEY(Esc), NUM(1), NUM(2), NUM(3), NUM(4), NUM(5)),         RROW1(NUM(6), NUM(7), NUM(8), NUM(9), NUM(0),     KEY(Minus)),
LROW2(KEY(Tab), KEY(Q), KEY(W), KEY(E), KEY(R), KEY(T)),         RROW2(KEY(Y), KEY(U), KEY(I), KEY(O), KEY(P),     KEY(Backslash)),
LROW3(MAC_CAP,  KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),         RROW3(KEY(H), KEY(J), KEY(K), KEY(L), SEMI_,      QUOTE_),
LROW4(LSHFT,    KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),         RROW4(KEY(N), KEY(M), COMMA_, DOT_,   KEY(Slash), RSHFT),
LROW5(LCTL, LOPT, LCMD, KEY(PgUp),    KEY(OBRC), KEY(BKSP)),    RROW5(SPACE_, EQ_,     UP_,     SHFT_FN, KEY(Del), KEY(Grave)),
LROW6(       KEY(Home), KEY(PgDn), KEY(End),        KEY(CBRC)), RROW6(ENTER_,    LEFT_, DOWN_, RIGHT_),
},
{// LAYER_WIN_BASE (1)
// Put Alt & GUI in the right spots
LROW1(___,       ___, ___, ___, ___, ___),    RROW1(___, ___, ___, ___, ___, ___),
LROW2(___,       ___, ___, ___, ___, ___),    RROW2(___, ___, ___, ___, ___, ___),
LROW3(WIN_CAP,   ___, ___, ___, ___, ___),    RROW3(___, ___, ___, ___, ___, ___),
LROW4(___,       ___, ___, ___, ___, ___),    RROW4(___, ___, ___, ___, ___, ___),
LROW5(WIN_CTL, LGUI, LALT, ___,  ___, ___),  RROW5(___, ___, ___, ___, ___, ___),
LROW6(                ___, ___, ___,   ___),RROW6(___, ___, ___, ___),
},
{// LAYER_LINUX_BASE (2)
// Put Alt & GUI in the right spots, Add the Insert key (instead of PRVT),
// Print Screen (instead of NXTT) and the application key (instead of MUTE)
LROW1(___,     ___, ___, ___, ___, ___),    RROW1(___, ___, ___, ___, ___, ___),
LROW2(___,     ___, ___, ___, ___, ___),    RROW2(___, ___, ___, ___, ___, ___),
LROW3(LIN_CAP, ___, ___, ___, ___, ___),    RROW3(___, ___, ___, ___, ___, ___),
LROW4(___,     ___, ___, ___, ___, ___),    RROW4(___, ___, ___, ___, ___, ___),
LROW5(___,   LGUI, LALT, ___,  ___, ___),  RROW5(___, ___, ___, ___, ___, ___),
LROW6(              ___, ___, ___,   ___),RROW6(___, ___, ___, ___),
},
{// LAYER_FUNC (3)
// Nothing too exciting here. I might perhaps go add my Rocksmith
// keybindings, and perhaps put the function keys in a more 'debugger
// binding friendly' order...
LROW1(KEY(F12), KEY(F1), KEY(F2), KEY(F3), KEY(F4), KEY(F5)), RROW1(  KEY(F6), KEY(F7), KEY(F8), KEY(F9), KEY(F10), KEY(F11)),
LROW2(KEY(F11), ___,     ___,     ___,     ___,     ___),     RROW2(  ___,     ___,     ___,     ___,     ___,      KEY(F12)),
LROW3(MODE(1),  ___,     ___,     ___,     ___,     ___),     RROW3(  ___,     ___,     ___,     ___,     ___,      ___),
LROW4(___,      ___,     ___,     ___,     ___,     ___),     RROW4(  ___,     ___,     ___,     ___,     ___,      ___),
LROW5(LCTL,___,  ___,      ___,             ___,     ___),    RROW5( ___,     ___,          VOLUP_,      ___,  LYR_MWL, MODE(2)),
LROW6(              PRVT_, PLAY_, NXTT_,              ___),   RROW6(___,               ___, VOLDN_, ___),
},
{// LAYER_MAC_CAP (4)
// Mostly just cmd + key (CMK(a)), with exceptions for some window
// manipulatiton bindings for my HammerSpoon configuration
LROW1(CMK(Esc), CMN(1), CMN(2), CMN(3), CMN(4), CMN(5)),     RROW1(  CMN(6), CMN(7), CMN(8), CMN(9), CMN(0),  CMK(Minus)),
LROW2(CMK(Tab), CMK(Q), CMK(W), CMK(E), CMK(R), CMK(T)),     RROW2(  CMK(Y), CMK(U), CMK(I), CMK(O), CMK(P),  CMK(Backslash)),
LROW3(___,      CMK(A), CMK(S), CMK(D), CMK(F), CMK(G)),     RROW3(  CMK(H), CMK(J), CMK(K), CMK(L), CM_SEMI, CM_QUOTE),
LROW4(SHFTCM,   CMK(Z), CMK(X), CMK(C), CMK(V), CMK(B)),     RROW4(  CMK(N), CMK(M), CM_CMA, CM_DOT, CM_SLSH, CM_SPC),
LROW5(CTLCM, OPTCM, ___,   CM_PUP,      CM_OBRC, OPK(BKSP)),  RROW5( CM_SPC, CM_EQ,   CM_UP,    ___, CMK(DEL), CMK(Grave)),
LROW6(          CMK(Home), CM_PDN, CMK(End),       CM_CBRC), RROW6(CM_ENT,  OP_LEFT, CM_DN, OP_RIGHT),
},
{// LAYER_WIN_CAP (5)
// This is magic to get a bunch of mac commands to send their Windows
// equivalent The poster children are Caps-Q => Alt-F4 and Caps-W => Ctl-F4
// Effectively making Caps-Q & Caps-W correspond to Quit and Close Window
// TODO: Support key sequences so that gui-left, up/down works for quadrant
// window docking. Alternatively, try to do it from AutoHotKey because the
// way Windows 10 natively handles it is shit.
LROW1(CTK(Esc), CTN(1),  CTN(2),  CTN(3), CTN(4), CTN(5)),      RROW1(  CTN(6), CTN(7), CTN(8), CTN(9),   CTN(0),   CTK(Minus)),
LROW2(CTK(Tab), ALK(F4), CTK(F4), CTK(E), CTK(R), CTK(T)),      RROW2(  CTK(Y), CTK(U), CTK(I), CTK(O),   CTK(P),   CTK(Backslash)),
LROW3(___,      CTK(A),  CTK(S),  CTK(D), CTK(F), CTK(G)),      RROW3(  CTK(H), CTK(J), CTK(K), CTK(L),   CT_SEMI,  CT_QUOTE),
LROW4(SHFTCT,   CTK(Z),  CTK(X),  CTK(C), CTK(V), CTK(B)),      RROW4(  CTK(N), CTK(M), CT_CMA, KEY(Esc), CT_SLSH,  RGUI),
LROW5(LCTL, GUICT, ALTCT,  CT_PUP,      CTK(OBRC), CTK(BKSP)),  RROW5( CT_SPC, CT_EQ,        CT_UP,   ___, CTK(DEL), CTK(Grave)),
LROW6(          CTK(Home), CT_PDN, CTK(End),        CTK(CBRC)), RROW6(CT_ENT,       CT_LEFT, CT_DN, CT_RIGHT),
},
{// LAYER_WIN_CTL (6)
// This is magic to make Unix line editing controls to work like they do in
// Unix, but when working on Windows. The only one I can't really do is
// ctrl-t because Transpose would require something quite fancy. I could
// pull it off with use of the clipboard and sequence support, but that's
// not likely to happen until I actually care.  Note: I'm not mapping any
// of the media-ish keys. I probably should.  The one thing I don't think
// I've really done is think about alt-prscn for handling screenshots & the
// like...
LROW1(CTK(Esc), CTN(1),    CTN(2), CTN(3),   CTN(4), CTN(5)),       RROW1(  CTN(6), CTN(7), CTN(8), CTN(9), CTN(0),  CTK(Minus)),
LROW2(CTK(Tab), CTK(Q),    CTK(W), KEY(End), CTK(R), CTK(T)),       RROW2(  CTK(Y), CTK(U), CTK(I), CTK(O), UP_,     CTK(Backslash)),
LROW3(LCTL,     KEY(Home), CTK(S), KEY(Del), RIGHT_, CTK(G)),       RROW3(  CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
LROW4(SHFTCT,   CTK(Z),    CTK(X), CTK(C),   CTK(V), LEFT_),       RROW4(  DOWN_,  CTK(M), CT_CMA, CT_DOT, CT_SLSH, RSHFCT),
LROW5(___, GUICT, ALTCT,   CT_PUP,         CTK(OBRC), CTK(BKSP)),   RROW5( CT_SPC, CT_EQ,   CT_UP,    ___, CTK(DEL), CTK(Grave)),
LROW6(          CTK(Home), CT_PDN, CTK(End),           CTK(CBRC)), RROW6(CT_ENT,   CT_LEFT, CT_DN, CT_RIGHT),
},
{// LAYER_LIN_CAP (7)
LROW1(CTK(Esc), CTN(1),  CTN(2),  CTN(3), CTN(4), CTN(5)),      RROW1(  CTN(6), CTN(7), CTN(8), CTN(9), CTN(0),   CTK(Minus)),
LROW2(CTK(Tab),    ALK(F4), CTK(F4), CTK(E), CTK(R), CTK(T)),      RROW2(  CTK(Y), CTK(U), CTK(I), CTK(O), CTK(P),   CTK(Backslash)),
LROW3(___,         CTK(A),  CTK(S),  CTK(D), CTK(F), CTK(G)),      RROW3(  CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI,  CT_QUOTE),
LROW4(SHFTCT,      CTK(Z),  CTK(X),  CTK(C), CTK(V), CTK(B)),      RROW4(  CTK(N), CTK(M), CT_CMA, CT_DOT, CT_SLSH,  RGUI),
LROW5(LCTL, GUICT,  ALTCT,   CT_PUP,       CTK(OBRC), CTK(BKSP)),  RROW5( CT_SPC, CT_EQ,      CT_UP,   ___, CTK(DEL), CTK(Grave)),
LROW6(            CTK(Home), CT_PDN, CTK(End),         KEY(CBRC)), RROW6(CT_ENT,     CT_LEFT, CT_DN, CT_RIGHT),
},
};

const action_t moduleKeyMap[BoardIO::matrix_size] = {
LROW1(KEY(Esc), NUM(1), NUM(2), NUM(3), NUM(4), NUM(5)),         RROW1(NUM(6), NUM(7), NUM(8), NUM(9), NUM(0),     KEY(Minus)),
LROW2(KEY(Tab), KEY(Q), KEY(W), KEY(E), KEY(R), KEY(T)),         RROW2(KEY(Y), KEY(U), KEY(I), KEY(O), KEY(P),     KEY(Backslash)),
LROW3(RCTL,     KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),         RROW3(KEY(H), KEY(J), KEY(K), KEY(L), SEMI_,      QUOTE_),
LROW4(LSHFT,    KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),         RROW4(KEY(N), KEY(M), COMMA_, DOT_,   KEY(Slash), RSHFT),
LROW5(LCTL, LOPT, LCMD, KEY(PgUp),    KEY(OBRC), KEY(BKSP)),    RROW5(SPACE_, EQ_,     UP_,       ROPT, KEY(Del), KEY(Grave)),
LROW6(       KEY(Home), KEY(PgDn), KEY(End),       KEY(CBRC)), RROW6(ENTER_,    LEFT_, DOWN_, RIGHT_),
};

// clang-format on
