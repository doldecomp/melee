#ifndef MELEE_FT_CHARA_FTLUIGI_FORWARD_H
#define MELEE_FT_CHARA_FTLUIGI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftLg_MotionFlags {
    ftLg_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftLg_MF_SpecialN = ftLg_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateThrowException,
    ftLg_MF_SpecialS = ftLg_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_PreserveSfx,
    ftLg_MF_SpecialHi = ftLg_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx | FtStateChange_PreserveSfx,
    ftLg_MF_SpecialLw = ftLg_MF_Special |
                        FtStateChange_PreserveColAnimHitStatus |
                        FtStateChange_PreserveSfx,
    ftLg_MF_SpecialAirN = ftLg_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftLg_MF_SpecialAirS = ftLg_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftLg_MF_SpecialAirHi = ftLg_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftLg_MF_SpecialAirLw = ftLg_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
} ftLg_MotionFlags;

typedef enum ftLuigi_MotionState {
    ftLg_MS_SpecialN = ftCo_MS_Count,
    ftLg_MS_SpecialAirN,
    ftLg_MS_SpecialSStart,
    ftLg_MS_SpecialSHold,
    ftLg_MS_SpecialSFly,
    ftLg_MS_SpecialSEnd,
    ftLg_MS_SpecialSLaunch,
    ftLg_MS_SpecialSMisfire,
    ftLg_MS_SpecialAirSStart,
    ftLg_MS_SpecialAirSHold,
    ftLg_MS_SpecialAirSFly,
    ftLg_MS_SpecialAirSEnd,
    ftLg_MS_SpecialAirSLaunch,
    ftLg_MS_SpecialAirSMisfire,
    ftLg_MS_SpecialHi,
    ftLg_MS_SpecialAirHi,
    ftLg_MS_SpecialLw,
    ftLg_MS_SpecialAirLw,
} ftLuigi_MotionState;

#endif
