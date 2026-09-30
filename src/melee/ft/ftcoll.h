/**
 * @file ftcoll.h
 * @brief Fighter collision system declarations.
 * @details Declares collision detection functions for offensive hitboxes, defensive hurtboxes,
 * shields, reflectors, absorbers, grabs, pushback physics, and environmental collision boxes (ECB).
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_0763C0
#define GALE01_0763C0

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>
#include <melee/it/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <placeholder.h>

#include <dolphin/mtx.h>

/**
 * @brief Updates consecutive hit / combo counter for an attacker hitting a victim.
 * @details Increments repeat-hit counter (fp->x2090) when the same attack connects consecutively.
 * If repeat count exceeds threshold (p_ftCommonData->x4C4), sets consecutive pushback frames (fp->x2092).
 * @param attacker Attacking fighter GObj
 * @param victim Defending fighter GObj receiving the hit
 * @param attackID Action / attack move identifier
 */
/* 0763C0 */ void ftColl_800763C0(Fighter_GObj* attacker, Fighter_GObj* victim,
                                  enum_t attackID);

/**
 * @brief Updates combo counter using the attacker's current attack ID.
 * @param attacker Attacking fighter GObj
 * @param victim Defending fighter GObj
 */
/* 076444 */ void ftColl_80076444(Fighter_GObj* attacker,
                                  Fighter_GObj* victim);

/**
 * @brief Updates combo counter for hits originating from a held or thrown item.
 * @param attackItem Item GObj dealing the damage
 * @param victim Defending fighter GObj
 */
/* 07646C */ void ftColl_8007646C(Fighter_GObj* attackItem,
                                  Fighter_GObj* victim);

/**
 * @brief Decrements combo duration timer and ends combo tracking if elapsed.
 * @param gobj Pointer to fighter GObj
 */
/* 0764DC */ void ftColl_800764DC(Fighter_GObj* gobj);

/**
 * @brief Applies horizontal pushback displacement on grounded fighters during consecutive hits.
 * @details Decrements fp->x2092 and pushes the fighter backward along floor normal if grounded.
 * @param gobj Pointer to fighter GObj
 */
/* 076528 */ void ftColl_80076528(Fighter_GObj* gobj);

/**
 * @brief Clears victim pointer from all attacking fighters when a victim despawns.
 * @param victim Defending fighter GObj being despawned or unloaded
 */
/* 0765AC */ void ftColl_800765AC(Fighter_GObj* victim);

/**
 * @brief Resets per-frame damage log indices.
 * @details Clears dmg_log0_idx and dmg_log1_idx at the start of attack collision processing.
 */
/* 0765E0 */ void ftColl_800765E0(void);

/**
 * @brief Computes scaled damage factoring grab state, frozen ice state, and behavior multipliers.
 * @param fp Attacking fighter data
 * @param victim Defending fighter GObj
 * @param unk_floatvar Base damage amount
 * @return Modified damage amount
 */
/* 0765F0 */ float ftColl_800765F0(Fighter* fp, Fighter_GObj* victim,
                                   float unk_floatvar);

/**
 * @brief Applies incoming damage to fighter's percent accumulator or armor/shield.
 * @details Subtracts from armor (fp->dmg.x1834) if active; otherwise adds to fp->dmg.x1838_percentTemp.
 * @param fp Defending fighter data
 * @param dmg Pointer to damage amount (modified if partially absorbed by armor)
 * @return True if damage was applied to fighter percent; false if absorbed
 */
/* 076640 */ bool ftColl_80076640(Fighter* fp, float* dmg);

/**
 * @brief Records a damage collision event into the primary damage log (dmg_log0).
 * @param arg0 Collision kind / source type
 * @param arg1 Collision sub-kind
 * @param arg2 Source entity GObj
 * @param arg3 Dynamics descriptor pointer
 * @param fp Defending fighter data
 * @param hurt Hurtbox capsule that was struck
 */
/* 076764 */ void ftColl_80076764(int arg0, enum_t arg1, Fighter_GObj* arg2,
                                  DynamicsDesc* arg3, Fighter* fp,
                                  FighterHurtCapsule* hurt);

/**
 * @brief Records a hit victim for all hitboxes in the same hitbox group.
 * @details Prevents multiple hitboxes of the same attack from striking the same target twice.
 * @param fp Attacking fighter data
 * @param hit Hitbox capsule that connected
 * @param arg2 Victim classification index
 * @param victim Pointer to victim entity
 * @param arg4 Flag indicating whether to clear hitbox pending state
 */
