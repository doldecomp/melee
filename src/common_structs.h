/// @file
/// @todo Delete this.
#ifndef _common_structs_h_
#define _common_structs_h_

#include <platform.h>

#include <dolphin/gx/forward.h>

#include <dolphin/gx/types.h>
#include <dolphin/mtx/types.h>

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
#define MPCOLL_RIGHTWALL 0x3F ///< Bits 0-5
#define MPCOLL_FLAGS_B05 (1 << 5)
#define MPCOLL_LEFTWALL 0xFC0                            ///< Bits 6-11
#define MPCOLL_WALL (MPCOLL_RIGHTWALL | MPCOLL_LEFTWALL) ///< Bits 0-11
#define MPCOLL_FLAGS_B11 (1 << 11)
#define MPCOLL_CEIL 0x6000 ///< Bits 13-14
#define MPCOLL_FLAGS_B14 (1 << 14)
#define MPCOLL_UNK 0x18000
#define MPCOLL_GRPUSH (1 << 15)
#define MPCOLL_FLAGS_B16 (1 << 16)
#define MPCOLL_FLAGS_B23 (1 << 23)
#define MPCOLL_FLAGS_B24 (1 << 24)
#define MPCOLL_FLAGS_B25 (1 << 25)

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

typedef struct ColorOverlay {
    s32 x0_timer;        // 0x0
    s32 x4_pri;          // 0x4  this colanims priority, lower = will persist
    s32* x8_ptr1;        // 0x8
    s32 xC_loop;         // 0xc
    s32* x10_ptr2;       // 0x10
    s32 x14;             // 0x14
    s32* x18_alloc;      // 0x18
    s32 x1c;             // 0x1c
    s32 x20;             // 0x20
    s32 x24;             // 0x24
    s32 x28_colanim;     // 0x28, id for the color animation in effect
    GXColor x2C_hex;     // 0x2C
    f32 x30_color_red;   // 0x30
    f32 x34_color_green; // 0x34
    f32 x38_color_blue;  // 0x38
    f32 x3C_color_alpha; // 0x3C
    f32 x40_colorblend_red;   // 0x40
    f32 x44_colorblend_green; // 0x44
    f32 x48_colorblend_blue;  // 0x48
    f32 x4C_colorblend_alpha; // 0x4C
    GXColor x50_light_color;  // 0x50
    f32 x54_light_red;        // 0x54
    f32 x58_light_green;      // 0x58
    f32 x5C_light_blue;       // 0x5C
    f32 x60_light_alpha;      // 0x60
    f32 x64_lightblend_red;   // 0x64
    f32 x68_lightblend_green; // 0x68
    f32 x6C_lightblend_blue;  // 0x6c
    f32 x70_lightblend_alpha; // 0x70
    f32 x74_light_angle;      // 0x74
    f32 x78_light_unk;        // 0x78
    u8 x7C_color_enable : 1;  // 0x7c, 0x80
    u8 x7C_flag2 : 1;         // 0x7c, 0x40
    u8 x7C_light_enable : 1;  // 0x7c, 0x20
    u8 x7C_flag4 : 1;         // 0x7c, 0x10
    u8 x7C_flag5 : 1;         // 0x7c, 0x08
    u8 x7C_flag6 : 1;         // 0x7c, 0x04
    u8 x7C_flag7 : 1;         // 0x7c, 0x02
    u8 x7C_flag8 : 1;         // 0x7c, 0x01
} ColorOverlay;

struct r13_ColAnimStruct {
    u32 x0_unk;
    u8 x4_unk;
    u8 x5_unk;
    u8 x6_unk;
    u8 x7_unk;
};

typedef enum GroundOrAir {
    GA_Ground,
    GA_Air,
} GroundOrAir;

#endif
