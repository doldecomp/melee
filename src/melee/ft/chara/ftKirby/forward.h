#ifndef MELEE_FT_CHARA_FTKIRBY_FORWARD_H
#define MELEE_FT_CHARA_FTKIRBY_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

/// @todo Clean up factorization

static MotionFlags const ftKb_MF_MultiJump ATTRIBUTE_USED =
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipAnimVel | Ft_MF_Unk06;

static MotionFlags const ftKb_MF_AttackDash ATTRIBUTE_USED =
    Ft_MF_KeepFastFall | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipItemVis |
    Ft_MF_FreezeState;

static MotionFlags const ftKb_MF_AttackDashAir ATTRIBUTE_USED =
    ftKb_MF_AttackDash | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_18_20_21 ATTRIBUTE_USED =
    Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState;

static MotionFlags const ftKb_MF_4_18_20_21 ATTRIBUTE_USED =
    ftKb_MF_18_20_21 | Ft_MF_SkipModel;

static MotionFlags const ftKb_MF_2_4_18_20_21 ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_5_18_20_21 ATTRIBUTE_USED =
    ftKb_MF_18_20_21 | Ft_MF_SkipAnimVel;

static MotionFlags const ftKb_MF_SpecialN ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialS ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialHi ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNMr ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNKp ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNPe ATTRIBUTE_USED =
    ftKb_MF_2_4_18_20_21 | Ft_MF_KeepFastFall | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNYs ATTRIBUTE_USED =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNLg ATTRIBUTE_USED =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNZd ATTRIBUTE_USED =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNDr ATTRIBUTE_USED =
    ftKb_MF_5_18_20_21 | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNGk ATTRIBUTE_USED =
    ftKb_MF_SpecialNZd | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNFx ATTRIBUTE_USED =
    ftKb_MF_2_4_18_20_21 | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNLk ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepGfx | Ft_MF_SkipHit |
    Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNSk ATTRIBUTE_USED =
    ftKb_MF_SpecialNLk | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNNs ATTRIBUTE_USED =
    ftKb_MF_2_4_18_20_21 | Ft_MF_SkipHit | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNPp ATTRIBUTE_USED =
    ftKb_MF_SpecialNNs | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNPk ATTRIBUTE_USED =
    ftKb_MF_SpecialNPp | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNSs ATTRIBUTE_USED =
    ftKb_MF_5_18_20_21 | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNSs_1 ATTRIBUTE_USED =
    ftKb_MF_SpecialNSs | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNMt ATTRIBUTE_USED =
    ftKb_MF_SpecialNSs_1 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNCl ATTRIBUTE_USED =
    ftKb_MF_SpecialNMt | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNFc ATTRIBUTE_USED =
    ftKb_MF_SpecialNDr | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftKb_MF_SpecialNPc ATTRIBUTE_USED =
    ftKb_MF_SpecialNSs_1 | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNGw ATTRIBUTE_USED =
    ftKb_MF_SpecialNPc | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialLw ATTRIBUTE_USED =
    ftKb_MF_2_4_18_20_21 | Ft_MF_KeepSfx;

static MotionFlags const ftKb_MF_SpecialNCa ATTRIBUTE_USED =
    ftKb_MF_SpecialLw | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNDk ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_SkipHit | Ft_MF_KeepSfx;

static MotionFlags const ftKb_MF_5_9_18_20_21 ATTRIBUTE_USED =
    ftKb_MF_5_18_20_21 | Ft_MF_KeepSfx;

static MotionFlags const ftKb_MF_2_5_9_18_20_21 ATTRIBUTE_USED =
    ftKb_MF_5_9_18_20_21 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftKb_MF_SpecialNPr ATTRIBUTE_USED =
    ftKb_MF_5_9_18_20_21 | Ft_MF_KeepGfx;

static MotionFlags const ftKb_MF_SpecialNMs ATTRIBUTE_USED =
    ftKb_MF_2_5_9_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNGn ATTRIBUTE_USED =
    ftKb_MF_2_5_9_18_20_21 | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialNFeStart ATTRIBUTE_USED =
    ftKb_MF_SpecialNMs | Ft_MF_SkipHit;

