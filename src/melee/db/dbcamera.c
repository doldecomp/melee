#include "cm/camera.h"
#include "db/db.h"
#include "ft/inlines.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "lb/lbshadow.h"
#include "lb/lbvector.h"

#include <math.h>
#include <trigf.h>

/* 4A03C0 */ static char db_CameraInfoDisplay_buf[0xC0];

/// TODO does the padding mean this should be in another file before this one?
static struct {
    u32 MiscStageVisualsStatus;
    u32 unused;
} db;

static DevText* db_CameraInfoDisplay;
static u8 db_CameraInfoDisplayTimer;
static u8 db_ShowCameraInfo;

const GXColor g_bg = { 0x00, 0x00, 0x00, 0x80 };
const GXColor g_fg = { 0xFF, 0xFF, 0xFF, 0xFF };

extern CameraDebugMode cm_80453004;

void fn_SetupMiscStageVisuals(void)
{
    db.MiscStageVisualsStatus = 0;
}

void fn_CheckMiscStageEffects(int player)
{
    if ((db_ButtonsDown(player) & HSD_PAD_R) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        db.MiscStageVisualsStatus += 1;
        switch (db.MiscStageVisualsStatus) {
        default:
            fn_802270C4(1);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(0);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(0);
            db.MiscStageVisualsStatus = 0;
            break;
        case 1:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(0);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(0);
            break;
        case 2:
            fn_802270C4(1);
            Camera_80030B0C(1);
            Camera_80030A60(0);
            Camera_80030A8C(1);
            fn_8022713C(0);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 3:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(0);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 4:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(1);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(0);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 5:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(1);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(1);
            Camera_80030B64(0);
            Camera_80030B90(1);
            break;
        case 6:
            fn_802270C4(0);
            Camera_80030B0C(0);
            Camera_80030A60(1);
            Camera_80030A8C(1);
            fn_8022713C(1);
            Camera_80030B38(0);
            Camera_80030B64(1);
            Camera_80030B90(1);
            break;
        }
    }
    if ((db_ButtonsDown(player) & HSD_PAD_X) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        switch (db_MiscVisualEffectsStatus) {
        case 0:
        case 1:
            Ground_ApplyStageBackgroundColor();
            Camera_SetStageVisible(1);
            break;
        default:
            Camera_SetStageVisible(0);
            break;
        }
    }
}

static void fn_802270C4(int arg0)
{
    Fighter_GObj* gobj;
    Fighter* ft;
    int stack;

    for (gobj = HSD_GObj_Entities->fighters; gobj != NULL; gobj = gobj->next) {
        ft = GET_FIGHTER(gobj);
        if (ft != NULL && ft->x20A4.shadow != NULL) {
            ft->x20A4.x0_b5 = !arg0;
            lbShadow_8000EEE0(gobj);
        }
    }
}

static void fn_8022713C(int arg0)
{
    HSD_GObj* gobj;
    struct {
        u8 pad[0x10];
        UnkFlagStruct x10;
    }* thing;

    for (gobj = HSD_GObj_Entities->x14; gobj != NULL; gobj = gobj->next) {
        thing = gobj->user_data;
        if (thing != NULL) {
            thing->x10.b7 = arg0;
        }
    }
}

void fn_SetupCameraInfo(void)
{
    db_CameraInfoDisplay = NULL;
    db_CameraInfoDisplayTimer = 0;
    db_ShowCameraInfo = 0;
}

static void fn_CheckCameraInfo_helper(void)
{
    GXColor bg = g_bg;
    GXColor fg = g_fg;
    HSD_GObj* gobj = DevText_GetGObj();
    if (db_CameraInfoDisplay == NULL && gobj != NULL) {
        if ((db_CameraInfoDisplay = DevText_Create(12, 420, 360, 32, 3,
                                                   db_CameraInfoDisplay_buf)))
        {
            DevText_Show(gobj, db_CameraInfoDisplay);
            DevText_HideCursor(db_CameraInfoDisplay);
            DevText_SetBGColor(db_CameraInfoDisplay, bg);
            DevText_SetTextColor(db_CameraInfoDisplay, fg);
            DevText_SetScale(db_CameraInfoDisplay, 12.0F, 16.0F);
            DevText_HideBackground(db_CameraInfoDisplay);
            DevText_HideText(db_CameraInfoDisplay);
        }
    }
}

