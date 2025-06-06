#include <platform.h>

#include "ftMs_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftMars/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <baselib/debug.h>

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
                msid = 349;
            } else {
                msid = 358;
            }

            Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, 0);
        }
    }

    ftAnim_8006EBA4(gobj);
}

void ftMs_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    MarsAttributes* da = getFtSpecialAttrsD(fp0);

    fp0->self_vel.x = fp0->self_vel.x / da->x14;
    if ((signed) fp0->fv.ms.x222C == 0) {
        fp0->fv.ms.x222C = 1;
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
                msid = 349;
            } else {
                msid = 358;
            }

            Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, 0);
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
            ftCo_800CC730(gobj);
        }
    }
}

void ftMs_SpecialAirS1_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[1] == 0 && (fp->input.x668 & HSD_PAD_AB) != 0) {
            ftMs_SpecialS_80137A9C(gobj);
        }
    } else {
        if ((fp->input.x668 & HSD_PAD_AB) != 0) {
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
        ftCommon_8007D494(fp, da->x20, da->x24);
        ftCommon_8007CE94(fp, da->x18);
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
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 358, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_80137748(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.ms.x222C = 0;

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 349, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
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
            ftCo_800CC730(gobj);
        }
    }
}

void ftMs_SpecialS2_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[1] == 0 && (fp->input.x668 & HSD_PAD_AB) != 0) {
            ftMs_SpecialS_80137E0C(gobj);
        }
    } else {
        if ((fp->input.x668 & HSD_PAD_AB) != 0) {
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
        ftCommon_8007D494(fp, da->x20, da->x24);
        ftCommon_8007CE94(fp, da->x18);
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
    case 350:
        msid = 359;
        break;
    case 351:
        msid = 360;
        break;
#ifdef BUGFIX
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_801379D0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->fv.ms.x222C = 0;
    ftCommon_8007D7FC(fp);

    switch (fp->motion_id) {
    case 359:
        msid = 350;
        break;
    case 360:
        msid = 351;
        break;
#ifdef BUGFIX
    default:
        HSD_ASSERT(__LINE__, false);
#endif
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

    if (fp->input.lstick.y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground) {
            msid = 350;
        } else {
            msid = 359;
        }
    } else {
        if (fp->ground_or_air == GA_Ground) {
            msid = 351;
        } else {
            msid = 360;
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
            ftCo_800CC730(gobj);
        }
    }
}

void ftMs_SpecialS3_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[1] == 0 && (fp->input.x668 & HSD_PAD_AB) != 0) {
            ftMs_SpecialS_80138148(gobj);
        }
    } else {
        if ((fp->input.x668 & HSD_PAD_AB) != 0) {
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
        ftCommon_8007D494(fp, sa->x20, sa->x24);
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
    case 352:
        msid = 361;
        break;
    case 354:
        msid = 363;
        break;
    case 353:
        msid = 362;
        break;
#ifdef BUGFIX
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_80137D60(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;
    fp->fv.ms.x222C = 0;

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);

    switch (fp->motion_id) {
    case 361:
        msid = 352;
        break;
    case 363:
        msid = 354;
        break;
    case 362:
        msid = 353;
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

    if (fp->input.lstick.y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground) {
            msid = 352;
        } else {
            msid = 361;
        }
    } else {
        if (fp->input.lstick.y < -p_ftCommonData->x21C) {
            if (fp->ground_or_air == GA_Ground) {
                msid = 354;
            } else {
                msid = 363;
            }
        } else {
            if (fp->ground_or_air == GA_Ground) {
                msid = 353;
            } else {
                msid = 362;
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
            ftCo_800CC730(gobj);
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
        ftCommon_8007D494(fp, sa->x20, sa->x24);
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
    case 355:
        msid = 364;
        break;
    case 357:
        msid = 366;
        break;
    case 356:
        msid = 365;
        break;
#ifdef BUGFIX
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftMs_SpecialS_8013809C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    fp->fv.ms.x222C = 0;

    // Air_SetAsGrounded2
    ftCommon_8007D7FC(fp);

    switch (fp->motion_id) {
    case 364:
        msid = 355;
        break;
    case 366:
        msid = 357;
        break;
    case 365:
        msid = 356;
        break;
#ifdef BUGFIX
    default:
        HSD_ASSERT(__LINE__, false);
#endif
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

    if (fp->input.lstick.y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground) {
            msid = 355;
        } else {
            msid = 364;
        }
    } else {
        if (fp->input.lstick.y < -p_ftCommonData->x21C) {
            if (fp->ground_or_air == GA_Ground) {
                msid = 357;
            } else {
                msid = 366;
            }
        } else {
            if (fp->ground_or_air == GA_Ground) {
                msid = 356;
            } else {
                msid = 365;
            }
        }
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipAttackCount, 0, 1, 0, 0);
}
