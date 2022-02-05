#ifndef _stage_h_
#define _stage_h_

#include <global.h>

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>


// This struct is based in part on the datasheet
// however the info there is likely incorrect as this doesn't quite match grGroundParam
typedef struct _StageCameraInfo {
    f32 cam_bounds_left; // 0x0
    f32 cam_bounds_right; // 0x4
    f32 cam_bounds_top; // 0x8
    f32 cam_bounds_bottom; // 0xC
    f32 cam_x_offset; // 0x10
    f32 cam_y_offset; // 0x14
    f32 cam_vertical_tilt; // 0x18
    f32 cam_pan_degrees; // 0x1C
    f32 x20; // 0x20
    f32 x24; // 0x24
    f32 cam_track_ratio; // 0x28
    f32 cam_fixed_zoom; // 0x2C
    f32 cam_track_smooth; // 0x30
    f32 cam_zoom_rate; // 0x34
    f32 cam_max_depth; // 0x38
    f32 x3C; // 0x3C
    f32 pausecam_zpos_min; // 0x40
    f32 pausecam_zpos_init; // 0x44
    f32 pausecam_zpos_max; // 0x48
    f32 cam_angle_up; // 0x4C
    f32 cam_angle_down; // 0x50
    f32 cam_angle_left; // 0x54
    f32 cam_angle_right; // 0x58
    Vec fixed_cam_pos; // 0x5C - 0x64
    f32 fixed_cam_fov; // 0x68
    f32 fixed_cam_vert_angle; // 0x6C
    f32 fixed_cam_horz_angle; // 0x70
} StageCameraInfo;

typedef struct _StageBlastZone {
    f32 left; // 0x74
    f32 right; // 0x78
    f32 top; // 0x7C
    f32 bottom; // 0x80
} StageBlastZone;

typedef struct _StageInfo {
    StageCameraInfo cam_info; // 0x00 - 0x70
    StageBlastZone blast_zone; // 0x74 - 0x80

    u32 x84; // 0x84

    u32 internal_stage_id; // 0x88

    s8 unk8C;
    u8 data[0x6EB];
} StageInfo;

f32 get_cam_bounds_left_offset();
f32 get_cam_bounds_right_offset();
f32 get_cam_bounds_top_offset();
f32 get_cam_bounds_bottom_offset();
f32 get_cam_pan_angle_radians();
f32 get_cam_max_depth();
f32 get_cam_zoom_rate();
f32 get_cam_info_x20();
f32 get_cam_info_x24();
f32 get_cam_fixed_zoom();
f32 get_cam_track_ratio();
f32 get_cam_track_smooth();
f32 get_blast_zone_right_offset();
f32 get_blast_zone_left_offset();
f32 get_blast_zone_top_offset();
f32 get_blast_zone_bottom_offset();
f32 calc_unk_cam_y_80224B98();
f32 calc_unk_cam_y_bounds_80224BC4();
f32 unk_set_vec3_to_cam_offset_80224BF8(Vec* vec3, f32 arg8);
f32 get_pausecam_zpos_min();
f32 get_pausecam_zpos_init();
f32 get_pausecam_zpos_max();
f32 get_cam_angle_radians_up();
f32 get_cam_angle_radians_down();
f32 get_cam_angle_radians_left();
f32 get_cam_angle_radians_right();
void func_80224CAC(Vec* arg0);
void set_vec_to_fixed_cam_pos(Vec* arg0);
f32 get_cam_fixed_fov();
BOOL func_80224DC8(s32 arg);
void func_80224E38(Vec* arg0, s32 arg1);
void func_80224E64(s32 arg0, Vec* arg_vec);
s32 func_80224FDC(Vec* arg0);
s32 func_80225074(s32 arg0);
s32 func_80225194();
s32 func_8022519C(s32 idx);
s32 func_802251B4(s32 idx, s32 arg1);
void func_802251E8(s32 idx, s32* unused);
void func_8022524C();
void func_80225298();
void func_802252E4(s32 idx, s32 unused);
void func_8022532C(s32 idx, s32 arg1);

#endif
