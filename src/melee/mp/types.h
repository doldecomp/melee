#ifndef MELEE_MP_TYPES_H
#define MELEE_MP_TYPES_H

#include <Runtime/platform.h>

#include <melee/gr/forward.h>
#include <melee/mp/forward.h> // IWYU pragma: export

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

struct mpIsland_80458E88_t {
    /*  +0 */ mpIsland* floors;
    /*  +4 */ mpIsland* ceilings;
    /*  +8 */ mpIsland* non_dynamic_floors_tail;
    /*  +C */ mpIsland* non_dynamic_ceilings_tail;
    /* +10 */ mpIsland* dynamic_floors;
    /* +14 */ mpIsland* dynamic_ceilings;
    /* +18 */ mpIsland* b1_floors;
    /* +1C */ mpIsland* b1_ceilings;
    /* +20 */ mpIsland* free_list;
};

struct mpIsland_PaletteEntry {
    mp_Terrain kind;
    GXColor color;
};

struct mpIsland_Palette {
    mpIsland_PaletteEntry entries[20];
};

struct mpIsland {
    /*  +0 */ mpIsland* next;
    /*  +4 */ u16 vtx0;
    /*  +6 */ u16 vtx1;
    /*  +8 */ Vec3 pos0;
    /* +14 */ Vec3 pos1;
    /* +20 */ int flags;
    /* +24 */ s16 line0;
    /* +26 */ s16 line1;
    /* +28 */ s16 joint_id;
};
ASSERT_SIZE(struct mpIsland, 0x2C);

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
    /* +0 */ MapLine* inner;
    /* +4 */ u32 flags;
};

struct CollVtx {
    /* 0x00 */ Vec2 base_pos;
    /* 0x08 */ Vec2 pos;
    /* 0x10 */ Vec2 prev_pos;
}; /* size = 0x18 */
ASSERT_SIZE(struct CollVtx, 0x18);

enum MapLineGroup {
    MapLineGroup_Floor,
    MapLineGroup_Ceiling,
    MapLineGroup_RightWall,
    MapLineGroup_LeftWall,
    MapLineGroup_Dynamic,
    MapLineGroup_Count,
};

struct MapLineRange {
    s16 start;
    s16 count;
};

struct MapJoint {
    /*  +0 */ struct MapLineRange ranges[MapLineGroup_Count];
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
    /* 0x20 */ HSD_JObj* jobj;
    /* 0x24 */ mpLib_JointCollisionCallback
        cb_0; ///< @todo Possible array here
    /* 0x28 */ Ground* cb_data_0;
    /* 0x2C */ mpLib_JointCollisionCallback cb_1;
    /* 0x30 */ Ground* cb_data_1;
}; /* size = 0x34 */
ASSERT_SIZE(struct CollJoint, 0x34);

struct MapCollData {
    /*  +0 */ Vec2* verts;
    /*  +4 */ int vert_count;
    /*  +8 */ MapLine* lines;
    /*  +C */ int line_count;
    /* +10 */ struct MapLineRange ranges[MapLineGroup_Count];
    /* +24 */ MapJoint* joints;
    /* +28 */ int joint_count;
    /* +2C */ int x2C; /* inferred */
};

struct mpCollisionBox {
    float top;
    float bottom;
    float left;
    float right;
};

#endif
