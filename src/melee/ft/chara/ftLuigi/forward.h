#ifndef MELEE_FT_CHARA_FTLUIGI_FORWARD_H
#define MELEE_FT_CHARA_FTLUIGI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftLg_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftLg_MF_SpecialN ATTRIBUTE_USED =
    ftLg_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftLg_MF_SpecialS ATTRIBUTE_USED =
    ftLg_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftLg_MF_SpecialHi ATTRIBUTE_USED =
    ftLg_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftLg_MF_SpecialLw ATTRIBUTE_USED =
    ftLg_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_KeepSfx;

static MotionFlags const ftLg_MF_SpecialAirN ATTRIBUTE_USED =
    ftLg_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftLg_MF_SpecialAirS ATTRIBUTE_USED =
    ftLg_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftLg_MF_SpecialAirHi ATTRIBUTE_USED =
    ftLg_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftLg_MF_SpecialAirLw ATTRIBUTE_USED =
    ftLg_MF_SpecialLw | Ft_MF_SkipParasol;

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

typedef enum ftLg_AnimId {
    ftLg_AnimId_SpecialN = ftCo_AnimId_Count,
    ftLg_AnimId_SpecialAirN,
    ftLg_AnimId_SpecialSStart,
    ftLg_AnimId_SpecialSHold,
    ftLg_AnimId_SpecialSLaunch,
    ftLg_AnimId_SpecialSMisfire,
    ftLg_AnimId_Unk301,
    ftLg_AnimId_SpecialSEnd,
    ftLg_AnimId_SpecialAirSStart,
    ftLg_AnimId_SpecialAirSHold,
    ftLg_AnimId_SpecialAirSLaunch,
    ftLg_AnimId_SpecialAirSMisfire,
    ftLg_AnimId_SpecialAirSEnd,
    ftLg_AnimId_SpecialHi,
    ftLg_AnimId_SpecialAirHi,
    ftLg_AnimId_SpecialLw,
    ftLg_AnimId_SpecialAirLw,
} ftLg_AnimId;

#endif
