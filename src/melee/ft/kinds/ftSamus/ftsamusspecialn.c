/**
 * @file ftsamusspecialn.c
 * @brief Neutral-B: Charge Shot and Side-B missile helpers implementation for
 * Samus
 * @details Implements Samus's Neutral-B special move (Charge Shot), including
 * startup, charging loop with pitch-escalating audio, charge
 * storage/cancellation via shield or roll, aerial firing recoil physics,
 * ledge-slip auto-fire mechanic, and Side-B missile spawn callbacks. Module
 * prefix: ftSs
 */

#include "ftsamusspecialn.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcolanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Escape.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itsamusmissile.h>
#include <melee/lb/lb_00B0.h>

/**
 * @brief Neutral-B (Charge Shot): Computes aerial horizontal recoil velocity
 * based on charge level.
 * @details Formula: recoil_vx = facing_dir * (samus_attr->x1C * charge_level).
 * @param gobj Samus fighter game object pointer
 */
static void ftSamus_801293BC_inner(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    s32 charge_level = fp->u.ss.x2230;
    // Aerial recoil pushback scaled by charge level
    fp->self_vel.x = (fp->facing_dir * (samus_attr->x1C * charge_level));
}

/**
 * @brief Neutral-B (Charge Shot): Clears Charge Shot item reference and
 * destroys visual effects.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_801291F0(HSD_GObj* gobj)
{
    PAD_STACK(8);

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->u.ss.x222C) {
            fp->u.ss.x222C = 0;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Resets charge level to 0 and clears visual
 * effects.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_80129258(HSD_GObj* gobj)
{
    PAD_STACK(8);

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSamus_UnkAndDestroyAllEF(gobj);
        fp->u.ss.x2230 = 0; // Reset charge level
    }
}

/**
 * @brief Neutral-B (Charge Shot): Spawns the Charge Shot item entity at the
 * arm cannon.
 * @param gobj Samus fighter game object pointer
 * @return True if item spawn failed, false on success
 */
static bool ftSs_SpecialN_801292E4(HSD_GObj* gobj)
{
    Vec3 spawn_pos;
    Vec3 offset;

    HSD_GObj* charge_gobj;

    u8 _[8];

    Fighter* fp = getFighter(gobj);

    if ((fp->cmd_vars[0] == 1U) && (!fp->u.ss.x222C)) {
        fp->cmd_vars[0] = 0U;
        offset.z = 4;
        offset.y = 0;
        offset.x = 0;
        // Obtain world position of right hand / arm cannon bone
        // (FtPart_RHandNb)
        lb_8000B1CC(fp->parts[FtPart_RHandNb].joint, &offset, &spawn_pos);
        spawn_pos.z = 0;
        charge_gobj = it_802B55C8(gobj, &spawn_pos, FtPart_RHandNb,
                                  It_Kind_Samus_Charge, fp->facing_dir);
        fp->u.ss.x222C = charge_gobj;
        if (charge_gobj != NULL) {
            ftSamus_updateDamageDeathCBs(gobj);
        } else {
            fp->u.ss.x222C = 0U;
            return true;
        }
    }
    return false;
}

/**
 * @brief Neutral-B (Charge Shot): Releases / fires the Charge Shot projectile.
 * @details Sets projectile velocity based on charge level, applies aerial
 * recoil, spawns muzzle blast effect (ID 1158), and resets charge level.
 * @param gobj Samus fighter game object pointer
 */
