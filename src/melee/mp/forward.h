#ifndef MELEE_MP_FORWARD_H
#define MELEE_MP_FORWARD_H

#include <platform.h>

#include "lb/forward.h"

typedef struct mp_UnkStruct0 mp_UnkStruct0;
typedef struct mp_UnkStruct1 mp_UnkStruct1;
typedef struct mp_UnkStruct2 mp_UnkStruct2;
typedef struct mp_UnkStruct3 mp_UnkStruct3;
typedef struct mp_UnkStruct4 mp_UnkStruct4;
typedef struct mp_UnkStruct5 mp_UnkStruct5;
typedef struct mp_UnkStruct6 mp_UnkStruct6;
typedef struct mp_UnkStruct7 mp_UnkStruct7;
typedef struct mpisland mpisland;

typedef void (*mpLib_Callback)(s32, s32, CollData*, s32, s32, f32);
typedef bool (*mpColl_Callback)(CollData*, u32);

#endif
