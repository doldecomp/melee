#ifndef INCLUDE_SYSDOLPHIN_BASELIB_QUATLIB_H
#define INCLUDE_SYSDOLPHIN_BASELIB_QUATLIB_H

#include <platform.h>

#include <dolphin/mtx.h>

s32 MatToQuat(Mtx, Quaternion*);
s32 HSD_QuatLib_8037EB28(Mtx, Vec3*);
s32 HSD_QuatLib_8037EC4C(Quaternion*, Quaternion*, Quaternion*);
s32 HSD_QuatLib_8037ECE0(Vec3*, Quaternion*, f32);
s32 EulerToQuat(Vec3*, Quaternion*);
s32 HSD_QuatLib_8037EF28(Quaternion*, Quaternion*, Quaternion*, f32);

#endif
