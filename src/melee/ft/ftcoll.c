#include <melee/ft/ftcoll.h>

#include <common_structs.h>
#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>
#include <math.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/gr/stage.h>
#include <melee/it/code_80266F3C.h>
#include <melee/it/item.h>
#include <melee/pl/pl_unknown_001.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

// 0x800763C0 //
// https://decomp.me/scratch/zSqbD //
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim,
                   s32 attackID) // Combo Count Logic //
{
    HSD_GObj* temp_GObj;
    Fighter* fp;

    if (attacker != victim) {
        fp = getFighter(attacker);
        temp_GObj = fp->x2094;
        if (temp_GObj == NULL) {
            fp->x208C = attackID;
            fp->x2090 = 1U;
            fp->x2094 = victim;
            return;
        }
        if (temp_GObj == victim) {
            if ((attackID != 1) && ((s32) fp->x208C == attackID)) {
                fp->x2090 = (u16) (fp->x2090 + 1);
                if (fp->x2090 >= p_ftCommonData->x4C4) {
                    fp->x2092 = p_ftCommonData->x4D8;
                }
            } else {
                fp->x2090 = 0U;
                fp->x208C = attackID;
            }
        }
    }
}

// 0x80076444 //
// https://decomp.me/scratch/PJyPr //
void func_80076444(HSD_GObj* attacker,
                   HSD_GObj* victim) // Combo Count Logic + Get Attack ID //
{
    Fighter* fp = getFighter(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

extern bool func_80086960(HSD_GObj*);

// 0x8007646C //
// https://decomp.me/scratch/TDdx4 //
void func_8007646C(HSD_GObj* attackItem,
                   HSD_GObj* victim) // Combo Count Logic w/ Item Owner //
{
    HSD_GObj* itemOwner = func_8026BC78(attackItem);
    s32 attackID = func_8026BC84(attackItem);

    if (func_80086960(itemOwner) != false) // Check if item's owner is a fp //
    {
        func_800763C0(itemOwner, victim, attackID);
    }
}

// 0x800764DC //
// https://decomp.me/scratch/pOUFp //
void func_800764DC(HSD_GObj* fighter_gobj) // Check to end combo for victim //
{
    u16 hitstunTimer; // Hitstun timer, presumably? //
    HSD_GObj* temp_gobj;
    Fighter* temp_fp;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    hitstunTimer = fp->x2098;
    if (hitstunTimer != 0) {
        fp->x2098 = (u16) (hitstunTimer - 1);
    }
    temp_gobj = fp->x2094;
    if (temp_gobj != NULL) {
        temp_fp = getFighter(temp_gobj);
        if ((temp_fp->x221C_flag.bits.b6 == 0) && ((u16) temp_fp->x2098 == 0)) {
            fp->x2094 = NULL;
        }
    }
}

inline void comboCount_Push(Fighter* fp)
{
    Vec3* pos = &fp->x6F0_collData.x14C_ground.normal;
    f32 temp_f2;
    f32 var_f2;
    if ((s32) fp->x2090 < (s32) p_ftCommonData->x4C8) {
        var_f2 = p_ftCommonData->x4D0;
    } else {
        var_f2 = p_ftCommonData->x4D4;
    }
    temp_f2 = fp->facing_dir * var_f2;
    fp->xB0_pos.x = -((pos->y * temp_f2) - fp->xB0_pos.x);
    fp->xB0_pos.y = -((-pos->x * temp_f2) - fp->xB0_pos.y);
}

// 0x80076528 //
// https://decomp.me/scratch/qGiYU //
void func_80076528(
    HSD_GObj* fighter_gobj) // Combo count something + adjust TopN //
{
    u16 temp_r3;
    Fighter* fp;

    fp = fighter_gobj->user_data;
    temp_r3 = fp->x2092;
    if (temp_r3 != 0) {
        fp->x2092 = (u16) (temp_r3 - 1);
        if ((fp->x1A58_interactedFighter == NULL) &&
            (fp->xE0_ground_or_air == GA_Ground))
        {
            comboCount_Push(fp);
        }
    }
}

// 0x800765AC //
// https://decomp.me/scratch/IPBrx //
void func_800765AC(HSD_GObj* victim) // Clear victim pointer from attacker upon
                                     // freeing memory? //
{
    Fighter* fp;
    HSD_GObj* gobj;

    gobj =
        lbl_804D782C
            ->x20_fighters; // Get fp GObj from global list of entities (?) //
    while (gobj != NULL) {
        fp = getFighter(gobj);
        if (victim == fp->x2094) {
            fp->x2094 = NULL;
        }
        gobj = gobj->next; // Repeat until there are no more fp GObjs left //
    }
}

extern s32 lbl_804D6558;
extern s32 lbl_804D655C;

// 0x800765E0 //
// https://decomp.me/scratch/F1xnr
void func_800765E0(void) // Reset hitbox and phantom collision count? //
{
    lbl_804D6558 = 0;
    lbl_804D655C = 0;
}

// 0x800765F0 //
// https://decomp.me/scratch/9hcKb //
f32 func_800765F0(Fighter* fp, HSD_GObj* victim,
                  f32 unk_floatvar) // Unk knockback related ? //
{
    HSD_GObj* currentVictim;

    currentVictim = fp->x1A58_interactedFighter;
    if ((currentVictim != NULL) && (fp->x221B_flag.bits.b5 == 0) &&
        (currentVictim != victim))
    {
        unk_floatvar *= p_ftCommonData->x128;
    }
    if (fp->x10_action_state_index == ASID_DAMAGEICE) {
        unk_floatvar *= p_ftCommonData->x714;
    }
    return unk_floatvar * fp->dmg.x182c_behavior;
}

extern f32 const lbl_804D82E0;
extern f32 const lbl_804D82E4;
extern char* const lbl_803C0C58;
extern char* const lbl_803C0C74;
extern char* const lbl_804D3A68;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076640(void)
{ // clang-format off
    nofralloc
/* 80076640 00073220  7C 08 02 A6 */	mflr r0
/* 80076644 00073224  90 01 00 04 */	stw r0, 4(r1)
/* 80076648 00073228  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007664C 0007322C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80076650 00073230  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80076654 00073234  7C 9E 23 78 */	mr r30, r4
/* 80076658 00073238  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8007665C 0007323C  7C 7D 1B 78 */	mr r29, r3
/* 80076660 00073240  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076664 00073244  C0 24 00 00 */	lfs f1, 0(r4)
/* 80076668 00073248  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8007666C 0007324C  41 82 00 2C */	beq lbl_80076698
/* 80076670 00073250  FC 00 08 1E */	fctiwz f0, f1
/* 80076674 00073254  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80076678 00073258  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007667C 0007325C  2C 00 00 00 */	cmpwi r0, 0
/* 80076680 00073260  41 82 00 10 */	beq lbl_80076690
/* 80076684 00073264  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80076688 00073268  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007668C 0007326C  48 00 00 10 */	b lbl_8007669C
lbl_80076690:
/* 80076690 00073270  3B E0 00 01 */	li r31, 1
/* 80076694 00073274  48 00 00 08 */	b lbl_8007669C
lbl_80076698:
/* 80076698 00073278  3B E0 00 00 */	li r31, 0
lbl_8007669C:
/* 8007669C 0007327C  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 800766A0 00073280  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800766A4 00073284  41 82 00 38 */	beq lbl_800766DC
/* 800766A8 00073288  C0 1D 18 34 */	lfs f0, 0x1834(r29)
/* 800766AC 0007328C  EC 00 08 28 */	fsubs f0, f0, f1
/* 800766B0 00073290  D0 1D 18 34 */	stfs f0, 0x1834(r29)
/* 800766B4 00073294  C0 3D 18 34 */	lfs f1, 0x1834(r29)
/* 800766B8 00073298  C0 02 89 00 */	lfs f0, lbl_804D82E0(r2)
/* 800766BC 0007329C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800766C0 000732A0  40 80 00 1C */	bge lbl_800766DC
/* 800766C4 000732A4  FC 00 08 50 */	fneg f0, f1
/* 800766C8 000732A8  38 60 00 00 */	li r3, 0
/* 800766CC 000732AC  D0 1E 00 00 */	stfs f0, 0(r30)
/* 800766D0 000732B0  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 800766D4 000732B4  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800766D8 000732B8  98 1D 22 1C */	stb r0, 0x221c(r29)
lbl_800766DC:
/* 800766DC 000732BC  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 800766E0 000732C0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800766E4 000732C4  40 82 00 60 */	bne lbl_80076744
/* 800766E8 000732C8  C0 3E 00 00 */	lfs f1, 0(r30)
/* 800766EC 000732CC  C0 02 89 04 */	lfs f0, lbl_804D82E4(r2)
/* 800766F0 000732D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800766F4 000732D4  40 81 00 28 */	ble lbl_8007671C
/* 800766F8 000732D8  3C 60 80 3C */	lis r3, lbl_803C0C58@ha
/* 800766FC 000732DC  4C C6 32 42 */	crset 6
/* 80076700 000732E0  38 63 0C 58 */	addi r3, r3, lbl_803C0C58@l
/* 80076704 000732E4  48 2C EF A5 */	bl OSReport
/* 80076708 000732E8  3C 60 80 3C */	lis r3, lbl_803C0C74@ha
/* 8007670C 000732EC  38 63 0C 74 */	addi r3, r3, lbl_803C0C74@l
/* 80076710 000732F0  38 80 00 B7 */	li r4, 0xb7
/* 80076714 000732F4  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 80076718 000732F8  48 31 1B 09 */	bl __assert
lbl_8007671C:
/* 8007671C 000732FC  C0 3D 18 38 */	lfs f1, 0x1838(r29)
/* 80076720 00073300  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80076724 00073304  EC 01 00 2A */	fadds f0, f1, f0
/* 80076728 00073308  D0 1D 18 38 */	stfs f0, 0x1838(r29)
/* 8007672C 0007330C  80 1D 18 3C */	lwz r0, 0x183c(r29)
/* 80076730 00073310  7C 1F 00 00 */	cmpw r31, r0
/* 80076734 00073314  40 81 00 08 */	ble lbl_8007673C
/* 80076738 00073318  93 FD 18 3C */	stw r31, 0x183c(r29)
lbl_8007673C:
/* 8007673C 0007331C  38 60 00 01 */	li r3, 1
/* 80076740 00073320  48 00 00 08 */	b lbl_80076748
lbl_80076744:
/* 80076744 00073324  38 60 00 00 */	li r3, 0
lbl_80076748:
/* 80076748 00073328  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8007674C 0007332C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80076750 00073330  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80076754 00073334  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80076758 00073338  38 21 00 30 */	addi r1, r1, 0x30
/* 8007675C 0007333C  7C 08 03 A6 */	mtlr r0
/* 80076760 00073340  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_80459278;
extern char* const lbl_803C0C80;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076764(void)
{ // clang-format off
    nofralloc
/* 80076764 00073344  7C 08 02 A6 */	mflr r0
/* 80076768 00073348  90 01 00 04 */	stw r0, 4(r1)
/* 8007676C 0007334C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80076770 00073350  80 0D AE B8 */	lwz r0, lbl_804D6558(r13)
/* 80076774 00073354  28 00 00 14 */	cmplwi r0, 0x14
/* 80076778 00073358  40 80 00 58 */	bge lbl_800767D0
/* 8007677C 0007335C  1D 40 00 28 */	mulli r10, r0, 0x28
/* 80076780 00073360  3D 20 80 46 */	lis r9, lbl_80459278@ha
/* 80076784 00073364  38 09 92 78 */	addi r0, r9, lbl_80459278@l
/* 80076788 00073368  7D 20 52 14 */	add r9, r0, r10
/* 8007678C 0007336C  90 69 00 00 */	stw r3, 0(r9)
/* 80076790 00073370  90 89 00 04 */	stw r4, 4(r9)
/* 80076794 00073374  90 A9 00 08 */	stw r5, 8(r9)
/* 80076798 00073378  90 C9 00 0C */	stw r6, 0xc(r9)
/* 8007679C 0007337C  91 09 00 10 */	stw r8, 0x10(r9)
/* 800767A0 00073380  80 67 00 B0 */	lwz r3, 0xb0(r7)
/* 800767A4 00073384  80 07 00 B4 */	lwz r0, 0xb4(r7)
/* 800767A8 00073388  90 69 00 14 */	stw r3, 0x14(r9)
/* 800767AC 0007338C  90 09 00 18 */	stw r0, 0x18(r9)
/* 800767B0 00073390  80 07 00 B8 */	lwz r0, 0xb8(r7)
/* 800767B4 00073394  90 09 00 1C */	stw r0, 0x1c(r9)
/* 800767B8 00073398  80 06 00 04 */	lwz r0, 4(r6)
/* 800767BC 0007339C  90 09 00 24 */	stw r0, 0x24(r9)
/* 800767C0 000733A0  80 6D AE B8 */	lwz r3, lbl_804D6558(r13)
/* 800767C4 000733A4  38 03 00 01 */	addi r0, r3, 1
/* 800767C8 000733A8  90 0D AE B8 */	stw r0, lbl_804D6558(r13)
/* 800767CC 000733AC  48 00 00 2C */	b lbl_800767F8
lbl_800767D0:
/* 800767D0 000733B0  3C 60 80 3C */	lis r3, lbl_803C0C80@ha
/* 800767D4 000733B4  4C C6 31 82 */	crclr 6
/* 800767D8 000733B8  38 63 0C 80 */	addi r3, r3, lbl_803C0C80@l
/* 800767DC 000733BC  38 80 00 14 */	li r4, 0x14
/* 800767E0 000733C0  48 2C EE C9 */	bl OSReport
/* 800767E4 000733C4  3C 60 80 3C */	lis r3, lbl_803C0C74@ha
/* 800767E8 000733C8  38 63 0C 74 */	addi r3, r3, lbl_803C0C74@l
/* 800767EC 000733CC  38 80 00 F9 */	li r4, 0xf9
/* 800767F0 000733D0  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 800767F4 000733D4  48 31 1A 2D */	bl __assert
lbl_800767F8:
/* 800767F8 000733D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800767FC 000733DC  38 21 00 08 */	addi r1, r1, 8
/* 80076800 000733E0  7C 08 03 A6 */	mtlr r0
/* 80076804 000733E4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_804D6560;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076808(void)
{ // clang-format off
    nofralloc
/* 80076808 000733E8  7C 08 02 A6 */	mflr r0
/* 8007680C 000733EC  90 01 00 04 */	stw r0, 4(r1)
/* 80076810 000733F0  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80076814 000733F4  BF 01 00 20 */	stmw r24, 0x20(r1)
/* 80076818 000733F8  3B 04 00 00 */	addi r24, r4, 0
/* 8007681C 000733FC  3B 25 00 00 */	addi r25, r5, 0
/* 80076820 00073400  3B 46 00 00 */	addi r26, r6, 0
/* 80076824 00073404  3B 67 00 00 */	addi r27, r7, 0
/* 80076828 00073408  3B C3 00 00 */	addi r30, r3, 0
/* 8007682C 0007340C  3B 80 00 00 */	li r28, 0
/* 80076830 00073410  3B AD AE C0 */	addi r29, r13, lbl_804D6560
/* 80076834 00073414  3B E0 00 00 */	li r31, 0
lbl_80076838:
/* 80076838 00073418  80 1E 09 14 */	lwz r0, 0x914(r30)
/* 8007683C 0007341C  38 7E 09 14 */	addi r3, r30, 0x914
/* 80076840 00073420  2C 00 00 00 */	cmpwi r0, 0
/* 80076844 00073424  41 82 00 34 */	beq lbl_80076878
/* 80076848 00073428  80 83 00 04 */	lwz r4, 4(r3)
/* 8007684C 0007342C  80 18 00 04 */	lwz r0, 4(r24)
/* 80076850 00073430  7C 04 00 40 */	cmplw r4, r0
/* 80076854 00073434  40 82 00 24 */	bne lbl_80076878
/* 80076858 00073438  38 99 00 00 */	addi r4, r25, 0
/* 8007685C 0007343C  38 BA 00 00 */	addi r5, r26, 0
/* 80076860 00073440  4B F9 1E 29 */	bl func_80008688
/* 80076864 00073444  2C 03 00 00 */	cmpwi r3, 0
/* 80076868 00073448  41 82 00 10 */	beq lbl_80076878
/* 8007686C 0007344C  2C 1B 00 00 */	cmpwi r27, 0
/* 80076870 00073450  41 82 00 08 */	beq lbl_80076878
/* 80076874 00073454  9B FD 00 00 */	stb r31, 0(r29)
lbl_80076878:
/* 80076878 00073458  3B 9C 00 01 */	addi r28, r28, 1
/* 8007687C 0007345C  28 1C 00 04 */	cmplwi r28, 4
/* 80076880 00073460  3B DE 01 38 */	addi r30, r30, 0x138
/* 80076884 00073464  3B BD 00 01 */	addi r29, r29, 1
/* 80076888 00073468  41 80 FF B0 */	blt lbl_80076838
/* 8007688C 0007346C  BB 01 00 20 */	lmw r24, 0x20(r1)
/* 80076890 00073470  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076894 00073474  38 21 00 40 */	addi r1, r1, 0x40
/* 80076898 00073478  7C 08 03 A6 */	mtlr r0
/* 8007689C 0007347C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800768A0(void)
{ // clang-format off
    nofralloc
/* 800768A0 00073480  7C 08 02 A6 */	mflr r0
/* 800768A4 00073484  38 C3 09 14 */	addi r6, r3, 0x914
/* 800768A8 00073488  90 01 00 04 */	stw r0, 4(r1)
/* 800768AC 0007348C  7C 06 20 40 */	cmplw r6, r4
/* 800768B0 00073490  94 21 FF F8 */	stwu r1, -8(r1)
/* 800768B4 00073494  41 82 00 2C */	beq lbl_800768E0
/* 800768B8 00073498  80 06 00 00 */	lwz r0, 0(r6)
/* 800768BC 0007349C  2C 00 00 00 */	cmpwi r0, 0
/* 800768C0 000734A0  41 82 00 20 */	beq lbl_800768E0
/* 800768C4 000734A4  80 A6 00 04 */	lwz r5, 4(r6)
/* 800768C8 000734A8  80 04 00 04 */	lwz r0, 4(r4)
/* 800768CC 000734AC  7C 05 00 40 */	cmplw r5, r0
/* 800768D0 000734B0  40 82 00 10 */	bne lbl_800768E0
/* 800768D4 000734B4  7C C3 33 78 */	mr r3, r6
/* 800768D8 000734B8  4B F9 1C 25 */	bl func_800084FC
/* 800768DC 000734BC  48 00 00 B0 */	b lbl_8007698C
lbl_800768E0:
/* 800768E0 000734C0  38 63 01 38 */	addi r3, r3, 0x138
/* 800768E4 000734C4  38 C3 09 14 */	addi r6, r3, 0x914
/* 800768E8 000734C8  7C 06 20 40 */	cmplw r6, r4
/* 800768EC 000734CC  41 82 00 2C */	beq lbl_80076918
/* 800768F0 000734D0  80 06 00 00 */	lwz r0, 0(r6)
/* 800768F4 000734D4  2C 00 00 00 */	cmpwi r0, 0
/* 800768F8 000734D8  41 82 00 20 */	beq lbl_80076918
/* 800768FC 000734DC  80 A6 00 04 */	lwz r5, 4(r6)
/* 80076900 000734E0  80 04 00 04 */	lwz r0, 4(r4)
/* 80076904 000734E4  7C 05 00 40 */	cmplw r5, r0
/* 80076908 000734E8  40 82 00 10 */	bne lbl_80076918
/* 8007690C 000734EC  7C C3 33 78 */	mr r3, r6
/* 80076910 000734F0  4B F9 1B ED */	bl func_800084FC
/* 80076914 000734F4  48 00 00 78 */	b lbl_8007698C
lbl_80076918:
/* 80076918 000734F8  38 C3 0A 4C */	addi r6, r3, 0xa4c
/* 8007691C 000734FC  7C 06 20 40 */	cmplw r6, r4
/* 80076920 00073500  38 63 01 38 */	addi r3, r3, 0x138
/* 80076924 00073504  41 82 00 2C */	beq lbl_80076950
/* 80076928 00073508  80 06 00 00 */	lwz r0, 0(r6)
/* 8007692C 0007350C  2C 00 00 00 */	cmpwi r0, 0
/* 80076930 00073510  41 82 00 20 */	beq lbl_80076950
/* 80076934 00073514  80 A6 00 04 */	lwz r5, 4(r6)
/* 80076938 00073518  80 04 00 04 */	lwz r0, 4(r4)
/* 8007693C 0007351C  7C 05 00 40 */	cmplw r5, r0
/* 80076940 00073520  40 82 00 10 */	bne lbl_80076950
/* 80076944 00073524  7C C3 33 78 */	mr r3, r6
/* 80076948 00073528  4B F9 1B B5 */	bl func_800084FC
/* 8007694C 0007352C  48 00 00 40 */	b lbl_8007698C
lbl_80076950:
/* 80076950 00073530  38 C3 0A 4C */	addi r6, r3, 0xa4c
/* 80076954 00073534  7C 06 20 40 */	cmplw r6, r4
/* 80076958 00073538  41 82 00 2C */	beq lbl_80076984
/* 8007695C 0007353C  80 06 00 00 */	lwz r0, 0(r6)
/* 80076960 00073540  2C 00 00 00 */	cmpwi r0, 0
/* 80076964 00073544  41 82 00 20 */	beq lbl_80076984
/* 80076968 00073548  80 A6 00 04 */	lwz r5, 4(r6)
/* 8007696C 0007354C  80 04 00 04 */	lwz r0, 4(r4)
/* 80076970 00073550  7C 05 00 40 */	cmplw r5, r0
/* 80076974 00073554  40 82 00 10 */	bne lbl_80076984
/* 80076978 00073558  7C C3 33 78 */	mr r3, r6
/* 8007697C 0007355C  4B F9 1B 81 */	bl func_800084FC
/* 80076980 00073560  48 00 00 0C */	b lbl_8007698C
lbl_80076984:
/* 80076984 00073564  7C 83 23 78 */	mr r3, r4
/* 80076988 00073568  4B F9 1A B9 */	bl func_80008440
lbl_8007698C:
/* 8007698C 0007356C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80076990 00073570  38 21 00 08 */	addi r1, r1, 8
/* 80076994 00073574  7C 08 03 A6 */	mtlr r0
/* 80076998 00073578  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern f32 const lbl_804D82E8;
extern f32 const lbl_804D82EC;
extern f32 const lbl_804D82F0;
extern f64 const lbl_804D82F8;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007699C(void)
{ // clang-format off
    nofralloc
/* 8007699C 0007357C  7C 08 02 A6 */	mflr r0
/* 800769A0 00073580  90 01 00 04 */	stw r0, 4(r1)
/* 800769A4 00073584  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 800769A8 00073588  BE E1 00 54 */	stmw r23, 0x54(r1)
/* 800769AC 0007358C  7C 7C 1B 78 */	mr r28, r3
/* 800769B0 00073590  7C 9D 23 78 */	mr r29, r4
/* 800769B4 00073594  7C DF 33 78 */	mr r31, r6
/* 800769B8 00073598  7C BE 2B 78 */	mr r30, r5
/* 800769BC 0007359C  C0 24 00 64 */	lfs f1, 0x64(r4)
/* 800769C0 000735A0  C0 06 00 64 */	lfs f0, 0x64(r6)
/* 800769C4 000735A4  C0 42 89 08 */	lfs f2, lbl_804D82E8
/* 800769C8 000735A8  EC 01 00 2A */	fadds f0, f1, f0
/* 800769CC 000735AC  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800769D0 000735B0  EC 02 00 32 */	fmuls f0, f2, f0
/* 800769D4 000735B4  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800769D8 000735B8  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 800769DC 000735BC  C0 06 00 68 */	lfs f0, 0x68(r6)
/* 800769E0 000735C0  EC 01 00 2A */	fadds f0, f1, f0
/* 800769E4 000735C4  EC 02 00 32 */	fmuls f0, f2, f0
/* 800769E8 000735C8  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800769EC 000735CC  C0 24 00 6C */	lfs f1, 0x6c(r4)
/* 800769F0 000735D0  C0 06 00 6C */	lfs f0, 0x6c(r6)
/* 800769F4 000735D4  EC 01 00 2A */	fadds f0, f1, f0
/* 800769F8 000735D8  EC 02 00 32 */	fmuls f0, f2, f0
/* 800769FC 000735DC  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 80076A00 000735E0  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 80076A04 000735E4  C0 46 00 0C */	lfs f2, 0xc(r6)
/* 80076A08 000735E8  FC 00 00 1E */	fctiwz f0, f0
/* 80076A0C 000735EC  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 80076A10 000735F0  FC 20 10 1E */	fctiwz f1, f2
/* 80076A14 000735F4  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80076A18 000735F8  D8 21 00 48 */	stfd f1, 0x48(r1)
/* 80076A1C 000735FC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076A20 00073600  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 80076A24 00073604  7C 64 18 50 */	subf r3, r4, r3
/* 80076A28 00073608  7C 03 00 00 */	cmpw r3, r0
/* 80076A2C 0007360C  40 80 01 24 */	bge lbl_80076B50
/* 80076A30 00073610  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076A34 00073614  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 80076A38 00073618  41 82 00 28 */	beq lbl_80076A60
/* 80076A3C 0007361C  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076A40 00073620  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076A44 00073624  2C 00 00 00 */	cmpwi r0, 0
/* 80076A48 00073628  41 82 00 10 */	beq lbl_80076A58
/* 80076A4C 0007362C  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076A50 00073630  83 21 00 44 */	lwz r25, 0x44(r1)
/* 80076A54 00073634  48 00 00 10 */	b lbl_80076A64
lbl_80076A58:
/* 80076A58 00073638  3B 20 00 01 */	li r25, 1
/* 80076A5C 0007363C  48 00 00 08 */	b lbl_80076A64
lbl_80076A60:
/* 80076A60 00073640  3B 20 00 00 */	li r25, 0
lbl_80076A64:
/* 80076A64 00073644  3B 40 00 00 */	li r26, 0
/* 80076A68 00073648  3B 1E 00 00 */	addi r24, r30, 0
/* 80076A6C 0007364C  3B 7A 00 00 */	addi r27, r26, 0
/* 80076A70 00073650  3A ED AE C0 */	addi r23, r13, lbl_804D6560
lbl_80076A74:
/* 80076A74 00073654  80 18 09 14 */	lwz r0, 0x914(r24)
/* 80076A78 00073658  38 78 09 14 */	addi r3, r24, 0x914
/* 80076A7C 0007365C  2C 00 00 00 */	cmpwi r0, 0
/* 80076A80 00073660  41 82 00 2C */	beq lbl_80076AAC
/* 80076A84 00073664  80 83 00 04 */	lwz r4, 4(r3)
/* 80076A88 00073668  80 1F 00 04 */	lwz r0, 4(r31)
/* 80076A8C 0007366C  7C 04 00 40 */	cmplw r4, r0
/* 80076A90 00073670  40 82 00 1C */	bne lbl_80076AAC
/* 80076A94 00073674  38 BC 00 00 */	addi r5, r28, 0
/* 80076A98 00073678  38 80 00 03 */	li r4, 3
/* 80076A9C 0007367C  4B F9 1B ED */	bl func_80008688
/* 80076AA0 00073680  2C 03 00 00 */	cmpwi r3, 0
/* 80076AA4 00073684  41 82 00 08 */	beq lbl_80076AAC
/* 80076AA8 00073688  9B 77 00 00 */	stb r27, 0(r23)
lbl_80076AAC:
/* 80076AAC 0007368C  3B 5A 00 01 */	addi r26, r26, 1
/* 80076AB0 00073690  28 1A 00 04 */	cmplwi r26, 4
/* 80076AB4 00073694  3B 18 01 38 */	addi r24, r24, 0x138
/* 80076AB8 00073698  3A F7 00 01 */	addi r23, r23, 1
/* 80076ABC 0007369C  41 80 FF B8 */	blt lbl_80076A74
/* 80076AC0 000736A0  80 1E 19 18 */	lwz r0, 0x1918(r30)
/* 80076AC4 000736A4  7C 19 00 00 */	cmpw r25, r0
/* 80076AC8 000736A8  40 81 00 74 */	ble lbl_80076B3C
/* 80076ACC 000736AC  93 3E 19 18 */	stw r25, 0x1918(r30)
/* 80076AD0 000736B0  88 1F 00 40 */	lbz r0, 0x40(r31)
/* 80076AD4 000736B4  54 00 D7 FE */	rlwinm r0, r0, 0x1a, 0x1f, 0x1f
/* 80076AD8 000736B8  28 00 00 01 */	cmplwi r0, 1
/* 80076ADC 000736BC  40 82 00 60 */	bne lbl_80076B3C
/* 80076AE0 000736C0  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80076AE4 000736C4  2C 00 00 00 */	cmpwi r0, 0
/* 80076AE8 000736C8  40 82 00 54 */	bne lbl_80076B3C
/* 80076AEC 000736CC  6F 20 80 00 */	xoris r0, r25, 0x8000
/* 80076AF0 000736D0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076AF4 000736D4  90 01 00 44 */	stw r0, 0x44(r1)
/* 80076AF8 000736D8  3C 00 43 30 */	lis r0, 0x4330
/* 80076AFC 000736DC  C8 62 89 18 */	lfd f3, lbl_804D82F8
/* 80076B00 000736E0  90 01 00 40 */	stw r0, 0x40(r1)
/* 80076B04 000736E4  C0 23 03 D0 */	lfs f1, 0x3d0(r3)
/* 80076B08 000736E8  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 80076B0C 000736EC  C0 03 03 D4 */	lfs f0, 0x3d4(r3)
/* 80076B10 000736F0  EC 42 18 28 */	fsubs f2, f2, f3
/* 80076B14 000736F4  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80076B18 000736F8  D0 1E 19 1C */	stfs f0, 0x191c(r30)
/* 80076B1C 000736FC  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 80076B20 00073700  C0 1C 00 B0 */	lfs f0, 0xb0(r28)
/* 80076B24 00073704  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076B28 00073708  40 80 00 0C */	bge lbl_80076B34
/* 80076B2C 0007370C  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80076B30 00073710  48 00 00 08 */	b lbl_80076B38
lbl_80076B34:
/* 80076B34 00073714  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_80076B38:
/* 80076B38 00073718  D0 1E 19 20 */	stfs f0, 0x1920(r30)
lbl_80076B3C:
/* 80076B3C 0007371C  38 A1 00 30 */	addi r5, r1, 0x30
/* 80076B40 00073720  4C C6 31 82 */	crclr 6
/* 80076B44 00073724  38 60 04 1C */	li r3, 0x41c
/* 80076B48 00073728  38 80 00 00 */	li r4, 0
/* 80076B4C 0007372C  4B FE 92 91 */	bl ef_Spawn
lbl_80076B50:
/* 80076B50 00073730  C0 5D 00 0C */	lfs f2, 0xc(r29)
/* 80076B54 00073734  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 80076B58 00073738  FC 20 10 1E */	fctiwz f1, f2
/* 80076B5C 0007373C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076B60 00073740  FC 00 00 1E */	fctiwz f0, f0
/* 80076B64 00073744  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 80076B68 00073748  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076B6C 0007374C  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80076B70 00073750  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80076B74 00073754  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80076B78 00073758  7C 64 18 50 */	subf r3, r4, r3
/* 80076B7C 0007375C  7C 03 00 00 */	cmpw r3, r0
/* 80076B80 00073760  40 80 01 24 */	bge lbl_80076CA4
/* 80076B84 00073764  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076B88 00073768  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 80076B8C 0007376C  41 82 00 28 */	beq lbl_80076BB4
/* 80076B90 00073770  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076B94 00073774  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076B98 00073778  2C 00 00 00 */	cmpwi r0, 0
/* 80076B9C 0007377C  41 82 00 10 */	beq lbl_80076BAC
/* 80076BA0 00073780  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076BA4 00073784  83 21 00 44 */	lwz r25, 0x44(r1)
/* 80076BA8 00073788  48 00 00 10 */	b lbl_80076BB8
lbl_80076BAC:
/* 80076BAC 0007378C  3B 20 00 01 */	li r25, 1
/* 80076BB0 00073790  48 00 00 08 */	b lbl_80076BB8
lbl_80076BB4:
/* 80076BB4 00073794  3B 20 00 00 */	li r25, 0
lbl_80076BB8:
/* 80076BB8 00073798  3B 40 00 00 */	li r26, 0
/* 80076BBC 0007379C  3A FC 00 00 */	addi r23, r28, 0
lbl_80076BC0:
/* 80076BC0 000737A0  80 17 09 14 */	lwz r0, 0x914(r23)
/* 80076BC4 000737A4  38 77 09 14 */	addi r3, r23, 0x914
/* 80076BC8 000737A8  2C 00 00 00 */	cmpwi r0, 0
/* 80076BCC 000737AC  41 82 00 20 */	beq lbl_80076BEC
/* 80076BD0 000737B0  80 83 00 04 */	lwz r4, 4(r3)
/* 80076BD4 000737B4  80 1D 00 04 */	lwz r0, 4(r29)
/* 80076BD8 000737B8  7C 04 00 40 */	cmplw r4, r0
/* 80076BDC 000737BC  40 82 00 10 */	bne lbl_80076BEC
/* 80076BE0 000737C0  38 BE 00 00 */	addi r5, r30, 0
/* 80076BE4 000737C4  38 80 00 03 */	li r4, 3
/* 80076BE8 000737C8  4B F9 1A A1 */	bl func_80008688
lbl_80076BEC:
/* 80076BEC 000737CC  3B 5A 00 01 */	addi r26, r26, 1
/* 80076BF0 000737D0  28 1A 00 04 */	cmplwi r26, 4
/* 80076BF4 000737D4  3A F7 01 38 */	addi r23, r23, 0x138
/* 80076BF8 000737D8  41 80 FF C8 */	blt lbl_80076BC0
/* 80076BFC 000737DC  80 1C 19 18 */	lwz r0, 0x1918(r28)
/* 80076C00 000737E0  7C 19 00 00 */	cmpw r25, r0
/* 80076C04 000737E4  40 81 00 74 */	ble lbl_80076C78
/* 80076C08 000737E8  93 3C 19 18 */	stw r25, 0x1918(r28)
/* 80076C0C 000737EC  88 1D 00 40 */	lbz r0, 0x40(r29)
/* 80076C10 000737F0  54 00 D7 FE */	rlwinm r0, r0, 0x1a, 0x1f, 0x1f
/* 80076C14 000737F4  28 00 00 01 */	cmplwi r0, 1
/* 80076C18 000737F8  40 82 00 60 */	bne lbl_80076C78
/* 80076C1C 000737FC  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80076C20 00073800  2C 00 00 00 */	cmpwi r0, 0
/* 80076C24 00073804  40 82 00 54 */	bne lbl_80076C78
/* 80076C28 00073808  6F 20 80 00 */	xoris r0, r25, 0x8000
/* 80076C2C 0007380C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076C30 00073810  90 01 00 44 */	stw r0, 0x44(r1)
/* 80076C34 00073814  3C 00 43 30 */	lis r0, 0x4330
/* 80076C38 00073818  C8 62 89 18 */	lfd f3, lbl_804D82F8
/* 80076C3C 0007381C  90 01 00 40 */	stw r0, 0x40(r1)
/* 80076C40 00073820  C0 23 03 D0 */	lfs f1, 0x3d0(r3)
/* 80076C44 00073824  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 80076C48 00073828  C0 03 03 D4 */	lfs f0, 0x3d4(r3)
/* 80076C4C 0007382C  EC 42 18 28 */	fsubs f2, f2, f3
/* 80076C50 00073830  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80076C54 00073834  D0 1C 19 1C */	stfs f0, 0x191c(r28)
/* 80076C58 00073838  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 80076C5C 0007383C  C0 1C 00 B0 */	lfs f0, 0xb0(r28)
/* 80076C60 00073840  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076C64 00073844  40 81 00 0C */	ble lbl_80076C70
/* 80076C68 00073848  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80076C6C 0007384C  48 00 00 08 */	b lbl_80076C74
lbl_80076C70:
/* 80076C70 00073850  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_80076C74:
/* 80076C74 00073854  D0 1C 19 20 */	stfs f0, 0x1920(r28)
lbl_80076C78:
/* 80076C78 00073858  38 A1 00 30 */	addi r5, r1, 0x30
/* 80076C7C 0007385C  4C C6 31 82 */	crclr 6
/* 80076C80 00073860  38 60 04 1C */	li r3, 0x41c
/* 80076C84 00073864  38 80 00 00 */	li r4, 0
/* 80076C88 00073868  4B FE 91 55 */	bl ef_Spawn
/* 80076C8C 0007386C  38 7E 00 00 */	addi r3, r30, 0
/* 80076C90 00073870  38 9D 00 00 */	addi r4, r29, 0
/* 80076C94 00073874  38 BF 00 00 */	addi r5, r31, 0
/* 80076C98 00073878  48 00 18 1D */	bl func_800784B4
/* 80076C9C 0007387C  38 60 00 01 */	li r3, 1
/* 80076CA0 00073880  48 00 00 08 */	b lbl_80076CA8
lbl_80076CA4:
/* 80076CA4 00073884  38 60 00 00 */	li r3, 0
lbl_80076CA8:
/* 80076CA8 00073888  BA E1 00 54 */	lmw r23, 0x54(r1)
/* 80076CAC 0007388C  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80076CB0 00073890  38 21 00 78 */	addi r1, r1, 0x78
/* 80076CB4 00073894  7C 08 03 A6 */	mtlr r0
/* 80076CB8 00073898  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076CBC(void)
{ // clang-format off
    nofralloc
/* 80076CBC 0007389C  7C 08 02 A6 */	mflr r0
/* 80076CC0 000738A0  90 01 00 04 */	stw r0, 4(r1)
/* 80076CC4 000738A4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80076CC8 000738A8  BF 61 00 2C */	stmw r27, 0x2c(r1)
/* 80076CCC 000738AC  3B A3 00 00 */	addi r29, r3, 0
/* 80076CD0 000738B0  3B C4 00 00 */	addi r30, r4, 0
/* 80076CD4 000738B4  3B E5 00 00 */	addi r31, r5, 0
/* 80076CD8 000738B8  3B 7D 00 00 */	addi r27, r29, 0
/* 80076CDC 000738BC  3B 80 00 00 */	li r28, 0
lbl_80076CE0:
/* 80076CE0 000738C0  80 1B 09 14 */	lwz r0, 0x914(r27)
/* 80076CE4 000738C4  38 7B 09 14 */	addi r3, r27, 0x914
/* 80076CE8 000738C8  2C 00 00 00 */	cmpwi r0, 0
/* 80076CEC 000738CC  41 82 00 20 */	beq lbl_80076D0C
/* 80076CF0 000738D0  80 83 00 04 */	lwz r4, 4(r3)
/* 80076CF4 000738D4  80 1E 00 04 */	lwz r0, 4(r30)
/* 80076CF8 000738D8  7C 04 00 40 */	cmplw r4, r0
/* 80076CFC 000738DC  40 82 00 10 */	bne lbl_80076D0C
/* 80076D00 000738E0  38 BF 00 00 */	addi r5, r31, 0
/* 80076D04 000738E4  38 80 00 01 */	li r4, 1
/* 80076D08 000738E8  4B F9 19 81 */	bl func_80008688
lbl_80076D0C:
/* 80076D0C 000738EC  3B 9C 00 01 */	addi r28, r28, 1
/* 80076D10 000738F0  28 1C 00 04 */	cmplwi r28, 4
/* 80076D14 000738F4  3B 7B 01 38 */	addi r27, r27, 0x138
/* 80076D18 000738F8  41 80 FF C8 */	blt lbl_80076CE0
/* 80076D1C 000738FC  C0 3E 00 0C */	lfs f1, 0xc(r30)
/* 80076D20 00073900  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076D24 00073904  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80076D28 00073908  41 82 00 2C */	beq lbl_80076D54
/* 80076D2C 0007390C  FC 00 08 1E */	fctiwz f0, f1
/* 80076D30 00073910  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 80076D34 00073914  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80076D38 00073918  2C 00 00 00 */	cmpwi r0, 0
/* 80076D3C 0007391C  41 82 00 10 */	beq lbl_80076D4C
/* 80076D40 00073920  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 80076D44 00073924  80 61 00 24 */	lwz r3, 0x24(r1)
/* 80076D48 00073928  48 00 00 10 */	b lbl_80076D58
lbl_80076D4C:
/* 80076D4C 0007392C  38 60 00 01 */	li r3, 1
/* 80076D50 00073930  48 00 00 08 */	b lbl_80076D58
lbl_80076D54:
/* 80076D54 00073934  38 60 00 00 */	li r3, 0
lbl_80076D58:
/* 80076D58 00073938  80 1D 19 24 */	lwz r0, 0x1924(r29)
/* 80076D5C 0007393C  7C 03 00 00 */	cmpw r3, r0
/* 80076D60 00073940  40 81 00 5C */	ble lbl_80076DBC
/* 80076D64 00073944  90 7D 19 24 */	stw r3, 0x1924(r29)
/* 80076D68 00073948  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 80076D6C 0007394C  2C 00 00 00 */	cmpwi r0, 0
/* 80076D70 00073950  40 82 00 4C */	bne lbl_80076DBC
/* 80076D74 00073954  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 80076D78 00073958  C8 22 89 18 */	lfd f1, lbl_804D82F8
/* 80076D7C 0007395C  90 01 00 24 */	stw r0, 0x24(r1)
/* 80076D80 00073960  3C 00 43 30 */	lis r0, 0x4330
/* 80076D84 00073964  C0 5F 19 9C */	lfs f2, 0x199c(r31)
/* 80076D88 00073968  90 01 00 20 */	stw r0, 0x20(r1)
/* 80076D8C 0007396C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80076D90 00073970  EC 00 08 28 */	fsubs f0, f0, f1
/* 80076D94 00073974  EC 02 00 32 */	fmuls f0, f2, f0
/* 80076D98 00073978  D0 1D 19 28 */	stfs f0, 0x1928(r29)
/* 80076D9C 0007397C  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 80076DA0 00073980  C0 1D 00 B0 */	lfs f0, 0xb0(r29)
/* 80076DA4 00073984  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076DA8 00073988  40 81 00 0C */	ble lbl_80076DB4
/* 80076DAC 0007398C  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80076DB0 00073990  48 00 00 08 */	b lbl_80076DB8
lbl_80076DB4:
/* 80076DB4 00073994  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_80076DB8:
/* 80076DB8 00073998  D0 1D 19 2C */	stfs f0, 0x192c(r29)
lbl_80076DBC:
/* 80076DBC 0007399C  80 1F 19 A4 */	lwz r0, 0x19a4(r31)
/* 80076DC0 000739A0  7C 03 00 00 */	cmpw r3, r0
/* 80076DC4 000739A4  40 81 00 38 */	ble lbl_80076DFC
/* 80076DC8 000739A8  90 7F 19 A4 */	stw r3, 0x19a4(r31)
/* 80076DCC 000739AC  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 80076DD0 000739B0  C0 1D 00 B0 */	lfs f0, 0xb0(r29)
/* 80076DD4 000739B4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076DD8 000739B8  40 81 00 0C */	ble lbl_80076DE4
/* 80076DDC 000739BC  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80076DE0 000739C0  48 00 00 08 */	b lbl_80076DE8
lbl_80076DE4:
/* 80076DE4 000739C4  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80076DE8:
/* 80076DE8 000739C8  D0 1F 19 AC */	stfs f0, 0x19ac(r31)
/* 80076DEC 000739CC  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 80076DF0 000739D0  90 1F 19 B0 */	stw r0, 0x19b0(r31)
/* 80076DF4 000739D4  80 1D 00 00 */	lwz r0, 0(r29)
/* 80076DF8 000739D8  90 1F 19 A8 */	stw r0, 0x19a8(r31)
lbl_80076DFC:
/* 80076DFC 000739DC  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80076E00 000739E0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80076E04 000739E4  40 82 00 58 */	bne lbl_80076E5C
/* 80076E08 000739E8  80 1E 00 34 */	lwz r0, 0x34(r30)
/* 80076E0C 000739EC  7C 03 02 15 */	add. r0, r3, r0
/* 80076E10 000739F0  40 80 00 0C */	bge lbl_80076E1C
/* 80076E14 000739F4  38 80 00 00 */	li r4, 0
/* 80076E18 000739F8  48 00 00 08 */	b lbl_80076E20
lbl_80076E1C:
/* 80076E1C 000739FC  7C 04 03 78 */	mr r4, r0
lbl_80076E20:
/* 80076E20 00073A00  80 1F 19 A0 */	lwz r0, 0x19a0(r31)
/* 80076E24 00073A04  38 BE 00 64 */	addi r5, r30, 0x64
/* 80076E28 00073A08  4C C6 31 82 */	crclr 6
/* 80076E2C 00073A0C  38 60 04 1C */	li r3, 0x41c
/* 80076E30 00073A10  7C 00 22 14 */	add r0, r0, r4
/* 80076E34 00073A14  90 1F 19 A0 */	stw r0, 0x19a0(r31)
/* 80076E38 00073A18  38 80 00 00 */	li r4, 0
/* 80076E3C 00073A1C  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80076E40 00073A20  90 1F 19 BC */	stw r0, 0x19bc(r31)
/* 80076E44 00073A24  88 DD 22 1F */	lbz r6, 0x221f(r29)
/* 80076E48 00073A28  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 80076E4C 00073A2C  50 C0 F7 BC */	rlwimi r0, r6, 0x1e, 0x1e, 0x1e
/* 80076E50 00073A30  98 1F 22 1F */	stb r0, 0x221f(r31)
/* 80076E54 00073A34  4B FE 8F 89 */	bl ef_Spawn
/* 80076E58 00073A38  48 00 00 54 */	b lbl_80076EAC
lbl_80076E5C:
/* 80076E5C 00073A3C  7F E3 FB 78 */	mr r3, r31
/* 80076E60 00073A40  48 01 D2 D9 */	bl func_80094138
/* 80076E64 00073A44  38 7F 00 00 */	addi r3, r31, 0
/* 80076E68 00073A48  38 80 00 76 */	li r4, 0x76
/* 80076E6C 00073A4C  38 A0 00 00 */	li r5, 0
/* 80076E70 00073A50  48 04 91 61 */	bl func_800BFFD0
/* 80076E74 00073A54  38 7F 00 00 */	addi r3, r31, 0
/* 80076E78 00073A58  38 80 00 68 */	li r4, 0x68
/* 80076E7C 00073A5C  38 A0 00 7F */	li r5, 0x7f
/* 80076E80 00073A60  38 C0 00 40 */	li r6, 0x40
/* 80076E84 00073A64  48 01 12 C5 */	bl func_80088148
/* 80076E88 00073A68  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80076E8C 00073A6C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80076E90 00073A70  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80076E94 00073A74  4B FC 72 BD */	bl func_8003E150
/* 80076E98 00073A78  38 BE 00 64 */	addi r5, r30, 0x64
/* 80076E9C 00073A7C  4C C6 31 82 */	crclr 6
/* 80076EA0 00073A80  38 60 00 1B */	li r3, 0x1b
/* 80076EA4 00073A84  38 80 00 00 */	li r4, 0
/* 80076EA8 00073A88  4B FE 8F 35 */	bl ef_Spawn
lbl_80076EAC:
/* 80076EAC 00073A8C  C0 3F 19 B4 */	lfs f1, 0x19b4(r31)
/* 80076EB0 00073A90  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076EB4 00073A94  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80076EB8 00073A98  41 82 00 0C */	beq lbl_80076EC4
/* 80076EBC 00073A9C  D0 3D 19 64 */	stfs f1, 0x1964(r29)
/* 80076EC0 00073AA0  D0 3F 19 64 */	stfs f1, 0x1964(r31)
lbl_80076EC4:
/* 80076EC4 00073AA4  BB 61 00 2C */	lmw r27, 0x2c(r1)
/* 80076EC8 00073AA8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076ECC 00073AAC  38 21 00 40 */	addi r1, r1, 0x40
/* 80076ED0 00073AB0  7C 08 03 A6 */	mtlr r0
/* 80076ED4 00073AB4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_803C0C40;
extern unk_t lbl_80459598;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076ED8(void)
{ // clang-format off
    nofralloc
/* 80076ED8 00073AB8  7C 08 02 A6 */	mflr r0
/* 80076EDC 00073ABC  90 01 00 04 */	stw r0, 4(r1)
/* 80076EE0 00073AC0  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 80076EE4 00073AC4  DB E1 00 90 */	stfd f31, 0x90(r1)
/* 80076EE8 00073AC8  DB C1 00 88 */	stfd f30, 0x88(r1)
/* 80076EEC 00073ACC  BE E1 00 64 */	stmw r23, 0x64(r1)
/* 80076EF0 00073AD0  3B 64 00 00 */	addi r27, r4, 0
/* 80076EF4 00073AD4  7C BC 2B 78 */	mr r28, r5
/* 80076EF8 00073AD8  3B 43 00 00 */	addi r26, r3, 0
/* 80076EFC 00073ADC  3B A6 00 00 */	addi r29, r6, 0
/* 80076F00 00073AE0  80 A5 1A 58 */	lwz r5, 0x1a58(r5)
/* 80076F04 00073AE4  80 83 00 00 */	lwz r4, 0(r3)
/* 80076F08 00073AE8  3C 60 80 3C */	lis r3, lbl_803C0C40@ha
/* 80076F0C 00073AEC  28 05 00 00 */	cmplwi r5, 0
/* 80076F10 00073AF0  C0 7B 00 0C */	lfs f3, 0xc(r27)
/* 80076F14 00073AF4  3B E3 0C 40 */	addi r31, r3, lbl_803C0C40@l
/* 80076F18 00073AF8  41 82 00 24 */	beq lbl_80076F3C
/* 80076F1C 00073AFC  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 80076F20 00073B00  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80076F24 00073B04  40 82 00 18 */	bne lbl_80076F3C
/* 80076F28 00073B08  7C 05 20 40 */	cmplw r5, r4
/* 80076F2C 00073B0C  41 82 00 10 */	beq lbl_80076F3C
/* 80076F30 00073B10  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076F34 00073B14  C0 03 01 28 */	lfs f0, 0x128(r3)
/* 80076F38 00073B18  EC 63 00 32 */	fmuls f3, f3, f0
lbl_80076F3C:
/* 80076F3C 00073B1C  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 80076F40 00073B20  2C 00 01 45 */	cmpwi r0, 0x145
/* 80076F44 00073B24  40 82 00 10 */	bne lbl_80076F54
/* 80076F48 00073B28  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076F4C 00073B2C  C0 03 07 14 */	lfs f0, 0x714(r3)
/* 80076F50 00073B30  EC 63 00 32 */	fmuls f3, f3, f0
lbl_80076F54:
/* 80076F54 00073B34  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076F58 00073B38  C0 5C 18 2C */	lfs f2, 0x182c(r28)
/* 80076F5C 00073B3C  C0 3B 00 70 */	lfs f1, 0x70(r27)
/* 80076F60 00073B40  C0 03 07 A8 */	lfs f0, 0x7a8(r3)
/* 80076F64 00073B44  EF E3 00 B2 */	fmuls f31, f3, f2
/* 80076F68 00073B48  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076F6C 00073B4C  40 80 00 0C */	bge lbl_80076F78
/* 80076F70 00073B50  38 00 00 01 */	li r0, 1
/* 80076F74 00073B54  48 00 00 08 */	b lbl_80076F7C
lbl_80076F78:
/* 80076F78 00073B58  38 00 00 00 */	li r0, 0
lbl_80076F7C:
/* 80076F7C 00073B5C  2C 00 00 00 */	cmpwi r0, 0
/* 80076F80 00073B60  41 82 02 44 */	beq lbl_800771C4
/* 80076F84 00073B64  80 0D AE B8 */	lwz r0, lbl_804D6558
/* 80076F88 00073B68  2C 00 00 00 */	cmpwi r0, 0
/* 80076F8C 00073B6C  40 82 04 B8 */	bne lbl_80077444
/* 80076F90 00073B70  C0 3C 18 9C */	lfs f1, 0x189c(r28)
/* 80076F94 00073B74  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076F98 00073B78  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80076F9C 00073B7C  40 82 04 A8 */	bne lbl_80077444
/* 80076FA0 00073B80  38 00 00 02 */	li r0, 2
/* 80076FA4 00073B84  7C 09 03 A6 */	mtctr r0
/* 80076FA8 00073B88  38 9B 00 D4 */	addi r4, r27, 0xd4
/* 80076FAC 00073B8C  38 60 00 00 */	li r3, 0
lbl_80076FB0:
/* 80076FB0 00073B90  80 04 00 00 */	lwz r0, 0(r4)
/* 80076FB4 00073B94  7C 00 E0 40 */	cmplw r0, r28
/* 80076FB8 00073B98  41 82 00 60 */	beq lbl_80077018
/* 80076FBC 00073B9C  84 04 00 08 */	lwzu r0, 8(r4)
/* 80076FC0 00073BA0  38 63 00 01 */	addi r3, r3, 1
/* 80076FC4 00073BA4  7C 00 E0 40 */	cmplw r0, r28
/* 80076FC8 00073BA8  41 82 00 50 */	beq lbl_80077018
/* 80076FCC 00073BAC  84 04 00 08 */	lwzu r0, 8(r4)
/* 80076FD0 00073BB0  38 63 00 01 */	addi r3, r3, 1
/* 80076FD4 00073BB4  7C 00 E0 40 */	cmplw r0, r28
/* 80076FD8 00073BB8  41 82 00 40 */	beq lbl_80077018
/* 80076FDC 00073BBC  84 04 00 08 */	lwzu r0, 8(r4)
/* 80076FE0 00073BC0  38 63 00 01 */	addi r3, r3, 1
/* 80076FE4 00073BC4  7C 00 E0 40 */	cmplw r0, r28
/* 80076FE8 00073BC8  41 82 00 30 */	beq lbl_80077018
/* 80076FEC 00073BCC  84 04 00 08 */	lwzu r0, 8(r4)
/* 80076FF0 00073BD0  38 63 00 01 */	addi r3, r3, 1
/* 80076FF4 00073BD4  7C 00 E0 40 */	cmplw r0, r28
/* 80076FF8 00073BD8  41 82 00 20 */	beq lbl_80077018
/* 80076FFC 00073BDC  84 04 00 08 */	lwzu r0, 8(r4)
/* 80077000 00073BE0  38 63 00 01 */	addi r3, r3, 1
/* 80077004 00073BE4  7C 00 E0 40 */	cmplw r0, r28
/* 80077008 00073BE8  41 82 00 10 */	beq lbl_80077018
/* 8007700C 00073BEC  38 84 00 08 */	addi r4, r4, 8
/* 80077010 00073BF0  38 63 00 01 */	addi r3, r3, 1
/* 80077014 00073BF4  42 00 FF 9C */	bdnz lbl_80076FB0
lbl_80077018:
/* 80077018 00073BF8  28 03 00 0C */	cmplwi r3, 0xc
/* 8007701C 00073BFC  40 82 00 0C */	bne lbl_80077028
/* 80077020 00073C00  38 00 00 00 */	li r0, 0
/* 80077024 00073C04  48 00 00 08 */	b lbl_8007702C
lbl_80077028:
/* 80077028 00073C08  38 00 00 01 */	li r0, 1
lbl_8007702C:
/* 8007702C 00073C0C  2C 00 00 00 */	cmpwi r0, 0
/* 80077030 00073C10  40 82 04 14 */	bne lbl_80077444
/* 80077034 00073C14  C0 02 89 08 */	lfs f0, lbl_804D82E8
/* 80077038 00073C18  EF C0 07 F2 */	fmuls f30, f0, f31
/* 8007703C 00073C1C  FC 00 F0 1E */	fctiwz f0, f30
/* 80077040 00073C20  D8 01 00 58 */	stfd f0, 0x58(r1)
/* 80077044 00073C24  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80077048 00073C28  2C 00 00 00 */	cmpwi r0, 0
/* 8007704C 00073C2C  40 82 00 14 */	bne lbl_80077060
/* 80077050 00073C30  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077054 00073C34  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 80077058 00073C38  41 82 00 08 */	beq lbl_80077060
/* 8007705C 00073C3C  C3 C2 89 0C */	lfs f30, lbl_804D82EC
lbl_80077060:
/* 80077060 00073C40  3B C0 00 00 */	li r30, 0
/* 80077064 00073C44  3B 1A 00 00 */	addi r24, r26, 0
lbl_80077068:
/* 80077068 00073C48  80 18 09 14 */	lwz r0, 0x914(r24)
/* 8007706C 00073C4C  38 78 09 14 */	addi r3, r24, 0x914
/* 80077070 00073C50  2C 00 00 00 */	cmpwi r0, 0
/* 80077074 00073C54  41 82 00 20 */	beq lbl_80077094
/* 80077078 00073C58  80 83 00 04 */	lwz r4, 4(r3)
/* 8007707C 00073C5C  80 1B 00 04 */	lwz r0, 4(r27)
/* 80077080 00073C60  7C 04 00 40 */	cmplw r4, r0
/* 80077084 00073C64  40 82 00 10 */	bne lbl_80077094
/* 80077088 00073C68  38 BC 00 00 */	addi r5, r28, 0
/* 8007708C 00073C6C  38 80 00 00 */	li r4, 0
/* 80077090 00073C70  4B F9 17 91 */	bl func_80008820
lbl_80077094:
/* 80077094 00073C74  3B DE 00 01 */	addi r30, r30, 1
/* 80077098 00073C78  28 1E 00 04 */	cmplwi r30, 4
/* 8007709C 00073C7C  3B 18 01 38 */	addi r24, r24, 0x138
/* 800770A0 00073C80  41 80 FF C8 */	blt lbl_80077068
/* 800770A4 00073C84  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 800770A8 00073C88  2C 00 00 00 */	cmpwi r0, 0
/* 800770AC 00073C8C  40 82 01 08 */	bne lbl_800771B4
/* 800770B0 00073C90  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 800770B4 00073C94  2C 00 00 00 */	cmpwi r0, 0
/* 800770B8 00073C98  40 82 00 FC */	bne lbl_800771B4
/* 800770BC 00073C9C  88 1C 22 1D */	lbz r0, 0x221d(r28)
/* 800770C0 00073CA0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800770C4 00073CA4  40 82 00 F0 */	bne lbl_800771B4
/* 800770C8 00073CA8  80 1D 00 00 */	lwz r0, 0(r29)
/* 800770CC 00073CAC  2C 00 00 00 */	cmpwi r0, 0
/* 800770D0 00073CB0  40 82 00 E4 */	bne lbl_800771B4
/* 800770D4 00073CB4  80 1B 00 08 */	lwz r0, 8(r27)
/* 800770D8 00073CB8  38 9A 00 00 */	addi r4, r26, 0
/* 800770DC 00073CBC  54 03 F8 7F */	rlwinm. r3, r0, 0x1f, 1, 0x1f
/* 800770E0 00073CC0  38 E3 00 00 */	addi r7, r3, 0
/* 800770E4 00073CC4  40 82 00 10 */	bne lbl_800770F4
/* 800770E8 00073CC8  28 00 00 00 */	cmplwi r0, 0
/* 800770EC 00073CCC  41 82 00 08 */	beq lbl_800770F4
/* 800770F0 00073CD0  38 E0 00 01 */	li r7, 1
lbl_800770F4:
/* 800770F4 00073CD4  FC 00 F0 1E */	fctiwz f0, f30
/* 800770F8 00073CD8  80 1C 18 40 */	lwz r0, 0x1840(r28)
/* 800770FC 00073CDC  D8 01 00 50 */	stfd f0, 0x50(r1)
/* 80077100 00073CE0  80 61 00 54 */	lwz r3, 0x54(r1)
/* 80077104 00073CE4  D8 01 00 58 */	stfd f0, 0x58(r1)
/* 80077108 00073CE8  7C 03 00 00 */	cmpw r3, r0
/* 8007710C 00073CEC  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80077110 00073CF0  40 81 00 08 */	ble lbl_80077118
/* 80077114 00073CF4  90 1C 18 40 */	stw r0, 0x1840(r28)
lbl_80077118:
/* 80077118 00073CF8  80 7A 11 98 */	lwz r3, 0x1198(r26)
/* 8007711C 00073CFC  28 03 00 00 */	cmplwi r3, 0
/* 80077120 00073D00  41 82 00 08 */	beq lbl_80077128
/* 80077124 00073D04  80 83 00 2C */	lwz r4, 0x2c(r3)
lbl_80077128:
/* 80077128 00073D08  80 0D AE BC */	lwz r0, lbl_804D655C
/* 8007712C 00073D0C  80 C4 00 00 */	lwz r6, 0(r4)
/* 80077130 00073D10  28 00 00 14 */	cmplwi r0, 0x14
/* 80077134 00073D14  80 A4 00 04 */	lwz r5, 4(r4)
/* 80077138 00073D18  40 80 00 5C */	bge lbl_80077194
/* 8007713C 00073D1C  1C 80 00 28 */	mulli r4, r0, 0x28
/* 80077140 00073D20  3C 60 80 46 */	lis r3, lbl_80459598@ha
/* 80077144 00073D24  38 03 95 98 */	addi r0, r3, lbl_80459598@l
/* 80077148 00073D28  7C 80 22 14 */	add r4, r0, r4
/* 8007714C 00073D2C  38 00 00 01 */	li r0, 1
/* 80077150 00073D30  90 04 00 00 */	stw r0, 0(r4)
/* 80077154 00073D34  90 A4 00 04 */	stw r5, 4(r4)
/* 80077158 00073D38  90 C4 00 08 */	stw r6, 8(r4)
/* 8007715C 00073D3C  93 64 00 0C */	stw r27, 0xc(r4)
/* 80077160 00073D40  93 A4 00 10 */	stw r29, 0x10(r4)
/* 80077164 00073D44  80 7B 00 64 */	lwz r3, 0x64(r27)
/* 80077168 00073D48  80 1B 00 68 */	lwz r0, 0x68(r27)
/* 8007716C 00073D4C  90 64 00 14 */	stw r3, 0x14(r4)
/* 80077170 00073D50  90 04 00 18 */	stw r0, 0x18(r4)
/* 80077174 00073D54  80 1B 00 6C */	lwz r0, 0x6c(r27)
/* 80077178 00073D58  90 04 00 1C */	stw r0, 0x1c(r4)
/* 8007717C 00073D5C  D3 C4 00 20 */	stfs f30, 0x20(r4)
/* 80077180 00073D60  90 E4 00 24 */	stw r7, 0x24(r4)
/* 80077184 00073D64  80 6D AE BC */	lwz r3, lbl_804D655C
/* 80077188 00073D68  38 03 00 01 */	addi r0, r3, 1
/* 8007718C 00073D6C  90 0D AE BC */	stw r0, lbl_804D655C
/* 80077190 00073D70  48 00 00 24 */	b lbl_800771B4
lbl_80077194:
/* 80077194 00073D74  38 7F 00 58 */	addi r3, r31, 0x58
/* 80077198 00073D78  4C C6 31 82 */	crclr 6
/* 8007719C 00073D7C  38 80 00 14 */	li r4, 0x14
/* 800771A0 00073D80  48 2C E5 09 */	bl OSReport
/* 800771A4 00073D84  38 7F 00 34 */	addi r3, r31, 0x34
/* 800771A8 00073D88  38 80 01 10 */	li r4, 0x110
/* 800771AC 00073D8C  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 800771B0 00073D90  48 31 10 71 */	bl __assert
lbl_800771B4:
/* 800771B4 00073D94  7F 83 E3 78 */	mr r3, r28
/* 800771B8 00073D98  48 00 12 D1 */	bl func_80078488
/* 800771BC 00073D9C  38 60 00 01 */	li r3, 1
/* 800771C0 00073DA0  48 00 02 88 */	b lbl_80077448
lbl_800771C4:
/* 800771C4 00073DA4  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800771C8 00073DA8  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 800771CC 00073DAC  41 82 00 2C */	beq lbl_800771F8
/* 800771D0 00073DB0  FC 00 F8 1E */	fctiwz f0, f31
/* 800771D4 00073DB4  D8 01 00 50 */	stfd f0, 0x50(r1)
/* 800771D8 00073DB8  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800771DC 00073DBC  2C 00 00 00 */	cmpwi r0, 0
/* 800771E0 00073DC0  41 82 00 10 */	beq lbl_800771F0
/* 800771E4 00073DC4  D8 01 00 50 */	stfd f0, 0x50(r1)
/* 800771E8 00073DC8  83 01 00 54 */	lwz r24, 0x54(r1)
/* 800771EC 00073DCC  48 00 00 10 */	b lbl_800771FC
lbl_800771F0:
/* 800771F0 00073DD0  3B 00 00 01 */	li r24, 1
/* 800771F4 00073DD4  48 00 00 08 */	b lbl_800771FC
lbl_800771F8:
/* 800771F8 00073DD8  3B 00 00 00 */	li r24, 0
lbl_800771FC:
/* 800771FC 00073DDC  3B 20 00 00 */	li r25, 0
/* 80077200 00073DE0  93 2D AE BC */	stw r25, lbl_804D655C
/* 80077204 00073DE4  3A FA 00 00 */	addi r23, r26, 0
/* 80077208 00073DE8  3B C0 00 00 */	li r30, 0
lbl_8007720C:
/* 8007720C 00073DEC  80 17 09 14 */	lwz r0, 0x914(r23)
/* 80077210 00073DF0  38 77 09 14 */	addi r3, r23, 0x914
/* 80077214 00073DF4  2C 00 00 00 */	cmpwi r0, 0
/* 80077218 00073DF8  41 82 00 20 */	beq lbl_80077238
/* 8007721C 00073DFC  80 83 00 04 */	lwz r4, 4(r3)
/* 80077220 00073E00  80 1B 00 04 */	lwz r0, 4(r27)
/* 80077224 00073E04  7C 04 00 40 */	cmplw r4, r0
/* 80077228 00073E08  40 82 00 10 */	bne lbl_80077238
/* 8007722C 00073E0C  38 BC 00 00 */	addi r5, r28, 0
/* 80077230 00073E10  38 80 00 00 */	li r4, 0
/* 80077234 00073E14  4B F9 14 55 */	bl func_80008688
lbl_80077238:
/* 80077238 00073E18  3B 39 00 01 */	addi r25, r25, 1
/* 8007723C 00073E1C  28 19 00 04 */	cmplwi r25, 4
/* 80077240 00073E20  3A F7 01 38 */	addi r23, r23, 0x138
/* 80077244 00073E24  41 80 FF C8 */	blt lbl_8007720C
/* 80077248 00073E28  80 1A 19 14 */	lwz r0, 0x1914(r26)
/* 8007724C 00073E2C  7C 18 00 00 */	cmpw r24, r0
/* 80077250 00073E30  40 81 00 08 */	ble lbl_80077258
/* 80077254 00073E34  93 1A 19 14 */	stw r24, 0x1914(r26)
lbl_80077258:
/* 80077258 00073E38  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 8007725C 00073E3C  2C 00 00 00 */	cmpwi r0, 0
/* 80077260 00073E40  40 82 01 C0 */	bne lbl_80077420
/* 80077264 00073E44  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 80077268 00073E48  2C 00 00 00 */	cmpwi r0, 0
/* 8007726C 00073E4C  40 82 01 B4 */	bne lbl_80077420
/* 80077270 00073E50  88 1C 22 1D */	lbz r0, 0x221d(r28)
/* 80077274 00073E54  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80077278 00073E58  40 82 01 A8 */	bne lbl_80077420
/* 8007727C 00073E5C  80 1D 00 00 */	lwz r0, 0(r29)
/* 80077280 00073E60  2C 00 00 00 */	cmpwi r0, 0
/* 80077284 00073E64  40 82 01 9C */	bne lbl_80077420
/* 80077288 00073E68  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007728C 00073E6C  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 80077290 00073E70  41 82 00 2C */	beq lbl_800772BC
/* 80077294 00073E74  FC 00 F8 1E */	fctiwz f0, f31
/* 80077298 00073E78  D8 01 00 50 */	stfd f0, 0x50(r1)
/* 8007729C 00073E7C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800772A0 00073E80  2C 00 00 00 */	cmpwi r0, 0
/* 800772A4 00073E84  41 82 00 10 */	beq lbl_800772B4
/* 800772A8 00073E88  D8 01 00 50 */	stfd f0, 0x50(r1)
/* 800772AC 00073E8C  83 01 00 54 */	lwz r24, 0x54(r1)
/* 800772B0 00073E90  48 00 00 10 */	b lbl_800772C0
lbl_800772B4:
/* 800772B4 00073E94  3B 00 00 01 */	li r24, 1
/* 800772B8 00073E98  48 00 00 08 */	b lbl_800772C0
lbl_800772BC:
/* 800772BC 00073E9C  3B 00 00 00 */	li r24, 0
lbl_800772C0:
/* 800772C0 00073EA0  88 1C 22 1C */	lbz r0, 0x221c(r28)
/* 800772C4 00073EA4  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800772C8 00073EA8  41 82 00 34 */	beq lbl_800772FC
/* 800772CC 00073EAC  C0 1C 18 34 */	lfs f0, 0x1834(r28)
/* 800772D0 00073EB0  EC 00 F8 28 */	fsubs f0, f0, f31
/* 800772D4 00073EB4  D0 1C 18 34 */	stfs f0, 0x1834(r28)
/* 800772D8 00073EB8  C0 3C 18 34 */	lfs f1, 0x1834(r28)
/* 800772DC 00073EBC  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800772E0 00073EC0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800772E4 00073EC4  40 80 00 18 */	bge lbl_800772FC
/* 800772E8 00073EC8  88 1C 22 1C */	lbz r0, 0x221c(r28)
/* 800772EC 00073ECC  38 60 00 00 */	li r3, 0
/* 800772F0 00073ED0  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800772F4 00073ED4  FF E0 08 50 */	fneg f31, f1
/* 800772F8 00073ED8  98 1C 22 1C */	stb r0, 0x221c(r28)
lbl_800772FC:
/* 800772FC 00073EDC  88 1C 22 1C */	lbz r0, 0x221c(r28)
/* 80077300 00073EE0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80077304 00073EE4  40 82 00 54 */	bne lbl_80077358
/* 80077308 00073EE8  C0 02 89 04 */	lfs f0, lbl_804D82E4
/* 8007730C 00073EEC  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80077310 00073EF0  40 81 00 24 */	ble lbl_80077334
/* 80077314 00073EF4  FC 20 F8 90 */	fmr f1, f31
/* 80077318 00073EF8  38 7F 00 18 */	addi r3, r31, 0x18
/* 8007731C 00073EFC  4C C6 32 42 */	crset 6
/* 80077320 00073F00  48 2C E3 89 */	bl OSReport
/* 80077324 00073F04  38 7F 00 34 */	addi r3, r31, 0x34
/* 80077328 00073F08  38 80 00 B7 */	li r4, 0xb7
/* 8007732C 00073F0C  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 80077330 00073F10  48 31 0E F1 */	bl __assert
lbl_80077334:
/* 80077334 00073F14  C0 1C 18 38 */	lfs f0, 0x1838(r28)
/* 80077338 00073F18  EC 00 F8 2A */	fadds f0, f0, f31
/* 8007733C 00073F1C  D0 1C 18 38 */	stfs f0, 0x1838(r28)
/* 80077340 00073F20  80 1C 18 3C */	lwz r0, 0x183c(r28)
/* 80077344 00073F24  7C 18 00 00 */	cmpw r24, r0
/* 80077348 00073F28  40 81 00 08 */	ble lbl_80077350
/* 8007734C 00073F2C  93 1C 18 3C */	stw r24, 0x183c(r28)
lbl_80077350:
/* 80077350 00073F30  38 00 00 01 */	li r0, 1
/* 80077354 00073F34  48 00 00 08 */	b lbl_8007735C
lbl_80077358:
/* 80077358 00073F38  38 00 00 00 */	li r0, 0
lbl_8007735C:
/* 8007735C 00073F3C  2C 00 00 00 */	cmpwi r0, 0
/* 80077360 00073F40  41 82 00 B0 */	beq lbl_80077410
/* 80077364 00073F44  80 7A 11 98 */	lwz r3, 0x1198(r26)
/* 80077368 00073F48  38 9A 00 00 */	addi r4, r26, 0
/* 8007736C 00073F4C  28 03 00 00 */	cmplwi r3, 0
/* 80077370 00073F50  41 82 00 08 */	beq lbl_80077378
/* 80077374 00073F54  80 83 00 2C */	lwz r4, 0x2c(r3)
lbl_80077378:
/* 80077378 00073F58  80 0D AE B8 */	lwz r0, lbl_804D6558
/* 8007737C 00073F5C  80 FB 00 08 */	lwz r7, 8(r27)
/* 80077380 00073F60  28 00 00 14 */	cmplwi r0, 0x14
/* 80077384 00073F64  80 C4 00 00 */	lwz r6, 0(r4)
/* 80077388 00073F68  80 A4 00 04 */	lwz r5, 4(r4)
/* 8007738C 00073F6C  40 80 00 60 */	bge lbl_800773EC
/* 80077390 00073F70  1C 80 00 28 */	mulli r4, r0, 0x28
/* 80077394 00073F74  3C 60 80 46 */	lis r3, lbl_80459278@ha
/* 80077398 00073F78  38 03 92 78 */	addi r0, r3, lbl_80459278@l
/* 8007739C 00073F7C  7C 80 22 14 */	add r4, r0, r4
/* 800773A0 00073F80  38 00 00 01 */	li r0, 1
/* 800773A4 00073F84  90 04 00 00 */	stw r0, 0(r4)
/* 800773A8 00073F88  90 A4 00 04 */	stw r5, 4(r4)
/* 800773AC 00073F8C  90 C4 00 08 */	stw r6, 8(r4)
/* 800773B0 00073F90  93 64 00 0C */	stw r27, 0xc(r4)
/* 800773B4 00073F94  93 A4 00 10 */	stw r29, 0x10(r4)
/* 800773B8 00073F98  80 7B 00 64 */	lwz r3, 0x64(r27)
/* 800773BC 00073F9C  80 1B 00 68 */	lwz r0, 0x68(r27)
/* 800773C0 00073FA0  90 64 00 14 */	stw r3, 0x14(r4)
/* 800773C4 00073FA4  90 04 00 18 */	stw r0, 0x18(r4)
/* 800773C8 00073FA8  80 1B 00 6C */	lwz r0, 0x6c(r27)
/* 800773CC 00073FAC  90 04 00 1C */	stw r0, 0x1c(r4)
/* 800773D0 00073FB0  C0 1B 00 0C */	lfs f0, 0xc(r27)
/* 800773D4 00073FB4  D0 04 00 20 */	stfs f0, 0x20(r4)
/* 800773D8 00073FB8  90 E4 00 24 */	stw r7, 0x24(r4)
/* 800773DC 00073FBC  80 6D AE B8 */	lwz r3, lbl_804D6558
/* 800773E0 00073FC0  38 03 00 01 */	addi r0, r3, 1
/* 800773E4 00073FC4  90 0D AE B8 */	stw r0, lbl_804D6558
/* 800773E8 00073FC8  48 00 00 24 */	b lbl_8007740C
lbl_800773EC:
/* 800773EC 00073FCC  38 7F 00 40 */	addi r3, r31, 0x40
/* 800773F0 00073FD0  4C C6 31 82 */	crclr 6
/* 800773F4 00073FD4  38 80 00 14 */	li r4, 0x14
/* 800773F8 00073FD8  48 2C E2 B1 */	bl OSReport
/* 800773FC 00073FDC  38 7F 00 34 */	addi r3, r31, 0x34
/* 80077400 00073FE0  38 80 00 E3 */	li r4, 0xe3
/* 80077404 00073FE4  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 80077408 00073FE8  48 31 0E 19 */	bl __assert
lbl_8007740C:
/* 8007740C 00073FEC  3B C0 00 01 */	li r30, 1
lbl_80077410:
/* 80077410 00073FF0  FC 20 F8 90 */	fmr f1, f31
/* 80077414 00073FF4  80 7A 00 00 */	lwz r3, 0(r26)
/* 80077418 00073FF8  80 9C 00 00 */	lwz r4, 0(r28)
/* 8007741C 00073FFC  48 00 15 01 */	bl func_8007891C
lbl_80077420:
/* 80077420 00074000  2C 1E 00 00 */	cmpwi r30, 0
/* 80077424 00074004  40 82 00 18 */	bne lbl_8007743C
/* 80077428 00074008  38 BB 00 64 */	addi r5, r27, 0x64
/* 8007742C 0007400C  4C C6 31 82 */	crclr 6
/* 80077430 00074010  38 60 04 1C */	li r3, 0x41c
/* 80077434 00074014  38 80 00 00 */	li r4, 0
/* 80077438 00074018  4B FE 89 A5 */	bl ef_Spawn
lbl_8007743C:
/* 8007743C 0007401C  38 60 00 01 */	li r3, 1
/* 80077440 00074020  48 00 00 08 */	b lbl_80077448
lbl_80077444:
/* 80077444 00074024  38 60 00 00 */	li r3, 0
lbl_80077448:
/* 80077448 00074028  BA E1 00 64 */	lmw r23, 0x64(r1)
/* 8007744C 0007402C  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 80077450 00074030  CB E1 00 90 */	lfd f31, 0x90(r1)
/* 80077454 00074034  CB C1 00 88 */	lfd f30, 0x88(r1)
/* 80077458 00074038  38 21 00 98 */	addi r1, r1, 0x98
/* 8007745C 0007403C  7C 08 03 A6 */	mtlr r0
/* 80077460 00074040  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80077464(void)
{ // clang-format off
    nofralloc
/* 80077464 00074044  7C 08 02 A6 */	mflr r0
/* 80077468 00074048  38 E0 00 00 */	li r7, 0
/* 8007746C 0007404C  90 01 00 04 */	stw r0, 4(r1)
/* 80077470 00074050  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80077474 00074054  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80077478 00074058  3B E5 00 00 */	addi r31, r5, 0
/* 8007747C 0007405C  38 DF 00 00 */	addi r6, r31, 0
/* 80077480 00074060  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80077484 00074064  3B C3 00 00 */	addi r30, r3, 0
/* 80077488 00074068  38 A0 00 07 */	li r5, 7
/* 8007748C 0007406C  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 80077490 00074070  3B A4 00 00 */	addi r29, r4, 0
/* 80077494 00074074  48 1F 86 31 */	bl func_8026FAC4
/* 80077498 00074078  C0 3D 00 0C */	lfs f1, 0xc(r29)
/* 8007749C 0007407C  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800774A0 00074080  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800774A4 00074084  41 82 00 2C */	beq lbl_800774D0
/* 800774A8 00074088  FC 00 08 1E */	fctiwz f0, f1
/* 800774AC 0007408C  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 800774B0 00074090  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800774B4 00074094  2C 00 00 00 */	cmpwi r0, 0
/* 800774B8 00074098  41 82 00 10 */	beq lbl_800774C8
/* 800774BC 0007409C  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 800774C0 000740A0  80 61 00 24 */	lwz r3, 0x24(r1)
/* 800774C4 000740A4  48 00 00 10 */	b lbl_800774D4
lbl_800774C8:
/* 800774C8 000740A8  38 60 00 01 */	li r3, 1
/* 800774CC 000740AC  48 00 00 08 */	b lbl_800774D4
lbl_800774D0:
/* 800774D0 000740B0  38 60 00 00 */	li r3, 0
lbl_800774D4:
/* 800774D4 000740B4  80 1F 1A 30 */	lwz r0, 0x1a30(r31)
/* 800774D8 000740B8  7C 03 00 00 */	cmpw r3, r0
/* 800774DC 000740BC  40 81 00 A8 */	ble lbl_80077584
/* 800774E0 000740C0  88 1D 00 41 */	lbz r0, 0x41(r29)
/* 800774E4 000740C4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800774E8 000740C8  41 82 00 18 */	beq lbl_80077500
/* 800774EC 000740CC  80 1E 0C 4C */	lwz r0, 0xc4c(r30)
/* 800774F0 000740D0  7C 03 00 00 */	cmpw r3, r0
/* 800774F4 000740D4  40 81 00 1C */	ble lbl_80077510
/* 800774F8 000740D8  90 7E 0C 4C */	stw r3, 0xc4c(r30)
/* 800774FC 000740DC  48 00 00 14 */	b lbl_80077510
lbl_80077500:
/* 80077500 000740E0  80 1E 0C 34 */	lwz r0, 0xc34(r30)
/* 80077504 000740E4  7C 03 00 00 */	cmpw r3, r0
/* 80077508 000740E8  40 81 00 08 */	ble lbl_80077510
/* 8007750C 000740EC  90 7E 0C 34 */	stw r3, 0xc34(r30)
lbl_80077510:
/* 80077510 000740F0  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 80077514 000740F4  C0 1E 00 4C */	lfs f0, 0x4c(r30)
/* 80077518 000740F8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007751C 000740FC  40 81 00 0C */	ble lbl_80077528
/* 80077520 00074100  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077524 00074104  48 00 00 08 */	b lbl_8007752C
lbl_80077528:
/* 80077528 00074108  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_8007752C:
/* 8007752C 0007410C  D0 1E 0C 68 */	stfs f0, 0xc68(r30)
/* 80077530 00074110  90 7F 1A 3C */	stw r3, 0x1a3c(r31)
/* 80077534 00074114  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077538 00074118  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 8007753C 0007411C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 80077540 00074120  41 82 00 20 */	beq lbl_80077560
/* 80077544 00074124  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077548 00074128  40 81 00 0C */	ble lbl_80077554
/* 8007754C 0007412C  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077550 00074130  48 00 00 08 */	b lbl_80077558
lbl_80077554:
/* 80077554 00074134  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80077558:
/* 80077558 00074138  D0 1F 1A 2C */	stfs f0, 0x1a2c(r31)
/* 8007755C 0007413C  48 00 01 10 */	b lbl_8007766C
lbl_80077560:
/* 80077560 00074140  C0 3E 00 4C */	lfs f1, 0x4c(r30)
/* 80077564 00074144  C0 1F 00 B0 */	lfs f0, 0xb0(r31)
/* 80077568 00074148  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007756C 0007414C  40 81 00 0C */	ble lbl_80077578
/* 80077570 00074150  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077574 00074154  48 00 00 08 */	b lbl_8007757C
lbl_80077578:
/* 80077578 00074158  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_8007757C:
/* 8007757C 0007415C  D0 1F 1A 2C */	stfs f0, 0x1a2c(r31)
/* 80077580 00074160  48 00 00 EC */	b lbl_8007766C
lbl_80077584:
/* 80077584 00074164  80 1F 00 00 */	lwz r0, 0(r31)
/* 80077588 00074168  90 1E 0C 64 */	stw r0, 0xc64(r30)
/* 8007758C 0007416C  80 1F 20 70 */	lwz r0, 0x2070(r31)
/* 80077590 00074170  90 1E 0C 74 */	stw r0, 0xc74(r30)
/* 80077594 00074174  80 7F 20 74 */	lwz r3, 0x2074(r31)
/* 80077598 00074178  80 1F 20 78 */	lwz r0, 0x2078(r31)
/* 8007759C 0007417C  90 7E 0C 78 */	stw r3, 0xc78(r30)
/* 800775A0 00074180  90 1E 0C 7C */	stw r0, 0xc7c(r30)
/* 800775A4 00074184  80 7F 20 7C */	lwz r3, 0x207c(r31)
/* 800775A8 00074188  80 1F 20 80 */	lwz r0, 0x2080(r31)
/* 800775AC 0007418C  90 7E 0C 80 */	stw r3, 0xc80(r30)
/* 800775B0 00074190  90 1E 0C 84 */	stw r0, 0xc84(r30)
/* 800775B4 00074194  80 1F 20 84 */	lwz r0, 0x2084(r31)
/* 800775B8 00074198  90 1E 0C 88 */	stw r0, 0xc88(r30)
/* 800775BC 0007419C  A0 1F 20 88 */	lhz r0, 0x2088(r31)
/* 800775C0 000741A0  B0 1E 0C 8C */	sth r0, 0xc8c(r30)
/* 800775C4 000741A4  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 800775C8 000741A8  C0 1E 00 4C */	lfs f0, 0x4c(r30)
/* 800775CC 000741AC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800775D0 000741B0  40 81 00 0C */	ble lbl_800775DC
/* 800775D4 000741B4  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 800775D8 000741B8  48 00 00 08 */	b lbl_800775E0
lbl_800775DC:
/* 800775DC 000741BC  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_800775E0:
/* 800775E0 000741C0  D0 1E 0C 68 */	stfs f0, 0xc68(r30)
/* 800775E4 000741C4  C0 1F 1A 34 */	lfs f0, 0x1a34(r31)
/* 800775E8 000741C8  D0 1E 0C 6C */	stfs f0, 0xc6c(r30)
/* 800775EC 000741CC  C0 1F 1A 38 */	lfs f0, 0x1a38(r31)
/* 800775F0 000741D0  D0 1E 0C 70 */	stfs f0, 0xc70(r30)
/* 800775F4 000741D4  88 7F 22 18 */	lbz r3, 0x2218(r31)
/* 800775F8 000741D8  88 1E 0D CC */	lbz r0, 0xdcc(r30)
/* 800775FC 000741DC  50 60 1E B4 */	rlwimi r0, r3, 3, 0x1a, 0x1a
/* 80077600 000741E0  98 1E 0D CC */	stb r0, 0xdcc(r30)
/* 80077604 000741E4  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 80077608 000741E8  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007760C 000741EC  41 82 00 14 */	beq lbl_80077620
/* 80077610 000741F0  88 1E 0D CC */	lbz r0, 0xdcc(r30)
/* 80077614 000741F4  38 60 00 01 */	li r3, 1
/* 80077618 000741F8  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8007761C 000741FC  98 1E 0D CC */	stb r0, 0xdcc(r30)
lbl_80077620:
/* 80077620 00074200  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077624 00074204  C0 3E 00 40 */	lfs f1, 0x40(r30)
/* 80077628 00074208  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8007762C 0007420C  41 82 00 20 */	beq lbl_8007764C
/* 80077630 00074210  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077634 00074214  40 81 00 0C */	ble lbl_80077640
/* 80077638 00074218  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 8007763C 0007421C  48 00 00 08 */	b lbl_80077644
lbl_80077640:
/* 80077640 00074220  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80077644:
/* 80077644 00074224  D0 1F 1A 2C */	stfs f0, 0x1a2c(r31)
/* 80077648 00074228  48 00 00 24 */	b lbl_8007766C
lbl_8007764C:
/* 8007764C 0007422C  C0 3E 00 4C */	lfs f1, 0x4c(r30)
/* 80077650 00074230  C0 1F 00 B0 */	lfs f0, 0xb0(r31)
/* 80077654 00074234  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077658 00074238  40 81 00 0C */	ble lbl_80077664
/* 8007765C 0007423C  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077660 00074240  48 00 00 08 */	b lbl_80077668
lbl_80077664:
/* 80077664 00074244  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80077668:
/* 80077668 00074248  D0 1F 1A 2C */	stfs f0, 0x1a2c(r31)
lbl_8007766C:
/* 8007766C 0007424C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80077670 00074250  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80077674 00074254  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80077678 00074258  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8007767C 0007425C  38 21 00 38 */	addi r1, r1, 0x38
/* 80077680 00074260  7C 08 03 A6 */	mtlr r0
/* 80077684 00074264  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
