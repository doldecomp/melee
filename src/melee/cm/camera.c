#include "camera.static.h"

#include "platform.h"

#include <placeholder.h>

#include "baselib/cobj.h"
#include "baselib/gobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"

#include "cm/forward.h"

#include "cm/types.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

#include "ft/forward.h"

#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <baselib/controller.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <melee/gr/grcastle.h>
#include <melee/gr/grcorneria.h>
#include <melee/gr/grgarden.h>
#include <melee/gr/grhomerun.h>
#include <melee/gr/grshrineroute.h>
#include <melee/gr/grzebes.h>

/* 029AAC */ static void Camera_80029AAC(CameraBounds* bounds,
                                         CameraTransformState* transform,
                                         f32 speed);
/* 4D6464 */ static HSD_CObj* cm_804D6464;

static inline float vec_len(Vec3* offset)
{
    return sqrtf((offset->x * offset->x) + (offset->y * offset->y) +
                 (offset->z * offset->z));
}

inline BOOL abs_threshold_inline(f32 value, f32 threshold)
{
    f32 abs_value = value;
    abs_value = ABS(abs_value);
    return (abs_value > threshold) ? true : false;
}

void Camera_80028B9C(int n_subjects)
{
    CmSubject* cam_box;
    Vec3* interest_pos;
    Vec3* eye_pos;
    int i;

    interest_pos = &cm_803BCB64.interest->pos;
    cm_80452C68.transform.interest = *interest_pos;
    cm_80452C68.transform.target_interest = *interest_pos;
    eye_pos = &cm_803BCB64.eyepos->pos;
    cm_80452C68.transform.position = *eye_pos;
    cm_80452C68.transform.target_position = *eye_pos;
    cm_80452C68.transform.target_fov = cm_803BCB64.fov;
    cm_80452C68.transform.fov = cm_803BCB64.fov;
    cm_80452C68.transform_copy.interest = *interest_pos;
    cm_80452C68.transform_copy.target_interest = *interest_pos;
    cm_80452C68.transform_copy.position = *eye_pos;
    cm_80452C68.transform_copy.target_position = *eye_pos;
    cm_80452C68.transform_copy.target_fov = cm_803BCB64.fov;
    cm_80452C68.transform_copy.fov = cm_803BCB64.fov;
    cm_80452C68.background_b = 0;
    cm_80452C68.background_g = 0;
    cm_80452C68.background_r = 0;
    cm_80452C68.nearz = 0.1f;
    cm_80452C68.farz = 16384.0f;
    cm_80452C68.mode = CAMERA_STANDARD;
    memzero(cm_80452C68._8C, 0x224);
    cm_80452C68.xAC = 1.0f;
    cm_80452C68.x2BC = 1.0f;
    cm_80452C68.x2C0 = -1.0f;
    cm_80452C68.x398_b0 = 0;
    cm_80452C68.x398_b1 = 0;
    cm_80452C68.x398_b2 = 0;
    cm_80452C68.x398_b3 = 0;
    cm_80452C68.x398_b4 = 0;
    cm_80452C68.x398_b5 = 0;
    cm_80452C68.x399_b0_b1 = 0;
    cm_80452C68.x399_b2 = 0;
    cm_80453004.last_mode = cm_80452C68.mode;
    cm_80452C68.x399_b3 = 0;
    cm_80452C68.x399_b4 = 0;
    cm_80452C68.x399_b5 = 0;
    cm_80452C68.x399_b6 = 0;
    memzero(&cm_80452C68.x380, 0x18);
    cm_80452C68.x399_b7 = 0;
    cm_80452C68.x39A_b0 = 0;
    cm_80452C68.x39A_b1 = 0;
    cm_80452C68.x39A_b2 = 0;
    cm_80452C68.gobj = NULL;
    cam_box = HSD_MemAlloc(n_subjects * sizeof(CmSubject));
    cm_804D6458 = cam_box;
    cm_804D645C = cam_box;
    memzero(cm_804D6458, n_subjects * sizeof(CmSubject));

    // Link subjects
    for (i = 0; i < n_subjects - 1; i++) {
        cm_804D645C[i].prev = &cm_804D645C[i + 1];
    }
    cm_804D645C[i].prev = NULL;

    cm_804D6460 = NULL;
    cm_804D6468 = NULL;
}

void Camera_80028F5C(CmSubject* subject, s32 arg1)
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

CmSubject* Camera_80029020(void)
{
    return Camera_80029044(0);
}

CmSubject* Camera_80029044(int arg0)
{
    CmSubject* subject = cm_804D6458;

    if ((CmSubject*) cm_804D6458 == NULL) {
        OSReport("couldn't get CmSubject struct.\n", arg0);
        while (true) {
        };
    }

    cm_804D6458 = subject->prev;
    subject->next = NULL;
    if ((CmSubject*) cm_804D6460 != NULL) {
        cm_804D6468->next = subject;
    } else {
        cm_804D6460 = subject;
    }
    subject->prev = cm_804D6468;
    cm_804D6468 = subject;
    Camera_80028F5C(subject, arg0);
    return subject;
}

void Camera_800290D4(CmSubject* subject)
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

s32 Camera_80029124(Vec3* subject_pos, s32 distance)
{
    /// @todo lots of ways to match this without the padding
    u8 _PAD[4];
    s32 result;
    f32 slope;
    f32 intercept;
    f32 bounds_left;
    f32 bounds_right;
    f32 bounds_top;
    f32 bounds_bottom;

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

    if (subject_pos->x < (bounds_left - distance)) {
        result |= LEFT_BOUND;
    }
    if (subject_pos->x > (bounds_right + distance)) {
        result |= RIGHT_BOUND;
    }

    if (subject_pos->y > (bounds_top + distance)) {
        result |= TOP_BOUND;
    }
    if (subject_pos->y < (bounds_bottom - distance)) {
        result |= BOTTOM_BOUND;
    }

    return result;
}

static inline bool cam_bound(float x)
{
    return x > 0.65f || x < 0.35f;
}