static MotionFlags const ftKb_MF_SpecialAirN ATTRIBUTE_USED =
    ftKb_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirS ATTRIBUTE_USED =
    ftKb_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirHi ATTRIBUTE_USED =
    ftKb_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMr ATTRIBUTE_USED =
    ftKb_MF_SpecialNMr | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNKp ATTRIBUTE_USED =
    ftKb_MF_SpecialNKp | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPe ATTRIBUTE_USED =
    ftKb_MF_SpecialNPe | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNYs ATTRIBUTE_USED =
    ftKb_MF_SpecialNYs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNLg ATTRIBUTE_USED =
    ftKb_MF_SpecialNLg | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNZd ATTRIBUTE_USED =
    ftKb_MF_SpecialNZd | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNDr ATTRIBUTE_USED =
    ftKb_MF_SpecialNDr | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGk ATTRIBUTE_USED =
    ftKb_MF_SpecialNGk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFx ATTRIBUTE_USED =
    ftKb_MF_SpecialNFx | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNLk ATTRIBUTE_USED =
    ftKb_MF_SpecialNLk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNSk ATTRIBUTE_USED =
    ftKb_MF_SpecialNSk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNNs ATTRIBUTE_USED =
    ftKb_MF_SpecialNNs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPp ATTRIBUTE_USED =
    ftKb_MF_SpecialNPp | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPk ATTRIBUTE_USED =
    ftKb_MF_SpecialNPk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNSs ATTRIBUTE_USED =
    ftKb_MF_SpecialNSs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMt ATTRIBUTE_USED =
    ftKb_MF_SpecialNMt | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNCl ATTRIBUTE_USED =
    ftKb_MF_SpecialNCl | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFc ATTRIBUTE_USED =
    ftKb_MF_SpecialNFc | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPc ATTRIBUTE_USED =
    ftKb_MF_SpecialNPc | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGw ATTRIBUTE_USED =
    ftKb_MF_SpecialNGw | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirLw ATTRIBUTE_USED =
    ftKb_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNCa ATTRIBUTE_USED =
    ftKb_MF_SpecialNCa | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNDk ATTRIBUTE_USED =
    ftKb_MF_SpecialNDk | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPr ATTRIBUTE_USED =
    ftKb_MF_SpecialNPr | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMs ATTRIBUTE_USED =
    ftKb_MF_SpecialNMs | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGn ATTRIBUTE_USED =
    ftKb_MF_SpecialNGn | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialNFe ATTRIBUTE_USED =
    ftKb_MF_SpecialNFeStart | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_0_4_18_20_21 ATTRIBUTE_USED =
    ftKb_MF_4_18_20_21 | Ft_MF_KeepFastFall;

static MotionFlags const ftKb_MF_SpecialNCaptureTurn ATTRIBUTE_USED =
    ftKb_MF_0_4_18_20_21 | Ft_MF_KeepAccessory;

static MotionFlags const ftKb_MF_SpecialAirNCaptureTurn ATTRIBUTE_USED =
    ftKb_MF_SpecialNCaptureTurn | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialNCaptureWalk ATTRIBUTE_USED =
    ftKb_MF_0_4_18_20_21 | Ft_MF_UpdateCmd;

static MotionFlags const ftKb_MF_SpecialNCaptureJumpSquat ATTRIBUTE_USED =
    ftKb_MF_0_4_18_20_21 | Ft_MF_SkipNametagVis;

static MotionFlags const ftKb_MF_SpecialNLoop ATTRIBUTE_USED =
    ftKb_MF_0_4_18_20_21 | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNKpLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNKp | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNGkLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNGk | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNFxLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNFx | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNLkCharged ATTRIBUTE_USED =
    ftKb_MF_SpecialNLk | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNSkLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNSk | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNMtLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNMt | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNClCharged ATTRIBUTE_USED =
    ftKb_MF_SpecialNCl | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNFcLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNFc | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialNPrLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNPr | Ft_MF_Unk19;

