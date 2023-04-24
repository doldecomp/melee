#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftGw_MF_Base ATTRIBUTE_USED =
    FtStateChange_SkipUpdateItemVis | FtStateChange_FreezeState;

static MotionFlags const ftGw_MF_Landing ATTRIBUTE_USED =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |
    FtStateChange_PreserveSfx | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftGw_MF_LandingAirB ATTRIBUTE_USED =
    ftGw_MF_Landing | FtStateChange_PreserveGfx;

static MotionFlags const ftGw_MF_LandingAirHi ATTRIBUTE_USED =
    ftGw_MF_LandingAirB | FtStateChange_PreserveFastFall;

static MotionFlags const ftGw_MF_Attack ATTRIBUTE_USED =
    ftGw_MF_Base | FtStateChange_PreserveSfx;

static MotionFlags const ftGw_MF_AttackLw3 ATTRIBUTE_USED =
    ftGw_MF_Attack | FtStateChange_SkipUpdateHit;

static MotionFlags const ftGw_MF_AttackAirN ATTRIBUTE_USED =
    ftGw_MF_Attack | ftGw_MF_Landing;

static MotionFlags const ftGw_MF_AttackAirB ATTRIBUTE_USED =
    ftGw_MF_AttackAirN | FtStateChange_PreserveGfx;

static MotionFlags const ftGw_MF_AttackAirHi ATTRIBUTE_USED =
    ftGw_MF_AttackAirB | FtStateChange_PreserveFastFall;

static MotionFlags const ftGw_MF_AttackS4 ATTRIBUTE_USED =
    ftGw_MF_AttackLw3 | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateRumble;

static MotionFlags const ftGw_MF_Attack11 ATTRIBUTE_USED =
    ftGw_MF_Attack | FtStateChange_PreserveFastFall | FtStateChange_Unk_19;

static MotionFlags const ftGw_MF_Attack100 ATTRIBUTE_USED =
    ftGw_MF_Attack | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_Unk_19;

static MotionFlags const ftGw_MF_Special ATTRIBUTE_USED =
    ftGw_MF_Base | FtStateChange_SkipUpdateModel |
    FtStateChange_Unk_UpdatePhys;

static MotionFlags const ftGw_MF_SpecialS ATTRIBUTE_USED =
    ftGw_MF_Special | FtStateChange_PreserveGfx;

static MotionFlags const ftGw_MF_SpecialHi ATTRIBUTE_USED =
    ftGw_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx;

static MotionFlags const ftGw_MF_SpecialLwCatch ATTRIBUTE_USED =
    ftGw_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftGw_MF_SpecialN ATTRIBUTE_USED =
    ftGw_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static MotionFlags const ftGw_MF_SpecialAirS ATTRIBUTE_USED =
    ftGw_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftGw_MF_SpecialAirHi ATTRIBUTE_USED =
    ftGw_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftGw_MF_SpecialAirLwCatch ATTRIBUTE_USED =
    ftGw_MF_SpecialLwCatch | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftGw_MF_SpecialAirN ATTRIBUTE_USED =
    ftGw_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftGw_MF_SpecialLw ATTRIBUTE_USED =
    ftGw_MF_SpecialLwCatch | FtStateChange_Unk_19;

static MotionFlags const ftGw_MF_SpecialAirLw ATTRIBUTE_USED =
    ftGw_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

// Mr. Game & Watch Motion State IDs
typedef enum ftGameWatch_MotionState {
    ftGw_MS_Attack11 = ftCo_MS_Count,
    ftGw_MS_Attack100Start,
    ftGw_MS_Attack100Loop,
    ftGw_MS_Attack100End,
    ftGw_MS_AttackLw3,
    ftGw_MS_AttackS4,
    ftGw_MS_AttackAirN,
    ftGw_MS_AttackAirB,
    ftGw_MS_AttackAirHi,
    ftGw_MS_LandingAirN,
    ftGw_MS_LandingAirB,
    ftGw_MS_LandingAirHi,
    ftGw_MS_SpecialN,
    ftGw_MS_SpecialAirN,
    ftGw_MS_SpecialS1,
    ftGw_MS_SpecialS2,
    ftGw_MS_SpecialS3,
    ftGw_MS_SpecialS4,
    ftGw_MS_SpecialS5,
    ftGw_MS_SpecialS6,
    ftGw_MS_SpecialS7,
    ftGw_MS_SpecialS8,
    ftGw_MS_SpecialS9,
    ftGw_MS_SpecialAirS1,
    ftGw_MS_SpecialAirS2,
    ftGw_MS_SpecialAirS3,
    ftGw_MS_SpecialAirS4,
    ftGw_MS_SpecialAirS5,
    ftGw_MS_SpecialAirS6,
    ftGw_MS_SpecialAirS7,
    ftGw_MS_SpecialAirS8,
    ftGw_MS_SpecialAirS9,
    ftGw_MS_SpecialHi,
    ftGw_MS_SpecialAirHi,
    ftGw_MS_SpecialLw,
    ftGw_MS_SpecialLw_Catch,
    ftGw_MS_SpecialLw_Shoot,
    ftGw_MS_SpecialAirLw,
    ftGw_MS_SpecialAirLw_Catch,
    ftGw_MS_SpecialAirLw_Shoot,
} ftGameWatch_MotionState;

typedef enum ftGameWatch_PanicLevel {
    ftGw_Panic_Empty,
    ftGw_Panic_Low,
    ftGw_Panic_Mid,
    ftGw_Panic_Full,
} ftGameWatch_PanicLevel;

#endif
