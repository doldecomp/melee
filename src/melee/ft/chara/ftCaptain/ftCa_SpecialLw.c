#include <platform.h>
#include <dolphin/mtx/forward.h>

#include "ftCaptain/ftCa_SpecialLw.h"

#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"

#include <common_structs.h>
#include <placeholder.h>

/* literal */ float const ftCa_SpecialHi_804D9220 = 0;
/* literal */ float const ftCa_SpecialHi_804D9224 = 0.01745329238474369f;
/* literal */ float const ftCa_SpecialHi_804D9228 = 1;
/* literal */ float const ftCa_SpecialHi_804D922C = -1;

static void ftCa_SpecialHi_800E3EAC(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

static void ftCa_SpecialHi_800E400C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = getFtSpecialAttrsD(fp);
    if (fp->mv.ca.speciallw.x0 <= da->speciallw_unk2) {
        ++fp->mv.ca.speciallw.x0;
        fp->mv.ca.speciallw.friction *= da->speciallw_on_hit_spd_modifier;
    }
}

void ftCa_SpecialLw_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->mv.ca.speciallw.x0 = 0;
    fp->mv.ca.speciallw.friction = 1;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLw, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->deal_dmg_cb = ftCa_SpecialHi_800E400C;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftCa_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLw, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftCa_SpecialLw_Anim(HSD_GObj* gobj)
{
    u8 _[32];
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            Fighter* fp = GET_FIGHTER(gobj);
            ftCaptain_DatAttrs* da = fp->dat_attrs;
            fp->cmd_vars[2] = 0;
            fp->cmd_vars[1] = 0;
            fp->cmd_vars[0] = 0;
            fp->throw_flags = 0;
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEnd, Ft_MF_None,
                                      0, da->speciallw_ground_lag_mul, 0,
                                      NULL);
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        } else {
            Fighter* fp = GET_FIGHTER(gobj);
            fp->cmd_vars[2] = 0;
            fp->cmd_vars[1] = 0;
            fp->cmd_vars[0] = 0;
            fp->throw_flags = 0;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEndAir,
                                      Ft_MF_None, 0, 1, 0, NULL);
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        }
    }
}

void ftCa_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCa_SpecialLwEndAir_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCa_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->throw_flags = 0;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEndAir, Ft_MF_None,
                                  0, 1, 0, NULL);
    }
}

void ftCa_SpecialAirLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCa_SpecialAirLwEndAir_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftCa_SpecialHiThrow1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftCa_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC((Fighter*) fp);
        ft_80085088(gobj);
    } else {
        ftParts_80075CB4((Fighter*) fp, 0, 0);
        ft_80085134(gobj);
    }
    {
        float friction = fp->mv.ca.speciallw.friction;
        fp->self_vel.x *= friction;
        fp->self_vel.y *= friction;
    }
    ftCa_SpecialHi_800E3EAC(gobj);
}

void ftCa_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = gobj->user_data;
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        if (fp->cmd_vars[2] != 0) {
            ftCommon_8007C930(fp, da->speciallw_ground_traction *
                                      fp->co_attrs.gr_friction);
            ftCommon_8007CB74(gobj);
        } else {
            ft_80084F3C(gobj);
        }
    } else {
        ftParts_80075CB4(fp, 0, 0);
        ft_80084EEC(gobj);
    }
    {
        float friction = fp->mv.ca.speciallw.friction;
        fp->self_vel.x *= friction;
        fp->self_vel.y *= friction;
    }
}

void ftCa_SpecialLwEndAir_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        ft_80085088(gobj);
        return;
    }
    ftParts_80075CB4(fp, 0, 0);
    if (fp->cmd_vars[0] != 0) {
        ft_80084EEC(gobj);
    } else {
        ft_80085134(gobj);
    }
}

void ftCa_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
    ftCa_SpecialHi_800E3EAC(gobj);
}

void ftCa_SpecialAirLwEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[2] != 0) {
        ftCommon_8007C930(fp, da->speciallw_air_landing_traction *
                                  fp->co_attrs.gr_friction);
        ftCommon_8007CB74(gobj);
        return;
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCa_SpecialAirLwEndAir_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCa_SpecialHiThrow1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCa_SpecialLw_Coll(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if ((s32) fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == 0) {
            ftCommon_8007D5D4((Fighter*) fp);
        }
    } else if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC((Fighter*) fp);
    }
    {
        float facing_dir;
        if ((fp->cmd_vars[0] != 0) &&
            /// @todo Pull out these check functions
            (((facing_dir = fp->facing_dir, ((facing_dir == -1) != 0)) &&
              (fp->coll_data.env_flags & MPCOLL_FLAGS_B11)) ||
             (facing_dir == +1 &&
              (fp->coll_data.env_flags & MPCOLL_FLAGS_B05))))
        {
            Fighter* fp = GET_FIGHTER(gobj);
            fp->cmd_vars[2] = 0;
            fp->cmd_vars[1] = 0;
            fp->cmd_vars[0] = 0;
            fp->throw_flags = 0;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiThrow1,
                                      Ft_MF_None, 0, 1, 0, NULL);
        }
    }
}

void ftCa_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        if (fp->cmd_vars[1] != 0) {
            if (!ft_800827A0(gobj)) {
                ftCommon_8007D5D4(fp);
            }
        } else if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}

void ftCa_SpecialLwEndAir_Coll(Fighter_GObj* gobj)
{
    ftCa_SpecialLwEnd_Coll(gobj);
}

void ftCa_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    u8 _[24];
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->throw_flags = 0;
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEnd, Ft_MF_None, 0,
                                  da->speciallw_landing_lag_mul, 0, NULL);
    }
}

void ftCa_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCa_SpecialAirLwEndAir_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        fp->cmd_vars[2] = 0;
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->throw_flags = 0;
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEnd, Ft_MF_None, 0,
                                  da->speciallw_landing_lag_mul, 0, NULL);
    }
}
