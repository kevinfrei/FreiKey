#pragma once

#include "sysstuff.h"

#define LROW1(l00, l01, l02, l03, l04, l05) \
  KEY(l05), KEY(l04), KEY(l03), KEY(l02), KEY(l01), KEY(l00)
#define LROW2(l10, l11, l12, l13, l14, l15) \
  KEY(l15), KEY(l14), KEY(l13), KEY(l12), KEY(l11), KEY(l10)
#define LROW3(l20, l21, l22, l23, l24, l25) \
  KEY(l25), KEY(l24), KEY(l23), KEY(l22), KEY(l21), KEY(l20)
#define LROW4(l30, l31, l32, l33, l34, l35) \
  KEY(l35), KEY(l34), KEY(l33), KEY(l32), KEY(l31), KEY(l30)
#define LROW5(l40, l41, l42, l43, l44, l45) \
  KEY(l45), KEY(l44), KEY(l43), KEY(l42), KEY(l41), KEY(l40)
#define LROW6(l52, l53, l54, lt55) \
  KEY(lt55), KEY(l54), KEY(l53), KEY(l52), KEY(___), KEY(___)

#define RROW1(r00, r01, r02, r03, r04, r05) \
  KEY(r05), KEY(r04), KEY(r03), KEY(r02), KEY(r01), KEY(r00)
#define RROW2(r10, r11, r12, r13, r14, r15) \
  KEY(r15), KEY(r14), KEY(r13), KEY(r12), KEY(r11), KEY(r10)
#define RROW3(r20, r21, r22, r23, r24, r25) \
  KEY(r25), KEY(r24), KEY(r23), KEY(r22), KEY(r21), KEY(r20)
#define RROW4(r30, r31, r32, r33, r34, r35) \
  KEY(r35), KEY(r34), KEY(r33), KEY(r32), KEY(r31), KEY(r30)
#define RROW5(r40, r41, r42, r43, r44, r45) \
  KEY(r45), KEY(r44), KEY(r43), KEY(r42), KEY(r41), KEY(r40)
#define RROW6(rt51, r52, r53, r54) \
  KEY(___), KEY(___), KEY(r54), KEY(r53), KEY(r52), KEY(rt51)

#define PROW1(t1, t2, t3) KEY(t1), KEY(t2), KEY(t3)
#define PROW2(b1, b2, b3) KEY(b1), KEY(b2), KEY(b3)

constexpr uint8_t base_keys[MatrixBits::num_bits * 2 + MacroBits::num_bits] = {
    LROW1(ESCAPE, 1, 2, 3, 4, 5),
    LROW2(TAB, Q, W, E, R, T),
    LROW3(CAPS_LOCK, A, S, D, F, G),
    LROW4(SHIFT_LEFT, Z, X, C, V, B),
    LROW5(CONTROL_LEFT, GUI_LEFT, ALT_LEFT, PAGE_UP, GRAVE, BKSP),
    LROW6(HOME, PGDN, END, DEL),

    RROW1(6, 7, 8, 9, 0, MINUS),
    RROW2(Y, U, I, O, P, BACKSLASH),
    RROW3(H, J, K, L, SEMICOLON, APOSTROPHE),
    RROW4(N, M, COMMA, PERIOD, SLASH, SHIFT_RIGHT),
    RROW5(SPACE, EQUAL, ARROW_UP, BRACKET_LEFT, GUI_RIGHT, BRACKET_RIGHT),
    RROW6(RETURN, ARROW_LEFT, ARROW_DOWN, ARROW_RIGHT),

    PROW1(F1, F2, F3),
    PROW2(F4, F5, F6)};

constexpr inline uint8_t scanCodeOf(uint8_t keyCode, uint8_t index = 0) {
  if (index >= sizeof(base_keys)) {
    return 0xFF;
  }
  if (base_keys[index] == keyCode) {
    return index;
  }
  return scanCodeOf(keyCode, index + 1);
}
