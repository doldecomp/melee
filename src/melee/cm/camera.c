#include <placeholder.h>

#include "cm/forward.h"
#include "ft/forward.h"

#include "camera.static.h"
#include "platform.h"

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
#include "lb/lb_00F9.h"
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
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>

static HSD_CObj* cm_804D6464;

void Camera_80028B9C(int n_subjects)
{
    CameraBox* cam_box;
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
    cm_80452C68.mode = 0;
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
    cm_80452C68.x398_b6_b7 = 0;
    cm_80452C68.x399_b0_b1 = 0;
    cm_80452C68.x399_b2 = 0;
    cm_80452C68.debug_mode.last_mode = cm_80452C68.mode;
    cm_80452C68.x399_b3 = 0;
    cm_80452C68.x399_b4 = 0;
    cm_80452C68.x399_b5 = 0;
    memzero(&cm_80452C68 + 0x380, 0x18);
    cm_80452C68.x399_b6 = 0;
    cm_80452C68.x39A_b5 = 0;
    cm_80452C68.x39A_b6 = 0;
    cm_80452C68.x39A_b7 = 0;
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

void Camera_8002958C(CameraBounds* bounds, CameraTransformState* transform)
{
    u8 PAD_STACK[8]; // TODO :: inline?
    f32 z_pos;
    f32 var_f3;
    enum_t in_bounds;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 scroll_offset;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 x_min;
    f32 y_min;
    f32 x_max;
    f32 y_max;
    CameraBox* subject;
    s32 i;
    f32 fixedness;
    f32 track_ratio;

    i = 0;
    subject = cm_804D6468;

    for (subject = cm_804D6468; subject != NULL; subject = subject->prev) {
        if (Camera_8002928C(subject)) {
            i++;
        }
    }

    if (i != 0) {
        if ((u32) i < 5U) {
            fixedness = cm_803BCB9C[i];
        } else {
            fixedness = 1.0f;
        }
        track_ratio = fixedness * Stage_GetCamTrackRatio();
        y_min = -3.4028235e38f;
        x_min = -3.4028235e38f;
        y_max = 3.4028235e38f;
        x_max = 3.4028235e38f;

        i = 0;
        subject = cm_804D6468;

        while (subject != NULL) {
            if (Camera_8002928C(subject)) {
                i += 1;

                sp50 = subject->x10;
                sp44 = subject->x10;

                // TODO :: these are probably inlined?
                in_bounds = Camera_80029124(&sp50, 0);
                if (in_bounds != 0) {
                    Ground_801C4368(&sp30, &sp34);
                    sp30 += 1.0;
                    if (in_bounds & 4)  sp50.x = Stage_GetCamBoundsLeftOffset();
                    if (in_bounds & 8)  sp50.x = Stage_GetCamBoundsRightOffset();
                    if (in_bounds & 1)  sp50.y = Stage_GetCamBoundsTopOffset();
                    if (in_bounds & 2) {
                        sp50.y = (Stage_GetCamBoundsBottomOffset() > sp30)
                                ? Stage_GetCamBoundsBottomOffset()
                                : sp30;
                    }
                }

                sp44.x = (subject->x2C.x * track_ratio) + sp50.x;
                in_bounds = Camera_80029124(&sp44, 0);
                if (in_bounds != 0) {
                    Ground_801C4368(&sp28, &sp2C);
                    sp28 += 1.0;
                    if (in_bounds & 4)  sp44.x = Stage_GetCamBoundsLeftOffset();
                    if (in_bounds & 8)  sp44.x = Stage_GetCamBoundsRightOffset();
                    if (in_bounds & 1)  sp44.y = Stage_GetCamBoundsTopOffset();
                    if (in_bounds & 2) {
                        sp44.y = (Stage_GetCamBoundsBottomOffset() > sp28)
                                ? Stage_GetCamBoundsBottomOffset()
                                : sp28;
                    }
                }

                if (sp44.x < x_min)
                {
                    x_min = sp44.x;
                }
                if (sp44.x > x_max)
                {
                    x_max = sp44.x;
                }

                sp44.x = (subject->x2C.y * track_ratio) + sp50.x;
                in_bounds = Camera_80029124(&sp44, 0);
                if (in_bounds != 0) {
                    Ground_801C4368(&sp20, &sp24);
                    sp20 += 1.0;
                    if (in_bounds & 4)  sp44.x = Stage_GetCamBoundsLeftOffset();
                    if (in_bounds & 8)  sp44.x = Stage_GetCamBoundsRightOffset();
                    if (in_bounds & 1)  sp44.y = Stage_GetCamBoundsTopOffset();
                    if (in_bounds & 2) {
                        sp44.y = (Stage_GetCamBoundsBottomOffset() > sp20)
                                ? Stage_GetCamBoundsBottomOffset()
                                : sp20;
                    }
                }
                if (sp44.x < x_min)
                {
                    x_min = sp44.x;
                }
                if (sp44.x > x_max)
                {
                    x_max = sp44.x;
                }

                sp44.y = (subject->x34.y * track_ratio) + sp50.y;
                in_bounds = Camera_80029124(&sp44, 0);
                if (in_bounds != 0) {
                    Ground_801C4368(&sp18, &sp1C);
                    sp18 += 1.0;
                    if (in_bounds & 4)  sp44.x = Stage_GetCamBoundsLeftOffset();
                    if (in_bounds & 8)  sp44.x = Stage_GetCamBoundsRightOffset();
                    if (in_bounds & 1)  sp44.y = Stage_GetCamBoundsTopOffset();
                    if (in_bounds & 2) {
                        sp44.y = (Stage_GetCamBoundsBottomOffset() > sp18)
                                ? Stage_GetCamBoundsBottomOffset()
                                : sp18;
                    }
                }
                if (sp44.y < y_min)
                {
                    y_min = sp44.y;
                }
                if (sp44.y > y_max)
                {
                    y_max = sp44.y;
                }

                sp44.y = (subject->x34.x * track_ratio) + sp50.y;
                in_bounds = Camera_80029124(&sp44, 0);
                if (in_bounds != 0) {
                    Ground_801C4368(&sp10, &sp14);
                    sp10 += 1.0;
                    if (in_bounds & 4)  sp44.x = Stage_GetCamBoundsLeftOffset();
                    if (in_bounds & 8)  sp44.x = Stage_GetCamBoundsRightOffset();
                    if (in_bounds & 1)  sp44.y = Stage_GetCamBoundsTopOffset();
                    if (in_bounds & 2) {
                        sp44.y = (Stage_GetCamBoundsBottomOffset() > sp10)
                                ? Stage_GetCamBoundsBottomOffset()
                                : sp10;
                    }
                }
                if (sp44.y < y_min)
                {
                    y_min = sp44.y;
                }
                if (sp44.y > y_max)
                {
                    y_max = sp44.y;
                }
            }
            subject = subject->prev;
        }
    }

    if (i == 0) {
        Stage_UnkSetVec3TCam_Offset(&scroll_offset);
        x_min = scroll_offset.x - 40.0f;
        y_min = scroll_offset.y - 40.0f;
        x_max = 40.0f + scroll_offset.x;
        y_max = 40.0f + scroll_offset.y;
    }

    z_pos = fabs_inline(transform->position.z);
    if (z_pos < 80.0f) {
        var_f3 = 0.0f;
    } else if (z_pos > 5000.0f) {
        var_f3 = 1.0f;
    } else {
        var_f3 = (z_pos - 80.0f) / 4920.0f;
    }

    bounds->x_min = x_min;
    bounds->y_min = y_min - ((390.0f * var_f3) + 10.0f);
    bounds->x_max = x_max;
    bounds->y_max = y_max;
    bounds->subjects = i;
    bounds->z_pos = z_pos;
}

void Camera_80029AAC(CameraBounds* bounds, CameraTransformState* transform, f32 speed)
{
    float dx, dy;
    f32 spread;
    f32 lerp_factor;
    f32 delta;
    f32 follow_speed;
    f32 offset_x, offset_y;
    CameraUnkGlobals* unk;

    if (bounds->subjects != 0) {
        dx = bounds->x_max - bounds->x_min;
        dy = bounds->y_max - bounds->y_min;
        if (dx > dy) {
            spread = dx;
        } else {
            spread = dy;
        }
    } else {
        spread = 99999.0f;
    }

    unk = &cm_803BCCA0;

    offset_x = transform->target_interest.x - transform->interest.x;
    offset_y = transform->target_interest.y - transform->interest.y;

    if (spread > unk->x38) {
        follow_speed = unk->x30;
    } else if (spread < unk->x34) {
        follow_speed = unk->x2C;
    } else {
        follow_speed = (spread - unk->x34) / (unk->x38 - unk->x34)
               * (unk->x30 - unk->x2C) + unk->x2C;
    }
    if (cm_80452C68.x2BC > 0.0001f) {
        delta = 1.0f / cm_80452C68.x2BC;
    } else {
        delta = 1000.0f;
    }
    lerp_factor = follow_speed * speed * delta;
    if (lerp_factor > 1.0f) {
        lerp_factor = 1.0f;
    } else if (lerp_factor < 0.0001f) {
        lerp_factor = 0.0001f;
    }

    transform->interest.x += offset_x * lerp_factor;
    transform->interest.y += offset_y * lerp_factor;
}

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

void Camera_80029C88(CameraBounds* unused, CameraTransformState* transform, f32 arg_scale)
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

void Camera_80029CF8(CameraBounds* bounds, CameraTransformState* transform)
{
    Vec3 scroll_offset;
    Vec3 scroll_offset2;
    f32 height;
    f32 min_v;
    f32 min_h;
    f32 up_half_fov;
    f32 down_half_fov;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 mid_x;
    f32 temp_f31_3;
    f32 max_h;
    f32 top;
    f32 max_v;
    f32 bottom;
    f32 width;
    f32 var_f28;
    f32 pitch_angle;
    f32 vert_frustum_dist;
    f32 pan_angle;
    f32 var_f3;
    f32* aspect;

    Stage_UnkSetVec3TCam_Offset(&scroll_offset);

    top = bounds->y_max;
    bottom = bounds->y_min;
    width = bounds->x_max - bounds->x_min;
    height = top - bottom;
    if (width > height) {

    } else {
        width = height;
    }

    if (width > 120.0f) {
        var_f3 = 0.0682f;
    } else if (width < 60.0f) {
        var_f3 = 0.0f;
    } else {
        var_f3 = ((0.0682f - 0.0f) * ((width - 60.f) / (120.0f / 60.f))) + 0.0f; /// whats up with the zeros?
    }

    max_v = deg_to_rad * 5.0f;
    pitch_angle = -(deg_to_rad * (((((bounds->y_min - scroll_offset.y) +
                                 (bounds->y_max - scroll_offset.y)) *
                                (0.5f - var_f3)) +
                                scroll_offset.y + -30.0f))) *
                                Stage_GetCamInfoX24();

    if (pitch_angle > max_v) {
        pitch_angle = max_v;
    }

    min_v = deg_to_rad * -7.0f;
    if (pitch_angle < min_v) {
        pitch_angle = min_v;
    }

    temp_f29 = pitch_angle + Stage_GetCamPanAngleRadians();
    up_half_fov = (0.5f * (deg_to_rad * transform->fov)) + temp_f29;
    if (!(up_half_fov < M_PI_2)) {
        __assert("camera.c",0x4FA,"fov_u<MTXDegToRad(90.0F)");
    }

    down_half_fov = (0.5f * (deg_to_rad * transform->fov)) - temp_f29;
    if (!(down_half_fov < M_PI_2)) {
        __assert("camera.c",0x4FB,"fov_d<MTXDegToRad(90.0F)");
    }

    vert_frustum_dist = (bounds->y_max - bounds->y_min) / (tanf(up_half_fov) + tanf(down_half_fov));
    Stage_GetCamBoundsBottomOffset();
    Stage_GetCamBoundsTopOffset();
    temp_f30 = vert_frustum_dist * tanf(temp_f29);
    transform->target_interest.y = temp_f30 + -((vert_frustum_dist * tanf(up_half_fov)) - bounds->y_max);
    Stage_UnkSetVec3TCam_Offset(&scroll_offset2);
    mid_x = 0.5f * (bounds->x_min + bounds->x_max);
    max_h = deg_to_rad * 17.5f;
    pan_angle = -(deg_to_rad * ((mid_x - scroll_offset2.x) * Stage_GetCamInfoX20()));
    if (pan_angle > max_h) {
        pan_angle = max_h;
    }

    min_h = deg_to_rad * -17.5f;
    if (pan_angle < min_h) {
        pan_angle = min_h;
    }

    temp_f1_3 = (0.5f * (deg_to_rad * transform->fov)) - pan_angle;
    if (!(temp_f1_3 < M_PI_2)) {
        __assert("camera.c",0x508,"fov_r<MTXDegToRad(90.0F)");
    }

    temp_f1_4 = (0.5f * (deg_to_rad * transform->fov)) + pan_angle;
    if (!(temp_f1_4 < M_PI_2)) {
        __assert("camera.c",0x509,"fov_l<MTXDegToRad(90.0F)");
    }
    aspect = &cm_803BCB64.aspect;
    temp_f26 = cm_803BCB64.aspect * tanf(temp_f1_3);
    temp_f28 = (bounds->x_max - bounds->x_min) / (temp_f26 + (*aspect * tanf(temp_f1_4)));
    Stage_GetCamBoundsLeftOffset();
    Stage_GetCamBoundsRightOffset();
    temp_f31_3 = *aspect * (temp_f28 * tanf(pan_angle));
    transform->target_interest.x = -((temp_f28 * temp_f26) - bounds->x_max) - temp_f31_3;
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

/// #Camera_8002A0C0

void Camera_8002A278(f32 x, f32 y)
{
    cm_80452C68.xA4 = x;
    cm_80452C68.xA8 = y;
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

    if ((test != -1) && (cm_80452C68.xA0 != NULL) && (cm_80452C68._8C[1] == 0)) {
        HSD_GObjPLink_80390228(cm_80452C68.xA0);
        cm_80452C68.xA0 = 0;
    }
}

void Camera_8002A4AC(HSD_GObj* gobj)
{
    Vec3 pos;
    HSD_CObj* cobj;
    f32 floor_y;
    PAD_STACK(8);

    cobj = GET_COBJ(gobj);
    switch (cm_80452C68.mode) {
    case 0:
    case 4:
        Camera_8002AF68(cobj, &cm_80452C68.transform);
        Camera_8002AF68(cm_804D6464, &cm_80452C68.transform_copy);
        HSD_CObjSetNear(cobj, cm_80452C68.nearz);
        HSD_CObjSetFar(cobj, cm_80452C68.farz);
        return;
    case 5:
        Camera_8002AF68(cobj, &cm_80452C68.transform);
        HSD_CObjSetNear(cobj, cm_80452C68.nearz);
        HSD_CObjSetFar(cobj, cm_80452C68.farz);
        return;
    case 1:
        pos = cm_80452C68.transform.position;
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
        HSD_CObjSetFov(cobj, cm_80452C68.transform.fov);
        HSD_CObjSetInterest(cobj, &cm_80452C68.transform.interest);
        HSD_CObjSetEyePosition(cobj, &pos);
        HSD_CObjSetNear(cobj, 0.1f);
        HSD_CObjSetFar(cobj, 16384.0f);
        return;
    case 2:
    case 3:
    case 6:
        HSD_CObjSetFov(cobj, cm_80452C68.transform.fov);
        HSD_CObjSetInterest(cobj, &cm_80452C68.transform.interest);
        HSD_CObjSetEyePosition(cobj, &cm_80452C68.transform.position);
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
    lbVector_Diff(&transform->target_interest, &transform->target_position, &dist);
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
    bool singleplayer;
    f32 cstick_y;
    f32 val;
    f32 x2bc;
    u8 player_id;

    singleplayer = gm_8016B41C();
    if (singleplayer && (cm_80452C68.x2C0 > 0.0f)) {
        player_id = Player_GetPlayerId(0);
        cstick_y = HSD_PadCopyStatus[player_id].nml_subStickY;
        val = cstick_y;

        if (cstick_y < 0.0f) {
            cstick_y = -cstick_y;
        }

        if (cstick_y < 0.85f) {
            val = 0.0f;
            if (cm_80452C68.x2BA > 0) {
                cm_80452C68.x2BA--;
            } else {
                cstick_y = cm_803BCCA0._44[0x28];
            }
            x2bc = cm_803BCCA0._44[40];
        } else {
            cm_80452C68.x2BA = cm_803BCCA0._44[0x27];
        }

        cm_80452C68.x2BC = -(val * cm_803BCCA0._44[36] - cm_80452C68.x2BC);
        if (cm_80452C68.x2BC < cm_803BCCA0._44[38]) {
            cm_80452C68.x2BC = cm_803BCCA0._44[38];
        }
        else if (cm_80452C68.x2BC > cm_803BCCA0._44[37]) {
            cm_80452C68.x2BC = cm_803BCCA0._44[37];
        }
    }
}

void Camera_8002B1F8(CameraTransformState* transform)
{
    Vec3 vec;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    CameraBox* var_r29;
    float temp_f1;
    float temp_f1_2;
    float temp_f31;
    float* temp_r31;

    temp_r31 = &cm_80452C68.x2BC;
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
        lbVector_Diff(&transform->target_interest, &var_r29->x1C, &vec);
        temp_f1 = *temp_r31;
        temp_f1_2 = temp_f1 * temp_f1;
        vec.x *= temp_f1_2;
        vec.y *= temp_f1_2;
        vec.z *= temp_f1_2;
        lbVector_Add(&vec, &var_r29->x1C);
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

float vec_len(Vec3* offset)
{
    return sqrtf((offset->x * offset->x) + (offset->y * offset->y) + (offset->z * offset->z));
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

    cm_80452C68.pause_eye_distance = ((zoom_amt * ((offset_len * cm_803BCCA0._44[0x16]) + cm_803BCCA0._44[0x17])) + cm_80452C68.pause_eye_distance);

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
        scale = y * ((view_dir * cm_803BCCA0._44[0x1E]) + cm_803BCCA0._44[0x1F]);
        // scale = y * ((view_dir * cm_803BCCA0._44[0x1E]) + cm_803BCCA0._44[0x1F]);
        up.x *= scale;
        up.y *= scale;
        up.z *= scale;
        lbVector_Add(&pos, &up);
    }

    if (x != 0.0F) {
        // scale = x * ((view_dir * cm_803BCCA0._44[0x1E]) + cm_803BCCA0._44[0x1F]);
        // TODO :: cant figure out how to get it to run the same logic as the y case
        // without it allocating stack space for it
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
    Vec3 spC;

    if (cm_80452C68.mode != 6) {
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

/// #Camera_8002EB5C

/// #Camera_8002EC7C

/// #Camera_8002ED9C

void Camera_8002EEC8(f32 fov)
{
    if (cm_80452C68.mode != 6) {
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

/// #Camera_8002F274

void fn_8002F360(HSD_GObj* x)
{
    if (cm_803BCB18.callback[cm_80452C68.mode]) {
        cm_803BCB18.callback[cm_80452C68.mode](x);
    }
}

void Camera_8002F3AC(void)
{
    HSD_GObj *gobj = cm_80452C68.gobj;
    PAD_STACK(1);

    if (cm_803BCB18.callback[cm_80452C68.mode] != NULL) {
        cm_803BCB18.callback[cm_80452C68.mode](gobj);
    }
    cm_80452C68.transform.position = cm_80452C68.transform.target_position;
    cm_80452C68.transform.interest = cm_80452C68.transform.target_interest;
    cm_80452C68.transform.fov = cm_80452C68.transform.target_fov;
    cm_80452C68.transform_copy.position = cm_80452C68.transform_copy.target_position;
    cm_80452C68.transform_copy.interest = cm_80452C68.transform_copy.target_interest;
    cm_80452C68.transform_copy.fov = cm_80452C68.transform_copy.target_fov;
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
    cm_80452C68.x2C4 = slot;
    cm_80452C68.x2C5 = arg1;
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

    center_h = (Stage_GetCamBoundsRightOffset() + Stage_GetCamBoundsLeftOffset()) * 0.5f;
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

    center_h = (Stage_GetCamBoundsRightOffset() + Stage_GetCamBoundsLeftOffset()) * 0.5f;
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
    cm_80452C68.x341_b1_b2 = 0;
    cm_80452C68.x341_b3_b4 = 0;
    cm_80452C68.x341_b5_b6 = 0;
    cm_80452C68.x341_b7 = 0;

    cm_80452C68.x350 = cm_80452C68.transform.interest;
    cm_80452C68.transform.target_interest = cm_80452C68.x350;
    cm_80452C68.x368 = cm_80452C68.transform.position;
    cm_80452C68.transform.target_position = cm_80452C68.x368;
    cm_80452C68.transform.target_fov = cm_80452C68.x374 = cm_80452C68.transform.fov;
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

static inline void compute_edge(Vec3 *forward, Vec3 *eye_pos, f32 fov, f32* value)
{
    f32 s;
    f32 c;
    f32 edge_x;
    f32 edge_z;

    s = sinf(fov);
    c = cosf(fov);
    edge_x = (forward->x * c) + (forward->z * s);
    edge_z = (forward->z * c) - (forward->x * s);

    if ((fabs_inline(edge_z) > 0.0001) && ((forward->z * edge_z) > 0.0)) {
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
    f32 aspect;
    f32 half_fov;
    Vec3 forward;
    Vec3 interest_pos;
    Vec3 eye_pos;
    bool b_r30;
    PAD_STACK(8);

    cobj = GET_COBJ(cm_80452C68.gobj);
    aspect = HSD_CObjGetAspect(cobj);
    half_fov = (0.5 * (deg_to_rad * HSD_CObjGetFov(cobj) * aspect));

    b_r30 = true;
    HSD_CObjGetEyePosition(cobj, &eye_pos);
    HSD_CObjGetEyeVector(cobj, &forward);
    HSD_CObjGetInterest(cobj, &interest_pos);

    if (fabs_inline(forward.x) > cm_804D7EE8) {
        if (fabs_inline(forward.z) > cm_804D7EE8) {
            // ray casts?
            forward.x *= -1.0f;
            forward.y *= -1.0f;
            forward.z *= -1.0f;
            *center = -((forward.x * (eye_pos.z / forward.z)) - eye_pos.x);

            compute_edge(&forward, &eye_pos, half_fov, left);
            compute_edge(&forward, &eye_pos, -half_fov, right);
        }
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
    cm_80452C68.x399_b5 = arg0 == 0;
}

bool Camera_80030AC4(void)
{
    return cm_80452C68.x399_b5 == 0;
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
    if (cm_80452C68.x2B8 < 1) {
        return 10000.f;
    }
    return cm_80452C68.x2B0;
}

void Camera_80030E34(f32 arg8)
{
    cm_80452C68.xAC = arg8;
}

/// #Camera_80030E44

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
