#include <melee/ft/chara/ftYoshi/ftyoshi2.h>

#include <melee/ef/efasync.h>
#include <melee/ft/chara/ftYoshi/ftyoshi1.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/itkind.h>

char lbl_803CEA98[] = "PlYs.dat";
char lbl_803CEAA4[] = "ftDataYoshi";
char lbl_803CEAB0[] = "PlYsNr.dat";
char lbl_803CEABC[] = "PlyYoshi5K_Share_joint";
char lbl_803CEAD4[] = "PlyYoshi5K_Share_matanim_joint";
char lbl_803CEAF4[] = "PlYsRe.dat";
char lbl_803CEB00[] = "PlyYoshi5KRe_Share_joint";
char lbl_803CEB1C[] = "PlyYoshi5KRe_Share_matanim_joint";
char lbl_803CEB40[] = "PlYsBu.dat";
char lbl_803CEB4C[] = "PlyYoshi5KBu_Share_joint";
char lbl_803CEB68[] = "PlyYoshi5KBu_Share_matanim_joint";
char lbl_803CEB8C[] = "PlYsYe.dat";
char lbl_803CEB98[] = "PlyYoshi5KYe_Share_joint";
char lbl_803CEBB4[] = "PlyYoshi5KYe_Share_matanim_joint";
char lbl_803CEBD8[] = "PlYsPi.dat";
char lbl_803CEBE4[] = "PlyYoshi5KPi_Share_joint";
char lbl_803CEC00[] = "PlyYoshi5KPi_Share_matanim_joint";
char lbl_803CEC24[] = "PlYsAq.dat";
char lbl_803CEC30[] = "PlyYoshi5KAq_Share_joint";
char lbl_803CEC4C[] = "PlyYoshi5KAq_Share_matanim_joint";
char lbl_803CEC70[] = "PlYsAJ.dat";

Fighter_DemoStrings lbl_803CECEC = {
    "ftDemoResultMotionFileYoshi",
    "ftDemoIntroMotionFileYoshi",
    "ftDemoEndingMotionFileYoshi",
    "ftDemoViWaitMotionFileYoshi",
};

Fighter_CostumeStrings lbl_803CECFC[] = {
    { lbl_803CEAB0, lbl_803CEABC, lbl_803CEAD4 },
    { lbl_803CEAF4, lbl_803CEB00, lbl_803CEB1C },
    { lbl_803CEB40, lbl_803CEB4C, lbl_803CEB68 },
    { lbl_803CEB8C, lbl_803CEB98, lbl_803CEBB4 },
    { lbl_803CEBD8, lbl_803CEBE4, lbl_803CEC00 },
    { lbl_803CEC24, lbl_803CEC30, lbl_803CEC4C },
};

/* static */ extern f32 const lbl_804D9A28;

static inline void spawnEffect(HSD_GObj* fighter_gobj)
{
    HSD_JObj* jobj;
    s32 bone_idx;
    Fighter* fp2;
    s32* x1CC;
    Fighter* fp;
    fp = GET_FIGHTER(fighter_gobj);
    func_80074B0C(fighter_gobj, 0, 0);
    func_8007B0C0(fighter_gobj, 0);

    x1CC = &fp->x110_attr.x1CC;
    bone_idx = func_8007500C(fp, 4);
    fp2 = GET_FIGHTER(fighter_gobj);
    jobj = fp->x5E8_fighterBones[bone_idx].x0_jobj;

    efAsync_Spawn(fighter_gobj, &fp2->x60C, 4U, 0x4CFU, jobj, x1CC);
}

void lbl_8012C030(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    u32 unused[2];

    fp = GET_FIGHTER(fighter_gobj);
    fp->x2340_f32 += lbl_804D9A28;
    func_80092BCC(fighter_gobj);
    if (func_800925A4(fighter_gobj)) {
        spawnEffect(fighter_gobj);
    } else if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800928CC(fighter_gobj);
    } else {
        func_8012B8A4(fighter_gobj);
    }
}

void lbl_8012C114(HSD_GObj* fighter_gobj)
{
    if (!func_80093694() && !func_8009515C(fighter_gobj) &&
        !func_80099794(fighter_gobj) && !func_8009917C(fighter_gobj) &&
        !func_800D8990(fighter_gobj) && !func_8009A080(fighter_gobj))
    {
        return;
    }
}

void lbl_8012C194(HSD_GObj* arg0)
{
    func_80092870(arg0);
}

void lbl_8012C1B4(HSD_GObj* arg0)
{
    func_800928AC(arg0);
}

