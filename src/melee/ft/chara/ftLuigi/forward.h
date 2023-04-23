#ifndef MELEE_FT_CHARA_FTLUIGI_FORWARD_H
#define MELEE_FT_CHARA_FTLUIGI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftLg_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static u32 const ftLg_MF_SpecialN ATTRIBUTE_USED =
    ftLg_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static u32 const ftLg_MF_SpecialS ATTRIBUTE_USED =
    ftLg_MF_Special | FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftLg_MF_SpecialHi ATTRIBUTE_USED =
    ftLg_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftLg_MF_SpecialLw ATTRIBUTE_USED =
    ftLg_MF_Special | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_PreserveSfx;

static u32 const ftLg_MF_SpecialAirN ATTRIBUTE_USED =
    ftLg_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftLg_MF_SpecialAirS ATTRIBUTE_USED =
    ftLg_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static u32 const ftLg_MF_SpecialAirHi ATTRIBUTE_USED =
    ftLg_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static u32 const ftLg_MF_SpecialAirLw ATTRIBUTE_USED =
    ftLg_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

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

#endif
