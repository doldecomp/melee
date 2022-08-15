.include "macros.inc"

.section .data
    .balign 8

struct_803BB0B0:
    .asciz "?"
    .balign 4
    .4byte NULL
    .4byte NULL
    .4byte 0x3F000000
    .4byte NULL
    .4byte 0xBF000000
    .4byte NULL
    .4byte 0x3F000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000

.section .text

# https://decomp.me/scratch/2RGzd
.global func_800222A4
func_800222A4:
/* 800222A4 0001EE84  7C 08 02 A6 */	mflr r0
/* 800222A8 0001EE88  3C 80 80 43 */	lis r4, skip40_804336D0@ha
/* 800222AC 0001EE8C  90 01 00 04 */	stw r0, 4(r1)
/* 800222B0 0001EE90  3C 60 80 3C */	lis r3, struct_803BB0B0@ha
/* 800222B4 0001EE94  4C C6 31 82 */	crclr 6
/* 800222B8 0001EE98  38 C0 00 00 */	li r6, 0
/* 800222BC 0001EE9C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800222C0 0001EEA0  BE E1 00 34 */	stmw r23, 0x34(r1)
/* 800222C4 0001EEA4  3B C3 B0 B0 */	addi r30, r3, struct_803BB0B0@l
/* 800222C8 0001EEA8  3A E4 36 D0 */	addi r23, r4, skip40_804336D0@l
/* 800222CC 0001EEAC  3B E0 00 00 */	li r31, 0
/* 800222D0 0001EEB0  38 7E 01 50 */	addi r3, r30, 0x150
/* 800222D4 0001EEB4  38 BE 01 5C */	addi r5, r30, 0x15c
/* 800222D8 0001EEB8  38 8D AD 48 */	addi r4, r13, skip8_804D63E8@sda21
/* 800222DC 0001EEBC  93 F7 00 00 */	stw r31, 0(r23)
/* 800222E0 0001EEC0  4B FF 49 85 */	bl func_80016C64
/* 800222E4 0001EEC4  38 60 01 40 */	li r3, 0x140
/* 800222E8 0001EEC8  38 80 00 F0 */	li r4, 0xf0
/* 800222EC 0001EECC  38 A0 00 04 */	li r5, 4
/* 800222F0 0001EED0  38 C0 00 00 */	li r6, 0
/* 800222F4 0001EED4  38 E0 00 00 */	li r7, 0
/* 800222F8 0001EED8  48 31 C4 95 */	bl func_8033E78C
/* 800222FC 0001EEDC  7C 78 1B 78 */	mr r24, r3
/* 80022300 0001EEE0  48 35 CE E5 */	bl HSD_MemAlloc
/* 80022304 0001EEE4  3B 77 00 04 */	addi r27, r23, 4
/* 80022308 0001EEE8  90 77 00 04 */	stw r3, 4(r23)
/* 8002230C 0001EEEC  38 B8 00 00 */	addi r5, r24, 0
/* 80022310 0001EEF0  38 80 00 00 */	li r4, 0
/* 80022314 0001EEF4  80 77 00 04 */	lwz r3, 4(r23)
/* 80022318 0001EEF8  4B FE 0D E9 */	bl memset
/* 8002231C 0001EEFC  80 6D AD 48 */	lwz r3, skip8_804D63E8@sda21(r13)
/* 80022320 0001EF00  88 03 00 00 */	lbz r0, 0(r3)
/* 80022324 0001EF04  54 03 10 3A */	slwi r3, r0, 2
/* 80022328 0001EF08  48 35 CE BD */	bl HSD_MemAlloc
/* 8002232C 0001EF0C  3B 37 00 0C */	addi r25, r23, 0xc
/* 80022330 0001EF10  90 77 00 0C */	stw r3, 0xc(r23)
/* 80022334 0001EF14  80 6D AD 48 */	lwz r3, skip8_804D63E8@sda21(r13)
/* 80022338 0001EF18  88 03 00 00 */	lbz r0, 0(r3)
/* 8002233C 0001EF1C  1C 60 00 18 */	mulli r3, r0, 0x18
/* 80022340 0001EF20  48 35 CE A5 */	bl HSD_MemAlloc
/* 80022344 0001EF24  90 77 00 08 */	stw r3, 8(r23)
/* 80022348 0001EF28  3B 57 00 08 */	addi r26, r23, 8
/* 8002234C 0001EF2C  3B BF 00 00 */	addi r29, r31, 0
/* 80022350 0001EF30  3B 9F 00 00 */	addi r28, r31, 0
/* 80022354 0001EF34  3B 00 00 00 */	li r24, 0
/* 80022358 0001EF38  48 00 01 00 */	b lbl_80022458
lbl_8002235C:
/* 8002235C 0001EF3C  38 60 00 20 */	li r3, 0x20
/* 80022360 0001EF40  38 80 00 20 */	li r4, 0x20
/* 80022364 0001EF44  38 A0 00 03 */	li r5, 3
/* 80022368 0001EF48  38 C0 00 00 */	li r6, 0
/* 8002236C 0001EF4C  38 E0 00 00 */	li r7, 0
/* 80022370 0001EF50  48 31 C4 1D */	bl func_8033E78C
/* 80022374 0001EF54  48 35 CE 71 */	bl HSD_MemAlloc
/* 80022378 0001EF58  3A E3 00 00 */	addi r23, r3, 0
/* 8002237C 0001EF5C  38 97 00 00 */	addi r4, r23, 0
/* 80022380 0001EF60  38 61 00 0C */	addi r3, r1, 0xc
/* 80022384 0001EF64  38 A0 00 03 */	li r5, 3
/* 80022388 0001EF68  38 C0 00 20 */	li r6, 0x20
/* 8002238C 0001EF6C  38 E0 00 20 */	li r7, 0x20
/* 80022390 0001EF70  4B FF FE 0D */	bl local_8002219C
/* 80022394 0001EF74  38 61 00 0C */	addi r3, r1, 0xc
/* 80022398 0001EF78  38 98 00 00 */	addi r4, r24, 0
/* 8002239C 0001EF7C  4B FF F9 4D */	bl local_80021CE8
/* 800223A0 0001EF80  80 BA 00 00 */	lwz r5, 0(r26)
/* 800223A4 0001EF84  38 7E 00 F4 */	addi r3, r30, 0xf4
/* 800223A8 0001EF88  80 9E 00 48 */	lwz r4, 0x48(r30)
/* 800223AC 0001EF8C  80 1E 00 4C */	lwz r0, 0x4c(r30)
/* 800223B0 0001EF90  7C A5 EA 14 */	add r5, r5, r29
/* 800223B4 0001EF94  90 85 00 00 */	stw r4, 0(r5)
/* 800223B8 0001EF98  90 05 00 04 */	stw r0, 4(r5)
/* 800223BC 0001EF9C  80 9E 00 50 */	lwz r4, 0x50(r30)
/* 800223C0 0001EFA0  80 1E 00 54 */	lwz r0, 0x54(r30)
/* 800223C4 0001EFA4  90 85 00 08 */	stw r4, 8(r5)
/* 800223C8 0001EFA8  90 05 00 0C */	stw r0, 0xc(r5)
/* 800223CC 0001EFAC  80 9E 00 58 */	lwz r4, 0x58(r30)
/* 800223D0 0001EFB0  80 1E 00 5C */	lwz r0, 0x5c(r30)
/* 800223D4 0001EFB4  90 85 00 10 */	stw r4, 0x10(r5)
/* 800223D8 0001EFB8  90 05 00 14 */	stw r0, 0x14(r5)
/* 800223DC 0001EFBC  80 1A 00 00 */	lwz r0, 0(r26)
/* 800223E0 0001EFC0  7C 00 EA 14 */	add r0, r0, r29
/* 800223E4 0001EFC4  90 1E 01 40 */	stw r0, 0x140(r30)
/* 800223E8 0001EFC8  48 33 C9 41 */	bl HSD_TObjLoadDesc
/* 800223EC 0001EFCC  80 99 00 00 */	lwz r4, 0(r25)
/* 800223F0 0001EFD0  39 20 00 04 */	li r9, 4
/* 800223F4 0001EFD4  39 00 01 40 */	li r8, 0x140
/* 800223F8 0001EFD8  7C 64 E1 2E */	stwx r3, r4, r28
/* 800223FC 0001EFDC  38 C0 00 F0 */	li r6, 0xf0
/* 80022400 0001EFE0  38 9F 00 08 */	addi r4, r31, 8
/* 80022404 0001EFE4  80 1B 00 00 */	lwz r0, 0(r27)
/* 80022408 0001EFE8  38 E0 00 03 */	li r7, 3
/* 8002240C 0001EFEC  38 7F 00 04 */	addi r3, r31, 4
/* 80022410 0001EFF0  90 1E 00 48 */	stw r0, 0x48(r30)
/* 80022414 0001EFF4  38 A0 00 20 */	li r5, 0x20
/* 80022418 0001EFF8  38 1F 00 06 */	addi r0, r31, 6
/* 8002241C 0001EFFC  91 3E 00 50 */	stw r9, 0x50(r30)
/* 80022420 0001F000  3B BD 00 18 */	addi r29, r29, 0x18
/* 80022424 0001F004  3B 9C 00 04 */	addi r28, r28, 4
/* 80022428 0001F008  B1 1E 00 4C */	sth r8, 0x4c(r30)
/* 8002242C 0001F00C  3B 18 00 01 */	addi r24, r24, 1
/* 80022430 0001F010  B0 DE 00 4E */	sth r6, 0x4e(r30)
/* 80022434 0001F014  80 DA 00 00 */	lwz r6, 0(r26)
/* 80022438 0001F018  7E E6 F9 2E */	stwx r23, r6, r31
/* 8002243C 0001F01C  3B FF 00 18 */	addi r31, r31, 0x18
/* 80022440 0001F020  80 DA 00 00 */	lwz r6, 0(r26)
/* 80022444 0001F024  7C E6 21 2E */	stwx r7, r6, r4
/* 80022448 0001F028  80 9A 00 00 */	lwz r4, 0(r26)
/* 8002244C 0001F02C  7C A4 1B 2E */	sthx r5, r4, r3
/* 80022450 0001F030  80 7A 00 00 */	lwz r3, 0(r26)
/* 80022454 0001F034  7C A3 03 2E */	sthx r5, r3, r0
lbl_80022458:
/* 80022458 0001F038  80 6D AD 48 */	lwz r3, skip8_804D63E8@sda21(r13)
/* 8002245C 0001F03C  88 03 00 00 */	lbz r0, 0(r3)
/* 80022460 0001F040  7C 18 00 40 */	cmplw r24, r0
/* 80022464 0001F044  41 80 FE F8 */	blt lbl_8002235C
/* 80022468 0001F048  BA E1 00 34 */	lmw r23, 0x34(r1)
/* 8002246C 0001F04C  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80022470 0001F050  38 21 00 58 */	addi r1, r1, 0x58
/* 80022474 0001F054  7C 08 03 A6 */	mtlr r0
/* 80022478 0001F058  4E 80 00 20 */	blr 

