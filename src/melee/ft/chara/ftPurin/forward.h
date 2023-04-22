#ifndef MELEE_FT_CHARA_FTPURIN_FORWARD_H
#define MELEE_FT_CHARA_FTPURIN_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftPr_MotionFlags {
    ftPr_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftPr_MF_SpecialHi = ftPr_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx,
    ftPr_MF_SpecialLw =
        ftPr_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftPr_MF_SpecialN = ftPr_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_PreserveSfx,
    ftPr_MF_SpecialS = ftPr_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_PreserveSfx,
    ftPr_MF_SpecialAirHi = ftPr_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftPr_MF_SpecialAirLw = ftPr_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftPr_MF_SpecialAirN = ftPr_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftPr_MF_SpecialAirS = ftPr_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftPr_MF_SpecialNCharged = ftPr_MF_SpecialN | FtStateChange_Unk_19,
    ftPr_SpecialAirNCharged =
        ftPr_MF_SpecialNCharged | FtStateChange_SkipUpdateParasol,
} ftPr_MotionFlags;

typedef enum ftPurin_MotionState {
    ftPr_MS_Jump2 = ftCo_MS_Count,
    ftPr_MS_Jump3,
    ftPr_MS_Jump4,
    ftPr_MS_Jump5,
    ftPr_MS_Jump6,
    ftPr_MS_SpecialN_ChargeStartR,
    ftPr_MS_SpecialN_ChargeStartL,
    ftPr_MS_SpecialN_ChargeLoop,
    ftPr_MS_SpecialN_ChargeFull,
    ftPr_MS_SpecialN_ChargeRelease,
    ftPr_MS_SpecialN_StartTurn,
    ftPr_MS_SpecialN_EndR,
    ftPr_MS_SpecialN_EndL,
    ftPr_MS_SpecialAirN_ChargeStartR,
    ftPr_MS_SpecialAirN_ChargeStartL,
    ftPr_MS_SpecialAirN_ChargeLoop,
    ftPr_MS_SpecialAirN_ChargeFull,
    ftPr_MS_SpecialAirN_ChargeRelease,
    ftPr_MS_SpecialAirN_StartTurn,
    ftPr_MS_SpecialAirN_EndR,
    ftPr_MS_SpecialAirN_EndL,
    ftPr_MS_SpecialN_Hit,
    ftPr_MS_SpecialS,
    ftPr_MS_SpecialAirS,
    ftPr_MS_SpecialHiL,
    ftPr_MS_SpecialAirHiL,
    ftPr_MS_SpecialHiR,
    ftPr_MS_SpecialAirHiR,
    ftPr_MS_SpecialLwL,
    ftPr_MS_SpecialAirLwL,
    ftPr_MS_SpecialLwR,
    ftPr_MS_SpecialAirLwR,
} ftPurin_MotionState;

#endif
