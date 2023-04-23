#ifndef MELEE_FT_CHARA_FTPEACH_FORWARD_H
#define MELEE_FT_CHARA_FTPEACH_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftPe_MotionFlags {
    ftPe_MF_Base = FtStateChange_SkipUpdateItemVis | FtStateChange_FreezeState,
    ftPe_MF_FloatAttack = ftPe_MF_Base | FtStateChange_SkipUpdateParasol,
    ftPe_MF_FloatAttackAirN = ftPe_MF_FloatAttack |
                              FtStateChange_PreserveColAnimHitStatus |
                              FtStateChange_SkipUpdateHit,
    ftPe_MF_Move_14 = ftPe_MF_FloatAttackAirN | FtStateChange_PreserveFastFall,
    ftPe_MF_FloatAttackAirB =
        ftPe_MF_FloatAttackAirN | FtStateChange_PreserveGfx,
    ftPe_MF_FloatAttackAirHi = ftPe_MF_FloatAttackAirN |
                               FtStateChange_PreserveFastFall |
                               FtStateChange_PreserveGfx,
    ftPe_MF_Move_17 = ftPe_MF_FloatAttack | FtStateChange_SkipUpdateModel,
    ftPe_MF_AttackS4 = ftPe_MF_Base | FtStateChange_PreserveFastFall |
                       FtStateChange_SkipUpdateHit |
                       FtStateChange_PreserveSfx |
                       FtStateChange_SkipUpdateRumble,
    ftPe_MF_Special = ftPe_MF_Base | FtStateChange_SkipUpdateModel |
                      FtStateChange_Unk_UpdatePhys,
    ftPe_MF_SpecialN = ftPe_MF_Special | FtStateChange_PreserveFastFall,
    ftPe_MF_SpecialHi = ftPe_MF_SpecialN | FtStateChange_PreserveGfx,
    ftPe_MF_SpecialLw =
        ftPe_MF_Special | FtStateChange_PreserveColAnimHitStatus,
    ftPe_MF_SpecialS = ftPe_MF_Special | FtStateChange_PreserveGfx |
                       FtStateChange_PreserveSfx,
    ftPe_MF_SpecialAirN = ftPe_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftPe_MF_SpecialAirHi = ftPe_MF_SpecialHi | FtStateChange_SkipUpdateParasol,
    ftPe_MF_SpecialAirS = ftPe_MF_SpecialS | FtStateChange_SkipUpdateParasol,
    ftPe_MF_ParasolOpen = FtStateChange_SkipUpdateHit |
                          FtStateChange_SkipUpdateModel | FtStateChange_Unk_6 |
                          FtStateChange_SkipUpdateItemVis |
                          FtStateChange_SkipUpdateModelPartVis,
    ftPe_MF_ParasolFallSpecial = ftPe_MF_ParasolOpen | FtStateChange_Unk_19,
} ftPe_MotionFlags;

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
