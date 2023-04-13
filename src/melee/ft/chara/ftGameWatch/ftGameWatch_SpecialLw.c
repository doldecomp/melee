#include <melee/lb/forward.h>

#include <sysdolphin/baselib/gobjproc.h>
#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftparts.h>
#include <melee/it/code_8027CF30.h>
#include <melee/lb/lbunknown_001.h>

/// Create Oil Panic Item
void ftGameWatch_ItemPanicSetup(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->ev.gw.x2268_panicGObj == NULL) {
        /// @todo Can't move below @c _.
        Vec3 vec;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[16];
#endif

        lb_8000B1CC(fp->x5E8_fighterBones[TopN].x0_jobj, NULL, &vec);

        fp->ev.gw.x2268_panicGObj =
            it_802C7D60(fighter_gobj, &vec, 0, fp->facing_dir);
    }

    if (fp->ev.gw.x2268_panicGObj != NULL) {
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
    }

    fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemPanicEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemPanicExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

/// Set Oil Panic flags + clear pointers
void ftGameWatch_ItemPanicSetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftGameWatch_ItemPanicExitHitlag(fighter_gobj);
    fp->ev.gw.x2268_panicGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

/// Remove Oil Panic item
void ftGameWatch_ItemPanicRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->ev.gw.x2268_panicGObj != NULL) {
        it_802C7E94(fp->ev.gw.x2268_panicGObj);
        ftGameWatch_ItemPanicSetFlag(fighter_gobj);
    }
}

/// Apply hitlag to Oil Panic item
void ftGameWatch_ItemPanicEnterHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->ev.gw.x2268_panicGObj != NULL) {
        it_802C7EE0(fp->ev.gw.x2268_panicGObj);
    }
}

/// Remove hitlag for Oil Panic item
void ftGameWatch_ItemPanicExitHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->ev.gw.x2268_panicGObj != NULL) {
        it_802C7F00(fp->ev.gw.x2268_panicGObj);
    }
}

/// Check if Mr. Game & Watch is in any of his Oil Panic Action States
bool ftGameWatch_ItemCheckPanicRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    /// @todo @c enum
    enum_t asid = fp->action_id;

    if (asid >= AS_GAMEWATCH_SPECIALLW_SHOOT &&
        asid <= AS_GAMEWATCH_SPECIALAIRLW_SHOOT)
    {
        return false;
    }

    return true;
}

/// Update Oil Panic charge level indicator models
void ftGameWatch_SpecialLw_UpdateBucketModel(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftParts_80074B0C(fighter_gobj, 5, 2);

    switch (fp->ev.gw.x2238_panicCharge) {
    case GAMEWATCH_PANIC_EMPTY:
        /// @todo @c enum for parts
        ftParts_80074B0C(fighter_gobj, 6, -1);
        ftParts_80074B0C(fighter_gobj, 7, -1);
        ftParts_80074B0C(fighter_gobj, 8, -1);
        return;
    case GAMEWATCH_PANIC_LOW:
        ftParts_80074B0C(fighter_gobj, 6, 0);
        ftParts_80074B0C(fighter_gobj, 7, -1);
        ftParts_80074B0C(fighter_gobj, 8, -1);
        return;
    case GAMEWATCH_PANIC_MID:
        ftParts_80074B0C(fighter_gobj, 6, 0);
        ftParts_80074B0C(fighter_gobj, 7, 0);
        ftParts_80074B0C(fighter_gobj, 8, -1);
        return;
    case GAMEWATCH_PANIC_FULL:
    default:
        ftParts_80074B0C(fighter_gobj, 6, 0);
        ftParts_80074B0C(fighter_gobj, 7, 0);
        ftParts_80074B0C(fighter_gobj, 8, 0);
        return;
    }
}

inline void ftGameWatch_SpecialLw_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->sv.gw.SpecialLw.isRelease = false;
    fp->sv.gw.SpecialLw.turnFrames = 0;
}

/// Mr. Game & Watch's Oil Panic Start Action State handler
void ftGameWatch_SpecialLw_StartMotion(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->ev.gw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL) {
        ftGameWatch_SpecialLwShoot_ReleaseOil(fighter_gobj);
        return;
    }

    fp->x80_self_vel.y = 0;

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW, 0, NULL, 0,
                              1, 0);

    ftAnim_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_SetVars(fighter_gobj);
}

