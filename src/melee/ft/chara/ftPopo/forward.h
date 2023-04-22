#ifndef MELEE_FT_CHARA_FTPOPO_FORWARD_H
#define MELEE_FT_CHARA_FTPOPO_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftPopo_MotionFlags {
    ftPp_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftPp_MF_SpecialLw =
        ftPp_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftPp_MF_SpecialN = ftPp_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftPp_MF_SpecialS = ftPp_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_PreserveSfx,
    ftPp_MF_SpecialHi = ftPp_MF_SpecialS | FtStateChange_PreserveFastFall,
    ftPp_MF_MS_358 = ftPp_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftPp_MF_SpecialAirN = ftPp_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftPp_MF_SpecialAirS = ftPp_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftPp_MF_SpecialAirHi = ftPp_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
} ftPopo_MotionFlags;

typedef enum ftPopo_MotionState {
    ftPp_MS_SpecialN = ftCo_MS_Count,
    ftPp_MS_SpecialAirN,
    ftPp_MS_SpecialS,
    ftPp_MS_SpecialS_Together,
    ftPp_MS_SpecialAirS,
    ftPp_MS_SpecialAirS_Together,
    ftPp_MS_SpecialHi_Start,
    ftPp_MS_SpecialHi,
    ftPp_MS_Unk_349,
    ftPp_MS_SpecialHi_Fail,
    ftPp_MS_SpecialHi_FailEnd,
    ftPp_MS_SpecialAirHi_Start,
    ftPp_MS_SpecialAirHi,
    ftPp_MS_SpecialAirHi_Fail,
    ftPp_MS_SpecialAirHi_FailEnd,
    ftPp_MS_SpecialLw,
    ftPp_MS_SpecialAirLw,
} ftPopo_MotionState;

#endif