bool Camera_8002928C(CmSubject* cam)
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
                cam_bound((cam->x10.y - bottom) / (top - bottom)))
            {
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
    CmSubject* curr;
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

void Camera_8002958C(CameraBounds* bounds, CameraTransformState* transform)
{
    f32 z_pos;
    f32 z_factor;
    CameraBounds* new_bounds;
    BOOL boundary_flags;
    Vec3 base_pos;
    Vec3 test_pos;
    Vec3 default_offset;
    f32 base_ground_intercept;
    f32 base_ground;
    f32 x_extent_intercept;
    f32 x_extent_ground;
    f32 alt_x_intercept;
    f32 alt_x_ground;
    f32 y_extent_intercept;
    f32 y_extent_ground;
    f32 alt_y_intercept;
    f32 alt_y_ground;
    f32 min_x;
    f32 min_y;
    f32 max_x;
    f32 max_y;
    CmSubject* subject;
    s32 subject_count;
    f32 tracking_weight;
    f32 tracking_multiplier;

    subject_count = 0;
    subject = cm_804D6468;
    for (subject = cm_804D6468; subject != 0L; subject = subject->prev) {
        if (Camera_8002928C(subject)) {
            subject_count++;
        }
    }

    new_bounds = bounds;
    if (subject_count != 0) {
        if (((u32) subject_count) < 5) {
            tracking_weight = cm_803BCB9C[subject_count];
        } else {
            tracking_weight = 1.0f;
        }
        tracking_multiplier = tracking_weight * Stage_GetCamTrackRatio();
        min_x = min_y = F32_MAX;
        max_x = max_y = -F32_MAX;

        subject_count = 0;
        subject = cm_804D6468;
        while (subject != NULL) {
            if (Camera_8002928C(subject)) {
                subject_count++;
                base_pos = subject->x10;
                test_pos = subject->x10;
                boundary_flags = Camera_80029124(&base_pos, 0);
                if (boundary_flags != 0) {
                    Ground_801C4368(&base_ground, &base_ground_intercept);
                    base_ground += 1.0;
                    if (boundary_flags & LEFT_BOUND) {
                        base_pos.x = Stage_GetCamBoundsLeftOffset();
                    }
                    if (boundary_flags & RIGHT_BOUND) {
                        base_pos.x = Stage_GetCamBoundsRightOffset();
                    }
                    if (boundary_flags & TOP_BOUND) {
                        base_pos.y = Stage_GetCamBoundsTopOffset();
                    }
                    if (boundary_flags & BOTTOM_BOUND) {
                        base_pos.y =
                            (Stage_GetCamBoundsBottomOffset() > base_ground)
                                ? (Stage_GetCamBoundsBottomOffset())
                                : (base_ground);
                    }
                }
                test_pos.x =
                    (subject->x2C.x * tracking_multiplier) + base_pos.x;
                boundary_flags = Camera_80029124(&test_pos, 0);
                if (boundary_flags != 0) {
                    Ground_801C4368(&x_extent_ground, &x_extent_intercept);
                    x_extent_ground += 1.0;
                    if (boundary_flags & LEFT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsLeftOffset();
                    }
                    if (boundary_flags & RIGHT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsRightOffset();
                    }
                    if (boundary_flags & TOP_BOUND) {
                        test_pos.y = Stage_GetCamBoundsTopOffset();
                    }
                    if (boundary_flags & BOTTOM_BOUND) {
                        test_pos.y = (Stage_GetCamBoundsBottomOffset() >
                                      x_extent_ground)
                                         ? (Stage_GetCamBoundsBottomOffset())
                                         : (x_extent_ground);
                    }
                }
                if (test_pos.x < min_x) {
                    min_x = test_pos.x;
                }
                if (test_pos.x > max_x) {
                    max_x = test_pos.x;
                }
                test_pos.x =
                    (subject->x2C.y * tracking_multiplier) + base_pos.x;
                boundary_flags = Camera_80029124(&test_pos, 0);
                if (boundary_flags != 0) {
                    Ground_801C4368(&alt_x_ground, &alt_x_intercept);
                    alt_x_ground += 1.0;
                    if (boundary_flags & LEFT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsLeftOffset();
                    }
                    if (boundary_flags & RIGHT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsRightOffset();
                    }
                    if (boundary_flags & TOP_BOUND) {
                        test_pos.y = Stage_GetCamBoundsTopOffset();
                    }
                    if (boundary_flags & BOTTOM_BOUND) {
                        test_pos.y =
                            (Stage_GetCamBoundsBottomOffset() > alt_x_ground)
                                ? (Stage_GetCamBoundsBottomOffset())
                                : (alt_x_ground);
                    }
                }
                if (test_pos.x < min_x) {
                    min_x = test_pos.x;
                }
                if (test_pos.x > max_x) {
                    max_x = test_pos.x;
                }
                test_pos.y =
                    (subject->x34.y * tracking_multiplier) + base_pos.y;
                boundary_flags = Camera_80029124(&test_pos, 0);
                if (boundary_flags != 0) {
                    Ground_801C4368(&y_extent_ground, &y_extent_intercept);
                    y_extent_ground += 1.0;
                    if (boundary_flags & LEFT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsLeftOffset();
                    }
                    if (boundary_flags & RIGHT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsRightOffset();
                    }
                    if (boundary_flags & TOP_BOUND) {
                        test_pos.y = Stage_GetCamBoundsTopOffset();
                    }
                    if (boundary_flags & BOTTOM_BOUND) {
                        test_pos.y = (Stage_GetCamBoundsBottomOffset() >
                                      y_extent_ground)
                                         ? (Stage_GetCamBoundsBottomOffset())
                                         : (y_extent_ground);
                    }
                }
                if (test_pos.y < min_y) {
                    min_y = test_pos.y;
                }
                if (test_pos.y > max_y) {
                    max_y = test_pos.y;
                }
                test_pos.y =
                    (subject->x34.x * tracking_multiplier) + base_pos.y;
                boundary_flags = Camera_80029124(&test_pos, 0);
                if (boundary_flags != 0) {
                    Ground_801C4368(&alt_y_ground, &alt_y_intercept);
                    alt_y_ground += 1.0;
                    if (boundary_flags & LEFT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsLeftOffset();
                    }
                    if (boundary_flags & RIGHT_BOUND) {
                        test_pos.x = Stage_GetCamBoundsRightOffset();
                    }
                    if (boundary_flags & TOP_BOUND) {
                        test_pos.y = Stage_GetCamBoundsTopOffset();
                    }
                    if (boundary_flags & BOTTOM_BOUND) {
                        test_pos.y =
                            (Stage_GetCamBoundsBottomOffset() > alt_y_ground)
                                ? (Stage_GetCamBoundsBottomOffset())
                                : (alt_y_ground);
                    }
                }
                if (test_pos.y < min_y) {
                    min_y = test_pos.y;
                }
                if (test_pos.y > max_y) {
                    max_y = test_pos.y;
                }
            }
            subject = subject->prev;
        }
    }
    if (subject_count == 0) {
        Stage_UnkSetVec3TCam_Offset(&default_offset);
        min_x = default_offset.x - 40.0f;
        min_y = default_offset.y - 40.0f;
        max_x = 40.0f + default_offset.x;
        max_y = 40.0f + default_offset.y;
    }
    z_pos = (transform->position.z < 0) ? (-transform->position.z)
                                        : (transform->position.z);
    if (z_pos < 80.0f) {
        z_factor = 0.0f;
    } else if (z_pos > 5000.0f) {
        z_factor = 1.0f;
    } else {
        z_factor = (z_pos - 80.0f) / 4920.0f;
    }
    new_bounds->x_min = min_x;
    new_bounds->y_min = min_y - ((390.0f * z_factor) + 10.0f);
    new_bounds->x_max = max_x;
    new_bounds->y_max = max_y;
    new_bounds->total_subjects = subject_count;
    new_bounds->z_pos = z_pos;
}

inline float get_follow_speed(float temp_f4, float spread,
                              CameraUnkGlobals* globals)
{
    if (spread > temp_f4) {
        return globals->x30;
    } else if (spread < globals->x34) {
        return globals->x2C;
    } else {
        return (((spread - globals->x34) / (temp_f4 - globals->x34)) *
                (globals->x30 - globals->x2C)) +
               globals->x2C;
    }
}

inline float get_delta(float temp_f)
{
    if (temp_f > 0.0001f) {
        return 1.0f / temp_f;
    } else {
        return 1000.0f;
    }
}

void Camera_80029AAC(CameraBounds* bounds, CameraTransformState* transform,
                     f32 speed)
{
    CameraUnkGlobals* globals;
    f32 follow_speed;
    f32 temp_f;
    f32 temp_f4;
    f32 temp_f3;
    f32 delta;
    f32 spread;
    f32 lerp_factor;
    f32 offset_x;
    f32 offset_y;

    if (bounds->total_subjects != 0) {
        temp_f4 = bounds->x_max - bounds->x_min;
        temp_f3 = bounds->y_max - bounds->y_min;
        if (temp_f4 > temp_f3) {
            spread = temp_f4;
        } else {
            spread = temp_f3;
        }
    } else {
        spread = 99999.0f;
    }
    offset_x = transform->target_interest.x - transform->interest.x;
    offset_y = transform->target_interest.y - transform->interest.y;

    globals = &cm_803BCCA0;
    /// @todo this makes it match, but its weird to pass in x38 as a param
    follow_speed = get_follow_speed(globals->x38, spread, globals);
    delta = get_delta(cm_80452C68.x2BC);

    lerp_factor = (follow_speed * speed) * delta;
    if (lerp_factor > 1.0f) {
        lerp_factor = 1.0f;
    } else if (lerp_factor < 0.0001f) {
        lerp_factor = 0.0001f;
    }

    transform->interest.x += offset_x * lerp_factor;
    transform->interest.y += offset_y * lerp_factor;
}

#pragma dont_inline on
void Camera_80029BC4(CameraBounds* bounds, CameraTransformState* transform)
{
    float cam_dist = (bounds->y_max - bounds->y_min) /
                     tanf(cm_804D7E60 * transform->target_fov);
    float x_dist =
        (bounds->x_max - bounds->x_min) /
        (cm_803BCB64.aspect * tanf(cm_804D7E60 * transform->target_fov));
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

void Camera_80029C88(CameraBounds* unused, CameraTransformState* transform,
                     f32 arg_scale)
{
    Vec3 dist;
    f32 scale;
    f32 camera_speed;

    dist.x = transform->target_position.x - transform->position.x;
    dist.y = transform->target_position.y - transform->position.y;
    dist.z = transform->target_position.z - transform->position.z;

    scale = cm_803BCCA0.x3C * arg_scale;
    if (scale > 1.0f) {
        scale = 1.0f;
    }

    transform->position.x += dist.x * scale;
    transform->position.y += dist.y * scale;
    transform->position.z += dist.z * scale;
}
#pragma dont_inline reset

inline float get_max_bounds_length(CameraBounds* bounds)
{
    f32 height;
    f32 width;
    f32 size;

    width = bounds->x_max - bounds->x_min;
    height = bounds->y_max - bounds->y_min;

    if (width > height) {
        size = width;
    } else {
        size = height;
    }

    return size;
}

void Camera_80029CF8(CameraBounds* bounds, CameraTransformState* transform)
{
    f32 len;
    Vec3 scroll_offset;
    Vec3 scroll_offset2;
    f32 min_v;
    f32 min_h;
    f32 fov_u;
    f32 fov_d;
    f32 fov_r;
    f32 fov_l;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 mid_x;
    f32 temp_f31_3;
    f32 max_h;
    f32 max_v;
    f32 var_f28;
    f32 pitch_angle;
    f32 vert_frustum_dist;
    f32 pan_angle;
    f32 var_f3;
    f32* aspect;

    Stage_UnkSetVec3TCam_Offset(&scroll_offset);
    len = get_max_bounds_length(bounds);

    if (len > cm_803BCCA0.x28) {
        var_f3 = cm_803BCCA0.x20;
    } else if (len < cm_803BCCA0.x24) {
        var_f3 = cm_803BCCA0.x1C;
    } else {
        var_f3 =
            ((cm_803BCCA0.x20 - cm_803BCCA0.x1C) *
             ((len - cm_803BCCA0.x24) / (cm_803BCCA0.x28 - cm_803BCCA0.x24))) +
            cm_803BCCA0.x1C;
    }

    max_v = deg_to_rad * cm_803BCCA0.xC;
    pitch_angle = -(deg_to_rad * (((((bounds->y_min - scroll_offset.y) +
                                     (bounds->y_max - scroll_offset.y)) *
                                    (0.5f - var_f3)) +
                                   scroll_offset.y + cm_803BCCA0.x8) *
                                  Stage_GetCamInfoX24()));
    if (pitch_angle > max_v) {
        pitch_angle = max_v;
    }

    min_v = deg_to_rad * cm_803BCCA0.x10;
    if (pitch_angle < min_v) {
        pitch_angle = min_v;
    }
    temp_f29 = pitch_angle + Stage_GetCamPanAngleRadians();

    fov_u = (0.5f * (deg_to_rad * transform->fov)) + temp_f29;
    HSD_ASSERTMSG(0x4FA, fov_u < M_PI_2, "fov_u<MTXDegToRad(90.0F)");

    fov_d = (0.5f * (deg_to_rad * transform->fov)) - temp_f29;
    HSD_ASSERTMSG(0x4FB, fov_d < M_PI_2, "fov_d<MTXDegToRad(90.0F)");

    vert_frustum_dist =
        (bounds->y_max - bounds->y_min) / (tanf(fov_u) + tanf(fov_d));
    Stage_GetCamBoundsBottomOffset();
    Stage_GetCamBoundsTopOffset();
    temp_f30 = vert_frustum_dist * tanf(temp_f29);
    transform->target_interest.y =
        temp_f30 + -((vert_frustum_dist * tanf(fov_u)) - bounds->y_max);
    Stage_UnkSetVec3TCam_Offset(&scroll_offset2);
    mid_x = 0.5f * (bounds->x_min + bounds->x_max);
    max_h = deg_to_rad * 17.5f;
    pan_angle =
        -(deg_to_rad * ((mid_x - scroll_offset2.x) * Stage_GetCamInfoX20()));
    if (pan_angle > max_h) {
        pan_angle = max_h;
    }

    min_h = deg_to_rad * -17.5f;
    if (pan_angle < min_h) {
        pan_angle = min_h;
    }

    fov_r = (0.5f * (deg_to_rad * transform->fov)) - pan_angle;
    HSD_ASSERTMSG(0x508, fov_r < M_PI_2, "fov_r<MTXDegToRad(90.0F)");
    fov_l = (0.5f * (deg_to_rad * transform->fov)) + pan_angle;
    HSD_ASSERTMSG(0x509, fov_l < M_PI_2, "fov_l<MTXDegToRad(90.0F)");

    aspect = &cm_803BCB64.aspect;
    temp_f26 = cm_803BCB64.aspect * tanf(fov_r);
    temp_f28 =
        (bounds->x_max - bounds->x_min) / (temp_f26 + (*aspect * tanf(fov_l)));
    Stage_GetCamBoundsLeftOffset();
    Stage_GetCamBoundsRightOffset();
    temp_f31_3 = *aspect * (temp_f28 * tanf(pan_angle));
    transform->target_interest.x =
        -((temp_f28 * temp_f26) - bounds->x_max) - temp_f31_3;
    transform->target_interest.z = 0.0f;

    if (vert_frustum_dist > temp_f28) {
    } else {
        vert_frustum_dist = temp_f28;
    }
    var_f28 = vert_frustum_dist;
    if (vert_frustum_dist < Stage_GetCamZoomRate()) {
        var_f28 = Stage_GetCamZoomRate();
    }
    if (var_f28 > Stage_GetCamMaxDepth()) {
        var_f28 = Stage_GetCamMaxDepth();
    }
    transform->target_position.x = transform->target_interest.x + temp_f31_3;
    transform->target_position.y = transform->target_interest.y - temp_f30;
    transform->target_position.z = transform->target_interest.z + var_f28;
}

void Camera_8002A0C0(CameraBounds* bounds, CameraTransformState* state)
{
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f5;
    f32 var_f30;
    f32 var_f31;
    f32 var_f6;

    var_f31 = cm_80452C68.xA4 * cm_80452C68.xAC * 10.0f;
    var_f30 = cm_80452C68.xA8 * cm_80452C68.xAC * 10.0f;

    /// @todo figure out how to get cm_803BCCA0 to load into r3
    if (gm_8016B41C() != 0) {
        var_f31 *= cm_803BCCA0.xE8;
        var_f30 *= cm_803BCCA0.xE8;
    }

    temp_f31 = var_f31 * cm_80452C68.x2BC;
    temp_f30 = var_f30 * cm_80452C68.x2BC;
    temp_f5 = bounds->z_pos * tanf(0.5f * (0.017453292f * state->fov));
    temp_f28 = cm_803BCB64.aspect *
               (temp_f5 / (0.5f * (f32) (cm_803BCB64.viewport.xmax -
                                         cm_803BCB64.viewport.xmin)));
    temp_f27 =
        temp_f5 /
        (0.5f * (f32) (cm_803BCB64.viewport.ymax - cm_803BCB64.viewport.ymin));
    temp_f29 = Stage_GetCamZoomRate();
    temp_f29_2 = Stage_GetCamMaxDepth() - temp_f29;

    if (temp_f29_2 < 0.001f) {
        var_f6 = 0.5f;
    } else {
        var_f6 = (bounds->z_pos - Stage_GetCamZoomRate()) / temp_f29_2;
    }

    Camera_80030DE4(
        ((var_f6 * (cm_803BCCA0.x60 - cm_803BCCA0.x58)) + cm_803BCCA0.x58) *
            (temp_f31 * temp_f28),
        ((var_f6 * (cm_803BCCA0.x5C - cm_803BCCA0.x54)) + cm_803BCCA0.x54) *
            (temp_f30 * temp_f27));
    cm_80452C68.xA4 = 0.0f;
    cm_80452C68.xA8 = 0.0f;
}

void Camera_8002A278(f32 x, f32 y)
{
    cm_80452C68.xA4 = x;
    cm_80452C68.xA8 = y;
}

void Camera_8002A28C(CameraBounds* arg0)
{
    u8 _[16];
    s32 test;
    int i;
    int j;

    test = -1;

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 8; ++j) {
            cm_80452C68._1B0[i][j] = cm_80452C68._B0[i][j];
            cm_80452C68._B0[i][j].type = 0;
        }
    }

    for (i = 0; i < 5; ++i) {
        if (cm_80452C68._8C[i] != 0) {
            cm_80452C68._8C[i] -= 1;
            test = i;
        }
    }

    if ((test != -1) && (cm_80452C68.xA0 != NULL) && (cm_80452C68._8C[1] == 0))
    {
        HSD_GObjPLink_80390228(cm_80452C68.xA0);
        cm_80452C68.xA0 = 0;
    }
}

/// @note doesnt check all stages...
// probably was a bandaid for problem stages
inline float get_stage_floor_height(InternalStageId stage_id)
{
    float height = -F32_MAX;
    switch (stage_id) {
    case CASTLE:
        height = grCastle_801D0FF0();
        break;
    case CORNERIA:
        height = grCorneria_801E2FCC();
        break;
    case ZEBES:
        height = grZebes_801DCCC8();
        break;
    case GARDEN:
        height = grGarden_80203624();
        break;
    case SHRINEROUTE:
        height = grShrineRoute_802087B0();
        break;
    case HOMERUN:
        height = grHomeRun_8021EF10();
        break;
    }
    return height;
}

void Camera_8002A4AC(HSD_GObj* gobj)
{
    f32 floor_height;
    Vec3 pos;
    HSD_CObj* cobj;
    CameraTransformState* transform = &cm_80452C68.transform;

    cobj = GET_COBJ(gobj);
    switch (cm_80452C68.mode) {
    case CAMERA_STANDARD:
    case CAMERA_FIXED:
        Camera_8002AF68(cobj, transform);
        Camera_8002AF68(cm_804D6464, &cm_80452C68.transform_copy);
        HSD_CObjSetNear(cobj, cm_80452C68.nearz);
        HSD_CObjSetFar(cobj, cm_80452C68.farz);
        break;
    case CAMERA_FREE:
        Camera_8002AF68(cobj, transform);
        HSD_CObjSetNear(cobj, cm_80452C68.nearz);
        HSD_CObjSetFar(cobj, cm_80452C68.farz);
        break;
    case CAMERA_PAUSE:
        pos = transform->position;
        floor_height = get_stage_floor_height(stage_info.internal_stage_id);
        if (pos.y < floor_height) {
            floor_height =
                get_stage_floor_height(stage_info.internal_stage_id);
            pos.y = floor_height;
        }
        HSD_CObjSetFov(cobj, transform->fov);
        HSD_CObjSetInterest(cobj, &transform->interest);
        HSD_CObjSetEyePosition(cobj, &pos);
        HSD_CObjSetNear(cobj, 0.1f);
        HSD_CObjSetFar(cobj, 16384.0f);
        break;
    case CAMERA_TRAINING_MENU:
    case CAMERA_CLEAR:
    case CAMERA_BOSS_INTRO:
        HSD_CObjSetFov(cobj, transform->fov);
        HSD_CObjSetInterest(cobj, &transform->interest);
        HSD_CObjSetEyePosition(cobj, &transform->position);
        HSD_CObjSetNear(cobj, 0.1f);
        HSD_CObjSetFar(cobj, 16384.0f);
        break;
    case CAMERA_DEBUG_FOLLOW:
        HSD_CObjSetFov(cobj, cm_80453004.follow_fov);
        HSD_CObjSetInterest(cobj, &cm_80453004.follow_eye_pos);
        HSD_CObjSetEyePosition(cobj, &cm_80453004.follow_int_pos);
        break;
    case CAMERA_DEBUG_FREE:
        HSD_CObjSetFov(cobj, cm_80453004.free_fov);
        HSD_CObjSetInterest(cobj, &cm_80453004.free_int_pos);
        HSD_CObjSetEyePosition(cobj, &cm_80453004.free_eye_pos);
    }
}

