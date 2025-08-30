#include "ftFx_SpecialS.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftFox/types.h"

#include <common_structs.h>
#include <melee/it/items/itfoxillusion.h>

#define FTFOX_SPECIALS_COLL_FLAG                                              \
    Ft_MF_SkipMatAnim | Ft_MF_SkipRumble | Ft_MF_UpdateCmd |                  \
        Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |                 \
        Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27

// 0x800E9DF8
// https://decomp.me/scratch/5Qwzg // Create Fox Illusion / Falco Phantasm GFX
void ftFx_SpecialS_CreateGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2219_b0 == false) {
        efSync_Spawn(0x48D, gobj, fp->parts[FtPart_TopN].joint,
                     &fp->facing_dir);
        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

// 0x800E9E78
// https://decomp.me/scratch/Er9l6 // Check if Fox or Falco are in any of their
// Illusion/Phantasm Motion States
bool ftFx_SpecialS_CheckGhostRemove(HSD_GObj* gobj)
{
    /// @todo @c enum
    enum_t msid = GET_FIGHTER(gobj)->motion_id;

    if (msid >= ftFx_MS_SpecialSStart && msid <= ftFx_MS_SpecialAirSEnd) {
        return false;
    }

    return true;
}

// 0x800E9EA0
// https://decomp.me/scratch/jUfwc // Return 0x2208 from Fighter Struct
s32 ftFx_SpecialS_GetCmdVar2(HSD_GObj* gobj)
{
    return (GET_FIGHTER(gobj))->cmd_vars[2];
}

// 0x800E9EAC
// https://decomp.me/scratch/IjtLj // Copy state variables into SpecialS struct
void ftFx_SpecialS_CopyGhostPosIndexed(HSD_GObj* gobj, s32 index,
                                       Vec3* ghostPos)
{
    Fighter* fp = GET_FIGHTER(gobj);

    *ghostPos = fp->mv.fx.SpecialS.ghostEffectPos[index];
}

// 0x800E9ED4
// https://decomp.me/scratch/bkSg9 // Return float from array @ 0x2374 for Fox
// & Falco's Illusion/Phantasm
float ftFx_SpecialS_ReturnFloatVarIndexed(HSD_GObj* gobj, s32 index)
{
    return getFighter(gobj)->mv.fx.SpecialS.blendFrames[index];
}

// 0x800E9EE8
// https://decomp.me/scratch/7sYVM // Fox & Falco's grounded Illusion/Phantasm
// Start Motion State handler
void ftFx_SpecialSStart_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    fp->cmd_vars[2] = 0;
    fp->mv.fx.SpecialS.gravityDelay = da->x24_FOX_ILLUSION_GRAVITY_DELAY;
    fp->mv.fx.SpecialS.ghostGObj = NULL;

    fp->gr_vel /= da->x28_FOX_ILLUSION_GROUND_VEL_X;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialSStart, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

// 0x800E9F6C
// https://decomp.me/scratch/Sm9I3 // Fox & Falco's aerial Illusion/Phantasm
// Start Motion State handler
void ftFx_SpecialAirSStart_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    da = getFtSpecialAttrs(fp);

    fp->cmd_vars[2] = 0;
    fp->mv.fx.SpecialS.gravityDelay = da->x24_FOX_ILLUSION_GRAVITY_DELAY;
    fp->mv.fx.SpecialS.ghostGObj = NULL;

    fp->self_vel.y = 0.0f;
    fp->self_vel.x /= da->x28_FOX_ILLUSION_GROUND_VEL_X;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirSStart, 0, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);

    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
}

// 0x800EA004
// https://decomp.me/scratch/MsR8G // Fox & Falco's grounded Illusion/Phantasm
// Start Animation callback
void ftFx_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFx_SpecialS_Enter(gobj);
    }
}

// 0x800EA040
// https://decomp.me/scratch/EmRIa // Fox & Falco's aerial Illusion/Phantasm
// Start Animation callback
void ftFx_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFx_SpecialAirS_Enter(gobj);
    }
}

