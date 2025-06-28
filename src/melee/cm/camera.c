#include <placeholder.h>

#include "cm/forward.h"
#include "ft/forward.h"

#include "camera.static.h"

#include "baselib/cobj.h"
#include "baselib/gobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "cm/types.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <melee/gr/grcastle.h>
#include <melee/gr/grcorneria.h>
#include <melee/gr/grzebes.h>
#include <melee/gr/grgarden.h>
#include <melee/gr/grshrineroute.h>
#include <melee/gr/grhomerun.h>

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <baselib/controller.h>
#include <baselib/gobjplink.h>

static HSD_CObj* cm_804D6464;

void Camera_80028B9C(int n_subjects)
{
    CameraBox* cam_box;
    Vec3* interest_pos;
    Vec3* eye_pos;
    int i;

    interest_pos = &cm_803BCB64.interest->pos;
    cm_80452C68.movement.interest = *interest_pos;
    cm_80452C68.movement.target_interest = *interest_pos;
    eye_pos = &cm_803BCB64.eyepos->pos;
    cm_80452C68.movement.position = *eye_pos;
    cm_80452C68.movement.target_position = *eye_pos;
    cm_80452C68.movement.target_fov = cm_803BCB64.fov;
    cm_80452C68.movement.fov = cm_803BCB64.fov;
    cm_80452C68.movement_lerp.interest = *interest_pos;
    cm_80452C68.movement_lerp.target_interest = *interest_pos;
    cm_80452C68.movement_lerp.position = *eye_pos;
    cm_80452C68.movement_lerp.target_position = *eye_pos;
    cm_80452C68.movement_lerp.target_fov = cm_803BCB64.fov;
    cm_80452C68.movement_lerp.fov = cm_803BCB64.fov;
    cm_80452C68.background_b = 0;
    cm_80452C68.background_g = 0;
    cm_80452C68.background_r = 0;
    cm_80452C68.nearz = 0.1f;
    cm_80452C68.farz = 16384.0f;
    cm_80452C68.mode = 0;
    memzero(cm_80452C68.unk_8C, 0x224);
    cm_80452C68.unk_AC = 1.0f;
    cm_80452C68.unk_2bc = 1.0f;
    cm_80452C68.unk_2c0 = -1.0f;
    cm_80452C68.unk_398_b0 = 0;
    cm_80452C68.unk_398_b1 = 0;
    cm_80452C68.unk_398_b2 = 0;
    cm_80452C68.unk_398_b3 = 0;
    cm_80452C68.unk_398_b4 = 0;
    cm_80452C68.unk_398_b5 = 0;
    cm_80452C68.unk_398_b6_b7 = 0;
    cm_80452C68.unk_399_b0_b1 = 0;
    cm_80452C68.unk_399_b2 = 0;
    cm_80452C68.debug_mode.last_mode = cm_80452C68.mode;
    cm_80452C68.unk_399_b3 = 0;
    cm_80452C68.unk_399_b4 = 0;
    cm_80452C68.unk_399_b5 = 0;
    memzero(&cm_80452C68 + 0x380, 0x18);
    cm_80452C68.unk_399_b6 = 0;
    cm_80452C68.unk_39A_b5 = 0;
    cm_80452C68.unk_39A_b6 = 0;
    cm_80452C68.unk_39A_b7 = 0;
    cm_80452C68.gobj = NULL;
    cam_box = HSD_MemAlloc( n_subjects * sizeof(CameraBox));
    cm_804D6458 = cam_box;
    cm_804D645C = cam_box;
    memzero(cm_804D6458, n_subjects * sizeof(CameraBox));

    // link subjects
    for (i = 0; i < n_subjects; i++) {
        cm_804D645C[i].prev = &cm_804D645C[i + 1];
    }
    cm_804D645C[n_subjects - 1].prev = NULL;
    cm_804D6460 = NULL;
    cm_804D6468 = NULL;
}

void Camera_80028F5C(CameraBox* subject, s32 arg1)
{
    if (subject != NULL) {
        subject->x8 = arg1;
        subject->x10.z = 0.0f;
        subject->x10.y = 0.0f;
        subject->x10.x = 0.0f;
        subject->x1C = subject->x10;
        subject->x28 = 0.0f;
        subject->xC_b0 = false;
        subject->xC_b1 = false;
        subject->xC_b2 = false;
        subject->xE = 0;
        subject->x2C.x = -1.0f;
        subject->x2C.y = 1.0f;
        subject->x34.x = 1.0f;
        subject->x34.y = -1.0f;
        subject->x34.z = 1.0f;
        subject->x40 = subject->x2C;
        subject->x48 = subject->x34;
        subject->x54.x = 0.0f;
        subject->x54.y = 0.0f;
        subject->x54.z = 0.0f;
        subject->x60.x = 0.0f;
        subject->x60.y = 0.0f;
        subject->x60.z = 0.0f;
    }
}

CameraBox* Camera_80029020(void)
{
    return Camera_80029044(0);
}

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

u32 Camera_80029124(Vec3* arg0, s32 distance)
{
    f32 _unused;
    f32 slope;
    f32 intercept;
    f32 bounds_left;
    f32 bounds_right;
    f32 bounds_top;
    f32 bounds_bottom;
    u32 result;

    result = 0;
    Ground_801C4368(&slope, &intercept);
    slope += 1.0;

    bounds_left = Stage_GetCamBoundsLeftOffset();
    bounds_right = Stage_GetCamBoundsRightOffset();
    bounds_top = Stage_GetCamBoundsTopOffset();

    if (Stage_GetCamBoundsBottomOffset() > slope) {
        bounds_bottom = Stage_GetCamBoundsBottomOffset();
    } else {
        bounds_bottom = slope;
    }

    if (arg0->x < (bounds_left - distance)) {
        result |= 4;
    }
    if (arg0->x > (bounds_right + distance)) {
        result |= 8;
    }

    if (arg0->y > (bounds_top + distance)) {
        result |= 1;
    }
    if (arg0->y < (bounds_bottom - distance)) {
        result |= 2;
    }

    return result;
}

