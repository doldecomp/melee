.include "macros.inc"

.section .data
    .balign 8

lbl_80430BD0:
    .int 38 
    .int 255
    .int 232
    .int 239
    .int 66
    .int 214
    .int 1
    .int 84
    .int 20
    .int 163
    .int 128
    .int 253
    .int 110

jtbl_80430C04:
	.4byte lbl_803B2E88
	.4byte lbl_803B2EB0
	.4byte lbl_803B2ED8
	.4byte lbl_803B2F00
	.4byte lbl_803B2F28
	.4byte lbl_803B2F50
	.4byte lbl_803B2F78

.section .text

# https://decomp.me/scratch/nfhCq // 8200 (20.39%)
func_803B2E04:
/* 803B2E04 003AF9E4  3C A0 4E C5 */	lis r5, 0x4EC4EC4F@ha
/* 803B2E08 003AF9E8  54 66 06 3E */	clrlwi r6, r3, 0x18
/* 803B2E0C 003AF9EC  38 05 EC 4F */	addi r0, r5, 0x4EC4EC4F@l
/* 803B2E10 003AF9F0  3C 60 92 49 */	lis r3, 0x92492493@ha
/* 803B2E14 003AF9F4  7C A0 30 96 */	mulhw r5, r0, r6
/* 803B2E18 003AF9F8  38 03 24 93 */	addi r0, r3, 0x92492493@l
/* 803B2E1C 003AF9FC  7C 00 30 96 */	mulhw r0, r0, r6
/* 803B2E20 003AFA00  7C A3 16 70 */	srawi r3, r5, 2
/* 803B2E24 003AFA04  54 65 0F FE */	srwi r5, r3, 0x1f
/* 803B2E28 003AFA08  7C 00 32 14 */	add r0, r0, r6
/* 803B2E2C 003AFA0C  7C 63 2A 14 */	add r3, r3, r5
/* 803B2E30 003AFA10  7C 00 16 70 */	srawi r0, r0, 2
/* 803B2E34 003AFA14  1C A3 00 0D */	mulli r5, r3, 0xd
/* 803B2E38 003AFA18  54 03 0F FE */	srwi r3, r0, 0x1f
/* 803B2E3C 003AFA1C  7C 00 1A 14 */	add r0, r0, r3
/* 803B2E40 003AFA20  1C 00 00 07 */	mulli r0, r0, 7
/* 803B2E44 003AFA24  7C A5 30 50 */	subf r5, r5, r6
/* 803B2E48 003AFA28  3C 60 80 43 */	lis r3, lbl_80430BD0@ha
/* 803B2E4C 003AFA2C  7C 00 30 50 */	subf r0, r0, r6
/* 803B2E50 003AFA30  54 A5 10 3A */	slwi r5, r5, 2
/* 803B2E54 003AFA34  38 63 0B D0 */	addi r3, r3, lbl_80430BD0@l
/* 803B2E58 003AFA38  7C 63 2A 14 */	add r3, r3, r5
/* 803B2E5C 003AFA3C  28 00 00 06 */	cmplwi r0, 6
/* 803B2E60 003AFA40  80 A3 00 00 */	lwz r5, 0(r3)
/* 803B2E64 003AFA44  7C C3 22 78 */	xor r3, r6, r4
/* 803B2E68 003AFA48  7C 63 2A 78 */	xor r3, r3, r5
/* 803B2E6C 003AFA4C  4D 81 00 20 */	bgtlr 
/* 803B2E70 003AFA50  3C 80 80 43 */	lis r4, jtbl_80430C04@ha
/* 803B2E74 003AFA54  38 84 0C 04 */	addi r4, r4, jtbl_80430C04@l
/* 803B2E78 003AFA58  54 00 10 3A */	slwi r0, r0, 2
/* 803B2E7C 003AFA5C  7C 04 00 2E */	lwzx r0, r4, r0
/* 803B2E80 003AFA60  7C 09 03 A6 */	mtctr r0
/* 803B2E84 003AFA64  4E 80 04 20 */	bctr 
lbl_803B2E88:
/* 803B2E88 003AFA68  54 60 1E F6 */	rlwinm r0, r3, 3, 0x1b, 0x1b
/* 803B2E8C 003AFA6C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 803B2E90 003AFA70  50 60 FF BC */	rlwimi r0, r3, 0x1f, 0x1e, 0x1e
/* 803B2E94 003AFA74  50 60 16 B4 */	rlwimi r0, r3, 2, 0x1a, 0x1a
/* 803B2E98 003AFA78  50 60 F7 7A */	rlwimi r0, r3, 0x1e, 0x1d, 0x1d
/* 803B2E9C 003AFA7C  50 60 0E 72 */	rlwimi r0, r3, 1, 0x19, 0x19
/* 803B2EA0 003AFA80  50 60 EF 38 */	rlwimi r0, r3, 0x1d, 0x1c, 0x1c
/* 803B2EA4 003AFA84  50 60 06 30 */	rlwimi r0, r3, 0, 0x18, 0x18
/* 803B2EA8 003AFA88  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2EAC 003AFA8C  4E 80 00 20 */	blr 
lbl_803B2EB0:
/* 803B2EB0 003AFA90  54 60 FF FE */	rlwinm r0, r3, 0x1f, 0x1f, 0x1f
/* 803B2EB4 003AFA94  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 803B2EB8 003AFA98  50 60 07 7A */	rlwimi r0, r3, 0, 0x1d, 0x1d
/* 803B2EBC 003AFA9C  50 60 1E 72 */	rlwimi r0, r3, 3, 0x19, 0x19
/* 803B2EC0 003AFAA0  50 60 0E B4 */	rlwimi r0, r3, 1, 0x1a, 0x1a
/* 803B2EC4 003AFAA4  50 60 FE F6 */	rlwimi r0, r3, 0x1f, 0x1b, 0x1b
/* 803B2EC8 003AFAA8  50 60 0E 30 */	rlwimi r0, r3, 1, 0x18, 0x18
/* 803B2ECC 003AFAAC  50 60 D7 BC */	rlwimi r0, r3, 0x1a, 0x1e, 0x1e
/* 803B2ED0 003AFAB0  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2ED4 003AFAB4  4E 80 00 20 */	blr 
lbl_803B2ED8:
/* 803B2ED8 003AFAB8  54 60 26 B4 */	rlwinm r0, r3, 4, 0x1a, 0x1a
/* 803B2EDC 003AFABC  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 803B2EE0 003AFAC0  50 60 F7 FE */	rlwimi r0, r3, 0x1e, 0x1f, 0x1f
/* 803B2EE4 003AFAC4  50 60 F7 BC */	rlwimi r0, r3, 0x1e, 0x1e, 0x1e
/* 803B2EE8 003AFAC8  50 60 FF 38 */	rlwimi r0, r3, 0x1f, 0x1c, 0x1c
/* 803B2EEC 003AFACC  50 60 16 30 */	rlwimi r0, r3, 2, 0x18, 0x18
/* 803B2EF0 003AFAD0  50 60 E7 7A */	rlwimi r0, r3, 0x1c, 0x1d, 0x1d
/* 803B2EF4 003AFAD4  50 60 EE F6 */	rlwimi r0, r3, 0x1d, 0x1b, 0x1b
/* 803B2EF8 003AFAD8  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2EFC 003AFADC  4E 80 00 20 */	blr 
lbl_803B2F00:
/* 803B2F00 003AFAE0  54 60 17 38 */	rlwinm r0, r3, 2, 0x1c, 0x1c
/* 803B2F04 003AFAE4  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 803B2F08 003AFAE8  50 60 2E 30 */	rlwimi r0, r3, 5, 0x18, 0x18
/* 803B2F0C 003AFAEC  50 60 0E F6 */	rlwimi r0, r3, 1, 0x1b, 0x1b
/* 803B2F10 003AFAF0  50 60 E7 FE */	rlwimi r0, r3, 0x1c, 0x1f, 0x1f
/* 803B2F14 003AFAF4  50 60 EF 7A */	rlwimi r0, r3, 0x1d, 0x1d, 0x1d
/* 803B2F18 003AFAF8  50 60 FE B4 */	rlwimi r0, r3, 0x1f, 0x1a, 0x1a
/* 803B2F1C 003AFAFC  50 60 FE 72 */	rlwimi r0, r3, 0x1f, 0x19, 0x19
/* 803B2F20 003AFB00  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2F24 003AFB04  4E 80 00 20 */	blr 
lbl_803B2F28:
/* 803B2F28 003AFB08  54 60 0F 7A */	rlwinm r0, r3, 1, 0x1d, 0x1d
/* 803B2F2C 003AFB0C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 803B2F30 003AFB10  50 60 1E B4 */	rlwimi r0, r3, 3, 0x1a, 0x1a
/* 803B2F34 003AFB14  50 60 EF FE */	rlwimi r0, r3, 0x1d, 0x1f, 0x1f
/* 803B2F38 003AFB18  50 60 16 72 */	rlwimi r0, r3, 2, 0x19, 0x19
/* 803B2F3C 003AFB1C  50 60 E7 BC */	rlwimi r0, r3, 0x1c, 0x1e, 0x1e
/* 803B2F40 003AFB20  50 60 F6 F6 */	rlwimi r0, r3, 0x1e, 0x1b, 0x1b
/* 803B2F44 003AFB24  50 60 E7 38 */	rlwimi r0, r3, 0x1c, 0x1c, 0x1c
/* 803B2F48 003AFB28  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2F4C 003AFB2C  4E 80 00 20 */	blr 
lbl_803B2F50:
/* 803B2F50 003AFB30  54 60 2E 72 */	rlwinm r0, r3, 5, 0x19, 0x19
/* 803B2F54 003AFB34  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 803B2F58 003AFB38  50 60 16 F6 */	rlwimi r0, r3, 2, 0x1b, 0x1b
/* 803B2F5C 003AFB3C  50 60 07 38 */	rlwimi r0, r3, 0, 0x1c, 0x1c
/* 803B2F60 003AFB40  50 60 1E 30 */	rlwimi r0, r3, 3, 0x18, 0x18
/* 803B2F64 003AFB44  50 60 DF FE */	rlwimi r0, r3, 0x1b, 0x1f, 0x1f
/* 803B2F68 003AFB48  50 60 DF BC */	rlwimi r0, r3, 0x1b, 0x1e, 0x1e
/* 803B2F6C 003AFB4C  50 60 DF 7A */	rlwimi r0, r3, 0x1b, 0x1d, 0x1d
/* 803B2F70 003AFB50  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2F74 003AFB54  4E 80 00 20 */	blr 
lbl_803B2F78:
/* 803B2F78 003AFB58  54 60 07 BC */	rlwinm r0, r3, 0, 0x1e, 0x1e
/* 803B2F7C 003AFB5C  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 803B2F80 003AFB60  50 60 26 72 */	rlwimi r0, r3, 4, 0x19, 0x19
/* 803B2F84 003AFB64  50 60 26 30 */	rlwimi r0, r3, 4, 0x18, 0x18
/* 803B2F88 003AFB68  50 60 06 F6 */	rlwimi r0, r3, 0, 0x1b, 0x1b
/* 803B2F8C 003AFB6C  50 60 F7 38 */	rlwimi r0, r3, 0x1e, 0x1c, 0x1c
/* 803B2F90 003AFB70  50 60 D7 FE */	rlwimi r0, r3, 0x1a, 0x1f, 0x1f
/* 803B2F94 003AFB74  50 60 F6 B4 */	rlwimi r0, r3, 0x1e, 0x1a, 0x1a
/* 803B2F98 003AFB78  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803B2F9C 003AFB7C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/2HBMp // 1864 (46.74%)
.global func_803B2FA0
func_803B2FA0:
/* 803B2FA0 003AFB80  7C 08 02 A6 */	mflr r0
/* 803B2FA4 003AFB84  90 01 00 04 */	stw r0, 4(r1)
/* 803B2FA8 003AFB88  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803B2FAC 003AFB8C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803B2FB0 003AFB90  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803B2FB4 003AFB94  93 A1 00 14 */	stw r29, 0x14(r1)
/* 803B2FB8 003AFB98  3B A4 00 00 */	addi r29, r4, 0
/* 803B2FBC 003AFB9C  93 81 00 10 */	stw r28, 0x10(r1)
/* 803B2FC0 003AFBA0  7C 7C 1B 79 */	or. r28, r3, r3
/* 803B2FC4 003AFBA4  40 82 00 0C */	bne lbl_803B2FD0
/* 803B2FC8 003AFBA8  38 60 FF FF */	li r3, -1
/* 803B2FCC 003AFBAC  48 00 00 40 */	b lbl_803B300C
lbl_803B2FD0:
/* 803B2FD0 003AFBB0  38 BC 00 00 */	addi r5, r28, 0
/* 803B2FD4 003AFBB4  38 7C 00 10 */	addi r3, r28, 0x10
/* 803B2FD8 003AFBB8  38 9D FF F0 */	addi r4, r29, -16
/* 803B2FDC 003AFBBC  4B FF FB 45 */	bl func_803B2B20
/* 803B2FE0 003AFBC0  3B C0 00 10 */	li r30, 0x10
/* 803B2FE4 003AFBC4  48 00 00 1C */	b lbl_803B3000
lbl_803B2FE8:
/* 803B2FE8 003AFBC8  7F FC F2 14 */	add r31, r28, r30
/* 803B2FEC 003AFBCC  88 7F FF FF */	lbz r3, -1(r31)
/* 803B2FF0 003AFBD0  88 9F 00 00 */	lbz r4, 0(r31)
/* 803B2FF4 003AFBD4  4B FF FE 11 */	bl func_803B2E04
/* 803B2FF8 003AFBD8  98 7F 00 00 */	stb r3, 0(r31)
/* 803B2FFC 003AFBDC  3B DE 00 01 */	addi r30, r30, 1
lbl_803B3000:
/* 803B3000 003AFBE0  7C 1E E8 00 */	cmpw r30, r29
/* 803B3004 003AFBE4  41 80 FF E4 */	blt lbl_803B2FE8
/* 803B3008 003AFBE8  38 60 00 00 */	li r3, 0
lbl_803B300C:
/* 803B300C 003AFBEC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 803B3010 003AFBF0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 803B3014 003AFBF4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 803B3018 003AFBF8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 803B301C 003AFBFC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 803B3020 003AFC00  38 21 00 20 */	addi r1, r1, 0x20
/* 803B3024 003AFC04  7C 08 03 A6 */	mtlr r0
/* 803B3028 003AFC08  4E 80 00 20 */	blr 

