#ifndef MELEE_FT_CHARA_FTSAMUS_FORWARD_H
#define MELEE_FT_CHARA_FTSAMUS_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftSs_MotionFlags {
    ftSs_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftSs_MF_SpecialN = ftSs_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftSs_MF_SpecialS = ftSs_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_SkipUpdateThrowException,
    ftSs_MF_SpecialLw = ftSs_MF_Special |
                        FtStateChange_PreserveColAnimHitStatus |
                        FtStateChange_SkipUpdateThrowException,
    ftSs_MF_SpecialHi = ftSs_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx | FtStateChange_PreserveSfx,
    ftSs_MF_SpecialAirN = ftSs_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftSs_MF_SpecialAirS = ftSs_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftSs_MF_SpecialAirLw = ftSs_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftSs_MF_SpecialAirHi = ftSs_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftSs_MF_SpecialSSmash = ftSs_MF_SpecialS | FtStateChange_SkipUpdateRumble,
    ftSs_MF_SpecialAirSSmash =
        ftSs_MF_SpecialSSmash | FtStateChange_SkipUpdateParasol,
    ftSs_MF_ZairCatch =
        FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateMetalB,
} ftSs_MotionFlags;

typedef enum ftSamus_MotionState {
    ftSs_MS_SpecialLw = ftCo_MS_Count,
    ftSs_MS_SpecialAirLw,
    ftSs_MS_SpecialN_Start,
    ftSs_MS_SpecialN_Loop,
    ftSs_MS_SpecialN_End,
    ftSs_MS_SpecialN_Shoot,
    ftSs_MS_SpecialAirN_Start,
    ftSs_MS_SpecialAirN_Shoot,
    ftSs_MS_SpecialS,

    /// @todo name
    ftSs_MS_SpecialS_Smash,

    ftSs_MS_SpecialAirS,
    ftSs_MS_SpecialAir_Smash,
    ftSs_MS_SpecialHi,
    ftSs_MS_SpecialAirHi,

    /// @todo name
    ftSs_MS_SpecialLw_BombEnd,
    ftSs_MS_SpecialAirLw_Bomb,

    /// @todo name
    ftSs_MS_Zair,
    ftSs_MS_ZairCatch,
} ftSamus_MotionState;

#endif
