/** @file
 * @todo Rename to @c ftUnk1.c
 */
#include <placeholder.h>
#include <melee/ef/efsync.h>
#include <melee/ft/code_8007C630.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftlib.h>
#include <melee/it/item.h>
#include <melee/it/item2.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/text_2.h>
#include <Runtime/platform.h>

#ifdef MWERKS_GEKKO

static f32 const lbl_804D8328 = 0.0F;
static f32 const lbl_804D832C = 1.0F;

extern unk_t func_8016B0B4(void);

#pragma push
asm void func_8007C630(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8007C630 00079210  7C 08 02 A6 */	mflr r0
/* 8007C634 00079214  90 01 00 04 */	stw r0, 4(r1)
/* 8007C638 00079218  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007C63C 0007921C  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8007C640 00079220  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8007C644 00079224  3B 80 00 00 */	li r28, 0
/* 8007C648 00079228  3B E0 00 00 */	li r31, 0
/* 8007C64C 0007922C  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8007C650 00079230  C3 E2 89 48 */	lfs f31, lbl_804D8328(r2)
/* 8007C654 00079234  3B DD 00 00 */	addi r30, r29, 0
lbl_8007C658:
/* 8007C658 00079238  80 9D 01 0C */	lwz r4, 0x10c(r29)
/* 8007C65C 0007923C  3B 7E 16 14 */	addi r27, r30, 0x1614
/* 8007C660 00079240  80 7D 05 E8 */	lwz r3, 0x5e8(r29)
/* 8007C664 00079244  38 BB 00 08 */	addi r5, r27, 8
/* 8007C668 00079248  80 04 00 38 */	lwz r0, 0x38(r4)
/* 8007C66C 0007924C  7C C0 FA 14 */	add r6, r0, r31
/* 8007C670 00079250  80 06 00 00 */	lwz r0, 0(r6)
/* 8007C674 00079254  38 86 00 04 */	addi r4, r6, 4
/* 8007C678 00079258  54 00 20 36 */	slwi r0, r0, 4
/* 8007C67C 0007925C  7C 03 00 2E */	lwzx r0, r3, r0
/* 8007C680 00079260  90 1E 16 18 */	stw r0, 0x1618(r30)
/* 8007C684 00079264  C0 06 00 10 */	lfs f0, 0x10(r6)
/* 8007C688 00079268  D0 1E 16 14 */	stfs f0, 0x1614(r30)
/* 8007C68C 0007926C  80 7E 16 18 */	lwz r3, 0x1618(r30)
/* 8007C690 00079270  4B F8 EB 3D */	bl func_8000B1CC
/* 8007C694 00079274  D3 FB 00 10 */	stfs f31, 0x10(r27)
/* 8007C698 00079278  3B 9C 00 01 */	addi r28, r28, 1
/* 8007C69C 0007927C  2C 1C 00 02 */	cmpwi r28, 2
/* 8007C6A0 00079280  80 7B 00 08 */	lwz r3, 8(r27)
/* 8007C6A4 00079284  3B FF 00 14 */	addi r31, r31, 0x14
/* 8007C6A8 00079288  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 8007C6AC 0007928C  3B DE 00 2C */	addi r30, r30, 0x2c
/* 8007C6B0 00079290  90 7B 00 14 */	stw r3, 0x14(r27)
/* 8007C6B4 00079294  90 1B 00 18 */	stw r0, 0x18(r27)
/* 8007C6B8 00079298  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8007C6BC 0007929C  90 1B 00 1C */	stw r0, 0x1c(r27)
/* 8007C6C0 000792A0  41 80 FF 98 */	blt lbl_8007C658
/* 8007C6C4 000792A4  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8007C6C8 000792A8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8007C6CC 000792AC  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8007C6D0 000792B0  38 21 00 30 */	addi r1, r1, 0x30
/* 8007C6D4 000792B4  7C 08 03 A6 */	mtlr r0
/* 8007C6D8 000792B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void func_8007C630(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void func_8007C6DC(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8007C6DC 000792BC  7C 08 02 A6 */	mflr r0
/* 8007C6E0 000792C0  90 01 00 04 */	stw r0, 4(r1)
/* 8007C6E4 000792C4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007C6E8 000792C8  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8007C6EC 000792CC  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8007C6F0 000792D0  7C 7B 1B 78 */	mr r27, r3
/* 8007C6F4 000792D4  48 0E E9 C1 */	bl func_8016B0B4
/* 8007C6F8 000792D8  2C 03 00 00 */	cmpwi r3, 0
/* 8007C6FC 000792DC  41 82 00 68 */	beq lbl_8007C764
/* 8007C700 000792E0  83 BB 00 2C */	lwz r29, 0x2c(r27)
/* 8007C704 000792E4  3B 80 00 00 */	li r28, 0
/* 8007C708 000792E8  C3 E2 89 48 */	lfs f31, lbl_804D8328(r2)
/* 8007C70C 000792EC  3B E0 00 00 */	li r31, 0
/* 8007C710 000792F0  3B DD 00 00 */	addi r30, r29, 0
lbl_8007C714:
/* 8007C714 000792F4  80 9D 01 0C */	lwz r4, 0x10c(r29)
/* 8007C718 000792F8  3B 7E 16 14 */	addi r27, r30, 0x1614
/* 8007C71C 000792FC  80 7E 16 1C */	lwz r3, 0x161c(r30)
/* 8007C720 00079300  38 BB 00 08 */	addi r5, r27, 8
/* 8007C724 00079304  80 84 00 38 */	lwz r4, 0x38(r4)
/* 8007C728 00079308  80 1E 16 20 */	lwz r0, 0x1620(r30)
/* 8007C72C 0007930C  7C 84 FA 14 */	add r4, r4, r31
/* 8007C730 00079310  90 7E 16 28 */	stw r3, 0x1628(r30)
/* 8007C734 00079314  38 84 00 04 */	addi r4, r4, 4
/* 8007C738 00079318  90 1E 16 2C */	stw r0, 0x162c(r30)
/* 8007C73C 0007931C  80 1E 16 24 */	lwz r0, 0x1624(r30)
/* 8007C740 00079320  90 1E 16 30 */	stw r0, 0x1630(r30)
/* 8007C744 00079324  80 7E 16 18 */	lwz r3, 0x1618(r30)
/* 8007C748 00079328  4B F8 EA 85 */	bl func_8000B1CC
/* 8007C74C 0007932C  3B 9C 00 01 */	addi r28, r28, 1
/* 8007C750 00079330  D3 FB 00 10 */	stfs f31, 0x10(r27)
/* 8007C754 00079334  2C 1C 00 02 */	cmpwi r28, 2
/* 8007C758 00079338  3B FF 00 14 */	addi r31, r31, 0x14
/* 8007C75C 0007933C  3B DE 00 2C */	addi r30, r30, 0x2c
/* 8007C760 00079340  41 80 FF B4 */	blt lbl_8007C714
lbl_8007C764:
/* 8007C764 00079344  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8007C768 00079348  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8007C76C 0007934C  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8007C770 00079350  38 21 00 30 */	addi r1, r1, 0x30
/* 8007C774 00079354  7C 08 03 A6 */	mtlr r0
/* 8007C778 00079358  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void func_8007C6DC(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

extern unk_t func_80023870();
extern unk_t func_802E5EF4();

#pragma push
asm void func_8007C77C(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8007C77C 0007935C  7C 08 02 A6 */	mflr r0
/* 8007C780 00079360  90 01 00 04 */	stw r0, 4(r1)
/* 8007C784 00079364  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8007C788 00079368  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 8007C78C 0007936C  BF 21 00 2C */	stmw r25, 0x2c(r1)
/* 8007C790 00079370  7C 7E 1B 78 */	mr r30, r3
/* 8007C794 00079374  48 0E E9 21 */	bl func_8016B0B4
/* 8007C798 00079378  2C 03 00 00 */	cmpwi r3, 0
/* 8007C79C 0007937C  41 82 01 7C */	beq lbl_8007C918
/* 8007C7A0 00079380  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8007C7A4 00079384  48 12 84 15 */	bl func_801A4BB8
/* 8007C7A8 00079388  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 8007C7AC 0007938C  54 63 07 FE */	clrlwi r3, r3, 0x1f
/* 8007C7B0 00079390  54 00 07 FE */	clrlwi r0, r0, 0x1f
/* 8007C7B4 00079394  7C 03 00 40 */	cmplw r3, r0
/* 8007C7B8 00079398  40 82 00 0C */	bne lbl_8007C7C4
/* 8007C7BC 0007939C  38 00 00 00 */	li r0, 0
/* 8007C7C0 000793A0  48 00 00 08 */	b lbl_8007C7C8
lbl_8007C7C4:
/* 8007C7C4 000793A4  38 00 00 01 */	li r0, 1
lbl_8007C7C8:
/* 8007C7C8 000793A8  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 8007C7CC 000793AC  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 8007C7D0 000793B0  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8007C7D4 000793B4  98 1F 22 29 */	stb r0, 0x2229(r31)
/* 8007C7D8 000793B8  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 8007C7DC 000793BC  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007C7E0 000793C0  40 82 01 38 */	bne lbl_8007C918
/* 8007C7E4 000793C4  7F C3 F3 78 */	mr r3, r30
/* 8007C7E8 000793C8  4B FF F0 81 */	bl func_8007B868
/* 8007C7EC 000793CC  2C 03 00 02 */	cmpwi r3, 2
/* 8007C7F0 000793D0  41 82 01 28 */	beq lbl_8007C918
/* 8007C7F4 000793D4  80 6D C1 8C */	lwz r3, lbl_804D782C(r13)
/* 8007C7F8 000793D8  C3 E2 89 4C */	lfs f31, lbl_804D832C(r2)
/* 8007C7FC 000793DC  80 63 00 24 */	lwz r3, 0x24(r3)
/* 8007C800 000793E0  48 00 01 10 */	b lbl_8007C910
lbl_8007C804:
/* 8007C804 000793E4  83 63 00 2C */	lwz r27, 0x2c(r3)
/* 8007C808 000793E8  83 83 00 08 */	lwz r28, 8(r3)
/* 8007C80C 000793EC  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8007C810 000793F0  2C 00 00 9E */	cmpwi r0, 0x9e
/* 8007C814 000793F4  40 82 00 F8 */	bne lbl_8007C90C
/* 8007C818 000793F8  80 9B 05 18 */	lwz r4, 0x518(r27)
/* 8007C81C 000793FC  38 7E 00 00 */	addi r3, r30, 0
/* 8007C820 00079400  3B A0 00 00 */	li r29, 0
/* 8007C824 00079404  48 00 A7 B1 */	bl func_80086FD4
/* 8007C828 00079408  2C 03 00 00 */	cmpwi r3, 0
/* 8007C82C 0007940C  41 82 00 18 */	beq lbl_8007C844
/* 8007C830 00079410  88 1B 0D EC */	lbz r0, 0xdec(r27)
/* 8007C834 00079414  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8007C838 00079418  41 82 00 1C */	beq lbl_8007C854
/* 8007C83C 0007941C  3B A0 00 01 */	li r29, 1
/* 8007C840 00079420  48 00 00 14 */	b lbl_8007C854
lbl_8007C844:
/* 8007C844 00079424  88 1B 0D EC */	lbz r0, 0xdec(r27)
/* 8007C848 00079428  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8007C84C 0007942C  41 82 00 08 */	beq lbl_8007C854
/* 8007C850 00079430  3B A0 00 01 */	li r29, 1
lbl_8007C854:
/* 8007C854 00079434  2C 1D 00 00 */	cmpwi r29, 0
/* 8007C858 00079438  41 82 00 B4 */	beq lbl_8007C90C
/* 8007C85C 0007943C  3B BF 00 00 */	addi r29, r31, 0
/* 8007C860 00079440  3B 5B 0D F0 */	addi r26, r27, 0xdf0
/* 8007C864 00079444  3B 20 00 00 */	li r25, 0
lbl_8007C868:
/* 8007C868 00079448  C0 3B 00 38 */	lfs f1, 0x38(r27)
/* 8007C86C 0007944C  38 9D 16 14 */	addi r4, r29, 0x1614
/* 8007C870 00079450  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8007C874 00079454  7F 43 D3 78 */	mr r3, r26
/* 8007C878 00079458  4B F8 B3 01 */	bl lbColl_80007B78
/* 8007C87C 0007945C  2C 03 00 00 */	cmpwi r3, 0
/* 8007C880 00079460  41 82 00 7C */	beq lbl_8007C8FC
/* 8007C884 00079464  80 7B 00 04 */	lwz r3, 4(r27)
/* 8007C888 00079468  48 26 96 6D */	bl func_802E5EF4
/* 8007C88C 0007946C  7C 7D 1B 78 */	mr r29, r3
/* 8007C890 00079470  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8007C894 00079474  4B FB 74 CD */	bl Player_GetCoins
/* 8007C898 00079478  7C 60 1B 78 */	mr r0, r3
/* 8007C89C 0007947C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8007C8A0 00079480  7C 9D 02 14 */	add r4, r29, r0
/* 8007C8A4 00079484  4B FB 75 2D */	bl Player_SetCoins
/* 8007C8A8 00079488  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8007C8AC 0007948C  4B FB 75 A1 */	bl Player_GetTotalCoins
/* 8007C8B0 00079490  7C 60 1B 78 */	mr r0, r3
/* 8007C8B4 00079494  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8007C8B8 00079498  7C 9D 02 14 */	add r4, r29, r0
/* 8007C8BC 0007949C  4B FB 76 01 */	bl Player_SetTotalCoins
/* 8007C8C0 000794A0  38 60 00 93 */	li r3, 0x93
/* 8007C8C4 000794A4  38 80 00 7F */	li r4, 0x7f
/* 8007C8C8 000794A8  38 A0 00 40 */	li r5, 0x40
/* 8007C8CC 000794AC  38 C0 00 1A */	li r6, 0x1a
/* 8007C8D0 000794B0  4B FA 6F A1 */	bl func_80023870
/* 8007C8D4 000794B4  D3 E1 00 18 */	stfs f31, 0x18(r1)
/* 8007C8D8 000794B8  38 BA 00 20 */	addi r5, r26, 0x20
/* 8007C8DC 000794BC  38 C1 00 18 */	addi r6, r1, 0x18
/* 8007C8E0 000794C0  4C C6 31 82 */	crclr 6
/* 8007C8E4 000794C4  38 60 04 32 */	li r3, 0x432
/* 8007C8E8 000794C8  38 80 00 00 */	li r4, 0
/* 8007C8EC 000794CC  4B FE 34 F1 */	bl ef_Spawn
/* 8007C8F0 000794D0  80 7B 00 04 */	lwz r3, 4(r27)
/* 8007C8F4 000794D4  48 1E DF F9 */	bl func_8026A8EC
/* 8007C8F8 000794D8  48 00 00 14 */	b lbl_8007C90C
lbl_8007C8FC:
/* 8007C8FC 000794DC  3B 39 00 01 */	addi r25, r25, 1
/* 8007C900 000794E0  2C 19 00 02 */	cmpwi r25, 2
/* 8007C904 000794E4  3B BD 00 2C */	addi r29, r29, 0x2c
/* 8007C908 000794E8  41 80 FF 60 */	blt lbl_8007C868
lbl_8007C90C:
/* 8007C90C 000794EC  7F 83 E3 78 */	mr r3, r28
lbl_8007C910:
/* 8007C910 000794F0  28 03 00 00 */	cmplwi r3, 0
/* 8007C914 000794F4  40 82 FE F0 */	bne lbl_8007C804
lbl_8007C918:
/* 8007C918 000794F8  BB 21 00 2C */	lmw r25, 0x2c(r1)
/* 8007C91C 000794FC  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8007C920 00079500  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 8007C924 00079504  38 21 00 50 */	addi r1, r1, 0x50
/* 8007C928 00079508  7C 08 03 A6 */	mtlr r0
/* 8007C92C 0007950C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void func_8007C77C(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

#endif
