#include <melee/ft/chara/ftFox/ftfox.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftparts.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/lb/lbunknown_003.h>

void ftFox_SpecialLw_CreateLoopGFX(HSD_GObj* fighter_gobj)
{
    /// @todo Shared @c inline with #ftFox_SpecialLw_CreateStartGFX.
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == false) {
        ef_Spawn(0x488, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

/// Create Reflector Start GFX
void ftFox_SpecialLw_CreateStartGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == false) {
        ef_Spawn(0x489, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

void ftFox_SpecialLw_CreateReflectGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == false) {
        ef_Spawn(0x48A, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

static inline void ftFox_SpecialLw_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftFoxAttributes* foxAttrs = foxAttrs = getFtSpecialAttrs(fp);

    fp->foxVars.SpecialLw.releaseLag =
        (s32) foxAttrs->x98_FOX_REFLECTOR_RELEASE_LAG;

    fp->foxVars.SpecialLw.isRelease = 0;
    fp->x2204_ftcmd_var1 = 4;

    fp->foxVars.SpecialLw.gravityDelay =
        (s32) foxAttrs->xA4_FOX_REFLECTOR_GRAVITY_DELAY;

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateStartGFX;
}

void ftFox_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    /// @todo Likely Missing arguments, or @c inline parameters, or something.
    ftFoxAttributes* foxAttrs;
    Fighter* fp;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_START, 0,
                                       NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftFox_SpecialLw_SetVars(fighter_gobj);
}

void ftFox_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x /= foxAttrs->xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_START,
                                       0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftFox_SpecialLw_SetVars(fighter_gobj);
}

/// Fox & Falco's grounded Reflector Loop Action State handler
static void ftFox_SpecialLwLoop_Action(HSD_GObj* fighter_gobj);

/// Fox & Falco's aerial Reflector Loop Action State handler
static void ftFox_SpecialAirLwLoop_Action(HSD_GObj* fighter_gobj);

// 0x800E8694
// https://decomp.me/scratch/isKUf // Fox & Falco's grounded Reflector Start
// Animation callback
void ftFox_SpecialLwStart_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fp->foxVars.SpecialLw.isRelease = true;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if ((s32) fp->xE0_ground_or_air == GA_Ground) {
            ftFox_SpecialLwLoop_Action(fighter_gobj);
        } else
            ftFox_SpecialAirLwLoop_Action(fighter_gobj);
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
    }
}

// 0x800E8720
// https://decomp.me/scratch/cvwhn // Fox & Falco's aerial Reflector Start
// Animation callback
void ftFox_SpecialAirLwStart_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    f32 var;

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fp->foxVars.SpecialLw.isRelease = true;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if ((s32) fp->xE0_ground_or_air == GA_Ground) {
            ftFox_SpecialLwLoop_Action(fighter_gobj);
        } else
            ftFox_SpecialAirLwLoop_Action(fighter_gobj);
        func_8007DB24(fighter_gobj);

        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
    }
}

// 0x800E87AC
// https://decomp.me/scratch/CYqHS // Fox & Falco's grounded Reflector Start
// IASA callback
void ftFox_SpecialLwStart_IASA(HSD_GObj* fighter_gobj)
{
    if (ftFox_SpecialLwStart_CheckPass(fighter_gobj))
        return;
}

// 0x800E87D0 - Fox & Falco's aerial Reflector Start IASA callback
void ftFox_SpecialAirLwStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

bool ftFox_SpecialLwStart_CheckPass(HSD_GObj* fighter_gobj)
{
    if (func_80099F1C(fighter_gobj) != false) {
        ftFox_SpecialLwStart_Pass(fighter_gobj);
        return true;
    }

    return false;
}

/// Create Reflector's reflect bubble
static void ftFox_SpecialLw_CreateReflectHit(HSD_GObj* fighter_gobj);

