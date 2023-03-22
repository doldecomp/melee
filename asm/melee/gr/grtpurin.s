.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80223160
func_80223160:
/* 80223160 0021FD40  4E 80 00 20 */	blr
.global lbl_80223164
lbl_80223164:
/* 80223164 0021FD44  7C 08 02 A6 */	mflr r0
/* 80223168 0021FD48  90 01 00 04 */	stw r0, 4(r1)
/* 8022316C 0021FD4C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223170 0021FD50  4B FA 18 89 */	bl Ground_801C49F8
/* 80223174 0021FD54  3C 80 80 4A */	lis r4, stage_info@ha
/* 80223178 0021FD58  90 6D B4 70 */	stw r3, lbl_804D6B10@sda21(r13)
/* 8022317C 0021FD5C  38 64 E6 C8 */	addi r3, r4, stage_info@l
/* 80223180 0021FD60  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80223184 0021FD64  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80223188 0021FD68  38 60 00 00 */	li r3, 0
/* 8022318C 0021FD6C  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80223190 0021FD70  98 05 00 00 */	stb r0, 0(r5)
/* 80223194 0021FD74  38 80 00 01 */	li r4, 1
/* 80223198 0021FD78  38 60 00 00 */	li r3, 0
/* 8022319C 0021FD7C  88 05 00 00 */	lbz r0, 0(r5)
/* 802231A0 0021FD80  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 802231A4 0021FD84  98 05 00 00 */	stb r0, 0(r5)
/* 802231A8 0021FD88  48 00 00 65 */	bl func_8022320C
/* 802231AC 0021FD8C  38 60 00 01 */	li r3, 1
/* 802231B0 0021FD90  48 00 00 5D */	bl func_8022320C
/* 802231B4 0021FD94  38 60 00 02 */	li r3, 2
/* 802231B8 0021FD98  48 00 00 55 */	bl func_8022320C
/* 802231BC 0021FD9C  4B FA 08 05 */	bl Ground_801C39C0
/* 802231C0 0021FDA0  4B FA 09 F5 */	bl Ground_801C3BB4
/* 802231C4 0021FDA4  4B FA 10 4D */	bl Ground_801C4210
/* 802231C8 0021FDA8  4B FA 10 E5 */	bl Ground_801C42AC
/* 802231CC 0021FDAC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802231D0 0021FDB0  38 21 00 08 */	addi r1, r1, 8
/* 802231D4 0021FDB4  7C 08 03 A6 */	mtlr r0
/* 802231D8 0021FDB8  4E 80 00 20 */	blr
.global lbl_802231DC
lbl_802231DC:
/* 802231DC 0021FDBC  4E 80 00 20 */	blr
.global lbl_802231E0
lbl_802231E0:
/* 802231E0 0021FDC0  7C 08 02 A6 */	mflr r0
/* 802231E4 0021FDC4  38 60 00 00 */	li r3, 0
/* 802231E8 0021FDC8  90 01 00 04 */	stw r0, 4(r1)
/* 802231EC 0021FDCC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802231F0 0021FDD0  4B FA 7C 15 */	bl func_801CAE04
/* 802231F4 0021FDD4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802231F8 0021FDD8  38 21 00 08 */	addi r1, r1, 8
/* 802231FC 0021FDDC  7C 08 03 A6 */	mtlr r0
/* 80223200 0021FDE0  4E 80 00 20 */	blr
.global lbl_80223204
lbl_80223204:
/* 80223204 0021FDE4  38 60 00 00 */	li r3, 0
/* 80223208 0021FDE8  4E 80 00 20 */	blr

