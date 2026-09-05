#include "ftCo_Walk.h"

#include <placeholder.h>

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftwalkcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

#include "forward.h"

#include "ftCo_AppealS.h"
#include "ftCo_Attack1.h"
#include "ftCo_Attack100.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_Dash.h"
#include "ftCo_Guard.h"
#include "ftCo_Jump.h"
#include "ftCo_SpecialS.h"
#include "ftCo_Squat.h"

bool ftCo_Walk_CheckInput(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ftWalkCommon_800DFC70(gobj)) {
        ftCo_Walk_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

bool ftCo_Walk_CheckInput_Ottotto(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir >=
            p_ftCommonData->teeter_walk_threshold &&
        ftWalkCommon_800DFC70(gobj))
    {
        ftCo_Walk_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

void ftCo_Walk_Enter(Fighter_GObj* gobj, f32 arg8)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 accel_mul = 1.0F;
    float* anim_vars = &fp->x2DC;

    if (fp->is_metal) {
        accel_mul = Fighter_804D651C->x0;
    }

    if (fp->x34_scale.y != 1.0F) {
        accel_mul = ftCo_CalcYScaledKnockback(accel_mul, fp->x34_scale.y,
                                              Fighter_804D6524->xC);
    }
    if (fp->x197C != NULL) {
        accel_mul *= Fighter_804D6520->x0;
    }
    ftWalkCommon_800DFCA4(
        gobj, ftCo_MS_WalkSlow, Ft_MF_None, arg8, anim_vars[0], anim_vars[1],
        anim_vars[2], fp->co_attrs.slow_walk_max, fp->co_attrs.mid_walk_point,
        fp->co_attrs.fast_walk_min, accel_mul);
}

void ftCo_Walk_Anim(Fighter_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftCo_Walk_IASA(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));
    RETURN_IF(ftCo_Dash_CheckInput(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
    RETURN_IF(ft_8008A244(gobj));
    ftWalkCommon_800DFEC8(gobj, ftCo_Walk_Enter);
}

void ftCo_Walk_Phys(Fighter_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftCo_Walk_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}