void Camera_8002A768(CameraTransformState* transform, s32 arg1)
{
    Vec3 dist;
    Vec3 forward;
    Vec3 top_left;
    Vec3 top_right;
    Vec3 bottom_right;
    Vec3 bottom_left;
    Vec3 cam_correction;
    f32 half_fov;
    f32 temp_f0;
    f32 temp_f1;
    f32 pitch_angle;
    f32 top_overlap;
    f32 right_overlap;
    f32 bottom_overlap;
    f32 left_overlap;
    enum_t var_r31;
    enum_t var_r30;

    var_r30 = var_r31 = 0;
    half_fov = 0.5f * (deg_to_rad * transform->target_fov);
    forward = cm_WorldForward;
    lbVector_Diff(&transform->target_interest, &transform->target_position,
                  &dist);
    lbVector_Normalize(&dist);
    pitch_angle = atan2f(dist.y, -dist.z);
    temp_f0 = atan2f(-dist.x, -dist.z);
    top_left = top_right = bottom_right = bottom_left = forward;
    lbVector_Rotate(&top_left, 1, half_fov);
    lbVector_Rotate(&top_left, 2, half_fov);
    top_left.x *= cm_803BCB64.aspect;
    lbVector_Normalize(&top_left);
    lbVector_Rotate(&top_left, 1, pitch_angle);
    lbVector_Rotate(&top_left, 2, temp_f0);
    if (top_left.z < -0.001f) {
        temp_f1 = -transform->target_position.z / top_left.z;
        top_left.x *= temp_f1;
        top_left.y *= temp_f1;
        top_left.z *= temp_f1;
        lbVector_Add(&top_left, &transform->target_position);
    } else {
        var_r30 |= 1;
    }
    lbVector_Rotate(&top_right, 1, half_fov);
    lbVector_Rotate(&top_right, 2, -half_fov);
    top_right.x *= cm_803BCB64.aspect;
    lbVector_Normalize(&top_right);
    lbVector_Rotate(&top_right, 1, pitch_angle);
    lbVector_Rotate(&top_right, 2, temp_f0);
    if (top_right.z < -0.001f) {
        temp_f1 = -transform->target_position.z / top_right.z;
        top_right.x *= temp_f1;
        top_right.y *= temp_f1;
        top_right.z *= temp_f1;
        lbVector_Add(&top_right, &transform->target_position);
    } else {
        var_r30 |= 2;
    }
    lbVector_Rotate(&bottom_right, 1, -half_fov);
    lbVector_Rotate(&bottom_right, 2, half_fov);
    bottom_right.x *= cm_803BCB64.aspect;
    lbVector_Normalize(&bottom_right);
    lbVector_Rotate(&bottom_right, 1, pitch_angle);
    lbVector_Rotate(&bottom_right, 2, temp_f0);
    if (bottom_right.z < -0.001f) {
        temp_f1 = -transform->target_position.z / bottom_right.z;
        bottom_right.x *= temp_f1;
        bottom_right.y *= temp_f1;
        bottom_right.z *= temp_f1;
        lbVector_Add(&bottom_right, &transform->target_position);
    } else {
        var_r30 |= 4;
    }
    lbVector_Rotate(&bottom_left, 1, -half_fov);
    lbVector_Rotate(&bottom_left, 2, -half_fov);
    bottom_left.x *= cm_803BCB64.aspect;
    lbVector_Normalize(&bottom_left);
    lbVector_Rotate(&bottom_left, 1, pitch_angle);
    lbVector_Rotate(&bottom_left, 2, temp_f0);
    if (bottom_left.z < -0.001f) {
        temp_f1 = -transform->target_position.z / bottom_left.z;
        bottom_left.x *= temp_f1;
        bottom_left.y *= temp_f1;
        bottom_left.z *= temp_f1;
        lbVector_Add(&bottom_left, &transform->target_position);
    } else {
        var_r30 |= 8;
    }

    left_overlap = bottom_overlap = right_overlap = top_overlap = 0.0f;
    if (arg1 != 0) { /// arg1 is always 0
        if (!(var_r30 & 1)) {
            if (top_left.x < Stage_GetBlastZoneLeftOffset()) {
                temp_f0 = Stage_GetBlastZoneLeftOffset() - top_left.x;
                if (temp_f0 > left_overlap) {
                    left_overlap = temp_f0;
                    var_r31 |= 4;
                }
            }
            if (top_left.y > Stage_GetBlastZoneTopOffset()) {
                temp_f1 = Stage_GetBlastZoneTopOffset() - top_left.y;
                if (temp_f1 < top_overlap) {
                    top_overlap = temp_f1;
                    var_r31 |= 1;
                }
            }
        }

        if (!(var_r30 & 2)) {
            if (top_right.x > Stage_GetBlastZoneRightOffset()) {
                temp_f0 = Stage_GetBlastZoneRightOffset() - top_right.x;
                if (temp_f0 < right_overlap) {
                    right_overlap = temp_f0;
                    var_r31 |= 8;
                }
            }
            if (top_right.y > Stage_GetBlastZoneTopOffset()) {
                temp_f0 = Stage_GetBlastZoneTopOffset() - top_right.y;
                if (temp_f0 < top_overlap) {
                    top_overlap = temp_f0;
                    var_r31 |= 1;
                }
            }
        }

        if (!(var_r30 & 4)) {
            if (bottom_right.x < Stage_GetBlastZoneLeftOffset()) {
                temp_f0 = Stage_GetBlastZoneLeftOffset() - bottom_right.x;
                if (temp_f0 > left_overlap) {
                    left_overlap = temp_f0;
                    var_r31 |= 4;
                }
            }
            if (bottom_right.y < Stage_GetBlastZoneBottomOffset()) {
                temp_f0 = Stage_GetBlastZoneBottomOffset() - bottom_right.y;
                if (temp_f0 > bottom_overlap) {
                    bottom_overlap = temp_f0;
                    var_r31 |= 2;
                }
            }
        }

        if (!(var_r30 & 8)) {
            if (bottom_left.x > Stage_GetBlastZoneRightOffset()) {
                temp_f0 = Stage_GetBlastZoneRightOffset() - bottom_left.x;
                if (temp_f0 < right_overlap) {
                    right_overlap = temp_f0;
                    var_r31 |= 8;
                }
            }
            if (bottom_left.y < Stage_GetBlastZoneBottomOffset()) {
                temp_f0 = Stage_GetBlastZoneBottomOffset() - bottom_left.y;
                if (temp_f0 > bottom_overlap) {
                    bottom_overlap = temp_f0;
                    var_r31 |= 2;
                }
            }
        }
    } else {
        if (!(var_r30 & 1)) {
            if (top_left.x < Stage_GetCamBoundsLeftOffset()) {
                temp_f0 = Stage_GetCamBoundsLeftOffset() - top_left.x;
                if (temp_f0 > left_overlap) {
                    left_overlap = temp_f0;
                    var_r31 |= 4;
                }
            }
            if (top_left.y > Stage_GetCamBoundsTopOffset()) {
                temp_f1 = Stage_GetCamBoundsTopOffset() - top_left.y;
                if (temp_f1 < top_overlap) {
                    top_overlap = temp_f1;
                    var_r31 |= 1;
                }
            }
        }

        if (!(var_r30 & 2)) {
            if (top_right.x > Stage_GetCamBoundsRightOffset()) {
                temp_f0 = Stage_GetCamBoundsRightOffset() - top_right.x;
                if (temp_f0 < right_overlap) {
                    right_overlap = temp_f0;
                    var_r31 |= 8;
                }
            }
            if (top_right.y > Stage_GetCamBoundsTopOffset()) {
                temp_f0 = Stage_GetCamBoundsTopOffset() - top_right.y;
                if (temp_f0 < top_overlap) {
                    top_overlap = temp_f0;
                    var_r31 |= 1;
                }
            }
        }

        if (!(var_r30 & 4)) {
            if (bottom_right.x < Stage_GetCamBoundsLeftOffset()) {
                temp_f0 = Stage_GetCamBoundsLeftOffset() - bottom_right.x;
                if (temp_f0 > left_overlap) {
                    left_overlap = temp_f0;
                    var_r31 |= 4;
                }
            }
            if (bottom_right.y < Stage_GetCamBoundsBottomOffset()) {
                temp_f0 = Stage_GetCamBoundsBottomOffset() - bottom_right.y;
                if (temp_f0 > bottom_overlap) {
                    bottom_overlap = temp_f0;
                    var_r31 |= 2;
                }
            }
        }

        if (!(var_r30 & 8)) {
            if (bottom_left.x > Stage_GetCamBoundsRightOffset()) {
                temp_f0 = Stage_GetCamBoundsRightOffset() - bottom_left.x;
                if (temp_f0 < right_overlap) {
                    right_overlap = temp_f0;
                    var_r31 |= 8;
                }
            }
            if (bottom_left.y < Stage_GetCamBoundsBottomOffset()) {
                temp_f0 = Stage_GetCamBoundsBottomOffset() - bottom_left.y;
                if (temp_f0 > bottom_overlap) {
                    bottom_overlap = temp_f0;
                    var_r31 |= 2;
                }
            }
        }
    }
    if (var_r31 != 0) {
        cam_correction = cm_803B73C4;
        if ((var_r31 & 4) && (var_r31 & 8)) {
            cam_correction.x = 0.5f * (left_overlap + right_overlap);
        } else if (var_r31 & 4) {
            cam_correction.x = left_overlap;
        } else if (var_r31 & 8) {
            cam_correction.x = right_overlap;
        }
        // temp_r3 = var_r31 & 1;
        if ((var_r31 & 1) && (var_r31 & 2)) {
            cam_correction.y = 0.5f * (bottom_overlap + top_overlap);
        } else if (var_r31 & 1) {
            cam_correction.y = top_overlap;
        } else if (var_r31 & 2) {
            cam_correction.y = bottom_overlap;
        }
        cam_correction.x *= -1.0f;
        cam_correction.y *= -1.0f;
        cam_correction.z *= -1.0f;
        lbVector_Add(&transform->target_position, &cam_correction);
        lbVector_Add(&transform->target_interest, &cam_correction);
    }
}

void Camera_8002AF68(HSD_CObj* cobj, CameraTransformState* transform)
{
    u8 _1[4];
    Vec3 vec;
    float eye_y_bound;
    u8 _2[4];

    HSD_CObjSetFov(cobj, transform->fov);

    vec = transform->interest;
    vec.x += cm_80452C68.translation.x;
    vec.y += cm_80452C68.translation.y;
    HSD_CObjSetInterest(cobj, &vec);

    vec = transform->position;
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
    CameraUnkGlobals* new_var2;
    f32 var_f1;
    f32 var_f2;
    f32* new_var;
    if ((gm_8016B41C() != 0) && (cm_80452C68.x2C0 > 0.0f)) {
        var_f1 =
            HSD_PadCopyStatus[Player_GetPlayerId(0) & 0xFFu].nml_subStickY;
        new_var2 = &cm_803BCCA0;
        var_f2 = var_f1;
        var_f2 = var_f1;
        if (var_f2 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1 < 0.85f) {
            var_f2 = 0.0f;
            if (((s32) cm_80452C68.x2BA) > 0) {
                cm_80452C68.x2BA = cm_80452C68.x2BA - 1;
            } else {
                var_f2 = (*new_var2).xE4;
            }
        } else {
            cm_80452C68.x2BA = (*new_var2).xE0;
        }
        cm_80452C68.x2BC = -((var_f2 * (*new_var2).xD4) - cm_80452C68.x2BC);
        if (cm_80452C68.x2BC < (*new_var2).xDC) {
            cm_80452C68.x2BC = (*new_var2).xDC;
            return;
        }
        if (cm_80452C68.x2BC > (*new_var2).xD8) {
            cm_80452C68.x2BC = (*new_var2).xD8;
        }
    }
}

void Camera_8002B1F8(CameraTransformState* transform)
{
    Vec3 vec;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    CmSubject* subject;
    float temp_f1;
    float temp_f1_2;
    float temp_f31;
    float* temp_r31;

    temp_r31 = &cm_80452C68.x2BC;
    if (cm_804D7E04 == *temp_r31) {
        return;
    }
    if ((((temp_r3 = Player_GetEntity(0), temp_r3 != NULL) &&
          (subject = ftLib_80086B74(temp_r3), subject != NULL) &&
          (Camera_8002928C(subject) != 0) &&
          (Camera_80029124(&subject->x1C, 0) == 0U) &&
          !ftLib_8008732C(temp_r3)) ||
         ((Player_GetPlayerCharacter(1) == CHKIND_SANDBAG) &&
          (temp_r3_2 = Player_GetEntity(1), ((temp_r3_2 == NULL) == 0)) &&
          (subject = ftLib_80086B74(temp_r3_2), ((subject == NULL) == 0)) &&
          (Camera_8002928C(subject) != 0) &&
          ((u32) Camera_80029124(&subject->x1C, 0) == false))))
    {
        lbVector_Diff(&transform->target_interest, &subject->x1C, &vec);
        temp_f1 = *temp_r31;
        temp_f1_2 = temp_f1 * temp_f1;
        vec.x *= temp_f1_2;
        vec.y *= temp_f1_2;
        vec.z *= temp_f1_2;
        lbVector_Add(&vec, &subject->x1C);
        transform->target_interest = vec;
        lbVector_Diff(&transform->target_position, &transform->target_interest,
                      &vec);
        temp_f31 = cm_80452C68.x2C0 * *temp_r31;
        lbVector_Normalize(&vec);
        vec.x *= temp_f31;
        vec.y *= temp_f31;
        vec.z *= temp_f31;
        lbVector_Add(&vec, &transform->target_interest);
        transform->target_position = vec;
    }
}

