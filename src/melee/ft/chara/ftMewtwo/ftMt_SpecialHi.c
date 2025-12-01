#include "ftMt_SpecialHi.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftMewtwo/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MSL/math.h>
#include <MSL/math_ppc.h>

/// Create Teleport Start GFX
void ftMt_SpecialHi_CreateGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMt_SpecialHi_SetStartGFX(gobj);
    fp->accessory4_cb = NULL;
}

/// Setup Teleport Start GFX
void ftMt_SpecialHi_SetStartGFX(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        Vec3 pos;

        if (!fp1->x2219_b0) {
            lb_8000B1CC(fp1->parts[FtPart_WaistN].joint, NULL, &pos);
            efSync_Spawn(0x4E8, gobj, &pos);
            fp1->x2219_b0 = true;
        }
    }

    fp0->pre_hitlag_cb = efLib_PauseAll;
    fp0->post_hitlag_cb = efLib_ResumeAll;
}

/// Setup Teleport End GFX
void ftMt_SpecialHi_SetEndGFX(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        Vec3 pos;

        if (!fp1->x2219_b0) {
            lb_8000B1CC(fp1->parts[FtPart_WaistN].joint, NULL, &pos);
            fp1->x2219_b0 = true;
        }
    }

    fp0->pre_hitlag_cb = efLib_PauseAll;
    fp0->post_hitlag_cb = efLib_ResumeAll;
    fp0->accessory4_cb = NULL;
}

/// Mewtwo's grounded Teleport Start Motion State handler
void ftMt_SpecialHiStart_Enter(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        fp1->gr_vel = 0;
        fp1->self_vel.y = 0;
        fp1->self_vel.x = 0;
    }

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialHiStart, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    fp0->cmd_vars[0] = 0;
    fp0->mv.mt.SpecialHi.unk4 = 0;
    fp0->accessory4_cb = ftMt_SpecialHi_CreateGFX;
}

/// Mewtwo's aerial Teleport Start Motion State handler
void ftMt_SpecialAirHiStart_Enter(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    fp->self_vel.x /= mewtwoAttrs->x40_MEWTWO_TELEPORT_VEL_DIV_X;
    fp->self_vel.y /= mewtwoAttrs->x44_MEWTWO_TELEPORT_VEL_DIV_Y;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirHiStart, 0, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);

    fp->cmd_vars[0] = 0;
    fp->mv.mt.SpecialHi.unk4 = 0;
    fp->accessory4_cb = ftMt_SpecialHi_CreateGFX;
}

/// Mewtwo's grounded Teleport Start Animation callback
void ftMt_SpecialHiStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMt_SpecialHi_Enter(gobj);
    }
}

/// Mewtwo's aerial Teleport Start Animation callback
void ftMt_SpecialAirHiStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMt_SpecialAirHi_Enter(gobj);
    }
}

// Mewtwo's grounded Teleport Start IASA callback
void ftMt_SpecialHiStart_IASA(HSD_GObj* gobj) {}

// Mewtwo's aerial Teleport Start IASA callback
void ftMt_SpecialAirHiStart_IASA(HSD_GObj* gobj) {}

// Mewtwo's grounded Teleport Start Physics callback
void ftMt_SpecialHiStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Mewtwo's aerial Teleport Start Physics callback
void ftMt_SpecialAirHiStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp0);

        ftCommon_Fall(fp1, mewtwoAttrs->x48_MEWTWO_TELEPORT_GRAVITY,
                      mewtwoAttrs->x4C_MEWTWO_TELEPORT_TERMINAL_VELOCITY);
    }

    ftCommon_8007CEF4(fp0);
}

/// Mewtwo's grounded Teleport Start Collision callback
void ftMt_SpecialHiStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftMt_SpecialHiStart_GroundToAir(gobj);
    }
}

/// Mewtwo's aerial Teleport Start Collision callback
void ftMt_SpecialAirHiStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_O(fp))) {
        ftMt_SpecialAirHiStart_AirToGround(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

static u32 const transition_flags0 =
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
    Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static u32 const transition_flags1 =
    transition_flags0 | Ft_MF_KeepColAnimHitStatus;

/// Mewtwo's ground -> air Teleport Start Motion State handler
void ftMt_SpecialHiStart_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirHiStart,
                              transition_flags1, fp->cur_anim_frame, 1, 0,
                              NULL);

    fp->accessory4_cb = ftMt_SpecialHi_CreateGFX;
}

