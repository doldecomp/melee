#include <platform.h>

#include "ftLk_SpecialLw.h"

#include "ftLk_Init.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#ifdef MWERKS_GEKKO
float const ftLk_Init_804D92F0 = 0;
float const ftLk_Init_804D92F4 = 1;
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialLw_Enter(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB65C 000E823C  7C 08 02 A6 */	mflr r0
/* 800EB660 000E8240  38 80 00 6C */	li r4, 0x6c
/* 800EB664 000E8244  90 01 00 04 */	stw r0, 4(r1)
/* 800EB668 000E8248  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800EB66C 000E824C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800EB670 000E8250  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800EB674 000E8254  7C 7E 1B 78 */	mr r30, r3
/* 800EB678 000E8258  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EB67C 000E825C  48 00 00 E1 */	bl ftLk_800EB75C
/* 800EB680 000E8260  2C 03 00 01 */	cmpwi r3, 1
/* 800EB684 000E8264  41 82 00 40 */	beq lbl_800EB6C4
/* 800EB688 000E8268  38 00 00 00 */	li r0, 0
/* 800EB68C 000E826C  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 800EB690 000E8270  38 7E 00 00 */	addi r3, r30, 0
/* 800EB694 000E8274  38 80 01 66 */	li r4, 0x166
/* 800EB698 000E8278  C0 22 99 10 */	lfs f1, ftLk_Init_804D92F0
/* 800EB69C 000E827C  38 A0 00 00 */	li r5, 0
/* 800EB6A0 000E8280  C0 42 99 14 */	lfs f2, ftLk_Init_804D92F4
/* 800EB6A4 000E8284  38 C0 00 00 */	li r6, 0
/* 800EB6A8 000E8288  FC 60 08 90 */	fmr f3, f1
/* 800EB6AC 000E828C  4B F7 DD 01 */	bl Fighter_ChangeMotionState
/* 800EB6B0 000E8290  7F C3 F3 78 */	mr r3, r30
/* 800EB6B4 000E8294  4B F8 34 F1 */	bl ftAnim_8006EBA4
/* 800EB6B8 000E8298  3C 60 80 0F */	lis r3, lbl_800EB7C8@ha
/* 800EB6BC 000E829C  38 03 B7 C8 */	addi r0, r3, lbl_800EB7C8@l
/* 800EB6C0 000E82A0  90 1F 21 BC */	stw r0, 0x21bc(r31)
lbl_800EB6C4:
/* 800EB6C4 000E82A4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800EB6C8 000E82A8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800EB6CC 000E82AC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800EB6D0 000E82B0  38 21 00 18 */	addi r1, r1, 0x18
/* 800EB6D4 000E82B4  7C 08 03 A6 */	mtlr r0
/* 800EB6D8 000E82B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialAirLw_Enter(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB6DC 000E82BC  7C 08 02 A6 */	mflr r0
/* 800EB6E0 000E82C0  38 80 00 70 */	li r4, 0x70
/* 800EB6E4 000E82C4  90 01 00 04 */	stw r0, 4(r1)
/* 800EB6E8 000E82C8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800EB6EC 000E82CC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800EB6F0 000E82D0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800EB6F4 000E82D4  7C 7E 1B 78 */	mr r30, r3
/* 800EB6F8 000E82D8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EB6FC 000E82DC  48 00 00 61 */	bl ftLk_800EB75C
/* 800EB700 000E82E0  2C 03 00 01 */	cmpwi r3, 1
/* 800EB704 000E82E4  41 82 00 40 */	beq lbl_800EB744
/* 800EB708 000E82E8  38 00 00 00 */	li r0, 0
/* 800EB70C 000E82EC  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 800EB710 000E82F0  38 7E 00 00 */	addi r3, r30, 0
/* 800EB714 000E82F4  38 80 01 67 */	li r4, 0x167
/* 800EB718 000E82F8  C0 22 99 10 */	lfs f1, ftLk_Init_804D92F0
/* 800EB71C 000E82FC  38 A0 00 00 */	li r5, 0
/* 800EB720 000E8300  C0 42 99 14 */	lfs f2, ftLk_Init_804D92F4
/* 800EB724 000E8304  38 C0 00 00 */	li r6, 0
/* 800EB728 000E8308  FC 60 08 90 */	fmr f3, f1
/* 800EB72C 000E830C  4B F7 DC 81 */	bl Fighter_ChangeMotionState
/* 800EB730 000E8310  7F C3 F3 78 */	mr r3, r30
/* 800EB734 000E8314  4B F8 34 71 */	bl ftAnim_8006EBA4
/* 800EB738 000E8318  3C 60 80 0F */	lis r3, lbl_800EB7C8@ha
/* 800EB73C 000E831C  38 03 B7 C8 */	addi r0, r3, lbl_800EB7C8@l
/* 800EB740 000E8320  90 1F 21 BC */	stw r0, 0x21bc(r31)
lbl_800EB744:
/* 800EB744 000E8324  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800EB748 000E8328  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800EB74C 000E832C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800EB750 000E8330  38 21 00 18 */	addi r1, r1, 0x18
/* 800EB754 000E8334  7C 08 03 A6 */	mtlr r0
/* 800EB758 000E8338  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_800EB75C(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB75C 000E833C  7C 08 02 A6 */	mflr r0
/* 800EB760 000E8340  90 01 00 04 */	stw r0, 4(r1)
/* 800EB764 000E8344  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EB768 000E8348  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EB76C 000E834C  7C 9F 23 78 */	mr r31, r4
/* 800EB770 000E8350  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800EB774 000E8354  7C 7E 1B 78 */	mr r30, r3
/* 800EB778 000E8358  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800EB77C 000E835C  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 800EB780 000E8360  28 03 00 00 */	cmplwi r3, 0
/* 800EB784 000E8364  41 82 00 28 */	beq lbl_800EB7AC
/* 800EB788 000E8368  48 17 FB 79 */	bl itGetKind
/* 800EB78C 000E836C  38 03 FF C6 */	addi r0, r3, -58
/* 800EB790 000E8370  28 00 00 01 */	cmplwi r0, 1
/* 800EB794 000E8374  41 81 00 10 */	bgt lbl_800EB7A4
/* 800EB798 000E8378  38 7E 00 00 */	addi r3, r30, 0
/* 800EB79C 000E837C  38 9F 00 00 */	addi r4, r31, 0
/* 800EB7A0 000E8380  4B FA A0 55 */	bl ft_800957F4
lbl_800EB7A4:
/* 800EB7A4 000E8384  38 60 00 01 */	li r3, 1
/* 800EB7A8 000E8388  48 00 00 08 */	b lbl_800EB7B0
lbl_800EB7AC:
/* 800EB7AC 000E838C  38 60 00 00 */	li r3, 0
lbl_800EB7B0:
/* 800EB7B0 000E8390  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EB7B4 000E8394  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EB7B8 000E8398  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800EB7BC 000E839C  38 21 00 20 */	addi r1, r1, 0x20
/* 800EB7C0 000E83A0  7C 08 03 A6 */	mtlr r0
/* 800EB7C4 000E83A4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbl_800EB7C8(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 800EB7C8 000E83A8  7C 08 02 A6 */	mflr r0
/* 800EB7CC 000E83AC  90 01 00 04 */	stw r0, 4(r1)
/* 800EB7D0 000E83B0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800EB7D4 000E83B4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800EB7D8 000E83B8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800EB7DC 000E83BC  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800EB7E0 000E83C0  7C 7D 1B 78 */	mr r29, r3
/* 800EB7E4 000E83C4  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800EB7E8 000E83C8  88 7E 22 10 */	lbz r3, 0x2210(r30)
/* 800EB7EC 000E83CC  83 FE 02 D4 */	lwz r31, 0x2d4(r30)
/* 800EB7F0 000E83D0  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 800EB7F4 000E83D4  41 82 00 18 */	beq lbl_800EB80C
/* 800EB7F8 000E83D8  38 00 00 00 */	li r0, 0
/* 800EB7FC 000E83DC  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 800EB800 000E83E0  98 7E 22 10 */	stb r3, 0x2210(r30)
/* 800EB804 000E83E4  38 00 00 01 */	li r0, 1
/* 800EB808 000E83E8  48 00 00 08 */	b lbl_800EB810
lbl_800EB80C:
/* 800EB80C 000E83EC  38 00 00 00 */	li r0, 0
lbl_800EB810:
/* 800EB810 000E83F0  2C 00 00 00 */	cmpwi r0, 0
/* 800EB814 000E83F4  41 82 00 74 */	beq lbl_800EB888
/* 800EB818 000E83F8  38 7E 00 00 */	addi r3, r30, 0
/* 800EB81C 000E83FC  38 80 00 1F */	li r4, 0x1f
/* 800EB820 000E8400  4B F8 97 ED */	bl ftParts_8007500C
/* 800EB824 000E8404  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800EB828 000E8408  54 60 20 36 */	slwi r0, r3, 4
/* 800EB82C 000E840C  38 A1 00 14 */	addi r5, r1, 0x14
/* 800EB830 000E8410  7C 64 00 2E */	lwzx r3, r4, r0
/* 800EB834 000E8414  38 80 00 00 */	li r4, 0
/* 800EB838 000E8418  4B F1 F9 95 */	bl lb_8000B1CC
/* 800EB83C 000E841C  80 BE 01 0C */	lwz r5, 0x10c(r30)
/* 800EB840 000E8420  7F A3 EB 78 */	mr r3, r29
/* 800EB844 000E8424  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 800EB848 000E8428  38 81 00 14 */	addi r4, r1, 0x14
/* 800EB84C 000E842C  80 A5 00 08 */	lwz r5, 8(r5)
/* 800EB850 000E8430  80 DF 00 48 */	lwz r6, 0x48(r31)
/* 800EB854 000E8434  88 A5 00 10 */	lbz r5, 0x10(r5)
/* 800EB858 000E8438  48 1B 25 01 */	bl it_8029DD58
/* 800EB85C 000E843C  7C 7F 1B 78 */	mr r31, r3
/* 800EB860 000E8440  93 FE 19 74 */	stw r31, 0x1974(r30)
/* 800EB864 000E8444  38 7D 00 00 */	addi r3, r29, 0
/* 800EB868 000E8448  38 80 00 02 */	li r4, 2
/* 800EB86C 000E844C  38 A0 00 01 */	li r5, 1
/* 800EB870 000E8450  4B F8 91 DD */	bl ftParts_80074A4C
/* 800EB874 000E8454  28 1F 00 00 */	cmplwi r31, 0
/* 800EB878 000E8458  41 82 00 10 */	beq lbl_800EB888
/* 800EB87C 000E845C  38 7D 00 00 */	addi r3, r29, 0
/* 800EB880 000E8460  38 80 00 01 */	li r4, 1
/* 800EB884 000E8464  4B FA 8F 95 */	bl ft_80094818
lbl_800EB888:
/* 800EB888 000E8468  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800EB88C 000E846C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800EB890 000E8470  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800EB894 000E8474  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800EB898 000E8478  38 21 00 30 */	addi r1, r1, 0x30
/* 800EB89C 000E847C  7C 08 03 A6 */	mtlr r0
/* 800EB8A0 000E8480  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialLw_Anim(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB8A4 000E8484  7C 08 02 A6 */	mflr r0
/* 800EB8A8 000E8488  90 01 00 04 */	stw r0, 4(r1)
/* 800EB8AC 000E848C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EB8B0 000E8490  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EB8B4 000E8494  7C 7F 1B 78 */	mr r31, r3
/* 800EB8B8 000E8498  4B F8 39 81 */	bl ftAnim_IsFramesRemaining
/* 800EB8BC 000E849C  2C 03 00 00 */	cmpwi r3, 0
/* 800EB8C0 000E84A0  40 82 00 0C */	bne lbl_800EB8CC
/* 800EB8C4 000E84A4  7F E3 FB 78 */	mr r3, r31
/* 800EB8C8 000E84A8  4B F9 E9 F5 */	bl ft_8008A2BC
lbl_800EB8CC:
/* 800EB8CC 000E84AC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EB8D0 000E84B0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EB8D4 000E84B4  38 21 00 20 */	addi r1, r1, 0x20
/* 800EB8D8 000E84B8  7C 08 03 A6 */	mtlr r0
/* 800EB8DC 000E84BC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialAirLw_Anim(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB8E0 000E84C0  7C 08 02 A6 */	mflr r0
/* 800EB8E4 000E84C4  90 01 00 04 */	stw r0, 4(r1)
/* 800EB8E8 000E84C8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800EB8EC 000E84CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800EB8F0 000E84D0  7C 7F 1B 78 */	mr r31, r3
/* 800EB8F4 000E84D4  4B F8 39 45 */	bl ftAnim_IsFramesRemaining
/* 800EB8F8 000E84D8  2C 03 00 00 */	cmpwi r3, 0
/* 800EB8FC 000E84DC  40 82 00 0C */	bne lbl_800EB908
/* 800EB900 000E84E0  7F E3 FB 78 */	mr r3, r31
/* 800EB904 000E84E4  4B FE 0E 2D */	bl ft_800CC730
lbl_800EB908:
/* 800EB908 000E84E8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800EB90C 000E84EC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800EB910 000E84F0  38 21 00 20 */	addi r1, r1, 0x20
/* 800EB914 000E84F4  7C 08 03 A6 */	mtlr r0
/* 800EB918 000E84F8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialLw_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB91C 000E84FC  7C 08 02 A6 */	mflr r0
/* 800EB920 000E8500  90 01 00 04 */	stw r0, 4(r1)
/* 800EB924 000E8504  94 21 FF F8 */	stwu r1, -8(r1)
/* 800EB928 000E8508  4B F9 96 15 */	bl ft_80084F3C
/* 800EB92C 000E850C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800EB930 000E8510  38 21 00 08 */	addi r1, r1, 8
/* 800EB934 000E8514  7C 08 03 A6 */	mtlr r0
/* 800EB938 000E8518  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialAirLw_Phys(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB93C 000E851C  7C 08 02 A6 */	mflr r0
/* 800EB940 000E8520  90 01 00 04 */	stw r0, 4(r1)
/* 800EB944 000E8524  94 21 FF F8 */	stwu r1, -8(r1)
/* 800EB948 000E8528  4B F9 95 A5 */	bl ft_80084EEC
/* 800EB94C 000E852C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800EB950 000E8530  38 21 00 08 */	addi r1, r1, 8
/* 800EB954 000E8534  7C 08 03 A6 */	mtlr r0
/* 800EB958 000E8538  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialLw_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB95C 000E853C  7C 08 02 A6 */	mflr r0
/* 800EB960 000E8540  90 01 00 04 */	stw r0, 4(r1)
/* 800EB964 000E8544  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800EB968 000E8548  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800EB96C 000E854C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800EB970 000E8550  7C 7E 1B 78 */	mr r30, r3
/* 800EB974 000E8554  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EB978 000E8558  4B F9 6D 91 */	bl ft_80082708
/* 800EB97C 000E855C  2C 03 00 00 */	cmpwi r3, 0
/* 800EB980 000E8560  40 82 00 3C */	bne lbl_800EB9BC
/* 800EB984 000E8564  7F E3 FB 78 */	mr r3, r31
/* 800EB988 000E8568  4B F9 1C 4D */	bl ftCommon_8007D5D4
/* 800EB98C 000E856C  3C 80 0C 4C */	lis r4, 0x0C4C5080@ha
/* 800EB990 000E8570  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800EB994 000E8574  C0 42 99 14 */	lfs f2, ftLk_Init_804D92F4
/* 800EB998 000E8578  7F C3 F3 78 */	mr r3, r30
/* 800EB99C 000E857C  C0 62 99 10 */	lfs f3, ftLk_Init_804D92F0
/* 800EB9A0 000E8580  38 A4 50 80 */	addi r5, r4, 0x0C4C5080@l
/* 800EB9A4 000E8584  38 80 01 67 */	li r4, 0x167
/* 800EB9A8 000E8588  38 C0 00 00 */	li r6, 0
/* 800EB9AC 000E858C  4B F7 DA 01 */	bl Fighter_ChangeMotionState
/* 800EB9B0 000E8590  3C 60 80 0F */	lis r3, lbl_800EB7C8@ha
/* 800EB9B4 000E8594  38 03 B7 C8 */	addi r0, r3, lbl_800EB7C8@l
/* 800EB9B8 000E8598  90 1F 21 BC */	stw r0, 0x21bc(r31)
lbl_800EB9BC:
/* 800EB9BC 000E859C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800EB9C0 000E85A0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800EB9C4 000E85A4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800EB9C8 000E85A8  38 21 00 18 */	addi r1, r1, 0x18
/* 800EB9CC 000E85AC  7C 08 03 A6 */	mtlr r0
/* 800EB9D0 000E85B0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftLk_SpecialAirLw_Coll(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 800EB9D4 000E85B4  7C 08 02 A6 */	mflr r0
/* 800EB9D8 000E85B8  90 01 00 04 */	stw r0, 4(r1)
/* 800EB9DC 000E85BC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800EB9E0 000E85C0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800EB9E4 000E85C4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800EB9E8 000E85C8  7C 7E 1B 78 */	mr r30, r3
/* 800EB9EC 000E85CC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800EB9F0 000E85D0  4B F9 63 1D */	bl ft_80081D0C
/* 800EB9F4 000E85D4  2C 03 00 00 */	cmpwi r3, 0
/* 800EB9F8 000E85D8  41 82 00 3C */	beq lbl_800EBA34
/* 800EB9FC 000E85DC  7F E3 FB 78 */	mr r3, r31
/* 800EBA00 000E85E0  4B F9 1D FD */	bl ftCommon_8007D7FC
/* 800EBA04 000E85E4  3C 80 0C 4C */	lis r4, 0x0C4C5080@ha
/* 800EBA08 000E85E8  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800EBA0C 000E85EC  C0 42 99 14 */	lfs f2, ftLk_Init_804D92F4
/* 800EBA10 000E85F0  7F C3 F3 78 */	mr r3, r30
/* 800EBA14 000E85F4  C0 62 99 10 */	lfs f3, ftLk_Init_804D92F0
/* 800EBA18 000E85F8  38 A4 50 80 */	addi r5, r4, 0x0C4C5080@l
/* 800EBA1C 000E85FC  38 80 01 66 */	li r4, 0x166
/* 800EBA20 000E8600  38 C0 00 00 */	li r6, 0
/* 800EBA24 000E8604  4B F7 D9 89 */	bl Fighter_ChangeMotionState
/* 800EBA28 000E8608  3C 60 80 0F */	lis r3, lbl_800EB7C8@ha
/* 800EBA2C 000E860C  38 03 B7 C8 */	addi r0, r3, lbl_800EB7C8@l
/* 800EBA30 000E8610  90 1F 21 BC */	stw r0, 0x21bc(r31)
lbl_800EBA34:
/* 800EBA34 000E8614  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800EBA38 000E8618  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800EBA3C 000E861C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800EBA40 000E8620  38 21 00 18 */	addi r1, r1, 0x18
/* 800EBA44 000E8624  7C 08 03 A6 */	mtlr r0
/* 800EBA48 000E8628  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
