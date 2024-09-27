#include "ft/forward.h"

#include "camera.h"

#include "ft/ftlib.h"
#include "gr/stage.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/mtx/types.h>
#include <baselib/cobj.h>

/* 3B73B8 */ extern Vec3 cm_803B73B8;
/* 3B73C4 */ extern Vec3 cm_803B73C4;
/* 3BCB64 */ extern HSD_CObjDesc cm_803BCB64;
/* 452C68 */ extern Camera cm_80452C68;
/* 4D7E04 */ extern float cm_804D7E04;
/* 4D7E04 */ extern float cm_804D7E04;
/* 4D7E14 */ extern float cm_804D7E14;
/* 4D7E30 */ extern float cm_804D7E30;
/* 4D7E60 */ extern float cm_804D7E60;
/* 4D7E6C */ extern float cm_804D7E6C;
/* 4D6458 */ extern CameraBox* cm_804D6458;
/* 4D6460 */ extern CameraBox* cm_804D6460;
/* 4D6468 */ extern CameraBox* cm_804D6468;

CameraBox* Camera_80029020(void)
{
    return Camera_80029044(0);
}

void Camera_80029BC4(CameraBounds* bounds, CameraMovement* movement)
{
    float cam_dist = (bounds->y_max - bounds->y_min) /
                     tanf(cm_804D7E60 * movement->target_fov);
    float x_dist = (bounds->x_max - bounds->x_min) /
                   (cm_803BCB64.perspective.aspect *
                    tanf(cm_804D7E60 * movement->target_fov));
    if (x_dist > cam_dist) {
        cam_dist = x_dist;
    }
    if (cam_dist < Stage_GetCamZoomRate()) {
        cam_dist = Stage_GetCamZoomRate();
    }
    if (cam_dist > Stage_GetCamMaxDepth()) {
        cam_dist = Stage_GetCamMaxDepth();
    }
    bounds->z_pos = cam_dist;
}

