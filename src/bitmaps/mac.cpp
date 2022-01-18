#include "bitmap.h"

// clang-format off
static const uint8_t gfx_mac_data[7256] PROGMEM = {
0xE5,0x00,0x00,0x8A,0x10,0x82,0x39,0xC7,0x52,0xAA,0x6B,0x4D,0x5A,0xEB,0x0D,0x81,0x00,0x00,0x8A,0x00,0x20,0x31,0x86,0x63,0x2D,0x8C,0x92,0x9D,0x14,0x85,0xA5,0x55,
0x82,0x6B,0x6D,0x0B,0x81,0x00,0x00,0x8A,0x31,0x86,0x7B,0xCF,0x9D,0x34,0xAD,0xB7,0xAD,0xD8,0x85,0xAD,0xD7,0x84,0xAD,0x97,0x6B,0x4D,0x07,0x81,0x00,0x00,0x88,0x10,
0xA2,0x6B,0x6D,0xA5,0x76,0xB6,0x18,0x87,0xB5,0xF8,0x88,0xB5,0xD8,0xAD,0xD8,0xAD,0x97,0x63,0x0C,0x05,0x81,0x00,0x00,0x8E,0x31,0x86,0x9C,0xF3,0xC6,0x7A,0xCE,0x9A,
0xC6,0x59,0xBE,0x19,0xB6,0x18,0x85,0xB5,0xF8,0x86,0xB5,0xD8,0xA5,0x76,0x52,0xAA,0x03,0x81,0x00,0x00,0x8C,0x4A,0x69,0xBE,0x18,0xDF,0x3C,0xD6,0xFB,0xCE,0x9A,0xC6,
0x7A,0x85,0xBE,0x39,0x82,0xBE,0x18,0x85,0xB5,0xF8,0x84,0x9D,0x55,0x39,0xE7,0x01,0x81,0x00,0x00,0x9C,0x52,0x8A,0xCE,0x9A,0xEF,0x7D,0xDF,0x3C,0xD6,0xDB,0xCE,0xBB,
0xC6,0x7A,0xC6,0x59,0xBE,0x59,0xBE,0x39,0xB6,0x18,0xB5,0xF8,0x94,0xF4,0x21,0x04,0xFF,0x00,0x00,0x9E,0x42,0x28,0xC6,0x59,0xEF,0x9E,0xE7,0x5D,0xDF,0x1C,0xD6,0xDB,
0xCE,0xBB,0xCE,0x9A,0xC6,0x7A,0xC6,0x59,0xBE,0x39,0xB6,0x18,0xB5,0xF8,0x84,0x51,0x00,0x20,0xFD,0x00,0x00,0x8C,0x29,0x25,0xAD,0xB6,0xE7,0x3C,0xEF,0x7D,0xE7,0x3C,
0xDF,0x1C,0x85,0xD6,0xDB,0x8E,0xCE,0xBB,0xCE,0x9A,0xC6,0x7A,0xBE,0x59,0xB6,0x18,0xAD,0xB7,0x52,0x8A,0xFD,0x00,0x00,0x86,0x08,0x41,0x8C,0x92,0xCE,0xBB,0x85,0xE7,
0x5D,0x86,0xDF,0x3C,0xDE,0xFC,0xD6,0xFB,0x85,0xD6,0xDB,0x8C,0xCE,0xBB,0xC6,0x7A,0xBE,0x59,0xB6,0x18,0x9D,0x14,0x20,0xE4,0xFD,0x00,0x00,0x8A,0x52,0xCB,0xBE,0x39,
0xD6,0xFB,0xE7,0x5D,0xE7,0x3C,0x85,0xDF,0x1C,0x90,0xDE,0xFC,0xDE,0xFB,0xD6,0xFB,0xD6,0xBB,0xCE,0x9A,0xBE,0x59,0xB5,0xF8,0x6B,0x6D,0xFD,0x00,0x00,0x8C,0x18,0xC3,
0xA5,0x55,0xC6,0x7A,0xDE,0xFC,0xE7,0x3C,0xDF,0x3C,0x8B,0xDF,0x1C,0x8A,0xD6,0xDB,0xCE,0x9A,0xBE,0x59,0xA5,0x55,0x21,0x24,0xFD,0x00,0x00,0x8A,0x63,0x0C,0xB6,0x18,
0xCE,0x9A,0xDF,0x1C,0xDF,0x3C,0x89,0xDF,0x1C,0x8C,0xE7,0x3C,0xDF,0x1C,0xD6,0xDB,0xCE,0x9A,0xB6,0x18,0x63,0x0C,0xFD,0x00,0x00,0x8A,0x10,0x82,0x9D,0x14,0xBE,0x39,
0xCE,0xBA,0xDE,0xFC,0x89,0xDF,0x1C,0x8E,0xE7,0x3C,0xE7,0x5D,0xDF,0x3C,0xD6,0xDB,0xC6,0x7A,0x94,0xB2,0x10,0x62,0xFD,0x00,0x00,0x8C,0x42,0x08,0xAD,0xD7,0xBE,0x59,
0xCE,0xBA,0xD6,0xFB,0xDE,0xFC,0x85,0xDF,0x1C,0x8E,0xDF,0x3C,0xE7,0x5D,0xEF,0x7D,0xE7,0x3C,0xD6,0xDB,0xAD,0x96,0x29,0x65,0xFF,0x00,0x00,0x8C,0x73,0xAF,0xB6,0x18,
0xC6,0x59,0xCE,0xBA,0xD6,0xDB,0xD6,0xFB,0x85,0xDF,0x1C,0x8C,0xE7,0x5D,0xEF,0x7D,0xEF,0x9E,0xDF,0x3C,0xBE,0x18,0x4A,0x49,0xFF,0x00,0x00,0x9C,0x08,0x41,0x94,0xF4,
0xB6,0x18,0xC6,0x59,0xCE,0x9A,0xD6,0xDB,0xD6,0xFB,0xDF,0x1C,0xDF,0x3C,0xE7,0x7D,0xF7,0xBE,0xE7,0x5D,0xBE,0x18,0x52,0x8A,0x01,0x81,0x00,0x00,0x9A,0x21,0x24,0xA5,
0x55,0xB6,0x18,0xBE,0x59,0xCE,0x9A,0xCE,0xBB,0xD6,0xFB,0xDF,0x1C,0xE7,0x5D,0xE7,0x7D,0xDF,0x3C,0xB5,0xB7,0x4A,0x29,0x03,0x81,0x00,0x00,0x98,0x31,0xA6,0xA5,0x76,
0xB6,0x18,0xBE,0x59,0xC6,0x7A,0xCE,0xBB,0xD6,0xDB,0xD6,0xFB,0xD6,0xDB,0xC6,0x7A,0x94,0xD3,0x29,0x65,0x05,0x81,0x00,0x00,0x8A,0x42,0x08,0xA5,0x96,0xB5,0xF8,0xBE,
0x39,0xBE,0x59,0x85,0xC6,0x59,0x88,0xBE,0x39,0xA5,0x55,0x5A,0xEC,0x10,0x62,0x07,0x81,0x00,0x00,0x86,0x42,0x08,0xA5,0x76,0xAD,0xD8,0x85,0xB5,0xF8,0x88,0xAD,0x96,
0x94,0xF4,0x5A,0xEC,0x18,0xE3,0x0B,0x81,0x00,0x00,0x8E,0x39,0xC7,0x8C,0x51,0x84,0x51,0x73,0xCF,0x5A,0xCB,0x31,0xA6,0x08,0x61,0x51,0x82,0x00,0x00,0x84,0x08,0x41,
0x10,0xA2,0x85,0x18,0xC3,0x84,0x10,0xA2,0x08,0x41,0xC9,0x00,0x00,0x98,0x18,0xE3,0x39,0xE7,0x52,0xAA,0x6B,0x2D,0x73,0xAE,0x84,0x10,0x7B,0xEF,0x73,0xAE,0x63,0x0C,
0x4A,0x49,0x29,0x65,0x08,0x41,0xA7,0x00,0x00,0xA0,0x08,0x21,0x29,0x45,0x4A,0x69,0x6B,0x4D,0x84,0x30,0x94,0xD3,0x9D,0x14,0xA5,0x34,0xA5,0x35,0xA5,0x34,0x9D,0x14,
0x8C,0x71,0x6B,0x4D,0x42,0x28,0x21,0x24,0x00,0x20,0xB9,0x00,0x00,0xA4,0x18,0xC3,0x4A,0x69,0x7B,0xCF,0x94,0xD3,0xAD,0x76,0xBE,0x18,0xC6,0x7A,0xCE,0xBA,0xCE,0xBB,
0xCE,0x9A,0xC6,0x79,0xBD,0xF8,0xAD,0x75,0x94,0xB2,0x84,0x10,0x5A,0xEB,0x31,0x86,0x08,0x21,0x9D,0x00,0x00,0x8C,0x29,0x45,0x5A,0xCB,0x8C,0x51,0xA5,0x35,0xB5,0xD7,
0xC6,0x59,0x93,0xCE,0x9A,0x8A,0xBE,0x39,0xAD,0x76,0x8C,0x51,0x4A,0x69,0x18,0xC3,0xB1,0x00,0x00,0x8E,0x20,0xE4,0x63,0x0C,0x8C,0x51,0xA5,0x55,0xC6,0x79,0xCE,0xBB,
0xD6,0xBB,0x8F,0xD6,0xDB,0x90,0xD6,0xBB,0xCE,0xBB,0xC6,0x7A,0xAD,0x96,0x94,0xB2,0x7B,0xCF,0x4A,0x69,0x18,0xC3,0x93,0x00,0x00,0x8A,0x10,0xA2,0x4A,0x49,0x84,0x30,
0xAD,0x55,0xBE,0x38,0x85,0xCE,0x9A,0x82,0xCE,0xBA,0x91,0xCE,0xBB,0x82,0xCE,0xBA,0x89,0xCE,0x9A,0x88,0xBE,0x18,0x9C,0xF3,0x5A,0xCB,0x18,0xA3,0xA9,0x00,0x00,0x8C,
0x08,0x61,0x52,0xAA,0x84,0x30,0xA5,0x55,0xCE,0x9A,0xCE,0xBB,0x85,0xD6,0xDB,0x85,0xD6,0xFB,0x85,0xDE,0xFC,0x85,0xDF,0x1C,0x85,0xDE,0xFC,0x82,0xD6,0xFB,0x85,0xD6,
0xDB,0x90,0xD6,0xBB,0xCE,0xBB,0xBE,0x39,0xA5,0x55,0x8C,0x51,0x6B,0x6D,0x39,0xE7,0x18,0xA3,0x87,0x00,0x00,0x8C,0x10,0x82,0x39,0xC7,0x6B,0x6D,0xA5,0x34,0xBE,0x18,
0xCE,0x9A,0xA1,0xCE,0xBB,0x82,0xCE,0xBA,0x87,0xCE,0x9A,0x88,0xBE,0x18,0x94,0xB2,0x4A,0x29,0x00,0x20,0xA3,0x00,0x00,0x8A,0x29,0x45,0x7B,0xCF,0x94,0xB2,0xC6,0x39,
0xCE,0xBB,0x85,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,0xFC,0x85,0xDF,0x1C,0x85,0xDF,0x3C,0x85,0xE7,0x3C,0x82,0xDF,0x3C,0x87,0xDF,0x1C,0x84,0xDE,0xFB,0xD6,0xFB,0x85,0xD6,
0xDB,0x96,0xCE,0xBB,0xCE,0x9A,0xB5,0xF7,0xA5,0x34,0x94,0xB2,0x84,0x10,0x73,0xAE,0x84,0x30,0xA5,0x34,0xB5,0xD7,0xCE,0x9A,0x89,0xCE,0xBB,0x85,0xD6,0xBB,0x91,0xD6,
0xDB,0x85,0xD6,0xBB,0x8D,0xCE,0xBB,0x87,0xCE,0x9A,0x86,0xAD,0x96,0x6B,0x6D,0x10,0x82,0x9F,0x00,0x00,0x88,0x42,0x08,0x84,0x10,0xA5,0x55,0xCE,0xBA,0x85,0xD6,0xDB,
0x82,0xDE,0xFB,0x85,0xDF,0x1C,0x84,0xDF,0x3C,0xE7,0x3C,0x87,0xE7,0x5D,0x85,0xE7,0x7D,0x85,0xE7,0x5D,0x84,0xE7,0x3C,0xDF,0x3C,0x85,0xDF,0x1C,0x84,0xDE,0xFC,0xD6,
0xFB,0x87,0xD6,0xDB,0x85,0xCE,0xBB,0x85,0xCE,0x9A,0x89,0xCE,0xBB,0x82,0xD6,0xBB,0xA3,0xD6,0xDB,0x82,0xD6,0xBB,0x8B,0xCE,0xBB,0x85,0xCE,0x9A,0x86,0xBE,0x18,0x7B,
0xEF,0x20,0xE4,0x9B,0x00,0x00,0x8C,0x52,0x8A,0x84,0x30,0xB5,0xD7,0xCE,0xBB,0xD6,0xDB,0xD6,0xFB,0x85,0xDF,0x1C,0x84,0xDF,0x3C,0xE7,0x3C,0x85,0xE7,0x5D,0x85,0xEF,
0x7D,0x87,0xEF,0x9E,0x86,0xEF,0x9D,0xEF,0x7D,0xE7,0x7D,0x85,0xE7,0x5D,0x84,0xE7,0x3C,0xDF,0x3C,0x85,0xDF,0x1C,0x84,0xDE,0xFC,0xD6,0xFB,0x93,0xD6,0xDB,0x8D,0xD6,
0xFB,0x8F,0xDE,0xFB,0x87,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,0xBB,0x87,0xCE,0xBB,0x85,0xCE,0x9A,0x86,0xBD,0xF8,0x84,0x10,0x21,0x04,0x97,0x00,0x00,0x94,0x52,0x8A,
0x8C,0x51,0xBE,0x18,0xD6,0xBB,0xD6,0xDB,0xDE,0xFB,0xDF,0x1C,0xDF,0x3C,0xE7,0x3C,0xE7,0x5D,0x85,0xEF,0x7D,0x84,0xEF,0x9E,0xF7,0x9E,0x85,0xF7,0xBE,0x82,0xF7,0xDE,
0x85,0xF7,0xBE,0x92,0xF7,0x9E,0xEF,0x9E,0xEF,0x9D,0xEF,0x7D,0xE7,0x7D,0xE7,0x5D,0xE7,0x3D,0xE7,0x3C,0xDF,0x3C,0x85,0xDF,0x1C,0x85,0xDE,0xFC,0x82,0xDE,0xFB,0x85,
0xD6,0xFB,0x82,0xDE,0xFB,0x87,0xDE,0xFC,0x95,0xDF,0x1C,0x85,0xDE,0xFC,0x87,0xD6,0xFB,0x8B,0xD6,0xDB,0x82,0xD6,0xBB,0x87,0xCE,0xBB,0x8A,0xCE,0xBA,0xCE,0x9A,0xAD,
0x96,0x7B,0xCF,0x18,0xA3,0x93,0x00,0x00,0x90,0x42,0x08,0x84,0x30,0xBE,0x18,0xD6,0xBB,0xD6,0xDB,0xDE,0xFC,0xDF,0x1C,0xDF,0x3C,0x85,0xE7,0x5D,0x85,0xEF,0x7D,0x84,
0xEF,0x9E,0xF7,0x9E,0x85,0xF7,0xBE,0x84,0xF7,0xDE,0xFF,0xDF,0x85,0xF7,0xDF,0x82,0xF7,0xDE,0x87,0xF7,0xBE,0x88,0xEF,0x9E,0xEF,0x9D,0xEF,0x7D,0xE7,0x7D,0x85,0xE7,
0x5D,0x82,0xE7,0x3C,0x85,0xDF,0x3C,0x8D,0xDF,0x1C,0x87,0xDF,0x3C,0x85,0xE7,0x3C,0x85,0xDF,0x3C,0x87,0xDF,0x1C,0x85,0xDE,0xFC,0x82,0xDE,0xFB,0x85,0xD6,0xFB,0x8B,
0xD6,0xDB,0x82,0xD6,0xBB,0x89,0xCE,0xBB,0x87,0xCE,0x9A,0x86,0x8C,0x92,0x73,0x8E,0x08,0x41,0x8F,0x00,0x00,0x92,0x21,0x24,0x84,0x10,0xB5,0xD7,0xCE,0xBB,0xD6,0xDB,
0xDE,0xFB,0xDF,0x1C,0xDF,0x3C,0xE7,0x3D,0x85,0xE7,0x5D,0x85,0xEF,0x7D,0x85,0xEF,0x9E,0x82,0xF7,0x9E,0x97,0xF7,0xBE,0x82,0xF7,0x9E,0x85,0xEF,0x9E,0x85,0xEF,0x7D,
0x95,0xE7,0x5D,0x82,0xE7,0x3D,0x85,0xE7,0x3C,0x82,0xDF,0x3C,0x89,0xDF,0x1C,0x84,0xDE,0xFC,0xDE,0xFB,0x85,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,0xBB,0x8B,0xCE,0xBB,
0x85,0xCE,0x9A,0x8A,0xC6,0x59,0x94,0xD3,0x84,0x10,0x6B,0x4D,0x10,0x82,0x8D,0x00,0x00,0x8C,0x08,0x41,0x73,0xAE,0xA5,0x55,0xCE,0xBB,0xD6,0xDB,0xD6,0xFB,0x85,0xDF,
0x1C,0x84,0xDF,0x3C,0xE7,0x3C,0x85,0xE7,0x5D,0x82,0xE7,0x7D,0x85,0xEF,0x7D,0x85,0xEF,0x9E,0x82,0xF7,0x9E,0x87,0xF7,0xBE,0x82,0xF7,0x9E,0x91,0xEF,0x9E,0x85,0xEF,
0x9D,0x8B,0xEF,0x7D,0x8B,0xE7,0x5D,0x82,0xE7,0x3D,0x85,0xE7,0x3C,0x82,0xDF,0x3C,0x89,0xDF,0x1C,0x84,0xDE,0xFC,0xDE,0xFB,0x85,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,
0xBB,0x89,0xCE,0xBB,0x87,0xCE,0x9A,0x8A,0xB5,0xD7,0x8C,0x51,0x84,0x10,0x4A,0x49,0x00,0x20,0x8F,0x00,0x00,0x8C,0x52,0xAA,0x94,0x92,0xCE,0x9A,0xD6,0xDB,0xD6,0xFB,
0xDE,0xFC,0x85,0xDF,0x1C,0x84,0xDF,0x3C,0xE7,0x3C,0x87,0xE7,0x5D,0x85,0xEF,0x7D,0x82,0xEF,0x9D,0x91,0xEF,0x9E,0x93,0xEF,0x7D,0x85,0xE7,0x7D,0x8B,0xE7,0x5D,0x82,
0xE7,0x3D,0x85,0xE7,0x3C,0x85,0xDF,0x3C,0x89,0xDF,0x1C,0x84,0xDE,0xFC,0xDE,0xFB,0x85,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,0xBB,0x89,0xCE,0xBB,0x85,0xCE,0x9A,0x84,
0xC6,0x7A,0x9D,0x14,0x85,0x84,0x10,0x82,0x31,0xA6,0x91,0x00,0x00,0x8E,0x18,0xE3,0x84,0x10,0xBE,0x18,0xCE,0xBB,0xD6,0xDB,0xD6,0xFB,0xDE,0xFC,0x85,0xDF,0x1C,0x86,
0xDF,0x3C,0xE7,0x3C,0xE7,0x3D,0x85,0xE7,0x5D,0x82,0xE7,0x7D,0x87,0xEF,0x7D,0x85,0xEF,0x9E,0x85,0xEF,0x9D,0x8F,0xEF,0x7D,0x85,0xE7,0x7D,0x91,0xE7,0x5D,0x82,0xE7,
0x3D,0x85,0xE7,0x3C,0x87,0xDF,0x3C,0x89,0xDF,0x1C,0x84,0xDE,0xFC,0xDE,0xFB,0x85,0xD6,0xFB,0x87,0xD6,0xDB,0x85,0xD6,0xBB,0x89,0xCE,0xBB,0x85,0xCE,0x9A,0x84,0xBE,
0x39,0x94,0x92,0x85,0x84,0x10,0x82,0x29,0x65,0x93,0x00,0x00,0x86,0x63,0x0C,0x9C,0xF4,0xCE,0xBB,0x85,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,0xFC,0x85,0xDF,0x1C,0x82,0xDF,
0x3C,0x85,0xE7,0x3C,0x87,0xE7,0x5D,0x82,0xE7,0x7D,0x93,0xEF,0x7D,0x99,0xE7,0x5D,0x89,0xE7,0x3C,0x85,0xDF,0x3C,0x8B,0xDF,0x1C,0x86,0xDE,0xFC,0xDE,0xFB,0xD6,0xFB,
0x89,0xD6,0xDB,0x82,0xD6,0xBB,0x89,0xCE,0xBB,0x87,0xCE,0x9A,0x8A,0xB5,0xF8,0x8C,0x92,0x84,0x30,0x84,0x10,0x31,0x86,0x93,0x00,0x00,0x88,0x18,0xC3,0x84,0x30,0xBE,
0x39,0xCE,0xBB,0x85,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,0xFC,0x87,0xDF,0x1C,0x84,0xDF,0x3C,0xE7,0x3C,0x89,0xE7,0x5D,0x82,0xE7,0x7D,0x89,0xEF,0x7D,0x82,0xE7,0x7D,0x93,
0xE7,0x5D,0x82,0xE7,0x3D,0x8D,0xE7,0x3C,0x87,0xDF,0x3C,0x8D,0xDF,0x1C,0x82,0xDE,0xFC,0x85,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,0xBB,0x89,0xCE,0xBB,0x85,0xCE,0x9A,
0x8C,0xBE,0x59,0xAD,0xB7,0x94,0xD3,0x84,0x30,0x84,0x10,0x4A,0x49,0x95,0x00,0x00,0x88,0x52,0x8A,0x94,0xD3,0xCE,0xBA,0xCE,0xBB,0x85,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,
0xFC,0x87,0xDF,0x1C,0x86,0xDF,0x3C,0xE7,0x3C,0xE7,0x3D,0x89,0xE7,0x5D,0x85,0xE7,0x7D,0x8F,0xE7,0x5D,0x82,0xE7,0x3D,0x8B,0xE7,0x3C,0x8D,0xDF,0x3C,0x91,0xDF,0x1C,
0x82,0xDE,0xFC,0x85,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,0xBB,0x87,0xCE,0xBB,0x85,0xCE,0x9A,0x8E,0xC6,0x9A,0xB5,0xF8,0xA5,0x97,0x9D,0x55,0x84,0x30,0x84,0x10,0x63,
0x2C,0x95,0x00,0x00,0x8A,0x08,0x21,0x7B,0xEF,0xB5,0xB7,0xCE,0xBB,0xD6,0xBB,0x85,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,0xFC,0x87,0xDF,0x1C,0x85,0xDF,0x3C,0x84,0xE7,0x3C,
0xE7,0x3D,0x91,0xE7,0x5D,0x85,0xE7,0x3D,0x89,0xE7,0x3C,0x87,0xDF,0x3C,0x9B,0xDF,0x1C,0x85,0xDE,0xFC,0x85,0xD6,0xFB,0x89,0xD6,0xDB,0x89,0xCE,0xBB,0x85,0xCE,0x9A,
0x84,0xBE,0x39,0xAD,0xB7,0x85,0xA5,0x97,0x88,0x8C,0x71,0x84,0x30,0x84,0x10,0x18,0xA3,0x95,0x00,0x00,0x8A,0x29,0x65,0x84,0x30,0xC6,0x7A,0xCE,0xBB,0xD6,0xBB,0x85,
0xD6,0xDB,0x84,0xD6,0xFB,0xDE,0xFC,0x87,0xDF,0x1C,0x85,0xDF,0x3C,0x85,0xE7,0x3C,0x82,0xE7,0x3D,0x8B,0xE7,0x5D,0x82,0xE7,0x3D,0x87,0xE7,0x3C,0x87,0xDF,0x3C,0x99,
0xDF,0x1C,0x89,0xDE,0xFC,0x82,0xDE,0xFB,0x87,0xD6,0xFB,0x87,0xD6,0xDB,0x82,0xD6,0xBB,0x87,0xCE,0xBB,0x85,0xCE,0x9A,0x84,0xC6,0x7A,0xB5,0xF8,0x87,0xA5,0x97,0x82,
0x9D,0x35,0x85,0x84,0x30,0x82,0x4A,0x49,0x97,0x00,0x00,0x88,0x52,0xAA,0x94,0xD3,0xCE,0x9A,0xCE,0xBB,0x87,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,0xFC,0x89,0xDF,0x1C,0x85,
0xDF,0x3C,0x85,0xE7,0x3C,0x87,0xE7,0x3D,0x87,0xE7,0x3C,0x85,0xDF,0x3C,0x95,0xDF,0x1C,0x8D,0xDE,0xFC,0x85,0xDE,0xFB,0x89,0xD6,0xFB,0x89,0xD6,0xDB,0x82,0xD6,0xBB,
0x87,0xCE,0xBB,0x85,0xCE,0x9A,0x84,0xBE,0x19,0xAD,0xB7,0x89,0xA5,0x97,0x88,0x8C,0x92,0x84,0x30,0x7B,0xEF,0x08,0x61,0x97,0x00,0x00,0x8A,0x73,0xAE,0xA5,0x55,0xCE,
0xBA,0xCE,0xBB,0xD6,0xBB,0x85,0xD6,0xDB,0x86,0xD6,0xFB,0xDE,0xFB,0xDE,0xFC,0x89,0xDF,0x1C,0x85,0xDF,0x3C,0x89,0xE7,0x3C,0x85,0xDF,0x3C,0x95,0xDF,0x1C,0x89,0xDE,
0xFC,0x85,0xDE,0xFB,0x8F,0xD6,0xFB,0x8B,0xD6,0xDB,0x87,0xCE,0xBB,0x85,0xCE,0x9A,0x88,0xC6,0x59,0xAD,0xD7,0xAD,0xB7,0xA5,0xB7,0x87,0xA5,0x97,0x82,0xA5,0x76,0x85,
0x84,0x30,0x82,0x4A,0x69,0x97,0x00,0x00,0x8A,0x10,0x82,0x84,0x10,0xB5,0xD7,0xCE,0xBA,0xCE,0xBB,0x87,0xD6,0xDB,0x85,0xD6,0xFB,0x82,0xDE,0xFC,0x8B,0xDF,0x1C,0x89,
0xDF,0x3C,0x91,0xDF,0x1C,0x89,0xDE,0xFC,0x85,0xDE,0xFB,0x91,0xD6,0xFB,0x8F,0xD6,0xDB,0x82,0xD6,0xBB,0x87,0xCE,0xBB,0x86,0xCE,0x9A,0xC6,0x7A,0xB5,0xF8,0x87,0xAD,
0xB7,0x82,0xA5,0xB7,0x87,0xA5,0x97,0x82,0x94,0xF4,0x85,0x84,0x30,0x82,0x18,0xE3,0x97,0x00,0x00,0x86,0x29,0x45,0x84,0x10,0xC6,0x59,0x85,0xCE,0xBB,0x87,0xD6,0xDB,
0x85,0xD6,0xFB,0x84,0xDE,0xFB,0xDE,0xFC,0x99,0xDF,0x1C,0x85,0xDE,0xFC,0x85,0xDE,0xFB,0x95,0xD6,0xFB,0x95,0xD6,0xDB,0x82,0xD6,0xBB,0x85,0xCE,0xBB,0x85,0xCE,0x9A,
0x82,0xBE,0x19,0x8B,0xAD,0xB7,0x82,0xA5,0xB7,0x87,0xA5,0x97,0x86,0x94,0xB2,0x84,0x30,0x73,0xAE,0x99,0x00,0x00,0x86,0x42,0x08,0x84,0x30,0xCE,0x9A,0x85,0xCE,0xBB,
0x89,0xD6,0xDB,0x86,0xD6,0xFB,0xDE,0xFB,0xDE,0xFC,0x91,0xDF,0x1C,0x82,0xDE,0xFC,0x85,0xDE,0xFB,0x8B,0xD6,0xFB,0xA3,0xD6,0xDB,0x85,0xD6,0xBB,0x85,0xCE,0xBB,0x86,
0xCE,0xBA,0xCE,0x9A,0xBE,0x39,0x85,0xAD,0xD7,0x8B,0xAD,0xB7,0x82,0xA5,0xB7,0x87,0xA5,0x97,0x86,0x8C,0x71,0x84,0x30,0x52,0xAA,0x99,0x00,0x00,0x86,0x52,0x8A,0x8C,
0x71,0xCE,0x9A,0x85,0xCE,0xBB,0x89,0xD6,0xDB,0x85,0xD6,0xFB,0x84,0xDE,0xFB,0xDE,0xFC,0x85,0xDF,0x1C,0x9C,0xD6,0xDB,0xC6,0x7A,0xBE,0x39,0xB6,0x18,0xB5,0xF8,0xAD,
0xD8,0xB5,0xD8,0xB5,0xF8,0xB6,0x18,0xBE,0x19,0xBE,0x59,0xC6,0x7A,0xCE,0x9A,0xCE,0xBB,0x99,0xD6,0xDB,0x89,0xD6,0xBB,0x87,0xCE,0xBB,0x86,0xCE,0x9A,0xBE,0x39,0xB5,
0xF8,0x85,0xAD,0xD7,0x8D,0xAD,0xB7,0x82,0xA5,0xB7,0x87,0xA5,0x97,0x85,0x84,0x30,0x82,0x39,0xC7,0x99,0x00,0x00,0x8C,0x63,0x0C,0x94,0x92,0xCE,0x9A,0xCE,0xBA,0xCE,
0xBB,0xD6,0xBB,0x87,0xD6,0xDB,0x87,0xD6,0xFB,0x86,0xDE,0xFB,0xCE,0x9A,0xB6,0x18,0x8D,0xAD,0xD7,0x82,0xAD,0xD8,0x8D,0xB5,0xF8,0x85,0xB6,0x18,0x86,0xBE,0x39,0xC6,
0x59,0xC6,0x9A,0x9B,0xCE,0xBB,0x88,0xCE,0x9A,0xBE,0x39,0xB5,0xF8,0xAD,0xD8,0x89,0xAD,0xD7,0x8B,0xAD,0xB7,0x82,0xA5,0xB7,0x85,0xA5,0x97,0x82,0xA5,0x96,0x85,0x84,
0x30,0x82,0x21,0x24,0x99,0x00,0x00,0x8C,0x6B,0x4D,0x94,0xB2,0xCE,0x9A,0xCE,0xBA,0xCE,0xBB,0xD6,0xBB,0x89,0xD6,0xDB,0x88,0xD6,0xFB,0xCE,0xBB,0xB6,0x18,0xAD,0xB7,
0x8F,0xAD,0xD7,0x82,0xB5,0xD8,0x8D,0xB5,0xF8,0x8D,0xB6,0x18,0x88,0xBE,0x39,0xBE,0x59,0xC6,0x59,0xC6,0x7A,0x85,0xCE,0x9A,0x85,0xCE,0xBA,0x85,0xCE,0x9A,0x84,0xC6,
0x59,0xBE,0x39,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x8B,0xAD,0xD7,0x89,0xAD,0xB7,0x82,0xA5,0xB7,0x85,0xA5,0x97,0x82,0xA5,0x96,0x85,0x84,0x30,0x82,0x18,0xA3,0x99,0x00,
0x00,0x8C,0x73,0x8E,0x94,0xB2,0xCE,0x9A,0xCE,0xBA,0xCE,0xBB,0xD6,0xBB,0x89,0xD6,0xDB,0x84,0xC6,0x7A,0xAD,0xD7,0x85,0xAD,0xB7,0x8F,0xAD,0xD7,0x82,0xB5,0xD8,0x8B,
0xB5,0xF8,0x91,0xB6,0x18,0x87,0xBE,0x18,0x8B,0xB6,0x18,0x8D,0xB5,0xF8,0x84,0xB5,0xD8,0xAD,0xD8,0x89,0xAD,0xD7,0x89,0xAD,0xB7,0x82,0xA5,0xB7,0x85,0xA5,0x97,0x82,
0xA5,0x96,0x85,0x84,0x30,0x82,0x10,0x82,0x99,0x00,0x00,0x88,0x73,0xAE,0x94,0xB2,0xCE,0x9A,0xCE,0xBA,0x85,0xCE,0xBB,0x87,0xD6,0xDB,0x82,0xC6,0x79,0x87,0xAD,0xB7,
0x91,0xAD,0xD7,0x8B,0xB5,0xF8,0x8F,0xB6,0x18,0x8F,0xBE,0x18,0x87,0xB6,0x18,0x8F,0xB5,0xF8,0x84,0xB5,0xD8,0xAD,0xD8,0x87,0xAD,0xD7,0x89,0xAD,0xB7,0x82,0xA5,0xB7,
0x87,0xA5,0x97,0x86,0x84,0x31,0x84,0x30,0x10,0x82,0x99,0x00,0x00,0x88,0x73,0xAE,0x94,0xB2,0xCE,0x9A,0xCE,0xBA,0x85,0xCE,0xBB,0x85,0xD6,0xBB,0x82,0xBE,0x59,0x89,
0xAD,0xB7,0x8F,0xAD,0xD7,0x82,0xB5,0xD7,0x8B,0xB5,0xF8,0x8D,0xB6,0x18,0x8B,0xBE,0x18,0x82,0xBE,0x39,0x85,0xBE,0x18,0x8B,0xB6,0x18,0x8D,0xB5,0xF8,0x82,0xB5,0xD8,
0x89,0xAD,0xD7,0x89,0xAD,0xB7,0x82,0xA5,0xB7,0x85,0xA5,0x97,0x86,0x8C,0x71,0x84,0x30,0x10,0xA2,0x99,0x00,0x00,0x84,0x73,0xAE,0x94,0x92,0x85,0xCE,0x9A,0x87,0xCE,
0xBB,0x82,0xBE,0x19,0x8B,0xAD,0xB7,0x8F,0xAD,0xD7,0x82,0xB5,0xD8,0x8B,0xB5,0xF8,0x8B,0xB6,0x18,0x89,0xBE,0x18,0x87,0xBE,0x39,0x82,0xBE,0x19,0x87,0xBE,0x18,0x87,
0xB6,0x18,0x8D,0xB5,0xF8,0x85,0xB5,0xD8,0x87,0xAD,0xD7,0x8B,0xAD,0xB7,0x85,0xA5,0x97,0x86,0x94,0xB2,0x84,0x30,0x20,0xE4,0x99,0x00,0x00,0x84,0x73,0x8E,0x8C,0x71,
0x85,0xCE,0x9A,0x86,0xCE,0xBB,0xCE,0x9A,0xB5,0xF8,0x8B,0xAD,0xB7,0x91,0xAD,0xD7,0x82,0xB5,0xD8,0x89,0xB5,0xF8,0x8B,0xB6,0x18,0x85,0xBE,0x18,0x91,0xBE,0x39,0x82,
0xBE,0x19,0x85,0xBE,0x18,0x87,0xB6,0x18,0x8D,0xB5,0xF8,0x82,0xB5,0xD8,0x89,0xAD,0xD7,0x89,0xAD,0xB7,0x85,0xA5,0x97,0x86,0x94,0xF4,0x84,0x30,0x29,0x65,0x99,0x00,
0x00,0x84,0x6B,0x4D,0x84,0x30,0x85,0xCE,0x9A,0x84,0xC6,0x7A,0xAD,0xD7,0x8D,0xAD,0xB7,0x8F,0xAD,0xD7,0x84,0xAD,0xD8,0xB5,0xD8,0x89,0xB5,0xF8,0x89,0xB6,0x18,0x85,
0xBE,0x18,0x82,0xBE,0x19,0x95,0xBE,0x39,0x82,0xBE,0x19,0x85,0xBE,0x18,0x87,0xB6,0x18,0x8B,0xB5,0xF8,0x84,0xB5,0xD8,0xAD,0xD8,0x87,0xAD,0xD7,0x87,0xAD,0xB7,0x85,
0xA5,0x97,0x86,0x9D,0x55,0x84,0x30,0x42,0x28,0x99,0x00,0x00,0x8C,0x5A,0xEB,0x84,0x30,0xC6,0x7A,0xBE,0x39,0xAD,0xB7,0xA5,0x97,0x8D,0xAD,0xB7,0x8F,0xAD,0xD7,0x85,
0xB5,0xD8,0x87,0xB5,0xF8,0x89,0xB6,0x18,0x87,0xBE,0x18,0x9B,0xBE,0x39,0x84,0xBE,0x19,0xBE,0x18,0x87,0xB6,0x18,0x8B,0xB5,0xF8,0x82,0xB5,0xD8,0x87,0xAD,0xD7,0x89,
0xAD,0xB7,0x85,0xA5,0x97,0x84,0x8C,0x51,0x63,0x0C,0x99,0x00,0x00,0x86,0x52,0x8A,0x84,0x30,0xA5,0x76,0x87,0xA5,0x97,0x82,0xA5,0xB7,0x8D,0xAD,0xB7,0x8B,0xAD,0xD7,
0x84,0xAD,0xD8,0xB5,0xD8,0x8B,0xB5,0xF8,0x87,0xB6,0x18,0x85,0xBE,0x18,0x82,0xBE,0x19,0x8D,0xBE,0x39,0x85,0xBE,0x59,0x84,0xC6,0x59,0xBE,0x59,0x8B,0xBE,0x39,0x85,
0xBE,0x18,0x87,0xB6,0x18,0x89,0xB5,0xF8,0x82,0xB5,0xD8,0x87,0xAD,0xD7,0x87,0xAD,0xB7,0x8A,0xA5,0xB7,0xA5,0x97,0x94,0xD3,0x7B,0xEF,0x08,0x21,0x97,0x00,0x00,0x86,
0x42,0x08,0x84,0x30,0x9D,0x34,0x87,0xA5,0x97,0x82,0xA5,0xB7,0x8D,0xAD,0xB7,0x8B,0xAD,0xD7,0x85,0xB5,0xD8,0x89,0xB5,0xF8,0x89,0xB6,0x18,0x84,0xBE,0x18,0xBE,0x19,
0x8D,0xBE,0x39,0x85,0xBE,0x59,0x8B,0xC6,0x59,0x8B,0xBE,0x39,0x84,0xBE,0x19,0xBE,0x18,0x85,0xB6,0x18,0x89,0xB5,0xF8,0x84,0xB5,0xD8,0xAD,0xD8,0x85,0xAD,0xD7,0x87,
0xAD,0xB7,0x88,0xA5,0x97,0x9D,0x55,0x84,0x30,0x29,0x65,0x97,0x00,0x00,0x86,0x31,0x86,0x84,0x10,0x94,0xF3,0x87,0xA5,0x97,0x82,0xA5,0xB7,0x8B,0xAD,0xB7,0x8D,0xAD,
0xD7,0x82,0xAD,0xD8,0x8B,0xB5,0xF8,0x87,0xB6,0x18,0x85,0xBE,0x18,0x8F,0xBE,0x39,0x82,0xBE,0x59,0x8F,0xC6,0x59,0x85,0xBE,0x59,0x89,0xBE,0x39,0x84,0xBE,0x19,0xBE,
0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x87,0xAD,0xD7,0x85,0xAD,0xB7,0x88,0xA5,0xB7,0xA5,0x97,0x8C,0x92,0x62,0xEC,0x97,0x00,0x00,0x86,0x18,0xC3,0x84,
0x10,0x94,0xB2,0x85,0xA5,0x97,0x85,0xA5,0xB7,0x8B,0xAD,0xB7,0x8D,0xAD,0xD7,0x84,0xAD,0xD8,0xB5,0xD8,0x89,0xB5,0xF8,0x87,0xB6,0x18,0x85,0xBE,0x18,0x8D,0xBE,0x39,
0x85,0xBE,0x59,0x87,0xC6,0x59,0x85,0xC6,0x7A,0x8B,0xC6,0x59,0x82,0xBE,0x59,0x89,0xBE,0x39,0x84,0xBE,0x19,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,
0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x88,0xA5,0xB7,0x9D,0x55,0x84,0x30,0x18,0xC3,0x95,0x00,0x00,0x86,0x08,0x21,0x84,0x10,0x8C,0x51,0x85,0xA5,0x97,0x85,0xA5,0xB7,0x8B,
0xAD,0xB7,0x8D,0xAD,0xD7,0x85,0xB5,0xD8,0x87,0xB5,0xF8,0x89,0xB6,0x18,0x84,0xBE,0x18,0xBE,0x19,0x8D,0xBE,0x39,0x82,0xBE,0x59,0x87,0xC6,0x59,0x89,0xC6,0x7A,0x85,
0xC6,0x79,0x89,0xC6,0x59,0x82,0xBE,0x59,0x89,0xBE,0x39,0x85,0xBE,0x18,0x85,0xB6,0x18,0x85,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x86,0xA5,0x97,
0x94,0xB3,0x5A,0xEB,0x97,0x00,0x00,0x86,0x6B,0x6D,0x84,0x30,0xA5,0x76,0x85,0xA5,0x97,0x85,0xA5,0xB7,0x8B,0xAD,0xB7,0x89,0xAD,0xD7,0x84,0xAD,0xD8,0xB5,0xD8,0x8B,
0xB5,0xF8,0x85,0xB6,0x18,0x85,0xBE,0x18,0x8D,0xBE,0x39,0x82,0xBE,0x59,0x89,0xC6,0x59,0x82,0xC6,0x79,0x85,0xC6,0x7A,0x82,0xCE,0x7A,0x87,0xC6,0x7A,0x85,0xC6,0x79,
0x87,0xC6,0x59,0x82,0xBE,0x59,0x89,0xBE,0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x86,0xA5,0x76,0x8C,0x51,0x29,0x45,0x95,
0x00,0x00,0x86,0x52,0x8A,0x84,0x30,0x9D,0x35,0x85,0xA5,0x97,0x85,0xA5,0xB7,0x8B,0xAD,0xB7,0x8B,0xAD,0xD7,0x82,0xB5,0xD8,0x8B,0xB5,0xF8,0x85,0xB6,0x18,0x85,0xBE,
0x18,0x8D,0xBE,0x39,0x82,0xBE,0x59,0x87,0xC6,0x59,0x82,0xC6,0x79,0x87,0xC6,0x7A,0x85,0xCE,0x9A,0x89,0xC6,0x7A,0x82,0xC6,0x79,0x89,0xC6,0x59,0x82,0xBE,0x59,0x89,
0xBE,0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x85,0xB5,0xF8,0x84,0xB5,0xD8,0xAD,0xD7,0x85,0xAD,0xB7,0x86,0x9D,0x55,0x7B,0xCF,0x08,0x61,0x93,0x00,0x00,0x86,0x31,0x86,
0x84,0x10,0x94,0xD3,0x85,0xA5,0x97,0x85,0xA5,0xB7,0x8B,0xAD,0xB7,0x8B,0xAD,0xD7,0x82,0xB5,0xD8,0x8B,0xB5,0xF8,0x85,0xB6,0x18,0x84,0xBE,0x18,0xBE,0x19,0x8B,0xBE,
0x39,0x82,0xBE,0x59,0x89,0xC6,0x59,0x82,0xC6,0x79,0x85,0xC6,0x7A,0x8D,0xCE,0x9A,0x87,0xC6,0x7A,0x82,0xC6,0x79,0x87,0xC6,0x59,0x82,0xBE,0x59,0x89,0xBE,0x39,0x82,
0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xAD,0xD7,0x85,0xAD,0xB7,0x86,0x9D,0x14,0x63,0x0C,0x00,0x20,0x91,0x00,0x00,0x86,0x10,0x82,0x84,0x10,0x8C,0x71,0x85,
0xA5,0x97,0x85,0xA5,0xB7,0x8B,0xAD,0xB7,0x89,0xAD,0xD7,0x84,0xAD,0xD8,0xB5,0xD8,0x8B,0xB5,0xF8,0x85,0xB6,0x18,0x85,0xBE,0x18,0x8B,0xBE,0x39,0x82,0xBE,0x59,0x89,
0xC6,0x59,0x87,0xC6,0x7A,0x8F,0xCE,0x9A,0x87,0xC6,0x7A,0x82,0xC6,0x79,0x87,0xC6,0x59,0x82,0xBE,0x59,0x89,0xBE,0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,
0x8A,0xB5,0xD8,0xAD,0xD7,0xAD,0xB7,0x9D,0x14,0x52,0xAA,0x93,0x00,0x00,0x86,0x6B,0x6D,0x84,0x30,0xA5,0x76,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x8B,0xAD,0xB7,0x89,0xAD,
0xD7,0x85,0xAD,0xD8,0x8B,0xB5,0xF8,0x85,0xB6,0x18,0x85,0xBE,0x18,0x8B,0xBE,0x39,0x82,0xBE,0x59,0x87,0xC6,0x59,0x82,0xC6,0x79,0x85,0xC6,0x7A,0x87,0xCE,0x9A,0x85,
0xCE,0xBA,0x89,0xCE,0x9A,0x89,0xC6,0x7A,0x87,0xC6,0x59,0x82,0xBE,0x59,0x89,0xBE,0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x8A,0xB5,0xD8,0xAD,0xD7,0xAD,
0xB7,0x9D,0x34,0x5A,0xAB,0x91,0x00,0x00,0x86,0x4A,0x49,0x84,0x30,0x94,0xF4,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x8B,0xAD,0xB7,0x8B,0xAD,0xD7,0x85,0xB5,0xD8,0x89,0xB5,
0xF8,0x85,0xB6,0x18,0x85,0xBE,0x18,0x8B,0xBE,0x39,0x82,0xBE,0x59,0x87,0xC6,0x59,0x87,0xC6,0x7A,0x85,0xCE,0x9A,0x85,0xCE,0xBA,0x82,0xCE,0xBB,0x85,0xCE,0xBA,0x89,
0xCE,0x9A,0x87,0xC6,0x7A,0x87,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x82,0xBE,0x18,0x87,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xAD,0xD8,0x85,0xAD,0xD7,0x86,0xA5,0x56,
0x6B,0x4D,0x08,0x41,0x8D,0x00,0x00,0x86,0x21,0x04,0x84,0x10,0x8C,0x72,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x8D,0xAD,0xB7,0x89,0xAD,0xD7,0x85,0xB5,0xD8,0x8B,0xB5,0xF8,
0x85,0xB6,0x18,0x82,0xBE,0x18,0x89,0xBE,0x39,0x85,0xBE,0x59,0x85,0xC6,0x59,0x82,0xC6,0x79,0x85,0xC6,0x7A,0x87,0xCE,0x9A,0x8A,0xCE,0xBA,0xCE,0xBB,0xD6,0xBB,0xCE,
0xBB,0xCE,0xBA,0x89,0xCE,0x9A,0x87,0xC6,0x7A,0x82,0xC6,0x79,0x85,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x84,0xBE,0x19,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,
0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x88,0xAD,0xB7,0xA5,0x97,0x84,0x51,0x21,0x04,0x8D,0x00,0x00,0x86,0x7B,0xCF,0x84,0x30,0xA5,0x56,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x8B,
0xAD,0xB7,0x8B,0xAD,0xD7,0x82,0xB5,0xD8,0x8B,0xB5,0xF8,0x82,0xB6,0x18,0x85,0xBE,0x18,0x89,0xBE,0x39,0x85,0xBE,0x59,0x85,0xC6,0x59,0x84,0xC6,0x79,0xC6,0x7A,0x87,
0xCE,0x9A,0x8C,0xCE,0xBA,0xCE,0xBB,0xD6,0xBB,0xD6,0xDB,0xD6,0xBB,0xCE,0xBB,0x85,0xCE,0xBA,0x87,0xCE,0x9A,0x87,0xC6,0x7A,0x87,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,
0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x87,0xAD,0xB7,0x86,0x9D,0x55,0x5A,0xEB,0x08,0x61,0x89,0x00,0x00,0x86,0x4A,0x69,
0x84,0x30,0x94,0xD3,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x8D,0xAD,0xB7,0x87,0xAD,0xD7,0x84,0xAD,0xD8,0xB5,0xD8,0x8B,0xB5,0xF8,0x85,0xB6,0x18,0x82,0xBE,0x18,0x89,0xBE,
0x39,0x82,0xBE,0x59,0x85,0xC6,0x59,0x82,0xC6,0x79,0x85,0xC6,0x7A,0x85,0xCE,0x9A,0x86,0xCE,0xBA,0xCE,0xBB,0xD6,0xBB,0x87,0xD6,0xDB,0x86,0xD6,0xBB,0xCE,0xBB,0xCE,
0xBA,0x87,0xCE,0x9A,0x82,0xCE,0x7A,0x85,0xC6,0x7A,0x82,0xC6,0x79,0x85,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,
0xB5,0xD8,0x85,0xAD,0xD7,0x87,0xAD,0xB7,0x88,0xA5,0xB7,0xA5,0x97,0x8C,0x51,0x42,0x28,0x87,0x00,0x00,0x88,0x18,0xE3,0x84,0x10,0x8C,0x51,0xA5,0x96,0x85,0xA5,0x97,
0x8D,0xAD,0xB7,0x89,0xAD,0xD7,0x85,0xB5,0xD8,0x8B,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x89,0xBE,0x39,0x82,0xBE,0x59,0x85,0xC6,0x59,0x85,0xC6,0x7A,0x85,0xCE,0x9A,
0x85,0xCE,0xBA,0x82,0xD6,0xBB,0x8B,0xD6,0xDB,0x86,0xD6,0xBB,0xCE,0xBB,0xCE,0xBA,0x87,0xCE,0x9A,0x87,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x82,
0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x87,0xAD,0xB7,0x88,0xA5,0x97,0xA5,0x96,0x84,0x30,0x52,0xAA,0x89,0x00,0x00,0x86,0x6B,0x6D,
0x84,0x30,0x9D,0x14,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x8B,0xAD,0xB7,0x89,0xAD,0xD7,0x85,0xB5,0xD8,0x8B,0xB5,0xF8,0x86,0xB6,0x18,0xBE,0x18,0xBE,0x19,0x87,0xBE,0x39,
0x85,0xC6,0x59,0x84,0xC6,0x79,0xC6,0x7A,0x85,0xCE,0x9A,0x85,0xCE,0xBA,0x82,0xD6,0xBB,0x8D,0xD6,0xDB,0x86,0xD6,0xBB,0xCE,0xBB,0xCE,0xBA,0x87,0xCE,0x9A,0x87,0xC6,
0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x82,0xBE,0x18,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0xB7,0xA5,
0x97,0x9D,0x14,0x84,0x30,0x29,0x45,0x89,0x00,0x00,0x86,0x39,0xC7,0x84,0x30,0x8C,0x71,0x87,0xA5,0x97,0x82,0xA5,0xB7,0x8B,0xAD,0xB7,0x87,0xAD,0xD7,0x84,0xAD,0xD8,
0xB5,0xD8,0x8B,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x87,0xBE,0x39,0x88,0xBE,0x59,0xC6,0x59,0xC6,0x79,0xC6,0x7A,0x85,0xCE,0x9A,0x85,0xCE,0xBA,0x82,0xD6,0xBB,0x87,
0xD6,0xDB,0x85,0xD6,0xFB,0x87,0xD6,0xDB,0x84,0xD6,0xBB,0xCE,0xBA,0x87,0xCE,0x9A,0x87,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x82,0xBE,0x18,0x85,
0xB6,0x18,0x85,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x87,0xAD,0xB7,0x8A,0xA5,0xB7,0xA5,0x97,0x8C,0x92,0x7B,0xCF,0x00,0x20,0x89,0x00,0x00,0x88,0x08,0x41,0x7B,
0xEF,0x84,0x30,0x9D,0x35,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x89,0xAD,0xB7,0x89,0xAD,0xD7,0x84,0xAD,0xD8,0xB5,0xD8,0x8B,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x85,0xBE,
0x39,0x82,0xBE,0x59,0x85,0xC6,0x59,0x84,0xC6,0x7A,0xCE,0x7A,0x85,0xCE,0x9A,0x84,0xCE,0xBA,0xD6,0xBB,0x87,0xD6,0xDB,0x82,0xD6,0xFB,0x85,0xDE,0xFB,0x82,0xD6,0xFB,
0x85,0xD6,0xDB,0x86,0xD6,0xBB,0xCE,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x82,0xCE,0x7A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x87,0xBE,0x39,0x84,0xBE,0x18,0xB6,
0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x87,0xAD,0xB7,0x88,0xA5,0x97,0x9D,0x55,0x84,0x30,0x4A,0x29,0x8D,0x00,0x00,0x86,0x4A,0x49,0x84,0x30,0x8C,0x71,
0x85,0xA5,0x97,0x85,0xA5,0xB7,0x89,0xAD,0xB7,0x89,0xAD,0xD7,0x85,0xB5,0xD8,0x87,0xB5,0xF8,0x85,0xB6,0x18,0x82,0xBE,0x18,0x85,0xBE,0x39,0x85,0xC6,0x59,0x85,0xC6,
0x7A,0x85,0xCE,0x9A,0x84,0xCE,0xBA,0xCE,0xBB,0x87,0xD6,0xDB,0x85,0xD6,0xFB,0x85,0xDE,0xFB,0x82,0xD6,0xFB,0x85,0xD6,0xDB,0x86,0xD6,0xBB,0xCE,0xBB,0xCE,0xBA,0x87,
0xCE,0x9A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x85,0xBE,0x39,0x86,0xBE,0x19,0xBE,0x18,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x85,0xAD,
0xB7,0x8A,0xA5,0xB7,0xA5,0x97,0x94,0xB3,0x84,0x10,0x10,0x82,0x8D,0x00,0x00,0x88,0x10,0x82,0x84,0x10,0x84,0x30,0x9D,0x14,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x89,0xAD,
0xB7,0x89,0xAD,0xD7,0x82,0xB5,0xD8,0x89,0xB5,0xF8,0x85,0xB6,0x18,0x88,0xBE,0x18,0xBE,0x39,0xBE,0x59,0xC6,0x59,0x85,0xC6,0x7A,0x85,0xCE,0x9A,0x86,0xCE,0xBA,0xCE,
0xBB,0xD6,0xBB,0x87,0xD6,0xDB,0x82,0xD6,0xFB,0x89,0xDE,0xFB,0x87,0xD6,0xDB,0x84,0xD6,0xBB,0xCE,0xBA,0x87,0xCE,0x9A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,
0x85,0xBE,0x39,0x82,0xBE,0x19,0x85,0xB6,0x18,0x87,0xB5,0xF8,0x82,0xAD,0xD8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x88,0xA5,0x97,0xA5,0x76,0x84,0x30,0x52,0xAA,0x91,0x00,
0x00,0x88,0x52,0x8A,0x84,0x30,0x8C,0x51,0xA5,0x96,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x89,0xAD,0xB7,0x87,0xAD,0xD7,0x82,0xB5,0xD8,0x87,0xB5,0xF8,0x85,0xB6,0x18,0x82,
0xBE,0x18,0x85,0xBE,0x39,0x86,0xC6,0x59,0xC6,0x79,0xC6,0x7A,0x87,0xCE,0x9A,0x84,0xCE,0xBA,0xD6,0xBB,0x87,0xD6,0xDB,0x82,0xD6,0xFB,0x85,0xDE,0xFB,0x82,0xDF,0x1C,
0x85,0xDE,0xFB,0x82,0xD6,0xFB,0x85,0xD6,0xDB,0x86,0xD6,0xBB,0xCE,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x85,0xBE,0x39,0x82,
0xBE,0x18,0x85,0xB6,0x18,0x85,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0xB7,0xA5,0x97,0x94,0xB3,0x84,0x30,0x18,0xC3,0x91,0x00,0x00,0x88,
0x10,0x82,0x84,0x10,0x84,0x30,0x94,0xD3,0x85,0xA5,0x97,0x82,0xA5,0xB7,0x89,0xAD,0xB7,0x87,0xAD,0xD7,0x82,0xB5,0xD8,0x87,0xB5,0xF8,0x86,0xB6,0x18,0xBE,0x18,0xBE,
0x19,0x85,0xBE,0x39,0x82,0xC6,0x59,0x85,0xC6,0x7A,0x85,0xCE,0x9A,0x86,0xCE,0xBA,0xCE,0xBB,0xD6,0xBB,0x87,0xD6,0xDB,0x85,0xDE,0xFB,0x87,0xDF,0x1C,0x85,0xDE,0xFB,
0x85,0xD6,0xDB,0x82,0xD6,0xBB,0x85,0xCE,0xBA,0x85,0xCE,0x9A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x87,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x87,0xB5,0xF8,0x87,0xAD,0xD7,
0x85,0xAD,0xB7,0x88,0xA5,0x97,0xA5,0x56,0x84,0x30,0x5A,0xCB,0x95,0x00,0x00,0x82,0x4A,0x49,0x85,0x84,0x30,0x82,0x9D,0x55,0x85,0xA5,0x97,0x89,0xAD,0xB7,0x85,0xAD,
0xD7,0x82,0xB5,0xD8,0x87,0xB5,0xF8,0x85,0xB6,0x18,0x82,0xBE,0x18,0x87,0xBE,0x39,0x82,0xC6,0x59,0x85,0xC6,0x7A,0x85,0xCE,0x9A,0x84,0xCE,0xBA,0xCE,0xBB,0x87,0xD6,
0xDB,0x84,0xD6,0xFB,0xDE,0xFB,0x89,0xDF,0x1C,0x85,0xDE,0xFB,0x87,0xD6,0xDB,0x84,0xCE,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x87,0xBE,0x39,
0x85,0xB6,0x18,0x87,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0xB7,0xA5,0x97,0x8C,0x92,0x84,0x10,0x18,0xA3,0x95,0x00,0x00,0x8E,0x08,0x41,0x7B,0xCF,0x84,
0x30,0x8C,0x71,0xA5,0x96,0xA5,0x97,0xA5,0xB7,0x87,0xAD,0xB7,0x85,0xAD,0xD7,0x87,0xB5,0xF8,0x85,0xB6,0x18,0x85,0xBE,0x18,0x87,0xBE,0x39,0x86,0xC6,0x59,0xC6,0x7A,
0xCE,0x7A,0x85,0xCE,0x9A,0x84,0xCE,0xBA,0xD6,0xBB,0x87,0xD6,0xDB,0x85,0xDE,0xFB,0x89,0xDF,0x1C,0x84,0xDE,0xFC,0xDE,0xFB,0x87,0xD6,0xDB,0x84,0xCE,0xBB,0xCE,0xBA,
0x85,0xCE,0x9A,0x88,0xC6,0x7A,0xC6,0x79,0xC6,0x59,0xBE,0x59,0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x87,0xB5,0xF8,0x84,0xB5,0xD8,0xAD,0xD7,0x87,0xAD,0xB7,0x88,
0xA5,0x97,0x9D,0x35,0x84,0x30,0x52,0x8A,0x99,0x00,0x00,0x88,0x31,0xA6,0x84,0x10,0x84,0x30,0x94,0xD3,0x85,0xA5,0x97,0x87,0xAD,0xB7,0x84,0xAD,0xD7,0xAD,0xD8,0x87,
0xB5,0xF8,0x85,0xB6,0x18,0x82,0xBE,0x18,0x89,0xBE,0x39,0x82,0xC6,0x59,0x85,0xC6,0x7A,0x85,0xCE,0x9A,0x84,0xCE,0xBA,0xD6,0xBB,0x85,0xD6,0xDB,0x84,0xD6,0xFB,0xDE,
0xFB,0x87,0xDF,0x1C,0x82,0xDF,0x3C,0x85,0xDF,0x1C,0x84,0xDE,0xFB,0xD6,0xFB,0x85,0xD6,0xDB,0x8A,0xCE,0xBB,0xCE,0xBA,0xCE,0x9A,0xCE,0x7A,0xC6,0x7A,0x85,0xC6,0x59,
0x82,0xBE,0x59,0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x87,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0xB7,0xA5,0x96,0x8C,0x71,0x7B,0xCF,0x08,0x61,0x9B,
0x00,0x00,0x82,0x63,0x2C,0x85,0x84,0x30,0x84,0x9D,0x35,0xA5,0x97,0x87,0xAD,0xB7,0x85,0xAD,0xD7,0x82,0xB5,0xD8,0x87,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x87,0xBE,
0x39,0x84,0xBE,0x59,0xC6,0x59,0x85,0xC6,0x7A,0x85,0xCE,0x9A,0x84,0xCE,0xBA,0xD6,0xBB,0x85,0xD6,0xDB,0x85,0xDE,0xFB,0x85,0xDF,0x1C,0x85,0xE7,0x3C,0x85,0xDF,0x1C,
0x8A,0xDE,0xFB,0xD6,0xFB,0xD6,0xDB,0xD6,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x85,0xC6,0x7A,0x85,0xC6,0x59,0x82,0xBE,0x59,0x85,0xBE,0x39,0x85,0xB6,0x18,0x85,0xB5,0xF8,
0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x88,0xA5,0x97,0x94,0xD3,0x84,0x30,0x31,0xA6,0x9D,0x00,0x00,0x8C,0x10,0xA2,0x7B,0xEF,0x84,0x30,0x8C,0x51,0xA5,0x76,
0xA5,0x97,0x85,0xAD,0xB7,0x85,0xAD,0xD7,0x82,0xB5,0xD8,0x87,0xB5,0xF8,0x82,0xB6,0x18,0x85,0xBE,0x18,0x85,0xBE,0x39,0x88,0xBE,0x59,0xC6,0x59,0xC6,0x79,0xC6,0x7A,
0x85,0xCE,0x9A,0x82,0xCE,0xBA,0x85,0xD6,0xDB,0x8A,0xD6,0xFB,0xDE,0xFB,0xDE,0xFC,0xDF,0x1C,0xDF,0x3C,0x85,0xE7,0x3C,0x85,0xDF,0x1C,0x8A,0xDE,0xFB,0xD6,0xFB,0xD6,
0xDB,0xD6,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x85,0xC6,0x7A,0x84,0xC6,0x59,0xBE,0x59,0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x85,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,
0xD7,0x85,0xAD,0xB7,0x88,0xA5,0x97,0x9D,0x35,0x84,0x30,0x63,0x0C,0xA1,0x00,0x00,0x82,0x39,0xC7,0x85,0x84,0x30,0x86,0x8C,0x92,0xA5,0x96,0xA5,0xB7,0x85,0xAD,0xB7,
0x85,0xAD,0xD7,0x82,0xB5,0xD8,0x85,0xB5,0xF8,0x85,0xB6,0x18,0x87,0xBE,0x39,0x8E,0xBE,0x59,0xC6,0x59,0xC6,0x79,0xC6,0x7A,0xCE,0x9A,0xCE,0xBA,0xCE,0xBB,0x85,0xD6,
0xDB,0x84,0xD6,0xFB,0xDE,0xFB,0x85,0xDF,0x1C,0x87,0xE7,0x3C,0x85,0xDF,0x1C,0x8A,0xDE,0xFB,0xD6,0xFB,0xD6,0xDB,0xD6,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x88,0xC6,0x7A,
0xC6,0x79,0xC6,0x59,0xBE,0x59,0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x85,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0x97,0xA5,0x76,0x8C,0x51,0x7B,0xEF,
0x10,0x82,0xA3,0x00,0x00,0x8A,0x5A,0xEB,0x84,0x30,0x8C,0x51,0x94,0xF3,0xA5,0x97,0x85,0xAD,0xB7,0x85,0xAD,0xD7,0x82,0xB5,0xD7,0x85,0xB5,0xF8,0x85,0xB6,0x18,0x82,
0xBE,0x18,0x85,0xBE,0x39,0x8E,0xBE,0x59,0xC6,0x59,0xC6,0x79,0xC6,0x7A,0xCE,0x9A,0xCE,0xBA,0xCE,0xBB,0x85,0xD6,0xDB,0x85,0xDE,0xFB,0x8A,0xDF,0x1C,0xDF,0x3C,0xE7,
0x3C,0xE7,0x5C,0xE7,0x3C,0x85,0xDF,0x1C,0x82,0xDE,0xFB,0x85,0xD6,0xDB,0x8A,0xD6,0xBB,0xCE,0xBA,0xCE,0x9A,0xCE,0x7A,0xC6,0x7A,0x85,0xC6,0x59,0x85,0xBE,0x39,0x84,
0xBE,0x18,0xB6,0x18,0x85,0xB5,0xF8,0x82,0xB5,0xD8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x88,0xA5,0x96,0x8C,0x72,0x84,0x30,0x31,0xA6,0xA5,0x00,0x00,0x8C,0x08,0x61,0x73,
0xAE,0x84,0x30,0x8C,0x51,0x9D,0x35,0xA5,0x97,0x85,0xAD,0xB7,0x85,0xAD,0xD7,0x87,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x85,0xBE,0x39,0x88,0xBE,0x59,0xC6,0x59,0xC6,
0x79,0xC6,0x7A,0x85,0xCE,0x9A,0x82,0xD6,0xBB,0x85,0xD6,0xDB,0x82,0xDE,0xFB,0x85,0xDF,0x1C,0x85,0xE7,0x3C,0x8A,0xE7,0x5D,0xE7,0x3C,0xDF,0x3C,0xDF,0x1C,0xDE,0xFB,
0x85,0xD6,0xDB,0x82,0xCE,0xBB,0x85,0xCE,0x9A,0x86,0xC6,0x7A,0xC6,0x79,0xC6,0x59,0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x87,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,
0xB7,0x88,0xA5,0x96,0x94,0x92,0x84,0x30,0x5A,0xEB,0xA9,0x00,0x00,0x8C,0x21,0x24,0x84,0x10,0x8C,0x51,0x8C,0x71,0xA5,0x76,0xA5,0x97,0x85,0xAD,0xB7,0x84,0xAD,0xD7,
0xB5,0xD8,0x85,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x85,0xBE,0x39,0x88,0xBE,0x59,0xC6,0x59,0xC6,0x79,0xC6,0x7A,0x85,0xCE,0x9A,0x82,0xD6,0xBB,0x85,0xD6,0xDB,0x82,
0xDE,0xFB,0x85,0xDF,0x1C,0x82,0xE7,0x3C,0x85,0xE7,0x5D,0x82,0xE7,0x3C,0x85,0xDF,0x1C,0x88,0xDE,0xFB,0xD6,0xDB,0xD6,0xBB,0xCE,0xBA,0x85,0xCE,0x9A,0x86,0xC6,0x7A,
0xC6,0x59,0xBE,0x59,0x85,0xBE,0x39,0x85,0xB6,0x18,0x85,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0x96,0x94,0xB2,0x84,0x30,0x73,0xAE,0x08,0x61,0xAB,0x00,
0x00,0x8E,0x42,0x08,0x84,0x30,0x8C,0x51,0x8C,0x92,0xA5,0x76,0xA5,0xB7,0xAD,0xB7,0x85,0xAD,0xD7,0x82,0xB5,0xD8,0x85,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x85,0xBE,
0x39,0x86,0xC6,0x59,0xC6,0x79,0xC6,0x7A,0x85,0xCE,0x9A,0x82,0xD6,0xBB,0x89,0xD6,0xDB,0x82,0xD6,0xFB,0x89,0xDE,0xFB,0x87,0xD6,0xDB,0x85,0xD6,0xBB,0x8A,0xCE,0xBA,
0xCE,0x9A,0xC6,0x7A,0xC6,0x79,0xC6,0x59,0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x85,0xB5,0xF8,0x85,0xAD,0xD7,0x85,0xAD,0xB7,0x8A,0xA5,0x96,0x94,0xB2,0x8C,0x51,
0x84,0x10,0x21,0x04,0xAF,0x00,0x00,0x8A,0x52,0xAA,0x84,0x30,0x8C,0x51,0x94,0xB2,0xA5,0x96,0x85,0xAD,0xB7,0x85,0xAD,0xD7,0x85,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,
0x85,0xBE,0x39,0x85,0xC6,0x59,0x85,0xC6,0x7A,0x82,0xCE,0x9A,0x87,0xC6,0x7A,0x87,0xC6,0x79,0x89,0xC6,0x7A,0x89,0xC6,0x79,0x87,0xC6,0x7A,0x84,0xC6,0x79,0xC6,0x59,
0x85,0xBE,0x39,0x84,0xBE,0x18,0xB6,0x18,0x85,0xB5,0xF8,0x85,0xAD,0xD7,0x8E,0xAD,0xB7,0xA5,0xB7,0xA5,0x56,0x94,0x92,0x8C,0x51,0x84,0x30,0x39,0xE7,0xB1,0x00,0x00,
0x8C,0x08,0x21,0x63,0x2C,0x84,0x30,0x8C,0x51,0x94,0xB2,0xA5,0x96,0x85,0xAD,0xB7,0x84,0xAD,0xD7,0xB5,0xD7,0x85,0xB5,0xF8,0x84,0xB6,0x18,0xBE,0x18,0x8B,0xBE,0x39,
0x82,0xBE,0x18,0x85,0xB6,0x18,0x88,0xC6,0x59,0xC6,0x7A,0xCE,0x9A,0xCE,0xBA,0x85,0xCE,0x9A,0x88,0xCE,0x7A,0xC6,0x79,0xC6,0x59,0xBE,0x18,0x85,0xB5,0xF8,0x86,0xB6,
0x18,0xBE,0x18,0xBE,0x19,0x87,0xBE,0x39,0x8A,0xBE,0x18,0xB6,0x18,0xB5,0xF8,0xB5,0xD8,0xAD,0xD7,0x85,0xAD,0xB7,0x8C,0xA5,0x97,0x9D,0x14,0x8C,0x71,0x8C,0x51,0x84,
0x30,0x52,0x8A,0xB5,0x00,0x00,0x8C,0x08,0x41,0x63,0x2C,0x84,0x30,0x8C,0x51,0x94,0xB2,0xA5,0x76,0x85,0xAD,0xB7,0x84,0xAD,0xD7,0xB5,0xD8,0x8D,0xB5,0xF8,0x85,0xAD,
0xD7,0x8A,0xBE,0x18,0xC6,0x39,0xCE,0x59,0xC6,0x58,0xC6,0x38,0x85,0xC6,0x18,0x85,0xBD,0xF7,0x86,0xBD,0xD7,0xBD,0xF7,0xC6,0x18,0x85,0xC6,0x38,0x82,0xB5,0xF7,0x87,
0xAD,0xD7,0x82,0xB5,0xD8,0x85,0xB5,0xF8,0x85,0xB5,0xD8,0x85,0xAD,0xD7,0x90,0xAD,0xB7,0xA5,0x97,0x9D,0x55,0x94,0xB2,0x8C,0x71,0x8C,0x51,0x84,0x30,0x5A,0xAB,0xB9,
0x00,0x00,0x8E,0x08,0x41,0x63,0x0C,0x84,0x30,0x8C,0x51,0x94,0x92,0xA5,0x55,0xA5,0xB7,0x87,0xAD,0xB7,0x82,0xAD,0xD7,0x89,0xAD,0xB7,0x92,0xB5,0xB7,0xB5,0xD7,0xB5,
0xB6,0xAD,0x75,0x8C,0x51,0x5A,0xCB,0x39,0xC7,0x20,0xE4,0x10,0x62,0x85,0x08,0x41,0x8C,0x10,0xA2,0x29,0x25,0x42,0x28,0x6B,0x6D,0x9C,0xD3,0xAD,0x55,0x85,0xB5,0x96,
0x84,0xAD,0x96,0xAD,0xB6,0x89,0xAD,0xB7,0x92,0xA5,0x97,0xA5,0x76,0x9D,0x34,0x94,0xD3,0x94,0x92,0x8C,0x71,0x8C,0x51,0x84,0x30,0x4A,0x69,0xBD,0x00,0x00,0x94,0x00,
0x20,0x4A,0x49,0x84,0x30,0x8C,0x51,0x8C,0x71,0x94,0xF3,0xA5,0x55,0xA5,0x96,0xA5,0x97,0xA5,0x96,0x85,0xA5,0x76,0x8C,0xAD,0x55,0xA5,0x54,0xA5,0x14,0x8C,0x71,0x52,
0x8A,0x18,0xA3,0x97,0x00,0x00,0xA4,0x00,0x20,0x29,0x65,0x6B,0x4D,0x94,0xD2,0xA5,0x14,0xA5,0x34,0xA5,0x54,0xA5,0x55,0xA5,0x34,0xA5,0x14,0x9C,0xF3,0x9C,0xD3,0x94,
0xB2,0x94,0x92,0x8C,0x71,0x8C,0x51,0x7B,0xEF,0x31,0x86,0xC3,0x00,0x00,0x8C,0x21,0x04,0x6B,0x6D,0x8C,0x51,0x8C,0x71,0x94,0x92,0x94,0xB2,0x87,0x9C,0xD3,0x8A,0x94,
0xD2,0x94,0xB2,0x6B,0x6D,0x31,0xA6,0x00,0x20,0xA1,0x00,0x00,0x8A,0x10,0x82,0x4A,0x49,0x7B,0xEF,0x94,0x92,0x94,0xB2,0x85,0x94,0xD2,0x8E,0x94,0xB2,0x94,0x92,0x8C,
0x71,0x8C,0x51,0x84,0x10,0x52,0x8A,0x10,0x62,0xC9,0x00,0x00,0x86,0x21,0x24,0x52,0x8A,0x73,0x8E,0x85,0x84,0x30,0x88,0x73,0xAE,0x5A,0xEB,0x39,0xE7,0x10,0xA2,0xAD,
0x00,0x00,0x92,0x18,0xC3,0x42,0x08,0x5A,0xCB,0x6B,0x4D,0x73,0x8E,0x6B,0x4D,0x52,0xAA,0x31,0xA6,0x08,0x61,0xA3,0x00,0x00,
};
// clang-format on

static const image_descriptor gfx_mac_raw = {
  .compression = image_compression::NQRLE,
  .width = 78,
  .height = 96,
  .byte_count = 7256,
  .image_data = gfx_mac_data,
}; // 2.06 compression ratio

image_descriptor* gfx_mac = (image_descriptor*)&gfx_mac_raw;