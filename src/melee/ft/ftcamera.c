#include "ftcamera.h"

#include "ftlib.h"

#include "ft/fighter.h"
#include "ft/types.h"
#include "gr/stage.h"

#include <dolphin/mtx.h>
#include <baselib/debug.h>

void ftCamera_80076018(UnkFloat6_Camera* in, UnkFloat6_Camera* out, float mul)
{
    out->x0.x = in->x0.x * mul;
    out->x0.y = in->x0.y * mul;
    out->x0.z = in->x0.z * mul;
    out->xC.x = in->xC.x * mul;
    out->xC.y = in->xC.y * mul;
    out->xC.z = in->xC.z * mul;
}

// Camera_CopyPlayerPositionToCameraBoxPosition
void ftCamera_80076064(Fighter* fp)
{
    CmSubject* camera_box;
    UnkFloat6_Camera spC;
    camera_box = fp->x890_cameraBox;
    ftCamera_80076018(fp->ft_data->x3C, &spC, fp->x34_scale.y);
    camera_box->x8 = 0;
    if (fp->facing_dir == 1.0f) {
        camera_box->x40.x = spC.x0.z;
        camera_box->x40.y = spC.x0.y * Stage_GetCamFixedZoom();
        camera_box->x28 = 1.0f;
    } else {
        camera_box->x40.x = -spC.x0.y * Stage_GetCamFixedZoom();
        camera_box->x40.y = -spC.x0.z;
        camera_box->x28 = -1.0f;
    }
    spC.xC; // this line changes everything lol
    camera_box->x48.x = spC.xC.x;
    camera_box->x48.y = spC.xC.y;
    camera_box->x48.z = spC.xC.z;
    camera_box->x2C = camera_box->x40;
    camera_box->x34 = camera_box->x48;
    camera_box->x10.x = fp->cur_pos.x;
    camera_box->x10.y = fp->cur_pos.y + spC.x0.x;
    camera_box->x10.z = fp->cur_pos.z;
    camera_box->x1C = camera_box->x10;
}

// Fighter_UpdateCameraBox
// Camera_UpdatePlayerCameraBoxPosition
void ftCamera_UpdateCameraBox(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CmSubject* camera_box = fp->x890_cameraBox;

    ///@todo lol
    fp->facing_dir + 1.0f;

    {
        UnkFloat6_Camera cam_floats;

        ftCamera_80076018(fp->ft_data->x3C, &cam_floats, fp->x34_scale.y);
        if (fp->facing_dir == 1.0f) {
            camera_box->x40.x = cam_floats.x0.z;
            camera_box->x40.y = cam_floats.x0.y * Stage_GetCamFixedZoom();
            camera_box->x28 = 1.0f;
        } else {
            camera_box->x40.x = -cam_floats.x0.y * Stage_GetCamFixedZoom();
            camera_box->x40.y = -cam_floats.x0.z;
            camera_box->x28 = -1.0f;
        }

        /// @todo this line changes everything lol
        cam_floats.xC;

        camera_box->x10.x = fp->cur_pos.x;
        camera_box->x10.y = fp->cur_pos.y + cam_floats.x0.x;
        camera_box->x10.z = fp->cur_pos.z;
    }

    camera_box->xC_b0 = false;

    // Fighter_GetCameraBonePos
    ftLib_800866DC(gobj, &camera_box->x1C);
}

void ftCamera_800762F4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftLib_800866DC(gobj, &fp->x890_cameraBox->x1C);
}

void ftCamera_80076320(HSD_GObj* gobj)
{
    Vec3 center_pos;
    Fighter* fp = gobj->user_data;
    CmSubject* camera_box;
    float temp_f1;
    float temp_f31;

    camera_box = fp->x890_cameraBox;
    ftCamera_UpdateCameraBox(gobj); // Fighter_UpdateCameraBox
    Stage_UnkSetVec3TCam_Offset(&center_pos);

    if (!(Stage_GetBlastZoneTopOffset() - center_pos.y != 0.0F)) {
        __assert("ftcamera.c", 137, "stGetPlyDeadUp() - center_pos.y != 0.0F");
    }

    temp_f31 = Stage_GetBlastZoneTopOffset() - center_pos.y;
    temp_f1 = Stage_GetCamBoundsTopOffset() - center_pos.y;
    camera_box->x10.x = (camera_box->x10.x * temp_f1) / temp_f31;
    camera_box->x10.y = Stage_GetBlastZoneTopOffset();
}