static inline bool cam_bound(float x)
{
    return x > 0.65f || x < 0.35f;
}

bool Camera_8002928C(CameraBox* cam)
{
    float left;
    float right;
    float bottom;
    float top;

    if (cam->x8 != 1 && !cam->xC_b1) {
        if (cam->x8 == 2) {
            if (cam->xE != 0) {
                cam->xE--;
                return false;
            }
            left = Stage_GetCamBoundsLeftOffset();
            right = Stage_GetCamBoundsRightOffset();
            top = Stage_GetCamBoundsTopOffset();
            bottom = Stage_GetCamBoundsBottomOffset();
            if (cam_bound((cam->x10.x - left) / (right - left)) ||
                cam_bound((cam->x10.y - bottom) / (top - bottom))) {
                if (cam->xC_b2) {
                    cam->xC_b2 = false;
                    cam->xE = 0x258;
                }
                return false;
            }
            cam->xE = 0;
        }
        cam->xC_b2 = true;
        return true;
    }
    return false;
}

void Camera_800293E0(void)
{
    CameraBox* curr;
    f32 temp_f0;
    f32 temp_f1;
    f32 distance;

    for (curr = cm_804D6468; curr != NULL; curr = curr->prev) {
        if (Camera_8002928C(curr) != 0) {
            temp_f1 = curr->x40.x;
            temp_f0 = curr->x2C.x;
            distance = temp_f1 - temp_f0;
            if (distance != 0.0f) {
                if (distance > 0.5f) {
                    curr->x2C.x += 0.5f;
                } else if (distance < -0.5f) {
                    curr->x2C.x -= 0.5f;
                } else {
                    curr->x2C.x = temp_f1;
                }
            }

            temp_f1 = curr->x40.y;
            temp_f0 = curr->x2C.y;
            distance = temp_f1 - temp_f0;
            if (distance != 0.0f) {
                if (distance > 0.5f) {
                    curr->x2C.y += 0.5f;
                } else if (distance < -0.5f) {
                    curr->x2C.y -= 0.5f;
                } else {
                    curr->x2C.y = temp_f1;
                }
            }

            temp_f1 = curr->x48.x;
            temp_f0 = curr->x34.x;
            distance = temp_f1 - temp_f0;
            if (distance != 0.0f) {
                if (distance > 0.5f) {
                    curr->x34.x += 0.5f;
                } else if (distance < -0.5f) {
                    curr->x34.x -= 0.5f;
                } else {
                    curr->x34.x = temp_f1;
                }
            }

            temp_f1 = curr->x48.y;
            temp_f0 = curr->x34.y;
            distance = temp_f1 - temp_f0;
            if (distance != 0.0f) {
                if (distance > 0.5f) {
                    curr->x34.y += 0.5f;
                } else if (distance < -0.5f) {
                    curr->x34.y -= 0.5f;
                } else {
                    curr->x34.y = temp_f1;
                }
            }

            temp_f1 = curr->x48.z;
            temp_f0 = curr->x34.z;
            distance = temp_f1 - temp_f0;
            if (distance != 0.0f) {
                if (distance > 0.5f) {
                    curr->x34.z += 0.5f;
                } else if (distance < -0.5f) {
                    curr->x34.z = temp_f0 - 0.5f;
                } else {
                    curr->x34.z = temp_f1;
                }
            }
        }
    }
}

/// #Camera_8002958C

void Camera_80029AAC(CameraBounds* bounds, CameraMovement* movement, f32 arg8)
{
    f32 var_f5;
    f32 var_f3;
    f32 var_f2;
    f32 var_f1;
    float dx, dy;
    CameraUnkGlobals* unk;

    if (bounds->subjects != 0) {
        float dx, dy;
        dx = bounds->x_max - bounds->x_min;
        dy = bounds->y_max - bounds->y_min;
        if (dx > dy) {
            var_f5 = dx;
        } else {
            var_f5 = dy;
        }
    } else {
        var_f5 = 99999.0f;
    }

    unk = &cm_803BCCA0;

    dx = movement->target_interest.x - movement->interest.x;
    dy = movement->target_interest.y - movement->interest.y;

    if (var_f5 > unk->x38) {
        var_f2 = unk->x30;
    } else if (var_f5 < unk->x34) {
        var_f2 = unk->x2C;
    } else {
        var_f2 = (var_f5 - unk->x34) / (unk->x38 - unk->x34)
               * (unk->x30 - unk->x2C) + unk->x2C;
    }
    if (cm_80452C68.unk_2bc > 0.0001f) {
        var_f3 = 1.0f / cm_80452C68.unk_2bc;
    } else {
        var_f3 = 1000.0f;
    }
    var_f1 = var_f2 * arg8 * var_f3;
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    } else if (var_f1 < 0.0001f) {
        var_f1 = 0.0001f;
    }

    movement->interest.x += dx * var_f1;
    movement->interest.y += dy * var_f1;
}