.global func_8022320C
func_8022320C:
/* 8022320C 0021FDEC  7C 08 02 A6 */	mflr r0
/* 80223210 0021FDF0  90 01 00 04 */	stw r0, 4(r1)
/* 80223214 0021FDF4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223218 0021FDF8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8022321C 0021FDFC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223220 0021FE00  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80223224 0021FE04  93 81 00 10 */	stw r28, 0x10(r1)
/* 80223228 0021FE08  3B 83 00 00 */	addi r28, r3, 0
/* 8022322C 0021FE0C  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80223230 0021FE10  3C 60 80 3F */	lis r3, lbl_803E9338@ha
/* 80223234 0021FE14  3B E3 93 38 */	addi r31, r3, lbl_803E9338@l
/* 80223238 0021FE18  38 7C 00 00 */	addi r3, r28, 0
/* 8022323C 0021FE1C  7F BF 02 14 */	add r29, r31, r0
/* 80223240 0021FE20  4B F9 E2 91 */	bl Ground_801C14D0
/* 80223244 0021FE24  7C 7E 1B 79 */	or. r30, r3, r3
/* 80223248 0021FE28  41 82 00 70 */	beq lbl_802232B8
/* 8022324C 0021FE2C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80223250 0021FE30  38 00 00 00 */	li r0, 0
/* 80223254 0021FE34  3C 60 80 1C */	lis r3, grDisplay_801C5DB0@ha
/* 80223258 0021FE38  90 1F 00 08 */	stw r0, 8(r31)
/* 8022325C 0021FE3C  38 83 5D B0 */	addi r4, r3, grDisplay_801C5DB0@l
/* 80223260 0021FE40  38 7E 00 00 */	addi r3, r30, 0
/* 80223264 0021FE44  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80223268 0021FE48  38 A0 00 03 */	li r5, 3
/* 8022326C 0021FE4C  38 C0 00 00 */	li r6, 0
/* 80223270 0021FE50  48 16 D4 2D */	bl GObj_SetupGXLink
/* 80223274 0021FE54  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80223278 0021FE58  28 00 00 00 */	cmplwi r0, 0
/* 8022327C 0021FE5C  41 82 00 08 */	beq lbl_80223284
/* 80223280 0021FE60  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80223284:
/* 80223284 0021FE64  81 9D 00 00 */	lwz r12, 0(r29)
/* 80223288 0021FE68  28 0C 00 00 */	cmplwi r12, 0
/* 8022328C 0021FE6C  41 82 00 10 */	beq lbl_8022329C
/* 80223290 0021FE70  7D 88 03 A6 */	mtlr r12
/* 80223294 0021FE74  38 7E 00 00 */	addi r3, r30, 0
/* 80223298 0021FE78  4E 80 00 21 */	blrl
lbl_8022329C:
/* 8022329C 0021FE7C  80 9D 00 08 */	lwz r4, 8(r29)
/* 802232A0 0021FE80  28 04 00 00 */	cmplwi r4, 0
/* 802232A4 0021FE84  41 82 00 2C */	beq lbl_802232D0
/* 802232A8 0021FE88  38 7E 00 00 */	addi r3, r30, 0
/* 802232AC 0021FE8C  38 A0 00 04 */	li r5, 4
/* 802232B0 0021FE90  48 16 CA A5 */	bl func_8038FD54
/* 802232B4 0021FE94  48 00 00 1C */	b lbl_802232D0
lbl_802232B8:
/* 802232B8 0021FE98  38 DC 00 00 */	addi r6, r28, 0
/* 802232BC 0021FE9C  4C C6 31 82 */	crclr 6
/* 802232C0 0021FEA0  38 7F 00 90 */	addi r3, r31, 0x90
/* 802232C4 0021FEA4  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 802232C8 0021FEA8  38 A0 00 CB */	li r5, 0xcb
/* 802232CC 0021FEAC  48 12 23 DD */	bl OSReport
lbl_802232D0:
/* 802232D0 0021FEB0  7F C3 F3 78 */	mr r3, r30
/* 802232D4 0021FEB4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802232D8 0021FEB8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802232DC 0021FEBC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802232E0 0021FEC0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802232E4 0021FEC4  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802232E8 0021FEC8  38 21 00 20 */	addi r1, r1, 0x20
/* 802232EC 0021FECC  7C 08 03 A6 */	mtlr r0
/* 802232F0 0021FED0  4E 80 00 20 */	blr
.global lbl_802232F4
lbl_802232F4:
/* 802232F4 0021FED4  7C 08 02 A6 */	mflr r0
/* 802232F8 0021FED8  38 A0 00 00 */	li r5, 0
/* 802232FC 0021FEDC  90 01 00 04 */	stw r0, 4(r1)
/* 80223300 0021FEE0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223304 0021FEE4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80223308 0021FEE8  80 84 00 14 */	lwz r4, 0x14(r4)
/* 8022330C 0021FEEC  4B FA 4E 2D */	bl grAnime_801C8138
/* 80223310 0021FEF0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223314 0021FEF4  38 21 00 08 */	addi r1, r1, 8
/* 80223318 0021FEF8  7C 08 03 A6 */	mtlr r0
/* 8022331C 0021FEFC  4E 80 00 20 */	blr
.global lbl_80223320
lbl_80223320:
/* 80223320 0021FF00  38 60 00 00 */	li r3, 0
/* 80223324 0021FF04  4E 80 00 20 */	blr
.global lbl_80223328
lbl_80223328:
/* 80223328 0021FF08  4E 80 00 20 */	blr
.global lbl_8022332C
lbl_8022332C:
/* 8022332C 0021FF0C  4E 80 00 20 */	blr
.global lbl_80223330
lbl_80223330:
/* 80223330 0021FF10  7C 08 02 A6 */	mflr r0
/* 80223334 0021FF14  90 01 00 04 */	stw r0, 4(r1)
/* 80223338 0021FF18  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8022333C 0021FF1C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223340 0021FF20  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223344 0021FF24  7C 7E 1B 78 */	mr r30, r3
/* 80223348 0021FF28  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8022334C 0021FF2C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80223350 0021FF30  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223354 0021FF34  4B F9 FB 7D */	bl Ground_801C2ED0
/* 80223358 0021FF38  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8022335C 0021FF3C  38 7E 00 00 */	addi r3, r30, 0
/* 80223360 0021FF40  38 A0 00 00 */	li r5, 0
/* 80223364 0021FF44  4B FA 4D D5 */	bl grAnime_801C8138
/* 80223368 0021FF48  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8022336C 0021FF4C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223370 0021FF50  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80223374 0021FF54  38 21 00 20 */	addi r1, r1, 0x20
/* 80223378 0021FF58  7C 08 03 A6 */	mtlr r0
/* 8022337C 0021FF5C  4E 80 00 20 */	blr
.global lbl_80223380
lbl_80223380:
/* 80223380 0021FF60  38 60 00 00 */	li r3, 0
/* 80223384 0021FF64  4E 80 00 20 */	blr
.global lbl_80223388
lbl_80223388:
/* 80223388 0021FF68  7C 08 02 A6 */	mflr r0
/* 8022338C 0021FF6C  3C 80 80 3C */	lis r4, lbl_803B84B8@ha
/* 80223390 0021FF70  90 01 00 04 */	stw r0, 4(r1)
/* 80223394 0021FF74  38 A4 84 B8 */	addi r5, r4, lbl_803B84B8@l
/* 80223398 0021FF78  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8022339C 0021FF7C  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 802233A0 0021FF80  93 E1 00 34 */	stw r31, 0x34(r1)
/* 802233A4 0021FF84  3B E1 00 0C */	addi r31, r1, 0xc
/* 802233A8 0021FF88  93 C1 00 30 */	stw r30, 0x30(r1)
/* 802233AC 0021FF8C  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 802233B0 0021FF90  93 81 00 28 */	stw r28, 0x28(r1)
/* 802233B4 0021FF94  7C 7C 1B 78 */	mr r28, r3
/* 802233B8 0021FF98  80 85 00 00 */	lwz r4, 0(r5)
/* 802233BC 0021FF9C  80 05 00 04 */	lwz r0, 4(r5)
/* 802233C0 0021FFA0  C3 E2 C2 E8 */	lfs f31, lbl_804DBCC8@sda21(r2)
/* 802233C4 0021FFA4  90 81 00 0C */	stw r4, 0xc(r1)
/* 802233C8 0021FFA8  90 01 00 10 */	stw r0, 0x10(r1)
/* 802233CC 0021FFAC  80 65 00 08 */	lwz r3, 8(r5)
/* 802233D0 0021FFB0  80 05 00 0C */	lwz r0, 0xc(r5)
/* 802233D4 0021FFB4  90 61 00 14 */	stw r3, 0x14(r1)
/* 802233D8 0021FFB8  90 01 00 18 */	stw r0, 0x18(r1)
/* 802233DC 0021FFBC  48 00 00 60 */	b lbl_8022343C
lbl_802233E0:
/* 802233E0 0021FFC0  38 60 00 02 */	li r3, 2
/* 802233E4 0021FFC4  38 9D 00 00 */	addi r4, r29, 0
/* 802233E8 0021FFC8  4B F9 FE ED */	bl Ground_801C32D4
/* 802233EC 0021FFCC  3B C3 00 00 */	addi r30, r3, 0
/* 802233F0 0021FFD0  2C 1E FF FF */	cmpwi r30, -1
/* 802233F4 0021FFD4  41 82 00 44 */	beq lbl_80223438
/* 802233F8 0021FFD8  38 7C 00 00 */	addi r3, r28, 0
/* 802233FC 0021FFDC  38 9D 00 00 */	addi r4, r29, 0
/* 80223400 0021FFE0  4B FA 0B A5 */	bl Ground_801C3FA4
/* 80223404 0021FFE4  28 03 00 00 */	cmplwi r3, 0
/* 80223408 0021FFE8  41 82 00 28 */	beq lbl_80223430
/* 8022340C 0021FFEC  38 A1 00 1C */	addi r5, r1, 0x1c
/* 80223410 0021FFF0  38 80 00 00 */	li r4, 0
/* 80223414 0021FFF4  4B DE 7D B9 */	bl func_8000B1CC
/* 80223418 0021FFF8  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 8022341C 0021FFFC  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 80223420 00220000  40 80 00 10 */	bge lbl_80223430
/* 80223424 00220004  7F C3 F3 78 */	mr r3, r30
/* 80223428 00220008  4B E3 42 11 */	bl func_80057638
/* 8022342C 0022000C  48 00 00 0C */	b lbl_80223438
lbl_80223430:
/* 80223430 00220010  7F C3 F3 78 */	mr r3, r30
/* 80223434 00220014  4B E3 47 8D */	bl func_80057BC0
lbl_80223438:
/* 80223438 00220018  3B FF 00 02 */	addi r31, r31, 2
lbl_8022343C:
/* 8022343C 0022001C  AB BF 00 00 */	lha r29, 0(r31)
/* 80223440 00220020  2C 1D FF FF */	cmpwi r29, -1
/* 80223444 00220024  40 82 FF 9C */	bne lbl_802233E0
/* 80223448 00220028  4B DE E1 AD */	bl func_800115F4
/* 8022344C 0022002C  7F 83 E3 78 */	mr r3, r28
/* 80223450 00220030  4B F9 FB 91 */	bl Ground_801C2FE0
/* 80223454 00220034  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80223458 00220038  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 8022345C 0022003C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80223460 00220040  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80223464 00220044  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80223468 00220048  83 81 00 28 */	lwz r28, 0x28(r1)
/* 8022346C 0022004C  38 21 00 40 */	addi r1, r1, 0x40
/* 80223470 00220050  7C 08 03 A6 */	mtlr r0
/* 80223474 00220054  4E 80 00 20 */	blr
.global lbl_80223478
lbl_80223478:
/* 80223478 00220058  4E 80 00 20 */	blr
.global lbl_8022347C
lbl_8022347C:
/* 8022347C 0022005C  7C 08 02 A6 */	mflr r0
/* 80223480 00220060  90 01 00 04 */	stw r0, 4(r1)
/* 80223484 00220064  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223488 00220068  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8022348C 0022006C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223490 00220070  7C 7E 1B 78 */	mr r30, r3
/* 80223494 00220074  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80223498 00220078  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8022349C 0022007C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802234A0 00220080  4B F9 FA 31 */	bl Ground_801C2ED0
/* 802234A4 00220084  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802234A8 00220088  38 7E 00 00 */	addi r3, r30, 0
/* 802234AC 0022008C  38 A0 00 00 */	li r5, 0
/* 802234B0 00220090  4B FA 4C 89 */	bl grAnime_801C8138
/* 802234B4 00220094  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802234B8 00220098  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802234BC 0022009C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802234C0 002200A0  38 21 00 20 */	addi r1, r1, 0x20
/* 802234C4 002200A4  7C 08 03 A6 */	mtlr r0
/* 802234C8 002200A8  4E 80 00 20 */	blr
.global lbl_802234CC
lbl_802234CC:
/* 802234CC 002200AC  38 60 00 00 */	li r3, 0
/* 802234D0 002200B0  4E 80 00 20 */	blr
.global lbl_802234D4
lbl_802234D4:
/* 802234D4 002200B4  7C 08 02 A6 */	mflr r0
/* 802234D8 002200B8  90 01 00 04 */	stw r0, 4(r1)
/* 802234DC 002200BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802234E0 002200C0  4B F9 FB 01 */	bl Ground_801C2FE0
/* 802234E4 002200C4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802234E8 002200C8  38 21 00 08 */	addi r1, r1, 8
/* 802234EC 002200CC  7C 08 03 A6 */	mtlr r0
/* 802234F0 002200D0  4E 80 00 20 */	blr
.global lbl_802234F4
lbl_802234F4:
/* 802234F4 002200D4  4E 80 00 20 */	blr
.global lbl_802234F8
lbl_802234F8:
/* 802234F8 002200D8  7C 08 02 A6 */	mflr r0
/* 802234FC 002200DC  90 01 00 04 */	stw r0, 4(r1)
/* 80223500 002200E0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80223504 002200E4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80223508 002200E8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8022350C 002200EC  3B C3 00 00 */	addi r30, r3, 0
/* 80223510 002200F0  2C 1E FF FF */	cmpwi r30, -1
/* 80223514 002200F4  41 82 00 48 */	beq lbl_8022355C
/* 80223518 002200F8  7F C3 F3 78 */	mr r3, r30
/* 8022351C 002200FC  4B E3 36 51 */	bl func_80056B6C
/* 80223520 00220100  3B E3 00 00 */	addi r31, r3, 0
/* 80223524 00220104  2C 1F FF FF */	cmpwi r31, -1
/* 80223528 00220108  41 82 00 34 */	beq lbl_8022355C
/* 8022352C 0022010C  7F C3 F3 78 */	mr r3, r30
/* 80223530 00220110  4B E3 17 3D */	bl func_80054C6C
/* 80223534 00220114  2C 1F 00 00 */	cmpwi r31, 0
/* 80223538 00220118  40 82 00 10 */	bne lbl_80223548
/* 8022353C 0022011C  80 6D B4 70 */	lwz r3, lbl_804D6B10@sda21(r13)
/* 80223540 00220120  80 63 00 00 */	lwz r3, 0(r3)
/* 80223544 00220124  48 00 00 1C */	b lbl_80223560
lbl_80223548:
/* 80223548 00220128  2C 1F 00 01 */	cmpwi r31, 1
/* 8022354C 0022012C  40 82 00 10 */	bne lbl_8022355C
/* 80223550 00220130  80 6D B4 70 */	lwz r3, lbl_804D6B10@sda21(r13)
/* 80223554 00220134  80 63 00 00 */	lwz r3, 0(r3)
/* 80223558 00220138  48 00 00 08 */	b lbl_80223560
lbl_8022355C:
/* 8022355C 0022013C  38 60 00 00 */	li r3, 0
lbl_80223560:
/* 80223560 00220140  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80223564 00220144  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80223568 00220148  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8022356C 0022014C  38 21 00 18 */	addi r1, r1, 0x18
/* 80223570 00220150  7C 08 03 A6 */	mtlr r0
/* 80223574 00220154  4E 80 00 20 */	blr
.global lbl_80223578
lbl_80223578:
/* 80223578 00220158  38 60 00 01 */	li r3, 1
/* 8022357C 0022015C  4E 80 00 20 */	blr


