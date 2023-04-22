#ifndef MELEE_FT_CHARA_FTSEAK_FORWARD_H
#define MELEE_FT_CHARA_FTSEAK_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftSk_MotionFlags {
    ftSk_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftSk_MF_SpecialS = ftSk_MF_Special | FtStateChange_PreserveGfx,
    ftSk_MF_SpecialLw =
        ftSk_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftSk_MF_SpecialN = ftSk_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftSk_MF_SpecialHi = ftSk_MF_SpecialS | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveSfx,
    ftSk_MF_SpecialAirS = ftSk_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftSk_MF_SpecialAirLw = ftSk_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftSk_MF_SpecialAirN = ftSk_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftSk_MF_SpecialAirHi = ftSk_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftSk_MF_SpecialSLoop = ftSk_MF_SpecialS | FtStateChange_Unk_19,
    ftSk_MF_SpecialNLoop = ftSk_MF_SpecialN | FtStateChange_Unk_19,
    ftSk_MF_SpecialAirSLoop =
        ftSk_MF_SpecialSLoop | FtStateChange_SkipUpdateParasol,
    ftSk_MF_SpecialAirNLoop =
        ftSk_MF_SpecialNLoop | FtStateChange_SkipUpdateParasol,
} ftSk_MotionFlags;

typedef enum ftSeak_MotionState {
    ftSk_MS_SpecialN_ChargeStart = ftCo_MS_Count,
    ftSk_MS_SpecialN_ChargeLoop,
    ftSk_MS_SpecialN_ChargeEnd,
    ftSk_MS_SpecialN_Shoot,
    ftSk_MS_SpecialAirN_ChargeStart,
    ftSk_MS_SpecialAirN_ChargeLoop,
    ftSk_MS_SpecialAirN_ChargeEnd,
    ftSk_MS_SpecialAirN_Shoot,
    ftSk_MS_SpecialS_Start,
    ftSk_MS_SpecialS_Loop,
    ftSk_MS_SpecialS_End,
    ftSk_MS_SpecialAirS_Start,
    ftSk_MS_SpecialAirS_Loop,
    ftSk_MS_SpecialAirS_End,
    ftSk_MS_SpecialHi_Start,
    ftSk_MS_SpecialHi,
    ftSk_MS_SpecialHi_End,
    ftSk_MS_SpecialAirHi_Start,
    ftSk_MS_SpecialAirHi,
    ftSk_MS_SpecialAirHi_End,
    ftSk_MS_SpecialLw,
    ftSk_MS_SpecialLw_End,
    ftSk_MS_SpecialAirLw,
    ftSk_MS_SpecialAirLw_End,
} ftSeak_MotionState;

#endif