void Camera_80029BC4(CameraBounds* bounds, CameraMovement* movement)
{
    float cam_dist = (bounds->y_max - bounds->y_min) /
                     tanf(cm_804D7E60 * movement->target_fov);
    float x_dist =
        (bounds->x_max - bounds->x_min) /
        (cm_803BCB64.aspect * tanf(cm_804D7E60 * movement->target_fov));
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

void Camera_80029C88(CameraBounds* unused, CameraMovement* movement, f32 arg_scale)
{
    Vec3 dist;
    f32 scale;
    f32 camera_speed;

    dist.x = movement->target_position.x - movement->position.x;
    dist.y = movement->target_position.y - movement->position.y;
    dist.z = movement->target_position.z - movement->position.z;

    scale = cm_803BCCA0.x3C * arg_scale;
    if (scale > 1.0f) {
        scale = 1.0f;
    }

    movement->position.x += dist.x * scale;
    movement->position.y += dist.y * scale;
    movement->position.z += dist.z * scale;
}

/// #Camera_80029CF8

/// #Camera_8002A0C0

void Camera_8002A278(f32 x, f32 y)
{
    cm_80452C68.unk_A4 = x;
    cm_80452C68.unk_A8 = y;
}

void Camera_8002A28C(void)
{
    u8 _[16];
    s32 test;
    int i;
    int j;

    test = -1;

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 8; ++j) {
            cm_80452C68.unk_1B0[i][j] = cm_80452C68.unk_B0[i][j];
            cm_80452C68.unk_B0[i][j].type = 0;
        }
    }

    for (i = 0; i < 5; ++i) {
        if (cm_80452C68.unk_8C[i] != 0) {
            cm_80452C68.unk_8C[i] -= 1;
            test = i;
        }
    }

    if ((test != -1) && (cm_80452C68.unk_A0 != NULL) && (cm_80452C68.unk_8C[1] == 0)) {
        HSD_GObjPLink_80390228(cm_80452C68.unk_A0);
        cm_80452C68.unk_A0 = 0;
    }
}

void Camera_8002A4AC(HSD_GObj* arg0)
{
    Vec3 pos;
    HSD_CObj* cobj;
    f32 floor_y;
    PAD_STACK(8);

    cobj = GET_COBJ(arg0);
    switch (cm_80452C68.mode) {
    case 0:
    case 4:
        Camera_8002AF68(cobj, &cm_80452C68.movement);
        Camera_8002AF68(cm_804D6464, &cm_80452C68.movement_lerp);
        HSD_CObjSetNear(cobj, cm_80452C68.nearz);
        HSD_CObjSetFar(cobj, cm_80452C68.farz);
        return;
    case 5:
        Camera_8002AF68(cobj, &cm_80452C68.movement);
        HSD_CObjSetNear(cobj, cm_80452C68.nearz);
        HSD_CObjSetFar(cobj, cm_80452C68.farz);
        return;
    case 1:
        pos = cm_80452C68.movement.position;
        floor_y = -3.4028235e38f;
        switch (stage_info.internal_stage_id) {
            case CASTLE:
                floor_y = grCastle_801D0FF0();
                break;
            case CORNERIA:
                floor_y = grCorneria_801E2FCC();
                break;
            case ZEBES:
                floor_y = grZebes_801DCCC8();
                break;
            case GARDEN:
                floor_y = grGarden_80203624();
                break;
            case SHRINEROUTE:
                floor_y = grShrineRoute_802087B0();
                break;
            case HOMERUN:
                floor_y = grHomeRun_8021EF10();
                break;
        }
        if (pos.y < floor_y) {
            floor_y = -3.4028235e38f;
            switch (stage_info.internal_stage_id) {
                case CASTLE:
                    floor_y = grCastle_801D0FF0();
                    break;
                case CORNERIA:
                    floor_y = grCorneria_801E2FCC();
                    break;
                case ZEBES:
                    floor_y = grZebes_801DCCC8();
                    break;
                case GARDEN:
                    floor_y = grGarden_80203624();
                    break;
                case SHRINEROUTE:
                    floor_y = grShrineRoute_802087B0();
                    break;
                case HOMERUN:
                    floor_y = grHomeRun_8021EF10();
                    break;
            }
            pos.y = floor_y;
        }
        HSD_CObjSetFov(cobj, cm_80452C68.movement.fov);
        HSD_CObjSetInterest(cobj, &cm_80452C68.movement.interest);
        HSD_CObjSetEyePosition(cobj, &pos);
        HSD_CObjSetNear(cobj, 0.1f);
        HSD_CObjSetFar(cobj, 16384.0f);
        return;
    case 2:
    case 3:
    case 6:
        HSD_CObjSetFov(cobj, cm_80452C68.movement.fov);
        HSD_CObjSetInterest(cobj, &cm_80452C68.movement.interest);
        HSD_CObjSetEyePosition(cobj, &cm_80452C68.movement.position);
        HSD_CObjSetNear(cobj, 0.1f);
        HSD_CObjSetFar(cobj, 16384.0f);
        return;
    case 7:
        HSD_CObjSetFov(cobj, cm_80452C68.debug_mode.mode7_fov);
        HSD_CObjSetInterest(cobj, &cm_80452C68.debug_mode.mode7_int_pos);
        HSD_CObjSetEyePosition(cobj, &cm_80452C68.debug_mode.mode7_eye_pos);
        return;
    case 8:
        HSD_CObjSetFov(cobj, cm_80452C68.debug_mode.mode8_fov);
        HSD_CObjSetInterest(cobj, &cm_80452C68.debug_mode.mode8_int_pos);
        HSD_CObjSetEyePosition(cobj, &cm_80452C68.debug_mode.mode8_eye_pos);
    }
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
    temp_r27 = &cm_803BCB64.aspect;
    top_left.x *= cm_803BCB64.aspect;
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

void Camera_8002AF68(HSD_CObj* cobj, CameraMovement* movement)
{
    u8 _1[4];
    Vec3 vec;
    float eye_y_bound;
    u8 _2[4];

    HSD_CObjSetFov(cobj, movement->fov);

    vec = movement->interest;
    vec.x += cm_80452C68.translation.x;
    vec.y += cm_80452C68.translation.y;
    HSD_CObjSetInterest(cobj, &vec);

    vec = movement->position;
    vec.x += cm_80452C68.translation.x;
    vec.y += cm_80452C68.translation.y;

    eye_y_bound = -3.4028235e38f;
    switch (stage_info.internal_stage_id) {
    case CASTLE:
        eye_y_bound = grCastle_801D0FF0();
        break;
    case CORNERIA:
        eye_y_bound = grCorneria_801E2FCC();
        break;
    case ZEBES:
        eye_y_bound = grZebes_801DCCC8();
        break;
    case GARDEN:
        eye_y_bound = grGarden_80203624();
        break;
    case SHRINEROUTE:
        eye_y_bound = grShrineRoute_802087B0();
        break;
    case HOMERUN:
        eye_y_bound = grHomeRun_8021EF10();
        break;
    }
    if (vec.y < eye_y_bound) {
        vec.y = eye_y_bound;
    }
    HSD_CObjSetEyePosition(cobj, &vec);
}

void Camera_8002B0E0(void)
{
    bool singleplayer;
    f32 cstick_y;
    f32 val;
    f32 x2bc;
    u8 player_id;

    singleplayer = gm_8016B41C();
    if (singleplayer && (cm_80452C68.unk_2c0 > 0.0f)) {
        player_id = Player_GetPlayerId(0);
        cstick_y = HSD_PadCopyStatus[player_id].nml_subStickY;
        val = cstick_y;

        if (cstick_y < 0.0f) {
            cstick_y = -cstick_y;
        }

        if (cstick_y < 0.85f) {
            cstick_y = 0.0f;
            if (cm_80452C68.unk_2ba > 0) {
                cm_80452C68.unk_2ba--;
            } else {
                cstick_y = cm_803BCCA0._44[0x28];
            }
            x2bc = cm_803BCCA0._44[40];
        } else {
            cm_80452C68.unk_2ba = cm_803BCCA0._44[0x27];
        }

        // scale = cm_803BCCA0._44[36];
        cm_80452C68.unk_2bc = -(val * cm_803BCCA0._44[36] - x2bc);

        if (cm_80452C68.unk_2bc < cm_803BCCA0._44[38]) {
            cm_80452C68.unk_2bc = cm_803BCCA0._44[38];
        }
        else if (cm_80452C68.unk_2bc > cm_803BCCA0._44[37]) {
            cm_80452C68.unk_2bc = cm_803BCCA0._44[37];
        }
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
          (Camera_80029124(&var_r29->x1C, 0) == 0))))
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

