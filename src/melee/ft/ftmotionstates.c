
#include "ft_0BEC.h"
#include "ft_0C31.h"
#include "ft_0CD1.h"
#include "ft_0CDD.h"
#include "ft_0D31.h"
#include "ftcamera.h"
#include "ftcliffcommon.h"
#include "ftcolanim.h"
#include "ftlipstickswing.h"
#include "ftstarrodswing.h"
#include "ftswing.h"
#include "types.h"

#include <melee/ft/chara/ftCommon/forward.h>

#include <melee/ft/chara/ftCommon/ftCo_AppealS.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack100.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackAir.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackDash.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_Barrel.h>
#include <melee/ft/chara/ftCommon/ftCo_BarrelWait.h>
#include <melee/ft/chara/ftCommon/ftCo_Bury.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureCaptain.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureCut.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureDamageKoopa.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureKirby.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureKoopa.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureWaitKirby.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureWaitKoopa.h>
#include <melee/ft/chara/ftCommon/ftCo_CaptureYoshi.h>
#include <melee/ft/chara/ftCommon/ftCo_CliffAttack.h>
#include <melee/ft/chara/ftCommon/ftCo_CliffClimb.h>
#include <melee/ft/chara/ftCommon/ftCo_CliffEscape.h>
#include <melee/ft/chara/ftCommon/ftCo_CliffJump.h>
#include <melee/ft/chara/ftCommon/ftCo_CliffWait.h>
#include <melee/ft/chara/ftCommon/ftCo_Damage.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageBind.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageFall.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageScrew.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageSong.h>
#include <melee/ft/chara/ftCommon/ftCo_Dash.h>
#include <melee/ft/chara/ftCommon/ftCo_Down.h>
#include <melee/ft/chara/ftCommon/ftCo_DownAttack.h>
#include <melee/ft/chara/ftCommon/ftCo_DownBound.h>
#include <melee/ft/chara/ftCommon/ftCo_DownDamage.h>
#include <melee/ft/chara/ftCommon/ftCo_DownSpot.h>
#include <melee/ft/chara/ftCommon/ftCo_DownStand.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_EscapeAir.h>
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_FallAerial.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_FlyReflect.h>
#include <melee/ft/chara/ftCommon/ftCo_Furafura.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerFall.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerJump.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerKneeBend.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerLanding.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerTurn.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerWait.h>
#include <melee/ft/chara/ftCommon/ftCo_HammerWalk.h>
#include <melee/ft/chara/ftCommon/ftCo_ItemParasolDamageFall.h>
#include <melee/ft/chara/ftCommon/ftCo_ItemParasolFall.h>
#include <melee/ft/chara/ftCommon/ftCo_ItemParasolFallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_ItemParasolOpen.h>
#include <melee/ft/chara/ftCommon/ftCo_ItemScrew.h>
#include <melee/ft/chara/ftCommon/ftCo_ItemThrow.h>
#include <melee/ft/chara/ftCommon/ftCo_Jump.h>
#include <melee/ft/chara/ftCommon/ftCo_JumpAerial.h>
#include <melee/ft/chara/ftCommon/ftCo_KinokoGiantEnd.h>
#include <melee/ft/chara/ftCommon/ftCo_KinokoGiantStart.h>
#include <melee/ft/chara/ftCommon/ftCo_KinokoSmallEnd.h>
#include <melee/ft/chara/ftCommon/ftCo_KinokoSmallStart.h>
#include <melee/ft/chara/ftCommon/ftCo_KneeBend.h>
#include <melee/ft/chara/ftCommon/ftCo_Landing.h>
#include <melee/ft/chara/ftCommon/ftCo_LandingAir.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_MissFoot.h>
#include <melee/ft/chara/ftCommon/ftCo_Ottotto.h>
#include <melee/ft/chara/ftCommon/ftCo_Pass.h>
#include <melee/ft/chara/ftCommon/ftCo_Passive.h>
#include <melee/ft/chara/ftCommon/ftCo_PassiveCeil.h>
#include <melee/ft/chara/ftCommon/ftCo_PassiveStand.h>
#include <melee/ft/chara/ftCommon/ftCo_PassiveWall.h>
#include <melee/ft/chara/ftCommon/ftCo_Rebound.h>
#include <melee/ft/chara/ftCommon/ftCo_Run.h>
#include <melee/ft/chara/ftCommon/ftCo_RunBrake.h>
#include <melee/ft/chara/ftCommon/ftCo_RunDirect.h>
#include <melee/ft/chara/ftCommon/ftCo_ShieldBreakDown.h>
#include <melee/ft/chara/ftCommon/ftCo_ShieldBreakFall.h>
#include <melee/ft/chara/ftCommon/ftCo_ShieldBreakFly.h>
#include <melee/ft/chara/ftCommon/ftCo_ShieldBreakStand.h>
#include <melee/ft/chara/ftCommon/ftCo_Shouldered.h>
#include <melee/ft/chara/ftCommon/ftCo_Squat.h>
#include <melee/ft/chara/ftCommon/ftCo_SquatRv.h>
#include <melee/ft/chara/ftCommon/ftCo_SquatWait.h>
#include <melee/ft/chara/ftCommon/ftCo_StopCeil.h>
#include <melee/ft/chara/ftCommon/ftCo_StopWall.h>
#include <melee/ft/chara/ftCommon/ftCo_Throw.h>
#include <melee/ft/chara/ftCommon/ftCo_Thrown.h>
#include <melee/ft/chara/ftCommon/ftCo_ThrownKirby.h>
#include <melee/ft/chara/ftCommon/ftCo_ThrownKoopa.h>
#include <melee/ft/chara/ftCommon/ftCo_ThrownMewtwo.h>
#include <melee/ft/chara/ftCommon/ftCo_Turn.h>
#include <melee/ft/chara/ftCommon/ftCo_TurnRun.h>
#include <melee/ft/chara/ftCommon/ftCo_Wait.h>
#include <melee/ft/chara/ftCommon/ftCo_Walk.h>
#include <melee/ft/chara/ftCommon/ftCo_WarpStar.h>
#include <melee/ft/chara/ftCommon/ftCo_YoshiEgg.h>
#include <melee/ft/chara/ftCommon/ftpickupitem.h>
#include <melee/ft/chara/ftCrazyHand/ftCh_Init.h>
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
#include <melee/ft/chara/ftMasterHand/ftMh_CaptureDamageMasterHand.h>
#include <melee/ft/chara/ftMasterHand/ftMh_CaptureMasterHand.h>
#include <melee/ft/chara/ftMasterHand/ftMh_ThrownMasterHand.h>