/* 076808 */ void ftColl_80076808(Fighter* fp, HitCapsule* hit, int arg2,
                                  void* victim, bool arg4);

/**
 * @brief Copies hit victim history between hitboxes of the same attack group.
 * @param fp Attacking fighter data
 * @param dst Destination hitbox capsule to receive the copied history
 */
/* 0768A0 */ void ftColl_800768A0(Fighter* fp, HitCapsule* dst);

/**
 * @brief Tests and resolves hitbox-on-hitbox clanking (rebound) between two fighters.
 * @details If damage difference is strictly less than 9% (p_ftCommonData->x3CC), attacks clank:
 * calculates recoil frames (recoil = damage * mult + base) and spawns clank spark effect (1052).
 * @param fp0 Attacking fighter 0
 * @param hit0 Hitbox 0
 * @param fp1 Attacking fighter 1
 * @param hit1 Hitbox 1
 * @return True if clank occurred
 */
/* 07699C */ bool ftColl_8007699C(Fighter* fp0, HitCapsule* hit0, Fighter* fp1,
                                  HitCapsule* hit1);

/**
 * @brief Resolves attack hitbox striking an opponent's shield bubble.
 * @details Calculates shield damage taken, shield pushback on attacker (lightshield_amount * dmg),
 * powershield reflections (triggering SFX 104 and spark effect 27), and updates shield depletion.
 * @param fp0 Attacking fighter
 * @param hit0 Offensive hitbox capsule
 * @param fp1 Defending fighter with active shield
 */
/* 076CBC */ void ftColl_80076CBC(Fighter* fp0, HitCapsule* hit0, Fighter* fp1);

/**
 * @brief Tests hitbox against hurtbox, detecting phantom hits or full hits.
 * @details Phantom hit (glancing blow): if coll_distance < p_ftCommonData->x7A8 (0.01),
 * deals half damage (0.5 * dmg), applies zero knockback/hitstun, and logs a tip hit.
 * Full hit: applies damage and logs entry in dmg_log0 for highest-knockback resolution.
 * @param fp0 Attacking fighter
 * @param hit0 Offensive hitbox
 * @param fp1 Defending fighter
 * @param hit1 Hurtbox capsule struck
 * @return True if collision occurred (phantom or full)
 */
/* 076ED8 */ bool ftColl_80076ED8(Fighter* fp0, HitCapsule* hit0, Fighter* fp1,
                                  HitCapsule* hit1);

/**
 * @brief Resolves item/projectile collision with a fighter's reflector bubble.
 * @details If projectile damage exceeds maxDamage, breaks reflector; otherwise reflects projectile,
 * reversing velocity and multiplying speed (x1A38) and damage (x1A34).
 * @param item Item / projectile data
 * @param hit Item hitbox capsule
 * @param fp Reflecting fighter data
 */
/* 077464 */ void ftColl_80077464(Item* item, HitCapsule* hit, Fighter* fp);

/**
 * @brief Resolves item/projectile striking a fighter's shield bubble.
 * @details Applies shield damage and pushback; handles powershield reflection if timed perfectly.
 * @param item Incoming item data
 * @param hurt Item hitbox capsule
 * @param fp Defending fighter data
 * @param pos Contact position vector
 * @param val Shield angle / parameter
 */
/* 077688 */ void ftColl_80077688(Item* item, HitCapsule* hurt, Fighter* fp,
                                  Vec3* pos, f32 val);

/**
 * @brief Tests item/projectile hitbox clanking against a fighter's attack hitbox.
 * @details Evaluates 9% damage threshold (p_ftCommonData->x3CC) to clank projectile against attack.
 * @param item Item / projectile data
 * @param hit1 Item hitbox capsule
 * @param fp Attacking fighter data
 * @param hit2 Fighter attack hitbox capsule
 */
/* 077970 */ void ftColl_80077970(Item* item, HitCapsule* hit1, Fighter* fp,
                                  HitCapsule* hit2);

/**
 * @brief Resolves item/projectile hitbox striking a fighter's hurtbox.
 * @details Applies damage, computes knockback, and triggers item impact callbacks.
 * @param item Item / projectile data
 * @param hit Item hitbox capsule
 * @param fp Defending fighter data
 * @param hit2 Defending hurtbox capsule
 * @return True if item hit registered
 */
/* 077C60 */ bool ftColl_80077C60(Item* item, HitCapsule* hit, Fighter* fp,
                                  HitCapsule* hit2);

