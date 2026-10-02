/**
 * @file ftfoxspecialn.c
 * @brief Neutral-B (Blaster)
 * @details Implements Fox and Falco's Neutral-B special move (Blaster).
 * Handles spawning and managing the Blaster gun item entity, firing laser shot
 * projectiles, the continuous firing loop (enabling Short Hop Double Laser),
 * holster animations, and firing laser shots during Fox/Falco's throws.
 * Module prefix: ftFx
 */

#include "ftfoxspecialn.h"

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

#include <math.h>

#include "ftfox.h"
#include "inlines.h"
#include "types.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ft_0C8C.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftpickupitem.h>
#include <melee/ft/types.h>
#include <melee/it/it_26B1.h>
#include <melee/it/kinds/itfoxblaster.h>
#include <melee/it/kinds/itfoxlaser.h>
#include <melee/lb/lb_00B0.h>
#include <sysdolphin/baselib/debug.h>

/**
 * @brief Computes world position of Blaster muzzle from right thumb joint
 * @param gobj The fighter's game object
 * @param[out] pos Output world coordinates
 * @param z_offset Z offset along bone
 */
static inline void ftFox_SpecialN_GetHoldJoint(HSD_GObj* gobj, Vec3* pos,
                                               f32 z_offset)
{
    Vec3 joint_offset;

    // Double fp init otherwise this will not match when inlined
    Fighter* fp = fp = GET_FIGHTER(gobj);

    joint_offset.x = 0;
    joint_offset.y = 1.2325000762939453f;
    joint_offset.z = z_offset;

    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                &joint_offset, pos);
}

/**
 * @brief Gets Blaster muzzle world position for fighter laser effects (z
 * = 4.2636f)
 * @param gobj The fighter's game object
 * @param[out] pos Output world coordinates
 */
void ftFx_SpecialN_FtGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    ftFox_SpecialN_GetHoldJoint(gobj, pos, 4.263599872589111f);
}

/**
 * @brief Gets Blaster muzzle world position for item laser effects (z =
 * 0.0136f)
 * @param gobj The fighter's game object
 * @param[out] pos Output world coordinates
 */
void ftFx_SpecialN_ItGetHoldJoint(HSD_GObj* gobj, Vec3* pos)
{
    ftFox_SpecialN_GetHoldJoint(gobj, pos, 0.013600001111626625f);
}

/**
 * @brief Callback when action state changes during Blaster
 * @param gobj The fighter's game object
 */
void ftFx_SpecialN_OnChangeAction(HSD_GObj* gobj)
{
    PAD_STACK(8);

    ft_800892A0(gobj);
    ft_80089824(gobj);
}

/**
 * @brief Checks if the Blaster item GObj pointer is NULL
 * @param gobj The fighter's game object
 * @return True if blaster GObj is NULL, false otherwise
 */
bool ftFx_SpecialN_CheckRemoveBlaster(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.fx.x222C_blasterGObj == NULL) {
        return true;
    }
    return false;
}

/**
 * @brief Maps current motion state to Blaster sub-action index
 * @param gobj The fighter's game object
 * @return Sub-action index (0..5 for SpecialN, 6..8 for throws, 9 for none)
 */
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

/**
 * @brief Checks if current action is an active Blaster action
 * @param gobj The fighter's game object
 * @return True if Blaster should remain active, false otherwise
 */
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

            if (fp->x2070.x0.x2071_b6) {
                return true;
            }
            return false;
        }
    }
    return true;
}

/**
 * @brief Clears Blaster GObj pointer and removes damage callback
 * @param gobj The fighter's game object
 */
void ftFx_SpecialN_ClearBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.fx.x222C_blasterGObj != NULL) {
        fp->u.fx.x222C_blasterGObj = NULL;
    }
    Fighter_SetDamageCallback(gobj, NULL);
}

/**
 * @brief Destroys Blaster item entity and clears pointer
 * @param gobj The fighter's game object
 */