MotionState ftData_MotionStateList[ftCo_MS_Count] = {
    {
        // ftCo_MS_DeadDown = 0
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadDown_Anim,
        NULL,
        NULL,
        NULL,
        ftCo_DeadDown_Cam,
    },
    {
        // ftCo_MS_DeadLeft = 1
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadLeft_Anim,
        NULL,
        NULL,
        NULL,
        ftCo_DeadLeft_Cam,
    },
    {
        // ftCo_MS_DeadRight = 2
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadRight_Anim,
        NULL,
        NULL,
        NULL,
        ftCo_DeadRight_Cam,
    },
    {
        // ftCo_MS_DeadUp = 3
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUp_Anim,
        NULL,
        NULL,
        NULL,
        ftCo_DeadUp_Cam,
    },
    {
        // ftCo_MS_DeadUpStar = 4
        ftCo_SM_DamageFall,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpStar_Anim,
        NULL,
        NULL,
        NULL,
        ftCo_DeadUpStar_Cam,
    },
    {
        // ftCo_MS_DeadUpStarIce = 5
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpStar_Anim,
        NULL,
        NULL,
        NULL,
        ftCo_DeadUpStar_Cam,
    },
    {
        // ftCo_MS_DeadUpFall = 6
        ftCo_SM_DamageFall,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpFall_Anim,
        NULL,
        ftCo_DeadUpFall_Phys,
        NULL,
        ftCo_DeadUpFall_Cam,
    },
    {
        // ftCo_MS_DeadUpFallHitCamera = 7
        ftCo_SM_DeadUpFallHitCamera,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpFall_Anim,
        NULL,
        ftCo_DeadUpFall_Phys,
        NULL,
        ftCo_DeadUpFall_Cam,
    },
    {
        // ftCo_MS_DeadUpFallHitCameraFlat = 8
        ftCo_SM_DeadUpFallHitCameraFlat,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpFall_Anim,
        NULL,
        ftCo_DeadUpFall_Phys,
        NULL,
        ftCo_DeadUpFall_Cam,
    },
    {
        // ftCo_MS_DeadUpFallIce = 9
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpFall_Anim,
        NULL,
        ftCo_DeadUpFall_Phys,
        NULL,
        ftCo_DeadUpFall_Cam,
    },
    {
        // ftCo_MS_DeadUpFallHitCameraIce = 10
        ftCo_SM_None,
        ftCo_MF_Dead,
        FtMoveId_Default << 24,
        ftCo_DeadUpFall_Anim,
        NULL,
        ftCo_DeadUpFall_Phys,
        NULL,
        ftCo_DeadUpFall_Cam,
    },
    {
        // ftCo_MS_Sleep = 11
        ftCo_SM_None,
        ftCo_MF_Sleep,
        FtMoveId_Default << 24,
        ftCo_Sleep_Anim,
        ftCo_Sleep_IASA,
        NULL,
        NULL,
        NULL,
    },
    {
        // ftCo_MS_Rebirth = 12
        ftCo_SM_Wait1_0,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_Rebirth_Anim,
        ftCo_Rebirth_IASA,
        ftCo_Rebirth_Phys,
        ftCo_Rebirth_Coll,
        ftCo_Rebirth_Cam,
    },
    {
        // ftCo_MS_RebirthWait = 13
        ftCo_SM_Wait1_0,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_RebirthWait_Anim,
        ftCo_RebirthWait_IASA,
        ftCo_RebirthWait_Phys,
        ftCo_RebirthWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Wait = 14
        ftCo_SM_Wait1_0,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_Wait_Anim,
        ftCo_Wait_IASA,
        ftCo_Wait_Phys,
        ftCo_Wait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_WalkSlow = 15
        ftCo_SM_WalkSlow,
        ftCo_MF_Walk,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_Walk_Anim,
        ftCo_Walk_IASA,
        ftCo_Walk_Phys,
        ftCo_Walk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_WalkMiddle = 16
        ftCo_SM_WalkMiddle,
        ftCo_MF_Walk,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_Walk_Anim,
        ftCo_Walk_IASA,
        ftCo_Walk_Phys,
        ftCo_Walk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_WalkFast = 17
        ftCo_SM_WalkFast,
        ftCo_MF_Walk,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_Walk_Anim,
        ftCo_Walk_IASA,
        ftCo_Walk_Phys,
        ftCo_Walk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Turn = 18
        ftCo_SM_Turn,
        ftCo_MF_Turn,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_Turn_Anim,
        ftCo_Turn_IASA,
        ftCo_Turn_Phys,
        ftCo_Turn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_TurnRun = 19
        ftCo_SM_TurnRun,
        ftCo_MF_Turn,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_TurnRun_Anim,
        ftCo_TurnRun_IASA,
        ftCo_TurnRun_Phys,
        ftCo_TurnRun_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Dash = 20
        ftCo_SM_Dash,
        ftCo_MF_Dash,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_Dash_Anim,
        ftCo_Dash_IASA,
        ftCo_Dash_Phys,
        ftCo_Dash_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Run = 21
        ftCo_SM_Run,
        ftCo_MF_Run,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Run_Anim,
        ftCo_Run_IASA,
        ftCo_Run_Phys,
        ftCo_Run_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_RunDirect = 22
        ftCo_SM_Run,
        ftCo_MF_Run,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_RunDirect_Anim,
        ftCo_RunDirect_IASA,
        ftCo_RunDirect_Phys,
        ftCo_RunDirect_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_RunBrake = 23
        ftCo_SM_RunBrake,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_RunBrake_Anim,
        ftCo_RunBrake_IASA,
        ftCo_RunBrake_Phys,
        ftCo_RunBrake_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KneeBend = 24
        ftCo_SM_Kneebend,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_KneeBend_Anim,
        ftCo_KneeBend_IASA,
        ftCo_KneeBend_Phys,
        ftCo_KneeBend_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_JumpF = 25
        ftCo_SM_JumpF,
        ftCo_MF_Jump,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Jump_Anim,
        ftCo_Jump_IASA,
        ftCo_Jump_Phys,
        ftCo_Jump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_JumpB = 26
        ftCo_SM_JumpB,
        ftCo_MF_Jump,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Jump_Anim,
        ftCo_Jump_IASA,
        ftCo_Jump_Phys,
        ftCo_Jump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_JumpAerialF = 27
        ftCo_SM_JumpAerialF,
        ftCo_MF_JumpAir,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_JumpAerial_Anim,
        ftCo_JumpAerial_IASA,
        ftCo_JumpAerial_Phys,
        ftCo_JumpAerial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_JumpAerialB = 28
        ftCo_SM_JumpAerialB,
        ftCo_MF_JumpAir,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_JumpAerial_Anim,
        ftCo_JumpAerial_IASA,
        ftCo_JumpAerial_Phys,
        ftCo_JumpAerial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Fall = 29
        ftCo_SM_Fall,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Fall_Anim,
        ftCo_Fall_IASA,
        ftCo_Fall_Phys,
        ftCo_Fall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallF = 30
        ftCo_SM_None,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Fall_Anim,
        ftCo_Fall_IASA,
        ftCo_Fall_Phys,
        ftCo_Fall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallB = 31
        ftCo_SM_None,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Fall_Anim,
        ftCo_Fall_IASA,
        ftCo_Fall_Phys,
        ftCo_Fall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallAerial = 32
        ftCo_SM_FallAerial,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_FallAerial_Anim,
        ftCo_FallAerial_IASA,
        ftCo_FallAerial_Phys,
        ftCo_FallAerial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallAerialF = 33
        ftCo_SM_FallAerialF,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Fall_Anim,
        ftCo_FallAerial_IASA,
        ftCo_Fall_Phys,
        ftCo_Fall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallAerialB = 34
        ftCo_SM_FallAerialB,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Fall_Anim,
        ftCo_FallAerial_IASA,
        ftCo_Fall_Phys,
        ftCo_Fall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallSpecial = 35
        ftCo_SM_FallSpecial,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_FallSpecial_Anim,
        ftCo_FallSpecial_IASA,
        ftCo_FallSpecial_Phys,
        ftCo_FallSpecial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallSpecialF = 36
        ftCo_SM_FallSpecialF,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_FallSpecial_Anim,
        ftCo_FallSpecial_IASA,
        ftCo_FallSpecial_Phys,
        ftCo_FallSpecial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FallSpecialB = 37
        ftCo_SM_FallSpecialB,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_FallSpecial_Anim,
        ftCo_FallSpecial_IASA,
        ftCo_FallSpecial_Phys,
        ftCo_FallSpecial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageFall = 38
        ftCo_SM_DamageFall,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageFall_Anim,
        ftCo_DamageFall_IASA,
        ftCo_DamageFall_Phys,
        ftCo_DamageFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Squat = 39
        ftCo_SM_Squat,
        ftCo_MF_Squat,
        FtMoveId_Default << 24,
        ftCo_Squat_Anim,
        ftCo_Squat_IASA,
        ftCo_Squat_Phys,
        ftCo_Squat_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_SquatWait = 40
        ftCo_SM_SquatWait,
        ftCo_MF_Squat,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_SquatWait_Anim,
        ftCo_SquatWait_IASA,
        ftCo_SquatWait_Phys,
        ftCo_SquatWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_SquatRv = 41
        ftCo_SM_SquatRv,
        ftCo_MF_Squat,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_SquatRv_Anim,
        ftCo_SquatRv_IASA,
        ftCo_SquatRv_Phys,
        ftCo_SquatRv_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Landing = 42
        ftCo_SM_Landing,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_Landing_Anim,
        ftCo_Landing_IASA,
        ftCo_Landing_Phys,
        ftCo_Landing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LandingFallSpecial = 43
        ftCo_SM_LandingFallSpecial,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_Landing_Anim,
        ftCo_Landing_IASA,
        ftCo_Landing_Phys,
        ftCo_Landing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Attack11 = 44
        ftCo_SM_Attack11,
        ftCo_MF_Attack11,
        (FtMoveId_Attack11 << 24) | (1 << 23),
        ftCo_Attack11_Anim,
        ftCo_Attack11_IASA,
        ftCo_Attack11_Phys,
        ftCo_Attack11_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Attack12 = 45
        ftCo_SM_Attack12,
        ftCo_MF_Attack12,
        (FtMoveId_Attack12 << 24) | (1 << 23),
        ftCo_Attack12_Anim,
        ftCo_Attack12_IASA,
        ftCo_Attack11_Phys,
        ftCo_Attack11_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Attack13 = 46
        ftCo_SM_Attack13,
        ftCo_MF_Attack13,
        (FtMoveId_Attack13 << 24) | (1 << 23),
        ftCo_Attack13_Anim,
        ftCo_Attack13_IASA,
        ftCo_Attack11_Phys,
        ftCo_Attack11_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Attack100Start = 47
        ftCo_SM_Attack100Start,
        ftCo_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftCo_Attack100Start_Anim,
        NULL,
        ftCo_Attack100Start_Phys,
        ftCo_Attack100Start_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Attack100Loop = 48
        ftCo_SM_Attack100Loop,
        ftCo_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftCo_Attack100Loop_Anim,
        ftCo_Attack100Loop_IASA,
        ftCo_Attack100Loop_Phys,
        ftCo_Attack100Loop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Attack100End = 49
        ftCo_SM_Attack100End,
        ftCo_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftCo_Attack100End_Anim,
        NULL,
        ftCo_Attack100End_Phys,
        ftCo_Attack100End_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackDash = 50
        ftCo_SM_AttackDash,
        ftCo_MF_AttackDash,
        (FtMoveId_AttackDash << 24) | (1 << 23),
        ftCo_AttackDash_Anim,
        ftCo_AttackDash_IASA,
        ftCo_AttackDash_Phys,
        ftCo_AttackDash_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS3Hi = 51
        ftCo_SM_AttackS3Hi,
        ftCo_MF_AttackS3,
        (FtMoveId_AttackS3 << 24) | (1 << 23),
        ftCo_AttackS3_Anim,
        ftCo_AttackS3_IASA,
        ftCo_AttackS3_Phys,
        ftCo_AttackS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS3HiS = 52
        ftCo_SM_AttackS3HiS,
        ftCo_MF_AttackS3,
        (FtMoveId_AttackS3 << 24) | (1 << 23),
        ftCo_AttackS3_Anim,
        ftCo_AttackS3_IASA,
        ftCo_AttackS3_Phys,
        ftCo_AttackS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS3S = 53
        ftCo_SM_AttackS3,
        ftCo_MF_AttackS3,
        (FtMoveId_AttackS3 << 24) | (1 << 23),
        ftCo_AttackS3_Anim,
        ftCo_AttackS3_IASA,
        ftCo_AttackS3_Phys,
        ftCo_AttackS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS3LwS = 54
        ftCo_SM_AttackS3LwS,
        ftCo_MF_AttackS3,
        (FtMoveId_AttackS3 << 24) | (1 << 23),
        ftCo_AttackS3_Anim,
        ftCo_AttackS3_IASA,
        ftCo_AttackS3_Phys,
        ftCo_AttackS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS3Lw = 55
        ftCo_SM_AttackS3Lw,
        ftCo_MF_AttackS3,
        (FtMoveId_AttackS3 << 24) | (1 << 23),
        ftCo_AttackS3_Anim,
        ftCo_AttackS3_IASA,
        ftCo_AttackS3_Phys,
        ftCo_AttackS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackHi3 = 56
        ftCo_SM_AttackHi3,
        ftCo_MF_AttackHi3,
        (FtMoveId_AttackHi3 << 24) | (1 << 23),
        ftCo_AttackHi3_Anim,
        ftCo_AttackHi3_IASA,
        ftCo_AttackHi3_Phys,
        ftCo_AttackHi3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackLw3 = 57
        ftCo_SM_AttackLw3,
        ftCo_MF_AttackLw3,
        (FtMoveId_AttackLw3 << 24) | (1 << 23),
        ftCo_AttackLw3_Anim,
        ftCo_AttackLw3_IASA,
        ftCo_AttackLw3_Phys,
        ftCo_AttackLw3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS4Hi = 58
        ftCo_SM_AttackS4Hi,
        ftCo_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftCo_AttackS4_Anim,
        ftCo_AttackS4_IASA,
        ftCo_AttackS4_Phys,
        ftCo_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS4HiS = 59
        ftCo_SM_AttackS4HiS,
        ftCo_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftCo_AttackS4_Anim,
        ftCo_AttackS4_IASA,
        ftCo_AttackS4_Phys,
        ftCo_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS4S = 60
        ftCo_SM_AttackS4,
        ftCo_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftCo_AttackS4_Anim,
        ftCo_AttackS4_IASA,
        ftCo_AttackS4_Phys,
        ftCo_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS4LwS = 61
        ftCo_SM_AttackS4LwS,
        ftCo_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftCo_AttackS4_Anim,
        ftCo_AttackS4_IASA,
        ftCo_AttackS4_Phys,
        ftCo_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackS4Lw = 62
        ftCo_SM_AttackS4Lw,
        ftCo_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftCo_AttackS4_Anim,
        ftCo_AttackS4_IASA,
        ftCo_AttackS4_Phys,
        ftCo_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackHi4 = 63
        ftCo_SM_AttackHi4,
        ftCo_MF_AttackHi4,
        (FtMoveId_AttackHi4 << 24) | (1 << 23),
        ftCo_AttackHi4_Anim,
        ftCo_AttackHi4_IASA,
        ftCo_AttackHi4_Phys,
        ftCo_AttackHi4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackLw4 = 64
        ftCo_SM_AttackLw4,
        ftCo_MF_AttackLw4,
        (FtMoveId_AttackLw4 << 24) | (1 << 23),
        ftCo_AttackLw4_Anim,
        ftCo_AttackLw4_IASA,
        ftCo_AttackLw4_Phys,
        ftCo_AttackLw4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackAirN = 65
        ftCo_SM_AttackAirN,
        ftCo_MF_AttackAirN,
        (FtMoveId_AttackAirN << 24) | (1 << 23),
        ftCo_AttackAir_Anim,
        ftCo_AttackAirN_IASA,
        ftCo_AttackAir_Phys,
        ftCo_AttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackAirF = 66
        ftCo_SM_AttackAirF,
        ftCo_MF_AttackAirF,
        (FtMoveId_AttackAirF << 24) | (1 << 23),
        ftCo_AttackAir_Anim,
        ftCo_AttackAirF_IASA,
        ftCo_AttackAir_Phys,
        ftCo_AttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackAirB = 67
        ftCo_SM_AttackAirB,
        ftCo_MF_AttackAirB,
        (FtMoveId_AttackAirB << 24) | (1 << 23),
        ftCo_AttackAir_Anim,
        ftCo_AttackAirB_IASA,
        ftCo_AttackAir_Phys,
        ftCo_AttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackAirHi = 68
        ftCo_SM_AttackAirHi,
        ftCo_MF_AttackAirHi,
        (FtMoveId_AttackAirHi << 24) | (1 << 23),
        ftCo_AttackAir_Anim,
        ftCo_AttackAirHi_IASA,
        ftCo_AttackAir_Phys,
        ftCo_AttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AttackAirLw = 69
        ftCo_SM_AttackAirLw,
        ftCo_MF_AttackAirLw,
        (FtMoveId_AttackAirLw << 24) | (1 << 23),
        ftCo_AttackAir_Anim,
        ftCo_AttackAirLw_IASA,
        ftCo_AttackAir_Phys,
        ftCo_AttackAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LandingAirN = 70
        ftCo_SM_LandingAirN,
        ftCo_MF_LandingAirN,
        (FtMoveId_AttackAirN << 24) | ftCo_MF_Rebirth,
        ftCo_LandingAir_Anim,
        ftCo_LandingAir_IASA,
        ftCo_LandingAir_Phys,
        ftCo_LandingAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LandingAirF = 71
        ftCo_SM_LandingAirF,
        ftCo_MF_LandingAirF,
        (FtMoveId_AttackAirF << 24) | ftCo_MF_Rebirth,
        ftCo_LandingAir_Anim,
        ftCo_LandingAir_IASA,
        ftCo_LandingAir_Phys,
        ftCo_LandingAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LandingAirB = 72
        ftCo_SM_LandingAirB,
        ftCo_MF_LandingAirB,
        (FtMoveId_AttackAirB << 24) | ftCo_MF_Rebirth,
        ftCo_LandingAir_Anim,
        ftCo_LandingAir_IASA,
        ftCo_LandingAir_Phys,
        ftCo_LandingAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LandingAirHi = 73
        ftCo_SM_LandingAirHi,
        ftCo_MF_LandingAirHi,
        (FtMoveId_AttackAirHi << 24) | ftCo_MF_Rebirth,
        ftCo_LandingAir_Anim,
        ftCo_LandingAir_IASA,
        ftCo_LandingAir_Phys,
        ftCo_LandingAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LandingAirLw = 74
        ftCo_SM_LandingAirLw,
        ftCo_MF_LandingAirLw,
        (FtMoveId_AttackAirLw << 24) | ftCo_MF_Rebirth,
        ftCo_LandingAir_Anim,
        ftCo_LandingAir_IASA,
        ftCo_LandingAir_Phys,
        ftCo_LandingAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageHi1 = 75
        ftCo_SM_DamageHi1,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageHi2 = 76
        ftCo_SM_DamageHi2,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageHi3 = 77
        ftCo_SM_DamageHi3,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageN1 = 78
        ftCo_SM_DamageN1,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageN2 = 79
        ftCo_SM_DamageN2,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageN3 = 80
        ftCo_SM_DamageN3,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageLw1 = 81
        ftCo_SM_DamageLw1,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageLw2 = 82
        ftCo_SM_DamageLw2,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageLw3 = 83
        ftCo_SM_DamageLw3,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageAir1 = 84
        ftCo_SM_DamageAir1,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageAir2 = 85
        ftCo_SM_DamageAir2,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageAir3 = 86
        ftCo_SM_DamageAir3,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_Damage_Anim,
        ftCo_Damage_IASA,
        ftCo_Damage_Phys,
        ftCo_Damage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageFlyHi = 87
        ftCo_SM_DamageFlyHi,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageFly_Anim,
        ftCo_DamageFly_IASA,
        ftCo_DamageFly_Phys,
        ftCo_DamageFly_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageFlyN = 88
        ftCo_SM_DamageFlyN,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageFly_Anim,
        ftCo_DamageFly_IASA,
        ftCo_DamageFly_Phys,
        ftCo_DamageFly_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageFlyLw = 89
        ftCo_SM_DamageFlyLw,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageFly_Anim,
        ftCo_DamageFly_IASA,
        ftCo_DamageFly_Phys,
        ftCo_DamageFly_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageFlyTop = 90
        ftCo_SM_DamageFlyTop,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageFly_Anim,
        ftCo_DamageFly_IASA,
        ftCo_DamageFly_Phys,
        ftCo_DamageFly_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageFlyRoll = 91
        ftCo_SM_DamageFlyRoll,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageFlyRoll_Anim,
        ftCo_DamageFlyRoll_IASA,
        ftCo_DamageFlyRoll_Phys,
        ftCo_DamageFlyRoll_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightGet = 92
        ftCo_SM_LightGet,
        Ft_MF_SkipModelPartVis,
        (FtMoveId_Default << 24) | (1 << 23),
        ftpickupitem_Anim,
        ftpickupitem_IASA,
        ftpickupitem_Phys,
        ftpickupitem_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyGet = 93
        ftCo_SM_HeavyGet,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftpickupitem_Anim,
        ftpickupitem_IASA,
        ftpickupitem_Phys,
        ftpickupitem_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowF = 94
        ftCo_SM_LightThrowF,
        ftCo_MF_ItemThrow,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowB = 95
        ftCo_SM_LightThrowB,
        ftCo_MF_ItemThrow,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowHi = 96
        ftCo_SM_LightThrowHi,
        ftCo_MF_ItemThrow,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowLw = 97
        ftCo_SM_LightThrowLw,
        ftCo_MF_ItemThrow,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowDash = 98
        ftCo_SM_LightThrowDash,
        ftCo_MF_ItemThrow,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowDash_Phys,
        ftCo_LightThrowDashDrop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowDrop = 99
        ftCo_SM_LightThrowDrop,
        ftCo_MF_ItemThrow,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrowDashDrop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirF = 100
        ftCo_SM_LightThrowAirF,
        ftCo_MF_ItemThrowAir,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirB = 101
        ftCo_SM_LightThrowAirB,
        ftCo_MF_ItemThrowAir,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirHi = 102
        ftCo_SM_LightThrowAirHi,
        ftCo_MF_ItemThrowAir,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirLw = 103
        ftCo_SM_LightThrowAirLw,
        ftCo_MF_ItemThrowAir,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowF = 104
        ftCo_SM_HeavyThrowF,
        ftCo_MF_ItemThrow,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowB = 105
        ftCo_SM_HeavyThrowB,
        ftCo_MF_ItemThrow,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowHi = 106
        ftCo_SM_HeavyThrowHi,
        ftCo_MF_ItemThrow,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowLw = 107
        ftCo_SM_HeavyThrowLw,
        ftCo_MF_ItemThrow,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowF4 = 108
        ftCo_SM_LightThrowF4,
        ftCo_MF_ItemThrow4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowB4 = 109
        ftCo_SM_LightThrowB4,
        ftCo_MF_ItemThrow4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowHi4 = 110
        ftCo_SM_LightThrowHi4,
        ftCo_MF_ItemThrow4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowLw4 = 111
        ftCo_SM_LightThrowLw4,
        ftCo_MF_ItemThrow4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_LightThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirF4 = 112
        ftCo_SM_LightThrowAirF4,
        ftCo_MF_ItemThrowAir4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirB4 = 113
        ftCo_SM_LightThrowAirB4,
        ftCo_MF_ItemThrowAir4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirHi4 = 114
        ftCo_SM_LightThrowAirHi4,
        ftCo_MF_ItemThrowAir4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LightThrowAirLw4 = 115
        ftCo_SM_LightThrowAirLw4,
        ftCo_MF_ItemThrowAir4,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_LightThrowAir_Phys,
        ftCo_LightThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowF4 = 116
        ftCo_SM_HeavyThrowF4,
        ftCo_MF_ItemThrow4,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowB4 = 117
        ftCo_SM_HeavyThrowB4,
        ftCo_MF_ItemThrow4,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowHi4 = 118
        ftCo_SM_HeavyThrowHi4,
        ftCo_MF_ItemThrow4,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HeavyThrowLw4 = 119
        ftCo_SM_HeavyThrowLw4,
        ftCo_MF_ItemThrow4,
        FtMoveId_Default << 24,
        ftCo_ItemThrow_Anim,
        ftCo_ItemThrow_IASA,
        ftCo_ItemThrow_Phys,
        ftCo_HeavyThrow_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_SwordSwing1 = 120
        ftCo_SM_SwordSwing1,
        ftCo_MF_SwordSwing1,
        (FtMoveId_SwordSwing1 << 24) | (1 << 23),
        ftCo_SwordSwing_Anim,
        ftCo_SwordSwing_IASA,
        ftCo_SwordSwing_Phys,
        ftCo_SwordSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_SwordSwing3 = 121
        ftCo_SM_SwordSwing3,
        ftCo_MF_SwordSwing3,
        (FtMoveId_SwordSwing3 << 24) | (1 << 23),
        ftCo_SwordSwing_Anim,
        ftCo_SwordSwing_IASA,
        ftCo_SwordSwing_Phys,
        ftCo_SwordSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_SwordSwing4 = 122
        ftCo_SM_SwordSwing4,
        ftCo_MF_SwordSwing4,
        (FtMoveId_SwordSwing4 << 24) | (1 << 23),
        ftCo_SwordSwing_Anim,
        ftCo_SwordSwing_IASA,
        ftCo_SwordSwing_Phys,
        ftCo_SwordSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_SwordSwingDash = 123
        ftCo_SM_SwordSwingDash,
        ftCo_MF_SwordSwingDash,
        (FtMoveId_SwordSwingDash << 24) | (1 << 23),
        ftCo_SwordSwing_Anim,
        ftCo_SwordSwing_IASA,
        ftCo_SwordSwing_Phys,
        ftCo_SwordSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BatSwing1 = 124
        ftCo_SM_BatSwing1,
        ftCo_MF_BatSwing1,
        (FtMoveId_BatSwing1 << 24) | (1 << 23),
        ftCo_BatSwing_Anim,
        ftCo_BatSwing_IASA,
        ftCo_BatSwing_Phys,
        ftCo_BatSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BatSwing3 = 125
        ftCo_SM_BatSwing3,
        ftCo_MF_BatSwing3,
        (FtMoveId_BatSwing3 << 24) | (1 << 23),
        ftCo_BatSwing_Anim,
        ftCo_BatSwing_IASA,
        ftCo_BatSwing_Phys,
        ftCo_BatSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BatSwing4 = 126
        ftCo_SM_BatSwing4,
        ftCo_MF_BatSwing4,
        (FtMoveId_BatSwing4 << 24) | (1 << 23),
        ftCo_BatSwing_Anim,
        ftCo_BatSwing_IASA,
        ftCo_BatSwing_Phys,
        ftCo_BatSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BatSwingDash = 127
        ftCo_SM_BatSwingDash,
        ftCo_MF_BatSwingDash,
        (FtMoveId_BatSwingDash << 24) | (1 << 23),
        ftCo_BatSwing_Anim,
        ftCo_BatSwing_IASA,
        ftCo_BatSwing_Phys,
        ftCo_BatSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ParasolSwing1 = 128
        ftCo_SM_ParasolSwing1,
        ftCo_MF_ParasolSwing1,
        (FtMoveId_ParasolSwing1 << 24) | (1 << 23),
        ftCo_ParasolSwing_Anim,
        ftCo_ParasolSwing_IASA,
        ftCo_ParasolSwing_Phys,
        ftCo_ParasolSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ParasolSwing3 = 129
        ftCo_SM_ParasolSwing3,
        ftCo_MF_ParasolSwing3,
        (FtMoveId_ParasolSwing3 << 24) | (1 << 23),
        ftCo_ParasolSwing_Anim,
        ftCo_ParasolSwing_IASA,
        ftCo_ParasolSwing_Phys,
        ftCo_ParasolSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ParasolSwing4 = 130
        ftCo_SM_ParasolSwing4,
        ftCo_MF_ParasolSwing4,
        (FtMoveId_ParasolSwing4 << 24) | (1 << 23),
        ftCo_ParasolSwing_Anim,
        ftCo_ParasolSwing_IASA,
        ftCo_ParasolSwing_Phys,
        ftCo_ParasolSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ParasolSwingDash = 131
        ftCo_SM_ParasolSwingDash,
        ftCo_MF_ParasolSwingDash,
        (FtMoveId_ParasolSwingDash << 24) | (1 << 23),
        ftCo_ParasolSwing_Anim,
        ftCo_ParasolSwing_IASA,
        ftCo_ParasolSwing_Phys,
        ftCo_ParasolSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HarisenSwing1 = 132
        ftCo_SM_HarisenSwing1,
        ftCo_MF_HarisenSwing1,
        (FtMoveId_HarisenSwing1 << 24) | (1 << 23),
        ftCo_HarisenSwing_Anim,
        ftCo_HarisenSwing_IASA,
        ftCo_HarisenSwing_Phys,
        ftCo_HarisenSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HarisenSwing3 = 133
        ftCo_SM_HarisenSwing3,
        ftCo_MF_HarisenSwing3,
        (FtMoveId_HarisenSwing3 << 24) | (1 << 23),
        ftCo_HarisenSwing_Anim,
        ftCo_HarisenSwing_IASA,
        ftCo_HarisenSwing_Phys,
        ftCo_HarisenSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HarisenSwing4 = 134
        ftCo_SM_HarisenSwing4,
        ftCo_MF_HarisenSwing4,
        (FtMoveId_HarisenSwing4 << 24) | (1 << 23),
        ftCo_HarisenSwing_Anim,
        ftCo_HarisenSwing_IASA,
        ftCo_HarisenSwing_Phys,
        ftCo_HarisenSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HarisenSwingDash = 135
        ftCo_SM_HarisenSwingDash,
        ftCo_MF_HarisenSwingDash,
        (FtMoveId_HarisenSwingDash << 24) | (1 << 23),
        ftCo_HarisenSwing_Anim,
        ftCo_HarisenSwing_IASA,
        ftCo_HarisenSwing_Phys,
        ftCo_HarisenSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_StarRodSwing1 = 136
        ftCo_SM_StarRodSwing1,
        ftCo_MF_StarRodSwing1,
        (FtMoveId_StarRodSwing1 << 24) | (1 << 23),
        ftCo_StarRodSwing_Anim,
        ftCo_StarRodSwing_IASA,
        ftCo_StarRodSwing_Phys,
        ftCo_StarRodSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_StarRodSwing3 = 137
        ftCo_SM_StarRodSwing3,
        ftCo_MF_StarRodSwing3,
        (FtMoveId_StarRodSwing3 << 24) | (1 << 23),
        ftCo_StarRodSwing_Anim,
        ftCo_StarRodSwing_IASA,
        ftCo_StarRodSwing_Phys,
        ftCo_StarRodSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_StarRodSwing4 = 138
        ftCo_SM_StarRodSwing4,
        ftCo_MF_StarRodSwing4,
        (FtMoveId_StarRodSwing4 << 24) | (1 << 23),
        ftCo_StarRodSwing_Anim,
        ftCo_StarRodSwing_IASA,
        ftCo_StarRodSwing_Phys,
        ftCo_StarRodSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_StarRodSwingDash = 139
        ftCo_SM_StarRodSwingDash,
        ftCo_MF_StarRodSwingDash,
        (FtMoveId_StarRodSwingDash << 24) | (1 << 23),
        ftCo_StarRodSwing_Anim,
        ftCo_StarRodSwing_IASA,
        ftCo_StarRodSwing_Phys,
        ftCo_StarRodSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LipstickSwing1 = 140
        ftCo_SM_LipstickSwing1,
        ftCo_MF_LipstickSwing1,
        (FtMoveId_LipstickSwing1 << 24) | (1 << 23),
        ftCo_LipstickSwing_Anim,
        ftCo_LipstickSwing_IASA,
        ftCo_LipstickSwing_Phys,
        ftCo_LipstickSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LipstickSwing3 = 141
        ftCo_SM_LipstickSwing3,
        ftCo_MF_LipstickSwing3,
        (FtMoveId_LipstickSwing3 << 24) | (1 << 23),
        ftCo_LipstickSwing_Anim,
        ftCo_LipstickSwing_IASA,
        ftCo_LipstickSwing_Phys,
        ftCo_LipstickSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LipstickSwing4 = 142
        ftCo_SM_LipstickSwing4,
        ftCo_MF_LipstickSwing4,
        (FtMoveId_LipstickSwing4 << 24) | (1 << 23),
        ftCo_LipstickSwing_Anim,
        ftCo_LipstickSwing_IASA,
        ftCo_LipstickSwing_Phys,
        ftCo_LipstickSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LipstickSwingDash = 143
        ftCo_SM_LipstickSwingDash,
        ftCo_MF_LipstickSwingDash,
        (FtMoveId_LipstickSwingDash << 24) | (1 << 23),
        ftCo_LipstickSwing_Anim,
        ftCo_LipstickSwing_IASA,
        ftCo_LipstickSwing_Phys,
        ftCo_LipstickSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemParasolOpen = 144
        ftCo_SM_ItemParasolOpen,
        ftCo_MF_ParasolOpen,
        (FtMoveId_Parasol << 24) | (1 << 23),
        ftCo_ItemParasolOpen_Anim,
        ftCo_ItemParasolOpen_IASA,
        ftCo_ItemParasolOpen_Phys,
        ftCo_ItemParasolOpen_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemParasolFall = 145
        ftCo_SM_ItemParasolFall,
        ftCo_MF_ParasolFall,
        (FtMoveId_Parasol << 24) | (1 << 23),
        ftCo_ItemParasolFall_Anim,
        ftCo_ItemParasolFall_IASA,
        ftCo_ItemParasolFall_Phys,
        ftCo_ItemParasolFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemParasolFallSpecial = 146
        ftCo_SM_ItemParasolFallSpecial,
        ftCo_MF_ParasolFall,
        (FtMoveId_Parasol << 24) | (1 << 23),
        ftCo_ItemParasolFallSpecial_Anim,
        ftCo_ItemParasolFallSpecial_IASA,
        ftCo_ItemParasolFallSpecial_Phys,
        ftCo_ItemParasolFallSpecial_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemParasolDamageFall = 147
        ftCo_SM_ItemParasolDamageFall,
        ftCo_MF_ParasolFall,
        (FtMoveId_Parasol << 24) | (1 << 23),
        ftCo_ItemParasolDamageFall_Anim,
        ftCo_ItemParasolDamageFall_IASA,
        ftCo_ItemParasolDamageFall_Phys,
        ftCo_ItemParasolDamageFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LGunShoot = 148
        ftCo_SM_LGunShoot,
        ftCo_MF_LGunShoot,
        (FtMoveId_LGunShoot << 24) | (1 << 23),
        ftCo_LGunShoot_Anim,
        ftCo_LGunShoot_IASA,
        ftCo_LGunShoot_Phys,
        ftCo_LGunShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LGunShootAir = 149
        ftCo_SM_LGunShootAir,
        ftCo_MF_LGunShootAir,
        (FtMoveId_LGunShoot << 24) | (1 << 23),
        ftCo_LGunShootAir_Anim,
        ftCo_LGunShootAir_IASA,
        ftCo_LGunShootAir_Phys,
        ftCo_LGunShootAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LGunShootEmpty = 150
        ftCo_SM_LGunShootEmpty,
        ftCo_MF_LGunShoot,
        (FtMoveId_LGunShoot << 24) | (1 << 23),
        ftCo_LGunShoot_Anim,
        ftCo_LGunShoot_IASA,
        ftCo_LGunShoot_Phys,
        ftCo_LGunShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LGunShootAirEmpty = 151
        ftCo_SM_LGunShootAirEmpty,
        ftCo_MF_LGunShootAir,
        (FtMoveId_LGunShoot << 24) | (1 << 23),
        ftCo_LGunShootAir_Anim,
        ftCo_LGunShootAir_IASA,
        ftCo_LGunShootAir_Phys,
        ftCo_LGunShootAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FireFlowerShoot = 152
        ftCo_SM_FireFlowerShoot,
        ftCo_MF_FireFlowerShoot,
        (FtMoveId_FireFlowerShoot << 24) | (1 << 23),
        ftCo_FireFlowerShoot_Anim,
        ftCo_FireFlowerShoot_IASA,
        ftCo_FireFlowerShoot_Phys,
        ftCo_FireFlowerShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FireFlowerShootAir = 153
        ftCo_SM_FireFlowerShootAir,
        ftCo_MF_FireFlowerShootAir,
        (FtMoveId_FireFlowerShoot << 24) | (1 << 23),
        ftCo_FireFlowerShootAir_Anim,
        ftCo_FireFlowerShootAir_IASA,
        ftCo_FireFlowerShootAir_Phys,
        ftCo_FireFlowerShootAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScrew = 154
        ftCo_SM_ItemScrew,
        ftCo_MF_ItemScrew,
        (FtMoveId_Screw << 24) | (1 << 23),
        ftCo_ItemScrew_Anim,
        ftCo_ItemScrew_IASA,
        ftCo_ItemScrew_Phys,
        ftCo_ItemScrew_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScrewAir = 155
        ftCo_SM_ItemScrewAir,
        ftCo_MF_ItemScrewAir,
        (FtMoveId_Screw << 24) | (1 << 23),
        ftCo_ItemScrewAir_Anim,
        ftCo_ItemScrewAir_IASA,
        ftCo_ItemScrewAir_Phys,
        ftCo_ItemScrewAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageScrew = 156
        ftCo_SM_ItemScrewDamage,
        ftCo_MF_DamageScrew,
        FtMoveId_Default << 24,
        ftCo_DamageScrew_Anim,
        ftCo_DamageScrew_IASA,
        ftCo_DamageScrew_Phys,
        ftCo_DamageScrew_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageScrewAir = 157
        ftCo_SM_ItemScrewDamageAir,
        ftCo_MF_DamageScrewAir,
        FtMoveId_Default << 24,
        ftCo_DamageScrew_Anim,
        ftCo_DamageScrew_IASA,
        ftCo_DamageScrew_Phys,
        ftCo_DamageScrew_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeStart = 158
        ftCo_SM_ItemScopeStart,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeStart_Anim,
        ftCo_ItemScopeStart_IASA,
        ftCo_ItemScopeStart_Phys,
        ftCo_ItemScopeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeRapid = 159
        ftCo_SM_ItemScopeRapid,
        ftCo_MF_ItemScopeRapid,
        (FtMoveId_ScopeRapid << 24) | (1 << 23),
        ftCo_ItemScopeRapid_Anim,
        ftCo_ItemScopeRapid_IASA,
        ftCo_ItemScopeRapid_Phys,
        ftCo_ItemScopeRapid_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeFire = 160
        ftCo_SM_ItemScopeFire,
        ftCo_MF_ItemScopeFire,
        (FtMoveId_ScopeFire << 24) | (1 << 23),
        ftCo_ItemScopeFire_Anim,
        ftCo_ItemScopeFire_IASA,
        ftCo_ItemScopeFire_Phys,
        ftCo_ItemScopeFire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeEnd = 161
        ftCo_SM_ItemScopeEnd,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeEnd_Anim,
        ftCo_ItemScopeEnd_IASA,
        ftCo_ItemScopeEnd_Phys,
        ftCo_ItemScopeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirStart = 162
        ftCo_SM_ItemScopeAirStart,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeAirStart_Anim,
        ftCo_ItemScopeAirStart_IASA,
        ftCo_ItemScopeAirStart_Phys,
        ftCo_ItemScopeAirStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirRapid = 163
        ftCo_SM_ItemScopeAirRapid,
        ftCo_MF_ItemScopeAirRapid,
        (FtMoveId_ScopeRapid << 24) | (1 << 23),
        ftCo_ItemScopeAirRapid_Anim,
        ftCo_ItemScopeAirRapid_IASA,
        ftCo_ItemScopeAirRapid_Phys,
        ftCo_ItemScopeAirRapid_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirFire = 164
        ftCo_SM_ItemScopeAirFire,
        ftCo_MF_ItemScopeAir,
        (FtMoveId_ScopeFire << 24) | (1 << 23),
        ftCo_ItemScopeAirFire_Anim,
        ftCo_ItemScopeAirFire_IASA,
        ftCo_ItemScopeAirFire_Phys,
        ftCo_ItemScopeAirFire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirEnd = 165
        ftCo_SM_ItemScopeAirEnd,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeAirEnd_Anim,
        ftCo_ItemScopeAirEnd_IASA,
        ftCo_ItemScopeAirEnd_Phys,
        ftCo_ItemScopeAirEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeStartEmpty = 166
        ftCo_SM_ItemScopeStartEmpty,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeStart_Anim,
        ftCo_ItemScopeStart_IASA,
        ftCo_ItemScopeStart_Phys,
        ftCo_ItemScopeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeRapidEmpty = 167
        ftCo_SM_ItemScopeRapidEmpty,
        ftCo_MF_ItemScopeRapid,
        (FtMoveId_ScopeRapid << 24) | (1 << 23),
        ftCo_ItemScopeRapid_Anim,
        ftCo_ItemScopeRapid_IASA,
        ftCo_ItemScopeRapid_Phys,
        ftCo_ItemScopeRapid_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeFireEmpty = 168
        ftCo_SM_ItemScopeFireEmpty,
        ftCo_MF_ItemScopeFire,
        (FtMoveId_ScopeFire << 24) | (1 << 23),
        ftCo_ItemScopeFire_Anim,
        ftCo_ItemScopeFire_IASA,
        ftCo_ItemScopeFire_Phys,
        ftCo_ItemScopeFire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeEndEmpty = 169
        ftCo_SM_ItemScopeEndEmpty,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeEnd_Anim,
        ftCo_ItemScopeEnd_IASA,
        ftCo_ItemScopeEnd_Phys,
        ftCo_ItemScopeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirStartEmpty = 170
        ftCo_SM_ItemScopeAirStartEmpty,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeAirStart_Anim,
        ftCo_ItemScopeAirStart_IASA,
        ftCo_ItemScopeAirStart_Phys,
        ftCo_ItemScopeAirStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirRapidEmpty = 171
        ftCo_SM_ItemScopeAirRapidEmpty,
        ftCo_MF_ItemScopeAirRapid,
        (FtMoveId_ScopeRapid << 24) | (1 << 23),
        ftCo_ItemScopeAirRapid_Anim,
        ftCo_ItemScopeAirRapid_IASA,
        ftCo_ItemScopeAirRapid_Phys,
        ftCo_ItemScopeAirRapid_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirFireEmpty = 172
        ftCo_SM_ItemScopeAirFireEmpty,
        ftCo_MF_ItemScopeAir,
        (FtMoveId_ScopeFire << 24) | (1 << 23),
        ftCo_ItemScopeAirFire_Anim,
        ftCo_ItemScopeAirFire_IASA,
        ftCo_ItemScopeAirFire_Phys,
        ftCo_ItemScopeAirFire_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ItemScopeAirEndEmpty = 173
        ftCo_SM_ItemScopeAirEndEmpty,
        ftCo_MF_ItemScope,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_ItemScopeAirEnd_Anim,
        ftCo_ItemScopeAirEnd_IASA,
        ftCo_ItemScopeAirEnd_Phys,
        ftCo_ItemScopeAirEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LiftWait = 174
        ftCo_SM_None,
        ftCo_MF_LiftWait,
        FtMoveId_Default << 24,
        ftCo_LiftWait_Anim,
        ftCo_LiftWait_IASA,
        ftCo_LiftWait_Phys,
        ftCo_LiftWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LiftWalk1 = 175
        ftCo_SM_HeavyWalk1,
        ftCo_MF_LiftWalk,
        FtMoveId_Default << 24,
        ftCo_LiftWalk_Anim,
        ftCo_LiftWalk_IASA,
        ftCo_LiftWalk_Phys,
        ftCo_LiftWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LiftWalk2 = 176
        ftCo_SM_HeavyWalk2,
        ftCo_MF_LiftWalk,
        FtMoveId_Default << 24,
        ftCo_LiftWalk_Anim,
        ftCo_LiftWalk_IASA,
        ftCo_LiftWalk_Phys,
        ftCo_LiftWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_LiftTurn = 177
        ftCo_SM_None,
        ftCo_MF_LiftTurn,
        FtMoveId_Default << 24,
        ftCo_LiftTurn_Anim,
        ftCo_LiftTurn_IASA,
        ftCo_LiftTurn_Phys,
        ftCo_LiftTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_GuardOn = 178
        ftCo_SM_GuardOn,
        Ft_MF_UnkUpdatePhys,
        (FtMoveId_Default << 24) | (1 << 22) | (1 << 23),
        ftCo_GuardOn_Anim,
        ftCo_GuardOn_IASA,
        ftCo_GuardOn_Phys,
        ftCo_GuardOn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Guard = 179
        ftCo_SM_Guard,
        ftCo_MF_Guard,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Guard_Anim,
        ftCo_Guard_IASA,
        ftCo_Guard_Phys,
        ftCo_Guard_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_GuardOff = 180
        ftCo_SM_GuardOff,
        Ft_MF_UnkUpdatePhys,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_GuardOff_Anim,
        ftCo_GuardOff_IASA,
        ftCo_GuardOff_Phys,
        ftCo_GuardOff_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_GuardSetOff = 181
        ftCo_SM_GuardDamage,
        Ft_MF_UnkUpdatePhys,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_GuardSetOff_Anim,
        ftCo_GuardSetOff_IASA,
        ftCo_GuardSetOff_Phys,
        ftCo_GuardSetOff_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_GuardReflect = 182
        ftCo_SM_GuardOn,
        ftCo_MF_GuardReflect,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_GuardReflect_Anim,
        ftCo_GuardReflect_IASA,
        ftCo_GuardReflect_Phys,
        ftCo_GuardReflect_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownBoundU = 183
        ftCo_SM_DownBoundU,
        ftCo_MF_DownU,
        FtMoveId_Default << 24,
        ftCo_DownBound_Anim,
        ftCo_DownBound_IASA,
        ftCo_DownBound_Phys,
        ftCo_DownBound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownWaitU = 184
        ftCo_SM_DownWaitU,
        ftCo_MF_DownU,
        FtMoveId_Default << 24,
        ftCo_DownWait_Anim,
        ftCo_DownWait_IASA,
        ftCo_DownWait_Phys,
        ftCo_DownWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownDamageU = 185
        ftCo_SM_DownDamageU,
        ftCo_MF_DownDamageU,
        FtMoveId_Default << 24,
        ftCo_DownDamage_Anim,
        ftCo_DownDamage_IASA,
        ftCo_DownDamage_Phys,
        ftCo_DownDamage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownStandU = 186
        ftCo_SM_DownStandU,
        ftCo_MF_DownU,
        FtMoveId_Default << 24,
        ftCo_DownStand_Anim,
        ftCo_DownStand_IASA,
        ftCo_DownStand_Phys,
        ftCo_DownStand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownAttackU = 187
        ftCo_SM_DownAttackU,
        ftCo_MF_DownAttackU,
        FtMoveId_DownAttackU << 24,
        ftCo_DownAttack_Anim,
        ftCo_DownAttack_IASA,
        ftCo_DownAttack_Phys,
        ftCo_DownAttack_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownFowardU = 188
        ftCo_SM_DownFowardU,
        ftCo_MF_DownU,
        FtMoveId_Default << 24,
        ftCo_Down_Anim,
        ftCo_Down_IASA,
        ftCo_Down_Phys,
        ftCo_Down_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownBackU = 189
        ftCo_SM_DownBackU,
        ftCo_MF_DownU,
        FtMoveId_Default << 24,
        ftCo_Down_Anim,
        ftCo_Down_IASA,
        ftCo_Down_Phys,
        ftCo_Down_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownSpotU = 190
        ftCo_SM_DownSpotU,
        ftCo_MF_DownU,
        FtMoveId_Default << 24,
        ftCo_DownSpot_Anim,
        ftCo_DownSpot_IASA,
        ftCo_DownSpot_Phys,
        ftCo_DownSpot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownBoundD = 191
        ftCo_SM_DownBoundD,
        ftCo_MF_DownD,
        FtMoveId_Default << 24,
        ftCo_DownBound_Anim,
        ftCo_DownBound_IASA,
        ftCo_DownBound_Phys,
        ftCo_DownBound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownWaitD = 192
        ftCo_SM_DownWaitD,
        ftCo_MF_DownD,
        FtMoveId_Default << 24,
        ftCo_DownWait_Anim,
        ftCo_DownWait_IASA,
        ftCo_DownWait_Phys,
        ftCo_DownWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownDamageD = 193
        ftCo_SM_DownDamageD,
        ftCo_MF_DownDamageD,
        FtMoveId_Default << 24,
        ftCo_DownDamage_Anim,
        ftCo_DownDamage_IASA,
        ftCo_DownDamage_Phys,
        ftCo_DownDamage_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownStandD = 194
        ftCo_SM_DownStandD,
        ftCo_MF_DownD,
        FtMoveId_Default << 24,
        ftCo_DownStand_Anim,
        ftCo_DownStand_IASA,
        ftCo_DownStand_Phys,
        ftCo_DownStand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownAttackD = 195
        ftCo_SM_DownAttackD,
        ftCo_MF_DownAttackD,
        FtMoveId_DownAttackD << 24,
        ftCo_DownAttack_Anim,
        ftCo_DownAttack_IASA,
        ftCo_DownAttack_Phys,
        ftCo_DownAttack_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownFowardD = 196
        ftCo_SM_DownFowardD,
        ftCo_MF_DownD,
        FtMoveId_Default << 24,
        ftCo_Down_Anim,
        ftCo_Down_IASA,
        ftCo_Down_Phys,
        ftCo_Down_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownBackD = 197
        ftCo_SM_DownBackD,
        ftCo_MF_DownD,
        FtMoveId_Default << 24,
        ftCo_Down_Anim,
        ftCo_Down_IASA,
        ftCo_Down_Phys,
        ftCo_Down_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownSpotD = 198
        ftCo_SM_DownSpotD,
        ftCo_MF_DownD,
        FtMoveId_Default << 24,
        ftCo_DownSpot_Anim,
        ftCo_DownSpot_IASA,
        ftCo_DownSpot_Phys,
        ftCo_DownSpot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Passive = 199
        ftCo_SM_Passive,
        ftCo_MF_Passive,
        FtMoveId_Default << 24,
        ftCo_Passive_Anim,
        ftCo_Passive_IASA,
        ftCo_Passive_Phys,
        ftCo_Passive_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_PassiveStandF = 200
        ftCo_SM_PassiveStandF,
        ftCo_MF_Passive,
        FtMoveId_Default << 24,
        ftCo_PassiveStand_Anim,
        ftCo_PassiveStand_IASA,
        ftCo_PassiveStand_Phys,
        ftCo_PassiveStand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_PassiveStandB = 201
        ftCo_SM_PassiveStandB,
        ftCo_MF_Passive,
        FtMoveId_Default << 24,
        ftCo_PassiveStand_Anim,
        ftCo_PassiveStand_IASA,
        ftCo_PassiveStand_Phys,
        ftCo_PassiveStand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_PassiveWall = 202
        ftCo_SM_PassiveWall,
        ftCo_MF_PassiveWall,
        FtMoveId_Default << 24,
        ftCo_PassiveWall_Anim,
        ftCo_PassiveWall_IASA,
        ftCo_PassiveWall_Phys,
        ftCo_PassiveWall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_PassiveWallJump = 203
        ftCo_SM_PassiveWallJump,
        ftCo_MF_PassiveWall,
        FtMoveId_Default << 24,
        ftCo_PassiveWall_Anim,
        ftCo_PassiveWall_IASA,
        ftCo_PassiveWall_Phys,
        ftCo_PassiveWall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_PassiveCeil = 204
        ftCo_SM_PassiveCeil,
        ftCo_MF_PassiveWall,
        FtMoveId_Default << 24,
        ftCo_PassiveCeil_Anim,
        ftCo_PassiveCeil_IASA,
        ftCo_PassiveCeil_Phys,
        ftCo_PassiveCeil_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShieldBreakFly = 205
        ftCo_SM_ShieldBreakFly,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_ShieldBreakFly_Anim,
        ftCo_ShieldBreakFly_IASA,
        ftCo_ShieldBreakFly_Phys,
        ftCo_ShieldBreakFly_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShieldBreakFall = 206
        ftCo_SM_ShieldBreakFall,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_ShieldBreakFall_Anim,
        ftCo_ShieldBreakFall_IASA,
        ftCo_ShieldBreakFall_Phys,
        ftCo_ShieldBreakFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShieldBreakDownU = 207
        ftCo_SM_ShieldBreakDownU,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_ShieldBreakDown_Anim,
        ftCo_ShieldBreakDown_IASA,
        ftCo_ShieldBreakDown_Phys,
        ftCo_ShieldBreakDown_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShieldBreakDownD = 208
        ftCo_SM_ShieldBreakDownD,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_ShieldBreakDown_Anim,
        ftCo_ShieldBreakDown_IASA,
        ftCo_ShieldBreakDown_Phys,
        ftCo_ShieldBreakDown_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShieldBreakStandU = 209
        ftCo_SM_ShieldBreakStandU,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_ShieldBreakStand_Anim,
        ftCo_ShieldBreakStand_IASA,
        ftCo_ShieldBreakStand_Phys,
        ftCo_ShieldBreakStand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShieldBreakStandD = 210
        ftCo_SM_ShieldBreakStandD,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_ShieldBreakStand_Anim,
        ftCo_ShieldBreakStand_IASA,
        ftCo_ShieldBreakStand_Phys,
        ftCo_ShieldBreakStand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Furafura = 211
        ftCo_SM_FuraFura,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_Furafura_Anim,
        ftCo_Furafura_IASA,
        ftCo_Furafura_Phys,
        ftCo_Furafura_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Catch = 212
        ftCo_SM_Catch,
        ftCo_MF_Catch,
        FtMoveId_Default << 24,
        ftCo_Catch_Anim,
        ftCo_Catch_IASA,
        ftCo_Catch_Phys,
        ftCo_Catch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CatchPull = 213
        ftCo_SM_Catch,
        ftCo_MF_CatchWait,
        FtMoveId_Default << 24,
        ftCo_CatchPull_Anim,
        ftCo_CatchPull_IASA,
        ftCo_CatchPull_Phys,
        ftCo_CatchPull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CatchDash = 214
        ftCo_SM_CatchDash,
        ftCo_MF_Catch,
        FtMoveId_Default << 24,
        ftCo_CatchDash_Anim,
        ftCo_CatchDash_IASA,
        ftCo_CatchDash_Phys,
        ftCo_CatchDash_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CatchDashPull = 215
        ftCo_SM_CatchDash,
        ftCo_MF_CatchWait,
        FtMoveId_Default << 24,
        ftCo_CatchPull_Anim,
        ftCo_CatchPull_IASA,
        ftCo_CatchPull_Phys,
        ftCo_CatchPull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CatchWait = 216
        ftCo_SM_CatchWait,
        ftCo_MF_CatchWait,
        FtMoveId_Default << 24,
        ftCo_CatchWait_Anim,
        ftCo_CatchWait_IASA,
        ftCo_CatchWait_Phys,
        ftCo_CatchWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CatchAttack = 217
        ftCo_SM_CatchAttack,
        ftCo_MF_CatchAttack,
        FtMoveId_CatchAttack << 24,
        ftCo_CatchAttack_Anim,
        ftCo_CatchAttack_IASA,
        ftCo_CatchAttack_Phys,
        ftCo_CatchAttack_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CatchCut = 218
        ftCo_SM_CatchCut,
        ftCo_MF_CatchWait,
        FtMoveId_Default << 24,
        ftCo_CatchCut_Anim,
        ftCo_CatchCut_IASA,
        ftCo_CatchCut_Phys,
        ftCo_CatchCut_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrowF = 219
        ftCo_SM_ThrowF,
        ftCo_MF_ThrowF,
        FtMoveId_ThrowF << 24,
        ftCo_ThrowF_Anim,
        ftCo_ThrowF_IASA,
        ftCo_ThrowF_Phys,
        ftCo_ThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrowB = 220
        ftCo_SM_ThrowB,
        ftCo_MF_ThrowB,
        FtMoveId_ThrowB << 24,
        ftCo_ThrowB_Anim,
        ftCo_ThrowB_IASA,
        ftCo_ThrowB_Phys,
        ftCo_ThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrowHi = 221
        ftCo_SM_ThrowHi,
        ftCo_MF_ThrowHi,
        FtMoveId_ThrowHi << 24,
        ftCo_ThrowHi_Anim,
        ftCo_ThrowHi_IASA,
        ftCo_ThrowHi_Phys,
        ftCo_ThrowHi_Coll,
        ftCo_ThrowHi_Cam,
    },
    {
        // ftCo_MS_ThrowLw = 222
        ftCo_SM_ThrowLw,
        ftCo_MF_ThrowLw,
        FtMoveId_ThrowLw << 24,
        ftCo_ThrowLw_Anim,
        ftCo_ThrowLw_IASA,
        ftCo_ThrowLw_Phys,
        ftCo_ThrowLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CapturePulledHi = 223
        ftCo_SM_CapturePulledHi,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CapturePulledHi_Anim,
        ftCo_CapturePulledHi_IASA,
        ftCo_CapturePulledHi_Phys,
        ftCo_CapturePulledHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitHi = 224
        ftCo_SM_CaptureWaitHi,
        ftCo_MF_Capture,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_CaptureWaitHi_Anim,
        ftCo_CaptureWaitHi_IASA,
        ftCo_CaptureWaitHi_Phys,
        ftCo_CaptureWaitHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureDamageHi = 225
        ftCo_SM_CaptureDamageHi,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_CaptureDamageHi_Anim,
        ftCo_CaptureDamageHi_IASA,
        ftCo_CaptureDamageHi_Phys,
        ftCo_CaptureDamageHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CapturePulledLw = 226
        ftCo_SM_CapturePulledLw,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CapturePulledLw_Anim,
        ftCo_CapturePulledLw_IASA,
        ftCo_CapturePulledLw_Phys,
        ftCo_CapturePulledLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitLw = 227
        ftCo_SM_CaptureWaitLw,
        ftCo_MF_Capture,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_CaptureWaitLw_Anim,
        ftCo_CaptureWaitLw_IASA,
        ftCo_CaptureWaitLw_Phys,
        ftCo_CaptureWaitLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureDamageLw = 228
        ftCo_SM_CaptureDamageLw,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_CaptureDamageLw_Anim,
        ftCo_CaptureDamageLw_IASA,
        ftCo_CaptureDamageLw_Phys,
        ftCo_CaptureDamageLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureCut = 229
        ftCo_SM_CaptureCut,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureCut_Anim,
        ftCo_CaptureCut_IASA,
        ftCo_CaptureCut_Phys,
        ftCo_CaptureCut_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureJump = 230
        ftCo_SM_CaptureJump,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureJump_Anim,
        ftCo_CaptureJump_IASA,
        ftCo_CaptureJump_Phys,
        ftCo_CaptureJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureNeck = 231
        ftCo_SM_CaptureNeck,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureFoot = 232
        ftCo_SM_CaptureFoot,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_EscapeF = 233
        ftCo_SM_EscapeF,
        Ft_MF_UnkUpdatePhys,
        FtMoveId_Default << 24,
        ftCo_Escape_Anim,
        ftCo_Escape_IASA,
        ftCo_Escape_Phys,
        ftCo_Escape_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_EscapeB = 234
        ftCo_SM_EscapeB,
        Ft_MF_UnkUpdatePhys,
        FtMoveId_Default << 24,
        ftCo_Escape_Anim,
        ftCo_Escape_IASA,
        ftCo_Escape_Phys,
        ftCo_Escape_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_EscapeN = 235
        ftCo_SM_EscapeN,
        Ft_MF_UnkUpdatePhys,
        FtMoveId_Default << 24,
        ftCo_EscapeN_Anim,
        ftCo_EscapeN_IASA,
        ftCo_EscapeN_Phys,
        ftCo_EscapeN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_EscapeAir = 236
        ftCo_SM_EscapeAir,
        Ft_MF_UnkUpdatePhys,
        FtMoveId_Default << 24,
        ftCo_EscapeAir_Anim,
        ftCo_EscapeAir_IASA,
        ftCo_EscapeAir_Phys,
        ftCo_EscapeAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ReboundStop = 237
        ftCo_SM_None,
        Ft_MF_UnkUpdatePhys,
        FtMoveId_Default << 24,
        ftCo_ReboundStop_Anim,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // ftCo_MS_Rebound = 238
        ftCo_SM_Rebound,
        Ft_MF_UnkUpdatePhys,
        FtMoveId_Default << 24,
        ftCo_Rebound_Anim,
        ftCo_Rebound_IASA,
        ftCo_Rebound_Phys,
        ftCo_Rebound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownF = 239
        ftCo_SM_ThrownF,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownF_Anim,
        ftCo_ThrownF_IASA,
        ftCo_ThrownF_Phys,
        ftCo_ThrownF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownB = 240
        ftCo_SM_ThrownB,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownB_Anim,
        ftCo_ThrownB_IASA,
        ftCo_ThrownB_Phys,
        ftCo_ThrownB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownHi = 241
        ftCo_SM_ThrownHi,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownHi_Anim,
        ftCo_ThrownHi_IASA,
        ftCo_ThrownHi_Phys,
        ftCo_ThrownHi_Coll,
        ftCo_ThrownHi_Cam,
    },
    {
        // ftCo_MS_ThrownLw = 242
        ftCo_SM_ThrownLw,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownLw_Anim,
        ftCo_ThrownLw_IASA,
        ftCo_ThrownLw_Phys,
        ftCo_ThrownLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownlwWomen = 243
        ftCo_SM_ThrownlwWomen,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownLw_Anim,
        ftCo_ThrownLw_IASA,
        ftCo_ThrownLw_Phys,
        ftCo_ThrownLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Pass = 244
        ftCo_SM_Pass,
        ftCo_MF_Pass,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_Pass_Anim,
        ftCo_Pass_IASA,
        ftCo_Pass_Phys,
        ftCo_Pass_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Ottotto = 245
        ftCo_SM_Ottotto,
        Ft_MF_SkipMetalB,
        FtMoveId_Default << 24,
        ftCo_Ottotto_Anim,
        ftCo_Ottotto_IASA,
        ftCo_Ottotto_Phys,
        ftCo_Ottotto_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_OttottoWait = 246
        ftCo_SM_OttottoWait,
        ftCo_MF_OttottoWait,
        FtMoveId_Default << 24,
        ftCo_OttottoWait_Anim,
        ftCo_OttottoWait_IASA,
        ftCo_OttottoWait_Phys,
        ftCo_OttottoWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FlyReflectWall = 247
        ftCo_SM_WallDamage,
        ftCo_MF_StopWall,
        FtMoveId_Default << 24,
        ftCo_FlyReflect_Anim,
        ftCo_FlyReflect_IASA,
        ftCo_FlyReflect_Phys,
        ftCo_FlyReflect_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_FlyReflectCeil = 248
        ftCo_SM_StopCeil,
        Ft_MF_SkipMetalB,
        FtMoveId_Default << 24,
        ftCo_FlyReflect_Anim,
        ftCo_FlyReflect_IASA,
        ftCo_FlyReflect_Phys,
        ftCo_FlyReflect_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_StopWall = 249
        ftCo_SM_StopWall,
        ftCo_MF_StopWall,
        FtMoveId_Default << 24,
        ftCo_StopWall_Anim,
        ftCo_StopWall_IASA,
        ftCo_StopWall_Phys,
        ftCo_StopWall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_StopCeil = 250
        ftCo_SM_StopCeil,
        Ft_MF_SkipMetalB,
        FtMoveId_Default << 24,
        ftCo_StopCeil_Anim,
        ftCo_StopCeil_IASA,
        ftCo_StopCeil_Phys,
        ftCo_StopCeil_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_MissFoot = 251
        ftCo_SM_MissFoot,
        Ft_MF_SkipMetalB,
        FtMoveId_Default << 24,
        ftCo_MissFoot_Anim,
        ftCo_MissFoot_IASA,
        ftCo_MissFoot_Phys,
        ftCo_MissFoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CliffCatch = 252
        ftCo_SM_CliffCatch,
        ftCo_MF_CliffCatch,
        FtMoveId_Default << 24,
        ftCo_CliffCatch_Anim,
        ftCo_CliffCatch_IASA,
        ftCo_CliffCatch_Phys,
        ftCo_CliffCatch_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffWait = 253
        ftCo_SM_CliffWait,
        ftCo_MF_CliffWait,
        FtMoveId_Default << 24,
        ftCo_CliffWait_Anim,
        ftCo_CliffWait_IASA,
        ftCo_CliffWait_Phys,
        ftCo_CliffWait_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffClimbSlow = 254
        ftCo_SM_CliffClimbSlow,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffClimb_Anim,
        ftCo_CliffClimb_IASA,
        ftCo_CliffClimb_Phys,
        ftCo_CliffClimb_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffClimbQuick = 255
        ftCo_SM_CliffClimbQuick,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffClimb_Anim,
        ftCo_CliffClimb_IASA,
        ftCo_CliffClimb_Phys,
        ftCo_CliffClimb_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffAttackSlow = 256
        ftCo_SM_CliffAttackSlow,
        ftCo_MF_CliffAttackSlow,
        FtMoveId_CliffAttackSlow << 24,
        ftCo_CliffAttack_Anim,
        ftCo_CliffAttack_IASA,
        ftCo_CliffAttack_Phys,
        ftCo_CliffAttack_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffAttackQuick = 257
        ftCo_SM_CliffAttackQuick,
        ftCo_MF_CliffAttackQuick,
        FtMoveId_CliffAttackQuick << 24,
        ftCo_CliffAttack_Anim,
        ftCo_CliffAttack_IASA,
        ftCo_CliffAttack_Phys,
        ftCo_CliffAttack_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffEscapeSlow = 258
        ftCo_SM_CliffEscapeSlow,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffEscape_Anim,
        ftCo_CliffEscape_IASA,
        ftCo_CliffEscape_Phys,
        ftCo_CliffEscape_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffEscapeQuick = 259
        ftCo_SM_CliffEscapeQuick,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffEscape_Anim,
        ftCo_CliffEscape_IASA,
        ftCo_CliffEscape_Phys,
        ftCo_CliffEscape_Coll,
        ftCo_Cliff_Cam,
    },
    {
        // ftCo_MS_CliffJumpSlow1 = 260
        ftCo_SM_CliffJumpSlow1,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffJump1_Anim,
        ftCo_CliffJump1_IASA,
        ftCo_CliffJump1_Phys,
        ftCo_CliffJump1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CliffJumpSlow2 = 261
        ftCo_SM_CliffJumpSlow2,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffJump2_Anim,
        ftCo_CliffJump2_IASA,
        ftCo_CliffJump2_Phys,
        ftCo_CliffJump2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CliffJumpQuick1 = 262
        ftCo_SM_CliffJumpQuick1,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffJump1_Anim,
        ftCo_CliffJump1_IASA,
        ftCo_CliffJump1_Phys,
        ftCo_CliffJump1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CliffJumpQuick2 = 263
        ftCo_SM_CliffJumpQuick2,
        ftCo_MF_CliffAction,
        FtMoveId_Default << 24,
        ftCo_CliffJump2_Anim,
        ftCo_CliffJump2_IASA,
        ftCo_CliffJump2_Phys,
        ftCo_CliffJump2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AppealSR = 264
        ftCo_SM_AppealSR,
        ftCo_MF_Appeal,
        FtMoveId_Default << 24,
        ftCo_AppealS_Anim,
        ftCo_AppealS_IASA,
        ftCo_AppealS_Phys,
        ftCo_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_AppealSL = 265
        ftCo_SM_AppealSL,
        ftCo_MF_Appeal,
        FtMoveId_Default << 24,
        ftCo_AppealS_Anim,
        ftCo_AppealS_IASA,
        ftCo_AppealS_Phys,
        ftCo_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShoulderedWait = 266
        ftCo_SM_ShoulderedWait,
        ftCo_MF_Shouldered,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_Shouldered_Anim,
        ftCo_Shouldered_IASA,
        ftCo_Shouldered_Phys,
        ftCo_Shouldered_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShoulderedWalkSlow = 267
        ftCo_SM_ShoulderedWalkSlow,
        ftCo_MF_Shouldered,
        FtMoveId_Default << 24,
        ftCo_Shouldered_Anim,
        ftCo_Shouldered_IASA,
        ftCo_Shouldered_Phys,
        ftCo_Shouldered_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShoulderedWalkMiddle = 268
        ftCo_SM_ShoulderedWalkMiddle,
        ftCo_MF_Shouldered,
        FtMoveId_Default << 24,
        ftCo_Shouldered_Anim,
        ftCo_Shouldered_IASA,
        ftCo_Shouldered_Phys,
        ftCo_Shouldered_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShoulderedWalkFast = 269
        ftCo_SM_ShoulderedWalkFast,
        ftCo_MF_Shouldered,
        FtMoveId_Default << 24,
        ftCo_Shouldered_Anim,
        ftCo_Shouldered_IASA,
        ftCo_Shouldered_Phys,
        ftCo_Shouldered_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ShoulderedTurn = 270
        ftCo_SM_ShoulderedTurn,
        ftCo_MF_Shouldered,
        FtMoveId_Default << 24,
        ftCo_Shouldered_Anim,
        ftCo_Shouldered_IASA,
        ftCo_Shouldered_Phys,
        ftCo_Shouldered_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownFF = 271
        ftCo_SM_ThrownFF,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownF_Anim,
        ftCo_ThrownF_IASA,
        ftCo_ThrownF_Phys,
        ftCo_ThrownF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownFB = 272
        ftCo_SM_ThrownFB,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownB_Anim,
        ftCo_ThrownB_IASA,
        ftCo_ThrownB_Phys,
        ftCo_ThrownB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownFHi = 273
        ftCo_SM_ThrownFHi,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownHi_Anim,
        ftCo_ThrownHi_IASA,
        ftCo_ThrownHi_Phys,
        ftCo_ThrownHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownFLw = 274
        ftCo_SM_ThrownFLw,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownLw_Anim,
        ftCo_ThrownLw_IASA,
        ftCo_ThrownLw_Phys,
        ftCo_ThrownLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureCaptain = 275
        ftCo_SM_CaptureCaptain,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureCaptain_Anim,
        ftCo_CaptureCaptain_IASA,
        ftCo_CaptureCaptain_Phys,
        ftCo_CaptureCaptain_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureYoshi = 276
        ftCo_SM_CapturePulledLw,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureYoshi_Anim,
        ftCo_CaptureYoshi_IASA,
        ftCo_CaptureYoshi_Phys,
        ftCo_CaptureYoshi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_YoshiEgg = 277
        ftCo_SM_YoshiEgg,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_YoshiEgg_Anim,
        ftCo_YoshiEgg_IASA,
        ftCo_YoshiEgg_Phys,
        ftCo_YoshiEgg_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureKoopa = 278
        ftCo_SM_None,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureKoopa_Anim,
        ftCo_CaptureKoopa_IASA,
        ftCo_CaptureKoopa_Phys,
        ftCo_CaptureKoopa_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureDamageKoopa = 279
        ftCo_SM_CaptureDamageKoopa,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_CaptureDamageKoopa_Anim,
        ftCo_CaptureDamageKoopa_IASA,
        ftCo_CaptureDamageKoopa_Phys,
        ftCo_CaptureDamageKoopa_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitKoopa = 280
        ftCo_SM_None,
        ftCo_MF_Capture,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_CaptureWaitKoopa_Anim,
        ftCo_CaptureWaitKoopa_IASA,
        ftCo_CaptureWaitKoopa_Phys,
        ftCo_CaptureWaitKoopa_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownKoopaF = 281
        ftCo_SM_ThrownKoopaF,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownKoopaF_Anim,
        ftCo_ThrownKoopaF_IASA,
        ftCo_ThrownKoopaF_Phys,
        ftCo_ThrownKoopaF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownKoopaB = 282
        ftCo_SM_ThrownKoopaB,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownKoopaB_Anim,
        ftCo_ThrownKoopaB_IASA,
        ftCo_ThrownKoopaB_Phys,
        ftCo_ThrownKoopaB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureKoopaAir = 283
        ftCo_SM_None,
        ftCo_MF_CaptureAir,
        FtMoveId_Default << 24,
        ftCo_CaptureKoopaAir_Anim,
        ftCo_CaptureKoopaAir_IASA,
        ftCo_CaptureKoopaAir_Phys,
        ftCo_CaptureKoopaAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureDamageKoopaAir = 284
        ftCo_SM_CaptureDamageKoopaAir,
        ftCo_MF_ThrownAir,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_CaptureDamageKoopaAir_Anim,
        ftCo_CaptureDamageKoopaAir_IASA,
        ftCo_CaptureDamageKoopaAir_Phys,
        ftCo_CaptureDamageKoopaAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitKoopaAir = 285
        ftCo_SM_None,
        ftCo_MF_CaptureAir,
        FtMoveId_Default << 24,
        ftCo_CaptureWaitKoopaAir_Anim,
        ftCo_CaptureWaitKoopaAir_IASA,
        ftCo_CaptureWaitKoopaAir_Phys,
        ftCo_CaptureWaitKoopaAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownKoopaAirF = 286
        ftCo_SM_ThrownKoopaAirF,
        ftCo_MF_ThrownAir,
        FtMoveId_Default << 24,
        ftCo_ThrownKoopaAirF_Anim,
        ftCo_ThrownKoopaAirF_IASA,
        ftCo_ThrownKoopaAirF_Phys,
        ftCo_ThrownKoopaAirF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownKoopaAirB = 287
        ftCo_SM_ThrownKoopaAirB,
        ftCo_MF_ThrownAir,
        FtMoveId_Default << 24,
        ftCo_ThrownKoopaAirB_Anim,
        ftCo_ThrownKoopaAirB_IASA,
        ftCo_ThrownKoopaAirB_Phys,
        ftCo_ThrownKoopaAirB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureKirby = 288
        ftCo_SM_DamageFall,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureKirby_Anim,
        ftCo_CaptureKirby_IASA,
        ftCo_CaptureKirby_Phys,
        ftCo_CaptureKirby_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitKirby = 289
        ftCo_SM_None,
        ftCo_MF_Capture,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_CaptureWaitKirby_Anim,
        ftCo_CaptureWaitKirby_IASA,
        ftCo_CaptureWaitKirby_Phys,
        ftCo_CaptureWaitKirby_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownKirbyStar = 290
        ftCo_SM_ThrownKirbyStar,
        ftCo_MF_ThrownStar,
        FtMoveId_Default << 24,
        ftCo_ThrownKirbyStar_Anim,
        ftCo_ThrownKirbyStar_IASA,
        ftCo_ThrownKirbyStar_Phys,
        ftCo_ThrownKirbyStar_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownCopyStar = 291
        ftCo_SM_ThrownCopyStar,
        ftCo_MF_ThrownStar,
        FtMoveId_Default << 24,
        ftCo_ThrownCopyStar_Anim,
        ftCo_ThrownCopyStar_IASA,
        ftCo_ThrownCopyStar_Phys,
        ftCo_ThrownCopyStar_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownKirby = 292
        ftCo_SM_DamageFall,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownKirby_Anim,
        ftCo_ThrownKirby_IASA,
        ftCo_ThrownKirby_Phys,
        ftCo_ThrownKirby_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BarrelWait = 293
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_BarrelWait_Anim,
        ftCo_BarrelWait_IASA,
        ftCo_BarrelWait_Phys,
        ftCo_BarrelWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Bury = 294
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_Bury_Anim,
        ftCo_Bury_IASA,
        ftCo_Bury_Phys,
        ftCo_Bury_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BuryWait = 295
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_BuryWait_Anim,
        ftCo_BuryWait_IASA,
        ftCo_BuryWait_Phys,
        ftCo_BuryWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_BuryJump = 296
        ftCo_SM_JumpF,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 23),
        ftCo_BuryJump_Anim,
        ftCo_BuryJump_IASA,
        ftCo_BuryJump_Phys,
        ftCo_BuryJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageSong = 297
        ftCo_SM_FuraSleepStart,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_DamageSong_Anim,
        ftCo_DamageSong_IASA,
        ftCo_DamageSong_Phys,
        ftCo_DamageSong_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageSongWait = 298
        ftCo_SM_FuraSleepLoop,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_DamageSongWait_Anim,
        ftCo_DamageSongWait_IASA,
        ftCo_DamageSongWait_Phys,
        ftCo_DamageSongWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageSongRv = 299
        ftCo_SM_FuraSleepEnd,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_DamageSongRv_Anim,
        ftCo_DamageSongRv_IASA,
        ftCo_DamageSongRv_Phys,
        ftCo_DamageSongRv_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageBind = 300
        ftCo_SM_FuraFura,
        ftCo_MF_Dazed,
        FtMoveId_Default << 24,
        ftCo_DamageBind_Anim,
        ftCo_DamageBind_IASA,
        ftCo_DamageBind_Phys,
        ftCo_DamageBind_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureMewtwo = 301
        ftCo_SM_None,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureMewtwoAir = 302
        ftCo_SM_None,
        ftCo_MF_CaptureAir,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownMewtwo = 303
        ftCo_SM_ThrownMewtwo,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownMewtwo_Anim,
        ftCo_ThrownMewtwo_IASA,
        ftCo_ThrownMewtwo_Phys,
        ftCo_ThrownMewtwo_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownMewtwoAir = 304
        ftCo_SM_ThrownMewtwoAir,
        ftCo_MF_ThrownAir,
        FtMoveId_Default << 24,
        ftCo_ThrownMewtwoAir_Anim,
        ftCo_ThrownMewtwoAir_IASA,
        ftCo_ThrownMewtwoAir_Phys,
        ftCo_ThrownMewtwoAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_WarpStarJump = 305
        ftCo_SM_Squat,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_WarpStarJump_Anim,
        ftCo_WarpStarJump_IASA,
        ftCo_WarpStarJump_Phys,
        ftCo_WarpStarJump_Coll,
        ftCo_WarpStarJump_Cam,
    },
    {
        // ftCo_MS_WarpStarFall = 306
        ftCo_SM_SquatWait,
        ftCo_MF_WarpStarFall,
        FtMoveId_WarpStarFall << 24,
        ftCo_WarpStarFall_Anim,
        ftCo_WarpStarFall_IASA,
        ftCo_WarpStarFall_Phys,
        ftCo_WarpStarFall_Coll,
        ftCo_WarpStarFall_Cam,
    },
    {
        // ftCo_MS_HammerWait = 307
        ftCo_SM_HammerWait,
        ftCo_MF_Hammer,
        (FtMoveId_Hammer << 24) | ftCo_MF_Rebirth,
        ftCo_HammerWait_Anim,
        ftCo_HammerWait_IASA,
        ftCo_HammerWait_Phys,
        ftCo_HammerWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HammerWalk = 308
        ftCo_SM_HammerMove,
        ftCo_MF_HammerWalk,
        (FtMoveId_Hammer << 24) | (1 << 23),
        ftCo_HammerWalk_Anim,
        ftCo_HammerWalk_IASA,
        ftCo_HammerWalk_Phys,
        ftCo_HammerWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HammerTurn = 309
        ftCo_SM_HammerMove,
        ftCo_MF_HammerTurn,
        (FtMoveId_Hammer << 24) | (1 << 23),
        ftCo_HammerTurn_Anim,
        ftCo_HammerTurn_IASA,
        ftCo_HammerTurn_Phys,
        ftCo_HammerTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HammerKneeBend = 310
        ftCo_SM_HammerMove,
        ftCo_MF_Hammer,
        (FtMoveId_Hammer << 24) | (1 << 23),
        ftCo_HammerKneeBend_Anim,
        ftCo_HammerKneeBend_IASA,
        ftCo_HammerKneeBend_Phys,
        ftCo_HammerKneeBend_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HammerFall = 311
        ftCo_SM_HammerMove,
        ftCo_MF_HammerFall,
        (FtMoveId_Hammer << 24) | (1 << 23),
        ftCo_HammerFall_Anim,
        ftCo_HammerFall_IASA,
        ftCo_HammerFall_Phys,
        ftCo_HammerFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HammerJump = 312
        ftCo_SM_HammerMove,
        ftCo_MF_HammerJump,
        (FtMoveId_Hammer << 24) | (1 << 23),
        ftCo_HammerJump_Anim,
        ftCo_HammerJump_IASA,
        ftCo_HammerJump_Phys,
        ftCo_HammerJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_HammerLanding = 313
        ftCo_SM_HammerMove,
        ftCo_MF_Hammer,
        (FtMoveId_Hammer << 24) | (1 << 22),
        ftCo_HammerLanding_Anim,
        ftCo_HammerLanding_IASA,
        ftCo_HammerLanding_Phys,
        ftCo_HammerLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoGiantStart = 314
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoGiantStart_Anim,
        NULL,
        NULL,
        ftCo_KinokoGiantStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoGiantStartAir = 315
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoGiantStartAir_Anim,
        NULL,
        NULL,
        ftCo_KinokoGiantStartAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoGiantEnd = 316
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoGiantEnd_Anim,
        NULL,
        NULL,
        ftCo_KinokoGiantEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoGiantEndAir = 317
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoGiantEndAir_Anim,
        NULL,
        NULL,
        ftCo_KinokoGiantEndAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoSmallStart = 318
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoSmallStart_Anim,
        NULL,
        NULL,
        ftCo_KinokoSmallStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoSmallStartAir = 319
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoSmallStartAir_Anim,
        NULL,
        NULL,
        ftCo_KinokoSmallStartAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoSmallEnd = 320
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoSmallEnd_Anim,
        NULL,
        NULL,
        ftCo_KinokoSmallEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KinokoSmallEndAir = 321
        ftCo_SM_None,
        Ft_MF_SkipModelPartVis,
        FtMoveId_Default << 24,
        ftCo_KinokoSmallEndAir_Anim,
        NULL,
        NULL,
        ftCo_KinokoSmallEndAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Entry = 322
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_Entry_Anim,
        ftCo_Entry_IASA,
        ftCo_Entry_Phys,
        ftCo_Entry_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_EntryStart = 323
        ftCo_SM_EntryStart,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_EntryStart_Anim,
        ftCo_EntryStart_IASA,
        ftCo_EntryStart_Phys,
        ftCo_EntryStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_EntryEnd = 324
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_EntryEnd_Anim,
        ftCo_EntryEnd_IASA,
        ftCo_EntryEnd_Phys,
        ftCo_EntryEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageIce = 325
        ftCo_SM_None,
        ftCo_MF_Damage,
        FtMoveId_Default << 24,
        ftCo_DamageIce_Anim,
        ftCo_DamageIce_IASA,
        ftCo_DamageIce_Phys,
        ftCo_DamageIce_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DamageIceJump = 326
        ftCo_SM_Fall,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_DamageIceJump_Anim,
        ftCo_DamageIceJump_IASA,
        ftCo_DamageIceJump_Phys,
        ftCo_DamageIceJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureMasterHand = 327
        ftCo_SM_None,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftMh_CaptureMasterHand_Anim,
        ftMh_CaptureMasterHand_IASA,
        ftMh_CaptureMasterHand_Phys,
        ftMh_CaptureMasterHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureDamageMasterHand = 328
        ftCo_SM_None,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftMh_CaptureDamageMasterHand_Anim,
        ftMh_CaptureDamageMasterHand_IASA,
        ftMh_CaptureDamageMasterHand_Phys,
        ftMh_CaptureDamageMasterHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitMasterHand = 329
        ftCo_SM_None,
        ftCo_MF_Capture,
        (FtMoveId_Default << 24) | (1 << 22),
        ftMh_CaptureWaitMasterHand_Anim,
        ftMh_CaptureWaitMasterHand_IASA,
        ftMh_CaptureWaitMasterHand_Phys,
        ftMh_CaptureWaitMasterHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownMasterHand = 330
        ftCo_SM_None,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftMh_ThrownMasterHand_Anim,
        ftMh_ThrownMasterHand_IASA,
        ftMh_ThrownMasterHand_Phys,
        ftMh_ThrownMasterHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureKirbyYoshi = 331
        ftCo_SM_CapturePulledLw,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureKirbyYoshi_Anim,
        ftCo_CaptureKirbyYoshi_IASA,
        ftCo_CaptureKirbyYoshi_Phys,
        ftCo_CaptureKirbyYoshi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_KirbyYoshiEgg = 332
        ftCo_SM_KirbyYoshiEgg,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_KirbyYoshiEgg_Anim,
        ftCo_KirbyYoshiEgg_IASA,
        ftCo_KirbyYoshiEgg_Phys,
        ftCo_KirbyYoshiEgg_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureLeadead = 333
        ftCo_SM_None,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureLeadead_Anim,
        ftCo_CaptureLeadead_IASA,
        ftCo_CaptureLeadead_Phys,
        ftCo_CaptureLeadead_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureLikelike = 334
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        FtMoveId_Default << 24,
        ftCo_CaptureLikelike_Anim,
        ftCo_CaptureLikelike_IASA,
        ftCo_CaptureLikelike_Phys,
        ftCo_CaptureLikelike_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_DownReflect = 335
        ftCo_SM_WallDamage,
        Ft_MF_SkipMetalB,
        FtMoveId_Default << 24,
        ftCo_DownReflect_Anim,
        ftCo_DownReflect_IASA,
        ftCo_DownReflect_Phys,
        ftCo_DownReflect_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureCrazyHand = 336
        ftCo_SM_None,
        ftCo_MF_Capture,
        FtMoveId_Default << 24,
        ftCo_CaptureCrazyHand_Anim,
        ftCo_CaptureCrazyHand_IASA,
        ftCo_CaptureCrazyHand_Phys,
        ftCo_CaptureCrazyHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureDamageCrazyHand = 337
        ftCo_SM_None,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_CaptureDamageCrazyHand_Anim,
        ftCo_CaptureDamageCrazyHand_IASA,
        ftCo_CaptureDamageCrazyHand_Phys,
        ftCo_CaptureDamageCrazyHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_CaptureWaitCrazyHand = 338
        ftCo_SM_None,
        ftCo_MF_Capture,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_CaptureWaitCrazyHand_Anim,
        ftCo_CaptureWaitCrazyHand_IASA,
        ftCo_CaptureWaitCrazyHand_Phys,
        ftCo_CaptureWaitCrazyHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_ThrownCrazyHand = 339
        ftCo_SM_None,
        ftCo_MF_Thrown,
        FtMoveId_Default << 24,
        ftCo_ThrownCrazyHand_Anim,
        ftCo_ThrownCrazyHand_IASA,
        ftCo_ThrownCrazyHand_Phys,
        ftCo_ThrownCrazyHand_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCo_MS_Barrel = 340
        ftCo_SM_None,
        ftCo_MF_Rebirth,
        (FtMoveId_Default << 24) | (1 << 22),
        ftCo_Barrel_Anim,
        ftCo_Barrel_IASA,
        ftCo_Barrel_Phys,
        ftCo_Barrel_Coll,
        ftCamera_UpdateCameraBox,
    },
};

MotionState ftData_803C52A0[14] = {
    {
        ftCo_SM_DeadUpFallHitCamera,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_800BED84,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_DeadUpFallHitCameraFlat,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Wait1_0,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_800BEF00,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Wait2,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Unk004,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Unk005,
        Ft_MF_None,
        FtMoveId_Default << 24,
        ftCo_800BEFD0,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Wait1_1,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_WalkSlow,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_WalkMiddle,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_WalkFast,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Turn,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_TurnRun,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Dash,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Run,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};