/**
 * @brief Updates hurtbox hit reaction and elemental effect.
 * @param fp Defending fighter data
 * @param arg1 Hurtbox capsule struck
 * @param arg2 Offensive hitbox that connected
 */
/* 078384 */ void ftColl_80078384(Fighter* fp, FighterHurtCapsule* arg1,
                                  HitCapsule* arg2);

/**
 * @brief Spawns visual hit effects and plays impact audio.
 * @param fp Defending fighter data
 */
/* 078488 */ void ftColl_80078488(Fighter* fp);

/**
 * @brief Records clank / rebound collision event between two hitboxes.
 * @param arg0 Attacking fighter data
 * @param arg1 First hitbox capsule
 * @param arg2 Second hitbox capsule
 */
/* 0784B4 */ void ftColl_800784B4(Fighter* arg0, HitCapsule* arg1,
                                  HitCapsule* arg2);

/**
 * @brief Spawns directional hit spark effect based on attack severity.
 * @param gobj Pointer to fighter GObj
 * @param pos World position vector of the impact
 * @param dmg Hit severity level
 * @param ignored Unused parameter
 * @param kb Calculated knockback magnitude
 */
/* 078538 */ void ftColl_80078538(Fighter_GObj* gobj, Vec3* pos, u32 dmg,
                                  float ignored, float kb);

/**
 * @brief Logs combat hit statistics to player match tracking data.
 * @param arg0 Attacking fighter GObj
 * @param gobj Defending fighter GObj
 */
/* 07861C */ void ftColl_8007861C(Fighter_GObj* arg0, Fighter_GObj* gobj, int,
                                  int, int, UNK_T, u16, UNK_T, int);

/**
 * @brief Releases grab / breaks hold between grabber and victim.
 * @param arg0 Grabber fighter GObj
 * @param arg1 Victim fighter GObj
 * @param arg2 Release type flag
 */
/* 078710 */ void ftColl_80078710(Fighter_GObj* arg0, Fighter_GObj* arg1,
                                  UNK_T arg2);

/**
 * @brief Binds a captured victim to the grabber entity upon successful grab.
 * @param arg0 Grabber fighter GObj
 * @param arg1 Victim fighter GObj
 * @param arg2 Unused flag
 */
/* 078754 */ void ftColl_80078754(Fighter_GObj* arg0, Fighter_GObj* arg1,
                                  bool arg2);

/**
 * @brief Links an item grab / pickup to the fighter entity.
 * @param arg0 Item GObj being grabbed
 * @param arg1 Fighter GObj picking up the item
 * @param arg2 Grab slot index
 */
/* 0787B4 */ void ftColl_800787B4(Item_GObj* arg0, Fighter_GObj* arg1, int arg2);

/**
 * @brief Deactivates and clears all active attack hitboxes for a fighter.
 * @param gobj Pointer to fighter GObj
 */
/* 0788D4 */ void ftColl_800788D4(Fighter_GObj* gobj);

/**
 * @brief Applies horizontal pushing separation between two overlapping grounded fighters.
 * @param arg0 First fighter GObj
 * @param arg1 Second fighter GObj
 * @param arg2 Pushback displacement distance
 */
/* 07891C */ void ftColl_8007891C(Fighter_GObj* arg0, Fighter_GObj* arg1,
                                  float arg2);

/**
 * @brief Applies horizontal separation between two overlapping HSD_GObjs.
 * @param arg0 First entity GObj
 * @param arg1 Second entity GObj
 * @param arg2 Displacement amount
 */
/* 078998 */ void ftColl_80078998(HSD_GObj* arg0, HSD_GObj* arg1, float arg2);

/**
 * @brief Tests grab hitboxes against all opposing fighters on the stage.
 * @details Called from procGrabColl (priority 12). Tests hitboxes with element HitElement_Catch
 * against opponent hurtboxes with is_grabbable set, selecting the closest valid victim.
 * @param this_gobj Attacking fighter GObj performing the grab
 */
/* 078A2C */ void ftColl_80078A2C(Fighter_GObj* this_gobj);

/**
 * @brief Tests offensive attack hitboxes against all opponents, shields, reflectors, and hurtboxes.
 * @details Called from procAttackColl (priority 13). Main combat collision dispatch loop in Melee.
 * @param this_gobj Attacking fighter GObj
 */
/* 078C70 */ void ftColl_80078C70(Fighter_GObj* this_gobj);

