.include "macros.inc"

.section .text  # 0x80344E30 - 0x803456A4

.global __OSContextInit
__OSContextInit:
/* 80345660 00342240  7C 08 02 A6 */	mflr r0
/* 80345664 00342244  90 01 00 04 */	stw r0, 4(r1)
/* 80345668 00342248  94 21 FF F8 */	stwu r1, -8(r1)
/* 8034566C 0034224C  3C 60 80 34 */	lis r3, OSSwitchFPUContext@ha
/* 80345670 00342250  38 83 55 DC */	addi r4, r3, OSSwitchFPUContext@l
/* 80345674 00342254  38 60 00 07 */	li r3, 7
/* 80345678 00342258  4B FF DF 3D */	bl __OSSetExceptionHandler
/* 8034567C 0034225C  38 00 00 00 */	li r0, 0
/* 80345680 00342260  4C C6 31 82 */	crclr 6
/* 80345684 00342264  3C 80 80 00 */	lis r4, 0x800000D8@ha
/* 80345688 00342268  3C 60 80 40 */	lis r3, lbl_80401FD4@ha
/* 8034568C 0034226C  90 04 00 D8 */	stw r0, 0x800000D8@l(r4)
/* 80345690 00342270  38 63 1F D4 */	addi r3, r3, lbl_80401FD4@l
/* 80345694 00342274  4B FF 08 E5 */	bl DBPrintf
/* 80345698 00342278  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8034569C 0034227C  38 21 00 08 */	addi r1, r1, 8
/* 803456A0 00342280  7C 08 03 A6 */	mtlr r0
/* 803456A4 00342284  4E 80 00 20 */	blr 

.section .data
    .balign 8
.global lbl_80401E20
lbl_80401E20:
    .asciz "------------------------- Context 0x%08x -------------------------\n"
    .balign 4
    .asciz "r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n"
    .balign 4
    .asciz "LR   = 0x%08x                   CR   = 0x%08x\n"
    .balign 4
    .asciz "SRR0 = 0x%08x                   SRR1 = 0x%08x\n"
    .balign 4
    .asciz "\nGQRs----------\n"
    .balign 4
    .asciz "gqr%d = 0x%08x \t gqr%d = 0x%08x\n"
    .balign 4
    .asciz "\n\nFPRs----------\n"
    .balign 4
    .asciz "fr%d \t= %d \t fr%d \t= %d\n"
    .balign 4
    .asciz "\n\nPSFs----------\n"
    .balign 4
    .asciz "ps%d \t= 0x%x \t ps%d \t= 0x%x\n"
    .balign 4
    .asciz "\nAddress:      Back Chain    LR Save\n"
    .balign 4
    .asciz "0x%08x:   0x%08x    0x%08x\n"
    .balign 4
.global lbl_80401FD4
lbl_80401FD4:
    .asciz "FPU-unavailable handler installed\n"
    .balign 4
