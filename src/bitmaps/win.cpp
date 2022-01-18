#include "bitmap.h"

// clang-format off
static const uint8_t gfx_win_data[2001] PROGMEM = {
0x33,0x81,0x00,0x00,0x8E,0x08,0x21,0x18,0x44,0x28,0x66,0x38,0x88,0x48,0xCA,0x50,0xEC,0x18,0x23,0x25,0x81,0x00,0x00,0x8E,0x08,0x21,0x18,0x43,0x28,0x66,0x30,0x88,
0x40,0xAA,0x50,0xEC,0x61,0x0E,0x8D,0x69,0x0F,0x82,0x18,0x43,0x17,0x81,0x00,0x00,0x8E,0x08,0x01,0x18,0x43,0x20,0x65,0x30,0x87,0x40,0xAA,0x50,0xCC,0x61,0x0E,0x9B,
0x69,0x0F,0x82,0x18,0x43,0x09,0x81,0x00,0x00,0x8E,0x08,0x01,0x10,0x23,0x20,0x65,0x30,0x87,0x40,0xA9,0x50,0xCB,0x60,0xED,0xA9,0x69,0x0F,0x82,0x18,0x43,0xFB,0x00,
0x00,0x8E,0x00,0x01,0x10,0x22,0x20,0x45,0x30,0x87,0x40,0xA9,0x48,0xCB,0x58,0xED,0xB7,0x69,0x0F,0x82,0x18,0x43,0xEF,0x00,0x00,0x8E,0x10,0x22,0x20,0x44,0x28,0x66,
0x38,0xA9,0x48,0xCB,0x58,0xED,0x61,0x0F,0xC3,0x69,0x0F,0x82,0x18,0x43,0xE1,0x00,0x00,0x8E,0x08,0x22,0x18,0x44,0x28,0x66,0x38,0x88,0x48,0xCA,0x58,0xED,0x61,0x0E,
0xD1,0x69,0x0F,0x82,0x18,0x43,0xD7,0x00,0x00,0x8A,0x10,0x22,0x38,0x88,0x48,0xCA,0x50,0xEC,0x61,0x0E,0xDF,0x69,0x0F,0x82,0x18,0x43,0xC5,0x00,0x00,0x86,0x08,0x22,
0x18,0x44,0x28,0x66,0x85,0x38,0x88,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xB5,0x00,0x00,0x90,0x00,0x01,0x10,0x22,0x20,0x44,0x28,0x66,0x38,
0xA8,0x48,0xCA,0x58,0xEC,0x61,0x0E,0x89,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xA7,0x00,0x00,0x90,0x08,0x01,0x18,
0x43,0x20,0x65,0x30,0x87,0x40,0xA9,0x48,0xCB,0x58,0xED,0x61,0x0F,0x97,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0x99,
0x00,0x00,0x8E,0x08,0x22,0x18,0x44,0x28,0x66,0x38,0x88,0x40,0xAA,0x50,0xCC,0x61,0x0E,0xA7,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,
0x82,0x18,0x43,0x89,0x00,0x00,0x90,0x00,0x01,0x10,0x22,0x20,0x44,0x28,0x66,0x38,0xA8,0x48,0xCA,0x58,0xED,0x61,0x0E,0xB5,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,
0x82,0x20,0x65,0xE7,0x69,0x0F,0x8C,0x18,0x43,0x30,0x87,0x40,0xA9,0x50,0xCB,0x58,0xED,0x61,0x0F,0xC3,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,
0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,
0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,
0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,
0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,
0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,
0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,
0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,
0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,
0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,
0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,
0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,
0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,
0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,
0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,
0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,
0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,
0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,
0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0x87,0x61,0x0E,0xA3,0x58,0xED,0x9F,0x50,0xCC,0x82,0x50,0xCB,0x85,
0x48,0xCA,0x82,0x40,0xA9,0x89,0x00,0x00,0x84,0x18,0x43,0x40,0xAA,0x95,0x40,0xA9,0x85,0x38,0xA9,0x8F,0x38,0x88,0x82,0x30,0x88,0x89,0x30,0x87,0x97,0x28,0x66,0x82,
0x28,0x65,0x8F,0x20,0x65,0x85,0x20,0x45,0x85,0x20,0x44,0x87,0x18,0x44,0x82,0x08,0x01,0x41,0x84,0x00,0x00,0x89,0x08,0x21,0x8F,0x08,0x01,0x2B,0x81,0x00,0x00,0x97,
0x69,0x0F,0x9D,0x61,0x0E,0x82,0x60,0xEE,0x99,0x58,0xED,0x82,0x48,0xCB,0x89,0x00,0x00,0x82,0x18,0x43,0x91,0x38,0xA9,0x82,0x38,0xA8,0xBF,0x38,0x88,0x97,0x30,0x88,
0x82,0x08,0x22,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,
0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,
0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,
0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,
0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,
0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,
0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,
0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,
0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,
0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x28,
0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,
0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,
0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,
0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,
0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,
0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,
0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xCD,
0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x8C,0x18,0x43,0x20,0x65,0x30,0x87,0x40,0xA9,0x50,0xCB,0x58,0xED,0xC3,0x69,0x0F,0x82,0x58,
0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0x8B,0x00,0x00,0x90,0x08,0x01,0x10,0x23,0x20,0x45,0x30,0x87,0x38,0xA9,0x48,0xCB,0x58,0xED,0x61,
0x0E,0xB3,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0x9B,0x00,0x00,0x8E,0x10,0x22,0x18,0x44,0x28,0x66,0x38,0x88,0x48,
0xAA,0x50,0xEC,0x61,0x0E,0xA5,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xA9,0x00,0x00,0x8E,0x08,0x21,0x18,0x43,0x28,
0x66,0x30,0x88,0x40,0xAA,0x50,0xCC,0x60,0xEE,0x97,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xB7,0x00,0x00,0x90,0x08,
0x01,0x10,0x23,0x20,0x65,0x30,0x87,0x40,0xA9,0x48,0xCB,0x58,0xED,0x61,0x0F,0x87,0x69,0x0F,0x82,0x58,0xED,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,
0x43,0xC7,0x00,0x00,0x88,0x10,0x22,0x20,0x44,0x28,0x66,0x30,0x87,0x89,0x00,0x00,0x82,0x20,0x65,0xE7,0x69,0x0F,0x82,0x18,0x43,0xD7,0x00,0x00,0x8C,0x08,0x21,0x20,
0x65,0x30,0x87,0x40,0xA9,0x50,0xCB,0x58,0xED,0xDD,0x69,0x0F,0x82,0x18,0x43,0xE3,0x00,0x00,0x8E,0x08,0x01,0x10,0x23,0x20,0x65,0x30,0x87,0x40,0xA9,0x48,0xCB,0x58,
0xED,0xCF,0x69,0x0F,0x82,0x18,0x43,0xF3,0x00,0x00,0x8E,0x10,0x23,0x20,0x45,0x30,0x87,0x40,0xA9,0x48,0xCB,0x58,0xED,0x61,0x0F,0xBF,0x69,0x0F,0x82,0x18,0x43,0x01,
0x81,0x00,0x00,0x8E,0x10,0x22,0x20,0x44,0x30,0x67,0x38,0xA9,0x48,0xCB,0x58,0xED,0x61,0x0E,0xB1,0x69,0x0F,0x82,0x18,0x43,0x0F,0x81,0x00,0x00,0x8E,0x10,0x22,0x20,
0x44,0x28,0x66,0x38,0xA8,0x48,0xCB,0x58,0xED,0x61,0x0E,0xA3,0x69,0x0F,0x82,0x18,0x43,0x1D,0x81,0x00,0x00,0x8E,0x10,0x22,0x20,0x44,0x28,0x66,0x38,0x88,0x48,0xCA,
0x58,0xED,0x61,0x0E,0x95,0x69,0x0F,0x82,0x18,0x43,0x2B,0x81,0x00,0x00,0x8E,0x10,0x22,0x18,0x44,0x28,0x66,0x38,0x88,0x48,0xCA,0x50,0xEC,0x61,0x0E,0x87,0x69,0x0F,
0x82,0x18,0x43,0x39,0x81,0x00,0x00,0x86,0x08,0x22,0x18,0x44,0x28,0x66,0x82,0x08,0x21,
};
// clang-format on

static const image_descriptor gfx_win_raw = {
  .compression = image_compression::NQRLE,
  .width = 96,
  .height = 96,
  .byte_count = 2001,
  .image_data = gfx_win_data,
}; // 9.21 compression ratio

image_descriptor* gfx_win = (image_descriptor*)&gfx_win_raw;