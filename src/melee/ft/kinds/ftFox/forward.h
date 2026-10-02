/**
 * @file forward.h
 * @brief Forward declarations and motion state definitions for Fox & Falco
 * @details Declares motion flags, motion state IDs, submotion IDs, and state
 * indices for Fox's special moves (Neutral-B Blaster, Side-B Fox Illusion,
 * Up-B Fire Fox, Down-B Reflector/Shine) and the Star Fox Smash Taunt. Module
 * prefix: ftFx
 */

#ifndef MELEE_FT_CHARA_FTFOX_FORWARD_H
#define MELEE_FT_CHARA_FTFOX_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

typedef struct ftFox_DatAttrs ftFox_DatAttrs;

/// Motion flags for Fox & Falco's Star Fox Smash Taunt
static MotionFlags const ftFx_MF_Appeal =
    Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipAnimVel | Ft_MF_Unk06;

/// Base motion flags common to Fox & Falco special moves
static MotionFlags const ftFx_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

/// Motion flags for grounded Neutral-B (Blaster)
static MotionFlags const ftFx_MF_SpecialN =
    ftFx_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

/// Motion flags for grounded Side-B (Fox Illusion / Falco Phantasm)
static MotionFlags const ftFx_MF_SpecialS =
    ftFx_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

/// Motion flags for Up-B (Fire Fox / Firebird)
static MotionFlags const ftFx_MF_SpecialHi =
    ftFx_MF_SpecialS | Ft_MF_KeepFastFall;

/// Motion flags for aerial Neutral-B (Blaster)
static MotionFlags const ftFx_MF_SpecialAirN =
    ftFx_MF_SpecialN | Ft_MF_SkipParasol;

/// Motion flags for aerial Side-B (Fox Illusion / Falco Phantasm)
static MotionFlags const ftFx_MF_SpecialAirS =
    ftFx_MF_SpecialS | Ft_MF_SkipParasol;

/// Motion flags for aerial Up-B charge/hold (Fire Fox / Firebird)
static MotionFlags const ftFx_MF_SpecialAirHiHold =
    ftFx_MF_SpecialHi | Ft_MF_SkipParasol;

/// Motion flags for grounded Down-B (Reflector / Shine)
static MotionFlags const ftFx_MF_SpecialLw =
    ftFx_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipColAnim;

/// Motion flags for aerial Down-B (Reflector / Shine)
static MotionFlags const ftFx_MF_SpecialAirLw =
    ftFx_MF_SpecialLw | Ft_MF_SkipParasol;

/// Motion flags for grounded Neutral-B firing loop (Blaster)
static MotionFlags const ftFx_MF_SpecialNLoop = ftFx_MF_SpecialN | Ft_MF_Unk19;

/// Motion flags for aerial Neutral-B firing loop (Blaster)
static MotionFlags const ftFx_MF_SpecialAirNLoop =
    ftFx_MF_SpecialNLoop | Ft_MF_SkipParasol;

/// Motion flags for grounded Down-B active loop (Reflector / Shine)
static MotionFlags const ftFx_MF_SpecialLwLoop =
    ftFx_MF_SpecialLw | Ft_MF_Unk19;

/// Motion flags for aerial Down-B active loop (Reflector / Shine)
static MotionFlags const ftFx_MF_SpecialAirLwLoop =
    ftFx_MF_SpecialLwLoop | Ft_MF_SkipParasol;

/**
 * @brief Fox & Falco Motion State identifiers (Action States 341-375)
 * @details Covers Neutral-B (Blaster), Side-B (Fox Illusion), Up-B (Fire Fox),
 * Down-B (Reflector), and Smash Taunt (Corneria/Venom comms).
 */
