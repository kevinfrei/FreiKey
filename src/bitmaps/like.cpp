#include "bitmap.h"

// clang-format off
uint8_t gfx_like_data[] = {
137,0,0,0,0,1,0,2,9,9,9,10,18,17,35,23,35,24,35,25,12,31,20,31,36,31,44,31,52,31,166,31,174,31,215,
31,223,31,0,32,0,33,0,34,0,35,0,36,18,49,18,50,26,50,35,57,36,63,52,63,60,63,68,63,125,63,174,63,
223,63,0,67,0,68,0,69,0,70,9,75,18,82,18,83,26,83,35,89,35,90,43,90,52,95,60,95,68,95,133,95,231,95,
0,99,0,100,0,101,8,102,26,115,26,116,35,122,43,122,35,123,43,123,68,127,76,127,133,127,141,127,231,
127,239,127,0,132,0,133,0,134,0,135,9,141,9,142,26,148,43,155,43,156,3,159,76,159,149,159,190,159,
198,159,239,159,247,159,0,166,0,167,0,168,8,168,9,174,17,174,17,175,26,181,34,181,43,188,43,189,51,
189,3,191,84,191,92,191,100,191,149,191,157,191,198,191,206,191,247,191,0,199,17,207,17,208,34,214,
34,215,43,221,51,221,43,222,51,222,3,223,11,223,92,223,100,223,108,223,157,223,206,223,247,223,255,
223,8,232,17,240,34,246,34,247,34,248,51,254,3,255,19,255,27,255,35,255,51,255,108,255,157,255,165,
255,214,255,255,255,157,0,132,1,22,135,0,136,21,87,24,106,133,44,138,26,8,90,25,4,137,0,132,21,1,
181,0,132,1,22,133,0,138,52,41,43,108,13,133,28,137,45,133,28,136,131,108,26,122,135,0,132,22,1,175,
0,130,21,133,0,138,52,106,126,28,45,133,28,145,13,133,28,138,45,28,92,72,82,133,0,130,21,171,0,138,
21,0,35,89,111,133,28,135,13,151,28,130,13,135,28,138,126,124,67,0,21,165,0,133,1,138,0,104,91,45,
28,133,13,161,28,133,13,138,28,45,126,5,0,133,2,159,0,130,2,133,0,130,124,133,28,130,13,173,28,130,
13,133,28,130,124,133,0,130,2,155,0,136,21,0,2,57,133,28,130,13,157,28,133,29,145,28,130,13,133,28,
136,59,52,0,21,151,0,138,20,0,18,74,45,133,13,157,28,136,13,94,112,29,147,28,134,13,45,74,133,0,130,
20,147,0,130,2,133,0,134,74,45,13,159,28,138,12,28,77,48,128,149,28,140,13,28,74,50,0,2,143,0,130,1,
133,0,134,73,45,13,159,28,134,29,112,100,133,136,134,134,112,29,147,28,134,13,45,73,147,0,138,21,0,
7,45,13,161,28,134,13,47,102,133,136,134,80,46,13,149,28,138,13,45,124,0,21,139,0,136,21,0,5,28,133,
13,161,28,134,12,61,81,135,136,134,31,112,29,153,28,134,5,0,21,135,0,140,1,0,69,109,28,13,163,28,
134,13,47,102,135,136,134,98,112,29,149,28,140,13,28,109,34,0,1,133,0,138,22,0,124,45,13,163,28,134,
47,75,134,137,136,134,99,112,29,151,28,148,13,45,7,0,22,0,1,0,121,126,163,28,136,13,30,112,98,139,
136,134,31,112,29,151,28,150,13,28,126,103,0,1,22,0,124,28,13,161,28,134,29,112,31,139,136,134,80,
28,13,137,28,130,13,145,28,144,13,28,124,0,22,0,19,111,165,28,134,13,45,65,139,136,134,78,94,47,137,
29,147,28,136,13,28,110,19,133,0,134,54,28,13,161,28,134,29,94,78,139,136,136,119,115,112,11,137,
129,132,28,29,145,28,134,13,28,54,133,0,134,26,45,13,159,28,134,29,112,48,141,136,134,16,76,116,139,
115,134,12,129,29,143,28,144,13,45,26,0,36,111,28,13,145,28,139,29,133,28,134,13,27,64,153,136,140,
120,136,49,114,130,29,141,28,140,13,28,111,37,38,13,147,28,130,13,135,130,140,11,129,12,30,94,98,
161,136,134,118,112,29,145,28,134,13,70,25,147,28,132,12,45,137,96,138,97,60,13,112,118,161,136,134,
64,127,29,143,28,140,13,28,54,124,45,13,141,28,136,13,29,33,120,135,119,138,120,80,115,127,49,161,
136,134,32,112,29,143,28,140,13,28,106,59,45,13,139,28,136,29,129,115,120,141,136,134,62,127,80,159,
136,132,135,127,147,28,132,13,45,133,59,132,28,13,139,28,136,29,129,115,119,141,136,134,48,129,81,
161,136,134,15,112,29,143,28,140,13,45,59,58,28,13,139,28,136,29,129,115,120,141,136,134,48,9,102,
161,136,134,17,94,29,143,28,140,13,45,58,59,45,13,139,28,136,29,129,97,120,141,136,134,48,9,102,161,
136,134,133,112,29,143,28,140,13,28,44,123,45,13,139,28,136,29,129,97,120,141,136,134,48,9,102,159,
136,134,32,94,29,145,28,140,13,45,106,72,28,13,139,28,136,29,129,97,120,141,136,134,48,9,102,159,
136,134,64,61,12,145,28,138,13,45,72,88,13,141,28,136,29,129,97,120,141,136,134,48,9,102,161,136,
134,132,128,29,143,28,138,13,28,86,35,111,141,28,136,29,129,97,120,141,136,134,48,9,102,159,136,134,
79,11,29,143,28,134,13,28,109,133,0,134,42,45,13,137,28,136,29,129,97,120,141,136,134,48,9,102,157,
136,136,81,61,11,29,143,28,134,13,28,26,133,0,134,40,28,13,137,28,136,29,129,97,120,141,136,134,48,
10,102,159,136,134,14,94,29,147,28,130,41,133,0,132,34,111,139,28,136,29,130,96,119,141,136,134,63,
127,81,159,136,134,62,112,29,145,28,130,93,133,0,138,22,0,124,28,13,135,28,136,29,129,97,119,141,
136,136,63,75,98,118,153,101,136,118,117,128,29,143,28,146,13,28,107,0,22,1,0,4,13,139,28,134,11,95,
120,141,136,134,31,113,128,157,94,130,112,149,28,148,126,3,0,1,0,22,0,124,45,13,137,28,134,11,117,
100,135,79,132,100,15,133,28,130,29,157,30,130,29,145,28,138,13,45,124,0,22,133,0,140,1,0,84,126,28,
13,135,28,132,13,112,141,94,130,13,177,28,140,13,28,109,68,0,1,135,0,138,21,0,39,28,13,137,28,130,
29,139,30,130,29,183,28,134,23,0,21,139,0,138,21,0,7,45,13,197,28,138,13,45,7,0,21,141,0,130,1,133,
0,134,74,28,13,193,28,134,13,28,74,133,0,130,1,143,0,140,2,0,82,91,28,13,189,28,140,13,28,91,53,0,2,
147,0,140,21,0,51,91,45,13,185,28,140,13,28,91,51,0,21,151,0,142,21,0,22,73,45,28,13,177,28,133,13,
138,45,73,22,0,21,155,0,130,21,133,0,130,7,133,28,130,13,171,28,133,13,133,28,130,7,133,0,130,20,
159,0,130,2,133,0,136,25,126,45,28,133,13,161,28,133,13,136,28,45,111,25,133,0,130,2,163,0,144,1,21,
0,83,7,131,45,28,135,13,149,28,135,13,133,28,140,126,124,83,0,22,1,169,0,130,21,133,0,138,121,6,126,
28,45,133,28,145,13,133,28,138,45,28,126,124,85,133,0,130,21,175,0,132,1,22,133,0,136,36,54,56,111,
133,28,143,45,138,28,126,8,54,66,133,0,132,22,1,181,0,132,1,22,135,0,136,36,105,55,124,135,59,138,
44,125,55,71,68,135,0,132,22,1,157,0,
};
// clang-format on

static const image_descriptor gfx_like_raw = {
  .width = 50,
  .height = 50,
  .byte_count = 1611,
  .compression = image_compression::PAL_NQRLE, 
  .image_data = gfx_like_data
}; // 3.10366 compression rate

const image_descriptor* gfx_like = &gfx_like_raw;
