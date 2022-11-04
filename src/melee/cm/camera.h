#ifndef MELEE_CM_CAMERA_H
#define MELEE_CM_CAMERA_H

#include <ctypes.h>

#include <common_structs.h>

typedef struct _CameraBox {
    u32 data_filler[2];
    s32 x8;
    UnkFlagStruct xC_flag;
    u8 xD_fill[0x10 - 0xD];
    Vec3 x10; // might be Vec2?
    Vec3 x1C;
    f32 x28;
    Vec2 x2C;
    Vec3 x34;
    Vec2 x40;
    Vec3 x48;
} CameraBox;

unk_t func_8003118C();
void func_8002F474(void);
unk_t func_80030E44();
CameraBox* func_80029020();
void func_800290D4();

#endif
