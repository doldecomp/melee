#ifndef GALE01_20F468
#define GALE01_20F468
#include <melee/gr/forward.h>

/* 2105AC */ void grOldKongo_802105AC(Ground_GObj*);
/* 2105C8 */ void grOldKongo_802105C8(HSD_GObj*);
/* 3E65E8 */ extern StageData grOk_StageData;

/// @note Field names originate from SSBU param files.
struct grOldKongo_YakumonoParam {
    s16 rframe_bird_wait_a;
    s16 rframe_bird_wait_b;
    f32 rrange_bird_random_offset_y;
    f32 rframe_barrel_shoot_a;
    f32 rframe_barrel_shoot_b;
    f32 rframe_barrel_in;
    f32 rframe_barrel_wait_a;
    f32 rframe_barrel_wait_b;
    f32 rspeed_barrel_rot_accel;
    f32 rspeed_barrel_rot_max;
    f32 rframe_barrel_roll_a;
    f32 rframe_barrel_roll_b;
    s16 rrate_barrel_ld;
    s16 rrate_barrel_l;
    s16 rrate_barrel_lu;
    s16 rrate_barrel_u;
    s16 rrate_barrel_ru;
    s16 rrate_barrel_r;
    s16 rrate_barrel_rd;
    s16 rrate_barrel_d;
    s32 rframe_barrel_interval_a;
    s32 rframe_barrel_interval_b;
    f32 rspeed_barrel_move_accel;
    f32 rspeed_barrel_move_max;
    s32 rframe_barrel_stop_a;
    s32 rframe_barrel_stop_b;
    s32 rpower_barrel_attack;
    s32 rvector_barrel_attack;
    s32 rreff_barrel_attack;
    s32 rrfix_barrel_attack;
    s32 rradd_barrel_attack;
    s32 x68;
    void* x6C;
};

#endif