void ftFox_SpecialLwStart_Pass(HSD_GObj* fighter_gobj)
{
    func_8009A184(fighter_gobj, AS_FOX_SPECIALAIRLW_START,
                  FTFOX_SPECIALLW_COLL_FLAG,
                  GET_FIGHTER(fighter_gobj)->x894_currentAnimFrame);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

void ftFox_SpecialLwStart_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftFox_SpecialAirLwStart_Phys(HSD_GObj* fighter_gobj)
{
    attr* ftAttrs;
    ftFoxAttributes* foxAttrs;
    Fighter* fp = fighter_gobj->user_data;
    s32 var;
    s32 var2;

    ftAttrs = &fp->x110_attr;
    foxAttrs = fp->x2D4_specialAttributes;

    if (fp->foxVars.SpecialLw.gravityDelay != 0) {
        fp->foxVars.SpecialLw.gravityDelay--;
    } else {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL,
                      ftAttrs->x170_TerminalVelocity);
    }

    func_8007CF58(fp);
}

void ftFox_SpecialLwStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == false)
        ftFox_SpecialLwStart_GroundToAir(fighter_gobj);
}

void ftFox_SpecialAirLwStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != false)
        ftFox_SpecialAirLwStart_AirToGround(fighter_gobj);
}

void ftFox_SpecialLwStart_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_START,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftFox_SpecialAirLwStart_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_START,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    func_8007D468(fp);
}

void ftFox_SpecialLwLoop_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Shared @c inline with #ftFox_SpecialAirLwLoop_Anim.
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false)

        fp->foxVars.SpecialLw.isRelease = true;

    if (fp->foxVars.SpecialLw.releaseLag > 0)
        fp->foxVars.SpecialLw.releaseLag--;

    if (((s32) fp->foxVars.SpecialLw.releaseLag <= 0) &&
        ((s32) fp->foxVars.SpecialLw.isRelease != false))
    {
        if ((s32) fp->xE0_ground_or_air == GA_Ground) {
            ftFox_SpecialLwEnd_Action(fighter_gobj);
            return;
        }

        ftFox_SpecialAirLwEnd_Action(fighter_gobj);
    }
}

void ftFox_SpecialAirLwLoop_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false)
        fp->foxVars.SpecialLw.isRelease = true;

    if (fp->foxVars.SpecialLw.releaseLag > 0)
        fp->foxVars.SpecialLw.releaseLag--;

    if (((s32) fp->foxVars.SpecialLw.releaseLag <= 0) &&
        ((s32) fp->foxVars.SpecialLw.isRelease != false))
    {
        if ((s32) fp->xE0_ground_or_air == GA_Ground) {
            ftFox_SpecialLwEnd_Action(fighter_gobj);
            return;
        }

        ftFox_SpecialAirLwEnd_Action(fighter_gobj);
    }
}

/// Check for drop-through platform while in SpecialLwLoop
static bool ftFox_SpecialLwLoop_CheckPass(HSD_GObj* fighter_gobj);

void ftFox_SpecialLwLoop_IASA(HSD_GObj* fighter_gobj)
{
    if ((ftFox_SpecialLwTurn_Check(fighter_gobj) == false) &&
        (func_800CAED0(fighter_gobj) == false))
    {
        if (ftFox_SpecialLwLoop_CheckPass(fighter_gobj))
            return;
    }
}

void ftFox_SpecialAirLwLoop_IASA(HSD_GObj* fighter_gobj)
{
    if (ftFox_SpecialLwTurn_Check(fighter_gobj) == false &&
        func_800CB870(fighter_gobj))
    {
        /// @remarks Kinda weird, was this stripped or are there side effects?
        return;
    }
}

/// Fox & Falco's Reflector Loop Platform Drop Action State handler
static void ftFox_SpecialLwLoop_Pass(HSD_GObj* fighter_gobj);

static bool ftFox_SpecialLwLoop_CheckPass(HSD_GObj* fighter_gobj)
{
    if (func_80099F1C(fighter_gobj) != false) {
        ftFox_SpecialLwLoop_Pass(fighter_gobj);
        return true;
    }

    return false;
}

static void ftFox_SpecialLwLoop_Pass(HSD_GObj* fighter_gobj)
{
    func_8009A184(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP,
                  FTFOX_SPECIALLW_COLL_FLAG,
                  GET_FIGHTER(fighter_gobj)->x894_currentAnimFrame);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

void ftFox_SpecialLwLoop_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

static inline void ftFox_SpecialLw_InlinePhys(HSD_GObj* fighter_gobj)
{
    attr* ftAttrs;
    ftFoxAttributes* foxAttrs;
    Fighter* fp = getFighter(fighter_gobj);

    ftAttrs = getFtAttrs(fp);
    foxAttrs = getFtSpecialAttrs(fp);

    /// @todo Shared @c inline with other functions in this file.
    if (fp->foxVars.SpecialLw.gravityDelay != 0) {
        fp->foxVars.SpecialLw.gravityDelay--;
    } else {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL,
                      ftAttrs->x170_TerminalVelocity);
    }

    func_8007CF58(fp);
}

