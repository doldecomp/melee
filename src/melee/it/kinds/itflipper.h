#ifndef GALE01_290938
#define GALE01_290938
/**
 * @file
 * @brief Flipper item (@c It_Kind_Flipper) -- the pinball paddle.
 *
 * @note These names were determined by Claude (an AI), not recovered from an
 * original author; treat them as tentative until confirmed by a human. Each
 * symbol keeps an @c \@alias tag recording the machine-generated name it
 * replaced (revertible with @c melee-replace-symbols), and the superscript
 * markers in the briefs are footnotes into @ref itflipper_naming, where the
 * supporting debugger experiment for each name is recorded.
 */

#include <Runtime/platform.h>

#include <melee/it/forward.h>

#include <melee/it/kinds/types.h>

/**
 * Motion-state ids written to the item's motion state through
 * @c Item_80268E5C; each value equals the @c UnkMotionN callback index it was
 * named from. The id-to-meaning map -- 0 resting, 1 falling, 2 held,
 * 3 in-flight, 4 airborne, 5 active, 6 spinning -- was recovered by
 * watch-pointing the motion state across a full lifecycle.<sup>[\ref fp_f1
 * "F1"]</sup>
 */
typedef enum itFlipper_MotionState {
    FLIPPER_MS_RESTING,
    FLIPPER_MS_FALLING,
    FLIPPER_MS_HELD,
    FLIPPER_MS_INFLIGHT,
    FLIPPER_MS_AIRBORNE,
    FLIPPER_MS_ACTIVE,
    FLIPPER_MS_SPINNING,
} itFlipper_MotionState;

/**
 * Spawns a flipper pinned to a stage joint @p jobj (Break-the-Targets
 * obstacles): stores it in @c xDEC_stageAnchor, sets @c xDE8_isStageFixed,
 * and settles it.<sup>[\ref fp_e6 "E6"]</sup>
 * @alias{it_80290938}
 */
/* 290938 */ HSD_GObj* itFlipper_Spawn(HSD_JObj*);
/**
 * Logic-20 spawn callback: zero-initializes the itemVars and enters the
 * falling state.
 * @alias{itFlipper_Logic20_Spawned}
 */
/* 290A20 */ void itFlipper_Spawned(Item_GObj*);
/**
 * Advances the paddle spin one frame: decays @c xDE4_spinVel toward 0, adds
 * it into @c xDE0_spinAngle, and applies that as an X rotation.<sup>[\ref
 * fp_e3 "E3"]</sup>
 * @alias{it_80290A7C}
 */
/* 290A7C */ void itFlipper_UpdateSpin(Item_GObj*);
/**
 * Adds a spin impulse directed by the contact point @p pos, clamped to
 * +/- @c x24_maxSpinVel.<sup>[\ref fp_e3 "E3"], [\ref fp_e4 "E4"]</sup>
 * @alias{it_80290C38}
 */
/* 290C38 */ void itFlipper_AddSpinImpulse(Item_GObj*, Vec3*, f32);
/**
 * Derives the spin impulse from the striking fighter's speed and applies it
 * via itFlipper_AddSpinImpulse(), reading the fighter from
 * @c xCF4_fighterGObjUnk (the dealt-damage side).<sup>[\ref fp_e4 "E4"]</sup>
 * @alias{it_80290CE8}
 */
/* 290CE8 */ void itFlipper_SpinFromFighter(Item_GObj*);
/**
 * Pushes the flipper away from @p pos with a fixed 0.2 impulse, only when
 * @p kind is @c It_Kind_Flipper (0x14).<sup>[\ref fp_f2 "F2"]</sup>
 * @alias{it_80290DD4}
 */
/* 290DD4 */ void itFlipper_Repel(Item_GObj* gobj, s32 kind, Vec3* pos);
/**
 * Resets the flipper's velocity and enters the resting state (motion state
 * 0).<sup>[\ref fp_f1 "F1"]</sup>
 * @alias{it_80290E78}
 */
/* 290E78 */ void itFlipper_EnterResting(Item_GObj*);
/**
 * Animate callback for the resting state (motion state 0).
 * @alias{itFlipper_UnkMotion0_Anim}
 */
/* 290EC8 */ bool itFlipper_Resting_Anim(Item_GObj* gobj);
/**
 * Physics callback for the resting state (motion state 0).
 * @alias{itFlipper_UnkMotion0_Phys}
 */
/* 290ED0 */ void itFlipper_Resting_Phys(Item_GObj* gobj);
/**
 * Collision callback for the resting state (motion state 0): falls again if
 * the ground vanishes.
 * @alias{itFlipper_UnkMotion0_Coll}
 */
