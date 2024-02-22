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
