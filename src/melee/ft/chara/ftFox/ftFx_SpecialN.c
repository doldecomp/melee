#include "ftFx_SpecialN.h"

#include "ftFx_Init.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftpickupitem.h"
#include "ftFox/inlines.h"
#include "ftFox/types.h"
#include "it/it_26B1.h"
#include "it/items/itfoxblaster.h"
#include "lb/lb_00B0.h"
#include "lb/lbrefract.h"

#include <common_structs.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <melee/it/items/itfoxlaser.h>

static inline void ftFox_SpecialN_GetHoldJoint(HSD_GObj* gobj, Vec3* pos,
                                               f32 z_offset)
{
    Vec3 sp14;

    // Double fp init otherwise this will not match when inlined
    Fighter* fp = fp = GET_FIGHTER(gobj);

    sp14.x = 0;
    sp14.y = 1.2325000762939453f;
    sp14.z = z_offset;

    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                &sp14, pos);
}

void ftFx_SpecialN_FtGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    ftFox_SpecialN_GetHoldJoint(gobj, pos, 4.263599872589111f);
}

void ftFx_SpecialN_ItGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    ftFox_SpecialN_GetHoldJoint(gobj, pos, 0.013600001111626625f);
}

/// 0x800E5D90
/// https://decomp.me/scratch/DRgo9 // Fox & Falco's Blaster
/// OnMotionStateChange function
void ftFx_SpecialN_OnChangeAction(HSD_GObj* gobj)
{
    PAD_STACK(8);

    ft_800892A0(gobj);
    ft_80089824(gobj);
}

/// 0x800E5DC4
/// https://decomp.me/scratch/A0n4M // Check if Fox/Falco has a Blaster GOBj
/// pointer
bool ftFx_SpecialN_CheckRemoveBlaster(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.fx.x222C_blasterGObj == NULL) {
        return true;
    }
    return false;
}

/// 0x800E5DE4 - shoutouts to Olifre for figuring this one out!
/// https://decomp.me/scratch/aatYF // Get msid for Fox/Falco moves that
/// require the Blaster item
s32 ftFx_SpecialN_GetBlasterAction(HSD_GObj* gobj)
{
    s32 msid = 9;

    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            s32 currASID = fp->motion_id;
            switch (currASID) {
            case ftFx_MS_SpecialNStart:
            case ftFx_MS_SpecialNLoop:
            case ftFx_MS_SpecialNEnd:
            case ftFx_MS_SpecialAirNStart:
            case ftFx_MS_SpecialAirNLoop:
            case ftFx_MS_SpecialAirNEnd:
                msid = currASID - ftFx_MS_SpecialNStart;
                break;

            case ftCo_MS_ThrowB:
            case ftCo_MS_ThrowHi:
            case ftCo_MS_ThrowLw:
                msid = currASID - ftCo_MS_CatchDash;
            }
        }
    }
    return msid;
}

/// 0x800E5E38
/// https://decomp.me/scratch/f6oIX // Check if Fox/Falco is performing a move
/// that requires the Blaster item
bool ftFx_SpecialN_CheckBlasterAction(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        switch (fp->motion_id) {
        case ftFx_MS_SpecialNStart:
        case ftFx_MS_SpecialNLoop:
        case ftFx_MS_SpecialNEnd:
        case ftFx_MS_SpecialAirNStart:
        case ftFx_MS_SpecialAirNLoop:
        case ftFx_MS_SpecialAirNEnd:
        case ftCo_MS_ThrowB:
        case ftCo_MS_ThrowHi:
        case ftCo_MS_ThrowLw:

            if (fp->x2070.x2071_b6) {
                return true;
            }
            return false;
        }
    }
    return true;
}

inline void ftFox_SpecialN_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

/// 0x800E5E90
/// https://decomp.me/scratch/4v8j4 // Clear Blaster GObj pointer and callbacks
void ftFx_SpecialN_ClearBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(gobj);
}

/// 0x800E5EBC
/// https://decomp.me/scratch/WglAb // Remove Blaster item
void ftFx_SpecialN_RemoveBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        it_802AEAB4(fp->fv.fx.x222C_blasterGObj);
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    if (ftFx_Init_800E5534(gobj) == false) {
        ftFox_SpecialN_SetNULL(gobj);
    }
}

