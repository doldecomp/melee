/**
 * @file fighter.h
 * @brief Core fighter subsystem API and process loop declarations.
 * @details Declares the primary fighter lifecycle functions (creation, spawning, state
 * transitions, destruction), GObj per-frame process callback handlers (animation, input,
 * physics update, collisions, IK, dynamics, camera), memory allocators, and global modifier
 * tables (metal, bunny hood, character scaling, and CPU attack tables).
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_0679B0
#define GALE01_0679B0

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <placeholder.h>

#include <dolphin/mtx.h>
#include <melee/ft/inlines.h> // IWYU pragma: export
#include <melee/ft/types.h>
#include <sysdolphin/baselib/objalloc.h>

/**
 * @brief CPU AI attack evaluation tables loaded from PlCo.dat.
 * @details Contains pointers to per-character attack decision data used by the AI engine
 * (ftCo_800B3900 / ftCpuAttack) to evaluate move choice, range, and spacing.
 * Initialized in #Fighter_LoadCommonData.
 */
extern struct Fighter_804D64FC_t {
    u8** cmdscripts; ///< +00 Per-character AI script command arrays (evaluated during CPU think routine)
    void** x4;       ///< +04 Ground attack decision tables (jab, tilts, dash attack per character)
    void** x8;       ///< +08 Aerial attack decision tables (NAir, FAir, BAir, UAir, DAir per character)
    UNK_T* xC;       ///< +0C Ranged and projectile attack decision tables
    void** x10;      ///< +10 Smash attack decision tables (FSmash, USmash, DSmash per character)
    void** x14;      ///< +14 Special move action tables (Neutral-B, Side-B, Up-B, Down-B per character)
    void** x18;      ///< +18 Item/weapon attack decision tables (battering items, shooting items)
    void** x1C;      ///< +1C Edge guard and ledge recovery tables (off-stage tactic evaluation)
    float* x20;      ///< +20 Spacing and distance threshold lookup array per character
    float* x24;      ///< +24 Weapon and item reach extension bonus table
}* Fighter_804D64FC;

struct plAllocInfo;

/**
 * @brief Initializes memory pools and common subsystems for all fighters.
 * @details Configures HSD_ObjAlloc allocators for Fighter structs (sizeof(Fighter)),
 * attribute backup buffers, skeletal bone parts arrays, and DObj lists.
 * Calls #Fighter_LoadCommonData to unpack PlCo.dat and invokes per-character
 * initialization callbacks from ftData_Table_Unk1.
 */
/* 0679B0 */ void Fighter_800679B0(void);

/**
 * @brief Top-level initialization entry point for the fighter system.
 * @details Invokes #Fighter_800679B0 to set up fighter object pools and common data,
 * and initializes the 32 KB animation/scratch buffer pool (fighter_x59C_alloc_data).
 */
/* 067A84 */ void Fighter_FirstInitialize_80067A84(void);

/**
 * @brief Loads common fighter parameters from PlCo.dat.
 * @details Opens the PlCo.dat archive via lbArchive_LoadSymbols and extracts the
 * ftLoadCommonData root symbol. Distributes pointers to global modifier tables including
 * p_ftCommonData, item throw attributes, stale move queue values, bunny hood modifiers,
 * metal box modifiers, scale modifiers, shield bubble joints, and crowd reaction configs.
 */
/* 067ABC */ void Fighter_LoadCommonData(void);

/**
 * @brief Updates the 3D model scale of a fighter's root JObj.
 * @details Queries the character's base model scale via ftCommon_GetModelScale(fp)
 * and combines it with dynamic scaling factors (e.g. Poison/Super Mushroom or Flat Zone
 * Z-scale from fp->x34_scale), then applies the resulting scale vector to the root JObj.
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 067BB4 */ void Fighter_UpdateModelScale(Fighter_GObj* gobj);

/**
 * @brief Resets and reinitializes a fighter's match state for spawning/respawning.
 * @details Allocates a new spawn number via #Fighter_NewSpawn_80068E40, loads initial
 * coordinates and facing direction from player match data, syncs current/previous
 * positions, resets scale, and clears hitlag, combo, input, and damage state flags.
 * @param fp Pointer to the Fighter instance data
 */
/* 067C98 */ void Fighter_UnkInitReset_80067C98(Fighter* fp);

