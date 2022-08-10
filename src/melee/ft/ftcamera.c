#include "fighter.h"

typedef struct UnkFloat6_Camera {
    Vec3 x0;
    Vec3 xC;
} UnkFloat6_Camera;

void func_80076018(UnkFloat6_Camera* in, UnkFloat6_Camera* out, f32 mul) {
    out->x0.x = in->x0.x * mul;
    out->x0.y = in->x0.y * mul;
    out->x0.z = in->x0.z * mul;
    out->xC.x = in->xC.x * mul;
    out->xC.y = in->xC.y * mul;
    out->xC.z = in->xC.z * mul;
}

// Camera_CopyPlayerPositionToCameraBoxPosition
void func_80076064(Fighter* ft) {
    CameraBox* camera_box;
    UnkFloat6_Camera* ftData_floats;
    UnkFloat6_Camera spC;

    camera_box = ft->x890_cameraBox;
    func_80076018(ft->x10C_ftData->x3C, &spC, ft->x34_scale.y);
    camera_box->x8 = 0;
    if (ft->x2C_facing_direction == 1.0f) {
        camera_box->x40.x = spC.x0.z;
        camera_box->x40.y = spC.x0.y * Stage_GetCamFixedZoom();
        camera_box->x28 = 1.0f;
    } else {
        camera_box->x40.x = -spC.x0.y * Stage_GetCamFixedZoom();
        camera_box->x40.y = -spC.x0.z;
        camera_box->x28 = -1.0f;
    }
    spC.xC; //this line changes everything lol
    camera_box->x48.x = spC.xC.x;
    camera_box->x48.y = spC.xC.y;
    camera_box->x48.z = spC.xC.z;
    camera_box->x2C = camera_box->x40;
    camera_box->x34 = camera_box->x48;
    camera_box->x10.x = ft->xB0_pos.x;
    camera_box->x10.y = ft->xB0_pos.y + spC.x0.x;
    camera_box->x10.z = ft->xB0_pos.z;
    camera_box->x1C = camera_box->x10;
}

// Fighter_UpdateCameraBox
// Camera_UpdatePlayerCameraBoxPosition
void func_800761C8(HSD_GObj* gobj) {
    Fighter* ft;
    CameraBox* camera_box;
    UnkFloat6_Camera sp10;
    s32 unused;

    ft = gobj->user_data;
    camera_box = ft->x890_cameraBox;
    ft->x2C_facing_direction + 1.0f; // lol
    func_80076018(ft->x10C_ftData->x3C, &sp10, ft->x34_scale.y);
    if (ft->x2C_facing_direction == 1.0f) {
        camera_box->x40.x = sp10.x0.z;
        camera_box->x40.y = sp10.x0.y * Stage_GetCamFixedZoom();
        camera_box->x28 = 1.0f;
    } else {
        camera_box->x40.x = -sp10.x0.y * Stage_GetCamFixedZoom();
        camera_box->x40.y = -sp10.x0.z;
        camera_box->x28 = -1.0f;
    }
    sp10.xC; //this line changes everything lol
    camera_box->x10.x = ft->xB0_pos.x;
    camera_box->x10.y = ft->xB0_pos.y + sp10.x0.x;
    camera_box->x10.z = ft->xB0_pos.z;
    camera_box->xC_flag.bits.b0 = 0;
    func_800866DC(gobj, &camera_box->x1C); // Fighter_GetCameraBonePos
}

void func_800762F4(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_800866DC(gobj, &ft->x890_cameraBox->x1C);
}

void func_80076320(HSD_GObj* gobj) {
    Vec3 center_pos;
    Fighter* ft = gobj->user_data;
    CameraBox* camera_box;
    f32 temp_f1;
    f32 temp_f31;

    camera_box = ft->x890_cameraBox;
    func_800761C8(gobj); // Fighter_UpdateCameraBox
    Stage_UnkSetVec3TCam_Offset(&center_pos);

    if (!(Stage_GetBlastZoneTopOffset() - center_pos.y != 0.0F)) {
        __assert("ftcamera.c", 137, "stGetPlyDeadUp() - center_pos.y != 0.0F");
    }

    temp_f31 = Stage_GetBlastZoneTopOffset() - center_pos.y;
    temp_f1 = Stage_GetCamBoundsTopOffset() - center_pos.y;
    camera_box->x10.x = (camera_box->x10.x * temp_f1) / temp_f31;
    camera_box->x10.y = Stage_GetBlastZoneTopOffset();
}
