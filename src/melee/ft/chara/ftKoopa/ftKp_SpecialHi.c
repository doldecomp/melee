#include "ftKp_SpecialHi.h"

#include "ftKp_Init.h"
#include "ftKp_SpecialN.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"

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
#include <melee/it/items/itkoopaflame.h>
#include <melee/lb/lb_00B0.h>

static inline void ftKp_SpecialHi_Enter_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKp_Init_80132B38;
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKp_Init_80132B38;
}

void ftKp_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x167, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialHi_Enter_inline(gobj);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->self_vel.y = 0.0f;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->mv.co.capturekoopa.xC = 0.0f;
    fp->mv.kp.specials.x10 = 0;
    efSync_Spawn(0x4DA, gobj, fp->parts->joint);
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
}

void ftKp_SpecialAirHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x168, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialHi_Enter_inline(gobj);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_ClampGrVel(fp, da->x60);
    fp->self_vel.y = da->x54;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->mv.co.capturekoopa.xC = 0.0f;
    fp->mv.kp.specials.x10 = 0;
    efSync_Spawn(0x4DA, gobj, fp->parts->joint);
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
    ftKp_SpecialHi_Anim(gobj);
}

void ftKp_SpecialHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.walk.middle_anim_frame += 1.0f;
    ftKp_SpecialN_80135780(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialAirHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);

    fp->mv.co.walk.middle_anim_frame += 1.0f;
    ftKp_SpecialN_80135780(gobj);
    if (fp->cmd_vars[2] == 2) {
        if (fp->ground_or_air == GA_Air) {
            ftCommon_8007D60C(fp);
            efLib_DestroyAll(gobj);
            fp->x2219_b0 = false;
            fp->pre_hitlag_cb = NULL;
            fp->post_hitlag_cb = NULL;
            if (da->x7C == 0.0f) {
                ftCo_Fall_Enter(gobj);
            } else {
                ftCo_80096900(gobj, 1, 0, 1, 1.0f, da->x7C);
            }
        }
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (da->x7C == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0f, da->x7C);
        }
    }
}

void ftKp_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirHi_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialHi_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->cmd_vars[0] == 0) {
        ftCommon_8007CADC(fp, 0.0f, da->x68, da->x60);
        ftCommon_ApplyGroundMovement(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftKp_SpecialAirHi_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->cmd_vars[0] == 0) {
        ftCommon_Fall(fp, da->x58, da->x5C);
        ftCommon_8007D344(fp, 0.0f, da->x6C, da->x64);
    } else {
        ft_80084DB0(gobj);
    }
}

static void ftKp_SpecialHi_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[3] != 0) && (fp->mv.kp.specials.x10 != 0)) {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

void ftKp_SpecialHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, 0x168, 0x0C4C5292, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKp_SpecialHi_Enter_inline(gobj);
        ftCommon_ClampSelfVelX(fp, da->x64);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fp->mv.kp.specials.x10 = 0;
    } else {
        fp->mv.kp.specials.x10 = 1;
    }
    ftKp_SpecialN_80135780(gobj);
    ftKp_SpecialHi_Coll_inline(gobj);
}

static inline void ftKp_SpecialAirHi_Coll_inline(Fighter_GObj* gobj,
                                                 Fighter* fp,
                                                 ftKoopaAttributes* da)
{
    ftCommon_8007D7FC(fp);
    da->x70 = da->x70;
    if ((da->x70 < fp->mv.co.walk.middle_anim_frame) &&
        (fp->mv.co.walk.middle_anim_frame < da->x70))
    {
        Fighter_ChangeMotionState(gobj, 0x167, 0x0C4C5292,
                                  fp->cur_anim_frame - da->x78, 1.0f, 0.0f,
                                  NULL);
        ftKp_SpecialHi_Enter_inline(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x167, 0x0C4C5292, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKp_SpecialHi_Enter_inline(gobj);
    }
    ftCommon_ClampGrVel(fp, da->x60);
}

static inline void ftKp_SpecialAirHi_Coll_inline_2(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftKp_SpecialN_80135780(gobj);
    fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[3] != 0) && (fp->mv.kp.specials.x10 != 0)) {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

void ftKp_SpecialAirHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->self_vel.y >= 0.0f) {
        if (ft_80081D0C(gobj) != GA_Ground) {
            ftKp_SpecialAirHi_Coll_inline(gobj, fp, da);
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
            fp->mv.kp.specials.x10 = 1;
        } else {
            fp->mv.kp.specials.x10 = 0;
        }
        ftKp_SpecialAirHi_Coll_inline_2(gobj);
    } else if (ft_CheckGroundAndLedge(gobj, 0) != 0) {
        ftKp_SpecialAirHi_Coll_inline(gobj, fp, da);
        fp->mv.kp.specials.x10 = 1;
        ftKp_SpecialAirHi_Coll_inline_2(gobj);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    } else {
        fp->mv.kp.specials.x10 = 0;
        if (ftCliffCommon_80081298(gobj) != 0) {
            ftCliffCommon_80081370(gobj);
        }
    }
}