/// update gameplay camera
void Camera_8002B3D4(void* arg0)
{
    CameraBounds bounds;
    CameraBounds sp2C;
    Vec3 distance;
    Vec3 fighter_pos;
    float total_dist;
    HSD_GObj* p1_fgp;
    f32 temp_f31;
    f32 var_f1;
    f32 var_f1_2;
    BOOL var_r0;

    Camera_80030DF8();
    Camera_800293E0();
    Camera_8002B0E0();
    Camera_8002958C(&bounds, &cm_80452C68.transform);
    cm_80452C68.transform.target_fov = cm_803BCCA0.x40;
    total_dist = cm_80452C68.transform.target_fov - cm_80452C68.transform.fov;
    cm_80452C68.transform.fov += total_dist * cm_803BCCA0.x44;
    Camera_80029BC4(&bounds, &cm_80452C68.transform);
    if ((Camera_80030AF8() != 0) &&
        ((p1_fgp = Ground_801C57A4(), p1_fgp != NULL)))
    {
        ftLib_80086644(p1_fgp, &fighter_pos);
        /// @todo inline?
        var_f1 = fighter_pos.z;
        var_r0 = abs_threshold_inline(var_f1, 30.0f);
        // if (var_f1 < 0.0f) {
        //     var_f1 = -var_f1;
        // }
        // if (var_f1 > 30.0f) {
        //     var_r0 = 1;
        // } else {
        //     var_r0 = 0;
        // }
    }
    if (var_r0 == 0) {
        Camera_80029CF8(&bounds, &cm_80452C68.transform);
        Camera_8002A768(&cm_80452C68.transform, 0);
    }
    Camera_8002958C(&sp2C, &cm_80452C68.transform_copy);
    cm_80452C68.transform_copy.target_fov = cm_803BCCA0.x40;
    temp_f31 =
        cm_80452C68.transform_copy.target_fov - cm_80452C68.transform_copy.fov;
    cm_80452C68.transform_copy.fov += temp_f31 * cm_803BCCA0.x44;
    Camera_80029BC4(&sp2C, &cm_80452C68.transform_copy);
    if ((Camera_80030AF8() != 0) &&
        ((p1_fgp = Ground_801C57A4(), p1_fgp != NULL)))
    {
        ftLib_80086644(p1_fgp, &fighter_pos);
        var_f1_2 = fighter_pos.z;
        if (var_f1_2 < 0.0f) {
            var_f1_2 = -var_f1_2;
        }
        if (var_f1_2 > 30.0f) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
    }
    if (var_r0 == 0) {
        Camera_80029CF8(&sp2C, &cm_80452C68.transform_copy);
        Camera_8002A768(&cm_80452C68.transform_copy, 0);
    }

    /// @remarks permuter jank
    distance.y = cm_80452C68.transform.target_position.y -
                 cm_80452C68.transform.target_interest.y;
    if (cm_80452C68.x2BC == 1.0f) {
        distance.x = cm_80452C68.transform.target_position.x -
                     cm_80452C68.transform.target_interest.x;
        distance.y = cm_80452C68.transform.target_position.y -
                     cm_80452C68.transform.target_interest.y;
        distance.z = cm_80452C68.transform.target_position.z -
                     cm_80452C68.transform.target_interest.z;
        var_f1 = distance.y * distance.y;
        temp_f31 = distance.z * distance.z;
        var_f1_2 = distance.x * distance.x;
        total_dist = (var_f1_2 + var_f1) + temp_f31;
        cm_80452C68.x2C0 = sqrtf__Ff(total_dist);
    }

    Camera_8002B1F8(&cm_80452C68.transform);
    Camera_80029AAC(&bounds, &cm_80452C68.transform,
                    Stage_GetCamTrackSmooth());
    Camera_80029C88(&bounds, &cm_80452C68.transform,
                    Stage_GetCamTrackSmooth());
    Camera_80029AAC(&sp2C, &cm_80452C68.transform_copy,
                    Stage_GetCamTrackSmooth());
    Camera_80029C88(&sp2C, &cm_80452C68.transform_copy,
                    Stage_GetCamTrackSmooth());
    Camera_8002A28C(&bounds);
    Camera_8002A0C0(&bounds, &cm_80452C68.transform);

    if (((s16) cm_80452C68.x2B8) > 0x3E8) {
        cm_80452C68.x2B4 = cm_80452C68.x2B0;
        cm_80452C68.x2B8 = 1;
    }

    temp_f31 = Stage_GetCamBoundsLeftOffset();
    cm_80452C68.x2B4 += Stage_GetCamBoundsRightOffset() - temp_f31;
    cm_80452C68.x2B8 += 1;
    cm_80452C68.x2B0 = cm_80452C68.x2B4 / ((f32) cm_80452C68.x2B8);
}

inline HSD_PadStatus* get_slot_pad(u8 arg0)
{
    return &HSD_PadCopyStatus[arg0];
}

inline f32 get_stick_x(HSD_PadStatus* arg0)
{
    return arg0->nml_stickX;
}

inline f32 get_stick_y(HSD_PadStatus* arg0)
{
    return arg0->nml_stickY;
}

void Camera_8002B694(CameraInputs* inputs, s32 slot)
{
    HSD_PadStatus* pad;
    f32 stick_x;
    f32 stick_y;
    f32 substick_x;
    f32 substick_y;
    f32 temp_x;
    f32 temp_y;
    s32 var_r4;
    s32 var_r5;
    u64 temp_ret;
    PAD_STACK(8);

    if (slot == 5) {
        inputs->stick_x = 0.0f;
        inputs->stick_y = 0.0f;
        inputs->substick_x = 0.0f;
        inputs->substick_y = 0.0f;
        inputs->x18._u64 = 0;
        inputs->x10._u64 = 0;
        return;
    }
    if (slot == 4) {
        /// @todo there is probably a bigger inline
        for (var_r4 = 0; var_r4 < 4; var_r4++) {
            pad = get_slot_pad(var_r4);
            temp_x = get_stick_x(pad);
            temp_y = get_stick_y(pad);
            stick_x = temp_x;
            stick_y = temp_y;
            if (temp_x < 0.0f) {
                temp_x = -temp_x;
            }
            if (temp_x > 0.85f) {
                break;
            }
            if (temp_y < 0.0f) {
                temp_y = -temp_y;
            }
            if (temp_y > 0.85f) {
                break;
            }
        }

        if (var_r4 == 4) {
            stick_y = 0.0f;
            stick_x = 0.0f;
        }

        for (var_r5 = 0; var_r5 < 4; var_r5++) {
            pad = get_slot_pad(var_r5);
            temp_x = pad->nml_subStickX;
            temp_y = pad->nml_subStickY;
            substick_x = temp_x;
            substick_y = temp_y;
            if (temp_x < 0.0f) {
                temp_x = -temp_x;
            }
            if (temp_x > 0.85f) {
                break;
            }
            if (temp_y < 0.0f) {
                temp_y = -temp_y;
            }
            if (temp_y > 0.85f) {
                break;
            }
        }

        if (var_r5 == 4) {
            substick_y = 0.0f;
            substick_x = 0.0f;
        }
        inputs->stick_x = stick_x;
        inputs->stick_y = stick_y;
        inputs->substick_x = substick_x;
        inputs->substick_y = substick_y;
        temp_ret = gm_801A3680(4U);
        inputs->x10._u64 = temp_ret;
        temp_ret = gm_801A36A0(4U);
        inputs->x18._u64 = temp_ret;
        return;
    }
    pad = get_slot_pad(slot);
    inputs->stick_x = pad->nml_stickX;
    inputs->stick_y = pad->nml_stickY;
    inputs->substick_x = pad->nml_subStickX;
    inputs->substick_y = pad->nml_subStickY;
    temp_ret = gm_801A3680(slot);
    inputs->x10._u64 = temp_ret;
    temp_ret = gm_801A36A0(slot);
    inputs->x18._u64 = temp_ret;
}