void ftFx_SpecialN_RemoveBlaster(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.fx.x222C_blasterGObj != NULL) {
        it_802AEAB4(fp->u.fx.x222C_blasterGObj);
        fp->u.fx.x222C_blasterGObj = NULL;
    }
    if (ftFx_Init_800E5534(gobj) == false) {
        Fighter_SetDamageCallback(gobj, NULL);
    }
}

/// Sound effect IDs for Fox Blaster shot [facing_right, facing_left]
u32 foxSFX[2] = { 110103, 110106 };
/// Sound effect IDs for Falco Blaster shot [facing_right, facing_left]
u32 falcoSFX[2] = { 100099, 100102 };

/**
 * @brief Prepares Blaster muzzle position and computes firing angle
 * @param gobj The fighter's game object
 * @param fp Pointer to the Fighter data structure
 * @param da Character attributes
 * @param[out] pos Output muzzle coordinates
 * @return Firing angle in radians
 */
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

/**
 * @brief Spawns laser shot projectile and triggers SFX
 * @param gobj The fighter's game object
 * @param fp Pointer to the Fighter data structure
 * @param da Character attributes
 * @param pos Muzzle world coordinates
 * @param launch_angle Firing angle in radians
 */
static inline void ftFox_SpecialN_FireBlasterShot(HSD_GObj* gobj, Fighter* fp,
                                                  ftFox_DatAttrs* da,
                                                  Vec3* pos, f64 launch_angle)
{
    it_8029C6A4(launch_angle, da->x14_FOX_BLASTER_VEL, gobj, pos,
                da->x1C_FOX_BLASTER_SHOT_ITKIND);
    it_802AE1D0(fp->u.fx.x222C_blasterGObj);

    switch (ftLib_GetKind(gobj)) {
    case Ft_Kind_Fox:
        ft_PlaySFX(fp, foxSFX[fp->facing_dir == -1], SFX_VOLUME_MAX,
                   SFX_PAN_MID);
        return;
    case Ft_Kind_Falco:
        ft_PlaySFX(fp, falcoSFX[fp->facing_dir == -1], SFX_VOLUME_MAX,
                   SFX_PAN_MID);
        return;
    default:
        break;
    }
}

/**
 * @brief Animation script accessory callback to spawn laser projectile
 * @param gobj The fighter's game object
 */
void ftFx_SpecialN_CreateBlasterShot(HSD_GObj* gobj)
{
    Vec3 shot_pos;

    ftFox_DatAttrs* da;
    Fighter* fp;
    f64 launchAngle;

    PAD_STACK(4);

    /// @todo Seems fake, probably one or more missing @c inline functions.
#ifdef MUST_MATCH
    fp =
#endif
        fp = GET_FIGHTER(gobj);

    da = getFtSpecialAttrs(fp);

    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        launchAngle =
            ftFox_SpecialN_PrepareBlasterShot(gobj, fp, da, &shot_pos);
        ftFox_SpecialN_FireBlasterShot(gobj, fp, da, &shot_pos, launchAngle);
    }
}

/**
 * @brief Spawns the Blaster gun item attached to the fighter's hand
 * @param gobj The fighter's game object
 * @param fp Pointer to the Fighter data structure
 * @param da Character attributes
 * @param assert_line Source line for assertion if spawning fails
 */
static inline void ftFox_SpecialN_SpawnBlaster(HSD_GObj* gobj, Fighter* fp,
                                               ftFox_DatAttrs* da,
                                               int assert_line)
{
    HSD_GObj* blaster_gobj =
        it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                    ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                    da->x20_FOX_BLASTER_GUN_ITKIND);
    fp->u.fx.x222C_blasterGObj = blaster_gobj;

    if (blaster_gobj != NULL) {
        it_8026BAE8(fp->u.fx.x222C_blasterGObj, 0.85);
        Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    /// @todo Replace direct __assert with HSD_ASSERT once byte matching is
    /// verified.
    __assert("ftfoxspecialn.c", assert_line, "0");
}

