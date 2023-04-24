#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftMr_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static MotionFlags const ftMr_MF_SpecialN ATTRIBUTE_USED =
    ftMr_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static MotionFlags const ftMr_MF_SpecialHi ATTRIBUTE_USED =
    ftMr_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static MotionFlags const ftMr_MF_SpecialLw ATTRIBUTE_USED =
    ftMr_MF_Special | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_PreserveSfx;

static MotionFlags const ftMr_MF_SpecialAirN ATTRIBUTE_USED =
    ftMr_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftMr_MF_SpecialAirHi ATTRIBUTE_USED =
    ftMr_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftMr_MF_SpecialAirLw ATTRIBUTE_USED =
    ftMr_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftMr_MF_SpecialS ATTRIBUTE_USED =
    ftMr_MF_Special | FtStateChange_PreserveGfx |
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateColAnim;

typedef enum ftMario_MotionState {
    ftMr_MS_AppealR = ftCo_MS_Count,
    ftMr_MS_AppealL,
    ftMr_MS_SpecialN,
    ftMr_MS_SpecialAirN,
    ftMr_MS_SpecialS,
    ftMr_MS_SpecialAirS,
    ftMr_MS_SpecialHi,
    ftMr_MS_SpecialAirHi,
    ftMr_MS_SpecialLw,
    ftMr_MS_SpecialAirLw,
    ftMr_MS_Count,
} ftMario_MotionState;

#endif
