#include "ft/chara/ftMewtwo/ftMewtwo_SpecialHi.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftMewtwo/ftmewtwo.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "lb/lb_00B0.h"
#include "melee/ft/types.h"

#include <MSL/trigf.h>

/// Create Teleport Start GFX
void ftMewtwo_SpecialHi_CreateGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwo_SpecialHi_SetStartGFX(gobj);
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

/// Setup Teleport Start GFX
void ftMewtwo_SpecialHi_SetStartGFX(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        Vec3 pos;

        if (!fp1->x2219_flag.bits.b0) {
            lb_8000B1CC(fp1->x5E8_fighterBones[WaistN].x0_jobj, NULL, &pos);
            efSync_Spawn(0x4E8, gobj, &pos);
            fp1->x2219_flag.bits.b0 = true;
        }
    }

    fp0->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp0->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

/// Setup Teleport End GFX
void ftMewtwo_SpecialHi_SetEndGFX(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        Vec3 pos;

        if (!fp1->x2219_flag.bits.b0) {
            lb_8000B1CC(fp1->x5E8_fighterBones[WaistN].x0_jobj, NULL, &pos);
            fp1->x2219_flag.bits.b0 = true;
        }
    }

    fp0->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp0->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp0->cb.x21BC_callback_Accessory4 = NULL;
}

/// Mewtwo's grounded Teleport Start Motion State handler
void ftMewtwo_SpecialHi_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        fp1->xEC_ground_vel = 0;
        fp1->x80_self_vel.y = 0;
        fp1->x80_self_vel.x = 0;
    }

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALHI_START, 0, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);

    fp0->x2200_ftcmd_var0 = 0;
    fp0->sv.mt.SpecialHi.unk4 = 0;
    fp0->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

/// Mewtwo's aerial Teleport Start Motion State handler
void ftMewtwo_SpecialAirHi_StartMotion(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    fp->x80_self_vel.x /= mewtwoAttrs->x40_MEWTWO_TELEPORT_VEL_DIV_X;
    fp->x80_self_vel.y /= mewtwoAttrs->x44_MEWTWO_TELEPORT_VEL_DIV_Y;

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRHI_START, 0, NULL, 0,
                              1, 0);
    ftAnim_8006EBA4(gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->sv.mt.SpecialHi.unk4 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

/// Mewtwo's grounded Teleport Start Animation callback
void ftMewtwo_SpecialHiStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMewtwo_SpecialHi_Action(gobj);
    }
}

/// Mewtwo's aerial Teleport Start Animation callback
void ftMewtwo_SpecialAirHiStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMewtwo_SpecialAirHi_Action(gobj);
    }
}

// Mewtwo's grounded Teleport Start IASA callback
void ftMewtwo_SpecialHiStart_IASA(HSD_GObj* gobj) {}

// Mewtwo's aerial Teleport Start IASA callback
void ftMewtwo_SpecialAirHiStart_IASA(HSD_GObj* gobj) {}

// Mewtwo's grounded Teleport Start Physics callback
void ftMewtwo_SpecialHiStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Mewtwo's aerial Teleport Start Physics callback
void ftMewtwo_SpecialAirHiStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp0);

        ftCommon_8007D494(fp1, mewtwoAttrs->x48_MEWTWO_TELEPORT_GRAVITY,
                          mewtwoAttrs->x4C_MEWTWO_TELEPORT_TERMINAL_VELOCITY);
    }

    ftCommon_8007CEF4(fp0);
}

/// Mewtwo's grounded Teleport Start Collision callback
void ftMewtwo_SpecialHiStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftMewtwo_SpecialHiStart_GroundToAir(gobj);
    }
}

/// Mewtwo's aerial Teleport Start Collision callback
void ftMewtwo_SpecialAirHiStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_O(fp))) {
        ftMewtwo_SpecialAirHiStart_AirToGround(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

static Fighter_MotionStateChangeFlags const transition_flags0 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

static Fighter_MotionStateChangeFlags const transition_flags1 =
    transition_flags0 | FtStateChange_PreserveColAnimHitStatus;

/// Mewtwo's ground -> air Teleport Start Motion State handler
void ftMewtwo_SpecialHiStart_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRHI_START,
                              transition_flags1, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

/// Mewtwo's air -> ground Teleport Start Motion State handler
void ftMewtwo_SpecialAirHiStart_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALHI_START,
                              transition_flags1, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

/// Mewtwo's grounded Teleport Zoom Animation callback
void ftMewtwo_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->sv.mt.SpecialHi.travelFrames--;

    if (fp->sv.mt.SpecialHi.travelFrames <= 0) {
        ftMewtwo_SpecialHiLost_Action(gobj);
    }
}

/// Mewtwo's aerial Teleport Zoom Animation callback
void ftMewtwo_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->sv.mt.SpecialHi.travelFrames--;

    if (fp->sv.mt.SpecialHi.travelFrames <= 0) {
        ftMewtwo_SpecialAirHiLost_Action(gobj);
    }
}