void ftGameWatch_SpecialAirLw_StartMotion(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->ev.gw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL) {
        ftGameWatch_SpecialAirLwShoot_ReleaseOil(fighter_gobj);
        return;
    }

    fp->x80_self_vel.x /= sa->x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE;
    fp->x80_self_vel.y = 0;

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW, 0, NULL,
                              0, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_SetVars(fighter_gobj);
}

static inline void ftGameWatch_SpecialLw_UpdateVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    if (ftcmd_var == 1) {
        fp->x2200_ftcmd_var0 = 2;
        ftColl_CreateAbsorbHit(fighter_gobj,
                               &sa->x80_GAMEWATCH_PANIC_ABSORPTION);
    } else if (ftcmd_var == 0) {
        fp->x2218_flag.bits.b6 = false;
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    }
}

static int const anim_update_frame = 38;

/// Mr. Game & Watch's grounded Oil Panic Loop Animation callback
void ftGameWatch_SpecialLw_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLw_Anim.
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Frame number constant
    if (fp->x894_currentAnimFrame == anim_update_frame &&
        !fp->sv.gw.SpecialLw.isRelease)
    {
        ftGameWatch_SpecialLw_UpdateAction(fighter_gobj, 5);
    }

    ftGameWatch_SpecialLw_UpdateVars(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

/// Mr. Game & Watch's aerial Oil Panic Loop Animation callback
void ftGameWatch_SpecialAirLw_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x894_currentAnimFrame == anim_update_frame &&
        !fp->sv.gw.SpecialLw.isRelease)
    {
        ftGameWatch_SpecialAirLw_UpdateAction(fighter_gobj, 5);
    }

    ftGameWatch_SpecialLw_UpdateVars(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_800CC730(fighter_gobj);
    }
}

/// Mr. Game & Watch's grounded Oil Panic Loop IASA callback
void ftGameWatch_SpecialLw_IASA(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLw_IASA.
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        int turn_frames = fp->sv.gw.SpecialLw.turnFrames;
        ftGameWatchAttributes* sa = getFtSpecialAttrsD(fp);

        if (turn_frames > 0) {
            fp->sv.gw.SpecialLw.turnFrames = turn_frames - 1;
        } else {
            f32 stick_range = fp->input.x620_lstick_x;

            if (stick_range < 0) {
                stick_range = -stick_range;
            }

            if (stick_range > p_ftCommonData->x0) {
                f32 facing_dir = fp->facing_dir;

                ftCommon_8007D9FC(fp);

                if (facing_dir != fp->facing_dir) {
                    fp->sv.gw.SpecialLw.turnFrames =
                        sa->x7C_GAMEWATCH_PANIC_TURN_FRAMES;
                }
            }
        }
    }

    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B)) {
        fp->sv.gw.SpecialLw.isRelease = true;
    }
}

/// Mr. Game & Watch's aerial Oil Panic Loop IASA callback
void ftGameWatch_SpecialAirLw_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        int turnFrames = fp->sv.gw.SpecialLw.turnFrames;
        ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

        if (turnFrames > 0) {
            fp->sv.gw.SpecialLw.turnFrames = turnFrames - 1;
        } else {
            f32 stick_range = fp->input.x620_lstick_x;

            if (stick_range < 0) {
                stick_range = -stick_range;
            }

            if (stick_range > p_ftCommonData->x0) {
                f32 facingDir = fp->facing_dir;
                ftCommon_8007D9FC(fp);

                if (facingDir != fp->facing_dir) {
                    fp->sv.gw.SpecialLw.turnFrames =
                        sa->x7C_GAMEWATCH_PANIC_TURN_FRAMES;
                }
            }
        }
    }

    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B)) {
        fp->sv.gw.SpecialLw.isRelease = true;
    }
}

/// Mr. Game & Watch's grounded Oil Panic Loop Physics callback
void ftGameWatch_SpecialLw_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
    ftColl_8007AF10(fighter_gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Loop Physics callback
void ftGameWatch_SpecialAirLw_Phys(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    ftCommon_8007D494(fp, sa->x6C_GAMEWATCH_PANIC_FALL_ACCEL,
                      sa->x70_GAMEWATCH_PANIC_VEL_Y_MAX);

    ftCommon_8007CE94(fp, sa->x68_GAMEWATCH_PANIC_MOMENTUM_MUL);
    ftColl_8007AF10(fighter_gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Loop Collision callback
void ftGameWatch_SpecialLw_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_800827A0(fighter_gobj) == false) {
        ftGameWatch_SpecialLw_GroundToAir(fighter_gobj);
    }
}

/// Mr. Game & Watch's aerial Oil Panic Loop Collision callback
void ftGameWatch_SpecialAirLw_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj) != false) {
        ftGameWatch_SpecialAirLw_AirToGround(fighter_gobj);
    }
}