/**
 * @brief Spawns or respawns a fighter entity onto the stage.
 * @details Resets state via #Fighter_UnkInitReset_80067C98, positions root joint,
 * computes initial modified attributes (applying metal, bunny hood, and mushroom scale via
 * ftCo_800D105C), initializes ECB stage collision, attaches camera tracking box, enables
 * hurtbox capsules, sets up CPU AI parameters, and invokes character-specific OnDeath/spawn
 * callbacks.
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 068354 */ void Fighter_Spawn(Fighter_GObj* gobj);

/**
 * @brief Loads and binds the skeletal joint hierarchy for the fighter's active costume.
 * @details Retrieves costume joint data from CostumeListsForeachCharacter based on
 * fp->kind and fp->costume_id, initializes polygon objects (PObj) with default class,
 * creates the HSD_JObj hierarchy, and binds it to the fighter GObj.
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 0686E4 */ void Fighter_UnkUpdateCostumeJoint_800686E4(Fighter_GObj* gobj);

/**
 * @brief Computes height ratio and skeletal reference offsets between key bones.
 * @details Reads the translation of bone part 2 (transN/hip) to compute height ratio
 * (vec.y / 8.55f in fp->x1A6C), and calculates the 3D difference vector between
 * bone part 1 (TopN) and bone part 2 into fp->x1A70.
 * @param fp Pointer to the Fighter instance data
 */
/* 06876C */ void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fp);

/**
 * @brief Clears all controller input buffers and resets input timers.
 * @details Zeroes out analog control stick coordinates, C-stick coordinates, trigger
 * pressures, and button states (held, pressed, released). Sets all tap/smash detection
 * activity timers and duration counters to their default expiration value (254 / 255).
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 068854 */ void Fighter_ResetInputData_80068854(Fighter_GObj* gobj);

/**
 * @brief Initializes fighter instance properties from player allocation info.
 * @details Populates internal fighter fields including character kind, player slot index,
 * controller port, sub-fighter flag (e.g. Nana vs Popo), model scale, costume/sub-color,
 * and permanent metal status (Player_GetFlagsBit5).
 * @param gobj Pointer to the fighter's HSD_GObj
 * @param argdata Pointer to match allocation info (struct plAllocInfo)
 */
/* 068914 */ void Fighter_UnkInitLoad_80068914(Fighter_GObj* gobj,
                                               struct plAllocInfo* argdata);

/**
 * @brief Generates a new unique spawn identifier for a fighter instance.
 * @details Increments the global spawn counter (g_spawnNumCounter), wrapping to 1 if
 * it overflows to 0, and returns the previous counter value.
 * @return Unique 32-bit spawn number
 */
/* 068E40 */ u32 Fighter_NewSpawn_80068E40(void);

/**
 * @brief Sets stage-specific model depth scaling (Flat Zone 2D mode).
 * @details If the current stage is Flat Zone (Gr_Kind_Flatzone), flattens the fighter's
 * Z-axis scale using p_ftCommonData->x7E4_scaleZ; otherwise restores Z-scale to 1.0f.
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 068E64 */ void Fighter_80068E64(Fighter_GObj* gobj);

/**
 * @brief Allocates, constructs, and initializes a complete new Fighter entity.
 * @details High-level factory function:
 * 1. Creates HSD_GObj with class HSD_GOBJ_CLASS_FIGHTER (4) and p-link 8.
 * 2. Allocates Fighter struct and attribute backup from HSD_ObjAlloc pools.
 * 3. Loads character archives, model data, costume joints, and parts hierarchy.
 * 4. Attaches 15 GObj process callbacks in strict priority order:
 *    - Priority 0:  procHitlag   (freeze frame handling)
 *    - Priority 1:  procAnim     (animation update & frame timers)
 *    - Priority 2:  procCpu      (AI decision logic)
 *    - Priority 3:  procInput    (hardware / CPU input polling)
 *    - Priority 4:  procUpdate   (physics, knockback decay, positions)
 *    - Priority 6:  procMap      (stage collision ECB checks)
 *    - Priority 7:  procIK       (inverse kinematics / bone alignment)
 *    - Priority 8:  procAccessory(accessory / item callbacks 1-3)
 *    - Priority 9:  procCollPos  (bone matrices, accessory cb 4, hurtbox positions)
 *    - Priority 12: procGrabColl (grab detection & throw initiation)
 *    - Priority 13: procAttackColl (offensive hitboxes & clank/damage)
 *    - Priority 14: procCollResolve (hitstun, shield damage/break, knockback)
 *    - Priority 16: procDynamics (secondary bone cloth/hair physics)
 *    - Priority 18: procCamera   (viewport & camera tracking updates)
 *    - Priority 22: procPlayer   (sync coordinates to player data)
 * 5. Calls #Fighter_Spawn to place the fighter on stage in initial action state.
 * @param input Pointer to player allocation descriptor (struct plAllocInfo)
 * @return Pointer to newly created Fighter_GObj, or NULL on failure
 */
