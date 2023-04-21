#ifndef MELEE_FT_CHARA_FTMARS_FORWARD_H
#define MELEE_FT_CHARA_FTMARS_FORWARD_H

#include "ftCommon/forward.h"

typedef enum ftMars_MotionState {
    ftMs_MS_SpecialNChargeStart = ftCo_MS_Count,
    ftMs_MS_SpecialNChargeLoop,
    ftMs_MS_SpecialNEarlyRelease,
    ftMs_MS_SpecialNFullRelease,

    ftMs_MS_SpecialAirNChargeStart,
    ftMs_MS_SpecialAirNChargeLoop,
    ftMs_MS_SpecialAirNEarlyRelease,
    ftMs_MS_SpecialAirNFullRelease,

    ftMs_MS_SpecialS1,
    ftMs_MS_SpecialS2U,
    ftMs_MS_SpecialS2S,
    ftMs_MS_SpecialS3U,
    ftMs_MS_SpecialS3S,
    ftMs_MS_SpecialS3D,
    ftMs_MS_SpecialS4U,
    ftMs_MS_SpecialS4S,
    ftMs_MS_SpecialS4D,

    ftMs_MS_SpecialAirS1,
    ftMs_MS_SpecialAirS2U,
    ftMs_MS_SpecialAirS2S,
    ftMs_MS_SpecialAirS3U,
    ftMs_MS_SpecialAirS3S,
    ftMs_MS_SpecialAirS3D,
    ftMs_MS_SpecialAirS4U,
    ftMs_MS_SpecialAirS4S,
    ftMs_MS_SpecialAirS4D,

    ftMs_MS_SpecialHi,
    ftMs_MS_SpecialAirHi,

    ftMs_MS_SpecialLw,
    ftMs_MS_SpecialLwHit,

    ftMs_MS_SpecialAirLw,
    ftMs_MS_SpecialAirLwHit,
} ftMars_MotionState;

#endif