/// #Camera_8002B3D4

/// #Camera_8002B694

s32 Camera_8002BA00(s32 slot, s32 arg1)
{
    if (slot == 0xA) {
        if (arg1 > 0) {
            slot = 0;
        }
        else if (arg1 < 0) {
            slot = 5;
        }
    }
    else {
        slot += arg1;
        if (slot < 0) {
            slot = 0xA;
        } else if (slot > 5) {
            slot = 0xA;
        }
    }
    if (slot == 0xA) {
        return 0xA;
    }
    if (Player_GetEntity(slot) != NULL) {
        return slot;
    }
    return Camera_8002BA00(slot, arg1);
}

void Camera_8002BAA8(f32 arg8)
{
    Vec3 vec;
    f32 sp10;
    f32 temp_f31;
    f32 var_f5;
    f32* temp_r5;
    f64 temp_f2;
    f64 temp_f2_2;
    f64 temp_f2_3;
    void* temp_r31;

    vec = cm_80452C68.unk_320;
    vec.x *= -1.0f;
    vec.y *= -1.0f;
    vec.z *= -1.0f;
    var_f5 = (vec.z * vec.z) + ((vec.x * vec.x) + (vec.y * vec.y));
    if (var_f5 > 0.0f) {
        temp_f2 = __frsqrte(var_f5);
        temp_f2_2 = 0.5 * temp_f2 * -((var_f5 * (temp_f2 * temp_f2)) - 3.0);
        temp_f2_3 = 0.5 * temp_f2_2 * -((var_f5 * (temp_f2_2 * temp_f2_2)) - 3.0);
        sp10 = var_f5 * (0.5 * temp_f2_3 * -((var_f5 * (temp_f2_3 * temp_f2_3)) - 3.0));
        var_f5 = sp10;
    }
    if (var_f5 < 1.0f) {
        vec.y = 0.0f;
        vec.x = 0.0f;
        vec.z = 1.0f;
        cm_80452C68.unk_330 = 10.0f;
    }
    cm_80452C68.unk_330 = ((arg8 * ((var_f5 * cm_803BCCA0._44[0x16]) + cm_803BCCA0._44[0x17])) + cm_80452C68.unk_330);
    if (cm_80452C68.unk_330 < cm_80452C68.unk_2F8) {
        cm_80452C68.unk_320.x = cm_80452C68.unk_2F8;
    } else if (cm_80452C68.unk_330 > cm_80452C68.unk_2FC) {
        cm_80452C68.unk_320.x = cm_80452C68.unk_2FC;
    }
    temp_f31 = cm_80452C68.unk_330;
    lbVector_Normalize(&vec);
    vec.x *= temp_f31;
    vec.y *= temp_f31;
    vec.z *= temp_f31;
    vec.x *= temp_f31 * -1;
    vec.y *= temp_f31 * -1;
    vec.z *= temp_f31 * -1;
    // temp_f0_2 = sp18 * temp_f31;
    // sp18 = temp_f0_2;
    // temp_f0_3 = sp1C * temp_f31;
    // sp1C = temp_f0_3;
    // temp_f0_4 = sp20 * temp_f31;
    // sp20 = temp_f0_4;
    // sp18 = temp_f0_2 * -1.0f;
    // sp1C = temp_f0_3 * -1.0f;
    // sp20 = temp_f0_4 * -1.0f;
    cm_80452C68.unk_320 = vec;
}

