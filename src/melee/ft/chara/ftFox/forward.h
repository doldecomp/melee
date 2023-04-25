#ifndef MELEE_FT_CHARA_FTFOX_FORWARD_H
#define MELEE_FT_CHARA_FTFOX_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftFx_MF_Appeal ATTRIBUTE_USED =
    Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipAnimVel | Ft_MF_Unk06;

static MotionFlags const ftFx_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftFx_MF_SpecialN ATTRIBUTE_USED =
    ftFx_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftFx_MF_SpecialS ATTRIBUTE_USED =
    ftFx_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftFx_MF_SpecialHi ATTRIBUTE_USED =
    ftFx_MF_SpecialS | Ft_MF_KeepFastFall;

static MotionFlags const ftFx_MF_SpecialAirN ATTRIBUTE_USED =
    ftFx_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftFx_MF_SpecialAirS ATTRIBUTE_USED =
    ftFx_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftFx_MF_SpecialAirHiHold ATTRIBUTE_USED =
    ftFx_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftFx_MF_SpecialLw ATTRIBUTE_USED =
    ftFx_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipColAnim;

static MotionFlags const ftFx_MF_SpecialAirLw ATTRIBUTE_USED =
    ftFx_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftFx_MF_SpecialNLoop ATTRIBUTE_USED =
    ftFx_MF_SpecialN | Ft_MF_Unk19;

static MotionFlags const ftFx_MF_SpecialAirNLoop ATTRIBUTE_USED =
    ftFx_MF_SpecialNLoop | Ft_MF_SkipParasol;

static MotionFlags const ftFx_MF_SpecialLwLoop ATTRIBUTE_USED =
    ftFx_MF_SpecialLw | Ft_MF_Unk19;

static MotionFlags const ftFx_MF_SpecialAirLwLoop ATTRIBUTE_USED =
    ftFx_MF_SpecialLwLoop | Ft_MF_SkipParasol;

typedef enum ftFox_MotionState {
    ftFx_MS_SpecialNStart = ftCo_MS_Count,
    ftFx_MS_SpecialNLoop,
    ftFx_MS_SpecialNEnd,
    ftFx_MS_SpecialAirNStart,
    ftFx_MS_SpecialAirNLoop,
    ftFx_MS_SpecialAirNEnd,
    ftFx_MS_SpecialSStart,
    ftFx_MS_SpecialS,
    ftFx_MS_SpecialSEnd,
    ftFx_MS_SpecialAirSStart,
    ftFx_MS_SpecialAirS,
    ftFx_MS_SpecialAirSEnd,
    ftFx_MS_SpecialHiStart,
    ftFx_MS_SpecialAirHiStart,
    ftFx_MS_SpecialHi,
    ftFx_MS_SpecialAirHi,
    ftFx_MS_SpecialHiEnd,
    ftFx_MS_SpecialAirHiEnd,
    ftFx_MS_SpecialHiBound,
    ftFx_MS_SpecialLwStart,
    ftFx_MS_SpecialLwLoop,
    ftFx_MS_SpecialLwReflect,
    ftFx_MS_SpecialLwEnd,
    ftFx_MS_SpecialLwTurn,
    ftFx_MS_SpecialAirLwStart,
    ftFx_MS_SpecialAirLwLoop,
    ftFx_MS_SpecialAirLwReflect,
    ftFx_MS_SpecialAirLwEnd,
    ftFx_MS_SpecialAirLwTurn,
    ftFx_MS_AppealRStart,
    ftFx_MS_AppealLStart,
    ftFx_MS_AppealR,
    ftFx_MS_AppealL,
    ftFx_MS_AppealREnd,
    ftFx_MS_AppealLEnd,
} ftFox_MotionState;

typedef enum ftFx_AnimId {
    ftFx_AnimId_SpecialNStart = ftCo_AnimId_Count,
    ftFx_AnimId_SpecialNLoop,
    ftFx_AnimId_SpecialNEnd,
    ftFx_AnimId_SpecialAirNStart,
    ftFx_AnimId_SpecialAirNLoop,
    ftFx_AnimId_SpecialAirNEnd,
    ftFx_AnimId_SpecialSStart,
    ftFx_AnimId_SpecialS,
    ftFx_AnimId_SpecialSEnd,
    ftFx_AnimId_SpecialAirSStart,
    ftFx_AnimId_SpecialAirS,
    ftFx_AnimId_SpecialAirSEnd,
    ftFx_AnimId_SpecialHiHold,
    ftFx_AnimId_SpecialHiHoldAir,
    ftFx_AnimId_SpecialHi,
    ftFx_AnimId_SpecialHiLanding,
    ftFx_AnimId_SpecialHiFall,
    ftFx_AnimId_SpecialHiBound,
    ftFx_AnimId_SpecialLwStart,
    ftFx_AnimId_SpecialLwLoop,
    ftFx_AnimId_SpecialLwHit,
    ftFx_AnimId_SpecialLwEnd,
    ftFx_AnimId_SpecialAirLwStart,
    ftFx_AnimId_SpecialAirLwLoop,
    ftFx_AnimId_SpecialAirLwHit,
    ftFx_AnimId_SpecialAirLwEnd,
    ftFx_AnimId_Appeal0,
    ftFx_AnimId_Appeal1,
    ftFx_AnimId_Appeal2,
    ftFx_AnimId_Appeal3,
    ftFx_AnimId_Appeal4,
    ftFx_AnimId_Appeal5,
} ftFx_AnimId;

#endif
