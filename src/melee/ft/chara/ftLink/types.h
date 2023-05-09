#ifndef MELEE_FT_CHARA_FTLINK_TYPES_H
#define MELEE_FT_CHARA_FTLINK_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftLink/forward.h"

#include <placeholder.h>

struct ftLk_DatAttrs {
    /* +0 */ s32 x0;
    /* +4 */ s32 x4;
    /* +8 */ s32 x8;
    /* +C */ s32 xC;
    /* +10 */ s32 x10;
    /* +14 */ u8 x14_filler[0x2C - 0x18];
    /* +28 */ f32 specialhi_pos_y_offset;
    /* +2C */ s32 x2C;
    /* +30 */ float x30;
    /* +34 */ float x34;
    /* +38 */ float specialairhi_drift_stick_mul;
    /* +3C */ float specialairhi_drift_max_mul;
    /* +40 */ float x40;
    /* +44 */ float specialhi_grav_mul;
    /* +48 */ s32 x48;
    /* +4C */ float attackairlw_hit_vel_y;
    /* +50 */ float attackairlw_hit_anim_frame_start;
    /* +54 */ float attackairlw_hit_anim_frame_end;
    /* +58 */ u32 attackairlw_anim_flags[3];
    /* +64 */ u8 x64[0xBC - 0x64];
    /* +BC */ s32 xBC;
    /* +C0 */ u8 xC0_filler[0xC4 - 0xC0];
    /* +C4 */ float xC4;
    /* +C8 */ u8 xC8_filler[0xD8 - 0xC8];
    /* +D8 */ f32 xD8;
};

struct ftLink_FighterVars {
    /* fp+222C */ u32 x0;
    /* fp+2230 */ int x4;
    /* fp+2234 */ u32 x8;
    /* fp+2238 */ u32 xC;
    /* fp+223C */ u32 x10;
    /* fp+2240 */ u32 x14;
    /* fp+2244 */ HSD_GObj* x18;
    /* fp+2248 */ u32 x1C;
    u8 _[FIGHTERVARS_SIZE - 0x20];
};

union ftLk_MotionVars {
    struct ftLk_AttackAirVars {
        /* fp+2340 */ float lw_frame_start;
    } attackair;
};

#endif
