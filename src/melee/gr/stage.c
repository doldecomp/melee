#include "melee/gr/stage.h"

extern struct _StageInfo stage_info;

extern f32 degrees_2_radians; // 0.017453f
extern f32 unk_one_half_const_804DBCD8; // 0.5
extern f32 unk_zero_const_804DBCD8; //0.0

f32 get_cam_bounds_left_offset()
{
    return stage_info.cam_info.cam_bounds_left + stage_info.cam_info.cam_x_offset;
}

f32 get_cam_bounds_right_offset()
{
    return stage_info.cam_info.cam_bounds_right + stage_info.cam_info.cam_x_offset;
}

f32 get_cam_bounds_top_offset()
{
    return stage_info.cam_info.cam_bounds_top + stage_info.cam_info.cam_y_offset;
}

f32 get_cam_bounds_bottom_offset()
{
    return stage_info.cam_info.cam_bounds_bottom + stage_info.cam_info.cam_y_offset;
}

f32 get_cam_pan_angle_radians()
{
    return degrees_2_radians * stage_info.cam_info.cam_pan_degrees;
}

f32 get_cam_max_depth()
{
    return stage_info.cam_info.cam_max_depth;
}

f32 get_cam_zoom_rate()
{
    return stage_info.cam_info.cam_zoom_rate;
}

f32 get_cam_info_x20() {
    return stage_info.cam_info.x20;
}

f32 get_cam_info_x24() {
    return stage_info.cam_info.x24;
}

f32 get_cam_fixed_zoom() {
    return stage_info.cam_info.cam_fixed_zoom;
}

f32 get_cam_track_ratio() {
    return stage_info.cam_info.cam_track_ratio;
}

f32 get_cam_track_smooth() {
    return stage_info.cam_info.cam_track_smooth;
}

f32 get_blast_zone_right_offset() {
    return stage_info.blast_zone.right + stage_info.cam_info.cam_x_offset;
}

f32 get_blast_zone_left_offset() {
    return stage_info.blast_zone.left + stage_info.cam_info.cam_x_offset;
}

f32 get_blast_zone_top_offset() {
    return stage_info.blast_zone.top + stage_info.cam_info.cam_y_offset;
}

f32 get_blast_zone_bottom_offset() {
   return stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset;
}

f32 calc_unk_cam_y_80224B98() {
    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 y_pos = stage_info.cam_info.cam_bounds_bottom + cam_y_offset + (stage_info.blast_zone.bottom + cam_y_offset);
    return unk_one_half_const_804DBCD8 * y_pos;
}

f32 calc_unk_cam_y_bounds_80224BC4() {

    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 cam_bounds_bottom_offset = stage_info.cam_info.cam_bounds_bottom + cam_y_offset;

    f32 y_pos = stage_info.blast_zone.bottom + cam_y_offset + cam_bounds_bottom_offset;
    f32 y_pos_product = unk_one_half_const_804DBCD8 * y_pos;

    return unk_one_half_const_804DBCD8 * (cam_bounds_bottom_offset + y_pos_product);
}

f32 unk_set_vec3_to_cam_offset_80224BF8(Vec *vec3, f32 arg8) {
    vec3->x = stage_info.cam_info.cam_x_offset;
    vec3->y = stage_info.cam_info.cam_y_offset;
    vec3->z = unk_zero_const_804DBCD8;
    return arg8;
}

f32 get_pausecam_zpos_min() { 
    return stage_info.cam_info.pausecam_zpos_min;
}

f32 get_pausecam_zpos_init() {
    return stage_info.cam_info.pausecam_zpos_init;
}

f32 get_pausecam_zpos_max() { 
    return stage_info.cam_info.pausecam_zpos_max;
}

f32 get_cam_angle_radians_up() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_up;
}

f32 get_cam_angle_radians_down() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_down;
}

f32 get_cam_angle_radians_left() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_left;
}

f32 get_cam_angle_radians_right() {
    return degrees_2_radians * stage_info.cam_info.cam_angle_right;
}