// 0x800EA07C - Fox & Falco's grounded Illusion/Phantasm Start IASA callback
void ftFx_SpecialSStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA080 - Fox & Falco's aerial Illusion/Phantasm Start IASA callback
void ftFx_SpecialAirSStart_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA084
// https://decomp.me/scratch/Xpw0e // Fox & Falco's grounded Illusion/Phantasm
// Start Physics callback
void ftFx_SpecialSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    }
    ft_80084F3C(gobj);
}

// 0x800EA0BC
// https://decomp.me/scratch/GDjT9 // Fox & Falco's aerial Illusion/Phantasm
// Start Physics callback
void ftFx_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;

    u8 _[8];

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->x30_FOX_ILLUSION_UNK2, ca->terminal_vel);
    }
    ftCommon_8007CE94(fp, da->x2C_FOX_ILLUSION_UNK1);
}

// 0x800EA128
// https://decomp.me/scratch/9RjgG // Fox & Falco's grounded Illusion/Phantasm
// Start Collision callback
void ftFx_SpecialSStart_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialSStart_GroundToAir(gobj);
    }
}

// 0x800EA164
// https://decomp.me/scratch/xsH1P // Fox & Falco's aerial Illusion/Phantasm
// Start Collision callback
void ftFx_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cliffCatchDir;

    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }

    if (ft_CheckGroundAndLedge(gobj, cliffCatchDir)) {
        ftFx_SpecialAirSStart_AirToGround(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

// 0x800EA1D4
// https://decomp.me/scratch/P6TMv // Fox & Falco's ground -> air
// Illusion/Phantasm Start Motion State handler
void ftFx_SpecialSStart_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirSStart,
                              FTFOX_SPECIALS_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

// 0x800EA234
// https://decomp.me/scratch/sPuow // Fox & Falco's air -> ground
// Illusion/Phantasm Start Motion State handler
void ftFx_SpecialAirSStart_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialSStart,
                              FTFOX_SPECIALS_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

static inline void ftFox_SpecialS_CreateGhostItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* ghostGObj;

    if (fp->cmd_vars[2] == 1) {
        fp->cmd_vars[2] = 0;
        if (fp->kind == FTKIND_FOX) {
            ghostGObj = it_8029CEB4(gobj, &fp->cur_pos, 0x38, fp->facing_dir);
        } else {
            ghostGObj = it_8029CEB4(gobj, &fp->cur_pos, 0x39, fp->facing_dir);
        }
        if (ghostGObj != NULL) {
            fp->mv.fx.SpecialS.ghostGObj = ghostGObj;
            fp->x2222_b2 = 1;
        }
    }
}

// 0x800EA294
// https://decomp.me/scratch/CmfTU // Fox & Falco's grounded Illusion/Phantasm
// Dash Animation callback
void ftFx_SpecialS_Anim(HSD_GObj* gobj)
{
    u8 _[24];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFx_SpecialSEnd_Enter(gobj);
    }
    ftFox_SpecialS_CreateGhostItem(gobj);
}

// 0x800EA344
// https://decomp.me/scratch/CmfTU // Fox & Falco's aerial Illusion/Phantasm
// Dash Animation callback
void ftFx_SpecialAirS_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftFx_SpecialAirSEnd_Enter(gobj);
    }
    ftFox_SpecialS_CreateGhostItem(gobj);
}

// 0x800EA3F4
// https://decomp.me/scratch/8H8Wi // Fox & Falco's grounded Illusion/Phantasm
// Dash IASA callback
void ftFx_SpecialS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & HSD_PAD_B)) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialAirSEnd_Enter(gobj);
            return;
        } else {
            ftFx_SpecialSEnd_Enter(gobj);
        }
    }
}

