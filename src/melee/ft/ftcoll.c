#include <melee/ft/ftcoll.h>

#include <common_structs.h>
#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>
#include <math.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/gr/stage.h>
#include <melee/it/code_80266F3C.h>
#include <melee/it/item.h>
#include <melee/pl/pl_unknown_001.h>
#include <melee/pl/player.h>
#include <MSL/trigf.h>
#include <Runtime/platform.h>
#include <Runtime/runtime.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

f32 const lbl_804D82E0 = 0.0F;
f32 const lbl_804D82E4 = 500.0F;
f32 const lbl_804D82E8 = 0.5F;
f32 const lbl_804D82EC = 1.0F;
f32 const lbl_804D82F0 = -1.0F;
f64 const lbl_804D82F8 = 4503601774854144.0;

/// Combo Count Logic
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID)
{
    HSD_GObj* temp_GObj;
    Fighter* fp;

    if (attacker != victim) {
        fp = GET_FIGHTER(attacker);
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

/// Combo Count Logic + Get Attack ID
void func_80076444(HSD_GObj* attacker, HSD_GObj* victim)
{
    Fighter* fp = GET_FIGHTER(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

/// Combo Count Logic w/ Item Owner
void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim)
{
    HSD_GObj* owner = func_8026BC78(attackItem);
    enum_t asid = func_8026BC84(attackItem);

    if (func_80086960(owner))
        func_800763C0(owner, victim, asid);
}

/// Check to end combo for victim
void func_800764DC(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER adds an instruction
    Fighter* fp1 = gobj->user_data;

    if (fp1->x2098 != 0)
        fp1->x2098--;

    if (fp1->x2094 != NULL) {
        Fighter* fp2 = fp1->x2094->user_data;

        if (!fp2->x221C_flag.bits.b6 && fp2->x2098 == 0)
            fp1->x2094 = NULL;
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

/// Combo count something + adjust TopN
void func_80076528(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    u16 temp_r3 = fp->x2092;

    if (temp_r3 != 0) {
        fp->x2092 = (u16) (temp_r3 - 1);
        if ((fp->x1A58_interactedFighter == NULL) &&
            (fp->xE0_ground_or_air == GA_Ground))
        {
            comboCount_Push(fp);
        }
    }
}

/// Clear victim pointer from attacker upon freeing memory?
void func_800765AC(HSD_GObj* victim)
{
    HSD_GObj* cur = lbl_804D782C->x20_fighters;

    while (cur != NULL) {
        Fighter* fp = GET_FIGHTER(cur);

        if (victim == fp->x2094)
            fp->x2094 = NULL;

        cur = cur->next;
    }
}

extern unk_t lbl_804D6558;
extern unk_t lbl_804D655C;

/// Reset hitbox and phantom collision count?
void func_800765E0(void)
{
    lbl_804D6558 = NULL;
    lbl_804D655C = NULL;
}

f32 func_800765F0(Fighter* fp, HSD_GObj* victim, f32 arg2)
{
    HSD_GObj* cur = fp->x1A58_interactedFighter;

    if (cur != NULL && !fp->x221B_flag.bits.b5 && cur != victim)
        arg2 *= p_ftCommonData->x128;

    if (fp->action_id == ASID_DAMAGEICE)
        arg2 *= p_ftCommonData->x714;

    return arg2 * fp->dmg.x182c_behavior;
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
/* 800766B8 00073298  C0 02 89 00 */	lfs f0, lbl_804D82E0
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
/* 800766EC 000732CC  C0 02 89 04 */	lfs f0, lbl_804D82E4
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
/* 80076770 00073350  80 0D AE B8 */	lwz r0, lbl_804D6558
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
/* 800767C0 000733A0  80 6D AE B8 */	lwz r3, lbl_804D6558
/* 800767C4 000733A4  38 03 00 01 */	addi r0, r3, 1
/* 800767C8 000733A8  90 0D AE B8 */	stw r0, lbl_804D6558
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
{
    // clang-format off
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

extern f32 const lbl_804D8300;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80077688(void)
{ // clang-format off
    nofralloc
/* 80077688 00074268  7C 08 02 A6 */	mflr r0
/* 8007768C 0007426C  90 01 00 04 */	stw r0, 4(r1)
/* 80077690 00074270  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80077694 00074274  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 80077698 00074278  FF E0 08 90 */	fmr f31, f1
/* 8007769C 0007427C  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 800776A0 00074280  7C 9C 23 78 */	mr r28, r4
/* 800776A4 00074284  3B 63 00 00 */	addi r27, r3, 0
/* 800776A8 00074288  3B A5 00 00 */	addi r29, r5, 0
/* 800776AC 0007428C  3B C6 00 00 */	addi r30, r6, 0
/* 800776B0 00074290  88 04 00 41 */	lbz r0, 0x41(r4)
/* 800776B4 00074294  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800776B8 00074298  41 82 00 0C */	beq lbl_800776C4
/* 800776BC 0007429C  38 A0 00 02 */	li r5, 2
/* 800776C0 000742A0  48 00 00 08 */	b lbl_800776C8
lbl_800776C4:
/* 800776C4 000742A4  38 A0 00 01 */	li r5, 1
lbl_800776C8:
/* 800776C8 000742A8  38 7B 00 00 */	addi r3, r27, 0
/* 800776CC 000742AC  38 9C 00 00 */	addi r4, r28, 0
/* 800776D0 000742B0  38 DD 00 00 */	addi r6, r29, 0
/* 800776D4 000742B4  38 E0 00 00 */	li r7, 0
/* 800776D8 000742B8  48 1F 83 ED */	bl func_8026FAC4
/* 800776DC 000742BC  C0 3C 00 0C */	lfs f1, 0xc(r28)
/* 800776E0 000742C0  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800776E4 000742C4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 800776E8 000742C8  41 82 00 2C */	beq lbl_80077714
/* 800776EC 000742CC  FC 00 08 1E */	fctiwz f0, f1
/* 800776F0 000742D0  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 800776F4 000742D4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800776F8 000742D8  2C 00 00 00 */	cmpwi r0, 0
/* 800776FC 000742DC  41 82 00 10 */	beq lbl_8007770C
/* 80077700 000742E0  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80077704 000742E4  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80077708 000742E8  48 00 00 10 */	b lbl_80077718
lbl_8007770C:
/* 8007770C 000742EC  3B E0 00 01 */	li r31, 1
/* 80077710 000742F0  48 00 00 08 */	b lbl_80077718
lbl_80077714:
/* 80077714 000742F4  3B E0 00 00 */	li r31, 0
lbl_80077718:
/* 80077718 000742F8  80 1B 0C 34 */	lwz r0, 0xc34(r27)
/* 8007771C 000742FC  7C 1F 00 00 */	cmpw r31, r0
/* 80077720 00074300  40 81 01 64 */	ble lbl_80077884
/* 80077724 00074304  93 FB 0C 50 */	stw r31, 0xc50(r27)
/* 80077728 00074308  88 1D 22 1B */	lbz r0, 0x221b(r29)
/* 8007772C 0007430C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80077730 00074310  40 82 00 18 */	bne lbl_80077748
/* 80077734 00074314  88 7C 00 42 */	lbz r3, 0x42(r28)
/* 80077738 00074318  88 1B 0D CE */	lbz r0, 0xdce(r27)
/* 8007773C 0007431C  50 60 F7 7A */	rlwimi r0, r3, 0x1e, 0x1d, 0x1d
/* 80077740 00074320  98 1B 0D CE */	stb r0, 0xdce(r27)
/* 80077744 00074324  48 00 00 14 */	b lbl_80077758
lbl_80077748:
/* 80077748 00074328  88 1B 0D CE */	lbz r0, 0xdce(r27)
/* 8007774C 0007432C  38 60 00 00 */	li r3, 0
/* 80077750 00074330  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 80077754 00074334  98 1B 0D CE */	stb r0, 0xdce(r27)
lbl_80077758:
/* 80077758 00074338  80 1D 00 00 */	lwz r0, 0(r29)
/* 8007775C 0007433C  90 1B 0C F4 */	stw r0, 0xcf4(r27)
/* 80077760 00074340  C0 5B 00 40 */	lfs f2, 0x40(r27)
/* 80077764 00074344  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077768 00074348  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8007776C 0007434C  40 80 00 0C */	bge lbl_80077778
/* 80077770 00074350  FC 20 10 50 */	fneg f1, f2
/* 80077774 00074354  48 00 00 08 */	b lbl_8007777C
lbl_80077778:
/* 80077778 00074358  FC 20 10 90 */	fmr f1, f2
lbl_8007777C:
/* 8007777C 0007435C  80 6D B6 88 */	lwz r3, lbl_804D6D28
/* 80077780 00074360  C0 03 00 D4 */	lfs f0, 0xd4(r3)
/* 80077784 00074364  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077788 00074368  40 80 00 24 */	bge lbl_800777AC
/* 8007778C 0007436C  C0 3B 00 4C */	lfs f1, 0x4c(r27)
/* 80077790 00074370  C0 1D 00 B0 */	lfs f0, 0xb0(r29)
/* 80077794 00074374  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077798 00074378  40 81 00 0C */	ble lbl_800777A4
/* 8007779C 0007437C  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 800777A0 00074380  48 00 00 24 */	b lbl_800777C4
lbl_800777A4:
/* 800777A4 00074384  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 800777A8 00074388  48 00 00 1C */	b lbl_800777C4
lbl_800777AC:
/* 800777AC 0007438C  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800777B0 00074390  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800777B4 00074394  40 80 00 0C */	bge lbl_800777C0
/* 800777B8 00074398  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 800777BC 0007439C  48 00 00 08 */	b lbl_800777C4
lbl_800777C0:
/* 800777C0 000743A0  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_800777C4:
/* 800777C4 000743A4  D0 1B 0C B8 */	stfs f0, 0xcb8(r27)
/* 800777C8 000743A8  88 1B 0D CE */	lbz r0, 0xdce(r27)
/* 800777CC 000743AC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800777D0 000743B0  41 82 00 A0 */	beq lbl_80077870
/* 800777D4 000743B4  88 1D 22 1B */	lbz r0, 0x221b(r29)
/* 800777D8 000743B8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 800777DC 000743BC  41 82 00 78 */	beq lbl_80077854
/* 800777E0 000743C0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800777E4 000743C4  C0 42 89 20 */	lfs f2, lbl_804D8300
/* 800777E8 000743C8  C0 23 02 D0 */	lfs f1, 0x2d0(r3)
/* 800777EC 000743CC  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800777F0 000743D0  EF E2 00 72 */	fmuls f31, f2, f1
/* 800777F4 000743D4  D0 1B 0C 54 */	stfs f0, 0xc54(r27)
/* 800777F8 000743D8  FC 20 F8 90 */	fmr f1, f31
/* 800777FC 000743DC  48 2A EA 45 */	bl cosf
/* 80077800 000743E0  FC 00 08 90 */	fmr f0, f1
/* 80077804 000743E4  FC 20 F8 90 */	fmr f1, f31
/* 80077808 000743E8  FF E0 00 90 */	fmr f31, f0
/* 8007780C 000743EC  48 2A EB C9 */	bl sinf
/* 80077810 000743F0  C0 5E 00 00 */	lfs f2, 0(r30)
/* 80077814 000743F4  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077818 000743F8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8007781C 000743FC  4C 41 13 82 */	cror 2, 1, 2
/* 80077820 00074400  40 82 00 0C */	bne lbl_8007782C
/* 80077824 00074404  FC 00 F8 90 */	fmr f0, f31
/* 80077828 00074408  48 00 00 08 */	b lbl_80077830
lbl_8007782C:
/* 8007782C 0007440C  FC 00 F8 50 */	fneg f0, f31
lbl_80077830:
/* 80077830 00074410  D0 1B 0C 58 */	stfs f0, 0xc58(r27)
/* 80077834 00074414  38 60 00 01 */	li r3, 1
/* 80077838 00074418  D0 3B 0C 5C */	stfs f1, 0xc5c(r27)
/* 8007783C 0007441C  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077840 00074420  D0 1B 0C 60 */	stfs f0, 0xc60(r27)
/* 80077844 00074424  88 1B 0D CE */	lbz r0, 0xdce(r27)
/* 80077848 00074428  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8007784C 0007442C  98 1B 0D CE */	stb r0, 0xdce(r27)
/* 80077850 00074430  48 00 00 20 */	b lbl_80077870
lbl_80077854:
/* 80077854 00074434  D3 FB 0C 54 */	stfs f31, 0xc54(r27)
/* 80077858 00074438  80 7E 00 00 */	lwz r3, 0(r30)
/* 8007785C 0007443C  80 1E 00 04 */	lwz r0, 4(r30)
/* 80077860 00074440  90 7B 0C 58 */	stw r3, 0xc58(r27)
/* 80077864 00074444  90 1B 0C 5C */	stw r0, 0xc5c(r27)
/* 80077868 00074448  80 1E 00 08 */	lwz r0, 8(r30)
/* 8007786C 0007444C  90 1B 0C 60 */	stw r0, 0xc60(r27)
lbl_80077870:
/* 80077870 00074450  C0 3D 19 B8 */	lfs f1, 0x19b8(r29)
/* 80077874 00074454  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077878 00074458  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8007787C 0007445C  41 82 00 08 */	beq lbl_80077884
/* 80077880 00074460  D0 3B 0C C0 */	stfs f1, 0xcc0(r27)
lbl_80077884:
/* 80077884 00074464  80 1C 00 34 */	lwz r0, 0x34(r28)
/* 80077888 00074468  7C 1F 02 15 */	add. r0, r31, r0
/* 8007788C 0007446C  40 80 00 0C */	bge lbl_80077898
/* 80077890 00074470  38 60 00 00 */	li r3, 0
/* 80077894 00074474  48 00 00 08 */	b lbl_8007789C
lbl_80077898:
/* 80077898 00074478  7C 03 03 78 */	mr r3, r0
lbl_8007789C:
/* 8007789C 0007447C  80 1D 19 A0 */	lwz r0, 0x19a0(r29)
/* 800778A0 00074480  7C 00 1A 14 */	add r0, r0, r3
/* 800778A4 00074484  90 1D 19 A0 */	stw r0, 0x19a0(r29)
/* 800778A8 00074488  80 7B 05 18 */	lwz r3, 0x518(r27)
/* 800778AC 0007448C  48 00 F0 B5 */	bl func_80086960
/* 800778B0 00074490  2C 03 00 00 */	cmpwi r3, 0
/* 800778B4 00074494  41 82 00 28 */	beq lbl_800778DC
/* 800778B8 00074498  80 7B 05 18 */	lwz r3, 0x518(r27)
/* 800778BC 0007449C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800778C0 000744A0  88 03 00 0C */	lbz r0, 0xc(r3)
/* 800778C4 000744A4  90 1D 19 BC */	stw r0, 0x19bc(r29)
/* 800778C8 000744A8  88 63 22 1F */	lbz r3, 0x221f(r3)
/* 800778CC 000744AC  88 1D 22 1F */	lbz r0, 0x221f(r29)
/* 800778D0 000744B0  50 60 F7 BC */	rlwimi r0, r3, 0x1e, 0x1e, 0x1e
/* 800778D4 000744B4  98 1D 22 1F */	stb r0, 0x221f(r29)
/* 800778D8 000744B8  48 00 00 0C */	b lbl_800778E4
lbl_800778DC:
/* 800778DC 000744BC  38 00 00 06 */	li r0, 6
/* 800778E0 000744C0  90 1D 19 BC */	stw r0, 0x19bc(r29)
lbl_800778E4:
/* 800778E4 000744C4  80 1D 19 A4 */	lwz r0, 0x19a4(r29)
/* 800778E8 000744C8  7C 1F 00 00 */	cmpw r31, r0
/* 800778EC 000744CC  40 81 00 38 */	ble lbl_80077924
/* 800778F0 000744D0  93 FD 19 A4 */	stw r31, 0x19a4(r29)
/* 800778F4 000744D4  C0 3D 00 B0 */	lfs f1, 0xb0(r29)
/* 800778F8 000744D8  C0 1B 00 4C */	lfs f0, 0x4c(r27)
/* 800778FC 000744DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077900 000744E0  40 81 00 0C */	ble lbl_8007790C
/* 80077904 000744E4  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077908 000744E8  48 00 00 08 */	b lbl_80077910
lbl_8007790C:
/* 8007790C 000744EC  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80077910:
/* 80077910 000744F0  D0 1D 19 AC */	stfs f0, 0x19ac(r29)
/* 80077914 000744F4  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 80077918 000744F8  90 1D 19 B0 */	stw r0, 0x19b0(r29)
/* 8007791C 000744FC  80 1B 00 04 */	lwz r0, 4(r27)
/* 80077920 00074500  90 1D 19 A8 */	stw r0, 0x19a8(r29)
lbl_80077924:
/* 80077924 00074504  C0 3D 19 B8 */	lfs f1, 0x19b8(r29)
/* 80077928 00074508  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007792C 0007450C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80077930 00074510  41 82 00 14 */	beq lbl_80077944
/* 80077934 00074514  88 1C 00 42 */	lbz r0, 0x42(r28)
/* 80077938 00074518  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007793C 0007451C  41 82 00 08 */	beq lbl_80077944
/* 80077940 00074520  D0 3D 19 64 */	stfs f1, 0x1964(r29)
lbl_80077944:
/* 80077944 00074524  38 BC 00 64 */	addi r5, r28, 0x64
/* 80077948 00074528  4C C6 31 82 */	crclr 6
/* 8007794C 0007452C  38 60 04 1C */	li r3, 0x41c
/* 80077950 00074530  38 80 00 00 */	li r4, 0
/* 80077954 00074534  4B FE 84 89 */	bl ef_Spawn
/* 80077958 00074538  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 8007795C 0007453C  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80077960 00074540  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 80077964 00074544  38 21 00 60 */	addi r1, r1, 0x60
/* 80077968 00074548  7C 08 03 A6 */	mtlr r0
/* 8007796C 0007454C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80077970(void)
{ // clang-format off
    nofralloc
/* 80077970 00074550  7C 08 02 A6 */	mflr r0
/* 80077974 00074554  90 01 00 04 */	stw r0, 4(r1)
/* 80077978 00074558  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 8007797C 0007455C  BE E1 00 54 */	stmw r23, 0x54(r1)
/* 80077980 00074560  7C 7C 1B 78 */	mr r28, r3
/* 80077984 00074564  7C 9D 23 78 */	mr r29, r4
/* 80077988 00074568  7C DF 33 78 */	mr r31, r6
/* 8007798C 0007456C  7C BE 2B 78 */	mr r30, r5
/* 80077990 00074570  C0 24 00 64 */	lfs f1, 0x64(r4)
/* 80077994 00074574  C0 06 00 64 */	lfs f0, 0x64(r6)
/* 80077998 00074578  C0 42 89 08 */	lfs f2, lbl_804D82E8
/* 8007799C 0007457C  EC 01 00 2A */	fadds f0, f1, f0
/* 800779A0 00074580  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800779A4 00074584  EC 02 00 32 */	fmuls f0, f2, f0
/* 800779A8 00074588  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800779AC 0007458C  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 800779B0 00074590  C0 06 00 68 */	lfs f0, 0x68(r6)
/* 800779B4 00074594  EC 01 00 2A */	fadds f0, f1, f0
/* 800779B8 00074598  EC 02 00 32 */	fmuls f0, f2, f0
/* 800779BC 0007459C  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800779C0 000745A0  C0 24 00 6C */	lfs f1, 0x6c(r4)
/* 800779C4 000745A4  C0 06 00 6C */	lfs f0, 0x6c(r6)
/* 800779C8 000745A8  EC 01 00 2A */	fadds f0, f1, f0
/* 800779CC 000745AC  EC 02 00 32 */	fmuls f0, f2, f0
/* 800779D0 000745B0  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800779D4 000745B4  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 800779D8 000745B8  C0 46 00 0C */	lfs f2, 0xc(r6)
/* 800779DC 000745BC  FC 00 00 1E */	fctiwz f0, f0
/* 800779E0 000745C0  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 800779E4 000745C4  FC 20 10 1E */	fctiwz f1, f2
/* 800779E8 000745C8  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 800779EC 000745CC  D8 21 00 48 */	stfd f1, 0x48(r1)
/* 800779F0 000745D0  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800779F4 000745D4  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 800779F8 000745D8  7C 64 18 50 */	subf r3, r4, r3
/* 800779FC 000745DC  7C 03 00 00 */	cmpw r3, r0
/* 80077A00 000745E0  40 80 01 24 */	bge lbl_80077B24
/* 80077A04 000745E4  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077A08 000745E8  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 80077A0C 000745EC  41 82 00 28 */	beq lbl_80077A34
/* 80077A10 000745F0  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80077A14 000745F4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80077A18 000745F8  2C 00 00 00 */	cmpwi r0, 0
/* 80077A1C 000745FC  41 82 00 10 */	beq lbl_80077A2C
/* 80077A20 00074600  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80077A24 00074604  83 21 00 44 */	lwz r25, 0x44(r1)
/* 80077A28 00074608  48 00 00 10 */	b lbl_80077A38
lbl_80077A2C:
/* 80077A2C 0007460C  3B 20 00 01 */	li r25, 1
/* 80077A30 00074610  48 00 00 08 */	b lbl_80077A38
lbl_80077A34:
/* 80077A34 00074614  3B 20 00 00 */	li r25, 0
lbl_80077A38:
/* 80077A38 00074618  3B 40 00 00 */	li r26, 0
/* 80077A3C 0007461C  3B 1E 00 00 */	addi r24, r30, 0
/* 80077A40 00074620  3B 7A 00 00 */	addi r27, r26, 0
/* 80077A44 00074624  3A ED AE C0 */	addi r23, r13, lbl_804D6560
lbl_80077A48:
/* 80077A48 00074628  80 18 09 14 */	lwz r0, 0x914(r24)
/* 80077A4C 0007462C  38 78 09 14 */	addi r3, r24, 0x914
/* 80077A50 00074630  2C 00 00 00 */	cmpwi r0, 0
/* 80077A54 00074634  41 82 00 2C */	beq lbl_80077A80
/* 80077A58 00074638  80 83 00 04 */	lwz r4, 4(r3)
/* 80077A5C 0007463C  80 1F 00 04 */	lwz r0, 4(r31)
/* 80077A60 00074640  7C 04 00 40 */	cmplw r4, r0
/* 80077A64 00074644  40 82 00 1C */	bne lbl_80077A80
/* 80077A68 00074648  38 BC 00 00 */	addi r5, r28, 0
/* 80077A6C 0007464C  38 80 00 03 */	li r4, 3
/* 80077A70 00074650  4B F9 0C 19 */	bl func_80008688
/* 80077A74 00074654  2C 03 00 00 */	cmpwi r3, 0
/* 80077A78 00074658  41 82 00 08 */	beq lbl_80077A80
/* 80077A7C 0007465C  9B 77 00 00 */	stb r27, 0(r23)
lbl_80077A80:
/* 80077A80 00074660  3B 5A 00 01 */	addi r26, r26, 1
/* 80077A84 00074664  28 1A 00 04 */	cmplwi r26, 4
/* 80077A88 00074668  3B 18 01 38 */	addi r24, r24, 0x138
/* 80077A8C 0007466C  3A F7 00 01 */	addi r23, r23, 1
/* 80077A90 00074670  41 80 FF B8 */	blt lbl_80077A48
/* 80077A94 00074674  80 1E 19 18 */	lwz r0, 0x1918(r30)
/* 80077A98 00074678  7C 19 00 00 */	cmpw r25, r0
/* 80077A9C 0007467C  40 81 00 74 */	ble lbl_80077B10
/* 80077AA0 00074680  93 3E 19 18 */	stw r25, 0x1918(r30)
/* 80077AA4 00074684  88 1F 00 40 */	lbz r0, 0x40(r31)
/* 80077AA8 00074688  54 00 D7 FE */	rlwinm r0, r0, 0x1a, 0x1f, 0x1f
/* 80077AAC 0007468C  28 00 00 01 */	cmplwi r0, 1
/* 80077AB0 00074690  40 82 00 60 */	bne lbl_80077B10
/* 80077AB4 00074694  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80077AB8 00074698  2C 00 00 00 */	cmpwi r0, 0
/* 80077ABC 0007469C  40 82 00 54 */	bne lbl_80077B10
/* 80077AC0 000746A0  6F 20 80 00 */	xoris r0, r25, 0x8000
/* 80077AC4 000746A4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80077AC8 000746A8  90 01 00 44 */	stw r0, 0x44(r1)
/* 80077ACC 000746AC  3C 00 43 30 */	lis r0, 0x4330
/* 80077AD0 000746B0  C8 62 89 18 */	lfd f3, lbl_804D82F8
/* 80077AD4 000746B4  90 01 00 40 */	stw r0, 0x40(r1)
/* 80077AD8 000746B8  C0 23 03 D0 */	lfs f1, 0x3d0(r3)
/* 80077ADC 000746BC  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 80077AE0 000746C0  C0 03 03 D4 */	lfs f0, 0x3d4(r3)
/* 80077AE4 000746C4  EC 42 18 28 */	fsubs f2, f2, f3
/* 80077AE8 000746C8  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80077AEC 000746CC  D0 1E 19 1C */	stfs f0, 0x191c(r30)
/* 80077AF0 000746D0  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 80077AF4 000746D4  C0 1C 00 4C */	lfs f0, 0x4c(r28)
/* 80077AF8 000746D8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077AFC 000746DC  40 80 00 0C */	bge lbl_80077B08
/* 80077B00 000746E0  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80077B04 000746E4  48 00 00 08 */	b lbl_80077B0C
lbl_80077B08:
/* 80077B08 000746E8  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_80077B0C:
/* 80077B0C 000746EC  D0 1E 19 20 */	stfs f0, 0x1920(r30)
lbl_80077B10:
/* 80077B10 000746F0  38 A1 00 30 */	addi r5, r1, 0x30
/* 80077B14 000746F4  4C C6 31 82 */	crclr 6
/* 80077B18 000746F8  38 60 04 1C */	li r3, 0x41c
/* 80077B1C 000746FC  38 80 00 00 */	li r4, 0
/* 80077B20 00074700  4B FE 82 BD */	bl ef_Spawn
lbl_80077B24:
/* 80077B24 00074704  C0 5D 00 0C */	lfs f2, 0xc(r29)
/* 80077B28 00074708  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 80077B2C 0007470C  FC 20 10 1E */	fctiwz f1, f2
/* 80077B30 00074710  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80077B34 00074714  FC 00 00 1E */	fctiwz f0, f0
/* 80077B38 00074718  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 80077B3C 0007471C  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80077B40 00074720  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80077B44 00074724  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80077B48 00074728  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80077B4C 0007472C  7C 64 18 50 */	subf r3, r4, r3
/* 80077B50 00074730  7C 03 00 00 */	cmpw r3, r0
/* 80077B54 00074734  40 80 00 F8 */	bge lbl_80077C4C
/* 80077B58 00074738  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077B5C 0007473C  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 80077B60 00074740  41 82 00 28 */	beq lbl_80077B88
/* 80077B64 00074744  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80077B68 00074748  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80077B6C 0007474C  2C 00 00 00 */	cmpwi r0, 0
/* 80077B70 00074750  41 82 00 10 */	beq lbl_80077B80
/* 80077B74 00074754  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80077B78 00074758  83 21 00 44 */	lwz r25, 0x44(r1)
/* 80077B7C 0007475C  48 00 00 10 */	b lbl_80077B8C
lbl_80077B80:
/* 80077B80 00074760  3B 20 00 01 */	li r25, 1
/* 80077B84 00074764  48 00 00 08 */	b lbl_80077B8C
lbl_80077B88:
/* 80077B88 00074768  3B 20 00 00 */	li r25, 0
lbl_80077B8C:
/* 80077B8C 0007476C  88 1D 00 41 */	lbz r0, 0x41(r29)
/* 80077B90 00074770  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80077B94 00074774  41 82 00 0C */	beq lbl_80077BA0
/* 80077B98 00074778  38 A0 00 04 */	li r5, 4
/* 80077B9C 0007477C  48 00 00 08 */	b lbl_80077BA4
lbl_80077BA0:
/* 80077BA0 00074780  38 A0 00 03 */	li r5, 3
lbl_80077BA4:
/* 80077BA4 00074784  38 7C 00 00 */	addi r3, r28, 0
/* 80077BA8 00074788  38 9D 00 00 */	addi r4, r29, 0
/* 80077BAC 0007478C  38 DE 00 00 */	addi r6, r30, 0
/* 80077BB0 00074790  38 E0 00 00 */	li r7, 0
/* 80077BB4 00074794  48 1F 7F 11 */	bl func_8026FAC4
/* 80077BB8 00074798  80 1C 0C 48 */	lwz r0, 0xc48(r28)
/* 80077BBC 0007479C  7C 19 00 00 */	cmpw r25, r0
/* 80077BC0 000747A0  40 81 00 78 */	ble lbl_80077C38
/* 80077BC4 000747A4  80 1E 00 00 */	lwz r0, 0(r30)
/* 80077BC8 000747A8  90 1C 0C F4 */	stw r0, 0xcf4(r28)
/* 80077BCC 000747AC  93 3C 0C 48 */	stw r25, 0xc48(r28)
/* 80077BD0 000747B0  C0 5C 00 40 */	lfs f2, 0x40(r28)
/* 80077BD4 000747B4  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077BD8 000747B8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80077BDC 000747BC  40 80 00 0C */	bge lbl_80077BE8
/* 80077BE0 000747C0  FC 20 10 50 */	fneg f1, f2
/* 80077BE4 000747C4  48 00 00 08 */	b lbl_80077BEC
lbl_80077BE8:
/* 80077BE8 000747C8  FC 20 10 90 */	fmr f1, f2
lbl_80077BEC:
/* 80077BEC 000747CC  80 6D B6 88 */	lwz r3, lbl_804D6D28
/* 80077BF0 000747D0  C0 03 00 D4 */	lfs f0, 0xd4(r3)
/* 80077BF4 000747D4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077BF8 000747D8  40 80 00 24 */	bge lbl_80077C1C
/* 80077BFC 000747DC  C0 3C 00 4C */	lfs f1, 0x4c(r28)
/* 80077C00 000747E0  C0 1E 00 B0 */	lfs f0, 0xb0(r30)
/* 80077C04 000747E4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077C08 000747E8  40 81 00 0C */	ble lbl_80077C14
/* 80077C0C 000747EC  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077C10 000747F0  48 00 00 24 */	b lbl_80077C34
lbl_80077C14:
/* 80077C14 000747F4  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80077C18 000747F8  48 00 00 1C */	b lbl_80077C34
lbl_80077C1C:
/* 80077C1C 000747FC  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077C20 00074800  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80077C24 00074804  40 80 00 0C */	bge lbl_80077C30
/* 80077C28 00074808  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80077C2C 0007480C  48 00 00 08 */	b lbl_80077C34
lbl_80077C30:
/* 80077C30 00074810  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80077C34:
/* 80077C34 00074814  D0 1C 0C B8 */	stfs f0, 0xcb8(r28)
lbl_80077C38:
/* 80077C38 00074818  38 A1 00 30 */	addi r5, r1, 0x30
/* 80077C3C 0007481C  4C C6 31 82 */	crclr 6
/* 80077C40 00074820  38 60 04 1C */	li r3, 0x41c
/* 80077C44 00074824  38 80 00 00 */	li r4, 0
/* 80077C48 00074828  4B FE 81 95 */	bl ef_Spawn
lbl_80077C4C:
/* 80077C4C 0007482C  BA E1 00 54 */	lmw r23, 0x54(r1)
/* 80077C50 00074830  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80077C54 00074834  38 21 00 78 */	addi r1, r1, 0x78
/* 80077C58 00074838  7C 08 03 A6 */	mtlr r0
/* 80077C5C 0007483C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80077C60(void)
{ // clang-format off
    nofralloc
/* 80077C60 00074840  7C 08 02 A6 */	mflr r0
/* 80077C64 00074844  3C E0 80 3C */	lis r7, lbl_803C0C40@ha
/* 80077C68 00074848  90 01 00 04 */	stw r0, 4(r1)
/* 80077C6C 0007484C  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80077C70 00074850  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 80077C74 00074854  DB C1 00 70 */	stfd f30, 0x70(r1)
/* 80077C78 00074858  BF 21 00 54 */	stmw r25, 0x54(r1)
/* 80077C7C 0007485C  7C 7A 1B 78 */	mr r26, r3
/* 80077C80 00074860  3B 64 00 00 */	addi r27, r4, 0
/* 80077C84 00074864  3B 85 00 00 */	addi r28, r5, 0
/* 80077C88 00074868  3B A6 00 00 */	addi r29, r6, 0
/* 80077C8C 0007486C  3B E7 0C 40 */	addi r31, r7, lbl_803C0C40@l
/* 80077C90 00074870  80 63 00 CC */	lwz r3, 0xcc(r3)
/* 80077C94 00074874  88 03 00 00 */	lbz r0, 0(r3)
/* 80077C98 00074878  54 00 EF 3E */	rlwinm r0, r0, 0x1d, 0x1c, 0x1f
/* 80077C9C 0007487C  28 00 00 04 */	cmplwi r0, 4
/* 80077CA0 00074880  40 82 01 08 */	bne lbl_80077DA8
/* 80077CA4 00074884  88 1B 00 41 */	lbz r0, 0x41(r27)
/* 80077CA8 00074888  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80077CAC 0007488C  41 82 00 0C */	beq lbl_80077CB8
/* 80077CB0 00074890  38 A0 00 05 */	li r5, 5
/* 80077CB4 00074894  48 00 00 08 */	b lbl_80077CBC
lbl_80077CB8:
/* 80077CB8 00074898  38 A0 00 00 */	li r5, 0
lbl_80077CBC:
/* 80077CBC 0007489C  38 7A 00 00 */	addi r3, r26, 0
/* 80077CC0 000748A0  38 9B 00 00 */	addi r4, r27, 0
/* 80077CC4 000748A4  38 DC 00 00 */	addi r6, r28, 0
/* 80077CC8 000748A8  38 E0 00 00 */	li r7, 0
/* 80077CCC 000748AC  48 1F 7D F9 */	bl func_8026FAC4
/* 80077CD0 000748B0  88 1C 22 24 */	lbz r0, 0x2224(r28)
/* 80077CD4 000748B4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80077CD8 000748B8  40 82 00 C8 */	bne lbl_80077DA0
/* 80077CDC 000748BC  80 1A 00 10 */	lwz r0, 0x10(r26)
/* 80077CE0 000748C0  2C 00 00 1A */	cmpwi r0, 0x1a
/* 80077CE4 000748C4  41 82 00 6C */	beq lbl_80077D50
/* 80077CE8 000748C8  40 80 00 10 */	bge lbl_80077CF8
/* 80077CEC 000748CC  2C 00 00 0A */	cmpwi r0, 0xa
/* 80077CF0 000748D0  41 82 00 14 */	beq lbl_80077D04
/* 80077CF4 000748D4  48 00 00 98 */	b lbl_80077D8C
lbl_80077CF8:
/* 80077CF8 000748D8  2C 00 00 1C */	cmpwi r0, 0x1c
/* 80077CFC 000748DC  40 80 00 90 */	bge lbl_80077D8C
/* 80077D00 000748E0  48 00 00 70 */	b lbl_80077D70
lbl_80077D04:
/* 80077D04 000748E4  38 00 00 00 */	li r0, 0
/* 80077D08 000748E8  90 1B 00 00 */	stw r0, 0(r27)
/* 80077D0C 000748EC  38 00 00 01 */	li r0, 1
/* 80077D10 000748F0  38 7A 00 00 */	addi r3, r26, 0
/* 80077D14 000748F4  90 1A 0C 34 */	stw r0, 0xc34(r26)
/* 80077D18 000748F8  48 1F AB 01 */	bl func_80272818
/* 80077D1C 000748FC  38 83 00 00 */	addi r4, r3, 0
/* 80077D20 00074900  38 7C 00 00 */	addi r3, r28, 0
/* 80077D24 00074904  48 00 3A D9 */	bl func_8007B7FC
/* 80077D28 00074908  38 7C 00 00 */	addi r3, r28, 0
/* 80077D2C 0007490C  38 80 00 F9 */	li r4, 0xf9
/* 80077D30 00074910  38 A0 00 7F */	li r5, 0x7f
/* 80077D34 00074914  38 C0 00 40 */	li r6, 0x40
/* 80077D38 00074918  48 01 04 11 */	bl func_80088148
/* 80077D3C 0007491C  38 7C 00 00 */	addi r3, r28, 0
/* 80077D40 00074920  38 80 00 11 */	li r4, 0x11
/* 80077D44 00074924  38 A0 00 00 */	li r5, 0
/* 80077D48 00074928  48 00 6E 65 */	bl func_8007EBAC
/* 80077D4C 0007492C  48 00 00 40 */	b lbl_80077D8C
lbl_80077D50:
/* 80077D50 00074930  38 00 00 00 */	li r0, 0
/* 80077D54 00074934  90 1B 00 00 */	stw r0, 0(r27)
/* 80077D58 00074938  38 00 00 01 */	li r0, 1
/* 80077D5C 0007493C  80 7C 20 0C */	lwz r3, 0x200c(r28)
/* 80077D60 00074940  38 63 00 01 */	addi r3, r3, 1
/* 80077D64 00074944  90 7C 20 0C */	stw r3, 0x200c(r28)
/* 80077D68 00074948  90 1A 0C 34 */	stw r0, 0xc34(r26)
/* 80077D6C 0007494C  48 00 00 20 */	b lbl_80077D8C
lbl_80077D70:
/* 80077D70 00074950  38 00 00 00 */	li r0, 0
/* 80077D74 00074954  90 1B 00 00 */	stw r0, 0(r27)
/* 80077D78 00074958  38 00 00 01 */	li r0, 1
/* 80077D7C 0007495C  80 7C 20 10 */	lwz r3, 0x2010(r28)
/* 80077D80 00074960  38 63 00 01 */	addi r3, r3, 1
/* 80077D84 00074964  90 7C 20 10 */	stw r3, 0x2010(r28)
/* 80077D88 00074968  90 1A 0C 34 */	stw r0, 0xc34(r26)
lbl_80077D8C:
/* 80077D8C 0007496C  88 9C 22 1F */	lbz r4, 0x221f(r28)
/* 80077D90 00074970  88 7C 00 0C */	lbz r3, 0xc(r28)
/* 80077D94 00074974  80 BA 00 04 */	lwz r5, 4(r26)
/* 80077D98 00074978  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80077D9C 0007497C  4B FC 63 E1 */	bl func_8003E17C
lbl_80077DA0:
/* 80077DA0 00074980  38 60 00 00 */	li r3, 0
/* 80077DA4 00074984  48 00 05 C4 */	b lbl_80078368
lbl_80077DA8:
/* 80077DA8 00074988  80 7A 00 04 */	lwz r3, 4(r26)
/* 80077DAC 0007498C  7F 64 DB 78 */	mr r4, r27
/* 80077DB0 00074990  48 1F 34 25 */	bl func_8026B1D4
/* 80077DB4 00074994  FF C0 08 90 */	fmr f30, f1
/* 80077DB8 00074998  80 7C 1A 58 */	lwz r3, 0x1a58(r28)
/* 80077DBC 0007499C  28 03 00 00 */	cmplwi r3, 0
/* 80077DC0 000749A0  FC 60 F0 90 */	fmr f3, f30
/* 80077DC4 000749A4  41 82 00 24 */	beq lbl_80077DE8
/* 80077DC8 000749A8  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 80077DCC 000749AC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80077DD0 000749B0  40 82 00 18 */	bne lbl_80077DE8
/* 80077DD4 000749B4  28 03 00 00 */	cmplwi r3, 0
/* 80077DD8 000749B8  41 82 00 10 */	beq lbl_80077DE8
/* 80077DDC 000749BC  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80077DE0 000749C0  C0 03 01 28 */	lfs f0, 0x128(r3)
/* 80077DE4 000749C4  EC 63 00 32 */	fmuls f3, f3, f0
lbl_80077DE8:
/* 80077DE8 000749C8  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 80077DEC 000749CC  2C 00 01 45 */	cmpwi r0, 0x145
/* 80077DF0 000749D0  40 82 00 10 */	bne lbl_80077E00
/* 80077DF4 000749D4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80077DF8 000749D8  C0 03 07 14 */	lfs f0, 0x714(r3)
/* 80077DFC 000749DC  EC 63 00 32 */	fmuls f3, f3, f0
lbl_80077E00:
/* 80077E00 000749E0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80077E04 000749E4  C0 5C 18 2C */	lfs f2, 0x182c(r28)
/* 80077E08 000749E8  C0 3B 00 70 */	lfs f1, 0x70(r27)
/* 80077E0C 000749EC  C0 03 07 A8 */	lfs f0, 0x7a8(r3)
/* 80077E10 000749F0  EF E3 00 B2 */	fmuls f31, f3, f2
/* 80077E14 000749F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80077E18 000749F8  40 80 00 0C */	bge lbl_80077E24
/* 80077E1C 000749FC  38 00 00 01 */	li r0, 1
/* 80077E20 00074A00  48 00 00 08 */	b lbl_80077E28
lbl_80077E24:
/* 80077E24 00074A04  38 00 00 00 */	li r0, 0
lbl_80077E28:
/* 80077E28 00074A08  2C 00 00 00 */	cmpwi r0, 0
/* 80077E2C 00074A0C  41 82 02 84 */	beq lbl_800780B0
/* 80077E30 00074A10  80 0D AE B8 */	lwz r0, lbl_804D6558
/* 80077E34 00074A14  2C 00 00 00 */	cmpwi r0, 0
/* 80077E38 00074A18  40 82 05 2C */	bne lbl_80078364
/* 80077E3C 00074A1C  C0 3C 18 9C */	lfs f1, 0x189c(r28)
/* 80077E40 00074A20  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077E44 00074A24  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80077E48 00074A28  40 82 05 1C */	bne lbl_80078364
/* 80077E4C 00074A2C  38 00 00 02 */	li r0, 2
/* 80077E50 00074A30  7C 09 03 A6 */	mtctr r0
/* 80077E54 00074A34  38 9B 00 D4 */	addi r4, r27, 0xd4
/* 80077E58 00074A38  38 60 00 00 */	li r3, 0
lbl_80077E5C:
/* 80077E5C 00074A3C  80 04 00 00 */	lwz r0, 0(r4)
/* 80077E60 00074A40  7C 00 E0 40 */	cmplw r0, r28
/* 80077E64 00074A44  41 82 00 60 */	beq lbl_80077EC4
/* 80077E68 00074A48  84 04 00 08 */	lwzu r0, 8(r4)
/* 80077E6C 00074A4C  38 63 00 01 */	addi r3, r3, 1
/* 80077E70 00074A50  7C 00 E0 40 */	cmplw r0, r28
/* 80077E74 00074A54  41 82 00 50 */	beq lbl_80077EC4
/* 80077E78 00074A58  84 04 00 08 */	lwzu r0, 8(r4)
/* 80077E7C 00074A5C  38 63 00 01 */	addi r3, r3, 1
/* 80077E80 00074A60  7C 00 E0 40 */	cmplw r0, r28
/* 80077E84 00074A64  41 82 00 40 */	beq lbl_80077EC4
/* 80077E88 00074A68  84 04 00 08 */	lwzu r0, 8(r4)
/* 80077E8C 00074A6C  38 63 00 01 */	addi r3, r3, 1
/* 80077E90 00074A70  7C 00 E0 40 */	cmplw r0, r28
/* 80077E94 00074A74  41 82 00 30 */	beq lbl_80077EC4
/* 80077E98 00074A78  84 04 00 08 */	lwzu r0, 8(r4)
/* 80077E9C 00074A7C  38 63 00 01 */	addi r3, r3, 1
/* 80077EA0 00074A80  7C 00 E0 40 */	cmplw r0, r28
/* 80077EA4 00074A84  41 82 00 20 */	beq lbl_80077EC4
/* 80077EA8 00074A88  84 04 00 08 */	lwzu r0, 8(r4)
/* 80077EAC 00074A8C  38 63 00 01 */	addi r3, r3, 1
/* 80077EB0 00074A90  7C 00 E0 40 */	cmplw r0, r28
/* 80077EB4 00074A94  41 82 00 10 */	beq lbl_80077EC4
/* 80077EB8 00074A98  38 84 00 08 */	addi r4, r4, 8
/* 80077EBC 00074A9C  38 63 00 01 */	addi r3, r3, 1
/* 80077EC0 00074AA0  42 00 FF 9C */	bdnz lbl_80077E5C
lbl_80077EC4:
/* 80077EC4 00074AA4  28 03 00 0C */	cmplwi r3, 0xc
/* 80077EC8 00074AA8  40 82 00 0C */	bne lbl_80077ED4
/* 80077ECC 00074AAC  38 00 00 00 */	li r0, 0
/* 80077ED0 00074AB0  48 00 00 08 */	b lbl_80077ED8
lbl_80077ED4:
/* 80077ED4 00074AB4  38 00 00 01 */	li r0, 1
lbl_80077ED8:
/* 80077ED8 00074AB8  2C 00 00 00 */	cmpwi r0, 0
/* 80077EDC 00074ABC  40 82 04 88 */	bne lbl_80078364
/* 80077EE0 00074AC0  88 1B 00 41 */	lbz r0, 0x41(r27)
/* 80077EE4 00074AC4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80077EE8 00074AC8  41 82 00 0C */	beq lbl_80077EF4
/* 80077EEC 00074ACC  38 A0 00 05 */	li r5, 5
/* 80077EF0 00074AD0  48 00 00 08 */	b lbl_80077EF8
lbl_80077EF4:
/* 80077EF4 00074AD4  38 A0 00 00 */	li r5, 0
lbl_80077EF8:
/* 80077EF8 00074AD8  38 7A 00 00 */	addi r3, r26, 0
/* 80077EFC 00074ADC  38 9B 00 00 */	addi r4, r27, 0
/* 80077F00 00074AE0  38 DC 00 00 */	addi r6, r28, 0
/* 80077F04 00074AE4  48 1F 7C FD */	bl func_8026FC00
/* 80077F08 00074AE8  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 80077F0C 00074AEC  2C 00 00 00 */	cmpwi r0, 0
/* 80077F10 00074AF0  40 82 01 90 */	bne lbl_800780A0
/* 80077F14 00074AF4  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 80077F18 00074AF8  2C 00 00 00 */	cmpwi r0, 0
/* 80077F1C 00074AFC  40 82 01 84 */	bne lbl_800780A0
/* 80077F20 00074B00  88 1C 22 1D */	lbz r0, 0x221d(r28)
/* 80077F24 00074B04  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80077F28 00074B08  40 82 01 78 */	bne lbl_800780A0
/* 80077F2C 00074B0C  80 1D 00 00 */	lwz r0, 0(r29)
/* 80077F30 00074B10  2C 00 00 00 */	cmpwi r0, 0
/* 80077F34 00074B14  40 82 01 6C */	bne lbl_800780A0
/* 80077F38 00074B18  FC 00 F8 1E */	fctiwz f0, f31
/* 80077F3C 00074B1C  3C 00 43 30 */	lis r0, 0x4330
/* 80077F40 00074B20  FC 60 F0 1E */	fctiwz f3, f30
/* 80077F44 00074B24  C8 22 89 18 */	lfd f1, lbl_804D82F8
/* 80077F48 00074B28  C0 42 89 08 */	lfs f2, lbl_804D82E8
/* 80077F4C 00074B2C  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80077F50 00074B30  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 80077F54 00074B34  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80077F58 00074B38  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80077F5C 00074B3C  90 61 00 34 */	stw r3, 0x34(r1)
/* 80077F60 00074B40  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 80077F64 00074B44  90 01 00 30 */	stw r0, 0x30(r1)
/* 80077F68 00074B48  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80077F6C 00074B4C  D8 61 00 40 */	stfd f3, 0x40(r1)
/* 80077F70 00074B50  EC 00 08 28 */	fsubs f0, f0, f1
/* 80077F74 00074B54  80 81 00 44 */	lwz r4, 0x44(r1)
/* 80077F78 00074B58  EC 22 00 32 */	fmuls f1, f2, f0
/* 80077F7C 00074B5C  FC 00 08 1E */	fctiwz f0, f1
/* 80077F80 00074B60  FC 80 08 90 */	fmr f4, f1
/* 80077F84 00074B64  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 80077F88 00074B68  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80077F8C 00074B6C  2C 00 00 00 */	cmpwi r0, 0
/* 80077F90 00074B70  40 82 00 10 */	bne lbl_80077FA0
/* 80077F94 00074B74  2C 03 00 00 */	cmpwi r3, 0
/* 80077F98 00074B78  41 82 00 08 */	beq lbl_80077FA0
/* 80077F9C 00074B7C  C0 82 89 0C */	lfs f4, lbl_804D82EC
lbl_80077FA0:
/* 80077FA0 00074B80  7C 80 0E 70 */	srawi r0, r4, 1
/* 80077FA4 00074B84  C8 62 89 18 */	lfd f3, lbl_804D82F8
/* 80077FA8 00074B88  7C 00 01 94 */	addze r0, r0
/* 80077FAC 00074B8C  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80077FB0 00074B90  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 80077FB4 00074B94  90 61 00 34 */	stw r3, 0x34(r1)
/* 80077FB8 00074B98  3C 00 43 30 */	lis r0, 0x4330
/* 80077FBC 00074B9C  90 01 00 30 */	stw r0, 0x30(r1)
/* 80077FC0 00074BA0  C8 21 00 30 */	lfd f1, 0x30(r1)
/* 80077FC4 00074BA4  90 61 00 2C */	stw r3, 0x2c(r1)
/* 80077FC8 00074BA8  EC 21 18 28 */	fsubs f1, f1, f3
/* 80077FCC 00074BAC  90 01 00 28 */	stw r0, 0x28(r1)
/* 80077FD0 00074BB0  C8 41 00 28 */	lfd f2, 0x28(r1)
/* 80077FD4 00074BB4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80077FD8 00074BB8  EC 22 18 28 */	fsubs f1, f2, f3
/* 80077FDC 00074BBC  40 82 00 10 */	bne lbl_80077FEC
/* 80077FE0 00074BC0  2C 04 00 00 */	cmpwi r4, 0
/* 80077FE4 00074BC4  41 82 00 08 */	beq lbl_80077FEC
/* 80077FE8 00074BC8  C0 22 89 0C */	lfs f1, lbl_804D82EC
lbl_80077FEC:
/* 80077FEC 00074BCC  FC 00 20 1E */	fctiwz f0, f4
/* 80077FF0 00074BD0  80 1C 18 40 */	lwz r0, 0x1840(r28)
/* 80077FF4 00074BD4  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 80077FF8 00074BD8  80 61 00 34 */	lwz r3, 0x34(r1)
/* 80077FFC 00074BDC  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 80078000 00074BE0  7C 03 00 00 */	cmpw r3, r0
/* 80078004 00074BE4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80078008 00074BE8  40 81 00 08 */	ble lbl_80078010
/* 8007800C 00074BEC  90 1C 18 40 */	stw r0, 0x1840(r28)
lbl_80078010:
/* 80078010 00074BF0  80 0D AE BC */	lwz r0, lbl_804D655C
/* 80078014 00074BF4  80 DA 00 04 */	lwz r6, 4(r26)
/* 80078018 00074BF8  28 00 00 14 */	cmplwi r0, 0x14
/* 8007801C 00074BFC  80 BA 00 10 */	lwz r5, 0x10(r26)
/* 80078020 00074C00  40 80 00 60 */	bge lbl_80078080
/* 80078024 00074C04  1C 80 00 28 */	mulli r4, r0, 0x28
/* 80078028 00074C08  3C 60 80 46 */	lis r3, lbl_80459598@ha
/* 8007802C 00074C0C  38 03 95 98 */	addi r0, r3, lbl_80459598@l
/* 80078030 00074C10  7F 40 22 14 */	add r26, r0, r4
/* 80078034 00074C14  38 00 00 02 */	li r0, 2
/* 80078038 00074C18  90 1A 00 00 */	stw r0, 0(r26)
/* 8007803C 00074C1C  90 BA 00 04 */	stw r5, 4(r26)
/* 80078040 00074C20  90 DA 00 08 */	stw r6, 8(r26)
/* 80078044 00074C24  93 7A 00 0C */	stw r27, 0xc(r26)
/* 80078048 00074C28  93 BA 00 10 */	stw r29, 0x10(r26)
/* 8007804C 00074C2C  80 7B 00 64 */	lwz r3, 0x64(r27)
/* 80078050 00074C30  80 1B 00 68 */	lwz r0, 0x68(r27)
/* 80078054 00074C34  90 7A 00 14 */	stw r3, 0x14(r26)
/* 80078058 00074C38  90 1A 00 18 */	stw r0, 0x18(r26)
/* 8007805C 00074C3C  80 1B 00 6C */	lwz r0, 0x6c(r27)
/* 80078060 00074C40  90 1A 00 1C */	stw r0, 0x1c(r26)
/* 80078064 00074C44  D0 9A 00 20 */	stfs f4, 0x20(r26)
/* 80078068 00074C48  48 2A A8 59 */	bl __cvt_fp2unsigned
/* 8007806C 00074C4C  90 7A 00 24 */	stw r3, 0x24(r26)
/* 80078070 00074C50  80 6D AE BC */	lwz r3, lbl_804D655C
/* 80078074 00074C54  38 03 00 01 */	addi r0, r3, 1
/* 80078078 00074C58  90 0D AE BC */	stw r0, lbl_804D655C
/* 8007807C 00074C5C  48 00 00 24 */	b lbl_800780A0
lbl_80078080:
/* 80078080 00074C60  38 7F 00 58 */	addi r3, r31, 0x58
/* 80078084 00074C64  4C C6 31 82 */	crclr 6
/* 80078088 00074C68  38 80 00 14 */	li r4, 0x14
/* 8007808C 00074C6C  48 2C D6 1D */	bl OSReport
/* 80078090 00074C70  38 7F 00 34 */	addi r3, r31, 0x34
/* 80078094 00074C74  38 80 01 10 */	li r4, 0x110
/* 80078098 00074C78  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 8007809C 00074C7C  48 31 01 85 */	bl __assert
lbl_800780A0:
/* 800780A0 00074C80  7F 83 E3 78 */	mr r3, r28
/* 800780A4 00074C84  48 00 03 E5 */	bl func_80078488
/* 800780A8 00074C88  38 60 00 01 */	li r3, 1
/* 800780AC 00074C8C  48 00 02 BC */	b lbl_80078368
lbl_800780B0:
/* 800780B0 00074C90  38 A0 00 00 */	li r5, 0
/* 800780B4 00074C94  90 AD AE BC */	stw r5, lbl_804D655C
/* 800780B8 00074C98  3B C0 00 00 */	li r30, 0
/* 800780BC 00074C9C  88 1B 00 41 */	lbz r0, 0x41(r27)
/* 800780C0 00074CA0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800780C4 00074CA4  41 82 00 08 */	beq lbl_800780CC
/* 800780C8 00074CA8  38 A0 00 05 */	li r5, 5
lbl_800780CC:
/* 800780CC 00074CAC  38 7A 00 00 */	addi r3, r26, 0
/* 800780D0 00074CB0  38 9B 00 00 */	addi r4, r27, 0
/* 800780D4 00074CB4  38 DC 00 00 */	addi r6, r28, 0
/* 800780D8 00074CB8  38 E0 00 00 */	li r7, 0
/* 800780DC 00074CBC  48 1F 79 E9 */	bl func_8026FAC4
/* 800780E0 00074CC0  80 7A 0C 34 */	lwz r3, 0xc34(r26)
/* 800780E4 00074CC4  3C 00 43 30 */	lis r0, 0x4330
/* 800780E8 00074CC8  C8 22 89 18 */	lfd f1, lbl_804D82F8
/* 800780EC 00074CCC  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 800780F0 00074CD0  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800780F4 00074CD4  90 01 00 28 */	stw r0, 0x28(r1)
/* 800780F8 00074CD8  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800780FC 00074CDC  EC 00 08 28 */	fsubs f0, f0, f1
/* 80078100 00074CE0  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80078104 00074CE4  40 81 00 84 */	ble lbl_80078188
/* 80078108 00074CE8  FC 00 F8 1E */	fctiwz f0, f31
/* 8007810C 00074CEC  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 80078110 00074CF0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80078114 00074CF4  90 1A 0C 34 */	stw r0, 0xc34(r26)
/* 80078118 00074CF8  80 1C 00 00 */	lwz r0, 0(r28)
/* 8007811C 00074CFC  90 1A 0C F4 */	stw r0, 0xcf4(r26)
/* 80078120 00074D00  C0 5A 00 40 */	lfs f2, 0x40(r26)
/* 80078124 00074D04  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80078128 00074D08  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8007812C 00074D0C  40 80 00 0C */	bge lbl_80078138
/* 80078130 00074D10  FC 20 10 50 */	fneg f1, f2
/* 80078134 00074D14  48 00 00 08 */	b lbl_8007813C
lbl_80078138:
/* 80078138 00074D18  FC 20 10 90 */	fmr f1, f2
lbl_8007813C:
/* 8007813C 00074D1C  80 6D B6 88 */	lwz r3, lbl_804D6D28
/* 80078140 00074D20  C0 03 00 D4 */	lfs f0, 0xd4(r3)
/* 80078144 00074D24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80078148 00074D28  40 80 00 24 */	bge lbl_8007816C
/* 8007814C 00074D2C  C0 3A 00 4C */	lfs f1, 0x4c(r26)
/* 80078150 00074D30  C0 1C 00 B0 */	lfs f0, 0xb0(r28)
/* 80078154 00074D34  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80078158 00074D38  40 81 00 0C */	ble lbl_80078164
/* 8007815C 00074D3C  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 80078160 00074D40  48 00 00 24 */	b lbl_80078184
lbl_80078164:
/* 80078164 00074D44  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80078168 00074D48  48 00 00 1C */	b lbl_80078184
lbl_8007816C:
/* 8007816C 00074D4C  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80078170 00074D50  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80078174 00074D54  40 80 00 0C */	bge lbl_80078180
/* 80078178 00074D58  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 8007817C 00074D5C  48 00 00 08 */	b lbl_80078184
lbl_80078180:
/* 80078180 00074D60  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80078184:
/* 80078184 00074D64  D0 1A 0C B8 */	stfs f0, 0xcb8(r26)
lbl_80078188:
/* 80078188 00074D68  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 8007818C 00074D6C  2C 00 00 00 */	cmpwi r0, 0
/* 80078190 00074D70  40 82 01 B0 */	bne lbl_80078340
/* 80078194 00074D74  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 80078198 00074D78  2C 00 00 00 */	cmpwi r0, 0
/* 8007819C 00074D7C  40 82 01 A4 */	bne lbl_80078340
/* 800781A0 00074D80  88 1C 22 1D */	lbz r0, 0x221d(r28)
/* 800781A4 00074D84  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800781A8 00074D88  40 82 01 98 */	bne lbl_80078340
/* 800781AC 00074D8C  80 1D 00 00 */	lwz r0, 0(r29)
/* 800781B0 00074D90  2C 00 00 00 */	cmpwi r0, 0
/* 800781B4 00074D94  40 82 01 8C */	bne lbl_80078340
/* 800781B8 00074D98  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800781BC 00074D9C  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 800781C0 00074DA0  41 82 00 2C */	beq lbl_800781EC
/* 800781C4 00074DA4  FC 00 F8 1E */	fctiwz f0, f31
/* 800781C8 00074DA8  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 800781CC 00074DAC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800781D0 00074DB0  2C 00 00 00 */	cmpwi r0, 0
/* 800781D4 00074DB4  41 82 00 10 */	beq lbl_800781E4
/* 800781D8 00074DB8  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 800781DC 00074DBC  83 21 00 2C */	lwz r25, 0x2c(r1)
/* 800781E0 00074DC0  48 00 00 10 */	b lbl_800781F0
lbl_800781E4:
/* 800781E4 00074DC4  3B 20 00 01 */	li r25, 1
/* 800781E8 00074DC8  48 00 00 08 */	b lbl_800781F0
lbl_800781EC:
/* 800781EC 00074DCC  3B 20 00 00 */	li r25, 0
lbl_800781F0:
/* 800781F0 00074DD0  88 1C 22 1C */	lbz r0, 0x221c(r28)
/* 800781F4 00074DD4  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800781F8 00074DD8  41 82 00 34 */	beq lbl_8007822C
/* 800781FC 00074DDC  C0 1C 18 34 */	lfs f0, 0x1834(r28)
/* 80078200 00074DE0  EC 00 F8 28 */	fsubs f0, f0, f31
/* 80078204 00074DE4  D0 1C 18 34 */	stfs f0, 0x1834(r28)
/* 80078208 00074DE8  C0 3C 18 34 */	lfs f1, 0x1834(r28)
/* 8007820C 00074DEC  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80078210 00074DF0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80078214 00074DF4  40 80 00 18 */	bge lbl_8007822C
/* 80078218 00074DF8  88 1C 22 1C */	lbz r0, 0x221c(r28)
/* 8007821C 00074DFC  38 60 00 00 */	li r3, 0
/* 80078220 00074E00  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80078224 00074E04  FF E0 08 50 */	fneg f31, f1
/* 80078228 00074E08  98 1C 22 1C */	stb r0, 0x221c(r28)
lbl_8007822C:
/* 8007822C 00074E0C  88 1C 22 1C */	lbz r0, 0x221c(r28)
/* 80078230 00074E10  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80078234 00074E14  40 82 00 54 */	bne lbl_80078288
/* 80078238 00074E18  C0 02 89 04 */	lfs f0, lbl_804D82E4
/* 8007823C 00074E1C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80078240 00074E20  40 81 00 24 */	ble lbl_80078264
/* 80078244 00074E24  FC 20 F8 90 */	fmr f1, f31
/* 80078248 00074E28  38 7F 00 18 */	addi r3, r31, 0x18
/* 8007824C 00074E2C  4C C6 32 42 */	crset 6
/* 80078250 00074E30  48 2C D4 59 */	bl OSReport
/* 80078254 00074E34  38 7F 00 34 */	addi r3, r31, 0x34
/* 80078258 00074E38  38 80 00 B7 */	li r4, 0xb7
/* 8007825C 00074E3C  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 80078260 00074E40  48 30 FF C1 */	bl __assert
lbl_80078264:
/* 80078264 00074E44  C0 1C 18 38 */	lfs f0, 0x1838(r28)
/* 80078268 00074E48  EC 00 F8 2A */	fadds f0, f0, f31
/* 8007826C 00074E4C  D0 1C 18 38 */	stfs f0, 0x1838(r28)
/* 80078270 00074E50  80 1C 18 3C */	lwz r0, 0x183c(r28)
/* 80078274 00074E54  7C 19 00 00 */	cmpw r25, r0
/* 80078278 00074E58  40 81 00 08 */	ble lbl_80078280
/* 8007827C 00074E5C  93 3C 18 3C */	stw r25, 0x183c(r28)
lbl_80078280:
/* 80078280 00074E60  38 00 00 01 */	li r0, 1
/* 80078284 00074E64  48 00 00 08 */	b lbl_8007828C
lbl_80078288:
/* 80078288 00074E68  38 00 00 00 */	li r0, 0
lbl_8007828C:
/* 8007828C 00074E6C  2C 00 00 00 */	cmpwi r0, 0
/* 80078290 00074E70  41 82 00 A0 */	beq lbl_80078330
/* 80078294 00074E74  80 0D AE B8 */	lwz r0, lbl_804D6558
/* 80078298 00074E78  80 DA 00 04 */	lwz r6, 4(r26)
/* 8007829C 00074E7C  28 00 00 14 */	cmplwi r0, 0x14
/* 800782A0 00074E80  80 BA 00 10 */	lwz r5, 0x10(r26)
/* 800782A4 00074E84  40 80 00 68 */	bge lbl_8007830C
/* 800782A8 00074E88  1C 80 00 28 */	mulli r4, r0, 0x28
/* 800782AC 00074E8C  FC 20 F0 90 */	fmr f1, f30
/* 800782B0 00074E90  3C 60 80 46 */	lis r3, lbl_80459278@ha
/* 800782B4 00074E94  38 03 92 78 */	addi r0, r3, lbl_80459278@l
/* 800782B8 00074E98  7F C0 22 14 */	add r30, r0, r4
/* 800782BC 00074E9C  38 00 00 02 */	li r0, 2
/* 800782C0 00074EA0  90 1E 00 00 */	stw r0, 0(r30)
/* 800782C4 00074EA4  90 BE 00 04 */	stw r5, 4(r30)
/* 800782C8 00074EA8  90 DE 00 08 */	stw r6, 8(r30)
/* 800782CC 00074EAC  93 7E 00 0C */	stw r27, 0xc(r30)
/* 800782D0 00074EB0  93 BE 00 10 */	stw r29, 0x10(r30)
/* 800782D4 00074EB4  80 7B 00 64 */	lwz r3, 0x64(r27)
/* 800782D8 00074EB8  80 1B 00 68 */	lwz r0, 0x68(r27)
/* 800782DC 00074EBC  90 7E 00 14 */	stw r3, 0x14(r30)
/* 800782E0 00074EC0  90 1E 00 18 */	stw r0, 0x18(r30)
/* 800782E4 00074EC4  80 1B 00 6C */	lwz r0, 0x6c(r27)
/* 800782E8 00074EC8  90 1E 00 1C */	stw r0, 0x1c(r30)
/* 800782EC 00074ECC  C0 1B 00 0C */	lfs f0, 0xc(r27)
/* 800782F0 00074ED0  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 800782F4 00074ED4  48 2A A5 CD */	bl __cvt_fp2unsigned
/* 800782F8 00074ED8  90 7E 00 24 */	stw r3, 0x24(r30)
/* 800782FC 00074EDC  80 6D AE B8 */	lwz r3, lbl_804D6558
/* 80078300 00074EE0  38 03 00 01 */	addi r0, r3, 1
/* 80078304 00074EE4  90 0D AE B8 */	stw r0, lbl_804D6558
/* 80078308 00074EE8  48 00 00 24 */	b lbl_8007832C
lbl_8007830C:
/* 8007830C 00074EEC  38 7F 00 40 */	addi r3, r31, 0x40
/* 80078310 00074EF0  4C C6 31 82 */	crclr 6
/* 80078314 00074EF4  38 80 00 14 */	li r4, 0x14
/* 80078318 00074EF8  48 2C D3 91 */	bl OSReport
/* 8007831C 00074EFC  38 7F 00 34 */	addi r3, r31, 0x34
/* 80078320 00074F00  38 80 00 E3 */	li r4, 0xe3
/* 80078324 00074F04  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 80078328 00074F08  48 30 FE F9 */	bl __assert
lbl_8007832C:
/* 8007832C 00074F0C  3B C0 00 01 */	li r30, 1
lbl_80078330:
/* 80078330 00074F10  FC 20 F8 90 */	fmr f1, f31
/* 80078334 00074F14  80 7A 00 04 */	lwz r3, 4(r26)
/* 80078338 00074F18  80 9C 00 00 */	lwz r4, 0(r28)
/* 8007833C 00074F1C  48 00 06 5D */	bl func_80078998
lbl_80078340:
/* 80078340 00074F20  2C 1E 00 00 */	cmpwi r30, 0
/* 80078344 00074F24  40 82 00 18 */	bne lbl_8007835C
/* 80078348 00074F28  38 BB 00 64 */	addi r5, r27, 0x64
/* 8007834C 00074F2C  4C C6 31 82 */	crclr 6
/* 80078350 00074F30  38 60 04 1C */	li r3, 0x41c
/* 80078354 00074F34  38 80 00 00 */	li r4, 0
/* 80078358 00074F38  4B FE 7A 85 */	bl ef_Spawn
lbl_8007835C:
/* 8007835C 00074F3C  38 60 00 01 */	li r3, 1
/* 80078360 00074F40  48 00 00 08 */	b lbl_80078368
lbl_80078364:
/* 80078364 00074F44  38 60 00 00 */	li r3, 0
lbl_80078368:
/* 80078368 00074F48  BB 21 00 54 */	lmw r25, 0x54(r1)
/* 8007836C 00074F4C  80 01 00 84 */	lwz r0, 0x84(r1)
/* 80078370 00074F50  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 80078374 00074F54  CB C1 00 70 */	lfd f30, 0x70(r1)
/* 80078378 00074F58  38 21 00 80 */	addi r1, r1, 0x80
/* 8007837C 00074F5C  7C 08 03 A6 */	mtlr r0
/* 80078380 00074F60  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078384(void)
{ // clang-format off
    nofralloc
/* 80078384 00074F64  7C 08 02 A6 */	mflr r0
/* 80078388 00074F68  90 01 00 04 */	stw r0, 4(r1)
/* 8007838C 00074F6C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80078390 00074F70  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80078394 00074F74  7C 7F 1B 78 */	mr r31, r3
/* 80078398 00074F78  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007839C 00074F7C  3B C5 00 00 */	addi r30, r5, 0
/* 800783A0 00074F80  80 03 19 88 */	lwz r0, 0x1988(r3)
/* 800783A4 00074F84  2C 00 00 00 */	cmpwi r0, 0
/* 800783A8 00074F88  40 82 00 28 */	bne lbl_800783D0
/* 800783AC 00074F8C  80 1F 19 8C */	lwz r0, 0x198c(r31)
/* 800783B0 00074F90  2C 00 00 00 */	cmpwi r0, 0
/* 800783B4 00074F94  40 82 00 1C */	bne lbl_800783D0
/* 800783B8 00074F98  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 800783BC 00074F9C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800783C0 00074FA0  40 82 00 10 */	bne lbl_800783D0
/* 800783C4 00074FA4  80 04 00 00 */	lwz r0, 0(r4)
/* 800783C8 00074FA8  2C 00 00 00 */	cmpwi r0, 0
/* 800783CC 00074FAC  41 82 00 34 */	beq lbl_80078400
lbl_800783D0:
/* 800783D0 00074FB0  80 9E 00 38 */	lwz r4, 0x38(r30)
/* 800783D4 00074FB4  3C 60 80 3C */	lis r3, lbl_803C0C40@ha
/* 800783D8 00074FB8  38 03 0C 40 */	addi r0, r3, lbl_803C0C40@l
/* 800783DC 00074FBC  54 83 10 3A */	slwi r3, r4, 2
/* 800783E0 00074FC0  7C 60 1A 14 */	add r3, r0, r3
/* 800783E4 00074FC4  80 83 00 00 */	lwz r4, 0(r3)
/* 800783E8 00074FC8  38 7F 00 00 */	addi r3, r31, 0
/* 800783EC 00074FCC  38 A0 00 7F */	li r5, 0x7f
/* 800783F0 00074FD0  38 C0 00 40 */	li r6, 0x40
/* 800783F4 00074FD4  48 00 FD 55 */	bl func_80088148
/* 800783F8 00074FD8  38 00 00 01 */	li r0, 1
/* 800783FC 00074FDC  48 00 00 08 */	b lbl_80078404
lbl_80078400:
/* 80078400 00074FE0  38 00 00 00 */	li r0, 0
lbl_80078404:
/* 80078404 00074FE4  2C 00 00 00 */	cmpwi r0, 0
/* 80078408 00074FE8  40 82 00 68 */	bne lbl_80078470
/* 8007840C 00074FEC  80 1E 00 3C */	lwz r0, 0x3c(r30)
/* 80078410 00074FF0  28 00 00 0D */	cmplwi r0, 0xd
/* 80078414 00074FF4  40 82 00 38 */	bne lbl_8007844C
/* 80078418 00074FF8  80 1E 00 38 */	lwz r0, 0x38(r30)
/* 8007841C 00074FFC  28 00 00 02 */	cmplwi r0, 2
/* 80078420 00075000  40 82 00 2C */	bne lbl_8007844C
/* 80078424 00075004  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80078428 00075008  7F C3 F3 78 */	mr r3, r30
/* 8007842C 0007500C  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 80078430 00075010  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80078434 00075014  54 00 08 3C */	slwi r0, r0, 1
/* 80078438 00075018  7C 80 22 14 */	add r4, r0, r4
/* 8007843C 0007501C  38 84 00 72 */	addi r4, r4, 0x72
/* 80078440 00075020  4B F8 D7 71 */	bl func_80005BB0
/* 80078444 00075024  90 7F 21 5C */	stw r3, 0x215c(r31)
/* 80078448 00075028  48 00 00 28 */	b lbl_80078470
lbl_8007844C:
/* 8007844C 0007502C  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80078450 00075030  7F C3 F3 78 */	mr r3, r30
/* 80078454 00075034  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 80078458 00075038  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8007845C 0007503C  54 00 08 3C */	slwi r0, r0, 1
/* 80078460 00075040  7C 80 22 14 */	add r4, r0, r4
/* 80078464 00075044  38 84 00 7E */	addi r4, r4, 0x7e
/* 80078468 00075048  4B F8 D7 49 */	bl func_80005BB0
/* 8007846C 0007504C  90 7F 21 60 */	stw r3, 0x2160(r31)
lbl_80078470:
/* 80078470 00075050  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80078474 00075054  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80078478 00075058  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007847C 0007505C  38 21 00 20 */	addi r1, r1, 0x20
/* 80078480 00075060  7C 08 03 A6 */	mtlr r0
/* 80078484 00075064  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078488(void)
{ // clang-format off
    nofralloc
/* 80078488 00075068  7C 08 02 A6 */	mflr r0
/* 8007848C 0007506C  38 80 00 55 */	li r4, 0x55
/* 80078490 00075070  90 01 00 04 */	stw r0, 4(r1)
/* 80078494 00075074  38 A0 00 7F */	li r5, 0x7f
/* 80078498 00075078  38 C0 00 40 */	li r6, 0x40
/* 8007849C 0007507C  94 21 FF F8 */	stwu r1, -8(r1)
/* 800784A0 00075080  48 00 FC A9 */	bl func_80088148
/* 800784A4 00075084  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800784A8 00075088  38 21 00 08 */	addi r1, r1, 8
/* 800784AC 0007508C  7C 08 03 A6 */	mtlr r0
/* 800784B0 00075090  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_803C0C4C;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800784B4(void)
{ // clang-format off
    nofralloc
/* 800784B4 00075094  7C 08 02 A6 */	mflr r0
/* 800784B8 00075098  90 01 00 04 */	stw r0, 4(r1)
/* 800784BC 0007509C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800784C0 000750A0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800784C4 000750A4  3B E3 00 00 */	addi r31, r3, 0
/* 800784C8 000750A8  80 04 00 30 */	lwz r0, 0x30(r4)
/* 800784CC 000750AC  28 00 00 03 */	cmplwi r0, 3
/* 800784D0 000750B0  40 82 00 40 */	bne lbl_80078510
/* 800784D4 000750B4  80 05 00 30 */	lwz r0, 0x30(r5)
/* 800784D8 000750B8  28 00 00 03 */	cmplwi r0, 3
/* 800784DC 000750BC  40 82 00 34 */	bne lbl_80078510
/* 800784E0 000750C0  38 60 00 03 */	li r3, 3
/* 800784E4 000750C4  48 30 80 9D */	bl HSD_Randi
/* 800784E8 000750C8  3C 80 80 3C */	lis r4, lbl_803C0C4C@ha
/* 800784EC 000750CC  54 63 10 3A */	slwi r3, r3, 2
/* 800784F0 000750D0  38 04 0C 4C */	addi r0, r4, lbl_803C0C4C@l
/* 800784F4 000750D4  7C 60 1A 14 */	add r3, r0, r3
/* 800784F8 000750D8  80 83 00 00 */	lwz r4, 0(r3)
/* 800784FC 000750DC  38 7F 00 00 */	addi r3, r31, 0
/* 80078500 000750E0  38 A0 00 7F */	li r5, 0x7f
/* 80078504 000750E4  38 C0 00 40 */	li r6, 0x40
/* 80078508 000750E8  48 00 FC 41 */	bl func_80088148
/* 8007850C 000750EC  48 00 00 18 */	b lbl_80078524
lbl_80078510:
/* 80078510 000750F0  38 7F 00 00 */	addi r3, r31, 0
/* 80078514 000750F4  38 80 00 6A */	li r4, 0x6a
/* 80078518 000750F8  38 A0 00 7F */	li r5, 0x7f
/* 8007851C 000750FC  38 C0 00 40 */	li r6, 0x40
/* 80078520 00075100  48 00 FC 29 */	bl func_80088148
lbl_80078524:
/* 80078524 00075104  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80078528 00075108  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007852C 0007510C  38 21 00 20 */	addi r1, r1, 0x20
/* 80078530 00075110  7C 08 03 A6 */	mtlr r0
/* 80078534 00075114  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078538(void)
{ // clang-format off
    nofralloc
/* 80078538 00075118  7C 08 02 A6 */	mflr r0
/* 8007853C 0007511C  90 01 00 04 */	stw r0, 4(r1)
/* 80078540 00075120  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80078544 00075124  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80078548 00075128  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8007854C 0007512C  7C BE 2B 78 */	mr r30, r5
/* 80078550 00075130  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80078554 00075134  7C 9D 23 78 */	mr r29, r4
/* 80078558 00075138  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 8007855C 0007513C  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80078560 00075140  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80078564 00075144  C0 04 03 F0 */	lfs f0, 0x3f0(r4)
/* 80078568 00075148  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8007856C 0007514C  40 80 00 20 */	bge lbl_8007858C
/* 80078570 00075150  38 BD 00 00 */	addi r5, r29, 0
/* 80078574 00075154  4C C6 31 82 */	crclr 6
/* 80078578 00075158  38 C1 00 14 */	addi r6, r1, 0x14
/* 8007857C 0007515C  38 60 03 E8 */	li r3, 0x3e8
/* 80078580 00075160  38 80 00 00 */	li r4, 0
/* 80078584 00075164  4B FE 78 59 */	bl ef_Spawn
/* 80078588 00075168  48 00 00 18 */	b lbl_800785A0
lbl_8007858C:
/* 8007858C 0007516C  38 BD 00 00 */	addi r5, r29, 0
/* 80078590 00075170  4C C6 31 82 */	crclr 6
/* 80078594 00075174  38 60 03 F3 */	li r3, 0x3f3
/* 80078598 00075178  38 80 00 00 */	li r4, 0
/* 8007859C 0007517C  4B FE 78 41 */	bl ef_Spawn
lbl_800785A0:
/* 800785A0 00075180  28 1E 00 01 */	cmplwi r30, 1
/* 800785A4 00075184  41 80 00 5C */	blt lbl_80078600
/* 800785A8 00075188  80 1F 01 B0 */	lwz r0, 0x1b0(r31)
/* 800785AC 0007518C  2C 00 00 01 */	cmpwi r0, 1
/* 800785B0 00075190  41 82 00 44 */	beq lbl_800785F4
/* 800785B4 00075194  40 80 00 4C */	bge lbl_80078600
/* 800785B8 00075198  2C 00 00 00 */	cmpwi r0, 0
/* 800785BC 0007519C  40 80 00 08 */	bge lbl_800785C4
/* 800785C0 000751A0  48 00 00 40 */	b lbl_80078600
lbl_800785C4:
/* 800785C4 000751A4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800785C8 000751A8  80 63 03 F4 */	lwz r3, 0x3f4(r3)
/* 800785CC 000751AC  48 30 7F B5 */	bl HSD_Randi
/* 800785D0 000751B0  2C 03 00 00 */	cmpwi r3, 0
/* 800785D4 000751B4  40 82 00 2C */	bne lbl_80078600
/* 800785D8 000751B8  38 BD 00 00 */	addi r5, r29, 0
/* 800785DC 000751BC  4C C6 31 82 */	crclr 6
/* 800785E0 000751C0  38 DF 00 2C */	addi r6, r31, 0x2c
/* 800785E4 000751C4  38 60 03 EF */	li r3, 0x3ef
/* 800785E8 000751C8  38 80 00 00 */	li r4, 0
/* 800785EC 000751CC  4B FE 77 F1 */	bl ef_Spawn
/* 800785F0 000751D0  48 00 00 10 */	b lbl_80078600
lbl_800785F4:
/* 800785F4 000751D4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800785F8 000751D8  80 63 03 F8 */	lwz r3, 0x3f8(r3)
/* 800785FC 000751DC  48 30 7F 85 */	bl HSD_Randi
lbl_80078600:
/* 80078600 000751E0  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80078604 000751E4  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80078608 000751E8  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8007860C 000751EC  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80078610 000751F0  38 21 00 40 */	addi r1, r1, 0x40
/* 80078614 000751F4  7C 08 03 A6 */	mtlr r0
/* 80078618 000751F8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007861C(void)
{ // clang-format off
    nofralloc
/* 8007861C 000751FC  7C 08 02 A6 */	mflr r0
/* 80078620 00075200  28 03 00 00 */	cmplwi r3, 0
/* 80078624 00075204  90 01 00 04 */	stw r0, 4(r1)
/* 80078628 00075208  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8007862C 0007520C  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80078630 00075210  81 61 00 50 */	lwz r11, 0x50(r1)
/* 80078634 00075214  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80078638 00075218  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 8007863C 0007521C  41 82 00 0C */	beq lbl_80078648
/* 80078640 00075220  81 83 00 2C */	lwz r12, 0x2c(r3)
/* 80078644 00075224  48 00 00 08 */	b lbl_8007864C
lbl_80078648:
/* 80078648 00075228  39 80 00 00 */	li r12, 0
lbl_8007864C:
/* 8007864C 0007522C  83 E4 00 2C */	lwz r31, 0x2c(r4)
/* 80078650 00075230  28 0C 00 00 */	cmplwi r12, 0
/* 80078654 00075234  3B C0 00 00 */	li r30, 0
/* 80078658 00075238  83 BF 18 C4 */	lwz r29, 0x18c4(r31)
/* 8007865C 0007523C  41 82 00 40 */	beq lbl_8007869C
/* 80078660 00075240  7C 0C F8 40 */	cmplw r12, r31
/* 80078664 00075244  40 82 00 0C */	bne lbl_80078670
/* 80078668 00075248  38 00 00 00 */	li r0, 0
/* 8007866C 0007524C  48 00 00 08 */	b lbl_80078674
lbl_80078670:
/* 80078670 00075250  80 0C 00 08 */	lwz r0, 8(r12)
lbl_80078674:
/* 80078674 00075254  90 1F 18 C0 */	stw r0, 0x18c0(r31)
/* 80078678 00075258  38 00 FF FF */	li r0, -1
/* 8007867C 0007525C  89 6C 00 0C */	lbz r11, 0xc(r12)
/* 80078680 00075260  91 7F 18 C4 */	stw r11, 0x18c4(r31)
/* 80078684 00075264  90 1F 18 C8 */	stw r0, 0x18c8(r31)
/* 80078688 00075268  89 6C 22 1F */	lbz r11, 0x221f(r12)
/* 8007868C 0007526C  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 80078690 00075270  51 60 FF 7A */	rlwimi r0, r11, 0x1f, 0x1d, 0x1d
/* 80078694 00075274  98 1F 22 1F */	stb r0, 0x221f(r31)
/* 80078698 00075278  48 00 00 24 */	b lbl_800786BC
lbl_8007869C:
/* 8007869C 0007527C  38 00 00 00 */	li r0, 0
/* 800786A0 00075280  90 1F 18 C0 */	stw r0, 0x18c0(r31)
/* 800786A4 00075284  38 00 FF FF */	li r0, -1
/* 800786A8 00075288  2C 0B 00 00 */	cmpwi r11, 0
/* 800786AC 0007528C  90 1F 18 C8 */	stw r0, 0x18c8(r31)
/* 800786B0 00075290  40 82 00 0C */	bne lbl_800786BC
/* 800786B4 00075294  38 00 00 06 */	li r0, 6
/* 800786B8 00075298  90 1F 18 C4 */	stw r0, 0x18c4(r31)
lbl_800786BC:
/* 800786BC 0007529C  90 BF 18 CC */	stw r5, 0x18cc(r31)
/* 800786C0 000752A0  28 0A 00 00 */	cmplwi r10, 0
/* 800786C4 000752A4  90 DF 18 D0 */	stw r6, 0x18d0(r31)
/* 800786C8 000752A8  41 82 00 14 */	beq lbl_800786DC
/* 800786CC 000752AC  80 0A 00 08 */	lwz r0, 8(r10)
/* 800786D0 000752B0  2C 00 00 00 */	cmpwi r0, 0
/* 800786D4 000752B4  40 82 00 08 */	bne lbl_800786DC
/* 800786D8 000752B8  3B C0 00 01 */	li r30, 1
lbl_800786DC:
/* 800786DC 000752BC  38 A7 00 00 */	addi r5, r7, 0
/* 800786E0 000752C0  38 C8 00 00 */	addi r6, r8, 0
/* 800786E4 000752C4  38 E9 00 00 */	addi r7, r9, 0
/* 800786E8 000752C8  39 1E 00 00 */	addi r8, r30, 0
/* 800786EC 000752CC  39 3D 00 00 */	addi r9, r29, 0
/* 800786F0 000752D0  4B FB FA 55 */	bl func_80038144
/* 800786F4 000752D4  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800786F8 000752D8  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 800786FC 000752DC  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80078700 000752E0  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 80078704 000752E4  38 21 00 48 */	addi r1, r1, 0x48
/* 80078708 000752E8  7C 08 03 A6 */	mtlr r0
/* 8007870C 000752EC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078710(void)
{ // clang-format off
    nofralloc
/* 80078710 000752F0  7C 08 02 A6 */	mflr r0
/* 80078714 000752F4  7C AA 2B 78 */	mr r10, r5
/* 80078718 000752F8  90 01 00 04 */	stw r0, 4(r1)
/* 8007871C 000752FC  38 00 00 00 */	li r0, 0
/* 80078720 00075300  38 A0 00 01 */	li r5, 1
/* 80078724 00075304  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80078728 00075308  81 03 00 2C */	lwz r8, 0x2c(r3)
/* 8007872C 0007530C  90 01 00 08 */	stw r0, 8(r1)
/* 80078730 00075310  80 C8 00 04 */	lwz r6, 4(r8)
/* 80078734 00075314  80 E8 20 70 */	lwz r7, 0x2070(r8)
/* 80078738 00075318  A1 28 20 88 */	lhz r9, 0x2088(r8)
/* 8007873C 0007531C  39 08 20 74 */	addi r8, r8, 0x2074
/* 80078740 00075320  4B FF FE DD */	bl func_8007861C
/* 80078744 00075324  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80078748 00075328  38 21 00 28 */	addi r1, r1, 0x28
/* 8007874C 0007532C  7C 08 03 A6 */	mtlr r0
/* 80078750 00075330  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078754(HSD_GObj*, HSD_GObj*, bool)
{ // clang-format off
    nofralloc
/* 80078754 00075334  7C 08 02 A6 */	mflr r0
/* 80078758 00075338  7C AA 2B 78 */	mr r10, r5
/* 8007875C 0007533C  90 01 00 04 */	stw r0, 4(r1)
/* 80078760 00075340  38 00 00 00 */	li r0, 0
/* 80078764 00075344  38 A0 00 01 */	li r5, 1
/* 80078768 00075348  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007876C 0007534C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80078770 00075350  81 23 00 2C */	lwz r9, 0x2c(r3)
/* 80078774 00075354  83 E4 00 2C */	lwz r31, 0x2c(r4)
/* 80078778 00075358  39 09 20 74 */	addi r8, r9, 0x2074
/* 8007877C 0007535C  90 01 00 08 */	stw r0, 8(r1)
/* 80078780 00075360  80 C9 00 04 */	lwz r6, 4(r9)
/* 80078784 00075364  80 E9 20 70 */	lwz r7, 0x2070(r9)
/* 80078788 00075368  A1 29 20 88 */	lhz r9, 0x2088(r9)
/* 8007878C 0007536C  4B FF FE 91 */	bl func_8007861C
/* 80078790 00075370  38 00 00 06 */	li r0, 6
/* 80078794 00075374  90 1F 18 C4 */	stw r0, 0x18c4(r31)
/* 80078798 00075378  38 00 FF FF */	li r0, -1
/* 8007879C 0007537C  90 1F 18 C8 */	stw r0, 0x18c8(r31)
/* 800787A0 00075380  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800787A4 00075384  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800787A8 00075388  38 21 00 30 */	addi r1, r1, 0x30
/* 800787AC 0007538C  7C 08 03 A6 */	mtlr r0
/* 800787B0 00075390  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800787B4(void)
{ // clang-format off
    nofralloc
/* 800787B4 00075394  7C 08 02 A6 */	mflr r0
/* 800787B8 00075398  90 01 00 04 */	stw r0, 4(r1)
/* 800787BC 0007539C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800787C0 000753A0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800787C4 000753A4  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800787C8 000753A8  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800787CC 000753AC  7C BD 2B 78 */	mr r29, r5
/* 800787D0 000753B0  93 81 00 28 */	stw r28, 0x28(r1)
/* 800787D4 000753B4  7C 9C 23 78 */	mr r28, r4
/* 800787D8 000753B8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800787DC 000753BC  80 64 00 2C */	lwz r3, 0x2c(r4)
/* 800787E0 000753C0  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800787E4 000753C4  83 DF 05 18 */	lwz r30, 0x518(r31)
/* 800787E8 000753C8  2C 00 00 06 */	cmpwi r0, 6
/* 800787EC 000753CC  40 82 00 1C */	bne lbl_80078808
/* 800787F0 000753D0  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 800787F4 000753D4  80 1F 00 1C */	lwz r0, 0x1c(r31)
/* 800787F8 000753D8  88 63 00 0C */	lbz r3, 0xc(r3)
/* 800787FC 000753DC  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80078800 000753E0  54 05 04 3E */	clrlwi r5, r0, 0x10
/* 80078804 000753E4  4B FC 93 05 */	bl func_80041B08
lbl_80078808:
/* 80078808 000753E8  7F C3 F3 78 */	mr r3, r30
/* 8007880C 000753EC  48 00 E1 55 */	bl func_80086960
/* 80078810 000753F0  2C 03 00 00 */	cmpwi r3, 0
/* 80078814 000753F4  41 82 00 34 */	beq lbl_80078848
/* 80078818 000753F8  38 00 00 00 */	li r0, 0
/* 8007881C 000753FC  90 01 00 08 */	stw r0, 8(r1)
/* 80078820 00075400  38 7E 00 00 */	addi r3, r30, 0
/* 80078824 00075404  38 9C 00 00 */	addi r4, r28, 0
/* 80078828 00075408  80 DF 00 10 */	lwz r6, 0x10(r31)
/* 8007882C 0007540C  7F AA EB 78 */	mr r10, r29
/* 80078830 00075410  80 FF 0D 90 */	lwz r7, 0xd90(r31)
/* 80078834 00075414  39 1F 0D 94 */	addi r8, r31, 0xd94
/* 80078838 00075418  A1 3F 0D A8 */	lhz r9, 0xda8(r31)
/* 8007883C 0007541C  38 A0 00 02 */	li r5, 2
/* 80078840 00075420  4B FF FD DD */	bl func_8007861C
/* 80078844 00075424  48 00 00 70 */	b lbl_800788B4
lbl_80078848:
/* 80078848 00075428  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 8007884C 0007542C  4B FC 4D C1 */	bl func_8003D60C
/* 80078850 00075430  2C 03 00 00 */	cmpwi r3, 0
/* 80078854 00075434  41 82 00 34 */	beq lbl_80078888
/* 80078858 00075438  38 00 00 01 */	li r0, 1
/* 8007885C 0007543C  90 01 00 08 */	stw r0, 8(r1)
/* 80078860 00075440  38 9C 00 00 */	addi r4, r28, 0
/* 80078864 00075444  39 5D 00 00 */	addi r10, r29, 0
/* 80078868 00075448  80 DF 00 10 */	lwz r6, 0x10(r31)
/* 8007886C 0007544C  39 1F 0D 94 */	addi r8, r31, 0xd94
/* 80078870 00075450  80 FF 0D 90 */	lwz r7, 0xd90(r31)
/* 80078874 00075454  38 60 00 00 */	li r3, 0
/* 80078878 00075458  A1 3F 0D A8 */	lhz r9, 0xda8(r31)
/* 8007887C 0007545C  38 A0 00 02 */	li r5, 2
/* 80078880 00075460  4B FF FD 9D */	bl func_8007861C
/* 80078884 00075464  48 00 00 30 */	b lbl_800788B4
lbl_80078888:
/* 80078888 00075468  38 00 00 00 */	li r0, 0
/* 8007888C 0007546C  90 01 00 08 */	stw r0, 8(r1)
/* 80078890 00075470  38 9C 00 00 */	addi r4, r28, 0
/* 80078894 00075474  39 5D 00 00 */	addi r10, r29, 0
/* 80078898 00075478  80 DF 00 10 */	lwz r6, 0x10(r31)
/* 8007889C 0007547C  39 1F 0D 94 */	addi r8, r31, 0xd94
/* 800788A0 00075480  80 FF 0D 90 */	lwz r7, 0xd90(r31)
/* 800788A4 00075484  38 60 00 00 */	li r3, 0
/* 800788A8 00075488  A1 3F 0D A8 */	lhz r9, 0xda8(r31)
/* 800788AC 0007548C  38 A0 00 02 */	li r5, 2
/* 800788B0 00075490  4B FF FD 6D */	bl func_8007861C
lbl_800788B4:
/* 800788B4 00075494  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800788B8 00075498  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800788BC 0007549C  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800788C0 000754A0  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 800788C4 000754A4  83 81 00 28 */	lwz r28, 0x28(r1)
/* 800788C8 000754A8  38 21 00 38 */	addi r1, r1, 0x38
/* 800788CC 000754AC  7C 08 03 A6 */	mtlr r0
/* 800788D0 000754B0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
