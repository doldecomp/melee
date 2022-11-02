#ifndef DOLPHIN_MTX_MTXTYPES_H
#define DOLPHIN_MTX_MTXTYPES_H

#include <dolphin/types.h>

typedef struct _Vec2 {
    f32 x, y;
} Vec2, *Vec2Ptr, Point2d, *Point2dPtr;

typedef struct _Vec {
    f32 x, y, z;
} Vec, *VecPtr, Vec3, *Vec3Ptr, Point3d, *Point3dPtr;

typedef struct _S16Vec {
    s16 x, y, z;
} S16Vec, *S16VecPtr;

typedef struct _S8Vec {
    s8 x, y, z;
} S8Vec, *S8VecPtr;

typedef struct _S32Vec {
    s32 x, y, z;
} S32Vec, *S32VecPtr;

typedef struct _Quaternion {
    f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

#endif
