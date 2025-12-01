
#include "ftCaptain/ftCa_SpecialLw.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCaptain/forward.h"

#include "ftCaptain/types.h"
#include "ftCommon/ftCo_Fall.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

// /* literal */ float const ftCa_SpecialHi_804D9220 = 0.0F;
// /* literal */ float const ftCa_SpecialHi_804D9224 = 0.01745329238474369f;
// /* literal */ float const ftCa_SpecialHi_804D9228 = 1;
// /* literal */ float const ftCa_SpecialHi_804D922C = -1;

static inline bool ftCa_Special_Inline_Check_Flag(Fighter* fp)
{
    if (fp->throw_flags_b1) {
        fp->throw_flags_b1 = 0;
        return 1;
    } else {
        return 0;
    }
}

static inline void ftCa_Special_Inline_SetFlags(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
}

void ftCa_SpecialHi_800E3EAC(HSD_GObj* gobj)
{
    f32 sp1C;
    enum Fighter_Part var_r29;

    // var_r29 = saved_reg_r29;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(12);
    if (ftCa_Special_Inline_Check_Flag(fp) != 0) {
        if (!fp->x2219_b0) {
            if (fp->motion_id == 0x165) {
                sp1C = 0.0F;
                var_r29 = ftParts_GetBoneIndex(fp, FtPart_RFootJA);
            } else if (fp->motion_id == 0x167) {
                sp1C = 0.017453292f * da->speciallw_flame_particle_angle;
                var_r29 = ftParts_GetBoneIndex(fp, FtPart_LFootJA);
            }
            switch (ftLib_800872A4(gobj)) {
            case FTKIND_CAPTAIN:
                efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3U, 0x490U,
                              fp->parts[var_r29].joint, &sp1C);
                break;
            case FTKIND_GANON:
                efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3U, 0x50CU,
                              fp->parts[var_r29].joint, &sp1C);
                break;
            }
            fp->x2219_b0 = 1;
            return;
        }
        ftCommon_8007DB24((Fighter_GObj*) gobj);
    }
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
    fp->mv.ca.speciallw.x0 = 0.0F;
    fp->mv.ca.speciallw.friction = 1.0F;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLw, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
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

static inline void ftCa_SpecialLw_Anim_inline(HSD_GObj* gobj, s32 condition)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    if (condition == 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEnd, Ft_MF_None, 0,
                                  da->speciallw_ground_lag_mul, 0, NULL);
    } else {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEndAir, Ft_MF_None, 0,
                                  1, 0, NULL);
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftCa_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            ftCa_SpecialLw_Anim_inline(gobj, 0);
        } else {
            ftCa_SpecialLw_Anim_inline(gobj, 1);
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

static inline void ftCa_SpecialAirLw_Anim_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
}

void ftCa_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCa_SpecialAirLw_Anim_inline(gobj);
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
        ftCo_Fall_Enter(gobj);
    }
}

void ftCa_SpecialHiThrow1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

static inline void ftCa_Special_Inline_Friction(Fighter* fp)
{
    float friction = fp->mv.ca.speciallw.friction;
    fp->self_vel.x *= friction;
    fp->self_vel.y *= friction;
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
    ftCa_Special_Inline_Friction(fp);
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
            ftCommon_ApplyFrictionGround(fp, da->speciallw_ground_traction *
                                                 fp->co_attrs.gr_friction);
            ftCommon_ApplyGroundMovement(gobj);
        } else {
            ft_80084F3C(gobj);
        }
    } else {
        ftParts_80075CB4(fp, 0, 0.0F);
        ft_80084EEC(gobj);
    }
    ftCa_Special_Inline_Friction(fp);
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
    ftCo_DatAttrs* ca;
    ftCaptain_DatAttrs* da;

    Fighter* fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    if (fp->cmd_vars[2] != 0) {
        ca = getFtAttrs(fp);
        ftCommon_ApplyFrictionGround(fp, da->speciallw_air_landing_traction *
                                             ca->gr_friction);
        ftCommon_ApplyGroundMovement(gobj);
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
        if ((fp->cmd_vars[0] != 0) &&
            /// @todo Pull out these check functions
            (((((fp->facing_dir == -1) != 0)) &&
              (fp->coll_data.env_flags & Collide_RightWallHug)) ||
             (fp->facing_dir == +1 &&
              (fp->coll_data.env_flags & Collide_LeftWallHug))))
        {
            fp = GET_FIGHTER(gobj);
            ftCa_Special_Inline_SetFlags(gobj);
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

static void resetCmdAndThrow(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = 0;
    fp->throw_flags = 0;
}

static void doColl(Fighter_GObj* gobj, ftCaptain_MotionState msid)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        PAD_STACK(4 * 4);
        resetCmdAndThrow(gobj);
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0,
                                  da->speciallw_landing_lag_mul, 0, NULL);
    }
}

void ftCa_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 4);
    doColl(gobj, ftCa_MS_SpecialAirLwEnd);
}

void ftCa_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCa_SpecialAirLwEndAir_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 4);
    doColl(gobj, ftCa_MS_SpecialAirLwEnd);
}
