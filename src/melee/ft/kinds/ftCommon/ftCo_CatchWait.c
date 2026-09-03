#include "ftCo_Attack100.h"
#include "ftCo_Fall.h"
#include "ftCo_Throw.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/kinds/itlinkhookshot.h"
#include "it/kinds/itsamusgrapple.h"

void fn_800DA054(Fighter_GObj* gobj);

void fn_800DA1D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj;
    PAD_STACK(8);
    fp->gr_vel = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CatchWait, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp->accessory1_cb = fn_800DA4A0;
    fp->take_dmg_cb = fn_800DA490;
    fp->x221B_b7 = false;
    jobj = fp->parts[fp->ft_data->x8->x11].joint;
    fp->mv.co.capturedamage.x18 = jobj;
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 1, 0x41D, jobj);
    ftCommon_8007EBAC(fp, 3, 0);
    ftCommon_8007E2F4(fp, 0x1FF);
    fn_800DB6C8(fp->victim_gobj);
}

void fn_800DA2B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CatchWait, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp->accessory1_cb = fn_800DA4A0;
    fp->take_dmg_cb = fn_800DA490;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

void ftCo_CatchWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fn_800DA4C0(gobj)) {
        if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
            it_802A7AAC(gobj);
        } else if (fp->kind == FTKIND_SAMUS) {
            it_802BAC3C(gobj);
        }
    } else if (ftCo_800DD1E4(gobj)) {
        if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
            it_802A7AAC(gobj);
        } else if (fp->kind == FTKIND_SAMUS) {
            it_802BAC3C(gobj);
        }
    }
}

void ftCo_CatchWait_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 *
                                         fp->co_attrs.ground_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftCo_CatchWait_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA440);
}

void fn_800DA440(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}

void fn_800DA490(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void fn_800DA4A0(Fighter_GObj* gobj)
{
    fn_800DA054(gobj);
}

bool fn_800DA4C0(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->input.x668 & 0x100) {
        fn_800DA4FC(gobj);
        return true;
    }
    return false;
}
