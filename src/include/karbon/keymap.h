#pragma once

#include "boardio.h"
#include "dongle.h"
#include "keyhelpers.h"

#define LROW1(l00, l01, l02, l03, l04, l05) l05, l04, l03, l02, l01, l00
#define LROW2(l10, l11, l12, l13, l14, l15) l15, l14, l13, l12, l11, l10
#define LROW3(l20, l21, l22, l23, l24, l25) l25, l24, l23, l22, l21, l20
#define LROW4(l30, l31, l32, l33, l34, l35) l35, l34, l33, l32, l31, l30
#define LROW5(l40, l41, l42, l43, l44, l45) l45, l44, l43, l42, l41, l40
#define LROW6(l52, l53, l54, lt55) lt55, l54, l53, l52, ___, ___

#define RROW1(r00, r01, r02, r03, r04, r05) r05, r04, r03, r02, r01, r00
#define RROW2(r10, r11, r12, r13, r14, r15) r15, r14, r13, r12, r11, r10
#define RROW3(r20, r21, r22, r23, r24, r25) r25, r24, r23, r22, r21, r20
#define RROW4(r30, r31, r32, r33, r34, r35) r35, r34, r33, r32, r31, r30
#define RROW5(r40, r41, r42, r43, r44, r45) r45, r44, r43, r42, r41, r40
#define RROW6(rt51, r52, r53, r54) ___, ___, r54, r53, r52, rt51

#define PROW1(t1, t2, t3) t1, t2, t3
#define PROW2(b1, b2, b3) b1, b2, b3

#if defined(STATUS_DUMP)
// For the status dumper thingamajig
const char* layer_names[] = {
    "Base/Mac", "Win", "Fn", "MacCaps", "WinCaps", "WinCtrl"};
#endif