/**
 * @brief Resets command variables and advances animation frame
 * @param gobj The fighter's game object
 * @param fp Pointer to the Fighter data structure
 */
static inline void ftFox_SpecialN_InitializeState(HSD_GObj* gobj, Fighter* fp)
{
    Fighter_ClearCmdVars(fp);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Action State initialization for grounded Neutral-B (Blaster)
 * @details Spawns blaster gun and zeroes ground/self velocity.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialNStart, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftFox_SpecialN_InitializeState(gobj, fp);

    fp->gr_vel = 0;
    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    ftFox_SpecialN_SpawnBlaster(gobj, fp, da, 305);
}

/**
 * @brief Action State initialization for aerial Neutral-B (Blaster)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNStart, Ft_MF_None, 0, 1,
                              0, NULL);
    ftFox_SpecialN_InitializeState(gobj, fp);

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    ftFox_SpecialN_SpawnBlaster(gobj, fp, da, 333);
}

/**
 * @brief Updates Blaster model animation state
 * @param fp Pointer to the Fighter data structure
 */
static inline void ftFox_SpecialN_UpdateBlaster(Fighter* fp)
{
    it_802ADDD0(fp->u.fx.x222C_blasterGObj, 1);
    if (fp->cmd_vars[3] == 1 && fp->u.fx.x222C_blasterGObj != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE538(fp->u.fx.x222C_blasterGObj);
    }
}

/**
 * @brief Helper for draw animation completing and entering firing loop
 * @param gobj The fighter's game object
 * @param loop_msid Motion state ID of the loop to transition into
 */
static inline void ftFox_SpecialN_StartAnimation(HSD_GObj* gobj,
                                                 FtMotionId loop_msid)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftFox_SpecialN_UpdateBlaster(fp);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(
            gobj, loop_msid, (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1, 0, NULL);
        Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
        fp->accessory4_cb = ftFx_SpecialN_CreateBlasterShot;
        it_802ADDD0(fp->u.fx.x222C_blasterGObj, 1);
    }
}

/**
 * @brief Animation callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
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
    it_802ADDD0(fp->u.fx.x222C_blasterGObj, 1);
}

static inline void ftFox_SpecialN_FinishEndTransition(Fighter* fp)
{
    HSD_GObj* blaster_gobj = fp->u.fx.x222C_blasterGObj;
    fp->cmd_vars[1] = 1;
    it_802ADDD0(blaster_gobj, 1);
}

/**
 * @brief Animation callback for grounded Neutral-B firing loop
 * @details If `isBlasterLoop` is true (from tapping B), repeats firing loop.
 * Otherwise transitions to holster animation (SpecialNEnd).
 * @param gobj The fighter's game object
 */
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
        Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
    }
    {
        Vec3 shot_pos;
        ftFox_DatAttrs* da;
        f64 launchAngle;

        fp = GET_FIGHTER(gobj);
        da = getFtSpecialAttrs(fp);

        /// @todo Unused assignment.
        {
            Fighter* _ = GET_FIGHTER(gobj);
        }

        if (fp->cmd_vars[2] != 0) {
            fp->cmd_vars[2] = 0;
            launchAngle =
                ftFox_SpecialN_PrepareBlasterShot(gobj, fp, da, &shot_pos);
            ftFox_SpecialN_FireBlasterShot(gobj, fp, da, &shot_pos,
                                           launchAngle);
        }
    }
}

static inline void ftFox_SpecialN_RemoveBlasterNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.fx.x222C_blasterGObj != NULL) {
        fp->u.fx.x222C_blasterGObj = NULL;
    }
    Fighter_SetDamageCallback(gobj, NULL);
}