static void fn_80227188(void)
{
    Vec3 camera;
    Vec3 interest;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    float fov, ang;
    int eye_x, eye_y, eye_z;
    int int_x, int_y, int_z;
    int stack;

    gobj = Camera_80030A50();
    if (db_CameraInfoDisplay != NULL) {
        if ((gobj != NULL) && (db_ShowCameraInfo != 0)) {
            if (db_CameraInfoDisplayTimer > 1) {
                cobj = gobj->hsd_obj;
                HSD_CObjGetEyePosition(cobj, &camera);
                HSD_CObjGetInterest(cobj, &interest);
                fov = HSD_CObjGetFov(cobj);
                ang = rad_to_deg *
                      atan2f(interest.y - camera.y, -(interest.z - camera.z));
                DevText_Erase(db_CameraInfoDisplay);
                DevText_SetCursorXY(db_CameraInfoDisplay, 0, 0);
                if (ABS(camera.z) > 99999.0F) {
                    eye_z = -1;
                } else {
                    eye_z = camera.z;
                }
                if (ABS(camera.y) > 99999.0F) {
                    eye_y = -1;
                } else {
                    eye_y = camera.y;
                }
                if (ABS(camera.x) > 99999.0F) {
                    eye_x = -1;
                } else {
                    eye_x = camera.x;
                }
                DevText_Printf(db_CameraInfoDisplay, "EYE %d,%d,%d", eye_x,
                               eye_y, eye_z);
                DevText_SetCursorXY(db_CameraInfoDisplay, 0, 1);
                if (ABS(interest.z) > 99999.0F) {
                    int_z = -1;
                } else {
                    int_z = interest.z;
                }
                if (ABS(interest.y) > 99999.0F) {
                    int_y = -1;
                } else {
                    int_y = interest.y;
                }
                if (ABS(interest.x) > 99999.0F) {
                    int_x = -1;
                } else {
                    int_x = interest.x;
                }
                DevText_Printf(db_CameraInfoDisplay, "INT %d,%d,%d", int_x,
                               int_y, int_z);
                DevText_SetCursorXY(db_CameraInfoDisplay, 0, 2);
                DevText_Printf(db_CameraInfoDisplay, "FOV %d  ANG %d",
                               (int) fov, (int) ang);
                DevText_ShowBackground(db_CameraInfoDisplay);
                DevText_ShowText(db_CameraInfoDisplay);
            } else if (db_CameraInfoDisplayTimer == 1) {
                DevText_HideBackground(db_CameraInfoDisplay);
                DevText_HideText(db_CameraInfoDisplay);
            } else {
                return;
            }
            db_CameraInfoDisplayTimer--;
        } else {
            DevText_HideBackground(db_CameraInfoDisplay);
            DevText_HideText(db_CameraInfoDisplay);
        }
    }
}

void fn_CheckCameraInfo(int player, int buttons_down, int buttons_pressed,
                        f32 cstick_x, f32 cstick_y)
{
    if (gm_8018841C() == 0 && gm_801A4310() != 0xA) {
        if (Camera_80030178() == 0 && Camera_80030154() == 0 &&
            (ABS(cstick_x) > 0.6F || ABS(cstick_y) > 0.6F))
        {
            fn_CheckCameraInfo_helper();
            Camera_8003006C();
        } else {
            if (buttons_pressed & HSD_PAD_DPADUP) {
                fn_CheckCameraInfo_helper();
                if ((buttons_down &
                     (HSD_PAD_Y | HSD_PAD_X | HSD_PAD_L | HSD_PAD_R)) == 0)
                {
                    if (Camera_80030178() != 0) {
                        Camera_8002FEEC(player);
                    } else if (Camera_80030154() != 0) {
                        Camera_800300F0();
                    } else {
                        Camera_8003006C();
                    }
                }
            }
        }
    }
    if (Camera_80030154() != 0) {
        fn_802277E8(Camera_80030A50(), player);
    } else if (Camera_80030178() != 0) {
        fn_80227904(Camera_80030A50(), player);
    }
    if (Camera_80030178() != 0 && db.MiscStageVisualsStatus - 3 <= 1) {
        if (buttons_pressed & HSD_PAD_B) {
            db_ShowCameraInfo = !db_ShowCameraInfo;
        }
    } else {
        db_ShowCameraInfo = 0;
    }
    fn_80227188();
    if ((db_ButtonsDown(player) & HSD_PAD_X) &&
        (db_ButtonsPressed(player) & HSD_PAD_DPADDOWN))
    {
        switch (db_MiscVisualEffectsStatus) {
        case 2:
            Camera_SetBackgroundColor(0xFF, 0xFF, 0xFF);
            break;
        case 3:
            Camera_SetBackgroundColor(0, 0, 0);
            break;
        }
    }
}

