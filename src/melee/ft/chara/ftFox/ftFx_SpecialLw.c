#include "ftFx_SpecialLw.h"

#include "math.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftFox/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

#define FTFOX_SPECIALLW_COLL_FLAG                                             \
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_UpdateCmd | Ft_MF_SkipColAnim | \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

void ftFx_SpecialLw_CreateLoopGFX(HSD_GObj* gobj)
{
    /// @todo Shared @c inline with #ftFx_SpecialLw_CreateStartGFX.
    Fighter* fp = gobj->user_data;

    if (fp->x2219_b0 == false) {
        efSync_Spawn(1160, gobj, fp->parts[FtPart_HipN].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

/// Create Reflector Start GFX
void ftFx_SpecialLw_CreateStartGFX(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->x2219_b0 == false) {
        efSync_Spawn(1161, gobj, fp->parts[FtPart_HipN].joint);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftFx_SpecialLw_CreateReflectGFX(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->x2219_b0 == false) {
        efSync_Spawn(1162, gobj, fp->parts[FtPart_HipN].joint);
        fp->x2219_b0 = true;
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static inline void ftFox_SpecialLw_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialLw.releaseLag = da->x98_FOX_REFLECTOR_RELEASE_LAG;

    fp->mv.fx.SpecialLw.isRelease = 0;
    fp->cmd_vars[1] = 4;

    fp->mv.fx.SpecialLw.gravityDelay = da->xA4_FOX_REFLECTOR_GRAVITY_DELAY;

    fp->accessory4_cb = ftFx_SpecialLw_CreateStartGFX;
}

void ftFx_SpecialLw_Enter(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwStart, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    ftFox_SpecialLw_SetVars(gobj);
}

void ftFx_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    fp->self_vel.y = 0;
    fp->self_vel.x /= da->xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwStart, 0, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);

    ftFox_SpecialLw_SetVars(gobj);
}

/// Fox & Falco's grounded Reflector Loop Motion State handler
static void ftFx_SpecialLwLoop_Enter(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Loop Motion State handler
static void ftFx_SpecialAirLwLoop_Enter(HSD_GObj* gobj);

// 0x800E8694
// https://decomp.me/scratch/isKUf // Fox & Falco's grounded Reflector Start
// Animation callback
void ftFx_SpecialLwStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            ftFx_SpecialLwLoop_Enter(gobj);
        } else {
            ftFx_SpecialAirLwLoop_Enter(gobj);
        }
        ftCommon_8007DB24(gobj);
        fp->accessory4_cb = ftFx_SpecialLw_CreateLoopGFX;
    }
}

/// Fox & Falco's aerial Reflector Start Animation callback
void ftFx_SpecialAirLwStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            ftFx_SpecialLwLoop_Enter(gobj);
        } else {
            ftFx_SpecialAirLwLoop_Enter(gobj);
        }
        ftCommon_8007DB24(gobj);

        fp->accessory4_cb = ftFx_SpecialLw_CreateLoopGFX;
    }
}

// 0x800E87AC
// https://decomp.me/scratch/CYqHS // Fox & Falco's grounded Reflector Start
// IASA callback
void ftFx_SpecialLwStart_IASA(HSD_GObj* gobj)
{
    if (ftFx_SpecialLwStart_CheckPass(gobj)) {
        return;
    }
}

// 0x800E87D0 - Fox & Falco's aerial Reflector Start IASA callback
void ftFx_SpecialAirLwStart_IASA(HSD_GObj* gobj)
{
    return;
}

bool ftFx_SpecialLwStart_CheckPass(HSD_GObj* gobj)
{
    if (ftCo_80099F1C(gobj) != false) {
        ftFx_SpecialLwStart_Pass(gobj);
        return true;
    }

    return false;
}

/// Create Reflector's reflect bubble
static void ftFx_SpecialLw_CreateReflectHit(HSD_GObj* gobj);

