#ifndef MELEE_FT_CHARA_FTSEAK_FORWARD_H
#define MELEE_FT_CHARA_FTSEAK_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftSk_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftSk_MF_SpecialS ATTRIBUTE_USED =
    ftSk_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftSk_MF_SpecialLw ATTRIBUTE_USED =
    ftSk_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftSk_MF_SpecialN ATTRIBUTE_USED =
    ftSk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftSk_MF_SpecialHi ATTRIBUTE_USED =
    ftSk_MF_SpecialS | Ft_MF_KeepFastFall | Ft_MF_KeepSfx;

static MotionFlags const ftSk_MF_SpecialAirS ATTRIBUTE_USED =
    ftSk_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftSk_MF_SpecialAirLw ATTRIBUTE_USED =
    ftSk_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftSk_MF_SpecialAirN ATTRIBUTE_USED =
    ftSk_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftSk_MF_SpecialAirHi ATTRIBUTE_USED =
    ftSk_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftSk_MF_SpecialSLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialS | Ft_MF_Unk19;

static MotionFlags const ftSk_MF_SpecialNLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialN | Ft_MF_Unk19;

static MotionFlags const ftSk_MF_SpecialAirSLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialSLoop | Ft_MF_SkipParasol;

static MotionFlags const ftSk_MF_SpecialAirNLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialNLoop | Ft_MF_SkipParasol;

typedef enum ftSeak_MotionState {
    ftSk_MS_SpecialN_ChargeStart = ftCo_MS_Count,
    ftSk_MS_SpecialN_ChargeLoop,
    ftSk_MS_SpecialN_ChargeEnd,
    ftSk_MS_SpecialN_Shoot,
    ftSk_MS_SpecialAirN_ChargeStart,
    ftSk_MS_SpecialAirN_ChargeLoop,
    ftSk_MS_SpecialAirN_ChargeEnd,
    ftSk_MS_SpecialAirN_Shoot,
    ftSk_MS_SpecialS_Start,
    ftSk_MS_SpecialS_Loop,
    ftSk_MS_SpecialS_End,
    ftSk_MS_SpecialAirS_Start,
    ftSk_MS_SpecialAirS_Loop,
    ftSk_MS_SpecialAirS_End,
    ftSk_MS_SpecialHi_Start,
    ftSk_MS_SpecialHi,
    ftSk_MS_SpecialHi_End,
    ftSk_MS_SpecialAirHi_Start,
    ftSk_MS_SpecialAirHi,
    ftSk_MS_SpecialAirHi_End,
    ftSk_MS_SpecialLw,
    ftSk_MS_SpecialLw_End,
    ftSk_MS_SpecialAirLw,
    ftSk_MS_SpecialAirLw_End,
} ftSeak_MotionState;

typedef enum ftSk_Submotion {
    ftSk_SM_SpecialNStart = ftCo_SM_Count,
    ftSk_SM_SpecialNLoop,
    ftSk_SM_SpecialNCancel,
    ftSk_SM_SpecialNEnd,
    ftSk_SM_SpecialAirNStart,
    ftSk_SM_SpecialAirNLoop,
    ftSk_SM_SpecialAirNCancel,
    ftSk_SM_SpecialAirNEnd,
    ftSk_SM_SpecialSStart,
    ftSk_SM_SpecialSEnd,
    ftSk_SM_SpecialS,
    ftSk_SM_SpecialAirSStart,
    ftSk_SM_SpecialAirSEnd,
    ftSk_SM_SpecialAirS,
    ftSk_SM_SpecialHiStart,
    ftSk_SM_SpecialHi,
    ftSk_SM_SpecialAirHiStart,
    ftSk_SM_SpecialAirHi,
    ftSk_SM_SpecialLw,
    ftSk_SM_SpecialLw2,
    ftSk_SM_SpecialAirLw,
    ftSk_SM_SpecialAirLw2,
} ftSk_Submotion;

#endif