u32 foxSFX[2] = { 110103, 110106 };
u32 falcoSFX[2] = { 100099, 100102 };

static inline f64 ftFox_SpecialN_PrepareBlasterShot(HSD_GObj* gobj,
                                                    Fighter* fp,
                                                    ftFox_DatAttrs* da,
                                                    Vec3* pos)
{
    ftFx_SpecialN_FtGetHoldJoint(gobj, pos);
    pos->z = 0.0F;
    if (fp->facing_dir == 1.0F) {
        return da->x10_FOX_BLASTER_ANGLE;
    }
    return M_PI - da->x10_FOX_BLASTER_ANGLE;
}

static inline void ftFox_SpecialN_FireBlasterShot(HSD_GObj* gobj, Fighter* fp,
                                                  ftFox_DatAttrs* da,
                                                  Vec3* pos, f64 launch_angle)
{
    it_8029C6A4(launch_angle, da->x14_FOX_BLASTER_VEL, gobj, pos,
                da->x1C_FOX_BLASTER_SHOT_ITKIND);
    it_802AE1D0(fp->fv.fx.x222C_blasterGObj);

    switch (ftLib_GetKind(gobj)) {
    case FTKIND_FOX:
        ft_PlaySFX(fp, foxSFX[fp->facing_dir == -1], SFX_VOLUME_MAX,
                   SFX_PAN_MID);
        return;
    case FTKIND_FALCO:
        ft_PlaySFX(fp, falcoSFX[fp->facing_dir == -1], SFX_VOLUME_MAX,
                   SFX_PAN_MID);
        return;
    }
}

/// 0x800E5F28
/// https://decomp.me/scratch/iPgDc // Create Blaster Shot Item
void ftFx_SpecialN_CreateBlasterShot(HSD_GObj* gobj)
{
    Vec3 sp2C;

    ftFox_DatAttrs* da;
    Fighter* fp;
    f64 launchAngle;

    PAD_STACK(4);

    /// @todo Seems fake, probably one or more missing @c inline functions.
    fp = fp = GET_FIGHTER(gobj);

    da = getFtSpecialAttrs(fp);

    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        launchAngle = ftFox_SpecialN_PrepareBlasterShot(gobj, fp, da, &sp2C);
        ftFox_SpecialN_FireBlasterShot(gobj, fp, da, &sp2C, launchAngle);
    }
}

inline void ftFox_SpecialN_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftFx_Init_800E5588;
    fp->death2_cb = ftFx_Init_800E5588;
}

static inline void ftFox_SpecialN_SpawnBlaster(HSD_GObj* gobj, Fighter* fp,
                                               ftFox_DatAttrs* da,
                                               int assert_line)
{
    HSD_GObj* blaster_gobj =
        it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                    ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                    da->x20_FOX_BLASTER_GUN_ITKIND);
    fp->fv.fx.x222C_blasterGObj = blaster_gobj;

    if (blaster_gobj != NULL) {
        it_8026BAE8(fp->fv.fx.x222C_blasterGObj, 0.85);
        ftFox_SpecialN_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    __assert("ftfoxspecialn.c", assert_line, "0");
}

static inline void ftFox_SpecialN_InitializeState(HSD_GObj* gobj, Fighter* fp)
{
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}

/// 0x800E608C
/// https://decomp.me/scratch/B3aTL // Fox & Falco's grounded Blaster Action
/// State handler
void ftFx_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialNStart, 0, 0, 1, 0, NULL);
    ftFox_SpecialN_InitializeState(gobj, fp);

    fp->gr_vel = 0;
    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    ftFox_SpecialN_SpawnBlaster(gobj, fp, da, 305);
}

/// 0x800E61A8
/// https://decomp.me/scratch/TUDhU
void ftFx_SpecialAirN_Enter(
    HSD_GObj* gobj) // Fox & Falco's aerial Blaster Motion State handler
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNStart, 0, 0, 1, 0,
                              NULL);
    ftFox_SpecialN_InitializeState(gobj, fp);

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    ftFox_SpecialN_SpawnBlaster(gobj, fp, da, 333);
}

