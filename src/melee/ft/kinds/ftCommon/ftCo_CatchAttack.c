#include "ftCo_Attack100.h"
#include "ftCo_Fall.h"
#include "ftCo_Throw.h"

#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>

void fn_800DA054(Fighter_GObj* gobj);

void fn_800DA4FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CatchAttack, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp->accessory1_cb = fn_800DA678;
    fp->take_dmg_cb = fn_800DA668;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftCo_CatchAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DA2B0(gobj);
    }
}

void ftCo_CatchAttack_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchAttack_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 *
                                         fp->co_attrs.ground_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftCo_CatchAttack_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA618);
}

void fn_800DA618(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;

    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}

void fn_800DA668(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void fn_800DA678(Fighter_GObj* gobj)
{
    fn_800DA054(gobj);
}
