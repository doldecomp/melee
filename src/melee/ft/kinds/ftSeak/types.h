/**
 * @file types.h
 * @brief Type definitions and character structures for Sheik (ftSeak).
 * @details Defines Sheik's fighter variables (`ftSeak_FighterVars`), motion
 * variables
 * (`ftSeak_MotionVars`), special move attributes (`ftSeakAttributes`), and
 * chain segment parameters (`itChainSegment`).
 * Module prefix: ftSk (Fighter: Sheik)
 */

#ifndef MELEE_FT_CHARA_FTSEAK_TYPES_H
#define MELEE_FT_CHARA_FTSEAK_TYPES_H

#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/**
 * @brief Sheik's persistent character variables (stored at fp->u.sk).
 */
struct ftSeak_FighterVars {
    /* fp+222C */ int x0; ///< Number of stored needles charged (0 to 6)
    /* fp+2230 */ Item_GObj*
        x4; ///< Pointer to held needle item entity (`It_Kind_Seak_NeedleHeld`)
    /* fp+2234 */ HSD_GObj*
        x8; ///< Pointer to active chain item entity (`It_Kind_Seak_Chain`)
    /* fp+2238 */ Vec3
        xC[4]; ///< Current positions of the 4 chain segment hitboxes
    /* fp+2268 */ Vec3 x3C[4]; ///< Previous positions of the 4 chain segment
                               ///< hitboxes (displacement tracking)
    /* fp+2298 */ Vec3 lstick_delta; ///< Analog stick movement delta (used for
                                     ///< chain flick/snap detection)
};

/**
 * @brief Sheik's special move attributes loaded from PlSk.dat (fp->dat_attrs).
 */
typedef struct _ftSeakAttributes { // x2D4 (fp->dat_attrs)
    float x0;  ///< Neutral-B: Grounded needle spawn X offset
    float x4;  ///< Neutral-B: Grounded needle spawn Y offset
    float x8;  ///< Neutral-B: Aerial needle spawn X offset
    float xC;  ///< Neutral-B: Aerial needle spawn Y offset
    float x10; ///< Neutral-B: Aerial cancel landing lag / fall special flag
    float x14; ///< Side-B: Chain active loop minimum duration before B-release
               ///< allows retract
    float x18; ///< Side-B: Active hitbox duration when chain movement
               ///< threshold is reached
    float x1C; ///< Side-B: Startup frame when chain item entity spawns
    float x20; ///< Side-B: Startup duration before entering active whip loop
    float x24; ///< Side-B: Retraction frame when chain link retract begins
    float x28; ///< Side-B: Retraction frame when chain item is destroyed
    float self_vel_y; ///< Up-B: Initial aerial vertical boost/velocity
    f32 x30;          ///< Up-B: Fall gravity during startup phase
    f32 x34;          ///< Up-B: Terminal velocity during startup phase
    int x38;          ///< Up-B: Vanish invisible travel duration (frames
                      ///< intangible/invisible)
    f32 x3C; ///< Up-B: Ledge grab enable frame threshold during travel
    f32 x40; ///< Up-B: Control stick deadzone magnitude threshold for steering
    f32 x44; ///< Up-B: Control stick steering velocity scaling factor
    f32 x48; ///< Up-B: Base steering velocity offset
    f32 x4C; ///< Up-B: Aerial drift clamp multiplier after reappearance
    int x50; ///< Up-B: Teleport collision flags / surface snap parameters
    f32 x54; ///< Up-B: Reappearance residual velocity retention multiplier
    f32 x58; ///< Up-B: Freefall landing lag (frames)
    f32 x5C; ///< Up-B: FallSpecial landing lag parameter
    f32 x60; ///< Down-B: Horizontal velocity divisor on Transform start
    f32 x64; ///< Down-B: Vertical velocity divisor on Transform start
    f32 x68; ///< Down-B: Aerial gravity fall rate during transform
    f32 x6C; ///< Down-B: Aerial terminal velocity during transform
    f32 x70; ///< Down-B: Reappearance animation start frame when transforming
             ///< back
    // u8 data_filler_1[0x04];
} ftSeakAttributes;

/**
 * @brief Chain physical properties (stored in chain article special
 * attributes).
 */
struct itChainSegment {
    float x00;
    float x04;
    float x08;
    float x0C;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48; ///< Stick deflection deadzone threshold for chain damping
    float x4C; ///< Segment displacement speed threshold to activate hitboxes
    float x50; ///< Initial horizontal launch impulse on chain extend
};

/**
 * @brief Sheik's motion-specific variables union (stored in fp->mv.sk).
 */
union ftSeak_MotionVars {
    struct ftSeak_SpecialNVars {
        enum_t x0; ///< Frame counter during throw / firing sequence
        bool x4; ///< Flag indicating needle projectile should be fired on this
                 ///< frame
        s32 x8;  ///< Charge animation / SFX interval counter
        s32 xC;
        s32 x10;
        s32 x14;
        s32 x18;
        s32 x1C;
        s32 x20;
        s32 x24;
        s32 x28;
        s32 x2C;
    } specialn;

    struct ftSeak_SpecialSVars {
        s32 x0; ///< Startup / action frame timer
        s32 x4; ///< Flag set when B button is released (signals transition to
                ///< retract)
        s32 x8; ///< Cooldown timer for forward whip-crack sound effect
        s32 xC; ///< Cooldown timer for backward whip-crack sound effect
        float x10;
        float
            x14; ///< Filtered control stick magnitude (whip extension amount)
        float x18; ///< Filtered control stick angle in degrees (whip angle)
        s32 x1C;   ///< Active hitbox countdown timer (frames remaining with
                   ///< active hitboxes)
        s32 x20;   ///< Hitlag / pause state timer
        s32 x24;
        s32 x28;
        s32 x2C;
    } specials;

    struct ftSeakSpecialHi {
        s32 x0;   ///< Invisible travel countdown timer (frames remaining)
        Vec2 vel; ///< Teleport steering direction vector (from analog stick)
        s32 xC; ///< Travel duration elapsed frame counter (used for ledge grab
                ///< check)
        s32 x10;
        s32 x14;
        s32 x18;
        s32 x1C;
        s32 x20;
        s32 x24;
        s32 x28;
        s32 x2C;
    } specialhi;
};

#endif
