/**
 * @file ftsamusspeciallw1.c
 * @brief Down-B: Bomb Drop implementation for Samus
 * @details Implements Samus's Down-B special move (Bomb Drop), including morph
 * ball transformation, hurtbox resizing, bomb spawning accessory callback,
 * grounded hop, and ground/air transition logic. Module prefix: ftSs
 */

#include "ftsamusspeciallw1.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_SquatWait.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/kinds/ftCommon/types.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itsamusbomb.h>
#include <melee/lb/lb_00B0.h>

static MotionFlags const ftSs_MF_SpecialLw_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit |
    Ft_MF_SkipModel;

/**
 * @brief Down-B (Bomb): Accessory callback that instantiates and spawns the
 * bomb item.
 * @details Computes spawn position relative to TopN joint using offset vector
 * (samus_attr->x74_vec), then creates the bomb item entity
 * (It_Kind_Samus_Bomb).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_8012ADF0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    if (ftCheckThrowB0(fp)) {
        Vec3 spawn_pos;
        PAD_STACK(4);
        lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &spawn_pos);
        spawn_pos.x += samus_attr->x74_vec.x * fp->facing_dir;
        spawn_pos.y += samus_attr->x74_vec.y;
        spawn_pos.z += samus_attr->x74_vec.z;
        it_802B4AC8(gobj, &spawn_pos, fp->facing_dir);
        fp->accessory4_cb = NULL;
    }
}

/**
 * @brief Down-B (Bomb): Reconfigures Samus's hurtbox into a single compact
 * sphere (Morph Ball).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_8012AEBC(HSD_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* fp = GET_FIGHTER(gobj);
    ftColl_8007B0C0(gobj, HurtCapsule_Intangible);

    hurt.bone_idx = FtPart_XRotN;
    hurt.height = HurtHeight_Mid;
    hurt.is_grabbable = false;
    hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0;
    hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0;
    hurt.scale = 3;
    ftColl_HurtboxInit(fp, &fp->hurt_capsules[0], &hurt);
}

/**
 * @brief Down-B (Bomb): Restores Samus's default enabled hurtbox capsules.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_8012AF38(HSD_GObj* gobj)
{
    ftColl_8007B0C0(gobj, HurtCapsule_Enabled);
}

/**
 * @brief Helper initializing state variables and registering the bomb drop
 * callback.
 * @param gobj Samus fighter game object pointer
 */
static void ftSamus_SpecialLw_StartAction_inner(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.x0.throw_flags_b0 = 0;
    fp->mv.ss.speciallw_jump.x0 = 0;
    if (fp->cur_anim_frame == 3.0f) {
        fp->cmd_vars[1] = 1;
    }
    fp->accessory4_cb = &ftSs_SpecialLw_8012ADF0;
}

/**
 * @brief Down-B (Bomb): Grounded action state entry callback.
 * @details Retains a fraction of horizontal ground velocity (samus_attr->x6C).
 * If entering from crouch (motion 0x28), skips startup roll and performs a
 * small hop.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    fp->gr_vel *= samus_attr->x6C;
    // Fast morph ball from crouch (0x28 = squat wait)
    if (fp->motion_id == 0x28) {
        Fighter_ChangeMotionState(gobj, 0x163, Ft_MF_None, 3.0f, 1.0f, 0.0f,
                                  NULL);
        ftSamus_SpecialLw_StartAction_inner(gobj);
        fp->cmd_vars[1] = 2;
        ftSs_SpecialLw_8012B5F0(gobj); // Perform vertical hop
        return;
    }
    // Normal grounded bomb drop entry (0x163 = 355: ftSs_MS_SpecialLwBomb)
    Fighter_ChangeMotionState(gobj, 0x163, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftSamus_SpecialLw_StartAction_inner(gobj);
}

/**
 * @brief Down-B (Bomb): Aerial action state entry callback.
 * @details Retains horizontal velocity scaled by x70 and sets vertical
 * velocity to x58.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    fp->self_vel.x *= samus_attr->x70;
    fp->self_vel.y = samus_attr->x58;

    // Aerial bomb drop entry (0x164 = 356: ftSs_MS_SpecialAirLwBomb)
    Fighter_ChangeMotionState(gobj, 0x164, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftSamus_SpecialLw_StartAction_inner(gobj);
}

/**
 * @brief Helper updating morph ball hurtbox state flag.
 * @param fp Fighter instance pointer
 * @param val State flag value
 */
static inline void setSamusBits(Fighter* fp, int val)
{
    fp->mv.ss.speciallw_jump.x0 = val;
}

/**
 * @brief Toggles between morph ball compact hurtbox and standard fighter
 * hurtboxes.
 * @param gobj Samus fighter game object pointer
 */
static inline void checkStateVar1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->cmd_vars[0]) && (!fp->mv.ss.speciallw_jump.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        setSamusBits(fp, 1);
    }
    if ((!fp->cmd_vars[0]) && (fp->mv.ss.speciallw_jump.x0)) {
        ftColl_8007B0C0((Fighter_GObj*) gobj, HurtCapsule_Enabled);
        setSamusBits(fp, 0);
    }
}

