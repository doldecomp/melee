#ifndef MELEE_FT_CHARA_FTCOMMON_FORWARD_H
#define MELEE_FT_CHARA_FTCOMMON_FORWARD_H

#include <platform.h>

#include "ft/forward.h"

typedef struct ftHurtboxInit ftHurtboxInit;
typedef struct ftCollisionBox ftCollisionBox;

typedef enum ftCo_JumpInput {
    JumpInput_None,
    JumpInput_LStick,
    JumpInput_CStick,
    JumpInput_XY,
} ftCo_JumpInput;

static MotionFlags const ftCo_MF_5_6 = Ft_MF_SkipAnimVel | Ft_MF_Unk06;
static MotionFlags const ftCo_MF_2_5_6 =
    ftCo_MF_5_6 | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_Squat = ftCo_MF_2_5_6 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_Dash = ftCo_MF_Squat | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_Run = ftCo_MF_5_6 | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_Appeal =
    ftCo_MF_5_6 | Ft_MF_KeepFastFall | Ft_MF_SkipModel;
static MotionFlags const ftCo_MF_9_10 = Ft_MF_KeepSfx | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_LandingAirN =
    ftCo_MF_9_10 | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_LandingAirF =
    ftCo_MF_LandingAirN | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_LandingAirB =
    ftCo_MF_LandingAirN | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_LandingAirHi =
    ftCo_MF_LandingAirB | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_LandingAirLw = ftCo_MF_9_10 | Ft_MF_SkipModel;
static MotionFlags const ftCo_MF_Turn = ftCo_MF_2_5_6 | Ft_MF_KeepAccessory;
static MotionFlags const ftCo_MF_Walk =
    ftCo_MF_2_5_6 | Ft_MF_KeepGfx | Ft_MF_UpdateCmd;
static MotionFlags const ftCo_MF_3_5_6 = ftCo_MF_5_6 | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_Jump =
    ftCo_MF_3_5_6 | Ft_MF_KeepFastFall | Ft_MF_SkipNametagVis;
static MotionFlags const ftCo_MF_JumpAir =
    ftCo_MF_3_5_6 | Ft_MF_KeepGfx | Ft_MF_KeepColAnimPartHitStatus;
static MotionFlags const ftCo_MF_GuardReflect =
    ftCo_MF_5_6 | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipModel |
    Ft_MF_SkipColAnim | Ft_MF_UnkUpdatePhys;
static MotionFlags const ftCo_MF_Guard = Ft_MF_Unk19 | Ft_MF_UnkUpdatePhys;
static MotionFlags const ftCo_MF_AttackBase =
    Ft_MF_KeepSfx | Ft_MF_SkipItemVis;
static MotionFlags const ftCo_MF_Attack =
    ftCo_MF_AttackBase | Ft_MF_FreezeState;
static MotionFlags const ftCo_MF_Attack_2 =
    ftCo_MF_Attack | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_AttackDash =
    ftCo_MF_Attack_2 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_AttackS3 = ftCo_MF_Attack_2 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_AttackHi3 =
    ftCo_MF_AttackS3 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_AttackLw3 = ftCo_MF_Attack | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_CliffAttackQuick =
    ftCo_MF_AttackLw3 | Ft_MF_KeepFastFall | Ft_MF_KeepGfx |
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipModel | Ft_MF_SkipAnimVel;
static MotionFlags const ftCo_MF_AttackAir =
    ftCo_MF_Attack | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_AttackAirN =
    ftCo_MF_AttackAir | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit |
    Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_AttackAirF =
    ftCo_MF_AttackAirN | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_AttackAirB =
    ftCo_MF_AttackAirN | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_AttackAirHi =
    ftCo_MF_AttackAirF | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_AttackAirLw =
    ftCo_MF_AttackAir | Ft_MF_SkipModel;
static MotionFlags const ftCo_MF_Attack4 =
    ftCo_MF_AttackLw3 | Ft_MF_SkipRumble;
static MotionFlags const ftCo_MF_AttackS4 =
    ftCo_MF_Attack4 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_AttackHi4 = ftCo_MF_Attack4 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_AttackLw4 =
    ftCo_MF_Attack4 | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_Attack1 = ftCo_MF_Attack | Ft_MF_Unk19;
static MotionFlags const ftCo_MF_Attack11 =
    ftCo_MF_Attack1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_Attack12 = ftCo_MF_Attack1 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_Attack13 =
    ftCo_MF_Attack12 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_Attack100 =
    ftCo_MF_Attack1 | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_ItemScope =
    Ft_MF_SkipItemVis | Ft_MF_SkipModelPartVis;
static MotionFlags const ftCo_MF_SwordSwing1 = ftCo_MF_ItemScope | Ft_MF_Unk06;
static MotionFlags const ftCo_MF_SwordSwing3 =
    ftCo_MF_SwordSwing1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_SwordSwingDash =
    ftCo_MF_SwordSwing3 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_BatSwing1 =
    ftCo_MF_SwordSwing1 | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_BatSwing3 =
    ftCo_MF_BatSwing1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_BatSwingDash =
    ftCo_MF_BatSwing3 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_ParasolSwing1 =
    ftCo_MF_SwordSwing1 | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_ParasolSwing3 =
    ftCo_MF_ParasolSwing1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_ParasolSwingDash =
    ftCo_MF_ParasolSwing3 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_HarisenSwing1 =
    ftCo_MF_BatSwing1 | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_HarisenSwing3 =
    ftCo_MF_HarisenSwing1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_HarisenSwingDash =
    ftCo_MF_HarisenSwing3 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_StarRodSwing1 =
    ftCo_MF_SwordSwing1 | Ft_MF_SkipModel;
