#include "ft/forward.h"
#include "lb/forward.h"

#include "ftCo_Bury.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_BarrelWait.h"
#include "ftCo_Damage.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_HammerWait.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_Lift.h"
#include "ftCo_SpecialAir.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "gr/ground.h"
#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/types.h"
#include "mp/mplib.h"
#include "pl/plbonuslib.h"

#include <placeholder.h>
#include <dolphin/mtx/vec.h>

#ifdef WIP
#pragma force_active on
#endif

/* literal */ extern double const ftCo_804D8C28;
/* literal */ extern double const ftCo_804D8C30;
/* literal */ extern float const ftCo_804D8C38;
/* literal */ extern float const ftCo_804D8C3C;

/* literal */ extern char* const ftCo_803C6BA0;
/* literal */ extern char* const ftCo_803C6BC8;

/* literal */ extern char* const ftCo_804D3C20;
/* literal */ extern char* const ftCo_804D3C28;

void ftCo_800C0874(ftCo_GObj* gobj, UNK_T arg1, ftCommon_BuryType arg2)
{
    switch (arg2) {
    case BuryType_Unk2:
        ftCo_8009EB18(gobj);
    }
}

ASM void ftCo_800C08A0(ftCo_GObj* gobj, int arg1, lb_UnkAnimStruct* arg2,
                       ftCommon_BuryType arg3)
#if !defined(MUST_MATCH) || defined(WIP)
{
    float f;
    HitCapsule hit;
    HurtCapsule* p_hurt;
    Fighter* fp = GET_FIGHTER(gobj);
    f = ftColl_800765F0(fp, NULL, arg2->x4_size);
    switch (arg3) {
    case BuryType_Unk2:
        break;
    case BuryType_Unk1:
        fp->bury_timer_1 = p_ftCommonData->bury_timer_unk1;
        break;
    case BuryType_Unk3:
        fp->bury_timer_2 = p_ftCommonData->bury_timer_unk3;
        break;
    }
    if (ftColl_80076640(fp, &f) != 0) {
        p_hurt = &fp->x11A0_fighterHurtbox[0];
        ftColl_80076764(3, arg3, arg1, arg2, fp, p_hurt);
        lbColl_80008D30(&hit, arg2);
        ftColl_80078384(fp, p_hurt, &hit);
    }
    pl_8003EC30(fp->player_id, fp->x221F_b4, arg3, f);
}

