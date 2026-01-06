#ifndef MELEE_MP_TYPES_H
#define MELEE_MP_TYPES_H

#include "platform.h"

#include <placeholder.h>

#include "dolphin/gx/GXStruct.h"

#include "gr/forward.h"
#include "mp/forward.h" // IWYU pragma: export

#include <dolphin/mtx.h>

struct mpIsland_80458E88_t {
    /*  +0 */ mp_UnkStruct0* next;
    /*  +4 */ mp_UnkStruct0* x4;
    /*  +8 */ mp_UnkStruct0* x8;
    /*  +C */ mp_UnkStruct0* xC;
    /* +10 */ mp_UnkStruct0* x10;
    /* +14 */ mp_UnkStruct0* x14;
    /* +18 */ mp_UnkStruct0* x18;
    /* +1C */ mp_UnkStruct0* x1C;
    /* +20 */ mp_UnkStruct0* x20;
};

struct mpIsland_PaletteEntry {
    mp_Terrain kind;
    GXColor color;
};

struct mpIsland_Palette {
    mpIsland_PaletteEntry x0[20];
};

struct mp_UnkStruct0 {
    /*  +0 */ mp_UnkStruct0* next;
    /*  +4 */ u16 x4;
    /*  +6 */ u16 x6;
    /*  +8 */ Vec3 x8;
    /* +14 */ Vec3 x14;
    /* +20 */ int x20;
    /* +24 */ short x24;
    /* +26 */ short x26;
    /* +28 */ short x28;
    /* +2A */ short x2A;
    /* +2C */ mp_UnkStruct3* ptr;
};

struct MapLine {
    /* +0 */ u16 v0_idx;
    /* +2 */ u16 v1_idx;
    /* +4 */ s16 prev_id0;
    /* +6 */ s16 next_id0;
    /* +8 */ s16 prev_id1;
    /* +A */ s16 next_id1;
    /* +C */ u16 hi_flags;
    /* +E */ u16 lo_flags;
};

struct CollLine {
    /* +0 */ MapLine* x0;
    /* +4 */ u32 flags;
};

struct mpisland {
    /*  +0 */ int x0[8];
    /* +20 */ int x20[8];
};

struct mp_UnkStruct3 {
    int x0;
    int x4;
    int xC;
};

struct CollVtx {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ Vec2 pos;
    /* 0x10 */ float x10;
    /* 0x14 */ float x14;
}; /* size = 0x18 */
STATIC_ASSERT(sizeof(struct CollVtx) == 0x18);

struct MapJoint {
    /*  +0 */ s16 floor_start;
    /*  +2 */ s16 floor_count;
    /*  +4 */ s16 ceiling_start;
    /*  +6 */ s16 ceiling_count;
    /*  +8 */ s16 right_wall_start;
    /*  +A */ s16 right_wall_count;
    /*  +C */ s16 left_wall_start;
    /*  +E */ s16 left_wall_count;
    /* +10 */ s16 dynamic_start;
    /* +12 */ s16 dynamic_count;
    /* +14 */ float left_bound;
    /* +18 */ float bottom_bound;
    /* +1C */ float right_bound;
    /* +20 */ float top_bound;
    /* +24 */ s16 vtx_start;
    /* +26 */ s16 vtx_count;
};

struct CollJoint {
    /* 0x00 */ CollJoint* next;
    /* 0x04 */ MapJoint* inner;
    /* 0x08 */ u32 flags;
    /* 0x0C */ s16 xC;
    /* 0x0E */ u8 xE : 1;
    /* 0x10 */ Vec2 bounding_min;
    /* 0x18 */ Vec2 bounding_max;
    /* 0x20 */ HSD_JObj* x20;
    /* 0x24 */ mpLib_Callback x24;
    /* 0x28 */ Ground* x28;
    /* 0x2C */ mpLib_Callback x2C;
    /* 0x30 */ Ground* x30;
}; /* size = 0x34 */
STATIC_ASSERT(sizeof(struct CollJoint) == 0x34);

struct MapCollData {
    /*  +0 */ Vec2* verts;
    /*  +4 */ int vert_count;
    /*  +8 */ MapLine* lines;
    /*  +C */ int line_count;
    /* +10 */ s16 floor_start;
    /* +12 */ s16 floor_count;
    /* +14 */ s16 ceiling_start;
    /* +16 */ s16 ceiling_count;
    /* +18 */ s16 right_wall_start;
    /* +1A */ s16 right_wall_count;
    /* +1C */ s16 left_wall_start;
    /* +1E */ s16 left_wall_count;
    /* +20 */ s16 dynamic_start;
    /* +22 */ s16 dynamic_count;
    /* +24 */ MapJoint* joints;
    /* +28 */ int joint_count;
    /* +2C */ int x2C; /* inferred */
};

#endif
