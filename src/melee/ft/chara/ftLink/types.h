#ifndef MELEE_FT_CHARA_FTLINK_TYPES_H
#define MELEE_FT_CHARA_FTLINK_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "ft/forward.h"
#include "ftLink/forward.h" // IWYU pragma: export
#include "it/forward.h"

#include "lb/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

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
    /* +64 */ UNK_T x64;
    /* +68 */ UNK_T x68;
    /* +6C */ UNK_T x6C;
    /* +70 */ UNK_T x70;
    /* +74 */ UNK_T x74;
    /* +78 */ UNK_T x78;
    /* +7C */ UNK_T x7C;
    /* +80 */ UNK_T x80;
    /* +84 */ UNK_T x84;
    /* +88 */ s32 x88;
    /* +8C */ UNK_T x8C;
    /* +90 */ UNK_T x90;
    /* +94 */ UNK_T x94;
    /* +98 */ s32 x98;
    /* +9C */ UNK_T x9C;
    /* +A0 */ UNK_T xA0;
    /* +A4 */ int xA4;
    /* +A8 */ s32 xA8;
    /* +AC */ int xAC;
    /* +B0 */ int xB0;
    /* +B4 */ float xB4;
    /* +B8 */ int xB8;
    /* +BC */ int xBC;
    /* +C0 */ u8 xC0_filler[0xC4 - 0xC0];
    /* +C4 */ AbsorbDesc xC4;
    /* +D8 */ float xD8;
};

struct ftLk_FighterVars {
    /* fp+222C */ bool used_boomerang;
    /* fp+2230 */ bool x4;
    /* fp+2234 */ Item_GObj* boomerang_gobj;
    /* fp+2238 */ Item_GObj* xC;
    /* fp+223C */ Item_GObj* arrow_gobj;
    /* fp+2240 */ Item_GObj* x14;
    /* fp+2244 */ Item_GObj* x18;
    /* fp+2248 */ u32 x1C;
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
