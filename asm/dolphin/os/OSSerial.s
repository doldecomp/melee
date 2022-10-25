.include "macros.inc"

.section .text  # 0x80342E94 - 0x803B7240 

.global SIGetTypeAsync
SIGetTypeAsync:
/* 8034AA44 00347624  7C 08 02 A6 */	mflr r0
/* 8034AA48 00347628  90 01 00 04 */	stw r0, 4(r1)
/* 8034AA4C 0034762C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8034AA50 00347630  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8034AA54 00347634  3B E4 00 00 */	addi r31, r4, 0
/* 8034AA58 00347638  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8034AA5C 0034763C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8034AA60 00347640  93 81 00 10 */	stw r28, 0x10(r1)
/* 8034AA64 00347644  3B 83 00 00 */	addi r28, r3, 0
/* 8034AA68 00347648  4B FF C8 FD */	bl OSDisableInterrupts
/* 8034AA6C 0034764C  3B C3 00 00 */	addi r30, r3, 0
/* 8034AA70 00347650  38 7C 00 00 */	addi r3, r28, 0
/* 8034AA74 00347654  4B FF FE 0D */	bl SIGetType
/* 8034AA78 00347658  3C 80 80 40 */	lis r4, lbl_8040236C@ha
/* 8034AA7C 0034765C  57 85 10 3A */	slwi r5, r28, 2
/* 8034AA80 00347660  38 04 23 6C */	addi r0, r4, lbl_8040236C@l
/* 8034AA84 00347664  7C 80 2A 14 */	add r4, r0, r5
/* 8034AA88 00347668  80 04 00 00 */	lwz r0, 0(r4)
/* 8034AA8C 0034766C  3B A3 00 00 */	addi r29, r3, 0
/* 8034AA90 00347670  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 8034AA94 00347674  41 82 00 AC */	beq lbl_8034AB40
/* 8034AA98 00347678  3C 60 80 4A */	lis r3, lbl_804A7F18@ha
/* 8034AA9C 0034767C  57 84 20 36 */	slwi r4, r28, 4
/* 8034AAA0 00347680  38 03 7F 18 */	addi r0, r3, lbl_804A7F18@l
/* 8034AAA4 00347684  7C 80 22 14 */	add r4, r0, r4
/* 8034AAA8 00347688  80 04 00 00 */	lwz r0, 0(r4)
/* 8034AAAC 0034768C  38 A0 00 00 */	li r5, 0
/* 8034AAB0 00347690  7C 00 F8 40 */	cmplw r0, r31
/* 8034AAB4 00347694  41 82 00 A0 */	beq lbl_8034AB54
/* 8034AAB8 00347698  28 00 00 00 */	cmplwi r0, 0
/* 8034AABC 0034769C  40 82 00 10 */	bne lbl_8034AACC
/* 8034AAC0 003476A0  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AAC4 003476A4  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AAC8 003476A8  48 00 00 8C */	b lbl_8034AB54
lbl_8034AACC:
/* 8034AACC 003476AC  38 64 00 04 */	addi r3, r4, 4
/* 8034AAD0 003476B0  80 04 00 04 */	lwz r0, 4(r4)
/* 8034AAD4 003476B4  38 A0 00 01 */	li r5, 1
/* 8034AAD8 003476B8  7C 00 F8 40 */	cmplw r0, r31
/* 8034AADC 003476BC  41 82 00 78 */	beq lbl_8034AB54
/* 8034AAE0 003476C0  28 00 00 00 */	cmplwi r0, 0
/* 8034AAE4 003476C4  40 82 00 10 */	bne lbl_8034AAF4
/* 8034AAE8 003476C8  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AAEC 003476CC  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AAF0 003476D0  48 00 00 64 */	b lbl_8034AB54
lbl_8034AAF4:
/* 8034AAF4 003476D4  84 03 00 04 */	lwzu r0, 4(r3)
/* 8034AAF8 003476D8  38 A0 00 02 */	li r5, 2
/* 8034AAFC 003476DC  7C 00 F8 40 */	cmplw r0, r31
/* 8034AB00 003476E0  41 82 00 54 */	beq lbl_8034AB54
/* 8034AB04 003476E4  28 00 00 00 */	cmplwi r0, 0
/* 8034AB08 003476E8  40 82 00 10 */	bne lbl_8034AB18
/* 8034AB0C 003476EC  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AB10 003476F0  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AB14 003476F4  48 00 00 40 */	b lbl_8034AB54
lbl_8034AB18:
/* 8034AB18 003476F8  80 03 00 04 */	lwz r0, 4(r3)
/* 8034AB1C 003476FC  38 A0 00 03 */	li r5, 3
/* 8034AB20 00347700  7C 00 F8 40 */	cmplw r0, r31
/* 8034AB24 00347704  41 82 00 30 */	beq lbl_8034AB54
/* 8034AB28 00347708  28 00 00 00 */	cmplwi r0, 0
/* 8034AB2C 0034770C  40 82 00 28 */	bne lbl_8034AB54
/* 8034AB30 00347710  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AB34 00347714  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AB38 00347718  48 00 00 1C */	b lbl_8034AB54
/* 8034AB3C 0034771C  48 00 00 18 */	b lbl_8034AB54
lbl_8034AB40:
/* 8034AB40 00347720  39 9F 00 00 */	addi r12, r31, 0
/* 8034AB44 00347724  7D 88 03 A6 */	mtlr r12
/* 8034AB48 00347728  38 7C 00 00 */	addi r3, r28, 0
/* 8034AB4C 0034772C  38 9D 00 00 */	addi r4, r29, 0
/* 8034AB50 00347730  4E 80 00 21 */	blrl 
lbl_8034AB54:
/* 8034AB54 00347734  7F C3 F3 78 */	mr r3, r30
/* 8034AB58 00347738  4B FF C8 35 */	bl OSRestoreInterrupts
/* 8034AB5C 0034773C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8034AB60 00347740  7F A3 EB 78 */	mr r3, r29
/* 8034AB64 00347744  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8034AB68 00347748  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8034AB6C 0034774C  7C 08 03 A6 */	mtlr r0
/* 8034AB70 00347750  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8034AB74 00347754  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8034AB78 00347758  38 21 00 20 */	addi r1, r1, 0x20
/* 8034AB7C 0034775C  4E 80 00 20 */	blr 

