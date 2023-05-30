#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CargoThrow.h"

#include "ftCo_CargoFall.h"
#include "ftCo_CargoWait.h"
#include "ftCo_Damage.h"

#include "ft/ft_081B.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

/* 09C02C */ static bool ftCo_8009C02C(ftCo_GObj* gobj, FtMotionId msid);
/* 09C170 */ static void ftCo_8009C170(ftCo_GObj* gobj);
/* 09C45C */ static void ftCo_8009C45C(ftCo_GObj* gobj, float lag);

void ftCo_CargoWait2_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_8008F744(gobj);
    if (!fp->x221C_b6) {
        if (fp->ground_or_air == GA_Air) {
            ftCo_8009BC58(gobj);
        } else {
            ftCo_8009B518(gobj);
        }
    }
}

void ftCo_CargoWait2_Phys(ftCo_GObj* gobj)
{
    ftCo_Damage_Phys(gobj);
}

void ftCo_CargoWait2_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
    }
}

static inline FtMotionId inlineA0(ftCo_Fighter* fp)
{
    FtMotionId msid = fp->motion_id;
    if (fp->input.x668 & HSD_PAD_AB) {
        float lstick_x = fp->input.lstick.x;
        if (ABS(lstick_x) >= p_ftCommonData->x98) {
            if (lstick_x * fp->facing_dir > 0) {
                msid = fp->x2CC->x4_motion_state + 10;
            } else {
                msid = fp->x2CC->x4_motion_state + 11;
            }
        } else {
            float lstick_y = fp->input.lstick.y;
            if (lstick_y >= p_ftCommonData->attackhi3_stick_threshold_y) {
                msid = fp->x2CC->x4_motion_state + 12;
            } else if (lstick_y <= p_ftCommonData->xB0) {
                msid = fp->x2CC->x4_motion_state + 13;
            }
        }
    }
    return msid;
}

