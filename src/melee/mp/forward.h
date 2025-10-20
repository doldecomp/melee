#ifndef MELEE_MP_FORWARD_H
#define MELEE_MP_FORWARD_H

#include <placeholder.h>
#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"

typedef struct mpIsland_PaletteEntry mpIsland_PaletteEntry;
typedef struct mpIsland_Palette mpIsland_Palette;
typedef struct mp_UnkStruct0 mp_UnkStruct0;
typedef struct mpLib_Line mpLib_Line;
typedef struct CollLine CollLine;
typedef struct mp_UnkStruct3 mp_UnkStruct3;
typedef struct mpisland mpisland;
typedef struct CollVtx CollVtx;
typedef struct CollInfo CollInfo;
typedef struct CollJoint CollJoint;
typedef struct mpCollData mpCollData;

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

#define LINE_FLAG_FLOOR (1 << 0)
#define LINE_FLAG_CEILING (1 << 1)
#define LINE_FLAG_RIGHT_WALL (1 << 2)
#define LINE_FLAG_LEFT_WALL (1 << 3)
#define LINE_FLAG_EMPTY (1 << 7)
#define LINE_FLAG_PLATFORM (1 << 8)
#define LINE_FLAG_LEDGE (1 << 9)

#endif
