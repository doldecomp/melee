#include "ftCo_Turn.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Dash.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_SpecialS.h"

bool ftCo_800C97A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir <= p_ftCommonData->x34) {
        return true;
    }
    return false;
}

bool ftCo_Turn_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C97A8(gobj)) {
        ftCo_Turn_Enter_Basic(gobj);
        return true;
    }
    return false;
}

void ftCo_Turn_Enter(Fighter_GObj* gobj, FtMotionId msid, MotionFlags flags,
                     f32 arg3, f32 frames_to_turn, f32 anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.co.turn.has_turned = false;
    fp->mv.co.turn.just_turned = 0;
    fp->mv.co.turn.facing_after = -fp->facing_dir;
    fp->mv.co.turn.frames_to_turn = frames_to_turn;
    fp->mv.co.turn.x8 = arg3;
    fp->mv.co.turn.x1C = 0;
    Fighter_ChangeMotionState(gobj, msid, flags, anim_start, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_Turn_Enter_Basic(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float frames = fp->co_attrs.frames_to_change_direction_on_standing_turn;
    PAD_STACK(8);
    ftCo_Turn_Enter(gobj, ftCo_MS_Turn, Ft_MF_None, 0.0F, frames, 0.0F);
}

void ftCo_Turn_Anim_Inner(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.turn.frames_to_turn > 0.0F) {
        fp->mv.co.turn.frames_to_turn -= 1.0F;
        return;
    }

    if (!fp->mv.co.turn.has_turned) {
        fp->mv.co.turn.has_turned = true;
        fp->mv.co.turn.just_turned = true;
        fp->facing_dir = -fp->facing_dir;
    }
}

void ftCo_Turn_Anim(Fighter_GObj* gobj)
{
    ftCo_Turn_Anim_Inner(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Turn_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.turn.just_turned) {
        fp->input.x668 |= fp->mv.co.turn.x1C;
    }
    if (!fp->mv.co.turn.has_turned) {
        fp->facing_dir = -fp->facing_dir;
    }

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));

    if (!fp->mv.co.turn.has_turned) {
        fp->facing_dir = -fp->facing_dir;
    }

    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));

    fn_800C9C2C(gobj);
    if (fp->mv.co.turn.just_turned && fp->mv.co.turn.x8) {
        if (fp->input.lstick.x * fp->mv.co.turn.facing_after >=
            p_ftCommonData->x3C)
        {
            ftCo_Dash_Enter(gobj, 0);
        }
    }

    if (fp->input.x668 & HSD_PAD_A) {
        fp->mv.co.turn.x1C |= HSD_PAD_A;
    }

    if (fp->input.x668 & HSD_PAD_B) {
        fp->mv.co.turn.x1C |= HSD_PAD_B;
    }

    if (fp->mv.co.turn.just_turned) {
        fp->mv.co.turn.just_turned = false;
    }
}

void ftCo_Turn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Turn_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

bool fn_800C9C2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->mv.co.turn.facing_after >=
            p_ftCommonData->x3C &&
        fp->x670_timer_lstick_tilt_x < p_ftCommonData->x40)
    {
        fp->mv.co.turn.x8 = fp->mv.co.turn.facing_after;
        return true;
    }
    return false;
}

void ftCo_Turn_Enter_Smash(Fighter_GObj* gobj)
{
    Fighter* fp_r7 = GET_FIGHTER(gobj);
    float facing = fp_r7->facing_dir;
    PAD_STACK(1);

    fp_r7->mv.co.turn.has_turned = false;
    fp_r7->mv.co.turn.just_turned = false;
    fp_r7->mv.co.turn.facing_after = -fp_r7->facing_dir;
    fp_r7->mv.co.turn.frames_to_turn = 0.0F;
    fp_r7->mv.co.turn.x8 = facing;
    fp_r7->mv.co.turn.x1C = 0;

    Fighter_ChangeMotionState(gobj, ftCo_MS_Turn, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
}
