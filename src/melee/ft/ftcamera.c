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

/// Camera_CopyPlayerPositionToCameraBoxPosition
void ftCamera_80076064(Fighter* fp)
{
    CmSubject* camera_box;
    UnkFloat6_Camera spC;
    camera_box = fp->x890_cameraBox;
    ftCamera_80076018(fp->ft_data->x3C, &spC, fp->x34_scale.y);
    camera_box->state = CmSubjectState_Active;
    if (fp->facing_dir == 1.0f) {
        camera_box->target_ext.h.x = spC.x0.z;
        camera_box->target_ext.h.y = spC.x0.y * Stage_GetCamFixedZoom();
        camera_box->facing_dir = 1.0f;
    } else {
        camera_box->target_ext.h.x = -spC.x0.y * Stage_GetCamFixedZoom();
        camera_box->target_ext.h.y = -spC.x0.z;
        camera_box->facing_dir = -1.0f;
    }
    spC.xC; // this line changes everything lol
    camera_box->target_ext.v.x = spC.xC.x;
    camera_box->target_ext.v.y = spC.xC.y;
    camera_box->target_ext.v.z = spC.xC.z;
    camera_box->ext.h = camera_box->target_ext.h;
    camera_box->ext.v = camera_box->target_ext.v;
    camera_box->pos.x = fp->cur_pos.x;
    camera_box->pos.y = fp->cur_pos.y + spC.x0.x;
    camera_box->pos.z = fp->cur_pos.z;
    camera_box->bone_pos = camera_box->pos;
}

/// Fighter_UpdateCameraBox
/// Camera_UpdatePlayerCameraBoxPosition
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
            camera_box->target_ext.h.x = cam_floats.x0.z;
            camera_box->target_ext.h.y =
                cam_floats.x0.y * Stage_GetCamFixedZoom();
            camera_box->facing_dir = 1.0f;
        } else {
            camera_box->target_ext.h.x =
                -cam_floats.x0.y * Stage_GetCamFixedZoom();
            camera_box->target_ext.h.y = -cam_floats.x0.z;
            camera_box->facing_dir = -1.0f;
        }

        /// @todo this line changes everything lol
        cam_floats.xC;

        camera_box->pos.x = fp->cur_pos.x;
        camera_box->pos.y = fp->cur_pos.y + cam_floats.x0.x;
        camera_box->pos.z = fp->cur_pos.z;
    }

    camera_box->on_ledge = false;

    // Fighter_GetCameraBonePos
    ftLib_800866DC(gobj, &camera_box->bone_pos);
}

void ftCamera_800762F4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftLib_800866DC(gobj, &fp->x890_cameraBox->bone_pos);
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

    HSD_ASSERTMSG(137, Stage_GetBlastZoneTopOffset() - center_pos.y != 0.0F,
                  "stGetPlyDeadUp() - center_pos.y != 0.0F");

    temp_f31 = Stage_GetBlastZoneTopOffset() - center_pos.y;
    temp_f1 = Stage_GetCamBoundsTopOffset() - center_pos.y;
    camera_box->pos.x = (camera_box->pos.x * temp_f1) / temp_f31;
    camera_box->pos.y = Stage_GetBlastZoneTopOffset();
}