static inline void ftGameWatch_SpecialLw_UpdateVarsColl(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* sa = fp->x2D4_specialAttributes;

    if (ftcmd_var == 2) {
        ftColl_CreateAbsorbHit(fighter_gobj,
                               &sa->x80_GAMEWATCH_PANIC_ABSORPTION);
    } else if (ftcmd_var == 0) {
        fp->x2218_flag.bits.b6 = false;
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    }
}

static Fighter_ActionStateChangeFlags const transition_flags0 =
    FtStateChange_PreserveGfx | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateHit | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

void ftGameWatch_SpecialLw_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateVarsColl(fighter_gobj);
}

void ftGameWatch_SpecialAirLw_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateVarsColl(fighter_gobj);
}

static inline void
ftGameWatch_SpecialLw_UpdateVarsAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

    if (fp->x2200_ftcmd_var0 >= 1) {
        fp->x2200_ftcmd_var0 = 2;

        ftColl_CreateAbsorbHit(fighter_gobj,
                               &sa->x80_GAMEWATCH_PANIC_ABSORPTION);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    }
}

/// @todo Combine common flags with #transition_flags0.
static Fighter_ActionStateChangeFlags const transition_flags1 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

void ftGameWatch_SpecialLw_UpdateAction(HSD_GObj* fighter_gobj, f32 anim_frame)
{
    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW,
                              transition_flags1, NULL, anim_frame - 1, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
}

void ftGameWatch_SpecialAirLw_UpdateAction(HSD_GObj* fighter_gobj,
                                           f32 anim_frame)
{
    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW,
                              transition_flags1, NULL, anim_frame - 1, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Fill Action State handler
void ftGameWatch_SpecialLwCatch_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj)) {
        return;
    }

    if (fp->ev.gw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL) {
        ft_8008A2BC(fighter_gobj);
        return;
    }

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW,
                              transition_flags1, NULL, 4, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Fill Animation callback
void ftGameWatch_SpecialAirLwCatch_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj)) {
        return;
    }

    if (fp->ev.gw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL) {
        ft_800CC730(fighter_gobj);
        return;
    }

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW,
                              transition_flags1, NULL, 4, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialLw_UpdateVarsAction(fighter_gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Fill IASA callback
void ftGameWatch_SpecialLwCatch_IASA(HSD_GObj* fighter_gobj) {}

/// Mr. Game & Watch's aerial Oil Panic Fill IASA callback
void ftGameWatch_SpecialAirLwCatch_IASA(HSD_GObj* fighter_gobj) {}

/// Mr. Game & Watch's grounded Oil Panic Fill Physics callback
void ftGameWatch_SpecialLwCatch_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Fill Physics callback
void ftGameWatch_SpecialAirLwCatch_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Fill Collision callback
void ftGameWatch_SpecialLwCatch_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ftGameWatch_SpecialLwCatch_GroundToAir(fighter_gobj);
    }
}

/// Mr. Game & Watch's aerial Oil Panic Fill Collision callback
void ftGameWatch_SpecialAirLwCatch_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ftGameWatch_SpecialAirLwCatch_AirToGround(fighter_gobj);
    }
}

/// Mr. Game & Watch's ground -> air Oil Panic Fill Action State handler
void ftGameWatch_SpecialLwCatch_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW_CATCH,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Mr. Game & Watch's air -> ground Oil Panic Fill Action State handler
void ftGameWatch_SpecialAirLwCatch_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW_CATCH,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Check to enter grounded or aerial Oil Panic Fill
void ftGameWatch_AbsorbThink_DecideAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo @c enum
    enum_t asid;

    fp->ev.gw.x2238_panicCharge += fp->AbsorbAttr.x1A48_hitsTaken;
    fp->ev.gw.x223C_panicDamage += fp->AbsorbAttr.x1A44_damageTaken;

    if (fp->ev.gw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL) {
        ft_800BFFD0(fp, 5, 0);
    }

    if (fp->xE0_ground_or_air == GA_Ground) {
        asid = AS_GAMEWATCH_SPECIALLW_CATCH;
    } else {
        asid = AS_GAMEWATCH_SPECIALAIRLW_CATCH;
    }

    Fighter_ChangeMotionState(fighter_gobj, asid, 0, NULL, 0, 1, 0);
    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
}