s32 Camera_8002BC78(Vec3* arg0, Vec3* arg1, Vec3* arg2)
{
    s32 var_r31 = 0;

    if (arg0->y > 0.999f) {
        var_r31 = 1;
        arg0->y = 1.0f;
        arg0->z = 0.0f;
        arg0->x = 0.0f;
        *arg1 = cm_80452C68.unk_334;
    } else if (arg0->y < -0.999f) {
        var_r31 = -1;
        arg0->y = -1.0f;
        arg0->z = 0.0f;
        arg0->x = 0.0f;
        *arg1 = cm_80452C68.unk_334;
    }
    PSVECCrossProduct(arg1, arg0, arg2);
    lbVector_Normalize(arg2);
    PSVECCrossProduct(arg0, arg2, arg1);
    lbVector_Normalize(arg1);
    return var_r31;
}

/// #Camera_8002BD88

/// #Camera_8002C010

/// #Camera_8002C1A8

/// #Camera_8002C5B4

/// #Camera_8002C908

/// #Camera_8002CB0C

/// #Camera_8002CDDC

/// #Camera_8002D318

/// #Camera_8002D85C

/// #Camera_8002DDC4

/// #Camera_8002DFE4

/// #Camera_8002E158

/// #Camera_8002E234

/// #Camera_8002E490

/// #Camera_8002E6FC

/// #Camera_8002E818

/// #Camera_8002E948

void Camera_8002EA64(Vec* arg0)
{
    f32 spC;
    s32 (*cb)(f32*);
    PAD_STACK(4);

    if (cm_80452C68.mode != 6) {
        Camera_8002FE38();
    }

    cm_80452C68.unk_341_b3_b4 = 1;
    cm_80452C68.unk_35C.vec = *arg0;
    switch (cm_80452C68.unk_341_b3_b4) {
    case 1:
        cm_80452C68.movement.target_position = cm_80452C68.unk_35C.vec;
        return;
    case 3:
        cb = cm_80452C68.unk_35C.cb;
        if (cb && cb(&spC)) {
            cm_80452C68.movement.target_position = *arg0;
        }
    case 2:
    case 0:
        return;
    }
}

/// #Camera_8002EB5C

/// #Camera_8002EC7C

/// #Camera_8002ED9C

void Camera_8002EEC8(f32 fov)
{
    if (cm_80452C68.mode != 6) {
        Camera_8002FE38();
    }
    cm_80452C68.movement.target_fov = fov;
}

/// #Camera_8002EF14

/// #Camera_8002F0E4

bool Camera_8002F260(void)
{
    return cm_80452C68.unk_341_b7;
}

/// #Camera_8002F274

void fn_8002F360(void* x)
{
    if (cm_803BCB18.callback[cm_80452C68.mode]) {
        (*cm_803BCB18.callback[cm_80452C68.mode])(x);
    }
}

void Camera_8002F3AC(void)
{
    HSD_GObj *gobj = cm_80452C68.gobj;
    PAD_STACK(1);

    if (cm_803BCB18.callback[cm_80452C68.mode] != NULL) {
        cm_803BCB18.callback[cm_80452C68.mode](gobj);
    }
    cm_80452C68.movement.position = cm_80452C68.movement.target_position;
    cm_80452C68.movement.interest = cm_80452C68.movement.target_interest;
    cm_80452C68.movement.fov = cm_80452C68.movement.target_fov;
    cm_80452C68.movement_lerp.position = cm_80452C68.movement_lerp.target_position;
    cm_80452C68.movement_lerp.interest = cm_80452C68.movement_lerp.target_interest;
    cm_80452C68.movement_lerp.fov = cm_80452C68.movement_lerp.target_fov;
}

void Camera_8002F474(void)
{
    cm_80452C68.mode = 0;
}

s32 fn_8002F488(Vec4* arg0)
{
    arg0->z = Stage_GetCamBoundsLeftOffset();
    arg0->w = Stage_GetCamBoundsRightOffset();
    arg0->x = Stage_GetCamBoundsTopOffset();
    arg0->y = Stage_GetCamBoundsBottomOffset();
    return 1;
}

/// #Camera_8002F4D4

void Camera_8002F73C(s8 arg0, s8 arg1)
{
    Camera_8002F4D4(arg0, arg1, 0);
}

void Camera_8002F760(s8 arg0, s8 arg1)
{
    Camera_8002F4D4(arg0, arg1, 1);
}

// Camera_SetModeTraining
void Camera_8002F784(s8 slot, s8 arg1)
{
    cm_80452C68.mode = 2;
    cm_80452C68.unk_2C4 = slot;
    cm_80452C68.unk_2C5 = arg1;
    cm_80452C68.pitch_offset = 0.0f;
    cm_80452C68.yaw_offset = 0.0f;
}

