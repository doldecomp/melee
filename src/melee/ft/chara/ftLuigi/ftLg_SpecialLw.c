#include <platform.h>

#include "forward.h"
#include "ftCommon/forward.h"

#include "ftLg_SpecialLw.h"

#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "lb/lbrefract.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

// SpecialLw (Luigi Cyclone)
#define FTLUIGI_SPECIALLW_FLAG                                                \
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_UpdateCmd |     \
        Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |                 \
        Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27

// 0x801445C4
// https://decomp.me/scratch/TTyNT // Luigi Cyclone Rotation Update
void ftLg_SpecialLw_UpdateRot(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_8007592C(fp, 0, 0.0f);
}

static inline void ftLuigi_SpecialLw_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* luigiAttrs = fp->dat_attrs;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->mv.lg.SpecialLw.groundVelX = (float) 0.0f;
    fp->mv.lg.SpecialLw.unk = (s32) luigiAttrs->x88_LUIGI_CYCLONE_UNK + 1;
    fp->mv.lg.SpecialLw.isUnkColl = false;
}

static inline void ftLuigi_SpecialLw_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftLg_SpecialLw_UpdateRot;
    fp->death2_cb = ftLg_SpecialLw_UpdateRot;
}

static inline void ftLuigi_SpecialLw_SetGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* hsd_obj = gobj->hsd_obj;
    efSync_Spawn(0x509, gobj, hsd_obj);
    fp->x2219_b0 = 1;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

// 0x801445F0
// https://decomp.me/scratch/ // Luigi's grounded Cyclone Motion State handler
void ftLg_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    Fighter* temp_fp;
    Fighter* fp2;

    u8 _[20];

    temp_fp = (fp = GET_FIGHTER(gobj));
    luigiAttrs = temp_fp->dat_attrs;
    fp2 = temp_fp;
    GET_FIGHTER(gobj)->cmd_vars[2] = 0;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirLw, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp2->self_vel.y = (float) (luigiAttrs->x70_LUIGI_CYCLONE_TAP_MOMENTUM -
                               luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX);
    ftCommon_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    ftLuigi_SpecialLw_SetVars(gobj);
    ftLuigi_SpecialLw_SetCall(gobj);
    ftLuigi_SpecialLw_SetGFX(gobj);
    fp2->pre_hitlag_cb = efLib_PauseAll;
    fp2->post_hitlag_cb = efLib_ResumeAll;
}

// 0x80144708
// https://decomp.me/scratch/egaIB // Luigi's aerial Cyclone Motion State
// handler
void ftLg_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    Fighter* temp_fp;
    Fighter* fp2;
    float cycloneVar;

    u8 _[16];

    temp_fp = (fp = GET_FIGHTER(gobj));
    luigiAttrs = temp_fp->dat_attrs;
    fp2 = temp_fp;
    GET_FIGHTER(gobj)->cmd_vars[2] = 0;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirLw, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    if (fp2->fv.lg.x222C_cycloneCharge != 0) {
        cycloneVar = 0.0f;
    } else {
        cycloneVar = luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
    }
    fp2->self_vel.y =
        (float) (luigiAttrs->x70_LUIGI_CYCLONE_TAP_MOMENTUM - cycloneVar);
    ftCommon_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    ftLuigi_SpecialLw_SetVars(gobj);
    ftLuigi_SpecialLw_SetCall(gobj);
    ftLuigi_SpecialLw_SetGFX(gobj);
    fp2->pre_hitlag_cb = efLib_PauseAll;
    fp2->post_hitlag_cb = efLib_ResumeAll;
}

static inline void ftLuigi_SpecialLw_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

/// Luigi's grounded Cyclone Animation callback
void ftLg_SpecialLw_Anim(HSD_GObj* gobj)
{
    u8 _[4];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLuigi_SpecialLw_SetNULL(gobj);
        ft_8008A2BC(gobj);
    }
}

/// Luigi's aerial Cyclone Animation callback
void ftLg_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* attrs = getFtSpecialAttrsD(fp);

    if (fp->cmd_vars[1] != 0) {
        fp->cmd_vars[1] = 0;
        fp->fv.lg.x222C_cycloneCharge = true;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLuigi_SpecialLw_SetNULL(gobj);
        {
            int landing_lag = attrs->x94_LUIGI_CYCLONE_LANDING_LAG;

            if (landing_lag == 0.0) {
                ftCo_800CC730(gobj);
                return;
            }

            ftCo_80096900(gobj, 1, 0, 1, 1, (float) landing_lag);
        }
    }
}

/// Luigi's grounded Cyclone IASA callback
void ftLg_SpecialLw_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Cyclone IASA callback
void ftLg_SpecialAirLw_IASA(HSD_GObj* gobj) {}