.section .sdata2
    .balign 8

lbl_804D7DA8:
	.float 0.5
lbl_804D7DAC:
	.float -0.5

.section .text

# https://decomp.me/scratch/aGGLH
.global func_8002247C
func_8002247C:
/* 8002247C 0001F05C  7C 08 02 A6 */	mflr r0
/* 80022480 0001F060  3C 80 80 43 */	lis r4, skip40_804336D0@ha
/* 80022484 0001F064  90 01 00 04 */	stw r0, 4(r1)
/* 80022488 0001F068  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8002248C 0001F06C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80022490 0001F070  3B E4 36 D0 */	addi r31, r4, skip40_804336D0@l
/* 80022494 0001F074  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80022498 0001F078  3B C3 00 00 */	addi r30, r3, 0
/* 8002249C 0001F07C  80 1F 00 00 */	lwz r0, 0(r31)
/* 800224A0 0001F080  2C 00 00 00 */	cmpwi r0, 0
/* 800224A4 0001F084  41 82 00 A4 */	beq lbl_80022548
/* 800224A8 0001F088  7F C3 F3 78 */	mr r3, r30
/* 800224AC 0001F08C  48 34 7C 81 */	bl HSD_CObjGetProjectionType
/* 800224B0 0001F090  2C 03 00 02 */	cmpwi r3, 2
/* 800224B4 0001F094  41 82 00 3C */	beq lbl_800224F0
/* 800224B8 0001F098  40 80 00 68 */	bge lbl_80022520
/* 800224BC 0001F09C  2C 03 00 01 */	cmpwi r3, 1
/* 800224C0 0001F0A0  40 80 00 0C */	bge lbl_800224CC
/* 800224C4 0001F0A4  48 00 00 5C */	b lbl_80022520
/* 800224C8 0001F0A8  48 00 00 58 */	b lbl_80022520
lbl_800224CC:
/* 800224CC 0001F0AC  C0 62 83 C8 */	lfs f3, lbl_804D7DA8@sda21(r2)
/* 800224D0 0001F0B0  38 7F 00 10 */	addi r3, r31, 0x10
/* 800224D4 0001F0B4  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 800224D8 0001F0B8  FC A0 18 90 */	fmr f5, f3
/* 800224DC 0001F0BC  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 800224E0 0001F0C0  FC C0 18 90 */	fmr f6, f3
/* 800224E4 0001F0C4  C0 82 83 CC */	lfs f4, lbl_804D7DAC@sda21(r2)
/* 800224E8 0001F0C8  48 32 04 6D */	bl C_MTXLightPerspective
/* 800224EC 0001F0CC  48 00 00 5C */	b lbl_80022548
lbl_800224F0:
/* 800224F0 0001F0D0  C0 C2 83 C8 */	lfs f6, lbl_804D7DA8@sda21(r2)
/* 800224F4 0001F0D4  38 7F 00 10 */	addi r3, r31, 0x10
/* 800224F8 0001F0D8  D0 C1 00 08 */	stfs f6, 8(r1)
/* 800224FC 0001F0DC  FD 00 30 90 */	fmr f8, f6
/* 80022500 0001F0E0  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 80022504 0001F0E4  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 80022508 0001F0E8  C0 7E 00 48 */	lfs f3, 0x48(r30)
/* 8002250C 0001F0EC  C0 9E 00 4C */	lfs f4, 0x4c(r30)
/* 80022510 0001F0F0  C0 BE 00 38 */	lfs f5, 0x38(r30)
/* 80022514 0001F0F4  C0 E2 83 CC */	lfs f7, lbl_804D7DAC@sda21(r2)
/* 80022518 0001F0F8  48 32 03 A9 */	bl C_MTXLightFrustum
/* 8002251C 0001F0FC  48 00 00 2C */	b lbl_80022548
lbl_80022520:
/* 80022520 0001F100  C0 A2 83 C8 */	lfs f5, lbl_804D7DA8@sda21(r2)
/* 80022524 0001F104  38 7F 00 10 */	addi r3, r31, 0x10
/* 80022528 0001F108  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 8002252C 0001F10C  FC E0 28 90 */	fmr f7, f5
/* 80022530 0001F110  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 80022534 0001F114  FD 00 28 90 */	fmr f8, f5
/* 80022538 0001F118  C0 7E 00 48 */	lfs f3, 0x48(r30)
/* 8002253C 0001F11C  C0 9E 00 4C */	lfs f4, 0x4c(r30)
/* 80022540 0001F120  C0 C2 83 CC */	lfs f6, lbl_804D7DAC@sda21(r2)
/* 80022544 0001F124  48 32 04 DD */	bl C_MTXLightOrtho
lbl_80022548:
/* 80022548 0001F128  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8002254C 0001F12C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80022550 0001F130  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80022554 0001F134  38 21 00 20 */	addi r1, r1, 0x20
/* 80022558 0001F138  7C 08 03 A6 */	mtlr r0
/* 8002255C 0001F13C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/ZtsBi
.global func_80022560
func_80022560:
/* 80022560 0001F140  7C 08 02 A6 */	mflr r0
/* 80022564 0001F144  3C 60 80 43 */	lis r3, skip40_804336D0@ha
/* 80022568 0001F148  90 01 00 04 */	stw r0, 4(r1)
/* 8002256C 0001F14C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80022570 0001F150  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80022574 0001F154  3B E3 36 D0 */	addi r31, r3, skip40_804336D0@l
/* 80022578 0001F158  80 1F 00 00 */	lwz r0, 0(r31)
/* 8002257C 0001F15C  2C 00 00 00 */	cmpwi r0, 0
/* 80022580 0001F160  41 82 00 40 */	beq lbl_800225C0
/* 80022584 0001F164  38 60 00 00 */	li r3, 0
/* 80022588 0001F168  38 80 00 00 */	li r4, 0
/* 8002258C 0001F16C  38 A0 02 80 */	li r5, 0x280
/* 80022590 0001F170  38 C0 01 E0 */	li r6, 0x1e0
/* 80022594 0001F174  48 31 AF 35 */	bl func_8033D4C8
/* 80022598 0001F178  38 60 01 40 */	li r3, 0x140
/* 8002259C 0001F17C  38 80 00 F0 */	li r4, 0xf0
/* 800225A0 0001F180  38 A0 00 04 */	li r5, 4
/* 800225A4 0001F184  38 C0 00 01 */	li r6, 1
/* 800225A8 0001F188  48 31 B0 25 */	bl func_8033D5CC
/* 800225AC 0001F18C  80 7F 00 04 */	lwz r3, 4(r31)
/* 800225B0 0001F190  38 80 00 00 */	li r4, 0
/* 800225B4 0001F194  48 31 B7 09 */	bl func_8033DCBC
/* 800225B8 0001F198  48 31 A7 65 */	bl GXPixModeSync
/* 800225BC 0001F19C  48 31 CC B5 */	bl func_8033F270
lbl_800225C0:
/* 800225C0 0001F1A0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800225C4 0001F1A4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800225C8 0001F1A8  38 21 00 10 */	addi r1, r1, 0x10
/* 800225CC 0001F1AC  7C 08 03 A6 */	mtlr r0
/* 800225D0 0001F1B0  4E 80 00 20 */	blr 