static inline void
ftGameWatch_SpecialLwShoot_ApplyDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    int i;
    for (i = 0; i < 4; i++) {
        if (fp->x914[i].state == HitCapsule_Enabled) {
            ftColl_8007ABD0(&fp->x914[i], fp->x2204_ftcmd_var1, fighter_gobj);
        }
    }
}

/// Mr. Game & Watch's grounded Oil Panic Release Animation callback
void ftGameWatch_SpecialLwShoot_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLwShoot_Anim.
    ftGameWatch_SpecialLwShoot_ApplyDamage(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

/// Mr. Game & Watch's aerial Oil Panic Release Animation callback
void ftGameWatch_SpecialAirLwShoot_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftGameWatch_SpecialLwShoot_ApplyDamage(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_800CC730(fighter_gobj);
    }
}

/// Mr. Game & Watch's grounded Oil Panic Release IASA callback
void ftGameWatch_SpecialLwShoot_IASA(HSD_GObj* fighter_gobj) {}

/// Mr. Game & Watch's aerial Oil Panic Release IASA callback
void ftGameWatch_SpecialAirLwShoot_IASA(HSD_GObj* fighter_gobj) {}

/// Mr. Game & Watch's grounded Oil Panic Release Physics callback
void ftGameWatch_SpecialLwShoot_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

/// Mr. Game & Watch's aerial Oil Panic Release Physics callback
void ftGameWatch_SpecialAirLwShoot_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

/// Mr. Game & Watch's grounded Oil Panic Release Collision callback
void ftGameWatch_SpecialLwShoot_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ftGameWatch_SpecialLwShoot_GroundToAir(fighter_gobj);
    }
}

/// Mr. Game & Watch's aerial Oil Panic Release Collision callback
void ftGameWatch_SpecialAirLwShoot_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ftGameWatch_SpecialAirLwShoot_AirToGround(fighter_gobj);
    }
}

/// Mr. Game & Watch's ground -> air Oil Panic Release Action State handler
void ftGameWatch_SpecialLwShoot_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW_SHOOT,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

/// Mr. Game & Watch's air -> ground Oil Panic Release Action State handler
void ftGameWatch_SpecialAirLwShoot_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW_SHOOT,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
}

/// Enter SpecialLwShoot and calculate damage
void ftGameWatch_SpecialLwShoot_ReleaseOil(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftGameWatch_SpecialAirLwShoot_ReleaseOil
    /// @todo Please for the love of god stop copy-pasting code

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALLW_SHOOT, 0,
                              NULL, 0, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);

        {
            ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

            fp->x2204_ftcmd_var1 = fp->ev.gw.x223C_panicDamage *
                                   sa->x78_GAMEWATCH_PANIC_DAMAGE_MUL;

            {
                f32 panicDamage =
                    fp->x2204_ftcmd_var1 + sa->x74_GAMEWATCH_PANIC_DAMAGE_ADD;

                fp->x2204_ftcmd_var1 = panicDamage;
                fp->ev.gw.x2238_panicCharge = GAMEWATCH_PANIC_EMPTY;
                fp->ev.gw.x223C_panicDamage = 0;
            }
        }

        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
    }
}

/// Enter SpecialAirLwShoot and calculate damage
void ftGameWatch_SpecialAirLwShoot_ReleaseOil(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(fighter_gobj, AS_GAMEWATCH_SPECIALAIRLW_SHOOT, 0,
                              NULL, 0, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);

        {
            ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

            fp->x2204_ftcmd_var1 = fp->ev.gw.x223C_panicDamage *
                                   sa->x78_GAMEWATCH_PANIC_DAMAGE_MUL;

            {
                f32 panicDamage =
                    fp->x2204_ftcmd_var1 + sa->x74_GAMEWATCH_PANIC_DAMAGE_ADD;
                fp->x2204_ftcmd_var1 = panicDamage;
            }

            fp->ev.gw.x2238_panicCharge = 0;
            fp->ev.gw.x223C_panicDamage = 0;
        }

        ftGameWatch_SpecialLw_UpdateBucketModel(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemPanicSetup;
    }
}
