#if !defined(KEYMAP_H)
#define KEYMAP_H

#include "boardio.h"
#include "keyhelpers.h"

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
     LROW3(MAC_CAP, KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),
     RROW3(KEY(H), KEY(J), KEY(K), KEY(L), SEMI_, QUOTE_),
     LROW4(LSHFT, KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),
     RROW4(KEY(N), KEY(M), COMMA_, DOT_, KEY(SLASH), RSHFT),
     LROW5(LCTL, LOPT, LCMD, KEY(PGUP), KEY(GRAVE), KEY(BKSP)),
     RROW5(SPACE_, EQ_, UP_, KEY(OBRC), RCTL, KEY(CBRC)),
     LROW6(PLAY_, KEY(HOME), KEY(PGDN), KEY(END), KEY(DEL)),
     RROW6(ENTER_, LEFT_, DOWN_, RIGHT_, ROPT)},

    {// LAYER_FUNC (1)
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

    {// LAYER_MAC_CAP (2)
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
     RROW6(CM_RET, OP_LEFT, CM_DN, OP_RIGHT, NXTT_)}};

#endif
