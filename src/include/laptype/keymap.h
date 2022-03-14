#pragma once

#include "boardio.h"
#include "keyhelpers.h"

#define LROW1(l00, l01, l02, l03, l04, l05) l00, l01, l02, l03, l04, l05
#define LROW2(l10, l11, l12, l13, l14, l15) l10, l11, l12, l13, l14, l15
#define LROW3(l20, l21, l22, l23, l24, l25) l20, l21, l22, l23, l24, l25
#define LROW4(l30, l31, l32, l33, l34, l35) l30, l31, l32, l33, l34, l35
#define LROW5(l40, l41, l42, l43, l44, l45) l40, l41, l42, l43, l44, l45
#define LROW6(l52, l53, l54, lt55) ___, ___, l52, l53, l54, lt55

#define RROW1(r00, r01, r02, r03, r04, r05) r00, r01, r02, r03, r04, r05
#define RROW2(r10, r11, r12, r13, r14, r15) r10, r11, r12, r13, r14, r15
#define RROW3(r20, r21, r22, r23, r24, r25) r20, r21, r22, r23, r24, r25
#define RROW4(r30, r31, r32, r33, r34, r35) r30, r31, r32, r33, r34, r35
#define RROW5(r40, r41, r42, r43, r44, r45) r40, r41, r42, r43, r44, r45
#define RROW6(rt50, r51, r52, r53) rt50, r51, r52, r53, ___, ___

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

