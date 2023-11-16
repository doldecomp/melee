#include <platform.h>
#include "ft/forward.h"
#include "lb/forward.h"

#include "ftCo_BarrelWait.h"

#include "ftCo_09CB.h"
#include "ftCo_Damage.h"
#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "gr/ground.h"
#include "mp/mpcoll.h"

#include <placeholder.h>

#if defined(MWERKS_GEKKO) && defined(WIP)
#pragma force_active on
#endif

static inline void setCamData(ftCommonData* cd, CameraBox* cam)
{
    cam->x40 = cd->x4DC;
    cam->x48 = cd->x4E4;
}

void ftCo_8009EB18(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_BarrelWait, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->death2_cb = ftCo_8009EAF8;
    fp->accessory1_cb = ftCo_8009EC44;
    ftCommon_8007E2FC(gobj);
    fp->x1988 = 2;
    fp->x221E_b0 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    setCamData(p_ftCommonData, fp->x890_cameraBox);
    ftCommon_8007EFC0(fp, 1);
}

void ftCo_BarrelWait_Anim(ftCo_GObj* gobj) {}

void ftCo_BarrelWait_IASA(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->input.x668 & HSD_PAD_AB) {
        Ground_801C4DD0();
    }
}

void ftCo_BarrelWait_Phys(ftCo_GObj* gobj) {}

void ftCo_BarrelWait_Coll(ftCo_GObj* gobj) {}

void ftCo_8009EC44(ftCo_GObj* gobj)
{
    float param;
/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif
    Ground_801C4DA0(&GET_FIGHTER(gobj)->cur_pos, &param);
}

