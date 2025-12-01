/// @file
/// @todo Delete this.
#ifndef _common_structs_h_
#define _common_structs_h_

#include <platform.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

// Most of these should be moved to independent headers once they are created

// SOUND EFFECTS

#define SFX_VOLUME_MAX 0x7FU
#define SFX_PAN_MID 0x40U

// HSD_PAD
/// @todo @c PascalCase members
typedef u32 HSD_Pad;

#define HSD_PAD_DPADLEFT (1 << 0)
#define HSD_PAD_DPADRIGHT (1 << 1)
#define HSD_PAD_DPADDOWN (1 << 2)
#define HSD_PAD_DPADUP (1 << 3)
#define HSD_PAD_Z (1 << 4)
#define HSD_PAD_R (1 << 5)
#define HSD_PAD_L (1 << 6)
#define HSD_PAD_7 (1 << 7)

/// @remarks Also covers Z-Button macro in-game.
#define HSD_PAD_A (1 << 8)

#define HSD_PAD_B (1 << 9)
#define HSD_PAD_X (1 << 10)
#define HSD_PAD_Y (1 << 11)
#define HSD_PAD_START (1 << 12)

/// Digital input of either L or R
#define HSD_PAD_LR (1 << 31)

#define HSD_PAD_AB (HSD_PAD_A | HSD_PAD_B)
#define HSD_PAD_XY (HSD_PAD_X | HSD_PAD_Y)

// COLLISION FLAGS

// From Ness's Yo-Yo collision check

/// @todo These (and #CollData::env_flags) should be a bitfield struct
#define Collide_LeftWallPush 0x1
#define Collide_LeftWallHug 0x20
#define Collide_LeftWallMask 0x3F
#define Collide_RightWallPush 0x40
#define Collide_RightWallHug 0x800
#define Collide_RightWallMask 0xFC0
#define Collide_WallMask (Collide_LeftWallMask | Collide_RightWallMask)

#define Collide_CeilingPush 0x2000
#define Collide_CeilingHug 0x4000
#define Collide_CeilingMask (Collide_CeilingPush | Collide_CeilingHug)

#define Collide_FloorPush 0x8000
#define Collide_FloorHug 0x10000
#define Collide_FloorMask (Collide_FloorPush | Collide_FloorHug)

#define Collide_LeftEdge 0x100000
#define Collide_RightEdge 0x200000
#define Collide_Edge 0x800000
#define Collide_LeftLedgeGrab 0x1000000
#define Collide_RightLedgeGrab 0x2000000
#define Collide_LedgeGrabMask (Collide_LeftLedgeGrab | Collide_RightLedgeGrab)
#define Collide_LeftLedgeSlip 0x10000000
#define Collide_RightLedgeSlip 0x20000000

typedef union UnkFlagStruct {
    u8 u8;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
} UnkFlagStruct;

typedef enum GroundOrAir {
    GA_Ground,
    GA_Air,
} GroundOrAir;

#endif