/// #fn_802277E8

static inline HSD_PadStatus* get_pad(u8 i)
{
    return &HSD_PadMasterStatus[i];
}

static inline float cstick_threshold(float cstick, float val)
{
    if (ABS(cstick) < val) {
        return 0;
    }
    return cstick;
}

static void fn_802277E8(HSD_GObj* arg0, int port)
{
    HSD_PadStatus* temp_r3;
    UNK_T r4;
    float cstick_x, cstick_y;
    u32 buttons;
    PAD_STACK(0x20);

    port &= 0xFF;

    cstick_x = cstick_threshold(HSD_PadMasterStatus[port].nml_subStickX, 0.2F);
    cstick_y = cstick_threshold(HSD_PadMasterStatus[port].nml_subStickY, 0.2F);

    buttons = HSD_PadMasterStatus[port].button;
    r4 = Camera_8003019C();

    if (buttons & 1) {
        fn_80227D38(arg0, r4, cstick_y);
    } else if (buttons & 2) {
        fn_80228124(arg0, r4, -cstick_x, -cstick_y);
    } else {
        fn_80227BA8(arg0, r4, cstick_x, cstick_y);
    }
}

/// Debug_UpdateCamera
static void fn_80227904(HSD_GObj* camera, int port)
{
    f32 cstick_x;
    f32 cstick_y;
    u32 buttons;

    // TODO port should probably be a u8, but it's difficult
    // to match all the functions that call this
    port &= 0xFF;

    cstick_x = cstick_threshold(HSD_PadMasterStatus[port].nml_subStickX, 0.2F);
    cstick_y = cstick_threshold(HSD_PadMasterStatus[port].nml_subStickY, 0.2F);

    buttons = HSD_PadMasterStatus[port].button;

    if (buttons & 1) {
        fn_80227CAC(camera, cstick_y);
    } else if (buttons & 2) {
        fn_80227FE0(camera, -cstick_x, -cstick_y);
    } else {
        fn_80227B64(camera, cstick_x, cstick_y);
    }
    db_CameraInfoDisplayTimer = 0x3C;
}

/// Debug_OrbitAroundInterest
void fn_802279E8(HSD_GObj* camera, Vec3* camera_pos, Vec3* camera_interest,
                 f32 cstick_x, f32 cstick_y)
{
    HSD_CObj* cobj;
    Mtx mtx;
    Vec3 forward_vec;
    Vec3 axis;
    f32 eye_dist;
    f32 pitch;
    f32 new_pitch;

    cobj = GET_COBJ(camera);
    if ((cstick_x != 0.0F) || (cstick_y != 0.0F)) {
        Vec3 up_vec = { 0, 1, 0 };
        HSD_CObjGetEyeVector(cobj, &forward_vec);
        pitch = 57.29578F * acosf(PSVECDotProduct(&forward_vec, &up_vec));
        new_pitch = 2.0F * cstick_y;
        if ((pitch + new_pitch) > 179.0F) {
            new_pitch = 179.0F - pitch;
        }
        if ((pitch + new_pitch) < 1.0F) {
            new_pitch = 1.0F - pitch;
        }
        VECCrossProduct(&up_vec, &forward_vec, &axis);
        VECNormalize(&axis, &axis);
        PSMTXRotAxisRad(mtx, &axis, 0.017453292F * new_pitch);
        MTXMultVec(mtx, &forward_vec, &forward_vec);
        eye_dist = HSD_CObjGetEyeDistance(cobj);
        PSMTXRotAxisRad(mtx, &up_vec, 0.017453292F * (2.0F * cstick_x));
        MTXMultVec(mtx, &forward_vec, &forward_vec);
        VECScale(&forward_vec, &forward_vec, eye_dist);
        VECSubtract(camera_interest, &forward_vec, camera_pos);
    }
}