.section .rodata
    .balign 8
.global lbl_803B84B8
lbl_803B84B8:
    .4byte 0x00370039
    .4byte 0x003B003D
    .4byte 0x003F0041
    .4byte 0x0043FFFF


.section .data
    .balign 8
.global lbl_803E9338
lbl_803E9338:
    .4byte lbl_802232F4
    .4byte lbl_80223320
    .4byte lbl_80223328
    .4byte lbl_8022332C
    .4byte NULL
    .4byte lbl_8022347C
    .4byte lbl_802234CC
    .4byte lbl_802234D4
    .4byte lbl_802234F4
    .4byte NULL
    .4byte lbl_80223330
    .4byte lbl_80223380
    .4byte lbl_80223388
    .4byte lbl_80223478
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9388
lbl_803E9388:
    .asciz "/GrTPr.dat"
    .balign 4
.global lbl_803E9394
lbl_803E9394:
    .4byte 0x0000003A
    .4byte lbl_803E9338
    .4byte lbl_803E9388
    .4byte lbl_80223164
    .4byte func_80223160
    .4byte lbl_802231DC
    .4byte lbl_802231E0
    .4byte lbl_80223204
    .4byte lbl_802234F8
    .4byte lbl_80223578
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtpurin.c"


.section .sbss
    .balign 8
.global lbl_804D6B10
lbl_804D6B10:
    .skip 0x4


.section .sdata2
    .balign 8
.global lbl_804DBCC8
lbl_804DBCC8:
    .4byte 0x43020000
    .4byte 0x00000000