.section .data
    .balign 8
.global lbl_80402358
lbl_80402358:
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_8040236C
lbl_8040236C:
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x4E6F2072
    .4byte 0x6573706F
    .4byte 0x6E736500
    .4byte 0x4E363420
    .4byte 0x636F6E74
    .4byte 0x726F6C6C
    .4byte 0x65720000
    .4byte 0x4E363420
    .4byte 0x6D696372
    .4byte 0x6F70686F
    .4byte 0x6E650000
    .4byte 0x4E363420
    .4byte 0x6B657962
    .4byte 0x6F617264
    .4byte NULL
    .4byte 0x4E363420
    .4byte 0x6D6F7573
    .4byte 0x65000000
    .4byte 0x47616D65
    .4byte 0x426F7920
    .4byte 0x41647661
    .4byte 0x6E636500
    .4byte 0x5374616E
    .4byte 0x64617264
    .4byte 0x20636F6E
    .4byte 0x74726F6C
    .4byte 0x6C657200
    .4byte 0x57697265
    .4byte 0x6C657373
    .4byte 0x20726563
    .4byte 0x65697665
    .4byte 0x72000000
    .4byte 0x57617665
    .4byte 0x42697264
    .4byte 0x20636F6E
    .4byte 0x74726F6C
    .4byte 0x6C657200
    .4byte 0x4B657962
    .4byte 0x6F617264
    .4byte NULL
    .4byte NULL

.section .bss, "wa"
    .balign 8
.global Packet
Packet:
	.skip 0x80
.global Alarm
Alarm:
	.skip 0xA0
.global lbl_804A7ED8
lbl_804A7ED8:
	.skip 0x20
.global lbl_804A7EF8
lbl_804A7EF8:
	.skip 0x20
.global lbl_804A7F18
lbl_804A7F18:
	.skip 0x40
.global lbl_804A7F58
lbl_804A7F58:
	.skip 0x60

.section .sbss
    .balign 8
.global lbl_804D73C8
lbl_804D73C8:
	.skip 0x4
.global lbl_804D73CC
lbl_804D73CC:
	.skip 0x4
.global lbl_804D73D0
lbl_804D73D0:
	.skip 0x8
