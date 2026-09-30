/**
 * @file ftcamera.c
 * @brief Handles fighter camera tracking and bounding boxes
 * @details Manages how the camera calculates its bounding box around fighters, tracking player positions, zooming, and panning based on player distance.
 * Module prefix: ft (Fighter)
 */

#include "ftcamera.h"

#include "fighter.h"
#include "ftlib.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/gr/stage.h>
#include <sysdolphin/baselib/debug.h>

/**
 * @brief Scales camera box float arrays by a multiplier
 * @param in Input camera float array
 * @param out Output camera float array
 * @param mul Multiplier to scale by (usually fighter scale)
 */
void ftCamera_80076018(UnkFloat6_Camera* in, UnkFloat6_Camera* out, float mul)
{
    out->x0.x = in->x0.x * mul;
    out->x0.y = in->x0.y * mul;
    out->x0.z = in->x0.z * mul;
    out->xC.x = in->xC.x * mul;
    out->xC.y = in->xC.y * mul;
    out->xC.z = in->xC.z * mul;
}

/**
 * @brief Initializes and copies the player position to the camera subject box
 * @param fp Fighter instance data
 */
void ftCamera_80076064(Fighter* fp)
{
    CmSubject* camera_box;
    UnkFloat6_Camera scaled_cam_floats;
    camera_box = fp->x890_cameraBox;

    // Scale camera bounds by the fighter's Y scale
    ftCamera_80076018(fp->ft_data->x3C, &scaled_cam_floats, fp->x34_scale.y);
    camera_box->state = CmSubjectState_Active;

    // Set horizontal bounds based on facing direction
    if (fp->facing_dir == 1.0f) {
        camera_box->target_ext.h.x = scaled_cam_floats.x0.z;
        camera_box->target_ext.h.y = scaled_cam_floats.x0.y * Stage_GetCamFixedZoom();
        camera_box->facing_dir = 1.0f;
    } else {
        camera_box->target_ext.h.x = -scaled_cam_floats.x0.y * Stage_GetCamFixedZoom();
        camera_box->target_ext.h.y = -scaled_cam_floats.x0.z;
        camera_box->facing_dir = -1.0f;
    }

    scaled_cam_floats.xC; // this line changes everything lol

    // Set vertical bounds
    camera_box->target_ext.v.x = scaled_cam_floats.xC.x;
    camera_box->target_ext.v.y = scaled_cam_floats.xC.y;
    camera_box->target_ext.v.z = scaled_cam_floats.xC.z;

    // Apply targets immediately
    camera_box->ext.h = camera_box->target_ext.h;
    camera_box->ext.v = camera_box->target_ext.v;

    // Set absolute position
    camera_box->pos.x = fp->cur_pos.x;
    camera_box->pos.y = fp->cur_pos.y + scaled_cam_floats.x0.x;
    camera_box->pos.z = fp->cur_pos.z;
    camera_box->bone_pos = camera_box->pos;
}

/**
 * @brief Updates the camera subject bounding box based on player position and facing direction
 * @param gobj Fighter GObj
 */
void ftCamera_UpdateCameraBox(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CmSubject* camera_box = fp->x890_cameraBox;

    ///@todo lol
    fp->facing_dir + 1.0f;

    {
        UnkFloat6_Camera cam_floats;

        // Scale camera bounds by the fighter's Y scale
        ftCamera_80076018(fp->ft_data->x3C, &cam_floats, fp->x34_scale.y);

        // Update horizontal bounds targets based on facing direction
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

        // Update absolute position
        camera_box->pos.x = fp->cur_pos.x;
        camera_box->pos.y = fp->cur_pos.y + cam_floats.x0.x;
        camera_box->pos.z = fp->cur_pos.z;
    }

    camera_box->on_ledge = false;

    // Update the position of the camera relative to the fighter's skeleton
    ftLib_GetCameraBonePos(gobj, &camera_box->bone_pos);
}

/**
 * @brief Updates the camera bone position for the given fighter
 * @param gobj Fighter GObj
 */
void ftCamera_800762F4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftLib_GetCameraBonePos(gobj, &fp->x890_cameraBox->bone_pos);
}

/**
 * @brief Updates the camera subject when a fighter hits the upper blast zone (Star KO/Screen KO)
 * @param gobj Fighter GObj
 */
void ftCamera_80076320(HSD_GObj* gobj)
{
    Vec3 center_pos;
    Fighter* fp = gobj->user_data;
    CmSubject* camera_box;
    float cam_bounds_top_dist;
    float blast_zone_top_dist;

    camera_box = fp->x890_cameraBox;
    ftCamera_UpdateCameraBox(gobj); // Fighter_UpdateCameraBox
    Stage_UnkSetVec3TCam_Offset(&center_pos);

    HSD_ASSERTMSG(137, Stage_GetBlastZoneTopOffset() - center_pos.y != 0.0F,
                  "stGetPlyDeadUp() - center_pos.y != 0.0F");

    // Calculate vertical distances relative to the center offset
    blast_zone_top_dist = Stage_GetBlastZoneTopOffset() - center_pos.y;
    cam_bounds_top_dist = Stage_GetCamBoundsTopOffset() - center_pos.y;

    // Scale X position based on how far up the blast zone is compared to camera bounds
    camera_box->pos.x = (camera_box->pos.x * cam_bounds_top_dist) / blast_zone_top_dist;
    camera_box->pos.y = Stage_GetBlastZoneTopOffset();
}
