#include <melee/ft/chara/ftFox/ftfox.h>

// 0x800E9DF8
// https://decomp.me/scratch/5Qwzg // Create Fox Illusion / Falco Phantasm GFX
void ftFox_SpecialS_CreateGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x48D, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x800E9E78
// https://decomp.me/scratch/Er9l6 // Check if Fox or Falco are in any of their Illusion/Phantasm Action States
BOOL ftFox_SpecialS_CheckGhostRemove(HSD_GObj* fighter_gobj)
{
    s32 ASID = getFighter(fighter_gobj)->x10_action_state_index;

    if ((ASID >= AS_FOX_SPECIALS_START) && (ASID <= AS_FOX_SPECIALAIRS_END))
    {
        return FALSE;
    }
    return TRUE;
}

// 0x800E9EA0
// https://decomp.me/scratch/jUfwc // Return 0x2208 from Fighter Struct
u32 ftFox_SpecialS_GetCmdVar2(HSD_GObj* fighter_gobj)
{
    return ((Fighter*)fighter_gobj->user_data)->x2208_ftcmd_var2;
}

// 0x800E9EAC
// https://decomp.me/scratch/IjtLj // Copy state variables into SpecialS struct
void ftFox_SpecialS_CopyGhostPosIndexed(HSD_GObj* fighter_gobj, s32 index, Vec3* ghostPos)
{
    Fighter* fp = fighter_gobj->user_data;

    *ghostPos = fp->foxVars[0].SpecialS.ghostEffectPos[index];
}

// 0x800E9ED4
// https://decomp.me/scratch/bkSg9 // Return float from array @ 0x2374 for Fox & Falco's Illusion/Phantasm
f32 ftFox_SpecialS_ReturnFloatVarIndexed(HSD_GObj* fighter_gobj, s32 index)
{
    return getFighter(fighter_gobj)->foxVars[0].SpecialS.blendFrames[index];
}

// 0x800E9EE8
// https://decomp.me/scratch/7sYVM // Fox & Falco's grounded Illusion/Phantasm Start Action State handler
void ftFox_SpecialS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp = getFighter(fighter_gobj);
    foxAttrs = fp->x2D4_specialAttributes;

    fp->x2208_ftcmd_var2 = 0;
    fp->foxVars[0].SpecialS.gravityDelay = (s32)foxAttrs->x24_FOX_ILLUSION_GRAVITY_DELAY;
    fp->foxVars[0].SpecialS.ghostGObj = NULL;

    fp->xEC_ground_vel /= foxAttrs->x28_FOX_ILLUSION_GROUND_VEL_X;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALS_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

// 0x800E9F6C
// https://decomp.me/scratch/Sm9I3 // Fox & Falco's aerial Illusion/Phantasm Start Action State handler
void ftFox_SpecialAirS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp = getFighter(fighter_gobj);
    foxAttrs = getFtSpecialAttrs(fp);

    fp->x2208_ftcmd_var2 = 0;
    fp->foxVars[0].SpecialS.gravityDelay = (s32)foxAttrs->x24_FOX_ILLUSION_GRAVITY_DELAY;
    fp->foxVars[0].SpecialS.ghostGObj = NULL;

    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x /= foxAttrs->x28_FOX_ILLUSION_GROUND_VEL_X;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRS_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
}

// 0x800EA004
// https://decomp.me/scratch/MsR8G // Fox & Falco's grounded Illusion/Phantasm Start Animation callback
void ftFox_SpecialSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftFox_SpecialS_Action(fighter_gobj);
    }
}

// 0x800EA040
// https://decomp.me/scratch/EmRIa // Fox & Falco's aerial Illusion/Phantasm Start Animation callback
void ftFox_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftFox_SpecialAirS_Action(fighter_gobj);
    }
}

// 0x800EA07C - Fox & Falco's grounded Illusion/Phantasm Start IASA callback
void ftFox_SpecialSStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800EA080 - Fox & Falco's aerial Illusion/Phantasm Start IASA callback
void ftFox_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800EA084
// https://decomp.me/scratch/Xpw0e // Fox & Falco's grounded Illusion/Phantasm Start Physics callback
void ftFox_SpecialSStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->foxVars[0].SpecialS.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialS.gravityDelay--;
    }
    func_80084F3C(fighter_gobj);
}

