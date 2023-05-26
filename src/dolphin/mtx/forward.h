#ifndef DOLPHIN_MTX_FORWARD_H
#define DOLPHIN_MTX_FORWARD_H

#include <platform.h>

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

typedef struct IntVec3 IntVec3;
typedef struct S16Vec3 S16Vec3;
typedef struct S32Vec2 S32Vec2;
typedef struct S32Vec3 S32Vec3;
typedef struct S8Vec3 S8Vec3;
typedef struct Vec2 Vec2;
typedef struct Vec3 Vec3;
typedef struct Vec4 Quaternion, Vec4;

#endif