/// Debug_UpdateFreecamRotation
static void fn_80227B64(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    if ((cstick_x != 0.0F) || (cstick_y != 0.0F)) {
        fn_802279E8(camera, &cm_80453004.free_eye_pos,
                    &cm_80453004.free_int_pos, cstick_x, cstick_y);
    }
}

void fn_80227BA8(HSD_GObj* camera, Vec3* arg1, f32 arg2, f32 arg3)
{
    Vec3 sp28;
    Vec3 sp1C;
    PAD_STACK(4);

    if (arg1 != NULL) {
        fn_802279E8(camera, &cm_80453004.follow_eye_offset,
                    &cm_80453004.follow_int_offset, arg2, arg3);
        sp28 = cm_80453004.follow_int_offset;
        lbVector_Add(&sp28, arg1);
        cm_80453004.follow_eye_pos = sp28;
        sp1C = cm_80453004.follow_eye_offset;
        lbVector_Add(&sp1C, arg1);
        cm_80453004.follow_int_pos = sp1C;
        return;
    }
    if (arg2 != 0.0F || arg3 != 0.0F) {
        fn_802279E8(camera, &cm_80453004.free_eye_pos,
                    &cm_80453004.free_int_pos, arg2, arg3);
    }
}

/// Debug_UpdateFreecamDolly
static void fn_80227CAC(HSD_GObj* camera, f32 cstick_y)
{
    Vec3 forward;
    HSD_CObj* cobj;

    if (cstick_y != 0.0F && cstick_y != 0.0F) {
        cobj = GET_COBJ(camera);
        HSD_CObjGetEyeVector(cobj, &forward);
        {
            float dist = HSD_CObjGetEyeDistance(cobj);
            VECScale(&forward, &forward, dist * (1.0F - 0.05F * cstick_y));
        }
        VECSubtract(&cm_80453004.free_int_pos, &forward,
                    &cm_80453004.free_eye_pos);
    }
}

void fn_80227D38(HSD_GObj* camera, Vec3* arg1, f32 arg2)
{
    Vec3 sp40;
    Vec3 sp34;
    Vec3 sp28;
    Vec3 sp1C;
    HSD_CObj* cobj;
    float dist;

    if (arg1 != NULL) {
        if (arg2 != 0.0F) {
            cobj = GET_COBJ(camera);
            HSD_CObjGetEyeVector(cobj, &sp28);
            dist = HSD_CObjGetEyeDistance(cobj);
            PSVECScale(&sp28, &sp28, dist * -(0.05F * arg2 - 1.0F));
            PSVECSubtract(&cm_80453004.follow_int_offset, &sp28,
                          &cm_80453004.follow_eye_offset);
        }
        sp40 = cm_80453004.follow_int_offset;
        lbVector_Add(&sp40, arg1);
        cm_80453004.follow_eye_pos = sp40;
        sp34 = cm_80453004.follow_eye_offset;
        lbVector_Add(&sp34, arg1);
        cm_80453004.follow_int_pos = sp34;
    } else {
        if (arg2 != 0.0F && arg2 != 0.0F) {
            cobj = GET_COBJ(camera);
            HSD_CObjGetEyeVector(cobj, &sp1C);
            dist = HSD_CObjGetEyeDistance(cobj);
            PSVECScale(&sp1C, &sp1C, dist * -(0.05F * arg2 - 1.0F));
            PSVECSubtract(&cm_80453004.free_int_pos, &sp1C,
                          &cm_80453004.free_eye_pos);
        }
    }
}

static void fn_80227EB0(HSD_GObj* arg0, Vec3* arg1, Vec3* arg2, f32 arg8,
                        f32 arg9)
{
    Vec3 sp2C;
    Vec3 sp20;
    HSD_CObj* cobj;
    f32 dist;

    cobj = GET_COBJ(arg0);
    dist = HSD_CObjGetEyeDistance(cobj);
    dist =
        0.03F * (2.0F * (dist * tanf(deg_to_rad * HSD_CObjGetFov(cobj) / 2)));
    if (arg8 != 0.0F) {
        HSD_CObjGetLeftVector(cobj, &sp2C);
        PSVECScale(&sp2C, &sp2C, dist * arg8);
        PSVECAdd(arg2, &sp2C, arg2);
        PSVECAdd(arg1, &sp2C, arg1);
    }
    if (arg9 != 0.0F) {
        HSD_CObjGetUpVector(cobj, &sp20);
        PSVECScale(&sp20, &sp20, -dist * arg9);
        PSVECAdd(arg2, &sp20, arg2);
        PSVECAdd(arg1, &sp20, arg1);
    }
}