static inline void ftLuigi_SpecialLw_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    fp->cmd_vars[2] = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x166, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftCommon_ClampFallSpeed(fp, luigiAttrs->x90_LUIGI_CYCLONE_TAP_GRAVITY);
    ftCommon_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

// 0x80144958
// https://decomp.me/scratch/pXs3o // Luigi's grounded Cyclone Physics callback
void ftLg_SpecialLw_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* attrs = getFtSpecialAttrs(fp);

    {
        float var2 = attrs->x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND;

        if (fp->cmd_vars[0] != 0) {
            fp->mv.lg.SpecialLw.groundVelX -=
                attrs->x84_LUIGI_CYCLONE_FRICTION_END;
            var2 += fp->mv.lg.SpecialLw.groundVelX;

            if (var2 < 0) {
                var2 = 0;
            }
        }

        ftCommon_8007CADC(
            fp, 0, attrs->x7C_LUIGI_CYCLONE_MOMENTUM_X_MUL_GROUND, var2);
    }

    ftCommon_8007CB74(gobj);

    if (fp->cmd_vars[2] != 0 && (fp->input.x668 & HSD_PAD_B)) {
        fp->self_vel.y += attrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
        ftLuigi_SpecialLw_GroundToAir(gobj);
    }
}

// 0x80144A74C
// https://decomp.me/scratch/85hbq // Luigi's aerial Cyclone Physics callback
void ftLg_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* attrs0 = fp->dat_attrs;

    if (!fp->fv.lg.x222C_cycloneCharge && fp->cmd_vars[2] != 0 &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftCommon_8007D508(fp, attrs0->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX,
                          attrs0->x90_LUIGI_CYCLONE_TAP_GRAVITY);
    }

    ftCommon_8007D4B8(fp);

    {
        float spd_x = attrs0->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR;

        {
            ftLuigiAttributes* attrs1 = fp->dat_attrs;

            if (fp->cmd_vars[0] != 0) {
                fp->mv.lg.SpecialLw.groundVelX -=
                    attrs1->x84_LUIGI_CYCLONE_FRICTION_END;
                spd_x += fp->mv.lg.SpecialLw.groundVelX;

                if (spd_x < 0) {
                    spd_x = 0;
                }
            }
        }

        ftCommon_8007D3A8(fp, 0, attrs0->x80_LUIGI_CYCLONE_MOMENTUM_X_MUL_AIR,
                          spd_x);
    }
}

static ftCollisionBox ftLg_SpecialLw_CollisionBox = {
    12, 0, { -6, +6 }, { +6, +6 }
};

static inline void ftLuigi_SpecialLw_UnkAngle(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (((u32) fp->cmd_vars[3] != 0U) &&
        ((s32) fp->mv.lg.SpecialLw.isUnkColl != false))
    {
        ftParts_8007592C(fp, 0,
                         fp->facing_dir *
                             atan2f(fp->coll_data.floor.normal.x,
                                    fp->coll_data.floor.normal.y));
        return;
    }
    ftParts_8007592C(fp, 0, 0.0f);
}

/// Luigi's grounded Cyclone Collision callback
void ftLg_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[20];

    if (fp->ground_or_air == GA_Ground) {
        if (!ft_80082888(gobj, &ftLg_SpecialLw_CollisionBox)) {
            ftLuigi_SpecialLw_GroundToAir(gobj);
            fp->mv.lg.SpecialLw.isUnkColl = false;
        } else {
            fp->mv.lg.SpecialLw.isUnkColl = true;
        }
    } else if (ft_800824A0(gobj, &ftLg_SpecialLw_CollisionBox) == false) {
        ftLuigi_SpecialLw_GroundToAir(gobj);
        fp->mv.lg.SpecialLw.isUnkColl = false;
    } else {
        fp->mv.lg.SpecialLw.isUnkColl = true;
    }

    ftLuigi_SpecialLw_UnkAngle(gobj);
}

static inline void ftLuigi_SpecialAirLw_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* luigiAttrs = fp->dat_attrs;
    fp->cmd_vars[2] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0.0f;
    fp->fv.lg.x222C_cycloneCharge = false;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialLw, FTLUIGI_SPECIALLW_FLAG,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftCommon_8007CC78(fp, luigiAttrs->x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

// 0x80144CEC
// https://decomp.me/scratch/fdQ4f // Luigi's aerial Cyclone Collision callback
void ftLg_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[24];

    if (ft_800824A0(gobj, &ftLg_SpecialLw_CollisionBox) != false) {
        ftLuigi_SpecialAirLw_AirToGround(gobj);
        fp->mv.lg.SpecialLw.isUnkColl = true;
    } else {
        fp->mv.lg.SpecialLw.isUnkColl = false;
    }
    ftLuigi_SpecialLw_UnkAngle(gobj);
}