/* 068E98 */ Fighter_GObj* Fighter_Create(struct plAllocInfo* input);

/**
 * @brief Transitions a fighter to a new action state (Motion State).
 * @details THE central state machine function in Melee. Switches the fighter's active
 * motion state (Action State ID @p msid), rebinds action callbacks (animation, I/O,
 * physics, collision, accessory), sets animation playback flags, updates hurtbox status,
 * and clears or preserves hitboxes and state data based on MotionFlags bitmask:
 * - Ft_MF_KeepGfx: Preserves graphic effects across state transition
 * - Ft_MF_SkipHit: Preserves active hitboxes (does not clear hitboxes)
 * - Ft_MF_SkipModel: Retains current model parts display state
 * - Ft_MF_KeepFastFall: Preserves fast-falling status into new state
 * - Ft_MF_KeepColAnimHitStatus: Retains color animation hit status
 * - Ft_MF_SkipThrowException: Does not reset thrown hitbox owner
 *
 * @param gobj Pointer to fighter HSD_GObj
 * @param msid Target motion/action state ID (FtMotionId, e.g. ftCo_MS_Wait, ftCo_MS_Damage)
 * @param flags Bitmask of MotionFlags controlling preserved state attributes
 * @param anim_start Starting animation frame (typically 0.0f)
 * @param anim_speed Animation playback speed multiplier (1.0f = normal speed)
 * @param anim_blend Animation frame interpolation blend factor (typically 0.0f)
 * @param arg3 Optional partner/reference fighter GObj (used during throws/grabs)
 */
/* 0693AC */ void Fighter_ChangeMotionState(Fighter_GObj* gobj,
                                            FtMotionId msid, MotionFlags flags,
                                            f32 anim_start, f32 anim_speed,
                                            f32 anim_blend,
                                            Fighter_GObj* arg3);

