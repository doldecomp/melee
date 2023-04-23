#ifndef MELEE_FT_CHARA_FTZELDA_FORWARD_H
#define MELEE_FT_CHARA_FTZELDA_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftZd_MotionFlags {
    ftZd_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftZd_MF_SpecialN = ftZd_MF_Special | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateColAnim,
    ftZd_MF_SpecialHi = ftZd_MF_Special | FtStateChange_PreserveFastFall |
                        FtStateChange_PreserveGfx,
    ftZd_MF_SpecialLw =
        ftZd_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftZd_MF_SpecialS = ftZd_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_SkipUpdateThrowException,
    ftZd_MF_SpecialAirN = ftZd_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftZd_MF_SpecialAirHi = ftZd_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftZd_MF_SpecialAirLw = ftZd_MF_SpecialLw | FtStateChange_SkipUpdateParasol,
    ftZd_MF_SpecialAirS = ftZd_MF_SpecialS | FtStateChange_SkipUpdateParasol,
} ftZd_MotionFlags;

enum ftZelda_AS {
    ftZd_MS_SpecialN = ftCo_MS_Count,
    ftZd_MS_SpecialAirN,
    ftZd_MS_SpecialS_Start,
    ftZd_MS_SpecialS_Hold,
    ftZd_MS_SpecialS_End,

    ftZd_MS_SpecialAirS_Start,
    ftZd_MS_SpecialAirS_Hold,
    ftZd_MS_SpecialAirS_End,

    ftZd_MS_SpecialHi_Start,
    ftZd_MS_SpecialHi,
    ftZd_MS_SpecialHi_End,

    ftZd_MS_SpecialAirHi_Start,
    ftZd_MS_SpecialAirHi,
    ftZd_MS_SpecialAirHi_End,

    ftZd_MS_SpecialLw,
    ftZd_MS_SpecialLw_End,

    ftZd_MS_SpecialAirLw,
    ftZd_MS_SpecialAirLw_End,
};

#endif
