#ifndef MELEE_FT_CHARA_FTPOPO_FORWARD_H
#define MELEE_FT_CHARA_FTPOPO_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPp_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftPp_MF_SpecialLw =
    ftPp_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPp_MF_SpecialN =
    ftPp_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftPp_MF_SpecialS =
    ftPp_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPp_MF_SpecialHi =
    ftPp_MF_SpecialS | Ft_MF_KeepFastFall;

static MotionFlags const ftPp_MF_MS_358 =
    ftPp_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftPp_MF_SpecialAirN =
    ftPp_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPp_MF_SpecialAirS =
    ftPp_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftPp_MF_SpecialAirHi =
    ftPp_MF_SpecialHi | Ft_MF_SkipParasol;

typedef enum ftPopo_MotionState {
    ftPp_MS_SpecialN = ftCo_MS_Count,
    ftPp_MS_SpecialAirN,
    ftPp_MS_SpecialS1,
    ftPp_MS_SpecialS2,
    ftPp_MS_SpecialAirS1,
    ftPp_MS_SpecialAirS2,
    ftPp_MS_SpecialHiStart_0,
    ftPp_MS_SpecialHiThrow_0,
    ftPp_MS_SpecialHiThrow2,
    ftPp_MS_SpecialHiStart_1,
    ftPp_MS_SpecialHiThrow_1,
    ftPp_MS_SpecialAirHiStart_0,
    ftPp_MS_SpecialAirHiThrow_0,
    ftPp_MS_SpecialAirHiThrow2,
    ftPp_MS_SpecialAirHiStart_1,
    ftPp_MS_SpecialAirHiThrow_1,
    ftPp_MS_SpecialLw,
    ftPp_MS_SpecialAirLw,
    ftPp_MS_SpecialS_0,
    ftPp_MS_SpecialS_1,
    ftPp_MS_SpecialHi_0,
    ftPp_MS_SpecialHi_1,
    ftPp_MS_SpecialHi_2,
    ftPp_MS_SpecialHi_3,
    ftPp_MS_SpecialHi_4,
    ftPp_MS_SpecialHi_5,
    ftPp_MS_Count,
    ftPp_MS_SelfCount = ftPp_MS_Count - ftCo_MS_Count,
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
    ftPp_SM_Count,
    ftPp_SM_SelfCount = ftPp_SM_Count - ftCo_SM_Count,
} ftPp_Submotion;

#endif
