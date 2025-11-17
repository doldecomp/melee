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
#define MPCOLL_LEFTWALL 0x3F ///< Bits 0-5
#define MPCOLL_FLAGS_B05 (1 << 5)
#define MPCOLL_RIGHTWALL 0xFC0                           ///< Bits 6-11
#define MPCOLL_WALL (MPCOLL_LEFTWALL | MPCOLL_RIGHTWALL) ///< Bits 0-11
#define MPCOLL_FLAGS_B11 (1 << 11)
#define MPCOLL_CEIL 0x6000 ///< Bits 13-14
#define MPCOLL_FLAGS_B14 (1 << 14)
#define MPCOLL_UNK 0x18000 // Floor??
#define MPCOLL_GRPUSH (1 << 15)
#define MPCOLL_FLAGS_B16 (1 << 16)
#define MPCOLL_FLAGS_B20 (1 << 20) // 0x100000
#define MPCOLL_FLAGS_B21 (1 << 21) // 0x200000
#define MPCOLL_FLAGS_B23 (1 << 23) // 0x800000
#define MPCOLL_FLAGS_B24 (1 << 24) // 0x1000000
#define MPCOLL_FLAGS_B25 (1 << 25) // 0x2000000
#define MPCOLL_FLAGS_B28 (1 << 28) // 0x10000000
#define MPCOLL_FLAGS_B29 (1 << 29) // 0x20000000

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