// 0x800EA438
// https://decomp.me/scratch/VKuOt // Fox & Falco's aerial Illusion/Phantasm
// Dash IASA callback
void ftFx_SpecialAirS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & HSD_PAD_B)) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialAirSEnd_Enter(gobj);
            return;
        } else {
            ftFx_SpecialSEnd_Enter(gobj);
        }
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

    fp->mv.fx.SpecialS.ghostEffectPos[0] = fp->cur_pos;

    fp->mv.fx.SpecialS.blendFrames[3] = fp->mv.fx.SpecialS.blendFrames[2];
    fp->mv.fx.SpecialS.blendFrames[2] = fp->mv.fx.SpecialS.blendFrames[1];
    fp->mv.fx.SpecialS.blendFrames[1] = fp->mv.fx.SpecialS.blendFrames[0];

    fp->mv.fx.SpecialS.blendFrames[0] = ftParts_80075E78(fp, 0);
}

// 0x800EA47C
// https://decomp.me/scratch/vTYge // Fox & Falco's grounded Illusion/Phantasm
// Dash Physics callback
void ftFx_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80085088(gobj);

    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EA534
// https://decomp.me/scratch/uC46r
void ftFx_SpecialAirS_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);

    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EA5EC
// https://decomp.me/scratch/r79Jx // Fox & Falco's grounded Illusion/Phantasm
// Dash Collision callback
void ftFx_SpecialS_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialS_GroundToAir(gobj);
    }
}

// 0x800EA628
// https://decomp.me/scratch/e4nEC // Fox & Falco's aerial Illusion/Phantasm
// Dash Collision callback
void ftFx_SpecialAirS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cliffCatchDir;

    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }
    if (ft_CheckGroundAndLedge(gobj, cliffCatchDir)) {
        ftFx_SpecialAirS_AirToGround(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

// 0x800EA698
// https://decomp.me/scratch/ARHkv // Fox & Falco's ground -> air
// Illusion/Phantasm Dash Motion State handler
void ftFx_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(
        gobj, ftFx_MS_SpecialAirS,
        (Ft_MF_KeepColAnimHitStatus | FTFOX_SPECIALS_COLL_FLAG),
        fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->cmd_vars[2] = 0;
}

// 0x800EA700
// https://decomp.me/scratch/SsE2h // Fox & Falco's air -> ground
// Illusion/Phantasm Dash Motion State handler
void ftFx_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(
        gobj, ftFx_MS_SpecialS,
        (Ft_MF_KeepColAnimHitStatus | FTFOX_SPECIALS_COLL_FLAG),
        fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->cmd_vars[2] = 0;
}

inline void ftFox_SpecialS_SetVars(HSD_GObj* gobj)
{
    float var;
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.SpecialS.ghostEffectPos[3] = fp->cur_pos;
    fp->mv.fx.SpecialS.ghostEffectPos[2] = fp->cur_pos;
    fp->mv.fx.SpecialS.ghostEffectPos[1] = fp->cur_pos;
    fp->mv.fx.SpecialS.ghostEffectPos[0] = fp->cur_pos;

    var = ftParts_80075E78(fp, 0);

    fp->mv.fx.SpecialS.blendFrames[3] = var;
    fp->mv.fx.SpecialS.blendFrames[2] = var;
    fp->mv.fx.SpecialS.blendFrames[1] = var;
    fp->mv.fx.SpecialS.blendFrames[0] = var;

    fp->accessory4_cb = &ftFx_SpecialS_CreateGFX;
}

// 0x800EA768
// https://decomp.me/scratch/orLir // Fox & Falco's grounded Illusion/Phantasm
// Dash Motion State handler
void ftFx_SpecialS_Enter(HSD_GObj* gobj)
{
    u8 _[28];

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialS, Ft_MF_SkipRumble, 0.0f,
                              1.0f, 0.0f, NULL);
    ftFox_SpecialS_SetVars(gobj);
}

// 0x800EA838
// https://decomp.me/scratch/ij6np // Fox & Falco's aerial Illusion/Phantasm
// Dash Motion State handler
void ftFx_SpecialAirS_Enter(HSD_GObj* gobj)
{
    u8 _[36];

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirS, Ft_MF_SkipRumble,
                              0.0f, 1.0f, 0.0f, NULL);
    ftFox_SpecialS_SetVars(gobj);
}

