CLS
RET
SYS 0A7
JP 0A3
CALL 7C3
SE V8, A7
SNE VC, 9C
SE V8, V7
LD V9, 08
LD V3, VD
ADD V9, 8c
LD VD, V7
OR Va, V9
AND Va, V9
XOR Va, V9
ADD Va, V9
SUB Va, V9
SHR Va, V9
SUBN Va, V9
SHL Va, V9
SNE Va, V9
LD I, 08c
JP V0, 08c
RND V8, A7
DRW V8, VB, A
SKP VD
SKNP VD
LD V9, DT
LD V3, K
LD DT, V9
LD ST, VD
ADD I, VC
LD F, V9
LD B, VD
LD [I], V9
LD VD, [I]