static inline void ftFox_SpecialN_UpdateBlaster(Fighter* fp)
{
    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    if (fp->cmd_vars[3] == 1 && fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE538(fp->fv.fx.x222C_blasterGObj);
    }
}

static inline void ftFox_SpecialN_StartAnimation(HSD_GObj* gobj,
                                                 FtMotionId loop_msid)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftFox_SpecialN_UpdateBlaster(fp);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(
            gobj, loop_msid, (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1, 0, NULL);
        ftFox_SpecialN_SetCall(gobj);
        fp->accessory4_cb = ftFx_SpecialN_CreateBlasterShot;
        it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
    }
}

/// 0x800E62A4
/// https://decomp.me/scratch/ZOB3l // Fox & Falco's grounded Blaster Start
/// Animation callback
void ftFx_SpecialNStart_Anim(HSD_GObj* gobj)
{
    ftFox_SpecialN_StartAnimation(gobj, ftFx_MS_SpecialNLoop);
}

static inline void ftFox_SpecialN_BeginLoopTransition(HSD_GObj* gobj,
                                                      Fighter* fp,
                                                      FtMotionId loop_msid)
{
    fp->x21EC = ftFx_SpecialN_OnChangeAction;
    Fighter_ChangeMotionState(
        gobj, loop_msid,
        (Ft_MF_SkipAttackCount | Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1, 0,
        NULL);
}

static inline void ftFox_SpecialN_FinishLoopTransition(Fighter* fp)
{
    fp->accessory4_cb = ftFx_SpecialN_CreateBlasterShot;
    fp->mv.fx.SpecialN.isBlasterLoop = false;
    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, 1);
}

static inline void ftFox_SpecialN_FinishEndTransition(Fighter* fp)
{
    HSD_GObj* blaster_gobj = fp->fv.fx.x222C_blasterGObj;
    fp->cmd_vars[1] = 1;
    it_802ADDD0(blaster_gobj, 1);
}

/// 0x800E6368
/// https://decomp.me/scratch/J7zwX // Fox & Falco's grounded Blaster Loop
/// Animation callback
void ftFx_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftFox_SpecialN_UpdateBlaster(fp);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.fx.SpecialN.isBlasterLoop == true) {
            ftFox_SpecialN_BeginLoopTransition(gobj, fp, ftFx_MS_SpecialNLoop);
            ftFox_SpecialN_FinishLoopTransition(fp);
        } else {
            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialNEnd,
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1,
                                      0, NULL);
            ftFox_SpecialN_FinishEndTransition(fp);
        }
        ftFox_SpecialN_SetCall(gobj);
    }
    {
        Vec3 sp2C;
        ftFox_DatAttrs* da;
        Fighter* fp;
        f64 launchAngle;

        /// @todo Fake assignment.
        fp = fp = GET_FIGHTER(gobj);

        da = getFtSpecialAttrs(fp);

        {
            Fighter* _ = GET_FIGHTER(gobj);
        }

        if (fp->cmd_vars[2] != 0) {
            fp->cmd_vars[2] = 0;
            launchAngle =
                ftFox_SpecialN_PrepareBlasterShot(gobj, fp, da, &sp2C);
            ftFox_SpecialN_FireBlasterShot(gobj, fp, da, &sp2C, launchAngle);
        }
    }
}

static inline void ftFox_SpecialN_RemoveBlasterNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->fv.fx.x222C_blasterGObj = NULL;
    }
    ftFox_SpecialN_SetNULL(gobj);
}

static inline bool ftFox_SpecialN_UpdateEndAnimation(HSD_GObj* gobj,
                                                     Fighter* fp)
{
    it_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->cmd_vars[1]);
    if (fp->cmd_vars[1] == 2) {
        ftpickupitem_80094818(gobj, 0);
    }
    if (fp->cmd_vars[3] == 2 && fp->fv.fx.x222C_blasterGObj != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE608(fp->fv.fx.x222C_blasterGObj);
    }
    return ftAnim_IsFramesRemaining(gobj);
}

/// 0x800E65BC
/// https://decomp.me/scratch/aIEIA // Fox & Falco's grounded Blaster End
/// Animation callback
void ftFx_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    if (!ftFox_SpecialN_UpdateEndAnimation(gobj, fp)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        ft_8008A2BC(gobj);
    }
}