static MotionFlags const ftCo_MF_StarRodSwing3 =
    ftCo_MF_StarRodSwing1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_StarRodSwingDash =
    ftCo_MF_StarRodSwing3 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_LipstickSwing1 =
    ftCo_MF_StarRodSwing1 | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_LipstickSwing3 =
    ftCo_MF_LipstickSwing1 | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_LipstickSwingDash =
    ftCo_MF_LipstickSwing3 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_ParasolOpen =
    ftCo_MF_ParasolSwing1 | Ft_MF_SkipModel;
static MotionFlags const ftCo_MF_HammerBase =
    ftCo_MF_LipstickSwing1 | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_Hammer = ftCo_MF_HammerBase | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_WarpStarFall =
    ftCo_MF_Hammer | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_ItemScope_5_6 =
    ftCo_MF_5_6 | ftCo_MF_ItemScope;
static MotionFlags const ftCo_MF_ItemThrow =
    ftCo_MF_ItemScope_5_6 | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_LGunShoot =
    ftCo_MF_ItemScope | Ft_MF_KeepFastFall | Ft_MF_SkipHit | Ft_MF_SkipModel |
    Ft_MF_Unk06 | Ft_MF_SkipThrowException;
static MotionFlags const ftCo_MF_ItemScopeFire =
    ftCo_MF_LGunShoot | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_HammerFall =
    ftCo_MF_Hammer | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_ItemThrowAir =
    ftCo_MF_ItemThrow | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_LGunShootAir =
    ftCo_MF_LGunShoot | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_ItemScopeAir =
    ftCo_MF_HammerBase | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException |
    Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_Swing4 = Ft_MF_KeepGfx | Ft_MF_SkipRumble;
static MotionFlags const ftCo_MF_SwordSwing4 =
    ftCo_MF_SwordSwing1 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_BatSwing4 =
    ftCo_MF_BatSwing1 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_ParasolSwing4 =
    ftCo_MF_ParasolSwing1 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_HarisenSwing4 =
    ftCo_MF_HarisenSwing1 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_StarRodSwing4 =
    ftCo_MF_StarRodSwing1 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_LipstickSwing4 =
    ftCo_MF_LipstickSwing1 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_ItemThrow4 =
    ftCo_MF_ItemScope_5_6 | ftCo_MF_Swing4;
static MotionFlags const ftCo_MF_ItemThrowAir4 =
    ftCo_MF_ItemThrow4 | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_HammerMove =
    ftCo_MF_HammerBase | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_HammerTurn =
    ftCo_MF_HammerMove | Ft_MF_KeepAccessory;
static MotionFlags const ftCo_MF_HammerWalk =
    ftCo_MF_HammerMove | Ft_MF_UpdateCmd;
static MotionFlags const ftCo_MF_ItemFall =
    Ft_MF_SkipHit | Ft_MF_SkipModel | Ft_MF_Unk06 | Ft_MF_SkipModelPartVis;
static MotionFlags const ftCo_MF_ItemScrewBase =
    ftCo_MF_AttackBase | ftCo_MF_ItemFall | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_ItemScrew =
    ftCo_MF_ItemScrewBase | Ft_MF_SkipNametagVis;
static MotionFlags const ftCo_MF_HammerJump =
    ftCo_MF_HammerMove | Ft_MF_SkipParasol | Ft_MF_SkipNametagVis;
static MotionFlags const ftCo_MF_ItemScrewAir =
    ftCo_MF_ItemScrewBase | Ft_MF_SkipParasol | Ft_MF_KeepColAnimPartHitStatus;
static MotionFlags const ftCo_MF_LiftWait =
    Ft_MF_Unk19 | Ft_MF_SkipModelPartVis;
static MotionFlags const ftCo_MF_LiftMove = ftCo_MF_LiftWait |
                                            Ft_MF_KeepColAnimHitStatus |
                                            Ft_MF_SkipAnimVel | Ft_MF_Unk06;
static MotionFlags const ftCo_MF_LiftTurn =
    ftCo_MF_LiftMove | Ft_MF_KeepAccessory;
static MotionFlags const ftCo_MF_LiftWalk =
    ftCo_MF_LiftMove | Ft_MF_KeepGfx | Ft_MF_UpdateCmd;
static MotionFlags const ftCo_MF_ParasolFall =
    ftCo_MF_ItemFall | Ft_MF_SkipItemVis | Ft_MF_Unk19;
static MotionFlags const ftCo_MF_FireFlowerShoot =
    ftCo_MF_ParasolFall | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;
static MotionFlags const ftCo_MF_ItemScopeRapid =
    ftCo_MF_ParasolFall | Ft_MF_KeepColAnimHitStatus |
    Ft_MF_SkipThrowException | Ft_MF_Unk19;
static MotionFlags const ftCo_MF_FireFlowerShootAir =
    ftCo_MF_FireFlowerShoot | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_ItemScopeAirRapid =
    ftCo_MF_ItemScopeRapid | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_Dazed =
    Ft_MF_UnkUpdatePhys | Ft_MF_SkipModelPartVis;
static MotionFlags const ftCo_MF_Damage = ftCo_MF_Dazed | Ft_MF_KeepSwordTrail;
static MotionFlags const ftCo_MF_DamageScrew =
    ftCo_MF_Damage | Ft_MF_SkipNametagVis;
static MotionFlags const ftCo_MF_DamageScrewAir =
    ftCo_MF_Damage | Ft_MF_KeepColAnimPartHitStatus;
static MotionFlags const ftCo_MF_Down = Ft_MF_SkipHit | Ft_MF_SkipAnimVel |
                                        Ft_MF_Unk06 | Ft_MF_FreezeState |
                                        Ft_MF_SkipModelPartVis;