static void ftSs_SpecialN_801293BC(HSD_GObj* gobj)
{
    ftSs_DatAttrs* samus_attr;
    HSD_GObj* held_item;
    Fighter* fp;
    f64 fire_angle;
    u8 unused0[20];

    fp = getFighterPlus(gobj);
    samus_attr = fp->dat_attrs;

    if ((fp->cmd_vars[1] == 1) && (fp->u.ss.x222C)) {
        Vec3 spawn_pos;
        u32 charge_level;

        fp->cmd_vars[1] = 2;
        lb_8000B1CC(fp->parts[FtPart_ThrowN].joint, NULL, &spawn_pos);
        spawn_pos.z = 0;
        held_item = fp->item_gobj;
        // Set fire direction (0 = right, pi = left)
        if (fp->facing_dir == +1) {
            fire_angle = 0;
        } else {
            fire_angle = M_PI;
        }
        charge_level = fp->u.ss.x2230;
        it_802B56E4(fp->u.ss.x222C, &spawn_pos, fire_angle, charge_level,
                    samus_attr->x18);
        // Apply aerial recoil velocity if firing in midair
        if ((fp->motion_id == 348) || (fp->ground_or_air == GA_Air)) {
            u8 unused1[28];
            ftSamus_801293BC_inner(gobj);
        }
        fp->u.ss.x2230 = 0U; // Clear stored charge level

        ftSs_SpecialN_801291F0(gobj);
        efSync_Spawn(1158, gobj, &spawn_pos,
                     &fp->facing_dir); // Muzzle flash effect
        fp->item_gobj = held_item;
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_Enter(HSD_GObj* gobj)
{
    Vec3* self_vel;
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    // Change to ftSs_MS_SpecialNStart (343)
    Fighter_ChangeMotionState(gobj, 343, Ft_MF_None, 0, 1, 0, NULL);
    Fighter_ClearCmdVars(fp);
    ftCommon_8007D7FC(fp);
    self_vel = &fp->self_vel;
    self_vel->y = 0;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.specialn.x0 = 0; // Grounded startup flag
    fp->mv.ss.specialn.x4 = 0; // Charge tick frame counter
    fp->mv.ss.specialn.x8 = 0;
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Aerial action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    // Change to ftSs_MS_SpecialAirNStart (347)
    Fighter_ChangeMotionState(gobj, 347, Ft_MF_None, 0, 1, 0, NULL);
    Fighter_ClearCmdVars(fp);
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.specialn.x0 = 1; // Aerial startup flag
    fp->mv.ss.specialn.x4 = 0;
    fp->mv.ss.specialn.x8 = 0;
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Grounded startup animation callback.
 * @details If already fully charged or in aerial state, proceeds directly to
 * fire (state 346); otherwise transitions into charging loop (state 344).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    ftSs_SpecialN_801292E4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // If already fully charged (charge_level == samus_attr->x18), fire
        // immediately
        if ((fp->mv.ss.specialn.x0 == 1) ||
            (fp->u.ss.x2230 == samus_attr->x18))
        {
            Fighter_ChangeMotionState(gobj, 346, Ft_MF_None, 0, 1, 0,
                                      NULL); // ftSs_MS_SpecialN (Fire)
        } else {
            Fighter_ChangeMotionState(gobj, 344, Ft_MF_None, 0, 1, 0,
                                      NULL); // ftSs_MS_SpecialNHold (Charging)
            ftSamus_SetAttrx2334(gobj);
        }
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/// Sound effect IDs for ascending pitch tones during charging
u32 ftSs_Unk3_803CE6B8[] = {
    0x0003F7A6, 0x0003F7A9, 0x0003F7AC, 0x0003F7AF, 0x0003F7B2,
};

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop animation callback.
 * @details Increments charge level every samus_attr->x20 frames and plays
 * ascending audio. When maximum charge (samus_attr->x18) is reached, triggers
 * full charge flash and enters cancel state.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    Fighter* fighter2;
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;

    u8 unused1[40];

    fp = fighter2 = getFighter(gobj);
    samus_attr = samus_attr2 = fp->dat_attrs;
    // Play pitch-shifted charging sound on tick
    if (fighter2->cmd_vars[2]) {
        float charge_ratio;
        s32 index;
        fighter2->cmd_vars[2] = 0;
        if (fighter2->u.ss.x2230) {
            charge_ratio = (float) fighter2->u.ss.x2230 / samus_attr->x18;
        } else {
            charge_ratio = 0.0f;
        }
        index = 5 * charge_ratio;
        ft_80088510(fighter2, ftSs_Unk3_803CE6B8[index], 127, 64);
    }

    // Increment charging frame timer
    fp->mv.ss.specialn.x4 += 1;
    if (fp->mv.ss.specialn.x4 > samus_attr->x20) {
        fp->mv.ss.specialn.x4 = 0;
        fp->u.ss.x2230 += 1; // Increment charge level
        // Check if maximum charge reached
        if (fp->u.ss.x2230 >= samus_attr->x18) {
            ftCo_800BFFD0(fp, 53, 0); // Full charge sparkle/audio
            fp->u.ss.x2230 = samus_attr->x18;
            Fighter_ChangeMotionState(gobj, 345, Ft_MF_None, 0, 1, 0,
                                      0); // ftSs_MS_SpecialNCancel
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel animation callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNCancel_Anim(HSD_GObj* gobj)
{
    u8 _[20];

    ftSamus_UnkAndDestroyAllEF(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Return to grounded wait
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded firing animation callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_Anim(HSD_GObj* gobj)
{
    u8 _[24];

    ftSs_SpecialN_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Return to grounded wait
    }
}

/**
 * @brief Neutral-B (Charge Shot): Aerial startup animation callback.
 * @details On animation end, transitions to aerial firing state 348.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftSs_SpecialN_801292E4(gobj);
    fp->mv.ss.specialn.x0 = 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 348, Ft_MF_None, 0, 1, 0,
                                  NULL); // ftSs_MS_SpecialAirN
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Aerial firing animation callback.
 * @details On animation end, transitions to helpless fall with landing lag
 * (samus_attr->x24).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    ftSs_SpecialN_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (samus_attr->x24 == 0) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1, samus_attr->x24);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded startup IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNStart_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop IASA callback.
 * @details Handles B press to fire immediately, L/R to cancel into hold state,
 * or shield / roll input via ftCo_8009917C.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNHold_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* fighterObj2;

    u8 _[32];

    // Check roll / shield interrupt
    if (ftCo_8009917C(gobj)) {
        fighterObj2 = gobj;
        ftSamus_UnkAndDestroyAllEF(fighterObj2);
    } else {
        // Press B: Fire Charge Shot immediately
        if (fp->input.pressed_buttons & HSD_PAD_B) {
            Fighter_ChangeMotionState(gobj, 346, Ft_MF_None, 0, 1, 0, NULL);
            ftSamus_updateDamageDeathCBs(gobj);
            return;
        }
        // Press L or R: Cancel charging
        if (fp->input.pressed_buttons & HSD_PAD_LR) {
            Fighter_ChangeMotionState(gobj, 345, Ft_MF_None, 0, 1, 0, NULL);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNCancel_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Neutral-B (Charge Shot): Grounded firing IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Neutral-B (Charge Shot): Aerial startup IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Neutral-B (Charge Shot): Aerial firing IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirN_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Neutral-B (Charge Shot): Grounded startup physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNHold_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Grounded firing physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Aerial startup physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Aerial firing physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Neutral-B (Charge Shot): Grounded startup collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_GroundToAirStateChange(gobj, fp, 347,
                                        ftCommon_GroundAirColl_MF);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop collision callback.
 * @details If Samus slips or is pushed off a ledge while charging, transitions
 * to aerial firing state (348) and immediately releases the Charge Shot.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNHold_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    // Check if grounded contact lost (ledge slip)
    if (!ft_80082708(gobj)) {
        ftCommon_GroundToAirStateChange(gobj, fp, 348,
                                        ftCommon_GroundAirColl_MF);
        ftSamus_updateDamageDeathCBs(gobj);
        ft_PlaySFX(fp, 260021, 127, 64);
        fp->cmd_vars[1] = 1; // Force immediate shot release in air
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_GroundToAirStateChange(gobj, fp, 348,
                                        ftCommon_GroundAirColl_MF);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Grounded firing collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_GroundToAirStateChange(gobj, fp, 348,
                                        ftCommon_GroundAirColl_MF);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Aerial startup collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_AirToGroundStateChange(gobj, fp, 343,
                                        ftCommon_GroundAirColl_MF);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/**
 * @brief Neutral-B (Charge Shot): Aerial firing collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_AirToGroundStateChange(gobj, fp, 346,
                                        ftCommon_GroundAirColl_MF);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

/**
 * @brief Side-B (Missile): Returns current missile count / identifier.
 * @param gobj Samus fighter game object pointer
 * @return Missile count value
 */
int ftSs_SpecialS_8012A068(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->u.ss.x2238;
}

static void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation);

/**
 * @brief Side-B (Missile): Accessory callback that instantiates and fires a
 * missile item.
 * @details Differentiates between normal Homing Missile (SpecialS/SpecialAirS,
 * flag=false) and Super Missile (SpecialSSmash/SpecialAirSSmash, flag=true).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_8012A074(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    if (ftCheckThrowB0(fp)) {
        Vec3 position;
        fp->u.ss.x2238++;
        // Bone 56 corresponds to the tip of Samus's arm cannon
        lb_8000B1CC(fp->parts[FtPart_56].joint, NULL, &position);
        position.x += samus_attr->x34 * fp->facing_dir;

        // Check if regular tilt input (Homing Missile) or smash input (Super
        // Missile)
        if (fp->motion_id == ftSs_MS_SpecialS ||
            fp->motion_id == ftSs_MS_SpecialAirS)
        {
            PAD_STACK(4);
            it_802B62D0(gobj, &position, false,
                        fp->facing_dir); // Homing Missile
        } else {
            it_802B62D0(gobj, &position, true,
                        fp->facing_dir); // Super Missile
        }

        ftSs_SpecialS_8012A168(gobj, &position);
        fp->accessory4_cb = 0;
    }
}

/**
 * @brief Side-B (Missile): Spawns muzzle blast effect (ID 1155) at the arm
 * cannon tip.
 * @param gobj Samus fighter game object pointer
 * @param spawnlocation World coordinates of missile spawn point
 */
static void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1155, gobj, spawnlocation);
        fp->x2219_b0 = 1;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
}