# https://decomp.me/scratch/ioqOn
.global func_800225D4
func_800225D4:
/* 800225D4 0001F1B4  7C 08 02 A6 */	mflr r0
/* 800225D8 0001F1B8  38 60 00 00 */	li r3, 0
/* 800225DC 0001F1BC  90 01 00 04 */	stw r0, 4(r1)
/* 800225E0 0001F1C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 800225E4 0001F1C4  48 31 D6 A9 */	bl func_8033FC8C
/* 800225E8 0001F1C8  38 60 00 00 */	li r3, 0
/* 800225EC 0001F1CC  48 31 D6 75 */	bl func_8033FC60
/* 800225F0 0001F1D0  38 60 FF FF */	li r3, -1
/* 800225F4 0001F1D4  48 33 F9 D1 */	bl func_80361FC4
/* 800225F8 0001F1D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800225FC 0001F1DC  38 21 00 08 */	addi r1, r1, 8
/* 80022600 0001F1E0  7C 08 03 A6 */	mtlr r0
/* 80022604 0001F1E4  4E 80 00 20 */	blr 
lbl_80022608:
/* 80022608 0001F1E8  7C 08 02 A6 */	mflr r0
/* 8002260C 0001F1EC  3C E0 80 40 */	lis r7, hsdDObj@ha
/* 80022610 0001F1F0  90 01 00 04 */	stw r0, 4(r1)
/* 80022614 0001F1F4  38 E7 54 50 */	addi r7, r7, hsdDObj@l
/* 80022618 0001F1F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8002261C 0001F1FC  81 87 00 3C */	lwz r12, 0x3c(r7)
/* 80022620 0001F200  7D 88 03 A6 */	mtlr r12
/* 80022624 0001F204  4E 80 00 21 */	blrl 
/* 80022628 0001F208  38 60 00 00 */	li r3, 0
/* 8002262C 0001F20C  48 31 D6 61 */	bl func_8033FC8C
/* 80022630 0001F210  38 60 00 00 */	li r3, 0
/* 80022634 0001F214  48 31 D6 2D */	bl func_8033FC60
/* 80022638 0001F218  38 60 FF FF */	li r3, -1
/* 8002263C 0001F21C  48 33 F9 89 */	bl func_80361FC4
/* 80022640 0001F220  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80022644 0001F224  38 21 00 08 */	addi r1, r1, 8
/* 80022648 0001F228  7C 08 03 A6 */	mtlr r0
/* 8002264C 0001F22C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/BDJjp
local_80022650:
/* 80022650 0001F230  7C 08 02 A6 */	mflr r0
/* 80022654 0001F234  3C 60 80 3C */	lis r3, struct_803BB0B0@ha
/* 80022658 0001F238  90 01 00 04 */	stw r0, 4(r1)
/* 8002265C 0001F23C  38 E0 00 44 */	li r7, 0x44
/* 80022660 0001F240  39 00 00 18 */	li r8, 0x18
/* 80022664 0001F244  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80022668 0001F248  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8002266C 0001F24C  3B E3 B0 B0 */	addi r31, r3, struct_803BB0B0@l
/* 80022670 0001F250  3C 60 80 40 */	lis r3, hsdDObj@ha
/* 80022674 0001F254  38 83 54 50 */	addi r4, r3, hsdDObj@l
/* 80022678 0001F258  38 7F 01 68 */	addi r3, r31, 0x168
/* 8002267C 0001F25C  38 BF 01 F4 */	addi r5, r31, 0x1f4
/* 80022680 0001F260  38 DF 02 0C */	addi r6, r31, 0x20c
/* 80022684 0001F264  48 35 F5 95 */	bl hsdInitClassInfo
/* 80022688 0001F268  3C 60 80 02 */	lis r3, lbl_80022608@ha
/* 8002268C 0001F26C  38 03 26 08 */	addi r0, r3, lbl_80022608@l
/* 80022690 0001F270  90 1F 01 A4 */	stw r0, 0x1a4(r31)
/* 80022694 0001F274  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80022698 0001F278  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8002269C 0001F27C  38 21 00 10 */	addi r1, r1, 0x10
/* 800226A0 0001F280  7C 08 03 A6 */	mtlr r0
/* 800226A4 0001F284  4E 80 00 20 */	blr 

