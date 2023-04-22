#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftGw_MotionFlags {
    ftGw_MF_Base = FtStateChange_SkipUpdateItemVis | FtStateChange_FreezeState,
    ftGw_MF_Landing = FtStateChange_PreserveColAnimHitStatus |
                      FtStateChange_SkipUpdateHit | FtStateChange_PreserveSfx |
                      FtStateChange_SkipUpdateParasol,
    ftGw_MF_LandingAirB = ftGw_MF_Landing | FtStateChange_PreserveGfx,
    ftGw_MF_LandingAirHi =
        ftGw_MF_LandingAirB | FtStateChange_PreserveFastFall,
    ftGw_MF_Attack = ftGw_MF_Base | FtStateChange_PreserveSfx,
    ftGw_MF_AttackLw3 = ftGw_MF_Attack | FtStateChange_SkipUpdateHit,
    ftGw_MF_AttackAirN = ftGw_MF_Attack | ftGw_MF_Landing,
    ftGw_MF_AttackAirB = ftGw_MF_AttackAirN | FtStateChange_PreserveGfx,
    ftGw_MF_AttackAirHi = ftGw_MF_AttackAirB | FtStateChange_PreserveFastFall,
    ftGw_MF_AttackS4 = ftGw_MF_AttackLw3 | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateRumble,
    ftGw_MF_Attack11 =
        ftGw_MF_Attack | FtStateChange_PreserveFastFall | FtStateChange_Unk_19,
    ftGw_MF_Attack100 = ftGw_MF_Attack |
                        FtStateChange_PreserveColAnimHitStatus |
                        FtStateChange_Unk_19,
    ftGw_MF_Special = ftGw_MF_Base | FtStateChange_SkipUpdateModel |
                      FtStateChange_Unk_UpdatePhys,
    ftGw_MF_SpecialS = ftGw_MF_Special | FtStateChange_PreserveGfx,
    ftGw_MF_SpecialHi = ftGw_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx,
    ftGw_MF_SpecialLwCatch =
        ftGw_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftGw_MF_SpecialN = ftGw_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftGw_MF_SpecialAirS = ftGw_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftGw_MF_SpecialAirHi = ftGw_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftGw_MF_SpecialAirLwCatch =
        ftGw_MF_SpecialLwCatch | FtStateChange_SkipUpdateParasol,
    ftGw_MF_SpecialAirN = ftGw_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftGw_MF_SpecialLw = ftGw_MF_SpecialLwCatch | FtStateChange_Unk_19,
    ftGw_MF_SpecialAirLw = ftGw_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
} ftGw_MotionFlags;

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