/// 0x800E667C
/// https://decomp.me/scratch/Os6Ik // Fox & Falco's aerial Blaster Start
/// Animation callback
void ftFx_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    ftFox_SpecialN_StartAnimation(gobj, ftFx_MS_SpecialAirNLoop);
}

/// 0x800E6740
/// https://decomp.me/scratch/FyW7c // Fox & Falco's aerial Blaster Loop
/// Animation callback
void ftFx_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftFox_SpecialN_UpdateBlaster(fp);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.fx.SpecialN.isBlasterLoop == true) {
            ftFox_SpecialN_BeginLoopTransition(gobj, fp,
                                               ftFx_MS_SpecialAirNLoop);
            ftFox_SpecialN_SetCall(gobj);
            ftFox_SpecialN_FinishLoopTransition(fp);
        } else {
            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNEnd,
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1,
                                      0, NULL);
            ftFox_SpecialN_SetCall(gobj);
            ftFox_SpecialN_FinishEndTransition(fp);
        }
        ftFox_SpecialN_SetCall(gobj);
    }
    {
        Vec3 sp2C;
        ftFox_DatAttrs* da;
        Fighter* fp;

        /// @todo Fake assignment.
        fp = fp = GET_FIGHTER(gobj);

        da = getFtSpecialAttrs(fp);

        /// @todo Unused assignment.
        {
            Fighter* _ = GET_FIGHTER(gobj);
        }

        if (fp->cmd_vars[2] != 0) {
            f64 launchAngle;

            fp->cmd_vars[2] = 0;
            launchAngle =
                ftFox_SpecialN_PrepareBlasterShot(gobj, fp, da, &sp2C);
            ftFox_SpecialN_FireBlasterShot(gobj, fp, da, &sp2C, launchAngle);
        }
    }
}

/// 0x800E69BC
/// https://decomp.me/scratch/OAWla // Fox & Falco's aerial Blaster End
/// Animation callback
void ftFx_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    if (!ftFox_SpecialN_UpdateEndAnimation(gobj, fp)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        if (0 == da->x18_FOX_BLASTER_LANDING_LAG) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, true, 1, da->x18_FOX_BLASTER_LANDING_LAG);
    }
}

/// 0x800E6AB4
/// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Start
/// IASA callback
void ftFx_SpecialNStart_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/// 0x800E6ADC
/// https://decomp.me/scratch/7JCEh // Fox & Falco's grounded Blaster Loop IASA
/// callback
void ftFx_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/// 0x800E6B04 - Fox & Falco's grounded Blaster End IASA callback
void ftFx_SpecialNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x800E6B08
/// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Start IASA
/// callback
void ftFx_SpecialAirNStart_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/// 0x800E6B30
/// https://decomp.me/scratch/7JCEh // Fox & Falco's aerial Blaster Loop IASA
/// callback
void ftFx_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/// 0x800E6B58 - Fox & Falco's aerial Blaster End IASA callback
void ftFx_SpecialAirNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x800E6B5C - Fox & Falco's grounded Blaster Start Physics callback
void ftFx_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 0x800E6B7C - Fox & Falco's grounded Blaster Loop Physics callback
void ftFx_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 0x800E6B9C - Fox & Falco's grounded Blaster End Physics callback
void ftFx_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 0x800E6BBC - Fox & Falco's aerial Blaster Start Physics callback
void ftFx_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// 0x800E6BDC - Fox & Falco's aerial Blaster Loop Physics callback
void ftFx_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// 0x800E6BFC - Fox & Falco's aerial Blaster End Physics callback
void ftFx_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// 0x800E6C1C - Fox & Falco's grounded Blaster Start Collision callback
void ftFx_SpecialNStart_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

/// 0x800E6C3C - Fox & Falco's grounded Blaster Loop Collision callback
void ftFx_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

/// 0x800E6C1C - Fox & Falco's grounded Blaster End Collision callback
void ftFx_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

