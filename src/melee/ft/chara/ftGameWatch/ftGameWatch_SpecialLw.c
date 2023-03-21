#include "forward.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcoll.h"
#include "ft/ftparts.h"
#include "ftGameWatch/ftgamewatch.h"
#include "it/code_8027CF30.h"
#include "lb/forward.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>
#include <baselib/gobjproc.h>

/// Create Oil Panic Item
void ftGameWatch_ItemPanicSetup(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x2268_panicGObj == NULL) {
        /// @todo Can't move below @c _.
        Vec3 vec;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[16];
#endif

        func_8000B1CC(fp->x5E8_fighterBones[TopN].x0_jobj, NULL, &vec);

        fp->fv.gw.x2268_panicGObj =
            func_802C7D60(gobj, &vec, 0, fp->facing_dir);
    }

    if (fp->fv.gw.x2268_panicGObj != NULL) {
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
    }

    fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemPanicEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemPanicExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

/// Set Oil Panic flags + clear pointers
void ftGameWatch_ItemPanicSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGameWatch_ItemPanicExitHitlag(gobj);
    fp->fv.gw.x2268_panicGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

/// Remove Oil Panic item
void ftGameWatch_ItemPanicRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2268_panicGObj != NULL) {
        func_802C7E94(fp->fv.gw.x2268_panicGObj);
        ftGameWatch_ItemPanicSetFlag(gobj);
    }
}

/// Apply hitlag to Oil Panic item
void ftGameWatch_ItemPanicEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2268_panicGObj != NULL)
        func_802C7EE0(fp->fv.gw.x2268_panicGObj);
}

/// Remove hitlag for Oil Panic item
void ftGameWatch_ItemPanicExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2268_panicGObj != NULL)
        func_802C7F00(fp->fv.gw.x2268_panicGObj);
}

/// Check if Mr. Game & Watch is in any of his Oil Panic Action States
bool ftGameWatch_ItemCheckPanicRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo @c enum
    enum_t msid = fp->motion_id;

    if (msid >= ftGw_MS_SpecialLw_Shoot && msid <= ftGw_MS_SpecialAirLw_Shoot)
    {
        return false;
    }

    return true;
}

/// Update Oil Panic charge level indicator models
void ftGameWatch_SpecialLw_UpdateBucketModel(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_80074B0C(gobj, 5, 2);

    switch (fp->fv.gw.x2238_panicCharge) {
    case ftGw_Panic_Empty:
        /// @todo @c enum for parts
        func_80074B0C(gobj, 6, -1);
        func_80074B0C(gobj, 7, -1);
        func_80074B0C(gobj, 8, -1);
        return;
    case ftGw_Panic_Low:
        func_80074B0C(gobj, 6, 0);
        func_80074B0C(gobj, 7, -1);
        func_80074B0C(gobj, 8, -1);
        return;
    case ftGw_Panic_Mid:
        func_80074B0C(gobj, 6, 0);
        func_80074B0C(gobj, 7, 0);
        func_80074B0C(gobj, 8, -1);
        return;
    case ftGw_Panic_Full:
    default:
        func_80074B0C(gobj, 6, 0);
        func_80074B0C(gobj, 7, 0);
        func_80074B0C(gobj, 8, 0);
        return;
    }
}

inline void ftGameWatch_SpecialLw_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.gw.SpecialLw.isRelease = false;
    fp->mv.gw.SpecialLw.turnFrames = 0;
}

/// Mr. Game & Watch's Oil Panic Start Action State handler
void ftGameWatch_SpecialLw_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2238_panicCharge >= ftGw_Panic_Full) {
        ftGameWatch_SpecialLwShoot_ReleaseOil(gobj);
        return;
    }

    fp->x80_self_vel.y = 0;

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw, 0, NULL, 0, 1, 0);

    func_8006EBA4(gobj);
    ftGameWatch_SpecialLw_SetVars(gobj);
}

