#include "ftCa_SpecialHi.h"

#include "math.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"
#include "ftCommon/ftCo_CaptureCaptain.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Thrown.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftCa_SpecialHiThrow1_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

static void ftCa_SpecialLw_800E49FC(HSD_GObj* gobj)
{
    u8 _[16];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->mv.ca.specialhi.x0 = da->specialhi_air_var;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = da->specialhi_unk2;
    fp->mv.ca.specialhi.vel.x = 0;
    fp->mv.ca.specialhi.vel.y = 0;
    fp->mv.ca.specialhi.x2_b0 = false;
    fp->mv.ca.specialhi.x2_b1 = false;
}

static void ftCa_SpecialLw_800E5128(HSD_GObj*);

void ftCa_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x21EC = ftCa_SpecialLw_800E49FC;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHi, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007E2D0(fp, 2, ftCa_SpecialLw_800E5128, NULL, ftCo_8009CA0C);
    ftAnim_8006EBA4(gobj);
}

void ftCa_SpecialHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* temp_r31 = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 1, false,
                      temp_r31->specialhi_freefall_air_spd_mul,
                      temp_r31->specialhi_landing_lag);
    }
}

void ftCa_SpecialHi_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        fp->cmd_vars[0] = 0;
        fp->mv.ca.specialhi.x2_b1 = true;
        {
            float lstick_x = fp->input.lstick.x;
            if (lstick_x < 0) {
                lstick_x = -lstick_x;
            }
            if (lstick_x > da->specialhi_input_var) {
                ftCommon_8007D9FC(fp);
                ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftCa_SpecialHi_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    fp->self_vel.x = fp->mv.ca.specialhi.vel.x;
    fp->self_vel.y = fp->mv.ca.specialhi.vel.y;
    fp->self_vel.z = 0;
    if (!ftCommon_8007D050(fp, da->specialhi_horz_vel * ca->air_drift_max)) {
        ftCommon_8007D3A8(fp, p_ftCommonData->x258,
                          ca->air_drift_stick_mul *
                              da->specialhi_air_friction_mul,
                          ca->air_drift_max * da->specialhi_horz_vel);
    }
    fp->mv.ca.specialhi.vel.x = fp->x74_anim_vel.x + fp->self_vel.x;
    fp->mv.ca.specialhi.vel.y = fp->x74_anim_vel.y + fp->self_vel.y;
    ft_80085134(gobj);
    fp->x74_anim_vel.x = fp->x74_anim_vel.y = 0;
    fp->self_vel.x = fp->self_vel.x + fp->mv.ca.specialhi.vel.x;
    fp->self_vel.y = fp->self_vel.y + fp->mv.ca.specialhi.vel.y;
}

void ftCa_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x21EC = ftCa_SpecialLw_800E49FC;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirHi, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007E2D0(fp, 2, ftCa_SpecialLw_800E5128, NULL, ftCo_8009CA0C);
    ftAnim_8006EBA4(gobj);
}

static void doAirColl(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        if (fp->mv.ca.specialhi.x2_b1) {
            ftCo_LandingFallSpecial_Enter(gobj, false,
                                          da->specialhi_landing_lag);
        } else {
            ft_80083B68(gobj);
        }
    } else if (fp->mv.ca.specialhi.x2_b1 && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftCa_SpecialHi_Coll(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        doAirColl(gobj);
    } else if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
    }
}

void ftCa_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    u8 _[24];
    ftCaptain_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 1, false, da->specialhi_freefall_air_spd_mul,
                      da->specialhi_landing_lag);
    }
}

static void doAirIASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    fp->cmd_vars[0] = 0;
    fp->mv.ca.specialhi.x2_b1 = true;
    {
        float lstick_x = fp->input.lstick.x;
        if (lstick_x < 0) {
            lstick_x = -lstick_x;
        }
        if (lstick_x > da->specialhi_input_var) {
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
        }
    }
}
void ftCa_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    if (temp_r31->cmd_vars[0]) {
        doAirIASA(gobj);
    }
}

void ftCa_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    PAD_STACK(28);
    ftCa_SpecialHi_Phys(gobj);
}

void ftCa_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    ftCa_SpecialHi_Coll(gobj);
}

static void ftCa_SpecialLw_800E550C(HSD_GObj*);

void ftCa_SpecialLw_800E5128(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* vic_fp = GET_FIGHTER(fp->victim_gobj);
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiCatch, 2, 0, 1, 0, NULL);
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    if (vic_fp->ground_or_air == GA_Air) {
        fp->x221B_b7 = false;
    } else {
        ftCo_800DB368(vic_fp, fp);
        fp->x221B_b7 = true;
        fp->accessory4_cb = ftCa_SpecialLw_800E550C;
    }
}

static void doCatchAnim(HSD_GObj* gobj);

void ftCa_SpecialHiCatch_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        doCatchAnim(gobj);
    }
}

void ftCa_SpecialHiCatch_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialHiCatch_Phys(HSD_GObj* gobj) {}

void ftCa_SpecialHiCatch_Coll(HSD_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221B_b7) {
        ft_80083B68(gobj);
    }
}

static void doCatchAnim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* vic_gobj = fp->victim_gobj;
    fp->cmd_vars[0] = 0;
    fp->mv.ca.specialhi.x2_b0 = false;
    fp->mv.ca.specialhi.vel.x = 0;
    fp->mv.ca.specialhi.vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiThrow,
                              Ft_MF_Unk19 | Ft_MF_KeepGfx, 0, 1, 0, NULL);
    ftCommon_8007E2F4(fp, 0);
    ftCo_800DE2A8(gobj, vic_gobj);
    ftCo_800DE7C0(vic_gobj, 0, 0);
}

void ftCa_SpecialHiThrow0_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
    ftCommon_8007D60C(fp);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        fp->mv.ca.specialhi.x2_b0 = true;
    }
}

void ftCa_SpecialHiThrow0_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialHiThrow0_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca;
    PAD_STACK(32);
    if (fp->mv.ca.specialhi.x2_b0) {
        ftCa_SpecialHi_Phys(gobj);
        ca = &fp->co_attrs;
        {
            float vel_y = fp->self_vel.y - fp->mv.ca.specialhi.vel.y;
            ftCommon_8007D494(fp, da->specialhi_catch_grav, ca->terminal_vel);
            fp->mv.ca.specialhi.vel.y = fp->self_vel.y - vel_y;
        }
    } else {
        ft_80085134(gobj);
    }
}

void ftCa_SpecialHiThrow0_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (ft_80081D0C(gobj)) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->specialhi_landing_lag);
    }
}

static void ftCa_SpecialLw_800E550C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* vic_fp = GET_FIGHTER(fp->victim_gobj);
    fp->cur_pos = vic_fp->cur_pos;
}
