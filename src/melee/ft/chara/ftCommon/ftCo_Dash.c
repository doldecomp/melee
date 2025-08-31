#include "ftCo_Dash.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_AttackDash.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Run.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftCommon/ftCo_Turn.h"

bool ftCo_Dash_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float lsx_abs = fp->input.lstick.x;
    if (lsx_abs < 0.0F) {
        lsx_abs = -lsx_abs;
    }

    if ((lsx_abs >= p_ftCommonData->x3C) &&
        ((int) fp->x670_timer_lstick_tilt_x < p_ftCommonData->x40))
    {
        if ((fp->input.lstick.x * fp->facing_dir) < 0.0F) {
            ftCo_Turn_Enter_Smash(gobj);
        } else {
            ftCo_Dash_Enter(gobj, 1);
        }
        return true;
    }
    return false;
}

void ftCo_Dash_Enter(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 init_vel;
    PAD_STACK(8);

    fp->cmd_vars[0] = 0;

    Fighter_ChangeMotionState(gobj, ftCo_MS_Dash, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->x670_timer_lstick_tilt_x = 0xFE;
    init_vel = fp->facing_dir * fp->co_attrs.dash_initial_velocity;
    if ((fp->gr_vel * fp->facing_dir) < 0.0F) {
        fp->mv.co.dash.x0 = init_vel;
    } else {
        fp->mv.co.dash.x0 = init_vel - fp->gr_vel;
    }
    ftCommon_800804A0(fp, fp->mv.ca.specials.grav);
    fp->mv.co.dash.x4 = arg1;
    if (fp->x197C != NULL) {
        ft_PlaySFX(fp, 0x118, 0x7F, 0x40);
    }
}

void ftCo_Dash_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Dash_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->mv.co.dash.x4 != 0) &&
        (fp->cur_anim_frame <= p_ftCommonData->x44))
    {
        if (!ftCo_SpecialS_CheckInput(gobj)) {
            if ((fp->item_gobj != NULL) && ftCo_80094E54(fp)) {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowF4);
            } else if (ftCo_800D8A38(gobj)) {
                return;
            } else {
                if (!ftCo_AttackS4_8008C114(gobj)) {
                    if (!(fp->cur_anim_frame <= p_ftCommonData->x48 &&
                          ftCo_80099264(gobj)))
                    {
                        goto block_42;
                    }
                }
            }
        }
    } else if (fp->cur_anim_frame <= p_ftCommonData->x4C) {
        if (!ftCo_SpecialS_CheckInput(gobj)) {
            RETURN_IF(ftCo_800D8A38(gobj));
            if (ftCo_AttackDash_CheckInput(gobj)) {
                ftCo_AttackDash_SetMv0(gobj);
                return;
            }
            if (!(fp->input.lstick.x * fp->facing_dir < 0.0F) ||
                !ftCo_Dash_CheckInput(gobj))
            {
                if (ftCo_80091AD8(gobj, (s32) (p_ftCommonData->x4C -
                                               fp->cur_anim_frame)))
                {
                } else {
                    goto block_42;
                }
            }
        }
    } else {
        RETURN_IF(ftCo_800D8A38(gobj));
        if (!ftCo_Dash_CheckInput(gobj)) {
            if (ftCo_80091A4C(gobj)) {
                ftCo_80091B9C(gobj);
            } else {
            block_42:
                if (!ftCo_800DE9D8(gobj)) {
                    RETURN_IF(fn_800CAF78(gobj));
                    RETURN_IF(!fp->cmd_vars[0]);
                    RETURN_IF(fn_800CA5F0(gobj));
                    return;
                }
            }
        }
    }

    {
        float friction = ft_GetGroundFrictionMultiplier(fp);
        float temp_f0 = fp->gr_vel * p_ftCommonData->x54;
        fp->gr_vel += -temp_f0 * friction;
    }
}

void ftCo_Dash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    if (fp->mv.co.dash.x0) {
        fp->mv.co.dash.x0 = 0;
    } else {
        ftCo_DatAttrs* attrs = &fp->co_attrs;
        float accel, target_vel;
        getAccelAndTarget(fp, &accel, &target_vel);
        ftCommon_8007C98C(fp, accel, target_vel,
                          attrs->gr_friction *
                              p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

void ftCo_Dash_Coll(Fighter_GObj* gobj)
{
    ft_800844EC();
}
