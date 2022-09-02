#include <melee/ft/chara/ftMewtwo/ftmewtwo.h>

#define HALF_PI32 1.5707963705062866f

// 0x801450A0
// https://decomp.me/scratch/ZN9lq // Create Teleport Start GFX
void ftMewtwo_SpecialHi_CreateGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftMewtwo_SpecialHi_SetStartGFX(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x801450D4
// https://decomp.me/scratch/ycmf2 // Setup Teleport Start GFX
void ftMewtwo_SpecialHi_SetStartGFX(HSD_GObj* fighter_gobj)
{
    Vec3 pos;
    Fighter* fp = fp = getFighter(fighter_gobj);


    if (fp->x2219_flag.bits.b0 == 0)
    {
        func_8000B1CC(fp->x5E8_fighterBones[5].x0_jobj, NULL, &pos);
        ef_Spawn(0x4E8, fighter_gobj, &pos);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80145164
// https://decomp.me/scratch/rmcHC // Setup Teleport End GFX
void ftMewtwo_SpecialHi_SetEndGFX(HSD_GObj* fighter_gobj)
{
    Vec3 pos;
    Fighter* fp = fp = getFighter(fighter_gobj);

    if (fp->x2219_flag.bits.b0 == 0)
    {
        func_8000B1CC(fp->x5E8_fighterBones[5].x0_jobj, NULL, &pos);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x801451DC
// https://decomp.me/scratch/lXunH // Mewtwo's grounded Teleport Start Action State handler
void ftMewtwo_SpecialHi_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    void (*cb_Accessory4)(HSD_GObj*);

    fp->xEC_ground_vel = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALHI_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->mewtwoVars[0].SpecialHi.unk4 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

// 0x80145258
// https://decomp.me/scratch/AnthU // Mewtwo's aerial Teleport Start Action State handler
void ftMewtwo_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    void (*cb_Accessory4)(HSD_GObj*);
    f32 var;

    fp->x80_self_vel.x /= mewtwoAttrs->x40_MEWTWO_TELEPORT_VEL_DIV_X;
    fp->x80_self_vel.y /= mewtwoAttrs->x44_MEWTWO_TELEPORT_VEL_DIV_Y;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRHI_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->mewtwoVars[0].SpecialHi.unk4 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

// 0x801452EC
// https://decomp.me/scratch/stKjh // Mewtwo's grounded Teleport Start Animation callback
void ftMewtwo_SpecialHiStart_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftMewtwo_SpecialHi_Action(fighter_gobj);
    }
}

// 0x80145328
// https://decomp.me/scratch/oEogM // Mewtwo's aerial Teleport Start Animation callback
void ftMewtwo_SpecialAirHiStart_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftMewtwo_SpecialAirHi_Action(fighter_gobj);
    }
}

// 0x80145364 - Mewtwo's grounded Teleport Start IASA callback
void ftMewtwo_SpecialHiStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80145368 - Mewtwo's aerial Teleport Start IASA callback
void ftMewtwo_SpecialAirHiStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014536C - Mewtwo's grounded Teleport Start Physics callback
void ftMewtwo_SpecialHiStart_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x8014538C
// https://decomp.me/scratch/zxxkG // Mewtwo's aerial Teleport Start Physics callback
void ftMewtwo_SpecialAirHiStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    f32 gravity = mewtwoAttrs->x48_MEWTWO_TELEPORT_GRAVITY;
    f32 tVel = mewtwoAttrs->x4C_MEWTWO_TELEPORT_TERMINAL_VELOCITY;

    func_8007D494(fp, mewtwoAttrs->x48_MEWTWO_TELEPORT_GRAVITY, mewtwoAttrs->x4C_MEWTWO_TELEPORT_TERMINAL_VELOCITY);
    func_8007CEF4(fp);
}

// 0x801453D0
// https://decomp.me/scratch/T1M53 // Mewtwo's grounded Teleport Start Collision callback
void ftMewtwo_SpecialHiStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftMewtwo_SpecialHiStart_GroundToAir(fighter_gobj);
    }
}

