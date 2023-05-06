#ifndef MELEE_FT_CHARA_FTPEACH_TYPES_H
#define MELEE_FT_CHARA_FTPEACH_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"

#include <placeholder.h>

struct ftPeach_FighterVars {
    /* fp+222C */ bool has_float;
    /* fp+2230 */ f32 x4;
    /* fp+2234 */ FtMotionId attacks4_motion_id;
    /* fp+2238 */ u32 xC;
    /* fp+223C */ u32 x10;
    /* fp+2240 */ u32 x14;
    /* fp+2244 */ u32 x18;
    /* fp+2248 */ HSD_GObj* veg_gobj;
};

typedef struct ftPe_DatAttrs {
    /* +0 */ float floatfallf_anim_start;
    /* +4 */ float floatfallb_anim_start;
    /* +8 */ float floatfall_anim_start_offset;
    /* +C */ float xC;
    /* +10 */ int speciallw_item_table_count;
    /* +14 */ int x14;
    /* +1C */ struct ftPe_ItemChance {
        /* +0 */ int randi_max;
        /* +4 */ ItemKind kind;
    } speciallw_item_table[3];
    /* +30 */ int x30;
    /* +34 */ float x34;
    /* +38 */ f32 x38;
    /* +3C */ f32 x3C;
    /* +40 */ f32 x40;
    /* +44 */ f32 specials_vel_x;
    /* +48 */ f32 specials_smash_vel_x;
    /* +4C */ f32 specials_vel_y;
    /* +50 */ f32 x50;
    /* +54 */ f32 x54;
    /* +58 */ f32 x58;
    /* +5C */ f32 x5C;
    /* +60 */ f32 specials_end_vel_x;
    /* +64 */ f32 specials_end_vel_y;
    /* +68 */ f32 x68;
    /* +6C */ f32 x6C;
    /* +70 */ u8 x70[0xC0 - 0x70];
} ftPe_DatAttrs;

union ftPe_MotionVars {
    struct ftPe_FloatAttackVars {
        /* fp+2340 */ bool x0;
    } floatattack;
    struct ftPe_SpecialSVars {
        /* fp+2340 */ bool x0;
    } specials;
};

#endif
