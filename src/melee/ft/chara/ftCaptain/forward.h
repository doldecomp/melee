#ifndef MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H
#define MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef struct ftCaptain_DatAttrs ftCaptain_DatAttrs;
typedef union ftCaptain_MotionVars ftCaptain_MotionVars;

static MotionFlags const ftCa_MF_Special ATTRIBUTE_USED =
    ftCo_MF_Special | Ft_MF_KeepSfx;

static MotionFlags const ftCa_MF_SpecialN ATTRIBUTE_USED =
    ftCa_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftCa_MF_SpecialAirN ATTRIBUTE_USED =
    ftCa_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftCa_MF_SpecialS ATTRIBUTE_USED =
    ftCa_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftCa_MF_SpecialAirSStart ATTRIBUTE_USED =
    ftCa_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftCa_MF_SpecialAirS ATTRIBUTE_USED =
    ftCa_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftCa_MF_SpecialHi ATTRIBUTE_USED =
    ftCo_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftCa_MF_SpecialAirHi ATTRIBUTE_USED =
    ftCa_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftCa_MF_SpecialLw ATTRIBUTE_USED =
    ftCa_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftCa_MF_SpecialLwRebound ATTRIBUTE_USED =
    ftCa_MF_SpecialLw | Ft_MF_SkipParasol;

typedef enum ftCaptain_MotionState {
    ftCa_MS_SwordSwing4 = ftCo_MS_Count,
    ftCa_MS_BatSwing4,
    ftCa_MS_ParasolSwing4,
    ftCa_MS_HarisenSwing4,
    ftCa_MS_StarRodSwing4,
    ftCa_MS_LipstickSwing4,
    ftCa_MS_SpecialN,
    ftCa_MS_SpecialAirN,
    ftCa_MS_SpecialSStart,
    ftCa_MS_SpecialS,
    ftCa_MS_SpecialAirSStart,
    ftCa_MS_SpecialAirS,
    ftCa_MS_SpecialHi,
    ftCa_MS_SpecialAirHi,
    ftCa_MS_SpecialHiCatch,
    ftCa_MS_SpecialHiThrow,
    ftCa_MS_SpecialLw,
    ftCa_MS_SpecialLwEnd,
    ftCa_MS_SpecialAirLw,
    ftCa_MS_SpecialAirLwEnd,
    ftCa_MS_SpecialAirLwEndAir,
    ftCa_MS_SpecialLwEndAir,
    ftCa_MS_SpecialHiThrow1,
} ftCaptain_MotionState;

typedef enum ftCa_Submotion {
    ftCa_SM_SwordSwing4 = ftCo_SM_Count,
    ftCa_SM_BatSwing4,
    ftCa_SM_ParasolSwing4,
    ftCa_SM_HarisenSwing4,
    ftCa_SM_StarRodSwing4,
    ftCa_SM_LipstickSwing4,
    ftCa_SM_SpecialN,
    ftCa_SM_SpecialAirN,
    ftCa_SM_SpecialSStart,
    ftCa_SM_SpecialS,
    ftCa_SM_SpecialAirSStart,
    ftCa_SM_SpecialAirS,
    ftCa_SM_SpecialHi,
    ftCa_SM_SpecialAirHi,
    ftCa_SM_SpecialHiCatch,
    ftCa_SM_SpecialHiThrow0,
    ftCa_SM_SpecialLw,
    ftCa_SM_SpecialLwEnd,
    ftCa_SM_SpecialAirLw,
    ftCa_SM_SpecialAirLwEnd,
    ftCa_SM_SpecialLwEndAir,
    ftCa_SM_SpecialAirLwEndAir,
    ftCa_SM_SpecialHiThrow1,
} ftCa_Submotion;

#endif
