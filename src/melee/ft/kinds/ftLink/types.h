#ifndef MELEE_FT_CHARA_FTLINK_TYPES_H
#define MELEE_FT_CHARA_FTLINK_TYPES_H

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftLink/forward.h> // IWYU pragma: export
#include <melee/it/forward.h>

#include <placeholder.h>

#include <dolphin/mtx.h>
#include <melee/ft/kinds/ftMars/types.h>
#include <melee/lb/types.h>

struct ftLk_DatAttrs {
    /* +0 */ float x0;
    /* +4 */ float specialn_anim_rate;
    /* +8 */ float x8;
    /* +C */ ItemKind arrow_kind; // It_Kind_Link_Arrow or It_Kind_CLink_Arrow
    /* +10 */ ItemKind bow_kind;  // It_Kind_Link_Bow or It_Kind_CLink_Bow
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ float x1C;
    /* +20 */ float x20;
    /* +24 */ float x24;
    /* +28 */ float specialhi_pos_y_offset;
    /* +2C */ ItemKind
        boomerang_kind; // It_Kind_Link_Boomerang or It_Kind_CLink_Boomerang
    /* +30 */ float x30;
    /* +34 */ float x34;
    /* +38 */ float specialairhi_drift_stick_mul;
    /* +3C */ float specialairhi_drift_max_mul;
    /* +40 */ float x40;
    /* +44 */ float specialhi_grav_mul;
    /* +48 */ ItemKind bomb_kind; // It_Kind_Link_Bomb or It_Kind_CLink_Bomb
    /* +4C */ float attackairlw_hit_vel_y;
    /* +50 */ float attackairlw_hit_anim_frame_start;
    /* +54 */ float attackairlw_hit_anim_frame_end;
    /* +58 */ u32 attackairlw_anim_flags[3];
    /* +64 */ struct SwordAttrs x64;
    /* +84 */ s32 x84;
    /* +88 */ s32 x88;
    /* +8C */ s32 x8C;
    /* +90 */ s32 x90;
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
    /* +BC */ ItemKind
        hookshot_kind; // It_Kind_Link_Hookshot or It_Kind_CLink_Hookshot
    /* +C0 */ u8 xC0_filler[0xC4 - 0xC0];
    /* +C4 */ AbsorbDesc xC4;
    /* +D8 */ float xD8;
};

struct ftLk_FighterVars {
    /* fp+222C */ bool used_boomerang;
    /* fp+2230 */ bool x4;
    /* fp+2234 */ Item_GObj* boomerang_gobj;
    /* fp+2238 */ Item_GObj* hookshot_gobj;
    /* fp+223C */ Item_GObj* arrow_gobj;
    /* fp+2240 */ Item_GObj* bow_gobj;
    /* fp+2244 */ Item_GObj* milk_gobj; // Only used by Young Link
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