/// 0x800E6C7C - Fox & Falco's aerial Blaster Start Collision callback
void ftFx_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/// 0x800E6C9C - Fox & Falco's aerial Blaster Loop Collision callback
void ftFx_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/// 0x800E6CBC - Fox & Falco's aerial Blaster End Collision callback
void ftFx_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/// 0x800E6CDC
/// https://decomp.me/scratch/G1jsj // Fox & Falco's Throw Animation callback -
/// spawn Blaster
void ftFx_Throw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;
    s32 ftKind = ftGetKind(fp);

    if (ftKind == FTKIND_FOX || ftKind == FTKIND_FALCO) {
        if (!ftAnim_IsFramesRemaining(gobj)) {
            fp->fv.fx.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(gobj);
            return;
        }
        switch (fp->cmd_vars[1]) {
        case 1:
            if (fp->fv.fx.x222C_blasterGObj == NULL) {
                HSD_GObj* blasterGObj =
                    it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                                ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                                da->x20_FOX_BLASTER_GUN_ITKIND);

                fp->fv.fx.x222C_blasterGObj = blasterGObj;
                if (blasterGObj != NULL) {
                    it_8026BAE8(fp->fv.fx.x222C_blasterGObj,
                                (0.85f * (fp->x34_scale.y *
                                          fp->co_attrs.model_scaling)));
                    ftFox_SpecialN_SetCall(gobj);
                }
                return;
            } else {
                bool flag;

                it_802ADDD0(fp->fv.fx.x222C_blasterGObj, fp->cmd_vars[1]);
                switch (fp->cmd_vars[3]) {
                case 1:
                    fp->cmd_vars[3] = 0;
                    it_802AE538(fp->fv.fx.x222C_blasterGObj);
                    break;
                case 2:
                    fp->cmd_vars[3] = 0;
                    it_802AE608(fp->fv.fx.x222C_blasterGObj);
                    break;
                }
                if (fp->throw_flags_b0 != 0) {
                    fp->throw_flags_b0 = 0;
                    flag = true;
                } else {
                    flag = false;
                }
                if (flag) {
                    Vec3 sp50;
                    Vec3 sp44;

                    ftFx_SpecialN_FtGetHoldJoint(gobj, &sp50);
                    ftFx_SpecialN_ItGetHoldJoint(gobj, &sp44);

                    sp44.z = 0;
                    sp50.z = 0;
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowB:
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw:

                        it_8029C6CC(atan2f(sp50.y - sp44.y, sp50.x - sp44.x),
                                    da->x14_FOX_BLASTER_VEL, gobj, &sp50,
                                    da->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;

                    default:
                        it_8029C6A4(atan2f(sp50.y - sp44.y, sp50.x - sp44.x),
                                    da->x14_FOX_BLASTER_VEL, gobj, &sp50,
                                    da->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;
                    }
                    it_802AE1D0(fp->fv.fx.x222C_blasterGObj);
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw: {
                        switch (ftLib_GetKind(gobj)) {
                        case FTKIND_FOX:
                            ft_PlaySFX(fp, 110109, SFX_VOLUME_MAX,
                                       SFX_PAN_MID);
                            return;
                        case FTKIND_FALCO:
                            ft_PlaySFX(fp, 100105, SFX_VOLUME_MAX,
                                       SFX_PAN_MID);
                            return;
                        }
                    default:
                        break;
                    }
                    case ftCo_MS_ThrowB:
                        switch (ftLib_GetKind(gobj)) {
                        case FTKIND_FOX:
                            ft_PlaySFX(fp, foxSFX[1 == fp->facing_dir],
                                       SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;

                        case FTKIND_FALCO:
                            ft_PlaySFX(fp, falcoSFX[1 == fp->facing_dir],
                                       SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
        case 2:
            if (fp->fv.fx.x222C_blasterGObj != NULL) {
                fp->fv.fx.x222C_blasterGObj = NULL;
                ftFox_SpecialN_SetNULL(gobj);
                switch (ftLib_GetKind(gobj)) {
                case FTKIND_FOX:
                    ft_PlaySFX(fp, 110100, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                case FTKIND_FALCO:
                    ft_PlaySFX(fp, 100096, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                }
            }
            break;
        case 0:
            fp->fv.fx.x222C_blasterGObj = NULL;
            ftFox_SpecialN_SetNULL(gobj);
            ftpickupitem_80094818(gobj, 0);
            break;
        }
    }
}