/**
 * @brief Tests item and projectile hitboxes against the fighter's hurtboxes, shields, and reflectors.
 * @param gobj Defending fighter GObj
 */
/* 07925C */ void ftColl_8007925C(Fighter_GObj* gobj);

/**
 * @brief Computes knockback magnitude from damage, weight, ratios, and constants.
 * @details Core Melee knockback formula:
 * Knockback = defense * attack * match_ratio * (0.01 * KBG * (scaling_terms) + BKB)
 * If hit has fixed/set knockback (hit->x28 != 0), set knockback replaces target damage.
 * @param fp Defending fighter data
 * @param hit Offensive hitbox capsule
 * @param unk_count Stale move scaling factor
 * @param arg3 Match damage ratio multiplier (gm_8016B248)
 * @param attack Attacker attack ratio multiplier (handicap)
 * @param defense Defender defense ratio multiplier (handicap)
 * @param weight Defender character weight
 * @return Calculated knockback velocity magnitude (capped at ftd->x108)
 */
/* 079AB0 */ float ftColl_80079AB0(Fighter* fp, HitCapsule* hit, u32 unk_count,
                                   float arg3, float attack, float defense,
                                   float weight);

/**
 * @brief Computes knockback for fighter-on-fighter combat hit.
 * @param fp Defending fighter data
 * @param attacker Attacking fighter data
 * @param hit Offensive hitbox capsule
 * @param unk_count Move staleness factor
 * @return Calculated knockback magnitude
 */
/* 079C70 */ float ftColl_80079C70(Fighter* fp, Fighter* attacker,
                                   HitCapsule* hit, int unk_count);

/**
 * @brief Computes unscaled raw knockback magnitude (attack=1, defense=1, ratio=1).
 * @param fp Defending fighter data
 * @param hit Offensive hitbox capsule
 * @param unk_count Staleness multiplier
 * @return Raw knockback magnitude
 */
/* 079EA8 */ float ftColl_80079EA8(Fighter* fp, HitCapsule* hit, u32 unk_count);

/**
 * @brief Updates bone-relative hitbox world positions from skeletal joint transforms.
 * @param gobj Pointer to fighter GObj
 */
/* 07AB48 */ void ftColl_8007AB48(Fighter_GObj* gobj);

/**
 * @brief Updates hitbox positions and performs capsule sweep interpolation between frames.
 * @param gobj Pointer to fighter GObj
 */
/* 07AB80 */ void ftColl_8007AB80(Fighter_GObj* gobj);

/**
 * @brief Scales hitbox base damage by character scale factor and stale-move reduction queue.
 * @param arg0 Hitbox capsule to update
 * @param damageAmount Base unscaled damage integer
 * @param arg2 Fighter GObj owning the hitbox
 */
/* 07ABD0 */ void ftColl_8007ABD0(HitCapsule* arg0, u32 damageAmount,
                                  Fighter_GObj* arg2);

/**
 * @brief Tests if knockback angle is a meteor smash or spike angle.
 * @details Returns true if kb_angle is not 361 (Sakurai angle) and lies within meteor range
 * (p_ftCommonData->unk_kb_angle_min to unk_kb_angle_max, typically 230 to 310 degrees).
 * @param kb_angle Knockback trajectory angle in degrees
 * @return True if meteor smash / spike angle
 */
/* 07AC68 */ bool ftColl_8007AC68(u32 kb_angle);

/**
 * @brief Sets hitbox knockback trajectory angle and flags meteor smash status.
 * @param arg0 Hitbox capsule
 * @param arg1 Angle in degrees (0-360, or 361 for Sakurai angle)
 * @param arg2 Fighter GObj owning the hitbox
 */
/* 07AC9C */ void ftColl_8007AC9C(HitCapsule* arg0, int arg1,
                                  Fighter_GObj* arg2);

/**
 * @brief Updates previous and current hitbox world position coordinates (x4C, x58).
 * @param fp Fighter data
 * @param arg1 Hitbox capsule
 */
/* 07AD18 */ void ftColl_8007AD18(Fighter* fp, HitCapsule* arg1);

/**
 * @brief Updates hurtbox capsule world positions from skeletal joint matrices.
 * @details Called from procCollPos (priority 9) to sync hurtboxes with current animation pose.
 * @param gobj Pointer to fighter GObj
 */
/* 07AE80 */ void ftColl_8007AE80(Fighter_GObj* gobj);

