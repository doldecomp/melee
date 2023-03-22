.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_802246D8
func_802246D8:
/* 802246D8 002212B8  4E 80 00 20 */	blr
.global lbl_802246DC
lbl_802246DC:
/* 802246DC 002212BC  7C 08 02 A6 */	mflr r0
/* 802246E0 002212C0  90 01 00 04 */	stw r0, 4(r1)
/* 802246E4 002212C4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802246E8 002212C8  4B FA 03 11 */	bl Ground_801C49F8
/* 802246EC 002212CC  3C 80 80 4A */	lis r4, stage_info@ha
/* 802246F0 002212D0  90 6D B4 78 */	stw r3, lbl_804D6B18@sda21(r13)
/* 802246F4 002212D4  38 64 E6 C8 */	addi r3, r4, stage_info@l
/* 802246F8 002212D8  38 A3 00 8C */	addi r5, r3, 0x8c
/* 802246FC 002212DC  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80224700 002212E0  38 60 00 00 */	li r3, 0
/* 80224704 002212E4  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80224708 002212E8  98 05 00 00 */	stb r0, 0(r5)
/* 8022470C 002212EC  38 80 00 01 */	li r4, 1
/* 80224710 002212F0  38 60 00 00 */	li r3, 0
/* 80224714 002212F4  88 05 00 00 */	lbz r0, 0(r5)
/* 80224718 002212F8  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 8022471C 002212FC  98 05 00 00 */	stb r0, 0(r5)
/* 80224720 00221300  48 00 00 65 */	bl func_80224784
/* 80224724 00221304  38 60 00 01 */	li r3, 1
/* 80224728 00221308  48 00 00 5D */	bl func_80224784
/* 8022472C 0022130C  38 60 00 02 */	li r3, 2
/* 80224730 00221310  48 00 00 55 */	bl func_80224784
/* 80224734 00221314  4B F9 F2 8D */	bl Ground_801C39C0
/* 80224738 00221318  4B F9 F4 7D */	bl Ground_801C3BB4
/* 8022473C 0022131C  4B F9 FA D5 */	bl Ground_801C4210
/* 80224740 00221320  4B F9 FB 6D */	bl Ground_801C42AC
/* 80224744 00221324  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80224748 00221328  38 21 00 08 */	addi r1, r1, 8
/* 8022474C 0022132C  7C 08 03 A6 */	mtlr r0
/* 80224750 00221330  4E 80 00 20 */	blr
.global lbl_80224754
lbl_80224754:
/* 80224754 00221334  4E 80 00 20 */	blr
.global lbl_80224758
lbl_80224758:
/* 80224758 00221338  7C 08 02 A6 */	mflr r0
/* 8022475C 0022133C  38 60 00 00 */	li r3, 0
/* 80224760 00221340  90 01 00 04 */	stw r0, 4(r1)
/* 80224764 00221344  94 21 FF F8 */	stwu r1, -8(r1)
/* 80224768 00221348  4B FA 66 9D */	bl grZakoGenerator_801CAE04
/* 8022476C 0022134C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80224770 00221350  38 21 00 08 */	addi r1, r1, 8
/* 80224774 00221354  7C 08 03 A6 */	mtlr r0
/* 80224778 00221358  4E 80 00 20 */	blr
.global lbl_8022477C
lbl_8022477C:
/* 8022477C 0022135C  38 60 00 00 */	li r3, 0
/* 80224780 00221360  4E 80 00 20 */	blr