/**
 * @brief GObj process callback running at priority 0: hitlag freeze frames.
 * @details Manages frame freeze during hits (both attacker and defender):
 * - Decrements damage hitlag timers (fp->dmg.x1954 and fp->dmg.x195c_hitlag_frames).
 * - Accepts Smash Directional Influence (SDI) inputs during hitlag frames.
 * - On timer expiration, invokes #Fighter_8006D10C to exit hitlag and clear SDI flags.
 * - Processes pending mushroom growth/shrink transitions (Super Mushroom / Poison Mushroom).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06A1BC */ void Fighter_procHitlag(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 1: animation update tick.
 * @details Advances the character's skeletal animation and frame timers:
 * - Updates position delta (pos_delta = cur_pos - prev_pos).
 * - Decrements combo/hit timer, invulnerability frames, and color animation timers.
 * - Ticks bone animations and executes character subaction animation script commands.
 * - Calls the current action state's animation callback (fp->anim_cb).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06A360 */ void Fighter_procAnim(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 2: CPU AI decision logic.
 * @details When the fighter is computer-controlled (ftCo_IsCpuControlled), invokes
 * the AI decision routine (ftCo_800B3900) to evaluate target distances, select moves,
 * and populate virtual controller stick and button inputs.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06ABA0 */ void Fighter_procCpu(Fighter_GObj* gobj);

/**
 * @brief Updates buffered input timers and tap detection counters.
 * @details Increments multi-frame input buffer timers (capped at 255):
 * - Jump input buffer timer (fp->x685, used for jump squat transitions)
 * - Smash input timer (fp->x686, detects stick smash within tap window)
 * - Attack/tilt input timer (fp->x687)
 * - Side special input buffer timer (fp->x688)
 * - Special move input buffer timer (fp->x689)
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06ABEC */ void Fighter_UnkIncrementCounters_8006ABEC(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 3: controller input processing.
 * @details Polls raw hardware controller data or simulated CPU inputs:
 * - Updates analog stick coordinates (lstick[0] and lstick[1] history).
 * - Updates C-stick (cstick[0]) coordinates.
 * - Updates analog trigger values (L/R triggers).
 * - Computes button transitions (pressed_buttons = newly pressed, released_buttons).
 * - Detects smash stick thresholds, tap jump inputs, and L-cancel triggers.
 * - Calls the current action state's input callback (fp->input_cb).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06AD10 */ void Fighter_procInput(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 4: main per-frame physics & state logic.
 * @details Executes core movement physics and timers:
 * - Decrements ledge regrab lockout timer (fp->x2064_ledgeCooldown).
 * - Decrements capture timer (fp->capture_timer).
 * - Invokes action state physics callback (fp->phys_cb) to compute self-induced velocities.
 * - Applies knockback velocity decay (air deaccel vs ground friction).
 * - Applies shield attack knockback decay.
 * - Integrates wind velocity offsets into current position.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06B82C */ void Fighter_procUpdate(Fighter_GObj* gobj);

/**
 * @brief Recomputes composite transformation matrix with custom scaling.
 * @details If custom Z-scale is active (fp->x34_scale.z != 1.0f, e.g. Flat Zone),
 * extracts joint scale, rotation, and translation, builds an SRT matrix, inverts the
 * joint matrix, and stores the concatenated result into fp->x44_mtx.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06C0F0 */ void Fighter_UnkApplyTransformation_8006C0F0(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 6: stage collision detection (ECB).
 * @details Performs environment collision checks using the Environmental Collision Box (ECB):
 * - Decrements ECB lock timer and unlocks ECB when expired.
 * - Sets joint root translation to current position.
 * - Executes action state map collision callback (fp->coll_cb).
 * - Resolves ground/air state transitions, ledge grabs, ceiling hits, and wall collisions.
 * - Validates coordinate sanity (asserting against NaN positions in debug builds).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06C27C */ void Fighter_procMap(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 7: inverse kinematics (IK).
 * @details Computes procedural skeletal adjustments (via ft_80089B08) to align feet
 * and legs with uneven or sloped terrain collision geometry.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06C5F4 */ void Fighter_procIK(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 8: accessory & item callbacks.
 * @details Executes character-specific accessory callbacks (fp->accessory1_cb,
 * fp->accessory2_cb, fp->accessory3_cb) to update attached items, weapons, or custom
 * bone attachments, then synchronizes root joint translation.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06C624 */ void Fighter_procAccessory(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 9: collision position preparation.
 * @details Prepares world-space bone coordinates for collision testing:
 * - Flushes pending asynchronous effects (efAsync_QueueFlush).
 * - Recomputes transformation matrix (#Fighter_UnkApplyTransformation_8006C0F0).
 * - Invokes accessory callback 4 (fp->accessory4_cb).
 * - Updates hurtbox world coordinates from bone transforms (ftColl_8007AE80).
 * - Ticks accessory animations and tracks magnifying glass off-screen camera limits.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06C80C */ void Fighter_procCollPos(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 12: grab detection and resolution.
 * @details Tests offensive grab hitboxes against opponents:
 * - Checks grab collisions against victim hurtboxes.
 * - On valid grab: plays grab SFX, links victim GObj (fp->victim_gobj), triggers
 *   grabber callback (fp->grab_cb) and victim grabbed callback (fp->grabbed_cb).
 * - Tests item grab collisions to pick up items within range (fp->target_item_gobj).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06CA5C */ void Fighter_procGrabColl(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 13: attack hitboxes and damage.
 * @details Processes offensive hitbox interactions across all entities:
 * - Tests active attack hitboxes against opponent hurtboxes, shields, and reflectors.
 * - Detects clashing attacks (hitbox vs hitbox priority / damage threshold).
 * - Calculates damage and base/scaling knockback.
 * - Triggers hitlag on both attacker and defender, camera shake, and hit SFX.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06CB94 */ void Fighter_procAttackColl(Fighter_GObj* gobj);

/**
 * @brief Applies damage to a fighter and records player combat statistics.
 * @details High-level wrapper that calls #Fighter_TakeDamage_8006CC7C to modify damage
 * percent, then calls ftCommon_8007EA90 to log damage taken in player match records.
 * @param fp Pointer to Fighter instance data
 * @param damage_amount Amount of damage in percent to add
 */
/* 06CC30 */ void Fighter_UnkTakeDamage_8006CC30(Fighter* fp,
                                                 float damage_amount);

/**
 * @brief Increases fighter damage percentage and updates HUD display.
 * @details Core damage application routine:
 * - Adds damage_amount to fp->dmg.x1830_percent.
 * - Decrements metal health if in metal state (fp->metal_health).
 * - Clamps damage percent to maximum 999.0%.
 * - Syncs updated percentage to Player data structure and HUD display.
 * @param fp Pointer to Fighter instance data
 * @param damage_amount Amount of damage in percent to add
 */
/* 06CC7C */ void Fighter_TakeDamage_8006CC7C(Fighter* fp, float damage_amount);

/**
 * @brief Checks if damage taken causes the fighter to drop items or headgear.
 * @details Compares a random roll against damage threshold (p_ftCommonData->x418):
 * - If check succeeds, forces the fighter to drop their currently held light item.
 * - If fighter is wearing a Bunny Hood (fp->x197C), drops the Bunny Hood item.
 * @param fp Pointer to Fighter instance data
 * @param arg1 Damage value threshold used for drop probability check
 */
/* 06CDA4 */ void Fighter_8006CDA4(Fighter* fp, s32 arg1);

/**
 * @brief Accumulates flinch damage and triggers damage reaction effects.
 * @details If fighter is alive (not stamina dead), adds arg1 to damage counter
 * fp->dmg.x18F0 and invokes ftCo_800BFFD0 / ftCommon_8007EBAC to trigger hit reactions.
 * @param fp Pointer to Fighter instance data
 * @param arg1 Flinch/damage intensity value to accumulate
 */
/* 06CF5C */ void Fighter_8006CF5C(Fighter* fp, s32 arg1);

/**
 * @brief Flags fighter for delayed hitlag exit.
 * @details If hitlag flag fp->x2219_b7 is active, sets fp->x221A_b1 = 1 to signal
 * hitlag termination on the subsequent frame.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06CFBC */ void Fighter_UnkSetFlag_8006CFBC(Fighter_GObj* gobj);

/**
 * @brief Checks conditions and terminates hitlag freeze state.
 * @details If hitlag flag fp->x2219_b7 is set, verifies that SDI is inactive and
 * hitlag frames (fp->dmg.x1954) have elapsed, then calls #Fighter_8006D10C to exit hitlag.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06CFE0 */ void Fighter_8006CFE0(Fighter_GObj* gobj);

/**
 * @brief Enters hitlag state and recursively propagates hitlag to linked fighters.
 * @details Invokes pre-hitlag callback (fp->pre_hitlag_cb), sets hitlag freeze flag
 * (fp->x2219_b5 = 1), and recursively sets hitlag on attached entities (such as grabbed
 * victims in fp->x1A5C).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06D044 */ void Fighter_UnkRecursiveFunc_8006D044(Fighter_GObj* gobj);

/**
 * @brief Exits hitlag state and unfreezes attached fighters.
 * @details Invokes post-hitlag callback (fp->post_hitlag_cb), clears hitlag freeze flag
 * (fp->x2219_b5 = 0), and recursively clears hitlag on linked fighters (fp->x1A5C).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06D10C */ void Fighter_8006D10C(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 14: collision response resolution.
 * @details Evaluates the gameplay outcome of collisions:
 * - Shield logic: regenerates shield HP when shield is inactive; applies shield damage,
 *   shield depletion, and shield break (launching fighter and playing shield break sound).
 * - Hitstun calculation: converts received knockback into hitstun frames
 *   (formula: Hitstun = knockback * 0.4 frames).
 * - Initiates hitstun action states (Damage, DamageFly, DamageFall) or knockdown tumble.
 * - Handles rebound/clank recoil transitions.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06D1EC */ void Fighter_procCollResolve(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 16: physical dynamics simulation.
 * @details Executes physical bone dynamics simulation (ftCo_8009E0A8) for secondary
 * skeletal components such as hair, capes, scarves, ties, and dangling clothing.
 * Skipped if the fighter is sleeping or frozen in hitlag.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06D9AC */ void Fighter_procDynamics(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 18: camera tracking update.
 * @details Updates stage camera bounds and viewport tracking targets (ftCommon_8008021C)
 * and executes fighter-specific camera callback (fp->cam_cb) to ensure all active fighters
 * remain properly framed on screen.
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06D9EC */ void Fighter_procCamera(Fighter_GObj* gobj);

/**
 * @brief GObj process callback running at priority 22: player state synchronization.
 * @details Final per-frame tick for player tracking:
 * - Syncs fighter world coordinates to player match data (Player_80032828).
 * - Synchronizes facing direction (Player_SetFacingDirectionConditional).
 * - Updates player movement tracking history (pl_8003FAA8).
 * @param gobj Pointer to fighter HSD_GObj
 */
/* 06DA4C */ void Fighter_procPlayer(Fighter_GObj* gobj);

/**
 * @brief Destructor callback for Fighter GObj destruction and memory deallocation.
 * @details Cleans up all resources associated with a fighter:
 * - Calls character-specific cleanup callback (ftData_OnUserDataRemove).
 * - Removes collision hitboxes, camera box, dynamic bones, shadow textures, and accessories.
 * - Unreferences and removes skeleton HSD_JObj hierarchy and lights (HSD_LObj).
 * - Returns allocated blocks to HSD_ObjAlloc memory pools (fighter_alloc_data,
 *   dat_attrs, parts, dobj_list, x2040, x59C).
 * @param user_data Pointer to the Fighter struct passed as GObj user data
 */
/* 06DABC */ void Fighter_Unload_8006DABC(void* user_data);

/* 458FD0 */ extern HSD_ObjAllocData fighter_alloc_data;           ///< Memory pool for Fighter instance structs (sizeof(Fighter))
/* 458FFC */ extern HSD_ObjAllocData fighter_dat_attrs_alloc_data; ///< Memory pool for dat_attrs_backup (0x424 bytes)
/* 459028 */ extern HSD_ObjAllocData fighter_parts_alloc_data;     ///< Memory pool for skeletal bone arrays (MAX_FT_PARTS * sizeof(FighterBone))
/* 459054 */ extern HSD_ObjAllocData fighter_dobj_list_alloc_data; ///< Memory pool for primary DObj pointer lists (0x1F0 / 4 * sizeof(HSD_DObj*))
/* 459080 */ extern HSD_ObjAllocData fighter_x2040_alloc_data;     ///< Memory pool for secondary DObj pointer lists (0x80 / 4 * sizeof(HSD_DObj*))
/* 4590AC */ extern HSD_ObjAllocData fighter_x59C_alloc_data;      ///< Memory pool for fighter 32 KB scratch/animation buffers (0x8000 bytes)

/* 4D6504 */ extern HSD_Joint* Fighter_804D6504; ///< Root joint model for the fighter shield bubble
/* 4D6508 */ extern u8* Fighter_804D6508;         ///< Secondary shield bubble RGBA color lookup table (by player/color index)
/* 4D650C */ extern u8* Fighter_804D650C;         ///< Primary shield bubble RGBA color lookup table (by player/color index)
/* 4D6510 */ extern UNK_T Fighter_804D6510;
/* 4D6514 */ extern HSD_Joint* Fighter_804D6514; ///< Trophy stand / spawn platform model joint when characters spawn

/**
 * @brief Physics modifiers for player flag AE bit 0 (heavy / altered physics mode).
 * @details Applied in ftCo_800D105C when fp->x2229_b1 is set (e.g., Stamina Mode or Special Melee).
 */
/* 4D6518 */ extern struct Fighter_804D6518_t {
    f32 x0; ///< Gravity multiplier (modifies fp->co_attrs.gravity)
    f32 x4; ///< Weight multiplier (modifies fp->co_attrs.weight)
}* Fighter_804D6518;

/**
 * @brief Attribute multipliers applied when a fighter is in the Metal state.
 * @details Applied in ftCo_800D105C and ftCo_Walk when fp->is_metal is true (e.g. Metal Box item).
 * Makes the fighter significantly heavier, fall faster, and jump shorter.
 */
/* 4D651C */ extern struct Fighter_804D651C_t {
    f32 x0;  ///< Walk acceleration multiplier (applied in ftCo_Walk)
    f32 x4;  ///< Full hop jump initial vertical velocity multiplier (drastically reduces jump height)
    f32 x8;  ///< Short hop jump initial vertical velocity multiplier
    f32 xC;  ///< Gravity multiplier (increases downward acceleration)
    f32 x10; ///< Terminal fall speed multiplier (increases maximum downward speed)
    f32 x14; ///< Fast fall terminal speed multiplier
    f32 x18; ///< Weight multiplier (significantly increases weight -> massive knockback resistance)
    f32 x1C; ///< Ledge jump initial vertical velocity multiplier
    f32 x20; ///< Wall jump initial vertical velocity multiplier
}* Fighter_804D651C; ///< Metal modifiers - used in ftCo_800D105C and ftCo_Walk

/**
 * @brief Attribute multipliers applied when a fighter equips the Bunny Hood item.
 * @details Applied in ftCo_800D105C, ftCo_Walk, and ftCo_800D0CBC when fp->x197C is non-NULL.
 * Grants massive boosts to run speed, jump height, and mobility.
 */
/* 4D6520 */ extern struct Fighter_804D6520_t {
    f32 x0;  ///< Walk acceleration multiplier (applied in ftCo_Walk)
    f32 x4;  ///< Dash acceleration multiplier A (fp->co_attrs.dash_accel_mul)
    f32 x8;  ///< Dash base acceleration multiplier B (fp->co_attrs.dash_accel_base)
    f32 xC;  ///< Dash maximum velocity multiplier (greatly increased run speed)
    f32 x10; ///< Jump initial horizontal velocity multiplier
    f32 x14; ///< Full hop jump initial vertical velocity multiplier (significantly higher jumps)
    f32 x18; ///< Short hop jump initial vertical velocity multiplier
    f32 x1C; ///< Jump maximum horizontal velocity multiplier (increased aerial drift)
    f32 x20; ///< Gravity multiplier (adjusted gravity to keep jumping responsive at high speed)
    f32 x24; ///< Terminal fall speed multiplier
    f32 x28; ///< Fast fall terminal speed multiplier
    f32 x2C; ///< Ledge jump initial horizontal velocity multiplier
    f32 x30; ///< Ledge jump initial vertical velocity multiplier
    f32 x34; ///< Wall jump initial horizontal velocity multiplier
    f32 x38; ///< Wall jump initial vertical velocity multiplier
}* Fighter_804D6520; ///< Bunny Hood modifiers - used in ftCo_800D105C, ftCo_Walk, ftCo_800D0CBC

/**
 * @brief Attribute scaling modifiers applied when a fighter scale is non-default.
 * @details Applied dynamically via ftCo_CalcYScaledKnockback when fp->x34_scale.y != 1.0f
 * (e.g. Super Mushroom growth, Poison Mushroom shrinkage, or custom size modes).
 * Formulas scale gameplay values relative to model scale factor (scale >= 1.0 vs scale < 1.0).
 */
/* 4D6524 */ extern struct Fighter_804D6524_t {
    float x0;  ///< Knockback received multiplier (larger fighters take less KB, smaller take more)
    float x4;  ///< Damage dealt multiplier (giant attacks deal boosted damage; tiny deal less)
    float x8;  ///< Heavy item pickup animation playback speed multiplier (ftCo_MS_HeavyGet)
    float xC;  ///< Walk acceleration multiplier (applied in ftCo_Walk and ftCo_HammerWalk)
    float x10; ///< Slow walk maximum speed threshold multiplier
    float x14; ///< Mid walk point speed threshold multiplier
    float x18; ///< Fast walk minimum speed threshold multiplier
    float x1C; ///< Dash maximum velocity multiplier
    float x20; ///< Run animation playback scaling factor
    float x24; ///< Jump squat (startup frames) duration multiplier
    float x28; ///< Full hop jump initial vertical velocity multiplier
    float x2C; ///< Short hop jump initial vertical velocity multiplier
    float x30; ///< Gravity multiplier
    float x34; ///< Terminal fall speed multiplier
    float x38; ///< Air drift stick input multiplier (aerial mobility control)
    float x3C; ///< Aerial drift base acceleration multiplier
    float x40; ///< Maximum air drift speed multiplier
    float x44; ///< Fast fall terminal speed multiplier
    float x48; ///< Fighter weight multiplier (affects knockback calculation)
    float x4C; ///< Shield break initial vertical launch velocity multiplier
    float x50; ///< Ledge jump initial horizontal velocity multiplier
    float x54; ///< Ledge jump initial vertical velocity multiplier
    float x58; ///< Light item throw velocity multiplier
    float x5C; ///< Heavy item throw velocity multiplier
    float x60; ///< Collision bubble size / hurtbox radius scaling multiplier
    float x64; ///< Primary item pickup / grab reach range multiplier
    float x68; ///< Secondary item pickup reach range multiplier
    float x6C; ///< Normal (empty) landing lag duration multiplier
    float x70; ///< Neutral aerial (NAir) landing lag duration multiplier
    float x74; ///< Forward aerial (FAir) landing lag duration multiplier
    float x78; ///< Back aerial (BAir) landing lag duration multiplier
    float x7C; ///< Up aerial (UAir) landing lag duration multiplier
    float x80; ///< Down aerial (DAir) landing lag duration multiplier
    float x84; ///< Player name tag / HUD overhead display height multiplier
    float x88; ///< Screw Attack initial vertical launch velocity multiplier
    float x8C; ///< Ice breakout (damage ice jump) initial vertical velocity multiplier
    float x90; ///< Ice breakout (damage ice jump) horizontal velocity multiplier
    float x94; ///< Primary camera subject tracking target offset multiplier
    float x98; ///< Secondary camera subject tracking target offset multiplier
}* Fighter_804D6524; ///< Fighter scale modifiers - used in ftchangeparam, ftcoll, ftpickupitem, ftCo_Walk, ftCo_Damage

/**
 * @brief Shake animation offset entry for screen/model rumble.
 */
/* 4D6528 */ extern struct Fighter_ShakeTable_t {
    Vec2* x0; ///< Array of 2D translation shake offsets (X, Y jitter)
    int x4;   ///< Number of frames / entries in shake table
}* Fighter_SmashChargeShakeTable; ///< Shake offset table applied while charging a smash attack

/// Grab-mash shake table: shake offsets applied when mashing out of grabs
/* 4D652C */ extern struct Fighter_ShakeTable_t* Fighter_GrabMashShake;

/* 4D6530 */ extern Vec2** Fighter_804D6530; ///< Tumble / damage fall trajectory wobble offset table arrays (used in ftCo_DamageFall)
/* 4D6534 */ extern UNK_T Fighter_804D6534;   ///< Accessory attachment joint/data definitions (used in ft_0D4D)
/* 4D6538 */ extern struct Fighter_804D653C_t* Fighter_804D6538; ///< Secondary color overlay / flash animation table
/* 4D653C */ extern struct Fighter_804D653C_t* Fighter_804D653C; ///< Primary color overlay / flash animation table (used by lb_800144C8)

/**
 * @brief Per-character model part / bone index mapping for attached accessories and Kirby hats.
 */
typedef struct Fighter_804D6540_x0_t {
    u8 x0; ///< Bone/part index to hide or modify
    u8 x1; ///< Alternate joint/part state flag
    u8 x2; ///< Visibility state mask
    u8 x3; ///< Part configuration flag
} Fighter_804D6540_x0_t;

/**
 * @brief Item throw motion parameters loaded from PlCo.dat.
 * @details One entry per item throw motion state (forward, back, up, down, air throws).
 */
typedef struct ftCo_ItemThrowAttrs {
    float velocity_mul; ///< Launch velocity multiplier applied to the thrown item
    float angle;        ///< Launch trajectory angle in radians
    float x8;           ///< Additional throw parameter (damage or spin rate multiplier)
} ftCo_ItemThrowAttrs;

/**
 * @brief Container descriptor for per-character part visibility override tables.
 */
typedef struct Fighter_804D6540_t {
    Fighter_804D6540_x0_t* x0; ///< Array of part override entries for this character
    int x4;                    ///< Number of entries in override array
} Fighter_804D6540_t;

extern Fighter_804D6540_t** Fighter_804D6540; ///< Per-character part override table array (indexed by FtKind)
/* 4D6544 */ extern FighterPartsTable** ftPartsTable; ///< Per-character skeletal bone-to-part lookup tables

/**
 * @brief 9-slot stale move damage reduction penalty values.
 * @details Melee tracks the last 9 moves that connected in a queue. Each occurrence of a move
 * in the queue subtracts Fighter_804D6548[i] from the damage multiplier (1.0 - sum(stale_penalties)).
 */
/* 4D6548 */ extern float* Fighter_804D6548;

/**
 * @brief Battering and swing item attack animation playback speed table.
 * @details 2D array indexed by [swing_type][attack_sub_type] (e.g. Home Run Bat, Beam Sword,
 * Fan, Star Rod x neutral swing, tilt, smash, dash attack).
 */
/* 4D654C */ extern float (*Fighter_804D654C)[5];

/* 4D6550 */ extern ftCo_ItemThrowAttrs* Fighter_804D6550; ///< Array of item throw parameter structs indexed by throw motion state
/* 4D6554 */ extern ftCommonData* p_ftCommonData;          ///< Global pointer to the core common fighter constants table from PlCo.dat

#endif