const uint32_t layer_colors[] = {
    0x000000, // Base/mac
    0x040000, // Windows: Red
    0x000400, // Fn: Green
    0x000004, // MacCaps: Blue
    0x040004, // WinCaps: Purple
    0x040400  // WinCtrl: Yellow
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

const action_t keymap[][MatrixBits::num_bits * 2 + MacroBits::num_bits] = {
    {// LAYER_MAC_BASE (0)
     LROW1(KEY(ESCAPE), KEY(1), KEY(2), KEY(3), KEY(4), KEY(5)),
     LROW2(KEY(TAB), KEY(Q), KEY(W), KEY(E), KEY(R), KEY(T)),
     LROW3(MAC_CAP, KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),
     LROW4(LSHFT, KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),
     LROW5(LCTL, LOPT, LCMD, KEY(PGUP), KEY(GRAVE), KEY(BKSP)),
     LROW6(KEY(HOME), KEY(PGDN), KEY(END), KEY(DEL)),

     RROW1(KEY(6), KEY(7), KEY(8), KEY(9), KEY(0), KEY(MINUS)),
     RROW2(KEY(Y), KEY(U), KEY(I), KEY(O), KEY(P), KEY(BACKSLASH)),
     RROW3(KEY(H), KEY(J), KEY(K), KEY(L), SEMI_, QUOTE_),
     RROW4(KEY(N), KEY(M), COMMA_, DOT_, KEY(SLASH), RSHFT),
     RROW5(SPACE_, EQ_, UP_, KEY(OBRC), ROPT, KEY(CBRC)),
     RROW6(ENTER_, LEFT_, DOWN_, RIGHT_),

     PROW1(VOLDN_, MUTE_, VOLUP_),
     PROW2(PRVT_, PLAY_, NXTT_)},

    {// LAYER_WIN_BASE (1)
     // Put Alt & GUI in the right spots, Add the Insert key (instead of PRVT),
     // Print Screen (instead of NXTT) and the application key (instead of MUTE)
     LROW1(___, ___, ___, ___, ___, ___),
     LROW2(___, ___, ___, ___, ___, ___),
     LROW3(WIN_CAP, ___, ___, ___, ___, ___),
     LROW4(___, ___, ___, ___, ___, ___),
     LROW5(WIN_CTL, LGUI, LALT, ___, ___, ___),
     LROW6(___, ___, ___, ___),

     RROW1(___, ___, ___, ___, ___, ___),
     RROW2(___, ___, ___, ___, ___, ___),
     RROW3(___, ___, ___, ___, ___, ___),
     RROW4(___, ___, ___, ___, ___, ___),
     RROW5(___, ___, ___, ___, RGUI, ___),
     RROW6(___, ___, ___, ___),

     PROW1(___, ___, ___),
     PROW2(___, ___, ___)},

    {// LAYER_FUNC (2)
     // Nothing too exciting here. I might perhaps go add my Rocksmith
     // keybindings, and perhaps put the function keys in a more 'debugger
     // binding friendly' order...
     LROW1(KEY(F12), KEY(F1), KEY(F2), KEY(F3), KEY(F4), KEY(F5)),
     LROW2(___, ___, ___, ___, ___, ___),
     LROW3(___, ___, ___, ___, ___, ___),
     LROW4(___, ___, ___, ___, ___, ___),
     LROW5(___, ___, ___, ___, ___, ___),
     LROW6(___, ___, ___, ___),

     RROW1(KEY(F6), KEY(F7), KEY(F8), KEY(F9), KEY(F10), KEY(F11)),
     RROW2(___, ___, ___, ___, ___, ___),
     RROW3(___, ___, ___, ___, ___, ___),
     RROW4(___, ___, ___, ___, ___, ___),
     RROW5(___, ___, ___, ___, ___, ___),
     RROW6(___, ___, ___, ___),

     PROW1(___, ___, ___),
     PROW2(___, ___, ___)},

    {// LAYER_MAC_CAP (3)
     // Mostly just cmd + key (CMK(a)), with exceptions for some window
     // manipulatiton bindings for my HammerSpoon configuration
     LROW1(CMK(ESCAPE), CMK(1), CMK(2), CMK(3), CMK(4), CMK(5)),
     LROW2(CMK(TAB), CMK(Q), CMK(W), CMK(E), CMK(R), CMK(T)),
     LROW3(___, CMK(A), CMK(S), CMK(D), CMK(F), CMK(G)),
     LROW4(SHFTCM, CMK(Z), CMK(X), CMK(C), CMK(V), CMK(B)),
     LROW5(CTLCM, OPTCM, ___, CM_PUP, CMK(GRAVE), OPK(BKSP)),
     LROW6(CMK(HOME), CM_PDN, CMK(END), OPK(DEL)),

     RROW1(CMK(6), CMK(7), CMK(8), CMK(9), CMK(0), CMK(MINUS)),
     RROW2(CMK(Y), CMK(U), CMK(I), CMK(O), CMK(P), CMK(BACKSLASH)),
     RROW3(CMK(H), CMK(J), CMK(K), CMK(L), CM_SEMI, CM_QUOTE),
     RROW4(CMK(N), CMK(M), CM_CMA, CM_DOT, CM_SLSH, CM_SPC),
     RROW5(CM_SPC, CM_EQ, CM_UP, CM_CBRC, ___, CM_OBRC),
     RROW6(CM_RET, OP_LEFT, CM_DN, OP_RIGHT),

     PROW1(___, LYR_WIN, ___),
     PROW2(___, LYR_FN, ___)},

    {// LAYER_WIN_CAP (4)
     // This is magic to get a bunch of mac commands to send their Windows
     // equivalent The poster children are Caps-Q => Alt-F4 and Caps-W => Ctl-F4
     // Effectively making Caps-Q & Caps-W correspond to Quit and Close Window
     // TODO: Support key sequences so that gui-left, up/down works for quadrant
     // window docking. Alternatively, try to do it from AutoHotKey because the
     // way Windows 10 natively handles it is shit.
     LROW1(CTK(ESCAPE), CTK(1), CTK(2), CTK(3), CTK(4), CTK(5)),
     LROW2(CTK(TAB), ALK(F4), CTK(F4), CTK(E), CTK(R), CTK(T)),
     LROW3(___, CTK(A), CTK(S), CTK(D), CTK(F), CTK(G)),
     LROW4(SHFTCT, CTK(Z), CTK(X), CTK(C), CTK(V), CTK(B)),
     LROW5(LCTL, GUICT, ALTCT, CT_PUP, CTK(GRAVE), CTK(BKSP)),
     LROW6(CTK(HOME), CT_PDN, CTK(END), CTK(DEL)),

     RROW1(CTK(6), CTK(7), CTK(8), CTK(9), CTK(0), CTK(MINUS)),
     RROW2(CTK(Y), CTK(U), CTK(I), CTK(O), CTK(P), CTK(BACKSLASH)),
     RROW3(CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
     RROW4(CTK(N), CTK(M), CT_CMA, KEY(ESCAPE), CT_SLSH, RGUI),
     RROW5(CT_SPC, CT_EQ, CT_UP, CT_OBRC, ___, CT_CBRC),
     RROW6(CT_RET, CT_LEFT, CT_DN, CT_RIGHT),

     PROW1(___, LYR_MAC, ___),
     PROW2(___, LYR_FN, ___)},

    {// LAYER_WIN_CTL (5)
     // This is magic to make Unix line editing controls to work like they do in
     // Unix, but when working on Windows. The only one I can't really do is
     // ctrl-t because Transpose would require something quite fancy. I could
     // pull it off with use of the clipboard and sequence support, but that's
     // not likely to happen until I actually care.  Note: I'm not mapping any
     // of the media-ish keys. I probably should.  The one thing I don't think
     // I've really done is think about alt-prscn for handling screenshots & the
     // like...
     LROW1(CTK(ESCAPE), CTK(1), CTK(2), CTK(3), CTK(4), CTK(5)),
     LROW2(CTK(TAB), CTK(Q), CTK(W), KEY(END), CTK(R), CTK(T)),
     LROW3(LCTL, KEY(HOME), CTK(S), KEY(DEL), RIGHT_, CTK(G)),
     LROW4(SHFTCT, CTK(Z), CTK(X), CTK(C), CTK(V), CTK(B)),
     LROW5(___, GUICT, ALTCT, CT_PUP, CTK(GRAVE), CTK(BKSP)),
     LROW6(CTK(HOME), CT_PDN, CTK(END), CTK(DEL)),

     RROW1(CTK(6), CTK(7), CTK(8), CTK(9), CTK(0), CTK(MINUS)),
     RROW2(CTK(Y), CTK(U), CTK(I), CTK(O), UP_, CTK(BACKSLASH)),
     RROW3(CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
     RROW4(DOWN_, CTK(M), CT_CMA, CT_DOT, CT_SLSH, RSHFT | LCTL),
     RROW5(CT_SPC, CT_EQ, CT_UP, CT_OBRC, ___, CT_CBRC),
     RROW6(CT_RET, CT_LEFT, CT_DN, CT_RIGHT),

     PROW1(___, ___, ___),
     PROW2(___, ___, ___)}};