/**
 * @brief Toggles hurtbox active state.
 * @param gobj Pointer to fighter GObj
 */
/* 07AEE0 */ void ftColl_8007AEE0(Fighter_GObj* gobj);

/**
 * @brief Enables reflector bubble collision update.
 * @param gobj Pointer to fighter GObj
 */
/* 07AEF8 */ void ftColl_8007AEF8(Fighter_GObj* gobj);

/**
 * @brief Enables absorber bubble collision update (PSI Magnet, Oil Panic bucket).
 * @param gobj Pointer to fighter GObj
 */
/* 07AF10 */ void ftColl_8007AF10(Fighter_GObj* gobj);

/**
 * @brief Deactivates all hitboxes upon motion state transition.
 * @param gobj Pointer to fighter GObj
 */
/* 07AF28 */ void ftColl_8007AF28(Fighter_GObj* gobj);

/**
 * @brief Deactivates hitboxes without clearing persistent hitbox flags.
 * @param gobj Pointer to fighter GObj
 */
/* 07AF60 */ void ftColl_8007AF60(Fighter_GObj* gobj);

/**
 * @brief Deactivates a specific hitbox capsule by array index.
 * @param gobj Pointer to fighter GObj
 * @param hit_idx Hitbox array index (0-3)
 */
/* 07AFC8 */ void ftColl_8007AFC8(Fighter_GObj* gobj, int hit_idx);

/**
 * @brief Disables all attack hitboxes on a fighter.
 * @param gobj Pointer to fighter GObj
 */
/* 07AFF8 */ void ftColl_8007AFF8(Fighter_GObj* gobj);

/**
 * @brief Sets hitbox state flags across all active hitboxes.
 * @param gobj Pointer to fighter GObj
 * @param state Hitbox state flags
 */
/* 07B064 */ void ftColl_8007B064(Fighter_GObj* gobj, enum_t state);

/**
 * @brief Sets vulnerability state for all hurtboxes on a fighter.
 * @details States:
 * - HurtCapsule_Normal (0): Vulnerable to attacks
 * - HurtCapsule_Invincible (1): Takes no damage, attacks bounce/spark
 * - HurtCapsule_Intangible (2): Attacks pass completely through (phasing)
 * @param gobj Pointer to fighter GObj
 * @param state Desired HurtCapsuleState
 */
/* 07B0C0 */ void ftColl_8007B0C0(Fighter_GObj* gobj, HurtCapsuleState state);

/**
 * @brief Sets vulnerability state for a specific bone hurtbox.
 * @param gobj Pointer to fighter GObj
 * @param bone_id Bone index identifying the target hurtbox
 * @param state Desired HurtCapsuleState
 */
/* 07B128 */ void ftColl_8007B128(Fighter_GObj* gobj, int bone_id,
                                  HurtCapsuleState state);

/**
 * @brief Configures shield bubble collision description and callback.
 * @param gobj Pointer to fighter GObj
 * @param shield Pointer to shield descriptor parameters
 * @param cb Event callback when shield is struck
 */
/* 07B1B8 */ void ftColl_8007B1B8(Fighter_GObj* gobj, ShieldDesc* shield,
                                  HSD_GObjEvent cb);

/**
 * @brief Configures reflector bubble collision description and callback.
 * @param gobj Pointer to fighter GObj
 * @param reflect Pointer to reflector descriptor parameters
 * @param on_reflect Event callback triggered when reflection occurs
 */
/* 07B23C */ void ftColl_CreateReflectHit(Fighter_GObj* gobj,
                                          ReflectDesc* reflect,
                                          HSD_GObjEvent on_reflect);

/**
 * @brief Configures absorber bubble collision description (PSI Magnet, Bucket).
 * @param gobj Pointer to fighter GObj
 * @param absorb Pointer to absorber descriptor parameters
 */
/* 07B2C4 */ void ftColl_CreateAbsorbHit(Fighter_GObj* gobj,
                                         AbsorbDesc* absorb);

/**
 * @brief Allocates and initializes hurtbox capsule arrays from character data.
 * @param gobj Pointer to fighter GObj
 */
/* 07B320 */ void ftColl_8007B320(Fighter_GObj* gobj);

/**
 * @brief Reinitializes hurtbox skeletal joint and bone references.
 * @param gobj Pointer to fighter GObj
 */
/* 07B4E0 */ void ftColl_8007B4E0(Fighter_GObj* gobj);

