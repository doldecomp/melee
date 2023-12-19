#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CaptureKirby.h"

#include "ftCo_Lift.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"

#include <math.h>
#include <placeholder.h>
#include <baselib/jobj.h>

float ftCo_800BD19C(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = gobj->user_data;
    return SQ(fp->cur_pos.x - pos->x) + SQ(fp->cur_pos.y - pos->y) +
           SQ(fp->cur_pos.z - pos->z);
}

float const ftCo_804D8BA8 = 0;
float const ftCo_804D8BAC = 1;
double const ftCo_804D8BB0 = S32_TO_F32;

static inline void foo(Fighter_GObj* gobj, float arg1) {}
static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 vec0;
    Vec2 vec1;
    {
        fp->mv.co.capturekirby.x8.x = ftKb_SpecialN_800F5B4C(fp->victim_gobj);
        fp->mv.co.capturekirby.x8.y = ftKb_SpecialN_800F5B3C(fp->victim_gobj);
        ftKb_SpecialN_800F5B5C(fp->victim_gobj);
        {
            fp->mv.co.capturekirby.pos_offset.x = fp->cur_pos.x - vec0.x;
            fp->mv.co.capturekirby.pos_offset.y = fp->cur_pos.y - vec0.y;
        }
        ftKb_SpecialN_800F5B20(fp->victim_gobj);
        {
            Vec3* scale = &fp->mv.co.capturekirby.scale;
            fp->mv.co.capturekirby.x10.x = vec1.x;
            fp->mv.co.capturekirby.x10.y = vec1.y;
            HSD_JObjGetScale(jobj, scale);
        }
        fp->x2226_b2 = true;
        ftCommon_8007DBCC(fp, 0, ftKb_SpecialN_800F5AF0(fp->victim_gobj));
    }
}

