#ifndef MELEE_FT_CHARA_FTLINK_TYPES_H
#define MELEE_FT_CHARA_FTLINK_TYPES_H

#include <platform.h>
#include "ft/forward.h"

typedef struct ftLk_DatAttrs {
    /* +0 */ s32 x0;
    /* +4 */ s32 x4;
    /* +8 */ s32 x8;
    /* +C */ s32 xC;
    /* +10 */ s32 x10;
    /* +14 */ u8 x14_filler[0x2C - 0x18];
    /* +28 */ f32 x28;
    /* +2C */ s32 x2C;
    /* +30 */ u8 x30_filler[0x48 - 0x30];
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
} ftLk_DatAttrs;

struct ftLink_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ HSD_GObj* x2244;
    /* 0x2248 */ u32 x2248;
    u8 _[FIGHTERVARS_SIZE - 0x20];
};

union ftLk_MotionVars {
    struct ftLk_AttackAirVars {
        /* fp+2340 */ float lw_frame_start;
    } attackair;
};
#endif
