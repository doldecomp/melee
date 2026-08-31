#ifndef MELEE_MP_FORWARD_H
#define MELEE_MP_FORWARD_H

#include <platform.h>

#include "lb/forward.h"

typedef struct CollJoint CollJoint;
typedef struct CollLine CollLine;
typedef struct CollVtx CollVtx;
typedef struct MapCollData MapCollData;
typedef struct MapJoint MapJoint;
typedef struct MapLine MapLine;
typedef struct mp_UnkStruct0 mp_UnkStruct0;
typedef struct mp_UnkStruct3 mp_UnkStruct3;
typedef struct mpCollisionBox mpCollisionBox;
typedef struct mpisland mpisland;
typedef struct mpIsland_Palette mpIsland_Palette;
typedef struct mpIsland_PaletteEntry mpIsland_PaletteEntry;

typedef enum mp_Terrain {
    mp_Terrain_Basic,
    mp_Terrain_Rock,
    mp_Terrain_Grass,
    mp_Terrain_Dirt,
    mp_Terrain_Wood,
    mp_Terrain_LightMetal,
    mp_Terrain_HeavyMetal,
    mp_Terrain_Paper,
    mp_Terrain_Goop,
    mp_Terrain_Birdo, // used in GrI2
    mp_Terrain_Water,
    mp_Terrain_Unk11, // used in GrTe
    mp_Terrain_UFO,
    mp_Terrain_Turtle,
    mp_Terrain_Snow,
    mp_Terrain_Ice,
    mp_Terrain_GnW,
    mp_Terrain_Unk17, // used in GrTe
    mp_Terrain_Checkered,
    mp_Terrain_Unk19,
} mp_Terrain;

typedef enum mpLib_GroundEnum {
    mpLib_GroundEnum_Unk0,
    mpLib_GroundEnum_Unk1,
    mpLib_GroundEnum_Unk2,
} mpLib_GroundEnum;

typedef void (*mpLib_JointCollisionCallback)(void* user_data, int joint_id,
                                             CollData* coll, int coll_x50,
                                             mpLib_GroundEnum ground_kind,
                                             float delta_y);
typedef bool (*mpColl_Callback)(CollData*, u32);

typedef enum CollLineKind {
    CollLine_Floor = 1 << 0,
    CollLine_Ceiling = 1 << 1,
    CollLine_RightWall = 1 << 2,
    CollLine_LeftWall = 1 << 3,
} CollLineKind;

#define LINE_FLAG_KIND (0xF)
#define LINE_FLAG_EMPTY (1 << 7)
#define LINE_FLAG_PLATFORM (1 << 8)
#define LINE_FLAG_LEDGE (1 << 9)
#define LINE_FLAG_ENABLED (1 << 16)
#define LINE_FLAG_HIDDEN (1 << 18)

#define MPCOLL_WALLID_MAX 9

enum CollDataX130Flags {
    CollData_X130_Locked = 1 << 4,
    CollData_X130_Clear = 1 << 5,
};

enum CollJointFlags {
    CollJoint_B8 = 1 << 8,
    CollJoint_B9 = 1 << 9,
    CollJoint_B10 = 1 << 10,
    CollJoint_B11 = 1 << 11,
    CollJoint_TooFar = 1 << 12,
    CollJoint_Enabled = 1 << 16,
    CollJoint_Hidden = 1 << 18,
};

/// COLLISION FLAGS
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

#endif
