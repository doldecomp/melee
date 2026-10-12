#include "ftmarsspecials.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include "forward.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>

void ftMs_SpecialS_Enter(HSD_GObj* gobj)
{
    u8 _[8];

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.y = 0.0f;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[1] = 0;
        fp->cmd_vars[0] = 0;
        fp->mv.ms.specials.x0 = 0;

        {
            enum_t msid;
            if (fp->ground_or_air == GA_Ground) {
                msid = ftMs_MS_SpecialS1;
            } else {
                msid = ftMs_MS_SpecialAirS1;
            }

            Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, 0);
        }
    }

    ftAnim_8006EBA4(gobj);
}

void ftMs_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    MarsAttributes* da = getFtSpecialAttrsD(fp0);

    fp0->self_vel.x = fp0->self_vel.x / da->x14;
    if ((signed) fp0->u.ms.x222C == 0) {
        fp0->u.ms.x222C = 1;
        fp0->self_vel.y = da->x1C;
    } else {
        fp0->self_vel.y = 0;
    }

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->cmd_vars[1] = 0;
        fp1->cmd_vars[0] = 0;
        fp1->mv.ms.specials.x0 = 0;

        {
            enum_t msid;
            if (fp1->ground_or_air == GA_Ground) {
                msid = ftMs_MS_SpecialS1;
            } else {
                msid = ftMs_MS_SpecialAirS1;
            }

            Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, 0);
        }
    }

    ftAnim_8006EBA4(gobj);
}

void ftMs_SpecialAirS1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftMs_SpecialAirS1_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[1] == 0 &&
            (fp->input.pressed_buttons & HSD_PAD_AB) != 0)
        {
            ftMs_SpecialS_80137A9C(gobj);
        }
    } else {
        if ((fp->input.pressed_buttons & HSD_PAD_AB) != 0) {
            fp->cmd_vars[1] = 1;
        }
    }
}

void ftMs_SpecialAirS1_Phys(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;

    if (fp->ground_or_air == GA_Ground) {
        // Physics_Friction
        ft_80084F3C(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        ftCommon_Fall(fp, da->x20, da->x24);
        ftCommon_CalcSelfAccel_Deaccel(fp, da->x18);
    }
}

void ftMs_SpecialAirS1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (!ft_800827A0(gobj)) {
            ftMs_SpecialS_801376E8(gobj);
        }
    } else {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
        if (ft_80081D0C(gobj)) {
            // MarthSideBAir->Ground
            ftMs_SpecialS_80137748(gobj);
        }
    }
}

static u32 const transition_flags =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit | Ft_MF_SkipMatAnim |
    Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | Ft_MF_KeepSwordTrail |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftMs_SpecialS_801376E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    ftCommon_GroundToAirStateChange(gobj, fp, ftMs_MS_SpecialAirS1,
                                    transition_flags);
}

void ftMs_SpecialS_80137748(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.ms.x222C = 0;

    // Air_SetAsGrounded2
    ftCommon_AirToGroundStateChange(gobj, fp, ftMs_MS_SpecialS1,
                                    transition_flags);
}

void ftMs_SpecialS2_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            // MS_014_Wait_PlayerCheck
            ft_8008A2BC(gobj);
        } else {
            // MS_029_Fall
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftMs_SpecialS2_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[1] == 0 &&
            (fp->input.pressed_buttons & HSD_PAD_AB) != 0)
        {
            ftMs_SpecialS_80137E0C(gobj);
        }
    } else {
        if ((fp->input.pressed_buttons & HSD_PAD_AB) != 0) {
            fp->cmd_vars[1] = 1;
        }
    }
}

void ftMs_SpecialS2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = getFtSpecialAttrsD(fp);

    u8 _[8];

    if (fp->ground_or_air == GA_Ground) {
        // Physics_Friction
        ft_80084F3C(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        ftCommon_Fall(fp, da->x20, da->x24);
        ftCommon_CalcSelfAccel_Deaccel(fp, da->x18);
    }
}

void ftMs_SpecialS2_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (!ft_800827A0(gobj)) {
            ftMs_SpecialS_80137940(gobj);
        }
    } else if (ft_80081D0C(gobj)) {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)

        // MarthSideB2Air->Ground
        ftMs_SpecialS_801379D0(gobj);
    }
}

void ftMs_SpecialS_80137940(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    ftCommon_8007D5D4(fp);

    switch (fp->motion_id) {
    case ftMs_MS_SpecialS2Hi:
        msid = ftMs_MS_SpecialAirS2Hi;
        break;
    case ftMs_MS_SpecialS2Lw:
        msid = ftMs_MS_SpecialAirS2Lw;
        break;
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_801379D0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->u.ms.x222C = 0;
    ftCommon_8007D7FC(fp);

    switch (fp->motion_id) {
    case ftMs_MS_SpecialAirS2Hi:
        msid = ftMs_MS_SpecialS2Hi;
        break;
    case ftMs_MS_SpecialAirS2Lw:
        msid = ftMs_MS_SpecialS2Lw;
        break;
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_80137A68(HSD_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

void ftMs_SpecialS_80137A9C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x21EC = &ftMs_SpecialS_80137A68;

    if (fp->input.lstick[0].y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground) {
            msid = ftMs_MS_SpecialS2Hi;
        } else {
            msid = ftMs_MS_SpecialAirS2Hi;
        }
    } else {
        if (fp->ground_or_air == GA_Ground) {
            msid = ftMs_MS_SpecialS2Lw;
        } else {
            msid = ftMs_MS_SpecialAirS2Lw;
        }
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipAttackCount, 0, 1, 0, 0);
}

void ftMs_SpecialS3_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            // MS_014_Wait_PlayerCheck
            ft_8008A2BC(gobj);
        } else {
            // MS_029_Fall
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftMs_SpecialS3_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[1] == 0 &&
            (fp->input.pressed_buttons & HSD_PAD_AB) != 0)
        {
            ftMs_SpecialS_80138148(gobj);
        }
    } else {
        if ((fp->input.pressed_buttons & HSD_PAD_AB) != 0) {
            fp->cmd_vars[1] = 1;
        }
    }
}