/* 290ED4 */ bool itFlipper_Resting_Coll(Item_GObj* gobj);
/**
 * Enters the falling state (motion state 1).<sup>[\ref fp_f1 "F1"]</sup>
 * @alias{it_80290F00}
 */
/* 290F00 */ void itFlipper_EnterFalling(Item_GObj* gobj);
/**
 * Animate callback for the falling state (motion state 1).
 * @alias{itFlipper_UnkMotion1_Anim}
 */
/* 290F28 */ bool itFlipper_Falling_Anim(Item_GObj* gobj);
/**
 * Physics callback for the falling state (motion state 1): applies gravity
 * toward terminal speed.
 * @alias{itFlipper_UnkMotion1_Phys}
 */
/* 290F30 */ void itFlipper_Falling_Phys(Item_GObj* gobj);
/**
 * Collision callback for the falling state (motion state 1): rests on
 * landing.
 * @alias{itFlipper_UnkMotion1_Coll}
 */
/* 290F60 */ bool itFlipper_Falling_Coll(Item_GObj* gobj);
/**
 * Logic-20 pickup callback: enters the held state (motion state
 * 2).<sup>[\ref fp_f1 "F1"]</sup>
 * @alias{itFlipper_Logic20_PickedUp}
 */
/* 290F8C */ void itFlipper_PickedUp(Item_GObj*);
/**
 * Animate callback for the held state (motion state 2).
 * @alias{itFlipper_UnkMotion2_Anim}
 */
/* 290FB4 */ bool itFlipper_Held_Anim(Item_GObj* gobj);
/**
 * Physics callback for the held state (motion state 2).
 * @alias{itFlipper_UnkMotion2_Phys}
 */
/* 290FBC */ void itFlipper_Held_Phys(Item_GObj* gobj);
/**
 * Logic-20 drop callback: forwards to itFlipper_Thrown() -- a drop is handled
 * as a throw.
 * @alias{itFlipper_Logic20_Dropped}
 */
/* 290FC0 */ void itFlipper_Dropped(Item_GObj*);
/**
 * Logic-20 throw callback: loads @c xDD4_flightTimer from @c
 * x4_smashThrowDuration (smash) or @c x0_throwDuration (normal) and enters
 * the in-flight state.<sup>[\ref fp_e1 "E1"], [\ref fp_e2 "E2"]</sup>
 * @alias{itFlipper_Logic20_Thrown}
 */
/* 290FE0 */ void itFlipper_Thrown(Item_GObj*);
/**
 * Animate callback for the in-flight state (motion state 3): decrements
 * @c xDD4_flightTimer and settles the flipper at 0.<sup>[\ref fp_e2
 * "E2"]</sup>
 * @alias{itFlipper_UnkMotion3_Anim}
 */
/* 291068 */ bool itFlipper_Inflight_Anim(Item_GObj* gobj);
/**
 * Physics callback for the in-flight state (motion state 3): gravity plus
 * end-of-flight velocity damping.
 * @alias{itFlipper_UnkMotion3_Phys}
 */
/* 2910A8 */ void itFlipper_Inflight_Phys(Item_GObj* gobj);
/**
 * Collision callback for the in-flight state (motion state 3): bounces off
 * walls/ceiling by @c xC_wallBounce and the floor by
 * @c x10_floorBounce.<sup>[\ref fp_e5 "E5"]</sup>
 * @alias{itFlipper_UnkMotion3_Coll}
 */
/* 291188 */ bool itFlipper_Inflight_Coll(Item_GObj* gobj);
/**
 * Settles a thrown flipper into a stationary hazard: stops it, sets
 * @c xDD8_isSettled, loads @c xD44_lifeTimer from @c x8_lifetime, and enters
 * the active state.<sup>[\ref fp_e2 "E2"]</sup>
 * @alias{it_80291254}
 */
/* 291254 */ void itFlipper_Settle(Item_GObj*);
/**
 * Enters the active (settled, hitbox-armed) state (motion state
 * 5).<sup>[\ref fp_f1 "F1"]</sup>
 * @alias{it_8029131C}
 */
/* 29131C */ void itFlipper_EnterActive(Item_GObj* gobj);
/**
 * Per-frame update for the active flipper: advances the spin, damps leftover
 * velocity, ticks @c xDDC_hitboxTimer, and expires the item by lifetime
 * unless stage-fixed.<sup>[\ref fp_e3 "E3"], [\ref fp_e6 "E6"]</sup>
 * @alias{it_80291344}
 */
