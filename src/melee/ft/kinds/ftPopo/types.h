#ifndef MELEE_FT_CHARA_FTPOPO_TYPES_H
#define MELEE_FT_CHARA_FTPOPO_TYPES_H

/**
 * @file types.h
 * @brief Character struct definitions and motion variables for Ice Climbers
 * (Popo)
 * @details Contains per-fighter instance variables, DAT attribute table
 * definitions, and union of move-specific motion variables for Ice Climbers.
 * Module prefix: ftPp
 */

#include <Runtime/platform.h>

#include <melee/it/forward.h>

/**
 * @brief Per-fighter instance variables for Popo/Nana
 * @details Located at fp->u.popo / fp->u.nn (offset 0x222C in Fighter struct)
 */
struct ftPopo_FighterVars {
    /* 0x222C */ Item_GObj*
        x222C; ///< Pointer to spawned Ice Shot ice block item
    /* 0x2230:0 */ u8 x2230_b0 : 1; ///< Blizzard active particle effect flag
    /* 0x2231 */ u8 filler_x2231[3];
    /* 0x2234 */ u32 x2234;        ///< Death / despawn state timer
    /* 0x2238 */ Item_GObj* x2238; ///< Pointer to Belay rope string item
    /* 0x223C */ u32 x223C;        ///< Belay auxiliary timer
    /* 0x2240 */ Vec x2240;   ///< Belay Nana partner anchor joint position
    /* 0x224C */ u32 x224C;   ///< Aerial Ice Shot stall-used flag (limits 1
                              ///< stall per airtime)
    /* 0x2250 */ float x2250; ///< Aerial Ice Shot vertical spawn offset
};

/**
 * @brief Ice Climbers special move attributes from character DAT file
 * (PlPp.dat)
 * @details Contains frame data, physics constants, impulse values, and
 * thresholds for Neutral-B, Side-B, Up-B, and Down-B moves. Total size: 0x15C
 * bytes.
 */
typedef struct ftIceClimberAttributes {
    // --- SpecialN: Ice Shot attributes ---
    float x0;  ///< Initial parameter
    float x4;  ///< Aerial Ice Shot initial vertical hop velocity
    float x8;  ///< Ice Shot landing lag duration (frames)
    float xC;  ///< Ice Shot projectile X spawn forward offset
    float x10; ///< Ice Shot projectile Y spawn height offset
    float x14;
    float x18;
    int x1C;

    // --- SpecialS: Squall Hammer attributes ---
    float x20;         ///< Aerial Squall solo initial vertical velocity
    float x24;         ///< Aerial Squall paired initial vertical velocity
    float x28;         ///< Grounded Squall forward speed
    float x2C;         ///< Aerial Squall forward speed
    float x30;         ///< Grounded Squall steering acceleration multiplier
    float x34;         ///< Aerial Squall steering acceleration multiplier
    float x38;         ///< Grounded Squall max horizontal speed
    float x3C;         ///< Aerial Squall max horizontal speed
    float x40;         ///< Squall analog stick X steering deadzone threshold
    float x44;         ///< Squall wall bounce rebound elasticity retention
    float x48;         ///< Squall minimum wall bounce velocity threshold
    float x4C_gravity; ///< Squall solo gravity
    float x50_gravity; ///< Squall paired gravity
    float x54_terminal_vel; ///< Squall solo terminal velocity
    float x58_terminal_vel; ///< Squall paired terminal velocity
    float x5C;              ///< Squall custom gravity duration window (frames)
    float x60;              ///< Squall solo B-press vertical rise boost
    float x64;              ///< Squall paired B-press vertical rise boost
    int x68;                ///< Squall button mash interval limit (frames)
    float x6C;              ///< Squall slope normal acceleration factor
    float x70; ///< Squall aerial end state transition parameter (0.0 = fall)

    // --- SpecialHi: Belay attributes ---
    float x74; ///< Belay special fall horizontal mobility factor
    float x78; ///< Belay landing lag duration (frames)
    float x7C; ///< Belay Nana partner search radius threshold
    float x80; ///< Belay analog stick turnaround deadzone threshold
    float x84; ///< Belay start horizontal momentum divisor (slowdown)
    float x88; ///< Belay start vertical momentum divisor (slowdown)
    float x8C; ///< Belay start gravity
    float x90; ///< Belay start terminal fall velocity
    float x94; ///< Belay partner pull trajectory base impulse
    float x98; ///< Belay partner distance scale divisor
    float x9C; ///< Belay Popo rising gravity
    float xA0; ///< Belay Popo rising terminal velocity
    float xA4; ///< Belay solo failure initial upward velocity
    float xA8; ///< Belay solo failure gravity
    float xAC; ///< Belay solo failure terminal velocity
    float xB0; ///< Belay rising air drift stick multiplier
    float xB4; ///< Belay rising max air drift speed

    // --- SpecialLw: Blizzard attributes ---
    float xB8; ///< Blizzard cloud emission interval timer (frames)
    float xBC; ///< Blizzard emission forward X offset
    float xC0; ///< Blizzard emission height Y offset
    float xC4;
    float xC8;
    u8 _CC[0xD0 - 0xCC];
    float xD0;
    u8 _D4[0x12C - 0xD4];
    float x12C;
    float x130;
    float x134;
    float x138;
    float x13C;
    float x140;
    float x144;
    float x148;
    float x14C;
    u8 _150[0x15C - 0x150];
} ftIceClimberAttributes;
ASSERT_SIZE(ftIceClimberAttributes, 0x15C);

/**
 * @brief Union of temporary motion variables for active special move states
 * @details Reused in fp->mv for Squall Hammer, Belay, and Blizzard
 */
union ftPp_MotionVars {
    /// Side-B: Squall Hammer motion variables
    struct ftPp_SpecialSVars {
        /* fp+2340 */ float x0; ///< Unused/padding
        /* fp+2344 */ int x4;   ///< Initial timer countdown
        /* fp+2348 */ struct ftPp_SpecialSVars_x8_t {
            int x0;
            HSD_GObj* x4;
        }* x8; ///< Hammer head model / subpart reference
        /* fp+234C */ int
            xC; ///< Grounded contact state flag (0 = air, 1 = floor)
        /* fp+2350 */ int x10;   ///< B-button press count accumulator
        /* fp+2354 */ int x14;   ///< Frames since last rise boost applied
        /* fp+2358 */ int x18;   ///< Total active duration frame counter
        /* fp+235C */ float x1C; ///< Current steering velocity input
    } specials;

    /// Up-B: Belay motion variables (rope animation keyframe progression)
    struct ftPp_MotionVars_unk_80123954 {
        /* fp+2340 */ int x0; ///< Frame step counter for rope string events
    } unk_80123954;

    /// Down-B: Blizzard motion variables
    struct ftPp_MotionVars_speciallw {
        /* fp+2340 */ int x0; ///< Particle spawn interval countdown timer
        /* fp+2344:0 */ u8 x4_b0 : 1; ///< Frost emission active flag
    } speciallw;
};

#endif
