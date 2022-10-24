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

extern void func_80008441(Hitbox*);
extern unk_t func_800084FC();
extern void func_80008440(Hitbox*);

#pragma push
asm unk_t func_800768A0()
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

extern f32 lbl_804D82E8;
extern f32 lbl_804D82EC;
extern f64 lbl_804D82F0;
extern f64 lbl_804D82F8;
extern unk_t func_800784B4();

#pragma push
asm unk_t func_8007699C()
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
/* 800769C4 000735A4  C0 42 89 08 */	lfs f2, lbl_804D82E8(r2)
/* 800769C8 000735A8  EC 01 00 2A */	fadds f0, f1, f0
/* 800769CC 000735AC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
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
/* 80076A30 00073610  C0 02 89 00 */	lfs f0, lbl_804D82E0(r2)
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
/* 80076AF0 000736D0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80076AF4 000736D4  90 01 00 44 */	stw r0, 0x44(r1)
/* 80076AF8 000736D8  3C 00 43 30 */	lis r0, 0x4330
/* 80076AFC 000736DC  C8 62 89 18 */	lfd f3, lbl_804D82F8(r2)
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
/* 80076B2C 0007370C  C0 02 89 0C */	lfs f0, lbl_804D82EC(r2)
/* 80076B30 00073710  48 00 00 08 */	b lbl_80076B38
lbl_80076B34:
/* 80076B34 00073714  C0 02 89 10 */	lfs f0, lbl_804D82F0(r2)
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
/* 80076B5C 0007373C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80076B60 00073740  FC 00 00 1E */	fctiwz f0, f0
/* 80076B64 00073744  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 80076B68 00073748  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076B6C 0007374C  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80076B70 00073750  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80076B74 00073754  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80076B78 00073758  7C 64 18 50 */	subf r3, r4, r3
/* 80076B7C 0007375C  7C 03 00 00 */	cmpw r3, r0
/* 80076B80 00073760  40 80 01 24 */	bge lbl_80076CA4
/* 80076B84 00073764  C0 02 89 00 */	lfs f0, lbl_804D82E0(r2)
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
/* 80076C2C 0007380C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80076C30 00073810  90 01 00 44 */	stw r0, 0x44(r1)
/* 80076C34 00073814  3C 00 43 30 */	lis r0, 0x4330
/* 80076C38 00073818  C8 62 89 18 */	lfd f3, lbl_804D82F8(r2)
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
/* 80076C68 00073848  C0 02 89 0C */	lfs f0, lbl_804D82EC(r2)
/* 80076C6C 0007384C  48 00 00 08 */	b lbl_80076C74
lbl_80076C70:
/* 80076C70 00073850  C0 02 89 10 */	lfs f0, lbl_804D82F0(r2)
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

extern unk_t func_8003E150();
extern unk_t func_80094138();

#pragma push
asm unk_t func_80076CBC()
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
/* 80076D20 00073900  C0 02 89 00 */	lfs f0, lbl_804D82E0(r2)
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
/* 80076D78 00073958  C8 22 89 18 */	lfd f1, lbl_804D82F8(r2)
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
/* 80076DAC 0007398C  C0 02 89 0C */	lfs f0, lbl_804D82EC(r2)
/* 80076DB0 00073990  48 00 00 08 */	b lbl_80076DB8
lbl_80076DB4:
/* 80076DB4 00073994  C0 02 89 10 */	lfs f0, lbl_804D82F0(r2)
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
/* 80076DDC 000739BC  C0 02 89 10 */	lfs f0, lbl_804D82F0(r2)
/* 80076DE0 000739C0  48 00 00 08 */	b lbl_80076DE8
lbl_80076DE4:
/* 80076DE4 000739C4  C0 02 89 0C */	lfs f0, lbl_804D82EC(r2)
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
/* 80076EB0 00073A90  C0 02 89 00 */	lfs f0, lbl_804D82E0(r2)
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