// 0x800EA908
// https://decomp.me/scratch/u3jZn // Fox & Falco's grounded Illusion/Phantasm
// End Animation callback
void ftFx_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x800EA944
// https://decomp.me/scratch/YLYPn // Fox & Falco's aerial Illusion/Phantasm
// End Animation callback
void ftFx_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 0, true, da->x4C_FOX_ILLUSION_FREEFALL_MOBILITY,
                      da->x50_FOX_ILLUSION_LANDING_LAG);
    }
}

// 0x800EA9A4 - Fox & Falco's grounded Illusion/Phantasm End IASA callback
void ftFx_SpecialSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA9A8 - Fox & Falco's grounded Illusion/Phantasm End IASA callback
void ftFx_SpecialAirSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800EA9AC
// https://decomp.me/scratch/qGaVf // Fox & Falco's grounded Illusion/Phantasm
// End Physics callback
void ftFx_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    u8 _[8];

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    }
    ftCommon_8007C930(fp, da->x38_FOX_ILLUSION_GROUND_FRICTION);
    ftCommon_8007CB74(gobj);
    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EAA8C
// https://decomp.me/scratch/qGaVf // Fox & Falco's aerial Illusion/Phantasm
// End Physics callback
void ftFx_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;

    u8 _[8];

    if (fp->mv.fx.SpecialS.gravityDelay != 0) {
        fp->mv.fx.SpecialS.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, da->x48_FOX_ILLUSION_TERMINAL_VELOCITY,
                          ca->terminal_vel);
    }
    ftCommon_8007CE94(fp, da->x40_FOX_ILLUSION_AIR_MUL_X);
    ftFox_SpecialS_SetPhys(gobj);
}

// 0x800EAB90
// https://decomp.me/scratch/3uJsu // Fox & Falco's grounded Illusion/Phantasm
// End Collision callback
void ftFx_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    u8 _[8];

    if (ft_800827A0(gobj) == false) {
        ftCo_Fall_Enter(gobj);
    }
}

// 0x800EABCC
// https://decomp.me/scratch/pd3IU // Fox & Falco's aerial Illusion/Phantasm
// End Collision callback
void ftFx_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    u8 _[4];

    int cliffCatchDir;

    if (fp->facing_dir < 0.0f) {
        cliffCatchDir = -1;
    } else {
        cliffCatchDir = 1;
    }
    if (ft_CheckGroundAndLedge(gobj, cliffCatchDir)) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->x50_FOX_ILLUSION_LANDING_LAG);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
};

inline void ftFox_SpecialSEnd_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);
    fp->mv.fx.SpecialS.gravityDelay = da->x44_FOX_ILLUSION_FALL_ACCEL;
    fp->x2222_b2 = 1;
}

// 0x800EAC50
// https://decomp.me/scratch/ZZTJW // Fox & Falco's grounded Illusion End
// Motion State handler
void ftFx_SpecialSEnd_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    fp->gr_vel = da->x34_FOX_ILLUSION_GROUND_END_VEL_X * fp->facing_dir;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialSEnd, Ft_MF_SkipRumble,
                              0.0f, 1.0f, 0.0f, NULL);
    ftFox_SpecialSEnd_SetVars(gobj);
}

// 0x800EACD8
// https://decomp.me/scratch/QFxa9
void ftFx_SpecialAirSEnd_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    fp->self_vel.x = da->x3C_FOX_ILLUSION_AIR_END_VEL_X * fp->facing_dir;
    fp->self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirSEnd, Ft_MF_SkipRumble,
                              0.0f, 1.0f, 0.0f, NULL);
    ftFox_SpecialSEnd_SetVars(gobj);
}
