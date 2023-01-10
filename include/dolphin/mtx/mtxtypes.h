#ifndef _MTXTYPES_h_
#define _MTXTYPES_h_

#include <dolphin/types.h>

/// @todo Remove @c Vec (in favor of @c Vec3).
/// @todo Remove @c Point3d.
/// @todo Remove pointer alias.
typedef struct {
    f32 x, y, z;
} Vec3, Vec, *VecPtr, Point3d, *Point3dPtr;

/// @todo Remove pointer alias.
typedef struct {
    s16 x, y, z;
} S16Vec, *S16VecPtr;

/// @todo Remove pointer alias.
typedef struct {
    s8 x, y, z;
} S8Vec, *S8VecPtr;

/// @todo Remove pointer alias.
typedef struct {
    s32 x, y, z;
} S32Vec, *S32VecPtr;

/// @todo Base name should be @c Vec4 with @c Quaternion as an alias.
/// @todo Remove pointer alias.
typedef struct {
    f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef struct _S32Pair {
    s32 x, y;
} S32Pair;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

#endif