ASM bool ftCo_8009BF3C(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = gobj->user_data;
    if (inlineA0(fp) != fp->motion_id) {
        ftCo_8009C02C(gobj, fp->motion_id);
        return true;
    }
    return false;
}
#else /* clang-format off */
{ nofralloc
/* 8009BF3C 00098B1C  7C 08 02 A6 */	mflr r0
/* 8009BF40 00098B20  90 01 00 04 */	stw r0, 4(r1)
/* 8009BF44 00098B24  94 21 FF F8 */	stwu r1, -8(r1)
/* 8009BF48 00098B28  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8009BF4C 00098B2C  80 06 06 68 */	lwz r0, 0x668(r6)
/* 8009BF50 00098B30  80 86 00 10 */	lwz r4, 0x10(r6)
/* 8009BF54 00098B34  54 00 05 AF */	rlwinm. r0, r0, 0, 0x16, 0x17
/* 8009BF58 00098B38  41 82 00 A8 */	beq lbl_8009C000
/* 8009BF5C 00098B3C  C0 46 06 20 */	lfs f2, 0x620(r6)
/* 8009BF60 00098B40  C0 02 8D 60 */	lfs f0, 0.0f
/* 8009BF64 00098B44  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8009BF68 00098B48  40 80 00 0C */	bge lbl_8009BF74
/* 8009BF6C 00098B4C  FC 20 10 50 */	fneg f1, f2
/* 8009BF70 00098B50  48 00 00 08 */	b lbl_8009BF78
lbl_8009BF74:
/* 8009BF74 00098B54  FC 20 10 90 */	fmr f1, f2
lbl_8009BF78:
/* 8009BF78 00098B58  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 8009BF7C 00098B5C  C0 05 00 98 */	lfs f0, 0x98(r5)
/* 8009BF80 00098B60  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009BF84 00098B64  4C 41 13 82 */	cror 2, 1, 2
/* 8009BF88 00098B68  40 82 00 38 */	bne lbl_8009BFC0
/* 8009BF8C 00098B6C  C0 26 00 2C */	lfs f1, 0x2c(r6)
/* 8009BF90 00098B70  C0 02 8D 60 */	lfs f0, 0.0f
/* 8009BF94 00098B74  EC 22 00 72 */	fmuls f1, f2, f1
/* 8009BF98 00098B78  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009BF9C 00098B7C  40 81 00 14 */	ble lbl_8009BFB0
/* 8009BFA0 00098B80  80 86 02 CC */	lwz r4, 0x2cc(r6)
/* 8009BFA4 00098B84  80 84 00 04 */	lwz r4, 4(r4)
/* 8009BFA8 00098B88  38 84 00 0A */	addi r4, r4, 0xa
/* 8009BFAC 00098B8C  48 00 00 54 */	b lbl_8009C000
lbl_8009BFB0:
/* 8009BFB0 00098B90  80 86 02 CC */	lwz r4, 0x2cc(r6)
/* 8009BFB4 00098B94  80 84 00 04 */	lwz r4, 4(r4)
/* 8009BFB8 00098B98  38 84 00 0B */	addi r4, r4, 0xb
/* 8009BFBC 00098B9C  48 00 00 44 */	b lbl_8009C000
lbl_8009BFC0:
/* 8009BFC0 00098BA0  C0 26 06 24 */	lfs f1, 0x624(r6)
/* 8009BFC4 00098BA4  C0 05 00 AC */	lfs f0, 0xac(r5)
/* 8009BFC8 00098BA8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009BFCC 00098BAC  4C 41 13 82 */	cror 2, 1, 2
/* 8009BFD0 00098BB0  40 82 00 14 */	bne lbl_8009BFE4
/* 8009BFD4 00098BB4  80 86 02 CC */	lwz r4, 0x2cc(r6)
/* 8009BFD8 00098BB8  80 84 00 04 */	lwz r4, 4(r4)
/* 8009BFDC 00098BBC  38 84 00 0C */	addi r4, r4, 0xc
/* 8009BFE0 00098BC0  48 00 00 20 */	b lbl_8009C000
lbl_8009BFE4:
/* 8009BFE4 00098BC4  C0 05 00 B0 */	lfs f0, 0xb0(r5)
/* 8009BFE8 00098BC8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009BFEC 00098BCC  4C 40 13 82 */	cror 2, 0, 2
/* 8009BFF0 00098BD0  40 82 00 10 */	bne lbl_8009C000
/* 8009BFF4 00098BD4  80 86 02 CC */	lwz r4, 0x2cc(r6)
/* 8009BFF8 00098BD8  80 84 00 04 */	lwz r4, 4(r4)
/* 8009BFFC 00098BDC  38 84 00 0D */	addi r4, r4, 0xd
lbl_8009C000:
/* 8009C000 00098BE0  80 06 00 10 */	lwz r0, 0x10(r6)
/* 8009C004 00098BE4  7C 04 00 00 */	cmpw r4, r0
/* 8009C008 00098BE8  41 82 00 10 */	beq lbl_8009C018
/* 8009C00C 00098BEC  48 00 00 21 */	bl ftCo_8009C02C
/* 8009C010 00098BF0  38 60 00 01 */	li r3, 1
/* 8009C014 00098BF4  48 00 00 08 */	b lbl_8009C01C
lbl_8009C018:
/* 8009C018 00098BF8  38 60 00 00 */	li r3, 0
lbl_8009C01C:
/* 8009C01C 00098BFC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8009C020 00098C00  38 21 00 08 */	addi r1, r1, 8
/* 8009C024 00098C04  7C 08 03 A6 */	mtlr r0
/* 8009C028 00098C08  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

bool ftCo_8009C02C(ftCo_GObj* gobj, FtMotionId msid)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    {
        MotionFlags mf;
        FtMotionId msid1;
        if (fp->ground_or_air == GA_Air) {
            mf = 1;
        } else {
            mf = 0;
        }
        if (fp->ground_or_air == GA_Air) {
            msid1 = msid + 4;
        } else {
            msid1 = msid;
        }
        Fighter_ChangeMotionState(gobj, msid1, mf, NULL, 0, 1, 0);
    }
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    {
        FtMotionId msid1 = msid;
        msid1 -= fp->x2CC->x4_motion_state + 10;
        msid1 += ftCo_MS_ThrownFF;
        return ftCo_800DE3FC(fp->victim_gobj, msid1, 1);
    }
}

void ftCo_CargoThrowF_Anim(ftCo_GObj* gobj)
{
    ftCo_800DD724(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CargoThrowF_IASA(ftCo_GObj* gobj)
{
    ftCo_ThrowF_IASA(gobj);
}

void ftCo_CargoThrowF_Phys(ftCo_GObj* gobj)
{
    ftCo_ThrowF_Phys(gobj);
}

static inline void inlineB0(ftCo_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = gobj->user_data;
    float facing_dir = fp->facing_dir;
    if (facing_dir != fp->facing_dir1) {
        fp->facing_dir = fp->facing_dir1;
    }
    Fighter_ChangeMotionState(gobj, msid,
                              Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                                  Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
                                  Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
                                  Ft_MF_SkipModelFlags | Ft_MF_Unk27,
                              NULL, fp->cur_anim_frame, 1, 0);
    fp->facing_dir = facing_dir;
    ftCommon_8007E2F4(fp, 0x1FF);
}

static inline void inlineB1(ftCo_GObj* gobj, FighterEvent cb, int offset)
{
    Fighter* fp = GET_FIGHTER(gobj);
    cb(fp);
    inlineB0(gobj, fp->motion_id + offset);
}

void ftCo_8009C170(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    inlineB1(gobj, ftCommon_8007D5D4, 4);
}

void ftCo_CargoThrowF_Coll(ftCo_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowB_Anim(ftCo_GObj* gobj)
{
    ftCo_ThrowB_Anim(gobj);
}

void ftCo_CargoThrowB_IASA(ftCo_GObj* gobj)
{
    ftCo_ThrowB_IASA(gobj);
}

void ftCo_CargoThrowB_Phys(ftCo_GObj* gobj)
{
    ftCo_ThrowB_Phys(gobj);
}

void ftCo_CargoThrowB_Coll(ftCo_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowHi_Anim(ftCo_GObj* gobj)
{
    ftCo_ThrowHi_Anim(gobj);
}

void ftCo_CargoThrowHi_IASA(ftCo_GObj* gobj)
{
    ftCo_ThrowHi_IASA(gobj);
}

void ftCo_CargoThrowHi_Phys(ftCo_GObj* gobj)
{
    ftCo_ThrowHi_Phys(gobj);
}

void ftCo_CargoThrowHi_Coll(ftCo_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowLw_Anim(ftCo_GObj* gobj)
{
    ftCo_ThrowLw_Anim(gobj);
}

void ftCo_CargoThrowLw_IASA(ftCo_GObj* gobj)
{
    ftCo_ThrowLw_IASA(gobj);
}

void ftCo_CargoThrowLw_Phys(ftCo_GObj* gobj)
{
    ftCo_ThrowLw_Phys(gobj);
}

void ftCo_CargoThrowLw_Coll(ftCo_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009C170);
}

void ftCo_CargoThrowAir_Anim(ftCo_GObj* gobj)
{
    ftCo_800DD724(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CargoThrowAir_IASA(ftCo_GObj* gobj) {}

void ftCo_CargoThrowAir_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_CargoThrowAir_Coll(ftCo_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_8009C45C);
}

void ftCo_8009C45C(ftCo_GObj* gobj, float lag)
{
    inlineB1(gobj, ftCommon_8007D7FC, -4);
}
