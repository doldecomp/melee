#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ftMars/ftMars.h"
#include "melee/ft/inlines.h"

void ftMars_SpecialS_StartMotion(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x80_self_vel.y = 0.0f;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2204_ftcmd_var1 = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.ms.specials.x0 = 0;

        {
            enum_t msid;
            if (fp->ground_or_air == GA_Ground)
                msid = 349;
            else
                msid = 358;

            Fighter_ChangeMotionState(gobj, msid, 0, 0, 0, 1, 0);
        }
    }

    ftAnim_8006EBA4(gobj);
}

void ftMars_SpecialAirS_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    MarsAttributes* attr = getFtSpecialAttrsD(fp0);

    fp0->x80_self_vel.x = fp0->x80_self_vel.x / attr->x14;
    if ((signed) fp0->fv.ms.x222C == 0) {
        fp0->fv.ms.x222C = 1;
        fp0->x80_self_vel.y = attr->x1C;
    } else {
        fp0->x80_self_vel.y = 0;
    }

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->x2204_ftcmd_var1 = 0;
        fp1->x2200_ftcmd_var0 = 0;
        fp1->mv.ms.specials.x0 = 0;

        {
            enum_t msid;
            if (fp1->ground_or_air == GA_Ground)
                msid = 349;
            else
                msid = 358;

            Fighter_ChangeMotionState(gobj, msid, 0, 0, 0, 1, 0);
        }
    }

    ftAnim_8006EBA4(gobj);
}

void ftMars_80137558(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground)
            func_8008A2BC(gobj);
        else
            func_800CC730(gobj);
    }
}

void ftMars_801375B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2204_ftcmd_var1 == 0 && (fp->input.x668 & HSD_BUTTON_AB) != 0)
            ftMars_80137A9C(gobj);
    } else {
        if ((fp->input.x668 & HSD_BUTTON_AB) != 0)
            fp->x2204_ftcmd_var1 = 1;
    }
}

void ftMars_80137618(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* attr = fp->x2D4_specialAttributes;

    if (fp->ground_or_air == GA_Ground) {
        // Physics_Friction
        func_80084F3C(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, attr->x20, attr->x24);
        func_8007CE94(fp, attr->x18);
    }
}

void ftMars_8013767C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (!func_800827A0(gobj))
            ftMars_801376E8(gobj);
    } else {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
        if (func_80081D0C(gobj)) {
            // MarthSideBAir->Ground
            ftMars_80137748(gobj);
        }
    }
}

static Fighter_MotionStateChangeFlags const transition_flags =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_PreserveSwordTrail |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

void ftMars_801376E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 358, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137748(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.ms.x222C = 0;

    // Air_SetAsGrounded2
    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 349, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_801377B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            // MS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // MS_029_Fall
            func_800CC730(gobj);
        }
    }
}

void ftMars_80137810(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2204_ftcmd_var1 == 0 && (fp->input.x668 & HSD_BUTTON_AB) != 0)
            ftMars_80137E0C(gobj);
    } else {
        if ((fp->input.x668 & HSD_BUTTON_AB) != 0) {
            fp->x2204_ftcmd_var1 = 1;
        }
    }
}

void ftMars_80137870(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* attr = getFtSpecialAttrsD(fp);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ground_or_air == GA_Ground) {
        // Physics_Friction
        func_80084F3C(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, attr->x20, attr->x24);
        func_8007CE94(fp, attr->x18);
    }
}

void ftMars_801378D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (!func_800827A0(gobj))
            ftMars_80137940(gobj);
    } else if (func_80081D0C(gobj)) {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)

        // MarthSideB2Air->Ground
        ftMars_801379D0(gobj);
    }
}