typedef enum ftFox_MotionState {
    ftFx_MS_SpecialNStart =
        ftCo_MS_Count,    ///< Neutral-B (Blaster) grounded draw weapon (341)
    ftFx_MS_SpecialNLoop, ///< Neutral-B (Blaster) grounded fire loop (342)
    ftFx_MS_SpecialNEnd, ///< Neutral-B (Blaster) grounded holster weapon (343)
    ftFx_MS_SpecialAirNStart, ///< Neutral-B (Blaster) aerial draw weapon (344)
    ftFx_MS_SpecialAirNLoop,  ///< Neutral-B (Blaster) aerial fire loop (345)
    ftFx_MS_SpecialAirNEnd,   ///< Neutral-B (Blaster) aerial holster weapon
                              ///< (346)
    ftFx_MS_SpecialSStart,    ///< Side-B (Fox Illusion) grounded startup (347)
    ftFx_MS_SpecialS,         ///< Side-B (Fox Illusion) grounded dash (348)
    ftFx_MS_SpecialSEnd,      ///< Side-B (Fox Illusion) grounded end lag (349)
    ftFx_MS_SpecialAirSStart, ///< Side-B (Fox Illusion) aerial startup (350)
    ftFx_MS_SpecialAirS,      ///< Side-B (Fox Illusion) aerial dash (351)
    ftFx_MS_SpecialAirSEnd,   ///< Side-B (Fox Illusion) aerial end lag /
                              ///< freefall (352)
    ftFx_MS_SpecialHiHold, ///< Up-B (Fire Fox) grounded charge / angle select
                           ///< (353)
    ftFx_MS_SpecialHiHoldAir, ///< Up-B (Fire Fox) aerial charge / angle select
                              ///< (354)
    ftFx_MS_SpecialHi,        ///< Up-B (Fire Fox) grounded launch travel (355)
    ftFx_MS_SpecialAirHi,     ///< Up-B (Fire Fox) aerial launch travel (356)
    ftFx_MS_SpecialHiLanding, ///< Up-B (Fire Fox) landing lag (357)
    ftFx_MS_SpecialHiFall,  ///< Up-B (Fire Fox) special fall / freefall (358)
    ftFx_MS_SpecialHiBound, ///< Up-B (Fire Fox) wall/ceiling/floor rebound
                            ///< (359)
    ftFx_MS_SpecialLwStart, ///< Down-B (Reflector) grounded startup / frame 1
                            ///< hit (360)
    ftFx_MS_SpecialLwLoop,  ///< Down-B (Reflector) grounded active loop /
                            ///< jump-cancelable (361)
    ftFx_MS_SpecialLwHit, ///< Down-B (Reflector) grounded projectile reflected
                          ///< (362)
    ftFx_MS_SpecialLwEnd, ///< Down-B (Reflector) grounded release lag (363)
    ftFx_MS_SpecialLwTurn, ///< Down-B (Reflector) grounded turnaround (364)
    ftFx_MS_SpecialAirLwStart, ///< Down-B (Reflector) aerial startup / stall
                               ///< (365)
    ftFx_MS_SpecialAirLwLoop,  ///< Down-B (Reflector) aerial active loop (366)
    ftFx_MS_SpecialAirLwHit,   ///< Down-B (Reflector) aerial projectile
                               ///< reflected (367)
    ftFx_MS_SpecialAirLwEnd,   ///< Down-B (Reflector) aerial release lag (368)
    ftFx_MS_SpecialAirLwTurn,  ///< Down-B (Reflector) aerial turnaround (369)
    ftFx_MS_AppealSStartR,     ///< Smash Taunt start facing right (370)
    ftFx_MS_AppealSStartL,     ///< Smash Taunt start facing left (371)
    ftFx_MS_AppealSR, ///< Smash Taunt active transmission facing right (372)
    ftFx_MS_AppealSL, ///< Smash Taunt active transmission facing left (373)
    ftFx_MS_AppealSEndR, ///< Smash Taunt end facing right (374)
    ftFx_MS_AppealSEndL, ///< Smash Taunt end facing left (375)
    ftFx_MS_Count,       ///< Total Motion State count
    ftFx_MS_SelfCount =
        ftFx_MS_Count -
        ftCo_MS_Count, ///< Fox-specific Motion State count (35)
} ftFox_MotionState;

/**
 * @brief Fox & Falco Submotion (animation) identifiers
 */