void Camera_8002F7AC(s8 slot)
{
    CameraBox* cam_box;
    HSD_GObj* fighter_gobj;
    f32 direction;
    f32 randf;
    f32 offset_dir;
    f64 rand_dir;

    cm_80452C68.mode = 3;
    cm_80452C68.unk_2C4 = slot;
    fighter_gobj = Player_GetEntity(cm_80452C68.unk_2C4);
    if (fighter_gobj != NULL) {
        cam_box = ftLib_80086B74(fighter_gobj);
        if (cam_box != NULL) {
            direction = cam_box->x28;
            if (direction > 0.0f) {
                offset_dir = 1.0f;
            } else if (direction < 0.0f) {
                offset_dir = -1.0f;
            } else {
                if (HSD_Randi(2) != 0) {
                    rand_dir = 1.0;
                } else {
                    rand_dir = -1.0;
                }
                offset_dir = rand_dir;
            }
            if ((4.0f * HSD_Randf()) < 1.0f) {
                offset_dir = -offset_dir;
            }

            // swing the camera towards the opposite direction
            if (offset_dir > 0.0f) {
                randf = HSD_Randf();
                cm_80452C68.yaw_offset = randf * Stage_GetCamAngleRadiansLeft();
            } else {
                randf = HSD_Randf();
                cm_80452C68.yaw_offset = randf * -Stage_GetCamAngleRadiansRight();
            }
            randf = HSD_Randf();
            // pitch between +-pi/16
            // (M_PI_8 * randf) - M_PI_16
            cm_80452C68.pitch_offset = ((cm_804D7EC8 * randf) - cm_804D7ED0);
            return;
        }
    }
    // random pitch and yaw if no player or cambox
    cm_80452C68.pitch_offset = ((cm_804D7EC8 * HSD_Randf()) - cm_804D7ED0);
    randf = HSD_Randf();
    cm_80452C68.yaw_offset = ((cm_804D7ED8 * randf) - cm_804D7EE0);
}

void Camera_8002F8F4(void)
{
    cm_80452C68.mode = 4;
}

s32 fn_8002F908(HSD_RectF32* arg0)
{
    f32 half_width;
    f32 half_height;
    f32 center_h;
    f32 center_v;

    center_h = (Stage_GetCamBoundsLeftOffset() + Stage_GetCamBoundsRightOffset()) * 0.5f;
    half_width = cm_803BCCA0._44[0x1A] * (0.5f * (Stage_GetCamBoundsRightOffset() - Stage_GetCamBoundsLeftOffset()));
    arg0->ymax = center_h + half_width;
    arg0->ymin = center_h - half_width;
    center_v = 0.5f * (Stage_GetCamBoundsTopOffset() + Stage_GetCamBoundsBottomOffset());
    half_height = cm_803BCCA0._44[0x1B] * (0.5f * (Stage_GetCamBoundsTopOffset() - Stage_GetCamBoundsBottomOffset()));
    arg0->xmin = center_v + half_height;
    arg0->xmax = center_v - half_height;
    return 1;
}

/// #Camera_8002F9E4

s32 fn_8002FBA0(HSD_RectF32* arg0)
{
    // duplicate function?? fn_8002F908
    f32 half_width;
    f32 half_height;
    f32 center_h;
    f32 center_v;

    center_h = (Stage_GetCamBoundsLeftOffset() + Stage_GetCamBoundsRightOffset()) * 0.5f;
    half_width = cm_803BCCA0._44[0x1A] * (0.5f * (Stage_GetCamBoundsRightOffset() - Stage_GetCamBoundsLeftOffset()));
    arg0->ymax = center_h + half_width;
    arg0->ymin = center_h - half_width;
    center_v = 0.5f * (Stage_GetCamBoundsTopOffset() + Stage_GetCamBoundsBottomOffset());
    half_height = cm_803BCCA0._44[0x1B] * (0.5f * (Stage_GetCamBoundsTopOffset() - Stage_GetCamBoundsBottomOffset()));
    arg0->xmin = center_v + half_height;
    arg0->xmax = center_v - half_height;
    return 1;
}

/// #Camera_8002FC7C

void Camera_8002FE38(void)
{
    cm_80452C68.mode = 6;
    cm_80452C68.unk_341_b1_b2 = 0;
    cm_80452C68.unk_341_b3_b4 = 0;
    cm_80452C68.unk_341_b5_b6 = 0;
    cm_80452C68.unk_341_b7 = 0;

    cm_80452C68.unk_350 = cm_80452C68.movement.interest;
    cm_80452C68.movement.target_interest = cm_80452C68.unk_350;
    cm_80452C68.unk_368 = cm_80452C68.movement.position;
    cm_80452C68.movement.target_position = cm_80452C68.unk_368;
    cm_80452C68.movement.target_fov = cm_80452C68.unk_374 = cm_80452C68.movement.fov;
}

/// #Camera_8002FEEC

void Camera_8003006C(void)
{
    HSD_CObj* cobj;

    if (cm_80452C68.mode != 8) {
        if (cm_80452C68.mode <= 1U) {
            cm_80452C68.debug_mode.last_mode = cm_80452C68.mode;
        }
        cm_80452C68.mode = 8;
        cobj = GET_COBJ(cm_80452C68.gobj);
        HSD_CObjGetInterest(cobj, &cm_80452C68.debug_mode.mode8_int_pos);
        HSD_CObjGetEyePosition(cobj, &cm_80452C68.debug_mode.mode8_eye_pos);
        cm_80452C68.debug_mode.mode8_fov = HSD_CObjGetFov(cobj);
    }
}


void Camera_800300F0(void)
{
    cm_80452C68.mode = cm_80453004.last_mode;
}