void ftFx_SpecialLwStart_Pass(HSD_GObj* gobj)
{
    ftCo_8009A184(gobj, ftFx_MS_SpecialAirLwStart, FTFOX_SPECIALLW_COLL_FLAG,
                  GET_FIGHTER(gobj)->cur_anim_frame);

    ftFx_SpecialLw_CreateReflectHit(gobj);
}

void ftFx_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftFx_SpecialAirLwStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (fp->mv.fx.SpecialLw.gravityDelay != 0) {
        fp->mv.fx.SpecialLw.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->xAC_FOX_REFLECTOR_FALL_ACCEL,
                          ca->terminal_vel);
    }

    ftCommon_8007CF58(fp);
}

void ftFx_SpecialLwStart_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialLwStart_GroundToAir(gobj);
    }
}

void ftFx_SpecialAirLwStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftFx_SpecialAirLwStart_AirToGround(gobj);
    }
}

void ftFx_SpecialLwStart_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwStart,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);
}

void ftFx_SpecialAirLwStart_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwStart,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);

    ftCommon_8007D468(fp);
}

void ftFx_SpecialLwLoop_Anim(HSD_GObj* gobj)
{
    /// @todo Shared @c inline with #ftFx_SpecialAirLwLoop_Anim.
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }

    if (fp->mv.fx.SpecialLw.releaseLag > 0) {
        fp->mv.fx.SpecialLw.releaseLag--;
    }

    if (fp->mv.fx.SpecialLw.releaseLag <= 0 && fp->mv.fx.SpecialLw.isRelease) {
        if (fp->ground_or_air == GA_Ground) {
            ftFx_SpecialLwEnd_Enter(gobj);
            return;
        }

        ftFx_SpecialAirLwEnd_Enter(gobj);
    }
}

void ftFx_SpecialAirLwLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }

    if (fp->mv.fx.SpecialLw.releaseLag > 0) {
        fp->mv.fx.SpecialLw.releaseLag--;
    }

    if ((fp->mv.fx.SpecialLw.releaseLag <= 0) &&
        (fp->mv.fx.SpecialLw.isRelease != false))
    {
        if (fp->ground_or_air == GA_Ground) {
            ftFx_SpecialLwEnd_Enter(gobj);
            return;
        }

        ftFx_SpecialAirLwEnd_Enter(gobj);
    }
}

/// Check for drop-through platform while in SpecialLwLoop
static bool ftFx_SpecialLwLoop_CheckPass(HSD_GObj* gobj);

void ftFx_SpecialLwLoop_IASA(HSD_GObj* gobj)
{
    if ((ftFx_SpecialLwTurn_Check(gobj) == false) &&
        (ftCo_Jump_CheckInput(gobj) == false))
    {
        if (ftFx_SpecialLwLoop_CheckPass(gobj)) {
            return;
        }
    }
}

void ftFx_SpecialAirLwLoop_IASA(HSD_GObj* gobj)
{
    if (ftFx_SpecialLwTurn_Check(gobj) == false && ftCo_800CB870(gobj)) {
        /// @remarks Kinda weird, was this stripped or are there side effects?
        return;
    }
}

/// Fox & Falco's Reflector Loop Platform Drop Motion State handler
static void ftFx_SpecialLwLoop_Pass(HSD_GObj* gobj);

static bool ftFx_SpecialLwLoop_CheckPass(HSD_GObj* gobj)
{
    if (ftCo_80099F1C(gobj) != false) {
        ftFx_SpecialLwLoop_Pass(gobj);
        return true;
    }

    return false;
}

static void ftFx_SpecialLwLoop_Pass(HSD_GObj* gobj)
{
    ftCo_8009A184(gobj, ftFx_MS_SpecialAirLwLoop, FTFOX_SPECIALLW_COLL_FLAG,
                  GET_FIGHTER(gobj)->cur_anim_frame);

    ftFx_SpecialLw_CreateReflectHit(gobj);
}

void ftFx_SpecialLwLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