const uint16_t layer_colors[] = {
  ST77XX_BLUE, // Base/mac
  ST77XX_MAGENTA, // Windows
  ST77XX_CYAN, // Linux
  ST77XX_GREEN, // Fn
  ST77XX_ORANGE, // MacCaps
  ST77XX_YELLOW, // WinCap
  ST77XX_BLACK, // WinCtrl
  ST77XX_WHITE // LinCaps
};

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
LROW1(KEY(ESCAPE), KEY(1), KEY(2), KEY(3), KEY(4), KEY(5)),       RROW1(  KEY(6), KEY(7), KEY(8), KEY(9), KEY(0),     KEY(MINUS)),
LROW2(KEY(TAB),    KEY(Q), KEY(W), KEY(E), KEY(R), KEY(T)),       RROW2(  KEY(Y), KEY(U), KEY(I), KEY(O), KEY(P),     KEY(BACKSLASH)),
LROW3(MAC_CAP,     KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),       RROW3(  KEY(H), KEY(J), KEY(K), KEY(L), SEMI_,      QUOTE_),
LROW4(LSHFT,       KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),       RROW4(  KEY(N), KEY(M), COMMA_, DOT_,   KEY(SLASH), RSHFT),
LROW5(LCTL,   LOPT, LCMD, KEY(PGUP),    KEY(OBRC), KEY(BKSP)),    RROW5( SPACE_, EQ_,     UP_,     SHFT_FN, KEY(DEL), KEY(GRV)),
LROW6(         KEY(HOME), KEY(PGDN), KEY(END),        KEY(CBRC)), RROW6(ENTER_,    LEFT_, DOWN_, RIGHT_),
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
LROW3(___,      ___,     ___,     ___,     ___,     ___),     RROW3(  ___,     ___,     ___,     ___,     ___,      ___),
LROW4(___,      ___,     ___,     ___,     ___,     ___),     RROW4(  ___,     ___,     ___,     ___,     ___,      ___),
LROW5(___, ___,  ___,      ___,             ___,     ___),    RROW5( ___,     ___,          VOLUP_,      ___,  LYR_WIN, LYR_LIN),
LROW6(                PRVT_, PLAY_, NXTT_,            ___),   RROW6(___,               ___, VOLDN_, ___),
},
{// LAYER_MAC_CAP (4)
// Mostly just cmd + key (CMK(a)), with exceptions for some window
// manipulatiton bindings for my HammerSpoon configuration
LROW1(CMK(ESCAPE), CMK(1), CMK(2), CMK(3), CMK(4), CMK(5)),     RROW1(  CMK(6), CMK(7), CMK(8), CMK(9), CMK(0),  CMK(MINUS)),
LROW2(CMK(TAB),    CMK(Q), CMK(W), CMK(E), CMK(R), CMK(T)),     RROW2(  CMK(Y), CMK(U), CMK(I), CMK(O), CMK(P),  CMK(BACKSLASH)),
LROW3(___,         CMK(A), CMK(S), CMK(D), CMK(F), CMK(G)),     RROW3(  CMK(H), CMK(J), CMK(K), CMK(L), CM_SEMI, CM_QUOTE),
LROW4(SHFTCM,      CMK(Z), CMK(X), CMK(C), CMK(V), CMK(B)),     RROW4(  CMK(N), CMK(M), CM_CMA, CM_DOT, CM_SLSH, CM_SPC),
LROW5(CTLCM,   OPTCM,   ___,   CM_PUP,  CM_OBRC,   OPK(BKSP)),  RROW5( CM_SPC, CM_EQ,   CM_UP,    ___, CMK(DEL), CMK(GRV)),
LROW6(             CMK(HOME), CM_PDN, CMK(END),       CM_CBRC), RROW6(CM_ENT,  OP_LEFT, CM_DN, OP_RIGHT),
},
{// LAYER_WIN_CAP (5)
// This is magic to get a bunch of mac commands to send their Windows
// equivalent The poster children are Caps-Q => Alt-F4 and Caps-W => Ctl-F4
// Effectively making Caps-Q & Caps-W correspond to Quit and Close Window
// TODO: Support key sequences so that gui-left, up/down works for quadrant
// window docking. Alternatively, try to do it from AutoHotKey because the
// way Windows 10 natively handles it is shit.
LROW1(CTK(ESCAPE), CTK(1),  CTK(2),  CTK(3), CTK(4), CTK(5)),      RROW1(  CTK(6), CTK(7), CTK(8), CTK(9),      CTK(0),   CTK(MINUS)),
LROW2(CTK(TAB),    ALK(F4), CTK(F4), CTK(E), CTK(R), CTK(T)),      RROW2(  CTK(Y), CTK(U), CTK(I), CTK(O),      CTK(P),   CTK(BACKSLASH)),
LROW3(___,         CTK(A),  CTK(S),  CTK(D), CTK(F), CTK(G)),      RROW3(  CTK(H), CTK(J), CTK(K), CTK(L),      CT_SEMI,  CT_QUOTE),
LROW4(SHFTCT,      CTK(Z),  CTK(X),  CTK(C), CTK(V), CTK(B)),      RROW4(  CTK(N), CTK(M), CT_CMA, KEY(ESCAPE), CT_SLSH,  RGUI),
LROW5(LCTL,   GUICT,  ALTCT,  CT_PUP,    CTK(OBRC),   CTK(BKSP)),  RROW5( CT_SPC, CT_EQ,         CT_UP,     ___, CTK(DEL), CTK(GRV)),
LROW6(             CTK(HOME), CT_PDN, CTK(END),        CTK(CBRC)), RROW6(CT_ENT,        CT_LEFT, CT_DN, CT_RIGHT),
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
LROW1(CTK(ESCAPE), CTK(1),    CTK(2), CTK(3),   CTK(4), CTK(5)),       RROW1(  CTK(6), CTK(7), CTK(8), CTK(9), CTK(0),  CTK(MINUS)),
LROW2(CTK(TAB),    CTK(Q),    CTK(W), KEY(END), CTK(R), CTK(T)),       RROW2(  CTK(Y), CTK(U), CTK(I), CTK(O), UP_,     CTK(BACKSLASH)),
LROW3(LCTL,        KEY(HOME), CTK(S), KEY(DEL), RIGHT_, CTK(G)),       RROW3(  CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
LROW4(SHFTCT,      CTK(Z),    CTK(X), CTK(C),   CTK(V), CTK(B)),       RROW4(  DOWN_,  CTK(M), CT_CMA, CT_DOT, CT_SLSH, RSHFT | LCTL),
LROW5(___,     GUICT, ALTCT,   CT_PUP,        CTK(OBRC), CTK(BKSP)),   RROW5( CT_SPC, CT_EQ,      CT_UP,    ___, CTK(DEL), CTK(GRAVE)),
LROW6(              CTK(HOME), CT_PDN, CTK(END),           CTK(CBRC)), RROW6(CT_ENT,     CT_LEFT, CT_DN, CT_RIGHT),
},
{// LAYER_LIN_CAP (7)
LROW1(CTK(ESCAPE), CTK(1),  CTK(2),  CTK(3), CTK(4), CTK(5)),      RROW1(  CTK(6), CTK(7), CTK(8), CTK(9), CTK(0),   CTK(MINUS)),
LROW2(CTK(TAB),    ALK(F4), CTK(F4), CTK(E), CTK(R), CTK(T)),      RROW2(  CTK(Y), CTK(U), CTK(I), CTK(O), CTK(P),   CTK(BACKSLASH)),
LROW3(___,         CTK(A),  CTK(S),  CTK(D), CTK(F), CTK(G)),      RROW3(  CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI,  CT_QUOTE),
LROW4(SHFTCT,      CTK(Z),  CTK(X),  CTK(C), CTK(V), CTK(B)),      RROW4(  CTK(N), CTK(M), CT_CMA, CT_DOT, CT_SLSH,  RGUI),
LROW5(LCTL, GUICT,  ALTCT,   CT_PUP,       CTK(OBRC), CTK(BKSP)),  RROW5( CT_SPC, CT_EQ,      CT_UP,   ___, CTK(DEL), CTK(GRAVE)),
LROW6(            CTK(HOME), CT_PDN, CTK(END),         KEY(CBRC)), RROW6(CT_ENT,     CT_LEFT, CT_DN, CT_RIGHT),
},
};
// clang-format on
