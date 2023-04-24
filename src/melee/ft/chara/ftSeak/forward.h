#ifndef MELEE_FT_CHARA_FTSEAK_FORWARD_H
#define MELEE_FT_CHARA_FTSEAK_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftSk_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static MotionFlags const ftSk_MF_SpecialS ATTRIBUTE_USED =
    ftSk_MF_Special | FtStateChange_PreserveGfx;

static MotionFlags const ftSk_MF_SpecialLw ATTRIBUTE_USED =
    ftSk_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftSk_MF_SpecialN ATTRIBUTE_USED =
    ftSk_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static MotionFlags const ftSk_MF_SpecialHi ATTRIBUTE_USED =
    ftSk_MF_SpecialS | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveSfx;

static MotionFlags const ftSk_MF_SpecialAirS ATTRIBUTE_USED =
    ftSk_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftSk_MF_SpecialAirLw ATTRIBUTE_USED =
    ftSk_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftSk_MF_SpecialAirN ATTRIBUTE_USED =
    ftSk_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftSk_MF_SpecialAirHi ATTRIBUTE_USED =
    ftSk_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftSk_MF_SpecialSLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialS | FtStateChange_Unk_19;

static MotionFlags const ftSk_MF_SpecialNLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialN | FtStateChange_Unk_19;

static MotionFlags const ftSk_MF_SpecialAirSLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialSLoop | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftSk_MF_SpecialAirNLoop ATTRIBUTE_USED =
    ftSk_MF_SpecialNLoop | FtStateChange_SkipUpdateParasol;

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

#endif
