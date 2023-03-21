#include "ftfox.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftparts.h"
#include "it/code_8027CF30.h"

// 0x800E9DF8
// https://decomp.me/scratch/5Qwzg // Create Fox Illusion / Falco Phantasm GFX
void ftFox_SpecialS_CreateGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2219_flag.bits.b0 == false) {
        ef_Spawn(0x48D, gobj, fp->x5E8_fighterBones[0].x0_jobj,
                 &fp->facing_dir);
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x800E9E78
// https://decomp.me/scratch/Er9l6 // Check if Fox or Falco are in any of their
// Illusion/Phantasm Action States
bool ftFox_SpecialS_CheckGhostRemove(HSD_GObj* gobj)
{
    /// @todo @c enum
    enum_t asid = GET_FIGHTER(gobj)->action_id;

    if (asid >= AS_FOX_SPECIALS_START && asid <= AS_FOX_SPECIALAIRS_END)
        return false;

    return true;
}

// 0x800E9EA0
// https://decomp.me/scratch/jUfwc // Return 0x2208 from Fighter Struct
u32 ftFox_SpecialS_GetCmdVar2(HSD_GObj* gobj)
{
    return (GET_FIGHTER(gobj))->x2208_ftcmd_var2;
}

// 0x800E9EAC
// https://decomp.me/scratch/IjtLj // Copy state variables into SpecialS struct
void ftFox_SpecialS_CopyGhostPosIndexed(HSD_GObj* gobj, s32 index,
                                        Vec3* ghostPos)
{
    Fighter* fp = GET_FIGHTER(gobj);

    *ghostPos = fp->mv.fx.SpecialS.ghostEffectPos[index];
}

// 0x800E9ED4
// https://decomp.me/scratch/bkSg9 // Return float from array @ 0x2374 for Fox
// & Falco's Illusion/Phantasm
f32 ftFox_SpecialS_ReturnFloatVarIndexed(HSD_GObj* gobj, s32 index)
{
    return getFighter(gobj)->mv.fx.SpecialS.blendFrames[index];
}

// 0x800E9EE8
// https://decomp.me/scratch/7sYVM // Fox & Falco's grounded Illusion/Phantasm
// Start Action State handler
void ftFox_SpecialS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    foxAttrs = fp->x2D4_specialAttributes;

    fp->x2208_ftcmd_var2 = 0;
    fp->mv.fx.SpecialS.gravityDelay =
        (s32) foxAttrs->x24_FOX_ILLUSION_GRAVITY_DELAY;
    fp->mv.fx.SpecialS.ghostGObj = NULL;

    fp->xEC_ground_vel /= foxAttrs->x28_FOX_ILLUSION_GROUND_VEL_X;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALS_START, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 0x800E9F6C
// https://decomp.me/scratch/Sm9I3 // Fox & Falco's aerial Illusion/Phantasm
// Start Action State handler
void ftFox_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    foxAttrs = getFtSpecialAttrs(fp);

    fp->x2208_ftcmd_var2 = 0;
    fp->mv.fx.SpecialS.gravityDelay =
        (s32) foxAttrs->x24_FOX_ILLUSION_GRAVITY_DELAY;
    fp->mv.fx.SpecialS.ghostGObj = NULL;

    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x /= foxAttrs->x28_FOX_ILLUSION_GROUND_VEL_X;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALAIRS_START, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);

    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
}

// 0x800EA004
// https://decomp.me/scratch/MsR8G // Fox & Falco's grounded Illusion/Phantasm
// Start Animation callback
void ftFox_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialS_Action(gobj);
    }
}

// 0x800EA040
// https://decomp.me/scratch/EmRIa // Fox & Falco's aerial Illusion/Phantasm
// Start Animation callback
void ftFox_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialAirS_Action(gobj);
    }
}

// 0x800EA07C - Fox & Falco's grounded Illusion/Phantasm Start IASA callback
void ftFox_SpecialSStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA080 - Fox & Falco's aerial Illusion/Phantasm Start IASA callback
void ftFox_SpecialAirSStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA084
// https://decomp.me/scratch/Xpw0e // Fox & Falco's grounded Illusion/Phantasm
// Start Physics callback
void ftFox_SpecialSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    }
    func_80084F3C(gobj);
}