static MotionFlags const ftCo_MF_DownU =
    ftCo_MF_Down | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_DownD = ftCo_MF_DownU | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_DownDamageU =
    ftCo_MF_DownU | Ft_MF_KeepSwordTrail;
static MotionFlags const ftCo_MF_DownDamageD =
    ftCo_MF_DownD | Ft_MF_KeepSwordTrail;
static MotionFlags const ftCo_MF_DownAttack =
    ftCo_MF_Attack | Ft_MF_SkipModel | Ft_MF_SkipAnimVel |
    Ft_MF_SkipModelPartVis;
static MotionFlags const ftCo_MF_DownAttackU =
    ftCo_MF_DownAttack | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_DownAttackD =
    ftCo_MF_DownAttack | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_PassiveWall =
    ftCo_MF_Dazed | Ft_MF_FreezeState;
static MotionFlags const ftCo_MF_Passive = ftCo_MF_Down | Ft_MF_KeepGfx |
                                           Ft_MF_KeepColAnimHitStatus |
                                           Ft_MF_UnkUpdatePhys;
static MotionFlags const ftCo_MF_StopWall =
    Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipAnimVel |
    Ft_MF_Unk06 | Ft_MF_SkipMetalB;
static MotionFlags const ftCo_MF_Pass =
    ftCo_MF_StopWall | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_OttottoWait = Ft_MF_Unk19 | Ft_MF_SkipMetalB;
static MotionFlags const ftCo_MF_CliffAction =
    Ft_MF_UnkUpdatePhys | Ft_MF_SkipMetalB;
static MotionFlags const ftCo_MF_CliffAction_4_5 =
    ftCo_MF_CliffAction | Ft_MF_SkipModel | Ft_MF_SkipAnimVel;
static MotionFlags const ftCo_MF_CliffCatch =
    ftCo_MF_CliffAction_4_5 | Ft_MF_Unk06;
static MotionFlags const ftCo_MF_CliffAttackSlow =
    ftCo_MF_AttackBase | ftCo_MF_CliffAction_4_5 | Ft_MF_KeepGfx |
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_CliffWait = ftCo_MF_CliffAction | Ft_MF_Unk19;
static MotionFlags const ftCo_MF_CatchWait =
    Ft_MF_FreezeState | Ft_MF_SkipMetalB;
static MotionFlags const ftCo_MF_CatchBase =
    ftCo_MF_CatchWait | Ft_MF_SkipModel | Ft_MF_SkipAnimVel;
static MotionFlags const ftCo_MF_Catch =
    ftCo_MF_CatchBase | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_Throw = ftCo_MF_CatchBase | Ft_MF_SkipItemVis;
static MotionFlags const ftCo_MF_CatchAttack =
    ftCo_MF_Throw | Ft_MF_KeepColAnimHitStatus;
static MotionFlags const ftCo_MF_ThrowF =
    ftCo_MF_CatchAttack | Ft_MF_KeepFastFall;
static MotionFlags const ftCo_MF_ThrowB = ftCo_MF_CatchAttack | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_ThrowHi = ftCo_MF_ThrowF | Ft_MF_KeepGfx;
static MotionFlags const ftCo_MF_ThrowLw = ftCo_MF_Throw | Ft_MF_SkipHit;
static MotionFlags const ftCo_MF_Capture =
    ftCo_MF_CatchWait | Ft_MF_UnkUpdatePhys;
static MotionFlags const ftCo_MF_CaptureAir =
    ftCo_MF_Capture | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_Thrown =
    ftCo_MF_Capture | Ft_MF_KeepSwordTrail;
static MotionFlags const ftCo_MF_ThrownAir =
    ftCo_MF_Thrown | Ft_MF_SkipParasol;
static MotionFlags const ftCo_MF_Shouldered = ftCo_MF_Capture | Ft_MF_Unk19;
static MotionFlags const ftCo_MF_Rebirth =
    Ft_MF_SkipModelPartVis | Ft_MF_SkipMetalB;
static MotionFlags const ftCo_MF_ThrownStar =
    ftCo_MF_Rebirth | Ft_MF_KeepSwordTrail;
static MotionFlags const ftCo_MF_Dead = ftCo_MF_Dazed | Ft_MF_SkipMetalB;
static MotionFlags const ftCo_MF_Sleep = ftCo_MF_Dead | Ft_MF_KeepSwordTrail;
static MotionFlags const ftCo_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