void ftMars_80137940(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    func_8007D5D4(fp);

    switch (fp->motion_id) {
    case 350:
        msid = 359;
        break;
    case 351:
        msid = 360;
        break;
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_801379D0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->fv.ms.x222C = 0;
    func_8007D7FC(fp);

    switch (fp->motion_id) {
    case 359:
        msid = 350;
        break;
    case 360:
        msid = 351;
        break;
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137A68(HSD_GObj* gobj)
{
    func_80089824(gobj);
    func_800892A0(gobj);
}

void ftMars_80137A9C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &ftMars_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground)
            msid = 350;
        else
            msid = 359;
    } else {
        if (fp->ground_or_air == GA_Ground)
            msid = 351;
        else
            msid = 360;
    }
    Fighter_ChangeMotionState(gobj, msid, FtStateChange_SkipUpdateAttackCount,
                              0, 0, 1, 0);
}

void ftMars_80137B34(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            // MS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // MS_029_Fall
            func_800CC730(gobj);
        }
    }
}

void ftMars_80137B94(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2204_ftcmd_var1 == 0 && (fp->input.x668 & HSD_BUTTON_AB) != 0)
            ftMars_80138148(gobj);
    } else {
        if ((fp->input.x668 & HSD_BUTTON_AB) != 0)
            fp->x2204_ftcmd_var1 = 1;
    }
}

void ftMars_80137BF4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* sa = getFtSpecialAttrsD(fp);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ground_or_air == GA_Ground) {
        // somethingFriction
        func_80084FA8(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, sa->x20, sa->x24);
        func_80085204(gobj);
    }
}

void ftMars_80137C50(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (!func_800827A0(gobj))
            ftMars_80137CBC(gobj);
    } else {
        // EnvironmentCollision_CheckForGroundOnly_NoLedgeGrab
        if (func_80081D0C(gobj))
            ftMars_80137D60(gobj);
    }
}

void ftMars_80137CBC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
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
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137D60(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;
    fp->fv.ms.x222C = 0;

    // Air_SetAsGrounded2
    func_8007D7FC(fp);

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

    Fighter_ChangeMotionState(gobj, msid, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137E0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &ftMars_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground)
            msid = 352;
        else
            msid = 361;
    } else {
        if (fp->input.x624_lstick_y < -p_ftCommonData->x21C) {
            if (fp->ground_or_air == GA_Ground)
                msid = 354;
            else
                msid = 363;
        } else {
            if (fp->ground_or_air == GA_Ground)
                msid = 353;
            else
                msid = 362;
        }
    }

    Fighter_ChangeMotionState(gobj, msid, FtStateChange_SkipUpdateAttackCount,
                              0, 0, 1, 0);
}

void ftMars_80137ECC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            // MS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // MS_029_Fall
            func_800CC730(gobj);
        }
    }
}

void ftMars_80137F2C(HSD_GObj* gobj) {}

void ftMars_80137F30(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* sa = getFtSpecialAttrsD(fp);

#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ground_or_air == GA_Ground) {
        // somethingFriction
        func_80084FA8(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, sa->x20, sa->x24);
        func_80085204(gobj);
    }
}

void ftMars_80137F8C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (func_800827A0(gobj) == 0)
            ftMars_80137FF8(gobj);
    } else {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
        if (func_80081D0C(gobj) != 0)
            ftMars_8013809C(gobj);
    }
}

void ftMars_80137FF8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);

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
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_8013809C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t msid;

    fp->fv.ms.x222C = 0;

    // Air_SetAsGrounded2
    func_8007D7FC(fp);

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
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ChangeMotionState(gobj, msid, transition_flags, 0,
                              fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80138148(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t msid;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &ftMars_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->ground_or_air == GA_Ground)
            msid = 355;
        else
            msid = 364;
    } else {
        if (fp->input.x624_lstick_y < -p_ftCommonData->x21C) {
            if (fp->ground_or_air == GA_Ground)
                msid = 357;
            else
                msid = 366;
        } else {
            if (fp->ground_or_air == GA_Ground)
                msid = 356;
            else
                msid = 365;
        }
    }
    Fighter_ChangeMotionState(gobj, msid, FtStateChange_SkipUpdateAttackCount,
                              0, 0, 1, 0);
}
