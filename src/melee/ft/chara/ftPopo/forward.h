#ifndef MELEE_FT_CHARA_FTPOPO_FORWARD_H
#define MELEE_FT_CHARA_FTPOPO_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftPp_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static u32 const ftPp_MF_SpecialLw ATTRIBUTE_USED =
    ftPp_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static u32 const ftPp_MF_SpecialN ATTRIBUTE_USED =
    ftPp_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static u32 const ftPp_MF_SpecialS ATTRIBUTE_USED =
    ftPp_MF_Special | FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftPp_MF_SpecialHi ATTRIBUTE_USED =
    ftPp_MF_SpecialS | FtStateChange_PreserveFastFall;

static u32 const ftPp_MF_MS_358 ATTRIBUTE_USED =
    ftPp_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static u32 const ftPp_MF_SpecialAirN ATTRIBUTE_USED =
    ftPp_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftPp_MF_SpecialAirS ATTRIBUTE_USED =
    ftPp_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static u32 const ftPp_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPp_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

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

#endif
