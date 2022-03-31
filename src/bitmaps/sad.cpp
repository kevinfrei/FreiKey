#include "bitmap.h"

// clang-format off
uint8_t gfx_sad_data[] = {
171,0,0,0,0,1,33,1,41,1,74,1,74,2,82,2,74,3,123,4,255,5,148,6,156,6,189,7,197,7,189,8,230,9,255,10,
255,11,35,24,35,25,20,31,28,31,52,31,0,32,8,32,49,32,33,33,41,33,49,33,82,34,0,35,74,35,0,36,123,36,
156,38,255,38,197,39,197,40,205,40,230,41,238,41,255,41,230,42,238,42,18,49,26,50,214,51,52,63,60,
63,68,63,8,64,16,64,49,65,82,67,90,67,123,68,156,70,164,70,197,72,205,72,238,73,238,74,246,74,9,76,
230,80,157,90,68,94,52,95,16,96,24,96,16,97,98,97,16,98,82,98,90,98,49,99,82,99,90,99,98,99,0,100,
123,100,131,100,131,101,164,102,172,102,164,103,172,103,205,104,238,105,238,106,246,106,26,116,92,
126,8,128,24,128,32,128,57,129,57,130,65,130,90,130,90,131,139,133,164,134,172,134,172,135,205,136,
213,136,246,138,246,141,238,142,1,143,238,143,173,153,43,156,100,158,24,160,32,160,65,161,98,163,98,
164,139,164,131,165,139,165,180,166,180,167,213,168,221,168,221,169,246,170,254,170,246,172,246,173,
181,184,51,188,108,189,32,192,65,193,65,194,57,195,106,195,139,197,213,200,221,200,221,201,254,202,
254,203,189,214,197,214,189,215,51,221,116,221,3,223,32,224,40,224,65,226,73,226,98,227,254,230,188,
231,254,231,180,232,254,232,221,233,229,233,254,233,254,234,254,235,17,240,51,254,3,255,19,255,157,
0,132,51,94,135,0,136,117,55,84,36,135,142,138,143,37,103,55,136,135,0,132,94,68,181,0,132,50,116,
133,0,138,136,57,162,107,165,145,17,138,166,107,162,57,155,133,0,132,116,50,175,0,130,115,133,0,134,
77,87,128,133,17,132,165,166,145,144,132,165,166,133,17,134,128,105,78,133,0,130,116,169,0,144,24,
94,0,155,37,129,17,166,135,144,147,165,137,144,144,165,17,129,58,155,0,69,50,163,0,130,94,133,0,136,
57,107,17,165,133,144,161,165,133,144,136,165,16,107,57,133,0,130,94,159,0,140,115,0,28,125,165,166,
133,144,169,165,144,166,144,165,166,127,97,0,116,155,0,138,115,0,29,42,17,133,144,177,165,133,144,
138,17,60,77,0,116,151,0,140,115,0,118,90,16,144,185,165,140,144,17,107,139,0,116,147,0,140,94,0,74,
90,17,144,189,165,140,144,17,90,99,0,115,143,0,140,24,0,115,40,17,144,193,165,140,144,17,60,3,0,24,
141,0,138,94,0,105,17,144,197,165,138,144,17,125,0,68,139,0,138,116,0,57,17,144,201,165,138,144,17,
102,0,116,135,0,140,24,0,29,90,166,144,201,165,140,145,166,107,73,0,51,133,0,140,115,0,37,17,144,
166,203,165,152,144,17,87,0,116,0,51,0,54,129,165,144,205,165,150,144,165,144,119,0,68,94,0,37,17,
144,143,165,137,144,165,165,137,144,143,165,146,144,17,87,0,94,0,136,107,166,139,165,136,144,145,
144,165,133,17,132,166,144,161,165,136,144,165,16,17,133,165,133,144,139,165,134,166,129,29,133,0,
134,34,165,144,139,165,136,144,17,166,60,133,143,134,90,165,144,161,165,130,90,133,143,136,60,166,
17,144,139,165,134,145,17,83,133,0,134,162,17,144,137,165,138,144,16,162,82,3,133,0,136,138,61,165,
144,153,165,136,144,165,61,75,133,0,138,2,81,162,17,144,137,165,144,144,17,15,0,98,107,166,144,133,
165,133,144,132,166,37,141,0,134,39,17,144,153,165,134,144,17,15,141,0,152,14,16,144,165,166,165,
144,166,129,155,101,166,137,165,134,144,17,141,133,0,142,154,14,39,162,39,166,144,159,165,140,166,
39,163,39,12,155,133,0,134,125,17,144,135,165,140,144,166,140,103,17,144,135,165,142,144,165,80,0,5,
61,17,133,165,133,166,161,165,135,166,142,165,17,90,100,0,156,166,137,165,140,144,17,123,14,17,144,
135,165,144,144,166,37,26,125,17,166,165,133,166,130,144,161,165,150,144,165,17,166,165,17,162,1,
104,166,144,135,165,140,144,17,58,141,17,144,141,165,130,129,133,165,140,125,11,84,40,16,144,157,
165,140,144,17,43,103,34,125,133,165,134,128,144,166,137,165,140,144,17,162,143,17,144,139,165,136,
144,165,166,124,137,0,134,163,17,144,153,165,134,144,17,15,137,0,130,124,145,165,140,144,17,163,143,
17,144,139,165,148,144,17,40,0,51,116,28,0,8,144,155,165,150,144,165,55,0,25,135,69,0,39,166,144,
139,165,140,144,17,162,141,17,144,139,165,152,144,17,59,0,116,0,23,0,3,88,165,144,149,165,136,144,
166,90,96,135,0,138,135,0,37,17,144,139,165,140,144,17,162,58,17,144,139,165,152,144,17,87,0,152,0,
24,0,52,90,165,144,149,165,152,144,166,107,137,0,24,0,152,0,59,17,144,139,165,140,144,17,106,84,17,
144,139,165,146,144,165,89,1,0,152,25,0,122,157,165,140,144,166,140,0,25,153,133,0,134,61,165,144,
139,165,138,144,17,124,81,166,141,165,136,166,144,166,59,135,0,136,29,61,166,144,153,165,136,144,
166,61,76,135,0,134,58,16,144,141,165,142,144,166,120,117,107,165,144,139,165,146,145,144,16,40,158,
58,107,166,144,161,165,138,128,59,158,39,166,143,165,144,144,165,129,155,0,141,17,144,141,165,133,
144,130,166,133,17,132,165,144,161,165,132,144,165,135,17,130,144,143,165,134,144,17,162,133,0,134,
57,166,144,143,165,139,144,167,165,135,144,145,165,134,144,17,103,133,0,136,52,90,165,144,163,165,
141,144,163,165,148,144,165,107,117,0,115,0,12,17,144,159,165,134,144,165,166,137,17,130,166,135,
144,157,165,150,144,17,37,0,115,50,0,29,129,166,144,153,165,133,144,148,16,166,62,125,38,58,125,60,
166,16,133,144,143,165,130,145,139,165,150,166,129,77,0,51,0,115,0,37,17,144,151,165,130,144,133,
165,134,143,122,28,137,0,140,27,121,143,17,166,144,137,165,138,144,145,164,165,166,133,165,138,145,
17,59,0,116,133,0,140,24,0,5,107,165,144,147,165,136,144,165,144,103,137,0,133,117,137,0,136,85,144,
165,144,135,165,152,166,161,146,111,164,145,144,166,128,53,0,51,135,0,138,116,0,56,17,144,149,165,
132,144,34,133,0,134,5,158,39,133,107,134,39,12,31,133,0,132,34,144,135,165,152,145,164,109,169,132,
9,145,144,17,83,0,116,139,0,138,94,0,106,17,144,143,165,134,144,16,61,133,0,134,121,107,17,135,166,
133,17,132,107,140,133,0,132,40,17,133,144,150,145,159,112,151,92,131,144,17,125,0,68,141,0,140,24,
0,115,39,17,144,143,165,140,166,144,160,83,144,165,141,144,140,166,145,86,160,144,165,133,145,150,
165,108,66,48,169,147,35,42,3,0,24,143,0,140,94,0,4,90,17,144,141,165,132,144,165,133,17,132,166,
144,141,165,132,144,166,133,17,156,165,144,165,145,157,148,169,49,169,150,61,71,0,94,147,0,140,115,
0,100,89,16,144,143,165,133,144,149,165,135,144,152,165,166,165,145,134,170,48,47,133,93,0,70,151,0,
138,115,0,7,39,17,133,144,171,165,148,145,159,46,169,48,22,67,113,0,72,155,0,136,115,0,95,59,133,
166,133,144,167,165,150,145,157,65,151,48,22,47,149,79,0,1,155,0,130,68,133,0,136,10,107,17,165,133,
144,161,165,140,145,144,130,114,21,48,135,47,134,167,0,30,157,0,144,24,115,0,6,37,129,17,165,135,
144,147,165,137,144,138,166,41,64,20,48,133,47,138,22,47,18,0,32,161,0,130,115,133,0,134,78,58,107,
133,17,133,165,145,144,133,165,133,17,140,90,58,119,110,168,47,133,22,136,67,91,0,30,163,0,132,50,
115,133,0,138,96,83,143,107,144,145,17,154,144,90,162,83,52,0,1,0,44,22,67,47,19,173,0,132,51,115,
135,0,138,97,8,84,12,126,133,142,138,126,13,84,33,117,135,0,142,115,51,32,0,63,18,45,147,0,
};
// clang-format on

static const image_descriptor gfx_sad_raw = {
  .width = 50,
  .height = 50,
  .byte_count = 1840,
  .compression = image_compression::PAL_NQRLE, 
  .image_data = gfx_sad_data
}; // 2.71739 compression rate

const image_descriptor* gfx_sad = &gfx_sad_raw;
