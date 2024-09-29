#ifndef MELEE_FT_CHARA_FTKIRBY_FORWARD_H
#define MELEE_FT_CHARA_FTKIRBY_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef struct HSD_GObj ftKb_GObj;
typedef struct Fighter ftKb_Fighter;
typedef struct ftKb_DatAttrs ftKb_DatAttrs;

/// @todo Clean up factorization

static MotionFlags const ftKb_MF_MultiJump =
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipAnimVel | Ft_MF_Unk06;

static MotionFlags const ftKb_MF_AttackDash =
    Ft_MF_KeepFastFall | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipItemVis |
    Ft_MF_FreezeState;

static MotionFlags const ftKb_MF_AttackDashAir =
    ftKb_MF_AttackDash | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_18_20_21 =
    Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState;

static MotionFlags const ftKb_MF_4_18_20_21 =
    ftKb_MF_18_20_21 | Ft_MF_SkipModel;

static MotionFlags const ftKb_MF_2_4_18_20_21 =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_5_18_20_21 =
    ftKb_MF_18_20_21 | Ft_MF_SkipAnimVel;

static MotionFlags const ftKb_MF_SpecialN =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialS = ftKb_MF_4_18_20_21 | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialHi =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNMr =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNKp =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNPe =
    ftKb_MF_2_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNYs =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNLg =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNZd =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNDr =
    ftKb_MF_5_18_20_21 | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNGk =
    ftKb_MF_SpecialNZd | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNFx =
    ftKb_MF_2_4_18_20_21 | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNLk = ftKb_MF_4_18_20_21 |
                                              Ft_MF_KeepGfx | Ft_MF_SkipHit |
                                              Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNSk =
    ftKb_MF_SpecialNLk | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNNs =
    ftKb_MF_2_4_18_20_21 | Ft_MF_SkipHit | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNPp =
    ftKb_MF_SpecialNNs | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNPk =
    ftKb_MF_SpecialNPp | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNSs =
    ftKb_MF_5_18_20_21 | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNSs_1 =
    ftKb_MF_SpecialNSs | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNMt =
    ftKb_MF_SpecialNSs_1 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNCl =
    ftKb_MF_SpecialNMt | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNFc =
    ftKb_MF_SpecialNDr | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNPc =
    ftKb_MF_SpecialNSs_1 | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNGw =
    ftKb_MF_SpecialNPc | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialLw =
    ftKb_MF_2_4_18_20_21 | Ft_MF_KeepSfx;

static MotionFlags const ftKb_MF_SpecialNCa =
    ftKb_MF_SpecialLw | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNDk =
    ftKb_MF_4_18_20_21 | Ft_MF_SkipHit | Ft_MF_KeepSfx;

static MotionFlags const ftKb_MF_5_9_18_20_21 =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepSfx;

static MotionFlags const ftKb_MF_2_5_9_18_20_21 =
    ftKb_MF_5_9_18_20_21 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNPr =
    ftKb_MF_5_9_18_20_21 | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNMs =
    ftKb_MF_2_5_9_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNGn =
    ftKb_MF_2_5_9_18_20_21 | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNFeStart =
    ftKb_MF_SpecialNMs | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialAirN =
    ftKb_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirS =
    ftKb_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirHi =
    ftKb_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMr =
    ftKb_MF_SpecialNMr | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNKp =
    ftKb_MF_SpecialNKp | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPe =
    ftKb_MF_SpecialNPe | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNYs =
    ftKb_MF_SpecialNYs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNLg =
    ftKb_MF_SpecialNLg | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNZd =
    ftKb_MF_SpecialNZd | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNDr =
    ftKb_MF_SpecialNDr | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGk =
    ftKb_MF_SpecialNGk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFx =
    ftKb_MF_SpecialNFx | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNLk =
    ftKb_MF_SpecialNLk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNSk =
    ftKb_MF_SpecialNSk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNNs =
    ftKb_MF_SpecialNNs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPp =
    ftKb_MF_SpecialNPp | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPk =
    ftKb_MF_SpecialNPk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNSs =
    ftKb_MF_SpecialNSs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMt =
    ftKb_MF_SpecialNMt | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNCl =
    ftKb_MF_SpecialNCl | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFc =
    ftKb_MF_SpecialNFc | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPc =
    ftKb_MF_SpecialNPc | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGw =
    ftKb_MF_SpecialNGw | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirLw =
    ftKb_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNCa =
    ftKb_MF_SpecialNCa | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNDk =
    ftKb_MF_SpecialNDk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPr =
    ftKb_MF_SpecialNPr | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMs =
    ftKb_MF_SpecialNMs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGn =
    ftKb_MF_SpecialNGn | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialNFe =
    ftKb_MF_SpecialNFeStart | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_0_4_18_20_21 =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNCaptureTurn =
    ftKb_MF_0_4_18_20_21 | Ft_MF_KeepAccessory;

