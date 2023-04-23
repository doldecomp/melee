#ifndef MELEE_FT_CHARA_FTSAMUS_FORWARD_H
#define MELEE_FT_CHARA_FTSAMUS_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftSs_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static u32 const ftSs_MF_SpecialN ATTRIBUTE_USED =
    ftSs_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateThrowException;

static u32 const ftSs_MF_SpecialS ATTRIBUTE_USED =
    ftSs_MF_Special | FtStateChange_PreserveGfx |
    FtStateChange_SkipUpdateThrowException;

static u32 const ftSs_MF_SpecialLw ATTRIBUTE_USED =
    ftSs_MF_Special | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateThrowException;

static u32 const ftSs_MF_SpecialHi ATTRIBUTE_USED =
    ftSs_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftSs_MF_SpecialAirN ATTRIBUTE_USED =
    ftSs_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftSs_MF_SpecialAirS ATTRIBUTE_USED =
    ftSs_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static u32 const ftSs_MF_SpecialAirLw ATTRIBUTE_USED =
    ftSs_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static u32 const ftSs_MF_SpecialAirHi ATTRIBUTE_USED =
    ftSs_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static u32 const ftSs_MF_SpecialSSmash ATTRIBUTE_USED =
    ftSs_MF_SpecialS | FtStateChange_SkipUpdateRumble;

static u32 const ftSs_MF_SpecialAirSSmash ATTRIBUTE_USED =
    ftSs_MF_SpecialSSmash | FtStateChange_SkipUpdateParasol;

static u32 const ftSs_MF_ZairCatch ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateMetalB;

typedef enum ftSamus_MotionState {
    ftSs_MS_SpecialLw = ftCo_MS_Count,
    ftSs_MS_SpecialAirLw,
    ftSs_MS_SpecialN_Start,
    ftSs_MS_SpecialN_Loop,
    ftSs_MS_SpecialN_End,
    ftSs_MS_SpecialN_Shoot,
    ftSs_MS_SpecialAirN_Start,
    ftSs_MS_SpecialAirN_Shoot,
    ftSs_MS_SpecialS,

    /// @todo name
    ftSs_MS_SpecialS_Smash,

    ftSs_MS_SpecialAirS,
    ftSs_MS_SpecialAir_Smash,
    ftSs_MS_SpecialHi,
    ftSs_MS_SpecialAirHi,

    /// @todo name
    ftSs_MS_SpecialLw_BombEnd,
    ftSs_MS_SpecialAirLw_Bomb,

    /// @todo name
    ftSs_MS_Zair,
    ftSs_MS_ZairCatch,
} ftSamus_MotionState;

#endif
