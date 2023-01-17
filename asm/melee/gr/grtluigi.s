.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_80221EE0
lbl_80221EE0:
/* 80221EE0 0021EAC0  4E 80 00 20 */	blr

.global lbl_80221EE4
lbl_80221EE4:
/* 80221EE4 0021EAC4  38 60 00 00 */	li r3, 0
/* 80221EE8 0021EAC8  4E 80 00 20 */	blr

.global lbl_80221EEC
lbl_80221EEC:
/* 80221EEC 0021EACC  38 60 00 01 */	li r3, 1
/* 80221EF0 0021EAD0  4E 80 00 20 */	blr


