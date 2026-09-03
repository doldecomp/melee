#include "ftCo_AirCatch.h"
#include "ftCo_Attack100.h"
#include "ftCo_AttackAir.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_Fall.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_JumpAerial.h"
#include "ftCo_SpecialAir.h"
#include "ftCo_Throw.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void fn_800DC070(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    ftCommon_8007D5D4(fp);
    fp->self_vel.x = -fp->facing_dir * p_ftCommonData->x374;
    fp->self_vel.y = p_ftCommonData->x378;
    fp->mv.co.buryjump.x0 = 0;
    ftCo_800DC920(victim, gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureJump, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
}

void ftCo_CaptureJump_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.buryjump.x0 += 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_CaptureJump_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    if (fp->mv.ca.specials.grav >= p_ftCommonData->x3B8) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, NULL));
        RETURN_IF(ftCo_800D7100(gobj));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_80099A58(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
        RETURN_IF(ftCo_800D705C(gobj));
        RETURN_IF(ftCo_800CB870(gobj));
    }
}

void ftCo_CaptureJump_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    ftCommon_Fall(fp, fp->co_attrs.gravity, fp->co_attrs.terminal_velocity);
    ftCommon_8007D268(fp);
}

void ftCo_CaptureJump_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}