/* 291344 */ bool itFlipper_UpdateActive(Item_GObj* gobj);
/**
 * Animate callback for the active state (motion state 5): switches to
 * spinning while @c xDE4_spinVel is nonzero.
 * @alias{itFlipper_UnkMotion5_Anim}
 */
/* 2914C8 */ bool itFlipper_Active_Anim(Item_GObj* gobj);
/**
 * Animate callback for the spinning state (motion state 6): returns to active
 * once @c xDE4_spinVel reaches 0.
 * @alias{itFlipper_UnkMotion6_Anim}
 */
/* 29151C */ bool itFlipper_Spinning_Anim(Item_GObj* gobj);
/**
 * Physics callback for the spinning state (motion state 6): re-pins a
 * stage-fixed flipper to @c xDEC_stageAnchor each frame.<sup>[\ref fp_e6
 * "E6"]</sup>
 * @alias{itFlipper_UnkMotion6_Phys}
 */
/* 291570 */ void itFlipper_Spinning_Phys(Item_GObj* gobj);
/**
 * Collision callback for the spinning state (motion state 6).
 * @alias{itFlipper_UnkMotion6_Coll}
 */
/* 2915B4 */ bool itFlipper_Spinning_Coll(Item_GObj* gobj);
/**
 * Logic-20 "dealt damage" callback: bounces while airborne, or (once settled)
 * arms @c xDDC_hitboxTimer and kicks spin from the fighter via
 * @c xCF4_fighterGObjUnk.<sup>[\ref fp_e1 "E1"], [\ref fp_e3 "E3"], [\ref
 * fp_e4 "E4"]</sup>
 * @alias{it_3F14_Logic20_DmgDealt}
 */
/* 2915E8 */ bool itFlipper_DmgDealt(Item_GObj*);
/**
 * Logic-20 clank callback: same handling as itFlipper_DmgDealt().
 * @alias{it_3F14_Logic20_Clanked}
 */
/* 2917C8 */ bool itFlipper_Clanked(Item_GObj*);
/**
 * Logic-20 shield-hit callback: same handling as itFlipper_DmgDealt().
 * @alias{it_3F14_Logic20_HitShield}
 */
/* 2918A0 */ bool itFlipper_HitShield(Item_GObj*);
/**
 * Logic-20 reflected callback.
 * @alias{itFlipper_Logic20_Reflected}
 */
/* 291978 */ bool itFlipper_Reflected(Item_GObj*);
/**
 * Logic-20 shield-bounce callback.
 * @alias{itFlipper_Logic20_ShieldBounced}
 */
/* 291998 */ bool itFlipper_ShieldBounced(Item_GObj*);
/**
 * Logic-20 "received damage" callback: when settled, arms @c xDDC_hitboxTimer
 * and kicks spin from the attacking fighter via @c xCEC_fighterGObj (mirrors
 * itFlipper_DmgDealt()'s @c xCF4).<sup>[\ref fp_e1 "E1"]</sup>
 * @alias{it_3F14_Logic20_DmgReceived}
 */
/* 2919B8 */ bool itFlipper_DmgReceived(Item_GObj*);
/**
 * Logic-20 entered-air callback: enters the airborne state (motion state 4).
 * @alias{itFlipper_Logic20_EnteredAir}
 */
/* 291B58 */ void itFlipper_EnteredAir(Item_GObj*);
/**
 * Animate callback for the airborne state (motion state 4).
 * @alias{itFlipper_UnkMotion4_Anim}
 */
/* 291B80 */ bool itFlipper_Airborne_Anim(Item_GObj* gobj);
/**
 * Physics callback for the airborne state (motion state 4).
 * @alias{itFlipper_UnkMotion4_Phys}
 */
/* 291B88 */ void itFlipper_Airborne_Phys(Item_GObj* gobj);
/**
 * Collision callback for the airborne state (motion state 4): rests or falls
 * on contact.
 * @alias{itFlipper_UnkMotion4_Coll}
 */
/* 291B8C */ bool itFlipper_Airborne_Coll(Item_GObj* gobj);
/**
 * Logic-20 event callback (purpose not yet identified).
 * @alias{itFlipper_Logic20_EvtUnk}
 */
/* 291BC0 */ void itFlipper_EvtUnk(Item_GObj*, Item_GObj*);
/**
 * The flipper's motion-state table: the per-state {animate, physics,
 * collision} callbacks indexed by #itFlipper_MotionState.
 * @alias{it_803F5EA8}
 */
/* 3F5EA8 */ extern ItemStateTable ItemStateTable_Flipper[];

#endif