# https://decomp.me/scratch/GVvUT
.global func_800226A8
func_800226A8:
/* 800226A8 0001F288  7C 08 02 A6 */	mflr r0
/* 800226AC 0001F28C  3C A0 80 40 */	lis r5, lbl_80406398@ha
/* 800226B0 0001F290  90 01 00 04 */	stw r0, 4(r1)
/* 800226B4 0001F294  38 A5 63 98 */	addi r5, r5, lbl_80406398@l
/* 800226B8 0001F298  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800226BC 0001F29C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800226C0 0001F2A0  3B E3 00 00 */	addi r31, r3, 0
/* 800226C4 0001F2A4  81 85 00 44 */	lwz r12, 0x44(r5)
/* 800226C8 0001F2A8  7D 88 03 A6 */	mtlr r12
/* 800226CC 0001F2AC  4E 80 00 21 */	blrl 
/* 800226D0 0001F2B0  2C 03 00 00 */	cmpwi r3, 0
/* 800226D4 0001F2B4  41 82 00 08 */	beq lbl_800226DC
/* 800226D8 0001F2B8  48 00 02 54 */	b lbl_8002292C
lbl_800226DC:
/* 800226DC 0001F2BC  7F E3 FB 78 */	mr r3, r31
/* 800226E0 0001F2C0  48 34 91 F1 */	bl HSD_PObjGetFlags
/* 800226E4 0001F2C4  54 60 04 A5 */	rlwinm. r0, r3, 0, 0x12, 0x12
/* 800226E8 0001F2C8  40 82 00 0C */	bne lbl_800226F4
/* 800226EC 0001F2CC  38 60 00 00 */	li r3, 0
/* 800226F0 0001F2D0  48 00 02 3C */	b lbl_8002292C
lbl_800226F4:
/* 800226F4 0001F2D4  80 7F 00 08 */	lwz r3, 8(r31)
/* 800226F8 0001F2D8  38 A0 00 00 */	li r5, 0
/* 800226FC 0001F2DC  38 80 FF FF */	li r4, -1
/* 80022700 0001F2E0  38 C0 FF FF */	li r6, -1
/* 80022704 0001F2E4  48 00 00 DC */	b lbl_800227E0
lbl_80022708:
/* 80022708 0001F2E8  2C 00 00 0B */	cmpwi r0, 0xb
/* 8002270C 0001F2EC  40 80 00 1C */	bge lbl_80022728
/* 80022710 0001F2F0  2C 00 00 00 */	cmpwi r0, 0
/* 80022714 0001F2F4  41 82 00 34 */	beq lbl_80022748
/* 80022718 0001F2F8  41 80 00 C4 */	blt lbl_800227DC
/* 8002271C 0001F2FC  2C 00 00 09 */	cmpwi r0, 9
/* 80022720 0001F300  40 80 00 34 */	bge lbl_80022754
/* 80022724 0001F304  48 00 00 18 */	b lbl_8002273C
lbl_80022728:
/* 80022728 0001F308  2C 00 00 15 */	cmpwi r0, 0x15
/* 8002272C 0001F30C  40 80 00 B0 */	bge lbl_800227DC
/* 80022730 0001F310  2C 00 00 0D */	cmpwi r0, 0xd
/* 80022734 0001F314  40 80 00 20 */	bge lbl_80022754
/* 80022738 0001F318  48 00 00 38 */	b lbl_80022770
lbl_8002273C:
/* 8002273C 0001F31C  38 C5 00 00 */	addi r6, r5, 0
/* 80022740 0001F320  38 A5 00 01 */	addi r5, r5, 1
/* 80022744 0001F324  48 00 00 98 */	b lbl_800227DC
lbl_80022748:
/* 80022748 0001F328  38 85 00 00 */	addi r4, r5, 0
/* 8002274C 0001F32C  38 A5 00 01 */	addi r5, r5, 1
/* 80022750 0001F330  48 00 00 8C */	b lbl_800227DC
lbl_80022754:
/* 80022754 0001F334  80 03 00 04 */	lwz r0, 4(r3)
/* 80022758 0001F338  2C 00 00 03 */	cmpwi r0, 3
/* 8002275C 0001F33C  40 82 00 0C */	bne lbl_80022768
/* 80022760 0001F340  38 A5 00 02 */	addi r5, r5, 2
/* 80022764 0001F344  48 00 00 78 */	b lbl_800227DC
lbl_80022768:
/* 80022768 0001F348  38 A5 00 01 */	addi r5, r5, 1
/* 8002276C 0001F34C  48 00 00 70 */	b lbl_800227DC
lbl_80022770:
/* 80022770 0001F350  80 03 00 04 */	lwz r0, 4(r3)
/* 80022774 0001F354  2C 00 00 03 */	cmpwi r0, 3
/* 80022778 0001F358  41 82 00 14 */	beq lbl_8002278C
/* 8002277C 0001F35C  40 80 00 20 */	bge lbl_8002279C
/* 80022780 0001F360  2C 00 00 02 */	cmpwi r0, 2
/* 80022784 0001F364  40 80 00 10 */	bge lbl_80022794
/* 80022788 0001F368  48 00 00 14 */	b lbl_8002279C
lbl_8002278C:
/* 8002278C 0001F36C  38 A5 00 02 */	addi r5, r5, 2
/* 80022790 0001F370  48 00 00 4C */	b lbl_800227DC
lbl_80022794:
/* 80022794 0001F374  38 A5 00 01 */	addi r5, r5, 1
/* 80022798 0001F378  48 00 00 44 */	b lbl_800227DC
lbl_8002279C:
/* 8002279C 0001F37C  80 03 00 0C */	lwz r0, 0xc(r3)
/* 800227A0 0001F380  2C 00 00 02 */	cmpwi r0, 2
/* 800227A4 0001F384  41 82 00 34 */	beq lbl_800227D8
/* 800227A8 0001F388  40 80 00 14 */	bge lbl_800227BC
/* 800227AC 0001F38C  2C 00 00 00 */	cmpwi r0, 0
/* 800227B0 0001F390  41 82 00 18 */	beq lbl_800227C8
/* 800227B4 0001F394  40 80 00 1C */	bge lbl_800227D0
/* 800227B8 0001F398  48 00 00 24 */	b lbl_800227DC
lbl_800227BC:
/* 800227BC 0001F39C  2C 00 00 04 */	cmpwi r0, 4
/* 800227C0 0001F3A0  41 82 00 10 */	beq lbl_800227D0
/* 800227C4 0001F3A4  40 80 00 18 */	bge lbl_800227DC
lbl_800227C8:
/* 800227C8 0001F3A8  38 A5 00 02 */	addi r5, r5, 2
/* 800227CC 0001F3AC  48 00 00 10 */	b lbl_800227DC
lbl_800227D0:
/* 800227D0 0001F3B0  38 A5 00 03 */	addi r5, r5, 3
/* 800227D4 0001F3B4  48 00 00 08 */	b lbl_800227DC
lbl_800227D8:
/* 800227D8 0001F3B8  38 A5 00 04 */	addi r5, r5, 4
lbl_800227DC:
/* 800227DC 0001F3BC  38 63 00 18 */	addi r3, r3, 0x18
lbl_800227E0:
/* 800227E0 0001F3C0  28 03 00 00 */	cmplwi r3, 0
/* 800227E4 0001F3C4  41 82 00 10 */	beq lbl_800227F4
/* 800227E8 0001F3C8  80 03 00 00 */	lwz r0, 0(r3)
/* 800227EC 0001F3CC  2C 00 00 FF */	cmpwi r0, 0xff
/* 800227F0 0001F3D0  40 82 FF 18 */	bne lbl_80022708
lbl_800227F4:
/* 800227F4 0001F3D4  2C 04 FF FF */	cmpwi r4, -1
/* 800227F8 0001F3D8  41 82 00 0C */	beq lbl_80022804
/* 800227FC 0001F3DC  2C 06 00 02 */	cmpwi r6, 2
/* 80022800 0001F3E0  40 80 00 0C */	bge lbl_8002280C
lbl_80022804:
/* 80022804 0001F3E4  38 60 00 00 */	li r3, 0
/* 80022808 0001F3E8  48 00 01 24 */	b lbl_8002292C
lbl_8002280C:
/* 8002280C 0001F3EC  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 80022810 0001F3F0  39 40 00 00 */	li r10, 0
/* 80022814 0001F3F4  A0 1F 00 0E */	lhz r0, 0xe(r31)
/* 80022818 0001F3F8  7D 03 22 14 */	add r8, r3, r4
/* 8002281C 0001F3FC  54 04 28 34 */	slwi r4, r0, 5
/* 80022820 0001F400  7D 23 32 14 */	add r9, r3, r6
/* 80022824 0001F404  48 00 00 E8 */	b lbl_8002290C
lbl_80022828:
/* 80022828 0001F408  7D 40 53 78 */	mr r0, r10
/* 8002282C 0001F40C  7C 03 00 AE */	lbzx r0, r3, r0
/* 80022830 0001F410  39 4A 00 01 */	addi r10, r10, 1
/* 80022834 0001F414  54 00 06 39 */	rlwinm. r0, r0, 0, 0x18, 0x1c
/* 80022838 0001F418  41 82 00 DC */	beq lbl_80022914
/* 8002283C 0001F41C  7C E3 52 14 */	add r7, r3, r10
/* 80022840 0001F420  88 C7 00 00 */	lbz r6, 0(r7)
/* 80022844 0001F424  39 60 00 00 */	li r11, 0
/* 80022848 0001F428  89 87 00 01 */	lbz r12, 1(r7)
/* 8002284C 0001F42C  39 4A 00 02 */	addi r10, r10, 2
/* 80022850 0001F430  50 CC 44 2F */	rlwimi. r12, r6, 8, 0x10, 0x17
/* 80022854 0001F434  40 81 00 B8 */	ble lbl_8002290C
/* 80022858 0001F438  2C 0C 00 08 */	cmpwi r12, 8
/* 8002285C 0001F43C  38 CC FF F8 */	addi r6, r12, -8
/* 80022860 0001F440  40 81 00 C0 */	ble lbl_80022920
/* 80022864 0001F444  38 06 00 07 */	addi r0, r6, 7
/* 80022868 0001F448  54 00 E8 FE */	srwi r0, r0, 3
/* 8002286C 0001F44C  2C 06 00 00 */	cmpwi r6, 0
/* 80022870 0001F450  7C 09 03 A6 */	mtctr r0
/* 80022874 0001F454  40 81 00 AC */	ble lbl_80022920
lbl_80022878:
/* 80022878 0001F458  7C 08 50 AE */	lbzx r0, r8, r10
/* 8002287C 0001F45C  39 6B 00 08 */	addi r11, r11, 8
/* 80022880 0001F460  7C 09 51 AE */	stbx r0, r9, r10
/* 80022884 0001F464  7D 4A 2A 14 */	add r10, r10, r5
/* 80022888 0001F468  7C 08 50 AE */	lbzx r0, r8, r10
/* 8002288C 0001F46C  7C 09 51 AE */	stbx r0, r9, r10
/* 80022890 0001F470  7D 4A 2A 14 */	add r10, r10, r5
/* 80022894 0001F474  7C 08 50 AE */	lbzx r0, r8, r10
/* 80022898 0001F478  7C 09 51 AE */	stbx r0, r9, r10
/* 8002289C 0001F47C  7D 4A 2A 14 */	add r10, r10, r5
/* 800228A0 0001F480  7C 08 50 AE */	lbzx r0, r8, r10
/* 800228A4 0001F484  7C 09 51 AE */	stbx r0, r9, r10
/* 800228A8 0001F488  7D 4A 2A 14 */	add r10, r10, r5
/* 800228AC 0001F48C  7C 08 50 AE */	lbzx r0, r8, r10
/* 800228B0 0001F490  7C 09 51 AE */	stbx r0, r9, r10
/* 800228B4 0001F494  7D 4A 2A 14 */	add r10, r10, r5
/* 800228B8 0001F498  7C 08 50 AE */	lbzx r0, r8, r10
/* 800228BC 0001F49C  7C 09 51 AE */	stbx r0, r9, r10
/* 800228C0 0001F4A0  7D 4A 2A 14 */	add r10, r10, r5
/* 800228C4 0001F4A4  7C 08 50 AE */	lbzx r0, r8, r10
/* 800228C8 0001F4A8  7C 09 51 AE */	stbx r0, r9, r10
/* 800228CC 0001F4AC  7D 4A 2A 14 */	add r10, r10, r5
/* 800228D0 0001F4B0  7C 08 50 AE */	lbzx r0, r8, r10
/* 800228D4 0001F4B4  7C 09 51 AE */	stbx r0, r9, r10
/* 800228D8 0001F4B8  7D 4A 2A 14 */	add r10, r10, r5
/* 800228DC 0001F4BC  42 00 FF 9C */	bdnz lbl_80022878
/* 800228E0 0001F4C0  48 00 00 40 */	b lbl_80022920
lbl_800228E4:
/* 800228E4 0001F4C4  7C 0B 60 50 */	subf r0, r11, r12
/* 800228E8 0001F4C8  7C 0B 60 00 */	cmpw r11, r12
/* 800228EC 0001F4CC  7C 09 03 A6 */	mtctr r0
/* 800228F0 0001F4D0  40 80 00 1C */	bge lbl_8002290C
lbl_800228F4:
/* 800228F4 0001F4D4  88 06 00 00 */	lbz r0, 0(r6)
/* 800228F8 0001F4D8  7C C6 2A 14 */	add r6, r6, r5
/* 800228FC 0001F4DC  7D 4A 2A 14 */	add r10, r10, r5
/* 80022900 0001F4E0  98 07 00 00 */	stb r0, 0(r7)
/* 80022904 0001F4E4  7C E7 2A 14 */	add r7, r7, r5
/* 80022908 0001F4E8  42 00 FF EC */	bdnz lbl_800228F4
lbl_8002290C:
/* 8002290C 0001F4EC  7C 0A 20 00 */	cmpw r10, r4
/* 80022910 0001F4F0  41 80 FF 18 */	blt lbl_80022828
lbl_80022914:
/* 80022914 0001F4F4  48 32 1E F9 */	bl DCFlushRange
/* 80022918 0001F4F8  38 60 00 00 */	li r3, 0
/* 8002291C 0001F4FC  48 00 00 10 */	b lbl_8002292C
lbl_80022920:
/* 80022920 0001F500  7C C8 52 14 */	add r6, r8, r10
/* 80022924 0001F504  7C E9 52 14 */	add r7, r9, r10
/* 80022928 0001F508  4B FF FF BC */	b lbl_800228E4
lbl_8002292C:
/* 8002292C 0001F50C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80022930 0001F510  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80022934 0001F514  38 21 00 20 */	addi r1, r1, 0x20
/* 80022938 0001F518  7C 08 03 A6 */	mtlr r0
/* 8002293C 0001F51C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/iVwXp
local_80022940:
/* 80022940 0001F520  7C 08 02 A6 */	mflr r0
/* 80022944 0001F524  3C 60 80 3C */	lis r3, struct_803BB0B0@ha
/* 80022948 0001F528  90 01 00 04 */	stw r0, 4(r1)
/* 8002294C 0001F52C  38 E0 00 48 */	li r7, 0x48
/* 80022950 0001F530  39 00 00 18 */	li r8, 0x18
/* 80022954 0001F534  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80022958 0001F538  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8002295C 0001F53C  3B E3 B0 B0 */	addi r31, r3, struct_803BB0B0@l
/* 80022960 0001F540  3C 60 80 40 */	lis r3, lbl_80406398@ha
/* 80022964 0001F544  38 83 63 98 */	addi r4, r3, lbl_80406398@l
/* 80022968 0001F548  38 7F 01 AC */	addi r3, r31, 0x1ac
/* 8002296C 0001F54C  38 BF 01 F4 */	addi r5, r31, 0x1f4
/* 80022970 0001F550  38 DF 02 1C */	addi r6, r31, 0x21c
/* 80022974 0001F554  48 35 F2 A5 */	bl hsdInitClassInfo
/* 80022978 0001F558  3C 60 80 02 */	lis r3, func_800226A8@ha
/* 8002297C 0001F55C  38 03 26 A8 */	addi r0, r3, func_800226A8@l
/* 80022980 0001F560  90 1F 01 F0 */	stw r0, 0x1f0(r31)
/* 80022984 0001F564  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80022988 0001F568  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8002298C 0001F56C  38 21 00 10 */	addi r1, r1, 0x10
/* 80022990 0001F570  7C 08 03 A6 */	mtlr r0
/* 80022994 0001F574  4E 80 00 20 */	blr 

