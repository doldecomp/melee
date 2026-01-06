#include "ftKp_SpecialLw.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftKoopa/ftKp_Init.h"

#include <trigf.h>
#include <melee/cm/camera.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>

static void fn_80134518(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4D8, gobj, &fp->cur_pos);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static void fn_80134590(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4DF, gobj, fp->parts->joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static void ftKp_SpecialLw_Enter_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags_b0 = false;
    fp->x6A4_transNOffset.y = 0.0f;
    fp->x2223_b4 = true;
}

void ftKp_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);
    fp->self_vel.x = fp->self_vel.y = 0.0f;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftKp_SpecialLw_Enter_inline(gobj);
}

void ftKp_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    fp->self_vel.x *= da->x80;
    fp->self_vel.y *= da->x84;
    Fighter_ChangeMotionState(gobj, 0x16A, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftKp_SpecialLw_Enter_inline(gobj);
}

void ftKp_SpecialLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKp_SpecialLw_80134988(gobj);
    }
}

void ftKp_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->cmd_vars[1] = 1;
    }
}

void ftKp_SpecialLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0.0f) {
        fp->self_vel.y = 0.0f;
    }
}

void ftKp_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    ftCommon_Fall(fp, da->x8C, da->x90);
    ftCommon_ApplyFrictionAir(fp, da->x88);
    if ((fp->self_vel.y < da->x94) || (fp->cmd_vars[1] != 0)) {
        fp->self_vel.y = da->x94;
    }
    if (fp->cmd_vars[1] != 0) {
        fp->self_vel.x = 0.0f;
        if (!fp->x2219_b0) {
            fp->accessory4_cb = fn_80134590;
        }
    }
}

void ftKp_SpecialLw_Coll(Fighter_GObj* gobj)
{
    ftKp_SpecialAirLw_Coll(gobj);
}

void ftKp_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        if ((fp->cmd_vars[0] != 0) && fp->self_vel.y <= 0.0f) {
            ftKp_SpecialLw_80134A5C(gobj);
        } else {
            ftCommon_8007D5D4(fp);
            ftCommon_UnlockECB(fp);
        }
    } else if ((fp->cmd_vars[0] != 0) && (ftCliffCommon_80081298(gobj) != 0)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftKp_SpecialLw_80134988(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirLw, 0x0C4C5088, 30.0f,
                              1.0f, 0.0f, NULL);
}

void ftKp_SpecialLwLanding_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialLwLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialLwLanding_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKp_SpecialLw_80134A5C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0.0f;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16B, 0U, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_80134518;
}
