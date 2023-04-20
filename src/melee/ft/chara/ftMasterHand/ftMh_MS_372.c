#include "ftMh_MS_372.h"

#include "ftMh_CaptureMasterHand_0.h"
#include "ftMh_CaptureWaitMasterHand.h"
#include "ftMh_MS_375.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "lb/lbvector.h"

#include <dolphin/mtx/types.h>

void ftMh_MS_372_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.mh.unk0.x4(gobj);
    }
}

void ftMh_MS_372_IASA(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

void ftMh_MS_372_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_372_Coll(HSD_GObj* gobj) {}

void ftMh_MS_372_801542E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk373, 0, 0,
                              fp->x894_currentAnimFrame, 1, 0);
    ftAnim_SetAnimRate(gobj, attr->x110_pos.y);
    fp->mv.mh.unk0.x8 = attr->x110_pos.x;
}

void ftMh_MS_373_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int timer = fp->mv.mh.unk0.x8 - 1;
    int is_zero = timer == 0;
    fp->mv.mh.unk0.x8 = timer;

    if (is_zero) {
        ftAnim_SetAnimRate(gobj, 1);
        ftMh_MS_373_801545A0(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk373, 0, 0, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_MS_373_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftMh_MS_373_Phys(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER doesn't fit the stack.
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    f32 len;
    f32 speed;
    Vec3 sp28_pos;
    Vec3 vel;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ft_80085134(gobj);
    ftBossLib_8015C208(gobj, &sp28_pos);
    sp28_pos.x += attr->x108;
    sp28_pos.y += attr->x10C;
    sp28_pos.z = 0;
    lbVector_Diff(&sp28_pos, &fp->cur_pos, &vel);
    len = my_lbVector_Len(&vel);
    if (len < attr->x2C) {
        fp->x80_self_vel.x = vel.x;
        fp->x80_self_vel.y = vel.y;
    } else {
        lbVector_Normalize(&vel);
        speed = len * attr->x28;
        vel.x *= speed;
        vel.y *= speed;
        vel.z *= speed;
        fp->x80_self_vel.x = vel.x;
        fp->x80_self_vel.y = vel.y;
    }
}

void ftMh_MS_373_Coll(HSD_GObj* gobj) {}

void ftMh_MS_373_801545A0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk374, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2D0(fp, 128, ftMh_MS_375_80154A2C, 0, ftMh_MS_388_80155A58);
    fp->mv.mh.unk0.x20 = 0;
}

void ftMh_MS_374_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x80_self_vel.x = fp->x80_self_vel.y = fp->x80_self_vel.z = 0;
        ftMh_MS_378_80154CF8(gobj);
    }
}

void ftMh_MS_374_IASA(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

void ftMh_MS_374_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_374_Coll(HSD_GObj* gobj) {}

void ftMh_MS_374_801546D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk381, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.xC.x = attr->x30_pos2.x;
    fp->mv.mh.unk0.xC.y = attr->x30_pos2.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_MS_381_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_381_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_381_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

void ftMh_MS_381_Coll(HSD_GObj* gobj) {}

void ftMh_MS_381_8015483C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk375, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x24 = attr->x120;
    fp->x2200_ftcmd_var0 = 1;
    fp->x80_self_vel.x = 0;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.z = 0;
    fp->mv.mh.unk0.xC.x = attr->x30_pos2.x;
    fp->mv.mh.unk0.xC.y = attr->x30_pos2.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_MS_375_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.mh.unk0.x24 <= 0 && fp->x2200_ftcmd_var0) {
        ftMh_CaptureWaitMasterHand_80155D1C(fp->x1A58_interactedFighter);
        fp->mv.mh.unk0.x20 = 0;
        fp->x2200_ftcmd_var0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_375_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_375_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

void ftMh_MS_375_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->x80_self_vel.x = fp->x80_self_vel.y = fp->x80_self_vel.z = 0;
    }
}

void ftMh_MS_375_80154A2C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.z = 0;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = 0;
    fp->mv.mh.unk0.x20 = true;
    fp->x221E_flag.bits.b6 = false;
    ftMh_MS_375_80154C78(gobj);
}
