#ifndef MELEE_MP_FORWARD_H
#define MELEE_MP_FORWARD_H

#include <placeholder.h>
#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"

typedef struct mpIsland_803B73E8_inner mpIsland_803B73E8_inner;
typedef struct mpIsland_803B73E8_t mpIsland_803B73E8_t;
typedef struct mp_UnkStruct0 mp_UnkStruct0;
typedef struct mpLib_Line mpLib_Line;
typedef struct CollLine CollLine;
typedef struct mp_UnkStruct3 mp_UnkStruct3;
typedef struct mp_UnkStruct4 mp_UnkStruct4;
typedef struct mp_UnkStruct6 mp_UnkStruct6;
typedef struct mpisland mpisland;
typedef struct CollVtx CollVtx;
typedef struct mpLib_CollData mpLib_CollData;
typedef struct CollJoint CollJoint;
typedef struct mp_CollData mp_CollData;

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
#define LINE_FLAG_PLATFORM (1 << 8)
#define LINE_FLAG_LEDGE (1 << 9)

#endif
