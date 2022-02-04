#include "melee/gr/stage.h"

#include "melee/lb/lbvector.h"

extern struct _StageInfo stage_info;

struct StructStageIDWithUnks {
    s32 stage_id;
    s32 unk1;
    s32 unk2;
};
struct StructNumberAndStage {
    s32 list_idx;
    struct StructStageIDWithUnks* unk_struct;
};
struct StructPairWithStageID {
    s32 stage_id;
    s32 list_idx;
};

struct StructNumberAndStage unk_struct_804D49E8 = { 2, NULL };
struct StructPairWithStageID unk_struct_804D49F0 = { 12, 2 };
extern struct StructStageIDWithUnks unk_arr_803E9960[];

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
    return 0.0174532923847F * stage_info.cam_info.cam_pan_degrees;
}

f32 get_cam_max_depth()
{
    return stage_info.cam_info.cam_max_depth;
}

f32 get_cam_zoom_rate()
{
    return stage_info.cam_info.cam_zoom_rate;
}

f32 get_cam_info_x20()
{
    return stage_info.cam_info.x20;
}

f32 get_cam_info_x24()
{
    return stage_info.cam_info.x24;
}

f32 get_cam_fixed_zoom()
{
    return stage_info.cam_info.cam_fixed_zoom;
}

f32 get_cam_track_ratio()
{
    return stage_info.cam_info.cam_track_ratio;
}

f32 get_cam_track_smooth()
{
    return stage_info.cam_info.cam_track_smooth;
}

f32 get_blast_zone_right_offset()
{
    return stage_info.blast_zone.right + stage_info.cam_info.cam_x_offset;
}

f32 get_blast_zone_left_offset()
{
    return stage_info.blast_zone.left + stage_info.cam_info.cam_x_offset;
}

f32 get_blast_zone_top_offset()
{
    return stage_info.blast_zone.top + stage_info.cam_info.cam_y_offset;
}

f32 get_blast_zone_bottom_offset()
{
    return stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset;
}

f32 calc_unk_cam_y_80224B98()
{
    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 y_pos = stage_info.cam_info.cam_bounds_bottom + cam_y_offset + (stage_info.blast_zone.bottom + cam_y_offset);
    return 0.5F * y_pos;
}

f32 calc_unk_cam_y_bounds_80224BC4()
{
    f32 cam_offset = (stage_info.cam_info.cam_bounds_bottom + stage_info.cam_info.cam_y_offset);
    f32 y_pos_product = 0.5F * ((stage_info.cam_info.cam_bounds_bottom + stage_info.cam_info.cam_y_offset) + (stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset));

    return 0.5F * (cam_offset + y_pos_product);
}

f32 unk_set_vec3_to_cam_offset_80224BF8(Vec* vec3, f32 arg8)
{
    vec3->x = stage_info.cam_info.cam_x_offset;
    vec3->y = stage_info.cam_info.cam_y_offset;
    vec3->z = 0.0F;
    return arg8;
}

f32 get_pausecam_zpos_min()
{
    return stage_info.cam_info.pausecam_zpos_min;
}

f32 get_pausecam_zpos_init()
{
    return stage_info.cam_info.pausecam_zpos_init;
}

f32 get_pausecam_zpos_max()
{
    return stage_info.cam_info.pausecam_zpos_max;
}

f32 get_cam_angle_radians_up()
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_up;
}

f32 get_cam_angle_radians_down()
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_down;
}

f32 get_cam_angle_radians_left()
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_left;
}

f32 get_cam_angle_radians_right()
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_right;
}

void func_80224CAC(Vec* arg0)
{
    Vec another_vec = { 0, 0, -100.0F };
    Vec rot_vec;

    *arg0 = stage_info.cam_info.fixed_cam_pos;

    rot_vec.x = 0.0174532923847F * stage_info.cam_info.fixed_cam_vert_angle;
    rot_vec.y = 0.0174532923847F * stage_info.cam_info.fixed_cam_horz_angle;
    rot_vec.z = 0.0F;

    lbvector_ApplyEulerRotation(&another_vec, &rot_vec);

    {
        Vec last_vec;
        f32 temp_f4 = (arg0->z / -another_vec.z);

        last_vec.x = (another_vec.x * temp_f4) + arg0->x;
        last_vec.y = (another_vec.y * temp_f4) + arg0->y;
        last_vec.z = 0.0F;
        *arg0 = last_vec;
    }
}

void set_vec_to_fixed_cam_pos(Vec* arg0)
{
    *arg0 = stage_info.cam_info.fixed_cam_pos;
}

f32 get_cam_fixed_fov()
{
    return stage_info.cam_info.fixed_cam_fov;
}

BOOL func_80224DC8(s32 arg)
{
    return (arg == 0x3b || arg == 0x3f || arg == 0x42 || arg == 0x49 || arg == 0x4c) != 0;
}