void ftGameWatch_SpecialAirLw_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->fv.gw.x2238_panicCharge >= ftGw_Panic_Full) {
        ftGameWatch_SpecialAirLwShoot_ReleaseOil(gobj);
        return;
    }

    fp->x80_self_vel.x /= sa->x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE;
    fp->x80_self_vel.y = 0;

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw, 0, NULL, 0, 1, 0);

    func_8006EBA4(gobj);
    ftGameWatch_SpecialLw_SetVars(gobj);
}

static inline void ftGameWatch_SpecialLw_UpdateVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    if (ftcmd_var == 1) {
        fp->x2200_ftcmd_var0 = 2;
        ftColl_CreateAbsorbHit(gobj, &sa->x80_GAMEWATCH_PANIC_ABSORPTION);
    } else if (ftcmd_var == 0) {
        fp->x2218_flag.bits.b6 = false;
    }

    if (fp->x2200_ftcmd_var0 != 0)
        ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
}

static int const anim_update_frame = 38;

/// Mr. Game & Watch's grounded Oil Panic Loop Animation callback
void ftGameWatch_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLw_Anim.
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Frame number constant
    if (fp->x894_currentAnimFrame == anim_update_frame &&
        !fp->mv.gw.SpecialLw.isRelease)
    {
        ftGameWatch_SpecialLw_UpdateAction(gobj, 5);
    }

    ftGameWatch_SpecialLw_UpdateVars(gobj);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Loop Animation callback
void ftGameWatch_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x894_currentAnimFrame == anim_update_frame &&
        !fp->mv.gw.SpecialLw.isRelease)
    {
        ftGameWatch_SpecialAirLw_UpdateAction(gobj, 5);
    }

    ftGameWatch_SpecialLw_UpdateVars(gobj);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Loop IASA callback
void ftGameWatch_SpecialLw_IASA(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLw_IASA.
    Fighter* fp = GET_FIGHTER(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        int turn_frames = fp->mv.gw.SpecialLw.turnFrames;
        ftGameWatchAttributes* sa = getFtSpecialAttrsD(fp);

        if (turn_frames > 0) {
            fp->mv.gw.SpecialLw.turnFrames = turn_frames - 1;
        } else {
            f32 stick_range = fp->input.x620_lstick_x;

            if (stick_range < 0)
                stick_range = -stick_range;

            if (stick_range > p_ftCommonData->x0) {
                f32 facing_dir = fp->facing_dir;

                func_8007D9FC(fp);

                if (facing_dir != fp->facing_dir) {
                    fp->mv.gw.SpecialLw.turnFrames =
                        sa->x7C_GAMEWATCH_PANIC_TURN_FRAMES;
                }
            }
        }
    }

    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B))
        fp->mv.gw.SpecialLw.isRelease = true;
}

/// Mr. Game & Watch's aerial Oil Panic Loop IASA callback
void ftGameWatch_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        int turnFrames = fp->mv.gw.SpecialLw.turnFrames;
        ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

        if (turnFrames > 0) {
            fp->mv.gw.SpecialLw.turnFrames = turnFrames - 1;
        } else {
            f32 stick_range = fp->input.x620_lstick_x;

            if (stick_range < 0)
                stick_range = -stick_range;

            if (stick_range > p_ftCommonData->x0) {
                f32 facingDir = fp->facing_dir;
                func_8007D9FC(fp);

                if (facingDir != fp->facing_dir) {
                    fp->mv.gw.SpecialLw.turnFrames =
                        sa->x7C_GAMEWATCH_PANIC_TURN_FRAMES;
                }
            }
        }
    }

    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B))
        fp->mv.gw.SpecialLw.isRelease = true;
}

/// Mr. Game & Watch's grounded Oil Panic Loop Physics callback
void ftGameWatch_SpecialLw_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
    func_8007AF10(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Loop Physics callback
void ftGameWatch_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    func_8007D494(fp, sa->x6C_GAMEWATCH_PANIC_FALL_ACCEL,
                  sa->x70_GAMEWATCH_PANIC_VEL_Y_MAX);

    func_8007CE94(fp, sa->x68_GAMEWATCH_PANIC_MOMENTUM_MUL);
    func_8007AF10(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Loop Collision callback
void ftGameWatch_SpecialLw_Coll(HSD_GObj* gobj)
{
    if (func_800827A0(gobj) == false)
        ftGameWatch_SpecialLw_GroundToAir(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Loop Collision callback
void ftGameWatch_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj) != false)
        ftGameWatch_SpecialAirLw_AirToGround(gobj);
}

static inline void ftGameWatch_SpecialLw_UpdateVarsColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    if (ftcmd_var == 2) {
        ftColl_CreateAbsorbHit(gobj, &sa->x80_GAMEWATCH_PANIC_ABSORPTION);
    } else if (ftcmd_var == 0) {
        fp->x2218_flag.bits.b6 = false;
    }

    if (fp->x2200_ftcmd_var0 != 0)
        ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
}