static inline bool ftFox_SpecialN_UpdateEndAnimation(HSD_GObj* gobj,
                                                     Fighter* fp)
{
    it_802ADDD0(fp->u.fx.x222C_blasterGObj, fp->cmd_vars[1]);
    if (fp->cmd_vars[1] == 2) {
        ftpickupitem_80094818(gobj, 0);
    }
    if (fp->cmd_vars[3] == 2 && fp->u.fx.x222C_blasterGObj != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE608(fp->u.fx.x222C_blasterGObj);
    }
    return ftAnim_IsFramesRemaining(gobj);
}

/**
 * @brief Animation callback for grounded Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    if (!ftFox_SpecialN_UpdateEndAnimation(gobj, fp)) {
        ftFox_SpecialN_RemoveBlasterNULL(gobj);
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Animation callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    ftFox_SpecialN_StartAnimation(gobj, ftFx_MS_SpecialAirNLoop);
}

/**
 * @brief Animation callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftFox_SpecialN_UpdateBlaster(fp);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.fx.SpecialN.isBlasterLoop == true) {
            ftFox_SpecialN_BeginLoopTransition(gobj, fp,
                                               ftFx_MS_SpecialAirNLoop);
            Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
            ftFox_SpecialN_FinishLoopTransition(fp);
        } else {
            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirNEnd,
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1,
                                      0, NULL);
            Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
            ftFox_SpecialN_FinishEndTransition(fp);
        }
        Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
    }
    {
        Vec3 shot_pos;
        ftFox_DatAttrs* da;

        fp = GET_FIGHTER(gobj);
        da = getFtSpecialAttrs(fp);

        /// @todo Unused assignment.
        {
            Fighter* _ = GET_FIGHTER(gobj);
        }

        if (fp->cmd_vars[2] != 0) {
            f64 launchAngle;

            fp->cmd_vars[2] = 0;
            launchAngle =
                ftFox_SpecialN_PrepareBlasterShot(gobj, fp, da, &shot_pos);
            ftFox_SpecialN_FireBlasterShot(gobj, fp, da, &shot_pos,
                                           launchAngle);
        }
    }
}

/**
 * @brief Animation callback for aerial Neutral-B holster weapon
 * @details If landing lag is 0 (Fox), enters normal fall (ftCo_Fall_Enter)
 * without special fall lag upon completing the move in the air.
 * @param gobj The fighter's game object
 */
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

/**
 * @brief IASA callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNStart_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/**
 * @brief IASA callback for grounded Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/**
 * @brief IASA callback for grounded Neutral-B holster weapon (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief IASA callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNStart_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/**
 * @brief IASA callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    ftFox_SpecialN_CheckLoopInput(gobj);
}

/**
 * @brief IASA callback for aerial Neutral-B holster weapon (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for grounded Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for grounded Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/**
 * @brief Physics callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/**
 * @brief Physics callback for aerial Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/**
 * @brief Collision callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNStart_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

/**
 * @brief Collision callback for grounded Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

/**
 * @brief Collision callback for grounded Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

/**
 * @brief Collision callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/**
 * @brief Collision callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/**
 * @brief Collision callback for aerial Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/**
 * @brief Animation callback for Fox and Falco's throws that fire Blaster shots
 * @details Fires blaster shots into opponents during Back Throw, Up Throw,
 * Down Throw. Spawns blaster item, aligns it to hand bone, fires laser
 * projectile, and plays sound.
 * @param gobj The fighter's game object
 */
