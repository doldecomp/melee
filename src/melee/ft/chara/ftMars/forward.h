#ifndef MELEE_FT_CHARA_FTMARS_FORWARD_H
#define MELEE_FT_CHARA_FTMARS_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftMars_MotionFlags {
    ftMs_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_PreserveSfx |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftMs_MF_SpecialN = ftMs_MF_Special | FtStateChange_PreserveFastFall,
    ftMs_MF_SpecialS = ftMs_MF_Special | FtStateChange_PreserveGfx,
    ftMs_MF_SpecialHi = ftMs_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx,
    ftMs_MF_SpecialLw =
        ftMs_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftMs_MF_SpecialAirN = ftMs_MF_Special | FtStateChange_PreserveFastFall |
                          FtStateChange_SkipUpdateParasol,
    ftMs_MF_SpecialS1 = ftMs_MF_Special | FtStateChange_PreserveGfx |
                        FtStateChange_SkipUpdateParasol,
    ftMs_MF_SpecialAirHi = ftMs_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftMs_MF_SpecialAirLw = ftMs_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
} ftMars_MotionFlags;

typedef enum ftMars_MotionState {
    ftMs_MS_SpecialNChargeStart = ftCo_MS_Count,
    ftMs_MS_SpecialNChargeLoop,
    ftMs_MS_SpecialNEarlyRelease,
    ftMs_MS_SpecialNFullRelease,

    ftMs_MS_SpecialAirNChargeStart,
    ftMs_MS_SpecialAirNChargeLoop,
    ftMs_MS_SpecialAirNEarlyRelease,
    ftMs_MS_SpecialAirNFullRelease,

    ftMs_MS_SpecialS1,
    ftMs_MS_SpecialS2U,
    ftMs_MS_SpecialS2S,
    ftMs_MS_SpecialS3U,
    ftMs_MS_SpecialS3S,
    ftMs_MS_SpecialS3D,
    ftMs_MS_SpecialS4U,
    ftMs_MS_SpecialS4S,
    ftMs_MS_SpecialS4D,

    ftMs_MS_SpecialAirS1,
    ftMs_MS_SpecialAirS2U,
    ftMs_MS_SpecialAirS2S,
    ftMs_MS_SpecialAirS3U,
    ftMs_MS_SpecialAirS3S,
    ftMs_MS_SpecialAirS3D,
    ftMs_MS_SpecialAirS4U,
    ftMs_MS_SpecialAirS4S,
    ftMs_MS_SpecialAirS4D,

    ftMs_MS_SpecialHi,
    ftMs_MS_SpecialAirHi,

    ftMs_MS_SpecialLw,
    ftMs_MS_SpecialLwHit,

    ftMs_MS_SpecialAirLw,
    ftMs_MS_SpecialAirLwHit,
} ftMars_MotionState;

#endif