static Fighter_MotionStateChangeFlags const transition_flags0 =
    FtStateChange_PreserveGfx | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateHit | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

void ftGameWatch_SpecialLw_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw, transition_flags0,
                              NULL, fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateVarsColl(gobj);
}

void ftGameWatch_SpecialAirLw_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw, transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateVarsColl(gobj);
}

static inline void ftGameWatch_SpecialLw_UpdateVarsAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

    if (fp->x2200_ftcmd_var0 >= 1) {
        fp->x2200_ftcmd_var0 = 2;

        ftColl_CreateAbsorbHit(gobj, &sa->x80_GAMEWATCH_PANIC_ABSORPTION);
    }

    if (fp->x2200_ftcmd_var0 != 0)
        ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
}

/// @todo Combine common flags with #transition_flags0.
static Fighter_MotionStateChangeFlags const transition_flags1 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

void ftGameWatch_SpecialLw_UpdateAction(HSD_GObj* gobj, f32 anim_frame)
{
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw, transition_flags1, NULL,
                              anim_frame - 1, 1, 0);

    func_8006EBA4(gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(gobj);
}

void ftGameWatch_SpecialAirLw_UpdateAction(HSD_GObj* gobj, f32 anim_frame)
{
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw, transition_flags1,
                              NULL, anim_frame - 1, 1, 0);

    func_8006EBA4(gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Fill Action State handler
void ftGameWatch_SpecialLwCatch_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    if (fp->fv.gw.x2238_panicCharge >= ftGw_Panic_Full) {
        func_8008A2BC(gobj);
        return;
    }

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw, transition_flags1, NULL,
                              4, 1, 0);

    func_8006EBA4(gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Fill Animation callback
void ftGameWatch_SpecialAirLwCatch_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    if (fp->fv.gw.x2238_panicCharge >= ftGw_Panic_Full) {
        func_800CC730(gobj);
        return;
    }

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw, transition_flags1,
                              NULL, 4, 1, 0);

    func_8006EBA4(gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Fill IASA callback
void ftGameWatch_SpecialLwCatch_IASA(HSD_GObj* gobj) {}

/// Mr. Game & Watch's aerial Oil Panic Fill IASA callback
void ftGameWatch_SpecialAirLwCatch_IASA(HSD_GObj* gobj) {}

/// Mr. Game & Watch's grounded Oil Panic Fill Physics callback
void ftGameWatch_SpecialLwCatch_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Fill Physics callback
void ftGameWatch_SpecialAirLwCatch_Phys(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Fill Collision callback
void ftGameWatch_SpecialLwCatch_Coll(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftGameWatch_SpecialLwCatch_GroundToAir(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Fill Collision callback
void ftGameWatch_SpecialAirLwCatch_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        ftGameWatch_SpecialAirLwCatch_AirToGround(gobj);
}

/// Mr. Game & Watch's ground -> air Oil Panic Fill Action State handler
void ftGameWatch_SpecialLwCatch_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw_Catch,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Mr. Game & Watch's air -> ground Oil Panic Fill Action State handler
void ftGameWatch_SpecialAirLwCatch_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw_Catch, transition_flags0,
                              NULL, fp->x894_currentAnimFrame, 1, 0);
}

/// Check to enter grounded or aerial Oil Panic Fill
void ftGameWatch_AbsorbThink_DecideAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo @c enum
    enum_t msid;

    fp->fv.gw.x2238_panicCharge += fp->AbsorbAttr.x1A48_hitsTaken;
    fp->fv.gw.x223C_panicDamage += fp->AbsorbAttr.x1A44_damageTaken;

    if (fp->fv.gw.x2238_panicCharge >= ftGw_Panic_Full)
        func_800BFFD0(fp, 5, 0);

    if (fp->ground_or_air == GA_Ground)
        msid = ftGw_MS_SpecialLw_Catch;
    else
        msid = ftGw_MS_SpecialAirLw_Catch;

    Fighter_ChangeMotionState(gobj, msid, 0, NULL, 0, 1, 0);
    ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
}