#else /* clang-format off */
{ nofralloc
/* 800C08A0 000BD480  7C 08 02 A6 */	mflr r0
/* 800C08A4 000BD484  90 01 00 04 */	stw r0, 4(r1)
/* 800C08A8 000BD488  3C 00 43 30 */	lis r0, 0x4330
/* 800C08AC 000BD48C  94 21 FE 88 */	stwu r1, -0x178(r1)
/* 800C08B0 000BD490  BF 61 01 64 */	stmw r27, 0x164(r1)
/* 800C08B4 000BD494  3B 64 00 00 */	addi r27, r4, 0
/* 800C08B8 000BD498  7C BC 2B 78 */	mr r28, r5
/* 800C08BC 000BD49C  7C DD 33 78 */	mr r29, r6
/* 800C08C0 000BD4A0  38 80 00 00 */	li r4, 0
/* 800C08C4 000BD4A4  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800C08C8 000BD4A8  80 65 00 04 */	lwz r3, 4(r5)
/* 800C08CC 000BD4AC  C8 22 92 48 */	lfd f1, ftCo_804D8C28
/* 800C08D0 000BD4B0  90 61 01 5C */	stw r3, 0x15c(r1)
/* 800C08D4 000BD4B4  38 7E 00 00 */	addi r3, r30, 0
/* 800C08D8 000BD4B8  90 01 01 58 */	stw r0, 0x158(r1)
/* 800C08DC 000BD4BC  C8 01 01 58 */	lfd f0, 0x158(r1)
/* 800C08E0 000BD4C0  EC 20 08 28 */	fsubs f1, f0, f1
/* 800C08E4 000BD4C4  4B FB 5D 0D */	bl ftColl_800765F0
/* 800C08E8 000BD4C8  2C 1D 00 02 */	cmpwi r29, 2
/* 800C08EC 000BD4CC  D0 21 01 50 */	stfs f1, 0x150(r1)
/* 800C08F0 000BD4D0  3B E0 00 00 */	li r31, 0
/* 800C08F4 000BD4D4  41 82 00 3C */	beq lbl_800C0930
/* 800C08F8 000BD4D8  40 80 00 10 */	bge lbl_800C0908
/* 800C08FC 000BD4DC  2C 1D 00 01 */	cmpwi r29, 1
/* 800C0900 000BD4E0  40 80 00 14 */	bge lbl_800C0914
/* 800C0904 000BD4E4  48 00 00 2C */	b lbl_800C0930
lbl_800C0908:
/* 800C0908 000BD4E8  2C 1D 00 04 */	cmpwi r29, 4
/* 800C090C 000BD4EC  40 80 00 24 */	bge lbl_800C0930
/* 800C0910 000BD4F0  48 00 00 14 */	b lbl_800C0924
lbl_800C0914:
/* 800C0914 000BD4F4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C0918 000BD4F8  80 03 05 DC */	lwz r0, 0x5dc(r3)
/* 800C091C 000BD4FC  90 1E 23 28 */	stw r0, 0x2328(r30)
/* 800C0920 000BD500  48 00 00 10 */	b lbl_800C0930
lbl_800C0924:
/* 800C0924 000BD504  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C0928 000BD508  80 03 05 E4 */	lwz r0, 0x5e4(r3)
/* 800C092C 000BD50C  90 1E 23 2C */	stw r0, 0x232c(r30)
lbl_800C0930:
/* 800C0930 000BD510  38 7E 00 00 */	addi r3, r30, 0
/* 800C0934 000BD514  38 81 01 50 */	addi r4, r1, 0x150
/* 800C0938 000BD518  4B FB 5D 09 */	bl ftColl_80076640
/* 800C093C 000BD51C  2C 03 00 00 */	cmpwi r3, 0
/* 800C0940 000BD520  41 82 00 48 */	beq lbl_800C0988
/* 800C0944 000BD524  1C 7F 00 4C */	mulli r3, r31, 0x4c
/* 800C0948 000BD528  3B E3 11 A0 */	addi r31, r3, 0x11a0
/* 800C094C 000BD52C  7F FE FA 14 */	add r31, r30, r31
/* 800C0950 000BD530  38 9D 00 00 */	addi r4, r29, 0
/* 800C0954 000BD534  38 BB 00 00 */	addi r5, r27, 0
/* 800C0958 000BD538  38 DC 00 00 */	addi r6, r28, 0
/* 800C095C 000BD53C  38 FE 00 00 */	addi r7, r30, 0
/* 800C0960 000BD540  39 1F 00 00 */	addi r8, r31, 0
/* 800C0964 000BD544  38 60 00 03 */	li r3, 3
/* 800C0968 000BD548  4B FB 5D FD */	bl ftColl_80076764
/* 800C096C 000BD54C  38 61 00 1C */	addi r3, r1, 0x1c
/* 800C0970 000BD550  38 9C 00 00 */	addi r4, r28, 0
/* 800C0974 000BD554  4B F4 83 BD */	bl lbColl_80008D30
/* 800C0978 000BD558  38 7E 00 00 */	addi r3, r30, 0
/* 800C097C 000BD55C  38 9F 00 00 */	addi r4, r31, 0
/* 800C0980 000BD560  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800C0984 000BD564  4B FB 7A 01 */	bl ftColl_80078384
lbl_800C0988:
/* 800C0988 000BD568  88 9E 22 1F */	lbz r4, 0x221f(r30)
/* 800C098C 000BD56C  7F A5 EB 78 */	mr r5, r29
/* 800C0990 000BD570  88 7E 00 0C */	lbz r3, 0xc(r30)
/* 800C0994 000BD574  C0 21 01 50 */	lfs f1, 0x150(r1)
/* 800C0998 000BD578  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800C099C 000BD57C  4B F7 E2 95 */	bl pl_8003EC30
/* 800C09A0 000BD580  BB 61 01 64 */	lmw r27, 0x164(r1)
/* 800C09A4 000BD584  80 01 01 7C */	lwz r0, 0x17c(r1)
/* 800C09A8 000BD588  38 21 01 78 */	addi r1, r1, 0x178
/* 800C09AC 000BD58C  7C 08 03 A6 */	mtlr r0
/* 800C09B0 000BD590  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_800C09B4(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->bury_stage_kind = stage_info.internal_stage_id;
    fp->bury_timer_1 = 0;
    switch (fp->bury_stage_kind) {
    case OLDKONGO:
    case KONGO:
        fp->bury_timer_2 = 0;
        return;
    case STAGEKIND_UNK39:
    case STAGEKIND_UNK32:
    case ZEBES:
        fp->bury_timer_2 = 0;
        return;
    }
}

bool ftCo_800C0A28(ftCo_GObj* gobj, UNK_T arg1, ftCommon_BuryType arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (arg2) {
    case BuryType_Unk2: {
        if (fp->bury_timer_2 != 0 || fp->motion_id == ftCo_MS_BarrelWait ||
            fp->x1A6A & 0x20 || fp->x2224_b2)
        {
            return false;
        }
        break;
    }
    case BuryType_Unk3: {
        if (fp->bury_timer_2 != 0) {
            return false;
        }
        break;
    }
    }
    return true;
}

void ftCo_800C0A98(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->bury_timer_1 != 0) {
        --fp->bury_timer_1;
    }
    switch (fp->bury_stage_kind) {
    case OLDKONGO:
    case KONGO:
        if (fp->bury_timer_2 != 0) {
            --fp->bury_timer_2;
            return;
        }
        break;
    case STAGEKIND_UNK39:
    case STAGEKIND_UNK32:
    case ZEBES:
        if (fp->bury_timer_2 != 0) {
            --fp->bury_timer_2;
            return;
        }
        break;
    }
}

ASM void ftCo_800C0B20(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    lb_UnkAnimStruct* unk_anim;
    if (fp->bury_timer_1 == 0) {
        CollData* coll = &fp->coll_data;
        unk_anim = NULL;
        if (fp->coll_data.env_flags & (MPCOLL_GRPUSH | MPCOLL_FLAGS_B16)) {
            unk_anim = Ground_801C5700(coll->floor.index);
        }
        if (coll->env_flags & MPCOLL_CEIL) {
            unk_anim = Ground_801C5700(coll->ceiling.index);
        }
        if (coll->env_flags & MPCOLL_LEFTWALL) {
            unk_anim = Ground_801C5700(coll->left_wall.index);
        }
        if (coll->env_flags & MPCOLL_RIGHTWALL) {
            unk_anim = Ground_801C5700(coll->right_wall.index);
        }
        if (unk_anim != NULL) {
            HitCapsule hit;
            Fighter* fp = GET_FIGHTER(gobj);
            float f = ftColl_800765F0(fp, NULL, unk_anim->x4_size);
            fp->bury_timer_1 = p_ftCommonData->bury_timer_unk1;
            if (ftColl_80076640(fp, &f)) {
                HurtCapsule* hurt = &fp->x11A0_fighterHurtbox[0];
                ftColl_80076764(3, 1, 0, unk_anim, fp, hurt);
                lbColl_80008D30(&hit, unk_anim);
                ftColl_80078384(fp, hurt, &hit);
            }
            pl_8003EC30(fp->player_id, fp->x221F_b4, 1, f);
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C0B20 000BD700  7C 08 02 A6 */	mflr r0
/* 800C0B24 000BD704  90 01 00 04 */	stw r0, 4(r1)
/* 800C0B28 000BD708  94 21 FE 98 */	stwu r1, -0x168(r1)
/* 800C0B2C 000BD70C  93 E1 01 64 */	stw r31, 0x164(r1)
/* 800C0B30 000BD710  93 C1 01 60 */	stw r30, 0x160(r1)
/* 800C0B34 000BD714  7C 7E 1B 78 */	mr r30, r3
/* 800C0B38 000BD718  93 A1 01 5C */	stw r29, 0x15c(r1)
/* 800C0B3C 000BD71C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800C0B40 000BD720  80 03 23 28 */	lwz r0, 0x2328(r3)
/* 800C0B44 000BD724  28 00 00 00 */	cmplwi r0, 0
/* 800C0B48 000BD728  40 82 01 24 */	bne lbl_800C0C6C
/* 800C0B4C 000BD72C  80 03 08 24 */	lwz r0, 0x824(r3)
/* 800C0B50 000BD730  3B A3 06 F0 */	addi r29, r3, 0x6f0
/* 800C0B54 000BD734  3B E0 00 00 */	li r31, 0
/* 800C0B58 000BD738  54 00 03 E1 */	rlwinm. r0, r0, 0, 0xf, 0x10
/* 800C0B5C 000BD73C  41 82 00 10 */	beq lbl_800C0B6C
/* 800C0B60 000BD740  80 7D 01 4C */	lwz r3, 0x14c(r29)
/* 800C0B64 000BD744  48 10 4B 9D */	bl Ground_801C5700
/* 800C0B68 000BD748  7C 7F 1B 78 */	mr r31, r3
lbl_800C0B6C:
/* 800C0B6C 000BD74C  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 800C0B70 000BD750  54 00 04 65 */	rlwinm. r0, r0, 0, 0x11, 0x12
/* 800C0B74 000BD754  41 82 00 10 */	beq lbl_800C0B84
/* 800C0B78 000BD758  80 7D 01 88 */	lwz r3, 0x188(r29)
/* 800C0B7C 000BD75C  48 10 4B 85 */	bl Ground_801C5700
/* 800C0B80 000BD760  7C 7F 1B 78 */	mr r31, r3
lbl_800C0B84:
/* 800C0B84 000BD764  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 800C0B88 000BD768  54 00 05 33 */	rlwinm. r0, r0, 0, 0x14, 0x19
/* 800C0B8C 000BD76C  41 82 00 10 */	beq lbl_800C0B9C
/* 800C0B90 000BD770  80 7D 01 74 */	lwz r3, 0x174(r29)
/* 800C0B94 000BD774  48 10 4B 6D */	bl Ground_801C5700
/* 800C0B98 000BD778  7C 7F 1B 78 */	mr r31, r3
lbl_800C0B9C:
/* 800C0B9C 000BD77C  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 800C0BA0 000BD780  54 00 06 BF */	clrlwi. r0, r0, 0x1a
/* 800C0BA4 000BD784  41 82 00 10 */	beq lbl_800C0BB4
/* 800C0BA8 000BD788  80 7D 01 60 */	lwz r3, 0x160(r29)
/* 800C0BAC 000BD78C  48 10 4B 55 */	bl Ground_801C5700
/* 800C0BB0 000BD790  7C 7F 1B 78 */	mr r31, r3
lbl_800C0BB4:
/* 800C0BB4 000BD794  28 1F 00 00 */	cmplwi r31, 0
/* 800C0BB8 000BD798  41 82 00 B4 */	beq lbl_800C0C6C
/* 800C0BBC 000BD79C  80 7F 00 04 */	lwz r3, 4(r31)
/* 800C0BC0 000BD7A0  3C 00 43 30 */	lis r0, 0x4330
/* 800C0BC4 000BD7A4  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 800C0BC8 000BD7A8  38 80 00 00 */	li r4, 0
/* 800C0BCC 000BD7AC  90 61 01 54 */	stw r3, 0x154(r1)
/* 800C0BD0 000BD7B0  C8 22 92 48 */	lfd f1, ftCo_804D8C28
/* 800C0BD4 000BD7B4  7F A3 EB 78 */	mr r3, r29
/* 800C0BD8 000BD7B8  90 01 01 50 */	stw r0, 0x150(r1)
/* 800C0BDC 000BD7BC  C8 01 01 50 */	lfd f0, 0x150(r1)
/* 800C0BE0 000BD7C0  EC 20 08 28 */	fsubs f1, f0, f1
/* 800C0BE4 000BD7C4  4B FB 5A 0D */	bl ftColl_800765F0
/* 800C0BE8 000BD7C8  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 800C0BEC 000BD7CC  7F A3 EB 78 */	mr r3, r29
/* 800C0BF0 000BD7D0  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 800C0BF4 000BD7D4  38 81 00 14 */	addi r4, r1, 0x14
/* 800C0BF8 000BD7D8  3B C0 00 00 */	li r30, 0
/* 800C0BFC 000BD7DC  80 05 05 DC */	lwz r0, 0x5dc(r5)
/* 800C0C00 000BD7E0  90 1D 23 28 */	stw r0, 0x2328(r29)
/* 800C0C04 000BD7E4  4B FB 5A 3D */	bl ftColl_80076640
/* 800C0C08 000BD7E8  2C 03 00 00 */	cmpwi r3, 0
/* 800C0C0C 000BD7EC  41 82 00 48 */	beq lbl_800C0C54
/* 800C0C10 000BD7F0  1C 7E 00 4C */	mulli r3, r30, 0x4c
/* 800C0C14 000BD7F4  3B C3 11 A0 */	addi r30, r3, 0x11a0
/* 800C0C18 000BD7F8  7F DD F2 14 */	add r30, r29, r30
/* 800C0C1C 000BD7FC  38 DF 00 00 */	addi r6, r31, 0
/* 800C0C20 000BD800  38 FD 00 00 */	addi r7, r29, 0
/* 800C0C24 000BD804  39 1E 00 00 */	addi r8, r30, 0
/* 800C0C28 000BD808  38 60 00 03 */	li r3, 3
/* 800C0C2C 000BD80C  38 80 00 01 */	li r4, 1
/* 800C0C30 000BD810  38 A0 00 00 */	li r5, 0
/* 800C0C34 000BD814  4B FB 5B 31 */	bl ftColl_80076764
/* 800C0C38 000BD818  38 61 00 18 */	addi r3, r1, 0x18
/* 800C0C3C 000BD81C  38 9F 00 00 */	addi r4, r31, 0
/* 800C0C40 000BD820  4B F4 80 F1 */	bl lbColl_80008D30
/* 800C0C44 000BD824  38 7D 00 00 */	addi r3, r29, 0
/* 800C0C48 000BD828  38 9E 00 00 */	addi r4, r30, 0
/* 800C0C4C 000BD82C  38 A1 00 18 */	addi r5, r1, 0x18
/* 800C0C50 000BD830  4B FB 77 35 */	bl ftColl_80078384
lbl_800C0C54:
/* 800C0C54 000BD834  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 800C0C58 000BD838  38 A0 00 01 */	li r5, 1
/* 800C0C5C 000BD83C  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800C0C60 000BD840  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800C0C64 000BD844  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800C0C68 000BD848  4B F7 DF C9 */	bl pl_8003EC30
lbl_800C0C6C:
/* 800C0C6C 000BD84C  80 01 01 6C */	lwz r0, 0x16c(r1)
/* 800C0C70 000BD850  83 E1 01 64 */	lwz r31, 0x164(r1)
/* 800C0C74 000BD854  83 C1 01 60 */	lwz r30, 0x160(r1)
/* 800C0C78 000BD858  83 A1 01 5C */	lwz r29, 0x15c(r1)
/* 800C0C7C 000BD85C  38 21 01 68 */	addi r1, r1, 0x168
/* 800C0C80 000BD860  7C 08 03 A6 */	mtlr r0
/* 800C0C84 000BD864  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

bool ftCo_800C0C88(ftCommon_BuryType arg0)
{
    switch (arg0) {
    case BuryType_Unk1:
    case BuryType_Unk3:
        return true;
    default:
    case BuryType_Unk2:
        return false;
    }
}

bool ftCo_800C0CB8(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860 == 9 && fp->ground_or_air == GA_Ground && !fp->x2227_b6)
    {
        ftCo_800C0D0C(gobj);
        return true;
    }
    return false;
}

ASM void ftCo_800C0D0C(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Vec3 joint_pos;
    Vec3 hip_pos;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    ftCo_8008DCE0(gobj, -1, ftCo_804D8C38);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(
        gobj, ftCo_MS_Bury, Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim,
        ftCo_804D8C38, ftCo_804D8C3C, ftCo_804D8C38, NULL);
    ftCommon_8007E2FC(gobj);
    ftCommon_8007DBCC(
        fp, 0,
        (fp->dmg.x1830_percent * p_ftCommonData->x60C) +
            ((p_ftCommonData->x5FC *
              (p_ftCommonData->x600 - Player_GetHandicap(fp->player_id))) +
             p_ftCommonData->x5F8 +
             (p_ftCommonData->x604 *
              (p_ftCommonData->x608 - (Player_80033BB8(fp->player_id) + 1)))));
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221D_b5 = true;
    fp->x2220_flag.bits.b3 = true;
    fp->x2224_b4 = true;
    fp->mv.co.bury.x0 = p_ftCommonData->x5F4;
    fp->mv.co.bury.x20 = fp->coll_data.floor.index;
    ft_80084CB0(fp, &fp->mv.co.bury.coll_box);
    lb_8000B1CC(fp->parts->joint, NULL, &joint_pos);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint, NULL,
                &hip_pos);
    {
        float y = hip_pos.y - joint_pos.y;
        fp->mv.co.bury.x1C = y / p_ftCommonData->x5F4;
        fp->mv.co.bury.translate = fp->cur_pos;
        efSync_Spawn(1095, gobj, &fp->cur_pos, &fp->x34_scale.y, y);
    }
    fp->x2219_b0 = true;
}

#else /* clang-format off */
{ nofralloc
/* 800C0D0C 000BD8EC  7C 08 02 A6 */	mflr r0
/* 800C0D10 000BD8F0  90 01 00 04 */	stw r0, 4(r1)
/* 800C0D14 000BD8F4  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800C0D18 000BD8F8  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 800C0D1C 000BD8FC  93 E1 00 54 */	stw r31, 0x54(r1)
/* 800C0D20 000BD900  93 C1 00 50 */	stw r30, 0x50(r1)
/* 800C0D24 000BD904  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 800C0D28 000BD908  7C 7D 1B 78 */	mr r29, r3
/* 800C0D2C 000BD90C  93 81 00 48 */	stw r28, 0x48(r1)
/* 800C0D30 000BD910  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800C0D34 000BD914  4B FB CE 25 */	bl ftCommon_8007DB58
/* 800C0D38 000BD918  7F A3 EB 78 */	mr r3, r29
/* 800C0D3C 000BD91C  4B FD 67 D1 */	bl ftCo_8009750C
/* 800C0D40 000BD920  7F A3 EB 78 */	mr r3, r29
/* 800C0D44 000BD924  48 01 C4 25 */	bl ftCo_800DD168
/* 800C0D48 000BD928  C0 22 92 58 */	lfs f1, ftCo_804D8C38
/* 800C0D4C 000BD92C  38 7D 00 00 */	addi r3, r29, 0
/* 800C0D50 000BD930  38 80 FF FF */	li r4, -1
/* 800C0D54 000BD934  4B FC CF 8D */	bl ftCo_8008DCE0
/* 800C0D58 000BD938  7F C3 F3 78 */	mr r3, r30
/* 800C0D5C 000BD93C  4B FB CA A1 */	bl ftCommon_8007D7FC
/* 800C0D60 000BD940  C0 22 92 58 */	lfs f1, ftCo_804D8C38
/* 800C0D64 000BD944  7F A3 EB 78 */	mr r3, r29
/* 800C0D68 000BD948  C0 42 92 5C */	lfs f2, ftCo_804D8C3C
/* 800C0D6C 000BD94C  38 80 01 26 */	li r4, 0x126
/* 800C0D70 000BD950  FC 60 08 90 */	fmr f3, f1
/* 800C0D74 000BD954  38 A0 10 80 */	li r5, 0x1080
/* 800C0D78 000BD958  38 C0 00 00 */	li r6, 0
/* 800C0D7C 000BD95C  4B FA 86 31 */	bl Fighter_ChangeMotionState
/* 800C0D80 000BD960  7F A3 EB 78 */	mr r3, r29
/* 800C0D84 000BD964  4B FB D5 79 */	bl ftCommon_8007E2FC
/* 800C0D88 000BD968  83 ED AE B4 */	lwz r31, p_ftCommonData
/* 800C0D8C 000BD96C  88 7E 00 0C */	lbz r3, 0xc(r30)
/* 800C0D90 000BD970  4B F7 2E 29 */	bl Player_80033BB8
/* 800C0D94 000BD974  38 03 00 01 */	addi r0, r3, 1
/* 800C0D98 000BD978  C8 62 92 50 */	lfd f3, ftCo_804D8C30
/* 800C0D9C 000BD97C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C0DA0 000BD980  C0 3F 06 08 */	lfs f1, 0x608(r31)
/* 800C0DA4 000BD984  90 01 00 44 */	stw r0, 0x44(r1)
/* 800C0DA8 000BD988  3F 80 43 30 */	lis r28, 0x4330
/* 800C0DAC 000BD98C  C0 1F 06 04 */	lfs f0, 0x604(r31)
/* 800C0DB0 000BD990  93 81 00 40 */	stw r28, 0x40(r1)
/* 800C0DB4 000BD994  88 7E 00 0C */	lbz r3, 0xc(r30)
/* 800C0DB8 000BD998  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 800C0DBC 000BD99C  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C0DC0 000BD9A0  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C0DC4 000BD9A4  EF E0 00 72 */	fmuls f31, f0, f1
/* 800C0DC8 000BD9A8  4B F7 29 D1 */	bl Player_GetHandicap
/* 800C0DCC 000BD9AC  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 800C0DD0 000BD9B0  C8 22 92 50 */	lfd f1, ftCo_804D8C30
/* 800C0DD4 000BD9B4  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800C0DD8 000BD9B8  7F C3 F3 78 */	mr r3, r30
/* 800C0DDC 000BD9BC  C0 9F 06 00 */	lfs f4, 0x600(r31)
/* 800C0DE0 000BD9C0  38 80 00 00 */	li r4, 0
/* 800C0DE4 000BD9C4  93 81 00 38 */	stw r28, 0x38(r1)
/* 800C0DE8 000BD9C8  C0 7F 05 FC */	lfs f3, 0x5fc(r31)
/* 800C0DEC 000BD9CC  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 800C0DF0 000BD9D0  C0 5F 05 F8 */	lfs f2, 0x5f8(r31)
/* 800C0DF4 000BD9D4  EC A0 08 28 */	fsubs f5, f0, f1
/* 800C0DF8 000BD9D8  C0 3E 18 30 */	lfs f1, 0x1830(r30)
/* 800C0DFC 000BD9DC  C0 1F 06 0C */	lfs f0, 0x60c(r31)
/* 800C0E00 000BD9E0  EC 84 28 28 */	fsubs f4, f4, f5
/* 800C0E04 000BD9E4  EC 43 11 3A */	fmadds f2, f3, f4, f2
/* 800C0E08 000BD9E8  EC 42 F8 2A */	fadds f2, f2, f31
/* 800C0E0C 000BD9EC  EC 21 10 3A */	fmadds f1, f1, f0, f2
/* 800C0E10 000BD9F0  4B FB CD BD */	bl ftCommon_8007DBCC
/* 800C0E14 000BD9F4  38 7E 00 00 */	addi r3, r30, 0
/* 800C0E18 000BD9F8  38 80 01 FF */	li r4, 0x1ff
/* 800C0E1C 000BD9FC  4B FB D4 D9 */	bl ftCommon_8007E2F4
/* 800C0E20 000BDA00  88 1E 22 1D */	lbz r0, 0x221d(r30)
/* 800C0E24 000BDA04  3B E0 00 01 */	li r31, 1
/* 800C0E28 000BDA08  53 E0 17 7A */	rlwimi r0, r31, 2, 0x1d, 0x1d
/* 800C0E2C 000BDA0C  98 1E 22 1D */	stb r0, 0x221d(r30)
/* 800C0E30 000BDA10  38 7E 00 00 */	addi r3, r30, 0
/* 800C0E34 000BDA14  38 9E 23 44 */	addi r4, r30, 0x2344
/* 800C0E38 000BDA18  88 1E 22 20 */	lbz r0, 0x2220(r30)
/* 800C0E3C 000BDA1C  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 800C0E40 000BDA20  98 1E 22 20 */	stb r0, 0x2220(r30)
/* 800C0E44 000BDA24  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 800C0E48 000BDA28  53 E0 1F 38 */	rlwimi r0, r31, 3, 0x1c, 0x1c
/* 800C0E4C 000BDA2C  98 1E 22 24 */	stb r0, 0x2224(r30)
/* 800C0E50 000BDA30  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 800C0E54 000BDA34  80 05 05 F4 */	lwz r0, 0x5f4(r5)
/* 800C0E58 000BDA38  90 1E 23 40 */	stw r0, 0x2340(r30)
/* 800C0E5C 000BDA3C  80 1E 08 3C */	lwz r0, 0x83c(r30)
/* 800C0E60 000BDA40  90 1E 23 60 */	stw r0, 0x2360(r30)
/* 800C0E64 000BDA44  4B FC 3E 4D */	bl ft_80084CB0
/* 800C0E68 000BDA48  80 7E 05 E8 */	lwz r3, 0x5e8(r30)
/* 800C0E6C 000BDA4C  38 A1 00 20 */	addi r5, r1, 0x20
/* 800C0E70 000BDA50  38 80 00 00 */	li r4, 0
/* 800C0E74 000BDA54  80 63 00 00 */	lwz r3, 0(r3)
/* 800C0E78 000BDA58  4B F4 A3 55 */	bl lb_8000B1CC
/* 800C0E7C 000BDA5C  38 7E 00 00 */	addi r3, r30, 0
/* 800C0E80 000BDA60  38 80 00 04 */	li r4, 4
/* 800C0E84 000BDA64  4B FB 41 89 */	bl ftParts_8007500C
/* 800C0E88 000BDA68  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800C0E8C 000BDA6C  54 60 20 36 */	slwi r0, r3, 4
/* 800C0E90 000BDA70  38 A1 00 14 */	addi r5, r1, 0x14
/* 800C0E94 000BDA74  7C 64 00 2E */	lwzx r3, r4, r0
/* 800C0E98 000BDA78  38 80 00 00 */	li r4, 0
/* 800C0E9C 000BDA7C  4B F4 A3 31 */	bl lb_8000B1CC
/* 800C0EA0 000BDA80  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C0EA4 000BDA84  7F A4 EB 78 */	mr r4, r29
/* 800C0EA8 000BDA88  C0 41 00 18 */	lfs f2, 0x18(r1)
/* 800C0EAC 000BDA8C  38 BE 00 B0 */	addi r5, r30, 0xb0
/* 800C0EB0 000BDA90  80 03 05 F4 */	lwz r0, 0x5f4(r3)
/* 800C0EB4 000BDA94  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800C0EB8 000BDA98  38 DE 00 38 */	addi r6, r30, 0x38
/* 800C0EBC 000BDA9C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C0EC0 000BDAA0  C8 22 92 50 */	lfd f1, ftCo_804D8C30
/* 800C0EC4 000BDAA4  90 01 00 34 */	stw r0, 0x34(r1)
/* 800C0EC8 000BDAA8  EC 42 00 28 */	fsubs f2, f2, f0
/* 800C0ECC 000BDAAC  4C C6 31 82 */	crclr 6
/* 800C0ED0 000BDAB0  93 81 00 30 */	stw r28, 0x30(r1)
/* 800C0ED4 000BDAB4  38 60 04 47 */	li r3, 0x447
/* 800C0ED8 000BDAB8  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 800C0EDC 000BDABC  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C0EE0 000BDAC0  EC 02 00 24 */	fdivs f0, f2, f0
/* 800C0EE4 000BDAC4  D0 1E 23 5C */	stfs f0, 0x235c(r30)
/* 800C0EE8 000BDAC8  80 FE 00 B0 */	lwz r7, 0xb0(r30)
/* 800C0EEC 000BDACC  80 1E 00 B4 */	lwz r0, 0xb4(r30)
/* 800C0EF0 000BDAD0  90 FE 23 64 */	stw r7, 0x2364(r30)
/* 800C0EF4 000BDAD4  90 1E 23 68 */	stw r0, 0x2368(r30)
/* 800C0EF8 000BDAD8  80 1E 00 B8 */	lwz r0, 0xb8(r30)
/* 800C0EFC 000BDADC  90 1E 23 6C */	stw r0, 0x236c(r30)
/* 800C0F00 000BDAE0  4B F9 EE DD */	bl efSync_Spawn
/* 800C0F04 000BDAE4  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 800C0F08 000BDAE8  53 E0 3E 30 */	rlwimi r0, r31, 7, 0x18, 0x18
/* 800C0F0C 000BDAEC  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 800C0F10 000BDAF0  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800C0F14 000BDAF4  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 800C0F18 000BDAF8  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 800C0F1C 000BDAFC  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 800C0F20 000BDB00  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 800C0F24 000BDB04  83 81 00 48 */	lwz r28, 0x48(r1)
/* 800C0F28 000BDB08  38 21 00 60 */	addi r1, r1, 0x60
/* 800C0F2C 000BDB0C  7C 08 03 A6 */	mtlr r0
/* 800C0F30 000BDB10  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_Bury_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C -= p_ftCommonData->x610;
    ftCommon_8007DC08(fp, p_ftCommonData->x614);
    if (fp->x1A4C <= ftCo_804D8C38) {
        ftCo_800C13BC(gobj);
    }
    --fp->mv.co.bury.x0;
    if (fp->mv.co.bury.x0 == 0) {
        ftCo_800C124C(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C0F34 000BDB14  7C 08 02 A6 */	mflr r0
/* 800C0F38 000BDB18  90 01 00 04 */	stw r0, 4(r1)
/* 800C0F3C 000BDB1C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C0F40 000BDB20  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C0F44 000BDB24  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C0F48 000BDB28  7C 7E 1B 78 */	mr r30, r3
/* 800C0F4C 000BDB2C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C0F50 000BDB30  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800C0F54 000BDB34  C0 03 06 10 */	lfs f0, 0x610(r3)
/* 800C0F58 000BDB38  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C0F5C 000BDB3C  7F E3 FB 78 */	mr r3, r31
/* 800C0F60 000BDB40  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C0F64 000BDB44  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800C0F68 000BDB48  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C0F6C 000BDB4C  C0 24 06 14 */	lfs f1, 0x614(r4)
/* 800C0F70 000BDB50  4B FB CC 99 */	bl ftCommon_8007DC08
/* 800C0F74 000BDB54  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C0F78 000BDB58  C0 02 92 58 */	lfs f0, ftCo_804D8C38
/* 800C0F7C 000BDB5C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C0F80 000BDB60  4C 40 13 82 */	cror 2, 0, 2
/* 800C0F84 000BDB64  40 82 00 0C */	bne lbl_800C0F90
/* 800C0F88 000BDB68  7F C3 F3 78 */	mr r3, r30
/* 800C0F8C 000BDB6C  48 00 04 31 */	bl ftCo_800C13BC
lbl_800C0F90:
/* 800C0F90 000BDB70  80 7F 23 40 */	lwz r3, 0x2340(r31)
/* 800C0F94 000BDB74  38 03 FF FF */	addi r0, r3, -1
/* 800C0F98 000BDB78  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 800C0F9C 000BDB7C  80 1F 23 40 */	lwz r0, 0x2340(r31)
/* 800C0FA0 000BDB80  2C 00 00 00 */	cmpwi r0, 0
/* 800C0FA4 000BDB84  40 82 00 0C */	bne lbl_800C0FB0
/* 800C0FA8 000BDB88  7F C3 F3 78 */	mr r3, r30
/* 800C0FAC 000BDB8C  48 00 02 A1 */	bl ftCo_800C124C
lbl_800C0FB0:
/* 800C0FB0 000BDB90  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C0FB4 000BDB94  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C0FB8 000BDB98  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C0FBC 000BDB9C  38 21 00 20 */	addi r1, r1, 0x20
/* 800C0FC0 000BDBA0  7C 08 03 A6 */	mtlr r0
/* 800C0FC4 000BDBA4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_Bury_IASA(ftCo_GObj* gobj) {}

ASM void ftCo_800C0FCC(HSD_GObj* arg0, ftCo_GObj* arg1)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(arg1);
    if (mpLib_80054ED8(fp->mv.co.bury.x20)) {
        Vec3 normal;
        Vec3 offset;
        HSD_JObj* jobj = GET_JOBJ(arg0);
        mpLib_80054DFC(fp->mv.co.bury.x20, &normal);
        HSD_JObjSetRotationZ(jobj, atan2f(-normal.x, normal.y));
        if (mpLib_800567C0(fp->coll_data.floor.index,
                           &fp->mv.co.bury.translate, &offset))
        {
            PSVECAdd(&fp->mv.co.bury.translate, &offset,
                     &fp->mv.co.bury.translate);
            HSD_JObjSetTranslate(jobj, &fp->mv.co.bury.translate);
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C0FCC 000BDBAC  7C 08 02 A6 */	mflr r0
/* 800C0FD0 000BDBB0  90 01 00 04 */	stw r0, 4(r1)
/* 800C0FD4 000BDBB4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C0FD8 000BDBB8  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 800C0FDC 000BDBBC  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800C0FE0 000BDBC0  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800C0FE4 000BDBC4  7C 7E 1B 78 */	mr r30, r3
/* 800C0FE8 000BDBC8  83 E4 00 2C */	lwz r31, 0x2c(r4)
/* 800C0FEC 000BDBCC  80 7F 23 60 */	lwz r3, 0x2360(r31)
/* 800C0FF0 000BDBD0  4B F9 3E E9 */	bl mpLib_80054ED8
/* 800C0FF4 000BDBD4  2C 03 00 00 */	cmpwi r3, 0
/* 800C0FF8 000BDBD8  41 82 01 80 */	beq lbl_800C1178
/* 800C0FFC 000BDBDC  83 DE 00 28 */	lwz r30, 0x28(r30)
/* 800C1000 000BDBE0  38 81 00 24 */	addi r4, r1, 0x24
/* 800C1004 000BDBE4  80 7F 23 60 */	lwz r3, 0x2360(r31)
/* 800C1008 000BDBE8  4B F9 3D F5 */	bl mpLib_80054DFC
/* 800C100C 000BDBEC  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800C1010 000BDBF0  C0 41 00 28 */	lfs f2, 0x28(r1)
/* 800C1014 000BDBF4  FC 20 00 50 */	fneg f1, f0
/* 800C1018 000BDBF8  4B F6 1C 19 */	bl atan2f
/* 800C101C 000BDBFC  FF E0 08 90 */	fmr f31, f1
/* 800C1020 000BDC00  28 1E 00 00 */	cmplwi r30, 0
/* 800C1024 000BDC04  40 82 00 14 */	bne lbl_800C1038
/* 800C1028 000BDC08  38 6D 85 80 */	addi r3, r13, ftCo_804D3C20
/* 800C102C 000BDC0C  38 80 02 A9 */	li r4, 0x2a9
/* 800C1030 000BDC10  38 AD 85 88 */	addi r5, r13, ftCo_804D3C28
/* 800C1034 000BDC14  48 2C 71 ED */	bl __assert
lbl_800C1038:
/* 800C1038 000BDC18  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800C103C 000BDC1C  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 800C1040 000BDC20  41 82 00 18 */	beq lbl_800C1058
/* 800C1044 000BDC24  3C 60 80 3C */	lis r3, ftCo_803C6BA0@ha
/* 800C1048 000BDC28  38 A3 6B A0 */	addi r5, r3, ftCo_803C6BA0@l
/* 800C104C 000BDC2C  38 6D 85 80 */	addi r3, r13, ftCo_804D3C20
/* 800C1050 000BDC30  38 80 02 AA */	li r4, 0x2aa
/* 800C1054 000BDC34  48 2C 71 CD */	bl __assert
lbl_800C1058:
/* 800C1058 000BDC38  D3 FE 00 24 */	stfs f31, 0x24(r30)
/* 800C105C 000BDC3C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800C1060 000BDC40  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800C1064 000BDC44  40 82 00 4C */	bne lbl_800C10B0
/* 800C1068 000BDC48  28 1E 00 00 */	cmplwi r30, 0
/* 800C106C 000BDC4C  41 82 00 44 */	beq lbl_800C10B0
/* 800C1070 000BDC50  40 82 00 14 */	bne lbl_800C1084
/* 800C1074 000BDC54  38 6D 85 80 */	addi r3, r13, ftCo_804D3C20
/* 800C1078 000BDC58  38 80 02 34 */	li r4, 0x234
/* 800C107C 000BDC5C  38 AD 85 88 */	addi r5, r13, ftCo_804D3C28
/* 800C1080 000BDC60  48 2C 71 A1 */	bl __assert
lbl_800C1084:
/* 800C1084 000BDC64  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800C1088 000BDC68  38 60 00 00 */	li r3, 0
/* 800C108C 000BDC6C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C1090 000BDC70  40 82 00 10 */	bne lbl_800C10A0
/* 800C1094 000BDC74  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C1098 000BDC78  41 82 00 08 */	beq lbl_800C10A0
/* 800C109C 000BDC7C  38 60 00 01 */	li r3, 1
lbl_800C10A0:
/* 800C10A0 000BDC80  2C 03 00 00 */	cmpwi r3, 0
/* 800C10A4 000BDC84  40 82 00 0C */	bne lbl_800C10B0
/* 800C10A8 000BDC88  7F C3 F3 78 */	mr r3, r30
/* 800C10AC 000BDC8C  48 2B 22 3D */	bl HSD_JObjSetMtxDirtySub
lbl_800C10B0:
/* 800C10B0 000BDC90  80 7F 08 3C */	lwz r3, 0x83c(r31)
/* 800C10B4 000BDC94  38 9F 23 64 */	addi r4, r31, 0x2364
/* 800C10B8 000BDC98  38 A1 00 18 */	addi r5, r1, 0x18
/* 800C10BC 000BDC9C  4B F9 57 05 */	bl mpLib_800567C0
/* 800C10C0 000BDCA0  2C 03 00 00 */	cmpwi r3, 0
/* 800C10C4 000BDCA4  41 82 00 B4 */	beq lbl_800C1178
/* 800C10C8 000BDCA8  38 7F 23 64 */	addi r3, r31, 0x2364
/* 800C10CC 000BDCAC  38 A3 00 00 */	addi r5, r3, 0
/* 800C10D0 000BDCB0  38 81 00 18 */	addi r4, r1, 0x18
/* 800C10D4 000BDCB4  48 28 1C 81 */	bl PSVECAdd
/* 800C10D8 000BDCB8  28 1E 00 00 */	cmplwi r30, 0
/* 800C10DC 000BDCBC  40 82 00 14 */	bne lbl_800C10F0
/* 800C10E0 000BDCC0  38 6D 85 80 */	addi r3, r13, ftCo_804D3C20
/* 800C10E4 000BDCC4  38 80 03 94 */	li r4, 0x394
/* 800C10E8 000BDCC8  38 AD 85 88 */	addi r5, r13, ftCo_804D3C28
/* 800C10EC 000BDCCC  48 2C 71 35 */	bl __assert
lbl_800C10F0:
/* 800C10F0 000BDCD0  34 1F 23 64 */	addic. r0, r31, 0x2364
/* 800C10F4 000BDCD4  40 82 00 18 */	bne lbl_800C110C
/* 800C10F8 000BDCD8  3C 60 80 3C */	lis r3, ftCo_803C6BC8@ha
/* 800C10FC 000BDCDC  38 A3 6B C8 */	addi r5, r3, ftCo_803C6BC8@l
/* 800C1100 000BDCE0  38 6D 85 80 */	addi r3, r13, ftCo_804D3C20
/* 800C1104 000BDCE4  38 80 03 95 */	li r4, 0x395
/* 800C1108 000BDCE8  48 2C 71 19 */	bl __assert
lbl_800C110C:
/* 800C110C 000BDCEC  80 7F 23 64 */	lwz r3, 0x2364(r31)
/* 800C1110 000BDCF0  80 1F 23 68 */	lwz r0, 0x2368(r31)
/* 800C1114 000BDCF4  90 7E 00 38 */	stw r3, 0x38(r30)
/* 800C1118 000BDCF8  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 800C111C 000BDCFC  80 1F 23 6C */	lwz r0, 0x236c(r31)
/* 800C1120 000BDD00  90 1E 00 40 */	stw r0, 0x40(r30)
/* 800C1124 000BDD04  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800C1128 000BDD08  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800C112C 000BDD0C  40 82 00 4C */	bne lbl_800C1178
/* 800C1130 000BDD10  28 1E 00 00 */	cmplwi r30, 0
/* 800C1134 000BDD14  41 82 00 44 */	beq lbl_800C1178
/* 800C1138 000BDD18  40 82 00 14 */	bne lbl_800C114C
/* 800C113C 000BDD1C  38 6D 85 80 */	addi r3, r13, ftCo_804D3C20
/* 800C1140 000BDD20  38 80 02 34 */	li r4, 0x234
/* 800C1144 000BDD24  38 AD 85 88 */	addi r5, r13, ftCo_804D3C28
/* 800C1148 000BDD28  48 2C 70 D9 */	bl __assert
lbl_800C114C:
/* 800C114C 000BDD2C  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800C1150 000BDD30  38 60 00 00 */	li r3, 0
/* 800C1154 000BDD34  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C1158 000BDD38  40 82 00 10 */	bne lbl_800C1168
/* 800C115C 000BDD3C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C1160 000BDD40  41 82 00 08 */	beq lbl_800C1168
/* 800C1164 000BDD44  38 60 00 01 */	li r3, 1
lbl_800C1168:
/* 800C1168 000BDD48  2C 03 00 00 */	cmpwi r3, 0
/* 800C116C 000BDD4C  40 82 00 0C */	bne lbl_800C1178
/* 800C1170 000BDD50  7F C3 F3 78 */	mr r3, r30
/* 800C1174 000BDD54  48 2B 21 75 */	bl HSD_JObjSetMtxDirtySub
lbl_800C1178:
/* 800C1178 000BDD58  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C117C 000BDD5C  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 800C1180 000BDD60  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800C1184 000BDD64  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800C1188 000BDD68  38 21 00 40 */	addi r1, r1, 0x40
/* 800C118C 000BDD6C  7C 08 03 A6 */	mtlr r0
/* 800C1190 000BDD70  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_Bury_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCollisionBox* box = &fp->mv.co.bury.coll_box;
    float mv_x18_x =
        MAX(fp->mv.co.bury.coll_box.right.x, fp->mv.co.bury.coll_box.right.y);
    box->bottom += fp->mv.co.bury.coll_box.right.x;
    if (ftCo_804D8C3C + box->bottom > mv_x18_x) {
        box->bottom = mv_x18_x - ftCo_804D8C3C;
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C1194 000BDD74  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800C1198 000BDD78  38 83 23 44 */	addi r4, r3, 0x2344
/* 800C119C 000BDD7C  C0 43 23 58 */	lfs f2, 0x2358(r3)
/* 800C11A0 000BDD80  C0 03 23 50 */	lfs f0, 0x2350(r3)
/* 800C11A4 000BDD84  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C11A8 000BDD88  40 80 00 08 */	bge lbl_800C11B0
/* 800C11AC 000BDD8C  48 00 00 08 */	b lbl_800C11B4
lbl_800C11B0:
/* 800C11B0 000BDD90  FC 40 00 90 */	fmr f2, f0
lbl_800C11B4:
/* 800C11B4 000BDD94  C0 24 00 04 */	lfs f1, 4(r4)
/* 800C11B8 000BDD98  C0 03 23 5C */	lfs f0, 0x235c(r3)
/* 800C11BC 000BDD9C  EC 01 00 2A */	fadds f0, f1, f0
/* 800C11C0 000BDDA0  D0 04 00 04 */	stfs f0, 4(r4)
/* 800C11C4 000BDDA4  C0 22 92 5C */	lfs f1, ftCo_804D8C3C
/* 800C11C8 000BDDA8  C0 04 00 04 */	lfs f0, 4(r4)
/* 800C11CC 000BDDAC  EC 01 00 2A */	fadds f0, f1, f0
/* 800C11D0 000BDDB0  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800C11D4 000BDDB4  4C 81 00 20 */	blelr
/* 800C11D8 000BDDB8  EC 02 08 28 */	fsubs f0, f2, f1
/* 800C11DC 000BDDBC  D0 04 00 04 */	stfs f0, 4(r4)
/* 800C11E0 000BDDC0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_Bury_Coll(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082888(gobj, &fp->mv.co.bury.coll_box) ||
        fp->mv.co.bury.x20 != fp->coll_data.floor.index ||
        Ground_801C5700(fp->mv.co.bury.x20) != NULL)
    {
        ftCo_800C13BC(gobj);
    }
}

void ftCo_800C124C(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(
        gobj, ftCo_MS_BuryWait,
        Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim, ftCo_804D8C38,
        ftCo_804D8C3C, ftCo_804D8C38, NULL);
    ftCommon_8007E2FC(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221D_b5 = true;
    fp->x2220_flag.bits.b3 = true;
    fp->x2224_b4 = true;
}

void ftCo_BuryWait_Anim(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C -= p_ftCommonData->x610;
    ftCommon_8007DC08(fp, p_ftCommonData->x614);
    if (fp->x1A4C <= ftCo_804D8C38) {
        ftCo_800C13BC(gobj);
    }
}

void ftCo_BuryWait_IASA(ftCo_GObj* gobj) {}

void ftCo_BuryWait_Phys(ftCo_GObj* gobj) {}

ASM void ftCo_BuryWait_Coll(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Bury_Coll(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 800C1354 000BDF34  7C 08 02 A6 */	mflr r0
/* 800C1358 000BDF38  90 01 00 04 */	stw r0, 4(r1)
/* 800C135C 000BDF3C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C1360 000BDF40  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C1364 000BDF44  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800C1368 000BDF48  7C 7E 1B 78 */	mr r30, r3
/* 800C136C 000BDF4C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C1370 000BDF50  38 9F 23 44 */	addi r4, r31, 0x2344
/* 800C1374 000BDF54  4B FC 15 15 */	bl ft_80082888
/* 800C1378 000BDF58  2C 03 00 00 */	cmpwi r3, 0
/* 800C137C 000BDF5C  41 82 00 20 */	beq lbl_800C139C
/* 800C1380 000BDF60  80 7F 23 60 */	lwz r3, 0x2360(r31)
/* 800C1384 000BDF64  80 1F 08 3C */	lwz r0, 0x83c(r31)
/* 800C1388 000BDF68  7C 03 00 00 */	cmpw r3, r0
/* 800C138C 000BDF6C  40 82 00 10 */	bne lbl_800C139C
/* 800C1390 000BDF70  48 10 43 71 */	bl Ground_801C5700
/* 800C1394 000BDF74  28 03 00 00 */	cmplwi r3, 0
/* 800C1398 000BDF78  41 82 00 0C */	beq lbl_800C13A4
lbl_800C139C:
/* 800C139C 000BDF7C  7F C3 F3 78 */	mr r3, r30
/* 800C13A0 000BDF80  48 00 00 1D */	bl ftCo_800C13BC
lbl_800C13A4:
/* 800C13A4 000BDF84  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C13A8 000BDF88  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C13AC 000BDF8C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800C13B0 000BDF90  38 21 00 28 */	addi r1, r1, 0x28
/* 800C13B4 000BDF94  7C 08 03 A6 */	mtlr r0
/* 800C13B8 000BDF98  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C13BC(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCo_800C5240(gobj)) {
        ftCo_800C5A98(gobj);
        return;
    }
    ftCommon_8007D5D4(fp);
    fp->self_vel.x = 0;
    fp->self_vel.y = p_ftCommonData->x618;
    fp->mv.co.buryjump.x0 = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_BuryJump, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftColl_8007B7A4(gobj, p_ftCommonData->x620);
}

#else /* clang-format off */
{ nofralloc
/* 800C13BC 000BDF9C  7C 08 02 A6 */	mflr r0
/* 800C13C0 000BDFA0  90 01 00 04 */	stw r0, 4(r1)
/* 800C13C4 000BDFA4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C13C8 000BDFA8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C13CC 000BDFAC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800C13D0 000BDFB0  7C 7E 1B 78 */	mr r30, r3
/* 800C13D4 000BDFB4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C13D8 000BDFB8  48 00 3E 69 */	bl ftCo_800C5240
/* 800C13DC 000BDFBC  2C 03 00 00 */	cmpwi r3, 0
/* 800C13E0 000BDFC0  41 82 00 10 */	beq lbl_800C13F0
/* 800C13E4 000BDFC4  7F C3 F3 78 */	mr r3, r30
/* 800C13E8 000BDFC8  48 00 46 B1 */	bl ftCo_800C5A98
/* 800C13EC 000BDFCC  48 00 00 5C */	b lbl_800C1448
lbl_800C13F0:
/* 800C13F0 000BDFD0  7F E3 FB 78 */	mr r3, r31
/* 800C13F4 000BDFD4  4B FB C1 E1 */	bl ftCommon_8007D5D4
/* 800C13F8 000BDFD8  C0 22 92 58 */	lfs f1, ftCo_804D8C38
/* 800C13FC 000BDFDC  38 7E 00 00 */	addi r3, r30, 0
/* 800C1400 000BDFE0  38 80 01 28 */	li r4, 0x128
/* 800C1404 000BDFE4  D0 3F 00 80 */	stfs f1, 0x80(r31)
/* 800C1408 000BDFE8  FC 60 08 90 */	fmr f3, f1
/* 800C140C 000BDFEC  38 A0 00 00 */	li r5, 0
/* 800C1410 000BDFF0  80 ED AE B4 */	lwz r7, p_ftCommonData
/* 800C1414 000BDFF4  38 C0 00 00 */	li r6, 0
/* 800C1418 000BDFF8  C0 07 06 18 */	lfs f0, 0x618(r7)
/* 800C141C 000BDFFC  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800C1420 000BE000  D0 3F 23 40 */	stfs f1, 0x2340(r31)
/* 800C1424 000BE004  C0 42 92 5C */	lfs f2, ftCo_804D8C3C
/* 800C1428 000BE008  4B FA 7F 85 */	bl Fighter_ChangeMotionState
/* 800C142C 000BE00C  38 7F 00 00 */	addi r3, r31, 0
/* 800C1430 000BE010  38 80 01 FF */	li r4, 0x1ff
/* 800C1434 000BE014  4B FB CE C1 */	bl ftCommon_8007E2F4
/* 800C1438 000BE018  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C143C 000BE01C  7F C3 F3 78 */	mr r3, r30
/* 800C1440 000BE020  80 84 06 20 */	lwz r4, 0x620(r4)
/* 800C1444 000BE024  4B FB A3 61 */	bl ftColl_8007B7A4
lbl_800C1448:
/* 800C1448 000BE028  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C144C 000BE02C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C1450 000BE030  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800C1454 000BE034  38 21 00 18 */	addi r1, r1, 0x18
/* 800C1458 000BE038  7C 08 03 A6 */	mtlr r0
/* 800C145C 000BE03C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_BuryJump_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.buryjump.x0 += ftCo_804D8C3C;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C1460 000BE040  7C 08 02 A6 */	mflr r0
/* 800C1464 000BE044  90 01 00 04 */	stw r0, 4(r1)
/* 800C1468 000BE048  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C146C 000BE04C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C1470 000BE050  7C 7F 1B 78 */	mr r31, r3
/* 800C1474 000BE054  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800C1478 000BE058  C0 02 92 5C */	lfs f0, ftCo_804D8C3C
/* 800C147C 000BE05C  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 800C1480 000BE060  EC 01 00 2A */	fadds f0, f1, f0
/* 800C1484 000BE064  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 800C1488 000BE068  4B FA DD B1 */	bl ftAnim_IsFramesRemaining
/* 800C148C 000BE06C  2C 03 00 00 */	cmpwi r3, 0
/* 800C1490 000BE070  40 82 00 0C */	bne lbl_800C149C
/* 800C1494 000BE074  7F E3 FB 78 */	mr r3, r31
/* 800C1498 000BE078  48 00 B2 99 */	bl ftCo_800CC730
lbl_800C149C:
/* 800C149C 000BE07C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C14A0 000BE080  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C14A4 000BE084  38 21 00 20 */	addi r1, r1, 0x20
/* 800C14A8 000BE088  7C 08 03 A6 */	mtlr r0
/* 800C14AC 000BE08C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_BuryJump_IASA(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ca.specials.grav >= p_ftCommonData->x61C) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, NULL));
        RETURN_IF(ftCo_800D7100(gobj));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_80099A58(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
        RETURN_IF(ftCo_800D705C(gobj));
        RETURN_IF(ftCo_800CB870(gobj));
    }
}

void ftCo_BuryJump_Phys(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D494(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
    ftCommon_8007D268(fp);
}

void ftCo_BuryJump_Coll(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->self_vel.y >= ftCo_804D8C38) {
        ft_80082D40(gobj, fp->self_vel.y);
    } else {
        ftCo_AirCatchHit_Coll(gobj);
    }
}
