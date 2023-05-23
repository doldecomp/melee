#ifndef MELEE_FT_CHARA_FTLINK_TYPES_H
#define MELEE_FT_CHARA_FTLINK_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftLink/forward.h"
#include "it/forward.h"

#include <common_structs.h>
#include <placeholder.h>

struct ftLk_DatAttrs {
    /* +0 */ float x0;
    /* +4 */ float specialn_anim_rate;
    /* +8 */ float x8;
    /* +C */ int xC;
    /* +10 */ int x10;
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ float x1C;
    /* +20 */ float x20;
    /* +24 */ float x24;
    /* +28 */ float specialhi_pos_y_offset;
    /* +2C */ int x2C;
    /* +30 */ float x30;
    /* +34 */ float x34;
    /* +38 */ float specialairhi_drift_stick_mul;
    /* +3C */ float specialairhi_drift_max_mul;
    /* +40 */ float x40;
    /* +44 */ float specialhi_grav_mul;
    /* +48 */ int x48;
    /* +4C */ float attackairlw_hit_vel_y;
    /* +50 */ float attackairlw_hit_anim_frame_start;
    /* +54 */ float attackairlw_hit_anim_frame_end;
    /* +58 */ u32 attackairlw_anim_flags[3];
    /* +64 */ u8 x64[0xBC - 0x64];
    /* +BC */ int xBC;
    /* +C0 */ u8 xC0_filler[0xC4 - 0xC0];
    /* +C4 */ AbsorbDesc xC4;
    /* +D8 */ float xD8;
};

struct ftLk_FighterVars {
    /* fp+222C */ bool used_boomerang;
    /* fp+2230 */ bool x4;
    /* fp+2234 */ Item_GObj* boomerang_gobj;
    /* fp+2238 */ u32 xC;
    /* fp+223C */ Item_GObj* arrow_gobj;
    /* fp+2240 */ Item_GObj* x14;
    /* fp+2244 */ Item_GObj* x18;
    /* fp+2248 */ u32 x1C;
    u8 _[FIGHTERVARS_SIZE - 0x20];
};

union ftLk_MotionVars {
    struct ftLk_AttackAirVars {
        /* fp+2340 */ float lw_frame_start;
    } attackair;
    struct ftLk_SpecialNVars {
        /* fp+2340 */ Vec2 x0;
        /* fp+2348 */ Vec3 x8;
        /* fp+2354 */ float x14;
        /* fp+2358 */ int unk_timer;
    } specialn;
};

struct ftLk_SpecialN_Vec3Group {
    /*  +0 */ Vec3 a;
    /*  +C */ Vec3 b;
    /* +18 */ Vec3 c;
};

#endif