void ftFox_SpecialAirLwLoop_Phys(HSD_GObj* fighter_gobj)
{
    ftFox_SpecialLw_InlinePhys(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

/// Fox & Falco's ground -> air Reflector Loop Action State handler
static void ftFox_SpecialLwLoop_GroundToAir(HSD_GObj* fighter_gobj);

void ftFox_SpecialLwLoop_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == false)
        ftFox_SpecialLwLoop_GroundToAir(fighter_gobj);
}

/// Fox & Falco's air -> ground Reflector Loop Action State Handler
static void ftFox_SpecialAirLwLoop_AirToGround(HSD_GObj* fighter_gobj);

void ftFox_SpecialAirLwLoop_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != false)
        ftFox_SpecialAirLwLoop_AirToGround(fighter_gobj);
}

static void ftFox_SpecialLwLoop_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

static void ftFox_SpecialAirLwLoop_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_LOOP,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    func_8007D468(fp);
    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

static void ftFox_SpecialLw_CreateReflectHit(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    ftColl_CreateReflectHit(fighter_gobj,
                            &foxAttrs->xB0_FOX_REFLECTOR_REFLECTION,
                            ftFox_SpecialLwHit_Action);
}

static void ftFox_SpecialLwLoop_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_LOOP,
                                       FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f,
                                       0.0f);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

/// Fox & Falco's aerial Reflector Loop Action State handler
static void ftFox_SpecialAirLwLoop_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP,
                                       FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f,
                                       0.0f);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

/// @todo This @c pragma is fake. Probably an @c inline depth issue.
#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

/// Fox & Falco's Reflector Turn function
static void ftFox_SpecialLw_Turn(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    s32 var[2];

    fp->foxVars.SpecialLw.turnFrames--;
    if (((u32) fp->x2200_ftcmd_var0 == 0U) &&
        ((s32) fp->foxVars.SpecialLw.turnFrames <=
         foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES))
    {
        fp->x2200_ftcmd_var0 = 1;
        fp->facing_dir = -fp->facing_dir;
    }
    func_80075AF0(fp, 0,
                  -((0.01745329238474369f *
                     (180.0f / foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES)) -
                    func_80075F48(fp, 0)));
}

#ifdef MUST_MATCH
#pragma pop
#endif

/// Fox & Falco's Reflector Turn function
static inline void ftFox_SpecialLw_Turn_Inline(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    fp->foxVars.SpecialLw.turnFrames--;
    if (fp->x2200_ftcmd_var0 == false &&
        fp->foxVars.SpecialLw.turnFrames <=
            foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES)
    {
        fp->x2200_ftcmd_var0 = true;
        fp->facing_dir = -fp->facing_dir;
    }

    /// @todo Degrees-to-radians constant.
    func_80075AF0(fp, 0,
                  -((0.01745329238474369f *
                     (180.0f / foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES)) -
                    func_80075F48(fp, 0)));
}

void ftFox_SpecialLwTurn_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Shared @c inline with #ftFox_SpecialAirLwTurn_Anim.
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 var[4];

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false)
        fp->foxVars.SpecialLw.isRelease = true;

    if (fp->foxVars.SpecialLw.releaseLag > 0)
        fp->foxVars.SpecialLw.releaseLag--;

    ftFox_SpecialLw_Turn_Inline(fighter_gobj);

    if (fp->foxVars.SpecialLw.turnFrames <= 0)
        ftFox_SpecialLwHit_Check(fighter_gobj);
}

void ftFox_SpecialAirLwTurn_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 var[5];

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false)
        fp->foxVars.SpecialLw.isRelease = true;

    if (fp->foxVars.SpecialLw.releaseLag > 0)
        fp->foxVars.SpecialLw.releaseLag--;

    ftFox_SpecialLw_Turn_Inline(fighter_gobj);

    if (fp->foxVars.SpecialLw.turnFrames <= 0)
        ftFox_SpecialLwHit_Check(fighter_gobj);
}

