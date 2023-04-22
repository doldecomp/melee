#ifndef MELEE_FT_CHARA_FTFOX_FORWARD_H
#define MELEE_FT_CHARA_FTFOX_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftFx_MotionFlags {
    ftFx_MF_Appeal = FtStateChange_PreserveGfx |
                     FtStateChange_SkipUpdateModel |
                     FtStateChange_SkipUpdateAnimVel | FtStateChange_Unk_6,
    ftFx_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftFx_MF_SpecialN = ftFx_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftFx_MF_SpecialS = ftFx_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_PreserveSfx,
    ftFx_MF_SpecialHi = ftFx_MF_SpecialS | FtStateChange_PreserveFastFall,
    ftFx_MF_SpecialAirN = ftFx_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftFx_MF_SpecialAirS = ftFx_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftFx_MF_SpecialAirHiHold =
        ftFx_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftFx_MF_SpecialLw = ftFx_MF_Special |
                        FtStateChange_PreserveColAnimHitStatus |
                        FtStateChange_SkipUpdateColAnim,
    ftFx_MF_SpecialAirLw = ftFx_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftFx_MF_SpecialNLoop = ftFx_MF_SpecialN | FtStateChange_Unk_19,
    ftFx_MF_SpecialAirNLoop =
        ftFx_MF_SpecialNLoop | FtStateChange_SkipUpdateParasol,
    ftFx_MF_SpecialLwLoop = ftFx_MF_SpecialLw | FtStateChange_Unk_19,
    ftFx_MF_SpecialAirLwLoop =
        ftFx_MF_SpecialLwLoop | FtStateChange_SkipUpdateParasol,
} ftFx_MotionFlags;

typedef enum ftFox_MotionState {
    ftFx_MS_SpecialNStart = ftCo_MS_Count,
    ftFx_MS_SpecialNLoop,
    ftFx_MS_SpecialNEnd,
    ftFx_MS_SpecialAirNStart,
    ftFx_MS_SpecialAirNLoop,
    ftFx_MS_SpecialAirNEnd,
    ftFx_MS_SpecialSStart,
    ftFx_MS_SpecialS,
    ftFx_MS_SpecialSEnd,
    ftFx_MS_SpecialAirSStart,
    ftFx_MS_SpecialAirS,
    ftFx_MS_SpecialAirSEnd,
    ftFx_MS_SpecialHiStart,
    ftFx_MS_SpecialAirHiStart,
    ftFx_MS_SpecialHi,
    ftFx_MS_SpecialAirHi,
    ftFx_MS_SpecialHiEnd,
    ftFx_MS_SpecialAirHiEnd,
    ftFx_MS_SpecialHiBound,
    ftFx_MS_SpecialLwStart,
    ftFx_MS_SpecialLwLoop,
    ftFx_MS_SpecialLwReflect,
    ftFx_MS_SpecialLwEnd,
    ftFx_MS_SpecialLwTurn,
    ftFx_MS_SpecialAirLwStart,
    ftFx_MS_SpecialAirLwLoop,
    ftFx_MS_SpecialAirLwReflect,
    ftFx_MS_SpecialAirLwEnd,
    ftFx_MS_SpecialAirLwTurn,
    ftFx_MS_AppealRStart,
    ftFx_MS_AppealLStart,
    ftFx_MS_AppealR,
    ftFx_MS_AppealL,
    ftFx_MS_AppealREnd,
    ftFx_MS_AppealLEnd,
} ftFox_MotionState;

#endif
