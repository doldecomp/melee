.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80391304
func_80391304:
/* 80391304 0038DEE4  7C 08 02 A6 */	mflr r0
/* 80391308 0038DEE8  90 01 00 04 */	stw r0, 4(r1)
/* 8039130C 0038DEEC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80391310 0038DEF0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80391314 0038DEF4  7C 7F 1B 78 */	mr r31, r3
/* 80391318 0038DEF8  4B FF FF 49 */	bl func_80391260
/* 8039131C 0038DEFC  80 7F 00 00 */	lwz r3, 0(r31)
/* 80391320 0038DF00  3C 80 80 4D */	lis r4, HSD_GObjLibInitData@ha
/* 80391324 0038DF04  80 1F 00 04 */	lwz r0, 4(r31)
/* 80391328 0038DF08  94 64 E3 80 */	stwu r3, HSD_GObjLibInitData@l(r4)
/* 8039132C 0038DF0C  90 04 00 04 */	stw r0, 4(r4)
/* 80391330 0038DF10  80 1F 00 08 */	lwz r0, 8(r31)
/* 80391334 0038DF14  90 04 00 08 */	stw r0, 8(r4)
/* 80391338 0038DF18  88 7F 00 00 */	lbz r3, 0(r31)
/* 8039133C 0038DF1C  38 03 00 01 */	addi r0, r3, 1
/* 80391340 0038DF20  54 03 10 3A */	slwi r3, r0, 2
/* 80391344 0038DF24  4B FE DE A1 */	bl HSD_MemAlloc
/* 80391348 0038DF28  90 6D C1 8C */	stw r3, lbl_804D782C@sda21(r13)
/* 8039134C 0038DF2C  88 7F 00 00 */	lbz r3, 0(r31)
/* 80391350 0038DF30  38 03 00 01 */	addi r0, r3, 1
/* 80391354 0038DF34  54 03 10 3A */	slwi r3, r0, 2
/* 80391358 0038DF38  4B FE DE 8D */	bl HSD_MemAlloc
/* 8039135C 0038DF3C  38 A0 00 00 */	li r5, 0
/* 80391360 0038DF40  90 6D C1 88 */	stw r3, plinklow_gobjs@sda21(r13)
/* 80391364 0038DF44  38 85 00 00 */	addi r4, r5, 0
/* 80391368 0038DF48  38 C0 00 00 */	li r6, 0
/* 8039136C 0038DF4C  48 00 00 1C */	b lbl_80391388
lbl_80391370:
/* 80391370 0038DF50  80 6D C1 88 */	lwz r3, plinklow_gobjs@sda21(r13)
/* 80391374 0038DF54  38 C6 00 01 */	addi r6, r6, 1
/* 80391378 0038DF58  7C 83 29 2E */	stwx r4, r3, r5
/* 8039137C 0038DF5C  80 6D C1 8C */	lwz r3, lbl_804D782C@sda21(r13)
/* 80391380 0038DF60  7C 83 29 2E */	stwx r4, r3, r5
/* 80391384 0038DF64  38 A5 00 04 */	addi r5, r5, 4
lbl_80391388:
/* 80391388 0038DF68  88 7F 00 00 */	lbz r3, 0(r31)
/* 8039138C 0038DF6C  38 03 00 01 */	addi r0, r3, 1
/* 80391390 0038DF70  7C 06 00 00 */	cmpw r6, r0
/* 80391394 0038DF74  41 80 FF DC */	blt lbl_80391370
/* 80391398 0038DF78  88 7F 00 01 */	lbz r3, 1(r31)
/* 8039139C 0038DF7C  38 03 00 02 */	addi r0, r3, 2
/* 803913A0 0038DF80  54 03 10 3A */	slwi r3, r0, 2
/* 803913A4 0038DF84  4B FE DE 41 */	bl HSD_MemAlloc
/* 803913A8 0038DF88  90 6D C1 84 */	stw r3, lbl_804D7824@sda21(r13)
/* 803913AC 0038DF8C  88 7F 00 01 */	lbz r3, 1(r31)
/* 803913B0 0038DF90  38 03 00 02 */	addi r0, r3, 2
/* 803913B4 0038DF94  54 03 10 3A */	slwi r3, r0, 2
/* 803913B8 0038DF98  4B FE DE 2D */	bl HSD_MemAlloc
/* 803913BC 0038DF9C  38 C0 00 00 */	li r6, 0
/* 803913C0 0038DFA0  90 6D C1 80 */	stw r3, lbl_804D7820@sda21(r13)
/* 803913C4 0038DFA4  38 A6 00 00 */	addi r5, r6, 0
/* 803913C8 0038DFA8  38 86 00 00 */	addi r4, r6, 0
/* 803913CC 0038DFAC  48 00 00 1C */	b lbl_803913E8
lbl_803913D0:
/* 803913D0 0038DFB0  80 6D C1 80 */	lwz r3, lbl_804D7820@sda21(r13)
/* 803913D4 0038DFB4  38 C6 00 01 */	addi r6, r6, 1
/* 803913D8 0038DFB8  7C 83 29 2E */	stwx r4, r3, r5
/* 803913DC 0038DFBC  80 6D C1 84 */	lwz r3, lbl_804D7824@sda21(r13)
/* 803913E0 0038DFC0  7C 83 29 2E */	stwx r4, r3, r5
/* 803913E4 0038DFC4  38 A5 00 04 */	addi r5, r5, 4
lbl_803913E8:
/* 803913E8 0038DFC8  88 7F 00 01 */	lbz r3, 1(r31)
/* 803913EC 0038DFCC  38 03 00 02 */	addi r0, r3, 2
/* 803913F0 0038DFD0  7C 06 00 00 */	cmpw r6, r0
/* 803913F4 0038DFD4  41 80 FF DC */	blt lbl_803913D0
/* 803913F8 0038DFD8  88 7F 00 02 */	lbz r3, 2(r31)
/* 803913FC 0038DFDC  38 03 00 01 */	addi r0, r3, 1
/* 80391400 0038DFE0  54 03 10 3A */	slwi r3, r0, 2
/* 80391404 0038DFE4  4B FE DD E1 */	bl HSD_MemAlloc
/* 80391408 0038DFE8  38 C0 00 00 */	li r6, 0
/* 8039140C 0038DFEC  90 6D C1 A0 */	stw r3, lbl_804D7840@sda21(r13)
/* 80391410 0038DFF0  38 86 00 00 */	addi r4, r6, 0
/* 80391414 0038DFF4  38 06 00 00 */	addi r0, r6, 0
/* 80391418 0038DFF8  48 00 00 14 */	b lbl_8039142C
lbl_8039141C:
/* 8039141C 0038DFFC  80 6D C1 A0 */	lwz r3, lbl_804D7840@sda21(r13)
/* 80391420 0038E000  38 C6 00 01 */	addi r6, r6, 1
/* 80391424 0038E004  7C 03 21 2E */	stwx r0, r3, r4
/* 80391428 0038E008  38 84 00 04 */	addi r4, r4, 4
lbl_8039142C:
/* 8039142C 0038E00C  88 7F 00 02 */	lbz r3, 2(r31)
/* 80391430 0038E010  38 A3 00 01 */	addi r5, r3, 1
/* 80391434 0038E014  7C 06 28 00 */	cmpw r6, r5
/* 80391438 0038E018  41 80 FF E4 */	blt lbl_8039141C
/* 8039143C 0038E01C  88 7F 00 00 */	lbz r3, 0(r31)
/* 80391440 0038E020  54 A0 10 3A */	slwi r0, r5, 2
/* 80391444 0038E024  38 63 00 01 */	addi r3, r3, 1
/* 80391448 0038E028  7C 63 01 D6 */	mullw r3, r3, r0
/* 8039144C 0038E02C  4B FE DD 99 */	bl HSD_MemAlloc
/* 80391450 0038E030  38 E0 00 00 */	li r7, 0
/* 80391454 0038E034  90 6D C1 A4 */	stw r3, lbl_804D7844@sda21(r13)
/* 80391458 0038E038  38 C7 00 00 */	addi r6, r7, 0
/* 8039145C 0038E03C  38 A7 00 00 */	addi r5, r7, 0
/* 80391460 0038E040  48 00 00 14 */	b lbl_80391474
lbl_80391464:
/* 80391464 0038E044  80 6D C1 A4 */	lwz r3, lbl_804D7844@sda21(r13)
/* 80391468 0038E048  38 E7 00 01 */	addi r7, r7, 1
/* 8039146C 0038E04C  7C A3 31 2E */	stwx r5, r3, r6
/* 80391470 0038E050  38 C6 00 04 */	addi r6, r6, 4
lbl_80391474:
/* 80391474 0038E054  88 9F 00 02 */	lbz r4, 2(r31)
/* 80391478 0038E058  88 7F 00 00 */	lbz r3, 0(r31)
/* 8039147C 0038E05C  38 84 00 01 */	addi r4, r4, 1
/* 80391480 0038E060  38 03 00 01 */	addi r0, r3, 1
/* 80391484 0038E064  7C 04 01 D6 */	mullw r0, r4, r0
/* 80391488 0038E068  7C 07 00 00 */	cmpw r7, r0
/* 8039148C 0038E06C  41 80 FF D8 */	blt lbl_80391464
/* 80391490 0038E070  3C 60 80 4D */	lis r3, gobj_alloc_data@ha
/* 80391494 0038E074  38 63 E3 8C */	addi r3, r3, gobj_alloc_data@l
/* 80391498 0038E078  38 80 00 38 */	li r4, 0x38
/* 8039149C 0038E07C  38 A0 00 04 */	li r5, 4
/* 803914A0 0038E080  4B FE 98 A9 */	bl HSD_ObjAllocInit
/* 803914A4 0038E084  3C 60 80 4D */	lis r3, gobjproc_alloc_data@ha
/* 803914A8 0038E088  38 63 E3 B8 */	addi r3, r3, gobjproc_alloc_data@l
/* 803914AC 0038E08C  38 80 00 18 */	li r4, 0x18
/* 803914B0 0038E090  38 A0 00 04 */	li r5, 4
/* 803914B4 0038E094  4B FE 98 95 */	bl HSD_ObjAllocInit
/* 803914B8 0038E098  80 9F 00 04 */	lwz r4, 4(r31)
/* 803914BC 0038E09C  38 60 00 00 */	li r3, 0
/* 803914C0 0038E0A0  48 00 00 10 */	b lbl_803914D0
lbl_803914C4:
/* 803914C4 0038E0A4  88 04 00 04 */	lbz r0, 4(r4)
/* 803914C8 0038E0A8  80 84 00 00 */	lwz r4, 0(r4)
/* 803914CC 0038E0AC  7C 63 02 14 */	add r3, r3, r0
lbl_803914D0:
/* 803914D0 0038E0B0  28 04 00 00 */	cmplwi r4, 0
/* 803914D4 0038E0B4  40 82 FF F0 */	bne lbl_803914C4
/* 803914D8 0038E0B8  2C 03 00 00 */	cmpwi r3, 0
/* 803914DC 0038E0BC  41 82 00 68 */	beq lbl_80391544
/* 803914E0 0038E0C0  54 63 10 3A */	slwi r3, r3, 2
/* 803914E4 0038E0C4  4B FE DD 01 */	bl HSD_MemAlloc
/* 803914E8 0038E0C8  90 6D C1 70 */	stw r3, lbl_804D7810@sda21(r13)
/* 803914EC 0038E0CC  39 00 00 00 */	li r8, 0
/* 803914F0 0038E0D0  81 3F 00 04 */	lwz r9, 4(r31)
/* 803914F4 0038E0D4  48 00 00 44 */	b lbl_80391538
lbl_803914F8:
/* 803914F8 0038E0D8  38 E0 00 00 */	li r7, 0
/* 803914FC 0038E0DC  38 A7 00 00 */	addi r5, r7, 0
/* 80391500 0038E0E0  38 C8 00 00 */	addi r6, r8, 0
/* 80391504 0038E0E4  48 00 00 24 */	b lbl_80391528
lbl_80391508:
/* 80391508 0038E0E8  80 89 00 08 */	lwz r4, 8(r9)
/* 8039150C 0038E0EC  38 E7 00 01 */	addi r7, r7, 1
/* 80391510 0038E0F0  80 6D C1 70 */	lwz r3, lbl_804D7810@sda21(r13)
/* 80391514 0038E0F4  39 08 00 04 */	addi r8, r8, 4
/* 80391518 0038E0F8  7C 04 28 2E */	lwzx r0, r4, r5
/* 8039151C 0038E0FC  38 A5 00 04 */	addi r5, r5, 4
/* 80391520 0038E100  7C 03 31 2E */	stwx r0, r3, r6
/* 80391524 0038E104  38 C6 00 04 */	addi r6, r6, 4
lbl_80391528:
/* 80391528 0038E108  88 09 00 04 */	lbz r0, 4(r9)
/* 8039152C 0038E10C  7C 07 00 00 */	cmpw r7, r0
/* 80391530 0038E110  41 80 FF D8 */	blt lbl_80391508
/* 80391534 0038E114  81 29 00 00 */	lwz r9, 0(r9)
lbl_80391538:
/* 80391538 0038E118  28 09 00 00 */	cmplwi r9, 0
/* 8039153C 0038E11C  40 82 FF BC */	bne lbl_803914F8
/* 80391540 0038E120  48 00 00 0C */	b lbl_8039154C
lbl_80391544:
/* 80391544 0038E124  38 00 00 00 */	li r0, 0
/* 80391548 0038E128  90 0D C1 70 */	stw r0, lbl_804D7810@sda21(r13)
lbl_8039154C:
/* 8039154C 0038E12C  38 00 00 00 */	li r0, 0
/* 80391550 0038E130  90 0D C1 9C */	stw r0, lbl_804D783C@sda21(r13)
/* 80391554 0038E134  3C 60 80 4D */	lis r3, lbl_804CE3E4@ha
/* 80391558 0038E138  90 0D C1 7C */	stw r0, lbl_804D781C@sda21(r13)
/* 8039155C 0038E13C  90 0D C1 98 */	stw r0, lbl_804D7838@sda21(r13)
/* 80391560 0038E140  90 03 E3 E4 */	stw r0, lbl_804CE3E4@l(r3)
/* 80391564 0038E144  90 0D C1 78 */	stw r0, lbl_804D7818@sda21(r13)
/* 80391568 0038E148  90 0D C1 74 */	stw r0, lbl_804D7814@sda21(r13)
/* 8039156C 0038E14C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80391570 0038E150  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80391574 0038E154  38 21 00 18 */	addi r1, r1, 0x18
/* 80391578 0038E158  7C 08 03 A6 */	mtlr r0
/* 8039157C 0038E15C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_804085F0
lbl_804085F0:
    .4byte 0x00000001
    .4byte 0x00000004
    .4byte 0x00000002
    .4byte NULL
.global lbl_80408600
lbl_80408600:
    .4byte lbl_80391120
    .4byte HSD_LObjRemoveAll
    .4byte HSD_JObjRemoveAll
    .4byte lbl_803911C0
.global lbl_80408610
lbl_80408610:
    .4byte NULL
    .4byte 0x04000000
    .4byte lbl_80408600
    .4byte NULL
.global lbl_80408620
lbl_80408620:
    .4byte 0x3F3F0200
    .4byte NULL
    .4byte NULL
    .4byte NULL


.section .bss, "wa"
    .balign 8
.global HSD_GObjLibInitData
HSD_GObjLibInitData:
    .skip 0xC
.global gobj_alloc_data
gobj_alloc_data:
    .skip 0x2C
.global gobjproc_alloc_data
gobjproc_alloc_data:
    .skip 0x2C
.global lbl_804CE3E4
lbl_804CE3E4:
    .skip 0x14


.section .sbss
    .balign 8
.global lbl_804D7810
lbl_804D7810:
    .skip 0x4
.global lbl_804D7814
lbl_804D7814:
    .skip 0x4
.global lbl_804D7818
lbl_804D7818:
    .skip 0x4
.global lbl_804D781C
lbl_804D781C:
    .skip 0x4
.global lbl_804D7820
lbl_804D7820:
    .skip 0x4
.global lbl_804D7824
lbl_804D7824:
    .skip 0x4
.global plinklow_gobjs
plinklow_gobjs:
    .skip 0x4
.global lbl_804D782C
lbl_804D782C:
    .skip 0x4
.global lbl_804D7830
lbl_804D7830:
    .skip 0x4
.global lbl_804D7834
lbl_804D7834:
    .skip 0x4
.global lbl_804D7838
lbl_804D7838:
    .skip 0x4
.global lbl_804D783C
lbl_804D783C:
    .skip 0x4
.global lbl_804D7840
lbl_804D7840:
    .skip 0x4
.global lbl_804D7844
lbl_804D7844:
    .skip 0x4
.global lbl_804D7848
lbl_804D7848:
    .skip 0x1
.global lbl_804D7849
lbl_804D7849:
    .skip 0x1
.global lbl_804D784A
lbl_804D784A:
    .skip 0x1
.global lbl_804D784B
lbl_804D784B:
    .skip 0x5