typedef enum ftFx_Submotion {
    ftFx_SM_SpecialNStart =
        ftCo_SM_Count,    ///< Neutral-B (Blaster) grounded draw animation
    ftFx_SM_SpecialNLoop, ///< Neutral-B (Blaster) grounded fire loop animation
    ftFx_SM_SpecialNEnd,  ///< Neutral-B (Blaster) grounded holster animation
    ftFx_SM_SpecialAirNStart, ///< Neutral-B (Blaster) aerial draw animation
    ftFx_SM_SpecialAirNLoop,  ///< Neutral-B (Blaster) aerial fire loop
                              ///< animation
    ftFx_SM_SpecialAirNEnd,   ///< Neutral-B (Blaster) aerial holster animation
    ftFx_SM_SpecialSStart,    ///< Side-B (Fox Illusion) grounded startup
                              ///< animation
    ftFx_SM_SpecialS,    ///< Side-B (Fox Illusion) grounded dash animation
    ftFx_SM_SpecialSEnd, ///< Side-B (Fox Illusion) grounded end animation
    ftFx_SM_SpecialAirSStart, ///< Side-B (Fox Illusion) aerial startup
                              ///< animation
    ftFx_SM_SpecialAirS,      ///< Side-B (Fox Illusion) aerial dash animation
    ftFx_SM_SpecialAirSEnd,   ///< Side-B (Fox Illusion) aerial end animation
    ftFx_SM_SpecialHiHold,    ///< Up-B (Fire Fox) grounded charge animation
    ftFx_SM_SpecialHiHoldAir, ///< Up-B (Fire Fox) aerial charge animation
    ftFx_SM_SpecialHi,        ///< Up-B (Fire Fox) launch travel animation
    ftFx_SM_SpecialHiLanding, ///< Up-B (Fire Fox) landing animation
    ftFx_SM_SpecialHiFall,    ///< Up-B (Fire Fox) freefall animation
    ftFx_SM_SpecialHiBound,   ///< Up-B (Fire Fox) rebound animation
    ftFx_SM_SpecialLwStart, ///< Down-B (Reflector) grounded startup animation
    ftFx_SM_SpecialLwLoop,  ///< Down-B (Reflector) grounded active loop
                            ///< animation
    ftFx_SM_SpecialLwHit,   ///< Down-B (Reflector) grounded reflect hit
                            ///< animation
    ftFx_SM_SpecialLwEnd,   ///< Down-B (Reflector) grounded release animation
    ftFx_SM_SpecialAirLwStart, ///< Down-B (Reflector) aerial startup animation
    ftFx_SM_SpecialAirLwLoop,  ///< Down-B (Reflector) aerial active loop
                               ///< animation
    ftFx_SM_SpecialAirLwHit,   ///< Down-B (Reflector) aerial reflect hit
                               ///< animation
    ftFx_SM_SpecialAirLwEnd,   ///< Down-B (Reflector) aerial release animation
    ftFx_SM_AppealSStartR,     ///< Smash Taunt start facing right animation
    ftFx_SM_AppealSStartL,     ///< Smash Taunt start facing left animation
    ftFx_SM_AppealSR,    ///< Smash Taunt transmission facing right animation
    ftFx_SM_AppealSL,    ///< Smash Taunt transmission facing left animation
    ftFx_SM_AppealSEndR, ///< Smash Taunt end facing right animation
    ftFx_SM_AppealSEndL, ///< Smash Taunt end facing left animation
    ftFx_SM_Count,       ///< Total Submotion count
    ftFx_SM_SelfCount =
        ftFx_SM_Count - ftCo_SM_Count, ///< Fox-specific Submotion count
} ftFx_Submotion;

/**
 * @brief Blaster sub-action indices used by the Blaster item and throw logic
 */
typedef enum ftFx_SpecialNIndex {
    // msid = currASID - ftFx_MS_SpecialNStart;
    ftFx_SpecialNIndex_Start,    ///< Grounded draw weapon
    ftFx_SpecialNIndex_Loop,     ///< Grounded firing loop
    ftFx_SpecialNIndex_End,      ///< Grounded holster weapon
    ftFx_SpecialNIndex_AirStart, ///< Aerial draw weapon
    ftFx_SpecialNIndex_AirLoop,  ///< Aerial firing loop
    ftFx_SpecialNIndex_AirEnd,   ///< Aerial holster weapon
    // msid = currASID - ftCo_MS_CatchDash;
    ftFx_SpecialNIndex_ThrowB,  ///< Back throw blaster shot
    ftFx_SpecialNIndex_ThrowHi, ///< Up throw blaster shot
    ftFx_SpecialNIndex_ThrowLw, ///< Down throw blaster shot
    // ftFx_SpecialNIndex_None,
} ftFx_SpecialNIndex;

#endif