s32 Camera_8002BA00(s32 slot, s32 arg1)
{
    if (slot == 0xA) {
        if (arg1 > 0) {
            slot = 0;
        } else if (arg1 < 0) {
            slot = 5;
        }
    } else {
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

// Camera_PauseZoom
void Camera_8002BAA8(f32 zoom_amt)
{
    Vec3 offset;
    f32 offset_len;
    f32 dist;

    offset = cm_80452C68.pause_eye_offset;
    offset.x *= -1.0F;
    offset.y *= -1.0F;
    offset.z *= -1.0F;

    offset_len = vec_len(&offset);

    if (offset_len < 1.0F) {
        offset.y = 0.0F;
        offset.x = 0.0F;
        offset.z = 1.0F;
        cm_80452C68.pause_eye_distance = 10.0F;
    }

    cm_80452C68.pause_eye_distance =
        ((zoom_amt * ((offset_len * cm_803BCCA0.x9C) + cm_803BCCA0.xA0)) +
         cm_80452C68.pause_eye_distance);

    if (cm_80452C68.pause_eye_distance < cm_80452C68.min_distance) {
        cm_80452C68.pause_eye_distance = cm_80452C68.min_distance;
    } else if (cm_80452C68.pause_eye_distance > cm_80452C68.max_distance) {
        cm_80452C68.pause_eye_distance = cm_80452C68.max_distance;
    }

    dist = cm_80452C68.pause_eye_distance;
    lbVector_Normalize(&offset);
    offset.x *= dist;
    offset.y *= dist;
    offset.z *= dist;
    offset.x *= -1.0f;
    offset.y *= -1.0f;
    offset.z *= -1.0f;

    cm_80452C68.pause_eye_offset = offset;
}

static inline void OrthonormalizeBasis(Vec3* forward, Vec3* up, Vec3* right)
{
    PSVECCrossProduct(up, forward, right);
    lbVector_Normalize(right);
    PSVECCrossProduct(forward, right, up);
    lbVector_Normalize(up);
}

s32 Camera_8002BC78(Vec3* forward, Vec3* up, Vec3* right)
{
    s32 clamp_result = 0;

    if (forward->y > 0.999f) {
        clamp_result = 1;
        forward->y = 1.0f;
        forward->z = 0.0f;
        forward->x = 0.0f;
        *up = cm_80452C68.pause_up;
    } else if (forward->y < -0.999f) {
        clamp_result = -1;
        forward->y = -1.0f;
        forward->z = 0.0f;
        forward->x = 0.0f;
        *up = cm_80452C68.pause_up;
    }
    OrthonormalizeBasis(forward, up, right);
    // PSVECCrossProduct(up, forward, right);
    // lbVector_Normalize(right);
    // PSVECCrossProduct(forward, right, up);
    // lbVector_Normalize(up);
    return clamp_result;
}

// Camera_PauseRotate
void Camera_8002BD88(f32 x, f32 y)
{
    f32 scale;
    f32 view_dir;
    s32 clamp_result;
    Vec3 up;
    Vec3 forward;
    Vec3 right;
    Vec3 pos;

    up = cm_WorldUp;
    pos = cm_80452C68.pause_eye_offset;
    forward = pos;
    forward.x *= -1.0F;
    forward.y *= -1.0F;
    forward.z *= -1.0F;
    view_dir = lbVector_Normalize(&forward);

    if (view_dir < 1.0F) {
        forward.y = 0.0F;
        forward.x = 0.0F;
        forward.z = 1.0F;
        cm_80452C68.pause_eye_distance = 10.0F;
    }

    clamp_result = Camera_8002BC78(&forward, &up, &right);
    if (clamp_result == 1) {
        if (y < 0.0F) {
            y = 0.0F;
        }
        x = 0.0F;
    } else if (clamp_result == -1) {
        if (y > 0.0F) {
            y = 0.0F;
        }
        x = 0.0F;
    }

    OrthonormalizeBasis(&forward, &up, &right);
    // PSVECCrossProduct(&up, &forward, &right);
    // lbVector_Normalize(&right);
    // PSVECCrossProduct(&forward, &right, &up);
    // lbVector_Normalize(&up);
    cm_80452C68.pause_up = up;

    if (y != 0.0F) {
        scale = y * ((view_dir * cm_803BCCA0.xBC) + cm_803BCCA0.xC0);
        // scale = y * ((view_dir * cm_803BCCA0._44[0x1E]) +
        // cm_803BCCA0._44[0x1F]);
        up.x *= scale;
        up.y *= scale;
        up.z *= scale;
        lbVector_Add(&pos, &up);
    }

    if (x != 0.0F) {
        // scale = x * ((view_dir * cm_803BCCA0._44[0x1E]) +
        // cm_803BCCA0._44[0x1F]);
        // TODO :: cant figure out how to get it to run the same logic as the y
        // case without it allocating stack space for it
        scale = x * ((view_dir * 0.025F) + 0.2F); // fake
        right.x *= -scale;
        right.y *= -scale;
        right.z *= -scale;
        lbVector_Add(&pos, &right);
    }

    scale = cm_80452C68.pause_eye_distance;
    lbVector_Normalize(&pos);
    pos.x *= scale;
    pos.y *= scale;
    pos.z *= scale;
    cm_80452C68.pause_eye_offset = pos;
}

void Camera_8002C010(f32 farg0, f32 farg1)
{
    Vec3 up;
    Vec3 forward;
    Vec3 right;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 var_f30;

    up = cm_803B73DC;
    forward = cm_80452C68.pause_eye_offset;
    forward.x *= -1.0f;
    forward.y *= -1.0f;
    forward.z *= -1.0f;
    var_f30 = lbVector_Normalize(&forward);

    if (var_f30 < 1.0f) {
        var_f30 = 1.0f;
        forward.y = 0.0f;
        forward.x = 0.0f;
        forward.z = 1.0f;
        cm_80452C68.pause_eye_distance = 1.0f;
    }

    Camera_8002BC78(&forward, &up, &right);

    if (farg1 != 0.0f) {
        temp_f1_2 = (var_f30 * cm_803BCCA0.xB4) + cm_803BCCA0.xB8;
        temp_f1 = farg1 * temp_f1_2;
        up.x *= temp_f1;
        up.y *= temp_f1;
        up.z *= temp_f1;
        lbVector_Add(&cm_80452C68.x314, &up);
    }

    if (farg0 != 0.0f) {
        /// @todo not really sure how to get the same output as the if above
        // temp_f1_2 = (var_f30 * cm_803BCCA0.xB4) + cm_803BCCA0.xB8;
        temp_f1 = -(farg0 * var_f30);
        right.x *= temp_f1;
        right.y *= temp_f1;
        right.z *= temp_f1;
        lbVector_Add(&cm_80452C68.x314, &right);
    }
}

/// #Camera_8002C1A8

/// #Camera_8002C5B4

/// #Camera_8002C908

void Camera_8002CB0C(CameraBounds* bounds)
{
    Camera* camera;
    CameraInputs inputs;
    f32 stick_x;
    f32 stick_y;
    f32 abs_f1;
    s8* x2C4_ptr;
    Vec3* x308_ptr;
    s32 dir;
    f32 x_val;
    f32 y_val;
    f32 zoom_dir;
    s32 valid;
    s32 slot;
    f32 z_init;

    camera = &cm_80452C68;

    if ((s8) camera->x2C5 == 5) {
        return;
    }

    Camera_8002B694(&inputs, (s8) camera->x2C5);

    y_val = 0.0f;
    x_val = y_val;
    zoom_dir = x_val;
    dir = 0;

    stick_x = inputs.stick_x;
    stick_y = inputs.stick_y;

    // Check 0x20 bit using 64-bit access
    if ((inputs.x18._u64 & 0x20ULL) != 0) {
        dir = 1;
    } else if ((inputs.x18._u64 & 0x40ULL) != 0) {
        dir = -1;
    }

    // Check 0x400 bit using 64-bit access
    if ((inputs.x10._u64 & 0x400ULL) != 0) {
        zoom_dir = 1.0f;
    } else if ((inputs.x10._u64 & 0x800ULL) != 0) {
        zoom_dir = -1.0f;
    }

    // Process stick_x with threshold 0.125
    if (stick_x < 0.0f) {
        abs_f1 = -stick_x;
    } else {
        abs_f1 = stick_x;
    }
    if (abs_f1 > 0.125F) {
        x_val = stick_x;
    }

    // Process stick_y with threshold 0.125
    if (stick_y < 0.0f) {
        abs_f1 = -stick_y;
    } else {
        abs_f1 = stick_y;
    }
    if (abs_f1 > 0.125F) {
        y_val = stick_y;
    }

    if (dir != 0) {
        x2C4_ptr = &camera->x2C4;

        slot = Camera_8002BA00((s8) *x2C4_ptr, dir);
        *x2C4_ptr = (s8) slot;
        x308_ptr = &camera->x308;
        goto loop_body;

    loop_top:
        slot = Camera_8002BA00((s8) *x2C4_ptr, dir);
        *x2C4_ptr = (s8) slot;

    loop_body:
        slot = (s8) *x2C4_ptr;
        valid = 1;

        if (slot == 0xB) {
            valid = 0;
        } else if (slot == 0xA) {
            Stage_UnkSetVec3TCam_Offset(x308_ptr);
        } else {
            HSD_GObj* entity = Player_GetEntity(slot);
            if (entity != NULL) {
                CmSubject* subject = ftLib_80086B74(entity);
                if (subject != NULL) {
                    x308_ptr->x = subject->x1C.x;
                    x308_ptr->y = subject->x1C.y;
                    x308_ptr->z = subject->x1C.z;
                } else {
                    valid = 0;
                }
            } else {
                valid = 0;
            }
        }

        if (valid == 0) {
            goto loop_top;
        }

        {
            HSD_GObj* entity2 = Player_GetEntity((s8) *x2C4_ptr);
            if (entity2 == NULL) {
                goto loop_top;
            }
            if (ftLib_8008701C(entity2)) {
                goto loop_top;
            }

            slot = (s8) *x2C4_ptr;
            z_init = Stage_GetPauseCamZPosInit();

            camera->x314.x = 0.0f;
            camera->x314.y = 0.0f;
            camera->x314.z = 0.0f;
            camera->pause_eye_offset.x = 0.0f;
            camera->pause_eye_offset.y = 5.0f;
            camera->pause_eye_offset.z = 20.0f;
            camera->pause_up.x = 0.0f;
            camera->pause_up.y = 1.0f;
            camera->pause_up.z = 0.0f;

            if (slot == 0xA) {
                camera->pause_eye_distance = 3.0f * z_init;
            } else {
                camera->pause_eye_distance = z_init;
            }

            Camera_8002BAA8(0.0f);
        }
    }

    if (zoom_dir != 0.0f) {
        Camera_8002BAA8(zoom_dir);
    }

    if (!(x_val == 0.0f && y_val == 0.0f)) {
        Camera_8002BD88(x_val, y_val);
    }
}

void Camera_8002CDDC(void* unused)
{
    CameraBounds bounds;  // sp+0x78
    CameraBounds bounds2; // sp+0x44
    CameraBounds bounds3; // sp+0x2C
    Vec3 sp6C;
    Vec3 sp60;
    Vec3 sp1C;                       // sp+0x1C
    Camera* cam;                     // r31
    CameraTransformState* transform; // r30
    s8* slot_ptr;                    // r29
    s32 valid;                       // r28
    Vec3* pos_ptr;                   // r27
    CmSubject* subject;              // r26
    f32 temp_f31;

    cam = &cm_80452C68;
    Camera_80030DF8();
    Camera_800293E0();
    transform = &cam->transform;
    Camera_8002958C(&bounds, transform);
    slot_ptr = &cam->x2C4;
    if (*slot_ptr == 11) {
        goto after_loop;
    }
    pos_ptr = &cam->x308;
    goto loop_check;

loop_next:
    *slot_ptr = Camera_8002BA00(*slot_ptr, 1);

loop_check: {
    s8 slot = *slot_ptr;
    if (slot == 10) {
        goto loop_next;
    }
    valid = 1;
    if (slot == 11) {
        valid = 0;
        goto check_valid;
    }
    if (slot == 10) {
        Stage_UnkSetVec3TCam_Offset(pos_ptr);
        goto check_valid;
    }
    {
        HSD_GObj* gobj = Player_GetEntity(slot);
        if (gobj == NULL) {
            goto set_invalid;
        }
        subject = ftLib_80086B74(gobj);
        if (subject == NULL) {
            goto set_invalid;
        }
        *pos_ptr = subject->x1C;
        goto check_valid;
    }
}
set_invalid:
    valid = 0;

check_valid:
    if (valid == 0) {
        goto loop_next;
    }
    {
        HSD_GObj* gobj = Player_GetEntity(*slot_ptr);
        if (gobj == NULL) {
            goto loop_next;
        }
        if (ftLib_8008701C(gobj)) {
            goto loop_next;
        }
    }

after_loop:
    Camera_8002CB0C(&bounds);
    {
        s8 slot = *slot_ptr;
        if (slot == 10) {
            goto fallback_path;
        }
        if (slot == 11) {
            goto fallback_path;
        }
    }
    {
        HSD_GObj* gobj = Player_GetEntity(*slot_ptr);
        if (gobj == NULL) {
            goto fallback_path;
        }
        subject = ftLib_80086B74(gobj);
        if (subject == NULL) {
            goto fallback_path;
        }
        if (!Camera_8002928C(subject)) {
            goto fallback_path;
        }
        if (subject->x8) {
            goto fallback_path;
        }
        if (Camera_80029124(&subject->x1C, 0) != 0) {
            goto fallback_path;
        }
        temp_f31 = subject->x1C.z;
        if (temp_f31 < 0.0f) {
            temp_f31 = -temp_f31;
        }
        if (temp_f31 >= 45.0f) {
            goto fallback_path;
        }
        // Success path
        Camera_8002C5B4(&cam->x2D0);
    }
    return;

fallback_path: {
    f32* coeff_ptr;
    f32* base_ptr;
    CameraTransformState* transform_copy;
    s32 check;

    Camera_80030DF8();
    Camera_800293E0();
    Camera_8002B0E0();
    Camera_8002958C(&bounds3, transform);

    base_ptr = &cm_803BCCA0.x40;
    coeff_ptr = &cm_803BCCA0.x44;
    temp_f31 = *base_ptr;
    Camera_80029BC4(&bounds3, transform);

    if (Camera_80030AF8()) {
        HSD_GObj* gobj = Ground_801C57A4();
        if (gobj != NULL) {
            ftLib_80086644(gobj, &sp1C);
            temp_f31 = sp1C.z;
            if (temp_f31 < 0.0f) {
                temp_f31 = -temp_f31;
            }
            if (temp_f31 >= 45.0f) {
                check = 1;
                goto check_done;
            }
        }
    }
    check = 0;
check_done:
    if (check == 0) {
        Camera_80029CF8(&bounds3, transform);
        Camera_8002A768(transform, 0);
    }

    transform_copy = &cam->transform_copy;
    Camera_8002958C(&bounds2, transform_copy);
    temp_f31 = *base_ptr;
    Camera_80029BC4(&bounds2, transform_copy);

    if (Camera_80030AF8()) {
        HSD_GObj* gobj = Ground_801C57A4();
        if (gobj != NULL) {
            ftLib_80086644(gobj, &sp60);
            temp_f31 = sp60.z;
            if (temp_f31 < 0.0f) {
                temp_f31 = -temp_f31;
            }
            if (temp_f31 >= 45.0f) {
                check = 1;
                goto check_done2;
            }
        }
    }
    check = 0;
check_done2:
    if (check == 0) {
        Camera_80029CF8(&bounds2, transform_copy);
        Camera_8002A768(transform_copy, 0);
    }
}
}
/// #Camera_8002D318

void Camera_8002D85C(void* unused)
{
    CameraBounds bounds;
    CameraBounds bounds2;
    Vec3 sp1C;
    Vec3 spC;
    Camera* cam;
    s8* slot_ptr;
    f32* pitch_ptr;
    f32* yaw_ptr;
    CmSubject* subject;
    f32 distance;
    CameraTransformState* transform;
    CameraTransformState* transform2;
    f32* tgt_fov_ptr;
    f32* smooth_ptr;
    HSD_GObj* gobj;
    s8 slot;
    f32 z_val;
    s16* count_ptr;
    f32 left_off;
    s32 check_result;

    cam = &cm_80452C68;
    slot_ptr = &cam->x2C4;
    gobj = Player_GetEntity(*slot_ptr);
    if (gobj == NULL) {
        goto fallback;
    }
    subject = ftLib_80086B74(gobj);
    if (subject == NULL) {
        goto fallback;
    }
    if ((u32) Camera_80029124(&subject->x1C, 0) != 0) {
        goto fallback;
    }
    z_val = subject->x1C.z;
    if (z_val < 0.0f) {
        z_val = -z_val;
    }
    if (!(z_val < 30.0f)) {
        goto fallback;
    }

    Camera_80030DF8();
    gobj = Player_GetEntity(*slot_ptr);
    if (gobj != NULL) {
        subject = ftLib_80086B74(gobj);
        if (subject != NULL) {
            CmSubject* subj;
            CameraUnkGlobals* globals;
            f32 smooth;
            f32 x, dx;
            f32 y, dy;
            f32 z, dz;

            x = subject->x1C.x;
            subj = (CmSubject*) ((u8*) subject + 0x1C);
            globals = &cm_803BCCA0;
            cam->transform.target_interest.x = x;
            y = ((Vec3*) subj)->y;
            cam->transform.target_interest.y = y;
            z = ((Vec3*) subj)->z;
            cam->transform.target_interest.z = z;

            x = cam->transform.target_interest.x;
            y = cam->transform.target_interest.y;
            smooth = globals->x64;
            dx = x - cam->transform.interest.x;
            z = cam->transform.target_interest.z;
            dy = y - cam->transform.interest.y;
            dz = z - cam->transform.interest.z;
            cam->transform.interest.x =
                dx * smooth + cam->transform.interest.x;
            cam->transform.interest.y =
                dy * smooth + cam->transform.interest.y;
            cam->transform.interest.z =
                dz * smooth + cam->transform.interest.z;
        }
    }

    {
        CameraUnkGlobals* globals;
        f32 smooth;
        f32 delta;

        globals = &cm_803BCCA0;
        tgt_fov_ptr = &cam->transform.target_fov;
        *tgt_fov_ptr = globals->x6C;
        delta = *tgt_fov_ptr - cam->transform.fov;
        smooth = globals->x70;
        cam->transform.fov = delta * smooth + cam->transform.fov;
    }

    slot = *slot_ptr;
    if (slot == 0xA) {
        goto skip_fov_calc;
    }
    if (slot == 0xB) {
        goto skip_fov_calc;
    }
    if (slot < 0) {
        goto skip_fov_calc;
    }
    if (slot >= 6) {
        goto skip_fov_calc;
    }
    gobj = Player_GetEntity(slot);
    if (gobj == NULL) {
        goto skip_fov_calc;
    }
    subject = ftLib_80086B74(gobj);
    if (subject == NULL) {
        goto skip_fov_calc;
    }
    distance = (2.0f * subject->x34.z) / tanf(cm_804D7E60 * *tgt_fov_ptr);
    goto fov_done;
skip_fov_calc:
    distance = cm_804D7E5C;
fov_done:

    pitch_ptr = &cam->pitch_offset;
    if (*pitch_ptr > Stage_GetCamAngleRadiansUp()) {
        *pitch_ptr = Stage_GetCamAngleRadiansUp();
    } else if (*pitch_ptr < -Stage_GetCamAngleRadiansDown()) {
        *pitch_ptr = -Stage_GetCamAngleRadiansDown();
    }

    yaw_ptr = &cam->yaw_offset;
    if (*yaw_ptr > Stage_GetCamAngleRadiansLeft()) {
        *yaw_ptr = Stage_GetCamAngleRadiansLeft();
    } else if (*yaw_ptr < -Stage_GetCamAngleRadiansRight()) {
        *yaw_ptr = -Stage_GetCamAngleRadiansRight();
    }

    {
        f32 cos_pitch = cosf(*pitch_ptr);
        f32 sin_yaw = sinf(*yaw_ptr);
        cam->transform.target_position.x =
            cam->transform.target_interest.x + distance * cos_pitch * sin_yaw;
    }
    {
        f32 sin_pitch = sinf(*pitch_ptr);
        cam->transform.target_position.y =
            cam->transform.target_interest.y + distance * sin_pitch;
    }
    {
        f32 cos_pitch = cosf(*pitch_ptr);
        f32 cos_yaw = cosf(*yaw_ptr);
        cam->transform.target_position.z =
            cam->transform.target_interest.z + distance * cos_pitch * cos_yaw;
    }

    {
        CameraUnkGlobals* globals;
        f32 smooth;
        f32 x, y, z;

        x = cam->transform.target_position.x;
        globals = &cm_803BCCA0;
        y = cam->transform.target_position.y;
        z = cam->transform.target_position.z;
        smooth = globals->x68;
        cam->transform.position.x = (x - cam->transform.position.x) * smooth +
                                    cam->transform.position.x;
        cam->transform.position.y = (y - cam->transform.position.y) * smooth +
                                    cam->transform.position.y;
        cam->transform.position.z = (z - cam->transform.position.z) * smooth +
                                    cam->transform.position.z;
    }
    return;

fallback: {
    CameraUnkGlobals* globals;
    f32 smooth;
    f32 x, y, z;

    Camera_80030DF8();
    Camera_800293E0();
    Camera_8002B0E0();
    transform = &cam->transform;
    Camera_8002958C(&bounds, transform);
    globals = &cm_803BCCA0;
    smooth_ptr = &globals->x44;
    cam->transform.target_fov = globals->x40;
    cam->transform.fov =
        (cam->transform.target_fov - cam->transform.fov) * *smooth_ptr +
        cam->transform.fov;
    Camera_80029BC4(&bounds, transform);

    check_result = 0;
    if (Camera_80030AF8()) {
        gobj = Ground_801C57A4();
        if (gobj != NULL) {
            ftLib_80086644(gobj, &sp1C);
            z_val = sp1C.z;
            if (z_val < 0.0f) {
                z_val = -z_val;
            }
            if (z_val > 30.0f) {
                check_result = 1;
            }
        }
    }
    if (!check_result) {
        Camera_80029CF8(&bounds, transform);
        Camera_8002A768(transform, 0);
    }

    transform2 = &cam->transform_copy;
    Camera_8002958C(&bounds2, transform2);
    cam->transform_copy.target_fov = globals->x40;
    cam->transform_copy.fov =
        (cam->transform_copy.target_fov - cam->transform_copy.fov) *
            *smooth_ptr +
        cam->transform_copy.fov;
    Camera_80029BC4(&bounds2, transform2);

    check_result = 0;
    if (Camera_80030AF8()) {
        gobj = Ground_801C57A4();
        if (gobj != NULL) {
            ftLib_80086644(gobj, &spC);
            z_val = spC.z;
            if (z_val < 0.0f) {
                z_val = -z_val;
            }
            if (z_val > 30.0f) {
                check_result = 1;
            }
        }
    }
    if (!check_result) {
        Camera_80029CF8(&bounds2, transform2);
        Camera_8002A768(transform2, 0);
    }

    if (cam->x2BC == 1.0f) {
        x = cam->transform.target_position.x -
            cam->transform.target_interest.x;
        y = cam->transform.target_position.y -
            cam->transform.target_interest.y;
        z = cam->transform.target_position.z -
            cam->transform.target_interest.z;
        cam->x2C0 = sqrtf(x * x + y * y + z * z);
    }

    Camera_8002B1F8(transform);
    smooth = Stage_GetCamTrackSmooth();
    Camera_80029AAC(&bounds, transform, smooth);
    smooth = Stage_GetCamTrackSmooth();
    Camera_80029C88(&bounds, transform, smooth);
    smooth = Stage_GetCamTrackSmooth();
    Camera_80029AAC(&bounds2, transform2, smooth);
    smooth = Stage_GetCamTrackSmooth();
    Camera_80029C88(&bounds2, transform2, smooth);
    Camera_8002A28C(&bounds);
    Camera_8002A0C0(&bounds, transform);

    count_ptr = &cam->x2B8;
    if (*count_ptr > 1000) {
        cam->x2B4 = cam->x2B0;
        *count_ptr = 1;
    }
    left_off = Stage_GetCamBoundsLeftOffset();
    cam->x2B4 += Stage_GetCamBoundsRightOffset() - left_off;
    (*count_ptr)++;
    cam->x2B0 = cam->x2B4 / (f32) *count_ptr;
}
}
void Camera_8002DDC4(void* arg0)
{
    CameraBounds bounds;
    Vec3 spC;
    Vec3* target_pos;
    Vec3* target_interest;
    f32 temp_f1_3;

    Camera_80030DF8();
    target_interest = &cm_80452C68.transform.target_interest;
    Stage_80224CAC(target_interest);
    cm_80452C68.transform.interest.x +=
        (cm_80452C68.transform.target_interest.x -
         cm_80452C68.transform.interest.x) *
        cm_803BCCA0.x74;
    cm_80452C68.transform.interest.y +=
        (cm_80452C68.transform.target_interest.y -
         cm_80452C68.transform.interest.y) *
        cm_803BCCA0.x74;
    cm_80452C68.transform.interest.z +=
        (cm_80452C68.transform.target_interest.z -
         cm_80452C68.transform.interest.z) *
        cm_803BCCA0.x74;
    Stage_80224CAC(&cm_80452C68.transform_copy.target_interest);
    cm_80452C68.transform_copy.interest.x +=
        (cm_80452C68.transform_copy.target_interest.x -
         cm_80452C68.transform_copy.interest.x) *
        cm_803BCCA0.x74;
    cm_80452C68.transform_copy.interest.y +=
        (cm_80452C68.transform_copy.target_interest.y -
         cm_80452C68.transform_copy.interest.y) *
        cm_803BCCA0.x74;
    cm_80452C68.transform_copy.interest.z +=
        (cm_80452C68.transform_copy.target_interest.z -
         cm_80452C68.transform_copy.interest.z) *
        cm_803BCCA0.x74;
    cm_80452C68.transform.target_fov = Stage_GetCamFixedFov();
    cm_80452C68.transform.fov +=
        (cm_80452C68.transform.target_fov - cm_80452C68.transform.fov) *
        cm_803BCCA0.x7C;
    cm_80452C68.transform_copy.target_fov = Stage_GetCamFixedFov();
    target_pos = &cm_80452C68.transform.target_position;
    cm_80452C68.transform_copy.fov += (cm_80452C68.transform_copy.target_fov -
                                       cm_80452C68.transform_copy.fov) *
                                      cm_803BCCA0.x7C;
    Stage_SetVecToFixedCamPos(target_pos);
    cm_80452C68.transform.position.x +=
        (cm_80452C68.transform.target_position.x -
         cm_80452C68.transform.position.x) *
        cm_803BCCA0.x78;
    cm_80452C68.transform.position.y +=
        (cm_80452C68.transform.target_position.y -
         cm_80452C68.transform.position.y) *
        cm_803BCCA0.x78;
    cm_80452C68.transform.position.z +=
        (cm_80452C68.transform.target_position.z -
         cm_80452C68.transform.position.z) *
        cm_803BCCA0.x78;
    Stage_SetVecToFixedCamPos(&cm_80452C68.transform_copy.target_position);
    cm_80452C68.transform_copy.position.x +=
        (cm_80452C68.transform_copy.target_position.x -
         cm_80452C68.transform_copy.position.x) *
        cm_803BCCA0.x78;
    cm_80452C68.transform_copy.position.y +=
        (cm_80452C68.transform_copy.target_position.y -
         cm_80452C68.transform_copy.position.y) *
        cm_803BCCA0.x78;
    cm_80452C68.transform_copy.position.z +=
        (cm_80452C68.transform_copy.target_position.z -
         cm_80452C68.transform_copy.position.z) *
        cm_803BCCA0.x78;
    lbVector_Diff(target_interest, target_pos, &spC);
    temp_f1_3 = spC.x;
    bounds.z_pos = sqrtf__Ff((spC.z * spC.z) +
                             ((temp_f1_3 * temp_f1_3) + (spC.y * spC.y)));
    Camera_8002A28C(&bounds);
    Camera_8002A0C0(&bounds, &cm_80452C68.transform);
}

s32 Camera_8002DFE4(Vec3* arg0, Vec3* interest,
                    CameraTransformState* transform)
{
    Vec3 sp14;
    f32 var_f31;
    s32 var_r31;

    var_r31 = 0;
    switch (cm_80452C68.x341_b5_b6) {
    case 0:
        var_r31 = 1;
        break;
    case 1:
        if (cm_80452C68.x378.s32 == cm_80452C68.x37C) {
            var_r31 = 1;
        } else {
            var_f31 = cm_80452C68.x378.s32 / (f32) cm_80452C68.x37C;
        }
        break;
    case 2:
        if (cm_80452C68.x378.f32 >= 1.0f) {
            var_r31 = 1;
        } else {
            var_f31 = cm_80452C68.x378.f32;
        }
        break;
    }
    if (var_r31 != 0) {
        transform->interest = *interest;

    } else {
        lbVector_Diff(interest, arg0, &sp14);
        sp14.x *= var_f31;
        sp14.y *= var_f31;
        sp14.z *= var_f31;
        lbVector_Add(&sp14, arg0);
        transform->interest = sp14;
    }
    return var_r31;
}

s32 Camera_8002E158(f32* arg0, f32 farg0, f32 farg1, f32 farg2)
{
    s32 var_r6;
    f32 var_f4;

    var_r6 = 0;
    switch (cm_80452C68.x341_b5_b6) {
    case 0:
        var_r6 = 1;
        break;

    case 1:
        if (cm_80452C68.x378.s32 == cm_80452C68.x37C) {
            var_r6 = 1;
        } else {
            var_f4 = cm_80452C68.x378.s32 / (f32) cm_80452C68.x37C;
        }
        break;

    case 2:
        if (cm_80452C68.x378.f32 >= 1.0f) {
            var_r6 = 1;
        } else {
            var_f4 = cm_80452C68.x378.f32;
        }
        break;
    }

    if (var_r6 != 0) {
        *arg0 = farg1;
    } else {
        *arg0 = (var_f4 * (farg1 - farg0)) + farg0;
    }

    return var_r6;
}

/// #Camera_8002E234

/// #Camera_8002E490

void Camera_8002E6FC(int arg0)
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    cm_80452C68.x341_b1_b2 = 1;
    cm_80452C68.x344.s32 = arg0;

    switch (cm_80452C68.x341_b1_b2) {
    case 1: {
        HSD_GObj* gobj = Player_GetEntity(cm_80452C68.x344.s32);
        if (gobj != NULL) {
            CmSubject* subject = ftLib_80086B74(gobj);
            if (subject != NULL) {
                cm_80452C68.transform.target_interest = subject->x1C;
            }
        }
        break;
    }
    case 2:
        cm_80452C68.transform.target_interest = cm_80452C68.x344.vec;
        break;
    case 3: {
        if (cm_80452C68.x344.cb != NULL && cm_80452C68.x344.cb(&spC)) {
            cm_80452C68.transform.target_interest = spC;
        }
        break;
    }
    case 0:
    default:
        break;
    }
}

void Camera_8002E818(Vec3* pos)
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    cm_80452C68.x341_b1_b2 = 2;
    cm_80452C68.x344.vec = *pos;

    switch (cm_80452C68.x341_b1_b2) {
    case 1: {
        HSD_GObj* gobj = Player_GetEntity(cm_80452C68.x344.s32);
        if (gobj != NULL) {
            CmSubject* subject = ftLib_80086B74(gobj);
            if (subject != NULL) {
                cm_80452C68.transform.target_interest = subject->x1C;
            }
        }
        break;
    }
    case 2:
        cm_80452C68.transform.target_interest = cm_80452C68.x344.vec;
        break;
    case 3: {
        if (cm_80452C68.x344.cb != NULL && cm_80452C68.x344.cb(&spC)) {
            cm_80452C68.transform.target_interest = spC;
        }
        break;
    }
    case 0:
    default:
        break;
    }
}

