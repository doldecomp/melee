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

#endif
