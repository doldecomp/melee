#include "melee/gr/stage.h"

extern struct _StageInfo stage_info;

extern f32 unk_multiplier_804DBCD8;

extern f32 lbl_804DBCD0; // 0.017453f

f32 func_80224A54()
{
    return stage_info.cam_info.cam_bounds_left + stage_info.cam_info.cam_x_offset;
}

f32 func_80224A68()
{
    return stage_info.cam_info.cam_bounds_right + stage_info.cam_info.cam_x_offset;
}

f32 func_80224A80()
{
    return stage_info.cam_info.cam_bounds_top + stage_info.cam_info.cam_y_offset;
}

f32 func_80224A98()
{
    return stage_info.cam_info.cam_bounds_bottom + stage_info.cam_info.cam_y_offset;
}

f32 func_80224AB0()
{
    return lbl_804DBCD0 * stage_info.cam_info.cam_pan_degrees;
}

f32 func_80224AC8()
{
    return stage_info.cam_info.cam_max_depth;
}

f32 func_80224AD8()
{
    return stage_info.cam_info.cam_zoom_rate;
}

f32 func_80224AE8() {
    return stage_info.cam_info.x20;
}

f32 func_80224AF8() {
    return stage_info.cam_info.x24;
}

f32 func_80224B08() {
    return stage_info.cam_info.cam_fixed_zoom;
}

f32 func_80224B18() {
    return stage_info.cam_info.cam_track_ratio;
}

f32 func_80224B28() {
    return stage_info.cam_info.cam_track_smooth;
}

f32 func_80224B38() {
    return stage_info.blast_zone.right + stage_info.cam_info.cam_x_offset;
}

f32 func_80224B50() {
    return stage_info.blast_zone.left + stage_info.cam_info.cam_x_offset;
}

f32 func_80224B68() {
    return stage_info.blast_zone.top + stage_info.cam_info.cam_y_offset;
}

f32 func_80224B80() {
   return stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset;
}

f32 func_80224B98() {
    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 y_pos = stage_info.cam_info.cam_bounds_bottom + cam_y_offset + (stage_info.blast_zone.bottom + cam_y_offset);
    return unk_multiplier_804DBCD8 * y_pos;
}

f32 func_80224BC4() {

    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 cam_bounds_bottom_offset = stage_info.cam_info.cam_bounds_bottom + cam_y_offset;

    f32 y_pos = stage_info.blast_zone.bottom + cam_y_offset + cam_bounds_bottom_offset;
    f32 y_pos_product = unk_multiplier_804DBCD8 * y_pos;

    return unk_multiplier_804DBCD8 * (cam_bounds_bottom_offset + y_pos_product);
}