void Camera_8002E948(bool (*cb)(Vec*))
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    cm_80452C68.x341_b1_b2 = 3;
    cm_80452C68.x344.cb = (s32 (*)(Vec3*)) cb;

    switch (cm_80452C68.x341_b1_b2) {
    case 1: {
        HSD_GObj* gobj = Player_GetEntity(cm_80452C68.x344.s32);
        if (gobj != NULL) {
            CmSubject* subject = ftLib_80086B74(gobj);
            if (subject != NULL) {
                cm_80452C68.transform.target_interest = subject->x1C;
            }
        }
        break;
    }
    case 2:
        cm_80452C68.transform.target_interest = cm_80452C68.x344.vec;
        break;
    case 3: {
        if (cm_80452C68.x344.cb != NULL && cm_80452C68.x344.cb(&spC)) {
            cm_80452C68.transform.target_interest = spC;
        }
        break;
    }
    case 0:
    default:
        break;
    }
}

void Camera_8002EA64(Vec* arg0)
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    cm_80452C68.x341_b3_b4 = 1;
    cm_80452C68.x35C.vec = *arg0;
    switch (cm_80452C68.x341_b3_b4) {
    case 1:
        cm_80452C68.transform.target_position = cm_80452C68.x35C.vec;
        return;
    case 3:
        if (cm_80452C68.x35C.cb && cm_80452C68.x35C.cb(&spC)) {
            cm_80452C68.transform.target_position = spC;
        }
    case 2:
    case 0:
        return;
    }
}

