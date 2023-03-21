#include <platform.h>
#include "lb/forward.h"

#include "ft/ftcoll.h"

#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/fighter.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "gm/code_801601C4.h"
#include "gr/stage.h"
#include "it/code_80266F3C.h"
#include "it/item.h"
#include "lb/lbunknown_001.h"
#include "pl/pl_unknown_001.h"
#include "pl/player.h"

#include <common_structs.h>
#include <math.h>
#include <runtime.h>
#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>
#include <baselib/archive.h>
#include <baselib/controller.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/trigf.h>

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
    enum_t msid = func_8026BC84(attackItem);

    if (func_80086960(owner))
        func_800763C0(owner, victim, msid);
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
void func_80076528(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u16 temp_r3 = fp->x2092;

    if (temp_r3 != 0) {
        fp->x2092 = (u16) (temp_r3 - 1);
        if ((fp->x1A58_interactedFighter == NULL) &&
            (fp->ground_or_air == GA_Ground))
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

    if (cur != NULL && !fp->x221B_b5 && cur != victim)
        arg2 *= p_ftCommonData->x128;

    if (fp->motion_id == ftCo_MS_DamageIce)
        arg2 *= p_ftCommonData->x714;

    return arg2 * fp->dmg.x182c_behavior;
}

f32 const lbl_804D82E0 = 0.0F;
f32 const lbl_804D82E4 = 500.0F;
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

extern bool* lbl_804D6560;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076808(Fighter* attacker, HitCapsule*, int, Fighter* victim,
                       int)
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
/* 80076860 00073440  4B F9 1E 29 */	bl lbColl_80008688
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
asm void func_800768A0(void){
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
/* 800768D8 000734B8  4B F9 1C 25 */	bl lbColl_CopyHitCapsule
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
/* 80076910 000734F0  4B F9 1B ED */	bl lbColl_CopyHitCapsule
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
/* 80076948 00073528  4B F9 1B B5 */	bl lbColl_CopyHitCapsule
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
/* 8007697C 0007355C  4B F9 1B 81 */	bl lbColl_CopyHitCapsule
/* 80076980 00073560  48 00 00 0C */	b lbl_8007698C
lbl_80076984:
/* 80076984 00073564  7C 83 23 78 */	mr r3, r4
/* 80076988 00073568  4B F9 1A B9 */	bl lbColl_80008440
lbl_8007698C:
/* 8007698C 0007356C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80076990 00073570  38 21 00 08 */	addi r1, r1, 8
/* 80076994 00073574  7C 08 03 A6 */	mtlr r0
/* 80076998 00073578  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

f32 const lbl_804D82E8 = 0.5F;
f32 const lbl_804D82EC = 1.0F;
f32 const lbl_804D82F0 = -1.0F;
f64 const lbl_804D82F8 = 4503601774854144.0;

#ifdef MWERKS_GEKKO
#pragma push
asm bool func_8007699C(Fighter*, HitCapsule*, Fighter*, HitCapsule*)
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
/* 80076A9C 0007367C  4B F9 1B ED */	bl lbColl_80008688
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
/* 80076BE8 000737C8  4B F9 1A A1 */	bl lbColl_80008688
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
asm bool func_80076CBC(Fighter*, HitCapsule*, Fighter*)
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
/* 80076D08 000738E8  4B F9 19 81 */	bl lbColl_80008688
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
asm bool func_80076ED8(Fighter*, HitCapsule*, Fighter*, HurtCapsule*)
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
/* 80077090 00073C70  4B F9 17 91 */	bl lbColl_80008820
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
/* 80077234 00073E14  4B F9 14 55 */	bl lbColl_80008688
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
/* 80077A70 00074650  4B F9 0C 19 */	bl lbColl_80008688
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
/* 80078440 00075020  4B F8 D7 71 */	bl lbColl_80005BB0
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
/* 80078468 00075048  4B F8 D7 49 */	bl lbColl_80005BB0
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

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800788D4(void)
{ // clang-format off
    nofralloc
/* 800788D4 000754B4  7C 08 02 A6 */	mflr r0
/* 800788D8 000754B8  38 83 00 00 */	addi r4, r3, 0
/* 800788DC 000754BC  90 01 00 04 */	stw r0, 4(r1)
/* 800788E0 000754C0  38 00 00 00 */	li r0, 0
/* 800788E4 000754C4  38 60 00 00 */	li r3, 0
/* 800788E8 000754C8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800788EC 000754CC  38 A0 00 00 */	li r5, 0
/* 800788F0 000754D0  38 C0 FF F6 */	li r6, -10
/* 800788F4 000754D4  90 01 00 08 */	stw r0, 8(r1)
/* 800788F8 000754D8  38 E0 00 00 */	li r7, 0
/* 800788FC 000754DC  39 00 00 00 */	li r8, 0
/* 80078900 000754E0  39 20 00 00 */	li r9, 0
/* 80078904 000754E4  39 40 00 00 */	li r10, 0
/* 80078908 000754E8  4B FF FD 15 */	bl func_8007861C
/* 8007890C 000754EC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80078910 000754F0  38 21 00 18 */	addi r1, r1, 0x18
/* 80078914 000754F4  7C 08 03 A6 */	mtlr r0
/* 80078918 000754F8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007891C(void)
{ // clang-format off
    nofralloc
/* 8007891C 000754FC  7C 08 02 A6 */	mflr r0
/* 80078920 00075500  90 01 00 04 */	stw r0, 4(r1)
/* 80078924 00075504  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80078928 00075508  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8007892C 0007550C  FF E0 08 90 */	fmr f31, f1
/* 80078930 00075510  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80078934 00075514  3B E4 00 00 */	addi r31, r4, 0
/* 80078938 00075518  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8007893C 0007551C  3B C3 00 00 */	addi r30, r3, 0
/* 80078940 00075520  4B FB E8 ED */	bl func_8003722C
/* 80078944 00075524  38 7E 00 00 */	addi r3, r30, 0
/* 80078948 00075528  38 9F 00 00 */	addi r4, r31, 0
/* 8007894C 0007552C  4B FF DA F9 */	bl func_80076444
/* 80078950 00075530  80 FE 00 2C */	lwz r7, 0x2c(r30)
/* 80078954 00075534  FC 20 F8 90 */	fmr f1, f31
/* 80078958 00075538  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 8007895C 0007553C  88 87 22 1F */	lbz r4, 0x221f(r7)
/* 80078960 00075540  88 C5 22 1F */	lbz r6, 0x221f(r5)
/* 80078964 00075544  88 67 00 0C */	lbz r3, 0xc(r7)
/* 80078968 00075548  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8007896C 0007554C  88 A5 00 0C */	lbz r5, 0xc(r5)
/* 80078970 00075550  54 C6 EF FE */	rlwinm r6, r6, 0x1d, 0x1f, 0x1f
/* 80078974 00075554  88 E7 20 73 */	lbz r7, 0x2073(r7)
/* 80078978 00075558  4B FC 61 B9 */	bl func_8003EB30
/* 8007897C 0007555C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80078980 00075560  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80078984 00075564  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80078988 00075568  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8007898C 0007556C  38 21 00 30 */	addi r1, r1, 0x30
/* 80078990 00075570  7C 08 03 A6 */	mtlr r0
/* 80078994 00075574  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078998(void)
{ // clang-format off
    nofralloc
/* 80078998 00075578  7C 08 02 A6 */	mflr r0
/* 8007899C 0007557C  90 01 00 04 */	stw r0, 4(r1)
/* 800789A0 00075580  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800789A4 00075584  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 800789A8 00075588  FF E0 08 90 */	fmr f31, f1
/* 800789AC 0007558C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800789B0 00075590  3B E3 00 00 */	addi r31, r3, 0
/* 800789B4 00075594  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800789B8 00075598  3B C4 00 00 */	addi r30, r4, 0
/* 800789BC 0007559C  4B FB EA 11 */	bl func_800373CC
/* 800789C0 000755A0  38 7F 00 00 */	addi r3, r31, 0
/* 800789C4 000755A4  38 9E 00 00 */	addi r4, r30, 0
/* 800789C8 000755A8  4B FF DA A5 */	bl func_8007646C
/* 800789CC 000755AC  83 FF 00 2C */	lwz r31, 0x2c(r31)
/* 800789D0 000755B0  80 7F 05 18 */	lwz r3, 0x518(r31)
/* 800789D4 000755B4  48 00 DF 8D */	bl func_80086960
/* 800789D8 000755B8  2C 03 00 00 */	cmpwi r3, 0
/* 800789DC 000755BC  41 82 00 34 */	beq lbl_80078A10
/* 800789E0 000755C0  80 7F 05 18 */	lwz r3, 0x518(r31)
/* 800789E4 000755C4  FC 20 F8 90 */	fmr f1, f31
/* 800789E8 000755C8  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800789EC 000755CC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800789F0 000755D0  88 C5 22 1F */	lbz r6, 0x221f(r5)
/* 800789F4 000755D4  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 800789F8 000755D8  88 63 00 0C */	lbz r3, 0xc(r3)
/* 800789FC 000755DC  54 C6 EF FE */	rlwinm r6, r6, 0x1d, 0x1f, 0x1f
/* 80078A00 000755E0  88 A5 00 0C */	lbz r5, 0xc(r5)
/* 80078A04 000755E4  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80078A08 000755E8  88 FF 0D 93 */	lbz r7, 0xd93(r31)
/* 80078A0C 000755EC  4B FC 61 25 */	bl func_8003EB30
lbl_80078A10:
/* 80078A10 000755F0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80078A14 000755F4  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 80078A18 000755F8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80078A1C 000755FC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80078A20 00075600  38 21 00 38 */	addi r1, r1, 0x38
/* 80078A24 00075604  7C 08 03 A6 */	mtlr r0
/* 80078A28 00075608  4E 80 00 20 */	blr

} // clang-format on
#pragma pop
#endif

extern f32 const lbl_804D8310;

inline HitCapsule* ftHitGetPtr(Fighter* fp, u32 i)
{
    return &fp->x914[i];
}

#ifdef MUST_MATCH

#pragma push
asm void func_80078A2C(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 80078A2C 0007560C  7C 08 02 A6 */	mflr r0
/* 80078A30 00075610  90 01 00 04 */	stw r0, 4(r1)
/* 80078A34 00075614  38 00 00 00 */	li r0, 0
/* 80078A38 00075618  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80078A3C 0007561C  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80078A40 00075620  BE E1 00 24 */	stmw r23, 0x24(r1)
/* 80078A44 00075624  7C 79 1B 78 */	mr r25, r3
/* 80078A48 00075628  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80078A4C 0007562C  90 1E 1A 58 */	stw r0, 0x1a58(r30)
/* 80078A50 00075630  C0 02 89 30 */	lfs f0, lbl_804D8310
/* 80078A54 00075634  D0 1E 21 6C */	stfs f0, 0x216c(r30)
/* 80078A58 00075638  80 6D C1 8C */	lwz r3, lbl_804D782C
/* 80078A5C 0007563C  C3 E2 89 00 */	lfs f31, lbl_804D82E0
/* 80078A60 00075640  83 A3 00 20 */	lwz r29, 0x20(r3)
/* 80078A64 00075644  48 00 01 EC */	b lbl_80078C50
lbl_80078A68:
/* 80078A68 00075648  38 79 00 00 */	addi r3, r25, 0
/* 80078A6C 0007564C  38 9D 00 00 */	addi r4, r29, 0
/* 80078A70 00075650  48 00 E5 65 */	bl func_80086FD4
/* 80078A74 00075654  2C 03 00 00 */	cmpwi r3, 0
/* 80078A78 00075658  40 82 01 D4 */	bne lbl_80078C4C
/* 80078A7C 0007565C  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 80078A80 00075660  88 03 22 19 */	lbz r0, 0x2219(r3)
/* 80078A84 00075664  3B 83 00 00 */	addi r28, r3, 0
/* 80078A88 00075668  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80078A8C 0007566C  40 82 01 C0 */	bne lbl_80078C4C
/* 80078A90 00075670  88 1C 22 2A */	lbz r0, 0x222a(r28)
/* 80078A94 00075674  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80078A98 00075678  40 82 01 B4 */	bne lbl_80078C4C
/* 80078A9C 0007567C  48 0F 26 CD */	bl func_8016B168
/* 80078AA0 00075680  2C 03 00 00 */	cmpwi r3, 0
/* 80078AA4 00075684  41 82 00 20 */	beq lbl_80078AC4
/* 80078AA8 00075688  48 0F 26 2D */	bl func_8016B0D4
/* 80078AAC 0007568C  2C 03 00 00 */	cmpwi r3, 0
/* 80078AB0 00075690  40 82 00 14 */	bne lbl_80078AC4
/* 80078AB4 00075694  88 7C 06 1B */	lbz r3, 0x61b(r28)
/* 80078AB8 00075698  88 1E 06 1B */	lbz r0, 0x61b(r30)
/* 80078ABC 0007569C  7C 03 00 40 */	cmplw r3, r0
/* 80078AC0 000756A0  41 82 01 8C */	beq lbl_80078C4C
lbl_80078AC4:
/* 80078AC4 000756A4  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 80078AC8 000756A8  2C 00 00 00 */	cmpwi r0, 0
/* 80078ACC 000756AC  40 82 01 80 */	bne lbl_80078C4C
/* 80078AD0 000756B0  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 80078AD4 000756B4  2C 00 00 00 */	cmpwi r0, 0
/* 80078AD8 000756B8  40 82 01 74 */	bne lbl_80078C4C
/* 80078ADC 000756BC  88 1C 22 1D */	lbz r0, 0x221d(r28)
/* 80078AE0 000756C0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80078AE4 000756C4  40 82 01 68 */	bne lbl_80078C4C
/* 80078AE8 000756C8  A0 7C 1A 6A */	lhz r3, 0x1a6a(r28)
/* 80078AEC 000756CC  A0 1E 1A 68 */	lhz r0, 0x1a68(r30)
/* 80078AF0 000756D0  7C 60 00 39 */	and. r0, r3, r0
/* 80078AF4 000756D4  40 82 01 58 */	bne lbl_80078C4C
/* 80078AF8 000756D8  88 1C 22 24 */	lbz r0, 0x2224(r28)
/* 80078AFC 000756DC  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80078B00 000756E0  40 82 01 4C */	bne lbl_80078C4C
/* 80078B04 000756E4  3B 60 00 00 */	li r27, 0
/* 80078B08 000756E8  3B FE 00 00 */	addi r31, r30, 0
lbl_80078B0C:
/* 80078B0C 000756EC  38 7F 09 14 */	addi r3, r31, 0x914
/* 80078B10 000756F0  80 1F 09 14 */	lwz r0, 0x914(r31)
/* 80078B14 000756F4  3B 43 00 00 */	addi r26, r3, 0
/* 80078B18 000756F8  2C 00 00 00 */	cmpwi r0, 0
/* 80078B1C 000756FC  41 82 01 20 */	beq lbl_80078C3C
/* 80078B20 00075700  80 03 00 30 */	lwz r0, 0x30(r3)
/* 80078B24 00075704  28 00 00 08 */	cmplwi r0, 8
/* 80078B28 00075708  40 82 01 14 */	bne lbl_80078C3C
/* 80078B2C 0007570C  88 03 00 40 */	lbz r0, 0x40(r3)
/* 80078B30 00075710  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80078B34 00075714  41 82 00 10 */	beq lbl_80078B44
/* 80078B38 00075718  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80078B3C 0007571C  2C 00 00 01 */	cmpwi r0, 1
/* 80078B40 00075720  41 82 00 1C */	beq lbl_80078B5C
lbl_80078B44:
/* 80078B44 00075724  88 03 00 40 */	lbz r0, 0x40(r3)
/* 80078B48 00075728  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80078B4C 0007572C  41 82 00 F0 */	beq lbl_80078C3C
/* 80078B50 00075730  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80078B54 00075734  2C 00 00 00 */	cmpwi r0, 0
/* 80078B58 00075738  40 82 00 E4 */	bne lbl_80078C3C
lbl_80078B5C:
/* 80078B5C 0007573C  38 7C 00 00 */	addi r3, r28, 0
/* 80078B60 00075740  38 9A 00 00 */	addi r4, r26, 0
/* 80078B64 00075744  4B F9 21 99 */	bl lbColl_8000ACFC
/* 80078B68 00075748  2C 03 00 00 */	cmpwi r3, 0
/* 80078B6C 0007574C  40 82 00 D0 */	bne lbl_80078C3C
/* 80078B70 00075750  3B 1C 00 00 */	addi r24, r28, 0
/* 80078B74 00075754  3A E0 00 00 */	li r23, 0
/* 80078B78 00075758  48 00 00 B8 */	b lbl_80078C30
lbl_80078B7C:
/* 80078B7C 0007575C  80 18 11 E8 */	lwz r0, 0x11e8(r24)
/* 80078B80 00075760  2C 00 00 00 */	cmpwi r0, 0
/* 80078B84 00075764  41 82 00 A4 */	beq lbl_80078C28
/* 80078B88 00075768  7F 83 E3 78 */	mr r3, r28
/* 80078B8C 0007576C  48 00 6C 79 */	bl func_8007F804
/* 80078B90 00075770  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 80078B94 00075774  7C 65 1B 78 */	mr r5, r3
/* 80078B98 00075778  C0 5C 00 38 */	lfs f2, 0x38(r28)
/* 80078B9C 0007577C  7F 43 D3 78 */	mr r3, r26
/* 80078BA0 00075780  C0 7C 00 B8 */	lfs f3, 0xb8(r28)
/* 80078BA4 00075784  38 98 11 A0 */	addi r4, r24, 0x11a0
/* 80078BA8 00075788  4B F8 F3 25 */	bl lbColl_80007ECC
/* 80078BAC 0007578C  2C 03 00 00 */	cmpwi r3, 0
/* 80078BB0 00075790  41 82 00 78 */	beq lbl_80078C28
/* 80078BB4 00075794  38 7E 00 00 */	addi r3, r30, 0
/* 80078BB8 00075798  38 9C 00 00 */	addi r4, r28, 0
/* 80078BBC 0007579C  48 00 C1 29 */	bl func_80084CE4
/* 80078BC0 000757A0  2C 03 00 00 */	cmpwi r3, 0
/* 80078BC4 000757A4  40 82 00 88 */	bne lbl_80078C4C
/* 80078BC8 000757A8  38 7E 00 00 */	addi r3, r30, 0
/* 80078BCC 000757AC  38 9A 00 00 */	addi r4, r26, 0
/* 80078BD0 000757B0  38 DC 00 00 */	addi r6, r28, 0
/* 80078BD4 000757B4  38 A0 00 00 */	li r5, 0
/* 80078BD8 000757B8  38 E0 00 00 */	li r7, 0
/* 80078BDC 000757BC  4B FF DC 2D */	bl func_80076808
/* 80078BE0 000757C0  C0 3C 00 B0 */	lfs f1, 0xb0(r28)
/* 80078BE4 000757C4  C0 1E 00 B0 */	lfs f0, 0xb0(r30)
/* 80078BE8 000757C8  EC 21 00 28 */	fsubs f1, f1, f0
/* 80078BEC 000757CC  FC 01 F8 40 */	fcmpo cr0, f1, f31
/* 80078BF0 000757D0  40 80 00 08 */	bge lbl_80078BF8
/* 80078BF4 000757D4  FC 20 08 50 */	fneg f1, f1
lbl_80078BF8:
/* 80078BF8 000757D8  C0 1E 21 6C */	lfs f0, 0x216c(r30)
/* 80078BFC 000757DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80078C00 000757E0  40 80 00 4C */	bge lbl_80078C4C
/* 80078C04 000757E4  80 1C 00 00 */	lwz r0, 0(r28)
/* 80078C08 000757E8  38 60 00 01 */	li r3, 1
/* 80078C0C 000757EC  90 1E 1A 5C */	stw r0, 0x1a5c(r30)
/* 80078C10 000757F0  90 1E 1A 58 */	stw r0, 0x1a58(r30)
/* 80078C14 000757F4  88 1E 22 1B */	lbz r0, 0x221b(r30)
/* 80078C18 000757F8  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 80078C1C 000757FC  98 1E 22 1B */	stb r0, 0x221b(r30)
/* 80078C20 00075800  D0 3E 21 6C */	stfs f1, 0x216c(r30)
/* 80078C24 00075804  48 00 00 28 */	b lbl_80078C4C
lbl_80078C28:
/* 80078C28 00075808  3B 18 00 4C */	addi r24, r24, 0x4c
/* 80078C2C 0007580C  3A F7 00 01 */	addi r23, r23, 1
lbl_80078C30:
/* 80078C30 00075810  88 1C 11 9E */	lbz r0, 0x119e(r28)
/* 80078C34 00075814  7C 17 00 40 */	cmplw r23, r0
/* 80078C38 00075818  41 80 FF 44 */	blt lbl_80078B7C
lbl_80078C3C:
/* 80078C3C 0007581C  3B 7B 00 01 */	addi r27, r27, 1
/* 80078C40 00075820  28 1B 00 04 */	cmplwi r27, 4
/* 80078C44 00075824  3B FF 01 38 */	addi r31, r31, 0x138
/* 80078C48 00075828  41 80 FE C4 */	blt lbl_80078B0C
lbl_80078C4C:
/* 80078C4C 0007582C  83 BD 00 08 */	lwz r29, 8(r29)
lbl_80078C50:
/* 80078C50 00075830  28 1D 00 00 */	cmplwi r29, 0
/* 80078C54 00075834  40 82 FE 14 */	bne lbl_80078A68
/* 80078C58 00075838  BA E1 00 24 */	lmw r23, 0x24(r1)
/* 80078C5C 0007583C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80078C60 00075840  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 80078C64 00075844  38 21 00 50 */	addi r1, r1, 0x50
/* 80078C68 00075848  7C 08 03 A6 */	mtlr r0
/* 80078C6C 0007584C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

inline void ftGrabDist(Fighter* this_fp, Fighter* victim_fp)
{
    f32 grab_dist = victim_fp->xB0_pos.x - this_fp->xB0_pos.x;

    if (grab_dist < F32_MAX)
        grab_dist = -grab_dist;

    if (grab_dist < this_fp->unk_grab_val) {
        HSD_GObj* grabbed_fighter = victim_fp->x0_fighter;
        this_fp->x1A5C = grabbed_fighter;
        this_fp->x1A58_interactedFighter = grabbed_fighter;
        this_fp->x221B_b5 = true;
        this_fp->unk_grab_val = grab_dist;
    }
}

/// Checks for grabbable targets
void func_80078A2C(HSD_GObj* this_gobj)
{
    Fighter* this_fp;
    HSD_GObj* victim_gobj;
    Fighter* victim_fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    u32 i;
    HitCapsule* this_hit;
    u32 j;

    this_fp = this_gobj->user_data;
    this_fp->x1A58_interactedFighter = NULL;
    this_fp->unk_grab_val = F32_MAX;
    victim_gobj = lbl_804D782C->x20_fighters;

    while (victim_gobj != NULL) {
        if (func_80086FD4(this_gobj, victim_gobj) == false) {
            victim_fp = victim_gobj->user_data;
            if (((!(victim_fp->x2219_flag.bits.b1)) &&
                 ((!victim_fp->x222A_flag.bits.b0) &&
                  ((func_8016B168() == false) || (func_8016B0D4() != false) ||
                   ((u8) victim_fp->x61B_team != (u8) this_fp->x61B_team)) &&
                  ((s32) victim_fp->x1988 == 0) &&
                  ((s32) victim_fp->x198C == 0) &&
                  (!(victim_fp->x221D_flag.bits.b6) &&
                   !(victim_fp->x1A6A & this_fp->x1A68) &&
                   !((victim_fp->x2224_flag.bits.b2))))))
            {
                for (i = 0; i < 4; i++) {
                    this_hit = ftHitGetPtr(this_fp, i);
                    if ((this_hit->state != HitCapsule_Disabled) &&
                        (this_hit->element == (u32) HitElement_Catch) &&
                        ((((this_hit->x40_b2) &&
                           (victim_fp->ground_or_air == GA_Air)) ||
                          ((((u8) this_hit->x40_b3) &&
                            ((s32) victim_fp->ground_or_air == GA_Ground))))))
                    {
                        if (lbColl_8000ACFC(victim_fp, this_hit) == false) {
                            for (j = 0; j < victim_fp->x119E_hurtboxNum; j++) {
                                if ((s32) victim_fp->x11A0_fighterHurtbox[j]
                                        .is_grabbable != false)
                                {
                                    if (lbColl_80007ECC(
                                            this_hit,
                                            &victim_fp
                                                 ->x11A0_fighterHurtbox[j],
                                            *func_8007F804(victim_fp),
                                            this_fp->x34_scale.y,
                                            victim_fp->x34_scale.y,
                                            victim_fp->xB0_pos.z) != 0)
                                    {
                                        if (func_80084CE4(this_fp,
                                                          victim_fp) == false)
                                        {
                                            func_80076808(this_fp, this_hit, 0,
                                                          victim_fp, 0);

                                            ftGrabDist(this_fp, victim_fp);
                                        }
                                        goto next_gobj;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    next_gobj:
        victim_gobj = victim_gobj->next;
    }
}

#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80078C70(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 80078C70 00075850  7C 08 02 A6 */	mflr r0
/* 80078C74 00075854  90 01 00 04 */	stw r0, 4(r1)
/* 80078C78 00075858  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80078C7C 0007585C  DB E1 00 60 */	stfd f31, 0x60(r1)
/* 80078C80 00075860  BE 01 00 20 */	stmw r16, 0x20(r1)
/* 80078C84 00075864  7C 75 1B 78 */	mr r21, r3
/* 80078C88 00075868  83 83 00 2C */	lwz r28, 0x2c(r3)
/* 80078C8C 0007586C  48 0F 25 39 */	bl func_8016B1C4
/* 80078C90 00075870  2C 03 00 00 */	cmpwi r3, 0
/* 80078C94 00075874  40 82 05 B0 */	bne lbl_80079244
/* 80078C98 00075878  80 8D C1 8C */	lwz r4, lbl_804D782C
/* 80078C9C 0007587C  3C 60 80 3C */	lis r3, lbl_803C0C40@ha
/* 80078CA0 00075880  C3 E2 89 10 */	lfs f31, lbl_804D82F0
/* 80078CA4 00075884  3B E3 0C 40 */	addi r31, r3, lbl_803C0C40@l
/* 80078CA8 00075888  83 64 00 20 */	lwz r27, 0x20(r4)
/* 80078CAC 0007588C  3B 40 00 00 */	li r26, 0
/* 80078CB0 00075890  48 00 05 8C */	b lbl_8007923C
lbl_80078CB4:
/* 80078CB4 00075894  7C 15 D8 40 */	cmplw r21, r27
/* 80078CB8 00075898  40 82 00 0C */	bne lbl_80078CC4
/* 80078CBC 0007589C  3B 40 00 01 */	li r26, 1
/* 80078CC0 000758A0  48 00 05 78 */	b lbl_80079238
lbl_80078CC4:
/* 80078CC4 000758A4  80 7B 00 2C */	lwz r3, 0x2c(r27)
/* 80078CC8 000758A8  38 80 00 00 */	li r4, 0
/* 80078CCC 000758AC  80 03 11 98 */	lwz r0, 0x1198(r3)
/* 80078CD0 000758B0  3B 03 00 00 */	addi r24, r3, 0
/* 80078CD4 000758B4  28 00 00 00 */	cmplwi r0, 0
/* 80078CD8 000758B8  41 82 00 18 */	beq lbl_80078CF0
/* 80078CDC 000758BC  88 7C 00 0C */	lbz r3, 0xc(r28)
/* 80078CE0 000758C0  88 18 11 9D */	lbz r0, 0x119d(r24)
/* 80078CE4 000758C4  7C 03 00 40 */	cmplw r3, r0
/* 80078CE8 000758C8  41 82 05 50 */	beq lbl_80079238
/* 80078CEC 000758CC  38 80 00 01 */	li r4, 1
lbl_80078CF0:
/* 80078CF0 000758D0  2C 04 00 00 */	cmpwi r4, 0
/* 80078CF4 000758D4  40 82 00 14 */	bne lbl_80078D08
/* 80078CF8 000758D8  88 7C 00 0C */	lbz r3, 0xc(r28)
/* 80078CFC 000758DC  88 18 00 0C */	lbz r0, 0xc(r24)
/* 80078D00 000758E0  7C 03 00 40 */	cmplw r3, r0
/* 80078D04 000758E4  41 82 05 34 */	beq lbl_80079238
lbl_80078D08:
/* 80078D08 000758E8  48 0F 24 61 */	bl func_8016B168
/* 80078D0C 000758EC  2C 03 00 00 */	cmpwi r3, 0
/* 80078D10 000758F0  41 82 00 44 */	beq lbl_80078D54
/* 80078D14 000758F4  48 0F 23 C1 */	bl func_8016B0D4
/* 80078D18 000758F8  2C 03 00 00 */	cmpwi r3, 0
/* 80078D1C 000758FC  40 82 00 38 */	bne lbl_80078D54
/* 80078D20 00075900  88 18 22 25 */	lbz r0, 0x2225(r24)
/* 80078D24 00075904  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80078D28 00075908  40 82 00 2C */	bne lbl_80078D54
/* 80078D2C 0007590C  80 18 11 98 */	lwz r0, 0x1198(r24)
/* 80078D30 00075910  28 00 00 00 */	cmplwi r0, 0
/* 80078D34 00075914  41 82 00 0C */	beq lbl_80078D40
/* 80078D38 00075918  88 18 11 9C */	lbz r0, 0x119c(r24)
/* 80078D3C 0007591C  48 00 00 08 */	b lbl_80078D44
lbl_80078D40:
/* 80078D40 00075920  88 18 06 1B */	lbz r0, 0x61b(r24)
lbl_80078D44:
/* 80078D44 00075924  88 7C 06 1B */	lbz r3, 0x61b(r28)
/* 80078D48 00075928  54 00 06 3E */	clrlwi r0, r0, 0x18
/* 80078D4C 0007592C  7C 03 00 40 */	cmplw r3, r0
/* 80078D50 00075930  41 82 04 E8 */	beq lbl_80079238
lbl_80078D54:
/* 80078D54 00075934  80 18 11 98 */	lwz r0, 0x1198(r24)
/* 80078D58 00075938  7C 00 A8 40 */	cmplw r0, r21
/* 80078D5C 0007593C  41 82 04 DC */	beq lbl_80079238
/* 80078D60 00075940  2C 1A 00 00 */	cmpwi r26, 0
/* 80078D64 00075944  41 82 00 D8 */	beq lbl_80078E3C
/* 80078D68 00075948  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 80078D6C 0007594C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80078D70 00075950  40 82 00 CC */	bne lbl_80078E3C
/* 80078D74 00075954  3B DC 00 00 */	addi r30, r28, 0
/* 80078D78 00075958  3B 20 00 00 */	li r25, 0
/* 80078D7C 0007595C  3A E0 00 00 */	li r23, 0
/* 80078D80 00075960  3B AD AE C0 */	addi r29, r13, lbl_804D6560
lbl_80078D84:
/* 80078D84 00075964  80 1E 09 14 */	lwz r0, 0x914(r30)
/* 80078D88 00075968  38 9E 09 14 */	addi r4, r30, 0x914
/* 80078D8C 0007596C  2C 00 00 00 */	cmpwi r0, 0
/* 80078D90 00075970  41 82 00 90 */	beq lbl_80078E20
/* 80078D94 00075974  88 04 00 43 */	lbz r0, 0x43(r4)
/* 80078D98 00075978  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80078D9C 0007597C  40 82 00 84 */	bne lbl_80078E20
/* 80078DA0 00075980  80 04 00 30 */	lwz r0, 0x30(r4)
/* 80078DA4 00075984  28 00 00 08 */	cmplwi r0, 8
/* 80078DA8 00075988  41 82 00 78 */	beq lbl_80078E20
/* 80078DAC 0007598C  28 00 00 0B */	cmplwi r0, 0xb
/* 80078DB0 00075990  41 82 00 70 */	beq lbl_80078E20
/* 80078DB4 00075994  88 64 00 40 */	lbz r3, 0x40(r4)
/* 80078DB8 00075998  54 60 CF FE */	rlwinm r0, r3, 0x19, 0x1f, 0x1f
/* 80078DBC 0007599C  28 00 00 01 */	cmplwi r0, 1
/* 80078DC0 000759A0  40 82 00 60 */	bne lbl_80078E20
/* 80078DC4 000759A4  88 04 00 42 */	lbz r0, 0x42(r4)
/* 80078DC8 000759A8  54 00 F7 FE */	rlwinm r0, r0, 0x1e, 0x1f, 0x1f
/* 80078DCC 000759AC  28 00 00 01 */	cmplwi r0, 1
/* 80078DD0 000759B0  40 82 00 50 */	bne lbl_80078E20
/* 80078DD4 000759B4  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 80078DD8 000759B8  41 82 00 10 */	beq lbl_80078DE8
/* 80078DDC 000759BC  80 18 00 E0 */	lwz r0, 0xe0(r24)
/* 80078DE0 000759C0  2C 00 00 01 */	cmpwi r0, 1
/* 80078DE4 000759C4  41 82 00 1C */	beq lbl_80078E00
lbl_80078DE8:
/* 80078DE8 000759C8  88 04 00 40 */	lbz r0, 0x40(r4)
/* 80078DEC 000759CC  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80078DF0 000759D0  41 82 00 30 */	beq lbl_80078E20
/* 80078DF4 000759D4  80 18 00 E0 */	lwz r0, 0xe0(r24)
/* 80078DF8 000759D8  2C 00 00 00 */	cmpwi r0, 0
/* 80078DFC 000759DC  40 82 00 24 */	bne lbl_80078E20
lbl_80078E00:
/* 80078E00 000759E0  7F 03 C3 78 */	mr r3, r24
/* 80078E04 000759E4  4B F9 1E F9 */	bl lbColl_8000ACFC
/* 80078E08 000759E8  2C 03 00 00 */	cmpwi r3, 0
/* 80078E0C 000759EC  40 82 00 14 */	bne lbl_80078E20
/* 80078E10 000759F0  38 00 00 01 */	li r0, 1
/* 80078E14 000759F4  98 1D 00 00 */	stb r0, 0(r29)
/* 80078E18 000759F8  3B 39 00 01 */	addi r25, r25, 1
/* 80078E1C 000759FC  48 00 00 0C */	b lbl_80078E28
lbl_80078E20:
/* 80078E20 00075A00  38 00 00 00 */	li r0, 0
/* 80078E24 00075A04  98 1D 00 00 */	stb r0, 0(r29)
lbl_80078E28:
/* 80078E28 00075A08  3A F7 00 01 */	addi r23, r23, 1
/* 80078E2C 00075A0C  28 17 00 04 */	cmplwi r23, 4
/* 80078E30 00075A10  3B DE 01 38 */	addi r30, r30, 0x138
/* 80078E34 00075A14  3B BD 00 01 */	addi r29, r29, 1
/* 80078E38 00075A18  41 80 FF 4C */	blt lbl_80078D84
lbl_80078E3C:
/* 80078E3C 00075A1C  3B C0 00 00 */	li r30, 0
/* 80078E40 00075A20  3B B8 00 00 */	addi r29, r24, 0
lbl_80078E44:
/* 80078E44 00075A24  80 1D 09 14 */	lwz r0, 0x914(r29)
/* 80078E48 00075A28  3A FD 09 14 */	addi r23, r29, 0x914
/* 80078E4C 00075A2C  2C 00 00 00 */	cmpwi r0, 0
/* 80078E50 00075A30  41 82 03 D8 */	beq lbl_80079228
/* 80078E54 00075A34  80 17 00 30 */	lwz r0, 0x30(r23)
/* 80078E58 00075A38  28 00 00 08 */	cmplwi r0, 8
/* 80078E5C 00075A3C  41 82 03 CC */	beq lbl_80079228
/* 80078E60 00075A40  88 17 00 42 */	lbz r0, 0x42(r23)
/* 80078E64 00075A44  54 00 F7 FE */	rlwinm r0, r0, 0x1e, 0x1f, 0x1f
/* 80078E68 00075A48  28 00 00 01 */	cmplwi r0, 1
/* 80078E6C 00075A4C  40 82 03 BC */	bne lbl_80079228
/* 80078E70 00075A50  88 17 00 40 */	lbz r0, 0x40(r23)
/* 80078E74 00075A54  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80078E78 00075A58  41 82 00 10 */	beq lbl_80078E88
/* 80078E7C 00075A5C  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80078E80 00075A60  2C 00 00 01 */	cmpwi r0, 1
/* 80078E84 00075A64  41 82 00 1C */	beq lbl_80078EA0
lbl_80078E88:
/* 80078E88 00075A68  88 17 00 40 */	lbz r0, 0x40(r23)
/* 80078E8C 00075A6C  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80078E90 00075A70  41 82 03 98 */	beq lbl_80079228
/* 80078E94 00075A74  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80078E98 00075A78  2C 00 00 00 */	cmpwi r0, 0
/* 80078E9C 00075A7C  40 82 03 8C */	bne lbl_80079228
lbl_80078EA0:
/* 80078EA0 00075A80  88 17 01 34 */	lbz r0, 0x134(r23)
/* 80078EA4 00075A84  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80078EA8 00075A88  41 82 00 24 */	beq lbl_80078ECC
/* 80078EAC 00075A8C  80 78 1A 58 */	lwz r3, 0x1a58(r24)
/* 80078EB0 00075A90  28 03 00 00 */	cmplwi r3, 0
/* 80078EB4 00075A94  41 82 00 18 */	beq lbl_80078ECC
/* 80078EB8 00075A98  88 18 22 1B */	lbz r0, 0x221b(r24)
/* 80078EBC 00075A9C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80078EC0 00075AA0  41 82 00 0C */	beq lbl_80078ECC
/* 80078EC4 00075AA4  7C 03 A8 40 */	cmplw r3, r21
/* 80078EC8 00075AA8  40 82 03 60 */	bne lbl_80079228
lbl_80078ECC:
/* 80078ECC 00075AAC  38 7C 00 00 */	addi r3, r28, 0
/* 80078ED0 00075AB0  38 97 00 00 */	addi r4, r23, 0
/* 80078ED4 00075AB4  4B F9 1E 29 */	bl lbColl_8000ACFC
/* 80078ED8 00075AB8  2C 03 00 00 */	cmpwi r3, 0
/* 80078EDC 00075ABC  40 82 03 4C */	bne lbl_80079228
/* 80078EE0 00075AC0  88 17 00 43 */	lbz r0, 0x43(r23)
/* 80078EE4 00075AC4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80078EE8 00075AC8  41 82 00 0C */	beq lbl_80078EF4
/* 80078EEC 00075ACC  38 00 00 01 */	li r0, 1
/* 80078EF0 00075AD0  48 00 00 08 */	b lbl_80078EF8
lbl_80078EF4:
/* 80078EF4 00075AD4  38 00 00 00 */	li r0, 0
lbl_80078EF8:
/* 80078EF8 00075AD8  2C 1A 00 00 */	cmpwi r26, 0
/* 80078EFC 00075ADC  7C 16 03 78 */	mr r22, r0
/* 80078F00 00075AE0  41 82 00 DC */	beq lbl_80078FDC
/* 80078F04 00075AE4  2C 00 00 00 */	cmpwi r0, 0
/* 80078F08 00075AE8  40 82 00 D4 */	bne lbl_80078FDC
/* 80078F0C 00075AEC  80 18 1A 58 */	lwz r0, 0x1a58(r24)
/* 80078F10 00075AF0  7C 15 00 40 */	cmplw r21, r0
/* 80078F14 00075AF4  41 82 00 C8 */	beq lbl_80078FDC
/* 80078F18 00075AF8  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80078F1C 00075AFC  2C 00 00 00 */	cmpwi r0, 0
/* 80078F20 00075B00  40 82 00 BC */	bne lbl_80078FDC
/* 80078F24 00075B04  80 18 00 E0 */	lwz r0, 0xe0(r24)
/* 80078F28 00075B08  2C 00 00 00 */	cmpwi r0, 0
/* 80078F2C 00075B0C  40 82 00 B0 */	bne lbl_80078FDC
/* 80078F30 00075B10  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 80078F34 00075B14  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80078F38 00075B18  40 82 00 A4 */	bne lbl_80078FDC
/* 80078F3C 00075B1C  80 17 00 30 */	lwz r0, 0x30(r23)
/* 80078F40 00075B20  28 00 00 0B */	cmplwi r0, 0xb
/* 80078F44 00075B24  41 82 00 98 */	beq lbl_80078FDC
/* 80078F48 00075B28  88 17 00 40 */	lbz r0, 0x40(r23)
/* 80078F4C 00075B2C  54 00 CF FE */	rlwinm r0, r0, 0x19, 0x1f, 0x1f
/* 80078F50 00075B30  28 00 00 01 */	cmplwi r0, 1
/* 80078F54 00075B34  40 82 00 88 */	bne lbl_80078FDC
/* 80078F58 00075B38  2C 19 00 00 */	cmpwi r25, 0
/* 80078F5C 00075B3C  41 82 00 80 */	beq lbl_80078FDC
/* 80078F60 00075B40  3A 7C 00 00 */	addi r19, r28, 0
/* 80078F64 00075B44  3A 20 00 00 */	li r17, 0
/* 80078F68 00075B48  3A 40 00 00 */	li r18, 0
/* 80078F6C 00075B4C  3A 8D AE C0 */	addi r20, r13, lbl_804D6560
lbl_80078F70:
/* 80078F70 00075B50  88 14 00 00 */	lbz r0, 0(r20)
/* 80078F74 00075B54  28 00 00 00 */	cmplwi r0, 0
/* 80078F78 00075B58  41 82 00 48 */	beq lbl_80078FC0
/* 80078F7C 00075B5C  3A 13 09 14 */	addi r16, r19, 0x914
/* 80078F80 00075B60  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 80078F84 00075B64  C0 5C 00 38 */	lfs f2, 0x38(r28)
/* 80078F88 00075B68  38 77 00 00 */	addi r3, r23, 0
/* 80078F8C 00075B6C  38 90 00 00 */	addi r4, r16, 0
/* 80078F90 00075B70  4B F8 EB 6D */	bl lbColl_80007AFC
/* 80078F94 00075B74  2C 03 00 00 */	cmpwi r3, 0
/* 80078F98 00075B78  41 82 00 28 */	beq lbl_80078FC0
/* 80078F9C 00075B7C  38 78 00 00 */	addi r3, r24, 0
/* 80078FA0 00075B80  38 97 00 00 */	addi r4, r23, 0
/* 80078FA4 00075B84  38 BC 00 00 */	addi r5, r28, 0
/* 80078FA8 00075B88  38 D0 00 00 */	addi r6, r16, 0
/* 80078FAC 00075B8C  4B FF D9 F1 */	bl func_8007699C
/* 80078FB0 00075B90  2C 03 00 00 */	cmpwi r3, 0
/* 80078FB4 00075B94  41 82 00 0C */	beq lbl_80078FC0
/* 80078FB8 00075B98  3A 20 00 01 */	li r17, 1
/* 80078FBC 00075B9C  48 00 00 18 */	b lbl_80078FD4
lbl_80078FC0:
/* 80078FC0 00075BA0  3A 52 00 01 */	addi r18, r18, 1
/* 80078FC4 00075BA4  28 12 00 04 */	cmplwi r18, 4
/* 80078FC8 00075BA8  3A 94 00 01 */	addi r20, r20, 1
/* 80078FCC 00075BAC  3A 73 01 38 */	addi r19, r19, 0x138
/* 80078FD0 00075BB0  41 80 FF A0 */	blt lbl_80078F70
lbl_80078FD4:
/* 80078FD4 00075BB4  2C 11 00 00 */	cmpwi r17, 0
/* 80078FD8 00075BB8  40 82 02 50 */	bne lbl_80079228
lbl_80078FDC:
/* 80078FDC 00075BBC  88 7C 22 1B */	lbz r3, 0x221b(r28)
/* 80078FE0 00075BC0  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80078FE4 00075BC4  41 82 00 D0 */	beq lbl_800790B4
/* 80078FE8 00075BC8  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 80078FEC 00075BCC  38 60 00 01 */	li r3, 1
/* 80078FF0 00075BD0  41 82 00 3C */	beq lbl_8007902C
/* 80078FF4 00075BD4  C0 1C 00 2C */	lfs f0, 0x2c(r28)
/* 80078FF8 00075BD8  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 80078FFC 00075BDC  40 82 00 1C */	bne lbl_80079018
/* 80079000 00075BE0  C0 3C 00 B0 */	lfs f1, 0xb0(r28)
/* 80079004 00075BE4  C0 18 00 B0 */	lfs f0, 0xb0(r24)
/* 80079008 00075BE8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007900C 00075BEC  40 80 00 20 */	bge lbl_8007902C
/* 80079010 00075BF0  38 60 00 00 */	li r3, 0
/* 80079014 00075BF4  48 00 00 18 */	b lbl_8007902C
lbl_80079018:
/* 80079018 00075BF8  C0 3C 00 B0 */	lfs f1, 0xb0(r28)
/* 8007901C 00075BFC  C0 18 00 B0 */	lfs f0, 0xb0(r24)
/* 80079020 00075C00  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80079024 00075C04  40 81 00 08 */	ble lbl_8007902C
/* 80079028 00075C08  38 60 00 00 */	li r3, 0
lbl_8007902C:
/* 8007902C 00075C0C  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 80079030 00075C10  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80079034 00075C14  41 82 00 14 */	beq lbl_80079048
/* 80079038 00075C18  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007903C 00075C1C  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80079040 00075C20  40 82 00 08 */	bne lbl_80079048
/* 80079044 00075C24  38 60 00 00 */	li r3, 0
lbl_80079048:
/* 80079048 00075C28  2C 03 00 00 */	cmpwi r3, 0
/* 8007904C 00075C2C  41 82 00 68 */	beq lbl_800790B4
/* 80079050 00075C30  7F 83 E3 78 */	mr r3, r28
/* 80079054 00075C34  48 00 67 B1 */	bl func_8007F804
/* 80079058 00075C38  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 8007905C 00075C3C  7C 65 1B 78 */	mr r5, r3
/* 80079060 00075C40  C0 5C 00 38 */	lfs f2, 0x38(r28)
/* 80079064 00075C44  7E E3 BB 78 */	mr r3, r23
/* 80079068 00075C48  C0 7C 00 B8 */	lfs f3, 0xb8(r28)
/* 8007906C 00075C4C  38 D6 00 00 */	addi r6, r22, 0
/* 80079070 00075C50  38 9C 19 C0 */	addi r4, r28, 0x19c0
/* 80079074 00075C54  4B F8 EB 59 */	bl lbColl_80007BCC
/* 80079078 00075C58  2C 03 00 00 */	cmpwi r3, 0
/* 8007907C 00075C5C  41 82 00 38 */	beq lbl_800790B4
/* 80079080 00075C60  80 17 00 30 */	lwz r0, 0x30(r23)
/* 80079084 00075C64  28 00 00 0B */	cmplwi r0, 0xb
/* 80079088 00075C68  41 82 00 18 */	beq lbl_800790A0
/* 8007908C 00075C6C  38 78 00 00 */	addi r3, r24, 0
/* 80079090 00075C70  38 97 00 00 */	addi r4, r23, 0
/* 80079094 00075C74  38 BC 00 00 */	addi r5, r28, 0
/* 80079098 00075C78  4B FF DC 25 */	bl func_80076CBC
/* 8007909C 00075C7C  48 00 01 8C */	b lbl_80079228
lbl_800790A0:
/* 800790A0 00075C80  88 18 22 1C */	lbz r0, 0x221c(r24)
/* 800790A4 00075C84  38 60 00 01 */	li r3, 1
/* 800790A8 00075C88  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 800790AC 00075C8C  98 18 22 1C */	stb r0, 0x221c(r24)
/* 800790B0 00075C90  92 B8 20 AC */	stw r21, 0x20ac(r24)
lbl_800790B4:
/* 800790B4 00075C94  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 800790B8 00075C98  2C 00 00 02 */	cmpwi r0, 2
/* 800790BC 00075C9C  41 82 01 6C */	beq lbl_80079228
/* 800790C0 00075CA0  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 800790C4 00075CA4  2C 00 00 02 */	cmpwi r0, 2
/* 800790C8 00075CA8  41 82 01 60 */	beq lbl_80079228
/* 800790CC 00075CAC  3A 80 00 00 */	li r20, 0
/* 800790D0 00075CB0  1C 14 00 4C */	mulli r0, r20, 0x4c
/* 800790D4 00075CB4  7E 7C 02 14 */	add r19, r28, r0
/* 800790D8 00075CB8  48 00 01 44 */	b lbl_8007921C
lbl_800790DC:
/* 800790DC 00075CBC  7F 83 E3 78 */	mr r3, r28
/* 800790E0 00075CC0  48 00 67 25 */	bl func_8007F804
/* 800790E4 00075CC4  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 800790E8 00075CC8  7C 65 1B 78 */	mr r5, r3
/* 800790EC 00075CCC  C0 5C 00 38 */	lfs f2, 0x38(r28)
/* 800790F0 00075CD0  7E E3 BB 78 */	mr r3, r23
/* 800790F4 00075CD4  C0 7C 00 B8 */	lfs f3, 0xb8(r28)
/* 800790F8 00075CD8  38 D6 00 00 */	addi r6, r22, 0
/* 800790FC 00075CDC  38 93 11 A0 */	addi r4, r19, 0x11a0
/* 80079100 00075CE0  4B F8 EF 5D */	bl lbColl_8000805C
/* 80079104 00075CE4  2C 03 00 00 */	cmpwi r3, 0
/* 80079108 00075CE8  41 82 01 0C */	beq lbl_80079214
/* 8007910C 00075CEC  80 17 00 30 */	lwz r0, 0x30(r23)
/* 80079110 00075CF0  28 00 00 0B */	cmplwi r0, 0xb
/* 80079114 00075CF4  41 82 00 F8 */	beq lbl_8007920C
/* 80079118 00075CF8  1C 74 00 4C */	mulli r3, r20, 0x4c
/* 8007911C 00075CFC  3A 63 11 A0 */	addi r19, r3, 0x11a0
/* 80079120 00075D00  7E 7C 9A 14 */	add r19, r28, r19
/* 80079124 00075D04  38 78 00 00 */	addi r3, r24, 0
/* 80079128 00075D08  38 97 00 00 */	addi r4, r23, 0
/* 8007912C 00075D0C  38 BC 00 00 */	addi r5, r28, 0
/* 80079130 00075D10  38 D3 00 00 */	addi r6, r19, 0
/* 80079134 00075D14  4B FF DD A5 */	bl func_80076ED8
/* 80079138 00075D18  2C 03 00 00 */	cmpwi r3, 0
/* 8007913C 00075D1C  41 82 00 EC */	beq lbl_80079228
/* 80079140 00075D20  80 1C 19 88 */	lwz r0, 0x1988(r28)
/* 80079144 00075D24  2C 00 00 00 */	cmpwi r0, 0
/* 80079148 00075D28  40 82 00 28 */	bne lbl_80079170
/* 8007914C 00075D2C  80 1C 19 8C */	lwz r0, 0x198c(r28)
/* 80079150 00075D30  2C 00 00 00 */	cmpwi r0, 0
/* 80079154 00075D34  40 82 00 1C */	bne lbl_80079170
/* 80079158 00075D38  88 1C 22 1D */	lbz r0, 0x221d(r28)
/* 8007915C 00075D3C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80079160 00075D40  40 82 00 10 */	bne lbl_80079170
/* 80079164 00075D44  80 13 00 00 */	lwz r0, 0(r19)
/* 80079168 00075D48  2C 00 00 00 */	cmpwi r0, 0
/* 8007916C 00075D4C  41 82 00 2C */	beq lbl_80079198
lbl_80079170:
/* 80079170 00075D50  80 17 00 38 */	lwz r0, 0x38(r23)
/* 80079174 00075D54  38 7C 00 00 */	addi r3, r28, 0
/* 80079178 00075D58  38 A0 00 7F */	li r5, 0x7f
/* 8007917C 00075D5C  54 00 10 3A */	slwi r0, r0, 2
/* 80079180 00075D60  7C 9F 02 14 */	add r4, r31, r0
/* 80079184 00075D64  80 84 00 00 */	lwz r4, 0(r4)
/* 80079188 00075D68  38 C0 00 40 */	li r6, 0x40
/* 8007918C 00075D6C  48 00 EF BD */	bl func_80088148
/* 80079190 00075D70  38 00 00 01 */	li r0, 1
/* 80079194 00075D74  48 00 00 08 */	b lbl_8007919C
lbl_80079198:
/* 80079198 00075D78  38 00 00 00 */	li r0, 0
lbl_8007919C:
/* 8007919C 00075D7C  2C 00 00 00 */	cmpwi r0, 0
/* 800791A0 00075D80  40 82 00 88 */	bne lbl_80079228
/* 800791A4 00075D84  80 17 00 3C */	lwz r0, 0x3c(r23)
/* 800791A8 00075D88  28 00 00 0D */	cmplwi r0, 0xd
/* 800791AC 00075D8C  40 82 00 38 */	bne lbl_800791E4
/* 800791B0 00075D90  80 17 00 38 */	lwz r0, 0x38(r23)
/* 800791B4 00075D94  28 00 00 02 */	cmplwi r0, 2
/* 800791B8 00075D98  40 82 00 2C */	bne lbl_800791E4
/* 800791BC 00075D9C  88 9C 22 1F */	lbz r4, 0x221f(r28)
/* 800791C0 00075DA0  7E E3 BB 78 */	mr r3, r23
/* 800791C4 00075DA4  88 1C 00 0C */	lbz r0, 0xc(r28)
/* 800791C8 00075DA8  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800791CC 00075DAC  54 00 08 3C */	slwi r0, r0, 1
/* 800791D0 00075DB0  7C 80 22 14 */	add r4, r0, r4
/* 800791D4 00075DB4  38 84 00 72 */	addi r4, r4, 0x72
/* 800791D8 00075DB8  4B F8 C9 D9 */	bl lbColl_80005BB0
/* 800791DC 00075DBC  90 7C 21 5C */	stw r3, 0x215c(r28)
/* 800791E0 00075DC0  48 00 00 48 */	b lbl_80079228
lbl_800791E4:
/* 800791E4 00075DC4  88 9C 22 1F */	lbz r4, 0x221f(r28)
/* 800791E8 00075DC8  7E E3 BB 78 */	mr r3, r23
/* 800791EC 00075DCC  88 1C 00 0C */	lbz r0, 0xc(r28)
/* 800791F0 00075DD0  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800791F4 00075DD4  54 00 08 3C */	slwi r0, r0, 1
/* 800791F8 00075DD8  7C 80 22 14 */	add r4, r0, r4
/* 800791FC 00075DDC  38 84 00 7E */	addi r4, r4, 0x7e
/* 80079200 00075DE0  4B F8 C9 B1 */	bl lbColl_80005BB0
/* 80079204 00075DE4  90 7C 21 60 */	stw r3, 0x2160(r28)
/* 80079208 00075DE8  48 00 00 20 */	b lbl_80079228
lbl_8007920C:
/* 8007920C 00075DEC  92 B8 20 AC */	stw r21, 0x20ac(r24)
/* 80079210 00075DF0  48 00 00 18 */	b lbl_80079228
lbl_80079214:
/* 80079214 00075DF4  3A 73 00 4C */	addi r19, r19, 0x4c
/* 80079218 00075DF8  3A 94 00 01 */	addi r20, r20, 1
lbl_8007921C:
/* 8007921C 00075DFC  88 1C 11 9E */	lbz r0, 0x119e(r28)
/* 80079220 00075E00  7C 14 00 40 */	cmplw r20, r0
/* 80079224 00075E04  41 80 FE B8 */	blt lbl_800790DC
lbl_80079228:
/* 80079228 00075E08  3B DE 00 01 */	addi r30, r30, 1
/* 8007922C 00075E0C  28 1E 00 04 */	cmplwi r30, 4
/* 80079230 00075E10  3B BD 01 38 */	addi r29, r29, 0x138
/* 80079234 00075E14  41 80 FC 10 */	blt lbl_80078E44
lbl_80079238:
/* 80079238 00075E18  83 7B 00 08 */	lwz r27, 8(r27)
lbl_8007923C:
/* 8007923C 00075E1C  28 1B 00 00 */	cmplwi r27, 0
/* 80079240 00075E20  40 82 FA 74 */	bne lbl_80078CB4
lbl_80079244:
/* 80079244 00075E24  BA 01 00 20 */	lmw r16, 0x20(r1)
/* 80079248 00075E28  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8007924C 00075E2C  CB E1 00 60 */	lfd f31, 0x60(r1)
/* 80079250 00075E30  38 21 00 68 */	addi r1, r1, 0x68
/* 80079254 00075E34  7C 08 03 A6 */	mtlr r0
/* 80079258 00075E38  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007925C(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007925C 00075E3C  7C 08 02 A6 */	mflr r0
/* 80079260 00075E40  90 01 00 04 */	stw r0, 4(r1)
/* 80079264 00075E44  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 80079268 00075E48  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 8007926C 00075E4C  DB C1 00 80 */	stfd f30, 0x80(r1)
/* 80079270 00075E50  BE 21 00 44 */	stmw r17, 0x44(r1)
/* 80079274 00075E54  3B E3 00 00 */	addi r31, r3, 0
/* 80079278 00075E58  3C 60 80 3C */	lis r3, lbl_803C0C40@ha
/* 8007927C 00075E5C  3B C3 0C 40 */	addi r30, r3, lbl_803C0C40@l
/* 80079280 00075E60  80 8D C1 8C */	lwz r4, lbl_804D782C
/* 80079284 00075E64  83 7F 00 2C */	lwz r27, 0x2c(r31)
/* 80079288 00075E68  83 44 00 24 */	lwz r26, 0x24(r4)
/* 8007928C 00075E6C  C3 E2 89 10 */	lfs f31, lbl_804D82F0
/* 80079290 00075E70  C3 C2 89 00 */	lfs f30, lbl_804D82E0
/* 80079294 00075E74  48 00 07 F8 */	b lbl_80079A8C
lbl_80079298:
/* 80079298 00075E78  80 7A 00 2C */	lwz r3, 0x2c(r26)
/* 8007929C 00075E7C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 800792A0 00075E80  3B 03 00 00 */	addi r24, r3, 0
/* 800792A4 00075E84  2C 00 00 9E */	cmpwi r0, 0x9e
/* 800792A8 00075E88  41 82 07 E0 */	beq lbl_80079A88
/* 800792AC 00075E8C  7F E3 FB 78 */	mr r3, r31
/* 800792B0 00075E90  80 98 05 18 */	lwz r4, 0x518(r24)
/* 800792B4 00075E94  48 00 DD 21 */	bl func_80086FD4
/* 800792B8 00075E98  2C 03 00 00 */	cmpwi r3, 0
/* 800792BC 00075E9C  41 82 00 10 */	beq lbl_800792CC
/* 800792C0 00075EA0  88 18 0D CD */	lbz r0, 0xdcd(r24)
/* 800792C4 00075EA4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800792C8 00075EA8  41 82 07 C0 */	beq lbl_80079A88
lbl_800792CC:
/* 800792CC 00075EAC  48 0F 1E 9D */	bl func_8016B168
/* 800792D0 00075EB0  2C 03 00 00 */	cmpwi r3, 0
/* 800792D4 00075EB4  41 82 00 2C */	beq lbl_80079300
/* 800792D8 00075EB8  48 0F 1D FD */	bl func_8016B0D4
/* 800792DC 00075EBC  2C 03 00 00 */	cmpwi r3, 0
/* 800792E0 00075EC0  40 82 00 20 */	bne lbl_80079300
/* 800792E4 00075EC4  88 18 0D CD */	lbz r0, 0xdcd(r24)
/* 800792E8 00075EC8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800792EC 00075ECC  40 82 00 14 */	bne lbl_80079300
/* 800792F0 00075ED0  88 78 00 20 */	lbz r3, 0x20(r24)
/* 800792F4 00075ED4  88 1B 06 1B */	lbz r0, 0x61b(r27)
/* 800792F8 00075ED8  7C 03 00 40 */	cmplw r3, r0
/* 800792FC 00075EDC  41 82 07 8C */	beq lbl_80079A88
lbl_80079300:
/* 80079300 00075EE0  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 80079304 00075EE4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80079308 00075EE8  40 82 01 18 */	bne lbl_80079420
/* 8007930C 00075EEC  80 7B 11 98 */	lwz r3, 0x1198(r27)
/* 80079310 00075EF0  3B 20 00 00 */	li r25, 0
/* 80079314 00075EF4  28 03 00 00 */	cmplwi r3, 0
/* 80079318 00075EF8  41 82 00 54 */	beq lbl_8007936C
/* 8007931C 00075EFC  80 98 05 18 */	lwz r4, 0x518(r24)
/* 80079320 00075F00  48 00 DC B5 */	bl func_80086FD4
/* 80079324 00075F04  2C 03 00 00 */	cmpwi r3, 0
/* 80079328 00075F08  41 82 00 10 */	beq lbl_80079338
/* 8007932C 00075F0C  88 18 0D CD */	lbz r0, 0xdcd(r24)
/* 80079330 00075F10  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80079334 00075F14  41 82 00 EC */	beq lbl_80079420
lbl_80079338:
/* 80079338 00075F18  48 0F 1E 31 */	bl func_8016B168
/* 8007933C 00075F1C  2C 03 00 00 */	cmpwi r3, 0
/* 80079340 00075F20  41 82 00 2C */	beq lbl_8007936C
/* 80079344 00075F24  48 0F 1D 91 */	bl func_8016B0D4
/* 80079348 00075F28  2C 03 00 00 */	cmpwi r3, 0
/* 8007934C 00075F2C  40 82 00 20 */	bne lbl_8007936C
/* 80079350 00075F30  88 18 0D CD */	lbz r0, 0xdcd(r24)
/* 80079354 00075F34  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80079358 00075F38  40 82 00 14 */	bne lbl_8007936C
/* 8007935C 00075F3C  88 78 00 20 */	lbz r3, 0x20(r24)
/* 80079360 00075F40  88 1B 11 9C */	lbz r0, 0x119c(r27)
/* 80079364 00075F44  7C 03 00 40 */	cmplw r3, r0
/* 80079368 00075F48  41 82 00 B8 */	beq lbl_80079420
lbl_8007936C:
/* 8007936C 00075F4C  3A DB 00 00 */	addi r22, r27, 0
/* 80079370 00075F50  3A 80 00 00 */	li r20, 0
/* 80079374 00075F54  3A ED AE C0 */	addi r23, r13, lbl_804D6560
lbl_80079378:
/* 80079378 00075F58  38 76 09 14 */	addi r3, r22, 0x914
/* 8007937C 00075F5C  80 16 09 14 */	lwz r0, 0x914(r22)
/* 80079380 00075F60  38 83 00 00 */	addi r4, r3, 0
/* 80079384 00075F64  2C 00 00 00 */	cmpwi r0, 0
/* 80079388 00075F68  41 82 00 7C */	beq lbl_80079404
/* 8007938C 00075F6C  88 03 00 43 */	lbz r0, 0x43(r3)
/* 80079390 00075F70  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80079394 00075F74  40 82 00 70 */	bne lbl_80079404
/* 80079398 00075F78  80 03 00 30 */	lwz r0, 0x30(r3)
/* 8007939C 00075F7C  28 00 00 08 */	cmplwi r0, 8
/* 800793A0 00075F80  41 82 00 64 */	beq lbl_80079404
/* 800793A4 00075F84  88 03 00 42 */	lbz r0, 0x42(r3)
/* 800793A8 00075F88  54 00 F7 FE */	rlwinm r0, r0, 0x1e, 0x1f, 0x1f
/* 800793AC 00075F8C  28 00 00 01 */	cmplwi r0, 1
/* 800793B0 00075F90  40 82 00 54 */	bne lbl_80079404
/* 800793B4 00075F94  88 03 00 40 */	lbz r0, 0x40(r3)
/* 800793B8 00075F98  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800793BC 00075F9C  41 82 00 10 */	beq lbl_800793CC
/* 800793C0 00075FA0  80 18 00 C0 */	lwz r0, 0xc0(r24)
/* 800793C4 00075FA4  2C 00 00 01 */	cmpwi r0, 1
/* 800793C8 00075FA8  41 82 00 1C */	beq lbl_800793E4
lbl_800793CC:
/* 800793CC 00075FAC  88 03 00 40 */	lbz r0, 0x40(r3)
/* 800793D0 00075FB0  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800793D4 00075FB4  41 82 00 30 */	beq lbl_80079404
/* 800793D8 00075FB8  80 18 00 C0 */	lwz r0, 0xc0(r24)
/* 800793DC 00075FBC  2C 00 00 00 */	cmpwi r0, 0
/* 800793E0 00075FC0  40 82 00 24 */	bne lbl_80079404
lbl_800793E4:
/* 800793E4 00075FC4  7F 03 C3 78 */	mr r3, r24
/* 800793E8 00075FC8  4B F9 19 15 */	bl lbColl_8000ACFC
/* 800793EC 00075FCC  2C 03 00 00 */	cmpwi r3, 0
/* 800793F0 00075FD0  40 82 00 14 */	bne lbl_80079404
/* 800793F4 00075FD4  38 00 00 01 */	li r0, 1
/* 800793F8 00075FD8  98 17 00 00 */	stb r0, 0(r23)
/* 800793FC 00075FDC  3B 39 00 01 */	addi r25, r25, 1
/* 80079400 00075FE0  48 00 00 0C */	b lbl_8007940C
lbl_80079404:
/* 80079404 00075FE4  38 00 00 00 */	li r0, 0
/* 80079408 00075FE8  98 17 00 00 */	stb r0, 0(r23)
lbl_8007940C:
/* 8007940C 00075FEC  3A 94 00 01 */	addi r20, r20, 1
/* 80079410 00075FF0  28 14 00 04 */	cmplwi r20, 4
/* 80079414 00075FF4  3A D6 01 38 */	addi r22, r22, 0x138
/* 80079418 00075FF8  3A F7 00 01 */	addi r23, r23, 1
/* 8007941C 00075FFC  41 80 FF 5C */	blt lbl_80079378
lbl_80079420:
/* 80079420 00076000  3B 80 00 00 */	li r28, 0
/* 80079424 00076004  3B B8 00 00 */	addi r29, r24, 0
lbl_80079428:
/* 80079428 00076008  80 1D 05 D4 */	lwz r0, 0x5d4(r29)
/* 8007942C 0007600C  3A FD 05 D4 */	addi r23, r29, 0x5d4
/* 80079430 00076010  2C 00 00 00 */	cmpwi r0, 0
/* 80079434 00076014  41 82 06 44 */	beq lbl_80079A78
/* 80079438 00076018  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007943C 0007601C  54 00 F7 FE */	rlwinm r0, r0, 0x1e, 0x1f, 0x1f
/* 80079440 00076020  28 00 00 01 */	cmplwi r0, 1
/* 80079444 00076024  40 82 06 34 */	bne lbl_80079A78
/* 80079448 00076028  88 17 00 40 */	lbz r0, 0x40(r23)
/* 8007944C 0007602C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80079450 00076030  41 82 00 10 */	beq lbl_80079460
/* 80079454 00076034  80 1B 00 E0 */	lwz r0, 0xe0(r27)
/* 80079458 00076038  2C 00 00 01 */	cmpwi r0, 1
/* 8007945C 0007603C  41 82 00 1C */	beq lbl_80079478
lbl_80079460:
/* 80079460 00076040  88 17 00 40 */	lbz r0, 0x40(r23)
/* 80079464 00076044  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80079468 00076048  41 82 06 10 */	beq lbl_80079A78
/* 8007946C 0007604C  80 1B 00 E0 */	lwz r0, 0xe0(r27)
/* 80079470 00076050  2C 00 00 00 */	cmpwi r0, 0
/* 80079474 00076054  40 82 06 04 */	bne lbl_80079A78
lbl_80079478:
/* 80079478 00076058  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007947C 0007605C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80079480 00076060  41 82 00 14 */	beq lbl_80079494
/* 80079484 00076064  C0 3B 00 2C */	lfs f1, 0x2c(r27)
/* 80079488 00076068  C0 18 00 2C */	lfs f0, 0x2c(r24)
/* 8007948C 0007606C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80079490 00076070  41 82 05 E8 */	beq lbl_80079A78
lbl_80079494:
/* 80079494 00076074  48 0F 1D 31 */	bl func_8016B1C4
/* 80079498 00076078  2C 03 00 00 */	cmpwi r3, 0
/* 8007949C 0007607C  41 82 00 10 */	beq lbl_800794AC
/* 800794A0 00076080  88 17 01 38 */	lbz r0, 0x138(r23)
/* 800794A4 00076084  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800794A8 00076088  41 82 05 D0 */	beq lbl_80079A78
lbl_800794AC:
/* 800794AC 0007608C  38 7B 00 00 */	addi r3, r27, 0
/* 800794B0 00076090  38 97 00 00 */	addi r4, r23, 0
/* 800794B4 00076094  4B F9 18 49 */	bl lbColl_8000ACFC
/* 800794B8 00076098  2C 03 00 00 */	cmpwi r3, 0
/* 800794BC 0007609C  40 82 05 BC */	bne lbl_80079A78
/* 800794C0 000760A0  88 17 00 43 */	lbz r0, 0x43(r23)
/* 800794C4 000760A4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800794C8 000760A8  41 82 00 0C */	beq lbl_800794D4
/* 800794CC 000760AC  3A C0 00 01 */	li r22, 1
/* 800794D0 000760B0  48 00 00 08 */	b lbl_800794D8
lbl_800794D4:
/* 800794D4 000760B4  3A C0 00 00 */	li r22, 0
lbl_800794D8:
/* 800794D8 000760B8  80 17 00 30 */	lwz r0, 0x30(r23)
/* 800794DC 000760BC  28 00 00 0B */	cmplwi r0, 0xb
/* 800794E0 000760C0  41 82 01 70 */	beq lbl_80079650
/* 800794E4 000760C4  2C 16 00 00 */	cmpwi r22, 0
/* 800794E8 000760C8  40 82 01 68 */	bne lbl_80079650
/* 800794EC 000760CC  88 17 00 42 */	lbz r0, 0x42(r23)
/* 800794F0 000760D0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800794F4 000760D4  41 82 01 5C */	beq lbl_80079650
/* 800794F8 000760D8  88 1B 22 18 */	lbz r0, 0x2218(r27)
/* 800794FC 000760DC  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80079500 000760E0  41 82 00 54 */	beq lbl_80079554
/* 80079504 000760E4  88 17 00 41 */	lbz r0, 0x41(r23)
/* 80079508 000760E8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8007950C 000760EC  41 82 00 48 */	beq lbl_80079554
/* 80079510 000760F0  7F 63 DB 78 */	mr r3, r27
/* 80079514 000760F4  48 00 62 F1 */	bl func_8007F804
/* 80079518 000760F8  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 8007951C 000760FC  7C 65 1B 78 */	mr r5, r3
/* 80079520 00076100  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 80079524 00076104  7E E3 BB 78 */	mr r3, r23
/* 80079528 00076108  C0 7B 00 B8 */	lfs f3, 0xb8(r27)
/* 8007952C 0007610C  38 9B 19 E4 */	addi r4, r27, 0x19e4
/* 80079530 00076110  38 C0 00 00 */	li r6, 0
/* 80079534 00076114  4B F8 E6 99 */	bl lbColl_80007BCC
/* 80079538 00076118  2C 03 00 00 */	cmpwi r3, 0
/* 8007953C 0007611C  41 82 00 18 */	beq lbl_80079554
/* 80079540 00076120  38 78 00 00 */	addi r3, r24, 0
/* 80079544 00076124  38 97 00 00 */	addi r4, r23, 0
/* 80079548 00076128  38 BB 00 00 */	addi r5, r27, 0
/* 8007954C 0007612C  4B FF DF 19 */	bl func_80077464
/* 80079550 00076130  48 00 05 28 */	b lbl_80079A78
lbl_80079554:
/* 80079554 00076134  88 7B 22 18 */	lbz r3, 0x2218(r27)
/* 80079558 00076138  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8007955C 0007613C  41 82 00 F4 */	beq lbl_80079650
/* 80079560 00076140  88 17 00 42 */	lbz r0, 0x42(r23)
/* 80079564 00076144  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80079568 00076148  40 82 00 18 */	bne lbl_80079580
/* 8007956C 0007614C  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 80079570 00076150  41 82 00 E0 */	beq lbl_80079650
/* 80079574 00076154  88 17 00 41 */	lbz r0, 0x41(r23)
/* 80079578 00076158  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8007957C 0007615C  41 82 00 D4 */	beq lbl_80079650
lbl_80079580:
/* 80079580 00076160  7F 63 DB 78 */	mr r3, r27
/* 80079584 00076164  48 00 62 81 */	bl func_8007F804
/* 80079588 00076168  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 8007958C 0007616C  7C 65 1B 78 */	mr r5, r3
/* 80079590 00076170  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 80079594 00076174  7E E3 BB 78 */	mr r3, r23
/* 80079598 00076178  C0 7B 00 B8 */	lfs f3, 0xb8(r27)
/* 8007959C 0007617C  38 9B 1A 08 */	addi r4, r27, 0x1a08
/* 800795A0 00076180  38 C0 00 00 */	li r6, 0
/* 800795A4 00076184  4B F8 E6 29 */	bl lbColl_80007BCC
/* 800795A8 00076188  2C 03 00 00 */	cmpwi r3, 0
/* 800795AC 0007618C  41 82 00 A4 */	beq lbl_80079650
/* 800795B0 00076190  38 78 00 00 */	addi r3, r24, 0
/* 800795B4 00076194  38 97 00 00 */	addi r4, r23, 0
/* 800795B8 00076198  38 DB 00 00 */	addi r6, r27, 0
/* 800795BC 0007619C  38 A0 00 06 */	li r5, 6
/* 800795C0 000761A0  38 E0 00 00 */	li r7, 0
/* 800795C4 000761A4  48 1F 65 01 */	bl func_8026FAC4
/* 800795C8 000761A8  C0 17 00 0C */	lfs f0, 0xc(r23)
/* 800795CC 000761AC  FC 00 F0 00 */	fcmpu cr0, f0, f30
/* 800795D0 000761B0  41 82 00 2C */	beq lbl_800795FC
/* 800795D4 000761B4  FC 00 00 1E */	fctiwz f0, f0
/* 800795D8 000761B8  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 800795DC 000761BC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800795E0 000761C0  2C 00 00 00 */	cmpwi r0, 0
/* 800795E4 000761C4  41 82 00 10 */	beq lbl_800795F4
/* 800795E8 000761C8  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 800795EC 000761CC  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 800795F0 000761D0  48 00 00 10 */	b lbl_80079600
lbl_800795F4:
/* 800795F4 000761D4  38 60 00 01 */	li r3, 1
/* 800795F8 000761D8  48 00 00 08 */	b lbl_80079600
lbl_800795FC:
/* 800795FC 000761DC  38 60 00 00 */	li r3, 0
lbl_80079600:
/* 80079600 000761E0  80 1B 00 00 */	lwz r0, 0(r27)
/* 80079604 000761E4  90 18 0C 90 */	stw r0, 0xc90(r24)
/* 80079608 000761E8  C0 3B 00 B0 */	lfs f1, 0xb0(r27)
/* 8007960C 000761EC  C0 18 00 4C */	lfs f0, 0x4c(r24)
/* 80079610 000761F0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80079614 000761F4  40 81 00 0C */	ble lbl_80079620
/* 80079618 000761F8  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 8007961C 000761FC  48 00 00 08 */	b lbl_80079624
lbl_80079620:
/* 80079620 00076200  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_80079624:
/* 80079624 00076204  D0 1B 1A 40 */	stfs f0, 0x1a40(r27)
/* 80079628 00076208  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007962C 0007620C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80079630 00076210  41 82 04 48 */	beq lbl_80079A78
/* 80079634 00076214  80 1B 1A 44 */	lwz r0, 0x1a44(r27)
/* 80079638 00076218  7C 00 1A 14 */	add r0, r0, r3
/* 8007963C 0007621C  90 1B 1A 44 */	stw r0, 0x1a44(r27)
/* 80079640 00076220  80 7B 1A 48 */	lwz r3, 0x1a48(r27)
/* 80079644 00076224  38 03 00 01 */	addi r0, r3, 1
/* 80079648 00076228  90 1B 1A 48 */	stw r0, 0x1a48(r27)
/* 8007964C 0007622C  48 00 04 2C */	b lbl_80079A78
lbl_80079650:
/* 80079650 00076230  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 80079654 00076234  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80079658 00076238  40 82 01 08 */	bne lbl_80079760
/* 8007965C 0007623C  2C 16 00 00 */	cmpwi r22, 0
/* 80079660 00076240  40 82 01 00 */	bne lbl_80079760
/* 80079664 00076244  2C 19 00 00 */	cmpwi r25, 0
/* 80079668 00076248  41 82 00 F8 */	beq lbl_80079760
/* 8007966C 0007624C  3A 9B 00 00 */	addi r20, r27, 0
/* 80079670 00076250  3A 40 00 00 */	li r18, 0
/* 80079674 00076254  3A 60 00 00 */	li r19, 0
/* 80079678 00076258  3A AD AE C0 */	addi r21, r13, lbl_804D6560
lbl_8007967C:
/* 8007967C 0007625C  88 15 00 00 */	lbz r0, 0(r21)
/* 80079680 00076260  28 00 00 00 */	cmplwi r0, 0
/* 80079684 00076264  41 82 00 C0 */	beq lbl_80079744
/* 80079688 00076268  80 77 00 30 */	lwz r3, 0x30(r23)
/* 8007968C 0007626C  38 94 09 14 */	addi r4, r20, 0x914
/* 80079690 00076270  3A 24 00 00 */	addi r17, r4, 0
/* 80079694 00076274  28 03 00 0B */	cmplwi r3, 0xb
/* 80079698 00076278  41 82 00 10 */	beq lbl_800796A8
/* 8007969C 0007627C  80 04 00 30 */	lwz r0, 0x30(r4)
/* 800796A0 00076280  28 00 00 0B */	cmplwi r0, 0xb
/* 800796A4 00076284  40 82 00 48 */	bne lbl_800796EC
lbl_800796A8:
/* 800796A8 00076288  80 04 00 30 */	lwz r0, 0x30(r4)
/* 800796AC 0007628C  7C 03 00 40 */	cmplw r3, r0
/* 800796B0 00076290  41 82 00 94 */	beq lbl_80079744
/* 800796B4 00076294  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 800796B8 00076298  7E E3 BB 78 */	mr r3, r23
/* 800796BC 0007629C  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 800796C0 000762A0  7E 24 8B 78 */	mr r4, r17
/* 800796C4 000762A4  4B F8 E4 39 */	bl lbColl_80007AFC
/* 800796C8 000762A8  2C 03 00 00 */	cmpwi r3, 0
/* 800796CC 000762AC  41 82 00 78 */	beq lbl_80079744
/* 800796D0 000762B0  88 18 0D CE */	lbz r0, 0xdce(r24)
/* 800796D4 000762B4  38 60 00 01 */	li r3, 1
/* 800796D8 000762B8  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 800796DC 000762BC  98 18 0D CE */	stb r0, 0xdce(r24)
/* 800796E0 000762C0  3A 40 00 01 */	li r18, 1
/* 800796E4 000762C4  93 F8 0C F8 */	stw r31, 0xcf8(r24)
/* 800796E8 000762C8  48 00 00 70 */	b lbl_80079758
lbl_800796EC:
/* 800796EC 000762CC  88 17 00 40 */	lbz r0, 0x40(r23)
/* 800796F0 000762D0  54 00 CF FE */	rlwinm r0, r0, 0x19, 0x1f, 0x1f
/* 800796F4 000762D4  28 00 00 01 */	cmplwi r0, 1
/* 800796F8 000762D8  40 82 00 4C */	bne lbl_80079744
/* 800796FC 000762DC  88 04 00 40 */	lbz r0, 0x40(r4)
/* 80079700 000762E0  54 00 CF FE */	rlwinm r0, r0, 0x19, 0x1f, 0x1f
/* 80079704 000762E4  28 00 00 01 */	cmplwi r0, 1
/* 80079708 000762E8  40 82 00 3C */	bne lbl_80079744
/* 8007970C 000762EC  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 80079710 000762F0  7E E3 BB 78 */	mr r3, r23
/* 80079714 000762F4  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 80079718 000762F8  7E 24 8B 78 */	mr r4, r17
/* 8007971C 000762FC  4B F8 E3 E1 */	bl lbColl_80007AFC
/* 80079720 00076300  2C 03 00 00 */	cmpwi r3, 0
/* 80079724 00076304  41 82 00 20 */	beq lbl_80079744
/* 80079728 00076308  38 78 00 00 */	addi r3, r24, 0
/* 8007972C 0007630C  38 97 00 00 */	addi r4, r23, 0
/* 80079730 00076310  38 BB 00 00 */	addi r5, r27, 0
/* 80079734 00076314  38 D1 00 00 */	addi r6, r17, 0
/* 80079738 00076318  4B FF E2 39 */	bl func_80077970
/* 8007973C 0007631C  3A 40 00 01 */	li r18, 1
/* 80079740 00076320  48 00 00 18 */	b lbl_80079758
lbl_80079744:
/* 80079744 00076324  3A 73 00 01 */	addi r19, r19, 1
/* 80079748 00076328  28 13 00 04 */	cmplwi r19, 4
/* 8007974C 0007632C  3A B5 00 01 */	addi r21, r21, 1
/* 80079750 00076330  3A 94 01 38 */	addi r20, r20, 0x138
/* 80079754 00076334  41 80 FF 28 */	blt lbl_8007967C
lbl_80079758:
/* 80079758 00076338  2C 12 00 00 */	cmpwi r18, 0
/* 8007975C 0007633C  40 82 03 1C */	bne lbl_80079A78
lbl_80079760:
/* 80079760 00076340  80 17 00 30 */	lwz r0, 0x30(r23)
/* 80079764 00076344  28 00 00 0B */	cmplwi r0, 0xb
/* 80079768 00076348  41 82 01 14 */	beq lbl_8007987C
/* 8007976C 0007634C  88 7B 22 1B */	lbz r3, 0x221b(r27)
/* 80079770 00076350  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80079774 00076354  41 82 01 08 */	beq lbl_8007987C
/* 80079778 00076358  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007977C 0007635C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80079780 00076360  41 82 00 FC */	beq lbl_8007987C
/* 80079784 00076364  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 80079788 00076368  38 60 00 01 */	li r3, 1
/* 8007978C 0007636C  41 82 00 3C */	beq lbl_800797C8
/* 80079790 00076370  C0 1B 00 2C */	lfs f0, 0x2c(r27)
/* 80079794 00076374  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 80079798 00076378  40 82 00 1C */	bne lbl_800797B4
/* 8007979C 0007637C  C0 3B 00 B0 */	lfs f1, 0xb0(r27)
/* 800797A0 00076380  C0 18 00 4C */	lfs f0, 0x4c(r24)
/* 800797A4 00076384  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800797A8 00076388  40 80 00 20 */	bge lbl_800797C8
/* 800797AC 0007638C  38 60 00 00 */	li r3, 0
/* 800797B0 00076390  48 00 00 18 */	b lbl_800797C8
lbl_800797B4:
/* 800797B4 00076394  C0 3B 00 B0 */	lfs f1, 0xb0(r27)
/* 800797B8 00076398  C0 18 00 4C */	lfs f0, 0x4c(r24)
/* 800797BC 0007639C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800797C0 000763A0  40 81 00 08 */	ble lbl_800797C8
/* 800797C4 000763A4  38 60 00 00 */	li r3, 0
lbl_800797C8:
/* 800797C8 000763A8  88 1B 22 1B */	lbz r0, 0x221b(r27)
/* 800797CC 000763AC  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800797D0 000763B0  41 82 00 14 */	beq lbl_800797E4
/* 800797D4 000763B4  88 17 00 42 */	lbz r0, 0x42(r23)
/* 800797D8 000763B8  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800797DC 000763BC  40 82 00 08 */	bne lbl_800797E4
/* 800797E0 000763C0  38 60 00 00 */	li r3, 0
lbl_800797E4:
/* 800797E4 000763C4  2C 03 00 00 */	cmpwi r3, 0
/* 800797E8 000763C8  41 82 00 94 */	beq lbl_8007987C
/* 800797EC 000763CC  7F 63 DB 78 */	mr r3, r27
/* 800797F0 000763D0  48 00 60 15 */	bl func_8007F804
/* 800797F4 000763D4  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 800797F8 000763D8  7C 65 1B 78 */	mr r5, r3
/* 800797FC 000763DC  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 80079800 000763E0  7E E3 BB 78 */	mr r3, r23
/* 80079804 000763E4  C0 7B 00 B8 */	lfs f3, 0xb8(r27)
/* 80079808 000763E8  38 D6 00 00 */	addi r6, r22, 0
/* 8007980C 000763EC  38 9B 19 C0 */	addi r4, r27, 0x19c0
/* 80079810 000763F0  4B F8 E3 BD */	bl lbColl_80007BCC
/* 80079814 000763F4  2C 03 00 00 */	cmpwi r3, 0
/* 80079818 000763F8  41 82 00 64 */	beq lbl_8007987C
/* 8007981C 000763FC  88 7B 22 1B */	lbz r3, 0x221b(r27)
/* 80079820 00076400  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 80079824 00076404  40 82 00 3C */	bne lbl_80079860
/* 80079828 00076408  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007982C 0007640C  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80079830 00076410  40 82 00 0C */	bne lbl_8007983C
/* 80079834 00076414  54 60 D7 FF */	rlwinm. r0, r3, 0x1a, 0x1f, 0x1f
/* 80079838 00076418  41 82 00 28 */	beq lbl_80079860
lbl_8007983C:
/* 8007983C 0007641C  7F 63 DB 78 */	mr r3, r27
/* 80079840 00076420  48 00 5F C5 */	bl func_8007F804
/* 80079844 00076424  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 80079848 00076428  7C 65 1B 78 */	mr r5, r3
/* 8007984C 0007642C  38 77 00 00 */	addi r3, r23, 0
/* 80079850 00076430  38 9B 19 C0 */	addi r4, r27, 0x19c0
/* 80079854 00076434  38 C1 00 2C */	addi r6, r1, 0x2c
/* 80079858 00076438  38 E1 00 28 */	addi r7, r1, 0x28
/* 8007985C 0007643C  4B F8 E5 7D */	bl lbColl_80007DD8
lbl_80079860:
/* 80079860 00076440  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 80079864 00076444  38 78 00 00 */	addi r3, r24, 0
/* 80079868 00076448  38 97 00 00 */	addi r4, r23, 0
/* 8007986C 0007644C  38 BB 00 00 */	addi r5, r27, 0
/* 80079870 00076450  38 C1 00 2C */	addi r6, r1, 0x2c
/* 80079874 00076454  4B FF DE 15 */	bl func_80077688
/* 80079878 00076458  48 00 02 00 */	b lbl_80079A78
lbl_8007987C:
/* 8007987C 0007645C  80 17 00 30 */	lwz r0, 0x30(r23)
/* 80079880 00076460  28 00 00 0B */	cmplwi r0, 0xb
/* 80079884 00076464  40 82 00 70 */	bne lbl_800798F4
/* 80079888 00076468  3A 40 00 00 */	li r18, 0
/* 8007988C 0007646C  1C 12 00 4C */	mulli r0, r18, 0x4c
/* 80079890 00076470  7E 3B 02 14 */	add r17, r27, r0
/* 80079894 00076474  48 00 00 50 */	b lbl_800798E4
lbl_80079898:
/* 80079898 00076478  7F 63 DB 78 */	mr r3, r27
/* 8007989C 0007647C  48 00 5F 69 */	bl func_8007F804
/* 800798A0 00076480  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 800798A4 00076484  7C 65 1B 78 */	mr r5, r3
/* 800798A8 00076488  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 800798AC 0007648C  7E E3 BB 78 */	mr r3, r23
/* 800798B0 00076490  C0 7B 00 B8 */	lfs f3, 0xb8(r27)
/* 800798B4 00076494  38 91 11 A0 */	addi r4, r17, 0x11a0
/* 800798B8 00076498  4B F8 E9 91 */	bl lbColl_80008248
/* 800798BC 0007649C  2C 03 00 00 */	cmpwi r3, 0
/* 800798C0 000764A0  41 82 00 1C */	beq lbl_800798DC
/* 800798C4 000764A4  88 18 0D CE */	lbz r0, 0xdce(r24)
/* 800798C8 000764A8  38 60 00 01 */	li r3, 1
/* 800798CC 000764AC  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 800798D0 000764B0  98 18 0D CE */	stb r0, 0xdce(r24)
/* 800798D4 000764B4  93 F8 0C F8 */	stw r31, 0xcf8(r24)
/* 800798D8 000764B8  48 00 01 A0 */	b lbl_80079A78
lbl_800798DC:
/* 800798DC 000764BC  3A 31 00 4C */	addi r17, r17, 0x4c
/* 800798E0 000764C0  3A 52 00 01 */	addi r18, r18, 1
lbl_800798E4:
/* 800798E4 000764C4  88 1B 11 9E */	lbz r0, 0x119e(r27)
/* 800798E8 000764C8  7C 12 00 40 */	cmplw r18, r0
/* 800798EC 000764CC  41 80 FF AC */	blt lbl_80079898
/* 800798F0 000764D0  48 00 01 88 */	b lbl_80079A78
lbl_800798F4:
/* 800798F4 000764D4  80 1B 19 88 */	lwz r0, 0x1988(r27)
/* 800798F8 000764D8  2C 00 00 02 */	cmpwi r0, 2
/* 800798FC 000764DC  41 82 01 7C */	beq lbl_80079A78
/* 80079900 000764E0  80 1B 19 8C */	lwz r0, 0x198c(r27)
/* 80079904 000764E4  2C 00 00 02 */	cmpwi r0, 2
/* 80079908 000764E8  41 82 01 70 */	beq lbl_80079A78
/* 8007990C 000764EC  88 17 00 42 */	lbz r0, 0x42(r23)
/* 80079910 000764F0  54 00 F7 FE */	rlwinm r0, r0, 0x1e, 0x1f, 0x1f
/* 80079914 000764F4  28 00 00 01 */	cmplwi r0, 1
/* 80079918 000764F8  40 82 01 60 */	bne lbl_80079A78
/* 8007991C 000764FC  3A 9B 00 00 */	addi r20, r27, 0
/* 80079920 00076500  3A A0 00 00 */	li r21, 0
/* 80079924 00076504  48 00 01 48 */	b lbl_80079A6C
lbl_80079928:
/* 80079928 00076508  88 17 00 42 */	lbz r0, 0x42(r23)
/* 8007992C 0007650C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80079930 00076510  41 82 00 10 */	beq lbl_80079940
/* 80079934 00076514  80 14 11 E8 */	lwz r0, 0x11e8(r20)
/* 80079938 00076518  2C 00 00 00 */	cmpwi r0, 0
/* 8007993C 0007651C  41 82 01 28 */	beq lbl_80079A64
lbl_80079940:
/* 80079940 00076520  7F 63 DB 78 */	mr r3, r27
/* 80079944 00076524  48 00 5E C1 */	bl func_8007F804
/* 80079948 00076528  C0 38 00 38 */	lfs f1, 0x38(r24)
/* 8007994C 0007652C  7C 65 1B 78 */	mr r5, r3
/* 80079950 00076530  C0 5B 00 38 */	lfs f2, 0x38(r27)
/* 80079954 00076534  7E E3 BB 78 */	mr r3, r23
/* 80079958 00076538  C0 7B 00 B8 */	lfs f3, 0xb8(r27)
/* 8007995C 0007653C  38 D6 00 00 */	addi r6, r22, 0
/* 80079960 00076540  38 94 11 A0 */	addi r4, r20, 0x11a0
/* 80079964 00076544  4B F8 E6 F9 */	bl lbColl_8000805C
/* 80079968 00076548  2C 03 00 00 */	cmpwi r3, 0
/* 8007996C 0007654C  41 82 00 F8 */	beq lbl_80079A64
/* 80079970 00076550  1C 75 00 4C */	mulli r3, r21, 0x4c
/* 80079974 00076554  3A 23 11 A0 */	addi r17, r3, 0x11a0
/* 80079978 00076558  7E 3B 8A 14 */	add r17, r27, r17
/* 8007997C 0007655C  38 78 00 00 */	addi r3, r24, 0
/* 80079980 00076560  38 97 00 00 */	addi r4, r23, 0
/* 80079984 00076564  38 BB 00 00 */	addi r5, r27, 0
/* 80079988 00076568  38 D1 00 00 */	addi r6, r17, 0
/* 8007998C 0007656C  4B FF E2 D5 */	bl func_80077C60
/* 80079990 00076570  2C 03 00 00 */	cmpwi r3, 0
/* 80079994 00076574  41 82 00 E4 */	beq lbl_80079A78
/* 80079998 00076578  80 1B 19 88 */	lwz r0, 0x1988(r27)
/* 8007999C 0007657C  2C 00 00 00 */	cmpwi r0, 0
/* 800799A0 00076580  40 82 00 28 */	bne lbl_800799C8
/* 800799A4 00076584  80 1B 19 8C */	lwz r0, 0x198c(r27)
/* 800799A8 00076588  2C 00 00 00 */	cmpwi r0, 0
/* 800799AC 0007658C  40 82 00 1C */	bne lbl_800799C8
/* 800799B0 00076590  88 1B 22 1D */	lbz r0, 0x221d(r27)
/* 800799B4 00076594  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800799B8 00076598  40 82 00 10 */	bne lbl_800799C8
/* 800799BC 0007659C  80 11 00 00 */	lwz r0, 0(r17)
/* 800799C0 000765A0  2C 00 00 00 */	cmpwi r0, 0
/* 800799C4 000765A4  41 82 00 2C */	beq lbl_800799F0
lbl_800799C8:
/* 800799C8 000765A8  80 17 00 38 */	lwz r0, 0x38(r23)
/* 800799CC 000765AC  38 7B 00 00 */	addi r3, r27, 0
/* 800799D0 000765B0  38 A0 00 7F */	li r5, 0x7f
/* 800799D4 000765B4  54 00 10 3A */	slwi r0, r0, 2
/* 800799D8 000765B8  7C 9E 02 14 */	add r4, r30, r0
/* 800799DC 000765BC  80 84 00 00 */	lwz r4, 0(r4)
/* 800799E0 000765C0  38 C0 00 40 */	li r6, 0x40
/* 800799E4 000765C4  48 00 E7 65 */	bl func_80088148
/* 800799E8 000765C8  38 00 00 01 */	li r0, 1
/* 800799EC 000765CC  48 00 00 08 */	b lbl_800799F4
lbl_800799F0:
/* 800799F0 000765D0  38 00 00 00 */	li r0, 0
lbl_800799F4:
/* 800799F4 000765D4  2C 00 00 00 */	cmpwi r0, 0
/* 800799F8 000765D8  40 82 00 80 */	bne lbl_80079A78
/* 800799FC 000765DC  80 17 00 3C */	lwz r0, 0x3c(r23)
/* 80079A00 000765E0  28 00 00 0D */	cmplwi r0, 0xd
/* 80079A04 000765E4  40 82 00 38 */	bne lbl_80079A3C
/* 80079A08 000765E8  80 17 00 38 */	lwz r0, 0x38(r23)
/* 80079A0C 000765EC  28 00 00 02 */	cmplwi r0, 2
/* 80079A10 000765F0  40 82 00 2C */	bne lbl_80079A3C
/* 80079A14 000765F4  88 9B 22 1F */	lbz r4, 0x221f(r27)
/* 80079A18 000765F8  7E E3 BB 78 */	mr r3, r23
/* 80079A1C 000765FC  88 1B 00 0C */	lbz r0, 0xc(r27)
/* 80079A20 00076600  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80079A24 00076604  54 00 08 3C */	slwi r0, r0, 1
/* 80079A28 00076608  7C 80 22 14 */	add r4, r0, r4
/* 80079A2C 0007660C  38 84 00 72 */	addi r4, r4, 0x72
/* 80079A30 00076610  4B F8 C1 81 */	bl lbColl_80005BB0
/* 80079A34 00076614  90 7B 21 5C */	stw r3, 0x215c(r27)
/* 80079A38 00076618  48 00 00 40 */	b lbl_80079A78
lbl_80079A3C:
/* 80079A3C 0007661C  88 9B 22 1F */	lbz r4, 0x221f(r27)
/* 80079A40 00076620  7E E3 BB 78 */	mr r3, r23
/* 80079A44 00076624  88 1B 00 0C */	lbz r0, 0xc(r27)
/* 80079A48 00076628  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80079A4C 0007662C  54 00 08 3C */	slwi r0, r0, 1
/* 80079A50 00076630  7C 80 22 14 */	add r4, r0, r4
/* 80079A54 00076634  38 84 00 7E */	addi r4, r4, 0x7e
/* 80079A58 00076638  4B F8 C1 59 */	bl lbColl_80005BB0
/* 80079A5C 0007663C  90 7B 21 60 */	stw r3, 0x2160(r27)
/* 80079A60 00076640  48 00 00 18 */	b lbl_80079A78
lbl_80079A64:
/* 80079A64 00076644  3A 94 00 4C */	addi r20, r20, 0x4c
/* 80079A68 00076648  3A B5 00 01 */	addi r21, r21, 1
lbl_80079A6C:
/* 80079A6C 0007664C  88 1B 11 9E */	lbz r0, 0x119e(r27)
/* 80079A70 00076650  7C 15 00 40 */	cmplw r21, r0
/* 80079A74 00076654  41 80 FE B4 */	blt lbl_80079928
lbl_80079A78:
/* 80079A78 00076658  3B 9C 00 01 */	addi r28, r28, 1
/* 80079A7C 0007665C  28 1C 00 04 */	cmplwi r28, 4
/* 80079A80 00076660  3B BD 01 3C */	addi r29, r29, 0x13c
/* 80079A84 00076664  41 80 F9 A4 */	blt lbl_80079428
lbl_80079A88:
/* 80079A88 00076668  83 5A 00 08 */	lwz r26, 8(r26)
lbl_80079A8C:
/* 80079A8C 0007666C  28 1A 00 00 */	cmplwi r26, 0
/* 80079A90 00076670  40 82 F8 08 */	bne lbl_80079298
/* 80079A94 00076674  BA 21 00 44 */	lmw r17, 0x44(r1)
/* 80079A98 00076678  80 01 00 94 */	lwz r0, 0x94(r1)
/* 80079A9C 0007667C  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 80079AA0 00076680  CB C1 00 80 */	lfd f30, 0x80(r1)
/* 80079AA4 00076684  38 21 00 90 */	addi r1, r1, 0x90
/* 80079AA8 00076688  7C 08 03 A6 */	mtlr r0
/* 80079AAC 0007668C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern f64 const lbl_804D8308;
extern f32 const lbl_804D8314;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80079AB0(void)
{ // clang-format off
    nofralloc
/* 80079AB0 00076690  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80079AB4 00076694  81 0D AE B4 */	lwz r8, p_ftCommonData
/* 80079AB8 00076698  80 04 00 28 */	lwz r0, 0x28(r4)
/* 80079ABC 0007669C  C0 08 00 F4 */	lfs f0, 0xf4(r8)
/* 80079AC0 000766A0  28 00 00 00 */	cmplwi r0, 0
/* 80079AC4 000766A4  EC C4 00 32 */	fmuls f6, f4, f0
/* 80079AC8 000766A8  41 82 00 A0 */	beq lbl_80079B68
/* 80079ACC 000766AC  C0 A8 00 F8 */	lfs f5, 0xf8(r8)
/* 80079AD0 000766B0  3C 60 43 30 */	lis r3, 0x4330
/* 80079AD4 000766B4  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80079AD8 000766B8  EC 86 01 72 */	fmuls f4, f6, f5
/* 80079ADC 000766BC  90 01 00 44 */	stw r0, 0x44(r1)
/* 80079AE0 000766C0  EC 00 30 2A */	fadds f0, f0, f6
/* 80079AE4 000766C4  80 04 00 24 */	lwz r0, 0x24(r4)
/* 80079AE8 000766C8  90 61 00 40 */	stw r3, 0x40(r1)
/* 80079AEC 000766CC  EC 84 00 24 */	fdivs f4, f4, f0
/* 80079AF0 000766D0  90 01 00 4C */	stw r0, 0x4c(r1)
/* 80079AF4 000766D4  80 04 00 2C */	lwz r0, 0x2c(r4)
/* 80079AF8 000766D8  90 61 00 48 */	stw r3, 0x48(r1)
/* 80079AFC 000766DC  C9 42 89 28 */	lfd f10, lbl_804D8308
/* 80079B00 000766E0  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80079B04 000766E4  EC E5 20 28 */	fsubs f7, f5, f4
/* 80079B08 000766E8  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80079B0C 000766EC  C8 A1 00 48 */	lfd f5, 0x48(r1)
/* 80079B10 000766F0  EC 80 50 28 */	fsubs f4, f0, f10
/* 80079B14 000766F4  C1 68 01 18 */	lfs f11, 0x118(r8)
/* 80079B18 000766F8  90 61 00 38 */	stw r3, 0x38(r1)
/* 80079B1C 000766FC  ED 05 50 28 */	fsubs f8, f5, f10
/* 80079B20 00076700  C1 22 89 34 */	lfs f9, lbl_804D8314
/* 80079B24 00076704  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80079B28 00076708  EC 8B 01 32 */	fmuls f4, f11, f4
/* 80079B2C 0007670C  C0 A8 01 14 */	lfs f5, 0x114(r8)
/* 80079B30 00076710  C0 C8 01 10 */	lfs f6, 0x110(r8)
/* 80079B34 00076714  ED 29 02 32 */	fmuls f9, f9, f8
/* 80079B38 00076718  EC A5 01 32 */	fmuls f5, f5, f4
/* 80079B3C 0007671C  C1 08 01 1C */	lfs f8, 0x11c(r8)
/* 80079B40 00076720  EC 00 50 28 */	fsubs f0, f0, f10
/* 80079B44 00076724  C0 88 01 20 */	lfs f4, 0x120(r8)
/* 80079B48 00076728  EC AB 29 BA */	fmadds f5, f11, f6, f5
/* 80079B4C 0007672C  EC A7 01 72 */	fmuls f5, f7, f5
/* 80079B50 00076730  EC 88 21 7A */	fmadds f4, f8, f5, f4
/* 80079B54 00076734  EC 09 01 3A */	fmadds f0, f9, f4, f0
/* 80079B58 00076738  EC 01 00 32 */	fmuls f0, f1, f0
/* 80079B5C 0007673C  EC 02 00 32 */	fmuls f0, f2, f0
/* 80079B60 00076740  EC 23 00 32 */	fmuls f1, f3, f0
/* 80079B64 00076744  48 00 00 F0 */	b lbl_80079C54
lbl_80079B68:
/* 80079B68 00076748  88 03 22 25 */	lbz r0, 0x2225(r3)
/* 80079B6C 0007674C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80079B70 00076750  41 82 00 20 */	beq lbl_80079B90
/* 80079B74 00076754  88 03 22 24 */	lbz r0, 0x2224(r3)
/* 80079B78 00076758  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80079B7C 0007675C  41 82 00 0C */	beq lbl_80079B88
/* 80079B80 00076760  80 08 06 D8 */	lwz r0, 0x6d8(r8)
/* 80079B84 00076764  48 00 00 1C */	b lbl_80079BA0
lbl_80079B88:
/* 80079B88 00076768  80 08 06 D4 */	lwz r0, 0x6d4(r8)
/* 80079B8C 0007676C  48 00 00 14 */	b lbl_80079BA0
lbl_80079B90:
/* 80079B90 00076770  C0 03 18 30 */	lfs f0, 0x1830(r3)
/* 80079B94 00076774  FC 00 00 1E */	fctiwz f0, f0
/* 80079B98 00076778  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80079B9C 0007677C  80 01 00 3C */	lwz r0, 0x3c(r1)
lbl_80079BA0:
/* 80079BA0 00076780  C0 E8 00 F8 */	lfs f7, 0xf8(r8)
/* 80079BA4 00076784  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80079BA8 00076788  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80079BAC 0007678C  3C C0 43 30 */	lis r6, 0x4330
/* 80079BB0 00076790  EC 86 01 F2 */	fmuls f4, f6, f7
/* 80079BB4 00076794  EC 00 30 2A */	fadds f0, f0, f6
/* 80079BB8 00076798  90 01 00 44 */	stw r0, 0x44(r1)
/* 80079BBC 0007679C  80 E4 00 24 */	lwz r7, 0x24(r4)
/* 80079BC0 000767A0  90 C1 00 40 */	stw r6, 0x40(r1)
/* 80079BC4 000767A4  EC C4 00 24 */	fdivs f6, f4, f0
/* 80079BC8 000767A8  90 A1 00 4C */	stw r5, 0x4c(r1)
/* 80079BCC 000767AC  80 04 00 2C */	lwz r0, 0x2c(r4)
/* 80079BD0 000767B0  C8 82 89 18 */	lfd f4, lbl_804D82F8
/* 80079BD4 000767B4  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80079BD8 000767B8  90 C1 00 48 */	stw r6, 0x48(r1)
/* 80079BDC 000767BC  EC A0 20 28 */	fsubs f5, f0, f4
/* 80079BE0 000767C0  C0 83 18 38 */	lfs f4, 0x1838(r3)
/* 80079BE4 000767C4  EC E7 30 28 */	fsubs f7, f7, f6
/* 80079BE8 000767C8  90 E1 00 3C */	stw r7, 0x3c(r1)
/* 80079BEC 000767CC  C9 42 89 28 */	lfd f10, lbl_804D8308
/* 80079BF0 000767D0  C8 01 00 48 */	lfd f0, 0x48(r1)
/* 80079BF4 000767D4  ED 85 20 2A */	fadds f12, f5, f4
/* 80079BF8 000767D8  90 C1 00 38 */	stw r6, 0x38(r1)
/* 80079BFC 000767DC  EC 00 50 28 */	fsubs f0, f0, f10
/* 80079C00 000767E0  C0 A8 01 14 */	lfs f5, 0x114(r8)
/* 80079C04 000767E4  90 01 00 34 */	stw r0, 0x34(r1)
/* 80079C08 000767E8  C8 C1 00 38 */	lfd f6, 0x38(r1)
/* 80079C0C 000767EC  EC 80 03 32 */	fmuls f4, f0, f12
/* 80079C10 000767F0  90 C1 00 30 */	stw r6, 0x30(r1)
/* 80079C14 000767F4  ED 26 50 28 */	fsubs f9, f6, f10
/* 80079C18 000767F8  C1 62 89 34 */	lfs f11, lbl_804D8314
/* 80079C1C 000767FC  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80079C20 00076800  EC A5 01 32 */	fmuls f5, f5, f4
/* 80079C24 00076804  C0 C8 01 10 */	lfs f6, 0x110(r8)
/* 80079C28 00076808  C1 08 01 1C */	lfs f8, 0x11c(r8)
/* 80079C2C 0007680C  ED 2B 02 72 */	fmuls f9, f11, f9
/* 80079C30 00076810  C0 88 01 20 */	lfs f4, 0x120(r8)
/* 80079C34 00076814  EC A6 2B 3A */	fmadds f5, f6, f12, f5
/* 80079C38 00076818  EC 00 50 28 */	fsubs f0, f0, f10
/* 80079C3C 0007681C  EC A7 01 72 */	fmuls f5, f7, f5
/* 80079C40 00076820  EC 88 21 7A */	fmadds f4, f8, f5, f4
/* 80079C44 00076824  EC 09 01 3A */	fmadds f0, f9, f4, f0
/* 80079C48 00076828  EC 01 00 32 */	fmuls f0, f1, f0
/* 80079C4C 0007682C  EC 02 00 32 */	fmuls f0, f2, f0
/* 80079C50 00076830  EC 23 00 32 */	fmuls f1, f3, f0
lbl_80079C54:
/* 80079C54 00076834  C0 08 01 08 */	lfs f0, 0x108(r8)
/* 80079C58 00076838  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80079C5C 0007683C  4C 41 13 82 */	cror 2, 1, 2
/* 80079C60 00076840  40 82 00 08 */	bne lbl_80079C68
/* 80079C64 00076844  FC 20 00 90 */	fmr f1, f0
lbl_80079C68:
/* 80079C68 00076848  38 21 00 50 */	addi r1, r1, 0x50
/* 80079C6C 0007684C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80079C70(void)
{ // clang-format off
    nofralloc
/* 80079C70 00076850  7C 08 02 A6 */	mflr r0
/* 80079C74 00076854  90 01 00 04 */	stw r0, 4(r1)
/* 80079C78 00076858  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 80079C7C 0007685C  DB E1 00 68 */	stfd f31, 0x68(r1)
/* 80079C80 00076860  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 80079C84 00076864  DB A1 00 58 */	stfd f29, 0x58(r1)
/* 80079C88 00076868  93 E1 00 54 */	stw r31, 0x54(r1)
/* 80079C8C 0007686C  3B E6 00 00 */	addi r31, r6, 0
/* 80079C90 00076870  93 C1 00 50 */	stw r30, 0x50(r1)
/* 80079C94 00076874  3B C5 00 00 */	addi r30, r5, 0
/* 80079C98 00076878  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 80079C9C 0007687C  7C 9D 23 78 */	mr r29, r4
/* 80079CA0 00076880  93 81 00 48 */	stw r28, 0x48(r1)
/* 80079CA4 00076884  7C 7C 1B 78 */	mr r28, r3
/* 80079CA8 00076888  C3 A3 01 98 */	lfs f29, 0x198(r3)
/* 80079CAC 0007688C  88 63 00 0C */	lbz r3, 0xc(r3)
/* 80079CB0 00076890  4B FB 9D 31 */	bl Player_GetDefenseRatio
/* 80079CB4 00076894  FF C0 08 90 */	fmr f30, f1
/* 80079CB8 00076898  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 80079CBC 0007689C  4B FB 9C 39 */	bl Player_GetAttackRatio
/* 80079CC0 000768A0  FF E0 08 90 */	fmr f31, f1
/* 80079CC4 000768A4  48 0F 15 85 */	bl func_8016B248
/* 80079CC8 000768A8  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 80079CCC 000768AC  80 1E 00 28 */	lwz r0, 0x28(r30)
/* 80079CD0 000768B0  C0 05 00 F4 */	lfs f0, 0xf4(r5)
/* 80079CD4 000768B4  28 00 00 00 */	cmplwi r0, 0
/* 80079CD8 000768B8  EC 7D 00 32 */	fmuls f3, f29, f0
/* 80079CDC 000768BC  41 82 00 A0 */	beq lbl_80079D7C
/* 80079CE0 000768C0  C0 85 00 F8 */	lfs f4, 0xf8(r5)
/* 80079CE4 000768C4  3C 60 43 30 */	lis r3, 0x4330
/* 80079CE8 000768C8  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80079CEC 000768CC  EC 43 01 32 */	fmuls f2, f3, f4
/* 80079CF0 000768D0  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80079CF4 000768D4  EC 00 18 2A */	fadds f0, f0, f3
/* 80079CF8 000768D8  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 80079CFC 000768DC  90 61 00 38 */	stw r3, 0x38(r1)
/* 80079D00 000768E0  EC 42 00 24 */	fdivs f2, f2, f0
/* 80079D04 000768E4  90 01 00 44 */	stw r0, 0x44(r1)
/* 80079D08 000768E8  80 1E 00 2C */	lwz r0, 0x2c(r30)
/* 80079D0C 000768EC  90 61 00 40 */	stw r3, 0x40(r1)
/* 80079D10 000768F0  C9 02 89 28 */	lfd f8, lbl_804D8308
/* 80079D14 000768F4  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80079D18 000768F8  EC A4 10 28 */	fsubs f5, f4, f2
/* 80079D1C 000768FC  90 01 00 34 */	stw r0, 0x34(r1)
/* 80079D20 00076900  C8 61 00 40 */	lfd f3, 0x40(r1)
/* 80079D24 00076904  EC 40 40 28 */	fsubs f2, f0, f8
/* 80079D28 00076908  C1 25 01 18 */	lfs f9, 0x118(r5)
/* 80079D2C 0007690C  90 61 00 30 */	stw r3, 0x30(r1)
/* 80079D30 00076910  EC C3 40 28 */	fsubs f6, f3, f8
/* 80079D34 00076914  C0 E2 89 34 */	lfs f7, lbl_804D8314
/* 80079D38 00076918  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80079D3C 0007691C  EC 49 00 B2 */	fmuls f2, f9, f2
/* 80079D40 00076920  C0 65 01 14 */	lfs f3, 0x114(r5)
/* 80079D44 00076924  C0 85 01 10 */	lfs f4, 0x110(r5)
/* 80079D48 00076928  EC E7 01 B2 */	fmuls f7, f7, f6
/* 80079D4C 0007692C  EC 63 00 B2 */	fmuls f3, f3, f2
/* 80079D50 00076930  C0 C5 01 1C */	lfs f6, 0x11c(r5)
/* 80079D54 00076934  EC 00 40 28 */	fsubs f0, f0, f8
/* 80079D58 00076938  C0 45 01 20 */	lfs f2, 0x120(r5)
/* 80079D5C 0007693C  EC 69 19 3A */	fmadds f3, f9, f4, f3
/* 80079D60 00076940  EC 65 00 F2 */	fmuls f3, f5, f3
/* 80079D64 00076944  EC 46 10 FA */	fmadds f2, f6, f3, f2
/* 80079D68 00076948  EC 07 00 BA */	fmadds f0, f7, f2, f0
/* 80079D6C 0007694C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80079D70 00076950  EC 1F 00 32 */	fmuls f0, f31, f0
/* 80079D74 00076954  EC 3E 00 32 */	fmuls f1, f30, f0
/* 80079D78 00076958  48 00 00 F0 */	b lbl_80079E68
lbl_80079D7C:
/* 80079D7C 0007695C  88 1C 22 25 */	lbz r0, 0x2225(r28)
/* 80079D80 00076960  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80079D84 00076964  41 82 00 20 */	beq lbl_80079DA4
/* 80079D88 00076968  88 1C 22 24 */	lbz r0, 0x2224(r28)
/* 80079D8C 0007696C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80079D90 00076970  41 82 00 0C */	beq lbl_80079D9C
/* 80079D94 00076974  80 05 06 D8 */	lwz r0, 0x6d8(r5)
/* 80079D98 00076978  48 00 00 1C */	b lbl_80079DB4
lbl_80079D9C:
/* 80079D9C 0007697C  80 05 06 D4 */	lwz r0, 0x6d4(r5)
/* 80079DA0 00076980  48 00 00 14 */	b lbl_80079DB4
lbl_80079DA4:
/* 80079DA4 00076984  C0 1C 18 30 */	lfs f0, 0x1830(r28)
/* 80079DA8 00076988  FC 00 00 1E */	fctiwz f0, f0
/* 80079DAC 0007698C  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 80079DB0 00076990  80 01 00 34 */	lwz r0, 0x34(r1)
lbl_80079DB4:
/* 80079DB4 00076994  C0 A5 00 F8 */	lfs f5, 0xf8(r5)
/* 80079DB8 00076998  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80079DBC 0007699C  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80079DC0 000769A0  3C 60 43 30 */	lis r3, 0x4330
/* 80079DC4 000769A4  EC 43 01 72 */	fmuls f2, f3, f5
/* 80079DC8 000769A8  EC 00 18 2A */	fadds f0, f0, f3
/* 80079DCC 000769AC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80079DD0 000769B0  80 9E 00 24 */	lwz r4, 0x24(r30)
/* 80079DD4 000769B4  90 61 00 38 */	stw r3, 0x38(r1)
/* 80079DD8 000769B8  EC 82 00 24 */	fdivs f4, f2, f0
/* 80079DDC 000769BC  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80079DE0 000769C0  80 1E 00 2C */	lwz r0, 0x2c(r30)
/* 80079DE4 000769C4  C8 42 89 18 */	lfd f2, lbl_804D82F8
/* 80079DE8 000769C8  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80079DEC 000769CC  90 61 00 40 */	stw r3, 0x40(r1)
/* 80079DF0 000769D0  EC 60 10 28 */	fsubs f3, f0, f2
/* 80079DF4 000769D4  C0 5C 18 38 */	lfs f2, 0x1838(r28)
/* 80079DF8 000769D8  EC A5 20 28 */	fsubs f5, f5, f4
/* 80079DFC 000769DC  90 81 00 34 */	stw r4, 0x34(r1)
/* 80079E00 000769E0  C9 02 89 28 */	lfd f8, lbl_804D8308
/* 80079E04 000769E4  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80079E08 000769E8  ED 43 10 2A */	fadds f10, f3, f2
/* 80079E0C 000769EC  90 61 00 30 */	stw r3, 0x30(r1)
/* 80079E10 000769F0  EC 00 40 28 */	fsubs f0, f0, f8
/* 80079E14 000769F4  C0 65 01 14 */	lfs f3, 0x114(r5)
/* 80079E18 000769F8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80079E1C 000769FC  C8 81 00 30 */	lfd f4, 0x30(r1)
/* 80079E20 00076A00  EC 40 02 B2 */	fmuls f2, f0, f10
/* 80079E24 00076A04  90 61 00 28 */	stw r3, 0x28(r1)
/* 80079E28 00076A08  EC E4 40 28 */	fsubs f7, f4, f8
/* 80079E2C 00076A0C  C1 22 89 34 */	lfs f9, lbl_804D8314
/* 80079E30 00076A10  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 80079E34 00076A14  EC 63 00 B2 */	fmuls f3, f3, f2
/* 80079E38 00076A18  C0 85 01 10 */	lfs f4, 0x110(r5)
/* 80079E3C 00076A1C  C0 C5 01 1C */	lfs f6, 0x11c(r5)
/* 80079E40 00076A20  EC E9 01 F2 */	fmuls f7, f9, f7
/* 80079E44 00076A24  C0 45 01 20 */	lfs f2, 0x120(r5)
/* 80079E48 00076A28  EC 64 1A BA */	fmadds f3, f4, f10, f3
/* 80079E4C 00076A2C  EC 00 40 28 */	fsubs f0, f0, f8
/* 80079E50 00076A30  EC 65 00 F2 */	fmuls f3, f5, f3
/* 80079E54 00076A34  EC 46 10 FA */	fmadds f2, f6, f3, f2
/* 80079E58 00076A38  EC 07 00 BA */	fmadds f0, f7, f2, f0
/* 80079E5C 00076A3C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80079E60 00076A40  EC 1F 00 32 */	fmuls f0, f31, f0
/* 80079E64 00076A44  EC 3E 00 32 */	fmuls f1, f30, f0
lbl_80079E68:
/* 80079E68 00076A48  C0 05 01 08 */	lfs f0, 0x108(r5)
/* 80079E6C 00076A4C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80079E70 00076A50  4C 41 13 82 */	cror 2, 1, 2
/* 80079E74 00076A54  40 82 00 08 */	bne lbl_80079E7C
/* 80079E78 00076A58  FC 20 00 90 */	fmr f1, f0
lbl_80079E7C:
/* 80079E7C 00076A5C  80 01 00 74 */	lwz r0, 0x74(r1)
/* 80079E80 00076A60  CB E1 00 68 */	lfd f31, 0x68(r1)
/* 80079E84 00076A64  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 80079E88 00076A68  CB A1 00 58 */	lfd f29, 0x58(r1)
/* 80079E8C 00076A6C  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 80079E90 00076A70  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 80079E94 00076A74  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 80079E98 00076A78  83 81 00 48 */	lwz r28, 0x48(r1)
/* 80079E9C 00076A7C  38 21 00 70 */	addi r1, r1, 0x70
/* 80079EA0 00076A80  7C 08 03 A6 */	mtlr r0
/* 80079EA4 00076A84  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80079EA8(void)
{ // clang-format off
    nofralloc
/* 80079EA8 00076A88  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80079EAC 00076A8C  81 0D AE B4 */	lwz r8, p_ftCommonData
/* 80079EB0 00076A90  80 04 00 28 */	lwz r0, 0x28(r4)
/* 80079EB4 00076A94  C0 23 01 98 */	lfs f1, 0x198(r3)
/* 80079EB8 00076A98  C0 08 00 F4 */	lfs f0, 0xf4(r8)
/* 80079EBC 00076A9C  28 00 00 00 */	cmplwi r0, 0
/* 80079EC0 00076AA0  EC 21 00 32 */	fmuls f1, f1, f0
/* 80079EC4 00076AA4  41 82 00 A0 */	beq lbl_80079F64
/* 80079EC8 00076AA8  C1 02 89 0C */	lfs f8, lbl_804D82EC
/* 80079ECC 00076AAC  3C 60 43 30 */	lis r3, 0x4330
/* 80079ED0 00076AB0  C0 48 00 F8 */	lfs f2, 0xf8(r8)
/* 80079ED4 00076AB4  EC 08 08 2A */	fadds f0, f8, f1
/* 80079ED8 00076AB8  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80079EDC 00076ABC  EC 21 00 B2 */	fmuls f1, f1, f2
/* 80079EE0 00076AC0  80 04 00 24 */	lwz r0, 0x24(r4)
/* 80079EE4 00076AC4  90 61 00 38 */	stw r3, 0x38(r1)
/* 80079EE8 00076AC8  EC 21 00 24 */	fdivs f1, f1, f0
/* 80079EEC 00076ACC  90 01 00 44 */	stw r0, 0x44(r1)
/* 80079EF0 00076AD0  80 04 00 2C */	lwz r0, 0x2c(r4)
/* 80079EF4 00076AD4  90 61 00 40 */	stw r3, 0x40(r1)
/* 80079EF8 00076AD8  C8 E2 89 28 */	lfd f7, lbl_804D8308
/* 80079EFC 00076ADC  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80079F00 00076AE0  EC 82 08 28 */	fsubs f4, f2, f1
/* 80079F04 00076AE4  90 01 00 34 */	stw r0, 0x34(r1)
/* 80079F08 00076AE8  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 80079F0C 00076AEC  EC 20 38 28 */	fsubs f1, f0, f7
/* 80079F10 00076AF0  C1 28 01 18 */	lfs f9, 0x118(r8)
/* 80079F14 00076AF4  90 61 00 30 */	stw r3, 0x30(r1)
/* 80079F18 00076AF8  EC A2 38 28 */	fsubs f5, f2, f7
/* 80079F1C 00076AFC  C0 C2 89 34 */	lfs f6, lbl_804D8314
/* 80079F20 00076B00  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80079F24 00076B04  EC 29 00 72 */	fmuls f1, f9, f1
/* 80079F28 00076B08  C0 48 01 14 */	lfs f2, 0x114(r8)
/* 80079F2C 00076B0C  C0 68 01 10 */	lfs f3, 0x110(r8)
/* 80079F30 00076B10  EC C6 01 72 */	fmuls f6, f6, f5
/* 80079F34 00076B14  EC 42 00 72 */	fmuls f2, f2, f1
/* 80079F38 00076B18  C0 A8 01 1C */	lfs f5, 0x11c(r8)
/* 80079F3C 00076B1C  EC 00 38 28 */	fsubs f0, f0, f7
/* 80079F40 00076B20  C0 28 01 20 */	lfs f1, 0x120(r8)
/* 80079F44 00076B24  EC 49 10 FA */	fmadds f2, f9, f3, f2
/* 80079F48 00076B28  EC 44 00 B2 */	fmuls f2, f4, f2
/* 80079F4C 00076B2C  EC 25 08 BA */	fmadds f1, f5, f2, f1
/* 80079F50 00076B30  EC 06 00 7A */	fmadds f0, f6, f1, f0
/* 80079F54 00076B34  EC 08 00 32 */	fmuls f0, f8, f0
/* 80079F58 00076B38  EC 08 00 32 */	fmuls f0, f8, f0
/* 80079F5C 00076B3C  EC 28 00 32 */	fmuls f1, f8, f0
/* 80079F60 00076B40  48 00 00 F0 */	b lbl_8007A050
lbl_80079F64:
/* 80079F64 00076B44  88 03 22 25 */	lbz r0, 0x2225(r3)
/* 80079F68 00076B48  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80079F6C 00076B4C  41 82 00 20 */	beq lbl_80079F8C
/* 80079F70 00076B50  88 03 22 24 */	lbz r0, 0x2224(r3)
/* 80079F74 00076B54  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80079F78 00076B58  41 82 00 0C */	beq lbl_80079F84
/* 80079F7C 00076B5C  80 08 06 D8 */	lwz r0, 0x6d8(r8)
/* 80079F80 00076B60  48 00 00 1C */	b lbl_80079F9C
lbl_80079F84:
/* 80079F84 00076B64  80 08 06 D4 */	lwz r0, 0x6d4(r8)
/* 80079F88 00076B68  48 00 00 14 */	b lbl_80079F9C
lbl_80079F8C:
/* 80079F8C 00076B6C  C0 03 18 30 */	lfs f0, 0x1830(r3)
/* 80079F90 00076B70  FC 00 00 1E */	fctiwz f0, f0
/* 80079F94 00076B74  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 80079F98 00076B78  80 01 00 34 */	lwz r0, 0x34(r1)
lbl_80079F9C:
/* 80079F9C 00076B7C  C1 22 89 0C */	lfs f9, lbl_804D82EC
/* 80079FA0 00076B80  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80079FA4 00076B84  C0 88 00 F8 */	lfs f4, 0xf8(r8)
/* 80079FA8 00076B88  3C C0 43 30 */	lis r6, 0x4330
/* 80079FAC 00076B8C  EC 09 08 2A */	fadds f0, f9, f1
/* 80079FB0 00076B90  EC 21 01 32 */	fmuls f1, f1, f4
/* 80079FB4 00076B94  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80079FB8 00076B98  80 E4 00 24 */	lwz r7, 0x24(r4)
/* 80079FBC 00076B9C  90 C1 00 38 */	stw r6, 0x38(r1)
/* 80079FC0 00076BA0  EC 61 00 24 */	fdivs f3, f1, f0
/* 80079FC4 00076BA4  90 A1 00 44 */	stw r5, 0x44(r1)
/* 80079FC8 00076BA8  80 04 00 2C */	lwz r0, 0x2c(r4)
/* 80079FCC 00076BAC  C8 22 89 18 */	lfd f1, lbl_804D82F8
/* 80079FD0 00076BB0  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80079FD4 00076BB4  90 C1 00 40 */	stw r6, 0x40(r1)
/* 80079FD8 00076BB8  EC 40 08 28 */	fsubs f2, f0, f1
/* 80079FDC 00076BBC  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 80079FE0 00076BC0  EC 84 18 28 */	fsubs f4, f4, f3
/* 80079FE4 00076BC4  90 E1 00 34 */	stw r7, 0x34(r1)
/* 80079FE8 00076BC8  C8 E2 89 28 */	lfd f7, lbl_804D8308
/* 80079FEC 00076BCC  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80079FF0 00076BD0  ED 42 08 2A */	fadds f10, f2, f1
/* 80079FF4 00076BD4  90 C1 00 30 */	stw r6, 0x30(r1)
/* 80079FF8 00076BD8  EC 00 38 28 */	fsubs f0, f0, f7
/* 80079FFC 00076BDC  C0 48 01 14 */	lfs f2, 0x114(r8)
/* 8007A000 00076BE0  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8007A004 00076BE4  C8 61 00 30 */	lfd f3, 0x30(r1)
/* 8007A008 00076BE8  EC 20 02 B2 */	fmuls f1, f0, f10
/* 8007A00C 00076BEC  90 C1 00 28 */	stw r6, 0x28(r1)
/* 8007A010 00076BF0  EC C3 38 28 */	fsubs f6, f3, f7
/* 8007A014 00076BF4  C1 02 89 34 */	lfs f8, lbl_804D8314
/* 8007A018 00076BF8  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 8007A01C 00076BFC  EC 42 00 72 */	fmuls f2, f2, f1
/* 8007A020 00076C00  C0 68 01 10 */	lfs f3, 0x110(r8)
/* 8007A024 00076C04  C0 A8 01 1C */	lfs f5, 0x11c(r8)
/* 8007A028 00076C08  EC C8 01 B2 */	fmuls f6, f8, f6
/* 8007A02C 00076C0C  C0 28 01 20 */	lfs f1, 0x120(r8)
/* 8007A030 00076C10  EC 43 12 BA */	fmadds f2, f3, f10, f2
/* 8007A034 00076C14  EC 00 38 28 */	fsubs f0, f0, f7
/* 8007A038 00076C18  EC 44 00 B2 */	fmuls f2, f4, f2
/* 8007A03C 00076C1C  EC 25 08 BA */	fmadds f1, f5, f2, f1
/* 8007A040 00076C20  EC 06 00 7A */	fmadds f0, f6, f1, f0
/* 8007A044 00076C24  EC 09 00 32 */	fmuls f0, f9, f0
/* 8007A048 00076C28  EC 09 00 32 */	fmuls f0, f9, f0
/* 8007A04C 00076C2C  EC 29 00 32 */	fmuls f1, f9, f0
lbl_8007A050:
/* 8007A050 00076C30  C0 08 01 08 */	lfs f0, 0x108(r8)
/* 8007A054 00076C34  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A058 00076C38  4C 41 13 82 */	cror 2, 1, 2
/* 8007A05C 00076C3C  40 82 00 08 */	bne lbl_8007A064
/* 8007A060 00076C40  FC 20 00 90 */	fmr f1, f0
lbl_8007A064:
/* 8007A064 00076C44  38 21 00 48 */	addi r1, r1, 0x48
/* 8007A068 00076C48  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_803C0CAC;
extern f32 const lbl_804D8318;
extern f32 const lbl_804D831C;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007A06C(void)
{ // clang-format off
    nofralloc
/* 8007A06C 00076C4C  7C 08 02 A6 */	mflr r0
/* 8007A070 00076C50  90 01 00 04 */	stw r0, 4(r1)
/* 8007A074 00076C54  94 21 FD 38 */	stwu r1, -0x2c8(r1)
/* 8007A078 00076C58  DB E1 02 C0 */	stfd f31, 0x2c0(r1)
/* 8007A07C 00076C5C  DB C1 02 B8 */	stfd f30, 0x2b8(r1)
/* 8007A080 00076C60  DB A1 02 B0 */	stfd f29, 0x2b0(r1)
/* 8007A084 00076C64  DB 81 02 A8 */	stfd f28, 0x2a8(r1)
/* 8007A088 00076C68  DB 61 02 A0 */	stfd f27, 0x2a0(r1)
/* 8007A08C 00076C6C  DB 41 02 98 */	stfd f26, 0x298(r1)
/* 8007A090 00076C70  DB 21 02 90 */	stfd f25, 0x290(r1)
/* 8007A094 00076C74  DB 01 02 88 */	stfd f24, 0x288(r1)
/* 8007A098 00076C78  DA E1 02 80 */	stfd f23, 0x280(r1)
/* 8007A09C 00076C7C  DA C1 02 78 */	stfd f22, 0x278(r1)
/* 8007A0A0 00076C80  BD E1 02 34 */	stmw r15, 0x234(r1)
/* 8007A0A4 00076C84  7C D4 33 79 */	or. r20, r6, r6
/* 8007A0A8 00076C88  3B C3 00 00 */	addi r30, r3, 0
/* 8007A0AC 00076C8C  3B E4 00 00 */	addi r31, r4, 0
/* 8007A0B0 00076C90  3A 65 00 00 */	addi r19, r5, 0
/* 8007A0B4 00076C94  3A A7 00 00 */	addi r21, r7, 0
/* 8007A0B8 00076C98  41 82 0A 54 */	beq lbl_8007AB0C
/* 8007A0BC 00076C9C  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 8007A0C0 00076CA0  3C 60 80 3C */	lis r3, lbl_803C0CAC@ha
/* 8007A0C4 00076CA4  C3 42 89 10 */	lfs f26, lbl_804D82F0
/* 8007A0C8 00076CA8  7E 7A 9B 78 */	mr r26, r19
/* 8007A0CC 00076CAC  C3 82 89 0C */	lfs f28, lbl_804D82EC
/* 8007A0D0 00076CB0  C3 A2 89 34 */	lfs f29, lbl_804D8314
/* 8007A0D4 00076CB4  7C 99 23 78 */	mr r25, r4
/* 8007A0D8 00076CB8  CB C2 89 28 */	lfd f30, lbl_804D8308
/* 8007A0DC 00076CBC  3B 64 01 10 */	addi r27, r4, 0x110
/* 8007A0E0 00076CC0  CB E2 89 18 */	lfd f31, lbl_804D82F8
/* 8007A0E4 00076CC4  3B 83 0C AC */	addi r28, r3, lbl_803C0CAC@l
/* 8007A0E8 00076CC8  3B 00 00 00 */	li r24, 0
/* 8007A0EC 00076CCC  3F A0 43 30 */	lis r29, 0x4330
/* 8007A0F0 00076CD0  48 00 06 24 */	b lbl_8007A714
lbl_8007A0F4:
/* 8007A0F4 00076CD4  80 1A 00 00 */	lwz r0, 0(r26)
/* 8007A0F8 00076CD8  2C 00 00 02 */	cmpwi r0, 2
/* 8007A0FC 00076CDC  41 82 01 40 */	beq lbl_8007A23C
/* 8007A100 00076CE0  40 80 00 10 */	bge lbl_8007A110
/* 8007A104 00076CE4  2C 00 00 01 */	cmpwi r0, 1
/* 8007A108 00076CE8  40 80 00 14 */	bge lbl_8007A11C
/* 8007A10C 00076CEC  48 00 05 9C */	b lbl_8007A6A8
lbl_8007A110:
/* 8007A110 00076CF0  2C 00 00 04 */	cmpwi r0, 4
/* 8007A114 00076CF4  40 80 05 94 */	bge lbl_8007A6A8
/* 8007A118 00076CF8  48 00 03 D8 */	b lbl_8007A4F0
lbl_8007A11C:
/* 8007A11C 00076CFC  80 7A 00 08 */	lwz r3, 8(r26)
/* 8007A120 00076D00  82 1A 00 24 */	lwz r16, 0x24(r26)
/* 8007A124 00076D04  81 E3 00 2C */	lwz r15, 0x2c(r3)
/* 8007A128 00076D08  82 3A 00 0C */	lwz r17, 0xc(r26)
/* 8007A12C 00076D0C  88 79 00 0C */	lbz r3, 0xc(r25)
/* 8007A130 00076D10  4B FB 98 B1 */	bl Player_GetDefenseRatio
/* 8007A134 00076D14  FF 60 08 90 */	fmr f27, f1
/* 8007A138 00076D18  88 6F 00 0C */	lbz r3, 0xc(r15)
/* 8007A13C 00076D1C  4B FB 97 B9 */	bl Player_GetAttackRatio
/* 8007A140 00076D20  FE E0 08 90 */	fmr f23, f1
/* 8007A144 00076D24  48 0F 11 05 */	bl func_8016B248
/* 8007A148 00076D28  FC 40 B8 90 */	fmr f2, f23
/* 8007A14C 00076D2C  C0 9B 00 88 */	lfs f4, 0x88(r27)
/* 8007A150 00076D30  FC 60 D8 90 */	fmr f3, f27
/* 8007A154 00076D34  7F 23 CB 78 */	mr r3, r25
/* 8007A158 00076D38  38 91 00 00 */	addi r4, r17, 0
/* 8007A15C 00076D3C  38 B0 00 00 */	addi r5, r16, 0
/* 8007A160 00076D40  4B FF F9 51 */	bl func_80079AB0
/* 8007A164 00076D44  2C 15 00 00 */	cmpwi r21, 0
/* 8007A168 00076D48  FE C0 08 90 */	fmr f22, f1
/* 8007A16C 00076D4C  41 82 05 3C */	beq lbl_8007A6A8
/* 8007A170 00076D50  C0 3A 00 20 */	lfs f1, 0x20(r26)
/* 8007A174 00076D54  48 2A 87 4D */	bl __cvt_fp2unsigned
/* 8007A178 00076D58  80 9A 00 0C */	lwz r4, 0xc(r26)
/* 8007A17C 00076D5C  80 DE 00 2C */	lwz r6, 0x2c(r30)
/* 8007A180 00076D60  80 04 00 30 */	lwz r0, 0x30(r4)
/* 8007A184 00076D64  80 A4 00 38 */	lwz r5, 0x38(r4)
/* 8007A188 00076D68  54 00 10 3A */	slwi r0, r0, 2
/* 8007A18C 00076D6C  7C 9C 02 14 */	add r4, r28, r0
/* 8007A190 00076D70  80 04 00 00 */	lwz r0, 0(r4)
/* 8007A194 00076D74  2C 00 04 16 */	cmpwi r0, 0x416
/* 8007A198 00076D78  41 82 00 70 */	beq lbl_8007A208
/* 8007A19C 00076D7C  40 80 00 30 */	bge lbl_8007A1CC
/* 8007A1A0 00076D80  2C 00 03 EB */	cmpwi r0, 0x3eb
/* 8007A1A4 00076D84  41 82 05 04 */	beq lbl_8007A6A8
/* 8007A1A8 00076D88  40 80 00 14 */	bge lbl_8007A1BC
/* 8007A1AC 00076D8C  2C 00 03 E8 */	cmpwi r0, 0x3e8
/* 8007A1B0 00076D90  41 82 00 34 */	beq lbl_8007A1E4
/* 8007A1B4 00076D94  40 80 00 54 */	bge lbl_8007A208
/* 8007A1B8 00076D98  48 00 04 F0 */	b lbl_8007A6A8
lbl_8007A1BC:
/* 8007A1BC 00076D9C  2C 00 03 ED */	cmpwi r0, 0x3ed
/* 8007A1C0 00076DA0  41 82 00 60 */	beq lbl_8007A220
/* 8007A1C4 00076DA4  40 80 04 E4 */	bge lbl_8007A6A8
/* 8007A1C8 00076DA8  48 00 00 40 */	b lbl_8007A208
lbl_8007A1CC:
/* 8007A1CC 00076DAC  2C 00 04 E7 */	cmpwi r0, 0x4e7
/* 8007A1D0 00076DB0  41 82 00 38 */	beq lbl_8007A208
/* 8007A1D4 00076DB4  40 80 04 D4 */	bge lbl_8007A6A8
/* 8007A1D8 00076DB8  2C 00 04 79 */	cmpwi r0, 0x479
/* 8007A1DC 00076DBC  41 82 00 2C */	beq lbl_8007A208
/* 8007A1E0 00076DC0  48 00 04 C8 */	b lbl_8007A6A8
lbl_8007A1E4:
/* 8007A1E4 00076DC4  90 61 02 2C */	stw r3, 0x22c(r1)
/* 8007A1E8 00076DC8  FC 40 B0 90 */	fmr f2, f22
/* 8007A1EC 00076DCC  7F C3 F3 78 */	mr r3, r30
/* 8007A1F0 00076DD0  93 A1 02 28 */	stw r29, 0x228(r1)
/* 8007A1F4 00076DD4  38 9A 00 14 */	addi r4, r26, 0x14
/* 8007A1F8 00076DD8  C8 01 02 28 */	lfd f0, 0x228(r1)
/* 8007A1FC 00076DDC  EC 20 F0 28 */	fsubs f1, f0, f30
/* 8007A200 00076DE0  4B FF E3 39 */	bl func_80078538
/* 8007A204 00076DE4  48 00 04 A4 */	b lbl_8007A6A8
lbl_8007A208:
/* 8007A208 00076DE8  7C 03 03 78 */	mr r3, r0
/* 8007A20C 00076DEC  4C C6 31 82 */	crclr 6
/* 8007A210 00076DF0  38 BA 00 14 */	addi r5, r26, 0x14
/* 8007A214 00076DF4  38 80 00 00 */	li r4, 0
/* 8007A218 00076DF8  4B FE 5B C5 */	bl ef_Spawn
/* 8007A21C 00076DFC  48 00 04 8C */	b lbl_8007A6A8
lbl_8007A220:
/* 8007A220 00076E00  7C 03 03 78 */	mr r3, r0
/* 8007A224 00076E04  4C C6 31 82 */	crclr 6
/* 8007A228 00076E08  38 BA 00 14 */	addi r5, r26, 0x14
/* 8007A22C 00076E0C  38 C6 00 2C */	addi r6, r6, 0x2c
/* 8007A230 00076E10  38 80 00 00 */	li r4, 0
/* 8007A234 00076E14  4B FE 5B A9 */	bl ef_Spawn
/* 8007A238 00076E18  48 00 04 70 */	b lbl_8007A6A8
lbl_8007A23C:
/* 8007A23C 00076E1C  80 7A 00 08 */	lwz r3, 8(r26)
/* 8007A240 00076E20  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007A244 00076E24  81 E3 05 18 */	lwz r15, 0x518(r3)
/* 8007A248 00076E28  7D E3 7B 78 */	mr r3, r15
/* 8007A24C 00076E2C  48 00 C7 15 */	bl func_80086960
/* 8007A250 00076E30  2C 03 00 00 */	cmpwi r3, 0
/* 8007A254 00076E34  41 82 00 18 */	beq lbl_8007A26C
/* 8007A258 00076E38  80 6F 00 2C */	lwz r3, 0x2c(r15)
/* 8007A25C 00076E3C  88 63 00 0C */	lbz r3, 0xc(r3)
/* 8007A260 00076E40  4B FB 96 95 */	bl Player_GetAttackRatio
/* 8007A264 00076E44  FE E0 08 90 */	fmr f23, f1
/* 8007A268 00076E48  48 00 00 08 */	b lbl_8007A270
lbl_8007A26C:
/* 8007A26C 00076E4C  C2 E2 89 0C */	lfs f23, lbl_804D82EC
lbl_8007A270:
/* 8007A270 00076E50  C2 DB 00 88 */	lfs f22, 0x88(r27)
/* 8007A274 00076E54  88 79 00 0C */	lbz r3, 0xc(r25)
/* 8007A278 00076E58  4B FB 97 69 */	bl Player_GetDefenseRatio
/* 8007A27C 00076E5C  FF 60 08 90 */	fmr f27, f1
/* 8007A280 00076E60  48 0F 0F C9 */	bl func_8016B248
/* 8007A284 00076E64  82 3A 00 0C */	lwz r17, 0xc(r26)
/* 8007A288 00076E68  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8007A28C 00076E6C  80 11 00 28 */	lwz r0, 0x28(r17)
/* 8007A290 00076E70  C0 03 00 F4 */	lfs f0, 0xf4(r3)
/* 8007A294 00076E74  28 00 00 00 */	cmplwi r0, 0
/* 8007A298 00076E78  80 BA 00 24 */	lwz r5, 0x24(r26)
/* 8007A29C 00076E7C  EC 56 00 32 */	fmuls f2, f22, f0
/* 8007A2A0 00076E80  41 82 00 90 */	beq lbl_8007A330
/* 8007A2A4 00076E84  C0 83 00 F8 */	lfs f4, 0xf8(r3)
/* 8007A2A8 00076E88  EC 1C 10 2A */	fadds f0, f28, f2
/* 8007A2AC 00076E8C  90 01 02 24 */	stw r0, 0x224(r1)
/* 8007A2B0 00076E90  EC 42 01 32 */	fmuls f2, f2, f4
/* 8007A2B4 00076E94  80 91 00 24 */	lwz r4, 0x24(r17)
/* 8007A2B8 00076E98  93 A1 02 20 */	stw r29, 0x220(r1)
/* 8007A2BC 00076E9C  80 11 00 2C */	lwz r0, 0x2c(r17)
/* 8007A2C0 00076EA0  EC 62 00 24 */	fdivs f3, f2, f0
/* 8007A2C4 00076EA4  C8 01 02 20 */	lfd f0, 0x220(r1)
/* 8007A2C8 00076EA8  90 81 02 2C */	stw r4, 0x22c(r1)
/* 8007A2CC 00076EAC  C1 03 01 18 */	lfs f8, 0x118(r3)
/* 8007A2D0 00076EB0  93 A1 02 28 */	stw r29, 0x228(r1)
/* 8007A2D4 00076EB4  EC 40 F0 28 */	fsubs f2, f0, f30
/* 8007A2D8 00076EB8  90 01 02 1C */	stw r0, 0x21c(r1)
/* 8007A2DC 00076EBC  C8 01 02 28 */	lfd f0, 0x228(r1)
/* 8007A2E0 00076EC0  EC A4 18 28 */	fsubs f5, f4, f3
/* 8007A2E4 00076EC4  93 A1 02 18 */	stw r29, 0x218(r1)
/* 8007A2E8 00076EC8  EC E0 F0 28 */	fsubs f7, f0, f30
/* 8007A2EC 00076ECC  C8 01 02 18 */	lfd f0, 0x218(r1)
/* 8007A2F0 00076ED0  EC 48 00 B2 */	fmuls f2, f8, f2
/* 8007A2F4 00076ED4  C0 63 01 14 */	lfs f3, 0x114(r3)
/* 8007A2F8 00076ED8  C0 83 01 10 */	lfs f4, 0x110(r3)
/* 8007A2FC 00076EDC  EC 63 00 B2 */	fmuls f3, f3, f2
/* 8007A300 00076EE0  C0 C3 01 1C */	lfs f6, 0x11c(r3)
/* 8007A304 00076EE4  C0 43 01 20 */	lfs f2, 0x120(r3)
/* 8007A308 00076EE8  EC FD 01 F2 */	fmuls f7, f29, f7
/* 8007A30C 00076EEC  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8007A310 00076EF0  EC 68 19 3A */	fmadds f3, f8, f4, f3
/* 8007A314 00076EF4  EC 65 00 F2 */	fmuls f3, f5, f3
/* 8007A318 00076EF8  EC 46 10 FA */	fmadds f2, f6, f3, f2
/* 8007A31C 00076EFC  EC 07 00 BA */	fmadds f0, f7, f2, f0
/* 8007A320 00076F00  EC 01 00 32 */	fmuls f0, f1, f0
/* 8007A324 00076F04  EC 17 00 32 */	fmuls f0, f23, f0
/* 8007A328 00076F08  EC 1B 00 32 */	fmuls f0, f27, f0
/* 8007A32C 00076F0C  48 00 00 DC */	b lbl_8007A408
lbl_8007A330:
/* 8007A330 00076F10  88 19 22 25 */	lbz r0, 0x2225(r25)
/* 8007A334 00076F14  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8007A338 00076F18  41 82 00 20 */	beq lbl_8007A358
/* 8007A33C 00076F1C  88 19 22 24 */	lbz r0, 0x2224(r25)
/* 8007A340 00076F20  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8007A344 00076F24  41 82 00 0C */	beq lbl_8007A350
/* 8007A348 00076F28  80 03 06 D8 */	lwz r0, 0x6d8(r3)
/* 8007A34C 00076F2C  48 00 00 1C */	b lbl_8007A368
lbl_8007A350:
/* 8007A350 00076F30  80 03 06 D4 */	lwz r0, 0x6d4(r3)
/* 8007A354 00076F34  48 00 00 14 */	b lbl_8007A368
lbl_8007A358:
/* 8007A358 00076F38  C0 19 18 30 */	lfs f0, 0x1830(r25)
/* 8007A35C 00076F3C  FC 00 00 1E */	fctiwz f0, f0
/* 8007A360 00076F40  D8 01 02 18 */	stfd f0, 0x218(r1)
/* 8007A364 00076F44  80 01 02 1C */	lwz r0, 0x21c(r1)
lbl_8007A368:
/* 8007A368 00076F48  C0 A3 00 F8 */	lfs f5, 0xf8(r3)
/* 8007A36C 00076F4C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8007A370 00076F50  90 01 02 24 */	stw r0, 0x224(r1)
/* 8007A374 00076F54  EC 1C 10 2A */	fadds f0, f28, f2
/* 8007A378 00076F58  EC 42 01 72 */	fmuls f2, f2, f5
/* 8007A37C 00076F5C  93 A1 02 20 */	stw r29, 0x220(r1)
/* 8007A380 00076F60  80 91 00 24 */	lwz r4, 0x24(r17)
/* 8007A384 00076F64  EC 82 00 24 */	fdivs f4, f2, f0
/* 8007A388 00076F68  90 A1 02 2C */	stw r5, 0x22c(r1)
/* 8007A38C 00076F6C  C8 41 02 20 */	lfd f2, 0x220(r1)
/* 8007A390 00076F70  93 A1 02 28 */	stw r29, 0x228(r1)
/* 8007A394 00076F74  80 11 00 2C */	lwz r0, 0x2c(r17)
/* 8007A398 00076F78  C8 01 02 28 */	lfd f0, 0x228(r1)
/* 8007A39C 00076F7C  EC 62 F8 28 */	fsubs f3, f2, f31
/* 8007A3A0 00076F80  C0 59 18 38 */	lfs f2, 0x1838(r25)
/* 8007A3A4 00076F84  EC 85 20 28 */	fsubs f4, f5, f4
/* 8007A3A8 00076F88  90 81 02 1C */	stw r4, 0x21c(r1)
/* 8007A3AC 00076F8C  EC E3 10 2A */	fadds f7, f3, f2
/* 8007A3B0 00076F90  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8007A3B4 00076F94  93 A1 02 18 */	stw r29, 0x218(r1)
/* 8007A3B8 00076F98  C0 43 01 14 */	lfs f2, 0x114(r3)
/* 8007A3BC 00076F9C  90 01 02 14 */	stw r0, 0x214(r1)
/* 8007A3C0 00076FA0  EC 00 01 F2 */	fmuls f0, f0, f7
/* 8007A3C4 00076FA4  C8 61 02 18 */	lfd f3, 0x218(r1)
/* 8007A3C8 00076FA8  93 A1 02 10 */	stw r29, 0x210(r1)
/* 8007A3CC 00076FAC  EC C3 F0 28 */	fsubs f6, f3, f30
/* 8007A3D0 00076FB0  C0 63 01 10 */	lfs f3, 0x110(r3)
/* 8007A3D4 00076FB4  EC 42 00 32 */	fmuls f2, f2, f0
/* 8007A3D8 00076FB8  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A3DC 00076FBC  C0 A3 01 1C */	lfs f5, 0x11c(r3)
/* 8007A3E0 00076FC0  EC 63 11 FA */	fmadds f3, f3, f7, f2
/* 8007A3E4 00076FC4  C0 43 01 20 */	lfs f2, 0x120(r3)
/* 8007A3E8 00076FC8  EC DD 01 B2 */	fmuls f6, f29, f6
/* 8007A3EC 00076FCC  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8007A3F0 00076FD0  EC 64 00 F2 */	fmuls f3, f4, f3
/* 8007A3F4 00076FD4  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 8007A3F8 00076FD8  EC 06 00 BA */	fmadds f0, f6, f2, f0
/* 8007A3FC 00076FDC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8007A400 00076FE0  EC 17 00 32 */	fmuls f0, f23, f0
/* 8007A404 00076FE4  EC 1B 00 32 */	fmuls f0, f27, f0
lbl_8007A408:
/* 8007A408 00076FE8  C0 23 01 08 */	lfs f1, 0x108(r3)
/* 8007A40C 00076FEC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8007A410 00076FF0  4C 41 13 82 */	cror 2, 1, 2
/* 8007A414 00076FF4  40 82 00 08 */	bne lbl_8007A41C
/* 8007A418 00076FF8  FC 00 08 90 */	fmr f0, f1
lbl_8007A41C:
/* 8007A41C 00076FFC  FE C0 00 90 */	fmr f22, f0
/* 8007A420 00077000  2C 15 00 00 */	cmpwi r21, 0
/* 8007A424 00077004  41 82 02 84 */	beq lbl_8007A6A8
/* 8007A428 00077008  C0 3A 00 20 */	lfs f1, 0x20(r26)
/* 8007A42C 0007700C  48 2A 84 95 */	bl __cvt_fp2unsigned
/* 8007A430 00077010  80 11 00 30 */	lwz r0, 0x30(r17)
/* 8007A434 00077014  80 B1 00 38 */	lwz r5, 0x38(r17)
/* 8007A438 00077018  54 00 10 3A */	slwi r0, r0, 2
/* 8007A43C 0007701C  80 DE 00 2C */	lwz r6, 0x2c(r30)
/* 8007A440 00077020  7C 9C 02 14 */	add r4, r28, r0
/* 8007A444 00077024  80 04 00 00 */	lwz r0, 0(r4)
/* 8007A448 00077028  2C 00 04 16 */	cmpwi r0, 0x416
/* 8007A44C 0007702C  41 82 00 70 */	beq lbl_8007A4BC
/* 8007A450 00077030  40 80 00 30 */	bge lbl_8007A480
/* 8007A454 00077034  2C 00 03 EB */	cmpwi r0, 0x3eb
/* 8007A458 00077038  41 82 02 50 */	beq lbl_8007A6A8
/* 8007A45C 0007703C  40 80 00 14 */	bge lbl_8007A470
/* 8007A460 00077040  2C 00 03 E8 */	cmpwi r0, 0x3e8
/* 8007A464 00077044  41 82 00 34 */	beq lbl_8007A498
/* 8007A468 00077048  40 80 00 54 */	bge lbl_8007A4BC
/* 8007A46C 0007704C  48 00 02 3C */	b lbl_8007A6A8
lbl_8007A470:
/* 8007A470 00077050  2C 00 03 ED */	cmpwi r0, 0x3ed
/* 8007A474 00077054  41 82 00 60 */	beq lbl_8007A4D4
/* 8007A478 00077058  40 80 02 30 */	bge lbl_8007A6A8
/* 8007A47C 0007705C  48 00 00 40 */	b lbl_8007A4BC
lbl_8007A480:
/* 8007A480 00077060  2C 00 04 E7 */	cmpwi r0, 0x4e7
/* 8007A484 00077064  41 82 00 38 */	beq lbl_8007A4BC
/* 8007A488 00077068  40 80 02 20 */	bge lbl_8007A6A8
/* 8007A48C 0007706C  2C 00 04 79 */	cmpwi r0, 0x479
/* 8007A490 00077070  41 82 00 2C */	beq lbl_8007A4BC
/* 8007A494 00077074  48 00 02 14 */	b lbl_8007A6A8
lbl_8007A498:
/* 8007A498 00077078  90 61 02 14 */	stw r3, 0x214(r1)
/* 8007A49C 0007707C  FC 40 B0 90 */	fmr f2, f22
/* 8007A4A0 00077080  7F C3 F3 78 */	mr r3, r30
/* 8007A4A4 00077084  93 A1 02 10 */	stw r29, 0x210(r1)
/* 8007A4A8 00077088  38 9A 00 14 */	addi r4, r26, 0x14
/* 8007A4AC 0007708C  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A4B0 00077090  EC 20 F0 28 */	fsubs f1, f0, f30
/* 8007A4B4 00077094  4B FF E0 85 */	bl func_80078538
/* 8007A4B8 00077098  48 00 01 F0 */	b lbl_8007A6A8
lbl_8007A4BC:
/* 8007A4BC 0007709C  7C 03 03 78 */	mr r3, r0
/* 8007A4C0 000770A0  4C C6 31 82 */	crclr 6
/* 8007A4C4 000770A4  38 BA 00 14 */	addi r5, r26, 0x14
/* 8007A4C8 000770A8  38 80 00 00 */	li r4, 0
/* 8007A4CC 000770AC  4B FE 59 11 */	bl ef_Spawn
/* 8007A4D0 000770B0  48 00 01 D8 */	b lbl_8007A6A8
lbl_8007A4D4:
/* 8007A4D4 000770B4  7C 03 03 78 */	mr r3, r0
/* 8007A4D8 000770B8  4C C6 31 82 */	crclr 6
/* 8007A4DC 000770BC  38 BA 00 14 */	addi r5, r26, 0x14
/* 8007A4E0 000770C0  38 C6 00 2C */	addi r6, r6, 0x2c
/* 8007A4E4 000770C4  38 80 00 00 */	li r4, 0
/* 8007A4E8 000770C8  4B FE 58 F5 */	bl ef_Spawn
/* 8007A4EC 000770CC  48 00 01 BC */	b lbl_8007A6A8
lbl_8007A4F0:
/* 8007A4F0 000770D0  38 61 00 D0 */	addi r3, r1, 0xd0
/* 8007A4F4 000770D4  80 9A 00 0C */	lwz r4, 0xc(r26)
/* 8007A4F8 000770D8  4B F8 E8 39 */	bl lbColl_80008D30
/* 8007A4FC 000770DC  C2 DB 00 88 */	lfs f22, 0x88(r27)
/* 8007A500 000770E0  88 79 00 0C */	lbz r3, 0xc(r25)
/* 8007A504 000770E4  4B FB 94 DD */	bl Player_GetDefenseRatio
/* 8007A508 000770E8  FF 60 08 90 */	fmr f27, f1
/* 8007A50C 000770EC  48 0F 0D 3D */	bl func_8016B248
/* 8007A510 000770F0  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 8007A514 000770F4  80 01 00 F8 */	lwz r0, 0xf8(r1)
/* 8007A518 000770F8  C0 05 00 F4 */	lfs f0, 0xf4(r5)
/* 8007A51C 000770FC  28 00 00 00 */	cmplwi r0, 0
/* 8007A520 00077100  80 81 00 D8 */	lwz r4, 0xd8(r1)
/* 8007A524 00077104  EC 56 00 32 */	fmuls f2, f22, f0
/* 8007A528 00077108  41 82 00 90 */	beq lbl_8007A5B8
/* 8007A52C 0007710C  C0 85 00 F8 */	lfs f4, 0xf8(r5)
/* 8007A530 00077110  EC 1C 10 2A */	fadds f0, f28, f2
/* 8007A534 00077114  90 01 02 1C */	stw r0, 0x21c(r1)
/* 8007A538 00077118  EC 42 01 32 */	fmuls f2, f2, f4
/* 8007A53C 0007711C  80 61 00 F4 */	lwz r3, 0xf4(r1)
/* 8007A540 00077120  93 A1 02 18 */	stw r29, 0x218(r1)
/* 8007A544 00077124  80 01 00 FC */	lwz r0, 0xfc(r1)
/* 8007A548 00077128  EC 62 00 24 */	fdivs f3, f2, f0
/* 8007A54C 0007712C  C8 01 02 18 */	lfd f0, 0x218(r1)
/* 8007A550 00077130  90 61 02 14 */	stw r3, 0x214(r1)
/* 8007A554 00077134  C1 05 01 18 */	lfs f8, 0x118(r5)
/* 8007A558 00077138  93 A1 02 10 */	stw r29, 0x210(r1)
/* 8007A55C 0007713C  EC 40 F0 28 */	fsubs f2, f0, f30
/* 8007A560 00077140  90 01 02 24 */	stw r0, 0x224(r1)
/* 8007A564 00077144  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A568 00077148  EC A4 18 28 */	fsubs f5, f4, f3
/* 8007A56C 0007714C  93 A1 02 20 */	stw r29, 0x220(r1)
/* 8007A570 00077150  EC E0 F0 28 */	fsubs f7, f0, f30
/* 8007A574 00077154  C8 01 02 20 */	lfd f0, 0x220(r1)
/* 8007A578 00077158  EC 48 00 B2 */	fmuls f2, f8, f2
/* 8007A57C 0007715C  C0 65 01 14 */	lfs f3, 0x114(r5)
/* 8007A580 00077160  C0 85 01 10 */	lfs f4, 0x110(r5)
/* 8007A584 00077164  EC 63 00 B2 */	fmuls f3, f3, f2
/* 8007A588 00077168  C0 C5 01 1C */	lfs f6, 0x11c(r5)
/* 8007A58C 0007716C  C0 45 01 20 */	lfs f2, 0x120(r5)
/* 8007A590 00077170  EC FD 01 F2 */	fmuls f7, f29, f7
/* 8007A594 00077174  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8007A598 00077178  EC 68 19 3A */	fmadds f3, f8, f4, f3
/* 8007A59C 0007717C  EC 65 00 F2 */	fmuls f3, f5, f3
/* 8007A5A0 00077180  EC 46 10 FA */	fmadds f2, f6, f3, f2
/* 8007A5A4 00077184  EC 07 00 BA */	fmadds f0, f7, f2, f0
/* 8007A5A8 00077188  EC 01 00 32 */	fmuls f0, f1, f0
/* 8007A5AC 0007718C  EC 1C 00 32 */	fmuls f0, f28, f0
/* 8007A5B0 00077190  EC 1B 00 32 */	fmuls f0, f27, f0
/* 8007A5B4 00077194  48 00 00 DC */	b lbl_8007A690
lbl_8007A5B8:
/* 8007A5B8 00077198  88 19 22 25 */	lbz r0, 0x2225(r25)
/* 8007A5BC 0007719C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8007A5C0 000771A0  41 82 00 20 */	beq lbl_8007A5E0
/* 8007A5C4 000771A4  88 19 22 24 */	lbz r0, 0x2224(r25)
/* 8007A5C8 000771A8  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8007A5CC 000771AC  41 82 00 0C */	beq lbl_8007A5D8
/* 8007A5D0 000771B0  80 05 06 D8 */	lwz r0, 0x6d8(r5)
/* 8007A5D4 000771B4  48 00 00 1C */	b lbl_8007A5F0
lbl_8007A5D8:
/* 8007A5D8 000771B8  80 05 06 D4 */	lwz r0, 0x6d4(r5)
/* 8007A5DC 000771BC  48 00 00 14 */	b lbl_8007A5F0
lbl_8007A5E0:
/* 8007A5E0 000771C0  C0 19 18 30 */	lfs f0, 0x1830(r25)
/* 8007A5E4 000771C4  FC 00 00 1E */	fctiwz f0, f0
/* 8007A5E8 000771C8  D8 01 02 10 */	stfd f0, 0x210(r1)
/* 8007A5EC 000771CC  80 01 02 14 */	lwz r0, 0x214(r1)
lbl_8007A5F0:
/* 8007A5F0 000771D0  C0 A5 00 F8 */	lfs f5, 0xf8(r5)
/* 8007A5F4 000771D4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8007A5F8 000771D8  90 01 02 1C */	stw r0, 0x21c(r1)
/* 8007A5FC 000771DC  EC 1C 10 2A */	fadds f0, f28, f2
/* 8007A600 000771E0  EC 42 01 72 */	fmuls f2, f2, f5
/* 8007A604 000771E4  93 A1 02 18 */	stw r29, 0x218(r1)
/* 8007A608 000771E8  80 61 00 F4 */	lwz r3, 0xf4(r1)
/* 8007A60C 000771EC  EC 82 00 24 */	fdivs f4, f2, f0
/* 8007A610 000771F0  90 81 02 24 */	stw r4, 0x224(r1)
/* 8007A614 000771F4  C8 41 02 18 */	lfd f2, 0x218(r1)
/* 8007A618 000771F8  93 A1 02 20 */	stw r29, 0x220(r1)
/* 8007A61C 000771FC  80 01 00 FC */	lwz r0, 0xfc(r1)
/* 8007A620 00077200  C8 01 02 20 */	lfd f0, 0x220(r1)
/* 8007A624 00077204  EC 62 F8 28 */	fsubs f3, f2, f31
/* 8007A628 00077208  C0 59 18 38 */	lfs f2, 0x1838(r25)
/* 8007A62C 0007720C  EC 85 20 28 */	fsubs f4, f5, f4
/* 8007A630 00077210  90 61 02 14 */	stw r3, 0x214(r1)
/* 8007A634 00077214  EC E3 10 2A */	fadds f7, f3, f2
/* 8007A638 00077218  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8007A63C 0007721C  93 A1 02 10 */	stw r29, 0x210(r1)
/* 8007A640 00077220  C0 45 01 14 */	lfs f2, 0x114(r5)
/* 8007A644 00077224  90 01 02 2C */	stw r0, 0x22c(r1)
/* 8007A648 00077228  EC 00 01 F2 */	fmuls f0, f0, f7
/* 8007A64C 0007722C  C8 61 02 10 */	lfd f3, 0x210(r1)
/* 8007A650 00077230  93 A1 02 28 */	stw r29, 0x228(r1)
/* 8007A654 00077234  EC C3 F0 28 */	fsubs f6, f3, f30
/* 8007A658 00077238  C0 65 01 10 */	lfs f3, 0x110(r5)
/* 8007A65C 0007723C  EC 42 00 32 */	fmuls f2, f2, f0
/* 8007A660 00077240  C8 01 02 28 */	lfd f0, 0x228(r1)
/* 8007A664 00077244  C0 A5 01 1C */	lfs f5, 0x11c(r5)
/* 8007A668 00077248  EC 63 11 FA */	fmadds f3, f3, f7, f2
/* 8007A66C 0007724C  C0 45 01 20 */	lfs f2, 0x120(r5)
/* 8007A670 00077250  EC DD 01 B2 */	fmuls f6, f29, f6
/* 8007A674 00077254  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8007A678 00077258  EC 64 00 F2 */	fmuls f3, f4, f3
/* 8007A67C 0007725C  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 8007A680 00077260  EC 06 00 BA */	fmadds f0, f6, f2, f0
/* 8007A684 00077264  EC 01 00 32 */	fmuls f0, f1, f0
/* 8007A688 00077268  EC 1C 00 32 */	fmuls f0, f28, f0
/* 8007A68C 0007726C  EC 1B 00 32 */	fmuls f0, f27, f0
lbl_8007A690:
/* 8007A690 00077270  C0 25 01 08 */	lfs f1, 0x108(r5)
/* 8007A694 00077274  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8007A698 00077278  4C 41 13 82 */	cror 2, 1, 2
/* 8007A69C 0007727C  40 82 00 08 */	bne lbl_8007A6A4
/* 8007A6A0 00077280  FC 00 08 90 */	fmr f0, f1
lbl_8007A6A4:
/* 8007A6A4 00077284  FE C0 00 90 */	fmr f22, f0
lbl_8007A6A8:
/* 8007A6A8 00077288  FC 16 D0 40 */	fcmpo cr0, f22, f26
/* 8007A6AC 0007728C  40 81 00 60 */	ble lbl_8007A70C
/* 8007A6B0 00077290  80 1A 00 00 */	lwz r0, 0(r26)
/* 8007A6B4 00077294  2C 00 00 01 */	cmpwi r0, 1
/* 8007A6B8 00077298  40 82 00 3C */	bne lbl_8007A6F4
/* 8007A6BC 0007729C  80 79 1A 58 */	lwz r3, 0x1a58(r25)
/* 8007A6C0 000772A0  28 03 00 00 */	cmplwi r3, 0
/* 8007A6C4 000772A4  41 82 00 30 */	beq lbl_8007A6F4
/* 8007A6C8 000772A8  88 19 22 1B */	lbz r0, 0x221b(r25)
/* 8007A6CC 000772AC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8007A6D0 000772B0  40 82 00 24 */	bne lbl_8007A6F4
/* 8007A6D4 000772B4  80 1A 00 08 */	lwz r0, 8(r26)
/* 8007A6D8 000772B8  7C 03 00 40 */	cmplw r3, r0
/* 8007A6DC 000772BC  40 82 00 18 */	bne lbl_8007A6F4
/* 8007A6E0 000772C0  88 19 22 1C */	lbz r0, 0x221c(r25)
/* 8007A6E4 000772C4  38 60 00 01 */	li r3, 1
/* 8007A6E8 000772C8  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8007A6EC 000772CC  98 19 22 1C */	stb r0, 0x221c(r25)
/* 8007A6F0 000772D0  48 00 00 14 */	b lbl_8007A704
lbl_8007A6F4:
/* 8007A6F4 000772D4  88 19 22 1C */	lbz r0, 0x221c(r25)
/* 8007A6F8 000772D8  38 60 00 00 */	li r3, 0
/* 8007A6FC 000772DC  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8007A700 000772E0  98 19 22 1C */	stb r0, 0x221c(r25)
lbl_8007A704:
/* 8007A704 000772E4  FF 40 B0 90 */	fmr f26, f22
/* 8007A708 000772E8  7F 17 C3 78 */	mr r23, r24
lbl_8007A70C:
/* 8007A70C 000772EC  3B 5A 00 28 */	addi r26, r26, 0x28
/* 8007A710 000772F0  3B 18 00 01 */	addi r24, r24, 1
lbl_8007A714:
/* 8007A714 000772F4  7C 18 A0 40 */	cmplw r24, r20
/* 8007A718 000772F8  41 80 F9 DC */	blt lbl_8007A0F4
/* 8007A71C 000772FC  1C 17 00 28 */	mulli r0, r23, 0x28
/* 8007A720 00077300  7E 33 02 14 */	add r17, r19, r0
/* 8007A724 00077304  80 11 00 00 */	lwz r0, 0(r17)
/* 8007A728 00077308  2C 00 00 02 */	cmpwi r0, 2
/* 8007A72C 0007730C  41 82 00 74 */	beq lbl_8007A7A0
/* 8007A730 00077310  40 80 00 10 */	bge lbl_8007A740
/* 8007A734 00077314  2C 00 00 01 */	cmpwi r0, 1
/* 8007A738 00077318  40 80 00 14 */	bge lbl_8007A74C
/* 8007A73C 0007731C  48 00 01 28 */	b lbl_8007A864
lbl_8007A740:
/* 8007A740 00077320  2C 00 00 04 */	cmpwi r0, 4
/* 8007A744 00077324  40 80 01 20 */	bge lbl_8007A864
/* 8007A748 00077328  48 00 00 F0 */	b lbl_8007A838
lbl_8007A74C:
/* 8007A74C 0007732C  80 71 00 08 */	lwz r3, 8(r17)
/* 8007A750 00077330  C0 39 00 B0 */	lfs f1, 0xb0(r25)
/* 8007A754 00077334  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007A758 00077338  C0 03 00 B0 */	lfs f0, 0xb0(r3)
/* 8007A75C 0007733C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A760 00077340  40 81 00 0C */	ble lbl_8007A76C
/* 8007A764 00077344  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 8007A768 00077348  48 00 00 08 */	b lbl_8007A770
lbl_8007A76C:
/* 8007A76C 0007734C  C0 02 89 0C */	lfs f0, lbl_804D82EC
lbl_8007A770:
/* 8007A770 00077350  80 91 00 0C */	lwz r4, 0xc(r17)
/* 8007A774 00077354  3C 00 43 30 */	lis r0, 0x4330
/* 8007A778 00077358  C8 22 89 28 */	lfd f1, lbl_804D8308
/* 8007A77C 0007735C  FF 00 00 90 */	fmr f24, f0
/* 8007A780 00077360  80 64 00 20 */	lwz r3, 0x20(r4)
/* 8007A784 00077364  82 44 00 30 */	lwz r18, 0x30(r4)
/* 8007A788 00077368  90 61 02 14 */	stw r3, 0x214(r1)
/* 8007A78C 0007736C  82 C4 00 38 */	lwz r22, 0x38(r4)
/* 8007A790 00077370  90 01 02 10 */	stw r0, 0x210(r1)
/* 8007A794 00077374  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A798 00077378  EF 20 08 28 */	fsubs f25, f0, f1
/* 8007A79C 0007737C  48 00 00 C8 */	b lbl_8007A864
lbl_8007A7A0:
/* 8007A7A0 00077380  80 71 00 08 */	lwz r3, 8(r17)
/* 8007A7A4 00077384  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007A7A8 00077388  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8007A7AC 0007738C  C0 24 00 40 */	lfs f1, 0x40(r4)
/* 8007A7B0 00077390  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A7B4 00077394  40 80 00 08 */	bge lbl_8007A7BC
/* 8007A7B8 00077398  FC 20 08 50 */	fneg f1, f1
lbl_8007A7BC:
/* 8007A7BC 0007739C  80 6D B6 88 */	lwz r3, lbl_804D6D28
/* 8007A7C0 000773A0  C0 03 00 78 */	lfs f0, 0x78(r3)
/* 8007A7C4 000773A4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A7C8 000773A8  40 80 00 24 */	bge lbl_8007A7EC
/* 8007A7CC 000773AC  C0 39 00 B0 */	lfs f1, 0xb0(r25)
/* 8007A7D0 000773B0  C0 04 00 4C */	lfs f0, 0x4c(r4)
/* 8007A7D4 000773B4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A7D8 000773B8  40 81 00 0C */	ble lbl_8007A7E4
/* 8007A7DC 000773BC  C0 02 89 10 */	lfs f0, lbl_804D82F0
/* 8007A7E0 000773C0  48 00 00 28 */	b lbl_8007A808
lbl_8007A7E4:
/* 8007A7E4 000773C4  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 8007A7E8 000773C8  48 00 00 20 */	b lbl_8007A808
lbl_8007A7EC:
/* 8007A7EC 000773CC  C0 24 00 40 */	lfs f1, 0x40(r4)
/* 8007A7F0 000773D0  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007A7F4 000773D4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A7F8 000773D8  40 80 00 0C */	bge lbl_8007A804
/* 8007A7FC 000773DC  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 8007A800 000773E0  48 00 00 08 */	b lbl_8007A808
lbl_8007A804:
/* 8007A804 000773E4  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_8007A808:
/* 8007A808 000773E8  80 91 00 0C */	lwz r4, 0xc(r17)
/* 8007A80C 000773EC  3C 00 43 30 */	lis r0, 0x4330
/* 8007A810 000773F0  C8 22 89 28 */	lfd f1, lbl_804D8308
/* 8007A814 000773F4  FF 00 00 90 */	fmr f24, f0
/* 8007A818 000773F8  80 64 00 20 */	lwz r3, 0x20(r4)
/* 8007A81C 000773FC  82 44 00 30 */	lwz r18, 0x30(r4)
/* 8007A820 00077400  90 61 02 14 */	stw r3, 0x214(r1)
/* 8007A824 00077404  82 C4 00 38 */	lwz r22, 0x38(r4)
/* 8007A828 00077408  90 01 02 10 */	stw r0, 0x210(r1)
/* 8007A82C 0007740C  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A830 00077410  EF 20 08 28 */	fsubs f25, f0, f1
/* 8007A834 00077414  48 00 00 30 */	b lbl_8007A864
lbl_8007A838:
/* 8007A838 00077418  80 91 00 0C */	lwz r4, 0xc(r17)
/* 8007A83C 0007741C  3C 00 43 30 */	lis r0, 0x4330
/* 8007A840 00077420  C8 22 89 28 */	lfd f1, lbl_804D8308
/* 8007A844 00077424  3A C0 00 00 */	li r22, 0
/* 8007A848 00077428  80 64 00 08 */	lwz r3, 8(r4)
/* 8007A84C 0007742C  C3 19 00 2C */	lfs f24, 0x2c(r25)
/* 8007A850 00077430  90 61 02 14 */	stw r3, 0x214(r1)
/* 8007A854 00077434  82 44 00 18 */	lwz r18, 0x18(r4)
/* 8007A858 00077438  90 01 02 10 */	stw r0, 0x210(r1)
/* 8007A85C 0007743C  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A860 00077440  EF 20 08 28 */	fsubs f25, f0, f1
lbl_8007A864:
/* 8007A864 00077444  80 71 00 0C */	lwz r3, 0xc(r17)
/* 8007A868 00077448  80 03 00 20 */	lwz r0, 0x20(r3)
/* 8007A86C 0007744C  28 00 01 6A */	cmplwi r0, 0x16a
/* 8007A870 00077450  40 82 00 B4 */	bne lbl_8007A924
/* 8007A874 00077454  80 71 00 10 */	lwz r3, 0x10(r17)
/* 8007A878 00077458  C0 A2 89 08 */	lfs f5, lbl_804D82E8
/* 8007A87C 0007745C  C0 23 00 28 */	lfs f1, 0x28(r3)
/* 8007A880 00077460  C0 03 00 34 */	lfs f0, 0x34(r3)
/* 8007A884 00077464  C0 71 00 14 */	lfs f3, 0x14(r17)
/* 8007A888 00077468  EC 81 00 2A */	fadds f4, f1, f0
/* 8007A88C 0007746C  C0 43 00 2C */	lfs f2, 0x2c(r3)
/* 8007A890 00077470  C0 23 00 38 */	lfs f1, 0x38(r3)
/* 8007A894 00077474  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007A898 00077478  EC 65 19 38 */	fmsubs f3, f5, f4, f3
/* 8007A89C 0007747C  EC 42 08 2A */	fadds f2, f2, f1
/* 8007A8A0 00077480  C0 31 00 18 */	lfs f1, 0x18(r17)
/* 8007A8A4 00077484  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8007A8A8 00077488  EC 45 08 B8 */	fmsubs f2, f5, f2, f1
/* 8007A8AC 0007748C  40 80 00 0C */	bge lbl_8007A8B8
/* 8007A8B0 00077490  C0 22 89 0C */	lfs f1, lbl_804D82EC
/* 8007A8B4 00077494  48 00 00 08 */	b lbl_8007A8BC
lbl_8007A8B8:
/* 8007A8B8 00077498  C0 22 89 10 */	lfs f1, lbl_804D82F0
lbl_8007A8BC:
/* 8007A8BC 0007749C  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007A8C0 000774A0  FF 00 08 90 */	fmr f24, f1
/* 8007A8C4 000774A4  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8007A8C8 000774A8  40 80 00 0C */	bge lbl_8007A8D4
/* 8007A8CC 000774AC  FC 20 18 50 */	fneg f1, f3
/* 8007A8D0 000774B0  48 00 00 08 */	b lbl_8007A8D8
lbl_8007A8D4:
/* 8007A8D4 000774B4  FC 20 18 90 */	fmr f1, f3
lbl_8007A8D8:
/* 8007A8D8 000774B8  C0 02 89 38 */	lfs f0, lbl_804D8318
/* 8007A8DC 000774BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007A8E0 000774C0  40 80 00 0C */	bge lbl_8007A8EC
/* 8007A8E4 000774C4  38 00 00 00 */	li r0, 0
/* 8007A8E8 000774C8  48 00 00 20 */	b lbl_8007A908
lbl_8007A8EC:
/* 8007A8EC 000774CC  EC 22 08 24 */	fdivs f1, f2, f1
/* 8007A8F0 000774D0  4B FA 85 79 */	bl atanf
/* 8007A8F4 000774D4  C0 02 89 3C */	lfs f0, lbl_804D831C
/* 8007A8F8 000774D8  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007A8FC 000774DC  FC 00 00 1E */	fctiwz f0, f0
/* 8007A900 000774E0  D8 01 02 10 */	stfd f0, 0x210(r1)
/* 8007A904 000774E4  80 01 02 14 */	lwz r0, 0x214(r1)
lbl_8007A908:
/* 8007A908 000774E8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8007A90C 000774EC  C8 22 89 18 */	lfd f1, lbl_804D82F8
/* 8007A910 000774F0  90 01 02 14 */	stw r0, 0x214(r1)
/* 8007A914 000774F4  3C 00 43 30 */	lis r0, 0x4330
/* 8007A918 000774F8  90 01 02 10 */	stw r0, 0x210(r1)
/* 8007A91C 000774FC  C8 01 02 10 */	lfd f0, 0x210(r1)
/* 8007A920 00077500  EF 20 08 28 */	fsubs f25, f0, f1
lbl_8007A924:
/* 8007A924 00077504  FC 00 C8 1E */	fctiwz f0, f25
/* 8007A928 00077508  D3 1F 00 00 */	stfs f24, 0(r31)
/* 8007A92C 0007750C  D8 01 02 10 */	stfd f0, 0x210(r1)
/* 8007A930 00077510  80 01 02 14 */	lwz r0, 0x214(r1)
/* 8007A934 00077514  90 1F 00 04 */	stw r0, 4(r31)
/* 8007A938 00077518  80 71 00 10 */	lwz r3, 0x10(r17)
/* 8007A93C 0007751C  80 03 00 44 */	lwz r0, 0x44(r3)
/* 8007A940 00077520  90 1F 00 08 */	stw r0, 8(r31)
/* 8007A944 00077524  D3 5F 00 0C */	stfs f26, 0xc(r31)
/* 8007A948 00077528  80 71 00 14 */	lwz r3, 0x14(r17)
/* 8007A94C 0007752C  80 11 00 18 */	lwz r0, 0x18(r17)
/* 8007A950 00077530  90 7F 00 10 */	stw r3, 0x10(r31)
/* 8007A954 00077534  90 1F 00 14 */	stw r0, 0x14(r31)
/* 8007A958 00077538  80 11 00 1C */	lwz r0, 0x1c(r17)
/* 8007A95C 0007753C  90 1F 00 18 */	stw r0, 0x18(r31)
/* 8007A960 00077540  92 5F 00 1C */	stw r18, 0x1c(r31)
/* 8007A964 00077544  80 11 00 08 */	lwz r0, 8(r17)
/* 8007A968 00077548  90 1F 00 24 */	stw r0, 0x24(r31)
/* 8007A96C 0007754C  C0 11 00 20 */	lfs f0, 0x20(r17)
/* 8007A970 00077550  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 8007A974 00077554  92 DF 00 20 */	stw r22, 0x20(r31)
/* 8007A978 00077558  80 11 00 00 */	lwz r0, 0(r17)
/* 8007A97C 0007755C  2C 00 00 02 */	cmpwi r0, 2
/* 8007A980 00077560  41 82 00 5C */	beq lbl_8007A9DC
/* 8007A984 00077564  40 80 00 10 */	bge lbl_8007A994
/* 8007A988 00077568  2C 00 00 01 */	cmpwi r0, 1
/* 8007A98C 0007756C  40 80 00 14 */	bge lbl_8007A9A0
/* 8007A990 00077570  48 00 01 64 */	b lbl_8007AAF4
lbl_8007A994:
/* 8007A994 00077574  2C 00 00 04 */	cmpwi r0, 4
/* 8007A998 00077578  40 80 01 5C */	bge lbl_8007AAF4
/* 8007A99C 0007757C  48 00 01 2C */	b lbl_8007AAC8
lbl_8007A9A0:
/* 8007A9A0 00077580  80 71 00 08 */	lwz r3, 8(r17)
/* 8007A9A4 00077584  38 00 00 00 */	li r0, 0
/* 8007A9A8 00077588  38 9E 00 00 */	addi r4, r30, 0
/* 8007A9AC 0007758C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007A9B0 00077590  39 5F 00 00 */	addi r10, r31, 0
/* 8007A9B4 00077594  38 A0 00 01 */	li r5, 1
/* 8007A9B8 00077598  80 63 00 00 */	lwz r3, 0(r3)
/* 8007A9BC 0007759C  81 23 00 2C */	lwz r9, 0x2c(r3)
/* 8007A9C0 000775A0  90 01 00 08 */	stw r0, 8(r1)
/* 8007A9C4 000775A4  39 09 20 74 */	addi r8, r9, 0x2074
/* 8007A9C8 000775A8  80 C9 00 04 */	lwz r6, 4(r9)
/* 8007A9CC 000775AC  80 E9 20 70 */	lwz r7, 0x2070(r9)
/* 8007A9D0 000775B0  A1 29 20 88 */	lhz r9, 0x2088(r9)
/* 8007A9D4 000775B4  4B FF DC 49 */	bl func_8007861C
/* 8007A9D8 000775B8  48 00 01 1C */	b lbl_8007AAF4
lbl_8007A9DC:
/* 8007A9DC 000775BC  80 71 00 08 */	lwz r3, 8(r17)
/* 8007A9E0 000775C0  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8007A9E4 000775C4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007A9E8 000775C8  80 63 00 04 */	lwz r3, 4(r3)
/* 8007A9EC 000775CC  82 23 00 2C */	lwz r17, 0x2c(r3)
/* 8007A9F0 000775D0  80 11 00 10 */	lwz r0, 0x10(r17)
/* 8007A9F4 000775D4  82 11 05 18 */	lwz r16, 0x518(r17)
/* 8007A9F8 000775D8  2C 00 00 06 */	cmpwi r0, 6
/* 8007A9FC 000775DC  40 82 00 1C */	bne lbl_8007AA18
/* 8007AA00 000775E0  88 85 22 1F */	lbz r4, 0x221f(r5)
/* 8007AA04 000775E4  80 11 00 1C */	lwz r0, 0x1c(r17)
/* 8007AA08 000775E8  88 65 00 0C */	lbz r3, 0xc(r5)
/* 8007AA0C 000775EC  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8007AA10 000775F0  54 05 04 3E */	clrlwi r5, r0, 0x10
/* 8007AA14 000775F4  4B FC 70 F5 */	bl func_80041B08
lbl_8007AA18:
/* 8007AA18 000775F8  7E 03 83 78 */	mr r3, r16
/* 8007AA1C 000775FC  48 00 BF 45 */	bl func_80086960
/* 8007AA20 00077600  2C 03 00 00 */	cmpwi r3, 0
/* 8007AA24 00077604  41 82 00 34 */	beq lbl_8007AA58
/* 8007AA28 00077608  38 00 00 00 */	li r0, 0
/* 8007AA2C 0007760C  90 01 00 08 */	stw r0, 8(r1)
/* 8007AA30 00077610  38 70 00 00 */	addi r3, r16, 0
/* 8007AA34 00077614  38 9E 00 00 */	addi r4, r30, 0
/* 8007AA38 00077618  80 D1 00 10 */	lwz r6, 0x10(r17)
/* 8007AA3C 0007761C  7F EA FB 78 */	mr r10, r31
/* 8007AA40 00077620  80 F1 0D 90 */	lwz r7, 0xd90(r17)
/* 8007AA44 00077624  39 11 0D 94 */	addi r8, r17, 0xd94
/* 8007AA48 00077628  A1 31 0D A8 */	lhz r9, 0xda8(r17)
/* 8007AA4C 0007762C  38 A0 00 02 */	li r5, 2
/* 8007AA50 00077630  4B FF DB CD */	bl func_8007861C
/* 8007AA54 00077634  48 00 00 A0 */	b lbl_8007AAF4
lbl_8007AA58:
/* 8007AA58 00077638  80 71 00 10 */	lwz r3, 0x10(r17)
/* 8007AA5C 0007763C  4B FC 2B B1 */	bl func_8003D60C
/* 8007AA60 00077640  2C 03 00 00 */	cmpwi r3, 0
/* 8007AA64 00077644  41 82 00 34 */	beq lbl_8007AA98
/* 8007AA68 00077648  38 00 00 01 */	li r0, 1
/* 8007AA6C 0007764C  90 01 00 08 */	stw r0, 8(r1)
/* 8007AA70 00077650  38 9E 00 00 */	addi r4, r30, 0
/* 8007AA74 00077654  39 5F 00 00 */	addi r10, r31, 0
/* 8007AA78 00077658  80 D1 00 10 */	lwz r6, 0x10(r17)
/* 8007AA7C 0007765C  39 11 0D 94 */	addi r8, r17, 0xd94
/* 8007AA80 00077660  80 F1 0D 90 */	lwz r7, 0xd90(r17)
/* 8007AA84 00077664  38 60 00 00 */	li r3, 0
/* 8007AA88 00077668  A1 31 0D A8 */	lhz r9, 0xda8(r17)
/* 8007AA8C 0007766C  38 A0 00 02 */	li r5, 2
/* 8007AA90 00077670  4B FF DB 8D */	bl func_8007861C
/* 8007AA94 00077674  48 00 00 60 */	b lbl_8007AAF4
lbl_8007AA98:
/* 8007AA98 00077678  38 00 00 00 */	li r0, 0
/* 8007AA9C 0007767C  90 01 00 08 */	stw r0, 8(r1)
/* 8007AAA0 00077680  38 9E 00 00 */	addi r4, r30, 0
/* 8007AAA4 00077684  39 5F 00 00 */	addi r10, r31, 0
/* 8007AAA8 00077688  80 D1 00 10 */	lwz r6, 0x10(r17)
/* 8007AAAC 0007768C  39 11 0D 94 */	addi r8, r17, 0xd94
/* 8007AAB0 00077690  80 F1 0D 90 */	lwz r7, 0xd90(r17)
/* 8007AAB4 00077694  38 60 00 00 */	li r3, 0
/* 8007AAB8 00077698  A1 31 0D A8 */	lhz r9, 0xda8(r17)
/* 8007AABC 0007769C  38 A0 00 02 */	li r5, 2
/* 8007AAC0 000776A0  4B FF DB 5D */	bl func_8007861C
/* 8007AAC4 000776A4  48 00 00 30 */	b lbl_8007AAF4
lbl_8007AAC8:
/* 8007AAC8 000776A8  80 D1 00 04 */	lwz r6, 4(r17)
/* 8007AACC 000776AC  38 00 00 01 */	li r0, 1
/* 8007AAD0 000776B0  38 9E 00 00 */	addi r4, r30, 0
/* 8007AAD4 000776B4  90 01 00 08 */	stw r0, 8(r1)
/* 8007AAD8 000776B8  39 5F 00 00 */	addi r10, r31, 0
/* 8007AADC 000776BC  38 60 00 00 */	li r3, 0
/* 8007AAE0 000776C0  38 A0 00 03 */	li r5, 3
/* 8007AAE4 000776C4  38 E0 00 00 */	li r7, 0
/* 8007AAE8 000776C8  39 00 00 00 */	li r8, 0
/* 8007AAEC 000776CC  39 20 00 00 */	li r9, 0
/* 8007AAF0 000776D0  4B FF DB 2D */	bl func_8007861C
lbl_8007AAF4:
/* 8007AAF4 000776D4  80 1F 00 1C */	lwz r0, 0x1c(r31)
/* 8007AAF8 000776D8  28 00 00 02 */	cmplwi r0, 2
/* 8007AAFC 000776DC  40 82 00 10 */	bne lbl_8007AB0C
/* 8007AB00 000776E0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8007AB04 000776E4  C0 03 01 A4 */	lfs f0, 0x1a4(r3)
/* 8007AB08 000776E8  D0 19 19 60 */	stfs f0, 0x1960(r25)
lbl_8007AB0C:
/* 8007AB0C 000776EC  B9 E1 02 34 */	lmw r15, 0x234(r1)
/* 8007AB10 000776F0  80 01 02 CC */	lwz r0, 0x2cc(r1)
/* 8007AB14 000776F4  CB E1 02 C0 */	lfd f31, 0x2c0(r1)
/* 8007AB18 000776F8  CB C1 02 B8 */	lfd f30, 0x2b8(r1)
/* 8007AB1C 000776FC  CB A1 02 B0 */	lfd f29, 0x2b0(r1)
/* 8007AB20 00077700  CB 81 02 A8 */	lfd f28, 0x2a8(r1)
/* 8007AB24 00077704  CB 61 02 A0 */	lfd f27, 0x2a0(r1)
/* 8007AB28 00077708  CB 41 02 98 */	lfd f26, 0x298(r1)
/* 8007AB2C 0007770C  CB 21 02 90 */	lfd f25, 0x290(r1)
/* 8007AB30 00077710  CB 01 02 88 */	lfd f24, 0x288(r1)
/* 8007AB34 00077714  CA E1 02 80 */	lfd f23, 0x280(r1)
/* 8007AB38 00077718  CA C1 02 78 */	lfd f22, 0x278(r1)
/* 8007AB3C 0007771C  38 21 02 C8 */	addi r1, r1, 0x2c8
/* 8007AB40 00077720  7C 08 03 A6 */	mtlr r0
/* 8007AB44 00077724  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AB48(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AB48 00077728  7C 08 02 A6 */	mflr r0
/* 8007AB4C 0007772C  3C 80 80 46 */	lis r4, lbl_80459278@ha
/* 8007AB50 00077730  90 01 00 04 */	stw r0, 4(r1)
/* 8007AB54 00077734  38 A4 92 78 */	addi r5, r4, lbl_80459278@l
/* 8007AB58 00077738  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007AB5C 0007773C  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 8007AB60 00077740  80 CD AE B8 */	lwz r6, lbl_804D6558
/* 8007AB64 00077744  38 87 18 44 */	addi r4, r7, 0x1844
/* 8007AB68 00077748  38 E0 00 01 */	li r7, 1
/* 8007AB6C 0007774C  4B FF F5 01 */	bl func_8007A06C
/* 8007AB70 00077750  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007AB74 00077754  38 21 00 08 */	addi r1, r1, 8
/* 8007AB78 00077758  7C 08 03 A6 */	mtlr r0
/* 8007AB7C 0007775C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AB80(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AB80 00077760  7C 08 02 A6 */	mflr r0
/* 8007AB84 00077764  3C 80 80 46 */	lis r4, lbl_80459598@ha
/* 8007AB88 00077768  90 01 00 04 */	stw r0, 4(r1)
/* 8007AB8C 0007776C  38 A4 95 98 */	addi r5, r4, lbl_80459598@l
/* 8007AB90 00077770  38 E0 00 00 */	li r7, 0
/* 8007AB94 00077774  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8007AB98 00077778  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007AB9C 0007777C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8007ABA0 00077780  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 8007ABA4 00077784  38 9F 18 70 */	addi r4, r31, 0x1870
/* 8007ABA8 00077788  D0 1F 18 7C */	stfs f0, 0x187c(r31)
/* 8007ABAC 0007778C  80 CD AE BC */	lwz r6, lbl_804D655C
/* 8007ABB0 00077790  4B FF F4 BD */	bl func_8007A06C
/* 8007ABB4 00077794  C0 1F 18 7C */	lfs f0, 0x187c(r31)
/* 8007ABB8 00077798  D0 1F 18 A0 */	stfs f0, 0x18a0(r31)
/* 8007ABBC 0007779C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007ABC0 000777A0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8007ABC4 000777A4  38 21 00 18 */	addi r1, r1, 0x18
/* 8007ABC8 000777A8  7C 08 03 A6 */	mtlr r0
/* 8007ABCC 000777AC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007ABD0(HitCapsule*, u32, HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007ABD0 000777B0  7C 08 02 A6 */	mflr r0
/* 8007ABD4 000777B4  90 01 00 04 */	stw r0, 4(r1)
/* 8007ABD8 000777B8  3C 00 43 30 */	lis r0, 0x4330
/* 8007ABDC 000777BC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8007ABE0 000777C0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8007ABE4 000777C4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8007ABE8 000777C8  7C 7E 1B 78 */	mr r30, r3
/* 8007ABEC 000777CC  80 A5 00 2C */	lwz r5, 0x2c(r5)
/* 8007ABF0 000777D0  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8007ABF4 000777D4  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 8007ABF8 000777D8  7C BF 2B 78 */	mr r31, r5
/* 8007ABFC 000777DC  90 01 00 18 */	stw r0, 0x18(r1)
/* 8007AC00 000777E0  C0 45 00 38 */	lfs f2, 0x38(r5)
/* 8007AC04 000777E4  C8 62 89 28 */	lfd f3, lbl_804D8308
/* 8007AC08 000777E8  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 8007AC0C 000777EC  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8007AC10 000777F0  EC 21 18 28 */	fsubs f1, f1, f3
/* 8007AC14 000777F4  41 82 00 10 */	beq lbl_8007AC24
/* 8007AC18 000777F8  80 6D AE 84 */	lwz r3, lbl_804D6524
/* 8007AC1C 000777FC  C0 63 00 04 */	lfs f3, 4(r3)
/* 8007AC20 00077800  48 05 49 75 */	bl func_800CF594
lbl_8007AC24:
/* 8007AC24 00077804  7F E3 FB 78 */	mr r3, r31
/* 8007AC28 00077808  48 06 42 91 */	bl func_800DEEB8
/* 8007AC2C 0007780C  FC 00 08 1E */	fctiwz f0, f1
/* 8007AC30 00077810  7F E3 FB 78 */	mr r3, r31
/* 8007AC34 00077814  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8007AC38 00077818  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007AC3C 0007781C  90 1E 00 08 */	stw r0, 8(r30)
/* 8007AC40 00077820  80 9F 20 68 */	lwz r4, 0x2068(r31)
/* 8007AC44 00077824  A0 BF 20 6C */	lhz r5, 0x206c(r31)
/* 8007AC48 00077828  48 00 E5 E1 */	bl func_80089228
/* 8007AC4C 0007782C  D0 3E 00 0C */	stfs f1, 0xc(r30)
/* 8007AC50 00077830  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8007AC54 00077834  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8007AC58 00077838  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8007AC5C 0007783C  38 21 00 28 */	addi r1, r1, 0x28
/* 8007AC60 00077840  7C 08 03 A6 */	mtlr r0
/* 8007AC64 00077844  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AC68(void)
{ // clang-format off
    nofralloc
/* 8007AC68 00077848  28 03 01 69 */	cmplwi r3, 0x169
/* 8007AC6C 0007784C  41 82 00 28 */	beq lbl_8007AC94
/* 8007AC70 00077850  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8007AC74 00077854  80 04 07 E8 */	lwz r0, 0x7e8(r4)
/* 8007AC78 00077858  7C 00 18 40 */	cmplw r0, r3
/* 8007AC7C 0007785C  41 81 00 18 */	bgt lbl_8007AC94
/* 8007AC80 00077860  80 04 07 EC */	lwz r0, 0x7ec(r4)
/* 8007AC84 00077864  7C 03 00 40 */	cmplw r3, r0
/* 8007AC88 00077868  41 81 00 0C */	bgt lbl_8007AC94
/* 8007AC8C 0007786C  38 60 00 01 */	li r3, 1
/* 8007AC90 00077870  4E 80 00 20 */	blr
lbl_8007AC94:
/* 8007AC94 00077874  38 60 00 00 */	li r3, 0
/* 8007AC98 00077878  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AC9C(void)
{ // clang-format off
    nofralloc
/* 8007AC9C 0007787C  7C 08 02 A6 */	mflr r0
/* 8007ACA0 00077880  28 04 01 69 */	cmplwi r4, 0x169
/* 8007ACA4 00077884  90 01 00 04 */	stw r0, 4(r1)
/* 8007ACA8 00077888  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007ACAC 0007788C  80 C5 00 2C */	lwz r6, 0x2c(r5)
/* 8007ACB0 00077890  90 83 00 20 */	stw r4, 0x20(r3)
/* 8007ACB4 00077894  41 82 00 28 */	beq lbl_8007ACDC
/* 8007ACB8 00077898  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8007ACBC 0007789C  80 03 07 E8 */	lwz r0, 0x7e8(r3)
/* 8007ACC0 000778A0  7C 00 20 40 */	cmplw r0, r4
/* 8007ACC4 000778A4  41 81 00 18 */	bgt lbl_8007ACDC
/* 8007ACC8 000778A8  80 03 07 EC */	lwz r0, 0x7ec(r3)
/* 8007ACCC 000778AC  7C 04 00 40 */	cmplw r4, r0
/* 8007ACD0 000778B0  41 81 00 0C */	bgt lbl_8007ACDC
/* 8007ACD4 000778B4  38 00 00 01 */	li r0, 1
/* 8007ACD8 000778B8  48 00 00 08 */	b lbl_8007ACE0
lbl_8007ACDC:
/* 8007ACDC 000778BC  38 00 00 00 */	li r0, 0
lbl_8007ACE0:
/* 8007ACE0 000778C0  2C 00 00 00 */	cmpwi r0, 0
/* 8007ACE4 000778C4  41 82 00 24 */	beq lbl_8007AD08
/* 8007ACE8 000778C8  88 66 20 84 */	lbz r3, 0x2084(r6)
/* 8007ACEC 000778CC  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 8007ACF0 000778D0  40 82 00 18 */	bne lbl_8007AD08
/* 8007ACF4 000778D4  38 00 00 01 */	li r0, 1
/* 8007ACF8 000778D8  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 8007ACFC 000778DC  98 66 20 84 */	stb r3, 0x2084(r6)
/* 8007AD00 000778E0  7C A3 2B 78 */	mr r3, r5
/* 8007AD04 000778E4  4B FB D1 C9 */	bl func_80037ECC
lbl_8007AD08:
/* 8007AD08 000778E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007AD0C 000778EC  38 21 00 08 */	addi r1, r1, 8
/* 8007AD10 000778F0  7C 08 03 A6 */	mtlr r0
/* 8007AD14 000778F4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AD18(void)
{ // clang-format off
    nofralloc
/* 8007AD18 000778F8  7C 08 02 A6 */	mflr r0
/* 8007AD1C 000778FC  90 01 00 04 */	stw r0, 4(r1)
/* 8007AD20 00077900  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8007AD24 00077904  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8007AD28 00077908  7C 9F 23 78 */	mr r31, r4
/* 8007AD2C 0007790C  80 04 00 00 */	lwz r0, 0(r4)
/* 8007AD30 00077910  2C 00 00 02 */	cmpwi r0, 2
/* 8007AD34 00077914  41 82 00 B0 */	beq lbl_8007ADE4
/* 8007AD38 00077918  40 80 00 14 */	bge lbl_8007AD4C
/* 8007AD3C 0007791C  2C 00 00 00 */	cmpwi r0, 0
/* 8007AD40 00077920  41 82 01 2C */	beq lbl_8007AE6C
/* 8007AD44 00077924  40 80 00 14 */	bge lbl_8007AD58
/* 8007AD48 00077928  48 00 01 24 */	b lbl_8007AE6C
lbl_8007AD4C:
/* 8007AD4C 0007792C  2C 00 00 04 */	cmpwi r0, 4
/* 8007AD50 00077930  40 80 01 1C */	bge lbl_8007AE6C
/* 8007AD54 00077934  48 00 00 98 */	b lbl_8007ADEC
lbl_8007AD58:
/* 8007AD58 00077938  88 1F 00 43 */	lbz r0, 0x43(r31)
/* 8007AD5C 0007793C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8007AD60 00077940  41 82 00 38 */	beq lbl_8007AD98
/* 8007AD64 00077944  C0 42 89 0C */	lfs f2, lbl_804D82EC
/* 8007AD68 00077948  C0 23 00 38 */	lfs f1, 0x38(r3)
/* 8007AD6C 0007794C  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8007AD70 00077950  EC 22 08 24 */	fdivs f1, f2, f1
/* 8007AD74 00077954  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007AD78 00077958  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8007AD7C 0007795C  C0 1F 00 14 */	lfs f0, 0x14(r31)
/* 8007AD80 00077960  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007AD84 00077964  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8007AD88 00077968  C0 1F 00 18 */	lfs f0, 0x18(r31)
/* 8007AD8C 0007796C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007AD90 00077970  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8007AD94 00077974  48 00 00 1C */	b lbl_8007ADB0
lbl_8007AD98:
/* 8007AD98 00077978  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 8007AD9C 0007797C  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8007ADA0 00077980  90 61 00 10 */	stw r3, 0x10(r1)
/* 8007ADA4 00077984  90 01 00 14 */	stw r0, 0x14(r1)
/* 8007ADA8 00077988  80 1F 00 18 */	lwz r0, 0x18(r31)
/* 8007ADAC 0007798C  90 01 00 18 */	stw r0, 0x18(r1)
lbl_8007ADB0:
/* 8007ADB0 00077990  80 7F 00 48 */	lwz r3, 0x48(r31)
/* 8007ADB4 00077994  38 81 00 10 */	addi r4, r1, 0x10
/* 8007ADB8 00077998  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8007ADBC 0007799C  4B F9 04 11 */	bl func_8000B1CC
/* 8007ADC0 000779A0  80 9F 00 4C */	lwz r4, 0x4c(r31)
/* 8007ADC4 000779A4  38 00 00 02 */	li r0, 2
/* 8007ADC8 000779A8  80 7F 00 50 */	lwz r3, 0x50(r31)
/* 8007ADCC 000779AC  90 9F 00 58 */	stw r4, 0x58(r31)
/* 8007ADD0 000779B0  90 7F 00 5C */	stw r3, 0x5c(r31)
/* 8007ADD4 000779B4  80 7F 00 54 */	lwz r3, 0x54(r31)
/* 8007ADD8 000779B8  90 7F 00 60 */	stw r3, 0x60(r31)
/* 8007ADDC 000779BC  90 1F 00 00 */	stw r0, 0(r31)
/* 8007ADE0 000779C0  48 00 00 8C */	b lbl_8007AE6C
lbl_8007ADE4:
/* 8007ADE4 000779C4  38 00 00 03 */	li r0, 3
/* 8007ADE8 000779C8  90 1F 00 00 */	stw r0, 0(r31)
lbl_8007ADEC:
/* 8007ADEC 000779CC  80 9F 00 4C */	lwz r4, 0x4c(r31)
/* 8007ADF0 000779D0  80 1F 00 50 */	lwz r0, 0x50(r31)
/* 8007ADF4 000779D4  90 9F 00 58 */	stw r4, 0x58(r31)
/* 8007ADF8 000779D8  90 1F 00 5C */	stw r0, 0x5c(r31)
/* 8007ADFC 000779DC  80 1F 00 54 */	lwz r0, 0x54(r31)
/* 8007AE00 000779E0  90 1F 00 60 */	stw r0, 0x60(r31)
/* 8007AE04 000779E4  88 1F 00 43 */	lbz r0, 0x43(r31)
/* 8007AE08 000779E8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8007AE0C 000779EC  41 82 00 38 */	beq lbl_8007AE44
/* 8007AE10 000779F0  C0 42 89 0C */	lfs f2, lbl_804D82EC
/* 8007AE14 000779F4  C0 23 00 38 */	lfs f1, 0x38(r3)
/* 8007AE18 000779F8  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8007AE1C 000779FC  EC 22 08 24 */	fdivs f1, f2, f1
/* 8007AE20 00077A00  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007AE24 00077A04  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8007AE28 00077A08  C0 1F 00 14 */	lfs f0, 0x14(r31)
/* 8007AE2C 00077A0C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007AE30 00077A10  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8007AE34 00077A14  C0 1F 00 18 */	lfs f0, 0x18(r31)
/* 8007AE38 00077A18  EC 00 00 72 */	fmuls f0, f0, f1
/* 8007AE3C 00077A1C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8007AE40 00077A20  48 00 00 1C */	b lbl_8007AE5C
lbl_8007AE44:
/* 8007AE44 00077A24  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 8007AE48 00077A28  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8007AE4C 00077A2C  90 61 00 10 */	stw r3, 0x10(r1)
/* 8007AE50 00077A30  90 01 00 14 */	stw r0, 0x14(r1)
/* 8007AE54 00077A34  80 1F 00 18 */	lwz r0, 0x18(r31)
/* 8007AE58 00077A38  90 01 00 18 */	stw r0, 0x18(r1)
lbl_8007AE5C:
/* 8007AE5C 00077A3C  80 7F 00 48 */	lwz r3, 0x48(r31)
/* 8007AE60 00077A40  38 81 00 10 */	addi r4, r1, 0x10
/* 8007AE64 00077A44  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8007AE68 00077A48  4B F9 03 65 */	bl func_8000B1CC
lbl_8007AE6C:
/* 8007AE6C 00077A4C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8007AE70 00077A50  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8007AE74 00077A54  38 21 00 28 */	addi r1, r1, 0x28
/* 8007AE78 00077A58  7C 08 03 A6 */	mtlr r0
/* 8007AE7C 00077A5C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AE80(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AE80 00077A60  7C 08 02 A6 */	mflr r0
/* 8007AE84 00077A64  90 01 00 04 */	stw r0, 4(r1)
/* 8007AE88 00077A68  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007AE8C 00077A6C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007AE90 00077A70  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007AE94 00077A74  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8007AE98 00077A78  3B A0 00 00 */	li r29, 0
/* 8007AE9C 00077A7C  1C 1D 01 38 */	mulli r0, r29, 0x138
/* 8007AEA0 00077A80  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007AEA4 00077A84  7F FE 02 14 */	add r31, r30, r0
lbl_8007AEA8:
/* 8007AEA8 00077A88  38 7E 00 00 */	addi r3, r30, 0
/* 8007AEAC 00077A8C  38 9F 09 14 */	addi r4, r31, 0x914
/* 8007AEB0 00077A90  4B FF FE 69 */	bl func_8007AD18
/* 8007AEB4 00077A94  3B BD 00 01 */	addi r29, r29, 1
/* 8007AEB8 00077A98  28 1D 00 04 */	cmplwi r29, 4
/* 8007AEBC 00077A9C  3B FF 01 38 */	addi r31, r31, 0x138
/* 8007AEC0 00077AA0  41 80 FF E8 */	blt lbl_8007AEA8
/* 8007AEC4 00077AA4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007AEC8 00077AA8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007AECC 00077AAC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007AED0 00077AB0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007AED4 00077AB4  38 21 00 20 */	addi r1, r1, 0x20
/* 8007AED8 00077AB8  7C 08 03 A6 */	mtlr r0
/* 8007AEDC 00077ABC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AEE0(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AEE0 00077AC0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007AEE4 00077AC4  38 80 00 00 */	li r4, 0
/* 8007AEE8 00077AC8  88 03 19 C4 */	lbz r0, 0x19c4(r3)
/* 8007AEEC 00077ACC  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8007AEF0 00077AD0  98 03 19 C4 */	stb r0, 0x19c4(r3)
/* 8007AEF4 00077AD4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AEF8(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AEF8 00077AD8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007AEFC 00077ADC  38 80 00 00 */	li r4, 0
/* 8007AF00 00077AE0  88 03 19 E8 */	lbz r0, 0x19e8(r3)
/* 8007AF04 00077AE4  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8007AF08 00077AE8  98 03 19 E8 */	stb r0, 0x19e8(r3)
/* 8007AF0C 00077AEC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AF10(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AF10 00077AF0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007AF14 00077AF4  38 80 00 00 */	li r4, 0
/* 8007AF18 00077AF8  88 03 1A 0C */	lbz r0, 0x1a0c(r3)
/* 8007AF1C 00077AFC  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8007AF20 00077B00  98 03 1A 0C */	stb r0, 0x1a0c(r3)
/* 8007AF24 00077B04  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AF28(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AF28 00077B08  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8007AF2C 00077B0C  38 C0 00 00 */	li r6, 0
/* 8007AF30 00077B10  38 60 00 00 */	li r3, 0
/* 8007AF34 00077B14  38 85 00 00 */	addi r4, r5, 0
/* 8007AF38 00077B18  48 00 00 18 */	b lbl_8007AF50
lbl_8007AF3C:
/* 8007AF3C 00077B1C  88 04 11 C4 */	lbz r0, 0x11c4(r4)
/* 8007AF40 00077B20  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8007AF44 00077B24  38 C6 00 01 */	addi r6, r6, 1
/* 8007AF48 00077B28  98 04 11 C4 */	stb r0, 0x11c4(r4)
/* 8007AF4C 00077B2C  38 84 00 4C */	addi r4, r4, 0x4c
lbl_8007AF50:
/* 8007AF50 00077B30  88 05 11 9E */	lbz r0, 0x119e(r5)
/* 8007AF54 00077B34  7C 06 00 40 */	cmplw r6, r0
/* 8007AF58 00077B38  41 80 FF E4 */	blt lbl_8007AF3C
/* 8007AF5C 00077B3C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AF60(void)
{ // clang-format off
    nofralloc
/* 8007AF60 00077B40  7C 08 02 A6 */	mflr r0
/* 8007AF64 00077B44  90 01 00 04 */	stw r0, 4(r1)
/* 8007AF68 00077B48  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007AF6C 00077B4C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007AF70 00077B50  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007AF74 00077B54  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8007AF78 00077B58  3B A0 00 00 */	li r29, 0
/* 8007AF7C 00077B5C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007AF80 00077B60  3B FE 00 00 */	addi r31, r30, 0
/* 8007AF84 00077B64  48 00 00 1C */	b lbl_8007AFA0
lbl_8007AF88:
/* 8007AF88 00077B68  38 9F 16 70 */	addi r4, r31, 0x1670
/* 8007AF8C 00077B6C  80 7F 16 80 */	lwz r3, 0x1680(r31)
/* 8007AF90 00077B70  38 A4 00 18 */	addi r5, r4, 0x18
/* 8007AF94 00077B74  4B F9 02 39 */	bl func_8000B1CC
/* 8007AF98 00077B78  3B FF 00 28 */	addi r31, r31, 0x28
/* 8007AF9C 00077B7C  3B BD 00 01 */	addi r29, r29, 1
lbl_8007AFA0:
/* 8007AFA0 00077B80  88 1E 16 6C */	lbz r0, 0x166c(r30)
/* 8007AFA4 00077B84  7C 1D 00 40 */	cmplw r29, r0
/* 8007AFA8 00077B88  41 80 FF E0 */	blt lbl_8007AF88
/* 8007AFAC 00077B8C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007AFB0 00077B90  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007AFB4 00077B94  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007AFB8 00077B98  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007AFBC 00077B9C  38 21 00 20 */	addi r1, r1, 0x20
/* 8007AFC0 00077BA0  7C 08 03 A6 */	mtlr r0
/* 8007AFC4 00077BA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AFC8(void)
{ // clang-format off
    nofralloc
/* 8007AFC8 00077BA8  7C 08 02 A6 */	mflr r0
/* 8007AFCC 00077BAC  1C 84 01 38 */	mulli r4, r4, 0x138
/* 8007AFD0 00077BB0  90 01 00 04 */	stw r0, 4(r1)
/* 8007AFD4 00077BB4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007AFD8 00077BB8  80 03 00 2C */	lwz r0, 0x2c(r3)
/* 8007AFDC 00077BBC  38 64 09 14 */	addi r3, r4, 0x914
/* 8007AFE0 00077BC0  7C 60 1A 14 */	add r3, r0, r3
/* 8007AFE4 00077BC4  4B F8 D4 45 */	bl lbColl_80008428
/* 8007AFE8 00077BC8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007AFEC 00077BCC  38 21 00 08 */	addi r1, r1, 8
/* 8007AFF0 00077BD0  7C 08 03 A6 */	mtlr r0
/* 8007AFF4 00077BD4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007AFF8(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8007AFF8 00077BD8  7C 08 02 A6 */	mflr r0
/* 8007AFFC 00077BDC  90 01 00 04 */	stw r0, 4(r1)
/* 8007B000 00077BE0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007B004 00077BE4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007B008 00077BE8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007B00C 00077BEC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8007B010 00077BF0  3B A0 00 00 */	li r29, 0
/* 8007B014 00077BF4  1C 1D 01 38 */	mulli r0, r29, 0x138
/* 8007B018 00077BF8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007B01C 00077BFC  7F FE 02 14 */	add r31, r30, r0
lbl_8007B020:
/* 8007B020 00077C00  38 7F 09 14 */	addi r3, r31, 0x914
/* 8007B024 00077C04  4B F8 D4 05 */	bl lbColl_80008428
/* 8007B028 00077C08  3B BD 00 01 */	addi r29, r29, 1
/* 8007B02C 00077C0C  28 1D 00 04 */	cmplwi r29, 4
/* 8007B030 00077C10  3B FF 01 38 */	addi r31, r31, 0x138
/* 8007B034 00077C14  41 80 FF EC */	blt lbl_8007B020
/* 8007B038 00077C18  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 8007B03C 00077C1C  38 60 00 00 */	li r3, 0
/* 8007B040 00077C20  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8007B044 00077C24  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 8007B048 00077C28  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007B04C 00077C2C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007B050 00077C30  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007B054 00077C34  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8007B058 00077C38  38 21 00 20 */	addi r1, r1, 0x20
/* 8007B05C 00077C3C  7C 08 03 A6 */	mtlr r0
/* 8007B060 00077C40  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007B064(void)
{ // clang-format off
    nofralloc
/* 8007B064 00077C44  7C 08 02 A6 */	mflr r0
/* 8007B068 00077C48  1C 84 01 38 */	mulli r4, r4, 0x138
/* 8007B06C 00077C4C  90 01 00 04 */	stw r0, 4(r1)
/* 8007B070 00077C50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007B074 00077C54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007B078 00077C58  3B E4 09 14 */	addi r31, r4, 0x914
/* 8007B07C 00077C5C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007B080 00077C60  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007B084 00077C64  7F FE FA 14 */	add r31, r30, r31
/* 8007B088 00077C68  38 7F 00 00 */	addi r3, r31, 0
/* 8007B08C 00077C6C  4B F8 D3 A9 */	bl lbColl_80008434
/* 8007B090 00077C70  7F E3 FB 78 */	mr r3, r31
/* 8007B094 00077C74  4B F8 D3 AD */	bl lbColl_80008440
/* 8007B098 00077C78  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 8007B09C 00077C7C  38 60 00 01 */	li r3, 1
/* 8007B0A0 00077C80  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8007B0A4 00077C84  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 8007B0A8 00077C88  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007B0AC 00077C8C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007B0B0 00077C90  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007B0B4 00077C94  38 21 00 20 */	addi r1, r1, 0x20
/* 8007B0B8 00077C98  7C 08 03 A6 */	mtlr r0
/* 8007B0BC 00077C9C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007B0C0(HSD_GObj*, int)
{ // clang-format off
    nofralloc
/* 8007B0C0 00077CA0  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8007B0C4 00077CA4  38 E0 00 00 */	li r7, 0
/* 8007B0C8 00077CA8  38 60 00 00 */	li r3, 0
/* 8007B0CC 00077CAC  38 A6 00 00 */	addi r5, r6, 0
/* 8007B0D0 00077CB0  48 00 00 1C */	b lbl_8007B0EC
lbl_8007B0D4:
/* 8007B0D4 00077CB4  90 85 11 A0 */	stw r4, 0x11a0(r5)
/* 8007B0D8 00077CB8  38 E7 00 01 */	addi r7, r7, 1
/* 8007B0DC 00077CBC  88 05 11 C4 */	lbz r0, 0x11c4(r5)
/* 8007B0E0 00077CC0  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8007B0E4 00077CC4  98 05 11 C4 */	stb r0, 0x11c4(r5)
/* 8007B0E8 00077CC8  38 A5 00 4C */	addi r5, r5, 0x4c
lbl_8007B0EC:
/* 8007B0EC 00077CCC  88 06 11 9E */	lbz r0, 0x119e(r6)
/* 8007B0F0 00077CD0  7C 07 00 40 */	cmplw r7, r0
/* 8007B0F4 00077CD4  41 80 FF E0 */	blt lbl_8007B0D4
/* 8007B0F8 00077CD8  2C 04 00 00 */	cmpwi r4, 0
/* 8007B0FC 00077CDC  40 82 00 18 */	bne lbl_8007B114
/* 8007B100 00077CE0  88 06 22 1A */	lbz r0, 0x221a(r6)
/* 8007B104 00077CE4  38 60 00 00 */	li r3, 0
/* 8007B108 00077CE8  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8007B10C 00077CEC  98 06 22 1A */	stb r0, 0x221a(r6)
/* 8007B110 00077CF0  4E 80 00 20 */	blr
lbl_8007B114:
/* 8007B114 00077CF4  88 06 22 1A */	lbz r0, 0x221a(r6)
/* 8007B118 00077CF8  38 60 00 01 */	li r3, 1
/* 8007B11C 00077CFC  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8007B120 00077D00  98 06 22 1A */	stb r0, 0x221a(r6)
/* 8007B124 00077D04  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern char* const lbl_803C0CF0;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007B128(void)
{ // clang-format off
    nofralloc
/* 8007B128 00077D08  7C 08 02 A6 */	mflr r0
/* 8007B12C 00077D0C  90 01 00 04 */	stw r0, 4(r1)
/* 8007B130 00077D10  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007B134 00077D14  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8007B138 00077D18  88 06 11 9E */	lbz r0, 0x119e(r6)
/* 8007B13C 00077D1C  38 66 00 00 */	addi r3, r6, 0
/* 8007B140 00077D20  2C 00 00 00 */	cmpwi r0, 0
/* 8007B144 00077D24  7C 09 03 A6 */	mtctr r0
/* 8007B148 00077D28  40 81 00 3C */	ble lbl_8007B184
lbl_8007B14C:
/* 8007B14C 00077D2C  80 03 11 E0 */	lwz r0, 0x11e0(r3)
/* 8007B150 00077D30  38 E3 11 A0 */	addi r7, r3, 0x11a0
/* 8007B154 00077D34  7C 00 20 00 */	cmpw r0, r4
/* 8007B158 00077D38  40 82 00 24 */	bne lbl_8007B17C
/* 8007B15C 00077D3C  2C 05 00 00 */	cmpwi r5, 0
/* 8007B160 00077D40  90 A7 00 00 */	stw r5, 0(r7)
/* 8007B164 00077D44  41 82 00 44 */	beq lbl_8007B1A8
/* 8007B168 00077D48  88 06 22 1A */	lbz r0, 0x221a(r6)
/* 8007B16C 00077D4C  38 60 00 01 */	li r3, 1
/* 8007B170 00077D50  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8007B174 00077D54  98 06 22 1A */	stb r0, 0x221a(r6)
/* 8007B178 00077D58  48 00 00 30 */	b lbl_8007B1A8
lbl_8007B17C:
/* 8007B17C 00077D5C  38 63 00 4C */	addi r3, r3, 0x4c
/* 8007B180 00077D60  42 00 FF CC */	bdnz lbl_8007B14C
lbl_8007B184:
/* 8007B184 00077D64  3C 60 80 3C */	lis r3, lbl_803C0CF0@ha
/* 8007B188 00077D68  4C C6 31 82 */	crclr 6
/* 8007B18C 00077D6C  38 63 0C F0 */	addi r3, r3, lbl_803C0CF0@l
/* 8007B190 00077D70  48 2C A5 19 */	bl OSReport
/* 8007B194 00077D74  3C 60 80 3C */	lis r3, lbl_803C0C74@ha
/* 8007B198 00077D78  38 63 0C 74 */	addi r3, r3, lbl_803C0C74@l
/* 8007B19C 00077D7C  38 80 08 88 */	li r4, 0x888
/* 8007B1A0 00077D80  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 8007B1A4 00077D84  48 30 D0 7D */	bl __assert
lbl_8007B1A8:
/* 8007B1A8 00077D88  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007B1AC 00077D8C  38 21 00 08 */	addi r1, r1, 8
/* 8007B1B0 00077D90  7C 08 03 A6 */	mtlr r0
/* 8007B1B4 00077D94  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007B1B8(HSD_GObj*, f32*, HSD_GObjEvent)
{ // clang-format off
    nofralloc
/* 8007B1B8 00077D98  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 8007B1BC 00077D9C  38 C0 00 01 */	li r6, 1
/* 8007B1C0 00077DA0  38 60 00 00 */	li r3, 0
/* 8007B1C4 00077DA4  88 07 22 1B */	lbz r0, 0x221b(r7)
/* 8007B1C8 00077DA8  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 8007B1CC 00077DAC  98 07 22 1B */	stb r0, 0x221b(r7)
/* 8007B1D0 00077DB0  88 07 22 1B */	lbz r0, 0x221b(r7)
/* 8007B1D4 00077DB4  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8007B1D8 00077DB8  98 07 22 1B */	stb r0, 0x221b(r7)
/* 8007B1DC 00077DBC  88 07 22 1B */	lbz r0, 0x221b(r7)
/* 8007B1E0 00077DC0  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 8007B1E4 00077DC4  98 07 22 1B */	stb r0, 0x221b(r7)
/* 8007B1E8 00077DC8  88 07 22 1B */	lbz r0, 0x221b(r7)
/* 8007B1EC 00077DCC  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8007B1F0 00077DD0  98 07 22 1B */	stb r0, 0x221b(r7)
/* 8007B1F4 00077DD4  88 07 22 1B */	lbz r0, 0x221b(r7)
/* 8007B1F8 00077DD8  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8007B1FC 00077DDC  98 07 22 1B */	stb r0, 0x221b(r7)
/* 8007B200 00077DE0  90 A7 21 C4 */	stw r5, 0x21c4(r7)
/* 8007B204 00077DE4  80 04 00 00 */	lwz r0, 0(r4)
/* 8007B208 00077DE8  80 67 05 E8 */	lwz r3, 0x5e8(r7)
/* 8007B20C 00077DEC  54 00 20 36 */	slwi r0, r0, 4
/* 8007B210 00077DF0  7C 03 00 2E */	lwzx r0, r3, r0
/* 8007B214 00077DF4  90 07 19 C0 */	stw r0, 0x19c0(r7)
/* 8007B218 00077DF8  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8007B21C 00077DFC  D0 07 19 E0 */	stfs f0, 0x19e0(r7)
/* 8007B220 00077E00  80 64 00 04 */	lwz r3, 4(r4)
/* 8007B224 00077E04  80 04 00 08 */	lwz r0, 8(r4)
/* 8007B228 00077E08  90 67 19 D4 */	stw r3, 0x19d4(r7)
/* 8007B22C 00077E0C  90 07 19 D8 */	stw r0, 0x19d8(r7)
/* 8007B230 00077E10  80 04 00 0C */	lwz r0, 0xc(r4)
/* 8007B234 00077E14  90 07 19 DC */	stw r0, 0x19dc(r7)
/* 8007B238 00077E18  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftColl_CreateReflectHit(HSD_GObj*, ReflectDesc*, HSD_GObjEvent)
{ // clang-format off
    nofralloc
/* 8007B23C 00077E1C  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 8007B240 00077E20  38 C0 00 01 */	li r6, 1
/* 8007B244 00077E24  38 60 00 00 */	li r3, 0
/* 8007B248 00077E28  88 07 22 18 */	lbz r0, 0x2218(r7)
/* 8007B24C 00077E2C  50 C0 26 F6 */	rlwimi r0, r6, 4, 0x1b, 0x1b
/* 8007B250 00077E30  98 07 22 18 */	stb r0, 0x2218(r7)
/* 8007B254 00077E34  88 07 22 18 */	lbz r0, 0x2218(r7)
/* 8007B258 00077E38  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8007B25C 00077E3C  98 07 22 18 */	stb r0, 0x2218(r7)
/* 8007B260 00077E40  90 A7 21 C8 */	stw r5, 0x21c8(r7)
/* 8007B264 00077E44  80 04 00 04 */	lwz r0, 4(r4)
/* 8007B268 00077E48  90 07 1A 30 */	stw r0, 0x1a30(r7)
/* 8007B26C 00077E4C  C0 04 00 18 */	lfs f0, 0x18(r4)
/* 8007B270 00077E50  D0 07 1A 34 */	stfs f0, 0x1a34(r7)
/* 8007B274 00077E54  C0 04 00 1C */	lfs f0, 0x1c(r4)
/* 8007B278 00077E58  D0 07 1A 38 */	stfs f0, 0x1a38(r7)
/* 8007B27C 00077E5C  88 64 00 20 */	lbz r3, 0x20(r4)
/* 8007B280 00077E60  88 07 22 18 */	lbz r0, 0x2218(r7)
/* 8007B284 00077E64  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8007B288 00077E68  98 07 22 18 */	stb r0, 0x2218(r7)
/* 8007B28C 00077E6C  80 04 00 00 */	lwz r0, 0(r4)
/* 8007B290 00077E70  80 67 05 E8 */	lwz r3, 0x5e8(r7)
/* 8007B294 00077E74  54 00 20 36 */	slwi r0, r0, 4
/* 8007B298 00077E78  7C 03 00 2E */	lwzx r0, r3, r0
/* 8007B29C 00077E7C  90 07 19 E4 */	stw r0, 0x19e4(r7)
/* 8007B2A0 00077E80  C0 04 00 14 */	lfs f0, 0x14(r4)
/* 8007B2A4 00077E84  D0 07 1A 04 */	stfs f0, 0x1a04(r7)
/* 8007B2A8 00077E88  80 64 00 08 */	lwz r3, 8(r4)
/* 8007B2AC 00077E8C  80 04 00 0C */	lwz r0, 0xc(r4)
/* 8007B2B0 00077E90  90 67 19 F8 */	stw r3, 0x19f8(r7)
/* 8007B2B4 00077E94  90 07 19 FC */	stw r0, 0x19fc(r7)
/* 8007B2B8 00077E98  80 04 00 10 */	lwz r0, 0x10(r4)
/* 8007B2BC 00077E9C  90 07 1A 00 */	stw r0, 0x1a00(r7)
/* 8007B2C0 00077EA0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftColl_CreateAbsorbHit(HSD_GObj*, AbsorbDesc*)
{ // clang-format off
    nofralloc
/* 8007B2C4 00077EA4  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8007B2C8 00077EA8  38 A0 00 01 */	li r5, 1
/* 8007B2CC 00077EAC  38 60 00 00 */	li r3, 0
/* 8007B2D0 00077EB0  88 06 22 18 */	lbz r0, 0x2218(r6)
/* 8007B2D4 00077EB4  50 A0 0F BC */	rlwimi r0, r5, 1, 0x1e, 0x1e
/* 8007B2D8 00077EB8  98 06 22 18 */	stb r0, 0x2218(r6)
/* 8007B2DC 00077EBC  88 06 22 18 */	lbz r0, 0x2218(r6)
/* 8007B2E0 00077EC0  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8007B2E4 00077EC4  98 06 22 18 */	stb r0, 0x2218(r6)
/* 8007B2E8 00077EC8  80 04 00 00 */	lwz r0, 0(r4)
/* 8007B2EC 00077ECC  80 66 05 E8 */	lwz r3, 0x5e8(r6)
/* 8007B2F0 00077ED0  54 00 20 36 */	slwi r0, r0, 4
/* 8007B2F4 00077ED4  7C 03 00 2E */	lwzx r0, r3, r0
/* 8007B2F8 00077ED8  90 06 1A 08 */	stw r0, 0x1a08(r6)
/* 8007B2FC 00077EDC  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8007B300 00077EE0  D0 06 1A 28 */	stfs f0, 0x1a28(r6)
/* 8007B304 00077EE4  80 64 00 04 */	lwz r3, 4(r4)
/* 8007B308 00077EE8  80 04 00 08 */	lwz r0, 8(r4)
/* 8007B30C 00077EEC  90 66 1A 1C */	stw r3, 0x1a1c(r6)
/* 8007B310 00077EF0  90 06 1A 20 */	stw r0, 0x1a20(r6)
/* 8007B314 00077EF4  80 04 00 0C */	lwz r0, 0xc(r4)
/* 8007B318 00077EF8  90 06 1A 24 */	stw r0, 0x1a24(r6)
/* 8007B31C 00077EFC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