// 0x8014540C
// https://decomp.me/scratch/bUnVo // Mewtwo's aerial Teleport Start Collision callback
void ftMewtwo_SpecialAirHiStart_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (EnvColl_CheckGroundAndLedge(fighter_gobj, CLIFFCATCH_O(fp)) != FALSE)
    {
        ftMewtwo_SpecialAirHiStart_AirToGround(fighter_gobj);
            return;
    }
    if (func_80081298(fighter_gobj)) return;
}

// 0x8014547C
// https://decomp.me/scratch/ilbZX // Mewtwo's ground -> air Teleport Start Action State handler
void ftMewtwo_SpecialHiStart_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRHI_START, (FIGHTER_HITSTATUS_COLANIM_PRESERVE | FTMEWTWO_SPECIALHI_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

// 0x801454E8
// https://decomp.me/scratch/VMuhr // Mewtwo's air -> ground Teleport Start Action State handler
void ftMewtwo_SpecialAirHiStart_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALHI_START, (FIGHTER_HITSTATUS_COLANIM_PRESERVE | FTMEWTWO_SPECIALHI_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_CreateGFX;
}

// 0x80145554
// https://decomp.me/scratch/vvIis // Mewtwo's grounded Teleport Zoom Animation callback
void ftMewtwo_SpecialHi_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->mewtwoVars[0].SpecialHi.travelFrames--;
    if (fp->mewtwoVars[0].SpecialHi.travelFrames <= 0)
    {
        ftMewtwo_SpecialHiLost_Action(fighter_gobj);
    }
}

// 0x80145590
// https://decomp.me/scratch/exf6y // Mewtwo's aerial Teleport Zoom Animation callback
void ftMewtwo_SpecialAirHi_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->mewtwoVars[0].SpecialHi.travelFrames--;
    if (fp->mewtwoVars[0].SpecialHi.travelFrames <= 0)
    {
        ftMewtwo_SpecialAirHiLost_Action(fighter_gobj);
    }
}

// 0x801455CC - Mewtwo's grounded Teleport Zoom IASA callback
void ftMewtwo_SpecialHi_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x801455D0 - Mewtwo's aerial Teleport Zoom IASA callback
void ftMewtwo_SpecialAirHi_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x801455D4 - Mewtwo's grounded Teleport Zoom Physics callback
void ftMewtwo_SpecialHi_Phys(HSD_GObj* fighter_gobj)
{
    func_8007CB74(fighter_gobj);
}

// 0x801455F4 - Mewtwo's aerial Teleport Zoom Physics callback
void ftMewtwo_SpecialAirHi_Phys(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x801455F8
// https://decomp.me/scratch/H1pXi // Mewtwo's grounded Teleport Zoom Collision callback
void ftMewtwo_SpecialHi_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* temp_fp = getFighter(fighter_gobj);
    Fighter* fp = temp_fp;
    CollData* collData = &temp_fp->x6F0_collData;
    u32 envFlags;

    if (func_80082708(fighter_gobj) == FALSE)
    {
        envFlags = collData->x134_envFlags;
        if ((envFlags & 0x3F) || (envFlags & 0xFC0))
        {
            func_8007D60C(fp);
            ftMewtwo_SpecialAirHiLost_Action(fighter_gobj);
            return;
        }
        ftMewtwo_SpecialHi_GroundToAir(fighter_gobj);
        return;
    }

    envFlags = collData->x134_envFlags;
    if ((envFlags & 0x3F) || (envFlags & 0xFC0))
    {
        ftMewtwo_SpecialHiLost_Action(fighter_gobj);
    }
}

#define DEG_TO_RAD 0.01745329238474369f

BOOL ftMewtwo_SpecialHi_CheckTimer(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftMewtwoAttributes* mewtwoAttrs = fp->x2D4_specialAttributes;

    if ((f32)fp->mewtwoVars[0].SpecialHi.unk4 >= mewtwoAttrs->x54_MEWTWO_TELEPORT_UNK2)
    {
        return TRUE;
    }
    else if (func_8009A134(fighter_gobj) != FALSE)
    {
        return FALSE;
    }
    else return TRUE;
}