extern f32 const lbl_804D9A2C;
extern u8 lbl_803B75C0[];

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8012C1D4(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012C1D4 00128DB4  7C 08 02 A6 */	mflr r0
/* 8012C1D8 00128DB8  38 80 01 56 */	li r4, 0x156
/* 8012C1DC 00128DBC  90 01 00 04 */	stw r0, 4(r1)
/* 8012C1E0 00128DC0  38 A0 00 00 */	li r5, 0
/* 8012C1E4 00128DC4  38 C0 00 00 */	li r6, 0
/* 8012C1E8 00128DC8  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 8012C1EC 00128DCC  93 E1 00 64 */	stw r31, 0x64(r1)
/* 8012C1F0 00128DD0  93 C1 00 60 */	stw r30, 0x60(r1)
/* 8012C1F4 00128DD4  7C 7E 1B 78 */	mr r30, r3
/* 8012C1F8 00128DD8  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 8012C1FC 00128DDC  C0 22 A0 4C */	lfs f1, lbl_804D9A2C(r2)
/* 8012C200 00128DE0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012C204 00128DE4  FC 60 08 90 */	fmr f3, f1
/* 8012C208 00128DE8  C0 42 A0 48 */	lfs f2, lbl_804D9A28(r2)
/* 8012C20C 00128DEC  4B F3 D1 A1 */	bl Fighter_ActionStateChange_800693AC
/* 8012C210 00128DF0  80 BF 01 08 */	lwz r5, 0x108(r31)
/* 8012C214 00128DF4  38 7F 00 00 */	addi r3, r31, 0
/* 8012C218 00128DF8  38 80 00 01 */	li r4, 1
/* 8012C21C 00128DFC  80 A5 00 08 */	lwz r5, 8(r5)
/* 8012C220 00128E00  4B F4 38 39 */	bl func_8006FA58
/* 8012C224 00128E04  38 7E 00 00 */	addi r3, r30, 0
/* 8012C228 00128E08  38 80 00 00 */	li r4, 0
/* 8012C22C 00128E0C  38 A0 00 01 */	li r5, 1
/* 8012C230 00128E10  4B F4 88 DD */	bl func_80074B0C
/* 8012C234 00128E14  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 8012C238 00128E18  38 7E 00 00 */	addi r3, r30, 0
/* 8012C23C 00128E1C  38 80 00 02 */	li r4, 2
/* 8012C240 00128E20  4B F4 EE 81 */	bl func_8007B0C0
/* 8012C244 00128E24  80 9D 01 0C */	lwz r4, 0x10c(r29)
/* 8012C248 00128E28  3C 60 80 3B */	lis r3, lbl_803B75C0@ha
/* 8012C24C 00128E2C  38 00 00 01 */	li r0, 1
/* 8012C250 00128E30  C0 02 A0 48 */	lfs f0, lbl_804D9A28(r2)
/* 8012C254 00128E34  80 84 00 08 */	lwz r4, 8(r4)
/* 8012C258 00128E38  38 E3 75 C0 */	addi r7, r3, lbl_803B75C0@l
/* 8012C25C 00128E3C  88 A4 00 11 */	lbz r5, 0x11(r4)
/* 8012C260 00128E40  38 7D 00 00 */	addi r3, r29, 0
/* 8012C264 00128E44  38 9D 11 A0 */	addi r4, r29, 0x11a0
/* 8012C268 00128E48  90 A1 00 24 */	stw r5, 0x24(r1)
/* 8012C26C 00128E4C  38 A1 00 24 */	addi r5, r1, 0x24
/* 8012C270 00128E50  90 01 00 28 */	stw r0, 0x28(r1)
/* 8012C274 00128E54  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8012C278 00128E58  80 C7 00 00 */	lwz r6, 0(r7)
/* 8012C27C 00128E5C  80 07 00 04 */	lwz r0, 4(r7)
/* 8012C280 00128E60  90 C1 00 3C */	stw r6, 0x3c(r1)
/* 8012C284 00128E64  90 01 00 40 */	stw r0, 0x40(r1)
/* 8012C288 00128E68  80 07 00 08 */	lwz r0, 8(r7)
/* 8012C28C 00128E6C  90 01 00 44 */	stw r0, 0x44(r1)
/* 8012C290 00128E70  80 C1 00 3C */	lwz r6, 0x3c(r1)
/* 8012C294 00128E74  80 01 00 40 */	lwz r0, 0x40(r1)
/* 8012C298 00128E78  90 C1 00 30 */	stw r6, 0x30(r1)
/* 8012C29C 00128E7C  90 01 00 34 */	stw r0, 0x34(r1)
/* 8012C2A0 00128E80  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8012C2A4 00128E84  90 01 00 38 */	stw r0, 0x38(r1)
/* 8012C2A8 00128E88  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 8012C2AC 00128E8C  4B F4 F3 01 */	bl func_8007B5AC
/* 8012C2B0 00128E90  7F C3 F3 78 */	mr r3, r30
/* 8012C2B4 00128E94  4B F6 61 9D */	bl func_80092450
/* 8012C2B8 00128E98  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 8012C2BC 00128E9C  38 60 00 00 */	li r3, 0
/* 8012C2C0 00128EA0  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8012C2C4 00128EA4  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 8012C2C8 00128EA8  7F C3 F3 78 */	mr r3, r30
/* 8012C2CC 00128EAC  4B FF F5 D9 */	bl func_8012B8A4
/* 8012C2D0 00128EB0  7F E3 FB 78 */	mr r3, r31
/* 8012C2D4 00128EB4  4B F6 5A 85 */	bl func_80091D58
/* 8012C2D8 00128EB8  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8012C2DC 00128EBC  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 8012C2E0 00128EC0  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 8012C2E4 00128EC4  83 A1 00 5C */	lwz r29, 0x5c(r1)
/* 8012C2E8 00128EC8  38 21 00 68 */	addi r1, r1, 0x68
/* 8012C2EC 00128ECC  7C 08 03 A6 */	mtlr r0
/* 8012C2F0 00128ED0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void lbl_8012C2F4(HSD_GObj* fighter_gobj)
{
    u32 unused[3];
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    fp->x2340_f32 += lbl_804D9A28;
    func_80092BCC(fighter_gobj);

    if (func_800925A4(fighter_gobj)) {
        spawnEffect(fighter_gobj);
    } else if (fp->x234C_stateVar4_s32 != 0 ||
               (!(fp->x221B_b0 & 1) && !(fp->x2218_flag.bits.b3)))
    {
        func_80092BE8(fighter_gobj);
    } else {
        func_8012B8A4(fighter_gobj);
    }
}

void lbl_8012C3EC(HSD_GObj* fighter_gobj)
{
    if (!func_8009515C(fighter_gobj) && !func_80099794(fighter_gobj) &&
        !func_8009917C(fighter_gobj) && !func_800D8990(fighter_gobj) &&
        !func_8009A080(fighter_gobj))
    {
        return;
    }
}

void lbl_8012C45C(HSD_GObj* arg0)
{
    func_80092B70(arg0);
}

void lbl_8012C47C(HSD_GObj* arg0)
{
    func_80092BAC(arg0);
}

void func_8012C49C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32* x1CC;
    s32 bone_idx;
    Fighter* fp2;
    HSD_JObj* jobj;
    u32 unused[4];

    f32 temp_f1 = lbl_804D9A2C;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x157, 0, NULL, temp_f1,
                                       lbl_804D9A28, temp_f1);

    fp = fighter_gobj->user_data;
    func_80074B0C(fighter_gobj, 0, 0);
    func_8007B0C0(fighter_gobj, 0);

    x1CC = &fp->x110_attr.x1CC;
    bone_idx = func_8007500C(fp, 4);
    fp2 = fighter_gobj->user_data;
    jobj = fp->x5E8_fighterBones[bone_idx].x0_jobj;
    efAsync_Spawn(fighter_gobj, &fp2->x60C, 4U, 0x4CF, jobj, x1CC);
}

void lbl_8012C54C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 unused[2];
    fp = fighter_gobj->user_data;
    fp->x2340_f32 = fp->x2340_f32 + lbl_804D9A28;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        func_8008A2BC(fighter_gobj);
    }
}

void lbl_8012C59C(HSD_GObj* arg0)
{
    if (!func_80099794(arg0)) {
        return;
    }
}

void lbl_8012C5C0(HSD_GObj* arg0)
{
    func_80092E10(arg0);
}

void lbl_8012C5E0(HSD_GObj* arg0)
{
    func_80092E30(arg0);
}

extern f64 const lbl_804D9A30;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8012C600(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012C600 001291E0  7C 08 02 A6 */	mflr r0
/* 8012C604 001291E4  38 A0 00 00 */	li r5, 0
/* 8012C608 001291E8  90 01 00 04 */	stw r0, 4(r1)
/* 8012C60C 001291EC  38 C0 00 00 */	li r6, 0
/* 8012C610 001291F0  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 8012C614 001291F4  93 E1 00 74 */	stw r31, 0x74(r1)
/* 8012C618 001291F8  93 C1 00 70 */	stw r30, 0x70(r1)
/* 8012C61C 001291FC  3B C4 00 00 */	addi r30, r4, 0
/* 8012C620 00129200  38 80 01 58 */	li r4, 0x158
/* 8012C624 00129204  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 8012C628 00129208  3B A3 00 00 */	addi r29, r3, 0
/* 8012C62C 0012920C  93 81 00 68 */	stw r28, 0x68(r1)
/* 8012C630 00129210  C0 22 A0 4C */	lfs f1, lbl_804D9A2C
/* 8012C634 00129214  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012C638 00129218  FC 60 08 90 */	fmr f3, f1
/* 8012C63C 0012921C  C0 42 A0 48 */	lfs f2, lbl_804D9A28
/* 8012C640 00129220  4B F3 CD 6D */	bl Fighter_ActionStateChange_800693AC
/* 8012C644 00129224  3C 60 80 09 */	lis r3, func_80093240@ha
/* 8012C648 00129228  38 03 32 40 */	addi r0, r3, func_80093240@l
/* 8012C64C 0012922C  90 1F 21 D0 */	stw r0, 0x21d0(r31)
/* 8012C650 00129230  38 00 00 FE */	li r0, 0xfe
/* 8012C654 00129234  3C 60 80 09 */	lis r3, func_800932DC@ha
/* 8012C658 00129238  98 1F 06 70 */	stb r0, 0x670(r31)
/* 8012C65C 0012923C  38 03 32 DC */	addi r0, r3, func_800932DC@l
/* 8012C660 00129240  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 8012C664 00129244  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8012C668 00129248  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8012C66C 0012924C  40 82 00 14 */	bne lbl_8012C680
/* 8012C670 00129250  38 7D 00 00 */	addi r3, r29, 0
/* 8012C674 00129254  38 80 00 00 */	li r4, 0
/* 8012C678 00129258  38 A0 00 01 */	li r5, 1
/* 8012C67C 0012925C  4B F4 84 91 */	bl func_80074B0C
lbl_8012C680:
/* 8012C680 00129260  83 9D 00 2C */	lwz r28, 0x2c(r29)
/* 8012C684 00129264  38 7D 00 00 */	addi r3, r29, 0
/* 8012C688 00129268  38 80 00 02 */	li r4, 2
/* 8012C68C 0012926C  4B F4 EA 35 */	bl func_8007B0C0
/* 8012C690 00129270  80 9C 01 0C */	lwz r4, 0x10c(r28)
/* 8012C694 00129274  3C 60 80 3B */	lis r3, lbl_803B75C0@ha
/* 8012C698 00129278  38 00 00 01 */	li r0, 1
/* 8012C69C 0012927C  C0 02 A0 48 */	lfs f0, lbl_804D9A28
/* 8012C6A0 00129280  80 84 00 08 */	lwz r4, 8(r4)
/* 8012C6A4 00129284  38 E3 75 C0 */	addi r7, r3, lbl_803B75C0@l
/* 8012C6A8 00129288  88 A4 00 11 */	lbz r5, 0x11(r4)
/* 8012C6AC 0012928C  38 7C 00 00 */	addi r3, r28, 0
/* 8012C6B0 00129290  38 9C 11 A0 */	addi r4, r28, 0x11a0
/* 8012C6B4 00129294  90 A1 00 28 */	stw r5, 0x28(r1)
/* 8012C6B8 00129298  38 A1 00 28 */	addi r5, r1, 0x28
/* 8012C6BC 0012929C  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8012C6C0 001292A0  90 01 00 30 */	stw r0, 0x30(r1)
/* 8012C6C4 001292A4  80 C7 00 00 */	lwz r6, 0(r7)
/* 8012C6C8 001292A8  80 07 00 04 */	lwz r0, 4(r7)
/* 8012C6CC 001292AC  90 C1 00 40 */	stw r6, 0x40(r1)
/* 8012C6D0 001292B0  90 01 00 44 */	stw r0, 0x44(r1)
/* 8012C6D4 001292B4  80 07 00 08 */	lwz r0, 8(r7)
/* 8012C6D8 001292B8  90 01 00 48 */	stw r0, 0x48(r1)
/* 8012C6DC 001292BC  80 C1 00 40 */	lwz r6, 0x40(r1)
/* 8012C6E0 001292C0  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8012C6E4 001292C4  90 C1 00 34 */	stw r6, 0x34(r1)
/* 8012C6E8 001292C8  90 01 00 38 */	stw r0, 0x38(r1)
/* 8012C6EC 001292CC  80 01 00 48 */	lwz r0, 0x48(r1)
/* 8012C6F0 001292D0  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8012C6F4 001292D4  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 8012C6F8 001292D8  4B F4 EE B5 */	bl func_8007B5AC
/* 8012C6FC 001292DC  80 7F 19 A4 */	lwz r3, 0x19a4(r31)
/* 8012C700 001292E0  3C 00 43 30 */	lis r0, 0x4330
/* 8012C704 001292E4  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8012C708 001292E8  2C 1E 00 00 */	cmpwi r30, 0
/* 8012C70C 001292EC  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8012C710 001292F0  90 61 00 64 */	stw r3, 0x64(r1)
/* 8012C714 001292F4  C8 62 A0 50 */	lfd f3, lbl_804D9A30
/* 8012C718 001292F8  90 01 00 60 */	stw r0, 0x60(r1)
/* 8012C71C 001292FC  C0 22 A0 48 */	lfs f1, lbl_804D9A28
/* 8012C720 00129300  C8 41 00 60 */	lfd f2, 0x60(r1)
/* 8012C724 00129304  C0 1F 19 9C */	lfs f0, 0x199c(r31)
/* 8012C728 00129308  EC 42 18 28 */	fsubs f2, f2, f3
/* 8012C72C 0012930C  C0 64 02 8C */	lfs f3, 0x28c(r4)
/* 8012C730 00129310  EC 21 00 28 */	fsubs f1, f1, f0
/* 8012C734 00129314  C0 04 02 90 */	lfs f0, 0x290(r4)
/* 8012C738 00129318  EC 22 00 72 */	fmuls f1, f2, f1
/* 8012C73C 0012931C  EC 23 00 7A */	fmadds f1, f3, f1, f0
/* 8012C740 00129320  40 82 00 34 */	bne lbl_8012C774
/* 8012C744 00129324  C0 04 02 94 */	lfs f0, 0x294(r4)
/* 8012C748 00129328  EC 01 00 32 */	fmuls f0, f1, f0
/* 8012C74C 0012932C  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8012C750 00129330  C0 3F 19 AC */	lfs f1, 0x19ac(r31)
/* 8012C754 00129334  C0 02 A0 4C */	lfs f0, lbl_804D9A2C
/* 8012C758 00129338  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8012C75C 0012933C  40 80 00 0C */	bge lbl_8012C768
/* 8012C760 00129340  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 8012C764 00129344  48 00 00 0C */	b lbl_8012C770
lbl_8012C768:
/* 8012C768 00129348  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 8012C76C 0012934C  FC 00 00 50 */	fneg f0, f0
lbl_8012C770:
/* 8012C770 00129350  D0 1F 00 EC */	stfs f0, 0xec(r31)
lbl_8012C774:
/* 8012C774 00129354  7F A3 EB 78 */	mr r3, r29
/* 8012C778 00129358  4B F6 5C D9 */	bl func_80092450
/* 8012C77C 0012935C  7F E3 FB 78 */	mr r3, r31
/* 8012C780 00129360  4B F6 55 D9 */	bl func_80091D58
/* 8012C784 00129364  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 8012C788 00129368  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 8012C78C 0012936C  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 8012C790 00129370  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 8012C794 00129374  83 81 00 68 */	lwz r28, 0x68(r1)
/* 8012C798 00129378  38 21 00 78 */	addi r1, r1, 0x78
/* 8012C79C 0012937C  7C 08 03 A6 */	mtlr r0
/* 8012C7A0 00129380  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void lbl_8012C7A4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_80093BC0(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (fp->x234C_stateVar4_s32) {
            func_80092BE8(fighter_gobj);
        } else {
            func_800928CC(fighter_gobj);
        }
    }
}

void lbl_8012C80C(HSD_GObj* arg0) {}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012C810(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012C810 001293F0  7C 08 02 A6 */	mflr r0
/* 8012C814 001293F4  90 01 00 04 */	stw r0, 4(r1)
/* 8012C818 001293F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8012C81C 001293FC  4B F6 6E 0D */	bl func_80093628
/* 8012C820 00129400  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012C824 00129404  38 21 00 08 */	addi r1, r1, 8
/* 8012C828 00129408  7C 08 03 A6 */	mtlr r0
/* 8012C82C 0012940C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012C830(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012C830 00129410  7C 08 02 A6 */	mflr r0
/* 8012C834 00129414  90 01 00 04 */	stw r0, 4(r1)
/* 8012C838 00129418  94 21 FF F8 */	stwu r1, -8(r1)
/* 8012C83C 0012941C  4B F6 6E 21 */	bl func_8009365C
/* 8012C840 00129420  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012C844 00129424  38 21 00 08 */	addi r1, r1, 8
/* 8012C848 00129428  7C 08 03 A6 */	mtlr r0
/* 8012C84C 0012942C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void func_8012C850(HSD_GObj* fighter_gobj)
{
    ftCommonData* temp_r5;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x159, 0x10, NULL,
                                       fp->x894_currentAnimFrame, lbl_804D9A28,
                                       lbl_804D9A2C);
    fp->x672_input_timer_counter = 254;
    fp->x221A_flag.bits.b7 = false;
    fp->x221B_b0 = false;
    fp->x221C_flag.bits.b3 = true;
    fp->x221C_flag.bits.b1 = true;
    fp->x221C_flag.bits.b2 = true;

    fp->x2354_stateVar6_f32 = p_ftCommonData->x2A4;
    temp_r5 = p_ftCommonData;
    fp->x2358_stateVar7 = temp_r5->x2B4;
    func_8009370C(fighter_gobj, lbl_8012CACC, temp_r5);
}

extern char* const lbl_804D3E58;
extern char* const lbl_804D3E60;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8012C914(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012C914 001294F4  7C 08 02 A6 */	mflr r0
/* 8012C918 001294F8  38 80 01 59 */	li r4, 0x159
/* 8012C91C 001294FC  90 01 00 04 */	stw r0, 4(r1)
/* 8012C920 00129500  38 A0 00 00 */	li r5, 0
/* 8012C924 00129504  38 C0 00 00 */	li r6, 0
/* 8012C928 00129508  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8012C92C 0012950C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8012C930 00129510  7C 7F 1B 78 */	mr r31, r3
/* 8012C934 00129514  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8012C938 00129518  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8012C93C 0012951C  C0 22 A0 4C */	lfs f1, lbl_804D9A2C
/* 8012C940 00129520  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8012C944 00129524  FC 60 08 90 */	fmr f3, f1
/* 8012C948 00129528  C0 42 A0 48 */	lfs f2, lbl_804D9A28
/* 8012C94C 0012952C  4B F3 CA 61 */	bl Fighter_ActionStateChange_800693AC
/* 8012C950 00129530  7F E3 FB 78 */	mr r3, r31
/* 8012C954 00129534  4B F4 22 51 */	bl func_8006EBA4
/* 8012C958 00129538  38 00 00 FE */	li r0, 0xfe
/* 8012C95C 0012953C  98 1D 06 72 */	stb r0, 0x672(r29)
/* 8012C960 00129540  3C 60 80 13 */	lis r3, lbl_8012CACC@ha
/* 8012C964 00129544  38 83 CA CC */	addi r4, r3, lbl_8012CACC@l
/* 8012C968 00129548  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8012C96C 0012954C  38 A0 00 01 */	li r5, 1
/* 8012C970 00129550  50 A0 26 F6 */	rlwimi r0, r5, 4, 0x1b, 0x1b
/* 8012C974 00129554  98 1D 22 1C */	stb r0, 0x221c(r29)
/* 8012C978 00129558  7F E3 FB 78 */	mr r3, r31
/* 8012C97C 0012955C  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8012C980 00129560  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 8012C984 00129564  98 1D 22 1C */	stb r0, 0x221c(r29)
/* 8012C988 00129568  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8012C98C 0012956C  50 A0 2E B4 */	rlwimi r0, r5, 5, 0x1a, 0x1a
/* 8012C990 00129570  98 1D 22 1C */	stb r0, 0x221c(r29)
/* 8012C994 00129574  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 8012C998 00129578  C0 05 02 A4 */	lfs f0, 0x2a4(r5)
/* 8012C99C 0012957C  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 8012C9A0 00129580  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 8012C9A4 00129584  C0 05 02 B4 */	lfs f0, 0x2b4(r5)
/* 8012C9A8 00129588  D0 1D 23 58 */	stfs f0, 0x2358(r29)
/* 8012C9AC 0012958C  4B F6 6D 61 */	bl func_8009370C
/* 8012C9B0 00129590  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 8012C9B4 00129594  38 7F 00 00 */	addi r3, r31, 0
/* 8012C9B8 00129598  38 80 00 01 */	li r4, 1
/* 8012C9BC 0012959C  4B F4 E7 05 */	bl func_8007B0C0
/* 8012C9C0 001295A0  38 00 00 00 */	li r0, 0
/* 8012C9C4 001295A4  90 1E 23 4C */	stw r0, 0x234c(r30)
/* 8012C9C8 001295A8  C0 22 A0 4C */	lfs f1, lbl_804D9A2C
/* 8012C9CC 001295AC  D0 3E 23 40 */	stfs f1, 0x2340(r30)
/* 8012C9D0 001295B0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8012C9D4 001295B4  C0 03 02 68 */	lfs f0, 0x268(r3)
/* 8012C9D8 001295B8  D0 1E 23 50 */	stfs f0, 0x2350(r30)
/* 8012C9DC 001295BC  90 1E 23 64 */	stw r0, 0x2364(r30)
/* 8012C9E0 001295C0  90 1E 23 60 */	stw r0, 0x2360(r30)
/* 8012C9E4 001295C4  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8012C9E8 001295C8  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8012C9EC 001295CC  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 8012C9F0 001295D0  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 8012C9F4 001295D4  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8012C9F8 001295D8  80 63 00 08 */	lwz r3, 8(r3)
/* 8012C9FC 001295DC  88 03 00 11 */	lbz r0, 0x11(r3)
/* 8012CA00 001295E0  54 00 20 36 */	slwi r0, r0, 4
/* 8012CA04 001295E4  7F A4 00 2E */	lwzx r29, r4, r0
/* 8012CA08 001295E8  28 1D 00 00 */	cmplwi r29, 0
/* 8012CA0C 001295EC  40 82 00 14 */	bne lbl_8012CA20
/* 8012CA10 001295F0  38 6D 87 B8 */	addi r3, r13, lbl_804D3E58
/* 8012CA14 001295F4  38 80 03 94 */	li r4, 0x394
/* 8012CA18 001295F8  38 AD 87 C0 */	addi r5, r13, lbl_804D3E60
/* 8012CA1C 001295FC  48 25 B8 05 */	bl __assert
lbl_8012CA20:
/* 8012CA20 00129600  80 61 00 14 */	lwz r3, 0x14(r1)
/* 8012CA24 00129604  80 01 00 18 */	lwz r0, 0x18(r1)
/* 8012CA28 00129608  90 7D 00 38 */	stw r3, 0x38(r29)
/* 8012CA2C 0012960C  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8012CA30 00129610  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012CA34 00129614  90 1D 00 40 */	stw r0, 0x40(r29)
/* 8012CA38 00129618  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8012CA3C 0012961C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8012CA40 00129620  40 82 00 4C */	bne lbl_8012CA8C
/* 8012CA44 00129624  28 1D 00 00 */	cmplwi r29, 0
/* 8012CA48 00129628  41 82 00 44 */	beq lbl_8012CA8C
/* 8012CA4C 0012962C  40 82 00 14 */	bne lbl_8012CA60
/* 8012CA50 00129630  38 6D 87 B8 */	addi r3, r13, lbl_804D3E58
/* 8012CA54 00129634  38 80 02 34 */	li r4, 0x234
/* 8012CA58 00129638  38 AD 87 C0 */	addi r5, r13, lbl_804D3E60
/* 8012CA5C 0012963C  48 25 B7 C5 */	bl __assert
lbl_8012CA60:
/* 8012CA60 00129640  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8012CA64 00129644  38 60 00 00 */	li r3, 0
/* 8012CA68 00129648  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8012CA6C 0012964C  40 82 00 10 */	bne lbl_8012CA7C
/* 8012CA70 00129650  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8012CA74 00129654  41 82 00 08 */	beq lbl_8012CA7C
/* 8012CA78 00129658  38 60 00 01 */	li r3, 1
lbl_8012CA7C:
/* 8012CA7C 0012965C  2C 03 00 00 */	cmpwi r3, 0
/* 8012CA80 00129660  40 82 00 0C */	bne lbl_8012CA8C
/* 8012CA84 00129664  7F A3 EB 78 */	mr r3, r29
/* 8012CA88 00129668  48 24 68 61 */	bl HSD_JObjSetMtxDirtySub
lbl_8012CA8C:
/* 8012CA8C 0012966C  7F E3 FB 78 */	mr r3, r31
/* 8012CA90 00129670  4B FF EE 15 */	bl func_8012B8A4
/* 8012CA94 00129674  7F C3 F3 78 */	mr r3, r30
/* 8012CA98 00129678  4B F6 52 C1 */	bl func_80091D58
/* 8012CA9C 0012967C  38 7E 00 00 */	addi r3, r30, 0
/* 8012CAA0 00129680  38 80 00 6E */	li r4, 0x6e
/* 8012CAA4 00129684  38 A0 00 7F */	li r5, 0x7f
/* 8012CAA8 00129688  38 C0 00 40 */	li r6, 0x40
/* 8012CAAC 0012968C  4B F5 B6 9D */	bl func_80088148
/* 8012CAB0 00129690  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8012CAB4 00129694  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8012CAB8 00129698  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8012CABC 0012969C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8012CAC0 001296A0  38 21 00 30 */	addi r1, r1, 0x30
/* 8012CAC4 001296A4  7C 08 03 A6 */	mtlr r0
/* 8012CAC8 001296A8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void lbl_8012CACC(HSD_GObj* arg0) {}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012CAD0(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012CAD0 001296B0  7C 08 02 A6 */	mflr r0
/* 8012CAD4 001296B4  90 01 00 04 */	stw r0, 4(r1)
/* 8012CAD8 001296B8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8012CADC 001296BC  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8012CAE0 001296C0  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8012CAE4 001296C4  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8012CAE8 001296C8  7C 7D 1B 78 */	mr r29, r3
/* 8012CAEC 001296CC  4B F6 70 D5 */	bl func_80093BC0
/* 8012CAF0 001296D0  80 9D 00 2C */	lwz r4, 0x2c(r29)
/* 8012CAF4 001296D4  7F A3 EB 78 */	mr r3, r29
/* 8012CAF8 001296D8  C0 02 A0 48 */	lfs f0, lbl_804D9A28
/* 8012CAFC 001296DC  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 8012CB00 001296E0  EC 01 00 2A */	fadds f0, f1, f0
/* 8012CB04 001296E4  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 8012CB08 001296E8  4B F6 60 C5 */	bl func_80092BCC
/* 8012CB0C 001296EC  7F A3 EB 78 */	mr r3, r29
/* 8012CB10 001296F0  4B F6 5A 95 */	bl func_800925A4
/* 8012CB14 001296F4  2C 03 00 00 */	cmpwi r3, 0
/* 8012CB18 001296F8  41 82 00 64 */	beq lbl_8012CB7C
/* 8012CB1C 001296FC  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 8012CB20 00129700  38 7D 00 00 */	addi r3, r29, 0
/* 8012CB24 00129704  38 80 00 00 */	li r4, 0
/* 8012CB28 00129708  38 A0 00 00 */	li r5, 0
/* 8012CB2C 0012970C  4B F4 7F E1 */	bl func_80074B0C
/* 8012CB30 00129710  38 7D 00 00 */	addi r3, r29, 0
/* 8012CB34 00129714  38 80 00 00 */	li r4, 0
/* 8012CB38 00129718  4B F4 E5 89 */	bl func_8007B0C0
/* 8012CB3C 0012971C  38 7F 00 00 */	addi r3, r31, 0
/* 8012CB40 00129720  3B DF 01 CC */	addi r30, r31, 0x1cc
/* 8012CB44 00129724  38 80 00 04 */	li r4, 4
/* 8012CB48 00129728  4B F4 84 C5 */	bl func_8007500C
/* 8012CB4C 0012972C  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8012CB50 00129730  54 60 20 36 */	slwi r0, r3, 4
/* 8012CB54 00129734  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8012CB58 00129738  7F A3 EB 78 */	mr r3, r29
/* 8012CB5C 0012973C  7C E4 00 2E */	lwzx r7, r4, r0
/* 8012CB60 00129740  38 85 06 0C */	addi r4, r5, 0x60c
/* 8012CB64 00129744  4C C6 31 82 */	crclr 6
/* 8012CB68 00129748  39 1E 00 00 */	addi r8, r30, 0
/* 8012CB6C 0012974C  38 A0 00 04 */	li r5, 4
/* 8012CB70 00129750  38 C0 04 CF */	li r6, 0x4cf
/* 8012CB74 00129754  4B F3 AB 7D */	bl efAsync_Spawn
/* 8012CB78 00129758  48 00 00 28 */	b lbl_8012CBA0
lbl_8012CB7C:
/* 8012CB7C 0012975C  7F A3 EB 78 */	mr r3, r29
/* 8012CB80 00129760  4B F4 26 B9 */	bl ftAnim_IsFramesRemaining
/* 8012CB84 00129764  2C 03 00 00 */	cmpwi r3, 0
/* 8012CB88 00129768  40 82 00 10 */	bne lbl_8012CB98
/* 8012CB8C 0012976C  7F A3 EB 78 */	mr r3, r29
/* 8012CB90 00129770  4B F6 5D 3D */	bl func_800928CC
/* 8012CB94 00129774  48 00 00 0C */	b lbl_8012CBA0
lbl_8012CB98:
/* 8012CB98 00129778  7F A3 EB 78 */	mr r3, r29
/* 8012CB9C 0012977C  4B FF ED 09 */	bl func_8012B8A4
lbl_8012CBA0:
/* 8012CBA0 00129780  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012CBA4 00129784  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8012CBA8 00129788  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8012CBAC 0012978C  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8012CBB0 00129790  38 21 00 38 */	addi r1, r1, 0x38
/* 8012CBB4 00129794  7C 08 03 A6 */	mtlr r0
/* 8012CBB8 00129798  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012CBBC(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012CBBC 0012979C  7C 08 02 A6 */	mflr r0
/* 8012CBC0 001297A0  90 01 00 04 */	stw r0, 4(r1)
/* 8012CBC4 001297A4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8012CBC8 001297A8  4B F6 72 F9 */	bl func_80093EC0
/* 8012CBCC 001297AC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012CBD0 001297B0  38 21 00 08 */	addi r1, r1, 8
/* 8012CBD4 001297B4  7C 08 03 A6 */	mtlr r0
/* 8012CBD8 001297B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012CBDC(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012CBDC 001297BC  7C 08 02 A6 */	mflr r0
/* 8012CBE0 001297C0  90 01 00 04 */	stw r0, 4(r1)
/* 8012CBE4 001297C4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8012CBE8 001297C8  4B F6 74 55 */	bl func_8009403C
/* 8012CBEC 001297CC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012CBF0 001297D0  38 21 00 08 */	addi r1, r1, 8
/* 8012CBF4 001297D4  7C 08 03 A6 */	mtlr r0
/* 8012CBF8 001297D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012CBFC(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012CBFC 001297DC  7C 08 02 A6 */	mflr r0
/* 8012CC00 001297E0  90 01 00 04 */	stw r0, 4(r1)
/* 8012CC04 001297E4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8012CC08 001297E8  4B F6 74 71 */	bl func_80094078
/* 8012CC0C 001297EC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012CC10 001297F0  38 21 00 08 */	addi r1, r1, 8
/* 8012CC14 001297F4  7C 08 03 A6 */	mtlr r0
/* 8012CC18 001297F8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

bool func_8012CC1C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if ((fp->input.x65C_heldInputs & 0x80000000) &&
        (fp->x1998_shieldHealth >= lbl_804D9A2C))
    {
        func_800928CC(fighter_gobj);
        return true;
    }

    return false;
}

void func_8012CC6C(HSD_GObj* fighter_gobj)
{
    func_8007500C(GET_FIGHTER(fighter_gobj), 52);
}

extern f32 const lbl_804D9A38;

void func_8012CC94(HSD_GObj* fighter_gobj, Vec3* out)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftYoshiAttributes* attr = fp->x2D4_specialAttributes;
    out->x = (-fp->facing_dir * attr->x10);
    out->y = attr->x14;
    out->z = lbl_804D9A38;
}

f32 func_8012CCC4(HSD_GObj* fighter_gobj)
{
    return GET_FIGHTER(fighter_gobj)->facing_dir;
}

f32 func_8012CCD0(HSD_GObj* fighter_gobj)
{
    ftYoshiAttributes* attr = GET_FIGHTER(fighter_gobj)->x2D4_specialAttributes;
    return attr->x18;
}

f32 func_8012CCE0(HSD_GObj* fighter_gobj)
{
    ftYoshiAttributes* attr = GET_FIGHTER(fighter_gobj)->x2D4_specialAttributes;
    return attr->x1C;
}

f32 func_8012CCF0(HSD_GObj* fighter_gobj)
{
    ftYoshiAttributes* attr = GET_FIGHTER(fighter_gobj)->x2D4_specialAttributes;
    return attr->x20;
}

f32 func_8012CD00(HSD_GObj* fighter_gobj)
{
    ftYoshiAttributes* attr = GET_FIGHTER(fighter_gobj)->x2D4_specialAttributes;
    return attr->x24;
}