/// Mewtwo's air -> ground Teleport Start Motion State handler
void ftMt_SpecialAirHiStart_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialHiStart, transition_flags1,
                              fp->cur_anim_frame, 1, 0, NULL);

    fp->accessory4_cb = ftMt_SpecialHi_CreateGFX;
}

/// Mewtwo's grounded Teleport Zoom Animation callback
void ftMt_SpecialHiLost_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.mt.SpecialHi.travelFrames--;

    if (fp->mv.mt.SpecialHi.travelFrames <= 0) {
        ftMt_SpecialHiLost_Enter(gobj);
    }
}

/// Mewtwo's aerial Teleport Zoom Animation callback
void ftMt_SpecialAirHiLost_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.mt.SpecialHi.travelFrames--;

    if (fp->mv.mt.SpecialHi.travelFrames <= 0) {
        ftMt_SpecialAirHiLost_Enter(gobj);
    }
}

// Mewtwo's grounded Teleport Zoom IASA callback
void ftMt_SpecialHiLost_IASA(HSD_GObj* gobj) {}

// Mewtwo's aerial Teleport Zoom IASA callback
void ftMt_SpecialAirHiLost_IASA(HSD_GObj* gobj) {}

// Mewtwo's grounded Teleport Zoom Physics callback
void ftMt_SpecialHiLost_Phys(HSD_GObj* gobj)
{
    ftCommon_ApplyGroundMovement(gobj);
}

// Mewtwo's aerial Teleport Zoom Physics callback
void ftMt_SpecialAirHiLost_Phys(HSD_GObj* gobj) {}

/// Mewtwo's grounded Teleport Zoom Collision callback
void ftMt_SpecialHiLost_Coll(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        CollData* collData = &fp0->coll_data;

        if (!ft_80082708(gobj)) {
            u32 env_flags = collData->env_flags;
            if (env_flags & Collide_LeftWallMask ||
                env_flags & Collide_RightWallMask)
            {
                ftCommon_8007D60C(fp1);
                ftMt_SpecialAirHiLost_Enter(gobj);
                return;
            } else {
                ftMt_SpecialHi_GroundToAir(gobj);
            }
        } else {
            u32 env_flags = collData->env_flags;
            if (env_flags & Collide_LeftWallMask ||
                env_flags & Collide_RightWallMask)
            {
                ftMt_SpecialHiLost_Enter(gobj);
            }
        }
    }
}

static bool ftMewtwo_SpecialHi_CheckTimer(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = fp->dat_attrs;

    if (fp->mv.mt.SpecialHi.unk4 >= mewtwoAttrs->x54_MEWTWO_TELEPORT_UNK2) {
        return true;
    }

    if (ftCo_8009A134(gobj)) {
        return false;
    }

    return true;
}

static bool ftMewtwo_SpecialHi_CheckTimer(HSD_GObj* gobj);

/// Mewtwo's aerial Teleport Zoom Collision callback
void ftMt_SpecialAirHiLost_Coll(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs =
            getFtSpecialAttrsD(fp0);
        CollData* collData = collData = getFtColl(fp1);
        fp0->mv.mt.SpecialHi.unk4++;

        if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_O(fp0))) {
            if (ftMewtwo_SpecialHi_CheckTimer(gobj)) {
                ftMt_SpecialAirHi_AirToGround(gobj);
                return;
            }
        }

        if (ftCliffCommon_80081298(gobj)) {
            return;
        }

        if ((collData->env_flags & Collide_CeilingMask) &&
            (lbVector_AngleXY(&collData->ceiling.normal, &fp1->self_vel) >
             deg_to_rad *
                 (90.0f + mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP)))
        {
            ftMt_SpecialAirHiLost_Enter(gobj);
        }

        if (collData->env_flags & Collide_LeftWallMask &&
            (lbVector_AngleXY(&collData->left_facing_wall.normal,
                              &fp1->self_vel) >
             deg_to_rad *
                 (90.0f + mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP)))
        {
            ftMt_SpecialAirHiLost_Enter(gobj);
        }

        if (collData->env_flags & Collide_RightWallMask &&
            lbVector_AngleXY(&collData->right_facing_wall.normal,
                             &fp1->self_vel) >
                deg_to_rad *
                    (90.0f + mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP))
        {
            ftMt_SpecialAirHiLost_Enter(gobj);
        }
    }
}