// 0x80145698
// https://decomp.me/scratch/0XPnR // Mewtwo's aerial Teleport Zoom Collision callback
void ftMewtwo_SpecialAirHi_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    u32 envFlags;
    u32 var;

    fp->mewtwoVars[0].SpecialHi.unk4++;
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, CLIFFCATCH_O(fp)) != FALSE)
    {
        if (ftMewtwo_SpecialHi_CheckTimer(fighter_gobj) != FALSE)
        {
            ftMewtwo_SpecialAirHi_AirToGround(fighter_gobj);
            return;
        }
    }
    if (func_80081298(fighter_gobj) == FALSE)
    {
        if ((collData->x134_envFlags & 0x6000) && (lbvector_AngleXY(&collData->x188_ceiling.normal, &fp->x80_self_vel) > (DEG_TO_RAD * (90.0f + (f32)mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP))))
        {
            ftMewtwo_SpecialAirHiLost_Action(fighter_gobj);
        }
        if ((collData->x134_envFlags & 0x3F) && (lbvector_AngleXY(&collData->x160_rightwall.normal, &fp->x80_self_vel) > (DEG_TO_RAD * (90.0f + (f32)mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP))))
        {
            ftMewtwo_SpecialAirHiLost_Action(fighter_gobj);
        }
        if ((collData->x134_envFlags & 0xFC0) && (lbvector_AngleXY(&collData->x174_leftwall.normal, &fp->x80_self_vel) > (DEG_TO_RAD * (90.0f + (f32)mewtwoAttrs->x68_MEWTWO_TELEPORT_ANGLE_CLAMP))))
        {
            ftMewtwo_SpecialAirHiLost_Action(fighter_gobj);
        }
    }
}

// 0x801458A4
// https://decomp.me/scratch/RZEYl // Mewtwo's ground -> air Teleport Zoom Action State handler
void ftMewtwo_SpecialHi_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;
    f32 var2;

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRHI, (FIGHTER_HITSTATUS_COLANIM_PRESERVE | FTMEWTWO_SPECIALHI_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 0.0f, 0.0f);
    fp->x2223_flag.bits.b4 = 1;
    fp->x221E_flag.bits.b0 = 1;
}

// 0x80145920
// https://decomp.me/scratch/fw2b6 // Mewtwo's air -> ground Teleport Zoom Action State handler
void ftMewtwo_SpecialAirHi_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALHI, (FIGHTER_HITSTATUS_COLANIM_PRESERVE | FTMEWTWO_SPECIALHI_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 0.0f, 0.0f);
    fp->x221E_flag.bits.b0 = 1;
}

inline void ftMewtwo_SpecialHi_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    fp = getFighter(fighter_gobj);
    fp = getFighter(fighter_gobj);
    fp = getFighter(fighter_gobj);

    fp->mewtwoVars[0].SpecialHi.travelFrames = (s32)mewtwoAttrs->x50_MEWTWO_TELEPORT_DURATION;

    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    fp->x2223_flag.bits.b4 = 1;

    func_8007B62C(fighter_gobj, 2);

    fp->x221E_flag.bits.b0 = 1;

    func_80088148(fp, 0x30DA1U, SFX_VOLUME_MAX, SFX_PAN_MID);
}

extern BOOL func_8009A134(HSD_GObj*);