static inline void ftGameWatch_SpecialLwShoot_ApplyDamage(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    int i;
    for (i = 0; i < 4; i++)
        if (fp->x914[i].state == HitCapsule_Enabled)
            func_8007ABD0(&fp->x914[i], fp->x2204_ftcmd_var1, gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Release Animation callback
void ftGameWatch_SpecialLwShoot_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLwShoot_Anim.
    ftGameWatch_SpecialLwShoot_ApplyDamage(gobj);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Release Animation callback
void ftGameWatch_SpecialAirLwShoot_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftGameWatch_SpecialLwShoot_ApplyDamage(gobj);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Release IASA callback
void ftGameWatch_SpecialLwShoot_IASA(HSD_GObj* gobj) {}

/// Mr. Game & Watch's aerial Oil Panic Release IASA callback
void ftGameWatch_SpecialAirLwShoot_IASA(HSD_GObj* gobj) {}

/// Mr. Game & Watch's grounded Oil Panic Release Physics callback
void ftGameWatch_SpecialLwShoot_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Release Physics callback
void ftGameWatch_SpecialAirLwShoot_Phys(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Release Collision callback
void ftGameWatch_SpecialLwShoot_Coll(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftGameWatch_SpecialLwShoot_GroundToAir(gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Release Collision callback
void ftGameWatch_SpecialAirLwShoot_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        ftGameWatch_SpecialAirLwShoot_AirToGround(gobj);
}

/// Mr. Game & Watch's ground -> air Oil Panic Release Action State handler
void ftGameWatch_SpecialLwShoot_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw_Shoot,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

/// Mr. Game & Watch's air -> ground Oil Panic Release Action State handler
void ftGameWatch_SpecialAirLwShoot_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw_Shoot, transition_flags0,
                              NULL, fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

/// Enter SpecialLwShoot and calculate damage
void ftGameWatch_SpecialLwShoot_ReleaseOil(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLwShoot_ReleaseOil
    /// @todo Please for the love of god stop copy-pasting code

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialLw_Shoot, 0, NULL, 0, 1, 0);

    func_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        {
            ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

            fp->x2204_ftcmd_var1 = fp->fv.gw.x223C_panicDamage *
                                   sa->x78_GAMEWATCH_PANIC_DAMAGE_MUL;

            {
                f32 panicDamage =
                    fp->x2204_ftcmd_var1 + sa->x74_GAMEWATCH_PANIC_DAMAGE_ADD;

                fp->x2204_ftcmd_var1 = panicDamage;
                fp->fv.gw.x2238_panicCharge = ftGw_Panic_Empty;
                fp->fv.gw.x223C_panicDamage = 0;
            }
        }

        ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
    }
}

/// Enter SpecialAirLwShoot and calculate damage
void ftGameWatch_SpecialAirLwShoot_ReleaseOil(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirLw_Shoot, 0, NULL, 0, 1,
                              0);

    func_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        {
            ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

            fp->x2204_ftcmd_var1 = fp->fv.gw.x223C_panicDamage *
                                   sa->x78_GAMEWATCH_PANIC_DAMAGE_MUL;

            {
                f32 panicDamage =
                    fp->x2204_ftcmd_var1 + sa->x74_GAMEWATCH_PANIC_DAMAGE_ADD;
                fp->x2204_ftcmd_var1 = panicDamage;
            }

            fp->fv.gw.x2238_panicCharge = 0;
            fp->fv.gw.x223C_panicDamage = 0;
        }

        ftGameWatch_SpecialLw_UpdateBucketModel(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
    }
}