bool Camera_8003010C(void)
{
    if ((int) cm_80452C68.mode == 5) {
        return true;
    }
    return false;
}

bool Camera_80030130(void)
{
    if ((int) cm_80452C68.mode == 6) {
        return true;
    }
    return false;
}

bool Camera_80030154(void)
{
    if ((int) cm_80452C68.mode == 7) {
        return true;
    }
    return false;
}

bool Camera_80030178(void)
{
    if ((int) cm_80452C68.mode == 8) {
        return true;
    }
    return false;
}

Point3d* Camera_8003019C(void)
{
    return &ftLib_80086B74(Player_GetEntity(cm_80453004.ply_slot))->x1C;
}

/// #fn_800301D0

/// #Camera_800304E0

/// #Camera_80030688

void Camera_80030730(f32 arg8)
{
    cm_803BCCA0.x40 = arg8;
}

void Camera_SetBackgroundColor(u8 r, u8 g, u8 b)
{
    cm_80452C68.background_r = r;
    cm_80452C68.background_g = g;
    cm_80452C68.background_b = b;
}


GXColor Camera_80030758(void)
{
    GXColor color;

    color.r = cm_80452C68.background_r;
    color.g = cm_80452C68.background_g;
    color.b = cm_80452C68.background_b;
    return color;
}


void Camera_80030788(Vec3* arg0)
{
    *arg0 = cm_80452C68.movement.position;
}

void Camera_800307AC(Vec* arg0)
{
    *arg0 = cm_80452C68.movement.interest;
}

static inline f32 project_edge(
    f32 rot_z,
    f32 rot_x,
    Vec3 eye_pos,
    Vec3 forward
) {
    const f32 z_thresh   = cm_804D7EE8;
    const f32 dir_thresh = cm_804D7EF0;
    const f32 miss_value = 8.5070587e37f;

    if ((fabs_inline(rot_z) > z_thresh) && ((forward.z * rot_z) > dir_thresh)) {
        return -((rot_x * (eye_pos.z / rot_z)) - eye_pos.x);
    } else if (rot_x > 0.0f) {
        return 8.5070587e37f;
    } else {
        return -8.5070587e37f;
    }
}

bool Camera_800307D0(f32* left, f32* center, f32* right)
{
    HSD_CObj* cobj;
    bool var_r30;
    f32 rot_x;
    f32 aspect;
    f32 rot_z;
    f32 x;
    f32 z;
    f32 cos_half_fov;
    f32 half_fov;
    f32 sin_half_fov;
    Vec3 forward;
    Vec3 eye_pos;
    Vec3 interest_pos;

    cobj = GET_COBJ(cm_80452C68.gobj);
    aspect = HSD_CObjGetAspect(cobj);
    half_fov = (0.5 * (0.017453292f * HSD_CObjGetFov(cobj) * aspect));
    var_r30 = 1;
    HSD_CObjGetEyePosition(cobj, &eye_pos);
    HSD_CObjGetEyeVector(cobj, &forward);
    HSD_CObjGetInterest(cobj, &interest_pos);
    x = fabs_inline(forward.x);
    if (x > cm_804D7EE8) {
        z = fabs_inline(forward.z);
        if (z > cm_804D7EE8) {
            // ray casts?
            forward.x *= -1.0f;
            forward.y *= -1.0f;
            forward.z *= -1.0f;
            *center = -((forward.x * (eye_pos.z / forward.y)) - eye_pos.x);
            sin_half_fov = sinf(half_fov);
            cos_half_fov = cosf(half_fov);
            rot_x = (forward.x * cos_half_fov) + (forward.z * sin_half_fov);
            rot_z = (forward.z * cos_half_fov) - (forward.x * sin_half_fov);

            if ((fabs_inline(rot_z) > cm_804D7EE8) && ((forward.z * rot_z) > cm_804D7EF0)) {
                *left = -((rot_x * (eye_pos.z / rot_z)) - eye_pos.x);
            } else if (rot_x > cm_804D7E14) {
                *left = 8.5070587e37f;
            } else {
                *left = -8.5070587e37f;
            }

            half_fov = -half_fov;
            sin_half_fov = sinf(half_fov);
            cos_half_fov = cosf(half_fov);
            rot_x = (forward.x * cos_half_fov) + (forward.z * sin_half_fov);
            rot_z = (forward.z * cos_half_fov) - (forward.x * sin_half_fov);

            if ((fabs_inline(rot_z) > cm_804D7EE8) && ((forward.z * rot_z) > cm_804D7EF0)) {
                *right = -((rot_x * (eye_pos.z / rot_z)) - eye_pos.x);
            } else if (rot_x > 0.0f) {
                *right = 8.5070587e37f;
            } else {
                *right = -8.5070587e37f;
            }
        }
    } else {
        *left = -8.5070587e37f;
        *right = 8.5070587e37f;
        *center = 0.0f;
        var_r30 = 0;
    }
    return var_r30;
}

HSD_GObj* Camera_80030A50(void)
{
    return cm_80452C68.gobj;
}

void Camera_80030A60(bool arg0)
{
    cm_80452C68.unk_399_b3 = arg0;
}

bool Camera_80030A78(void)
{
    return cm_80452C68.unk_399_b3;
}

void Camera_80030A8C(bool arg0)
{
    cm_80452C68.unk_399_b4 = arg0;
}

void Camera_SetStageVisible(int arg0)
{
    cm_80452C68.unk_399_b5 = arg0 == 0;
}

bool Camera_80030AC4(void)
{
    return cm_80452C68.unk_399_b5 == 0;
}

void Camera_80030AE0(bool arg0)
{
    cm_80452C68.unk_399_b2 = arg0;
}

