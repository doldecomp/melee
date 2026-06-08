#include "ftkirbyattackdash.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AttackDash.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include <common_structs.h>
#include <stddef.h>
#include <trigf.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 0F1FDC */ static void fn_800F1FDC(Fighter_GObj* gobj);
/* 0F20C4 */ static void fn_800F20C4(Fighter_GObj* gobj);

void ftKb_SpecialN_800F1F68(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDash, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.attackdash.x0 = 0;
}

void fn_800F1FDC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDash, 0x0C4C5082U,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0,
                              NULL);
}

void ftKb_AttackDash_Anim(Fighter_GObj* gobj)
{
    ftCo_AttackDash_Anim(gobj);
}

void ftKb_AttackDash_IASA(Fighter_GObj* gobj)
{
    ftCo_AttackDash_IASA(gobj);
}

void ftKb_AttackDash_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftKb_AttackDash_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F20C4);
}

void fn_800F20C4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDashAir, 0x0C4C5082,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0f,
                              NULL);
}

void ftKb_AttackDashAir_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_AttackDashAir_IASA(Fighter_GObj* gobj) {}

void ftKb_AttackDashAir_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80085204(gobj);
    ftCommon_FallBasic(fp);
}

void ftKb_AttackDashAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F1FDC);
}

float ftKb_AttackDashAir_800F21C0(Fighter_GObj* gobj)
{
    return ftPartGetRotX(GET_FIGHTER(gobj), 0);
}
