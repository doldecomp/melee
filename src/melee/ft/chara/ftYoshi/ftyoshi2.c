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
extern f32 lbl_804D9A2C;
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
               (!(fp->x221B_flag.bits.b0 & 1) && !(fp->x2218_flag.bits.b3)))
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
