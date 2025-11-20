#ifndef MELEE_MP_FORWARD_H
#define MELEE_MP_FORWARD_H

#include <placeholder.h>
#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"

typedef struct mpIsland_PaletteEntry mpIsland_PaletteEntry;
typedef struct mpIsland_Palette mpIsland_Palette;
typedef struct mp_UnkStruct0 mp_UnkStruct0;
typedef struct MapLine MapLine;
typedef struct CollLine CollLine;
typedef struct mp_UnkStruct3 mp_UnkStruct3;
typedef struct mpisland mpisland;
typedef struct CollVtx CollVtx;
typedef struct MapJoint MapJoint;
typedef struct CollJoint CollJoint;
typedef struct MapCollData MapCollData;

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

typedef void (*mpLib_Callback)(Ground*, s32, CollData*, s32, mpLib_GroundEnum,
                               f32);
typedef bool (*mpColl_Callback)(CollData*, u32);

typedef enum CollLineKind {
    CollLine_Floor = 1 << 0,
    CollLine_Ceiling = 1 << 1,
    CollLine_RightWall = 1 << 2,
    CollLine_LeftWall = 1 << 3,
} CollLineKind;

#define LINE_FLAG_KIND (0b1111)
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

#endif
