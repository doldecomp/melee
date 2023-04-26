#ifndef MELEE_FT_CHARA_FTPOPO_FORWARD_H
#define MELEE_FT_CHARA_FTPOPO_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPp_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftPp_MF_SpecialLw ATTRIBUTE_USED =
    ftPp_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPp_MF_SpecialN ATTRIBUTE_USED =
    ftPp_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftPp_MF_SpecialS ATTRIBUTE_USED =
    ftPp_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPp_MF_SpecialHi ATTRIBUTE_USED =
    ftPp_MF_SpecialS | Ft_MF_KeepFastFall;

static MotionFlags const ftPp_MF_MS_358 ATTRIBUTE_USED =
    ftPp_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftPp_MF_SpecialAirN ATTRIBUTE_USED =
    ftPp_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPp_MF_SpecialAirS ATTRIBUTE_USED =
    ftPp_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftPp_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPp_MF_SpecialHi | Ft_MF_SkipParasol;

typedef enum ftPopo_MotionState {
    ftPp_MS_SpecialN = ftCo_MS_Count,
    ftPp_MS_SpecialAirN,
    ftPp_MS_SpecialS,
    ftPp_MS_SpecialS_Together,
    ftPp_MS_SpecialAirS,
    ftPp_MS_SpecialAirS_Together,
    ftPp_MS_SpecialHi_Start,
    ftPp_MS_SpecialHi,
    ftPp_MS_Unk_349,
    ftPp_MS_SpecialHi_Fail,
    ftPp_MS_SpecialHi_FailEnd,
    ftPp_MS_SpecialAirHi_Start,
    ftPp_MS_SpecialAirHi,
    ftPp_MS_SpecialAirHi_Fail,
    ftPp_MS_SpecialAirHi_FailEnd,
    ftPp_MS_SpecialLw,
    ftPp_MS_SpecialAirLw,
} ftPopo_MotionState;

typedef enum ftPp_Submotion {
    ftPp_SM_SpecialN = ftCo_SM_Count,
    ftPp_SM_SpecialAirN,
    ftPp_SM_SpecialS1,
    ftPp_SM_SpecialS2,
    ftPp_SM_SpecialAirS1,
    ftPp_SM_SpecialAirS2,
    ftPp_SM_SpecialHiStart_0,
    ftPp_SM_SpecialHiThrow_0,
    ftPp_SM_SpecialHiThrow2,
    ftPp_SM_SpecialHiStart_1,
    ftPp_SM_SpecialHiThrow_1,
    ftPp_SM_SpecialAirHiStart_0,
    ftPp_SM_SpecialAirHiThrow_0,
    ftPp_SM_SpecialAirHiThrow2,
    ftPp_SM_SpecialAirHiStart_1,
    ftPp_SM_SpecialAirHiThrow_1,
    ftPp_SM_SpecialLw,
    ftPp_SM_SpecialAirLw,
    ftPp_SM_SpecialS_0,
    ftPp_SM_SpecialS_1,
    ftPp_SM_SpecialHi_0,
    ftPp_SM_SpecialHi_1,
    ftPp_SM_SpecialHi_2,
    ftPp_SM_SpecialHi_3,
    ftPp_SM_SpecialHi_4,
    ftPp_SM_SpecialHi_5,
} ftPp_Submotion;

#endif
