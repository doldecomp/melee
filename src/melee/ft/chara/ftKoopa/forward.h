#ifndef MELEE_FT_CHARA_FTKOOPA_FORWARD_H
#define MELEE_FT_CHARA_FTKOOPA_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftKp_MotionFlags {
    ftKp_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftKp_MF_SpecialN = ftKp_MF_Special | FtStateChange_PreserveFastFall,
    ftKp_MF_SpecialS = ftKp_MF_Special | FtStateChange_PreserveGfx,
    ftKp_MF_SpecialHi = ftKp_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx | FtStateChange_PreserveSfx,
    ftKp_MF_SpecialLwStart = ftKp_MF_Special |
                             FtStateChange_PreserveColAnimHitStatus |
                             FtStateChange_PreserveSfx,
    ftKp_MF_SpecialNStart = ftKp_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftKp_MF_SpecialAirS = ftKp_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftKp_MF_SpecialAirHi = ftKp_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftKp_MF_SpecialAirLw =
        ftKp_MF_SpecialLwStart | FtStateChange_SkipUpdateParasol,
    ftKp_MF_SpecialNLoop = ftKp_MF_SpecialN | FtStateChange_Unk_19,
    ftKp_MF_SpecialAirNLoop =
        ftKp_MF_SpecialNLoop | FtStateChange_SkipUpdateParasol,
} ftKp_MotionFlags;

typedef enum ftKoopa_MotionState {
    ftKp_MS_SpecialNStart = ftCo_MS_Count,
    ftKp_MS_SpecialNLoop,
    ftKp_MS_SpecialNEnd,
    ftKp_MS_SpecialAirNStart,
    ftKp_MS_SpecialAirNLoop,
    ftKp_MS_SpecialAirNEnd,
    ftKp_MS_SpecialS,
    ftKp_MS_SpecialSCatch,
    ftKp_MS_SpecialSCatchAttack,
    ftKp_MS_SpecialSWait,
    ftKp_MS_SpecialSThrowF,
    ftKp_MS_SpecialSThrowB,
    ftKp_MS_SpecialAirS,
    ftKp_MS_SpecialAirSCatch,
    ftKp_MS_SpecialAirSCatchAttack,
    ftKp_MS_SpecialAirSWait,
    ftKp_MS_SpecialAirSThrowF,
    ftKp_MS_SpecialAirSThrowB,
    ftKp_MS_SpecialHi,
    ftKp_MS_SpecialAirHi,
    ftKp_MS_SpecialLwStart,
    ftKp_MS_SpecialAirLw,
    ftKp_MS_SpecialLwLanding,
} ftKoopa_MotionState;

#endif
