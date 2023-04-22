#ifndef MELEE_FT_CHARA_FTMEWTWO_FORWARD_H
#define MELEE_FT_CHARA_FTMEWTWO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftMt_MotionFlags {
    ftMt_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftMt_MF_SpecialHiStart = ftMt_MF_Special | FtStateChange_PreserveFastFall |
                             FtStateChange_PreserveGfx,
    ftMt_MF_SpecialNStart = ftMt_MF_Special | FtStateChange_PreserveFastFall |
                            FtStateChange_SkipUpdateThrowException,
    ftMt_MF_SpecialLw = ftMt_MF_Special |
                        FtStateChange_PreserveColAnimHitStatus |
                        FtStateChange_SkipUpdateThrowException,
    ftMt_MF_SpecialAirHiStart =
        ftMt_MF_SpecialHiStart | FtStateChange_SkipUpdateParasol,
    ftMt_MF_SpecialAirNStart =
        ftMt_MF_SpecialNStart | FtStateChange_SkipUpdateParasol,
    ftMt_MF_SpecialAirLw = ftMt_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftMt_MF_SpecialS = ftMt_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_SkipUpdateColAnim,
    ftMt_MF_SpecialAirS = ftMt_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftMt_MF_SpecialN = ftMt_MF_SpecialNStart | FtStateChange_Unk_19,
    ftMt_MF_SpecialAirN = ftMt_MF_SpecialN | FtStateChange_SkipUpdateParasol,
} ftMt_MotionFlags;

typedef enum ftMewtwo_MotionState {
    ftMt_MS_SpecialNStart = ftCo_MS_Count,
    ftMt_MS_SpecialNLoop,
    ftMt_MS_SpecialNFull,
    ftMt_MS_SpecialNCancel,
    ftMt_MS_SpecialNEnd,
    ftMt_MS_SpecialAirNStart,
    ftMt_MS_SpecialAirNLoop,
    ftMt_MS_SpecialAirNFull,
    ftMt_MS_SpecialAirNCancel,
    ftMt_MS_SpecialAirNEnd,
    ftMt_MS_SpecialS,
    ftMt_MS_SpecialAirS,
    ftMt_MS_SpecialHiStart,
    ftMt_MS_SpecialHi,
    ftMt_MS_SpecialHiLost,
    ftMt_MS_SpecialAirHiStart,
    ftMt_MS_SpecialAirHi,
    ftMt_MS_SpecialAirHiLost,
    ftMt_MS_SpecialLw,
    ftMt_MS_SpecialAirLw,
} ftMewtwo_MotionState;

#endif
