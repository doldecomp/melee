#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftMr_MotionFlags {
    ftMr_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftMr_MF_SpecialN = ftMr_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftMr_MF_SpecialHi = ftMr_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx | FtStateChange_PreserveSfx,
    ftMr_MF_SpecialLw = ftMr_MF_Special |
                        FtStateChange_PreserveColAnimHitStatus |
                        FtStateChange_PreserveSfx,
    ftMr_MF_SpecialAirN = ftMr_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftMr_MF_SpecialAirHi = ftMr_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftMr_MF_SpecialAirLw = ftMr_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftMr_MF_SpecialS = ftMr_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_SkipUpdateModel |
                       FtStateChange_SkipUpdateColAnim,
} ftMr_MotionFlags;

typedef enum ftMario_MotionState {
    ftMr_MS_AppealR = ftCo_MS_Count,
    ftMr_MS_AppealL,
    ftMr_MS_SpecialN,
    ftMr_MS_SpecialAirN,
    ftMr_MS_SpecialS,
    ftMr_MS_SpecialAirS,
    ftMr_MS_SpecialHi,
    ftMr_MS_SpecialAirHi,
    ftMr_MS_SpecialLw,
    ftMr_MS_SpecialAirLw,
    ftMr_MS_Count,
} ftMario_MotionState;

#endif
