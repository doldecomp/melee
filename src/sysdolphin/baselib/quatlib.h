#ifndef INCLUDE_SYSDOLPHIN_BASELIB_QUATLIB_H
#define INCLUDE_SYSDOLPHIN_BASELIB_QUATLIB_H

#include <Runtime/platform.h>

#include <dolphin/mtx.h>

s32 MatToQuat(Mtx, Quaternion*);
s32 MatToEuler(Mtx, Vec3*);
s32 QuatMul(Quaternion*, Quaternion*, Quaternion*);
s32 AngleAxisToQuat(Vec3*, Quaternion*, f32);
s32 EulerToQuat(Vec3*, Quaternion*);
s32 QuatSlerp(Quaternion*, Quaternion*, Quaternion*, f32);

#endif
