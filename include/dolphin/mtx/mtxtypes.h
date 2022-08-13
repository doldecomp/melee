#ifndef _MTXTYPES_h_
#define _MTXTYPES_h_

#include <dolphin/types.h>

typedef struct
{
	f32 x, y, z;
} Vec, *VecPtr, Point3d, *Point3dPtr;

typedef struct
{
    s16 x, y, z;
} S16Vec, *S16VecPtr;

typedef struct
{
    s8 x, y, z;
} S8Vec, *S8VecPtr;

typedef struct
{
    s32 x, y, z;
} S32Vec, *S32VecPtr;

typedef struct
{
	f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

#endif