void Camera_8002A768(CameraMovement* movement, int arg1)
{
    Vec3 sp58;
    float zero;
    float zero2;
    float neg_one;
    Vec3 top_left;
    Vec3 top_right;
    Vec3 bottom_right;
    Vec3 bottom_left;
    Vec3 cam_correction;
    float temp_f0;
    float temp_f0_10;
    float temp_f0_11;
    float temp_f0_12;
    float temp_f0_13;
    float temp_f0_14;
    float temp_f0_15;
    float temp_f0_2;
    float temp_f0_3;
    float temp_f0_4;
    float temp_f0_5;
    float temp_f0_6;
    float temp_f0_7;
    float temp_f0_8;
    float temp_f0_9;
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;
    float temp_f1_4;
    float temp_f1_5;
    float temp_f1_6;
    float temp_f28;
    float temp_f30;
    float temp_f31;
    float var_f28;
    float var_f29;
    float var_f30;
    float var_f31;
    float* temp_r27;
    int temp_r3;
    int temp_r5;
    int var_r30;
    int var_r31;

    var_r31 = 0;
    var_r30 = 0;
    zero = cm_803B73B8.x;
    zero2 = cm_803B73B8.y;
    temp_f30 = cm_804D7E30 * (cm_804D7E60 * movement->target_fov);
    neg_one = cm_803B73B8.z;
    lbVector_Diff(&movement->target_interest, &movement->target_position,
                  &sp58);
    lbVector_Normalize(&sp58);
    temp_f28 = atan2f(sp58.y, -sp58.z);
    temp_f0 = atan2f(-sp58.x, -sp58.z);
    bottom_left.x = zero;
    bottom_left.y = zero2;
    bottom_left.z = neg_one;
    bottom_right.x = zero;
    bottom_right.y = zero2;
    bottom_right.z = neg_one;
    top_right.x = zero;
    top_right.y = zero2;
    top_right.z = neg_one;
    top_left.x = zero;
    top_left.y = zero2;
    top_left.z = neg_one;
    lbVector_Rotate((Vec3*) &top_left.x, 1, temp_f30);
    lbVector_Rotate((Vec3*) &top_left.x, 2, temp_f30);
    temp_r27 = &cm_803BCB64.perspective.aspect;
    top_left.x *= cm_803BCB64.perspective.aspect;
    lbVector_Normalize((Vec3*) &top_left.x);
    lbVector_Rotate((Vec3*) &top_left.x, 1, temp_f28);
    lbVector_Rotate((Vec3*) &top_left.x, 2, temp_f0);
    if (top_left.z < cm_804D7E6C) {
        temp_f1 = -movement->target_position.x / top_left.z;
        top_left.x *= temp_f1;
        top_left.y *= temp_f1;
        top_left.z *= temp_f1;
        lbVector_Add((Vec3*) &top_left.x, &movement->target_position);
    } else {
        var_r30 = 1;
    }
    lbVector_Rotate((Vec3*) &top_right.x, 1, temp_f30);
    temp_f31 = -temp_f30;
    lbVector_Rotate((Vec3*) &top_right.x, 2, temp_f31);
    top_right.x *= *temp_r27;
    lbVector_Normalize((Vec3*) &top_right.x);
    lbVector_Rotate((Vec3*) &top_right.x, 1, temp_f28);
    lbVector_Rotate((Vec3*) &top_right.x, 2, temp_f0);
    if (top_right.z < cm_804D7E6C) {
        temp_f1_2 = -movement->target_position.x / top_right.z;
        top_right.x *= temp_f1_2;
        top_right.y *= temp_f1_2;
        top_right.z *= temp_f1_2;
        lbVector_Add((Vec3*) &top_right.x, &movement->target_position);
    } else {
        var_r30 |= 2;
    }
    lbVector_Rotate((Vec3*) &bottom_right.x, 1, temp_f31);
    lbVector_Rotate((Vec3*) &bottom_right.x, 2, temp_f30);
    lbVector_Rotate(M2C_ERROR(/* Read from unset register $r3 */), 1,
                    M2C_ERROR(/* Read from unset register $f1 */));
    lbVector_Rotate((Vec3*) &bottom_right.x, 2, temp_f0);
    if (bottom_right.z < cm_804D7E6C) {
        temp_f1_3 = -movement->target_position.x / bottom_right.z;
        bottom_right.x *= temp_f1_3;
        bottom_right.y *= temp_f1_3;
        bottom_right.z *= temp_f1_3;
        lbVector_Add((Vec3*) &bottom_right.x, &movement->target_position);
    } else {
        var_r30 |= 4;
    }
    lbVector_Rotate((Vec3*) &bottom_left, 1, temp_f31);
    lbVector_Rotate((Vec3*) &bottom_left, 2, temp_f31);
    bottom_left.x *= *temp_r27;
    lbVector_Normalize((Vec3*) &bottom_left);
    lbVector_Rotate((Vec3*) &bottom_left, 1, temp_f28);
    lbVector_Rotate((Vec3*) &bottom_left, 2, temp_f0);
    if (bottom_left.z < cm_804D7E6C) {
        temp_f1_4 = -movement->target_position.x / bottom_left.z;
        bottom_left.x *= temp_f1_4;
        bottom_left.y *= temp_f1_4;
        bottom_left.z *= temp_f1_4;
        lbVector_Add((Vec3*) &bottom_left, &movement->target_position);
    } else {
        var_r30 |= 8;
    }
    var_f28 = cm_804D7E14;
    var_f29 = var_f28;
    var_f30 = var_f29;
    var_f31 = var_f30;
    if (arg1 != 0) {
        if (!(var_r30 & 1)) {
            if (top_left.x < Stage_GetBlastZoneLeftOffset()) {
                temp_f0_2 = Stage_GetBlastZoneLeftOffset() - top_left.x;
                if (temp_f0_2 > var_f31) {
                    var_f31 = temp_f0_2;
                    var_r31 = 4;
                }
            }
            if (top_left.y > Stage_GetBlastZoneTopOffset()) {
                temp_f1_5 = Stage_GetBlastZoneTopOffset() - top_left.y;
                if (temp_f1_5 < cm_804D7E14) {
                    var_f28 = temp_f1_5;
                    var_r31 |= 1;
                }
            }
        }
        if (!(var_r30 & 2)) {
            if (top_right.x > Stage_GetBlastZoneRightOffset()) {
                temp_f0_3 = Stage_GetBlastZoneRightOffset() - top_right.x;
                if (temp_f0_3 < var_f29) {
                    var_f29 = temp_f0_3;
                    var_r31 |= 8;
                }
            }
            if (top_right.y > Stage_GetBlastZoneTopOffset()) {
                temp_f0_4 = Stage_GetBlastZoneTopOffset() - top_right.y;
                if (temp_f0_4 < var_f28) {
                    var_f28 = temp_f0_4;
                    var_r31 |= 1;
                }
            }
        }
        if (!(var_r30 & 4)) {
            if (bottom_right.x < Stage_GetBlastZoneLeftOffset()) {
                temp_f0_5 = Stage_GetBlastZoneLeftOffset() - bottom_right.x;
                if (temp_f0_5 > var_f31) {
                    var_f31 = temp_f0_5;
                    var_r31 |= 4;
                }
            }
            if (bottom_right.y < Stage_GetBlastZoneBottomOffset()) {
                temp_f0_6 = Stage_GetBlastZoneBottomOffset() - bottom_right.y;
                if (temp_f0_6 > var_f30) {
                    var_f30 = temp_f0_6;
                    var_r31 |= 2;
                }
            }
        }
        if (!(var_r30 & 8)) {
            if (bottom_left.x > Stage_GetBlastZoneRightOffset()) {
                temp_f0_7 = Stage_GetBlastZoneRightOffset() - bottom_left.x;
                if (temp_f0_7 < var_f29) {
                    var_f29 = temp_f0_7;
                    var_r31 |= 8;
                }
            }
            if (bottom_left.y < Stage_GetBlastZoneBottomOffset()) {
                temp_f0_8 = Stage_GetBlastZoneBottomOffset() - bottom_left.y;
                if (temp_f0_8 > var_f30) {
                    var_f30 = temp_f0_8;
                    var_r31 |= 2;
                }
            }
        }
    } else {
        if (!(var_r30 & 1)) {
            if (top_left.x < Stage_GetCamBoundsLeftOffset()) {
                temp_f0_9 = Stage_GetCamBoundsLeftOffset() - top_left.x;
                if (temp_f0_9 > var_f31) {
                    var_f31 = temp_f0_9;
                    var_r31 = 4;
                }
            }
            if (top_left.y > Stage_GetCamBoundsTopOffset()) {
                temp_f1_6 = Stage_GetCamBoundsTopOffset() - top_left.y;
                if (temp_f1_6 < cm_804D7E14) {
                    var_f28 = temp_f1_6;
                    var_r31 |= 1;
                }
            }
        }
        if (!(var_r30 & 2)) {
            if (top_right.x > Stage_GetCamBoundsRightOffset()) {
                temp_f0_10 = Stage_GetCamBoundsRightOffset() - top_right.x;
                if (temp_f0_10 < var_f29) {
                    var_f29 = temp_f0_10;
                    var_r31 |= 8;
                }
            }
            if (top_right.y > Stage_GetCamBoundsTopOffset()) {
                temp_f0_11 = Stage_GetCamBoundsTopOffset() - top_right.y;
                if (temp_f0_11 < var_f28) {
                    var_f28 = temp_f0_11;
                    var_r31 |= 1;
                }
            }
        }
        if (!(var_r30 & 4)) {
            if (bottom_right.x < Stage_GetCamBoundsLeftOffset()) {
                temp_f0_12 = Stage_GetCamBoundsLeftOffset() - bottom_right.x;
                if (temp_f0_12 > var_f31) {
                    var_f31 = temp_f0_12;
                    var_r31 |= 4;
                }
            }
            if (bottom_right.y < Stage_GetCamBoundsBottomOffset()) {
                temp_f0_13 = Stage_GetCamBoundsBottomOffset() - bottom_right.y;
                if (temp_f0_13 > var_f30) {
                    var_f30 = temp_f0_13;
                    var_r31 |= 2;
                }
            }
        }
        if (!(var_r30 & 8)) {
            if (bottom_left.x > Stage_GetCamBoundsRightOffset()) {
                temp_f0_14 = Stage_GetCamBoundsRightOffset() - bottom_left.x;
                if (temp_f0_14 < var_f29) {
                    var_f29 = temp_f0_14;
                    var_r31 |= 8;
                }
            }
            if (bottom_left.y < Stage_GetCamBoundsBottomOffset()) {
                temp_f0_15 = Stage_GetCamBoundsBottomOffset() - bottom_left.y;
                if (temp_f0_15 > var_f30) {
                    var_f30 = temp_f0_15;
                    var_r31 |= 2;
                }
            }
        }
    }
    if (var_r31 != 0) {
        temp_r5 = var_r31 & 4;
        cam_correction.x = cm_803B73C4.x;
        cam_correction.y = cm_803B73C4.y;
        cam_correction.z = cm_803B73C4.z;
        if ((temp_r5 != 0) && (var_r31 & 8)) {
            cam_correction.x = cm_804D7E30 * (var_f31 + var_f29);
        } else if (temp_r5 != 0) {
            cam_correction.x = var_f31;
        } else if (var_r31 & 8) {
            cam_correction.x = var_f29;
        }
        temp_r3 = var_r31 & 1;
        if ((temp_r3 != 0) && (var_r31 & 2)) {
            cam_correction.y = cm_804D7E30 * (var_f30 + var_f28);
        } else if (temp_r3 != 0) {
            cam_correction.y = var_f28;
        } else if (var_r31 & 2) {
            cam_correction.y = var_f30;
        }
        cam_correction.x *= cm_804D7E04;
        cam_correction.y *= cm_804D7E04;
        cam_correction.z *= cm_804D7E04;
        lbVector_Add(&movement->target_position, (Vec3*) &cam_correction.x);
        lbVector_Add(&movement->target_interest, (Vec3*) &cam_correction.x);
    }
}