static inline void ftFox_SpecialLw_InlinePhys(HSD_GObj* gobj)
{
    ftCo_DatAttrs* ca;
    ftFox_DatAttrs* da;
    Fighter* fp = getFighter(gobj);

    ca = getFtAttrs(fp);
    da = getFtSpecialAttrs(fp);

    /// @todo Shared @c inline with other functions in this file.
    if (fp->mv.fx.SpecialLw.gravityDelay != 0) {
        fp->mv.fx.SpecialLw.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->xAC_FOX_REFLECTOR_FALL_ACCEL,
                          ca->terminal_vel);
    }

    ftCommon_8007CF58(fp);
}

void ftFx_SpecialAirLwLoop_Phys(HSD_GObj* gobj)
{
    ftFox_SpecialLw_InlinePhys(gobj);
    ftColl_8007AEF8(gobj);
}

/// Fox & Falco's ground -> air Reflector Loop Motion State handler
static void ftFx_SpecialLwLoop_GroundToAir(HSD_GObj* gobj);

void ftFx_SpecialLwLoop_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialLwLoop_GroundToAir(gobj);
    }
}

/// Fox & Falco's air -> ground Reflector Loop Motion State Handler
static void ftFx_SpecialAirLwLoop_AirToGround(HSD_GObj* gobj);

void ftFx_SpecialAirLwLoop_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftFx_SpecialAirLwLoop_AirToGround(gobj);
    }
}

static void ftFx_SpecialLwLoop_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwLoop,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);

    ftFx_SpecialLw_CreateReflectHit(gobj);
}

static void ftFx_SpecialAirLwLoop_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwLoop,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);

    ftCommon_8007D468(fp);
    ftFx_SpecialLw_CreateReflectHit(gobj);
}

static void ftFx_SpecialLw_CreateReflectHit(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    ftColl_CreateReflectHit(gobj, &da->xB0_FOX_REFLECTOR_REFLECTION,
                            ftFx_SpecialLwHit_Enter);
}

static void ftFx_SpecialLwLoop_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwLoop, Ft_MF_KeepGfx, 0, 1,
                              0, NULL);

    ftFx_SpecialLw_CreateReflectHit(gobj);
}

/// Fox & Falco's aerial Reflector Loop Motion State handler
static void ftFx_SpecialAirLwLoop_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwLoop, Ft_MF_KeepGfx, 0,
                              1, 0, NULL);

    ftFx_SpecialLw_CreateReflectHit(gobj);
}

#pragma push
#pragma dont_inline on
/// Fox & Falco's Reflector Turn function
static void ftFx_SpecialLw_Turn(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftFox_DatAttrs* da = fp->dat_attrs;

    u8 _[8];

    fp->mv.fx.SpecialLw.turnFrames--;
    if (fp->cmd_vars[0] == 0 &&
        fp->mv.fx.SpecialLw.turnFrames <= da->x9C_FOX_REFLECTOR_TURN_FRAMES)
    {
        fp->cmd_vars[0] = 1;
        fp->facing_dir = -fp->facing_dir;
    }
    ftParts_80075AF0(fp, 0,
                     -(180 / da->x9C_FOX_REFLECTOR_TURN_FRAMES * deg_to_rad -
                       ftParts_80075F48(fp, 0)));
}
#pragma pop

/// Fox & Falco's Reflector Turn function
static inline void ftFox_SpecialLw_Turn_Inline(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftFox_DatAttrs* da = fp->dat_attrs;

    fp->mv.fx.SpecialLw.turnFrames--;
    if (fp->cmd_vars[0] == false &&
        fp->mv.fx.SpecialLw.turnFrames <= da->x9C_FOX_REFLECTOR_TURN_FRAMES)
    {
        fp->cmd_vars[0] = true;
        fp->facing_dir = -fp->facing_dir;
    }

    /// @todo Degrees-to-radians constant.
    ftParts_80075AF0(
        fp, 0,
        -((0.01745329238474369f * (180 / da->x9C_FOX_REFLECTOR_TURN_FRAMES)) -
          ftParts_80075F48(fp, 0)));
}

