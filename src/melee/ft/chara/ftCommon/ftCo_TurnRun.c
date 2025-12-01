#include "ftCo_TurnRun.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Run.h"

bool fn_800C9CEC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->facing_dir <=
        p_ftCommonData->x38_someLStickXThreshold)
    {
        ftCo_TurnRun_Enter(gobj, fp->cur_anim_frame);
        return true;
    }
    return false;
}

bool fn_800C9D40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir <=
        p_ftCommonData->x38_someLStickXThreshold)
    {
        ftCo_TurnRun_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

void ftCo_TurnRun_Enter(Fighter_GObj* gobj, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->mv.co.turnrun.accel_mul = fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftCo_MS_TurnRun, Ft_MF_SkipAnimVel,
                              anim_start, 1.0F, 0.0F, NULL);
    fp->mv.co.turnrun.x14 = 0;
    if (fp->x197C != NULL) {
        ft_PlaySFX(fp, 0x119, 0x7F, 0x40);
    }
}

void ftCo_TurnRun_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    if (fp->cmd_vars[1] != 0) {
        if (fp->mv.co.turnrun.x14 == 0) {
            ftAnim_SetAnimRate(gobj, 0.0F);
            fp->mv.co.turnrun.x14 = 1;
        } else {
            if ((fp->mv.co.walk.middle_anim_frame * fp->gr_vel) <= 0.01F) {
                ftAnim_SetAnimRate(gobj, 1.0F);
                fp->cmd_vars[1] = 0;
                fp->facing_dir = -fp->facing_dir;
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj) && !fn_800CA644(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_TurnRun_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(fn_800CAF78(gobj));
}

void ftCo_TurnRun_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);

    if (!target_vel) {
        ftCommon_ApplyFrictionGround(
            fp, co_attrs->gr_friction * p_ftCommonData->x60_someFrictionMul);
    } else if (fp->mv.co.turnrun.accel_mul * accel < 0) {
        if (accel > 0) {
            if (fp->gr_vel + accel > target_vel) {
                accel -= co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel < target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        } else {
            if (fp->gr_vel + accel < target_vel) {
                accel += co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel > target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        }
        fp->xE4_ground_accel_1 = accel;
    } else {
        ftCommon_ApplyFrictionGround(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_ApplyGroundMovement(gobj);
}

void ftCo_TurnRun_Coll(Fighter_GObj* gobj)
{
    s32 env_flags;
    bool var_r4;

    if (!ft_800827A0(gobj)) {
        ftCo_Fall_Enter(gobj);
        return;
    }
    var_r4 = true;
    env_flags = GET_FIGHTER(gobj)->coll_data.env_flags;
    if (!(env_flags & Collide_LeftEdge) && !(env_flags & Collide_RightEdge)) {
        var_r4 = false;
    }
    if (var_r4) {
        ftCommon_8007E2FC(gobj);
    }
}
