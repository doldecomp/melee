#include "ftCo_Jump.h"

#include "math.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_HammerJump.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_KneeBend.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftPeach/ftPe_Float.h"

ftCo_JumpInput ftCo_Jump_GetInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold) &&
        (fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74))
    {
        return JumpInput_LStick;
    }

    if (fp->input.x668 & HSD_PAD_XY) {
        return JumpInput_XY;
    }

    return JumpInput_None;
}

bool ftCo_Jump_CheckInput(Fighter_GObj* gobj)
{
    ftCo_JumpInput jump_input;
    if (ftCo_800C5240(gobj)) {
        return ftCo_800C5A50(gobj);
    }

    jump_input = ftCo_Jump_GetInput(gobj);

    if (jump_input) {
        ftCo_KneeBend_Enter(gobj, jump_input);
        return true;
    }
    return false;
}

bool fn_800CAF78(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C5240(gobj)) {
        return ftCo_800C5A50(gobj);
    }

    if ((fp->input.lstick.y >= p_ftCommonData->x80) &&
        (fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74))
    {
        ftCo_KneeBend_Enter(gobj, JumpInput_LStick);
        return true;
    }

    if (fp->input.x668 & HSD_PAD_XY) {
        ftCo_KneeBend_Enter(gobj, JumpInput_XY);
        return true;
    }

    return false;
}

bool ftCo_800CB024(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_Jump_CheckInput(gobj)) {
        return true;
    }

    if (ftCo_800DF910(fp)) {
        ftCo_KneeBend_Enter(gobj, JumpInput_CStick);
        return true;
    }
    return 0;
}

void ftCo_800CB110(Fighter_GObj* gobj, bool arg1, f32 jump_mul)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs;

    fp->mv.co.jump.x4 = false;
    co_attrs = &fp->co_attrs;
    fp->mv.co.jump.jump_mul = jump_mul;

    fp->self_vel.x *= fp->co_attrs.ground_to_air_jump_momentum_multiplier *
                      fp->mv.co.jump.jump_mul;
    fp->self_vel.y *= p_ftCommonData->x438;
    fp->self_vel.z = 0.0F;

    {
        float h_init_v =
            fp->input.lstick.x * fp->co_attrs.jump_h_initial_velocity;
        float h_vel = fp->mv.co.jump.jump_mul * h_init_v;
        float h_max_vel;
        float v_init_v;
        if (fp->mv.co.jump.x0) {
            v_init_v =
                co_attrs->hop_v_initial_velocity * fp->mv.co.jump.jump_mul;
        } else {
            v_init_v =
                co_attrs->jump_v_initial_velocity * fp->mv.co.jump.jump_mul;
        }

        fp->self_vel.y = v_init_v;
        h_vel = fp->self_vel.x + h_vel;
        h_max_vel = co_attrs->jump_h_max_velocity * fp->mv.co.jump.jump_mul;

        if (ABS(h_vel) > h_max_vel) {
            if (h_vel < 0.0F) {
                h_vel = -h_max_vel;
            } else {
                h_vel = h_max_vel;
            }
        }
        fp->self_vel.x = h_vel;
    }

    fp->x671_timer_lstick_tilt_y = 0xFE;
    if (arg1) {
        ft_800881D8(fp, fp->ft_data->x4C_sfx->x10, SFX_VOLUME_MAX,
                    SFX_PAN_MID);
        if (fp->x197C != NULL) {
            ft_PlaySFX(fp, 0x11A, SFX_VOLUME_MAX, SFX_PAN_MID);
        }
    }
}

void ftCo_Jump_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = (fp->input.lstick.x * fp->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpF
               : ftCo_MS_JumpB;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    ftCo_800CB110(gobj, true, 1.0F);
    fp->x2227_b0 = true;
}

void ftCo_Jump_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_Jump_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800D7100(gobj));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(fp->mv.co.jump.x4 && ftCo_800CEE70(gobj));
    RETURN_IF(fp->mv.co.jump.x4 && ftPe_8011BA54(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
    RETURN_IF(!fp->mv.co.jump.x4);
    RETURN_IF(ftPe_8011BAD8(gobj));
}

void ftCo_Jump_Phys_Inner(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->mv.co.jump.x4) {
        fp->mv.co.jump.x4 = true;
        return;
    }
    ft_80084DB0(gobj);
}

void ftCo_Jump_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftCo_Jump_Coll(Fighter_GObj* gobj)
{
    ft_800835B0(gobj, ftCo_80096CC8, ft_80082B1C);
}