.section .data
    .balign 4

jtbl_80430C20:
	.4byte lbl_803B3074
	.4byte lbl_803B309C
	.4byte lbl_803B30C4
	.4byte lbl_803B30EC
	.4byte lbl_803B3114
	.4byte lbl_803B313C
	.4byte lbl_803B3164
    .4byte NULL

.section .text
# https://decomp.me/scratch/cheus
func_803B302C:
/* 803B302C 003AFC0C  3C A0 92 49 */	lis r5, 0x92492493@ha
/* 803B3030 003AFC10  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 803B3034 003AFC14  38 A5 24 93 */	addi r5, r5, 0x92492493@l
/* 803B3038 003AFC18  7C A5 00 96 */	mulhw r5, r5, r0
/* 803B303C 003AFC1C  7C A5 02 14 */	add r5, r5, r0
/* 803B3040 003AFC20  7C A5 16 70 */	srawi r5, r5, 2
/* 803B3044 003AFC24  54 A6 0F FE */	srwi r6, r5, 0x1f
/* 803B3048 003AFC28  7C A5 32 14 */	add r5, r5, r6
/* 803B304C 003AFC2C  1C A5 00 07 */	mulli r5, r5, 7
/* 803B3050 003AFC30  7C E5 00 50 */	subf r7, r5, r0
/* 803B3054 003AFC34  28 07 00 06 */	cmplwi r7, 6
/* 803B3058 003AFC38  41 81 01 30 */	bgt lbl_803B3188
/* 803B305C 003AFC3C  3C A0 80 43 */	lis r5, jtbl_80430C20@ha
/* 803B3060 003AFC40  38 C5 0C 20 */	addi r6, r5, jtbl_80430C20@l
/* 803B3064 003AFC44  54 E5 10 3A */	slwi r5, r7, 2
/* 803B3068 003AFC48  7C A6 28 2E */	lwzx r5, r6, r5
/* 803B306C 003AFC4C  7C A9 03 A6 */	mtctr r5
/* 803B3070 003AFC50  4E 80 04 20 */	bctr 
lbl_803B3074:
/* 803B3074 003AFC54  54 85 0F 7A */	rlwinm r5, r4, 1, 0x1d, 0x1d
/* 803B3078 003AFC58  50 85 07 FE */	rlwimi r5, r4, 0, 0x1f, 0x1f
/* 803B307C 003AFC5C  50 85 16 F6 */	rlwimi r5, r4, 2, 0x1b, 0x1b
/* 803B3080 003AFC60  50 85 1E 72 */	rlwimi r5, r4, 3, 0x19, 0x19
/* 803B3084 003AFC64  50 85 EF BC */	rlwimi r5, r4, 0x1d, 0x1e, 0x1e
/* 803B3088 003AFC68  50 85 F7 38 */	rlwimi r5, r4, 0x1e, 0x1c, 0x1c
/* 803B308C 003AFC6C  50 85 FE B4 */	rlwimi r5, r4, 0x1f, 0x1a, 0x1a
/* 803B3090 003AFC70  50 85 06 30 */	rlwimi r5, r4, 0, 0x18, 0x18
/* 803B3094 003AFC74  54 A4 06 3E */	clrlwi r4, r5, 0x18
/* 803B3098 003AFC78  48 00 00 F0 */	b lbl_803B3188
lbl_803B309C:
/* 803B309C 003AFC7C  54 85 36 30 */	rlwinm r5, r4, 6, 0x18, 0x18
/* 803B30A0 003AFC80  50 85 0F BC */	rlwimi r5, r4, 1, 0x1e, 0x1e
/* 803B30A4 003AFC84  50 85 07 7A */	rlwimi r5, r4, 0, 0x1d, 0x1d
/* 803B30A8 003AFC88  50 85 EF FE */	rlwimi r5, r4, 0x1d, 0x1f, 0x1f
/* 803B30AC 003AFC8C  50 85 0E B4 */	rlwimi r5, r4, 1, 0x1a, 0x1a
/* 803B30B0 003AFC90  50 85 FE F6 */	rlwimi r5, r4, 0x1f, 0x1b, 0x1b
/* 803B30B4 003AFC94  50 85 EF 38 */	rlwimi r5, r4, 0x1d, 0x1c, 0x1c
/* 803B30B8 003AFC98  50 85 FE 72 */	rlwimi r5, r4, 0x1f, 0x19, 0x19
/* 803B30BC 003AFC9C  54 A4 06 3E */	clrlwi r4, r5, 0x18
/* 803B30C0 003AFCA0  48 00 00 C8 */	b lbl_803B3188
lbl_803B30C4:
/* 803B30C4 003AFCA4  54 85 17 38 */	rlwinm r5, r4, 2, 0x1c, 0x1c
/* 803B30C8 003AFCA8  50 85 17 7A */	rlwimi r5, r4, 2, 0x1d, 0x1d
/* 803B30CC 003AFCAC  50 85 26 72 */	rlwimi r5, r4, 4, 0x19, 0x19
/* 803B30D0 003AFCB0  50 85 0E F6 */	rlwimi r5, r4, 1, 0x1b, 0x1b
/* 803B30D4 003AFCB4  50 85 1E 30 */	rlwimi r5, r4, 3, 0x18, 0x18
/* 803B30D8 003AFCB8  50 85 E7 BC */	rlwimi r5, r4, 0x1c, 0x1e, 0x1e
/* 803B30DC 003AFCBC  50 85 D7 FE */	rlwimi r5, r4, 0x1a, 0x1f, 0x1f
/* 803B30E0 003AFCC0  50 85 F6 B4 */	rlwimi r5, r4, 0x1e, 0x1a, 0x1a
/* 803B30E4 003AFCC4  54 A4 06 3E */	clrlwi r4, r5, 0x18
/* 803B30E8 003AFCC8  48 00 00 A0 */	b lbl_803B3188
lbl_803B30EC:
/* 803B30EC 003AFCCC  54 85 FF FE */	rlwinm r5, r4, 0x1f, 0x1f, 0x1f
/* 803B30F0 003AFCD0  50 85 26 F6 */	rlwimi r5, r4, 4, 0x1b, 0x1b
/* 803B30F4 003AFCD4  50 85 1E B4 */	rlwimi r5, r4, 3, 0x1a, 0x1a
/* 803B30F8 003AFCD8  50 85 F7 BC */	rlwimi r5, r4, 0x1e, 0x1e, 0x1e
/* 803B30FC 003AFCDC  50 85 FF 38 */	rlwimi r5, r4, 0x1f, 0x1c, 0x1c
/* 803B3100 003AFCE0  50 85 0E 72 */	rlwimi r5, r4, 1, 0x19, 0x19
/* 803B3104 003AFCE4  50 85 0E 30 */	rlwimi r5, r4, 1, 0x18, 0x18
/* 803B3108 003AFCE8  50 85 DF 7A */	rlwimi r5, r4, 0x1b, 0x1d, 0x1d
/* 803B310C 003AFCEC  54 A4 06 3E */	clrlwi r4, r5, 0x18
/* 803B3110 003AFCF0  48 00 00 78 */	b lbl_803B3188
lbl_803B3114:
/* 803B3114 003AFCF4  54 85 26 B4 */	rlwinm r5, r4, 4, 0x1a, 0x1a
/* 803B3118 003AFCF8  50 85 1F 38 */	rlwimi r5, r4, 3, 0x1c, 0x1c
/* 803B311C 003AFCFC  50 85 FF BC */	rlwimi r5, r4, 0x1f, 0x1e, 0x1e
/* 803B3120 003AFD00  50 85 26 30 */	rlwimi r5, r4, 4, 0x18, 0x18
/* 803B3124 003AFD04  50 85 16 72 */	rlwimi r5, r4, 2, 0x19, 0x19
/* 803B3128 003AFD08  50 85 EF 7A */	rlwimi r5, r4, 0x1d, 0x1d, 0x1d
/* 803B312C 003AFD0C  50 85 F6 F6 */	rlwimi r5, r4, 0x1e, 0x1b, 0x1b
/* 803B3130 003AFD10  50 85 CF FE */	rlwimi r5, r4, 0x19, 0x1f, 0x1f
/* 803B3134 003AFD14  54 A4 06 3E */	clrlwi r4, r5, 0x18
/* 803B3138 003AFD18  48 00 00 50 */	b lbl_803B3188
lbl_803B313C:
/* 803B313C 003AFD1C  54 85 2E 72 */	rlwinm r5, r4, 5, 0x19, 0x19
/* 803B3140 003AFD20  50 85 2E B4 */	rlwimi r5, r4, 5, 0x1a, 0x1a
/* 803B3144 003AFD24  50 85 2E 30 */	rlwimi r5, r4, 5, 0x18, 0x18
/* 803B3148 003AFD28  50 85 07 38 */	rlwimi r5, r4, 0, 0x1c, 0x1c
/* 803B314C 003AFD2C  50 85 F7 7A */	rlwimi r5, r4, 0x1e, 0x1d, 0x1d
/* 803B3150 003AFD30  50 85 DF FE */	rlwimi r5, r4, 0x1b, 0x1f, 0x1f
/* 803B3154 003AFD34  50 85 DF BC */	rlwimi r5, r4, 0x1b, 0x1e, 0x1e
/* 803B3158 003AFD38  50 85 EE F6 */	rlwimi r5, r4, 0x1d, 0x1b, 0x1b
/* 803B315C 003AFD3C  54 A4 06 3E */	clrlwi r4, r5, 0x18
/* 803B3160 003AFD40  48 00 00 28 */	b lbl_803B3188
lbl_803B3164:
/* 803B3164 003AFD44  54 85 07 BC */	rlwinm r5, r4, 0, 0x1e, 0x1e
/* 803B3168 003AFD48  50 85 36 72 */	rlwimi r5, r4, 6, 0x19, 0x19
/* 803B316C 003AFD4C  50 85 F7 FE */	rlwimi r5, r4, 0x1e, 0x1f, 0x1f
/* 803B3170 003AFD50  50 85 16 B4 */	rlwimi r5, r4, 2, 0x1a, 0x1a
/* 803B3174 003AFD54  50 85 06 F6 */	rlwimi r5, r4, 0, 0x1b, 0x1b
/* 803B3178 003AFD58  50 85 16 30 */	rlwimi r5, r4, 2, 0x18, 0x18
/* 803B317C 003AFD5C  50 85 E7 7A */	rlwimi r5, r4, 0x1c, 0x1d, 0x1d
/* 803B3180 003AFD60  50 85 E7 38 */	rlwimi r5, r4, 0x1c, 0x1c, 0x1c
/* 803B3184 003AFD64  54 A4 06 3E */	clrlwi r4, r5, 0x18
lbl_803B3188:
/* 803B3188 003AFD68  3C A0 4E C5 */	lis r5, 0x4EC4EC4F@ha
/* 803B318C 003AFD6C  38 A5 EC 4F */	addi r5, r5, 0x4EC4EC4F@l
/* 803B3190 003AFD70  7C A5 00 96 */	mulhw r5, r5, r0
/* 803B3194 003AFD74  7C A5 16 70 */	srawi r5, r5, 2
/* 803B3198 003AFD78  54 A6 0F FE */	srwi r6, r5, 0x1f
/* 803B319C 003AFD7C  7C A5 32 14 */	add r5, r5, r6
/* 803B31A0 003AFD80  1C A5 00 0D */	mulli r5, r5, 0xd
/* 803B31A4 003AFD84  7C 05 00 50 */	subf r0, r5, r0
/* 803B31A8 003AFD88  3C A0 80 43 */	lis r5, lbl_80430BD0@ha
/* 803B31AC 003AFD8C  54 06 10 3A */	slwi r6, r0, 2
/* 803B31B0 003AFD90  38 05 0B D0 */	addi r0, r5, lbl_80430BD0@l
/* 803B31B4 003AFD94  7C A0 32 14 */	add r5, r0, r6
/* 803B31B8 003AFD98  80 05 00 00 */	lwz r0, 0(r5)
/* 803B31BC 003AFD9C  7C 84 02 78 */	xor r4, r4, r0
/* 803B31C0 003AFDA0  7C 84 1A 78 */	xor r4, r4, r3
/* 803B31C4 003AFDA4  38 64 00 00 */	addi r3, r4, 0
/* 803B31C8 003AFDA8  4E 80 00 20 */	blr 

