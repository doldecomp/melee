#ifndef MELEE_CM_CAMERA_H
#define MELEE_CM_CAMERA_H

#include <dolphin/mtx/types.h>

struct _CameraBox* Camera_80029020(void);
void Camera_800290D4(struct _CameraBox*);
void Camera_8002A278(f32 x, f32 y);
void Camera_8002E6FC(u8);
void Camera_8002E948(bool (*)(Vec3*));
void Camera_8002EB5C(f32);
void Camera_8002EC7C(f32);
void Camera_8002ED9C(f32);
void Camera_8002EEC8(f32);
void Camera_8002EF14(void);
void Camera_8002F0E4(s32);
s32 Camera_8002F260(void);
void Camera_8002F274(void);
void Camera_8002F474(void);
void* Camera_80030A50(void);
bool Camera_80030CFC(struct _CameraBox*, f32);
f32 Camera_80031144(void);
void Camera_80030E44(s32, Vec3*);
void Camera_8002EA64(Vec3*);
void Camera_8002E818(Vec3*);
bool Camera_80030CD8(struct _CameraBox*, S32Vec2*);
void Camera_80031154(Vec3*);
bool Camera_80030A78(void);

/// @param r The red component.
/// @param g The green component.
/// @param b The blue component.
void Camera_80030740(u8 r, u8 g, u8 b);

void Camera_8002F8F4(void);

#endif
