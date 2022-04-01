#include "bitmap.h"

// clang-format off
uint8_t gfx_batman_data[] = {
18,3,0,0,8,0,16,0,24,0,32,0,40,0,48,0,57,0,65,0,82,0,115,0,138,0,146,0,154,0,155,0,163,0,171,0,188,
0,205,0,213,0,230,0,238,0,246,0,255,0,0,1,8,1,65,1,73,1,81,1,82,1,90,1,115,1,130,1,138,1,146,1,155,
1,163,1,171,1,180,1,188,1,205,1,213,1,238,1,246,1,82,2,98,2,115,2,122,2,123,2,130,2,138,2,155,2,156,
2,164,2,180,2,188,2,205,2,213,2,246,2,98,3,106,3,114,3,115,3,122,3,123,3,130,3,131,3,138,3,147,3,
155,3,180,3,188,3,197,3,205,3,230,3,238,3,106,4,114,4,115,4,122,4,156,4,164,4,172,4,197,4,205,4,230,
4,238,4,114,5,139,5,147,5,148,5,155,5,156,5,164,5,189,5,197,5,205,5,230,5,156,6,164,6,172,6,189,6,
197,6,205,6,230,6,156,7,189,7,197,7,164,8,181,8,189,8,0,32,8,32,16,32,24,32,32,32,40,32,48,32,49,32,
65,32,89,32,90,32,146,32,154,32,163,32,171,32,188,32,196,32,213,32,238,32,246,32,73,33,81,33,82,33,
89,33,90,33,123,33,138,33,146,33,154,33,155,33,163,33,171,33,188,33,196,33,205,33,213,33,238,33,246,
33,90,34,98,34,122,34,123,34,130,34,138,34,155,34,163,34,164,34,205,34,213,34,230,34,238,34,122,35,
123,35,130,35,138,35,164,35,180,35,188,35,205,35,213,35,230,35,106,36,114,36,122,36,130,36,131,36,
138,36,155,36,156,36,164,36,180,36,205,36,213,36,114,37,122,37,131,37,156,37,164,37,188,37,197,37,
205,37,230,37,238,37,123,38,164,38,172,38,189,38,197,38,205,38,222,38,230,38,164,39,189,39,197,39,
230,39,197,40,230,40,230,41,222,42,16,64,24,64,32,64,40,64,48,64,56,64,64,64,65,64,90,64,123,64,131,
64,146,64,154,64,163,64,171,64,180,64,188,64,196,64,213,64,221,64,238,64,246,64,57,65,81,65,89,65,
97,65,123,65,138,65,146,65,154,65,155,65,163,65,171,65,179,65,188,65,196,65,213,65,221,65,238,65,
246,65,81,66,89,66,90,66,98,66,131,66,138,66,146,66,155,66,163,66,188,66,196,66,213,66,221,66,238,
66,246,66,106,67,115,67,123,67,130,67,131,67,138,67,146,67,147,67,155,67,163,67,164,67,188,67,238,
67,114,68,122,68,130,68,131,68,147,68,155,68,180,68,188,68,205,68,213,68,114,69,122,69,130,69,131,
69,139,69,147,69,148,69,164,69,172,69,180,69,205,69,213,69,230,69,238,69,172,70,197,70,205,70,230,
70,238,70,164,71,172,71,197,71,230,71,238,71,172,72,230,72,222,73,230,73,189,74,222,74,24,96,32,96,
40,96,48,96,56,96,73,96,81,96,114,96,121,96,146,96,154,96,162,96,171,96,179,96,196,96,204,96,213,96,
221,96,229,96,246,96,254,96,65,97,73,97,81,97,98,97,123,97,146,97,154,97,163,97,171,97,179,97,196,
97,213,97,221,97,246,97,106,98,138,98,146,98,163,98,213,98,221,98,246,98,81,99,89,99,106,99,114,99,
131,99,138,99,146,99,163,99,171,99,188,99,213,99,221,99,114,100,122,100,130,100,138,100,155,100,156,
100,163,100,188,100,213,100,221,100,238,100,246,100,122,101,130,101,131,101,139,101,155,101,156,101,
164,101,172,101,205,101,213,101,238,101,139,102,155,102,172,102,180,102,188,102,205,102,213,102,238,
102,246,102,164,103,172,103,180,103,205,103,238,103,197,104,205,104,230,104,238,104,197,106,24,128,
32,128,40,128,48,128,56,128,64,128,72,128,81,128,97,128,139,128,154,128,162,128,171,128,179,128,196,
128,204,128,221,128,229,128,246,128,254,128,98,129,106,129,138,129,154,129,163,129,171,129,179,129,
196,129,204,129,221,129,229,129,246,129,254,129,81,130,105,130,131,130,138,130,146,130,163,130,171,
130,188,130,196,130,221,130,246,130,254,130,98,131,130,131,131,131,138,131,146,131,163,131,180,131,
196,131,213,131,221,131,246,131,106,132,114,132,130,132,138,132,146,132,163,132,172,132,188,132,213,
132,221,132,246,132,114,133,122,133,130,133,138,133,155,133,164,133,171,133,180,133,188,133,205,133,
213,133,139,134,147,134,164,134,172,134,205,134,213,134,246,134,155,135,163,135,172,135,205,135,213,
135,230,135,238,135,197,138,40,160,48,160,56,160,64,160,65,160,73,160,80,160,81,160,114,160,129,160,
137,160,146,160,154,160,162,160,179,160,204,160,221,160,229,160,237,160,254,160,56,161,81,161,129,
161,154,161,162,161,171,161,179,161,196,161,204,161,221,161,229,161,254,161,73,162,98,162,106,162,
131,162,138,162,146,162,147,162,154,162,171,162,179,162,188,162,196,162,221,162,229,162,89,163,97,
163,114,163,122,163,146,163,147,163,171,163,180,163,188,163,196,163,221,163,246,163,89,164,106,164,
114,164,122,164,130,164,138,164,139,164,146,164,163,164,171,164,188,164,196,164,204,164,213,164,221,
164,246,164,130,165,138,165,139,165,163,165,180,165,188,165,196,165,213,165,221,165,246,165,139,166,
147,166,163,166,164,166,180,166,188,166,213,166,238,166,139,167,155,167,180,167,188,167,205,167,197,
168,238,168,180,169,238,169,48,192,64,192,72,192,73,192,81,192,106,192,137,192,145,192,154,192,162,
192,179,192,187,192,196,192,204,192,212,192,229,192,237,192,254,192,64,193,73,193,81,193,89,193,106,
193,114,193,129,193,137,193,146,193,154,193,162,193,179,193,187,193,196,193,204,193,212,193,229,193,
237,193,254,193,98,194,105,194,113,194,114,194,154,194,163,194,171,194,196,194,221,194,229,194,237,
194,246,194,97,195,139,195,146,195,171,195,196,195,221,195,246,195,105,196,122,196,139,196,146,196,
147,196,171,196,179,196,188,196,196,196,221,196,254,196,114,197,122,197,130,197,139,197,146,197,147,
197,180,197,221,197,254,197,114,198,155,198,163,198,171,198,188,198,196,198,229,198,254,198,188,199,
221,199,238,199,180,200,188,200,213,201,48,224,56,224,64,224,73,224,80,224,81,224,105,224,137,224,
145,224,146,224,162,224,163,224,170,224,179,224,187,224,196,224,204,224,212,224,229,224,237,224,254,
224,81,225,129,225,137,225,145,225,154,225,162,225,179,225,187,225,196,225,204,225,212,225,229,225,
237,225,254,225,81,226,121,226,122,226,129,226,137,226,154,226,179,226,196,226,204,226,212,226,229,
226,237,226,254,226,97,227,105,227,106,227,114,227,121,227,122,227,146,227,196,227,204,227,229,227,
114,228,122,228,139,228,146,228,147,228,196,228,204,228,237,228,122,229,130,229,138,229,147,229,155,
229,163,229,171,229,196,229,229,229,138,230,147,230,163,230,171,230,188,230,196,230,163,231,196,231,
204,231,221,231,155,232,180,233,213,234,193,0,0,139,1,0,130,113,0,133,2,0,150,159,209,25,214,183,
108,113,138,239,46,39,25,118,18,135,134,1,144,39,65,129,239,142,13,33,218,193,126,133,2,0,130,1,0,
133,112,0,132,1,192,1,135,1,0,247,0,0,133,1,0,133,2,0,148,114,100,131,104,136,166,68,151,47,21,182,
124,4,137,124,1,134,125,125,39,23,133,212,1,130,67,2,135,212,1,133,51,2,150,67,54,233,93,98,42,77,1,
35,13,136,252,42,7,133,113,0,133,1,0,235,0,0,137,1,0,150,2,196,193,66,70,188,76,57,48,21,170,124,
114,15,133,228,0,130,229,0,137,79,1,141,175,1,147,12,2,130,25,2,133,130,2,146,142,90,218,100,100,
198,76,249,239,114,114,0,133,2,0,133,1,0,130,112,0,221,0,0,133,1,0,156,2,200,1,166,16,81,252,152,47,
21,73,224,144,131,36,128,148,3,133,247,0,133,79,1,139,175,1,135,12,2,133,13,2,137,112,2,132,111,14,
10,137,112,2,133,111,2,134,130,102,136,33,133,39,2,146,51,14,217,164,74,169,186,8,160,28,2,0,133,1,
0,141,0,0,130,111,0,197,0,0,135,1,0,144,2,128,86,47,49,233,233,139,3,10,133,19,0,130,128,0,133,229,
0,135,79,1,138,175,65,245,26,131,175,1,133,25,2,135,130,2,130,219,2,135,112,2,132,205,194,9,135,131,
2,134,130,14,10,39,139,205,2,133,112,2,135,111,2,130,12,2,133,25,2,144,40,126,23,25,172,71,30,32,64,
28,133,1,0,135,0,0,130,111,0,195,0,0,156,1,8,32,135,90,1,167,7,170,188,229,98,139,194,4,128,144,3,
133,229,0,133,79,1,135,175,1,135,12,2,142,25,62,42,65,178,243,58,218,44,137,21,0,146,42,160,107,133,
4,128,232,208,108,5,22,0,139,205,2,132,112,54,11,133,112,2,154,131,190,153,225,110,200,81,247,157,
74,73,2,49,77,28,1,0,135,0,0,130,111,0,189,0,0,148,1,196,33,199,168,195,124,202,40,182,202,74,0,133,
40,0,142,158,124,50,151,89,247,240,150,33,133,175,1,133,12,2,133,111,2,144,219,10,186,239,94,68,201,
58,175,10,137,129,0,144,161,84,33,43,2,74,6,51,73,5,135,22,0,130,130,0,135,21,0,162,205,110,139,238,
185,40,98,152,225,107,12,186,182,27,114,235,169,113,229,52,2,0,133,1,0,187,0,0,170,1,196,33,135,46,
141,253,200,232,159,216,166,48,129,36,145,200,165,82,190,53,20,107,150,107,11,2,135,12,2,130,112,2,
133,205,2,166,111,106,27,204,97,64,77,148,12,40,230,228,35,72,62,161,52,211,9,80,83,182,52,9,133,
231,0,132,130,156,3,135,130,0,170,21,168,176,68,56,37,38,166,234,188,142,190,201,96,134,95,121,37,
23,95,103,180,10,90,28,1,0,179,0,0,135,1,0,142,3,220,232,18,168,140,2,138,45,135,40,0,150,169,120,
244,5,45,43,254,4,212,97,67,102,40,40,133,112,2,133,205,2,130,21,0,135,42,0,140,201,204,50,141,79,
157,197,4,133,161,0,133,7,1,144,49,233,231,211,79,39,77,134,80,62,143,231,0,168,148,4,67,37,80,96,
54,148,42,147,161,90,186,27,134,25,242,246,212,61,124,173,193,158,28,133,1,0,175,0,0,174,1,196,65,
103,23,63,154,104,97,155,202,74,128,66,42,190,76,153,145,79,113,8,32,7,34,85,158,248,38,133,112,2,
130,205,2,137,21,0,133,147,0,170,50,73,58,141,52,78,68,99,83,75,44,217,212,19,135,210,76,3,133,100,
96,245,6,91,84,82,1,135,81,1,176,231,228,19,74,51,10,76,35,64,28,118,152,106,76,147,150,98,184,224,
107,187,125,85,208,71,176,118,24,71,0,155,0,0,130,111,0,141,0,0,133,1,0,154,114,140,132,158,140,23,
182,169,44,182,40,164,226,11,119,119,2,133,113,0,135,1,0,138,211,168,33,100,163,204,2,133,205,2,133,
21,0,135,129,0,146,248,132,114,83,115,113,4,32,13,187,236,0,133,219,0,132,87,21,10,133,113,0,142,
210,72,42,89,114,26,198,230,32,137,177,1,133,81,1,136,8,181,84,211,52,133,1,0,160,112,8,48,141,63,
94,168,58,35,114,187,185,246,84,57,5,193,36,134,28,133,1,0,163,0,0,144,1,8,112,199,24,63,26,247,39,
160,133,216,2,138,56,252,242,94,135,113,0,133,1,0,133,0,0,142,1,72,51,74,149,141,106,219,44,133,21,
0,135,129,0,133,231,0,144,249,28,100,19,38,210,4,0,64,0,141,112,0,140,1,72,195,86,126,201,105,8,145,
177,1,138,96,85,212,140,11,113,0,137,1,0,133,113,0,156,10,21,163,234,137,187,189,246,148,61,158,120,
148,176,85,113,4,0,159,0,0,160,112,196,161,150,99,50,90,200,166,178,216,146,59,133,23,13,77,19,71,0,
137,0,0,142,112,72,115,171,170,218,170,80,1,135,129,0,135,231,0,144,81,129,85,145,77,118,198,1,192,
27,143,0,0,140,112,196,225,2,102,52,106,8,137,14,2,132,177,57,8,133,177,1,140,190,129,37,89,27,210,
4,0,139,0,0,138,112,72,131,175,122,67,2,133,187,1,133,79,1,140,94,165,98,198,72,113,192,1,155,0,0,
156,25,196,1,11,122,50,90,8,40,182,40,144,235,11,101,186,10,0,133,1,0,139,0,0,138,112,244,106,159,
18,204,2,133,21,0,132,129,80,2,133,130,0,133,231,0,140,81,129,245,215,51,121,196,1,149,0,0,138,210,
216,201,25,141,132,2,133,113,2,130,14,2,137,113,2,142,14,198,22,149,95,17,251,20,0,141,0,0,158,112,
196,49,231,148,76,34,183,155,107,79,221,131,195,47,0,203,17,0,149,0,0,133,1,0,138,3,140,132,94,137,
108,2,133,201,2,142,215,198,107,134,96,113,192,17,0,141,0,0,138,1,196,177,80,173,243,2,133,42,0,130,
129,0,133,249,0,133,231,0,144,96,193,22,149,114,127,65,51,38,28,149,0,0,140,210,104,179,153,168,132,
58,11,141,113,2,135,14,2,136,103,113,86,102,28,143,0,0,158,112,4,48,141,193,247,201,245,213,83,229,
220,131,195,23,105,76,3,7,147,0,0,154,1,200,145,145,146,38,90,8,40,182,228,78,161,134,108,113,0,133,
1,0,145,0,0,148,113,224,235,176,18,42,76,162,2,37,147,8,2,133,231,0,133,81,1,138,103,41,150,235,79,
1,0,147,0,0,140,1,196,145,192,78,171,166,11,135,206,2,139,113,2,140,14,198,86,93,126,30,74,3,139,0,
0,130,24,0,133,0,0,133,1,0,138,210,124,0,217,116,95,1,133,79,1,140,246,120,242,139,24,210,192,1,143,
0,0,156,1,196,81,47,149,37,254,153,44,182,228,78,129,235,179,113,192,1,149,0,0,140,113,220,9,89,89,
25,46,8,133,111,2,135,205,2,130,21,0,133,129,0,138,147,0,147,217,52,1,0,147,0,0,144,1,192,225,89,52,
179,166,123,129,179,133,220,2,130,206,2,137,113,2,138,14,86,135,95,112,113,0,141,0,0,130,24,0,135,0,
0,140,1,196,97,149,49,114,125,5,133,79,1,140,246,224,96,6,148,114,192,1,139,0,0,138,1,196,113,72,
150,49,2,133,127,2,142,216,150,11,134,27,100,198,17,0,151,0,0,138,1,124,230,204,116,174,1,133,111,2,
130,112,2,133,205,2,146,22,84,16,200,57,7,201,180,204,52,1,0,149,0,0,142,1,72,195,165,149,144,58,
123,1,135,206,2,132,220,58,11,133,113,2,138,26,130,167,211,127,112,0,145,0,0,130,111,0,133,0,0,190,
1,196,145,71,77,222,125,229,20,57,146,224,96,6,12,114,4,0,192,27,0,4,32,0,104,52,45,89,105,185,56,
200,11,36,77,252,9,16,0,153,0,0,150,1,196,113,100,124,200,97,40,232,160,112,170,176,2,133,148,0,138,
147,172,146,147,166,113,0,153,0,0,140,210,152,244,37,145,132,198,9,137,14,2,144,113,18,170,33,141,
93,186,39,77,0,153,0,0,156,1,196,209,33,100,114,121,229,20,57,146,200,75,235,174,2,4,0,133,0,0,154,
1,12,128,101,195,65,30,87,207,177,138,150,7,84,28,1,0,157,0,0,162,1,196,33,198,125,150,10,250,102,
179,20,84,16,200,36,21,217,4,177,52,1,0,153,0,0,140,1,72,195,147,173,151,18,10,133,113,2,133,14,2,
142,177,245,86,29,102,82,74,19,0,157,0,0,182,1,196,193,22,98,101,57,69,142,36,41,232,171,140,28,1,0,
16,128,0,8,188,74,233,55,124,52,194,200,118,9,13,16,0,161,0,0,142,112,72,227,67,25,235,169,74,48,
135,97,0,138,104,192,167,169,52,1,0,157,0,0,138,1,248,84,24,50,86,2,137,78,2,140,242,73,182,229,66,
210,192,1,145,0,0,130,111,0,137,0,0,130,111,0,133,0,0,178,112,196,81,217,122,94,125,69,14,32,158,
152,49,91,28,1,8,48,64,93,180,25,136,230,3,141,188,133,133,28,1,0,165,0,0,150,1,192,17,71,183,25,
253,203,133,22,108,21,18,7,133,1,0,161,0,0,133,112,0,150,113,112,104,111,94,230,21,102,42,63,210,
192,17,0,161,0,0,142,111,0,16,71,175,204,124,100,22,133,228,0,162,145,76,209,152,28,2,12,208,95,118,
32,242,73,236,3,156,16,118,135,0,1,0,135,0,0,130,111,0,161,0,0,135,1,0,130,2,0,133,113,0,133,1,0,
173,0,0,133,112,0,133,113,0,135,112,0,171,0,0,174,112,196,129,111,98,101,57,69,142,61,56,40,220,79,
28,4,172,43,22,86,19,242,249,128,68,88,12,16,0,173,0,0,139,1,0,181,0,0,130,111,0,133,0,0,130,112,0,
175,0,0,136,113,36,96,140,92,133,228,0,160,128,160,240,139,193,211,20,112,145,88,168,77,200,231,180,
27,237,48,64,0,33,129,0,0,136,1,72,83,223,122,133,94,1,133,128,0,156,72,212,55,141,53,23,181,131,20,
106,124,38,186,69,104,2,4,0,33,129,0,0,140,112,72,179,35,98,101,145,3,133,128,0,154,56,36,60,148,
152,12,37,130,84,106,18,38,90,48,1,2,0,35,129,0,0,170,1,196,209,238,101,5,217,67,142,36,56,152,49,
32,30,164,40,130,20,106,123,194,155,163,28,1,0,37,129,0,0,168,113,60,171,25,95,246,144,3,136,39,190,
112,131,199,11,137,120,131,84,109,147,210,37,64,0,37,129,0,0,168,1,200,209,152,74,102,217,3,136,39,
190,156,134,199,11,33,232,129,84,109,147,210,53,64,0,37,129,0,0,168,1,200,1,112,116,229,26,100,15,
14,190,156,230,171,187,209,234,225,13,86,207,137,55,64,0,37,129,0,0,170,1,200,65,6,69,226,176,150,
131,42,198,112,51,154,187,209,50,160,7,86,32,22,73,128,0,1,0,33,129,0,0,172,1,8,192,31,49,168,60,18,
1,178,210,49,92,84,29,79,224,41,173,34,239,140,117,106,80,2,4,0,17,129,0,0,130,24,0,143,0,0,172,1,8,
208,66,47,55,60,18,1,178,139,34,217,95,1,87,68,104,166,176,139,40,194,99,58,3,4,0,141,0,0,130,111,0,
177,0,0,130,111,0,173,0,0,130,111,0,143,0,0,130,111,0,163,0,0,172,1,196,65,18,71,143,32,107,109,181,
148,182,55,0,1,145,198,64,160,176,12,232,225,22,96,3,4,0,141,0,0,130,24,0,141,0,0,130,1,0,135,0,0,
133,111,0,145,0,0,133,1,0,191,0,0,143,1,0,155,0,0,148,1,200,177,240,41,143,32,171,102,133,157,242,
11,133,3,0,148,253,97,68,160,153,194,50,0,16,121,161,9,0,133,1,0,135,0,0,130,111,0,141,0,0,135,1,0,
133,2,0,135,1,0,133,0,0,130,24,0,133,0,0,141,1,0,167,0,0,139,1,0,137,0,0,135,1,0,135,2,0,130,113,0,
133,1,0,151,0,0,150,1,8,16,86,74,54,32,123,108,159,35,34,57,20,133,2,0,134,4,228,18,3,133,102,2,142,
12,40,242,143,43,4,8,16,0,147,0,0,150,1,8,0,26,171,236,61,201,158,117,3,8,16,0,133,0,0,134,1,8,128,
14,133,54,2,130,232,0,133,2,0,130,1,0,157,0,0,133,1,0,132,113,108,8,133,244,2,132,83,197,1,133,1,0,
152,0,4,32,192,79,194,164,81,223,76,236,233,42,64,0,133,0,0,130,111,0,143,0,0,178,1,12,224,170,17,
213,170,217,39,133,208,97,49,128,0,1,8,176,129,93,208,22,104,166,8,137,100,183,193,0,1,0,145,0,0,
152,1,196,113,35,25,181,156,66,81,92,221,161,4,139,28,133,1,0,136,113,60,153,240,192,133,95,0,138,
83,234,34,71,28,1,0,151,0,0,136,112,76,35,88,194,133,137,1,136,241,93,246,175,28,133,2,0,140,114,
160,106,140,74,182,36,1,133,84,0,136,12,47,22,71,0,145,0,0,166,1,200,81,175,20,213,246,169,102,130,
182,149,87,154,0,1,0,16,192,0,184,56,20,44,133,102,2,140,12,104,18,24,29,2,4,0,133,0,0,130,111,0,
135,0,0,142,1,8,112,163,192,139,30,27,1,133,126,0,136,245,12,148,222,195,133,114,0,150,245,198,202,
40,160,203,162,144,4,24,150,209,41,0,133,1,0,143,0,0,164,112,196,81,9,173,43,205,117,79,57,246,120,
114,25,44,212,240,231,229,49,56,164,0,133,19,0,142,41,40,91,174,194,131,197,17,0,141,0,0,154,1,8,80,
154,192,139,170,217,167,106,183,65,215,239,0,1,0,133,0,0,140,1,8,16,84,96,49,4,11,133,102,2,136,33,
56,20,210,0,133,1,0,137,0,0,142,1,8,192,95,148,196,245,137,44,133,17,0,133,126,0,148,143,12,180,87,
23,162,33,44,157,133,128,182,9,133,128,2,140,229,82,97,198,40,114,4,0,141,0,0,142,1,200,193,214,75,
182,72,2,8,133,229,0,144,247,72,114,203,99,188,42,169,111,185,133,41,0,130,203,2,133,110,2,140,109,
98,43,163,150,0,10,0,139,0,0,154,1,8,0,154,171,47,246,153,160,106,183,5,84,18,80,2,0,135,0,0,133,1,
0,152,3,252,134,29,8,193,22,104,102,180,12,225,50,64,0,137,0,0,146,1,12,112,157,94,183,85,152,224,
154,200,2,133,17,0,144,127,64,242,200,64,38,208,147,155,110,133,10,2,146,109,42,232,38,160,140,42,
60,146,28,1,0,137,0,0,140,112,200,193,158,25,56,72,2,133,128,0,135,19,0,146,128,72,130,109,110,229,
154,11,232,178,202,2,133,109,2,135,10,2,138,185,45,73,210,0,1,0,135,0,0,140,1,8,64,205,124,157,86,8,
133,171,1,140,91,197,131,23,132,3,4,0,137,0,0,133,1,0,152,3,48,113,87,8,102,22,104,102,180,14,53,65,
128,0,135,0,0,138,1,8,64,234,91,74,1,133,171,1,133,9,2,132,214,34,11,133,17,0,130,143,0,133,144,0,
130,245,0,133,76,1,130,77,1,135,173,1,133,10,2,140,128,154,24,235,187,113,4,0,133,0,0,140,1,196,209,
144,194,229,98,11,139,203,2,134,19,44,171,44,133,217,2,133,109,2,130,129,2,133,109,2,135,10,2,142,
173,177,86,207,94,237,201,17,0,133,0,0,156,1,8,0,20,99,47,142,120,155,106,183,193,179,81,66,3,4,0,
143,0,0,154,1,12,96,145,115,32,4,91,160,153,209,146,130,11,1,2,0,135,1,0,142,3,224,24,81,60,224,44,
181,26,133,9,2,130,106,2,133,200,2,135,17,0,133,127,0,135,227,0,130,76,1,133,77,1,133,173,1,138,23,
30,71,165,128,2,0,133,1,0,140,113,120,0,171,140,128,182,9,133,203,2,133,110,2,132,109,186,9,133,109,
2,132,10,182,9,135,10,2,135,173,1,132,172,181,6,133,76,1,152,245,116,52,152,28,1,0,16,128,0,161,209,
231,227,109,135,91,1,138,240,64,180,150,28,1,0,145,0,0,133,1,0,152,3,128,164,99,34,209,22,104,102,
180,154,136,20,212,0,133,1,0,146,3,168,91,4,9,142,128,163,212,82,171,1,133,9,2,133,107,2,133,200,2,
134,17,60,18,1,133,127,0,133,227,0,137,76,1,136,93,117,199,134,28,133,2,0,144,114,224,244,163,133,
23,182,9,104,155,141,10,2,132,173,41,8,133,173,1,130,76,1,133,77,1,133,76,1,142,227,252,1,201,13,
189,176,56,0,133,1,0,138,113,88,130,100,113,183,1,133,74,1,142,223,48,34,75,120,3,4,240,6,149,0,0,
140,1,12,208,138,142,154,136,0,135,102,2,160,50,220,149,206,0,2,12,32,218,166,123,146,192,71,31,224,
40,181,212,106,135,9,2,130,199,2,135,200,2,133,17,0,130,126,0,135,127,0,133,227,0,136,76,209,131,30,
162,133,3,0,134,239,162,103,28,135,172,1,139,173,1,130,76,1,133,173,1,139,76,1,135,227,0,135,127,0,
150,39,140,139,112,127,3,8,48,64,166,61,18,183,21,133,74,1,140,241,108,162,81,66,3,4,0,155,0,0,142,
1,12,144,162,145,154,132,16,44,133,5,2,136,209,150,226,138,80,133,4,0,140,23,77,58,45,177,16,244,1,
133,224,0,133,74,1,133,171,1,135,9,2,133,107,2,135,200,2,135,17,0,133,127,0,146,143,156,114,112,1,
116,28,220,17,65,227,0,141,76,1,135,227,0,134,245,140,227,7,133,227,0,133,127,0,133,17,0,152,39,32,
27,65,159,158,102,65,7,1,117,106,4,93,60,133,242,0,140,124,140,48,67,22,84,13,0,133,1,0,157,0,0,142,
1,12,16,218,120,206,37,34,2,135,102,2,150,50,196,130,169,1,216,104,87,27,130,105,18,11,1,133,125,0,
133,224,0,134,74,45,181,26,135,9,2,133,106,2,135,200,2,135,17,0,142,39,216,208,139,105,192,214,114,
3,133,144,0,137,127,0,133,227,0,141,127,0,135,17,0,137,200,2,166,107,170,73,226,121,1,146,230,239,
118,100,105,5,14,31,141,140,64,68,169,64,9,16,0,161,0,0,133,1,0,142,2,12,192,138,142,0,137,96,38,
133,5,2,142,121,106,242,144,81,33,212,134,26,133,8,2,135,196,2,133,125,0,133,224,0,135,74,1,133,171,
1,137,9,2,132,106,174,9,133,200,2,138,125,30,49,172,3,55,0,133,214,2,147,17,0,139,200,2,137,107,2,
130,106,2,137,9,2,136,223,160,9,151,64,133,141,0,146,124,60,64,173,184,247,238,48,128,0,1,0,169,0,0,
146,1,12,192,235,120,207,181,179,128,153,5,2,133,102,2,138,34,44,178,135,55,72,1,133,168,1,130,8,2,
133,105,2,133,15,0,133,125,0,135,224,0,135,75,1,135,171,1,134,9,170,153,32,133,125,2,133,170,1,133,
126,2,130,107,2,143,200,2,133,107,2,137,106,2,135,9,2,137,171,1,133,75,1,156,74,109,37,79,31,124,60,
64,194,8,226,194,91,87,104,3,4,0,175,0,0,146,1,8,48,64,138,118,57,215,78,176,102,2,133,5,2,146,194,
138,192,192,34,222,32,133,218,132,124,2,133,105,2,133,196,2,130,15,0,135,16,0,130,125,0,133,224,0,
139,74,1,133,171,1,138,184,173,150,96,133,171,1,149,9,2,137,171,1,139,74,1,135,224,0,134,16,244,241,
0,133,196,2,144,105,78,11,111,142,131,12,32,64,0,181,0,0,158,1,8,48,135,186,118,181,149,72,180,102,
22,104,230,153,194,234,177,7,133,222,0,132,72,161,6,133,8,2,133,105,2,135,196,2,133,15,0,135,125,0,
137,224,0,133,74,1,130,75,1,133,74,1,132,75,41,5,143,75,1,135,74,1,132,92,205,3,137,224,0,132,125,
56,2,133,15,0,134,142,60,64,44,133,123,2,142,122,78,202,92,85,3,8,16,0,135,0,0,130,111,0,179,0,0,
133,1,0,150,2,12,80,99,93,206,185,179,64,176,102,22,104,38,133,194,2,132,13,236,1,133,222,0,133,72,
1,134,168,29,136,32,133,105,2,135,196,2,130,15,0,135,16,0,143,125,0,130,224,0,133,125,0,130,224,0,
145,125,0,133,16,0,130,125,0,133,16,0,135,196,2,133,105,2,144,7,74,40,98,139,117,105,48,128,0,133,1,
0,137,0,0,130,111,0,167,0,0,130,111,0,145,0,0,146,1,8,48,64,152,162,180,229,150,12,209,2,133,5,2,
130,102,2,135,194,2,136,13,236,241,142,55,133,72,1,133,168,1,135,8,2,137,105,2,135,196,2,130,198,2,
133,37,0,130,198,2,139,16,0,133,198,2,134,16,24,11,1,135,196,2,139,105,2,133,18,2,146,34,130,248,
161,115,134,138,54,128,0,1,0,165,0,0,130,111,0,143,0,0,130,111,0,149,0,0,133,1,0,146,2,12,64,64,90,
174,48,244,79,34,193,2,135,102,2,130,103,2,133,194,2,134,12,232,177,7,135,222,0,132,72,37,5,133,168,
1,132,8,162,6,141,8,2,135,105,2,130,8,2,137,105,2,135,8,2,133,105,2,133,8,2,135,168,1,144,181,13,
231,156,93,60,28,48,128,0,135,1,0,211,0,0,133,1,0,158,2,12,16,148,58,61,144,226,16,41,49,224,25,33,
129,102,6,43,44,133,12,0,135,123,0,137,222,0,139,72,1,134,169,161,134,32,139,168,1,140,72,213,134,
90,109,71,101,5,133,88,1,148,195,9,39,22,67,134,250,87,192,0,2,4,0,221,0,0,137,1,0,133,2,0,144,3,0,
133,214,186,63,188,50,68,184,133,209,2,132,102,6,11,133,102,2,135,194,2,135,12,0,130,221,0,133,122,
0,130,222,0,135,221,0,134,71,117,115,20,133,221,0,152,238,232,225,206,88,154,56,132,81,15,42,62,56,
199,0,133,2,0,133,1,0,147,0,0,130,111,0,217,0,0,133,1,0,133,2,0,142,3,88,51,154,33,192,29,250,2,133,
63,0,130,65,0,137,224,2,133,208,2,132,32,196,0,133,32,0,132,153,128,0,139,153,0,133,151,0,140,222,
30,186,14,105,66,21,0,133,3,0,132,2,4,0,249,0,0,137,1,0,141,2,0,146,3,16,80,199,53,163,137,201,129,
62,251,0,139,132,0,142,27,200,41,148,53,213,204,49,0,141,2,0,137,1,0,191,0,0,
};
// clang-format on

static const image_descriptor gfx_batman_raw = {
  .width = 102,
  .height = 58,
  .byte_count = 6711,
  .compression = image_compression::PAL_NQRLE,
  .image_data = gfx_batman_data}; // 1.76308 compression rate

const image_descriptor* gfx_batman = &gfx_batman_raw;
