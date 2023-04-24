#ifndef MELEE_FT_CHARA_FTZELDA_FORWARD_H
#define MELEE_FT_CHARA_FTZELDA_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftZd_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static MotionFlags const ftZd_MF_SpecialN ATTRIBUTE_USED =
    ftZd_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateColAnim;

static MotionFlags const ftZd_MF_SpecialHi ATTRIBUTE_USED =
    ftZd_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx;

static MotionFlags const ftZd_MF_SpecialLw ATTRIBUTE_USED =
    ftZd_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftZd_MF_SpecialS ATTRIBUTE_USED =
    ftZd_MF_Special | FtStateChange_PreserveGfx |
    FtStateChange_SkipUpdateThrowException;

static MotionFlags const ftZd_MF_SpecialAirN ATTRIBUTE_USED =
    ftZd_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftZd_MF_SpecialAirHi ATTRIBUTE_USED =
    ftZd_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftZd_MF_SpecialAirLw ATTRIBUTE_USED =
    ftZd_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftZd_MF_SpecialAirS ATTRIBUTE_USED =
    ftZd_MF_SpecialS | FtStateChange_SkipUpdateParasol;

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