.section .data
    .balign 4

struct_803BB0E0:
    .4byte 0xBF000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0xBF000000
    .4byte NULL

.section .text

# https://decomp.me/scratch/n58XM
.global func_80022998
func_80022998:
/* 80022998 0001F578  7C 08 02 A6 */	mflr r0
/* 8002299C 0001F57C  3C 60 80 43 */	lis r3, skip40_804336D0@ha
/* 800229A0 0001F580  90 01 00 04 */	stw r0, 4(r1)
/* 800229A4 0001F584  54 A0 10 3A */	slwi r0, r5, 2
/* 800229A8 0001F588  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800229AC 0001F58C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800229B0 0001F590  3B E3 36 D0 */	addi r31, r3, skip40_804336D0@l
/* 800229B4 0001F594  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800229B8 0001F598  3B C4 00 00 */	addi r30, r4, 0
/* 800229BC 0001F59C  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 800229C0 0001F5A0  7C 63 00 2E */	lwzx r3, r3, r0
/* 800229C4 0001F5A4  48 33 DF 8D */	bl HSD_TObjSetup
/* 800229C8 0001F5A8  38 60 00 02 */	li r3, 2
/* 800229CC 0001F5AC  48 31 A1 AD */	bl GXSetNumTexGens
/* 800229D0 0001F5B0  38 60 00 00 */	li r3, 0
/* 800229D4 0001F5B4  38 80 00 00 */	li r4, 0
/* 800229D8 0001F5B8  38 A0 00 01 */	li r5, 1
/* 800229DC 0001F5BC  38 C0 00 1E */	li r6, 0x1e
/* 800229E0 0001F5C0  38 E0 00 01 */	li r7, 1
/* 800229E4 0001F5C4  39 00 00 40 */	li r8, 0x40
/* 800229E8 0001F5C8  48 31 9E C1 */	bl GXSetTexCoordGen2
/* 800229EC 0001F5CC  38 60 00 01 */	li r3, 1
/* 800229F0 0001F5D0  38 80 00 00 */	li r4, 0
/* 800229F4 0001F5D4  38 A0 00 00 */	li r5, 0
/* 800229F8 0001F5D8  38 C0 00 00 */	li r6, 0
/* 800229FC 0001F5DC  38 E0 00 00 */	li r7, 0
/* 80022A00 0001F5E0  39 00 00 43 */	li r8, 0x43
/* 80022A04 0001F5E4  48 31 9E A5 */	bl GXSetTexCoordGen2
/* 80022A08 0001F5E8  3C 60 80 3C */	lis r3, struct_803BB0B0@ha
/* 80022A0C 0001F5EC  38 63 B0 B0 */	addi r3, r3, struct_803BB0B0@l
/* 80022A10 0001F5F0  38 80 00 40 */	li r4, 0x40
/* 80022A14 0001F5F4  38 A0 00 00 */	li r5, 0
/* 80022A18 0001F5F8  48 31 EB 35 */	bl func_8034154C
/* 80022A1C 0001F5FC  38 7F 00 10 */	addi r3, r31, 0x10
/* 80022A20 0001F600  38 80 00 43 */	li r4, 0x43
/* 80022A24 0001F604  38 A0 00 00 */	li r5, 0
/* 80022A28 0001F608  48 31 EB 25 */	bl func_8034154C
/* 80022A2C 0001F60C  38 60 00 00 */	li r3, 0
/* 80022A30 0001F610  48 31 BB 2D */	bl GXSetNumChans
/* 80022A34 0001F614  38 60 00 01 */	li r3, 1
/* 80022A38 0001F618  48 31 DD 59 */	bl func_80340790
/* 80022A3C 0001F61C  38 60 00 00 */	li r3, 0
/* 80022A40 0001F620  38 80 00 01 */	li r4, 1
/* 80022A44 0001F624  38 A0 00 01 */	li r5, 1
/* 80022A48 0001F628  38 C0 00 FF */	li r6, 0xff
/* 80022A4C 0001F62C  48 31 DB A5 */	bl func_803405F0
/* 80022A50 0001F630  38 60 00 00 */	li r3, 0
/* 80022A54 0001F634  38 80 00 0F */	li r4, 0xf
/* 80022A58 0001F638  38 A0 00 0F */	li r5, 0xf
/* 80022A5C 0001F63C  38 C0 00 0F */	li r6, 0xf
/* 80022A60 0001F640  38 E0 00 08 */	li r7, 8
/* 80022A64 0001F644  48 31 D5 05 */	bl func_8033FF68
/* 80022A68 0001F648  38 60 00 00 */	li r3, 0
/* 80022A6C 0001F64C  38 80 00 07 */	li r4, 7
/* 80022A70 0001F650  38 A0 00 07 */	li r5, 7
/* 80022A74 0001F654  38 C0 00 07 */	li r6, 7
/* 80022A78 0001F658  38 E0 00 04 */	li r7, 4
/* 80022A7C 0001F65C  48 31 D5 6D */	bl func_8033FFE8
/* 80022A80 0001F660  38 60 00 00 */	li r3, 0
/* 80022A84 0001F664  38 80 00 00 */	li r4, 0
/* 80022A88 0001F668  38 A0 00 00 */	li r5, 0
/* 80022A8C 0001F66C  38 C0 00 00 */	li r6, 0
/* 80022A90 0001F670  38 E0 00 00 */	li r7, 0
/* 80022A94 0001F674  39 00 00 00 */	li r8, 0
/* 80022A98 0001F678  48 31 D5 D5 */	bl func_8034006C
/* 80022A9C 0001F67C  38 60 00 00 */	li r3, 0
/* 80022AA0 0001F680  38 80 00 00 */	li r4, 0
/* 80022AA4 0001F684  38 A0 00 00 */	li r5, 0
/* 80022AA8 0001F688  38 C0 00 00 */	li r6, 0
/* 80022AAC 0001F68C  38 E0 00 00 */	li r7, 0
/* 80022AB0 0001F690  39 00 00 00 */	li r8, 0
/* 80022AB4 0001F694  48 31 D6 79 */	bl func_8034012C
/* 80022AB8 0001F698  38 60 00 01 */	li r3, 1
/* 80022ABC 0001F69C  48 31 D1 A5 */	bl func_8033FC60
/* 80022AC0 0001F6A0  38 60 00 00 */	li r3, 0
/* 80022AC4 0001F6A4  38 80 00 00 */	li r4, 0
/* 80022AC8 0001F6A8  38 A0 00 00 */	li r5, 0
/* 80022ACC 0001F6AC  48 31 D0 5D */	bl func_8033FB28
/* 80022AD0 0001F6B0  38 60 00 00 */	li r3, 0
/* 80022AD4 0001F6B4  38 80 00 00 */	li r4, 0
/* 80022AD8 0001F6B8  38 A0 00 00 */	li r5, 0
/* 80022ADC 0001F6BC  48 31 CE 79 */	bl func_8033F954
/* 80022AE0 0001F6C0  3C 60 80 3C */	lis r3, struct_803BB0E0@ha
/* 80022AE4 0001F6C4  38 83 B0 E0 */	addi r4, r3, struct_803BB0E0@l
/* 80022AE8 0001F6C8  38 60 00 01 */	li r3, 1
/* 80022AEC 0001F6CC  38 A0 00 01 */	li r5, 1
/* 80022AF0 0001F6D0  48 31 CD 05 */	bl func_8033F7F4
/* 80022AF4 0001F6D4  3B E0 00 00 */	li r31, 0
/* 80022AF8 0001F6D8  93 E1 00 08 */	stw r31, 8(r1)
/* 80022AFC 0001F6DC  38 60 00 00 */	li r3, 0
/* 80022B00 0001F6E0  38 80 00 00 */	li r4, 0
/* 80022B04 0001F6E4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80022B08 0001F6E8  38 A0 00 00 */	li r5, 0
/* 80022B0C 0001F6EC  38 C0 00 03 */	li r6, 3
/* 80022B10 0001F6F0  38 E0 00 01 */	li r7, 1
/* 80022B14 0001F6F4  39 00 00 00 */	li r8, 0
/* 80022B18 0001F6F8  39 20 00 00 */	li r9, 0
/* 80022B1C 0001F6FC  39 40 00 00 */	li r10, 0
/* 80022B20 0001F700  48 31 CC 39 */	bl func_8033F758
/* 80022B24 0001F704  38 60 00 01 */	li r3, 1
/* 80022B28 0001F708  48 31 E2 19 */	bl func_80340D40
/* 80022B2C 0001F70C  38 60 00 00 */	li r3, 0
/* 80022B30 0001F710  48 31 E2 51 */	bl func_80340D80
/* 80022B34 0001F714  57 C0 00 85 */	rlwinm. r0, r30, 0, 2, 2
/* 80022B38 0001F718  41 82 00 08 */	beq lbl_80022B40
/* 80022B3C 0001F71C  48 00 00 08 */	b lbl_80022B44
lbl_80022B40:
/* 80022B40 0001F720  3B E0 00 01 */	li r31, 1
lbl_80022B44:
/* 80022B44 0001F724  57 C0 01 09 */	rlwinm. r0, r30, 0, 4, 4
/* 80022B48 0001F728  41 82 00 0C */	beq lbl_80022B54
/* 80022B4C 0001F72C  38 80 00 07 */	li r4, 7
/* 80022B50 0001F730  48 00 00 08 */	b lbl_80022B58
lbl_80022B54:
/* 80022B54 0001F734  38 80 00 03 */	li r4, 3
lbl_80022B58:
/* 80022B58 0001F738  38 BF 00 00 */	addi r5, r31, 0
/* 80022B5C 0001F73C  38 60 00 01 */	li r3, 1
/* 80022B60 0001F740  48 31 E2 61 */	bl func_80340DC0
/* 80022B64 0001F744  38 60 00 01 */	li r3, 1
/* 80022B68 0001F748  48 31 E2 D1 */	bl func_80340E38
/* 80022B6C 0001F74C  38 60 00 00 */	li r3, 0
/* 80022B70 0001F750  38 80 00 01 */	li r4, 1
/* 80022B74 0001F754  38 A0 00 00 */	li r5, 0
/* 80022B78 0001F758  38 C0 00 0F */	li r6, 0xf
/* 80022B7C 0001F75C  48 31 E0 C1 */	bl func_80340C3C
/* 80022B80 0001F760  38 60 00 07 */	li r3, 7
/* 80022B84 0001F764  38 80 00 00 */	li r4, 0
/* 80022B88 0001F768  38 A0 00 01 */	li r5, 1
/* 80022B8C 0001F76C  38 C0 00 07 */	li r6, 7
/* 80022B90 0001F770  38 E0 00 00 */	li r7, 0
/* 80022B94 0001F774  48 31 D9 89 */	bl func_8034051C
/* 80022B98 0001F778  38 60 00 00 */	li r3, 0
/* 80022B9C 0001F77C  48 31 E3 ED */	bl func_80340F88
/* 80022BA0 0001F780  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80022BA4 0001F784  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80022BA8 0001F788  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80022BAC 0001F78C  38 21 00 28 */	addi r1, r1, 0x28
/* 80022BB0 0001F790  7C 08 03 A6 */	mtlr r0
/* 80022BB4 0001F794  4E 80 00 20 */	blr 