/// Mewtwo's ground -> air Teleport Zoom Motion State handler
void ftMt_SpecialHi_GroundToAir(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirHiLost,
                              transition_flags1, fp->cur_anim_frame, 0, 0,
                              NULL);

    fp->x2223_b4 = true;
    fp->invisible = true;
}

/// Mewtwo's air -> ground Teleport Zoom Motion State handler
void ftMt_SpecialAirHi_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialHiLost, transition_flags1,
                              fp->cur_anim_frame, 0, 0, NULL);

    fp->invisible = true;
}

static inline void ftMewtwo_SpecialHi_SetVars(HSD_GObj* gobj)
{
    /// @todo This is like three functions in one. Split it.
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    fp = GET_FIGHTER(gobj);
    fp = GET_FIGHTER(gobj);
    fp = GET_FIGHTER(gobj);

    fp->mv.mt.SpecialHi.travelFrames =
        mewtwoAttrs->x50_MEWTWO_TELEPORT_DURATION;

    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->x2223_b4 = true;

    ftColl_8007B62C(gobj, 2);

    fp->invisible = true;

    ft_PlaySFX(fp, 0x30DA1, SFX_VOLUME_MAX, SFX_PAN_MID);
}

/// Mewtwo's grounded Teleport Zoom Motion State handler
void ftMt_SpecialHi_Enter(HSD_GObj* gobj)
{
    /// @todo Shared @c inline with #ftMt_SpecialAirHi_Enter.
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    float vel;
    float stick_y;
    float stick_x;
    float sqrt_stick;

    stick_x = fp->input.lstick.x;
    stick_y = fp->input.lstick.y;

    stick_x *= stick_x;
    stick_y *= stick_y;

    /// @todo Probably a missing @c inline function.
    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);

    sqrt_stick = sqrtf(stick_x + stick_y);

    if (sqrt_stick > 1) {
        sqrt_stick = 1;
    }

    if (!(sqrt_stick < mewtwoAttrs->x58_MEWTWO_TELEPORT_STICK_RANGE_MIN)) {
        Vec3 stickVec;

        stickVec.x = fp->input.lstick.x;
        stickVec.y = fp->input.lstick.y;
        stickVec.z = 0.0f;

        if (!(lbVector_AngleXY(&collData->floor.normal, &stickVec) <
              (float) M_PI_2) &&
            (ftCo_8009A134(gobj) == false))
        {
            ftCommon_UpdateFacing(fp);

            vel = atan2f(fp->input.lstick.y,
                         fp->input.lstick.x * fp->facing_dir);

            fp->mv.mt.SpecialHi.stickX = stickVec.x;
            fp->mv.mt.SpecialHi.stickY = stickVec.y;
            fp->gr_vel =
                fp->facing_dir *
                (((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick) +
                  mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) *
                 cosf(vel));

            Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialHiLost, 0, 35, 1, 0,
                                      NULL);

            ftAnim_8006EBA4(gobj);

            ftAnim_SetAnimRate(gobj, 0);

            ftMewtwo_SpecialHi_SetVars(gobj);
            return;
        }
    }

    ftCommon_8007D60C(fp);
    ftMt_SpecialAirHi_Enter(gobj);
}

static float const stick_epsilon = 0.001;