void ftFx_SpecialLwTurn_Anim(HSD_GObj* gobj)
{
    /// @todo Shared @c inline with #ftFx_SpecialAirLwTurn_Anim.
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[16];

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }

    if (fp->mv.fx.SpecialLw.releaseLag > 0) {
        fp->mv.fx.SpecialLw.releaseLag--;
    }

    ftFox_SpecialLw_Turn_Inline(gobj);

    if (fp->mv.fx.SpecialLw.turnFrames <= 0) {
        ftFx_SpecialLwHit_Check(gobj);
    }
}

void ftFx_SpecialAirLwTurn_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[20];

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }

    if (fp->mv.fx.SpecialLw.releaseLag > 0) {
        fp->mv.fx.SpecialLw.releaseLag--;
    }

    ftFox_SpecialLw_Turn_Inline(gobj);

    if (fp->mv.fx.SpecialLw.turnFrames <= 0) {
        ftFx_SpecialLwHit_Check(gobj);
    }
}

// 0x800E91FC - Fox & Falco's grounded Reflector Turn IASA callback
void ftFx_SpecialLwTurn_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E9200 - Fox & Falco's aerial Reflector Turn IASA callback
void ftFx_SpecialAirLwTurn_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E9204
// https://decomp.me/scratch/sQ6Zw // Fox & Falco's grounded Reflector Turn
// Physics callback
void ftFx_SpecialLwTurn_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

/// Fox & Falco's aerial Reflector Turn Physics callback
void ftFx_SpecialAirLwTurn_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);
    ftCo_DatAttrs* ca = getFtAttrs(fp);

    u8 _[4];

    if (fp->mv.fx.SpecialLw.gravityDelay != 0) {
        fp->mv.fx.SpecialLw.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->xAC_FOX_REFLECTOR_FALL_ACCEL,
                          ca->terminal_vel);
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AEF8(gobj);
}

// 0x800E92AC
// https://decomp.me/scratch/hKwfA // Fox & Falco's grounded Reflector Turn
// Collision callback
void ftFx_SpecialLwTurn_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialLwTurn_GroundToAir(gobj);
    }
}

// 0x800E92E8
// https://decomp.me/scratch/L0Bhg // Fox & Falco's aerial Reflector Turn
// Collision callback
void ftFx_SpecialAirLwTurn_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftFx_SpecialAirLwTurn_GroundToAir(gobj);
    }
}

inline void ftFox_SpecialLw_SetReflectVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->reflecting = true;
    fp->reflect_hit_cb = ftFx_SpecialLwHit_Enter;
}

// 0x800E9324
// https://decomp.me/scratch/L2Rcy // Fox & Falco's ground -> air Reflector
// Turn Motion State handler
void ftFx_SpecialLwTurn_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwTurn,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);
    ftFox_SpecialLw_SetReflectVars(gobj);
}

// 0x800E93A4
// https://decomp.me/scratch/BwZlC // Fox & Falco's air -> ground Reflector
// Turn Motion State handler
void ftFx_SpecialAirLwTurn_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwTurn,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);
    ftCommon_8007D468(fp);
    ftFox_SpecialLw_SetReflectVars(gobj);
}

inline void ftFox_SpecialLwTurn_SetVarAll(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);
    fp->reflecting = true;
    fp->reflect_hit_cb = ftFx_SpecialLwHit_Enter;
    fp->mv.fx.SpecialLw.turnFrames = da->x9C_FOX_REFLECTOR_TURN_FRAMES;
    fp->cmd_vars[0] = 0;
    ftFx_SpecialLw_Turn(gobj);
}

// 0x800E942C
// https://decomp.me/scratch/Hr5UW // Fox & Falco's Reflector Turn Motion State
// handler
bool ftFx_SpecialLwTurn_Check(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (ftCo_800C97A8(gobj) != false) {
        if (fp->ground_or_air == GA_Ground) {
            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwTurn,
                                      Ft_MF_KeepGfx, 0, 1, 0, NULL);
            ftFox_SpecialLwTurn_SetVarAll(gobj);
        } else {
            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwTurn,
                                      Ft_MF_KeepGfx, 0, 1, 0, NULL);
            ftFox_SpecialLwTurn_SetVarAll(gobj);
        }
        fp->accessory4_cb = ftFx_SpecialLw_CreateLoopGFX;

        return true;
    }
    return false;
}