# https://decomp.me/scratch/1k4lM
.global func_80022BB8
func_80022BB8:
/* 80022BB8 0001F798  3C 60 80 43 */	lis r3, skip40_804336D0@ha
/* 80022BBC 0001F79C  38 83 36 D0 */	addi r4, r3, skip40_804336D0@l
/* 80022BC0 0001F7A0  80 64 00 00 */	lwz r3, 0(r4)
/* 80022BC4 0001F7A4  38 03 00 01 */	addi r0, r3, 1
/* 80022BC8 0001F7A8  90 04 00 00 */	stw r0, 0(r4)
/* 80022BCC 0001F7AC  4E 80 00 20 */	blr 

.section .data
    .balign 8

struct_803BB0F8:
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte NULL

struct_803BB110:
    .4byte 0x00000001
    .4byte NULL
    .4byte 0x01010000
    .4byte NULL

struct_803BB120:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x01010000
    .4byte 0x00000083
    .4byte 0x3F800000
    .4byte 0x00000001
    .4byte struct_803BB0F8
    .4byte NULL
    .4byte struct_803BB110
    .4byte NULL

struct_803BB17C:
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte NULL

struct_803BB194:
    .4byte 0x00000001
    .4byte NULL
    .4byte 0x01010000
    .4byte NULL
    .4byte NULL
    .4byte struct_803BB120
    .4byte 0x00000001
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x01010000
    .4byte 0x00000081
    .4byte 0x3F800000
    .4byte 0x00000001
    .4byte struct_803BB17C
    .4byte NULL
    .4byte struct_803BB194
    .4byte NULL
    .asciz "LbRf.dat"
    .balign 4
    .asciz "lbRefData"
    .balign 4
    .4byte local_80022650
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte local_80022940
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .asciz "refract_class_library"
    .balign 4
    .asciz "refract_dobj"
    .balign 4
    .asciz "refract_pobj"
    .balign 4

