#ifndef MELEE_FT_CHARA_FTPEACH_FORWARD_H
#define MELEE_FT_CHARA_FTPEACH_FORWARD_H

#include "ftCommon/forward.h"

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
