#ifndef MELEE_FT_CHARA_FTKOOPA_FORWARD_H
#define MELEE_FT_CHARA_FTKOOPA_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftKp_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static u32 const ftKp_MF_SpecialN ATTRIBUTE_USED =
    ftKp_MF_Special | FtStateChange_PreserveFastFall;

static u32 const ftKp_MF_SpecialS ATTRIBUTE_USED =
    ftKp_MF_Special | FtStateChange_PreserveGfx;

static u32 const ftKp_MF_SpecialHi ATTRIBUTE_USED =
    ftKp_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftKp_MF_SpecialLwStart ATTRIBUTE_USED =
    ftKp_MF_Special | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_PreserveSfx;

static u32 const ftKp_MF_SpecialNStart ATTRIBUTE_USED =
    ftKp_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftKp_MF_SpecialAirS ATTRIBUTE_USED =
    ftKp_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static u32 const ftKp_MF_SpecialAirHi ATTRIBUTE_USED =
    ftKp_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static u32 const ftKp_MF_SpecialAirLw ATTRIBUTE_USED =
    ftKp_MF_SpecialLwStart | FtStateChange_SkipUpdateParasol;

static u32 const ftKp_MF_SpecialNLoop ATTRIBUTE_USED =
    ftKp_MF_SpecialN | FtStateChange_Unk_19;

static u32 const ftKp_MF_SpecialAirNLoop ATTRIBUTE_USED =
    ftKp_MF_SpecialNLoop | FtStateChange_SkipUpdateParasol;

typedef enum ftKoopa_MotionState {
    ftKp_MS_SpecialNStart = ftCo_MS_Count,
    ftKp_MS_SpecialNLoop,
    ftKp_MS_SpecialNEnd,
    ftKp_MS_SpecialAirNStart,
    ftKp_MS_SpecialAirNLoop,
    ftKp_MS_SpecialAirNEnd,
    ftKp_MS_SpecialS,
    ftKp_MS_SpecialSCatch,
    ftKp_MS_SpecialSCatchAttack,
    ftKp_MS_SpecialSWait,
    ftKp_MS_SpecialSThrowF,
    ftKp_MS_SpecialSThrowB,
    ftKp_MS_SpecialAirS,
    ftKp_MS_SpecialAirSCatch,
    ftKp_MS_SpecialAirSCatchAttack,
    ftKp_MS_SpecialAirSWait,
    ftKp_MS_SpecialAirSThrowF,
    ftKp_MS_SpecialAirSThrowB,
    ftKp_MS_SpecialHi,
    ftKp_MS_SpecialAirHi,
    ftKp_MS_SpecialLwStart,
    ftKp_MS_SpecialAirLw,
    ftKp_MS_SpecialLwLanding,
} ftKoopa_MotionState;

#endif