static MotionFlags const ftKb_MF_SpecialAirNCaptureTurn =
    ftKb_MF_SpecialNCaptureTurn | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialNCaptureWalk =
    ftKb_MF_0_4_18_20_21 | Ft_MF_UpdateCmd;

static MotionFlags const ftKb_MF_SpecialNCaptureJumpSquat =
    ftKb_MF_0_4_18_20_21 | Ft_MF_SkipNametagVis;

static MotionFlags const ftKb_MF_SpecialNLoop =
    ftKb_MF_0_4_18_20_21 | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNKpLoop =
    ftKb_MF_SpecialNKp | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNGkLoop =
    ftKb_MF_SpecialNGk | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNFxLoop =
    ftKb_MF_SpecialNFx | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNLkCharged =
    ftKb_MF_SpecialNLk | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNSkLoop =
    ftKb_MF_SpecialNSk | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNMtLoop =
    ftKb_MF_SpecialNMt | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNClCharged =
    ftKb_MF_SpecialNCl | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNFcLoop =
    ftKb_MF_SpecialNFc | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNPrLoop =
    ftKb_MF_SpecialNPr | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialAirNLoop =
    ftKb_MF_SpecialNLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNKpLoop =
    ftKb_MF_SpecialNKpLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGkLoop =
    ftKb_MF_SpecialNGkLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFxLoop =
    ftKb_MF_SpecialNFxLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNLkCharged =
    ftKb_MF_SpecialNLkCharged | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNSkLoop =
    ftKb_MF_SpecialNSkLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMtLoop =
    ftKb_MF_SpecialNMtLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNClCharged =
    ftKb_MF_SpecialNClCharged | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFcLoop =
    ftKb_MF_SpecialNFcLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPrLoop =
    ftKb_MF_SpecialNPrLoop | Ft_MF_SkipParasol;

