#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_RunBrake.h"

#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_TurnRun.h"

bool ftCo_RunBrake_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float lsx_abs = fp->input.lstick.x;
    if (lsx_abs < 0.0F) {
        lsx_abs = -lsx_abs;
    }
    if (lsx_abs < p_ftCommonData->x58_someLStickXThreshold) {
        ftCo_RunBrake_Enter(gobj);
        return true;
    }
    return false;
}

void ftCo_RunBrake_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_RunBrake, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.runbrake.x0 = false;
    fp->mv.co.runbrake.frames = fp->co_attrs.max_run_brake_frames;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x119, 0x7F, 0x40);
    }
}

void ftCo_RunBrake_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1]) {
        float maybe_max_vel = p_ftCommonData->x42C;
        if (!fp->mv.co.runbrake.x0) {
            if (fabs_inline(fp->gr_vel) >= maybe_max_vel) {
                ftAnim_SetAnimRate(gobj, 0.0F);
                fp->mv.co.runbrake.x0 = true;
            }
        } else {
            if (fabs_inline(fp->gr_vel) <= maybe_max_vel) {
                ftAnim_SetAnimRate(gobj, 1.0F);
                fp->cmd_vars[1] = 0;
            }
        }
    }

    if (fp->mv.co.runbrake.frames) {
        fp->mv.co.runbrake.frames -= 1.0F;
        if (fp->mv.co.runbrake.frames < 0.0F) {
            fp->mv.co.runbrake.frames = 0.0F;
        }
    }

    if (!(ftAnim_IsFramesRemaining(gobj) && fp->mv.co.runbrake.frames)) {
        ft_8008A2BC(gobj);
    }
}

#pragma push
#pragma dont_inline on
void ftCo_RunBrake_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    RETURN_IF(fn_800CAF78(gobj));
    RETURN_IF(fp->cmd_vars[0] && fn_800C9CEC(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
}
#pragma pop

void ftCo_RunBrake_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007C930(fp, p_ftCommonData->x60_someFrictionMul *
                              fp->co_attrs.gr_friction);
    ftCommon_8007CB74(gobj);
}

void ftCo_RunBrake_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}
