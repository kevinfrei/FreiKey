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

#if STATUS_DUMP
// For the status dumper thingamajig
const char* layer_names[] = {
    "Base/Mac", "Win", "Fn", "MacCaps", "WinCaps", "WinCtrl"};
#endif

// PRVT_, NXTT_, KEY(INSERT), CQ_EQ
const action_t keymap[][numcols * numrows * 2] = {
    {// LAYER_MAC_BASE (0)
     LROW1(KEY(ESCAPE), KEY(1), KEY(2), KEY(3), KEY(4), KEY(5)),
     LROW2(KEY(TAB), KEY(Q), KEY(W), KEY(E), KEY(R), KEY(T)),
     LROW3(MAC_CAP, KEY(A), KEY(S), KEY(D), KEY(F), KEY(G)),
     LROW4(LSHFT, KEY(Z), KEY(X), KEY(C), KEY(V), KEY(B)),
     LROW5(LCTL, LOPT, LCMD, KEY(PGUP), KEY(GRAVE), KEY(BKSP), KEY(DEL)),
     LROW6(PLAY_, KEY(HOME), KEY(PGDN), KEY(END), LYR_FN, KEY(OBRC)),

     RROW1(KEY(6), KEY(7), KEY(8), KEY(9), KEY(0), KEY(MINUS)),
     RROW2(KEY(Y), KEY(U), KEY(I), KEY(O), KEY(P), KEY(BACKSLASH)),
     RROW3(KEY(H), KEY(J), KEY(K), KEY(L), SEMI_, QUOTE_),
     RROW4(KEY(N), KEY(M), COMMA_, DOT_, KEY(SLASH), RSHFT),
     RROW5(ENTER_, SPACE_, EQ_, UP_, VOLDN_, MUTE_, VOLUP_),
     RROW6(KEY(CBRC), LYR_WIN, LEFT_, DOWN_, RIGHT_, ROPT)},

    {// LAYER_WIN_BASE (1)
     // Put Alt & GUI in the right spots, Add the Insert key (instead of PRVT),
     // Print Screen (instead of NXTT) and the application key (instead of MUTE)
     LROW1(___, ___, ___, ___, ___, ___),
     LROW2(___, ___, ___, ___, ___, ___),
     LROW3(WIN_CAP, ___, ___, ___, ___, ___),
     LROW4(___, ___, ___, ___, ___, ___),
     LROW5(WIN_CTL, LGUI, LALT, ___, ___, ___, ___),
     LROW6(KEY(APPLICATION), ___, ___, ___, ___, ___),

     RROW1(___, ___, ___, ___, ___, ___),
     RROW2(___, ___, ___, ___, ___, ___),
     RROW3(___, ___, ___, ___, ___, ___),
     RROW4(___, ___, ___, ___, ___, ___),
     RROW5(___, ___, ___, ___, ___, ___, ___),
     RROW6(___, LYR_MAC, ___, ___, ___, RGUI)},

    {// LAYER_FUNC (2)
     // Nothing too exciting here. I might perhaps go add my Rocksmith
     // keybindings, and perhaps put the function keys in a more 'debugger
     // binding friendly' order...
     LROW1(KEY(F12), KEY(F1), KEY(F2), KEY(F3), KEY(F4), KEY(F5)),
     LROW2(___, ___, ___, ___, ___, ___),
     LROW3(___, ___, ___, ___, ___, ___),
     LROW4(___, ___, ___, ___, ___, ___),
     LROW5(___, ___, ___, ___, ___, ___, ___),
     LROW6(___, ___, ___, ___, ___, ___),

     RROW1(KEY(F6), KEY(F7), KEY(F8), KEY(F9), KEY(F10), KEY(F11)),
     RROW2(___, ___, ___, ___, ___, ___),
     RROW3(___, ___, ___, ___, ___, ___),
     RROW4(___, ___, ___, ___, ___, ___),
     RROW5(___, ___, ___, ___, ___, ___, ___),
     RROW6(___, ___, ___, ___, ___, ___)},

    {// LAYER_MAC_CAP (3)
     // Mostly just cmd + key (CMK(a)), with exceptions for some window
     // manipulatiton bindings for my HammerSpoon configuration
     LROW1(CMK(ESCAPE), CMK(1), CMK(2), CMK(3), CMK(4), CMK(5)),
     LROW2(CMK(TAB), CMK(Q), CMK(W), CMK(E), CMK(R), CMK(T)),
     LROW3(___, CMK(A), CMK(S), CMK(D), CMK(F), CMK(G)),
     LROW4(SHFTCM, CMK(Z), CMK(X), CMK(C), CMK(V), CMK(B)),
     LROW5(CTLCM, OPTCM, ___, CM_PUP, CMK(GRAVE), OPK(BKSP), OPK(DEL)),
     LROW6(PRVT_, CMK(HOME), CM_PDN, CMK(END), ___, CM_OBRC),

     RROW1(CMK(6), CMK(7), CMK(8), CMK(9), CMK(0), CMK(MINUS)),
     RROW2(CMK(Y), CMK(U), CMK(I), CMK(O), CMK(P), CMK(BACKSLASH)),
     RROW3(CMK(H), CMK(J), CMK(K), CMK(L), CM_SEMI, CM_QUOTE),
     RROW4(CMK(N), CMK(M), CM_CMA, CM_DOT, CM_SLSH, CM_SPC),
     RROW5(CM_RET, CM_SPC, CM_EQ, CM_UP, MAC_WNL, MAC_WNMX, MAC_WNR),
     RROW6(CM_CBRC, ___, OP_LEFT, CM_DN, OP_RIGHT, NXTT_)},

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
     LROW5(LCTL, GUICT, ALTCT, CT_PUP, CTK(GRAVE), CTK(BKSP), CTK(DEL)),
     LROW6(PRVT_, CTK(HOME), CT_PDN, CTK(END), ___, CT_OBRC),

     RROW1(CTK(6), CTK(7), CTK(8), CTK(9), CTK(0), CTK(MINUS)),
     RROW2(CTK(Y), CTK(U), CTK(I), CTK(O), CTK(P), CTK(BACKSLASH)),
     RROW3(CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
     RROW4(CTK(N), CTK(M), CT_CMA, KEY(ESCAPE), CT_SLSH, RGUI),
     RROW5(CT_RET, CT_SPC, CT_EQ, CT_UP, WIN_WNL, WIN_WNMX, WIN_WNR),
     RROW6(CT_CBRC, ___, CT_LEFT, CT_DN, CT_RIGHT, NXTT_)},
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
     LROW5(___, GUICT, ALTCT, CT_PUP, CTK(GRAVE), CTK(BKSP), CTK(DEL)),
     LROW6(___, CTK(HOME), CT_PDN, CTK(END), ___, CT_OBRC),

     RROW1(CTK(6), CTK(7), CTK(8), CTK(9), CTK(0), CTK(MINUS)),
     RROW2(CTK(Y), CTK(U), CTK(I), CTK(O), UP_, CTK(BACKSLASH)),
     RROW3(CTK(H), CTK(J), CTK(K), CTK(L), CT_SEMI, CT_QUOTE),
     RROW4(DOWN_, CTK(M), CT_CMA, CT_DOT, CT_SLSH, RSHFT | LCTL),
     RROW5(CT_RET, CT_SPC, CT_EQ, CT_UP, ___, ___, ___),
     RROW6(CT_CBRC, ___, CT_LEFT, CT_DN, CT_RIGHT, NXTT_)}};