bool Camera_80030AF8(void)
{
    return cm_80452C68.unk_399_b2;
}

void Camera_80030B0C(bool arg0)
{
    cm_80452C68.unk_399_b7 = arg0;
}

bool Camera_80030B24(void)
{
    return cm_80452C68.unk_399_b7;
}

void Camera_80030B38(bool arg0)
{
    cm_80452C68.unk_39A_b0 = arg0;
}

bool Camera_80030B50(void)
{
    return cm_80452C68.unk_39A_b0;
}

void Camera_80030B64(bool arg0)
{
    cm_80452C68.unk_39A_b1 = arg0;
}

bool Camera_80030B7C(void)
{
    return cm_80452C68.unk_39A_b1;
}

void Camera_80030B90(bool arg0)
{
    cm_80452C68.unk_39A_b2 = arg0;
}

bool Camera_80030BA8(void)
{
    return cm_80452C68.unk_39A_b2;
}


// Camera_ToScreen
bool Camera_80030BBC(Point3d* arg0, S32Vec2* arg1)
{
    Point3d point;
    HSD_CObj* cobj;
    Scissor scissor;
    s32 px;
    s32 py;
    PAD_STACK(4);

    cobj = GET_COBJ(cm_80452C68.gobj);
    if (lbVector_WorldToScreen(cobj, arg0, &point, 1) == NULL) {
        return false;
    }

    if ((point.x > 2.1474836e9f) || (point.x < -2.1474836e9f) || (point.y > 2.1474836e9f) || (point.y < -2.1474836e9f)) {
        return false;
    }

    px = point.x;
    py = point.y;
    if (arg1 != NULL) {
        arg1->x = px;
        arg1->y = py;
    }
    HSD_CObjGetScissor(cobj, &scissor);
    if ((px < scissor.left) || (px >= scissor.right) || (py < scissor.top) || (py >= scissor.bottom)) {
        return false;
    }
    return true;
}

bool Camera_80030CD8(CameraBox* arg0, S32Vec2* arg1)
{
    return Camera_80030BBC(&arg0->x1C, arg1);
}

// Camera_IsSubjectOnScreen
bool Camera_80030CFC(CameraBox* cam_box, f32 tolerance)
{
    HSD_CObj* cobj;
    Point3d eye_pos;
    Point3d interest;
    Point3d sp38;
    Point3d sp20;
    f32 range;
    PAD_STACK(14);

    cobj = GET_COBJ(cm_80452C68.gobj);
    HSD_CObjGetEyePosition(cobj, &eye_pos);
    HSD_CObjGetInterest(cobj, &interest);
    if (lbVector_8000E838(&interest, &eye_pos, &cam_box->x1C, &sp38) < (cam_box->x34.z + tolerance)) {
        return 1;
    }
    lbVector_Diff(&sp38, &cam_box->x1C, &sp20);
    lbVector_Normalize(&sp20);
    range = cam_box->x34.z + tolerance;
    sp20.x *= range;
    sp20.y *= range;
    sp20.z *= range;
    lbVector_Add(&sp20, &cam_box->x1C);
    return Camera_80030BBC(&sp20, NULL);
}

void Camera_80030DE4(f32 arg8, f32 arg9)
{
    cm_80452C68.translation.x = arg8;
    cm_80452C68.translation.y = arg9;
}

void Camera_80030DF8(void)
{
    cm_80452C68.translation.x = cm_80452C68.translation.y = 0;
}

float Camera_80030E10(void)
{
    if (cm_80452C68.unk_2B8 < 1) {
        return 10000.f;
    }
    return cm_80452C68.unk_2B0;
}

void Camera_80030E34(f32 arg8)
{
    cm_80452C68.unk_AC = arg8;
}

/// #Camera_80030E44

void Camera_80031044(s32 arg0)
{
    cm_80452C68.unk_8C[arg0] = 0;
}

enum_t Camera_80031060(void)
{
    return cm_80452C68.unk_398_b6_b7;
}

void Camera_80031074(u8 arg0)
{
    cm_80452C68.unk_398_b6_b7 = arg0;
}

enum_t Camera_8003108C(void)
{
    return cm_80452C68.unk_399_b0_b1;
}

void Camera_800310A0(u8 arg0)
{
    cm_80452C68.unk_399_b0_b1 = arg0;
}

HSD_CObj* Camera_800310B8(void)
{
    HSD_CObjSetMtxDirty(cm_804D6464);
    HSD_CObjSetupViewingMtx(cm_804D6464);
    return cm_804D6464;
}

void Camera_800310E8(void)
{
    cm_80452C68.unk_398_b0 = 0;
    cm_80452C68.unk_398_b1 = 0;
    cm_80452C68.unk_398_b2 = 0;
    cm_80452C68.unk_398_b3 = 0;
    cm_80452C68.unk_398_b4 = 0;
    cm_80452C68.unk_398_b5 = 0;
}

f32 Camera_80031144(void)
{
    return cm_80452C68.unk_2bc;
}

bool Camera_80031154(Vec3* arg0)
{
    if (Camera_80029124(arg0, 0) == 0) {
        return true;
    }
    return false;
}

bool Camera_8003118C(Vec3* arg0, float arg1)
{
    if (Camera_80029124(arg0, arg1) == 0) {
        return true;
    }
    return false;
}

void Camera_800311CC(f32 arg8)
{
    cm_80452C68.farz = arg8;
}

void Camera_800311DC(f32 arg8)
{
    cm_80452C68.nearz = arg8;
}

/// #Camera_800311EC

/// #Camera_80031328

/// #Camera_800313E0