void Camera_8002EB5C(float arg0)
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    if (cm_80452C68.x341_b3_b4 != 2) {
        cm_80452C68.x341_b3_b4 = 2;
        cm_80452C68.x35C.bits.b0 = 0;
        cm_80452C68.x35C.bits.b2 = 0;
    }

    cm_80452C68.x35C.vec.y = arg0;
    cm_80452C68.x35C.bits.b1 = 1;

    switch (cm_80452C68.x341_b3_b4) {
    case 1:
        cm_80452C68.transform.target_position = cm_80452C68.x35C.vec;
        break;
    case 3:
        if (cm_80452C68.x35C.cb != NULL && cm_80452C68.x35C.cb(&spC)) {
            cm_80452C68.transform.target_position = spC;
        }
        break;
    case 2:
    case 0:
    default:
        break;
    }
}

void Camera_8002EC7C(float arg0)
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    if (cm_80452C68.x341_b3_b4 != 2) {
        cm_80452C68.x341_b3_b4 = 2;
        cm_80452C68.x35C.bits.b0 = 0;
        cm_80452C68.x35C.bits.b1 = 0;
    }

    cm_80452C68.x35C.vec.z = arg0;
    cm_80452C68.x35C.bits.b2 = 1;

    switch (cm_80452C68.x341_b3_b4) {
    case 1:
        cm_80452C68.transform.target_position = cm_80452C68.x35C.vec;
        break;
    case 3:
        if (cm_80452C68.x35C.cb != NULL && cm_80452C68.x35C.cb(&spC)) {
            cm_80452C68.transform.target_position = spC;
        }
        break;
    case 2:
    case 0:
    default:
        break;
    }
}

void Camera_8002ED9C(float arg0)
{
    Vec3 spC;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    if (cm_80452C68.x341_b3_b4 != 2) {
        cm_80452C68.x341_b3_b4 = 2;
        cm_80452C68.x35C.bits.b1 = 0;
        cm_80452C68.x35C.bits.b2 = 0;
    }

    cm_80452C68.x35C.bits.x2 = arg0;
    cm_80452C68.x35C.bits.b0 = 1;

    switch (cm_80452C68.x341_b3_b4) {
    case 1:
        cm_80452C68.transform.target_position = cm_80452C68.x35C.vec;
        break;
    case 3:
        if (cm_80452C68.x35C.cb != NULL && cm_80452C68.x35C.cb(&spC)) {
            cm_80452C68.transform.target_position = spC;
        }
        break;
    case 2:
    case 0:
    default:
        break;
    }
}

void Camera_8002EEC8(f32 fov)
{
    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }
    cm_80452C68.transform.target_fov = fov;
}

/// #Camera_8002EF14

/// #Camera_8002F0E4

bool Camera_8002F260(void)
{
    return cm_80452C68.x341_b7;
}

void Camera_8002F274(void)
{
    Vec3 sp8;

    if (cm_80452C68.mode != CAMERA_BOSS_INTRO) {
        Camera_8002FE38();
    }

    cm_80452C68.x341_b3_b4 = 1;
    cm_80452C68.x35C.vec = cm_80452C68.transform.position;

    switch (cm_80452C68.x341_b3_b4) {
    case 1:
        cm_80452C68.transform.target_position = cm_80452C68.x35C.vec;
        break;
    case 3:
        if (cm_80452C68.x35C.cb != NULL && cm_80452C68.x35C.cb(&sp8)) {
            cm_80452C68.transform.target_position = sp8;
        }
        break;
    case 2:
    case 0:
    default:
        break;
    }
}

void fn_8002F360(HSD_GObj* x)
{
    if (cm_803BCB18.callback[cm_80452C68.mode]) {
        cm_803BCB18.callback[cm_80452C68.mode](x);
    }
}

void Camera_8002F3AC(void)
{
    HSD_GObj* gobj = cm_80452C68.gobj;
    PAD_STACK(1);

    if (cm_803BCB18.callback[cm_80452C68.mode] != NULL) {
        cm_803BCB18.callback[cm_80452C68.mode](gobj);
    }
    cm_80452C68.transform.position = cm_80452C68.transform.target_position;
    cm_80452C68.transform.interest = cm_80452C68.transform.target_interest;
    cm_80452C68.transform.fov = cm_80452C68.transform.target_fov;
    cm_80452C68.transform_copy.position =
        cm_80452C68.transform_copy.target_position;
    cm_80452C68.transform_copy.interest =
        cm_80452C68.transform_copy.target_interest;
    cm_80452C68.transform_copy.fov = cm_80452C68.transform_copy.target_fov;
}

void Camera_8002F474(void)
{
    cm_80452C68.mode = CAMERA_STANDARD;
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
    cm_80452C68.mode = CAMERA_TRAINING_MENU;
    cm_80452C68.x2C4 = slot;
    cm_80452C68.x2C5 = arg1;
    cm_80452C68.pitch_offset = 0.0f;
    cm_80452C68.yaw_offset = 0.0f;
}

void Camera_8002F7AC(s8 slot)
{
    CmSubject* cam_box;
    HSD_GObj* fighter_gobj;
    f32 direction;
    f32 randf;
    f32 offset_dir;
    f64 rand_dir;

    cm_80452C68.mode = CAMERA_CLEAR;
    cm_80452C68.x2C4 = slot;
    fighter_gobj = Player_GetEntity(cm_80452C68.x2C4);
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
                cm_80452C68.yaw_offset =
                    randf * Stage_GetCamAngleRadiansLeft();
            } else {
                randf = HSD_Randf();
                cm_80452C68.yaw_offset =
                    randf * -Stage_GetCamAngleRadiansRight();
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
    cm_80452C68.mode = CAMERA_FIXED;
}

s32 fn_8002F908(HSD_RectF32* arg0)
{
    f32 half_width;
    f32 half_height;
    f32 center_h;
    f32 center_v;

    center_h =
        (Stage_GetCamBoundsRightOffset() + Stage_GetCamBoundsLeftOffset()) *
        0.5f;
    half_width = cm_803BCCA0.xAC * (0.5f * (Stage_GetCamBoundsRightOffset() -
                                            Stage_GetCamBoundsLeftOffset()));
    arg0->ymax = center_h + half_width;
    arg0->ymin = center_h - half_width;
    center_v = 0.5f * (Stage_GetCamBoundsTopOffset() +
                       Stage_GetCamBoundsBottomOffset());
    half_height =
        cm_803BCCA0.xB0 * (0.5f * (Stage_GetCamBoundsTopOffset() -
                                   Stage_GetCamBoundsBottomOffset()));
    arg0->xmin = center_v + half_height;
    arg0->xmax = center_v - half_height;
    return 1;
}

void Camera_8002F9E4(s8 arg0, s8 arg1)
{
    f32 fov;
    f32 scale;
    u8* x304_ptr;
    f32* x32C_ptr;
    Vec3* x314_ptr;
    Vec3* pause_eye_ptr;

    cm_80452C68.mode = CAMERA_FREE;
    cm_80452C68.x304 = Camera_8002BA00(arg0 - 1, 1);
    x304_ptr = (u8*) &cm_80452C68.x304;
    cm_803BCCA0; // Force load
    cm_80452C68.x305 = arg1;
    x32C_ptr = &cm_80452C68.x32C;
    cm_80452C68.x32C = cm_803BCCA0.x40;

    cm_80452C68.x2D8 = Stage_GetCamBoundsLeftOffset();
    cm_80452C68.x2DC = Stage_GetCamBoundsRightOffset();
    cm_80452C68.x2D0 = Stage_GetCamBoundsTopOffset();
    cm_80452C68.x2D4 = Stage_GetCamBoundsBottomOffset();

    cm_80452C68.x2E0 = cm_803BCCA0.xA8;
    cm_80452C68.x2E4 = cm_803BCCA0.xA4;

    cm_80452C68.x2E8 = Stage_GetCamAngleRadiansUp();
    cm_80452C68.x2EC = Stage_GetCamAngleRadiansDown();
    cm_80452C68.x2F0 = Stage_GetCamAngleRadiansRight();
    cm_80452C68.x2F4 = Stage_GetCamAngleRadiansLeft();

    fov = *x32C_ptr;
    x314_ptr = &cm_80452C68.x314;
    scale = fov * cm_803BCCA0.x8C + cm_803BCCA0.x90;
    pause_eye_ptr = &cm_80452C68.pause_eye_offset;
    cm_80452C68.min_distance = scale * cm_803BCCA0.x94;
    cm_80452C68.max_distance = scale * cm_803BCCA0.x98;
    cm_80452C68.x300 = (s32) fn_8002F908;

    cm_80452C68.x314.z = 0.0f;
    cm_80452C68.x314.y = 0.0f;
    cm_80452C68.x314.x = 0.0f;
    cm_80452C68.pause_eye_offset.x = 0.0f;
    cm_80452C68.pause_eye_offset.y = 85.0f;
    cm_80452C68.pause_eye_offset.z = 730.0f;
    cm_80452C68.pause_up.x = 0.0f;
    cm_80452C68.pause_up.y = 1.0f;
    cm_80452C68.pause_up.z = 0.0f;

    if (*x304_ptr == 10) {
        cm_80452C68.pause_eye_distance = 35.0f * scale;
    } else {
        cm_80452C68.pause_eye_distance = scale;
    }

    Camera_8002BAA8(0.0f);
    Camera_8002BD88(0.0f, 0.0f);
    Camera_8002C010(0.0f, 0.0f);

    cm_80452C68.transform.target_interest = cm_80452C68.x308;
    lbVector_Add(&cm_80452C68.transform.target_interest, x314_ptr);

    cm_80452C68.transform.target_position =
        cm_80452C68.transform.target_interest;
    lbVector_Add(&cm_80452C68.transform.target_position, pause_eye_ptr);
}

s32 fn_8002FBA0(HSD_RectF32* arg0)
{
    // duplicate function?? fn_8002F908
    f32 half_width;
    f32 half_height;
    f32 center_h;
    f32 center_v;

    center_h =
        (Stage_GetCamBoundsRightOffset() + Stage_GetCamBoundsLeftOffset()) *
        0.5f;
    half_width = cm_803BCCA0.xAC * (0.5f * (Stage_GetCamBoundsRightOffset() -
                                            Stage_GetCamBoundsLeftOffset()));
    arg0->ymax = center_h + half_width;
    arg0->ymin = center_h - half_width;
    center_v = 0.5f * (Stage_GetCamBoundsTopOffset() +
                       Stage_GetCamBoundsBottomOffset());
    half_height =
        cm_803BCCA0.xB0 * (0.5f * (Stage_GetCamBoundsTopOffset() -
                                   Stage_GetCamBoundsBottomOffset()));
    arg0->xmin = center_v + half_height;
    arg0->xmax = center_v - half_height;
    return 1;
}

void Camera_8002FC7C(s8 arg0, s8 arg1)
{
    CameraUnkGlobals* new_var;
    CameraTransformState* transform;
    f32 temp_f2;
    s8* x304_ptr;
    s8 x304_check;

    cm_80452C68.mode = CAMERA_FREE;
    cm_80452C68.x304 = Camera_8002BA00(arg0 - 1, 1);
    cm_80452C68.x305 = arg1;
    cm_80452C68.x32C = cm_803BCCA0.x40;
    cm_80452C68.x2D8 = Stage_GetCamBoundsLeftOffset();
    cm_80452C68.x2DC = Stage_GetCamBoundsRightOffset();
    cm_80452C68.x2D0 = Stage_GetCamBoundsTopOffset();
    cm_80452C68.x2D4 = Stage_GetCamBoundsBottomOffset();
    cm_80452C68.x2E0 = (*(new_var = &cm_803BCCA0)).xA8;
    cm_80452C68.x2E4 = (*new_var).xA4;
    cm_80452C68.x2E8 = Stage_GetCamAngleRadiansUp();
    cm_80452C68.x2EC = Stage_GetCamAngleRadiansDown();
    cm_80452C68.x2F0 = Stage_GetCamAngleRadiansRight();
    cm_80452C68.x2F4 = Stage_GetCamAngleRadiansLeft();
    temp_f2 = (cm_80452C68.x32C * (*new_var).x8C) + (*new_var).x90;
    cm_80452C68.min_distance = temp_f2 * (*new_var).x94;
    cm_80452C68.max_distance = temp_f2 * (*new_var).x98;
    cm_80452C68.x300 = (s32) fn_8002FBA0;
    x304_ptr = &cm_80452C68.x304;
    x304_check = *x304_ptr;
    cm_80452C68.x314.z = 0.0f;
    cm_80452C68.x314.y = 0.0f;
    cm_80452C68.x314.x = 0.0f;
    cm_80452C68.pause_eye_offset.x = 0.0f;
    cm_80452C68.pause_eye_offset.y = 5.0f;
    cm_80452C68.pause_eye_offset.z = 20.0f;
    cm_80452C68.pause_up.x = 0.0f;
    cm_80452C68.pause_up.y = 1.0f;
    cm_80452C68.pause_up.z = 0.0f;
    if (x304_check == 0xA) {
        cm_80452C68.pause_eye_distance = 3.0f * temp_f2;
    } else {
        cm_80452C68.pause_eye_distance = temp_f2;
    }
    Camera_8002BAA8(0.0f);
    Camera_8002BD88(0.0f, 0.0f);
    Camera_8002C010(0.0f, 0.0f);
    transform = &cm_80452C68.transform;
    transform->target_interest = cm_80452C68.x308;
    lbVector_Add(&transform->target_interest, &cm_80452C68.x314);
    transform->target_position = transform->target_interest;
    lbVector_Add(&transform->target_position, &cm_80452C68.pause_eye_offset);
}