// Mewtwo's grounded Teleport Zoom IASA callback
void ftMewtwo_SpecialHi_IASA(HSD_GObj* gobj) {}

// Mewtwo's aerial Teleport Zoom IASA callback
void ftMewtwo_SpecialAirHi_IASA(HSD_GObj* gobj) {}

// Mewtwo's grounded Teleport Zoom Physics callback
void ftMewtwo_SpecialHi_Phys(HSD_GObj* gobj)
{
    ftCommon_8007CB74(gobj);
}

// Mewtwo's aerial Teleport Zoom Physics callback
void ftMewtwo_SpecialAirHi_Phys(HSD_GObj* gobj) {}

/// Mewtwo's grounded Teleport Zoom Collision callback
void ftMewtwo_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        CollData* collData = &fp0->x6F0_collData;

        if (!ft_80082708(gobj)) {
            u32 env_flags = collData->x134_envFlags;
            if (env_flags & MPCOLL_RIGHTWALL || env_flags & MPCOLL_LEFTWALL) {
                ftCommon_8007D60C(fp1);
                ftMewtwo_SpecialAirHiLost_Action(gobj);
                return;
            } else {
                ftMewtwo_SpecialHi_GroundToAir(gobj);
            }
        } else {
            u32 env_flags = collData->x134_envFlags;
            if (env_flags & MPCOLL_RIGHTWALL || env_flags & MPCOLL_LEFTWALL) {
                ftMewtwo_SpecialHiLost_Action(gobj);
            }
        }
    }
}

bool ftMewtwo_SpecialHi_CheckTimer(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = fp->x2D4_specialAttributes;

    if (fp->sv.mt.SpecialHi.unk4 >= mewtwoAttrs->x54_MEWTWO_TELEPORT_UNK2) {
        return true;
    }

    if (ft_8009A134(gobj)) {
        return false;
    }

    return true;
}

/// Mewtwo's aerial Teleport Zoom Collision callback
void ftMewtwo_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        Fighter* fp1 = fp0;
        ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs =
            getFtSpecialAttrsD(fp0);
        CollData* collData = collData = getFtColl(fp1);
        fp0->sv.mt.SpecialHi.unk4++;

        if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_O(fp0))) {
            if (ftMewtwo_SpecialHi_CheckTimer(gobj)) {
                ftMewtwo_SpecialAirHi_AirToGround(gobj);
                return;
            }
        }

        if (ftCliffCommon_80081298(gobj)) {
            return;
        }

        if ((collData->x134_envFlags & MPCOLL_CEIL) &&
            (lbVector_AngleXY(&collData->x188_ceiling.normal,
                              &fp1->x80_self_vel) >
             DEG_TO_RAD *
                 (90.0f + mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP)))
        {
            ftMewtwo_SpecialAirHiLost_Action(gobj);
        }

        if (collData->x134_envFlags & MPCOLL_RIGHTWALL &&
            (lbVector_AngleXY(&collData->x160_rightwall.normal,
                              &fp1->x80_self_vel) >
             DEG_TO_RAD *
                 (90.0f + mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP)))
        {
            ftMewtwo_SpecialAirHiLost_Action(gobj);
        }

        if (collData->x134_envFlags & MPCOLL_LEFTWALL &&
            lbVector_AngleXY(&collData->x174_leftwall.normal,
                             &fp1->x80_self_vel) >
                DEG_TO_RAD *
                    (90.0f + mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP))
        {
            ftMewtwo_SpecialAirHiLost_Action(gobj);
        }
    }
}

/// Mewtwo's ground -> air Teleport Zoom Motion State handler
void ftMewtwo_SpecialHi_GroundToAir(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRHI, transition_flags1,
                              NULL, fp->x894_currentAnimFrame, 0, 0);

    fp->x2223_flag.bits.b4 = true;
    fp->x221E_flag.bits.b0 = true;
}