/**
 * @brief Down-B (Bomb): Grounded bomb release animation callback.
 * @details Checks hop trigger, updates hurtbox, and returns to grounded wait
 * upon completion.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLwBomb_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] == 1) {
        fp->cmd_vars[1] = 2;
        ftSs_SpecialLw_8012B5F0(gobj); // Trigger vertical hop
        return;
    }

    checkStateVar1(gobj);

    if (!ftAnim_IsFramesRemaining((Fighter_GObj*) gobj)) {
        ft_8008A2BC((Fighter_GObj*) gobj); // Return to wait/idle
    }
}

/**
 * @brief Down-B (Bomb): Aerial bomb release animation callback.
 * @details Updates hurtbox and transitions to normal aerial Fall upon
 * completion.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLwBomb_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    checkStateVar1(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj); // Transition to fall
    }
}

/**
 * @brief Down-B (Bomb): Grounded bomb release IASA callback.
 * @details Checks stick down input to unmorph into squat wait.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLwBomb_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    // Check if stick Y is pushed downward past unmorph threshold
    // (samus_attr->x80)
    if ((fp->cmd_vars[2]) && (fp->input.lstick[0].y < samus_attr->x80)) {
        fp->cmd_vars[2] = 0;
        ftCo_800D638C(gobj);
    }
}

/**
 * @brief Down-B (Bomb): Aerial bomb release IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLwBomb_IASA(HSD_GObj* gobj) {}

/**
 * @brief Down-B (Bomb): Grounded bomb release physics callback.
 * @details Applies horizontal roll movement if morph ball is active
 * (cmd_vars[0]).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLwBomb_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    ftCo_DatAttrs* ft_attr = &fp->co_attrs;

    if (fp->cmd_vars[0]) {
        ftCommon_CalcGroundAccel_AccelToLStickX(
            fp, 0.0f, ft_attr->walk_accel_mul * samus_attr->x64,
            ft_attr->walk_max_vel * samus_attr->x5C);
        ftCommon_SetSelfMovementFromGroundedMovement(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

/**
 * @brief Down-B (Bomb): Aerial bomb release physics callback.
 * @details Applies basic gravity and horizontal drift without friction.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLwBomb_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    ftCo_DatAttrs* ft_attr = &fp->co_attrs;

    u8 _[8];
    ftCommon_FallBasic(fp);
    ftCommon_CalcSelfAccel_DriftSimple_NoFriction(
        fp, 0.0f, ft_attr->air_drift_stick_mul * samus_attr->x68,
        ft_attr->air_drift_max * samus_attr->x60);
}

/**
 * @brief Down-B (Bomb): Grounded bomb release collision callback.
 * @details Checks environment collision; transitions to aerial bomb release if
 * walking off edge.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLwBomb_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (!ft_80082888(gobj, &samus_attr->height_attributes)) {
            ftSs_SpecialLw_8012B570(gobj);
        }
    } else if (!ft_800827A0(gobj)) {
        ftSs_SpecialLw_8012B570(gobj);
    }
}

/**
 * @brief Down-B (Bomb): Aerial bomb release collision callback.
 * @details Checks environment collision; transitions to grounded bomb release
 * upon landing.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLwBomb_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (ft_800824A0(gobj, &samus_attr->height_attributes)) {
            ftSs_SpecialLw_8012B668(gobj);
        }
    } else if (ft_80081D0C(gobj)) {
        ftSs_SpecialLw_8012B668(gobj);
    }
}

/**
 * @brief Helper restoring bomb drop callback and resetting state counters on
 * state transitions.
 * @param gobj Samus fighter game object pointer
 */
static void ftSamus_UnkSetStateAndCb(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    fp->cmd_vars[1] = 2;
    fp->mv.ss.speciallw_jump.x0 = 0;
    fp->accessory4_cb = &ftSs_SpecialLw_8012ADF0;
}

/**
 * @brief Down-B (Bomb): Ground-to-air transition during bomb drop.
 * @details Changes motion state to ftSs_MS_SpecialAirLwBomb (0x164).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_8012B570(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, 0x164, ftSs_MF_SpecialLw_Coll);
    ftSamus_UnkSetStateAndCb(gobj);
}

/**
 * @brief Down-B (Bomb): Ground-to-air transition with vertical hop during bomb
 * drop.
 * @details Sets vertical velocity to samus_attr->x54 and changes motion state
 * to 0x164.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_8012B5F0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    fp->self_vel.y = samus_attr->x54; // Vertical hop velocity
    ftCommon_GroundToAirStateChange(gobj, fp, 0x164, ftSs_MF_SpecialLw_Coll);
    fp->accessory4_cb = ftSs_SpecialLw_8012ADF0;
}

/**
 * @brief Down-B (Bomb): Air-to-ground transition during bomb drop.
 * @details Changes motion state to ftSs_MS_SpecialLwBomb (0x163).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_8012B668(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, 0x163, ftSs_MF_SpecialLw_Coll);
    ftSamus_UnkSetStateAndCb(gobj);
}
