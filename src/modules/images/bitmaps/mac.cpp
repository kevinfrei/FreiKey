#include "bitmap.h"

// clang-format off
static const uint8_t gfx_mac_data[] = {
136,0,0,0,33,4,66,8,99,12,132,16,157,20,165,20,182,24,190,24,198,24,190,25,223,28,0,32,8,33,33,36,
41,37,66,40,74,41,99,44,99,45,107,45,132,48,132,49,157,52,165,52,157,53,165,53,190,56,198,56,190,57,
198,57,223,60,231,60,231,61,8,65,41,69,74,73,107,77,132,81,140,81,165,84,157,85,165,85,173,85,165,
86,198,88,190,89,198,89,206,89,231,92,231,93,8,97,16,98,41,101,74,105,107,109,140,113,140,114,173,
117,165,118,173,118,198,121,198,122,206,122,231,125,239,125,16,130,49,134,82,138,115,142,140,146,
148,146,165,150,173,150,181,150,165,151,173,151,198,154,206,154,239,157,239,158,247,158,16,162,24,
163,49,166,82,170,90,171,115,174,115,175,148,178,148,179,173,182,181,182,165,183,173,183,181,183,
206,186,206,187,214,187,247,190,24,195,57,199,82,203,90,203,115,207,123,207,148,210,148,211,156,211,
173,215,181,215,189,215,173,216,181,216,214,219,247,222,247,223,255,223,24,227,32,228,57,231,90,235,
90,236,98,236,123,239,148,243,156,243,148,244,156,244,181,247,189,247,181,248,189,248,214,251,222,
251,222,252,229,0,138,66,101,85,37,121,13,129,0,138,12,67,19,70,5,133,42,130,55,11,129,0,138,67,105,
23,94,112,133,109,132,76,37,7,129,0,136,82,55,59,7,135,131,136,113,112,76,3,5,129,0,142,67,126,62,
78,47,10,7,133,131,134,113,59,85,3,129,0,140,54,8,31,133,78,62,133,29,130,8,133,131,132,41,120,1,
129,0,156,68,78,65,31,114,97,62,47,46,29,7,131,127,1,255,0,158,16,47,80,50,11,114,97,78,62,47,29,7,
131,38,12,253,0,140,15,91,32,65,32,11,133,114,142,97,78,62,46,7,94,68,253,0,134,34,70,97,133,50,134,
31,135,133,133,114,140,97,62,46,7,5,119,253,0,138,102,29,133,50,32,133,11,144,135,134,133,98,78,46,
131,55,253,0,140,100,42,62,135,32,31,139,11,138,114,78,46,42,14,253,0,138,3,7,78,11,31,137,11,140,
32,11,114,78,7,3,253,0,138,66,5,29,96,135,137,11,142,32,50,31,114,62,89,52,253,0,140,2,109,46,96,
133,135,133,11,142,31,50,65,32,114,73,53,255,0,140,88,7,47,96,114,133,133,11,140,50,65,80,31,8,36,
255,0,156,34,127,7,47,78,114,133,11,31,64,99,50,8,68,1,129,0,154,14,42,7,46,78,97,133,11,50,64,31,
95,17,3,129,0,152,84,59,7,46,62,97,114,133,114,62,107,53,5,129,0,138,2,72,131,29,46,133,47,136,29,
42,122,52,7,129,0,134,2,59,112,133,131,136,73,127,122,118,11,129,0,142,101,39,38,104,103,84,51,81,
130,0,132,34,82,133,100,132,82,34,201,0,152,118,120,85,20,87,4,124,87,3,36,53,34,167,0,160,13,35,54,
37,21,107,5,24,26,24,5,56,37,16,14,12,185,0,164,100,54,105,107,60,8,62,96,97,78,61,132,58,89,4,121,
67,13,157,0,140,35,103,39,26,110,47,147,78,138,29,60,39,54,100,177,0,142,119,3,39,42,61,97,98,143,
114,144,98,97,62,73,89,105,54,100,147,0,138,82,36,21,43,27,133,78,130,96,145,97,130,96,137,78,136,8,
126,103,83,169,0,140,51,85,21,42,78,97,133,114,133,133,133,135,133,11,133,135,130,133,133,114,144,
98,97,29,42,39,55,120,83,135,0,140,66,101,55,24,8,78,161,97,130,96,135,78,136,8,89,17,12,163,0,138,
35,105,89,30,97,133,114,132,133,135,133,11,133,31,133,32,130,31,135,11,132,134,133,133,114,150,97,
78,129,24,89,4,87,21,24,110,78,137,97,133,98,145,114,133,98,141,97,135,78,134,73,55,66,159,0,136,2,
4,42,96,133,114,130,134,133,11,132,31,32,135,50,133,64,133,50,132,32,31,133,11,132,135,133,135,114,
133,97,133,78,137,97,130,98,163,114,130,98,139,97,133,78,134,8,124,119,155,0,140,68,21,110,97,114,
133,133,11,132,31,32,133,50,133,65,135,80,134,79,65,64,133,50,132,32,31,133,11,132,135,133,147,114,
141,133,143,134,135,133,137,114,130,98,135,97,133,78,134,132,4,1,151,0,148,68,39,8,98,114,134,11,31,
32,50,133,65,132,80,81,133,99,130,115,133,99,146,81,80,79,65,64,50,33,32,31,133,11,133,135,130,134,
133,133,130,134,135,135,149,11,133,135,135,133,139,114,130,98,135,97,138,96,78,73,105,83,147,0,144,
2,21,8,98,114,135,11,31,133,50,133,65,132,80,81,133,99,132,115,117,133,116,130,115,135,99,136,80,79,
65,64,133,50,130,32,133,31,141,11,135,31,133,32,133,31,135,11,133,135,130,134,133,133,139,114,130,
98,137,97,135,78,134,70,69,34,143,0,146,14,4,110,97,114,134,11,31,33,133,50,133,65,133,80,130,81,
151,99,130,81,133,80,133,65,149,50,130,33,133,32,130,31,137,11,132,135,134,133,133,137,114,130,98,
139,97,133,78,138,47,107,4,37,66,141,0,140,34,87,42,97,114,133,133,11,132,31,32,133,50,130,64,133,
65,133,80,130,81,135,99,130,81,145,80,133,79,139,65,139,50,130,33,133,32,130,31,137,11,132,135,134,
133,133,137,114,130,98,137,97,135,78,138,110,39,4,36,12,143,0,140,85,71,78,114,133,135,133,11,132,
31,32,135,50,133,65,130,79,145,80,147,65,133,64,139,50,130,33,133,32,133,31,137,11,132,135,134,133,
133,137,114,130,98,137,97,133,78,132,62,5,133,4,130,84,145,0,142,118,4,8,97,114,133,135,133,11,134,
31,32,33,133,50,130,64,135,65,133,80,133,79,143,65,133,64,145,50,130,33,133,32,135,31,137,11,132,
135,134,133,133,135,114,133,98,137,97,133,78,132,29,71,133,4,130,53,147,0,134,3,128,97,133,114,132,
133,135,133,11,130,31,133,32,135,50,130,64,147,65,153,50,137,32,133,31,139,11,134,135,134,133,137,
114,130,98,137,97,135,78,138,131,70,21,4,67,147,0,136,100,21,29,97,133,114,132,133,135,135,11,132,
31,32,137,50,130,64,137,65,130,64,147,50,130,33,141,32,135,31,141,11,130,135,133,133,137,114,130,98,
137,97,133,78,140,46,94,107,21,4,36,149,0,136,68,107,96,97,133,114,132,133,135,135,11,134,31,32,33,
137,50,133,64,143,50,130,33,139,32,141,31,145,11,130,135,133,133,137,114,130,98,135,97,133,78,142,
77,131,75,41,21,4,18,149,0,138,13,124,95,97,98,133,114,132,133,135,135,11,133,31,132,32,33,145,50,
133,33,137,32,135,31,155,11,133,135,133,133,137,114,137,97,133,78,132,29,94,133,75,136,56,21,4,83,
149,0,138,53,21,62,97,98,133,114,132,133,135,135,11,133,31,133,32,130,33,139,50,130,33,135,32,135,
31,153,11,137,135,130,134,135,133,135,114,130,98,135,97,133,78,132,62,131,135,75,130,25,133,21,130,
36,151,0,136,85,107,78,97,135,114,132,133,135,137,11,133,31,133,32,135,33,135,32,133,31,149,11,141,
135,133,134,137,133,137,114,130,98,135,97,133,78,132,10,94,137,75,136,70,21,124,51,151,0,138,87,42,
96,97,98,133,114,134,133,134,135,137,11,133,31,137,32,133,31,149,11,137,135,133,134,143,133,139,114,
135,97,133,78,136,47,109,94,93,135,75,130,59,133,21,130,54,151,0,138,66,4,110,96,97,135,114,133,133,
130,135,139,11,137,31,145,11,137,135,133,134,145,133,143,114,130,98,135,97,134,78,62,131,135,94,130,
93,135,75,130,127,133,21,130,118,151,0,134,35,4,47,133,97,135,114,133,133,132,134,135,153,11,133,
135,133,134,149,133,149,114,130,98,133,97,133,78,130,10,139,94,130,93,135,75,134,89,21,87,153,0,134,
2,21,78,133,97,137,114,134,133,134,135,145,11,130,135,133,134,139,133,163,114,133,98,133,97,134,96,
78,29,133,109,139,94,130,93,135,75,134,56,21,85,153,0,134,68,56,78,133,97,137,114,133,133,132,134,
135,133,11,156,114,62,29,7,131,112,113,131,7,10,46,62,78,97,153,114,137,98,135,97,134,78,29,131,133,
109,141,94,130,93,135,75,133,21,130,101,153,0,140,3,71,78,96,97,98,135,114,135,133,134,134,78,7,141,
109,130,112,141,131,133,7,134,29,47,77,155,97,136,78,29,131,112,137,109,139,94,130,93,133,75,130,72,
133,21,130,14,153,0,140,37,89,78,96,97,98,137,114,136,133,97,7,94,143,109,130,113,141,131,141,7,136,
29,46,47,62,133,78,133,96,133,78,132,47,29,135,131,130,113,139,109,137,94,130,93,133,75,130,72,133,
21,130,83,153,0,140,69,89,78,96,97,98,137,114,132,62,109,133,94,143,109,130,113,139,131,145,7,135,8,
139,7,141,131,132,113,112,137,109,137,94,130,93,133,75,130,72,133,21,130,66,153,0,136,87,89,78,96,
133,97,135,114,130,61,135,94,145,109,139,131,143,7,143,8,135,7,143,131,132,113,112,135,109,137,94,
130,93,135,75,134,22,21,66,153,0,136,87,89,78,96,133,97,133,98,130,46,137,94,143,109,130,110,139,
131,141,7,139,8,130,29,133,8,139,7,141,131,130,113,137,109,137,94,130,93,133,75,134,56,21,82,153,0,
132,87,71,133,78,135,97,130,10,139,94,143,109,130,113,139,131,139,7,137,8,135,29,130,10,135,8,135,7,
141,131,133,113,135,109,139,94,133,75,134,89,21,119,153,0,132,69,56,133,78,134,97,78,131,139,94,145,
109,130,113,137,131,139,7,133,8,145,29,130,10,133,8,135,7,141,131,130,113,137,109,137,94,133,75,134,
127,21,53,153,0,132,37,21,133,78,132,62,109,141,94,143,109,132,112,113,137,131,137,7,133,8,130,10,
149,29,130,10,133,8,135,7,139,131,132,113,112,135,109,135,94,133,75,134,41,21,16,153,0,140,121,21,
62,29,94,75,141,94,143,109,133,113,135,131,137,7,135,8,155,29,132,10,8,135,7,139,131,130,113,135,
109,137,94,133,75,132,39,3,153,0,134,68,21,59,135,75,130,93,141,94,139,109,132,112,113,139,131,135,
7,133,8,130,10,141,29,133,46,132,47,46,139,29,133,8,135,7,137,131,130,113,135,109,135,94,138,93,75,
107,124,13,151,0,134,2,21,23,135,75,130,93,141,94,139,109,133,113,137,131,137,7,132,8,10,141,29,133,
46,139,47,139,29,132,10,8,133,7,137,131,132,113,112,133,109,135,94,136,75,41,21,53,151,0,134,67,4,
125,135,75,130,93,139,94,141,109,130,112,139,131,135,7,133,8,143,29,130,46,143,47,133,46,137,29,132,
10,8,133,7,135,131,130,113,135,109,133,94,136,93,75,70,123,151,0,134,100,4,89,133,75,133,93,139,94,
141,109,132,112,113,137,131,135,7,133,8,141,29,133,46,135,47,133,62,139,47,130,46,137,29,132,10,8,
133,7,135,131,130,113,133,109,133,94,136,93,41,21,100,149,0,134,13,4,39,133,75,133,93,139,94,141,
109,133,113,135,131,137,7,132,8,10,141,29,130,46,135,47,137,62,133,61,137,47,130,46,137,29,133,8,
133,7,133,131,130,113,133,109,133,94,134,75,90,121,151,0,134,55,21,59,133,75,133,93,139,94,137,109,
132,112,113,139,131,133,7,133,8,141,29,130,46,137,47,130,61,133,62,130,63,135,62,133,61,135,47,130,
46,137,29,130,8,133,7,135,131,133,109,133,94,134,59,39,35,149,0,134,68,21,25,133,75,133,93,139,94,
139,109,130,113,139,131,133,7,133,8,141,29,130,46,135,47,130,61,135,62,133,78,137,62,130,61,137,47,
130,46,137,29,130,8,133,7,133,131,132,113,109,133,94,134,41,105,51,147,0,134,67,4,107,133,75,133,93,
139,94,139,109,130,113,139,131,133,7,132,8,10,139,29,130,46,137,47,130,61,133,62,141,78,135,62,130,
61,135,47,130,46,137,29,130,8,133,7,135,131,130,109,133,94,134,5,3,12,145,0,134,66,4,56,133,75,133,
93,139,94,137,109,132,112,113,139,131,133,7,133,8,139,29,130,46,137,47,135,62,143,78,135,62,130,61,
135,47,130,46,137,29,130,8,133,7,135,131,138,113,109,94,5,85,147,0,134,55,21,59,133,75,130,93,139,
94,137,109,133,112,139,131,133,7,133,8,139,29,130,46,135,47,130,61,133,62,135,78,133,96,137,78,137,
62,135,47,130,46,137,29,130,8,133,7,135,131,138,113,109,94,23,86,145,0,134,36,21,127,133,75,130,93,
139,94,139,109,133,113,137,131,133,7,133,8,139,29,130,46,135,47,135,62,133,78,133,96,130,97,133,96,
137,78,135,62,135,47,130,46,135,29,130,8,135,7,135,131,130,112,133,109,134,44,37,34,141,0,134,1,4,
57,133,75,130,93,141,94,137,109,133,113,139,131,133,7,130,8,137,29,133,46,133,47,130,61,133,62,135,
78,138,96,97,98,97,96,137,78,135,62,130,61,133,47,130,46,135,29,132,10,8,133,7,135,131,130,113,133,
109,136,94,75,38,1,141,0,134,105,21,44,133,75,130,93,139,94,139,109,130,113,139,131,130,7,133,8,137,
29,133,46,133,47,132,61,62,135,78,140,96,97,98,114,98,97,133,96,135,78,135,62,135,47,130,46,135,29,
130,8,133,7,135,131,130,113,133,109,135,94,134,41,121,51,137,0,134,54,21,107,133,75,130,93,141,94,
135,109,132,112,113,139,131,133,7,130,8,137,29,130,46,133,47,130,61,133,62,133,78,134,96,97,98,135,
114,134,98,97,96,135,78,130,63,133,62,130,61,133,47,130,46,135,29,130,8,133,7,135,131,130,113,133,
109,135,94,136,93,75,39,16,135,0,136,118,4,39,72,133,75,141,94,137,109,133,113,139,131,132,7,8,137,
29,130,46,133,47,133,62,133,78,133,96,130,98,139,114,134,98,97,96,135,78,135,62,133,47,130,46,135,
29,130,8,133,7,135,131,130,113,133,109,135,94,136,75,72,21,85,137,0,134,55,21,5,133,75,130,93,139,
94,137,109,133,113,139,131,134,7,8,10,135,29,133,47,132,61,62,133,78,133,96,130,98,141,114,134,98,
97,96,135,78,135,62,133,47,130,46,135,29,130,8,133,7,135,131,130,113,133,109,133,94,138,93,75,5,21,
35,137,0,134,101,21,56,135,75,130,93,139,94,135,109,132,112,113,139,131,132,7,8,135,29,136,46,47,61,
62,133,78,133,96,130,98,135,114,133,133,135,114,132,98,96,135,78,135,62,133,47,130,46,135,29,130,8,
133,7,133,131,130,113,133,109,135,94,138,93,75,70,105,12,137,0,136,34,124,21,25,133,75,130,93,137,
94,137,109,132,112,113,139,131,132,7,8,133,29,130,46,133,47,132,62,63,133,78,132,96,98,135,114,130,
133,133,134,130,133,133,114,134,98,97,96,133,78,130,63,133,62,133,47,130,46,135,29,132,8,7,135,131,
130,113,133,109,135,94,136,75,41,21,17,141,0,134,36,21,56,133,75,133,93,137,94,137,109,133,113,135,
131,133,7,130,8,133,29,133,47,133,62,133,78,132,96,97,135,114,133,133,133,134,130,133,133,114,134,
98,97,96,135,78,133,62,133,47,130,46,133,29,134,10,8,7,135,131,130,113,133,109,133,94,138,93,75,90,
4,66,141,0,136,66,4,21,5,133,75,130,93,137,94,137,109,130,113,137,131,133,7,136,8,29,46,47,133,62,
133,78,134,96,97,98,135,114,130,133,137,134,135,114,132,98,96,135,78,133,62,133,47,130,46,133,29,
130,10,133,7,135,131,130,112,133,109,133,94,136,75,59,21,85,145,0,136,68,21,39,72,133,75,130,93,137,
94,135,109,130,113,135,131,133,7,130,8,133,29,134,47,61,62,135,78,132,96,98,135,114,130,133,133,134,
130,11,133,134,130,133,133,114,134,98,97,96,133,78,133,62,133,47,130,46,133,29,130,8,133,7,133,131,
130,113,133,109,133,94,138,93,75,90,21,100,145,0,136,66,4,21,107,133,75,130,93,137,94,135,109,130,
113,135,131,134,7,8,10,133,29,130,47,133,62,133,78,134,96,97,98,135,114,133,134,135,11,133,134,133,
114,130,98,133,96,133,78,133,62,133,47,135,29,132,8,7,135,131,135,109,133,94,136,75,44,21,103,149,0,
130,36,133,21,130,41,133,75,137,94,133,109,130,113,135,131,133,7,130,8,135,29,130,47,133,62,133,78,
132,96,97,135,114,132,133,134,137,11,133,134,135,114,132,97,96,133,78,133,62,133,47,135,29,133,7,
135,131,133,109,133,94,138,93,75,70,4,83,149,0,142,34,105,21,56,72,75,93,135,94,133,109,135,131,133,
7,133,8,135,29,134,47,62,63,133,78,132,96,98,135,114,133,134,137,11,132,135,134,135,114,132,97,96,
133,78,136,62,61,47,46,133,29,132,8,7,135,131,132,113,109,135,94,136,75,25,21,68,153,0,136,84,4,21,
107,133,75,135,94,132,109,112,135,131,133,7,130,8,137,29,130,47,133,62,133,78,132,96,98,133,114,132,
133,134,135,11,130,31,133,11,132,134,133,133,114,138,97,96,78,63,62,133,47,130,46,133,29,132,8,7,
135,131,133,109,133,94,138,93,72,56,105,51,155,0,130,18,133,21,132,25,75,135,94,133,109,130,113,135,
131,132,7,8,135,29,132,46,47,133,62,133,78,132,96,98,133,114,133,134,133,11,133,32,133,11,138,134,
133,114,98,96,133,78,133,62,133,47,130,46,133,29,133,7,133,131,130,113,133,109,133,94,136,75,107,21,
84,157,0,140,82,124,21,39,59,75,133,94,133,109,130,113,135,131,130,7,133,8,133,29,136,46,47,61,62,
133,78,130,96,133,114,138,133,134,135,11,31,133,32,133,11,138,134,133,114,98,96,133,78,133,62,132,
47,46,133,29,132,8,7,133,131,130,113,133,109,133,94,136,75,25,21,3,161,0,130,101,133,21,134,70,72,
93,133,94,133,109,130,113,133,131,133,7,135,29,142,46,47,61,62,78,96,97,133,114,132,133,134,133,11,
135,32,133,11,138,134,133,114,98,96,133,78,136,62,61,47,46,133,29,132,8,7,133,131,133,109,133,94,
138,75,59,39,124,66,163,0,138,121,21,39,125,75,133,94,133,109,130,110,133,131,133,7,130,8,133,29,
142,46,47,61,62,78,96,97,133,114,133,134,138,11,31,32,49,32,133,11,130,134,133,114,138,98,96,78,63,
62,133,47,133,29,132,8,7,133,131,130,113,133,109,133,94,136,72,57,21,84,165,0,140,51,87,21,39,25,75,
133,94,133,109,135,131,132,7,8,133,29,136,46,47,61,62,133,78,130,98,133,114,130,134,133,11,133,32,
138,50,32,31,11,134,133,114,130,97,133,78,134,62,61,47,133,29,132,8,7,135,131,133,109,133,94,136,72,
71,21,121,169,0,140,14,4,39,56,59,75,133,94,132,109,113,133,131,132,7,8,133,29,136,46,47,61,62,133,
78,130,98,133,114,130,134,133,11,130,32,133,50,130,32,133,11,136,134,114,98,96,133,78,134,62,47,46,
133,29,133,7,133,131,133,109,133,94,138,72,89,21,87,51,171,0,142,2,21,39,70,59,93,94,133,109,130,
113,133,131,132,7,8,133,29,134,47,61,62,133,78,130,98,137,114,130,133,137,134,135,114,133,98,138,96,
78,62,61,47,133,29,132,8,7,133,131,133,109,133,94,138,72,89,39,4,1,175,0,138,85,21,39,89,72,133,94,
133,109,133,131,132,7,8,133,29,133,47,133,62,130,78,135,62,135,61,137,62,137,61,135,62,132,61,47,
133,29,132,8,7,133,131,133,109,142,94,93,44,71,39,21,120,177,0,140,13,18,21,39,89,72,133,94,132,109,
110,133,131,132,7,8,139,29,130,8,133,7,136,47,62,78,96,133,78,136,63,61,47,8,133,131,134,7,8,10,135,
29,138,8,7,131,113,109,133,94,140,75,5,56,39,21,68,181,0,140,34,18,21,39,89,59,133,94,132,109,113,
141,131,133,109,138,8,30,48,45,28,133,9,133,130,134,111,130,9,133,28,130,129,135,109,130,113,133,
131,133,113,133,109,144,94,75,41,89,56,39,21,86,185,0,142,34,3,21,39,71,42,93,135,94,130,109,137,94,
146,95,110,92,58,39,103,101,119,52,133,34,140,82,15,16,55,108,43,133,74,132,73,91,137,94,146,75,59,
23,107,71,56,39,21,54,189,0,148,12,36,21,39,56,125,42,72,75,72,133,59,140,43,40,6,56,68,83,151,0,
164,12,53,37,106,6,24,40,42,24,6,126,108,89,71,56,39,124,67,195,0,140,1,55,39,56,71,89,135,108,138,
106,89,55,84,12,161,0,138,66,36,124,71,89,133,106,142,89,71,56,39,4,68,52,201,0,134,14,68,69,133,21,
136,87,121,120,82,173,0,146,100,2,103,37,69,37,85,84,51,163,0,
};
// clang-format on

static const image_descriptor gfx_mac_raw = {
  .width = 78,
  .height = 96,
  .byte_count = 4757,
  .compression = image_compression::PAL_NQRLE,
  .image_data = gfx_mac_data}; // 3.1482 compression rate

const image_descriptor* gfx_mac = &gfx_mac_raw;