// 0x800EA0BC
// https://decomp.me/scratch/GDjT9 // Fox & Falco's aerial Illusion/Phantasm Start Physics callback
void ftFox_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = &fp->x110_attr;

    if (fp->foxVars[0].SpecialS.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialS.gravityDelay--;
    }
    else
    {
        func_8007D494(fp, foxAttrs->x30_FOX_ILLUSION_UNK2, ftAttrs->x170_TerminalVelocity);
    }
    func_8007CE94(fp, foxAttrs->x2C_FOX_ILLUSION_UNK1);
}

// 0x800EA128
// https://decomp.me/scratch/9RjgG // Fox & Falco's grounded Illusion/Phantasm Start Collision callback
void ftFox_SpecialSStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialSStart_GroundToAir(fighter_gobj);
    }
}

// 0x800EA164
// https://decomp.me/scratch/xsH1P // Fox & Falco's aerial Illusion/Phantasm Start Collision callback
void ftFox_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 cliffCatchDir;

    if (fp->x2C_facing_direction < 0.0f)
    {
        cliffCatchDir = -1;
    }
    else
    {
        cliffCatchDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, cliffCatchDir) != FALSE)
    {
        ftFox_SpecialAirSStart_AirToGround(fighter_gobj);
        return;
    }
    if (func_80081298(fighter_gobj)) return;
}

// 0x800EA1D4
// https://decomp.me/scratch/P6TMv // Fox & Falco's ground -> air Illusion/Phantasm Start Action State handler
void ftFox_SpecialSStart_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRS_START, FTFOX_SPECIALS_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x800EA234
// https://decomp.me/scratch/sPuow // Fox & Falco's air -> ground Illusion/Phantasm Start Action State handler
void ftFox_SpecialAirSStart_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALS_START, FTFOX_SPECIALS_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

extern HSD_GObj* func_8029CEB4(HSD_GObj*, Vec3*, s32, f32);

inline void ftFox_SpecialS_CreateGhostItem(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* ghostGObj;

    if ((u32)fp->x2208_ftcmd_var2 == 1U)
    {
        fp->x2208_ftcmd_var2 = 0U;
        if ((s32)fp->x4_fighterKind == FTKIND_FOX)
        {
            ghostGObj = func_8029CEB4(fighter_gobj, &fp->xB0_pos, 0x38, fp->x2C_facing_direction);
        }
        else
        {
            ghostGObj = func_8029CEB4(fighter_gobj, &fp->xB0_pos, 0x39, fp->x2C_facing_direction);
        }
        if (ghostGObj != NULL)
        {
            fp->foxVars[0].SpecialS.ghostGObj = ghostGObj;
            fp->x2222_flag.bits.b2 = 1;
        }
    }
}

// 0x800EA294
// https://decomp.me/scratch/CmfTU // Fox & Falco's grounded Illusion/Phantasm Dash Animation callback
void ftFox_SpecialS_Anim(HSD_GObj* fighter_gobj)
{
    s32 filler[6];

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftFox_SpecialSEnd_Action(fighter_gobj);
    }
    ftFox_SpecialS_CreateGhostItem(fighter_gobj);
}

// 0x800EA344
// https://decomp.me/scratch/CmfTU // Fox & Falco's aerial Illusion/Phantasm Dash Animation callback
void ftFox_SpecialAirS_Anim(HSD_GObj* fighter_gobj)
{
    s32 filler[4];

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftFox_SpecialAirSEnd_Action(fighter_gobj);
    }
    ftFox_SpecialS_CreateGhostItem(fighter_gobj);
}

// 0x800EA3F4
// https://decomp.me/scratch/8H8Wi // Fox & Falco's grounded Illusion/Phantasm Dash IASA callback
void ftFox_SpecialS_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->input.x668 & HSD_BUTTON_B) != FALSE)
    {
        if ((s32)fp->xE0_ground_or_air == GA_Air)
        {
            ftFox_SpecialAirSEnd_Action(fighter_gobj);
            return;
        }
        else ftFox_SpecialSEnd_Action(fighter_gobj);
    }
}

// 0x800EA438
// https://decomp.me/scratch/VKuOt // Fox & Falco's aerial Illusion/Phantasm Dash IASA callback
void ftFox_SpecialAirS_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->input.x668 & HSD_BUTTON_B) != FALSE)
    {
        if ((s32)fp->xE0_ground_or_air == GA_Air)
        {
            ftFox_SpecialAirSEnd_Action(fighter_gobj);
            return;
        }
        else ftFox_SpecialSEnd_Action(fighter_gobj);
    }
}

extern f32 func_80075E78(Fighter*, s32);
extern void func_80085088(HSD_GObj*);

