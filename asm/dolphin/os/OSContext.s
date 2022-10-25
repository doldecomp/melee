.include "macros.inc"

.section .text  # 0x80344E30 - 0x803456A4

.global OSSwitchFPUContext
OSSwitchFPUContext:
/* 803455DC 003421BC  7C A0 00 A6 */	mfmsr r5
/* 803455E0 003421C0  60 A5 20 00 */	ori r5, r5, 0x2000
/* 803455E4 003421C4  7C A0 01 24 */	mtmsr r5
/* 803455E8 003421C8  4C 00 01 2C */	isync 
/* 803455EC 003421CC  80 A4 01 9C */	lwz r5, 0x19c(r4)
/* 803455F0 003421D0  60 A5 20 00 */	ori r5, r5, 0x2000
/* 803455F4 003421D4  7C BB 03 A6 */	mtspr 0x1b, r5
/* 803455F8 003421D8  3C 60 80 00 */	lis r3, 0x800000D8@ha
/* 803455FC 003421DC  80 A3 00 D8 */	lwz r5, 0x800000D8@l(r3)
/* 80345600 003421E0  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80345604 003421E4  7C 05 20 00 */	cmpw r5, r4
/* 80345608 003421E8  41 82 00 14 */	beq lbl_8034561C
/* 8034560C 003421EC  2C 05 00 00 */	cmpwi r5, 0
/* 80345610 003421F0  41 82 00 08 */	beq lbl_80345618
/* 80345614 003421F4  4B FF F9 41 */	bl __OSSaveFPUContext
lbl_80345618:
/* 80345618 003421F8  4B FF F8 19 */	bl __OSLoadFPUContext
lbl_8034561C:
/* 8034561C 003421FC  80 64 00 80 */	lwz r3, 0x80(r4)
/* 80345620 00342200  7C 6F F1 20 */	mtcrf 0xff, r3
/* 80345624 00342204  80 64 00 84 */	lwz r3, 0x84(r4)
/* 80345628 00342208  7C 68 03 A6 */	mtlr r3
/* 8034562C 0034220C  80 64 01 98 */	lwz r3, 0x198(r4)
/* 80345630 00342210  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80345634 00342214  80 64 00 88 */	lwz r3, 0x88(r4)
/* 80345638 00342218  7C 69 03 A6 */	mtctr r3
/* 8034563C 0034221C  80 64 00 8C */	lwz r3, 0x8c(r4)
/* 80345640 00342220  7C 61 03 A6 */	mtxer r3
/* 80345644 00342224  A0 64 01 A2 */	lhz r3, 0x1a2(r4)
/* 80345648 00342228  54 63 07 FA */	rlwinm r3, r3, 0, 0x1f, 0x1d
/* 8034564C 0034222C  B0 64 01 A2 */	sth r3, 0x1a2(r4)
/* 80345650 00342230  80 A4 00 14 */	lwz r5, 0x14(r4)
/* 80345654 00342234  80 64 00 0C */	lwz r3, 0xc(r4)
/* 80345658 00342238  80 84 00 10 */	lwz r4, 0x10(r4)
/* 8034565C 0034223C  4C 00 00 64 */	rfi 

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
