#ifndef MELEE_FT_CHARA_FTLINK_FORWARD_H
#define MELEE_FT_CHARA_FTLINK_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftLk_MF_Base0 ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateThrowException;

static u32 const ftLk_MF_Base1 ATTRIBUTE_USED =
    FtStateChange_SkipUpdateItemVis | FtStateChange_FreezeState;

static u32 const ftLk_MF_Base2 ATTRIBUTE_USED =
    ftLk_MF_Base1 | FtStateChange_PreserveFastFall;

static u32 const ftLk_MF_Base3 ATTRIBUTE_USED =
    ftLk_MF_Base0 | FtStateChange_Unk_UpdatePhys;

static u32 const ftLk_MF_AttackS42 ATTRIBUTE_USED =
    ftLk_MF_Base2 | FtStateChange_SkipUpdateHit;

static u32 const ftLk_MF_SpecialN ATTRIBUTE_USED =
    ftLk_MF_Base2 | ftLk_MF_Base3;

static u32 const ftLk_MF_SpecialNFullyCharged ATTRIBUTE_USED =
    ftLk_MF_SpecialN | FtStateChange_Unk_19;

static u32 const ftLk_MF_SpecialAirNCharge ATTRIBUTE_USED =
    ftLk_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftLk_MF_SpecialAirNFullyCharged ATTRIBUTE_USED =
    ftLk_MF_SpecialNFullyCharged | FtStateChange_SkipUpdateParasol;

static u32 const ftLk_MF_SpecialAirNFire ATTRIBUTE_USED =
    ftLk_MF_SpecialAirNCharge | FtStateChange_Unk_UpdatePhys;

static u32 const ftLk_MF_SpecialSThrow ATTRIBUTE_USED =
    ftLk_MF_Base3 | ftLk_MF_Base1 | FtStateChange_PreserveGfx;

static u32 const ftLk_MF_SpecialSCatch ATTRIBUTE_USED =
    ftLk_MF_SpecialSThrow | FtStateChange_Unk_UpdatePhys;

static u32 const ftLk_MF_SpecialAirSThrow ATTRIBUTE_USED =
    ftLk_MF_SpecialSThrow | ftLk_MF_Base3 | FtStateChange_SkipUpdateParasol;

static u32 const ftLk_MF_SpecialAirSThrowEmpty ATTRIBUTE_USED =
    ftLk_MF_SpecialSCatch | ftLk_MF_Base1 | FtStateChange_SkipUpdateParasol;

static u32 const ftLk_MF_SpecialHi ATTRIBUTE_USED =
    FtStateChange_PreserveFastFall | FtStateChange_PreserveGfx |
    FtStateChange_SkipUpdateModel | FtStateChange_PreserveSfx |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_UpdatePhys |
    FtStateChange_FreezeState;

static u32 const ftLk_MF_SpecialLw ATTRIBUTE_USED =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateModel |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_UpdatePhys |
    FtStateChange_FreezeState;

static u32 const ftLk_MF_SpecialAirLw ATTRIBUTE_USED =
    ftLk_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static u32 const ftLk_MF_ZairCatch ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateMetalB;

typedef enum ftLink_MotionState {
    ftLk_MS_AttackS42 = ftCo_MS_Count,
    ftLk_MS_AppealR,
    ftLk_MS_AppealL,
    ftLk_MS_SpecialNCharge,
    ftLk_MS_SpecialNFullyCharged,
    ftLk_MS_SpecialNFire,
    ftLk_MS_SpecialAirNCharge,
    ftLk_MS_SpecialAirNFullyCharged,
    ftLk_MS_SpecialAirNFire,
    ftLk_MS_SpecialSThrow,
    ftLk_MS_SpecialSCatch,
    ftLk_MS_SpecialSThrowEmpty,
    ftLk_MS_SpecialAirSThrow,
    ftLk_MS_SpecialAirSCatch,
    ftLk_MS_SpecialAirSThrowEmpty,
    ftLk_MS_SpecialHi,
    ftLk_MS_SpecialAirHi,
    ftLk_MS_SpecialLw,
    ftLk_MS_SpecialAirLw,
    ftLk_MS_Zair,
    ftLk_MS_ZairCatch,
} ftLink_MotionState;

#endif