ASM void ftCo_800BD1DC(Fighter_GObj* gobj, Fighter_GObj* victim_gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(victim_gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = victim_gobj;
    fp->victim_gobj = victim_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = -victim_fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureKirby, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007D5D4(fp);
    inlineA0(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007EBAC(fp, 1, 0);
    ftCommon_8007E2FC(gobj);
    fp->accessory1_cb = ftCo_800BD39C;
}

#else /* clang-format off */
{ nofralloc
/* 800BD1DC 000B9DBC  7C 08 02 A6 */	mflr r0
/* 800BD1E0 000B9DC0  90 01 00 04 */	stw r0, 4(r1)
/* 800BD1E4 000B9DC4  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800BD1E8 000B9DC8  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 800BD1EC 000B9DCC  3B 63 00 00 */	addi r27, r3, 0
/* 800BD1F0 000B9DD0  3B C4 00 00 */	addi r30, r4, 0
/* 800BD1F4 000B9DD4  83 83 00 2C */	lwz r28, 0x2c(r3)
/* 800BD1F8 000B9DD8  83 A4 00 2C */	lwz r29, 0x2c(r4)
/* 800BD1FC 000B9DDC  4B FC 09 5D */	bl ftCommon_8007DB58
/* 800BD200 000B9DE0  7F 63 DB 78 */	mr r3, r27
/* 800BD204 000B9DE4  4B FD A3 09 */	bl ftCo_8009750C
/* 800BD208 000B9DE8  7F 63 DB 78 */	mr r3, r27
/* 800BD20C 000B9DEC  48 01 FF 5D */	bl ftCo_800DD168
/* 800BD210 000B9DF0  93 DC 1A 5C */	stw r30, 0x1a5c(r28)
/* 800BD214 000B9DF4  38 E0 00 00 */	li r7, 0
/* 800BD218 000B9DF8  38 7B 00 00 */	addi r3, r27, 0
/* 800BD21C 000B9DFC  93 DC 1A 58 */	stw r30, 0x1a58(r28)
/* 800BD220 000B9E00  38 80 01 20 */	li r4, 0x120
/* 800BD224 000B9E04  38 A0 00 00 */	li r5, 0
/* 800BD228 000B9E08  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 800BD22C 000B9E0C  50 E0 17 7A */	rlwimi r0, r7, 2, 0x1d, 0x1d
/* 800BD230 000B9E10  38 C0 00 00 */	li r6, 0
/* 800BD234 000B9E14  98 1C 22 1B */	stb r0, 0x221b(r28)
/* 800BD238 000B9E18  88 1C 22 1B */	lbz r0, 0x221b(r28)
/* 800BD23C 000B9E1C  50 E0 07 FE */	rlwimi r0, r7, 0, 0x1f, 0x1f
/* 800BD240 000B9E20  98 1C 22 1B */	stb r0, 0x221b(r28)
/* 800BD244 000B9E24  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 800BD248 000B9E28  FC 00 00 50 */	fneg f0, f0
/* 800BD24C 000B9E2C  D0 1C 00 2C */	stfs f0, 0x2c(r28)
/* 800BD250 000B9E30  C0 22 91 C8 */	lfs f1, ftCo_804D8BA8
/* 800BD254 000B9E34  C0 42 91 CC */	lfs f2, ftCo_804D8BAC
/* 800BD258 000B9E38  FC 60 08 90 */	fmr f3, f1
/* 800BD25C 000B9E3C  4B FA C1 51 */	bl Fighter_ChangeMotionState
/* 800BD260 000B9E40  7F 83 E3 78 */	mr r3, r28
/* 800BD264 000B9E44  4B FC 03 71 */	bl ftCommon_8007D5D4
/* 800BD268 000B9E48  83 DB 00 2C */	lwz r30, 0x2c(r27)
/* 800BD26C 000B9E4C  83 FB 00 28 */	lwz r31, 0x28(r27)
/* 800BD270 000B9E50  80 7E 1A 58 */	lwz r3, 0x1a58(r30)
/* 800BD274 000B9E54  48 03 88 D9 */	bl ftKb_SpecialN_800F5B4C
/* 800BD278 000B9E58  D0 3E 23 48 */	stfs f1, 0x2348(r30)
/* 800BD27C 000B9E5C  80 7E 1A 58 */	lwz r3, 0x1a58(r30)
/* 800BD280 000B9E60  48 03 88 BD */	bl ftKb_SpecialN_800F5B3C
/* 800BD284 000B9E64  D0 3E 23 4C */	stfs f1, 0x234c(r30)
/* 800BD288 000B9E68  38 81 00 24 */	addi r4, r1, 0x24
/* 800BD28C 000B9E6C  80 7E 1A 58 */	lwz r3, 0x1a58(r30)
/* 800BD290 000B9E70  48 03 88 CD */	bl ftKb_SpecialN_800F5B5C
/* 800BD294 000B9E74  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 800BD298 000B9E78  38 81 00 30 */	addi r4, r1, 0x30
/* 800BD29C 000B9E7C  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800BD2A0 000B9E80  EC 01 00 28 */	fsubs f0, f1, f0
/* 800BD2A4 000B9E84  D0 1E 23 40 */	stfs f0, 0x2340(r30)
/* 800BD2A8 000B9E88  C0 3E 00 B4 */	lfs f1, 0xb4(r30)
/* 800BD2AC 000B9E8C  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 800BD2B0 000B9E90  EC 01 00 28 */	fsubs f0, f1, f0
/* 800BD2B4 000B9E94  D0 1E 23 44 */	stfs f0, 0x2344(r30)
/* 800BD2B8 000B9E98  80 7E 1A 58 */	lwz r3, 0x1a58(r30)
/* 800BD2BC 000B9E9C  48 03 88 65 */	bl ftKb_SpecialN_800F5B20
/* 800BD2C0 000B9EA0  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 800BD2C4 000B9EA4  28 1F 00 00 */	cmplwi r31, 0
/* 800BD2C8 000B9EA8  3B BE 23 6C */	addi r29, r30, 0x236c
/* 800BD2CC 000B9EAC  D0 1E 23 50 */	stfs f0, 0x2350(r30)
/* 800BD2D0 000B9EB0  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 800BD2D4 000B9EB4  D0 1E 23 54 */	stfs f0, 0x2354(r30)
/* 800BD2D8 000B9EB8  40 82 00 14 */	bne lbl_800BD2EC
/* 800BD2DC 000B9EBC  38 6D 85 10 */	addi r3, r13, ftCo_804D3BB0
/* 800BD2E0 000B9EC0  38 80 03 37 */	li r4, 0x337
/* 800BD2E4 000B9EC4  38 AD 85 18 */	addi r5, r13, ftCo_804D3BB8
/* 800BD2E8 000B9EC8  48 2C AF 39 */	bl __assert
lbl_800BD2EC:
/* 800BD2EC 000B9ECC  28 1D 00 00 */	cmplwi r29, 0
/* 800BD2F0 000B9ED0  40 82 00 14 */	bne lbl_800BD304
/* 800BD2F4 000B9ED4  38 6D 85 10 */	addi r3, r13, ftCo_804D3BB0
/* 800BD2F8 000B9ED8  38 80 03 38 */	li r4, 0x338
/* 800BD2FC 000B9EDC  38 AD 85 20 */	addi r5, r13, ftCo_804D3BC0
/* 800BD300 000B9EE0  48 2C AF 21 */	bl __assert
lbl_800BD304:
/* 800BD304 000B9EE4  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 800BD308 000B9EE8  38 60 00 01 */	li r3, 1
/* 800BD30C 000B9EEC  80 1F 00 30 */	lwz r0, 0x30(r31)
/* 800BD310 000B9EF0  90 9D 00 00 */	stw r4, 0(r29)
/* 800BD314 000B9EF4  90 1D 00 04 */	stw r0, 4(r29)
/* 800BD318 000B9EF8  80 1F 00 34 */	lwz r0, 0x34(r31)
/* 800BD31C 000B9EFC  90 1D 00 08 */	stw r0, 8(r29)
/* 800BD320 000B9F00  88 1E 22 26 */	lbz r0, 0x2226(r30)
/* 800BD324 000B9F04  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 800BD328 000B9F08  98 1E 22 26 */	stb r0, 0x2226(r30)
/* 800BD32C 000B9F0C  80 7C 1A 58 */	lwz r3, 0x1a58(r28)
/* 800BD330 000B9F10  48 03 87 C1 */	bl ftKb_SpecialN_800F5AF0
/* 800BD334 000B9F14  38 7C 00 00 */	addi r3, r28, 0
/* 800BD338 000B9F18  38 80 00 00 */	li r4, 0
/* 800BD33C 000B9F1C  4B FC 08 91 */	bl ftCommon_8007DBCC
/* 800BD340 000B9F20  38 7C 00 00 */	addi r3, r28, 0
/* 800BD344 000B9F24  38 80 01 FF */	li r4, 0x1ff
/* 800BD348 000B9F28  4B FC 0F AD */	bl ftCommon_8007E2F4
/* 800BD34C 000B9F2C  7F 63 DB 78 */	mr r3, r27
/* 800BD350 000B9F30  4B FB 18 55 */	bl ftAnim_8006EBA4
/* 800BD354 000B9F34  38 7C 00 00 */	addi r3, r28, 0
/* 800BD358 000B9F38  38 80 00 01 */	li r4, 1
/* 800BD35C 000B9F3C  38 A0 00 00 */	li r5, 0
/* 800BD360 000B9F40  4B FC 18 4D */	bl ftCommon_8007EBAC
/* 800BD364 000B9F44  7F 63 DB 78 */	mr r3, r27
/* 800BD368 000B9F48  4B FC 0F 95 */	bl ftCommon_8007E2FC
/* 800BD36C 000B9F4C  3C 60 80 0C */	lis r3, ftCo_800BD39C@ha
/* 800BD370 000B9F50  38 03 D3 9C */	addi r0, r3, ftCo_800BD39C@l
/* 800BD374 000B9F54  90 1C 21 B0 */	stw r0, 0x21b0(r28)
/* 800BD378 000B9F58  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800BD37C 000B9F5C  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 800BD380 000B9F60  38 21 00 58 */	addi r1, r1, 0x58
/* 800BD384 000B9F64  7C 08 03 A6 */	mtlr r0
/* 800BD388 000B9F68  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_CaptureKirby_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureKirby_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureKirby_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureKirby_Coll(HSD_GObj* gobj) {}

static inline void inlineB0(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float pos_x = pos->x;
    float pos_y = pos->y;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    float dist = sqrtf__Ff(SQ(pos_x) + SQ(pos_y) + SQ(pos->z));
    float mv_x8_x = fp->mv.co.capturekirby.x8.x;
    if (dist < mv_x8_x) {
        float mv_x8_y = fp->mv.co.capturekirby.x8.y;
        Vec3 scale;
        scale.x = scale.y = scale.z = 1 - mv_x8_y + dist / mv_x8_x * mv_x8_y;
        scale.x = scale.x * fp->mv.co.guard.x2C;
        scale.y *= fp->mv.co.capturekirby.scale.y;
        scale.z *= fp->mv.co.capturekirby.scale.z;
        HSD_JObjSetScale(jobj, &scale);
    }
}

static inline void inlineB1(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ABS(pos->x) > fp->mv.co.capturekirby.x10.x) {
        pos->x = fp->mv.co.capturekirby.x10.x * (pos->x < 0 ? -1 : +1);
    }
    if (ABS(pos->y) > fp->mv.co.capturekirby.x10.y) {
        pos->y = fp->mv.co.capturekirby.x10.y * (pos->y < 0 ? -1 : +1);
    }
    fp->mv.co.capturekirby.pos_offset.x -= pos->x;
    fp->mv.co.capturekirby.pos_offset.y -= pos->y;
    ftKb_SpecialN_800F5B5C(fp->victim_gobj);
    fp->cur_pos.x = pos->x + fp->mv.co.capturekirby.pos_offset.x;
    fp->cur_pos.y = pos->y + fp->mv.co.capturekirby.pos_offset.y;
    fp->cur_pos.z = pos->z;
}

ASM void ftCo_800BD39C(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    pos.x = fp->mv.co.capturekirby.pos_offset.x;
    pos.y = fp->mv.co.capturekirby.pos_offset.y;
    pos.z = 0;
    inlineB0(gobj, &pos);
    inlineB1(gobj, &pos);
}

#else /* clang-format off */
{ nofralloc
/* 800BD39C 000B9F7C  7C 08 02 A6 */	mflr r0
/* 800BD3A0 000B9F80  90 01 00 04 */	stw r0, 4(r1)
/* 800BD3A4 000B9F84  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800BD3A8 000B9F88  93 E1 00 54 */	stw r31, 0x54(r1)
/* 800BD3AC 000B9F8C  93 C1 00 50 */	stw r30, 0x50(r1)
/* 800BD3B0 000B9F90  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 800BD3B4 000B9F94  7C 7D 1B 78 */	mr r29, r3
/* 800BD3B8 000B9F98  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800BD3BC 000B9F9C  C0 03 23 40 */	lfs f0, 0x2340(r3)
/* 800BD3C0 000B9FA0  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800BD3C4 000B9FA4  C0 03 23 44 */	lfs f0, 0x2344(r3)
/* 800BD3C8 000B9FA8  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800BD3CC 000B9FAC  C0 02 91 C8 */	lfs f0, ftCo_804D8BA8
/* 800BD3D0 000B9FB0  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 800BD3D4 000B9FB4  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 800BD3D8 000B9FB8  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 800BD3DC 000B9FBC  EC 21 00 72 */	fmuls f1, f1, f1
/* 800BD3E0 000B9FC0  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 800BD3E4 000B9FC4  EC 00 00 32 */	fmuls f0, f0, f0
/* 800BD3E8 000B9FC8  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 800BD3EC 000B9FCC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800BD3F0 000B9FD0  EC 01 00 2A */	fadds f0, f1, f0
/* 800BD3F4 000B9FD4  83 DD 00 28 */	lwz r30, 0x28(r29)
/* 800BD3F8 000B9FD8  EC 22 00 2A */	fadds f1, f2, f0
/* 800BD3FC 000B9FDC  4B F5 01 C1 */	bl sqrtf__Ff
/* 800BD400 000B9FE0  C0 1F 23 48 */	lfs f0, 0x2348(r31)
/* 800BD404 000B9FE4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD408 000B9FE8  40 80 00 DC */	bge lbl_800BD4E4
/* 800BD40C 000B9FEC  EC 21 00 24 */	fdivs f1, f1, f0
/* 800BD410 000B9FF0  C0 5F 23 4C */	lfs f2, 0x234c(r31)
/* 800BD414 000B9FF4  C0 02 91 CC */	lfs f0, ftCo_804D8BAC
/* 800BD418 000B9FF8  28 1E 00 00 */	cmplwi r30, 0
/* 800BD41C 000B9FFC  EC 21 00 B2 */	fmuls f1, f1, f2
/* 800BD420 000BA000  EC 00 10 28 */	fsubs f0, f0, f2
/* 800BD424 000BA004  EC 00 08 2A */	fadds f0, f0, f1
/* 800BD428 000BA008  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800BD42C 000BA00C  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800BD430 000BA010  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800BD434 000BA014  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 800BD438 000BA018  C0 1F 23 6C */	lfs f0, 0x236c(r31)
/* 800BD43C 000BA01C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BD440 000BA020  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800BD444 000BA024  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 800BD448 000BA028  C0 1F 23 70 */	lfs f0, 0x2370(r31)
/* 800BD44C 000BA02C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BD450 000BA030  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800BD454 000BA034  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 800BD458 000BA038  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 800BD45C 000BA03C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BD460 000BA040  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800BD464 000BA044  40 82 00 14 */	bne lbl_800BD478
/* 800BD468 000BA048  38 6D 85 10 */	addi r3, r13, ftCo_804D3BB0
/* 800BD46C 000BA04C  38 80 02 F8 */	li r4, 0x2f8
/* 800BD470 000BA050  38 AD 85 18 */	addi r5, r13, ftCo_804D3BB8
/* 800BD474 000BA054  48 2C AD AD */	bl __assert
lbl_800BD478:
/* 800BD478 000BA058  80 61 00 24 */	lwz r3, 0x24(r1)
/* 800BD47C 000BA05C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 800BD480 000BA060  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 800BD484 000BA064  90 1E 00 30 */	stw r0, 0x30(r30)
/* 800BD488 000BA068  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BD48C 000BA06C  90 1E 00 34 */	stw r0, 0x34(r30)
/* 800BD490 000BA070  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800BD494 000BA074  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BD498 000BA078  40 82 00 4C */	bne lbl_800BD4E4
/* 800BD49C 000BA07C  28 1E 00 00 */	cmplwi r30, 0
/* 800BD4A0 000BA080  41 82 00 44 */	beq lbl_800BD4E4
/* 800BD4A4 000BA084  40 82 00 14 */	bne lbl_800BD4B8
/* 800BD4A8 000BA088  38 6D 85 10 */	addi r3, r13, ftCo_804D3BB0
/* 800BD4AC 000BA08C  38 80 02 34 */	li r4, 0x234
/* 800BD4B0 000BA090  38 AD 85 18 */	addi r5, r13, ftCo_804D3BB8
/* 800BD4B4 000BA094  48 2C AD 6D */	bl __assert
lbl_800BD4B8:
/* 800BD4B8 000BA098  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800BD4BC 000BA09C  38 60 00 00 */	li r3, 0
/* 800BD4C0 000BA0A0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BD4C4 000BA0A4  40 82 00 10 */	bne lbl_800BD4D4
/* 800BD4C8 000BA0A8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BD4CC 000BA0AC  41 82 00 08 */	beq lbl_800BD4D4
/* 800BD4D0 000BA0B0  38 60 00 01 */	li r3, 1
lbl_800BD4D4:
/* 800BD4D4 000BA0B4  2C 03 00 00 */	cmpwi r3, 0
/* 800BD4D8 000BA0B8  40 82 00 0C */	bne lbl_800BD4E4
/* 800BD4DC 000BA0BC  7F C3 F3 78 */	mr r3, r30
/* 800BD4E0 000BA0C0  48 2B 5E 09 */	bl HSD_JObjSetMtxDirtySub
lbl_800BD4E4:
/* 800BD4E4 000BA0C4  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 800BD4E8 000BA0C8  C0 02 91 C8 */	lfs f0, ftCo_804D8BA8
/* 800BD4EC 000BA0CC  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 800BD4F0 000BA0D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD4F4 000BA0D4  40 80 00 0C */	bge lbl_800BD500
/* 800BD4F8 000BA0D8  FC 00 08 50 */	fneg f0, f1
/* 800BD4FC 000BA0DC  48 00 00 08 */	b lbl_800BD504
lbl_800BD500:
/* 800BD500 000BA0E0  FC 00 08 90 */	fmr f0, f1
lbl_800BD504:
/* 800BD504 000BA0E4  C0 5F 23 50 */	lfs f2, 0x2350(r31)
/* 800BD508 000BA0E8  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800BD50C 000BA0EC  40 81 00 40 */	ble lbl_800BD54C
/* 800BD510 000BA0F0  C0 02 91 C8 */	lfs f0, ftCo_804D8BA8
/* 800BD514 000BA0F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD518 000BA0F8  40 80 00 0C */	bge lbl_800BD524
/* 800BD51C 000BA0FC  38 00 FF FF */	li r0, -1
/* 800BD520 000BA100  48 00 00 08 */	b lbl_800BD528
lbl_800BD524:
/* 800BD524 000BA104  38 00 00 01 */	li r0, 1
lbl_800BD528:
/* 800BD528 000BA108  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BD52C 000BA10C  C8 22 91 D0 */	lfd f1, ftCo_804D8BB0
/* 800BD530 000BA110  90 01 00 44 */	stw r0, 0x44(r1)
/* 800BD534 000BA114  3C 00 43 30 */	lis r0, 0x4330
/* 800BD538 000BA118  90 01 00 40 */	stw r0, 0x40(r1)
/* 800BD53C 000BA11C  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 800BD540 000BA120  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BD544 000BA124  EC 02 00 32 */	fmuls f0, f2, f0
/* 800BD548 000BA128  D0 01 00 34 */	stfs f0, 0x34(r1)
lbl_800BD54C:
/* 800BD54C 000BA12C  C0 21 00 38 */	lfs f1, 0x38(r1)
/* 800BD550 000BA130  C0 02 91 C8 */	lfs f0, ftCo_804D8BA8
/* 800BD554 000BA134  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD558 000BA138  40 80 00 0C */	bge lbl_800BD564
/* 800BD55C 000BA13C  FC 00 08 50 */	fneg f0, f1
/* 800BD560 000BA140  48 00 00 08 */	b lbl_800BD568
lbl_800BD564:
/* 800BD564 000BA144  FC 00 08 90 */	fmr f0, f1
lbl_800BD568:
/* 800BD568 000BA148  C0 5F 23 54 */	lfs f2, 0x2354(r31)
/* 800BD56C 000BA14C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800BD570 000BA150  40 81 00 40 */	ble lbl_800BD5B0
/* 800BD574 000BA154  C0 02 91 C8 */	lfs f0, ftCo_804D8BA8
/* 800BD578 000BA158  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BD57C 000BA15C  40 80 00 0C */	bge lbl_800BD588
/* 800BD580 000BA160  38 00 FF FF */	li r0, -1
/* 800BD584 000BA164  48 00 00 08 */	b lbl_800BD58C
lbl_800BD588:
/* 800BD588 000BA168  38 00 00 01 */	li r0, 1
lbl_800BD58C:
/* 800BD58C 000BA16C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BD590 000BA170  C8 22 91 D0 */	lfd f1, ftCo_804D8BB0
/* 800BD594 000BA174  90 01 00 44 */	stw r0, 0x44(r1)
/* 800BD598 000BA178  3C 00 43 30 */	lis r0, 0x4330
/* 800BD59C 000BA17C  90 01 00 40 */	stw r0, 0x40(r1)
/* 800BD5A0 000BA180  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 800BD5A4 000BA184  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BD5A8 000BA188  EC 02 00 32 */	fmuls f0, f2, f0
/* 800BD5AC 000BA18C  D0 01 00 38 */	stfs f0, 0x38(r1)
lbl_800BD5B0:
/* 800BD5B0 000BA190  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 800BD5B4 000BA194  38 81 00 34 */	addi r4, r1, 0x34
/* 800BD5B8 000BA198  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 800BD5BC 000BA19C  EC 01 00 28 */	fsubs f0, f1, f0
/* 800BD5C0 000BA1A0  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 800BD5C4 000BA1A4  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 800BD5C8 000BA1A8  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 800BD5CC 000BA1AC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800BD5D0 000BA1B0  D0 1F 23 44 */	stfs f0, 0x2344(r31)
/* 800BD5D4 000BA1B4  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 800BD5D8 000BA1B8  48 03 85 85 */	bl ftKb_SpecialN_800F5B5C
/* 800BD5DC 000BA1BC  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 800BD5E0 000BA1C0  C0 1F 23 40 */	lfs f0, 0x2340(r31)
/* 800BD5E4 000BA1C4  EC 01 00 2A */	fadds f0, f1, f0
/* 800BD5E8 000BA1C8  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 800BD5EC 000BA1CC  C0 21 00 38 */	lfs f1, 0x38(r1)
/* 800BD5F0 000BA1D0  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800BD5F4 000BA1D4  EC 01 00 2A */	fadds f0, f1, f0
/* 800BD5F8 000BA1D8  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
/* 800BD5FC 000BA1DC  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 800BD600 000BA1E0  D0 1F 00 B8 */	stfs f0, 0xb8(r31)
/* 800BD604 000BA1E4  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800BD608 000BA1E8  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 800BD60C 000BA1EC  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 800BD610 000BA1F0  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 800BD614 000BA1F4  38 21 00 58 */	addi r1, r1, 0x58
/* 800BD618 000BA1F8  7C 08 03 A6 */	mtlr r0
/* 800BD61C 000BA1FC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
