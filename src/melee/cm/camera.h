#ifndef MELEE_CM_CAMERA_H
#define MELEE_CM_CAMERA_H

#include <dolphin/mtx/mtxtypes.h>

struct _CameraBox* func_80029020(void);
void func_800290D4(struct _CameraBox*);
void func_8002A278(f32 x, f32 y);
void func_8002E6FC(u8);
void func_8002E948(u32 (*)(Vec*));
void func_8002EB5C(f32);
void func_8002EC7C(f32);
void func_8002ED9C(f32);
void func_8002EEC8(f32);
void func_8002EF14(void);
void func_8002F0E4(s32);
s32 func_8002F260(void);
void func_8002F274(void);
void func_8002F474(void);
void* func_80030A50(void);
BOOL func_80030CFC(struct _CameraBox*, f32);
f32 func_80031144(void);
void func_80030E44(s32, Vec3*);

#endif
