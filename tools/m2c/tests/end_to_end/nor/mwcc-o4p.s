.include "macros.inc"

.section .text  # 0x0 - 0x8

.global test
test:
/* 00000000 00000000  7C 63 20 F8 */	nor r3, r3, r4
/* 00000004 00000004  4E 80 00 20 */	blr 