void Camera_8002B1F8(CameraMovement* movement)
{
    Vec3 vec;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    CameraBox* var_r29;
    float temp_f1;
    float temp_f1_2;
    float temp_f31;
    float* temp_r31;

    temp_r31 = &cm_80452C68.unk_2bc;
    if (cm_804D7E04 == *temp_r31) {
        return;
    }
    if ((((temp_r3 = Player_GetEntity(0), temp_r3 != NULL) &&
          (var_r29 = ftLib_80086B74(temp_r3), var_r29 != NULL) &&
          (Camera_8002928C(var_r29) != 0) &&
          (Camera_80029124(&var_r29->x1C, 0) == 0U) &&
          !ftLib_8008732C(temp_r3)) ||
         ((Player_GetPlayerCharacter(1) == CHKIND_SANDBAG) &&
          (temp_r3_2 = Player_GetEntity(1), ((temp_r3_2 == NULL) == 0)) &&
          (var_r29 = ftLib_80086B74(temp_r3_2), ((var_r29 == NULL) == 0)) &&
          (Camera_8002928C(var_r29) != 0) &&
          (Camera_80029124(&var_r29->x1C, 0) == NULL))))
    {
        lbVector_Diff(&movement->target_interest, &var_r29->x1C, &vec);
        temp_f1 = *temp_r31;
        temp_f1_2 = temp_f1 * temp_f1;
        vec.x *= temp_f1_2;
        vec.y *= temp_f1_2;
        vec.z *= temp_f1_2;
        lbVector_Add(&vec, &var_r29->x1C);
        movement->target_interest = vec;
        lbVector_Diff(&movement->target_position, &movement->target_interest,
                      &vec);
        temp_f31 = cm_80452C68.unk_2c0 * *temp_r31;
        lbVector_Normalize(&vec);
        vec.x *= temp_f31;
        vec.y *= temp_f31;
        vec.z *= temp_f31;
        lbVector_Add(&vec, &movement->target_interest);
        movement->target_position = vec;
    }
}

