#ifndef MELEE_FT_CHARA_FTPEACH_FORWARD_H
#define MELEE_FT_CHARA_FTPEACH_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftPe_MF_Base ATTRIBUTE_USED =
    FtStateChange_SkipUpdateItemVis | FtStateChange_FreezeState;

static u32 const ftPe_MF_FloatAttack ATTRIBUTE_USED =
    ftPe_MF_Base | FtStateChange_SkipUpdateParasol;

static u32 const ftPe_MF_FloatAttackAirN ATTRIBUTE_USED =
    ftPe_MF_FloatAttack | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateHit;

static u32 const ftPe_MF_Move_14 ATTRIBUTE_USED =
    ftPe_MF_FloatAttackAirN | FtStateChange_PreserveFastFall;

static u32 const ftPe_MF_FloatAttackAirB ATTRIBUTE_USED =
    ftPe_MF_FloatAttackAirN | FtStateChange_PreserveGfx;

static u32 const ftPe_MF_FloatAttackAirHi ATTRIBUTE_USED =
    ftPe_MF_FloatAttackAirN | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx;

static u32 const ftPe_MF_Move_17 ATTRIBUTE_USED =
    ftPe_MF_FloatAttack | FtStateChange_SkipUpdateModel;

static u32 const ftPe_MF_AttackS4 ATTRIBUTE_USED =
    ftPe_MF_Base | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateHit | FtStateChange_PreserveSfx |
    FtStateChange_SkipUpdateRumble;

static u32 const ftPe_MF_Special ATTRIBUTE_USED =
    ftPe_MF_Base | FtStateChange_SkipUpdateModel |
    FtStateChange_Unk_UpdatePhys;

static u32 const ftPe_MF_SpecialN ATTRIBUTE_USED =
    ftPe_MF_Special | FtStateChange_PreserveFastFall;

static u32 const ftPe_MF_SpecialHi ATTRIBUTE_USED =
    ftPe_MF_SpecialN | FtStateChange_PreserveGfx;

static u32 const ftPe_MF_SpecialLw ATTRIBUTE_USED =
    ftPe_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static u32 const ftPe_MF_SpecialS ATTRIBUTE_USED =
    ftPe_MF_Special | FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftPe_MF_SpecialAirN ATTRIBUTE_USED =
    ftPe_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftPe_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPe_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static u32 const ftPe_MF_SpecialAirS ATTRIBUTE_USED =
    ftPe_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static u32 const ftPe_MF_ParasolOpen ATTRIBUTE_USED =
    FtStateChange_SkipUpdateHit | FtStateChange_SkipUpdateModel |
    FtStateChange_Unk_6 | FtStateChange_SkipUpdateItemVis |
    FtStateChange_SkipUpdateModelPartVis;

static u32 const ftPe_MF_ParasolFallSpecial ATTRIBUTE_USED =
    ftPe_MF_ParasolOpen | FtStateChange_Unk_19;

typedef enum ftPeach_MotionState {
    ftPe_MS_Float = ftCo_MS_Count,
    ftPe_MS_FloatEndF,
    ftPe_MS_FloatEndB,
    ftPe_MS_FloatAttackAirN,
    ftPe_MS_FloatAttackAirF,
    ftPe_MS_FloatAttackAirB,
    ftPe_MS_FloatAttackAirU,
    ftPe_MS_FloatAttackAirD,
    ftPe_MS_AttackS4_Club,
    ftPe_MS_AttackS4_Pan,
    ftPe_MS_AttackS4_Racket,
    ftPe_MS_SpecialLw,
    ftPe_MS_SpecialAirLw,
    ftPe_MS_SpecialSStart,
    ftPe_MS_SpecialSEnd,
    ftPe_MS_Unk_356,
    ftPe_MS_SpecialAirSStart,
    ftPe_MS_SpecialAirSEnd,
    ftPe_MS_SpecialAirSHit,
    ftPe_MS_SpecialAirS,
    ftPe_MS_SpecialHiStart,
    ftPe_MS_Unk_362,
    ftPe_MS_SpecialAirHiStart,
    ftPe_MS_Unk_364,
    ftPe_MS_SpecialN,
    ftPe_MS_SpecialNAttack,
    ftPe_MS_SpecialAirN,
    ftPe_MS_SpecialAirNAttack,
    ftPe_MS_ParasolOpening,
    ftPe_MS_ParasolOpen,
} ftPeach_MotionState;

#endif