typedef enum ftCommon_MotionState {
    ftCo_MS_None = -1,
    ftCo_MS_DeadDown,
    ftCo_MS_DeadLeft,
    ftCo_MS_DeadRight,
    ftCo_MS_DeadUp,
    ftCo_MS_DeadUpStar,
    ftCo_MS_DeadUpStarIce,
    ftCo_MS_DeadUpFall,
    ftCo_MS_DeadUpFallHitCamera,
    ftCo_MS_DeadUpFallHitCameraFlat,
    ftCo_MS_DeadUpFallIce,
    ftCo_MS_DeadUpFallHitCameraIce,
    ftCo_MS_Sleep,
    ftCo_MS_Rebirth,
    ftCo_MS_RebirthWait,
    ftCo_MS_Wait,
    ftCo_MS_WalkSlow,
    ftCo_MS_WalkMiddle,
    ftCo_MS_WalkFast,
    ftCo_MS_Turn,
    ftCo_MS_TurnRun,
    ftCo_MS_Dash,
    ftCo_MS_Run,
    ftCo_MS_RunDirect,
    ftCo_MS_RunBrake,
    ftCo_MS_KneeBend,
    ftCo_MS_JumpF,
    ftCo_MS_JumpB,
    ftCo_MS_JumpAerialF,
    ftCo_MS_JumpAerialB,
    ftCo_MS_Fall,
    ftCo_MS_FallF,
    ftCo_MS_FallB,
    ftCo_MS_FallAerial,
    ftCo_MS_FallAerialF,
    ftCo_MS_FallAerialB,
    ftCo_MS_FallSpecial,
    ftCo_MS_FallSpecialF,
    ftCo_MS_FallSpecialB,
    ftCo_MS_DamageFall,
    ftCo_MS_Squat,
    ftCo_MS_SquatWait,
    ftCo_MS_SquatRv,
    ftCo_MS_Landing,
    ftCo_MS_LandingFallSpecial,
    ftCo_MS_Attack11,
    ftCo_MS_Attack12,
    ftCo_MS_Attack13,
    ftCo_MS_Attack100Start,
    ftCo_MS_Attack100Loop,
    ftCo_MS_Attack100End,
    ftCo_MS_AttackDash,
    ftCo_MS_AttackS3Hi,
    ftCo_MS_AttackS3HiS,
    ftCo_MS_AttackS3S,
    ftCo_MS_AttackS3LwS,
    ftCo_MS_AttackS3Lw,
    ftCo_MS_AttackHi3,
    ftCo_MS_AttackLw3,
    ftCo_MS_AttackS4Hi,
    ftCo_MS_AttackS4HiS,
    ftCo_MS_AttackS4S,
    ftCo_MS_AttackS4LwS,
    ftCo_MS_AttackS4Lw,
    ftCo_MS_AttackHi4,
    ftCo_MS_AttackLw4,
    ftCo_MS_AttackAirN,
    ftCo_MS_AttackAirF,
    ftCo_MS_AttackAirB,
    ftCo_MS_AttackAirHi,
    ftCo_MS_AttackAirLw,
    ftCo_MS_LandingAirN,
    ftCo_MS_LandingAirF,
    ftCo_MS_LandingAirB,
    ftCo_MS_LandingAirHi,
    ftCo_MS_LandingAirLw,
    ftCo_MS_DamageHi1,
    ftCo_MS_DamageHi2,
    ftCo_MS_DamageHi3,
    ftCo_MS_DamageN1,
    ftCo_MS_DamageN2,
    ftCo_MS_DamageN3,
    ftCo_MS_DamageLw1,
    ftCo_MS_DamageLw2,
    ftCo_MS_DamageLw3,
    ftCo_MS_DamageAir1,
    ftCo_MS_DamageAir2,
    ftCo_MS_DamageAir3,
    ftCo_MS_DamageFlyHi,
    ftCo_MS_DamageFlyN,
    ftCo_MS_DamageFlyLw,
    ftCo_MS_DamageFlyTop,
    ftCo_MS_DamageFlyRoll,
    ftCo_MS_LightGet,
    ftCo_MS_HeavyGet,
    ftCo_MS_LightThrowF,
    ftCo_MS_LightThrowB,
    ftCo_MS_LightThrowHi,
    ftCo_MS_LightThrowLw,
    ftCo_MS_LightThrowDash,
    ftCo_MS_LightThrowDrop,
    ftCo_MS_LightThrowAirF,
    ftCo_MS_LightThrowAirB,
    ftCo_MS_LightThrowAirHi,
    ftCo_MS_LightThrowAirLw,
    ftCo_MS_HeavyThrowF,
    ftCo_MS_HeavyThrowB,
    ftCo_MS_HeavyThrowHi,
    ftCo_MS_HeavyThrowLw,
    ftCo_MS_LightThrowF4,
    ftCo_MS_LightThrowB4,
    ftCo_MS_LightThrowHi4,
    ftCo_MS_LightThrowLw4,
    ftCo_MS_LightThrowAirF4,
    ftCo_MS_LightThrowAirB4,
    ftCo_MS_LightThrowAirHi4,
    ftCo_MS_LightThrowAirLw4,
    ftCo_MS_HeavyThrowF4,
    ftCo_MS_HeavyThrowB4,
    ftCo_MS_HeavyThrowHi4,
    ftCo_MS_HeavyThrowLw4,
    ftCo_MS_SwordSwing1,
    ftCo_MS_SwordSwing3,
    ftCo_MS_SwordSwing4,
    ftCo_MS_SwordSwingDash,
    ftCo_MS_BatSwing1,
    ftCo_MS_BatSwing3,
    ftCo_MS_BatSwing4,
    ftCo_MS_BatSwingDash,
    ftCo_MS_ParasolSwing1,
    ftCo_MS_ParasolSwing3,
    ftCo_MS_ParasolSwing4,
    ftCo_MS_ParasolSwingDash,
    ftCo_MS_HarisenSwing1,
    ftCo_MS_HarisenSwing3,
    ftCo_MS_HarisenSwing4,
    ftCo_MS_HarisenSwingDash,
    ftCo_MS_StarRodSwing1,
    ftCo_MS_StarRodSwing3,
    ftCo_MS_StarRodSwing4,
    ftCo_MS_StarRodSwingDash,
    ftCo_MS_LipstickSwing1,
    ftCo_MS_LipstickSwing3,
    ftCo_MS_LipstickSwing4,
    ftCo_MS_LipstickSwingDash,
    ftCo_MS_ItemParasolOpen,
    ftCo_MS_ItemParasolFall,
    ftCo_MS_ItemParasolFallSpecial,
    ftCo_MS_ItemParasolDamageFall,
    ftCo_MS_LGunShoot,
    ftCo_MS_LGunShootAir,
    ftCo_MS_LGunShootEmpty,
    ftCo_MS_LGunShootAirEmpty,
    ftCo_MS_FireFlowerShoot,
    ftCo_MS_FireFlowerShootAir,
    ftCo_MS_ItemScrew,
    ftCo_MS_ItemScrewAir,
    ftCo_MS_DamageScrew,
    ftCo_MS_DamageScrewAir,
    ftCo_MS_ItemScopeStart,
    ftCo_MS_ItemScopeRapid,
    ftCo_MS_ItemScopeFire,
    ftCo_MS_ItemScopeEnd,
    ftCo_MS_ItemScopeAirStart,
    ftCo_MS_ItemScopeAirRapid,
    ftCo_MS_ItemScopeAirFire,
    ftCo_MS_ItemScopeAirEnd,
    ftCo_MS_ItemScopeStartEmpty,
    ftCo_MS_ItemScopeRapidEmpty,
    ftCo_MS_ItemScopeFireEmpty,
    ftCo_MS_ItemScopeEndEmpty,
    ftCo_MS_ItemScopeAirStartEmpty,
    ftCo_MS_ItemScopeAirRapidEmpty,
    ftCo_MS_ItemScopeAirFireEmpty,
    ftCo_MS_ItemScopeAirEndEmpty,
    ftCo_MS_LiftWait,
    ftCo_MS_LiftWalk1,
    ftCo_MS_LiftWalk2,
    ftCo_MS_LiftTurn,
    ftCo_MS_GuardOn,
    ftCo_MS_Guard,
    ftCo_MS_GuardOff,
    ftCo_MS_GuardSetOff,
    ftCo_MS_GuardReflect,
    ftCo_MS_DownBoundU,
    ftCo_MS_DownWaitU,
    ftCo_MS_DownDamageU,
    ftCo_MS_DownStandU,
    ftCo_MS_DownAttackU,
    ftCo_MS_DownFowardU,
    ftCo_MS_DownBackU,
    ftCo_MS_DownSpotU,
    ftCo_MS_DownBoundD,
    ftCo_MS_DownWaitD,
    ftCo_MS_DownDamageD,
    ftCo_MS_DownStandD,
    ftCo_MS_DownAttackD,
    ftCo_MS_DownFowardD,
    ftCo_MS_DownBackD,
    ftCo_MS_DownSpotD,
    ftCo_MS_Passive,
    ftCo_MS_PassiveStandF,
    ftCo_MS_PassiveStandB,
    ftCo_MS_PassiveWall,
    ftCo_MS_PassiveWallJump,
    ftCo_MS_PassiveCeil,
    ftCo_MS_ShieldBreakFly,
    ftCo_MS_ShieldBreakFall,
    ftCo_MS_ShieldBreakDownU,
    ftCo_MS_ShieldBreakDownD,
    ftCo_MS_ShieldBreakStandU,
    ftCo_MS_ShieldBreakStandD,
    ftCo_MS_Furafura, ///< Dazed
    ftCo_MS_Catch,
    ftCo_MS_CatchPull,
    ftCo_MS_CatchDash,
    ftCo_MS_CatchDashPull,
    ftCo_MS_CatchWait,
    ftCo_MS_CatchAttack,
    ftCo_MS_CatchCut,
    ftCo_MS_ThrowF,
    ftCo_MS_ThrowB,
    ftCo_MS_ThrowHi,
    ftCo_MS_ThrowLw,
    ftCo_MS_CapturePulledHi,
    ftCo_MS_CaptureWaitHi,
    ftCo_MS_CaptureDamageHi,
    ftCo_MS_CapturePulledLw,
    ftCo_MS_CaptureWaitLw,
    ftCo_MS_CaptureDamageLw,
    ftCo_MS_CaptureCut,
    ftCo_MS_CaptureJump,
    ftCo_MS_CaptureNeck,
    ftCo_MS_CaptureFoot,
    ftCo_MS_EscapeF,
    ftCo_MS_EscapeB,
    ftCo_MS_EscapeN,
    ftCo_MS_EscapeAir,
    ftCo_MS_ReboundStop,
    ftCo_MS_Rebound,
    ftCo_MS_ThrownF,
    ftCo_MS_ThrownB,
    ftCo_MS_ThrownHi,
    ftCo_MS_ThrownLw,
    ftCo_MS_ThrownlwWomen,
    ftCo_MS_Pass,
    ftCo_MS_Ottotto,     ///< teeter
    ftCo_MS_OttottoWait, ///< teeter wait
    ftCo_MS_FlyReflectWall,
    ftCo_MS_FlyReflectCeil,
    ftCo_MS_StopWall,
    ftCo_MS_StopCeil,
    ftCo_MS_MissFoot,
    ftCo_MS_CliffCatch,
    ftCo_MS_CliffWait,
    ftCo_MS_CliffClimbSlow,
    ftCo_MS_CliffClimbQuick,
    ftCo_MS_CliffAttackSlow,
    ftCo_MS_CliffAttackQuick,
    ftCo_MS_CliffEscapeSlow,
    ftCo_MS_CliffEscapeQuick,
    ftCo_MS_CliffJumpSlow1,
    ftCo_MS_CliffJumpSlow2,
    ftCo_MS_CliffJumpQuick1,
    ftCo_MS_CliffJumpQuick2,
    ftCo_MS_AppealSR,
    ftCo_MS_AppealSL,
    ftCo_MS_ShoulderedWait,
    ftCo_MS_ShoulderedWalkSlow,
    ftCo_MS_ShoulderedWalkMiddle,
    ftCo_MS_ShoulderedWalkFast,
    ftCo_MS_ShoulderedTurn,
    ftCo_MS_ThrownFF,
    ftCo_MS_ThrownFB,
    ftCo_MS_ThrownFHi,
    ftCo_MS_ThrownFLw,
    ftCo_MS_CaptureCaptain,
    ftCo_MS_CaptureYoshi,
    ftCo_MS_YoshiEgg,
    ftCo_MS_CaptureKoopa,
    ftCo_MS_CaptureDamageKoopa,
    ftCo_MS_CaptureWaitKoopa,
    ftCo_MS_ThrownKoopaF,
    ftCo_MS_ThrownKoopaB,
    ftCo_MS_CaptureKoopaAir,
    ftCo_MS_CaptureDamageKoopaAir,
    ftCo_MS_CaptureWaitKoopaAir,
    ftCo_MS_ThrownKoopaAirF,
    ftCo_MS_ThrownKoopaAirB,
    ftCo_MS_CaptureKirby,
    ftCo_MS_CaptureWaitKirby,
    ftCo_MS_ThrownKirbyStar,
    ftCo_MS_ThrownCopyStar,
    ftCo_MS_ThrownKirby,
    ftCo_MS_BarrelWait,
    ftCo_MS_Bury,
    ftCo_MS_BuryWait,
    ftCo_MS_BuryJump,
    ftCo_MS_DamageSong,
    ftCo_MS_DamageSongWait,
    ftCo_MS_DamageSongRv,
    ftCo_MS_DamageBind,
    ftCo_MS_CaptureMewtwo,
    ftCo_MS_CaptureMewtwoAir,
    ftCo_MS_ThrownMewtwo,
    ftCo_MS_ThrownMewtwoAir,
    ftCo_MS_WarpStarJump,
    ftCo_MS_WarpStarFall,
    ftCo_MS_HammerWait,
    ftCo_MS_HammerWalk,
    ftCo_MS_HammerTurn,
    ftCo_MS_HammerKneeBend,
    ftCo_MS_HammerFall,
    ftCo_MS_HammerJump,
    ftCo_MS_HammerLanding,
    ftCo_MS_KinokoGiantStart,
    ftCo_MS_KinokoGiantStartAir,
    ftCo_MS_KinokoGiantEnd,
    ftCo_MS_KinokoGiantEndAir,
    ftCo_MS_KinokoSmallStart,
    ftCo_MS_KinokoSmallStartAir,
    ftCo_MS_KinokoSmallEnd,
    ftCo_MS_KinokoSmallEndAir,
    ftCo_MS_Entry,
    ftCo_MS_EntryStart,
    ftCo_MS_EntryEnd,
    ftCo_MS_DamageIce,
    ftCo_MS_DamageIceJump,
    ftCo_MS_CaptureMasterHand,
    ftCo_MS_CaptureDamageMasterHand,
    ftCo_MS_CaptureWaitMasterHand,
    ftCo_MS_ThrownMasterHand,
    ftCo_MS_CaptureKirbyYoshi,
    ftCo_MS_KirbyYoshiEgg,
    ftCo_MS_CaptureLeadead,
    ftCo_MS_CaptureLikelike,
    ftCo_MS_DownReflect,
    ftCo_MS_CaptureCrazyHand,
    ftCo_MS_CaptureDamageCrazyHand,
    ftCo_MS_CaptureWaitCrazyHand,
    ftCo_MS_ThrownCrazyHand,
    ftCo_MS_Barrel,
    ftCo_MS_Count
} ftCommon_MotionState;