void Camera_80030DF8(void)
{
    cm_80452C68.translation.x = cm_80452C68.translation.y = 0;
}

bool Camera_80031154(Vec3* arg0)
{
    if (Camera_80029124(arg0, 0) == NULL) {
        return true;
    }
    return false;
}

bool Camera_8003118C(Vec3* arg0, float arg1)
{
    if (Camera_80029124(arg0, arg1) == NULL) {
        return true;
    }
    return false;
}

void Camera_80028F5C(CameraBox* subject, s32 arg1)
{
    if (subject != NULL) {
        subject->x8 = arg1;
        subject->x10.z = 0.0f;
        subject->x10.y = 0.0f;
        subject->x10.x = 0.0f;
        subject->x1C = subject->x10;
        // subject->x1C.y = subject->x10.y;
        // subject->x1C.z = subject->x10.z;
        subject->x28 = 0.0f;
        // subject->xC_b0 = subject->xC_b0 & ~0x80;
        subject->xC_b0 = subject->xC_b0 & ~0x80;
        subject->xC_b0 = subject->xC_b0 & ~0x40;
        subject->xC_b0 = subject->xC_b0 & ~0x20;
        subject->xD_fill[0] = 0;
        subject->x2C.x = -1.0f;
        subject->x2C.y = 1.0f;
        subject->x34.x = 1.0f;
        subject->x34.y = -1.0f;
        subject->x34.z = 1.0f;
        subject->x40 = subject->x2C;
        subject->x48 = subject->x34;
        // // subject->bounds.left = (f32) subject->default_bounds.left;
        // // subject->bounds.right = (f32) subject->default_bounds.right;
        // // subject->bounds.top = (f32) subject->default_bounds.top;
        // // subject->bounds.bottom = (f32) subject->default_bounds.bottom;
        // // subject->default_size = subject->size;
        // *(u32*) &subject->default_size = *(u32*) &subject->size;
        subject->x54.x = 0.0f;
        subject->x54.y = 0.0f;
        subject->x54.z = 0.0f;
        subject->x60.x = 0.0f;
        subject->x60.y = 0.0f;
        subject->x60.z = 0.0f;
    }
}