typedef enum ftKirby_MotionState {
    ftKb_MS_JumpAerialF1 = ftCo_MS_Count,
    ftKb_MS_JumpAerialF2,
    ftKb_MS_JumpAerialF3,
    ftKb_MS_JumpAerialF4,
    ftKb_MS_JumpAerialF5,
    ftKb_MS_JumpAerialF1Met,
    ftKb_MS_JumpAerialF2Met,
    ftKb_MS_JumpAerialF3Met,
    ftKb_MS_JumpAerialF4Met,
    ftKb_MS_JumpAerialF5Met,
    ftKb_MS_AttackDash,
    ftKb_MS_AttackDashAir,
    ftKb_MS_SpecialN,
    ftKb_MS_SpecialNLoop,
    ftKb_MS_SpecialNEnd,
    ftKb_MS_SpecialNCapture0,
    ftKb_MS_SpecialNCapture1,
    ftKb_MS_Eat,
    ftKb_MS_EatWait,
    ftKb_MS_EatWalkSlow,
    ftKb_MS_EatWalkMiddle,
    ftKb_MS_EatWalkFast,
    ftKb_MS_EatTurn,
    ftKb_MS_EatJump1,
    ftKb_MS_EatJump2,
    ftKb_MS_EatLanding,
    ftKb_MS_SpecialNDrink0,
    ftKb_MS_SpecialNDrink1,
    ftKb_MS_SpecialNSpit0,
    ftKb_MS_SpecialNSpit1,
    ftKb_MS_SpecialAirN,
    ftKb_MS_SpecialAirNLoop,
    ftKb_MS_SpecialAirNEnd,
    ftKb_MS_SpecialAirNCapture0,
    ftKb_MS_SpecialAirNCapture1,
    ftKb_MS_EatAir,
    ftKb_MS_EatFall,
    ftKb_MS_SpecialAirNDrink0,
    ftKb_MS_SpecialAirNDrink1,
    ftKb_MS_SpecialAirNSpit0,
    ftKb_MS_SpecialAirNSpit1,
    ftKb_MS_EatTurnAir,
    ftKb_MS_SpecialS,
    ftKb_MS_SpecialAirS,
    ftKb_MS_SpecialHi1,
    ftKb_MS_SpecialHi2,
    ftKb_MS_SpecialHi3,
    ftKb_MS_SpecialHi4,
    ftKb_MS_SpecialAirHi1,
    ftKb_MS_SpecialAirHi2,
    ftKb_MS_SpecialAirHi3,
    ftKb_MS_SpecialAirHi4,
    ftKb_MS_SpecialLw1,
    ftKb_MS_SpecialLw,
    ftKb_MS_SpecialLwEnd,
    ftKb_MS_SpecialAirLwStart,
    ftKb_MS_SpecialAirLw,
    ftKb_MS_SpecialAirLwEnd,
    ftKb_MS_MrSpecialN,
    ftKb_MS_MrSpecialAirN,
    ftKb_MS_LkSpecialNStart,
    ftKb_MS_LkSpecialNLoop,
    ftKb_MS_LkSpecialNEnd,
    ftKb_MS_LkSpecialAirNStart,
    ftKb_MS_LkSpecialAirNLoop,
    ftKb_MS_LkSpecialAirNEnd,
    ftKb_MS_SsSpecialNStart,
    ftKb_MS_SsSpecialNHold,
    ftKb_MS_SsSpecialNCancel,
    ftKb_MS_SsSpecialN,
    ftKb_MS_SsSpecialAirNStart,
    ftKb_MS_SsSpecialAirN,
    ftKb_MS_YsSpecialN1,
    ftKb_MS_YsSpecialNCapture1_0,
    ftKb_MS_YsSpecialNCapture1_1,
    ftKb_MS_YsSpecialNCapture2_0,
    ftKb_MS_YsSpecialNCapture2_1,
    ftKb_MS_YsSpecialAirNCapture2,
    ftKb_MS_YsSpecialAirNCapture1_0,
    ftKb_MS_YsSpecialAirNCapture1_1,
    ftKb_MS_YsSpecialAirN2_0,
    ftKb_MS_YsSpecialAirN2_1,
    ftKb_MS_FxSpecialNStart,
    ftKb_MS_FxSpecialNLoop,
    ftKb_MS_FxSpecialNEnd,
    ftKb_MS_FxSpecialAirNStart,
    ftKb_MS_FxSpecialAirNLoop,
    ftKb_MS_FxSpecialAirNEnd,
    ftKb_MS_PkSpecialN,
    ftKb_MS_PkSpecialAirN,
    ftKb_MS_LgSpecialN,
    ftKb_MS_LgSpecialAirN,
    ftKb_MS_CaSpecialN,
    ftKb_MS_CaSpecialAirN,
    ftKb_MS_NsSpecialNStart,
    ftKb_MS_NsSpecialNHold0,
    ftKb_MS_NsSpecialNHold1,
    ftKb_MS_NsSpecialNEnd,
    ftKb_MS_NsSpecialAirNStart,
    ftKb_MS_NsSpecialAirNHold0,
    ftKb_MS_NsSpecialAirNHold1,
    ftKb_MS_NsSpecialAirNEnd,
    ftKb_MS_KpSpecialNStart,
    ftKb_MS_KpSpecialN,
    ftKb_MS_KpSpecialNEnd,
    ftKb_MS_KpSpecialAirNStart,
    ftKb_MS_KpSpecialAirN,
    ftKb_MS_KpSpecialAirNEnd,
    ftKb_MS_PeSpecialLw,
    ftKb_MS_PeSpecialLwHit,
    ftKb_MS_PeSpecialAirLw,
    ftKb_MS_PeSpecialAirLwHit,
    ftKb_MS_PpSpecialN,
    ftKb_MS_PpSpecialAirN,
    ftKb_MS_DkSpecialNStart,
    ftKb_MS_DkSpecialNLoop,
    ftKb_MS_DkSpecialNCancel,
    ftKb_MS_DkSpecialN,
    ftKb_MS_DkSpecialNFull,
    ftKb_MS_DkSpecialAirNStart,
    ftKb_MS_DkSpecialAirNLoop,
    ftKb_MS_DkSpecialAirNCancel,
    ftKb_MS_DkSpecialAirN,
    ftKb_MS_DkSpecialAirNFull,
    ftKb_MS_ZdSpecialN,
    ftKb_MS_ZdSpecialAirN,
    ftKb_MS_SkSpecialNStart,
    ftKb_MS_SkSpecialNLoop,
    ftKb_MS_SkSpecialNCancel,
    ftKb_MS_SkSpecialNEnd,
    ftKb_MS_SkSpecialAirNStart,
    ftKb_MS_SkSpecialAirNLoop,
    ftKb_MS_SkSpecialAirNCancel,
    ftKb_MS_SkSpecialAirNEnd,
    ftKb_MS_PrSpecialNStartR,
    ftKb_MS_PrSpecialNStartL,
    ftKb_MS_PrSpecialNLoop,
    ftKb_MS_PrSpecialNFull,
    ftKb_MS_PrSpecialN1,
    ftKb_MS_PrSpecialNTurn,
    ftKb_MS_PrSpecialNEndR,
    ftKb_MS_PrSpecialNEndL,
    ftKb_MS_PrSpecialAirNStartR,
    ftKb_MS_PrSpecialAirNStartL,
    ftKb_MS_PrSpecialAirNLoop,
    ftKb_MS_PrSpecialAirNFull,
    ftKb_MS_PrSpecialAirN,
    ftKb_MS_PrSpecialN0,
    ftKb_MS_PrSpecialAirNEndR0,
    ftKb_MS_PrSpecialAirNEndR1,
    ftKb_MS_PrSpecialNHit,
    ftKb_MS_MsSpecialNStart,
    ftKb_MS_MsSpecialNLoop,
    ftKb_MS_MsSpecialNEnd0,
    ftKb_MS_MsSpecialNEnd1,
    ftKb_MS_MsSpecialAirNStart,
    ftKb_MS_MsSpecialAirNLoop,
    ftKb_MS_MsSpecialAirNEnd0,
    ftKb_MS_MsSpecialAirNEnd1,
    ftKb_MS_MtSpecialNStart,
    ftKb_MS_MtSpecialNLoop,
    ftKb_MS_MtSpecialNLoopFull,
    ftKb_MS_MtSpecialNCancel,
    ftKb_MS_MtSpecialNEnd,
    ftKb_MS_MtSpecialAirNStart,
    ftKb_MS_MtSpecialAirNLoop,
    ftKb_MS_MtSpecialAirNLoopFull,
    ftKb_MS_MtSpecialAirNCancel,
    ftKb_MS_MtSpecialAirNEnd,
    ftKb_MS_GwSpecialN,
    ftKb_MS_GwSpecialAirN,
    ftKb_MS_DrSpecialN,
    ftKb_MS_DrSpecialAirN,
    ftKb_MS_ClSpecialNStart,
    ftKb_MS_ClSpecialNLoop,
    ftKb_MS_ClSpecialNEnd,
    ftKb_MS_ClSpecialAirNStart,
    ftKb_MS_ClSpecialAirNLoop,
    ftKb_MS_ClSpecialAirNEnd,
    ftKb_MS_FcSpecialNStart,
    ftKb_MS_FcSpecialNLoop,
    ftKb_MS_FcSpecialNEnd,
    ftKb_MS_FcSpecialAirNStart,
    ftKb_MS_FcSpecialAirNLoop,
    ftKb_MS_FcSpecialAirNEnd,
    ftKb_MS_PcSpecialN,
    ftKb_MS_PcSpecialAirN,
    ftKb_MS_GnSpecialN,
    ftKb_MS_GnSpecialAirN,
    ftKb_MS_FeSpecialNStart,
    ftKb_MS_FeSpecialNLoop,
    ftKb_MS_FeSpecialNEnd0,
    ftKb_MS_FeSpecialNEnd1,
    ftKb_MS_FeSpecialAirNStart,
    ftKb_MS_FeSpecialAirNLoop,
    ftKb_MS_FeSpecialAirNEnd0,
    ftKb_MS_FeSpecialAirNEnd1,
    ftKb_MS_GkSpecialNStart,
    ftKb_MS_GkSpecialN,
    ftKb_MS_GkSpecialNEnd,
    ftKb_MS_GkSpecialAirNStart,
    ftKb_MS_GkSpecialAirN,
    ftKb_MS_GkSpecialAirNEnd,
    ftKb_MS_Count,
    ftKb_MS_SelfCount = ftKb_MS_Count - ftCo_MS_Count,
} ftKirby_MotionState;