/// Mewtwo's air -> ground Teleport Zoom Motion State handler
void ftMewtwo_SpecialAirHi_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALHI, transition_flags1,
                              NULL, fp->x894_currentAnimFrame, 0, 0);

    fp->x221E_flag.bits.b0 = true;
}

static inline void ftMewtwo_SpecialHi_SetVars(HSD_GObj* gobj)
{
    /// @todo This is like three functions in one. Split it.
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    fp = GET_FIGHTER(gobj);
    fp = GET_FIGHTER(gobj);
    fp = GET_FIGHTER(gobj);

    fp->sv.mt.SpecialHi.travelFrames =
        mewtwoAttrs->x50_MEWTWO_TELEPORT_DURATION;

    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    fp->x2223_flag.bits.b4 = true;

    ftColl_8007B62C(gobj, 2);

    fp->x221E_flag.bits.b0 = true;

    ft_80088148(fp, 0x30DA1, SFX_VOLUME_MAX, SFX_PAN_MID);
}

/// Mewtwo's grounded Teleport Zoom Motion State handler
void ftMewtwo_SpecialHi_Action(HSD_GObj* gobj)
{
    /// @todo Shared @c inline with #ftMewtwo_SpecialAirHi_Action.
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    f32 vel;
    f32 stick_y;
    f32 stick_x;
    f32 sqrt_stick;

    stick_x = fp->input.x620_lstick_x;
    stick_y = fp->input.x624_lstick_y;

    stick_x *= stick_x;
    stick_y *= stick_y;

    /// @todo Probably a missing @c inline function.
#ifdef MUST_MATCH
    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
#else
    mewtwoAttrs = getFtSpecialAttrsD(fp);
#endif

    sqrt_stick = sqrtf(stick_x + stick_y);

    if (sqrt_stick > 1) {
        sqrt_stick = 1;
    }

    if (!(sqrt_stick < mewtwoAttrs->x58_MEWTWO_TELEPORT_STICK_RANGE_MIN)) {
        Vec3 stickVec;

        stickVec.x = fp->input.x620_lstick_x;
        stickVec.y = fp->input.x624_lstick_y;
        stickVec.z = 0.0f;

        if (!(lbVector_AngleXY(&collData->x14C_ground.normal, &stickVec) <
              (f32) M_PI_2) &&
            (ft_8009A134(gobj) == false))
        {
            ftCommon_8007D9FC(fp);

            vel = atan2f(fp->input.x624_lstick_y,
                         fp->input.x620_lstick_x * fp->facing_dir);

            fp->sv.mt.SpecialHi.stickX = stickVec.x;
            fp->sv.mt.SpecialHi.stickY = stickVec.y;
            fp->xEC_ground_vel =
                fp->facing_dir *
                (((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick) +
                  mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) *
                 cosf(vel));

            Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALHI, 0, NULL, 35,
                                      1, 0);

            ftAnim_8006EBA4(gobj);

            ftAnim_SetAnimRate(gobj, 0);

            ftMewtwo_SpecialHi_SetVars(gobj);
            return;
        }
    }

    ftCommon_8007D60C(fp);
    ftMewtwo_SpecialAirHi_Action(gobj);
}

static f32 const stick_epsilon = 0.001;

