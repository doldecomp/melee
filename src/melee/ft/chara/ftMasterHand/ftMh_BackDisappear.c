#include <platform.h>

#include "ftMh_BackDisappear.h"

#include "ftMh_TagCancel.h"
#include "ftMh_ThrownMasterHand.h"
#include "ftMh_Wait1_1.h"
#include "ftMh_Wait1_2.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftMh_BackDisappear_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.mh.unk0.x4(gobj);
    }
}

void ftMh_BackDisappear_IASA(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

void ftMh_BackDisappear_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_BackDisappear_Coll(HSD_GObj* gobj) {}

void ftMh_MS_372_801542E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_1, 0, fp->cur_anim_frame, 1,
                              0, 0);
    ftAnim_SetAnimRate(gobj, da->x110_pos.y);
    fp->mv.mh.unk0.x8 = da->x110_pos.x;
}

void ftMh_Wait1_1_Anim(HSD_GObj* gobj)
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
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_1, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_Wait1_1_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[4] = { 0 };

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

void ftMh_Wait1_1_Phys(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER doesn't fit the stack.
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    float len;
    float speed;
    Vec3 sp28_pos;
    Vec3 vel;

    u8 _[4];

    ft_80085134(gobj);
    ftBossLib_8015C208(gobj, &sp28_pos);
    sp28_pos.x += da->x108;
    sp28_pos.y += da->x10C;
    sp28_pos.z = 0;
    lbVector_Diff(&sp28_pos, &fp->cur_pos, &vel);
    len = my_lbVector_Len(&vel);
    if (len < da->x2C) {
        fp->self_vel.x = vel.x;
        fp->self_vel.y = vel.y;
    } else {
        lbVector_Normalize(&vel);
        speed = len * da->x28;
        vel.x *= speed;
        vel.y *= speed;
        vel.z *= speed;
        fp->self_vel.x = vel.x;
        fp->self_vel.y = vel.y;
    }
}

void ftMh_Wait1_1_Coll(HSD_GObj* gobj) {}

void ftMh_MS_373_801545A0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Grab, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2D0(fp, 128, ftMh_MS_375_80154A2C, 0, ftMh_MS_388_80155A58);
    fp->mv.mh.unk0.x20 = 0;
}

void ftMh_Grab_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        ftMh_MS_378_80154CF8(gobj);
    }
}

void ftMh_Grab_IASA(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

void ftMh_Grab_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_Grab_Coll(HSD_GObj* gobj) {}

void ftMh_MS_374_801546D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Fail, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.xC.x = da->x30_pos2.x;
    fp->mv.mh.unk0.xC.y = da->x30_pos2.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_Fail_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_Fail_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Fail_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

void ftMh_Fail_Coll(HSD_GObj* gobj) {}

void ftMh_MS_381_8015483C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Cancel, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x24 = da->x120;
    fp->cmd_vars[0] = 1;
    fp->self_vel.x = 0;
    fp->self_vel.y = 0;
    fp->self_vel.z = 0;
    fp->mv.mh.unk0.xC.x = da->x30_pos2.x;
    fp->mv.mh.unk0.xC.y = da->x30_pos2.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_Cancel_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.mh.unk0.x24 <= 0 && fp->cmd_vars[0]) {
        ftMh_CaptureWaitMasterHand_80155D1C(fp->victim_gobj);
        fp->mv.mh.unk0.x20 = 0;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_Cancel_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Cancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

void ftMh_Cancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

void ftMh_MS_375_80154A2C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;
    fp->mv.mh.unk0.x20 = true;
    fp->x221E_b6 = false;
    ftMh_MS_375_80154C78(gobj);
}