.global func_80224784
func_80224784:
/* 80224784 00221364  7C 08 02 A6 */	mflr r0
/* 80224788 00221368  90 01 00 04 */	stw r0, 4(r1)
/* 8022478C 0022136C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80224790 00221370  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80224794 00221374  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80224798 00221378  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8022479C 0022137C  93 81 00 10 */	stw r28, 0x10(r1)
/* 802247A0 00221380  3B 83 00 00 */	addi r28, r3, 0
/* 802247A4 00221384  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 802247A8 00221388  3C 60 80 3F */	lis r3, lbl_803E9880@ha
/* 802247AC 0022138C  3B E3 98 80 */	addi r31, r3, lbl_803E9880@l
/* 802247B0 00221390  38 7C 00 00 */	addi r3, r28, 0
/* 802247B4 00221394  7F BF 02 14 */	add r29, r31, r0
/* 802247B8 00221398  4B F9 CD 19 */	bl Ground_801C14D0
/* 802247BC 0022139C  7C 7E 1B 79 */	or. r30, r3, r3
/* 802247C0 002213A0  41 82 00 70 */	beq lbl_80224830
/* 802247C4 002213A4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 802247C8 002213A8  38 00 00 00 */	li r0, 0
/* 802247CC 002213AC  3C 60 80 1C */	lis r3, grDisplay_801C5DB0@ha
/* 802247D0 002213B0  90 1F 00 08 */	stw r0, 8(r31)
/* 802247D4 002213B4  38 83 5D B0 */	addi r4, r3, grDisplay_801C5DB0@l
/* 802247D8 002213B8  38 7E 00 00 */	addi r3, r30, 0
/* 802247DC 002213BC  90 1F 00 0C */	stw r0, 0xc(r31)
/* 802247E0 002213C0  38 A0 00 03 */	li r5, 3
/* 802247E4 002213C4  38 C0 00 00 */	li r6, 0
/* 802247E8 002213C8  48 16 BE B5 */	bl GObj_SetupGXLink
/* 802247EC 002213CC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 802247F0 002213D0  28 00 00 00 */	cmplwi r0, 0
/* 802247F4 002213D4  41 82 00 08 */	beq lbl_802247FC
/* 802247F8 002213D8  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_802247FC:
/* 802247FC 002213DC  81 9D 00 00 */	lwz r12, 0(r29)
/* 80224800 002213E0  28 0C 00 00 */	cmplwi r12, 0
/* 80224804 002213E4  41 82 00 10 */	beq lbl_80224814
/* 80224808 002213E8  7D 88 03 A6 */	mtlr r12
/* 8022480C 002213EC  38 7E 00 00 */	addi r3, r30, 0
/* 80224810 002213F0  4E 80 00 21 */	blrl
lbl_80224814:
/* 80224814 002213F4  80 9D 00 08 */	lwz r4, 8(r29)
/* 80224818 002213F8  28 04 00 00 */	cmplwi r4, 0
/* 8022481C 002213FC  41 82 00 2C */	beq lbl_80224848
/* 80224820 00221400  38 7E 00 00 */	addi r3, r30, 0
/* 80224824 00221404  38 A0 00 04 */	li r5, 4
/* 80224828 00221408  48 16 B5 2D */	bl func_8038FD54
/* 8022482C 0022140C  48 00 00 1C */	b lbl_80224848
lbl_80224830:
/* 80224830 00221410  38 DC 00 00 */	addi r6, r28, 0
/* 80224834 00221414  4C C6 31 82 */	crclr 6
/* 80224838 00221418  38 7F 00 90 */	addi r3, r31, 0x90
/* 8022483C 0022141C  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80224840 00221420  38 A0 00 C9 */	li r5, 0xc9
/* 80224844 00221424  48 12 0E 65 */	bl OSReport
lbl_80224848:
/* 80224848 00221428  7F C3 F3 78 */	mr r3, r30
/* 8022484C 0022142C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224850 00221430  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80224854 00221434  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80224858 00221438  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8022485C 0022143C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80224860 00221440  38 21 00 20 */	addi r1, r1, 0x20
/* 80224864 00221444  7C 08 03 A6 */	mtlr r0
/* 80224868 00221448  4E 80 00 20 */	blr
.global lbl_8022486C
lbl_8022486C:
/* 8022486C 0022144C  7C 08 02 A6 */	mflr r0
/* 80224870 00221450  38 A0 00 00 */	li r5, 0
/* 80224874 00221454  90 01 00 04 */	stw r0, 4(r1)
/* 80224878 00221458  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022487C 0022145C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80224880 00221460  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80224884 00221464  4B FA 38 B5 */	bl grAnime_801C8138
/* 80224888 00221468  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8022488C 0022146C  38 21 00 08 */	addi r1, r1, 8
/* 80224890 00221470  7C 08 03 A6 */	mtlr r0
/* 80224894 00221474  4E 80 00 20 */	blr
.global lbl_80224898
lbl_80224898:
/* 80224898 00221478  38 60 00 00 */	li r3, 0
/* 8022489C 0022147C  4E 80 00 20 */	blr
.global lbl_802248A0
lbl_802248A0:
/* 802248A0 00221480  4E 80 00 20 */	blr
.global lbl_802248A4
lbl_802248A4:
/* 802248A4 00221484  4E 80 00 20 */	blr
.global lbl_802248A8
lbl_802248A8:
/* 802248A8 00221488  7C 08 02 A6 */	mflr r0
/* 802248AC 0022148C  90 01 00 04 */	stw r0, 4(r1)
/* 802248B0 00221490  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802248B4 00221494  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802248B8 00221498  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802248BC 0022149C  7C 7E 1B 78 */	mr r30, r3
/* 802248C0 002214A0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802248C4 002214A4  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802248C8 002214A8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802248CC 002214AC  4B F9 E6 05 */	bl Ground_801C2ED0
/* 802248D0 002214B0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802248D4 002214B4  38 7E 00 00 */	addi r3, r30, 0
/* 802248D8 002214B8  38 A0 00 00 */	li r5, 0
/* 802248DC 002214BC  4B FA 38 5D */	bl grAnime_801C8138
/* 802248E0 002214C0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802248E4 002214C4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802248E8 002214C8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802248EC 002214CC  38 21 00 20 */	addi r1, r1, 0x20
/* 802248F0 002214D0  7C 08 03 A6 */	mtlr r0
/* 802248F4 002214D4  4E 80 00 20 */	blr
.global lbl_802248F8
lbl_802248F8:
/* 802248F8 002214D8  38 60 00 00 */	li r3, 0
/* 802248FC 002214DC  4E 80 00 20 */	blr
.global lbl_80224900
lbl_80224900:
/* 80224900 002214E0  7C 08 02 A6 */	mflr r0
/* 80224904 002214E4  90 01 00 04 */	stw r0, 4(r1)
/* 80224908 002214E8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8022490C 002214EC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80224910 002214F0  7C 7F 1B 78 */	mr r31, r3
/* 80224914 002214F4  4B DE CC E1 */	bl func_800115F4
/* 80224918 002214F8  7F E3 FB 78 */	mr r3, r31
/* 8022491C 002214FC  4B F9 E6 C5 */	bl Ground_801C2FE0
/* 80224920 00221500  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80224924 00221504  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80224928 00221508  38 21 00 18 */	addi r1, r1, 0x18
/* 8022492C 0022150C  7C 08 03 A6 */	mtlr r0
/* 80224930 00221510  4E 80 00 20 */	blr
.global lbl_80224934
lbl_80224934:
/* 80224934 00221514  4E 80 00 20 */	blr
.global lbl_80224938
lbl_80224938:
/* 80224938 00221518  7C 08 02 A6 */	mflr r0
/* 8022493C 0022151C  90 01 00 04 */	stw r0, 4(r1)
/* 80224940 00221520  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80224944 00221524  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80224948 00221528  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8022494C 0022152C  7C 7E 1B 78 */	mr r30, r3
/* 80224950 00221530  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80224954 00221534  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80224958 00221538  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8022495C 0022153C  4B F9 E5 75 */	bl Ground_801C2ED0
/* 80224960 00221540  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224964 00221544  38 7E 00 00 */	addi r3, r30, 0
/* 80224968 00221548  38 A0 00 00 */	li r5, 0
/* 8022496C 0022154C  4B FA 37 CD */	bl grAnime_801C8138
/* 80224970 00221550  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224974 00221554  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80224978 00221558  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022497C 0022155C  38 21 00 20 */	addi r1, r1, 0x20
/* 80224980 00221560  7C 08 03 A6 */	mtlr r0
/* 80224984 00221564  4E 80 00 20 */	blr
.global lbl_80224988
lbl_80224988:
/* 80224988 00221568  38 60 00 00 */	li r3, 0
/* 8022498C 0022156C  4E 80 00 20 */	blr
.global lbl_80224990
lbl_80224990:
/* 80224990 00221570  7C 08 02 A6 */	mflr r0
/* 80224994 00221574  90 01 00 04 */	stw r0, 4(r1)
/* 80224998 00221578  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022499C 0022157C  4B F9 E6 45 */	bl Ground_801C2FE0
/* 802249A0 00221580  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802249A4 00221584  38 21 00 08 */	addi r1, r1, 8
/* 802249A8 00221588  7C 08 03 A6 */	mtlr r0
/* 802249AC 0022158C  4E 80 00 20 */	blr
.global lbl_802249B0
lbl_802249B0:
/* 802249B0 00221590  4E 80 00 20 */	blr
.global lbl_802249B4
lbl_802249B4:
/* 802249B4 00221594  7C 08 02 A6 */	mflr r0
/* 802249B8 00221598  90 01 00 04 */	stw r0, 4(r1)
/* 802249BC 0022159C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802249C0 002215A0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802249C4 002215A4  3B E3 00 00 */	addi r31, r3, 0
/* 802249C8 002215A8  2C 1F FF FF */	cmpwi r31, -1
/* 802249CC 002215AC  41 82 00 68 */	beq lbl_80224A34
/* 802249D0 002215B0  7F E3 FB 78 */	mr r3, r31
/* 802249D4 002215B4  4B E3 21 99 */	bl func_80056B6C
/* 802249D8 002215B8  2C 03 FF FF */	cmpwi r3, -1
/* 802249DC 002215BC  41 82 00 58 */	beq lbl_80224A34
/* 802249E0 002215C0  2C 03 00 00 */	cmpwi r3, 0
/* 802249E4 002215C4  40 82 00 50 */	bne lbl_80224A34
/* 802249E8 002215C8  7F E3 FB 78 */	mr r3, r31
/* 802249EC 002215CC  4B E3 02 81 */	bl func_80054C6C
/* 802249F0 002215D0  2C 03 00 02 */	cmpwi r3, 2
/* 802249F4 002215D4  40 82 00 10 */	bne lbl_80224A04
/* 802249F8 002215D8  80 6D B4 78 */	lwz r3, lbl_804D6B18@sda21(r13)
/* 802249FC 002215DC  80 63 00 00 */	lwz r3, 0(r3)
/* 80224A00 002215E0  48 00 00 38 */	b lbl_80224A38
lbl_80224A04:
/* 80224A04 002215E4  2C 03 00 04 */	cmpwi r3, 4
/* 80224A08 002215E8  40 82 00 10 */	bne lbl_80224A18
/* 80224A0C 002215EC  80 6D B4 78 */	lwz r3, lbl_804D6B18@sda21(r13)
/* 80224A10 002215F0  80 63 00 04 */	lwz r3, 4(r3)
/* 80224A14 002215F4  48 00 00 24 */	b lbl_80224A38
lbl_80224A18:
/* 80224A18 002215F8  2C 03 00 08 */	cmpwi r3, 8
/* 80224A1C 002215FC  40 82 00 10 */	bne lbl_80224A2C
/* 80224A20 00221600  80 6D B4 78 */	lwz r3, lbl_804D6B18@sda21(r13)
/* 80224A24 00221604  80 63 00 08 */	lwz r3, 8(r3)
/* 80224A28 00221608  48 00 00 10 */	b lbl_80224A38
lbl_80224A2C:
/* 80224A2C 0022160C  38 60 00 00 */	li r3, 0
/* 80224A30 00221610  48 00 00 08 */	b lbl_80224A38
lbl_80224A34:
/* 80224A34 00221614  38 60 00 00 */	li r3, 0
lbl_80224A38:
/* 80224A38 00221618  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80224A3C 0022161C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80224A40 00221620  38 21 00 18 */	addi r1, r1, 0x18
/* 80224A44 00221624  7C 08 03 A6 */	mtlr r0
/* 80224A48 00221628  4E 80 00 20 */	blr
.global lbl_80224A4C
lbl_80224A4C:
/* 80224A4C 0022162C  38 60 00 01 */	li r3, 1
/* 80224A50 00221630  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803E9880
lbl_803E9880:
    .4byte lbl_8022486C
    .4byte lbl_80224898
    .4byte lbl_802248A0
    .4byte lbl_802248A4
    .4byte NULL
    .4byte lbl_80224938
    .4byte lbl_80224988
    .4byte lbl_80224990
    .4byte lbl_802249B0
    .4byte NULL
    .4byte lbl_802248A8
    .4byte lbl_802248F8
    .4byte lbl_80224900
    .4byte lbl_80224934
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E98D0
lbl_803E98D0:
    .asciz "/GrTGn.dat"
    .balign 4
.global lbl_803E98DC
lbl_803E98DC:
    .4byte 0x00000041
    .4byte lbl_803E9880
    .4byte lbl_803E98D0
    .4byte lbl_802246DC
    .4byte func_802246D8
    .4byte lbl_80224754
    .4byte lbl_80224758
    .4byte lbl_8022477C
    .4byte lbl_802249B4
    .4byte lbl_80224A4C
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtganon.c"


.section .sbss
    .balign 8
.global lbl_804D6B18
lbl_804D6B18:
    .skip 0x4