void ftFx_Throw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;
    s32 ftKind = ftGetKind(fp);

    if (ftKind == Ft_Kind_Fox || ftKind == Ft_Kind_Falco) {
        if (!ftAnim_IsFramesRemaining(gobj)) {
            fp->u.fx.x222C_blasterGObj = NULL;
            Fighter_SetDamageCallback(gobj, NULL);
            return;
        }
        switch (fp->cmd_vars[1]) {
        case 1:
            if (fp->u.fx.x222C_blasterGObj == NULL) {
                HSD_GObj* blasterGObj =
                    it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                                ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                                da->x20_FOX_BLASTER_GUN_ITKIND);

                fp->u.fx.x222C_blasterGObj = blasterGObj;
                if (blasterGObj != NULL) {
                    it_8026BAE8(fp->u.fx.x222C_blasterGObj,
                                (0.85f * (fp->x34_scale.y *
                                          fp->co_attrs.model_scaling)));
                    Fighter_SetDamageCallback(gobj, ftFx_Init_800E5588);
                }
                return;
            } else {
                it_802ADDD0(fp->u.fx.x222C_blasterGObj, fp->cmd_vars[1]);
                switch (fp->cmd_vars[3]) {
                case 1:
                    fp->cmd_vars[3] = 0;
                    it_802AE538(fp->u.fx.x222C_blasterGObj);
                    break;
                case 2:
                    fp->cmd_vars[3] = 0;
                    it_802AE608(fp->u.fx.x222C_blasterGObj);
                    break;
                }
                if (ftCheckThrowB0(fp)) {
                    Vec3 ft_joint_pos;
                    Vec3 it_joint_pos;

                    ftFx_SpecialN_FtGetHoldJoint(gobj, &ft_joint_pos);
                    ftFx_SpecialN_ItGetHoldJoint(gobj, &it_joint_pos);

                    it_joint_pos.z = 0;
                    ft_joint_pos.z = 0;
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowB:
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw:

                        it_8029C6CC(atan2f(ft_joint_pos.y - it_joint_pos.y,
                                           ft_joint_pos.x - it_joint_pos.x),
                                    da->x14_FOX_BLASTER_VEL, gobj,
                                    &ft_joint_pos,
                                    da->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;

                    default:
                        it_8029C6A4(atan2f(ft_joint_pos.y - it_joint_pos.y,
                                           ft_joint_pos.x - it_joint_pos.x),
                                    da->x14_FOX_BLASTER_VEL, gobj,
                                    &ft_joint_pos,
                                    da->x1C_FOX_BLASTER_SHOT_ITKIND);
                        break;
                    }
                    it_802AE1D0(fp->u.fx.x222C_blasterGObj);
                    switch (ftGetAction(fp)) {
                    case ftCo_MS_ThrowHi:
                    case ftCo_MS_ThrowLw: {
                        switch (ftLib_GetKind(gobj)) {
                        case Ft_Kind_Fox:
                            ft_PlaySFX(fp, 110109, SFX_VOLUME_MAX,
                                       SFX_PAN_MID);
                            return;
                        case Ft_Kind_Falco:
                            ft_PlaySFX(fp, 100105, SFX_VOLUME_MAX,
                                       SFX_PAN_MID);
                            return;
                        default:
                            break;
                        }
                    default:
                        break;
                    }
                    case ftCo_MS_ThrowB:
                        switch (ftLib_GetKind(gobj)) {
                        case Ft_Kind_Fox:
                            ft_PlaySFX(fp, foxSFX[1 == fp->facing_dir],
                                       SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;

                        case Ft_Kind_Falco:
                            ft_PlaySFX(fp, falcoSFX[1 == fp->facing_dir],
                                       SFX_VOLUME_MAX, SFX_PAN_MID);
                            return;
                        default:
                            break;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
        case 2:
            if (fp->u.fx.x222C_blasterGObj != NULL) {
                fp->u.fx.x222C_blasterGObj = NULL;
                Fighter_SetDamageCallback(gobj, NULL);
                switch (ftLib_GetKind(gobj)) {
                case Ft_Kind_Fox:
                    ft_PlaySFX(fp, 110100, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                case Ft_Kind_Falco:
                    ft_PlaySFX(fp, 100096, SFX_VOLUME_MAX, SFX_PAN_MID);
                    return;
                default:
                    break;
                }
            }
            break;
        case 0:
            fp->u.fx.x222C_blasterGObj = NULL;
            Fighter_SetDamageCallback(gobj, NULL);
            ftpickupitem_80094818(gobj, 0);
            break;
        }
    }
}