typedef enum ftCo_Submotion {
    ftCo_SM_None = -1,
    ftCo_SM_DeadUpFallHitCamera,
    ftCo_SM_DeadUpFallHitCameraFlat,
    ftCo_SM_Wait1_0,
    ftCo_SM_Wait2,
    ftCo_SM_Unk004,
    ftCo_SM_Unk005,
    ftCo_SM_Wait1_1,
    ftCo_SM_WalkSlow,
    ftCo_SM_WalkMiddle,
    ftCo_SM_WalkFast,
    ftCo_SM_Turn,
    ftCo_SM_TurnRun,
    ftCo_SM_Dash,
    ftCo_SM_Run,
    ftCo_SM_RunBrake,
    ftCo_SM_Kneebend,
    ftCo_SM_JumpF,
    ftCo_SM_JumpB,
    ftCo_SM_JumpAerialF,
    ftCo_SM_JumpAerialB,
    ftCo_SM_Fall,
    ftCo_SM_FallF,
    ftCo_SM_FallB,
    ftCo_SM_FallAerial,
    ftCo_SM_FallAerialF,
    ftCo_SM_FallAerialB,
    ftCo_SM_FallSpecial,
    ftCo_SM_FallSpecialF,
    ftCo_SM_FallSpecialB,
    ftCo_SM_DamageFall,
    ftCo_SM_Squat,
    ftCo_SM_SquatWait,
    ftCo_SM_Unk032,
    ftCo_SM_SquatWaitItem,
    ftCo_SM_SquatRv,
    ftCo_SM_Landing,
    ftCo_SM_LandingFallSpecial,
    ftCo_SM_GuardOn,
    ftCo_SM_Guard,
    ftCo_SM_GuardOff,
    ftCo_SM_GuardDamage,
    ftCo_SM_EscapeN,
    ftCo_SM_EscapeF,
    ftCo_SM_EscapeB,
    ftCo_SM_EscapeAir,
    ftCo_SM_Rebound,
    ftCo_SM_Attack11,
    ftCo_SM_Attack12,
    ftCo_SM_Attack13,
    ftCo_SM_Attack100Start,
    ftCo_SM_Attack100Loop,
    ftCo_SM_Attack100End,
    ftCo_SM_AttackDash,
    ftCo_SM_AttackS3Hi,
    ftCo_SM_AttackS3HiS,
    ftCo_SM_AttackS3,
    ftCo_SM_AttackS3LwS,
    ftCo_SM_AttackS3Lw,
    ftCo_SM_AttackHi3,
    ftCo_SM_AttackLw3,
    ftCo_SM_AttackS4Hi,
    ftCo_SM_AttackS4HiS,
    ftCo_SM_AttackS4,
    ftCo_SM_AttackS4LwS,
    ftCo_SM_AttackS4Lw,
    ftCo_SM_Unk065,
    ftCo_SM_AttackHi4,
    ftCo_SM_AttackLw4,
    ftCo_SM_AttackAirN,
    ftCo_SM_AttackAirF,
    ftCo_SM_AttackAirB,
    ftCo_SM_AttackAirHi,
    ftCo_SM_AttackAirLw,
    ftCo_SM_LandingAirN,
    ftCo_SM_LandingAirF,
    ftCo_SM_LandingAirB,
    ftCo_SM_LandingAirHi,
    ftCo_SM_LandingAirLw,
    ftCo_SM_LightGet,
    ftCo_SM_LightThrowF,
    ftCo_SM_LightThrowB,
    ftCo_SM_LightThrowHi,
    ftCo_SM_LightThrowLw,
    ftCo_SM_LightThrowDash,
    ftCo_SM_LightThrowDrop,
    ftCo_SM_LightThrowAirF,
    ftCo_SM_LightThrowAirB,
    ftCo_SM_LightThrowAirHi,
    ftCo_SM_LightThrowAirLw,
    ftCo_SM_HeavyGet,
    ftCo_SM_HeavyWalk1,
    ftCo_SM_HeavyWalk2,
    ftCo_SM_HeavyThrowF,
    ftCo_SM_HeavyThrowB,
    ftCo_SM_HeavyThrowHi,
    ftCo_SM_HeavyThrowLw,
    ftCo_SM_LightThrowF4,
    ftCo_SM_LightThrowB4,
    ftCo_SM_LightThrowHi4,
    ftCo_SM_LightThrowLw4,
    ftCo_SM_LightThrowAirF4,
    ftCo_SM_LightThrowAirB4,
    ftCo_SM_LightThrowAirHi4,
    ftCo_SM_LightThrowAirLw4,
    ftCo_SM_HeavyThrowF4,
    ftCo_SM_HeavyThrowB4,
    ftCo_SM_HeavyThrowHi4,
    ftCo_SM_HeavyThrowLw4,
    ftCo_SM_SwordSwing1,
    ftCo_SM_SwordSwing3,
    ftCo_SM_SwordSwing4,
    ftCo_SM_SwordSwingDash,
    ftCo_SM_BatSwing1,
    ftCo_SM_BatSwing3,
    ftCo_SM_BatSwing4,
    ftCo_SM_BatSwingDash,
    ftCo_SM_ParasolSwing1,
    ftCo_SM_ParasolSwing3,
    ftCo_SM_ParasolSwing4,
    ftCo_SM_ParasolSwingDash,
    ftCo_SM_HarisenSwing1,
    ftCo_SM_HarisenSwing3,
    ftCo_SM_HarisenSwing4,
    ftCo_SM_HarisenSwingDash,
    ftCo_SM_StarRodSwing1,
    ftCo_SM_StarRodSwing3,
    ftCo_SM_StarRodSwing4,
    ftCo_SM_StarRodSwingDash,
    ftCo_SM_LipstickSwing1,
    ftCo_SM_LipstickSwing3,
    ftCo_SM_LipstickSwing4,
    ftCo_SM_LipstickSwingDash,
    ftCo_SM_HammerWait,
    ftCo_SM_HammerMove,
    ftCo_SM_ItemParasolOpen,
    ftCo_SM_ItemParasolFall,
    ftCo_SM_ItemParasolFallSpecial,
    ftCo_SM_ItemParasolDamageFall,
    ftCo_SM_LGunShoot,
    ftCo_SM_LGunShootAir,
    ftCo_SM_LGunShootEmpty,
    ftCo_SM_LGunShootAirEmpty,
    ftCo_SM_FireFlowerShoot,
    ftCo_SM_FireFlowerShootAir,
    ftCo_SM_ItemScrew,
    ftCo_SM_ItemScrewAir,
    ftCo_SM_ItemScrewDamage,
    ftCo_SM_ItemScrewDamageAir,
    ftCo_SM_ItemBlind,
    ftCo_SM_ItemScopeStart,
    ftCo_SM_ItemScopeRapid,
    ftCo_SM_ItemScopeFire,
    ftCo_SM_ItemScopeEnd,
    ftCo_SM_ItemScopeAirStart,
    ftCo_SM_ItemScopeAirRapid,
    ftCo_SM_ItemScopeAirFire,
    ftCo_SM_ItemScopeAirEnd,
    ftCo_SM_ItemScopeStartEmpty,
    ftCo_SM_ItemScopeRapidEmpty,
    ftCo_SM_ItemScopeFireEmpty,
    ftCo_SM_ItemScopeEndEmpty,
    ftCo_SM_ItemScopeAirStartEmpty,
    ftCo_SM_ItemScopeAirRapidEmpty,
    ftCo_SM_ItemScopeAirFireEmpty,
    ftCo_SM_ItemScopeAirEndEmpty,
    ftCo_SM_DamageHi1,
    ftCo_SM_DamageHi2,
    ftCo_SM_DamageHi3,
    ftCo_SM_DamageN1,
    ftCo_SM_DamageN2,
    ftCo_SM_DamageN3,
    ftCo_SM_DamageLw1,
    ftCo_SM_DamageLw2,
    ftCo_SM_DamageLw3,
    ftCo_SM_DamageAir1,
    ftCo_SM_DamageAir2,
    ftCo_SM_DamageAir3,
    ftCo_SM_DamageFlyHi,
    ftCo_SM_DamageFlyN,
    ftCo_SM_DamageFlyLw,
    ftCo_SM_DamageFlyTop,
    ftCo_SM_DamageFlyRoll,
    ftCo_SM_Unk182,
    ftCo_SM_DownBoundU,
    ftCo_SM_DownWaitU,
    ftCo_SM_DownDamageU,
    ftCo_SM_DownStandU,
    ftCo_SM_DownAttackU,
    ftCo_SM_DownFowardU,
    ftCo_SM_DownBackU,
    ftCo_SM_DownSpotU,
    ftCo_SM_DownBoundD,
    ftCo_SM_DownWaitD,
    ftCo_SM_DownDamageD,
    ftCo_SM_DownStandD,
    ftCo_SM_DownAttackD,
    ftCo_SM_DownFowardD,
    ftCo_SM_DownBackD,
    ftCo_SM_DownSpotD,
    ftCo_SM_Passive,
    ftCo_SM_PassiveStandF,
    ftCo_SM_PassiveStandB,
    ftCo_SM_PassiveWall,
    ftCo_SM_PassiveWallJump,
    ftCo_SM_PassiveCeil,
    ftCo_SM_FuraFura,
    ftCo_SM_FuraSleepStart,
    ftCo_SM_FuraSleepLoop,
    ftCo_SM_FuraSleepEnd,
    ftCo_SM_Pass,
    ftCo_SM_Ottotto,     ///< teeter
    ftCo_SM_OttottoWait, ///< teeter wait
    ftCo_SM_WallDamage,
    ftCo_SM_StopWall,
    ftCo_SM_StopCeil,
    ftCo_SM_MissFoot,
    ftCo_SM_CliffCatch,
    ftCo_SM_CliffWait,
    ftCo_SM_Unk218,
    ftCo_SM_CliffClimbSlow,
    ftCo_SM_CliffClimbQuick,
    ftCo_SM_CliffAttackSlow,
    ftCo_SM_CliffAttackQuick,
    ftCo_SM_CliffEscapeSlow,
    ftCo_SM_CliffEscapeQuick,
    ftCo_SM_CliffJumpSlow1,
    ftCo_SM_CliffJumpSlow2,
    ftCo_SM_CliffJumpQuick1,
    ftCo_SM_CliffJumpQuick2,
    ftCo_SM_Unk229,
    ftCo_SM_Unk230,
    ftCo_SM_Unk231,
    ftCo_SM_Unk232,
    ftCo_SM_Unk233,
    ftCo_SM_Unk234,
    ftCo_SM_Unk235,
    ftCo_SM_Unk236,
    ftCo_SM_Unk237,
    ftCo_SM_EntryStart,
    ftCo_SM_AppealSR,
    ftCo_SM_AppealSL,
    ftCo_SM_Unk241,
    ftCo_SM_Catch,
    ftCo_SM_CatchDash,
    ftCo_SM_CatchWait,
    ftCo_SM_CatchAttack,
    ftCo_SM_CatchCut,
    ftCo_SM_ThrowF,
    ftCo_SM_ThrowB,
    ftCo_SM_ThrowHi,
    ftCo_SM_ThrowLw,
    ftCo_SM_CapturePulledHi,
    ftCo_SM_CaptureWaitHi,
    ftCo_SM_CaptureDamageHi,
    ftCo_SM_CapturePulledLw,
    ftCo_SM_CaptureWaitLw,
    ftCo_SM_CaptureDamageLw,
    ftCo_SM_CaptureCut,
    ftCo_SM_CaptureJump,
    ftCo_SM_CaptureNeck,
    ftCo_SM_CaptureFoot,
    ftCo_SM_Unk261,
    ftCo_SM_ThrownF,
    ftCo_SM_ThrownB,
    ftCo_SM_ThrownHi,
    ftCo_SM_ThrownLw,
    ftCo_SM_ThrownlwWomen,
    ftCo_SM_ShoulderedWait,
    ftCo_SM_ShoulderedWalkSlow,
    ftCo_SM_ShoulderedWalkMiddle,
    ftCo_SM_ShoulderedWalkFast,
    ftCo_SM_ShoulderedTurn,
    ftCo_SM_ThrownFF,
    ftCo_SM_ThrownFB,
    ftCo_SM_ThrownFHi,
    ftCo_SM_ThrownFLw,
    ftCo_SM_CaptureCaptain,
    ftCo_SM_YoshiEgg,
    ftCo_SM_CaptureDamageKoopa,
    ftCo_SM_ThrownKoopaF,
    ftCo_SM_ThrownKoopaB,
    ftCo_SM_CaptureDamageKoopaAir,
    ftCo_SM_ThrownKoopaAirF,
    ftCo_SM_ThrownKoopaAirB,
    ftCo_SM_ThrownCopyStar,
    ftCo_SM_ThrownKirbyStar,
    ftCo_SM_ShieldBreakFly,
    ftCo_SM_ShieldBreakFall,
    ftCo_SM_ShieldBreakDownU,
    ftCo_SM_ShieldBreakDownD,
    ftCo_SM_ShieldBreakStandU,
    ftCo_SM_ShieldBreakStandD,
    ftCo_SM_ThrownMewtwo,
    ftCo_SM_ThrownMewtwoAir,
    ftCo_SM_KirbyYoshiEgg,
    ftCo_SM_Count,
} ftCo_Submotion;

typedef enum ftCo_Surface {
    FTCO_Surface_None,
    ftCo_Surface_LeftWall,
    ftCo_Surface_RightWall,
    ftCo_Surface_Ceiling,
} ftCo_Surface;

#endif