inline void ftFox_SpecialLwHit_CreateReflectInline(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);
    ftColl_CreateReflectHit(gobj, &da->xB0_FOX_REFLECTOR_REFLECTION,
                            ftFx_SpecialLwHit_Enter);
}

// 0x800E9564
// https://decomp.me/scratch/R1XfY // Fox & Falco's Reflector Hit Motion State
// handler
bool ftFx_SpecialLwHit_Check(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->mv.fx.SpecialLw.releaseLag <= 0 && fp->mv.fx.SpecialLw.isRelease) {
        if (fp->ground_or_air == GA_Ground) {
            ftFx_SpecialLwEnd_Enter(gobj);
        } else {
            ftFx_SpecialAirLwEnd_Enter(gobj);
        }
        return false;
    }
    if (fp->ground_or_air == GA_Ground) {
        Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwLoop, Ft_MF_KeepGfx,
                                  0, 1, 0, NULL);
        ftFox_SpecialLwHit_CreateReflectInline(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwLoop,
                                  Ft_MF_KeepGfx, 0, 1, 0, NULL);
        ftFox_SpecialLwHit_CreateReflectInline(gobj);
    }
    return true;
}

/// Fox & Falco's grounded Reflector Hit Animation callback
void ftFx_SpecialLwHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }

    if (fp->mv.fx.SpecialLw.releaseLag > 0) {
        fp->mv.fx.SpecialLw.releaseLag--;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (ftFx_SpecialLwHit_Check(gobj)) {
            ftCommon_8007DB24(gobj);
            fp->accessory4_cb = ftFx_SpecialLw_CreateLoopGFX;
        }
    }
}

#pragma dont_inline on
/// Fox & Falco's aerial Reflector Hit Animation callback
void ftFx_SpecialAirLwHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    u8 _[8];

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.fx.SpecialLw.isRelease = true;
    }

    if (fp->mv.fx.SpecialLw.releaseLag > 0) {
        fp->mv.fx.SpecialLw.releaseLag--;
    }

    if (!ftAnim_IsFramesRemaining(gobj) && ftFx_SpecialLwHit_Check(gobj)) {
        ftCommon_8007DB24(gobj);
        fp->accessory4_cb = ftFx_SpecialLw_CreateLoopGFX;
    }
}
#pragma dont_inline off

// 0x800E9844 - Fox & Falco's grounded Reflector Hit IASA callback
void ftFx_SpecialLwHit_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E9848 - Fox & Falco's aerial Reflector Hit IASA callback
void ftFx_SpecialAirLwHit_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E984C
// https://decomp.me/scratch/P8Wyt // Fox & Falco's grounded Reflector Hit
// Physics callback
void ftFx_SpecialLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

/// Fox & Falco's aerial Reflector Hit Physics callback
void ftFx_SpecialAirLwHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);
    ftCo_DatAttrs* ca = getFtAttrs(fp);

    u8 _[4];

    if (fp->mv.fx.SpecialLw.gravityDelay != 0) {
        fp->mv.fx.SpecialLw.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->xAC_FOX_REFLECTOR_FALL_ACCEL,
                          ca->terminal_vel);
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AEF8(gobj);
}

/// Fox & Falco's grounded Reflector Hit Collision callback
void ftFx_SpecialLwHit_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftFx_SpecialLwHit_GroundToAir(gobj);
    }
}

/// Fox & Falco's aerial Reflector Hit Collision callback
void ftFx_SpecialAirLwHit_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftFx_SpecialAirLwHit_AirToGround(gobj);
    }
}

// 0x800E996C
// https://decomp.me/scratch/wnviJ // Fox & Falco's ground -> air Reflector Hit
// Motion State handler
void ftFx_SpecialLwHit_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwHit,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);
    ftFx_SpecialLwHit_SetCall(gobj);
}