// 0x80145990
// https://decomp.me/scratch/kFSF2 // Mewtwo's grounded Teleport Zoom Action State handler
void ftMewtwo_SpecialHi_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    f32 vel;
    f32 stick_y;
    f32 stick_x;
    f32 sqrt_stick;

    stick_x = fp->input.x620_lstick_x;
    stick_y = fp->input.x624_lstick_y;

    stick_x *= stick_x;
    stick_y *= stick_y;

    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);

    sqrt_stick = sqrtf(stick_x + stick_y);

    if (sqrt_stick > 1.0f)
    {
        sqrt_stick = 1.0f;
    }

    if (!(sqrt_stick < mewtwoAttrs->x58_MEWTWO_TELEPORT_STICK_RANGE_MIN))
    {
        Vec3 stickVec;

        stickVec.x = fp->input.x620_lstick_x;
        stickVec.y = fp->input.x624_lstick_y;
        stickVec.z = 0.0f;

        if (!(lbvector_AngleXY(&collData->x14C_ground.normal, &stickVec) < HALF_PI32) && (func_8009A134(fighter_gobj) == FALSE))
        {
            func_8007D9FC(fp);

            vel = atan2f(fp->input.x624_lstick_y, fp->input.x620_lstick_x * fp->x2C_facing_direction);

            fp->mewtwoVars[0].SpecialHi.stickX = stickVec.x;
            fp->mewtwoVars[0].SpecialHi.stickY = stickVec.y;
            fp->xEC_ground_vel = fp->x2C_facing_direction * (((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick) + mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) * cosf(vel));

            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALHI, 0, NULL, 35.0f, 1.0f, 0.0f);
            func_8006EBA4(fighter_gobj);

            ftAnim_SetAnimRate(fighter_gobj, 0.0f);

            ftMewtwo_SpecialHi_SetVars(fighter_gobj);
            return;
        }
    }

    func_8007D60C(fp);
    ftMewtwo_SpecialAirHi_Action(fighter_gobj);
}

// 0x80145B94
// https://decomp.me/scratch/PuNnx // Mewtwo's aerial Teleport Zoom Action State handler
void ftMewtwo_SpecialAirHi_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);
    CollData* collData = collData = getFtColl(fp);
    f32 stick_y;
    f32 stick_x;
    f32 sqrt_stick;
    f32 floatVar;

    stick_x = fp->input.x620_lstick_x;
    stick_y = fp->input.x624_lstick_y;

    stick_x *= stick_x;
    stick_y *= stick_y;

    mewtwoAttrs = mewtwoAttrs = getFtSpecialAttrsD(fp);

    sqrt_stick = sqrtf(stick_x + stick_y);

    if (sqrt_stick > 1.0f)
    {
        sqrt_stick = 1.0f;
    }

    if ((sqrt_stick > mewtwoAttrs->x58_MEWTWO_TELEPORT_STICK_RANGE_MIN))
    {
        stick_x = stickGetDir(fp->input.x620_lstick_x, 0.0f);
        if (stick_x > 0.0010000000474974513f)
        {
            func_8007D9FC(fp);
        }
        floatVar = atan2f(fp->input.x624_lstick_y, fp->input.x620_lstick_x * fp->x2C_facing_direction);
        fp->mewtwoVars[0].SpecialHi.stickX = fp->input.x620_lstick_x;
        fp->mewtwoVars[0].SpecialHi.stickY = fp->input.x624_lstick_y;
    }

    else
    {
        func_8007DA24(fp);
        floatVar = HALF_PI32;
        fp->mewtwoVars[0].SpecialHi.stickX = 0.0f;
        sqrt_stick = fp->mewtwoVars[0].SpecialHi.stickY = 1.0f;
    }

    fp->x80_self_vel.x = fp->x2C_facing_direction * (((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick) + mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) * cosf(floatVar));
    fp->x80_self_vel.y = ((mewtwoAttrs->x5C_MEWTWO_TELEPORT_MOMENTUM * sqrt_stick) + mewtwoAttrs->x60_MEWTWO_TELEPORT_MOMENTUM_ADD) * sinf(floatVar);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRHI, 0, NULL, 35.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
    ftMewtwo_SpecialHi_SetVars(fighter_gobj);
}