void Camera_8002FE38(void)
{
    cm_80452C68.mode = CAMERA_BOSS_INTRO;
    cm_80452C68.x341_b1_b2 = 0;
    cm_80452C68.x341_b3_b4 = 0;
    cm_80452C68.x341_b5_b6 = 0;
    cm_80452C68.x341_b7 = 0;

    cm_80452C68.x350 = cm_80452C68.transform.interest;
    cm_80452C68.transform.target_interest = cm_80452C68.x350;
    cm_80452C68.x368 = cm_80452C68.transform.position;
    cm_80452C68.transform.target_position = cm_80452C68.x368;
    cm_80452C68.transform.target_fov = cm_80452C68.x374 =
        cm_80452C68.transform.fov;
}

void Camera_8002FEEC(s32 arg0)
{
    HSD_CObj* cobj;
    CmSubject* box;
    Vec3 target;
    Vec3 eye;
    f32 fov;
    f32 temp_f1_3;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f1_4;
    PAD_STACK(12);

    if (Player_GetEntity(arg0) != NULL) {
        box = ftLib_80086B74(Player_GetEntity(arg0));
        if ((box != NULL) && ((cm_80452C68.mode) != CAMERA_DEBUG_FOLLOW)) {
            if (cm_80452C68.mode <= (u32) CAMERA_PAUSE) {
                cm_80453004.last_mode = cm_80452C68.mode;
            }

            cm_80452C68.mode = CAMERA_DEBUG_FOLLOW;
            cm_80453004.ply_slot = arg0;
            temp_f1 = tanf(0.017453292f * cm_80452C68.transform.target_fov);
            temp_f31 = (2.0f * box->x34.z) / temp_f1;
            cm_80453004.follow_int_offset.z = 0.0f;
            cm_80453004.follow_int_offset.y = 0.0f;
            cm_80453004.follow_int_offset.x = 0.0f;
            cobj = cm_80452C68.gobj->hsd_obj;
            HSD_CObjGetInterest(cobj, &eye);
            HSD_CObjGetEyePosition(cobj, &target);
            fov = HSD_CObjGetFov(cobj);
            cm_80453004.follow_eye_pos = eye;
            cm_80453004.follow_int_pos = target;
            cm_80453004.follow_fov = fov;

            lbVector_Diff(&target, &eye, &cm_80453004.follow_eye_offset);
            temp_f1_3 = cm_80453004.follow_eye_offset.x;
            temp_f1 = temp_f1_3 * temp_f1_3;

            temp_f1_4 =
                temp_f31 /
                sqrtf__Ff((cm_80453004.follow_eye_offset.z *
                           cm_80453004.follow_eye_offset.z) +
                          (temp_f1 + (cm_80453004.follow_eye_offset.y *
                                      cm_80453004.follow_eye_offset.y)));

            cm_80453004.follow_eye_offset.x *= temp_f1_4;
            cm_80453004.follow_eye_offset.y *= temp_f1_4;
            cm_80453004.follow_eye_offset.z *= temp_f1_4;
        }
    }
}

void Camera_8003006C(void)
{
    HSD_CObj* cobj;

    if (cm_80452C68.mode != CAMERA_DEBUG_FREE) {
        if (cm_80452C68.mode <= (u32) CAMERA_PAUSE) {
            cm_80453004.last_mode = cm_80452C68.mode;
        }
        cm_80452C68.mode = CAMERA_DEBUG_FREE;
        cobj = GET_COBJ(cm_80452C68.gobj);
        HSD_CObjGetInterest(cobj, &cm_80453004.free_int_pos);
        HSD_CObjGetEyePosition(cobj, &cm_80453004.free_eye_pos);
        cm_80453004.free_fov = HSD_CObjGetFov(cobj);
    }
}

void Camera_800300F0(void)
{
    cm_80452C68.mode = cm_80453004.last_mode;
}

bool Camera_8003010C(void)
{
    if ((int) cm_80452C68.mode == CAMERA_FREE) {
        return true;
    }
    return false;
}

bool Camera_80030130(void)
{
    if ((int) cm_80452C68.mode == CAMERA_BOSS_INTRO) {
        return true;
    }
    return false;
}

bool Camera_80030154(void)
{
    if ((int) cm_80452C68.mode == CAMERA_DEBUG_FOLLOW) {
        return true;
    }
    return false;
}

bool Camera_80030178(void)
{
    if ((int) cm_80452C68.mode == CAMERA_DEBUG_FREE) {
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

void Camera_80030688(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(0x10, 0x12, 0);
    cm_80452C68.gobj = gobj;

    cobj = lb_80013B14(&cm_803BCB64);
    cm_804D6464 = lb_80013B14(&cm_803BCB64);
    {
        HSD_CObj* c = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, c);
    }

    GObj_SetupGXLinkMax(gobj, fn_800301D0, 2);
    HSD_GObjProc_8038FD54(gobj, fn_8002F360, 0x12);
}

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
    *arg0 = cm_80452C68.transform.position;
}

void Camera_800307AC(Vec* arg0)
{
    *arg0 = cm_80452C68.transform.interest;
}

static inline void compute_edge(Vec3* forward, Vec3* eye_pos, f32 fov,
                                f32* value)
{
    f32 s;
    f32 c;
    f32 edge_x;
    f32 edge_z;

    s = sinf(fov);
    c = cosf(fov);
    edge_x = (forward->x * c) + (forward->z * s);
    edge_z = (forward->z * c) - (forward->x * s);

    if ((ABS(edge_z) > 0.0001) && ((forward->z * edge_z) > 0.0)) {
        *value = -((edge_x * (eye_pos->z / edge_z)) - eye_pos->x);
    } else if (edge_x > 0.0f) {
        *value = 8.5070587e37f;
    } else {
        *value = -8.5070587e37f;
    }
}

bool Camera_800307D0(f32* left, f32* center, f32* right)
{
    HSD_CObj* cobj;
    f32 half_fov;
    Vec3 forward;
    Vec3 interest_pos;
    Vec3 eye_pos;
    bool b_r30;
    PAD_STACK(0x10);

    cobj = GET_COBJ(cm_80452C68.gobj);
    half_fov =
        0.5 * (deg_to_rad * HSD_CObjGetFov(cobj) * HSD_CObjGetAspect(cobj));

    b_r30 = true;
    HSD_CObjGetEyePosition(cobj, &eye_pos);
    HSD_CObjGetEyeVector(cobj, &forward);
    HSD_CObjGetInterest(cobj, &interest_pos);

    if (ABS(forward.x) > 1e-4 && ABS(forward.z) > 1e-4) {
        // ray casts?
        forward.x *= -1.0f;
        forward.y *= -1.0f;
        forward.z *= -1.0f;
        *center = -((forward.x * (eye_pos.z / forward.z)) - eye_pos.x);

        compute_edge(&forward, &eye_pos, half_fov, left);
        compute_edge(&forward, &eye_pos, -half_fov, right);
    } else {
        *left = -8.5070587e37f;
        *right = 8.5070587e37f;
        *center = 0.0f;
        b_r30 = false;
    }
    return b_r30;
}

HSD_GObj* Camera_80030A50(void)
{
    return cm_80452C68.gobj;
}

void Camera_80030A60(bool arg0)
{
    cm_80452C68.x399_b3 = arg0;
}

bool Camera_80030A78(void)
{
    return cm_80452C68.x399_b3;
}

void Camera_80030A8C(bool arg0)
{
    cm_80452C68.x399_b4 = arg0;
}

void Camera_SetStageVisible(int arg0)
{
    int temp;
    cm_80452C68.x399_b5 = (temp = 0) == arg0;
}

bool Camera_80030AC4(void)
{
    int temp;
    return (temp = 0) == cm_80452C68.x399_b5;
}

void Camera_80030AE0(bool arg0)
{
    cm_80452C68.x399_b2 = arg0;
}

bool Camera_80030AF8(void)
{
    return cm_80452C68.x399_b2;
}

void Camera_80030B0C(bool arg0)
{
    cm_80452C68.x399_b7 = arg0;
}

bool Camera_80030B24(void)
{
    return cm_80452C68.x399_b7;
}

void Camera_80030B38(bool arg0)
{
    cm_80452C68.x39A_b0 = arg0;
}

bool Camera_80030B50(void)
{
    return cm_80452C68.x39A_b0;
}

void Camera_80030B64(bool arg0)
{
    cm_80452C68.x39A_b1 = arg0;
}

bool Camera_80030B7C(void)
{
    return cm_80452C68.x39A_b1;
}

void Camera_80030B90(bool arg0)
{
    cm_80452C68.x39A_b2 = arg0;
}

bool Camera_80030BA8(void)
{
    return cm_80452C68.x39A_b2;
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

    if ((point.x > 2.1474836e9f) || (point.x < -2.1474836e9f) ||
        (point.y > 2.1474836e9f) || (point.y < -2.1474836e9f))
    {
        return false;
    }

    px = point.x;
    py = point.y;
    if (arg1 != NULL) {
        arg1->x = px;
        arg1->y = py;
    }
    HSD_CObjGetScissor(cobj, &scissor);
    if ((px < scissor.left) || (px >= scissor.right) || (py < scissor.top) ||
        (py >= scissor.bottom))
    {
        return false;
    }
    return true;
}

bool Camera_80030CD8(CmSubject* arg0, S32Vec2* arg1)
{
    return Camera_80030BBC(&arg0->x1C, arg1);
}

// Camera_IsSubjectOnScreen
bool Camera_80030CFC(CmSubject* cam_box, f32 tolerance)
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
    if (lbVector_8000E838(&interest, &eye_pos, &cam_box->x1C, &sp38) <
        (cam_box->x34.z + tolerance))
    {
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
    if (cm_80452C68.x2B8 < 1) {
        return 10000.f;
    }
    return cm_80452C68.x2B0;
}

void Camera_80030E34(f32 arg8)
{
    cm_80452C68.xAC = arg8;
}

void Camera_80030E44(enum_t arg0, Vec3* arg1)
{
    HSD_GObj** pgobj;
    s32 result;
    Camera* camera = &cm_80452C68;

    switch (arg0) {
    case 1:
        pgobj = &camera->xA0;
        if (camera->xA0 == NULL) {
            *pgobj = (HSD_GObj*) grLib_801C9CEC(arg0);
        }
        result = 10;
        break;
    case 2:
        grLib_801C9CEC(arg0);
        result = 22;
        break;
    case 3:
        grLib_801C9CEC(arg0);
        result = 22;
        break;
    case 4:
        grLib_801C9CEC(arg0);
        result = 22;
        break;
    }

    camera->_8C[arg0] = result;

    {
        s32 i;
        for (i = 0; i < 4; i++) {
            if (camera->_B0[0][i].type == 0) {
                camera->_B0[0][i].type = arg0;
                if (arg1 != NULL) {
                    camera->_B0[0][i].x0 = *arg1;
                } else {
                    camera->_B0[0][i].x0.z = 0.0f;
                    camera->_B0[0][i].x0.y = 0.0f;
                    camera->_B0[0][i].x0.x = 0.0f;
                }
            }
        }
    }
}

void Camera_80031044(s32 arg0)
{
    cm_80452C68._8C[arg0] = 0;
}

enum_t Camera_80031060(void)
{
    return cm_80452C68.x398_b6_b7;
}

void Camera_80031074(u8 arg0)
{
    cm_80452C68.x398_b6_b7 = arg0;
}

enum_t Camera_8003108C(void)
{
    return cm_80452C68.x399_b0_b1;
}

void Camera_800310A0(u8 arg0)
{
    cm_80452C68.x399_b0_b1 = arg0;
}

HSD_CObj* Camera_800310B8(void)
{
    HSD_CObjSetMtxDirty(cm_804D6464);
    HSD_CObjSetupViewingMtx(cm_804D6464);
    return cm_804D6464;
}

void Camera_800310E8(void)
{
    cm_80452C68.x398_b0 = 0;
    cm_80452C68.x398_b1 = 0;
    cm_80452C68.x398_b2 = 0;
    cm_80452C68.x398_b3 = 0;
    cm_80452C68.x398_b4 = 0;
    cm_80452C68.x398_b5 = 0;
}

f32 Camera_80031144(void)
{
    return cm_80452C68.x2BC;
}

bool Camera_80031154(Vec3* arg0)
{
    if ((u32) Camera_80029124(arg0, 0) == 0) {
        return true;
    }
    return false;
}

bool Camera_8003118C(Vec3* arg0, float arg1)
{
    if ((u32) Camera_80029124(arg0, arg1) == 0) {
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

void Camera_80031328(HSD_GObj* arg0, s32 arg2, s32 arg3)
{
    s32 var_r11;
    s32 var_r4;
    s32 var_r9;
    Camera* camera;

    cm_80452C68.x398_b6_b7 = 0;
    camera = &cm_80452C68;

    if (cm_80452C68.x398_b0) {
        var_r4 = 0;
    } else {
        var_r4 = 0x20;
    }

    if (cm_80452C68.x398_b4) {
        var_r9 = 0;
    } else {
        var_r9 = 0x10;
        var_r4 = 0;
    }

    if ((*camera).x398_b1) {
        var_r11 = 0;
    } else {
        var_r11 = 0x40;
        var_r9 = 0;
    }
    arg0->gxlink_prios =
        (var_r11 | var_r4) | (var_r9 | var_r4) | (arg2 | arg3) | (var_r11 | 0);
    HSD_GObj_80390ED0(arg0, 4);
}

/// #Camera_800313E0