// 0x800EA0BC
// https://decomp.me/scratch/GDjT9 // Fox & Falco's aerial Illusion/Phantasm
// Start Physics callback
void ftFox_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    attr* ftAttrs = &fp->x110_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    } else {
        func_8007D494(fp, foxAttrs->x30_FOX_ILLUSION_UNK2,
                      ftAttrs->x170_TerminalVelocity);
    }
    func_8007CE94(fp, foxAttrs->x2C_FOX_ILLUSION_UNK1);
}

// 0x800EA128
// https://decomp.me/scratch/9RjgG // Fox & Falco's grounded Illusion/Phantasm
// Start Collision callback
void ftFox_SpecialSStart_Coll(HSD_GObj* gobj)
{
    if (func_80082708(gobj) == false) {
        ftFox_SpecialSStart_GroundToAir(gobj);
    }
}

// 0x800EA164
// https://decomp.me/scratch/xsH1P // Fox & Falco's aerial Illusion/Phantasm
// Start Collision callback
void ftFox_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cliffCatchDir;

    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }

    if (EnvColl_CheckGroundAndLedge(gobj, cliffCatchDir) != false) {
        ftFox_SpecialAirSStart_AirToGround(gobj);
        return;
    }

    if (func_80081298(gobj))
        return;
}

// 0x800EA1D4
// https://decomp.me/scratch/P6TMv // Fox & Falco's ground -> air
// Illusion/Phantasm Start Action State handler
void ftFox_SpecialSStart_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALAIRS_START,
                                       FTFOX_SPECIALS_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x800EA234
// https://decomp.me/scratch/sPuow // Fox & Falco's air -> ground
// Illusion/Phantasm Start Action State handler
void ftFox_SpecialAirSStart_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALS_START,
                                       FTFOX_SPECIALS_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

static inline void ftFox_SpecialS_CreateGhostItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* ghostGObj;

    if ((u32) fp->x2208_ftcmd_var2 == 1U) {
        fp->x2208_ftcmd_var2 = 0U;
        if ((s32) fp->x4_fighterKind == FTKIND_FOX) {
            ghostGObj =
                func_8029CEB4(gobj, &fp->xB0_pos, 0x38, fp->facing_dir);
        } else {
            ghostGObj =
                func_8029CEB4(gobj, &fp->xB0_pos, 0x39, fp->facing_dir);
        }
        if (ghostGObj != NULL) {
            fp->mv.fx.SpecialS.ghostGObj = ghostGObj;
            fp->x2222_flag.bits.b2 = 1;
        }
    }
}

// 0x800EA294
// https://decomp.me/scratch/CmfTU // Fox & Falco's grounded Illusion/Phantasm
// Dash Animation callback
void ftFox_SpecialS_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialSEnd_Action(gobj);
    }
    ftFox_SpecialS_CreateGhostItem(gobj);
}

// 0x800EA344
// https://decomp.me/scratch/CmfTU // Fox & Falco's aerial Illusion/Phantasm
// Dash Animation callback
void ftFox_SpecialAirS_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFox_SpecialAirSEnd_Action(gobj);
    }
    ftFox_SpecialS_CreateGhostItem(gobj);
}

// 0x800EA3F4
// https://decomp.me/scratch/8H8Wi // Fox & Falco's grounded Illusion/Phantasm
// Dash IASA callback
void ftFox_SpecialS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & HSD_BUTTON_B) != false) {
        if ((s32) fp->ground_or_air == GA_Air) {
            ftFox_SpecialAirSEnd_Action(gobj);
            return;
        } else
            ftFox_SpecialSEnd_Action(gobj);
    }
}

// 0x800EA438
// https://decomp.me/scratch/VKuOt // Fox & Falco's aerial Illusion/Phantasm
// Dash IASA callback
void ftFox_SpecialAirS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & HSD_BUTTON_B) != false) {
        if ((s32) fp->ground_or_air == GA_Air) {
            ftFox_SpecialAirSEnd_Action(gobj);
            return;
        } else
            ftFox_SpecialSEnd_Action(gobj);
    }
}

