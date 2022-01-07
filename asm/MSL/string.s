.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80325B04
func_80325B04:
/* 80325B04 003226E4  38 80 FF FF */	li r4, -1
/* 80325B08 003226E8  38 63 FF FF */	addi r3, r3, -1
lbl_80325B0C:
/* 80325B0C 003226EC  8C 03 00 01 */	lbzu r0, 1(r3)
/* 80325B10 003226F0  38 84 00 01 */	addi r4, r4, 1
/* 80325B14 003226F4  28 00 00 00 */	cmplwi r0, 0
/* 80325B18 003226F8  40 82 FF F4 */	bne lbl_80325B0C
/* 80325B1C 003226FC  7C 83 23 78 */	mr r3, r4
/* 80325B20 00322700  4E 80 00 20 */	blr 


.section .sdata

    .4byte NULL
.global lbl_804D5B58
lbl_804D5B58:
    .4byte 0x80808080
.global lbl_804D5B5C
lbl_804D5B5C:
    .4byte 0xFEFEFEFF