void ftMs_SpecialS3_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* sa = getFtSpecialAttrsD(fp);

    u8 _[8];

    if (fp->ground_or_air == GA_Ground) {
        // somethingFriction
        ft_80084FA8(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        ftCommon_Fall(fp, sa->x20, sa->x24);
        ft_80085204(gobj);
    }
}

void ftMs_SpecialS3_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (!ft_800827A0(gobj)) {
            ftMs_SpecialS_80137CBC(gobj);
        }
    } else {
        // EnvironmentCollision_CheckForGroundOnly_NoLedgeGrab
        if (ft_80081D0C(gobj)) {
            ftMs_SpecialS_80137D60(gobj);
        }
    }
}

void ftMs_SpecialS_80137CBC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    ftCommon_8007D5D4(fp);
    switch (fp->motion_id) {
    case ftMs_MS_SpecialS3Hi:
        msid = ftMs_MS_SpecialAirS3Hi;
        break;
    case ftMs_MS_SpecialS3Lw:
        msid = ftMs_MS_SpecialAirS3Lw;
        break;
    case ftMs_MS_SpecialS3S:
        msid = ftMs_MS_SpecialAirS3S;
        break;
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_80137D60(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;
    fp->u.ms.x222C = 0;

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);

    switch (fp->motion_id) {
    case ftMs_MS_SpecialAirS3Hi:
        msid = ftMs_MS_SpecialS3Hi;
        break;
    case ftMs_MS_SpecialAirS3Lw:
        msid = ftMs_MS_SpecialS3Lw;
        break;
    case ftMs_MS_SpecialAirS3S:
        msid = ftMs_MS_SpecialS3S;
        break;
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_80137E0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x21EC = &ftMs_SpecialS_80137A68;

    if (fp->input.lstick[0].y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground) {
            msid = ftMs_MS_SpecialS3Hi;
        } else {
            msid = ftMs_MS_SpecialAirS3Hi;
        }
    } else {
        if (fp->input.lstick[0].y < -p_ftCommonData->x21C) {
            if (fp->ground_or_air == GA_Ground) {
                msid = ftMs_MS_SpecialS3Lw;
            } else {
                msid = ftMs_MS_SpecialAirS3Lw;
            }
        } else {
            if (fp->ground_or_air == GA_Ground) {
                msid = ftMs_MS_SpecialS3S;
            } else {
                msid = ftMs_MS_SpecialAirS3S;
            }
        }
    }

    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipAttackCount, 0, 1, 0, 0);
}

void ftMs_SpecialS4_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            // MS_014_Wait_PlayerCheck
            ft_8008A2BC(gobj);
        } else {
            // MS_029_Fall
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftMs_SpecialS4_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialS4_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* sa = getFtSpecialAttrsD(fp);

    u8 _[8];

    if (fp->ground_or_air == GA_Ground) {
        // somethingFriction
        ft_80084FA8(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        ftCommon_Fall(fp, sa->x20, sa->x24);
        ft_80085204(gobj);
    }
}

void ftMs_SpecialS4_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (ft_800827A0(gobj) == 0) {
            ftMs_SpecialS_80137FF8(gobj);
        }
    } else {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
        if (ft_80081D0C(gobj) != 0) {
            ftMs_SpecialS_8013809C(gobj);
        }
    }
}

void ftMs_SpecialS_80137FF8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    ftCommon_8007D5D4(fp);

    switch (fp->motion_id) {
    case ftMs_MS_SpecialS4Hi:
        msid = ftMs_MS_SpecialAirS4Hi;
        break;
    case ftMs_MS_SpecialS4Lw:
        msid = ftMs_MS_SpecialAirS4Lw;
        break;
    case ftMs_MS_SpecialS4S:
        msid = ftMs_MS_SpecialAirS4S;
        break;
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_8013809C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    fp->u.ms.x222C = 0;

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);

    switch (fp->motion_id) {
    case ftMs_MS_SpecialAirS4Hi:
        msid = ftMs_MS_SpecialS4Hi;
        break;
    case ftMs_MS_SpecialAirS4Lw:
        msid = ftMs_MS_SpecialS4Lw;
        break;
    case ftMs_MS_SpecialAirS4S:
        msid = ftMs_MS_SpecialS4S;
        break;
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_80138148(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x21EC = &ftMs_SpecialS_80137A68;

    if (fp->input.lstick[0].y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground) {
            msid = ftMs_MS_SpecialS4Hi;
        } else {
            msid = ftMs_MS_SpecialAirS4Hi;
        }
    } else {
        if (fp->input.lstick[0].y < -p_ftCommonData->x21C) {
            if (fp->ground_or_air == GA_Ground) {
                msid = ftMs_MS_SpecialS4Lw;
            } else {
                msid = ftMs_MS_SpecialAirS4Lw;
            }
        } else {
            if (fp->ground_or_air == GA_Ground) {
                msid = ftMs_MS_SpecialS4S;
            } else {
                msid = ftMs_MS_SpecialAirS4S;
            }
        }
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipAttackCount, 0, 1, 0, 0);
}