/// Debug_UpdateFreecamPosition
static void fn_80227FE0(HSD_GObj* camera, f32 cstick_x, f32 cstick_y)
{
    Vec3 up_vec;
    Vec3 left_vec;
    // fake temp variables?
    // probably an inline for getting the scale factor
    Vec3* temp_r3;
    Vec3* temp_r3_2;
    Vec3* temp_r3_3;
    Vec3* temp_r3_4;
    f32 eye_dist;
    f32 scale_factor;
    HSD_CObj* cobj;

    if ((cstick_x != 0.0F) || (cstick_y != 0.0F)) {
        cobj = GET_COBJ(camera);
        eye_dist = HSD_CObjGetEyeDistance(cobj);
        scale_factor =
            0.03F *
            (2.0F * (eye_dist * tanf(deg_to_rad * HSD_CObjGetFov(cobj) / 2)));
        if (cstick_x != 0.0F) {
            HSD_CObjGetLeftVector(cobj, &left_vec);
            VECScale(&left_vec, &left_vec, scale_factor * cstick_x);
            temp_r3 = &cm_80453004.free_int_pos;
            VECAdd(temp_r3, &left_vec, temp_r3);
            temp_r3_2 = &cm_80453004.free_eye_pos;
            VECAdd(temp_r3_2, &left_vec, temp_r3_2);
        }
        if (cstick_y != 0.0F) {
            HSD_CObjGetUpVector(cobj, &up_vec);
            VECScale(&up_vec, &up_vec, -scale_factor * cstick_y);
            temp_r3_3 = &cm_80453004.free_int_pos;
            VECAdd(&cm_80453004.free_int_pos, &up_vec, temp_r3_3);
            temp_r3_4 = &cm_80453004.free_eye_pos;
            VECAdd(temp_r3_4, &up_vec, temp_r3_4);
        }
    }
}

static inline void fn_80227EB0_dummy_inline(HSD_GObj* cam, Vec3* a, Vec3* b,
                                            float x, float y)
{
    if (x != 0.0F || y != 0.0F) {
        fn_80227EB0(cam, a, b, x, y);
    }
}

void fn_80228124(HSD_GObj* camera, Vec3* arg1, f32 arg2, f32 arg3)
{
    u8 _2[4];
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;
    f32 dist;
    HSD_CObj* cobj;
    u8 _[4];

    if (arg1 != NULL) {
        cobj = GET_COBJ(camera);
        dist = HSD_CObjGetEyeDistance(cobj);
        dist = 0.03f *
               (2.0f * (dist * tanf(0.017453292f * HSD_CObjGetFov(cobj) / 2)));
        if (arg2 != 0.0f) {
            HSD_CObjGetLeftVector(cobj, &sp20);
            PSVECScale(&sp20, &sp20, dist * arg2);
            PSVECAdd(&cm_80453004.follow_int_offset, &sp20,
                     &cm_80453004.follow_int_offset);
            PSVECAdd(&cm_80453004.follow_eye_offset, &sp20,
                     &cm_80453004.follow_eye_offset);
        }
        if (arg3 != 0.0f) {
            HSD_CObjGetUpVector(cobj, &sp2C);
            PSVECScale(&sp2C, &sp2C, -dist * arg3);
            PSVECAdd(&cm_80453004.follow_int_offset, &sp2C,
                     &cm_80453004.follow_int_offset);
            PSVECAdd(&cm_80453004.follow_eye_offset, &sp2C,
                     &cm_80453004.follow_eye_offset);
        }
        sp44 = cm_80453004.follow_int_offset;
        lbVector_Add(&sp44, arg1);
        cm_80453004.follow_eye_pos = sp44;
        sp38 = cm_80453004.follow_eye_offset;
        lbVector_Add(&sp38, arg1);
        cm_80453004.follow_int_pos = sp38;
    } else {
        fn_80227EB0_dummy_inline(camera, &cm_80453004.free_eye_pos,
                                 &cm_80453004.free_int_pos, arg2, arg3);
    }
}
