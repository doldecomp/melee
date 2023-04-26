#ifndef MELEE_FT_CHARA_FTMARS_FORWARD_H
#define MELEE_FT_CHARA_FTMARS_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftMs_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_KeepSfx | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftMs_MF_SpecialN ATTRIBUTE_USED =
    ftMs_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftMs_MF_SpecialS ATTRIBUTE_USED =
    ftMs_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftMs_MF_SpecialHi ATTRIBUTE_USED =
    ftMs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftMs_MF_SpecialLw ATTRIBUTE_USED =
    ftMs_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftMs_MF_SpecialAirN ATTRIBUTE_USED =
    ftMs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipParasol;

static MotionFlags const ftMs_MF_SpecialS1 ATTRIBUTE_USED =
    ftMs_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipParasol;

static MotionFlags const ftMs_MF_SpecialAirHi ATTRIBUTE_USED =
    ftMs_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftMs_MF_SpecialAirLw ATTRIBUTE_USED =
    ftMs_MF_SpecialLw | Ft_MF_SkipParasol;

typedef enum ftMars_MotionState {
    ftMs_MS_SpecialNChargeStart = ftCo_MS_Count,
    ftMs_MS_SpecialNChargeLoop,
    ftMs_MS_SpecialNEarlyRelease,
    ftMs_MS_SpecialNFullRelease,

    ftMs_MS_SpecialAirNChargeStart,
    ftMs_MS_SpecialAirNChargeLoop,
    ftMs_MS_SpecialAirNEarlyRelease,
    ftMs_MS_SpecialAirNFullRelease,

    ftMs_MS_SpecialS1,
    ftMs_MS_SpecialS2U,
    ftMs_MS_SpecialS2S,
    ftMs_MS_SpecialS3U,
    ftMs_MS_SpecialS3S,
    ftMs_MS_SpecialS3D,
    ftMs_MS_SpecialS4U,
    ftMs_MS_SpecialS4S,
    ftMs_MS_SpecialS4D,

    ftMs_MS_SpecialAirS1,
    ftMs_MS_SpecialAirS2U,
    ftMs_MS_SpecialAirS2S,
    ftMs_MS_SpecialAirS3U,
    ftMs_MS_SpecialAirS3S,
    ftMs_MS_SpecialAirS3D,
    ftMs_MS_SpecialAirS4U,
    ftMs_MS_SpecialAirS4S,
    ftMs_MS_SpecialAirS4D,

    ftMs_MS_SpecialHi,
    ftMs_MS_SpecialAirHi,

    ftMs_MS_SpecialLw,
    ftMs_MS_SpecialLwHit,

    ftMs_MS_SpecialAirLw,
    ftMs_MS_SpecialAirLwHit,
} ftMars_MotionState;

typedef enum ftMs_Submotion {
    ftMs_SM_SpecialNStart = ftCo_SM_Count,
    ftMs_SM_SpecialNLoop,
    ftMs_SM_SpecialNEnd0,
    ftMs_SM_SpecialNEnd1,
    ftMs_SM_SpecialAirNStart,
    ftMs_SM_SpecialAirNLoop,
    ftMs_SM_SpecialAirNEnd0,
    ftMs_SM_SpecialAirNEnd1,
    ftMs_SM_SpecialS1,
    ftMs_SM_SpecialS2Hi,
    ftMs_SM_SpecialS2Lw,
    ftMs_SM_SpecialS3Hi,
    ftMs_SM_SpecialS3S,
    ftMs_SM_SpecialS3Lw,
    ftMs_SM_SpecialS4Hi,
    ftMs_SM_SpecialS4S,
    ftMs_SM_SpecialS4Lw,
    ftMs_SM_SpecialAirS1,
    ftMs_SM_SpecialAirS2Hi,
    ftMs_SM_SpecialAirS2Lw,
    ftMs_SM_SpecialAirS3Hi,
    ftMs_SM_SpecialAirS3S,
    ftMs_SM_SpecialAirS3Lw,
    ftMs_SM_SpecialAirS4Hi,
    ftMs_SM_SpecialAirS4S,
    ftMs_SM_SpecialAirS4Lw,
    ftMs_SM_SpecialHi,
    ftMs_SM_SpecialAirHi,
    ftMs_SM_SpecialLw,
    ftMs_SM_SpecialLwHit,
    ftMs_SM_SpecialAirLw,
    ftMs_SM_SpecialAirLwHit,
} ftMs_Submotion;

#endif
