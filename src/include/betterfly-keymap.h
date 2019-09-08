#if !defined(KEYMAP_H)
#define KEYMAP_H

#include "keyhelpers.h"
#include "boardio.h"

#if defined(STATUS_DUMP)
// For the status dumper thingamajig
const char* layer_names[] = {
    "Base/Mac", "Win", "Fn", "MacCaps", "WinCaps", "WinCtrl"};
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

const action_t keymap[][BoardIO::matrix_size] = {
    {// LAYER_MAC_BASE (0) // LROW3:RCMD=>MAC_CAP, RROW5:CTRL=>LYR_WIN
     LROW1(KEY(ESCAPE), KEY(1), KEY(2), KEY(3), KEY(4), KEY(5)),
     RROW1(KEY(6), KEY(7), KEY(8), KEY(9), KEY(0), KEY(MINUS)),
     LROW2(KEY(TAB), KEY(Q), KEY(W), KEY(E), KEY(R), KEY(T)),
     RROW2(KEY(Y), KEY(U), KEY(I), KEY(O), KEY(P), KEY(BACKSLASH)),
     LROW3(RCMD, KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),
     RROW3(KEY(H), KEY(J), KEY(K), KEY(L), SEMI_, QUOTE_),
     LROW4(LSHFT, KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),
     RROW4(KEY(N), KEY(M), COMMA_, DOT_, KEY(SLASH), RSHFT),
     LROW5(LCTL, LOPT, LCMD, KEY(PGUP), KEY(GRAVE), KEY(BKSP)),
     RROW5(SPACE_, EQ_, UP_, KEY(OBRC), RCTL, KEY(CBRC)),
     LROW6(PLAY_, KEY(HOME), KEY(PGDN), KEY(END), KEY(DEL)),
     RROW6(ENTER_, LEFT_, DOWN_, RIGHT_, ROPT)},

    {// LAYER_WIN_BASE (1)
     // Put Alt & GUI in the right spots, Add the Insert key (instead of PRVT),
     // Print Screen (instead of NXTT) and the application key (instead of MUTE)
     LROW1(___, ___, ___, ___, ___, ___),
     RROW1(___, ___, ___, ___, ___, ___),
     LROW2(___, ___, ___, ___, ___, ___),
     RROW2(___, ___, ___, ___, ___, ___),
     LROW3(WIN_CAP, ___, ___, ___, ___, ___),
     RROW3(___, ___, ___, ___, ___, ___),
     LROW4(___, ___, ___, ___, ___, ___),
     RROW4(___, ___, ___, ___, ___, ___),
     LROW5(WIN_CTL, LGUI, LALT, ___, ___, ___),
     RROW5(___, ___, ___, ___, ___, LYR_MAC),
     LROW6(KEY(APPLICATION), ___, ___, ___, ___),
     RROW6(___, ___, ___, ___, RGUI)},

    {// LAYER_FUNC (2)
     // Nothing too exciting here. I might perhaps go add my Rocksmith
     // keybindings, and perhaps put the function keys in a more 'debugger
     // binding friendly' order...
     LROW1(KEY(F12), KEY(F1), KEY(F2), KEY(F3), KEY(F4), KEY(F5)),
     RROW1(KEY(F6), KEY(F7), KEY(F8), KEY(F9), KEY(F10), KEY(F11)),
     LROW2(___, ___, ___, ___, ___, ___),
     RROW2(___, ___, ___, ___, ___, ___),
     LROW3(___, ___, ___, ___, ___, ___),
     RROW3(___, ___, ___, ___, ___, ___),
     LROW4(___, ___, ___, ___, ___, ___),
     RROW4(___, ___, ___, ___, ___, ___),
     LROW5(___, ___, ___, ___, ___, ___),
     RROW5(___, ___, ___, ___, ___, ___),
     LROW6(___, ___, ___, ___, ___),
     RROW6(___, ___, ___, ___, ___)},

    {// LAYER_MAC_CAP (3)
     // Mostly just cmd + key (CMK(a)), with exceptions for some window
     // manipulatiton bindings for my HammerSpoon configuration
     LROW1(CMK(ESCAPE), CMK(1), CMK(2), CMK(3), CMK(4), CMK(5)),
     RROW1(CMK(6), CMK(7), CMK(8), CMK(9), CMK(0), CMK(MINUS)),
     LROW2(CMK(TAB), CMK(Q), CMK(W), CMK(E), CMK(R), CMK(T)),
     RROW2(CMK(Y), CMK(U), CMK(I), CMK(O), CMK(P), CMK(BACKSLASH)),
     LROW3(___, CMK(A), CMK(S), CMK(D), CMK(F), CMK(G)),
     RROW3(CMK(H), CMK(J), CMK(K), CMK(L), CM_SEMI, CM_QUOTE),
     LROW4(SHFTCM, CMK(Z), CMK(X), CMK(C), CMK(V), CMK(B)),
     RROW4(CMK(N), CMK(M), CM_CMA, CM_DOT, CM_SLSH, CM_SPC),
     LROW5(CTLCM, OPTCM, ___, CM_PUP, CMK(GRAVE), OPK(BKSP)),
     RROW5(CM_SPC, CM_EQ, CM_UP, CM_OBRC, MAC_WNMX, CM_CBRC),
     LROW6(PRVT_, CMK(HOME), CM_PDN, CMK(END), OPK(DEL)),
     RROW6(CM_RET, OP_LEFT, CM_DN, OP_RIGHT, NXTT_)},

    {// LAYER_WIN_CAP (4)
     // This is magic to get a bunch of mac commands to send their Windows
     // equivalent The poster children are Caps-Q => Alt-F4 and Caps-W => Ctl-F4
     // Effectively making Caps-Q & Caps-W correspond to Quit and Close Window
     // TODO: Support key sequences so that gui-left, up/down works for quadrant
     // window docking. Alternatively, try to do it from AutoHotKey because the
     // way Windows 10 natively handles it is shit.
     LROW1(CTK(ESCAPE), CTK(1), CTK(2), CTK(3), CTK(4), CTK(5)),
     RROW1(CTK(6), CTK(7), CTK(8), CTK(9), CTK(0), CTK(MINUS)),
     LROW2(CTK(TAB), ALK(F4), CTK(F4), CTK(E), CTK(R), CTK(T)),
     RROW2(CTK(Y), CTK(U), CTK(I), CTK(O), CTK(P), CTK(BACKSLASH)),
     LROW3(___, CTK(A), CTK(S), CTK(D), CTK(F), CTK(G)),
     RROW3(CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
     LROW4(SHFTCT, CTK(Z), CTK(X), CTK(C), CTK(V), CTK(B)),
     RROW4(CTK(N), CTK(M), CT_CMA, KEY(ESCAPE), CT_SLSH, RGUI),
     LROW5(LCTL, GUICT, ALTCT, CT_PUP, CTK(GRAVE), CTK(BKSP)),
     RROW5(CT_SPC, CT_EQ, CT_UP, CT_OBRC, WIN_WNMX, CT_CBRC),
     LROW6(PRVT_, CTK(HOME), CT_PDN, CTK(END), CTK(DEL)),
     RROW6(CT_RET, CT_LEFT, CT_DN, CT_RIGHT, NXTT_)},
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
     RROW1(CTK(6), CTK(7), CTK(8), CTK(9), CTK(0), CTK(MINUS)),
     LROW2(CTK(TAB), CTK(Q), CTK(W), KEY(END), CTK(R), CTK(T)),
     RROW2(CTK(Y), CTK(U), CTK(I), CTK(O), UP_, CTK(BACKSLASH)),
     LROW3(LCTL, KEY(HOME), CTK(S), KEY(DEL), RIGHT_, CTK(G)),
     RROW3(CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
     LROW4(SHFTCT, CTK(Z), CTK(X), CTK(C), CTK(V), CTK(B)),
     RROW4(DOWN_, CTK(M), CT_CMA, CT_DOT, CT_SLSH, RSHFT | LCTL),
     LROW5(___, GUICT, ALTCT, CT_PUP, CTK(GRAVE), CTK(BKSP)),
     RROW5(CT_SPC, CT_EQ, CT_UP, CT_OBRC, ___, CT_CBRC),
     LROW6(___, CTK(HOME), CT_PDN, CTK(END), CTK(DEL)),
     RROW6(CT_RET, CT_LEFT, CT_DN, CT_RIGHT, NXTT_)}};

#endif