static inline void ftFox_SpecialS_SetPhys(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);

    fp->mv.fx.SpecialS.ghostEffectPos[3] =
        fp->mv.fx.SpecialS.ghostEffectPos[2];
    fp->mv.fx.SpecialS.ghostEffectPos[2] =
        fp->mv.fx.SpecialS.ghostEffectPos[1];
    fp->mv.fx.SpecialS.ghostEffectPos[1] =
        fp->mv.fx.SpecialS.ghostEffectPos[0];

    fp->mv.fx.SpecialS.ghostEffectPos[0] = fp->xB0_pos;

    fp->mv.fx.SpecialS.blendFrames[3] = fp->mv.fx.SpecialS.blendFrames[2];
    fp->mv.fx.SpecialS.blendFrames[2] = fp->mv.fx.SpecialS.blendFrames[1];
    fp->mv.fx.SpecialS.blendFrames[1] = fp->mv.fx.SpecialS.blendFrames[0];

    fp->mv.fx.SpecialS.blendFrames[0] = func_80075E78(fp, 0);
}

// 0x800EA47C
// https://decomp.me/scratch/vTYge // Fox & Falco's grounded Illusion/Phantasm
// Dash Physics callback
void ftFox_SpecialS_Phys(HSD_GObj* gobj)
{
    func_80085088(gobj);

    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EA534
// https://decomp.me/scratch/uC46r
void ftFox_SpecialAirS_Phys(HSD_GObj* gobj)
{
    func_80085134(gobj);

    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EA5EC
// https://decomp.me/scratch/r79Jx // Fox & Falco's grounded Illusion/Phantasm
// Dash Collision callback
void ftFox_SpecialS_Coll(HSD_GObj* gobj)
{
    if (func_80082708(gobj) == false) {
        ftFox_SpecialS_GroundToAir(gobj);
    }
}

// 0x800EA628
// https://decomp.me/scratch/e4nEC // Fox & Falco's aerial Illusion/Phantasm
// Dash Collision callback
void ftFox_SpecialAirS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cliffCatchDir;

    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(gobj, cliffCatchDir) != false) {
        ftFox_SpecialAirS_AirToGround(gobj);
        return;
    }
    if (func_80081298(gobj))
        return;
}

// 0x800EA698
// https://decomp.me/scratch/ARHkv // Fox & Falco's ground -> air
// Illusion/Phantasm Dash Action State handler
void ftFox_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(
        gobj, AS_FOX_SPECIALAIRS,
        (FtStateChange_PreserveColAnimHitStatus | FTFOX_SPECIALS_COLL_FLAG),
        NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->x2208_ftcmd_var2 = 0;
}

// 0x800EA700
// https://decomp.me/scratch/SsE2h // Fox & Falco's air -> ground
// Illusion/Phantasm Dash Action State handler
void ftFox_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(
        gobj, AS_FOX_SPECIALS,
        (FtStateChange_PreserveColAnimHitStatus | FTFOX_SPECIALS_COLL_FLAG),
        NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->x2208_ftcmd_var2 = 0;
}

inline void ftFox_SpecialS_SetVars(HSD_GObj* gobj)
{
    f32 var;
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.SpecialS.ghostEffectPos[3] = fp->xB0_pos;
    fp->mv.fx.SpecialS.ghostEffectPos[2] = fp->xB0_pos;
    fp->mv.fx.SpecialS.ghostEffectPos[1] = fp->xB0_pos;
    fp->mv.fx.SpecialS.ghostEffectPos[0] = fp->xB0_pos;

    var = func_80075E78(fp, 0);

    fp->mv.fx.SpecialS.blendFrames[3] = var;
    fp->mv.fx.SpecialS.blendFrames[2] = var;
    fp->mv.fx.SpecialS.blendFrames[1] = var;
    fp->mv.fx.SpecialS.blendFrames[0] = var;

    fp->cb.x21BC_callback_Accessory4 = &ftFox_SpecialS_CreateGFX;
}

// 0x800EA768
// https://decomp.me/scratch/orLir // Fox & Falco's grounded Illusion/Phantasm
// Dash Action State handler
void ftFox_SpecialS_Action(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALS,
                                       FtStateChange_SkipUpdateRumble, NULL,
                                       0.0f, 1.0f, 0.0f);
    ftFox_SpecialS_SetVars(gobj);
}