// 0x800E91FC - Fox & Falco's grounded Reflector Turn IASA callback
void ftFox_SpecialLwTurn_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9200 - Fox & Falco's aerial Reflector Turn IASA callback
void ftFox_SpecialAirLwTurn_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9204
// https://decomp.me/scratch/sQ6Zw // Fox & Falco's grounded Reflector Turn
// Physics callback
void ftFox_SpecialLwTurn_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 0x800E9238
// https://decomp.me/scratch/3Q4Oj // Fox & Falco's aerial Reflector Turn
// Physics callback
void ftFox_SpecialAirLwTurn_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);
    s32 var;

    if (fp->foxVars.SpecialLw.gravityDelay != 0) {
        fp->foxVars.SpecialLw.gravityDelay--;
    } else {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL,
                      ftAttrs->x170_TerminalVelocity);
    }
    func_8007CF58(fp);
    func_8007AEF8(fighter_gobj);
}

// 0x800E92AC
// https://decomp.me/scratch/hKwfA // Fox & Falco's grounded Reflector Turn
// Collision callback
void ftFox_SpecialLwTurn_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == false) {
        ftFox_SpecialLwTurn_GroundToAir(fighter_gobj);
    }
}

// 0x800E92E8
// https://decomp.me/scratch/L0Bhg // Fox & Falco's aerial Reflector Turn
// Collision callback
void ftFox_SpecialAirLwTurn_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != false) {
        ftFox_SpecialAirLwTurn_GroundToAir(fighter_gobj);
    }
}

inline void ftFox_SpecialLw_SetReflectVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2218_flag.bits.b3 = 1;
    fp->cb.x21C8_callback_OnReflectHit = ftFox_SpecialLwHit_Action;
}

// 0x800E9324
// https://decomp.me/scratch/L2Rcy // Fox & Falco's ground -> air Reflector Turn
// Action State handler
void ftFox_SpecialLwTurn_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_TURN,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftFox_SpecialLw_SetReflectVars(fighter_gobj);
}

// 0x800E93A4
// https://decomp.me/scratch/BwZlC // Fox & Falco's air -> ground Reflector Turn
// Action State handler
void ftFox_SpecialAirLwTurn_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_TURN,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    ftFox_SpecialLw_SetReflectVars(fighter_gobj);
}

inline void ftFox_SpecialLwTurn_SetVarAll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    fp->x2218_flag.bits.b3 = 1;
    fp->cb.x21C8_callback_OnReflectHit = ftFox_SpecialLwHit_Action;
    fp->foxVars.SpecialLw.turnFrames =
        foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES;
    fp->x2200_ftcmd_var0 = 0;
    ftFox_SpecialLw_Turn(fighter_gobj);
}

// 0x800E942C
// https://decomp.me/scratch/Hr5UW // Fox & Falco's Reflector Turn Action State
// handler
bool ftFox_SpecialLwTurn_Check(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (func_800C97A8(fighter_gobj) != false) {
        if ((s32) fp->xE0_ground_or_air == GA_Ground) {
            Fighter_ActionStateChange_800693AC(
                fighter_gobj, AS_FOX_SPECIALLW_TURN, FIGHTER_GFX_PRESERVE, NULL,
                0.0f, 1.0f, 0.0f);
            ftFox_SpecialLwTurn_SetVarAll(fighter_gobj);
        } else {
            Fighter_ActionStateChange_800693AC(
                fighter_gobj, AS_FOX_SPECIALAIRLW_TURN, FIGHTER_GFX_PRESERVE,
                NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialLwTurn_SetVarAll(fighter_gobj);
        }
        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;

        return true;
    }
    return false;
}

inline void ftFox_SpecialLwHit_CreateReflectInline(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    ftColl_CreateReflectHit(fighter_gobj,
                            &foxAttrs->xB0_FOX_REFLECTOR_REFLECTION,
                            ftFox_SpecialLwHit_Action);
}

// 0x800E9564
// https://decomp.me/scratch/R1XfY // Fox & Falco's Reflector Hit Action State
// handler
bool ftFox_SpecialLwHit_Check(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (((s32) fp->foxVars.SpecialLw.releaseLag <= 0) &&
        ((s32) fp->foxVars.SpecialLw.isRelease != false))
    {
        if ((s32) fp->xE0_ground_or_air == GA_Ground) {
            ftFox_SpecialLwEnd_Action(fighter_gobj);
        } else {
            ftFox_SpecialAirLwEnd_Action(fighter_gobj);
        }
        return false;
    }
    if ((s32) fp->xE0_ground_or_air == GA_Ground) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_LOOP,
                                           FIGHTER_GFX_PRESERVE, NULL, 0.0f,
                                           1.0f, 0.0f);
        ftFox_SpecialLwHit_CreateReflectInline(fighter_gobj);
    } else {
        Fighter_ActionStateChange_800693AC(
            fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP, FIGHTER_GFX_PRESERVE, NULL,
            0.0f, 1.0f, 0.0f);
        ftFox_SpecialLwHit_CreateReflectInline(fighter_gobj);
    }
    return true;
}