void func_80224E38(Vec* arg0, s32 arg1)
{
    func_801C2D24(arg1 + 4, arg0);
}

void func_80224E64(s32 arg0, Vec* arg_vec)
{
    BOOL bool1;

    f32 counter_f;
    Vec internal_vec;

    if (arg0 == -1) {
        __assert(__FILE__, 360, "no!=St_Player_InitPos_None\0");
    }

    if (arg0 == 4) {
        bool1 = 0;
        for (counter_f = -10.0F; counter_f < 100.0f; counter_f += 10.0f) {
            s32 temp_ret = func_80051EC8(&internal_vec, 0, 0, 0, 1, -1, -1, 0.0F, 10.0f + counter_f, 0.0F, counter_f);
            if (temp_ret != 0) {
                bool1 = 1;
                break;
            }
        }

        if (bool1 == 0) {
            for (counter_f = -10.0F; counter_f > -100.0f; counter_f -= 10.0f) {
                s32 temp_ret = func_80051EC8(&internal_vec, 0, 0, 0, 1, -1, -1, 0.0F, counter_f, 0.0F, counter_f - 10.0f);

                if (temp_ret != 0) {
                    bool1 = 1;
                    break;
                }
            }
        }

        if (bool1) {
            *arg_vec = internal_vec;
            return;
        }
        arg_vec->z = 0.0F;
        arg_vec->y = 0.0F;
        arg_vec->x = 0.0F;
        return;
    }
    func_801C2D24(arg0, arg_vec);
}

s32 func_80224FDC(Vec* arg0)
{
    s32 rand_output;
    s32 counter = 0x15;
    s32 counter2;

    while (counter != 0) {
        if (func_801C2D24(HSD_Randi(counter) + 0x7F, arg0)) {
            return 1;
        }
        counter += -1;
    }

    counter2 = 4;
    while (counter2 != 0) {
        rand_output = HSD_Randi(counter2);
        counter2 = func_801C2D24(rand_output, arg0);

        if (counter2 != 0) {
            return 1;
        }
        counter2 = rand_output;
    }

    return 0;
}

s32 func_80225074(s32 arg0)
{

    s32 r31;
    s32 spC;

    if (func_8016B238() != 0) {
        if (((stage_info.unk8C >> 7) & 0x1) || (arg0 == 2)) {
            r31 = 0x12;
        } else {
            r31 = 0x11;
        }
    } else if (func_8016B3A0() != 0) {
        if (arg0 == 2) {
            r31 = 0x22;
        } else if (arg0 == 1) {
            r31 = 0x64;
        } else {
            r31 = 0x24;
        }
    } else if (arg0 == 0) {
        r31 = 4;
    } else if (arg0 == 3) {
        r31 = 1;
    } else if (arg0 == 2) {
        r31 = 2;
    } else if (arg0 == 1) {
        r31 = 0x44;
    } else {
        __assert(__FILE__, 526, "0");
    }

    r31 = func_801C28AC(unk_struct_804D49E8.list_idx, r31, &spC);
    func_80023F28(spC);
    func_801C5A84(spC);
    func_801C5AA4(r31);
    return arg0;
}

s32 func_80225194()
{
    return unk_struct_804D49E8.list_idx;
}

s32 func_8022519C(s32 idx)
{
    return unk_arr_803E9960[idx].stage_id;
}

s32 func_802251B4(s32 idx, s32 arg1)
{
    return func_801C06B8(unk_arr_803E9960[idx].stage_id);
}

void func_802251E8(s32 idx, s32* unused)
{
    struct StructPairWithStageID local_data;

    unk_struct_804D49E8.list_idx = idx;
    unk_struct_804D49E8.unk_struct = &unk_arr_803E9960[idx];

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.unk_struct->stage_id;
    local_data.list_idx = unk_struct_804D49E8.list_idx;

    func_801C0754(&local_data);
}

void func_8022524C()
{
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.unk_struct->stage_id;
    local_data.list_idx = unk_struct_804D49E8.list_idx;

    func_801C0800(&local_data);
}

void func_80225298()
{
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.unk_struct->stage_id;
    local_data.list_idx = unk_struct_804D49E8.list_idx;

    func_801C0F78(&local_data);
}

void func_802252E4(s32 idx, s32 unused)
{
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.unk_struct->stage_id;
    local_data.list_idx = idx;

    func_801C0FB8(&local_data);
}

void func_8022532C(s32 idx, s32 arg1)
{
    struct StructPairWithStageID local_data;

    local_data = unk_struct_804D49F0;

    local_data.stage_id = unk_struct_804D49E8.unk_struct->stage_id;
    local_data.list_idx = idx;

    func_801C1074(&local_data, arg1);
}