static MotionFlags const ftKb_MF_SpecialAirNLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNKpLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNKpLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNGkLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNGkLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFxLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNFxLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNLkCharged ATTRIBUTE_USED =
    ftKb_MF_SpecialNLkCharged | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNSkLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNSkLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNMtLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNMtLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNClCharged ATTRIBUTE_USED =
    ftKb_MF_SpecialNClCharged | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNFcLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNFcLoop | Ft_MF_SkipParasol;

static MotionFlags const ftKb_MF_SpecialAirNPrLoop ATTRIBUTE_USED =
    ftKb_MF_SpecialNPrLoop | Ft_MF_SkipParasol;

typedef enum ftKirby_MotionState {
    ftKb_MS_Jump2 = ftCo_MS_Count,
    ftKb_MS_Jump3,
    ftKb_MS_Jump4,
    ftKb_MS_Jump5,
    ftKb_MS_Jump6,

    ftKb_MS_Jump2_WithHat,
    ftKb_MS_Jump3_WithHat,
    ftKb_MS_Jump4_WithHat,
    ftKb_MS_Jump5_WithHat,
    ftKb_MS_Jump6_WithHat,

    ftKb_MS_AttackDash,
    ftKb_MS_AttackDash_Air,

    ftKb_MS_SpecialN_Start,
    ftKb_MS_SpecialN_Loop,
    ftKb_MS_SpecialN_End,
    ftKb_MS_SpecialN_Capture,
    ftKb_MS_Unk_357,
    ftKb_MS_SpecialN_Captured,
    ftKb_MS_SpecialN_CaptureWait,
    ftKb_MS_SpecialN_CaptureWalkSlow,
    ftKb_MS_SpecialN_CaptureWalkMiddle,
    ftKb_MS_SpecialN_CaptureWalkFast,
    ftKb_MS_SpecialN_CaptureTurn,
    ftKb_MS_SpecialN_CaptureJumpSquat,
    ftKb_MS_SpecialN_CaptureJump,
    ftKb_MS_SpecialN_CaptureLanding,
    ftKb_MS_SpecialN_Digest,
    ftKb_MS_Unk_368,
    ftKb_MS_SpecialN_Spit,
    ftKb_MS_Unk_370,
    ftKb_MS_SpecialAirN_Start,
    ftKb_MS_SpecialAirN_Loop,
    ftKb_MS_SpecialAirN_End,
    ftKb_MS_SpecialAirN_Capture,
    ftKb_MS_Unk_375,
    ftKb_MS_SpecialAirN_Captured,
    ftKb_MS_SpecialAirN_CaptureWait,
    ftKb_MS_SpecialAirN_Digest,
    ftKb_MS_Unk_379,
    ftKb_MS_SpecialAirN_Spit,
    ftKb_MS_Unk_381,
    ftKb_MS_SpecialAirN_CaptureTurn,

    ftKb_MS_SpecialS,
    ftKb_MS_SpecialAirS,

    ftKb_MS_SpecialHi_Start,
    ftKb_MS_Unk_386,
    ftKb_MS_Unk_387,
    ftKb_MS_SpecialHi_End,

    /// @todo Names.
    ftKb_MS_SpecialAirHi_Start,
    ftKb_MS_SpecialAirHi_Apex,
    ftKb_MS_SpecialHi_SwordDescent,
    ftKb_MS_SpecialAirHi_End,

    ftKb_MS_SpecialLw_Start,
    ftKb_MS_SpecialLw,
    ftKb_MS_SpecialLw_End,
    ftKb_MS_SpecialAirLw_Start,
    ftKb_MS_SpecialAirLw,
    ftKb_MS_SpecialAirLw_End,

    ftKb_MS_SpecialN_Mr,
    ftKb_MS_SpecialAirN_Mr,

    ftKb_MS_SpecialN_Lk_Charge,
    ftKb_MS_SpecialN_Lk_FullyCharged,
    ftKb_MS_SpecialN_Lk_Fire,
    ftKb_MS_SpecialAirN_Lk_Charge,
    ftKb_MS_SpecialAirN_Lk_FullyCharged,
    ftKb_MS_SpecialAirN_Lk_Fire,

    ftKb_MS_SpecialN_Ss_Start,
    ftKb_MS_SpecialN_Ss_Loop,
    ftKb_MS_SpecialN_Ss_End,
    ftKb_MS_SpecialN_Ss_Fire,
    ftKb_MS_SpecialAirN_Ss_Start,
    ftKb_MS_SpecialAirN_Ss_Fire,

    ftKb_MS_SpecialN_Ys,
    ftKb_MS_SpecialN_Ys_CaptureStart,
    ftKb_MS_Unk_415,
    ftKb_MS_SpecialN_Ys_Capture,
    ftKb_MS_Unk_417,
    ftKb_MS_SpecialAirN_Ys,
    ftKb_MS_SpecialAirN_Ys_CaptureStart,
    ftKb_MS_Unk_420,
    ftKb_MS_SpecialAirN_Ys_Capture,
    ftKb_MS_Unk_422,

    ftKb_MS_SpecialN_Fx_Start,
    ftKb_MS_SpecialN_Fx_Loop,
    ftKb_MS_SpecialN_Fx_End,
    ftKb_MS_SpecialAirN_Fx_Start,
    ftKb_MS_SpecialAirN_Fx_Loop,
    ftKb_MS_SpecialAirN_Fx_End,

    ftKb_MS_SpecialN_Pk,
    ftKb_MS_SpecialAirN_Pk,

    ftKb_MS_SpecialN_Lg,
    ftKb_MS_SpecialAirN_Lg,

    ftKb_MS_SpecialN_Ca,
    ftKb_MS_SpecialAirN_Ca,

    ftKb_MS_SpecialN_Ns_Start,
    ftKb_MS_SpecialN_Ns_Charge,
    ftKb_MS_SpecialN_Ns_Explode,
    ftKb_MS_SpecialN_Ns_End,
    ftKb_MS_SpecialAirN_Ns_Start,
    ftKb_MS_SpecialAirN_Ns_Charge,
    ftKb_MS_SpecialAirN_Ns_Explode,
    ftKb_MS_SpecialAirN_Ns_End,

    ftKb_MS_SpecialN_Kp_Start,
    ftKb_MS_SpecialN_Kp_Loop,
    ftKb_MS_SpecialN_Kp_End,
    ftKb_MS_SpecialAirN_Kp_Start,
    ftKb_MS_SpecialAirN_Kp_Loop,
    ftKb_MS_SpecialAirN_Kp_End,

    ftKb_MS_SpecialN_Pe,
    ftKb_MS_SpecialN_Pe_Attack,
    ftKb_MS_SpecialAirN_Pe,
    ftKb_MS_SpecialAirN_Pe_Attack,

    ftKb_MS_SpecialN_Ic,
    ftKb_MS_SpecialAirN_Ic,

    ftKb_MS_SpecialN_Dk_ChargeStart,
    ftKb_MS_SpecialN_Dk_ChargeLoop,
    ftKb_MS_SpecialN_Dk_ChargeStop,
    ftKb_MS_SpecialN_Dk_EarlyPunch,
    ftKb_MS_SpecialN_Dk_FullChargePunch,
    ftKb_MS_SpecialAirN_Dk_ChargeStart,
    ftKb_MS_SpecialAirN_Dk_ChargeLoop,
    ftKb_MS_SpecialAirN_Dk_ChargeStop,
    ftKb_MS_SpecialAirN_Dk_EarlyPunch,
    ftKb_MS_SpecialAirN_Dk_FullChargePunch,

    ftKb_MS_SpecialN_Zd,
    ftKb_MS_SpecialAirN_Zd,

    ftKb_MS_SpecialN_Sk_StartCharge,
    ftKb_MS_SpecialN_Sk_ChargeLoop,
    ftKb_MS_SpecialN_Sk_EndCharge,
    ftKb_MS_SpecialN_Sk_Fire,
    ftKb_MS_SpecialAirN_Sk_StartCharge,
    ftKb_MS_SpecialAirN_Sk_ChargeLoop,
    ftKb_MS_SpecialAirN_Sk_EndCharge,
    ftKb_MS_SpecialAirN_Sk_Fire,

    ftKb_MS_SpecialN_Pr_ChargeStartR,
    ftKb_MS_SpecialN_Pr_ChargeStartL,
    ftKb_MS_SpecialN_Pr_ChargeLoop,
    ftKb_MS_SpecialN_Pr_FullyCharged,
    ftKb_MS_SpecialN_Pr_ChargeRelease,
    ftKb_MS_SpecialN_Pr_TurnStart,
    ftKb_MS_SpecialN_Pr_EndR,
    ftKb_MS_SpecialN_Pr_EndL,
    ftKb_MS_SpecialAirN_Pr_ChargeStartR,
    ftKb_MS_SpecialAirN_Pr_ChargeStartL,
    ftKb_MS_SpecialAirN_Pr_ChargeLoop,
    ftKb_MS_SpecialAirN_Pr_FullyCharged,
    ftKb_MS_SpecialAirN_Pr_ChargeRelease,
    ftKb_MS_Unk_488,
    ftKb_MS_SpecialAirN_Pr_EndR,
    ftKb_MS_SpecialAirN_Pr_EndL,
    ftKb_MS_SpecialN_Pr_Hit,

    ftKb_MS_SpecialN_Ms_StartCharge,
    ftKb_MS_SpecialN_Ms_ChargeLoop,
    ftKb_MS_SpecialN_Ms_EarlyRelease,
    ftKb_MS_SpecialN_Ms_FullyCharged,
    ftKb_MS_SpecialAirN_Ms_StartCharge,
    ftKb_MS_SpecialAirN_Ms_ChargeLoop,
    ftKb_MS_SpecialAirN_Ms_EarlyRelease,
    ftKb_MS_SpecialAirN_Ms_FullyCharged,

    ftKb_MS_SpecialN_Mt_StartCharge,
    ftKb_MS_SpecialN_Mt_ChargeLoop,
    ftKb_MS_SpecialN_Mt_FullyCharged,
    ftKb_MS_SpecialN_Mt_EndCharge,
    ftKb_MS_SpecialN_Mt_Fire,
    ftKb_MS_SpecialAirN_Mt_StartCharge,
    ftKb_MS_SpecialAirN_Mt_ChargeLoop,
    ftKb_MS_SpecialAirN_Mt_FullyCharged,
    ftKb_MS_SpecialAirN_Mt_EndCharge,
    ftKb_MS_SpecialAirN_Mt_Fire,

    ftKb_MS_SpecialN_Gw,
    ftKb_MS_SpecialAirN_Gw,

    ftKb_MS_SpecialN_Dr,
    ftKb_MS_SpecialAirN_Dr,

    ftKb_MS_SpecialN_Cl_Charge,
    ftKb_MS_SpecialN_Cl_FullyCharged,
    ftKb_MS_SpecialN_Cl_Fire,
    ftKb_MS_SpecialAirN_Cl_Charge,
    ftKb_MS_SpecialAirN_Cl_FullyCharged,
    ftKb_MS_SpecialAirN_Cl_Fire,

    ftKb_MS_SpecialN_Fc_Start,
    ftKb_MS_SpecialN_Fc_Loop,
    ftKb_MS_SpecialN_Fc_End,
    ftKb_MS_SpecialAirN_Fc_Start,
    ftKb_MS_SpecialAirN_Fc_Loop,
    ftKb_MS_SpecialAirN_Fc_End,

    ftKb_MS_SpecialN_Pc,
    ftKb_MS_SpecialAirN_Pc,

    ftKb_MS_SpecialN_Gn,
    ftKb_MS_SpecialAirN_Gn,

    ftKb_MS_SpecialN_Fe_StartCharge,
    ftKb_MS_SpecialN_Fe_ChargeLoop,
    ftKb_MS_SpecialN_Fe_EarlyRelease,
    ftKb_MS_SpecialN_Fe_FullyCharged,
    ftKb_MS_SpecialAirN_Fe_StartCharge,
    ftKb_MS_SpecialAirN_Fe_ChargeLoop,
    ftKb_MS_SpecialAirN_Fe_EarlyRelease,
    ftKb_MS_SpecialAirN_Fe_FullyCharged,

    ftKb_MS_SpecialN_Gk_Start,
    ftKb_MS_SpecialN_Gk_Loop,
    ftKb_MS_SpecialN_Gk_End,
    ftKb_MS_SpecialAirN_Gk_Start,
    ftKb_MS_SpecialAirN_Gk_Loop,
    ftKb_MS_SpecialAirN_Gk_End,
} ftKirby_MotionState;