// 0x800E965C
// https://decomp.me/scratch/S2PRK // Fox & Falco's grounded Reflector Hit
// Animation callback
void ftFox_SpecialLwHit_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 var;

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fp->foxVars.SpecialLw.isRelease = true;
    }
    if (fp->foxVars.SpecialLw.releaseLag > 0) {
        fp->foxVars.SpecialLw.releaseLag--;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (ftFox_SpecialLwHit_Check(fighter_gobj) != false) {
            func_8007DB24(fighter_gobj);
            fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
        }
    }
}

#pragma dont_inline on

// 0x800E97B4
// https://decomp.me/scratch/A9W0B // Fox & Falco's aerial Reflector Hit
// Animation callback
void ftFox_SpecialAirLwHit_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 var[2];

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fp->foxVars.SpecialLw.isRelease = true;
    }
    if (fp->foxVars.SpecialLw.releaseLag > 0) {
        fp->foxVars.SpecialLw.releaseLag--;
    }
    if ((!ftAnim_IsFramesRemaining(fighter_gobj)) &&
        (ftFox_SpecialLwHit_Check(fighter_gobj) != false))
    {
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
    }
}

#pragma dont_inline off

// 0x800E9844 - Fox & Falco's grounded Reflector Hit IASA callback
void ftFox_SpecialLwHit_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9848 - Fox & Falco's aerial Reflector Hit IASA callback
void ftFox_SpecialAirLwHit_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E984C
// https://decomp.me/scratch/P8Wyt // Fox & Falco's grounded Reflector Hit
// Physics callback
void ftFox_SpecialLwHit_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 0x800E9880
// https://decomp.me/scratch/RUoIF // Fox & Falco's aerial Reflector Hit Physics
// callback
void ftFox_SpecialAirLwHit_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);
    s32 var;

    if (fp->foxVars.SpecialLw.gravityDelay != 0) {
        fp->foxVars.SpecialLw.gravityDelay--;
    } else {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL,
                      ftAttrs->x170_TerminalVelocity);
    }
    func_8007CF58(fp);
    func_8007AEF8(fighter_gobj);
}

// 0x800E98F4
// https://decomp.me/scratch/tH9vD // Fox & Falco's grounded Reflector Hit
// Collision callback
void ftFox_SpecialLwHit_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == false) {
        ftFox_SpecialLwHit_GroundToAir(fighter_gobj);
    }
}

// 0x800E9930
// https://decomp.me/scratch/fkoyN // Fox & Falco's aerial Reflector Hit
// Collision callback
void ftFox_SpecialAirLwHit_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != false) {
        ftFox_SpecialAirLwHit_AirToGround(fighter_gobj);
    }
}

// 0x800E996C
// https://decomp.me/scratch/wnviJ // Fox & Falco's ground -> air Reflector Hit
// Action State handler
void ftFox_SpecialLwHit_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_HIT,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftFox_SpecialLwHit_SetCall(fighter_gobj);
}

// 0x800E99D4
// https://decomp.me/scratch/zXqEI // Fox & Falco's air -> ground Reflector Hit
// Action State handler
void ftFox_SpecialAirLwHit_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_HIT,
                                       FTFOX_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    ftFox_SpecialLwHit_SetCall(fighter_gobj);
}