inline void ftFox_SpecialS_SetPhys(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    fp = fighter_gobj->user_data;

    fp->foxVars[0].SpecialS.ghostEffectPos[3] = fp->foxVars[0].SpecialS.ghostEffectPos[2];
    fp->foxVars[0].SpecialS.ghostEffectPos[2] = fp->foxVars[0].SpecialS.ghostEffectPos[1];
    fp->foxVars[0].SpecialS.ghostEffectPos[1] = fp->foxVars[0].SpecialS.ghostEffectPos[0];

    fp->foxVars[0].SpecialS.ghostEffectPos[0] = fp->xB0_pos;

    fp->foxVars[0].SpecialS.blendFrames[3] = fp->foxVars[0].SpecialS.blendFrames[2];
    fp->foxVars[0].SpecialS.blendFrames[2] = fp->foxVars[0].SpecialS.blendFrames[1];
    fp->foxVars[0].SpecialS.blendFrames[1] = fp->foxVars[0].SpecialS.blendFrames[0];

    fp->foxVars[0].SpecialS.blendFrames[0] = func_80075E78(fp, 0);
}

// 0x800EA47C
// https://decomp.me/scratch/vTYge // Fox & Falco's grounded Illusion/Phantasm Dash Physics callback
void ftFox_SpecialS_Phys(HSD_GObj* fighter_gobj)
{

    func_80085088(fighter_gobj);

    ftFox_SpecialS_SetPhys(fighter_gobj);
}

// 0x800EA534
// https://decomp.me/scratch/uC46r
void ftFox_SpecialAirS_Phys(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);

    ftFox_SpecialS_SetPhys(fighter_gobj);
}

// 0x800EA5EC
// https://decomp.me/scratch/r79Jx // Fox & Falco's grounded Illusion/Phantasm Dash Collision callback
void ftFox_SpecialS_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialS_GroundToAir(fighter_gobj);
    }
}

// 0x800EA628
// https://decomp.me/scratch/e4nEC // Fox & Falco's aerial Illusion/Phantasm Dash Collision callback
void ftFox_SpecialAirS_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 cliffCatchDir;

    if (fp->x2C_facing_direction < 0.0f)
    {
        cliffCatchDir = -1;
    }
    else
    {
        cliffCatchDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, cliffCatchDir) != FALSE)
    {
        ftFox_SpecialAirS_AirToGround(fighter_gobj);
        return;
    }
    if (func_80081298(fighter_gobj)) return;
}

// 0x800EA698
// https://decomp.me/scratch/ARHkv // Fox & Falco's ground -> air Illusion/Phantasm Dash Action State handler
void ftFox_SpecialS_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRS, (FIGHTER_HITSTATUS_COLANIM_PRESERVE | FTFOX_SPECIALS_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->x2208_ftcmd_var2 = 0;
}

// 0x800EA700 
// https://decomp.me/scratch/SsE2h // Fox & Falco's air -> ground Illusion/Phantasm Dash Action State handler
void ftFox_SpecialAirS_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALS, (FIGHTER_HITSTATUS_COLANIM_PRESERVE | FTFOX_SPECIALS_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->x2208_ftcmd_var2 = 0;
}

inline void ftFox_SpecialS_SetVars(HSD_GObj* fighter_gobj)
{
    f32 var;
    Fighter* fp = getFighter(fighter_gobj);

    fp->foxVars[0].SpecialS.ghostEffectPos[3] = fp->xB0_pos;
    fp->foxVars[0].SpecialS.ghostEffectPos[2] = fp->xB0_pos;
    fp->foxVars[0].SpecialS.ghostEffectPos[1] = fp->xB0_pos;
    fp->foxVars[0].SpecialS.ghostEffectPos[0] = fp->xB0_pos;

    var = func_80075E78(fp, 0);

    fp->foxVars[0].SpecialS.blendFrames[3] = var;
    fp->foxVars[0].SpecialS.blendFrames[2] = var;
    fp->foxVars[0].SpecialS.blendFrames[1] = var;
    fp->foxVars[0].SpecialS.blendFrames[0] = var;

    fp->cb.x21BC_callback_Accessory4 = &ftFox_SpecialS_CreateGFX;
}

// 0x800EA768
// https://decomp.me/scratch/orLir // Fox & Falco's grounded Illusion/Phantasm Dash Action State handler
void ftFox_SpecialS_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 unused[6];

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALS, FIGHTER_RUMBLE_NOUPDATE, NULL, 0.0f, 1.0f, 0.0f);
    ftFox_SpecialS_SetVars(fighter_gobj);
}