ASM void ftCo_8009EC70(ftCo_GObj* gobj, Vec3* pos, UNK_T arg2, float kb_angle)
#if !defined(MUST_MATCH) || defined(WIP)
{
    HitCapsule hit;
    Fighter* fp = gobj->user_data;
    fp->bury_timer_2 = p_ftCommonData->bury_timer_unk2;
    fp->cur_pos = *pos;
    mpColl_80043680(&fp->coll_data, pos);
    ftCamera_80076064(fp);
    lbColl_80008D30(&hit, arg2);
    ftColl_800788D4(gobj);
    if (kb_angle < 0) {
        kb_angle += 360;
    }
    kb_angle = fp->facing_dir < 0 ? kb_angle : 180 - kb_angle;
    fp->dmg.kb_applied = ftColl_80079EA8(fp, &hit, hit.x8);
    fp->dmg.x1848_kb_angle = kb_angle;
    fp->dmg.x1844_direction = fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 0;
    fp->dmg.x1854_collpos = fp->cur_pos;
    fp->dmg.x1860 = hit.element;
    Fighter_UnkTakeDamage_8006CC30(fp, hit.damage);
    ftCo_8008DCE0(gobj, 91, 0);
}
#else /* clang-format off */
{ nofralloc
/* 8009EC70 0009B850  7C 08 02 A6 */	mflr r0
/* 8009EC74 0009B854  90 01 00 04 */	stw r0, 4(r1)
/* 8009EC78 0009B858  94 21 FE 90 */	stwu r1, -0x170(r1)
/* 8009EC7C 0009B85C  DB E1 01 68 */	stfd f31, 0x168(r1)
/* 8009EC80 0009B860  FF E0 08 90 */	fmr f31, f1
/* 8009EC84 0009B864  93 E1 01 64 */	stw r31, 0x164(r1)
/* 8009EC88 0009B868  93 C1 01 60 */	stw r30, 0x160(r1)
/* 8009EC8C 0009B86C  7C BE 2B 78 */	mr r30, r5
/* 8009EC90 0009B870  93 A1 01 5C */	stw r29, 0x15c(r1)
/* 8009EC94 0009B874  7C 7D 1B 78 */	mr r29, r3
/* 8009EC98 0009B878  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 8009EC9C 0009B87C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009ECA0 0009B880  80 06 05 E0 */	lwz r0, 0x5e0(r6)
/* 8009ECA4 0009B884  38 7F 06 F0 */	addi r3, r31, 0x6f0
/* 8009ECA8 0009B888  90 1F 23 2C */	stw r0, 0x232c(r31)
/* 8009ECAC 0009B88C  80 A4 00 00 */	lwz r5, 0(r4)
/* 8009ECB0 0009B890  80 04 00 04 */	lwz r0, 4(r4)
/* 8009ECB4 0009B894  90 BF 00 B0 */	stw r5, 0xb0(r31)
/* 8009ECB8 0009B898  90 1F 00 B4 */	stw r0, 0xb4(r31)
/* 8009ECBC 0009B89C  80 04 00 08 */	lwz r0, 8(r4)
/* 8009ECC0 0009B8A0  90 1F 00 B8 */	stw r0, 0xb8(r31)
/* 8009ECC4 0009B8A4  4B FA 49 BD */	bl mpColl_80043680
/* 8009ECC8 0009B8A8  7F E3 FB 78 */	mr r3, r31
/* 8009ECCC 0009B8AC  4B FD 73 99 */	bl ftCamera_80076064
/* 8009ECD0 0009B8B0  38 61 00 1C */	addi r3, r1, 0x1c
/* 8009ECD4 0009B8B4  38 9E 00 00 */	addi r4, r30, 0
/* 8009ECD8 0009B8B8  4B F6 A0 59 */	bl lbColl_80008D30
/* 8009ECDC 0009B8BC  7F A3 EB 78 */	mr r3, r29
/* 8009ECE0 0009B8C0  4B FD 9B F5 */	bl ftColl_800788D4
/* 8009ECE4 0009B8C4  C0 02 8D 90 */	lfs f0, 0.0f
/* 8009ECE8 0009B8C8  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8009ECEC 0009B8CC  40 80 00 0C */	bge lbl_8009ECF8
/* 8009ECF0 0009B8D0  C0 02 8D 98 */	lfs f0, 360.0f
/* 8009ECF4 0009B8D4  EF FF 00 2A */	fadds f31, f31, f0
lbl_8009ECF8:
/* 8009ECF8 0009B8D8  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8009ECFC 0009B8DC  C0 02 8D 90 */	lfs f0, 0.0f
/* 8009ED00 0009B8E0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009ED04 0009B8E4  40 80 00 08 */	bge lbl_8009ED0C
/* 8009ED08 0009B8E8  48 00 00 0C */	b lbl_8009ED14
lbl_8009ED0C:
/* 8009ED0C 0009B8EC  C0 02 8D 9C */	lfs f0, 180.0f
/* 8009ED10 0009B8F0  EF E0 F8 28 */	fsubs f31, f0, f31
lbl_8009ED14:
/* 8009ED14 0009B8F4  80 A1 00 24 */	lwz r5, 0x24(r1)
/* 8009ED18 0009B8F8  38 7F 00 00 */	addi r3, r31, 0
/* 8009ED1C 0009B8FC  38 81 00 1C */	addi r4, r1, 0x1c
/* 8009ED20 0009B900  4B FD B1 89 */	bl ftColl_80079EA8
/* 8009ED24 0009B904  FC 00 F8 1E */	fctiwz f0, f31
/* 8009ED28 0009B908  D0 3F 18 50 */	stfs f1, 0x1850(r31)
/* 8009ED2C 0009B90C  38 00 00 00 */	li r0, 0
/* 8009ED30 0009B910  38 7F 00 00 */	addi r3, r31, 0
/* 8009ED34 0009B914  D8 01 01 50 */	stfd f0, 0x150(r1)
/* 8009ED38 0009B918  80 81 01 54 */	lwz r4, 0x154(r1)
/* 8009ED3C 0009B91C  90 9F 18 48 */	stw r4, 0x1848(r31)
/* 8009ED40 0009B920  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8009ED44 0009B924  D0 1F 18 44 */	stfs f0, 0x1844(r31)
/* 8009ED48 0009B928  90 1F 18 4C */	stw r0, 0x184c(r31)
/* 8009ED4C 0009B92C  80 9F 00 B0 */	lwz r4, 0xb0(r31)
/* 8009ED50 0009B930  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 8009ED54 0009B934  90 9F 18 54 */	stw r4, 0x1854(r31)
/* 8009ED58 0009B938  90 1F 18 58 */	stw r0, 0x1858(r31)
/* 8009ED5C 0009B93C  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 8009ED60 0009B940  90 1F 18 5C */	stw r0, 0x185c(r31)
/* 8009ED64 0009B944  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8009ED68 0009B948  90 1F 18 60 */	stw r0, 0x1860(r31)
/* 8009ED6C 0009B94C  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 8009ED70 0009B950  4B FC DE C1 */	bl Fighter_UnkTakeDamage_8006CC30
/* 8009ED74 0009B954  C0 22 8D 90 */	lfs f1, 0.0f
/* 8009ED78 0009B958  38 7D 00 00 */	addi r3, r29, 0
/* 8009ED7C 0009B95C  38 80 00 5B */	li r4, 0x5b
/* 8009ED80 0009B960  4B FE EF 61 */	bl ftCo_8008DCE0
/* 8009ED84 0009B964  80 01 01 74 */	lwz r0, 0x174(r1)
/* 8009ED88 0009B968  CB E1 01 68 */	lfd f31, 0x168(r1)
/* 8009ED8C 0009B96C  83 E1 01 64 */	lwz r31, 0x164(r1)
/* 8009ED90 0009B970  83 C1 01 60 */	lwz r30, 0x160(r1)
/* 8009ED94 0009B974  83 A1 01 5C */	lwz r29, 0x15c(r1)
/* 8009ED98 0009B978  38 21 01 70 */	addi r1, r1, 0x170
/* 8009ED9C 0009B97C  7C 08 03 A6 */	mtlr r0
/* 8009EDA0 0009B980  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