/**
 * @brief Initializes a single hurtbox capsule structure from initialization descriptor.
 * @param fp Fighter instance data
 * @param hurt Destination FighterHurtCapsule structure
 * @param init Initialization descriptor from character data
 */
/* 07B5AC */ void ftColl_HurtboxInit(Fighter* fp, FighterHurtCapsule* hurt,
                                     ftHurtboxInit* init);

/**
 * @brief Updates hurtbox vulnerability state based on motion state bitflags.
 * @param gobj Pointer to fighter GObj
 * @param arg1 Motion state vulnerability flags
 */
/* 07B62C */ void ftColl_8007B62C(Fighter_GObj* gobj, enum_t arg1);

/**
 * @brief Resets all hurtbox vulnerability states to default (HurtCapsule_Normal).
 * @param gobj Pointer to fighter GObj
 */
/* 07B6A0 */ void ftColl_8007B6A0(Fighter_GObj* gobj);

/**
 * @brief Updates Environment Collision Box (ECB) position and terrain collision flags.
 * @param gobj Pointer to fighter GObj
 */
/* 07B6EC */ void ftColl_8007B6EC(Fighter_GObj* gobj);

/**
 * @brief Modifies hurtbox vulnerability state.
 * @param gobj Pointer to fighter GObj
 * @param arg1 State flag
 */
/* 07B760 */ void ftColl_8007B760(Fighter_GObj* gobj, int arg1);

/**
 * @brief Modifies hurtbox vulnerability state for a specific bone.
 * @param gobj Pointer to fighter GObj
 * @param arg1 Target bone ID
 */
/* 07B7A4 */ void ftColl_8007B7A4(Fighter_GObj* gobj, int arg1);

/**
 * @brief Sets collision hit status integer flag.
 * @param fp Fighter instance data
 * @param arg1 Hit status flag
 */
/* 07B7FC */ void ftColl_8007B7FC(Fighter* fp, int arg1);

/**
 * @brief Returns the fighter's current composite hit status.
 * @param gobj Pointer to fighter GObj
 * @return Hit status integer (0 = normal, 1 = invincible, 2 = intangible)
 */
/* 07B868 */ s32 ftColl_8007B868(Fighter_GObj* gobj);

/**
 * @brief Updates world position of a hitbox capsule.
 * @param hit Hitbox capsule to update
 * @param vec World offset vector
 */
/* 07B8A8 */ void ftColl_8007B8A8(HitCapsule* hit, Vec3* vec);

/**
 * @brief Sets the grabber fighter GObj on a grabbed victim.
 * @param fp Defending victim fighter data
 * @param grabber_gobj Attacking grabber fighter GObj
 */
/* 07B8CC */ void ftColl_8007B8CC(Fighter* fp, Fighter_GObj* grabber_gobj);

/**
 * @brief Frees and deallocates all collision resources attached to a fighter.
 * @param gobj Pointer to fighter GObj being destroyed
 */
/* 07B8E8 */ void ftColl_8007B8E8(Fighter_GObj* gobj);

/**
 * @brief Computes wind offset displacement vector acting on a fighter.
 * @param fgp Fighter GObj pointer
 * @param out_wind Vector to store resultant wind velocity
 */
/* 07B924 */ void ftColl_GetWindOffsetVec(Fighter_GObj* fgp, Vec3* out_wind);

/**
 * @brief Executes grab collision detection against opposing fighters.
 * @param gobj Pointer to fighter GObj performing the grab check
 */
/* 07BA0C */ void ftColl_8007BA0C(Fighter_GObj* gobj);

/**
 * @brief Tests active item and projectile hitboxes against the fighter.
 * @param gobj Pointer to defending fighter GObj
 */
/* 07BAC0 */ void ftColl_8007BAC0(Fighter_GObj* gobj);

/**
 * @brief Computes collision overlap and horizontal pushback force between two fighters.
 * @param gobj Pointer to fighter GObj
 * @return Calculated horizontal pushback force
 */
/* 07BBCC */ float ftColl_8007BBCC(Fighter_GObj* gobj);

/**
 * @brief Tests grab hitboxes against nearby grabbable items on the stage.
 * @param gobj Pointer to fighter GObj
 */
/* 07BC90 */ void ftColl_8007BC90(Fighter_GObj* gobj);

/**
 * @brief Tests fighter interaction range with nearby stage items.
 * @param gobj Pointer to fighter GObj
 */
/* 07BE3C */ void ftColl_8007BE3C(Fighter_GObj* gobj);

#endif
