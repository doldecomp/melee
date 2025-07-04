#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_KneeBend.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_Jump.h"

void ftCo_KneeBend_Enter(Fighter_GObj* gobj, ftCo_JumpInput jump_input)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.kneebend.jump_input = jump_input;
    fp->mv.co.kneebend.is_short_hop = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_KneeBend, 0U, 0.0F, 1.0F, 0.0F,
                              NULL);
}

void ftCo_KneeBend_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;

    if (fp->cur_anim_frame >= co_attrs->jump_startup_time ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        if (ft_800D2D0C(gobj)) {
            ftCo_ItemScrew_Enter(gobj);
        } else {
            ftCo_Jump_Enter(gobj);
        }
    }
}

void ftCo_KneeBend_Check_ShortHop(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((!(fp->input.held_inputs & HSD_PAD_XY) &&
         fp->mv.co.kneebend.jump_input == JumpInput_XY) ||
        (fp->input.lstick.y < p_ftCommonData->tap_jump_release_threshold &&
         fp->mv.co.kneebend.jump_input == JumpInput_LStick) ||
        (fp->input.cstick.y < p_ftCommonData->tap_jump_release_threshold &&
         fp->mv.co.kneebend.jump_input == JumpInput_CStick))
    {
        fp->mv.co.kneebend.is_short_hop = true;
    }
}

void ftCo_KneeBend_IASA(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInputNoD0(gobj));
    ftCo_KneeBend_Check_ShortHop(gobj);
}

void ftCo_KneeBend_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_KneeBend_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