// 0x800EA838
// https://decomp.me/scratch/ij6np // Fox & Falco's aerial Illusion/Phantasm Dash Action State handler
void ftFox_SpecialAirS_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 unused[8];

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRS, FIGHTER_RUMBLE_NOUPDATE, NULL, 0.0f, 1.0f, 0.0f);
    ftFox_SpecialS_SetVars(fighter_gobj);
}

// 0x800EA908
// https://decomp.me/scratch/u3jZn // Fox & Falco's grounded Illusion/Phantasm End Animation callback
void ftFox_SpecialSEnd_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x800EA944
// https://decomp.me/scratch/YLYPn // Fox & Falco's aerial Illusion/Phantasm End Animation callback
void ftFox_SpecialAirSEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_80096900(fighter_gobj, 1, 0, IS_INTERRUPTIBLE, foxAttrs->x4C_FOX_ILLUSION_FREEFALL_MOBILITY, foxAttrs->x50_FOX_ILLUSION_LANDING_LAG);
    }
}

// 0x800EA9A4 - Fox & Falco's grounded Illusion/Phantasm End IASA callback
void ftFox_SpecialSEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800EA9A8 - Fox & Falco's grounded Illusion/Phantasm End IASA callback
void ftFox_SpecialAirSEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800EA9AC
// https://decomp.me/scratch/qGaVf // Fox & Falco's grounded Illusion/Phantasm End Physics callback
void ftFox_SpecialSEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    if (fp->foxVars[0].SpecialS.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialS.gravityDelay--;
    }
    func_8007C930(fp, foxAttrs->x38_FOX_ILLUSION_GROUND_FRICTION);
    func_8007CB74(fighter_gobj);
    ftFox_SpecialS_SetPhys(fighter_gobj);
}

// 0x800EAA8C
// https://decomp.me/scratch/qGaVf // Fox & Falco's aerial Illusion/Phantasm End Physics callback
void ftFox_SpecialAirSEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);

    if (fp->foxVars[0].SpecialS.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialS.gravityDelay--;
    }
    else func_8007D494(fp, foxAttrs->x48_FOX_ILLUSION_TERMINAL_VELOCITY, ftAttrs->x170_TerminalVelocity);
    func_8007CE94(fp, foxAttrs->x40_FOX_ILLUSION_AIR_MUL_X);
    ftFox_SpecialS_SetPhys(fighter_gobj);
}

// 0x800EAB90
// https://decomp.me/scratch/3uJsu // Fox & Falco's grounded Illusion/Phantasm End Collision callback
void ftFox_SpecialSEnd_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_800827A0(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x800EABCC
// https://decomp.me/scratch/pd3IU // Fox & Falco's aerial Illusion/Phantasm End Collision callback
void ftFox_SpecialAirSEnd_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    s32 cliffCatchDir;

    if (fp->x2C_facing_direction < 0.0f)
    {
        cliffCatchDir = -1;
    }
    else
    {
        cliffCatchDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, cliffCatchDir) != FALSE)
    {
        func_800D5CB0(fighter_gobj, 0, foxAttrs->x50_FOX_ILLUSION_LANDING_LAG);
        return;
    }
    if (func_80081298(fighter_gobj)) return;
};

inline void ftFox_SpecialSEnd_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    fp->foxVars[0].SpecialS.gravityDelay = foxAttrs->x44_FOX_ILLUSION_FALL_ACCEL;
    fp->x2222_flag.bits.b2 = 1;
}

// 0x800EAC50
// https://decomp.me/scratch/ZZTJW // Fox & Falco's grounded Illusion End Action State handler
void ftFox_SpecialSEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp->xEC_ground_vel = foxAttrs->x34_FOX_ILLUSION_GROUND_END_VEL_X * fp->x2C_facing_direction;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALS_END, FIGHTER_RUMBLE_NOUPDATE, NULL, 0.0f, 1.0f, 0.0f);
    ftFox_SpecialSEnd_SetVars(fighter_gobj);
}

// 0x800EACD8
// https://decomp.me/scratch/QFxa9
void ftFox_SpecialAirSEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp->x80_self_vel.x = foxAttrs->x3C_FOX_ILLUSION_AIR_END_VEL_X * fp->x2C_facing_direction;
    fp->x80_self_vel.y = 0.0f;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRS_END, FIGHTER_RUMBLE_NOUPDATE, NULL, 0.0f, 1.0f, 0.0f);
    ftFox_SpecialSEnd_SetVars(fighter_gobj);
}
