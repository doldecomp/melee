#include "melee/ft/inlines.h"
#include <melee/ft/chara/ftMars/ftMars.h>

#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcommon.h>

void ftMars_SpecialS_StartAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x80_self_vel.y = 0.0f;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2204_ftcmd_var1 = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->x2340_stateVar1 = 0;

        {
            enum_t asid;
            if (fp->xE0_ground_or_air == GA_Ground)
                asid = 349;
            else
                asid = 358;

            Fighter_ActionStateChange_800693AC(gobj, asid, 0, 0, 0, 1, 0);
        }
    }

    func_8006EBA4(gobj);
}

void ftMars_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    MarsAttributes* attr = getFtSpecialAttrsD(fp0);

    fp0->x80_self_vel.x = fp0->x80_self_vel.x / attr->x14;
    if ((signed) fp0->sa.mars.x222C == 0) {
        fp0->sa.mars.x222C = 1;
        fp0->x80_self_vel.y = attr->x1C;
    } else {
        fp0->x80_self_vel.y = 0;
    }

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->x2204_ftcmd_var1 = 0;
        fp1->x2200_ftcmd_var0 = 0;
        fp1->x2340_stateVar1 = 0;

        {
            enum_t asid;
            if (fp1->xE0_ground_or_air == GA_Ground)
                asid = 349;
            else
                asid = 358;

            Fighter_ActionStateChange_800693AC(gobj, asid, 0, 0, 0, 1, 0);
        }
    }

    func_8006EBA4(gobj);
}

void ftMars_80137558(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->xE0_ground_or_air == GA_Ground)
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
    u8 unused[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* attr = fp->x2D4_specialAttributes;

    if (fp->xE0_ground_or_air == GA_Ground) {
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

    if (fp->xE0_ground_or_air == GA_Ground) {
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

static u32 const transition_flags =
    FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_HIT_NOUPDATE |
    FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE |
    FIGHTER_SWORDTRAIL_PRESERVE | FIGHTER_ITEMVIS_NOUPDATE |
    FIGHTER_STATE_CHANGE_B19 | FIGHTER_MODELPART_VIS_NOUPDATE |
    FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_STATE_CHANGE_B27;

void ftMars_801376E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(gobj, 358, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137748(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->sa.mars.x222C = 0;

    // Air_SetAsGrounded2
    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, 349, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_801377B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            // AS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // AS_029_Fall
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
    u8 unused[8];
#endif

    if (fp->xE0_ground_or_air == GA_Ground) {
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

    if (fp->xE0_ground_or_air == GA_Ground) {
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
    enum_t asid;

    func_8007D5D4(fp);

    switch (fp->action_id) {
    case 350:
        asid = 359;
        break;
    case 351:
        asid = 360;
        break;
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ActionStateChange_800693AC(gobj, asid, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_801379D0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    enum_t asid;

    fp->sa.mars.x222C = 0;
    func_8007D7FC(fp);

    switch (fp->action_id) {
    case 359:
        asid = 350;
        break;
    case 360:
        asid = 351;
        break;
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ActionStateChange_800693AC(gobj, asid, transition_flags, 0,
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
    enum_t asid;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &ftMars_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->xE0_ground_or_air == GA_Ground)
            asid = 350;
        else
            asid = 359;
    } else {
        if (fp->xE0_ground_or_air == GA_Ground)
            asid = 351;
        else
            asid = 360;
    }
    Fighter_ActionStateChange_800693AC(gobj, asid, FIGHTER_ATTACKCOUNT_NOUPDATE,
                                       0, 0, 1, 0);
}

void ftMars_80137B34(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            // AS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // AS_029_Fall
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
    u8 unused[8];
#endif

    if (fp->xE0_ground_or_air == GA_Ground) {
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

    if (fp->xE0_ground_or_air == GA_Ground) {
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
    enum_t asid;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
    switch (fp->action_id) {
    case 352:
        asid = 361;
        break;
    case 354:
        asid = 363;
        break;
    case 353:
        asid = 362;
        break;
#ifndef MUST_MATCH
    default:
        HSD_ASSERT(__LINE__, false);
#endif
    }

    Fighter_ActionStateChange_800693AC(gobj, asid, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137D60(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t asid;
    fp->sa.mars.x222C = 0;

    // Air_SetAsGrounded2
    func_8007D7FC(fp);

    switch (fp->action_id) {
    case 361:
        asid = 352;
        break;
    case 363:
        asid = 354;
        break;
    case 362:
        asid = 353;
        break;
    }

    Fighter_ActionStateChange_800693AC(gobj, asid, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftMars_80137E0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t asid;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &ftMars_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->xE0_ground_or_air == GA_Ground)
            asid = 352;
        else
            asid = 361;
    } else {
        if (fp->input.x624_lstick_y < -p_ftCommonData->x21C) {
            if (fp->xE0_ground_or_air == GA_Ground)
                asid = 354;
            else
                asid = 363;
        } else {
            if (fp->xE0_ground_or_air == GA_Ground)
                asid = 353;
            else
                asid = 362;
        }
    }

    Fighter_ActionStateChange_800693AC(gobj, asid, FIGHTER_ATTACKCOUNT_NOUPDATE,
                                       0, 0, 1, 0);
}

void ftMars_80137ECC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            // AS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // AS_029_Fall
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
    u8 unused[8];
#endif

    if (fp->xE0_ground_or_air == GA_Ground) {
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

    if (fp->xE0_ground_or_air == GA_Ground) {
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
    enum_t asid;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
    switch (fp->action_id) {
    case 355:
        asid = 364;
        break;
    case 357:
        asid = 366;
        break;
    case 356:
        asid = 365;
        break;
        // default:
        // thing uninitialized
    }
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, asid, 0x0C4E508C, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 8013809C 00134C7C
// https://decomp.me/scratch/qwafK
void ftMars_8013809C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->sa.mars.x222C = 0;
    // Air_SetAsGrounded2
    func_8007D7FC(fp);
    switch (fp->action_id) {
    case 364:
        thing = 355;
        break;
    case 366:
        thing = 357;
        break;
    case 365:
        thing = 356;
        break;
        // default:
        // thing uninitialized
    }
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80138148 00134D28
// https://decomp.me/scratch/V6aHf
void ftMars_80138148(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &ftMars_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            thing = 355;
        } else {
            thing = 364;
        }
    } else {
        if (fp->input.x624_lstick_y < -p_ftCommonData->x21C) {
            if (fp->xE0_ground_or_air == GA_Ground) {
                thing = 357;
            } else {
                thing = 366;
            }
        } else {
            if (fp->xE0_ground_or_air == GA_Ground) {
                thing = 356;
            } else {
                thing = 365;
            }
        }
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x02000000, 0, 0.0f, 1.0f,
                                       0.0f);
}