typedef enum ftKb_AnimId {
    ftKb_AnimId_MultiJump0 = ftCo_AnimId_Count,
    ftKb_AnimId_MultiJump1,
    ftKb_AnimId_MultiJump2,
    ftKb_AnimId_MultiJump3,
    ftKb_AnimId_MultiJump4,
    ftKb_AnimId_MultiJump5,
    ftKb_AnimId_MultiJump6,
    ftKb_AnimId_MultiJump7,
    ftKb_AnimId_MultiJump8,
    ftKb_AnimId_MultiJump9,
    ftKb_AnimId_SpecialNStart,
    ftKb_AnimId_SpecialNLoop,
    ftKb_AnimId_SpecialNEnd,
    ftKb_AnimId_SpecialNCapture,
    ftKb_AnimId_SpecialNCaptured,
    ftKb_AnimId_SpecialNCaptureWalk0,
    ftKb_AnimId_Unk311,
    ftKb_AnimId_SpecialNCaptureWalk1,
    ftKb_AnimId_SpecialNCaptureWalk2,
    ftKb_AnimId_SpecialNCaptureJumpSquat,
    ftKb_AnimId_SpecialNCaptureJump,
    ftKb_AnimId_SpecialNDigest,
    ftKb_AnimId_SpecialNCaptureTurn,
    ftKb_AnimId_SpecialAirNDigest,
    ftKb_AnimId_SpecialNSpit,
    ftKb_AnimId_SpecialAirNStart,
    ftKb_AnimId_SpecialAirNLoop,
    ftKb_AnimId_SpecialS,
    ftKb_AnimId_SpecialAirS,
    ftKb_AnimId_SpecialHiStart,
    ftKb_AnimId_MS_386,
    ftKb_AnimId_MS_387,
    ftKb_AnimId_SpecialHiEnd,
    ftKb_AnimId_SpecialAirHiStart,
    ftKb_AnimId_SpecialAirHiApex,
    ftKb_AnimId_SpecialHiSwordDescent,
    ftKb_AnimId_SpecialAirHiEnd,
    ftKb_AnimId_SpecialLwStart,
    ftKb_AnimId_SpecialLw,
    ftKb_AnimId_SpecialLwEnd,
    ftKb_AnimId_SpecialAirLwStart,
    ftKb_AnimId_SpecialAirLw,
    ftKb_AnimId_SpecialAirLwEnd,
    ftKb_AnimId_SpecialNMr,
    ftKb_AnimId_SpecialAirNMr,
    ftKb_AnimId_SpecialNLkCharge,
    ftKb_AnimId_SpecialNLkFullyCharged,
    ftKb_AnimId_SpecialNLkFire,
    ftKb_AnimId_SpecialAirNLkCharge,
    ftKb_AnimId_SpecialAirNLkFullyCharged,
    ftKb_AnimId_SpecialAirNLkFire,
    ftKb_AnimId_SpecialNSsStart,
    ftKb_AnimId_SpecialNSsLoop,
    ftKb_AnimId_SpecialNSsEnd,
    ftKb_AnimId_SpecialNSsFire,
    ftKb_AnimId_SpecialAirNSsStart,
    ftKb_AnimId_SpecialAirNSsFire,
    ftKb_AnimId_SpecialNYs,
    ftKb_AnimId_SpecialNYsCaptureStart,
    ftKb_AnimId_SpecialNYsCapture,
    ftKb_AnimId_SpecialAirNYs,
    ftKb_AnimId_SpecialAirNYsCaptureStart,
    ftKb_AnimId_SpecialAirNYsCapture,
    ftKb_AnimId_SpecialNFxStart,
    ftKb_AnimId_SpecialNFxLoop,
    ftKb_AnimId_SpecialNFxEnd,
    ftKb_AnimId_SpecialAirNFxStart,
    ftKb_AnimId_SpecialAirNFxLoop,
    ftKb_AnimId_SpecialAirNFxEnd,
    ftKb_AnimId_SpecialNPk,
    ftKb_AnimId_SpecialAirNPk,
    ftKb_AnimId_SpecialNLg,
    ftKb_AnimId_SpecialAirNLg,
    ftKb_AnimId_SpecialNCa,
    ftKb_AnimId_SpecialAirNCa,
    ftKb_AnimId_SpecialNNsStart,
    ftKb_AnimId_SpecialNNsCharge0,
    ftKb_AnimId_SpecialNNsCharge1,
    ftKb_AnimId_SpecialNNsEnd,
    ftKb_AnimId_SpecialAirNNsStart,
    ftKb_AnimId_SpecialAirNNsCharge0,
    ftKb_AnimId_SpecialAirNNsCharge1,
    ftKb_AnimId_SpecialAirNNsEnd,
    ftKb_AnimId_SpecialNKpStart,
    ftKb_AnimId_SpecialNKpLoop,
    ftKb_AnimId_SpecialNKpEnd,
    ftKb_AnimId_SpecialAirNKpStart,
    ftKb_AnimId_SpecialAirNKpLoop,
    ftKb_AnimId_SpecialAirNKpEnd,
    ftKb_AnimId_SpecialNPe,
    ftKb_AnimId_SpecialNPeAttack,
    ftKb_AnimId_SpecialAirNPe,
    ftKb_AnimId_SpecialAirNPeAttack,
    ftKb_AnimId_SpecialNPp,
    ftKb_AnimId_SpecialAirNPp,
    ftKb_AnimId_SpecialNDkChargeStart,
    ftKb_AnimId_SpecialNDkChargeLoop,
    ftKb_AnimId_SpecialNDkChargeStop,
    ftKb_AnimId_SpecialNDkEarlyPunch,
    ftKb_AnimId_SpecialNDkFullChargePunch,
    ftKb_AnimId_SpecialAirNDkChargeStart,
    ftKb_AnimId_SpecialAirNDkChargeLoop,
    ftKb_AnimId_SpecialAirNDkChargeStop,
    ftKb_AnimId_SpecialAirNDkEarlyPunch,
    ftKb_AnimId_SpecialAirNDkFullChargePunch,
    ftKb_AnimId_SpecialNZd,
    ftKb_AnimId_SpecialAirNZd,
    ftKb_AnimId_SpecialNSkStartCharge,
    ftKb_AnimId_SpecialNSkChargeLoop,
    ftKb_AnimId_SpecialNSkEndCharge,
    ftKb_AnimId_SpecialNSkFire,
    ftKb_AnimId_SpecialAirNSkStartCharge,
    ftKb_AnimId_SpecialAirNSkChargeLoop,
    ftKb_AnimId_SpecialAirNSkEndCharge,
    ftKb_AnimId_SpecialAirNSkFire,
    ftKb_AnimId_SpecialNPrChargeStart0,
    ftKb_AnimId_SpecialNPrChargeStart1,
    ftKb_AnimId_SpecialNPrChargeLoop,
    ftKb_AnimId_SpecialNPrFullyCharged,
    ftKb_AnimId_SpecialNPrChargeRelease,
    ftKb_AnimId_SpecialNPrTurnStart,
    ftKb_AnimId_SpecialNPrEnd0,
    ftKb_AnimId_SpecialNPrEnd1,
    ftKb_AnimId_SpecialAirNPrChargeStart0,
    ftKb_AnimId_SpecialAirNPrChargeStart1,
    ftKb_AnimId_SpecialAirNPrChargeLoop,
    ftKb_AnimId_SpecialAirNPrFullyCharged,
    ftKb_AnimId_SpecialAirNPrChargeRelease,
    ftKb_AnimId_MS_488,
    ftKb_AnimId_SpecialAirNPrEnd0,
    ftKb_AnimId_SpecialAirNPrEnd1,
    ftKb_AnimId_SpecialNPrHit,
    ftKb_AnimId_SpecialNMsStartCharge,
    ftKb_AnimId_SpecialNMsChargeLoop,
    ftKb_AnimId_SpecialNMs0,
    ftKb_AnimId_SpecialNMs1,
    ftKb_AnimId_SpecialAirNMsStartCharge,
    ftKb_AnimId_SpecialAirNMsChargeLoop,
    ftKb_AnimId_SpecialAirNMs0,
    ftKb_AnimId_SpecialAirNMs1,
    ftKb_AnimId_SpecialNMtStartCharge,
    ftKb_AnimId_SpecialNMtChargeLoop,
    ftKb_AnimId_SpecialNMtFullyCharged,
    ftKb_AnimId_SpecialNMtEndCharge,
    ftKb_AnimId_SpecialNMtFire,
    ftKb_AnimId_SpecialAirNMtStartCharge,
    ftKb_AnimId_SpecialAirNMtChargeLoop,
    ftKb_AnimId_SpecialAirNMtFullyCharged,
    ftKb_AnimId_SpecialAirNMtEndCharge,
    ftKb_AnimId_SpecialAirNMtFire,
    ftKb_AnimId_SpecialNGw,
    ftKb_AnimId_SpecialAirNGw,
    ftKb_AnimId_SpecialNDr,
    ftKb_AnimId_SpecialAirNDr,
    ftKb_AnimId_SpecialNClCharge,
    ftKb_AnimId_SpecialNClFullyCharged,
    ftKb_AnimId_SpecialNClFire,
    ftKb_AnimId_SpecialAirNClCharge,
    ftKb_AnimId_SpecialAirNClFullyCharged,
    ftKb_AnimId_SpecialAirNClFire,
    ftKb_AnimId_SpecialNFcStart,
    ftKb_AnimId_SpecialNFcLoop,
    ftKb_AnimId_SpecialNFcEnd,
    ftKb_AnimId_SpecialAirNFcStart,
    ftKb_AnimId_SpecialAirNFcLoop,
    ftKb_AnimId_SpecialAirNFcEnd,
    ftKb_AnimId_SpecialNPc,
    ftKb_AnimId_SpecialAirNPc,
    ftKb_AnimId_SpecialNGn,
    ftKb_AnimId_SpecialAirNGn,
    ftKb_AnimId_SpecialNFeStartCharge,
    ftKb_AnimId_SpecialNFeChargeLoop,
    ftKb_AnimId_SpecialNFe0,
    ftKb_AnimId_SpecialNFe1,
    ftKb_AnimId_SpecialAirNFeStartCharge,
    ftKb_AnimId_SpecialAirNFeChargeLoop,
    ftKb_AnimId_SpecialAirNFe0,
    ftKb_AnimId_SpecialAirNFe1,
    ftKb_AnimId_SpecialNGkStart,
    ftKb_AnimId_SpecialNGkLoop,
    ftKb_AnimId_SpecialNGkEnd,
    ftKb_AnimId_SpecialAirNGkStart,
    ftKb_AnimId_SpecialAirNGkLoop,
    ftKb_AnimId_SpecialAirNGkEnd,
} ftKb_AnimId;

#endif