void Camera_80028F5C(CameraBox*, s32); /* static */
static s8 cm_803BCBB0[0x20] = "couldn't get CmSubject struct.\n";

CameraBox* Camera_80029044(int arg0)
{
    CameraBox* subject = cm_804D6458;

    // subject = cm_804D6458;
    if ((CameraBox*) cm_804D6458 == NULL) {
        OSReport("couldn't get CmSubject struct.\n", arg0);
    loop_2:
        goto loop_2;
    }
    cm_804D6458 = subject->prev;
    subject->next = NULL;
    if ((CameraBox*) cm_804D6460 != NULL) {
        cm_804D6468->next = subject;
    } else {
        cm_804D6460 = subject;
    }
    subject->prev = cm_804D6468;
    cm_804D6468 = subject;
    Camera_80028F5C(subject, arg0);
    return subject;
}

void Camera_800290D4(CameraBox* subject)
{
    if (subject->next != 0) {
        subject->next->prev = subject->prev;
    } else {
        cm_804D6468 = subject->prev;
    }

    if (subject->prev != 0) {
        subject->prev->next = subject->next;
    } else {
        cm_804D6460 = subject->next;
    }

    subject->prev = cm_804D6458;
    cm_804D6458 = subject;
}

static CameraUnkGlobals cm_803BCCA0;

void Camera_80029AAC(CameraBounds* bounds, CameraMovement* movement, f32 arg8)
{
    f32 temp_f0;
    f32 temp_f3;
    f32 var_f1;
    f32 var_f2;
    f32 var_f3;
    f32 var_f5;

    if (bounds->subjects != 0) {
        temp_f3 = bounds->x_max - bounds->x_min;
        temp_f0 = bounds->y_max - bounds->y_min;
        if (temp_f3 > temp_f0) {
            var_f5 = temp_f3;
        } else {
            var_f5 = temp_f0;
        }
    } else {
        var_f5 = 99999.0f;
    }
    if (var_f5 > cm_803BCCA0.x38) {
        var_f2 = cm_803BCCA0.x30;
    } else if (var_f5 < cm_803BCCA0.x34) {
        var_f2 = cm_803BCCA0.x2C;
    } else {
        var_f2 = ((cm_803BCCA0.x30 - cm_803BCCA0.x2C) *
                  ((var_f5 - cm_803BCCA0.x34) /
                   (cm_803BCCA0.x38 - cm_803BCCA0.x34))) +
                 cm_803BCCA0.x2C;
    }
    if (cm_80452C68.unk_2bc > 0.0001f) {
        var_f3 = 1.0f / cm_80452C68.unk_2bc;
    } else {
        var_f3 = 1000.0f;
    }
    var_f1 = var_f3 * (var_f2 * arg8);
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    } else if (var_f1 < 0.0001f) {
        var_f1 = 0.0001f;
    }
    movement->interest.x =
        (f32) (((movement->target_interest.x - movement->interest.x) *
                var_f1) +
               movement->interest.x);
    movement->interest.y =
        (f32) (((movement->target_interest.y - movement->interest.y) *
                var_f1) +
               movement->interest.y);
}
