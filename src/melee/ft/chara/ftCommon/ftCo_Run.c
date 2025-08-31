#include "ftCo_Run.h"

#include "math.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_AttackDash.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_RunBrake.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftCommon/ftCo_TurnRun.h"

bool fn_800CA5F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

bool fn_800CA644(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.lstick.x * fp->facing_dir) >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter(gobj, p_ftCommonData->x430);
        return true;
    }
    return false;
}

bool fn_800CA698(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->facing_dir >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter_Full(gobj, 0.0F, fp->cur_anim_frame,
                            fp->frame_speed_mul);
        return true;
    }
    return false;
}

void ftCo_Run_Enter(Fighter_GObj* gobj, float arg0)
{
    ftCo_Run_Enter_Full(gobj, arg0, 0.0F, 1.0F);
}

void ftCo_Run_Enter_Full(Fighter_GObj* gobj, float arg0, float anim_start,
                         float anim_speed)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Run, Ft_MF_None, anim_start,
                              anim_speed, 0.0F, NULL);
    fp->mv.co.run.x0 = arg0;
    fp->mv.co.run.x4 = fp->gr_vel;
}

void ftCo_Run_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 vel;
    f32 anim_rate;
    PAD_STACK(1);

    if (ft_GetGroundFrictionMultiplier(fp) < 1.0F) {
        vel = fp->mv.co.run.x4;
    } else {
        vel = fp->gr_vel;
    }

    if (vel * fp->facing_dir <= 0.0F) {
        anim_rate = 0.0F;
    } else {
        anim_rate = ABS(vel) / fp->co_attrs.run_animation_scaling;
    }

    ftAnim_SetAnimRate(gobj, anim_rate);
    if (fp->mv.co.run.x0 > 0.0F) {
        fp->mv.co.run.x0 -= 1.0F;
    }
}

void ftCo_Run_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_800D8A38(gobj));

    if (ftCo_AttackDash_CheckInput(gobj)) {
        ftCo_AttackDash_SetMv0(gobj);
        return;
    }

    if (ftCo_80091A4C(gobj)) {
        ftCo_80091B90(gobj, p_ftCommonData->x410);
        ftCo_80091B9C(gobj);
        return;
    }

    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(fn_800CAF78(gobj));

    RETURN_IF((fp->mv.co.run.x0 <= 0.0F) && fn_800C9D40(gobj));
    RETURN_IF(!(fp->mv.co.run.x0 <= 0.0F));
    RETURN_IF(ftCo_RunBrake_CheckInput(gobj));
}

void ftCo_Run_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);
    if (target_vel) {
        float gr_frac = fp->gr_vel / target_vel;
        if ((gr_frac > 0.0F) && (gr_frac < 1.0F)) {
            accel *= (1.0F - gr_frac) * p_ftCommonData->x5C;
        }
    }
    fp->mv.co.run.x4 = target_vel * p_ftCommonData->x440;
    ftCommon_8007C98C(fp, accel, target_vel,
                      attrs->gr_friction *
                          p_ftCommonData->x60_someFrictionMul);
    ftCommon_8007CB74(gobj);
}

void ftCo_Run_Coll(Fighter_GObj* gobj)
{
    ft_800844EC();
}
