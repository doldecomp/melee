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

void lbl_8012C030(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 bone_idx;
    Fighter* fp2;
    s32* x1CC;
    HSD_JObj* jobj;
    u32 unused[4];

    fp = GET_FIGHTER(fighter_gobj);
    fp->x2340_f32 += lbl_804D9A28;
    func_80092BCC(fighter_gobj);
    if (func_800925A4(fighter_gobj)) {
        fp = GET_FIGHTER(fighter_gobj);
        func_80074B0C(fighter_gobj, 0, 0);
        func_8007B0C0(fighter_gobj, 0);

        x1CC = &fp->x110_attr.x1CC;
        bone_idx = func_8007500C(fp, 4);
        fp2 = GET_FIGHTER(fighter_gobj);
        jobj = fp->x5E8_fighterBones[bone_idx].x0_jobj;

        efAsync_Spawn(fighter_gobj, &fp2->x60C, 4U, 0x4CFU, jobj, x1CC);
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

#ifdef MWERKS_GEKKO
#pragma push
asm void lbl_8012C2F4(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8012C2F4 00128ED4  7C 08 02 A6 */	mflr r0
/* 8012C2F8 00128ED8  90 01 00 04 */	stw r0, 4(r1)
/* 8012C2FC 00128EDC  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8012C300 00128EE0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8012C304 00128EE4  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8012C308 00128EE8  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8012C30C 00128EEC  7C 7D 1B 78 */	mr r29, r3
/* 8012C310 00128EF0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8012C314 00128EF4  C0 02 A0 48 */	lfs f0, lbl_804D9A28
/* 8012C318 00128EF8  C0 3E 23 40 */	lfs f1, 0x2340(r30)
/* 8012C31C 00128EFC  EC 01 00 2A */	fadds f0, f1, f0
/* 8012C320 00128F00  D0 1E 23 40 */	stfs f0, 0x2340(r30)
/* 8012C324 00128F04  4B F6 68 A9 */	bl func_80092BCC
/* 8012C328 00128F08  7F A3 EB 78 */	mr r3, r29
/* 8012C32C 00128F0C  4B F6 62 79 */	bl func_800925A4
/* 8012C330 00128F10  2C 03 00 00 */	cmpwi r3, 0
/* 8012C334 00128F14  41 82 00 64 */	beq lbl_8012C398
/* 8012C338 00128F18  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 8012C33C 00128F1C  38 7D 00 00 */	addi r3, r29, 0
/* 8012C340 00128F20  38 80 00 00 */	li r4, 0
/* 8012C344 00128F24  38 A0 00 00 */	li r5, 0
/* 8012C348 00128F28  4B F4 87 C5 */	bl func_80074B0C
/* 8012C34C 00128F2C  38 7D 00 00 */	addi r3, r29, 0
/* 8012C350 00128F30  38 80 00 00 */	li r4, 0
/* 8012C354 00128F34  4B F4 ED 6D */	bl func_8007B0C0
/* 8012C358 00128F38  38 7F 00 00 */	addi r3, r31, 0
/* 8012C35C 00128F3C  3B DF 01 CC */	addi r30, r31, 0x1cc
/* 8012C360 00128F40  38 80 00 04 */	li r4, 4
/* 8012C364 00128F44  4B F4 8C A9 */	bl func_8007500C
/* 8012C368 00128F48  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8012C36C 00128F4C  54 60 20 36 */	slwi r0, r3, 4
/* 8012C370 00128F50  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8012C374 00128F54  7F A3 EB 78 */	mr r3, r29
/* 8012C378 00128F58  7C E4 00 2E */	lwzx r7, r4, r0
/* 8012C37C 00128F5C  38 85 06 0C */	addi r4, r5, 0x60c
/* 8012C380 00128F60  4C C6 31 82 */	crclr 6
/* 8012C384 00128F64  39 1E 00 00 */	addi r8, r30, 0
/* 8012C388 00128F68  38 A0 00 04 */	li r5, 4
/* 8012C38C 00128F6C  38 C0 04 CF */	li r6, 0x4cf
/* 8012C390 00128F70  4B F3 B3 61 */	bl efAsync_Spawn
/* 8012C394 00128F74  48 00 00 3C */	b lbl_8012C3D0
lbl_8012C398:
/* 8012C398 00128F78  80 1E 23 4C */	lwz r0, 0x234c(r30)
/* 8012C39C 00128F7C  2C 00 00 00 */	cmpwi r0, 0
/* 8012C3A0 00128F80  40 82 00 1C */	bne lbl_8012C3BC
/* 8012C3A4 00128F84  88 1E 22 1B */	lbz r0, 0x221b(r30)
/* 8012C3A8 00128F88  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8012C3AC 00128F8C  40 82 00 1C */	bne lbl_8012C3C8
/* 8012C3B0 00128F90  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8012C3B4 00128F94  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8012C3B8 00128F98  40 82 00 10 */	bne lbl_8012C3C8
lbl_8012C3BC:
/* 8012C3BC 00128F9C  7F A3 EB 78 */	mr r3, r29
/* 8012C3C0 00128FA0  4B F6 68 29 */	bl func_80092BE8
/* 8012C3C4 00128FA4  48 00 00 0C */	b lbl_8012C3D0
lbl_8012C3C8:
/* 8012C3C8 00128FA8  7F A3 EB 78 */	mr r3, r29
/* 8012C3CC 00128FAC  4B FF F4 D9 */	bl func_8012B8A4
lbl_8012C3D0:
/* 8012C3D0 00128FB0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012C3D4 00128FB4  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8012C3D8 00128FB8  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8012C3DC 00128FBC  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8012C3E0 00128FC0  38 21 00 38 */	addi r1, r1, 0x38
/* 8012C3E4 00128FC4  7C 08 03 A6 */	mtlr r0
/* 8012C3E8 00128FC8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
