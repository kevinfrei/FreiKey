#include <bluefruit.h>

#define MANUFACTURER "FreikyStuff"
#define MODEL "BlErgoDox"
#define BT_NAME "BlErgoDox"
#define HW_REV "0000"
#define LHS_NAME BT_NAME "-LHS"

using scancode_t = uint8_t;

void shared_setup();