typedef enum ftKb_Submotion {
    ftKb_SM_JumpAerialF1 = ftCo_SM_Count,
    ftKb_SM_JumpAerialF2,
    ftKb_SM_JumpAerialF3,
    ftKb_SM_JumpAerialF4,
    ftKb_SM_JumpAerialF5,
    ftKb_SM_JumpAerialF1Met,
    ftKb_SM_JumpAerialF2Met,
    ftKb_SM_JumpAerialF3Met,
    ftKb_SM_JumpAerialF4Met,
    ftKb_SM_JumpAerialF5Met,
    ftKb_SM_SpecialN,
    ftKb_SM_SpecialNLoop,
    ftKb_SM_SpecialNEnd,
    ftKb_SM_SpecialNCapture,
    ftKb_SM_Eat,
    ftKb_SM_EatWait,
    ftKb_SM_EatWalkSlow,
    ftKb_SM_EatWalkMiddle,
    ftKb_SM_EatWalkFast,
    ftKb_SM_EatJump1,
    ftKb_SM_EatJump2,
    ftKb_SM_EatLanding,
    ftKb_SM_EatTurn,
    ftKb_SM_SpecialNDrink,
    ftKb_SM_SpecialNSpit,
    ftKb_SM_SpecialAirN,
    ftKb_SM_SpecialAirNLoop,
    ftKb_SM_SpecialS,
    ftKb_SM_SpecialAirS,
    ftKb_SM_SpecialHi1,
    ftKb_SM_SpecialHi2,
    ftKb_SM_SpecialHi3,
    ftKb_SM_SpecialHi4,
    ftKb_SM_SpecialAirHi1,
    ftKb_SM_SpecialAirHi2,
    ftKb_SM_SpecialAirHi3,
    ftKb_SM_SpecialAirHiEnd,
    ftKb_SM_SpecialLw1,
    ftKb_SM_SpecialLw,
    ftKb_SM_SpecialLwEnd,
    ftKb_SM_SpecialAirLwStart,
    ftKb_SM_SpecialAirLw,
    ftKb_SM_SpecialAirLwEnd,
    ftKb_SM_MrSpecialN,
    ftKb_SM_MrSpecialAirN,
    ftKb_SM_LkSpecialNStart,
    ftKb_SM_LkSpecialNLoop,
    ftKb_SM_LkSpecialNEnd,
    ftKb_SM_LkSpecialAirNStart,
    ftKb_SM_LkSpecialAirNLoop,
    ftKb_SM_LkSpecialAirNEnd,
    ftKb_SM_SsSpecialNStart,
    ftKb_SM_SsSpecialNHold,
    ftKb_SM_SsSpecialNCancel,
    ftKb_SM_SsSpecialN,
    ftKb_SM_SsSpecialAirNStart,
    ftKb_SM_SsSpecialAirN,
    ftKb_SM_YsSpecialN1,
    ftKb_SM_YsSpecialNCapture1,
    ftKb_SM_YsSpecialNCapture2,
    ftKb_SM_YsSpecialAirNCapture2,
    ftKb_SM_YsSpecialAirCapture1,
    ftKb_SM_YsSpecialAirN2,
    ftKb_SM_FxSpecialNStart,
    ftKb_SM_FxSpecialNLoop,
    ftKb_SM_FxSpecialNEnd,
    ftKb_SM_FxSpecialAirNStart,
    ftKb_SM_FxSpecialAirNLoop,
    ftKb_SM_FxSpecialAirNEnd,
    ftKb_SM_PkSpecialN,
    ftKb_SM_PkSpecialAirN,
    ftKb_SM_LgSpecialN,
    ftKb_SM_LgSpecialAirN,
    ftKb_SM_CaSpecialN,
    ftKb_SM_CaSpecialAirN,
    ftKb_SM_NsSpecialNStart,
    ftKb_SM_NsSpecialNHold0,
    ftKb_SM_NsSpecialNHold1,
    ftKb_SM_NsSpecialNEnd,
    ftKb_SM_NsSpecialAirNStart,
    ftKb_SM_NsSpecialAirNHold0,
    ftKb_SM_NsSpecialAirNHold1,
    ftKb_SM_NsSpecialAirNEnd,
    ftKb_SM_KpSpecialNStart,
    ftKb_SM_KpSpecialN,
    ftKb_SM_KpSpecialNEnd,
    ftKb_SM_KpSpecialAirNStart,
    ftKb_SM_KpSpecialAirN,
    ftKb_SM_KpSpecialAirNEnd,
    ftKb_SM_PeSpecialLw,
    ftKb_SM_PeSpecialLwHit,
    ftKb_SM_PeSpecialAirLw,
    ftKb_SM_PeSpecialAirLwHit,
    ftKb_SM_PpSpecialN,
    ftKb_SM_PpSpecialAirN,
    ftKb_SM_DkSpecialNStart,
    ftKb_SM_DkSpecialNLoop,
    ftKb_SM_DkSpecialNCancel,
    ftKb_SM_DkSpecialN,
    ftKb_SM_DkSpecialNFull,
    ftKb_SM_DkSpecialAirNStart,
    ftKb_SM_DkSpecialAirNLoop,
    ftKb_SM_DkSpecialAirNCancel,
    ftKb_SM_DkSpecialAirN,
    ftKb_SM_DkSpecialAirNFull,
    ftKb_SM_ZdSpecialN,
    ftKb_SM_ZdSpecialAirN,
    ftKb_SM_SkSpecialNStart,
    ftKb_SM_SkSpecialNLoop,
    ftKb_SM_SkSpecialNCancel,
    ftKb_SM_SkSpecialNEnd,
    ftKb_SM_SkSpecialAirNStart,
    ftKb_SM_SkSpecialAirNLoop,
    ftKb_SM_SkSpecialAirNCancel,
    ftKb_SM_SkSpecialAirNEnd,
    ftKb_SM_PrSpecialNStartR,
    ftKb_SM_PrSpecialNStartL,
    ftKb_SM_PrSpecialNLoop,
    ftKb_SM_PrSpecialNFull,
    ftKb_SM_PrSpecialN1,
    ftKb_SM_PrSpecialNTurn,
    ftKb_SM_PrSpecialNEndR,
    ftKb_SM_PrSpecialNEndL,
    ftKb_SM_PrSpecialAirNStartR,
    ftKb_SM_PrSpecialAirNStartL,
    ftKb_SM_PrSpecialAirNLoop,
    ftKb_SM_PrSpecialAirNFull,
    ftKb_SM_PrSpecialAirN,
    ftKb_SM_PrSpecialN0,
    ftKb_SM_PrSpecialAirNEndR0,
    ftKb_SM_PrSpecialAirNEndR1,
    ftKb_SM_PrSpecialNHit,
    ftKb_SM_MsSpecialNStart,
    ftKb_SM_MsSpecialNLoop,
    ftKb_SM_MsSpecialNEnd0,
    ftKb_SM_MsSpecialNEnd1,
    ftKb_SM_MsSpecialAirNStart,
    ftKb_SM_MsSpecialAirNLoop,
    ftKb_SM_MsSpecialAirNEnd0,
    ftKb_SM_MsSpecialAirNEnd1,
    ftKb_SM_MtSpecialNStart,
    ftKb_SM_MtSpecialNLoop,
    ftKb_SM_MtSpecialNLoopFull,
    ftKb_SM_MtSpecialNCancel,
    ftKb_SM_MtSpecialNEnd,
    ftKb_SM_MtSpecialAirNStart,
    ftKb_SM_MtSpecialAirNLoop,
    ftKb_SM_MtSpecialAirNLoopFull,
    ftKb_SM_MtSpecialAirNCancel,
    ftKb_SM_MtSpecialAirNEnd,
    ftKb_SM_GwSpecialN,
    ftKb_SM_GwSpecialAirN,
    ftKb_SM_DrSpecialN,
    ftKb_SM_DrSpecialAirN,
    ftKb_SM_ClSpecialNStart,
    ftKb_SM_ClSpecialNLoop,
    ftKb_SM_ClSpecialNEnd,
    ftKb_SM_ClSpecialAirNStart,
    ftKb_SM_ClSpecialAirNLoop,
    ftKb_SM_ClSpecialAirNEnd,
    ftKb_SM_FcSpecialNStart,
    ftKb_SM_FcSpecialNLoop,
    ftKb_SM_FcSpecialNEnd,
    ftKb_SM_FcSpecialAirNStart,
    ftKb_SM_FcSpecialAirNLoop,
    ftKb_SM_FcSpecialAirNEnd,
    ftKb_SM_PcSpecialN,
    ftKb_SM_PcSpecialAirN,
    ftKb_SM_GnSpecialN,
    ftKb_SM_GnSpecialAirN,
    ftKb_SM_FeSpecialNStart,
    ftKb_SM_FeSpecialNLoop,
    ftKb_SM_FeSpecialNEnd0,
    ftKb_SM_FeSpecialNEnd1,
    ftKb_SM_FeSpecialAirNStart,
    ftKb_SM_FeSpecialAirNLoop,
    ftKb_SM_FeSpecialAirNEnd0,
    ftKb_SM_FeSpecialAirNEnd1,
    ftKb_SM_GkSpecialNStart,
    ftKb_SM_GkSpecialN,
    ftKb_SM_GkSpecialNEnd,
    ftKb_SM_GkSpecialAirNStart,
    ftKb_SM_GkSpecialAirN,
    ftKb_SM_GkSpecialAirNEnd,
    ftKb_SM_Count,
    ftKb_SM_SelfCount = ftKb_SM_Count - ftCo_SM_Count,
} ftKb_Submotion;

#endif
