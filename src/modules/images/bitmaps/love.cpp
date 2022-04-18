#include "bitmap.h"

// clang-format off
uint8_t gfx_love_data[] = {
139,0,0,0,8,0,16,0,24,0,40,0,16,1,40,1,48,1,56,1,64,1,248,2,248,3,248,4,248,5,240,6,248,6,193,7,201,
7,248,7,193,8,201,8,209,8,217,8,248,8,241,9,249,9,250,11,251,14,252,18,253,21,254,24,255,28,40,33,
56,33,64,33,64,34,72,34,80,34,88,34,80,35,88,35,104,35,225,40,248,40,225,41,233,41,241,41,249,41,
251,47,252,50,253,53,253,54,254,57,255,61,96,67,104,67,112,67,112,68,233,72,233,73,241,73,249,73,
241,74,249,74,251,79,253,86,254,89,254,90,255,93,112,100,120,100,128,100,248,104,241,105,249,105,
249,106,250,108,251,111,251,112,253,119,254,122,255,125,255,126,136,132,136,133,144,133,152,133,160,
134,248,137,249,138,249,139,250,141,251,144,252,147,254,154,254,155,255,158,144,165,152,165,160,165,
168,165,160,166,168,166,248,168,248,169,241,170,249,170,249,171,250,173,251,177,253,183,254,187,255,
191,160,198,168,198,176,198,176,199,184,199,240,200,248,200,240,201,248,201,249,202,249,203,250,206,
252,212,254,219,255,223,192,231,200,231,200,232,208,232,248,233,251,241,252,244,252,245,253,248,254,
252,255,255,157,0,132,1,3,135,0,138,3,41,86,116,128,133,21,138,130,117,99,56,8,135,0,132,3,2,183,0,
130,3,133,0,140,6,84,128,44,60,63,133,75,133,63,130,75,133,63,138,61,45,17,99,36,133,0,132,3,2,175,
0,130,3,133,0,136,34,114,45,61,133,63,130,61,135,60,130,61,137,60,142,63,61,75,63,60,128,54,133,0,
130,3,171,0,140,3,0,2,115,59,63,133,61,130,60,153,61,132,60,61,133,63,136,60,129,38,0,133,2,163,0,
133,1,138,0,83,44,75,63,167,61,138,60,61,63,60,114,133,0,130,3,159,0,130,2,133,0,136,115,61,63,62,
173,61,130,60,133,63,136,20,33,0,3,155,0,142,2,0,1,21,63,61,60,179,61,140,60,63,44,54,0,3,151,0,140,
2,0,5,22,75,60,185,61,140,60,61,60,56,0,3,147,0,130,1,133,0,134,22,75,60,189,61,140,60,61,59,54,0,3,
145,0,138,2,0,19,75,60,195,61,138,63,44,32,0,2,141,0,136,3,0,114,63,149,61,133,75,153,61,134,63,75,
63,145,61,138,60,63,21,0,1,139,0,136,2,0,69,60,145,61,134,75,122,106,133,75,134,106,122,89,141,61,
130,75,133,106,133,75,130,89,133,106,130,63,141,61,138,60,63,113,0,3,141,0,134,22,63,60,141,61,150,
106,72,11,15,118,72,15,11,18,106,74,135,61,150,106,119,12,13,23,104,18,12,15,106,75,143,61,136,60,
55,0,2,133,0,138,3,0,98,63,60,141,61,138,106,13,124,110,126,133,31,168,111,110,77,13,60,75,61,89,13,
76,51,94,31,53,137,30,133,15,47,75,139,61,138,60,75,130,0,2,135,0,136,1,44,63,60,139,61,136,89,14,
29,112,143,138,142,136,120,47,106,15,134,96,143,138,136,52,24,25,75,139,61,146,63,60,55,0,2,3,0,97,
63,137,61,138,63,61,105,13,50,149,138,136,80,88,15,51,149,138,136,94,23,75,63,139,61,146,63,17,0,3,
1,0,22,63,60,135,61,138,63,89,18,64,127,151,138,132,29,108,153,138,134,65,12,106,141,61,132,60,37,
133,0,132,69,73,141,61,134,106,13,66,153,138,132,31,67,153,138,136,82,123,46,75,139,61,132,75,113,
133,0,134,114,75,60,137,61,136,75,121,76,96,183,138,134,93,13,106,137,61,134,60,63,21,133,0,134,21,
63,60,137,61,134,106,15,49,185,138,134,136,11,122,141,61,138,60,36,7,45,63,139,61,134,106,12,29,185,
138,134,80,13,106,141,61,134,63,70,55,143,61,134,122,12,65,185,138,134,95,13,106,141,61,136,75,99,
85,63,141,61,134,106,12,125,185,138,134,66,12,106,139,61,140,60,75,128,102,75,60,139,61,136,89,18,
77,127,183,138,134,50,12,106,139,61,140,60,63,21,100,63,60,139,61,136,63,75,23,31,181,138,136,127,
48,23,89,139,61,140,60,63,21,102,75,60,141,61,134,106,12,50,181,138,134,95,13,106,141,61,140,60,63,
21,87,63,60,141,61,136,75,47,90,68,179,138,134,133,18,89,141,61,138,60,63,131,71,63,145,61,134,106,
12,125,177,138,136,52,12,106,63,143,61,136,63,115,38,60,147,61,134,106,15,80,173,138,136,81,26,132,
75,145,61,138,63,86,1,44,63,145,61,136,75,132,107,53,169,138,136,127,133,14,106,147,61,140,62,56,0,
20,63,60,145,61,136,106,18,27,96,167,138,134,125,12,122,147,61,140,63,45,6,0,101,75,149,61,136,106,
14,92,96,163,138,134,51,13,106,147,61,134,60,63,20,133,0,132,39,60,149,61,138,47,122,13,78,96,159,
138,136,29,12,106,63,149,61,144,75,85,0,3,0,131,74,60,149,61,136,122,15,124,53,153,138,138,127,93,
12,106,63,149,61,144,63,58,8,0,3,0,71,63,153,61,136,106,18,107,94,149,138,136,68,78,12,122,151,61,
150,62,75,115,0,3,0,2,0,21,63,60,151,61,138,106,25,18,65,127,143,138,136,67,123,18,122,153,61,150,
63,59,34,0,1,0,3,0,70,61,63,153,61,138,75,106,11,109,31,137,138,138,96,135,15,25,106,153,61,138,60,
75,115,0,3,135,0,138,2,0,16,63,60,155,61,150,123,15,72,79,112,138,52,91,12,106,75,153,61,136,60,63,
44,7,139,0,138,1,0,9,45,63,157,61,146,106,75,10,64,28,12,103,122,63,157,61,136,63,84,0,3,139,0,136,
3,0,71,63,159,61,140,75,122,43,14,106,75,157,61,138,60,75,117,0,3,143,0,136,3,0,101,75,161,61,133,
89,159,61,134,60,75,21,151,0,136,2,0,115,63,191,61,134,60,75,21,133,0,130,2,147,0,133,1,132,0,117,
133,63,185,61,133,63,136,22,33,0,3,151,0,142,1,2,0,101,62,61,60,177,61,136,60,61,63,129,133,0,130,2,
157,0,142,3,0,71,59,75,61,60,169,61,132,60,61,133,63,130,114,133,0,130,2,161,0,136,3,0,35,16,133,63,
132,61,60,165,61,133,63,138,22,69,0,2,1,165,0,130,3,133,0,140,70,21,63,75,63,61,133,60,147,61,133,
60,138,61,75,63,42,98,133,0,130,3,171,0,132,1,2,133,0,138,71,130,60,63,75,133,63,130,61,137,60,133,
61,133,63,136,75,61,22,98,135,0,130,2,177,0,133,2,133,0,138,38,101,129,42,60,139,75,140,63,61,45,21,
114,57,135,0,130,3,185,0,132,2,3,137,0,146,40,84,99,114,115,99,86,55,4,135,0,132,1,3,159,0,
};
// clang-format on

static const image_descriptor gfx_love_raw = {
  .width = 50,
  .height = 50,
  .byte_count = 1544,
  .compression = image_compression::PAL_NQRLE,
  .image_data = gfx_love_data}; // 3.23834 compression rate

const image_descriptor* gfx_love = &gfx_love_raw;