str_lbRefSetUnuse_error:
    .asciz "lbRefSetUnuse error!\n"
    .balign 4

str_lbrefract_c:
    .asciz "lbrefract.c"
    .balign 4

.section .sdata
    .balign 8

str_0_804D3868:
    .asciz "0"
    .balign 4
    .float 0.0

.section .text

# https://decomp.me/scratch/1OXja
.global func_80022BD0
func_80022BD0:
/* 80022BD0 0001F7B0  7C 08 02 A6 */	mflr r0
/* 80022BD4 0001F7B4  3C 60 80 43 */	lis r3, skip40_804336D0@ha
/* 80022BD8 0001F7B8  90 01 00 04 */	stw r0, 4(r1)
/* 80022BDC 0001F7BC  38 83 36 D0 */	addi r4, r3, skip40_804336D0@l
/* 80022BE0 0001F7C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80022BE4 0001F7C4  80 64 00 00 */	lwz r3, 0(r4)
/* 80022BE8 0001F7C8  38 03 FF FF */	addi r0, r3, -1
/* 80022BEC 0001F7CC  90 04 00 00 */	stw r0, 0(r4)
/* 80022BF0 0001F7D0  80 04 00 00 */	lwz r0, 0(r4)
/* 80022BF4 0001F7D4  2C 00 00 00 */	cmpwi r0, 0
/* 80022BF8 0001F7D8  40 80 00 28 */	bge lbl_80022C20
/* 80022BFC 0001F7DC  3C 60 80 3C */	lis r3, str_lbRefSetUnuse_error@ha
/* 80022C00 0001F7E0  4C C6 31 82 */	crclr 6
/* 80022C04 0001F7E4  38 63 B2 DC */	addi r3, r3, str_lbRefSetUnuse_error@l
/* 80022C08 0001F7E8  48 32 2A A1 */	bl OSReport
/* 80022C0C 0001F7EC  3C 60 80 3C */	lis r3, str_lbrefract_c@ha
/* 80022C10 0001F7F0  38 63 B2 F4 */	addi r3, r3, str_lbrefract_c@l
/* 80022C14 0001F7F4  38 80 03 1C */	li r4, 0x31c
/* 80022C18 0001F7F8  38 AD 81 C8 */	addi r5, r13, str_0_804D3868@sda21
/* 80022C1C 0001F7FC  48 36 56 05 */	bl __assert
lbl_80022C20:
/* 80022C20 0001F800  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80022C24 0001F804  38 21 00 08 */	addi r1, r1, 8
/* 80022C28 0001F808  7C 08 03 A6 */	mtlr r0
/* 80022C2C 0001F80C  4E 80 00 20 */	blr 