// 0x800E99D4
// https://decomp.me/scratch/zXqEI // Fox & Falco's air -> ground Reflector Hit
// Motion State handler
void ftFx_SpecialAirLwHit_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwHit,
                              FTFOX_SPECIALLW_COLL_FLAG, fp->cur_anim_frame, 1,
                              0, NULL);
    ftCommon_8007D468(fp);
    ftFx_SpecialLwHit_SetCall(gobj);
}

// 0x800E9A44
// https://decomp.me/scratch/XIxX1 // Toggle bit flag and set OnReflect
// callback for Reflector
void ftFx_SpecialLwHit_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->reflecting = true;
    fp->reflect_hit_cb = ftFx_SpecialLwHit_Enter;
}

// 0x800E9A68
// https://decomp.me/scratch/SyGv6 // Fox & Falco's Reflect Hit Motion State
// handler
void ftFx_SpecialLwHit_Enter(HSD_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = fp = GET_FIGHTER(gobj);
    s32 msid;

    fp->facing_dir = fp->ReflectAttr.x1A2C_reflectHitDirection;

    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint, NULL,
                &sp14);

    lb_800119DC(&sp14, 120, 3, 0.1, M_PI / 3);

    if (fp->ground_or_air == GA_Ground) {
        msid = ftFx_MS_SpecialLwHit;
    } else {
        msid = ftFx_MS_SpecialAirLwHit;
    }

    Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    ftFx_SpecialLwHit_SetCall(gobj);

    fp->accessory4_cb = ftFx_SpecialLw_CreateReflectGFX;
}

/// Fox & Falco's grounded Reflector End Animation callback
void ftFx_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        ftCommon_8007D92C(gobj);
    }
}

/// Fox & Falco's aerial Reflector End Animation callback
void ftFx_SpecialAirLwEnd_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        ftCommon_8007D92C(gobj);
    }
}

/// Fox & Falco's grounded Reflector End IASA callback
void ftFx_SpecialLwEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E9BCC - Fox & Falco's aerial Reflector End IASA callback
void ftFx_SpecialAirLwEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E9BD0 - Fox & Falco's grounded Reflector End Physics callback
void ftFx_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Fox & Falco's aerial Reflector End Physics callback
void ftFx_SpecialAirLwEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);
    ftCo_DatAttrs* ca = getFtAttrs(fp);

    u8 _[4];

    if (fp->mv.fx.SpecialLw.gravityDelay != 0) {
        fp->mv.fx.SpecialLw.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->xAC_FOX_REFLECTOR_FALL_ACCEL,
                          ca->terminal_vel);
    }
    ftCommon_8007CF58(fp);
}

// 0x800E9C50
// https://decomp.me/scratch/chekC // Fox & Falco's grounded Reflector End
// Collision callback
void ftFx_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialLwEnd_GroundToAir(gobj);
    }
}

// 0x800E9C8C
// https://decomp.me/scratch/t5ghA // Fox & Falco's aerial Reflector End
// Collision callback
void ftFx_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftFx_SpecialAirLwEnd_AirToGround(gobj);
    }
}

// 0x800E9CC8
// https://decomp.me/scratch/xAGsZ // Fox & Falco's ground -> air Reflector End
// Motion State handler
void ftFx_SpecialLwEnd_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwEnd,
                              (Ft_MF_SkipColAnim | Ft_MF_UpdateCmd),
                              fp->cur_anim_frame, 1, 0, NULL);
}

// 0x800E9D24
// https://decomp.me/scratch/pG1xg // Fox & Falco's air -> ground Reflector End
// Motion State handler
void ftFx_SpecialAirLwEnd_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwEnd,
                              (Ft_MF_SkipColAnim | Ft_MF_UpdateCmd),
                              fp->cur_anim_frame, 1, 0, NULL);
    ftCommon_8007D468(fp);
}

// 0x800E9D88
// https://decomp.me/scratch/oUZ7Q // Fox & Falco's grounded Reflector End
// Motion State handler
void ftFx_SpecialLwEnd_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialLwEnd, 0, 0, 1, 0, NULL);
}

// 0x800E9DC0 - Fox & Falco's aerial Reflector End Motion State handler
void ftFx_SpecialAirLwEnd_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirLwEnd, 0, 0, 1, 0, NULL);
}