// 0x80145DB0
// https://decomp.me/scratch/X7Bbv // Mewtwo's grounded Teleport End Animation callback
void ftMewtwo_SpecialHiLost_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80145DEC
// https://decomp.me/scratch/MwArx // Mewtwo's aerial Teleport End Animation callback
void ftMewtwo_SpecialAirHiLost_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_80096900(fighter_gobj, 1, 0, IS_INTERRUPTIBLE, mewtwoAttrs->x70_MEWTWO_TELEPORT_FREEFALL_MOBILITY, mewtwoAttrs->x74_MEWTWO_TELEPORT_LANDING_LAG);
    }
}

// 0x80145E4C - Mewtwo's grounded Teleport End IASA callback
void ftMewtwo_SpecialHiLost_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80145E50 - Mewtwo's aerial Teleport End IASA callback
void ftMewtwo_SpecialAirHiLost_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// Mewtwo's grounded Teleport End Physics callback
void ftMewtwo_SpecialHiLost_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x80145E74
// https://decomp.me/scratch/Ip75U // Mewtwo's aerial Teleport End Physics callback
void ftMewtwo_SpecialAirHiLost_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    f32 velY;

    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {

        func_8007D4B8(fp);
        func_8007D440(fp, mewtwoAttrs->x64_MEWTWO_TELEPORT_DRIFT * fp->x110_attr.x17C_AerialDriftMax);
        return;
    }
    velY = fp->x80_self_vel.y;
    fp->x80_self_vel.y = velY - (velY / 10.0f);
    func_8007CEF4(fp);
}

// 0x80145EF0
// https://decomp.me/scratch/uXDH4 // Mewtwo's grounded Teleport End Collision callback
void ftMewtwo_SpecialHiLost_Coll(HSD_GObj* fighter_gobj)
{
    if (func_800827A0(fighter_gobj) == FALSE)
    {
        ftMewtwo_SpecialHiLost_GroundToAir(fighter_gobj);
    }
}

// 0x80145F2C
// https://decomp.me/scratch/sAZJT // Mewtwo's aerial Teleport End Collision callback
void ftMewtwo_SpecialAirHiLost_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    if (EnvColl_CheckGroundAndLedge(fighter_gobj, CLIFFCATCH_O(fp)) != FALSE)
    {
        func_800D5CB0(fighter_gobj, 0, mewtwoAttrs->x74_MEWTWO_TELEPORT_LANDING_LAG);
        return;
    }

    if (func_80081298(fighter_gobj)) return;
}

// 0x80145FB0
// https://decomp.me/scratch/LajOI // Mewtwo's ground -> air Teleport End Action State handler
void ftMewtwo_SpecialHiLost_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRHI_LOST, FTMEWTWO_SPECIALHI_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

inline void ftMewtwo_SpecialHiLost_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->mewtwoVars[0].SpecialHi.velX = fp->x80_self_vel.x;
    fp->mewtwoVars[0].SpecialHi.velY = (f32)fp->x80_self_vel.y;
    fp->mewtwoVars[0].SpecialHi.groundVelX = (f32)fp->xEC_ground_vel;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    fp->xEC_ground_vel = 0.0f;
    fp->x221E_flag.bits.b0 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialHi_SetEndGFX;
}

// 0x80146010
// https://decomp.me/scratch/E8woM // Mewtwo's grounded Teleport End Action State handler
void ftMewtwo_SpecialHiLost_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALHI_LOST, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftMewtwo_SpecialHiLost_SetVars(fighter_gobj);

    fp->xEC_ground_vel = fp->mewtwoVars[0].SpecialHi.groundVelX * mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
}

// 0x801460CC
// https://decomp.me/scratch/8dbJK // Mewtwo's aerial Teleport End Action State handler
void ftMewtwo_SpecialAirHiLost_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_MEWTWO_SPECIALAIRHI_LOST, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftMewtwo_SpecialHiLost_SetVars(fighter_gobj);

    fp->x80_self_vel.x = fp->mewtwoVars[0].SpecialHi.velX * mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
    fp->x80_self_vel.y = fp->mewtwoVars[0].SpecialHi.velY * mewtwoAttrs->x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
}

