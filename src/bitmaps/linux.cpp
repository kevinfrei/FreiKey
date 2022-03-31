#include "bitmap.h"

// clang-format off
static const uint8_t gfx_linux_data[] = {
203,1,0,0,8,0,57,0,255,0,254,1,49,2,57,2,254,2,254,3,33,4,106,4,254,4,254,5,163,6,171,6,245,6,254,6,
212,7,220,7,245,7,254,7,66,8,212,8,220,8,245,8,254,8,196,9,245,9,254,9,254,10,99,11,246,11,254,11,
99,12,156,12,237,12,246,12,246,13,148,14,246,14,132,15,246,15,132,16,246,16,246,17,238,18,246,18,
157,19,165,20,238,20,198,22,198,23,198,24,239,26,247,26,223,27,231,27,239,27,231,28,0,32,8,32,57,32,
65,32,254,32,8,33,254,33,57,34,254,34,246,35,254,35,33,36,114,36,41,37,98,37,245,37,171,38,245,38,
220,39,245,39,66,40,74,40,220,40,245,40,74,41,237,41,245,41,196,42,245,43,99,44,107,44,107,45,172,
45,245,45,246,47,132,48,140,48,197,48,246,48,132,49,246,49,254,50,173,51,246,51,165,52,173,52,246,
52,206,55,198,56,206,56,239,58,247,58,231,59,239,59,247,59,231,60,8,64,16,64,65,64,73,64,254,64,8,
65,16,65,254,65,65,66,254,66,57,67,73,67,114,68,122,68,245,68,41,69,245,69,171,70,179,70,245,70,179,
71,212,71,220,71,245,71,90,72,228,72,245,72,74,73,220,73,245,73,245,74,245,76,107,77,237,77,245,78,
140,80,213,80,140,81,246,81,246,82,254,82,246,83,173,84,181,84,173,85,246,85,206,88,214,88,206,89,
255,90,247,91,255,91,231,92,239,92,239,93,16,96,254,96,8,97,16,97,24,97,254,97,16,98,254,98,73,99,
122,100,245,100,41,101,49,101,122,101,130,101,245,101,49,102,245,102,98,103,179,103,187,103,212,103,
228,103,220,104,228,104,236,104,245,104,74,105,82,105,236,105,131,106,204,106,245,106,245,107,107,
109,115,109,245,110,245,111,140,113,148,113,246,115,254,115,181,116,254,116,173,117,181,117,214,120,
206,121,214,121,239,124,247,124,239,125,247,125,24,128,81,128,254,128,24,129,32,129,254,129,16,130,
254,130,81,131,245,131,245,132,130,133,138,133,245,133,49,134,220,134,187,135,195,135,212,135,228,
135,236,135,245,135,236,136,244,136,245,136,74,137,82,137,236,137,245,137,82,138,245,138,139,139,
245,139,245,140,115,142,180,142,164,144,245,144,148,145,148,146,254,148,254,149,181,150,238,150,246,
151,214,153,206,154,214,154,239,157,247,157,239,158,247,158,40,160,89,160,254,160,32,161,254,161,16,
162,24,162,24,163,81,163,89,163,245,163,73,164,245,164,138,165,146,165,245,165,49,166,57,166,187,
166,245,166,57,167,195,167,236,167,245,167,236,168,244,168,245,168,90,169,98,169,245,169,82,170,90,
170,236,170,245,170,90,171,139,171,245,171,245,172,245,173,115,174,123,174,245,176,237,177,245,177,
148,178,156,178,189,181,254,181,181,182,189,182,254,182,246,183,238,184,246,184,214,185,222,185,230,
185,214,186,222,186,247,189,247,190,40,192,254,192,32,193,40,193,254,193,24,194,32,194,245,194,253,
194,24,195,89,195,245,195,253,195,97,196,245,196,253,196,146,197,154,197,253,197,154,198,228,198,
245,198,57,199,195,199,203,199,236,199,244,199,245,199,203,200,236,200,244,200,245,201,90,202,245,
202,90,203,245,203,245,204,245,205,123,206,245,206,123,207,245,207,245,209,148,210,156,210,156,211,
197,213,181,214,189,214,197,214,254,214,189,215,246,215,254,215,246,216,238,217,222,218,230,218,222,
219,48,224,254,224,253,225,254,225,48,226,253,226,24,227,32,227,253,227,32,228,97,228,105,228,245,
228,253,228,253,229,236,230,253,230,57,231,65,231,203,231,211,231,236,231,244,231,245,231,253,231,
65,232,211,232,244,232,245,232,253,232,245,233,253,233,245,234,90,235,98,235,163,235,236,235,98,236,
236,236,245,236,245,237,245,238,123,239,131,239,245,239,245,240,164,242,245,242,156,243,164,243,237,
243,197,246,205,246,189,247,197,247,254,247,189,248,254,248,230,249,222,250,230,250,238,250,222,251,
230,251,3,131,0,0,144,59,18,56,130,61,41,132,163,4,11,129,0,0,134,89,153,37,4,143,217,0,134,214,88,
227,1,1,129,0,0,134,120,178,12,6,151,52,0,132,103,4,1,253,0,0,132,229,12,2,157,67,1,132,214,4,1,249,
0,0,132,172,160,1,161,159,0,132,63,129,0,247,0,0,130,90,0,165,187,1,130,156,1,245,0,0,130,146,1,137,
6,1,159,208,0,130,172,1,245,0,0,130,142,0,167,42,0,130,33,0,245,0,0,130,49,1,153,58,1,130,1,1,135,
58,1,136,1,117,6,44,6,245,0,0,130,197,0,167,88,0,130,130,0,245,0,0,132,237,100,2,133,49,1,130,50,1,
157,49,1,132,197,120,0,245,0,0,132,176,166,0,133,79,0,130,83,0,151,79,0,130,21,0,133,79,0,130,26,1,
249,0,0,136,148,219,153,29,9,143,237,0,132,156,161,1,133,67,1,134,152,204,102,5,251,0,0,138,120,196,
208,24,26,19,135,89,1,133,26,1,132,130,254,2,137,163,0,132,9,51,2,251,0,0,130,1,1,135,217,0,132,163,
218,1,137,0,0,130,123,1,141,217,0,130,208,0,249,0,0,132,176,214,0,137,12,1,130,187,1,135,0,0,140,70,
152,58,12,229,101,40,135,14,1,130,145,1,247,0,0,144,35,17,103,43,136,166,169,182,114,133,0,0,130,
173,1,133,77,1,142,94,250,214,10,222,20,177,92,247,0,0,144,142,142,99,130,6,155,225,241,118,133,0,0,
148,120,143,119,10,136,247,228,206,196,199,117,2,247,0,0,154,21,114,132,40,54,178,76,13,94,231,100,
153,168,241,5,133,21,0,138,26,101,214,64,174,19,247,0,0,134,148,107,52,3,133,60,0,136,91,94,183,53,
13,133,110,1,146,175,93,231,217,1,160,89,13,55,249,0,247,0,0,168,59,130,6,198,3,182,109,78,105,66,
167,229,196,96,218,243,185,60,65,75,33,47,7,249,0,0,138,157,109,36,51,125,27,139,8,1,144,154,150,97,
48,29,140,39,97,219,251,0,0,136,66,130,49,57,1,141,153,0,134,154,50,209,4,133,134,0,136,76,66,19,
114,5,247,0,0,136,90,211,230,98,7,147,37,0,130,111,1,137,236,0,132,185,74,2,245,0,0,134,116,220,125,
4,133,91,1,132,153,51,0,141,28,0,132,163,189,2,135,91,1,136,180,182,50,153,10,243,0,0,136,226,148,
92,29,4,135,4,0,139,67,0,137,4,0,133,180,0,136,141,131,12,178,8,243,0,0,140,1,74,6,33,16,232,7,145,
119,0,134,29,105,17,0,133,119,0,132,65,74,2,247,0,0,132,143,201,2,133,175,0,132,233,38,3,135,225,0,
138,21,195,77,78,119,0,135,225,0,134,122,54,12,4,249,0,0,138,30,175,12,137,202,7,139,31,1,130,124,0,
135,81,1,140,228,62,82,58,170,20,15,247,0,0,136,21,106,232,253,8,145,3,0,138,23,13,17,52,140,10,133,
53,0,130,102,1,247,0,0,140,30,224,56,5,181,203,49,137,3,0,136,140,189,58,179,1,135,16,1,134,57,144,
127,1,247,0,0,132,95,188,1,133,16,1,134,134,37,229,2,133,151,1,134,185,36,45,4,139,16,1,136,168,142,
171,193,3,245,0,0,130,68,1,139,16,1,136,113,144,26,142,3,143,16,1,130,220,0,133,199,1,130,102,1,243,
0,0,132,89,17,3,161,219,0,130,168,0,133,199,1,130,209,0,143,0,0,132,197,34,3,225,0,0,132,49,19,3,
161,168,0,130,112,0,133,136,1,132,218,202,1,141,0,0,134,25,161,225,1,213,0,0,130,130,0,137,0,0,134,
124,17,227,0,135,112,0,135,111,0,132,112,222,0,137,112,0,135,111,0,130,56,0,135,136,1,130,50,1,143,
0,0,132,33,2,2,211,0,0,132,164,117,2,135,0,0,132,24,181,1,133,136,1,155,56,0,132,202,113,0,137,136,
1,130,157,0,143,0,0,134,229,118,63,1,207,0,0,134,181,62,81,6,135,0,0,130,50,1,135,77,1,130,136,1,
143,201,1,132,198,17,3,133,198,1,135,136,1,139,77,1,130,182,0,143,0,0,134,252,250,82,6,203,0,0,134,
26,119,135,0,137,0,0,130,157,0,175,77,1,130,150,0,143,0,0,136,120,48,169,192,3,199,0,0,136,64,84,
252,108,5,135,0,0,132,181,28,2,133,76,1,130,14,1,169,76,1,132,163,52,2,133,0,0,132,21,96,1,135,0,0,
134,164,127,202,5,199,0,0,136,53,97,152,221,1,135,0,0,130,42,0,135,14,1,130,12,1,133,14,1,134,76,
147,227,0,137,114,0,136,58,146,51,117,8,135,12,1,130,14,1,135,12,1,132,14,39,1,133,0,0,134,26,189,
176,2,133,0,0,136,64,240,66,179,5,195,0,0,138,130,250,50,43,87,12,133,0,0,132,25,71,1,135,12,1,134,
14,113,116,3,149,79,1,134,221,112,56,4,141,12,1,132,51,88,1,133,0,0,134,145,107,239,0,133,0,0,136,
186,48,213,102,5,191,0,0,140,120,84,64,203,200,12,22,133,0,0,130,147,0,135,12,1,132,58,36,2,159,79,
1,132,58,28,2,139,12,1,130,176,1,135,0,0,132,156,67,0,135,0,0,134,147,84,196,4,191,0,0,138,197,12,
86,16,20,2,133,0,0,138,120,128,103,99,218,13,143,79,1,132,18,159,2,145,18,1,134,79,187,49,5,137,217,
0,132,192,89,1,135,0,0,132,120,5,1,133,0,0,130,72,0,133,181,1,130,9,0,187,0,0,140,24,189,232,196,
163,2,22,133,0,0,140,53,179,49,237,22,241,33,133,17,1,130,15,1,159,17,1,132,221,152,2,137,217,0,130,
89,0,135,0,0,134,26,13,238,0,133,0,0,134,33,116,182,6,187,0,0,138,114,189,232,34,201,26,133,0,0,134,
60,18,102,3,177,221,0,130,13,1,135,163,0,132,195,97,1,135,0,0,132,1,159,0,133,0,0,130,237,0,133,204,
0,130,70,0,183,0,0,140,89,107,51,227,129,169,28,133,0,0,134,83,70,233,0,177,221,0,130,114,0,137,163,
0,130,33,0,135,0,0,132,146,95,0,133,0,0,136,120,176,104,225,7,183,0,0,138,252,240,154,21,132,23,135,
0,0,132,103,28,2,181,169,0,130,14,1,135,163,0,132,67,129,0,135,0,0,132,125,219,1,133,0,0,130,142,0,
133,33,0,130,25,1,179,0,0,140,172,2,234,132,133,183,29,133,0,0,134,35,179,41,6,181,167,0,130,201,1,
137,217,0,130,142,0,135,0,0,132,33,116,2,133,0,0,130,181,0,133,114,1,130,35,1,179,0,0,140,35,153,
201,197,243,9,15,133,0,0,134,152,178,221,0,157,167,0,130,114,0,133,167,0,136,114,78,201,57,5,133,
114,0,130,167,0,133,114,0,130,58,0,135,217,0,132,218,246,2,135,0,0,132,35,135,2,133,0,0,130,26,1,
133,49,1,130,142,0,179,0,0,138,49,181,112,62,185,23,133,0,0,136,176,214,104,187,1,181,114,0,134,56,
24,106,3,135,217,0,130,26,1,133,0,0,138,145,179,105,4,128,7,135,142,0,130,176,0,175,0,0,130,173,0,
133,33,0,134,130,152,233,4,133,0,0,136,80,28,50,76,14,181,114,0,130,201,1,137,12,1,132,14,101,2,133,
0,0,138,24,71,141,4,176,3,135,21,0,130,89,1,175,0,0,130,9,0,133,172,1,134,89,127,98,1,133,0,0,130,
94,0,133,12,1,130,138,1,135,58,0,138,114,116,200,209,33,7,135,58,0,130,114,0,133,58,0,130,114,0,149,
58,0,136,114,20,51,116,8,135,12,1,130,63,1,133,0,0,134,89,179,57,2,133,0,0,130,35,1,133,102,1,130,9,
0,175,0,0,130,237,0,133,49,1,140,24,19,134,0,192,3,48,133,76,1,132,136,117,0,179,56,0,130,77,1,139,
76,1,140,107,240,0,168,149,205,24,133,0,0,130,181,0,133,237,0,130,9,0,175,0,0,144,39,139,225,211,8,
60,32,128,172,135,76,1,130,77,1,179,56,0,132,202,155,2,135,76,1,150,77,153,54,21,4,128,117,182,10,0,
118,36,0,133,70,0,130,145,1,175,0,0,130,35,1,133,79,0,140,145,1,255,4,192,25,49,135,77,1,130,198,1,
177,56,0,130,136,1,143,77,1,142,215,160,37,116,152,0,0,15,135,26,1,130,229,0,175,0,0,130,237,0,133,
164,1,138,70,120,175,97,213,26,139,136,1,135,202,1,133,56,0,137,202,1,133,56,0,135,202,1,130,56,0,
143,202,1,132,56,148,3,143,136,1,130,12,1,133,215,0,138,161,16,3,181,181,3,133,64,0,132,120,128,0,
175,0,0,130,130,0,133,36,1,138,182,152,53,229,183,19,139,136,1,130,199,1,173,202,1,143,136,1,148,
215,140,156,20,84,206,44,166,164,208,50,2,181,0,0,130,145,1,137,181,0,134,74,1,71,3,141,136,1,130,
199,1,135,202,1,130,199,1,157,202,1,133,199,1,130,137,1,141,136,1,134,199,73,254,4,133,214,0,142,48,
88,195,138,28,141,77,59,179,0,0,130,173,0,135,9,0,136,89,45,33,110,10,197,199,1,138,218,106,253,52,
248,19,133,6,1,140,208,106,1,112,196,70,50,175,0,0,146,83,65,190,235,117,203,106,86,192,137,1,195,
199,1,134,49,52,8,2,137,181,1,135,120,1,136,120,0,100,177,11,173,0,0,134,5,24,177,4,133,110,1,138,
245,46,200,162,236,27,193,199,1,136,189,143,33,202,10,133,33,0,135,176,1,140,173,67,176,2,208,46,26,
171,0,0,152,227,208,154,94,134,251,110,21,183,140,100,97,228,11,135,199,1,183,200,1,140,71,245,153,
166,82,142,51,139,21,0,130,130,0,133,0,0,136,73,172,168,155,10,165,0,0,138,60,8,185,5,40,28,133,196,
1,144,69,151,185,141,50,21,64,49,81,137,200,1,135,53,0,133,200,1,130,53,0,135,200,1,130,53,0,133,
200,1,135,53,0,130,200,1,137,53,0,135,200,1,146,53,122,214,147,162,105,17,30,141,25,1,133,24,1,130,
229,0,133,0,0,140,82,127,185,101,201,232,8,163,0,0,136,128,86,86,17,10,137,133,1,148,69,35,177,236,
197,3,64,198,220,53,144,3,179,53,0,140,177,77,231,228,4,6,15,141,0,0,132,125,226,1,137,24,0,132,245,
56,2,157,0,0,138,60,0,213,195,192,2,133,130,1,137,69,1,136,154,48,232,171,12,133,0,0,134,59,152,33,
7,177,53,0,136,135,245,97,88,1,133,100,0,132,34,240,0,135,0,0,136,85,109,154,201,11,133,24,0,138,78,
20,49,65,203,3,151,0,0,140,6,64,90,96,137,225,54,139,69,1,135,66,1,136,0,77,95,160,3,135,0,0,132,
249,18,3,133,53,0,145,110,0,130,109,0,153,110,0,134,10,135,73,1,133,44,0,133,99,0,140,151,252,33,19,
216,130,12,133,155,0,132,202,156,0,133,134,0,134,187,88,62,6,147,0,0,144,22,11,213,115,139,1,146,38,
161,141,8,1,133,7,1,136,155,48,212,155,5,137,0,0,134,142,106,180,1,171,110,0,134,105,234,65,2,143,
43,0,133,44,0,135,99,0,142,55,13,237,202,197,238,129,2,145,0,0,134,173,74,187,5,133,24,0,132,85,166,
1,143,7,1,137,213,0,136,203,76,51,162,3,137,0,0,132,89,226,0,171,110,0,134,189,87,70,2,145,183,1,
132,43,82,0,133,93,0,134,52,115,177,3,133,233,0,132,185,150,0,145,0,0,132,179,88,2,135,24,0,130,119,
1,135,213,0,139,211,0,130,210,0,135,156,0,136,43,48,232,251,3,137,0,0,132,59,60,1,171,110,0,136,62,
89,70,170,11,143,119,1,130,180,1,135,39,0,144,42,217,165,251,184,149,107,148,60,143,0,0,130,239,0,
137,24,0,130,183,1,143,156,0,137,154,0,133,155,0,136,145,76,71,105,5,137,0,0,134,36,75,197,1,167,
165,0,134,4,221,70,2,139,57,1,135,117,1,130,179,1,133,37,0,130,31,0,133,31,1,140,91,185,78,62,240,
160,50,143,0,0,130,240,0,135,78,0,140,24,0,106,218,164,105,19,141,100,0,135,99,0,136,183,49,172,4,
11,137,0,0,132,64,176,1,167,165,0,136,166,158,185,133,4,137,0,1,130,56,1,133,116,1,133,178,1,152,36,
64,136,222,202,117,50,100,2,65,26,39,50,0,141,0,0,132,132,152,0,135,134,0,132,78,86,0,141,99,0,137,
44,0,135,43,0,136,0,49,232,219,8,137,0,0,130,191,1,157,165,0,137,166,0,144,165,76,113,113,11,73,217,
191,126,133,52,1,133,113,1,133,171,1,133,28,0,138,95,39,67,38,16,4,133,63,0,136,119,176,162,117,5,
139,0,0,134,234,152,176,3,133,185,0,136,187,136,165,8,3,141,43,0,130,184,1,139,183,1,136,145,76,51,
122,12,133,0,0,132,35,221,0,167,166,0,138,164,102,98,104,4,9,133,251,0,133,48,1,133,111,1,142,167,
81,103,200,12,249,0,1,133,63,0,133,119,0,136,171,194,165,27,11,139,0,0,134,150,31,124,4,133,233,0,
133,236,0,130,244,0,133,39,0,134,41,110,211,6,133,183,1,135,121,1,137,119,1,140,85,220,162,117,137,
162,56,169,166,0,134,132,235,57,1,133,196,0,132,247,232,1,133,42,1,130,101,1,133,155,1,136,16,24,28,
32,0,135,63,0,130,119,0,133,171,0,130,225,0,133,21,1,132,41,167,2,137,0,0,138,178,30,76,230,186,21,
133,31,1,134,233,76,146,0,135,37,0,133,179,1,135,117,1,137,57,1,136,0,49,172,172,4,173,166,0,138,46,
88,26,218,149,11,133,236,0,142,34,197,126,197,188,0,1,1,135,63,0,130,119,0,133,171,0,130,225,0,133,
21,1,133,81,1,132,233,20,0,137,0,0,138,231,148,16,56,0,25,133,147,1,130,91,1,133,31,1,132,169,73,0,
135,178,1,137,116,1,133,56,1,133,0,1,136,145,48,212,211,13,169,166,0,138,165,70,76,200,197,14,133,
233,0,142,31,183,114,157,124,128,64,16,133,63,0,133,119,0,132,171,194,1,133,21,1,133,81,1,133,140,1,
132,233,44,3,137,0,0,132,97,59,2,135,63,0,144,65,8,28,128,60,153,235,102,14,133,29,0,133,171,1,133,
115,1,135,55,1,133,255,0,136,82,48,232,51,10,165,166,0,138,216,94,50,202,149,14,133,31,1,130,91,1,
133,147,1,132,7,8,0,135,63,0,133,119,0,132,171,194,1,133,21,1,133,81,1,133,140,1,136,3,204,53,177,8,
135,0,0,136,60,36,232,89,5,135,119,0,135,63,0,146,4,14,64,158,12,33,131,106,212,169,1,133,111,1,137,
48,1,138,196,20,153,126,148,27,157,165,0,154,166,150,238,108,181,145,101,186,143,91,185,78,62,64,0,
135,63,0,133,119,0,132,171,194,1,133,21,1,133,81,1,137,140,1,134,31,63,63,6,137,0,0,132,143,211,2,
133,21,1,133,225,0,133,171,0,133,119,0,135,63,0,133,4,0,136,8,24,64,160,0,133,163,1,133,107,1,133,
45,1,144,244,118,25,98,89,121,100,110,228,147,165,0,136,110,252,134,40,7,133,0,0,142,96,31,108,229,
58,249,0,1,135,63,0,133,119,0,132,171,194,1,133,21,1,135,81,1,135,140,1,136,94,129,173,115,5,139,0,
0,134,126,152,48,6,135,81,1,133,21,1,130,225,0,133,171,0,133,119,0,135,63,0,134,65,14,32,0,133,11,0,
132,12,50,3,133,98,1,138,34,211,177,99,130,18,133,0,0,152,26,243,125,241,36,67,141,12,106,150,224,
38,216,1,137,0,0,138,103,105,77,62,64,0,135,63,0,133,119,0,130,171,0,133,225,0,130,21,1,133,81,1,
137,140,1,136,94,129,173,27,7,143,0,0,134,143,53,15,0,135,140,1,135,81,1,133,21,1,133,225,0,133,171,
0,133,119,0,133,63,0,133,65,0,133,7,0,133,147,1,140,92,183,126,76,55,204,21,141,0,0,130,59,0,147,0,
0,136,116,24,113,37,0,135,63,0,133,119,0,130,171,0,133,225,0,130,21,1,133,81,1,135,140,1,138,3,136,
0,91,55,14,147,0,0,134,60,80,22,1,135,3,0,135,140,1,135,81,1,135,21,1,130,225,0,133,171,0,133,119,0,
135,63,0,130,65,0,133,4,0,138,144,39,115,181,55,21,161,0,0,134,226,134,17,0,133,63,0,133,119,0,130,
171,0,133,225,0,130,21,1,135,81,1,133,140,1,138,3,24,27,42,52,21,153,0,0,140,83,81,62,184,28,139,42,
135,3,0,135,140,1,135,81,1,133,21,1,133,225,0,130,171,0,135,119,0,135,63,0,136,4,32,31,107,5,161,0,
0,134,227,234,253,0,133,119,0,133,171,0,132,225,42,2,135,81,1,133,140,1,133,3,0,136,81,65,223,226,1,
157,0,0,150,60,132,220,114,192,54,138,218,7,185,46,155,3,137,140,1,135,81,1,133,21,1,130,225,0,133,
171,0,133,119,0,134,63,208,161,4,133,0,0,140,1,84,65,21,80,7,28,133,20,1,136,224,124,44,86,5,133,0,
0,136,60,232,92,32,0,133,171,0,132,225,42,2,135,81,1,133,140,1,135,3,0,134,140,65,43,0,173,0,0,146,
174,30,115,196,117,104,30,59,170,3,0,135,140,1,135,81,1,133,21,1,133,225,0,134,171,82,238,1,135,0,0,
134,223,160,246,0,135,118,0,138,62,22,79,84,53,7,137,0,0,136,33,105,133,171,8,135,81,1,133,140,1,
137,3,0,134,140,31,0,2,185,0,0,138,174,142,92,200,101,14,133,3,0,135,140,1,135,81,1,134,228,30,132,
4,167,0,0,134,227,154,240,1,133,81,1,133,140,1,139,3,0,134,23,65,3,2,191,0,0,154,116,42,195,75,203,
174,8,185,139,228,134,176,19,118,4,171,0,0,136,231,82,198,98,12,139,3,0,136,140,47,51,226,8,199,0,0,
146,83,187,134,45,132,214,87,131,202,226,0,175,0,0,150,178,34,176,139,117,145,106,172,143,242,194,
90,4,11,129,0,0,134,121,44,47,1,133,190,0,134,75,20,88,4,31,133,0,0,
};
// clang-format on

static const image_descriptor gfx_linux_raw = {
  .width = 79,
  .height = 96,
  .byte_count = 5103,
  .compression = image_compression::PAL_NQRLE,
  .image_data = gfx_linux_data}; // 2.97237 compression rate

const image_descriptor* gfx_linux = &gfx_linux_raw;