/// Mewtwo's aerial Teleport Zoom Motion State handler
void ftMt_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    float stick_y;
    float stick_x;
    float sqrt_stick;
    float floatVar;

    stick_x = fp->input.lstick.x;
    stick_y = fp->input.lstick.y;

    stick_x *= stick_x;
    stick_y *= stick_y;

    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);

    sqrt_stick = sqrtf(stick_x + stick_y);

    if (sqrt_stick > 1) {
        sqrt_stick = 1;
    }

    if (sqrt_stick > mewtwoAttrs->x58_MEWTWO_TELEPORT_STICK_RANGE_MIN) {
        stick_x = stickGetDir(fp->input.lstick.x, 0);

        /// @todo Express as a fraction or something.
        if (stick_x > stick_epsilon) {
            ftCommon_UpdateFacing(fp);
        }

        floatVar =
            atan2f(fp->input.lstick.y, fp->input.lstick.x * fp->facing_dir);
        fp->mv.mt.SpecialHi.stickX = fp->input.lstick.x;
        fp->mv.mt.SpecialHi.stickY = fp->input.lstick.y;
    } else {
        ftCommon_8007DA24(fp);
        floatVar = M_PI_2;
        fp->mv.mt.SpecialHi.stickX = 0;
        sqrt_stick = fp->mv.mt.SpecialHi.stickY = 1;
    }

    fp->self_vel.x = fp->facing_dir *
                     ((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick +
                       mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) *
                      cosf(floatVar));

    fp->self_vel.y = (mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick +
                      mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) *
                     sinf(floatVar);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirHiLost, 0, 35, 1, 0,
                              NULL);

    ftAnim_8006EBA4(gobj);

    ftAnim_SetAnimRate(gobj, 0);
    ftMewtwo_SpecialHi_SetVars(gobj);
}

/// Mewtwo's grounded Teleport End Animation callback
void ftMt_SpecialHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// Mewtwo's aerial Teleport End Animation callback
void ftMt_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 0, true,
                      mewtwoAttrs->x70_MEWTWO_TELEPORT_FREEFALL_MOBILITY,
                      mewtwoAttrs->x74_MEWTWO_TELEPORT_LANDING_LAG);
    }
}

// Mewtwo's grounded Teleport End IASA callback
void ftMt_SpecialHi_IASA(HSD_GObj* gobj) {}

// Mewtwo's aerial Teleport End IASA callback
void ftMt_SpecialAirHi_IASA(HSD_GObj* gobj) {}

// Mewtwo's grounded Teleport End Physics callback
void ftMt_SpecialHi_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Mewtwo's aerial Teleport End Physics callback
void ftMt_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (fp->cmd_vars[0]) {
        ftCommon_FallBasic(fp);
        ftCommon_ClampSelfVelX(fp, mewtwoAttrs->x64_MEWTWO_TELEPORT_DRIFT *
                                       fp->co_attrs.air_drift_max);
    } else {
        float velY = fp->self_vel.y;
        fp->self_vel.y = velY - velY / 10;
        ftCommon_8007CEF4(fp);
    }
}

/// Mewtwo's grounded Teleport End Collision callback
void ftMt_SpecialHi_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftMt_SpecialHiLost_GroundToAir(gobj);
    }
}

/// Mewtwo's aerial Teleport End Collision callback
void ftMt_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_O(fp))) {
        ftCo_LandingFallSpecial_Enter(
            gobj, false, mewtwoAttrs->x74_MEWTWO_TELEPORT_LANDING_LAG);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/// Mewtwo's ground -> air Teleport End Motion State handler
void ftMt_SpecialHiLost_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirHi, transition_flags0,
                              fp->cur_anim_frame, 1, 0, NULL);
}

static inline void ftMewtwo_SpecialHiLost_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.mt.SpecialHi.velX = fp->self_vel.x;
    fp->mv.mt.SpecialHi.velY = fp->self_vel.y;
    fp->mv.mt.SpecialHi.groundVelX = fp->gr_vel;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;
    fp->gr_vel = 0;
    fp->invisible = false;
    fp->accessory4_cb = ftMt_SpecialHi_SetEndGFX;
}

/// Mewtwo's grounded Teleport End Motion State handler
void ftMt_SpecialHiLost_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialHi, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    ftMewtwo_SpecialHiLost_SetVars(gobj);

    fp->gr_vel = fp->mv.mt.SpecialHi.groundVelX *
                 mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
}

/// Mewtwo's aerial Teleport End Motion State handler
void ftMt_SpecialAirHiLost_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirHi, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    ftMewtwo_SpecialHiLost_SetVars(gobj);

    fp->self_vel.x = fp->mv.mt.SpecialHi.velX *
                     mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
    fp->self_vel.y = fp->mv.mt.SpecialHi.velY *
                     mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
}
