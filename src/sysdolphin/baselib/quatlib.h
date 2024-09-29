#ifndef INCLUDE_SYSDOLPHIN_BASELIB_QUATLIB_H
#define INCLUDE_SYSDOLPHIN_BASELIB_QUATLIB_H

#include <platform.h>

#include <dolphin/mtx/forward.h>

#include <dolphin/mtx.h>

void EulerToQuat(Vec3*, Quaternion*);
void HSD_QuatLib_8037EF28(Quaternion*, Quaternion*, Quaternion*, f32);

#endif