// 0x800EA838
// https://decomp.me/scratch/ij6np // Fox & Falco's aerial Illusion/Phantasm
// Dash Action State handler
void ftFox_SpecialAirS_Action(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[36];
#endif

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALAIRS,
                                       FtStateChange_SkipUpdateRumble, NULL,
                                       0.0f, 1.0f, 0.0f);
    ftFox_SpecialS_SetVars(gobj);
}

// 0x800EA908
// https://decomp.me/scratch/u3jZn // Fox & Falco's grounded Illusion/Phantasm
// End Animation callback
void ftFox_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

// 0x800EA944
// https://decomp.me/scratch/YLYPn // Fox & Falco's aerial Illusion/Phantasm
// End Animation callback
void ftFox_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80096900(gobj, 1, 0, true,
                      foxAttrs->x4C_FOX_ILLUSION_FREEFALL_MOBILITY,
                      foxAttrs->x50_FOX_ILLUSION_LANDING_LAG);
    }
}

// 0x800EA9A4 - Fox & Falco's grounded Illusion/Phantasm End IASA callback
void ftFox_SpecialSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA9A8 - Fox & Falco's grounded Illusion/Phantasm End IASA callback
void ftFox_SpecialAirSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA9AC
// https://decomp.me/scratch/qGaVf // Fox & Falco's grounded Illusion/Phantasm
// End Physics callback
void ftFox_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    }
    func_8007C930(fp, foxAttrs->x38_FOX_ILLUSION_GROUND_FRICTION);
    func_8007CB74(gobj);
    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EAA8C
// https://decomp.me/scratch/qGaVf // Fox & Falco's aerial Illusion/Phantasm
// End Physics callback
void ftFox_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    attr* ftAttrs = &fp->x110_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    } else
        func_8007D494(fp, foxAttrs->x48_FOX_ILLUSION_TERMINAL_VELOCITY,
                      ftAttrs->x170_TerminalVelocity);
    func_8007CE94(fp, foxAttrs->x40_FOX_ILLUSION_AIR_MUL_X);
    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EAB90
// https://decomp.me/scratch/3uJsu // Fox & Falco's grounded Illusion/Phantasm
// End Collision callback
void ftFox_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (func_800827A0(gobj) == false) {
        func_800CC730(gobj);
    }
}

// 0x800EABCC
// https://decomp.me/scratch/pd3IU // Fox & Falco's aerial Illusion/Phantasm
// End Collision callback
void ftFox_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    int cliffCatchDir;

    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(gobj, cliffCatchDir) != false) {
        func_800D5CB0(gobj, 0, foxAttrs->x50_FOX_ILLUSION_LANDING_LAG);
        return;
    }
    if (func_80081298(gobj))
        return;
};

inline void ftFox_SpecialSEnd_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    fp->mv.fx.SpecialS.gravityDelay = foxAttrs->x44_FOX_ILLUSION_FALL_ACCEL;
    fp->x2222_flag.bits.b2 = 1;
}

// 0x800EAC50
// https://decomp.me/scratch/ZZTJW // Fox & Falco's grounded Illusion End
// Action State handler
void ftFox_SpecialSEnd_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    fp->xEC_ground_vel =
        foxAttrs->x34_FOX_ILLUSION_GROUND_END_VEL_X * fp->facing_dir;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALS_END,
                                       FtStateChange_SkipUpdateRumble, NULL,
                                       0.0f, 1.0f, 0.0f);
    ftFox_SpecialSEnd_SetVars(gobj);
}

// 0x800EACD8
// https://decomp.me/scratch/QFxa9
void ftFox_SpecialAirSEnd_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    fp->x80_self_vel.x =
        foxAttrs->x3C_FOX_ILLUSION_AIR_END_VEL_X * fp->facing_dir;
    fp->x80_self_vel.y = 0.0f;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALAIRS_END,
                                       FtStateChange_SkipUpdateRumble, NULL,
                                       0.0f, 1.0f, 0.0f);
    ftFox_SpecialSEnd_SetVars(gobj);
}
