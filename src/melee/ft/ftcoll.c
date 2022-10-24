#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>
#include <melee/it/item.h>
 
// Combo Count Logic
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID)
{
    HSD_GObj* temp_GObj;
    Fighter* fp;

    if (attacker != victim)
    {
        fp = getFighter(attacker);
        temp_GObj = fp->x2094;
        if (temp_GObj == NULL)
        {
            fp->x208C = attackID;
            fp->x2090 = 1U;
            fp->x2094 = victim;
            return;
        }
        if (temp_GObj == victim)
        {
            if ((attackID != 1) && ((s32)fp->x208C == attackID))
            {
                fp->x2090 = (u16)(fp->x2090 + 1);
                if (fp->x2090 >= p_ftCommonData->x4C4)
                {
                    fp->x2092 = p_ftCommonData->x4D8;
                }
            }
            else
            {
                fp->x2090 = 0U;
                fp->x208C = attackID;
            }
        }
    }
}

// Combo Count Logic + Get Attack ID
void func_80076444(HSD_GObj* attacker, HSD_GObj* victim)
{
    Fighter* fp = getFighter(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

extern BOOL func_80086960(HSD_GObj*);

// Combo Count Logic w/ Item Owner
void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim)
{
    HSD_GObj* itemOwner = func_8026BC78(attackItem);
    s32 attackID = func_8026BC84(attackItem);
 
    // Check if item's owner is a fp
    if (func_80086960(itemOwner) != FALSE)
    {
        func_800763C0(itemOwner, victim, attackID);
    }
}

// Check to end combo for victim
void func_800764DC(HSD_GObj* fighter_gobj)
{
    u16 hitstunTimer;
    HSD_GObj* temp_gobj;
    Fighter* temp_fp;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    hitstunTimer = fp->x2098;
    if (hitstunTimer != 0)
    {
        fp->x2098 = (u16)(hitstunTimer - 1);
    }
    temp_gobj = fp->x2094;
    if (temp_gobj != NULL)
    {
        temp_fp = getFighter(temp_gobj);
        if ((temp_fp->x221C_flag.bits.b6 == 0) && ((u16)temp_fp->x2098 == 0))
        {
            fp->x2094 = NULL;
        }
    }
}

inline void comboCount_Push(Fighter* fp)
{

    Vec3* pos = &fp->x6F0_collData.x14C_ground.normal;
    f32 temp_f2;
    f32 var_f2;
    if ((s32)fp->x2090 < (s32)p_ftCommonData->x4C8)
    {
        var_f2 = p_ftCommonData->x4D0;
    }
    else
    {
        var_f2 = p_ftCommonData->x4D4;
    }
    temp_f2 = fp->x2C_facing_direction * var_f2;
    fp->xB0_pos.x = -((pos->y * temp_f2) - fp->xB0_pos.x);
    fp->xB0_pos.y = -((-pos->x * temp_f2) - fp->xB0_pos.y);
}

// Combo count something + adjust TopN
void func_80076528(HSD_GObj* fighter_gobj)
{
    u16 temp_r3;
    Fighter* fp;

    fp = fighter_gobj->user_data;
    temp_r3 = fp->x2092;
    if (temp_r3 != 0)
    {
        fp->x2092 = (u16)(temp_r3 - 1);
        if ((fp->x1A58_interactedFighter == NULL) && (fp->xE0_ground_or_air == GA_Ground))
        {
            comboCount_Push(fp);
        }
    }
}

// Clear victim pointer from attacker upon freeing memory?
void func_800765AC(HSD_GObj* victim)
{
    Fighter* fp;
    HSD_GObj* gobj;
 
    // Get fp GObj from global list of entities (?)
    gobj = lbl_804D782C->x20_fighters;
    while (gobj != NULL)
    {
        fp = getFighter(gobj); 
        if (victim == fp->x2094)
        {
            fp->x2094 = NULL;
        }
        // Repeat until there are no more fp GObjs left
        gobj = gobj->next;
    }
}

extern s32 lbl_804D6558;
extern s32 lbl_804D655C;

// Reset hitbox and phantom collision count?
void func_800765E0(void)
{
    lbl_804D6558 = 0;
    lbl_804D655C = 0;
}

// Unk knockback related ?
f32 func_800765F0(Fighter* fp, HSD_GObj* victim, f32 unk_floatvar)
{
    HSD_GObj* currentVictim;

    currentVictim = fp->x1A58_interactedFighter;
    if ((currentVictim != NULL) && (fp->x221B_flag.bits.b5 == 0) && (currentVictim != victim))
    {
        unk_floatvar *= p_ftCommonData->x128;
    }
    if (fp->x10_action_state_index == ASID_DAMAGEICE)
    {
        unk_floatvar *= p_ftCommonData->x714;
    }
    return unk_floatvar * fp->dmg.x182c_behavior;
}

extern s32 lbl_804D82E0;
extern s32 lbl_804D82E4;
extern char* lbl_803C0C58;
extern char* lbl_803C0C74;
extern char* lbl_804D3A68;

#pragma push
asm unk_t func_80076640()
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
/* 80076660 00073240  C0 02 89 00 */	lfs f0, lbl_804D82E0(r2)
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

extern unk_t lbl_80459278;
extern char* lbl_803C0C80[];

#pragma push
asm unk_t func_80076764()
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

extern unk_t lbl_804D6560;
extern unk_t func_80008688();

#pragma push
asm unk_t func_80076808()
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