// 0x800E9A44
// https://decomp.me/scratch/XIxX1 // Toggle bit flag and set OnReflect callback
// for Reflector
void ftFox_SpecialLwHit_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    fp->x2218_flag.bits.b3 = 1;
    fp->cb.x21C8_callback_OnReflectHit = ftFox_SpecialLwHit_Action;
}

// 0x800E9A68
// https://decomp.me/scratch/SyGv6 // Fox & Falco's Reflect Hit Action State
// handler
void ftFox_SpecialLwHit_Action(HSD_GObj* fighter_gobj)
{
    Vec3 sp14;
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    s32 ASID;

    fp->facing_dir = fp->ReflectAttr.x1A2C_reflectHitDirection;

    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, NULL,
                  &sp14);

    func_800119DC(&sp14, 0x78, 3.0f, 0.10000000149011612f, 1.0471975803375244f);

    if ((s32) fp->xE0_ground_or_air == GA_Ground) {
        ASID = 0x16A;
    } else
        ASID = 0x16F;

    Fighter_ActionStateChange_800693AC(fighter_gobj, ASID, 0, NULL, 0.0f, 1.0f,
                                       0.0f);
    ftFox_SpecialLwHit_SetCall(fighter_gobj);

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateReflectGFX;
}

// 0x800E9B40
// https://decomp.me/scratch/cfyZU // Fox & Falco's grounded Reflector End
// Animation callback
void ftFox_SpecialLwEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007DB24(fighter_gobj);
        func_8007D92C(fighter_gobj);
    }
}

// 0x800E9B84
// https://decomp.me/scratch/2gua7 // Fox & Falco's aerial Reflector End
// Animation callback
void ftFox_SpecialAirLwEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007DB24(fighter_gobj);
        func_8007D92C(fighter_gobj);
    }
}

// 0x800E9BC8 - Fox & Falco's grounded Reflector End IASA callback
void ftFox_SpecialLwEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9BCC - Fox & Falco's aerial Reflector End IASA callback
void ftFox_SpecialAirLwEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9BD0 - Fox & Falco's grounded Reflector End Physics callback
void ftFox_SpecialLwEnd_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x800E9BF0
// https://decomp.me/scratch/ivwWP // Fox & Falco's aerial Reflector End Physics
// callback
void ftFox_SpecialAirLwEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);
    s32 var;

    if (fp->foxVars.SpecialLw.gravityDelay != 0) {
        fp->foxVars.SpecialLw.gravityDelay--;
    } else {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL,
                      ftAttrs->x170_TerminalVelocity);
    }
    func_8007CF58(fp);
}

// 0x800E9C50
// https://decomp.me/scratch/chekC // Fox & Falco's grounded Reflector End
// Collision callback
void ftFox_SpecialLwEnd_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == false) {
        ftFox_SpecialLwEnd_GroundToAir(fighter_gobj);
    }
}

// 0x800E9C8C
// https://decomp.me/scratch/t5ghA // Fox & Falco's aerial Reflector End
// Collision callback
void ftFox_SpecialAirLwEnd_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != false) {
        ftFox_SpecialAirLwEnd_AirToGround(fighter_gobj);
    }
}

// 0x800E9CC8
// https://decomp.me/scratch/xAGsZ // Fox & Falco's ground -> air Reflector End
// Action State handler
void ftFox_SpecialLwEnd_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(
        fighter_gobj, AS_FOX_SPECIALAIRLW_END,
        (FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x800E9D24
// https://decomp.me/scratch/pG1xg // Fox & Falco's air -> ground Reflector End
// Action State handler
void ftFox_SpecialAirLwEnd_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(
        fighter_gobj, AS_FOX_SPECIALLW_END,
        (FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

// 0x800E9D88
// https://decomp.me/scratch/oUZ7Q // Fox & Falco's grounded Reflector End
// Action State handler
void ftFox_SpecialLwEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_END, 0,
                                       NULL, 0.0f, 1.0f, 0.0f);
}

// 0x800E9DC0 - Fox & Falco's aerial Reflector End Action State handler
void ftFox_SpecialAirLwEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_END, 0,
                                       NULL, 0.0f, 1.0f, 0.0f);
}
