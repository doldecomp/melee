#include "ftMr_SpecialLw.h"

#include "inlines.h"
#include "types.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "lb/lbrefract.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

static void updateRot(HSD_GObj* gobj)
{
    Fighter* fp;
    fp = GET_FIGHTER(gobj);

    ftPartSetRotX(fp, 0, 0);
}

static void setGfx(HSD_GObj* gobj)
{
    void* hsd_obj_ptr;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    hsd_obj_ptr = gobj->hsd_obj;

    efSync_Spawn(0x47C, gobj, hsd_obj_ptr);
    fp->x2219_b0 = 1;
    fp->pre_hitlag_cb = &efLib_PauseAll;
    fp->post_hitlag_cb = &efLib_ResumeAll;
}

static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = &updateRot;
    fp->death2_cb = &updateRot;
}

static void doStartMotion(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    sa = (ftMario_DatAttrs*) fp->dat_attrs;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->mv.mr.SpecialLw.groundVelX = (float) 0;
    fp->mv.mr.SpecialLw.unk = (s32) (sa->speciallw.unk0 + 1);
    fp->mv.mr.SpecialLw.isUnkColl = 0;
    setCallbacks(gobj);
    setGfx(gobj);
}

static void setCmdVar2(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[2] = 0;
}

void ftMr_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMario_DatAttrs* sa = fp->dat_attrs;

    u8 _[28];

    setCmdVar2(gobj);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirLw, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    fp->self_vel.y = sa->speciallw.vel_y - sa->speciallw.tap_y_vel_max;
    ftCommon_ClampSelfVelX(fp, sa->speciallw.air_momentum_x);
    doStartMotion(gobj);
    fp->pre_hitlag_cb = &efLib_PauseAll;
    fp->post_hitlag_cb = &efLib_ResumeAll;
}

void ftMr_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    float sub_val;
    Fighter* fp = gobj->user_data;
    ftMario_DatAttrs* sa = fp->dat_attrs;

    u8 _[28];

    setCmdVar2(gobj);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirLw, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    if ((s32) fp->fv.mr.x2234_tornadoCharge != 0) {
        sub_val = 0;
    } else {
        sub_val = sa->speciallw.tap_y_vel_max;
    }
    fp->self_vel.y = (float) (sa->speciallw.vel_y - sub_val);
    ftCommon_ClampSelfVelX(fp, sa->speciallw.air_momentum_x);
    doStartMotion(gobj);
    fp->pre_hitlag_cb = &efLib_PauseAll;
    fp->post_hitlag_cb = &efLib_ResumeAll;
}

static void unsetCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

void ftMr_SpecialLw_Anim(HSD_GObj* gobj)
{
    u8 _[4];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        unsetCallbacks(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftMr_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = (ftMario_DatAttrs*) fp->dat_attrs;

    if ((u32) fp->cmd_vars[1] != 0U) {
        fp->cmd_vars[1] = 0U;
        fp->fv.mr.x2234_tornadoCharge = 1;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        unsetCallbacks(gobj);
        if (0.0 == (f64) sa->speciallw.landing_lag) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, true, 1, (float) sa->speciallw.landing_lag);
    }
}

void ftMr_SpecialLw_IASA(HSD_GObj* gobj) {}

void ftMr_SpecialAirLw_IASA(HSD_GObj* gobj) {}

static usize_t const transition_flags =
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static void doPhys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp);
    fp->cmd_vars[2] = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirLw, transition_flags,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftCommon_ClampFallSpeed(fp, sa->speciallw.tap_grav);
    ftCommon_ClampSelfVelX(fp, sa->speciallw.air_momentum_x);
    fp->pre_hitlag_cb = &efLib_PauseAll;
    fp->post_hitlag_cb = &efLib_ResumeAll;
}

void ftMr_SpecialLw_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp0 = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp0);
    float vel_y = sa->speciallw.momentum_x;

    if (fp0->cmd_vars[0] != 0) {
        fp0->mv.mr.SpecialLw.groundVelX =
            fp0->mv.mr.SpecialLw.groundVelX - sa->speciallw.friction_end;
        vel_y += fp0->mv.mr.SpecialLw.groundVelX;
        if (vel_y < 0) {
            vel_y = 0;
        }
    }

    {
        Fighter* fp1 = fp0;
        ftCommon_8007CADC(fp1, 0, sa->speciallw.momentum_x_mul, vel_y);
        ftCommon_ApplyGroundMovement(gobj);
        if (fp0->cmd_vars[2] != 0 && (fp0->input.x668 & HSD_PAD_B)) {
            vel_y = fp0->self_vel.y;
            fp0->self_vel.y = vel_y + sa->speciallw.tap_y_vel_max;
            doPhys(gobj);
        }
    }
}

void ftMr_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    float flt_var;
    ftMario_DatAttrs* sa;
    ftMario_DatAttrs* sa_2;
    Fighter* fp;

    u8 _[8];

    fp = getFighter(gobj);
    sa = fp->dat_attrs;

    if (((s32) fp->fv.mr.x2234_tornadoCharge == false) &&
        ((u32) fp->cmd_vars[2] != 0U) && ((fp->input.x668 & HSD_PAD_B) != 0))
    {
        ftCommon_Ascend(fp, sa->speciallw.tap_y_vel_max,
                        sa->speciallw.tap_grav);
    }
    ftCommon_FallBasic(fp);
    flt_var = sa->speciallw.air_momentum_x;
    sa_2 = fp->dat_attrs;
    if ((u32) fp->cmd_vars[0] != 0U) {
        fp->mv.mr.SpecialLw.groundVelX =
            (float) (fp->mv.mr.SpecialLw.groundVelX -
                     sa_2->speciallw.friction_end);
        flt_var += fp->mv.mr.SpecialLw.groundVelX;
        if (flt_var < 0) {
            flt_var = 0;
        }
    }
    ftCommon_8007D3A8(fp, 0, sa->speciallw.air_momentum_x_mul, flt_var);
}

static void doColl(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    if ((fp->cmd_vars[3] != 0U) &&
        ((s32) (fp->mv.mr.SpecialLw.isUnkColl) != 0))
    {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0);
    }
}

static ftCollisionBox coll_box = { 12, 0, { -6, +6 }, { +6, +6 } };

void ftMr_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[24];

    if (fp->ground_or_air == GA_Ground) {
        if (ft_80082888(gobj, &coll_box) == false) {
            doPhys(gobj);
            fp->mv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->mv.mr.SpecialLw.isUnkColl = true;
        }
    } else {
        if (ft_800824A0(gobj, &coll_box) == false) {
            doPhys(gobj);
            fp->mv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->mv.mr.SpecialLw.isUnkColl = true;
        }
    }

    doColl(gobj);
}

static void doAirCollIfUnk(HSD_GObj* gobj)
{
    Fighter* ft_tmp;
    Fighter* fp;
    ftMario_DatAttrs* sa;
    fp = getFighter(gobj);
    sa = GetMarioAttr(fp);
    fp->cmd_vars[2] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0;
    fp->fv.mr.x2234_tornadoCharge = 0;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialLw, transition_flags,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftCommon_ClampGrVel(ft_tmp = fp, sa->speciallw.momentum_x);
    fp->pre_hitlag_cb = &efLib_PauseAll;
    fp->post_hitlag_cb = &efLib_ResumeAll;
}

void ftMr_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800824A0(gobj, &coll_box)) {
        doAirCollIfUnk(gobj);
        fp->mv.mr.SpecialLw.isUnkColl = true;
    } else {
        fp->mv.mr.SpecialLw.isUnkColl = false;
    }

    doColl(gobj);
}