/// Mewtwo's aerial Teleport Zoom Motion State handler
void ftMewtwo_SpecialAirHi_Action(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    f32 stick_y;
    f32 stick_x;
    f32 sqrt_stick;
    f32 floatVar;

    stick_x = fp->input.x620_lstick_x;
    stick_y = fp->input.x624_lstick_y;

    stick_x *= stick_x;
    stick_y *= stick_y;

#ifdef MUST_MATCH
    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
#else
    mewtwoAttrs = getFtSpecialAttrsD(fp);
#endif

    sqrt_stick = sqrtf(stick_x + stick_y);

    if (sqrt_stick > 1) {
        sqrt_stick = 1;
    }

    if (sqrt_stick > mewtwoAttrs->x58_MEWTWO_TELEPORT_STICK_RANGE_MIN) {
        stick_x = stickGetDir(fp->input.x620_lstick_x, 0);

        /// @todo Express as a fraction or something.
        if (stick_x > stick_epsilon) {
            ftCommon_8007D9FC(fp);
        }

        floatVar = atan2f(fp->input.x624_lstick_y,
                          fp->input.x620_lstick_x * fp->facing_dir);
        fp->sv.mt.SpecialHi.stickX = fp->input.x620_lstick_x;
        fp->sv.mt.SpecialHi.stickY = fp->input.x624_lstick_y;
    } else {
        ftCommon_8007DA24(fp);
        floatVar = M_PI_2;
        fp->sv.mt.SpecialHi.stickX = 0;
        sqrt_stick = fp->sv.mt.SpecialHi.stickY = 1;
    }

    fp->x80_self_vel.x =
        fp->facing_dir *
        ((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick +
          mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) *
         cosf(floatVar));

    fp->x80_self_vel.y =
        (mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick +
         mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) *
        sinf(floatVar);

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRHI, 0, NULL, 35, 1, 0);

    ftAnim_8006EBA4(gobj);

    ftAnim_SetAnimRate(gobj, 0);
    ftMewtwo_SpecialHi_SetVars(gobj);
}

/// Mewtwo's grounded Teleport End Animation callback
void ftMewtwo_SpecialHiLost_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// Mewtwo's aerial Teleport End Animation callback
void ftMewtwo_SpecialAirHiLost_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_80096900(gobj, 1, 0, true,
                    mewtwoAttrs->x70_MEWTWO_TELEPORT_FREEFALL_MOBILITY,
                    mewtwoAttrs->x74_MEWTWO_TELEPORT_LANDING_LAG);
    }
}

// Mewtwo's grounded Teleport End IASA callback
void ftMewtwo_SpecialHiLost_IASA(HSD_GObj* gobj) {}

// Mewtwo's aerial Teleport End IASA callback
void ftMewtwo_SpecialAirHiLost_IASA(HSD_GObj* gobj) {}

// Mewtwo's grounded Teleport End Physics callback
void ftMewtwo_SpecialHiLost_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Mewtwo's aerial Teleport End Physics callback
void ftMewtwo_SpecialAirHiLost_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (fp->x2200_ftcmd_var0) {
        ftCommon_8007D4B8(fp);
        ftCommon_8007D440(fp, mewtwoAttrs->x64_MEWTWO_TELEPORT_DRIFT *
                                  fp->x110_attr.x17C_AerialDriftMax);
    } else {
        f32 velY = fp->x80_self_vel.y;
        fp->x80_self_vel.y = velY - velY / 10;
        ftCommon_8007CEF4(fp);
    }
}

/// Mewtwo's grounded Teleport End Collision callback
void ftMewtwo_SpecialHiLost_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftMewtwo_SpecialHiLost_GroundToAir(gobj);
    }
}

/// Mewtwo's aerial Teleport End Collision callback
void ftMewtwo_SpecialAirHiLost_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_O(fp))) {
        ft_800D5CB0(gobj, 0, mewtwoAttrs->x74_MEWTWO_TELEPORT_LANDING_LAG);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/// Mewtwo's ground -> air Teleport End Motion State handler
void ftMewtwo_SpecialHiLost_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRHI_LOST,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

static inline void ftMewtwo_SpecialHiLost_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->sv.mt.SpecialHi.velX = fp->x80_self_vel.x;
    fp->sv.mt.SpecialHi.velY = fp->x80_self_vel.y;
    fp->sv.mt.SpecialHi.groundVelX = fp->xEC_ground_vel;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = 0;
    fp->xEC_ground_vel = 0;
    fp->x221E_flag.bits.b0 = false;
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_SetEndGFX;
}

/// Mewtwo's grounded Teleport End Motion State handler
void ftMewtwo_SpecialHiLost_Action(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALHI_LOST, 0, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);

    ftMewtwo_SpecialHiLost_SetVars(gobj);

    fp->xEC_ground_vel = fp->sv.mt.SpecialHi.groundVelX *
                         mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
}

/// Mewtwo's aerial Teleport End Motion State handler
void ftMewtwo_SpecialAirHiLost_Action(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRHI_LOST, 0, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);

    ftMewtwo_SpecialHiLost_SetVars(gobj);

    fp->x80_self_vel.x = fp->sv.mt.SpecialHi.velX *
                         mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
    fp->x80_self_vel.y = fp->sv.mt.SpecialHi.velY *
                         mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
}