# https://decomp.me/scratch/vZixu
.global func_803B31CC
func_803B31CC:
/* 803B31CC 003AFDAC  7C 08 02 A6 */	mflr r0
/* 803B31D0 003AFDB0  90 01 00 04 */	stw r0, 4(r1)
/* 803B31D4 003AFDB4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 803B31D8 003AFDB8  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 803B31DC 003AFDBC  7C 7B 1B 79 */	or. r27, r3, r3
/* 803B31E0 003AFDC0  3B 84 00 00 */	addi r28, r4, 0
/* 803B31E4 003AFDC4  40 82 00 0C */	bne lbl_803B31F0
/* 803B31E8 003AFDC8  38 60 FF FF */	li r3, -1
/* 803B31EC 003AFDCC  48 00 01 44 */	b lbl_803B3330
lbl_803B31F0:
/* 803B31F0 003AFDD0  88 7B 00 0F */	lbz r3, 0xf(r27)
/* 803B31F4 003AFDD4  3B C0 00 10 */	li r30, 0x10
/* 803B31F8 003AFDD8  48 00 00 20 */	b lbl_803B3218
lbl_803B31FC:
/* 803B31FC 003AFDDC  7F FB F2 14 */	add r31, r27, r30
/* 803B3200 003AFDE0  88 9F 00 00 */	lbz r4, 0(r31)
/* 803B3204 003AFDE4  7C 9D 23 78 */	mr r29, r4
/* 803B3208 003AFDE8  4B FF FE 25 */	bl func_803B302C
/* 803B320C 003AFDEC  98 7F 00 00 */	stb r3, 0(r31)
/* 803B3210 003AFDF0  38 7D 00 00 */	addi r3, r29, 0
/* 803B3214 003AFDF4  3B DE 00 01 */	addi r30, r30, 1
lbl_803B3218:
/* 803B3218 003AFDF8  7C 1E E0 00 */	cmpw r30, r28
/* 803B321C 003AFDFC  41 80 FF E0 */	blt lbl_803B31FC
/* 803B3220 003AFE00  38 7B 00 10 */	addi r3, r27, 0x10
/* 803B3224 003AFE04  38 9C FF F0 */	addi r4, r28, -16
/* 803B3228 003AFE08  38 A1 00 10 */	addi r5, r1, 0x10
/* 803B322C 003AFE0C  4B FF F8 F5 */	bl func_803B2B20
/* 803B3230 003AFE10  38 00 00 02 */	li r0, 2
/* 803B3234 003AFE14  7C 09 03 A6 */	mtctr r0
/* 803B3238 003AFE18  38 7B 00 00 */	addi r3, r27, 0
/* 803B323C 003AFE1C  38 A1 00 10 */	addi r5, r1, 0x10
/* 803B3240 003AFE20  38 C0 00 00 */	li r6, 0
lbl_803B3244:
/* 803B3244 003AFE24  88 85 00 00 */	lbz r4, 0(r5)
/* 803B3248 003AFE28  88 03 00 00 */	lbz r0, 0(r3)
/* 803B324C 003AFE2C  7C 04 00 40 */	cmplw r4, r0
/* 803B3250 003AFE30  41 82 00 0C */	beq lbl_803B325C
/* 803B3254 003AFE34  38 60 FF FF */	li r3, -1
/* 803B3258 003AFE38  48 00 00 D8 */	b lbl_803B3330
lbl_803B325C:
/* 803B325C 003AFE3C  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B3260 003AFE40  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B3264 003AFE44  7C 04 00 40 */	cmplw r4, r0
/* 803B3268 003AFE48  41 82 00 0C */	beq lbl_803B3274
/* 803B326C 003AFE4C  38 60 FF FF */	li r3, -1
/* 803B3270 003AFE50  48 00 00 C0 */	b lbl_803B3330
lbl_803B3274:
/* 803B3274 003AFE54  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B3278 003AFE58  38 C6 00 01 */	addi r6, r6, 1
/* 803B327C 003AFE5C  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B3280 003AFE60  7C 04 00 40 */	cmplw r4, r0
/* 803B3284 003AFE64  41 82 00 0C */	beq lbl_803B3290
/* 803B3288 003AFE68  38 60 FF FF */	li r3, -1
/* 803B328C 003AFE6C  48 00 00 A4 */	b lbl_803B3330
lbl_803B3290:
/* 803B3290 003AFE70  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B3294 003AFE74  38 C6 00 01 */	addi r6, r6, 1
/* 803B3298 003AFE78  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B329C 003AFE7C  7C 04 00 40 */	cmplw r4, r0
/* 803B32A0 003AFE80  41 82 00 0C */	beq lbl_803B32AC
/* 803B32A4 003AFE84  38 60 FF FF */	li r3, -1
/* 803B32A8 003AFE88  48 00 00 88 */	b lbl_803B3330
lbl_803B32AC:
/* 803B32AC 003AFE8C  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B32B0 003AFE90  38 C6 00 01 */	addi r6, r6, 1
/* 803B32B4 003AFE94  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B32B8 003AFE98  7C 04 00 40 */	cmplw r4, r0
/* 803B32BC 003AFE9C  41 82 00 0C */	beq lbl_803B32C8
/* 803B32C0 003AFEA0  38 60 FF FF */	li r3, -1
/* 803B32C4 003AFEA4  48 00 00 6C */	b lbl_803B3330
lbl_803B32C8:
/* 803B32C8 003AFEA8  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B32CC 003AFEAC  38 C6 00 01 */	addi r6, r6, 1
/* 803B32D0 003AFEB0  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B32D4 003AFEB4  7C 04 00 40 */	cmplw r4, r0
/* 803B32D8 003AFEB8  41 82 00 0C */	beq lbl_803B32E4
/* 803B32DC 003AFEBC  38 60 FF FF */	li r3, -1
/* 803B32E0 003AFEC0  48 00 00 50 */	b lbl_803B3330
lbl_803B32E4:
/* 803B32E4 003AFEC4  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B32E8 003AFEC8  38 C6 00 01 */	addi r6, r6, 1
/* 803B32EC 003AFECC  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B32F0 003AFED0  7C 04 00 40 */	cmplw r4, r0
/* 803B32F4 003AFED4  41 82 00 0C */	beq lbl_803B3300
/* 803B32F8 003AFED8  38 60 FF FF */	li r3, -1
/* 803B32FC 003AFEDC  48 00 00 34 */	b lbl_803B3330
lbl_803B3300:
/* 803B3300 003AFEE0  8C 85 00 01 */	lbzu r4, 1(r5)
/* 803B3304 003AFEE4  38 C6 00 01 */	addi r6, r6, 1
/* 803B3308 003AFEE8  8C 03 00 01 */	lbzu r0, 1(r3)
/* 803B330C 003AFEEC  7C 04 00 40 */	cmplw r4, r0
/* 803B3310 003AFEF0  41 82 00 0C */	beq lbl_803B331C
/* 803B3314 003AFEF4  38 60 FF FF */	li r3, -1
/* 803B3318 003AFEF8  48 00 00 18 */	b lbl_803B3330
lbl_803B331C:
/* 803B331C 003AFEFC  38 A5 00 01 */	addi r5, r5, 1
/* 803B3320 003AFF00  38 C6 00 01 */	addi r6, r6, 1
/* 803B3324 003AFF04  38 63 00 01 */	addi r3, r3, 1
/* 803B3328 003AFF08  42 00 FF 1C */	bdnz lbl_803B3244
/* 803B332C 003AFF0C  38 60 00 00 */	li r3, 0
lbl_803B3330:
/* 803B3330 003AFF10  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 803B3334 003AFF14  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 803B3338 003AFF18  38 21 00 38 */	addi r1, r1, 0x38
/* 803B333C 003AFF1C  7C 08 03 A6 */	mtlr r0
/* 803B3340 003AFF20  4E 80 00 20 */	blr 
