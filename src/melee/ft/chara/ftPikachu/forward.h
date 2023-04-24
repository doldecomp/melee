#ifndef MELEE_FT_CHARA_FTPIKACHU_FORWARD_H
#define MELEE_FT_CHARA_FTPIKACHU_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPk_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static MotionFlags const ftPk_MF_SpecialLw ATTRIBUTE_USED =
    ftPk_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftPk_MF_SpecialN ATTRIBUTE_USED =
    ftPk_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static MotionFlags const ftPk_MF_SpecialHi ATTRIBUTE_USED =
    ftPk_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateThrowException;

static MotionFlags const ftPk_MF_SpecialS ATTRIBUTE_USED =
    ftPk_MF_Special | FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static MotionFlags const ftPk_MF_SpecialAirLw ATTRIBUTE_USED =
    ftPk_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftPk_MF_SpecialAirN ATTRIBUTE_USED =
    ftPk_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftPk_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPk_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftPk_MF_SpecialAirS ATTRIBUTE_USED =
    ftPk_MF_SpecialS | FtStateChange_SkipUpdateParasol;

typedef enum ftPikachu_MotionState {
    ftPk_MS_SpecialN = ftCo_MS_Count,
    ftPk_MS_SpecialAirN,
    ftPk_MS_SpecialS_Start,
    ftPk_MS_SpecialS_Charge,
    ftPk_MS_Unk_345,
    ftPk_MS_SpecialS_Landing,
    ftPk_MS_SpecialS_Launch,
    ftPk_MS_SpecialAirS_Start,
    ftPk_MS_SpecialAirS_Charge,
    ftPk_MS_SpecialAirS,
    ftPk_MS_SpecialAirS_End,
    ftPk_MS_SpecialAirS_Launch,
    ftPk_MS_SpecialHi_Start,
    ftPk_MS_SpecialHi,
    ftPk_MS_SpecialHi_End,
    ftPk_MS_SpecialAirHi_Start,
    ftPk_MS_SpecialAir,
    ftPk_MS_SpecialAir_End,
    ftPk_MS_SpecialLw_Start,
    ftPk_MS_SpecialLw,
    ftPk_MS_SpecialLw_Hit,
    ftPk_MS_SpecialLw_End,
    ftPk_MS_SpecialAirLw_Start,
    ftPk_MS_SpecialAirLw,
    ftPk_MS_SpecialAirLw_Hit,
    ftPk_MS_SpecialAirLw_End,
} ftPikachu_MotionState;

#endif
