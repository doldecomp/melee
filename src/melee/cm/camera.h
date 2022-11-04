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
void func_8002A278(f32 x, f32 y);
void func_8002E6FC(u8);
void func_8002E948(u32 (*)(Vec*));
void func_8002EB5C(f32);
void func_8002EC7C(f32);
void func_8002ED9C(f32);
void func_8002EEC8(f32);
void func_8002EF14(void);
void func_8002F0E4(s32);

#endif
