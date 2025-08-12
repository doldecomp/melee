#ifndef MELEE_FT_CHARA_FTPEACH_TYPES_H
#define MELEE_FT_CHARA_FTPEACH_TYPES_H

#include <platform.h>

#include "ft/forward.h"
#include "ftPeach/forward.h" // IWYU pragma: export
#include "it/forward.h"

#include "lb/types.h"

#include <baselib/forward.h>

#include <common_structs.h>

struct ftPeach_FighterVars {
    /* fp+222C */ bool has_float;
    /* fp+2230 */ float x4;
    /* fp+2234 */ FtMotionId attacks4_motion_id;
    /* fp+2238 */ HSD_GObj* unk_item_gobj;
    /* fp+223C */ HSD_GObj* parasol_gobj;
    /* fp+2240 */ bool specialairn_used;
    /* fp+2244 */ HSD_GObj* toad_gobj;
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
    /* +38 */ float x38;
    /* +3C */ float x3C;
    /* +40 */ float x40;
    /* +44 */ float specials_vel_x;
    /* +48 */ float specials_smash_vel_x;
    /* +4C */ float specials_vel_y;
    /* +50 */ float x50;
    /* +54 */ float x54;
    /* +58 */ float x58;
    /* +5C */ float x5C;
    /* +60 */ float specials_end_vel_x;
    /* +64 */ float specials_end_vel_y;
    /* +68 */ float x68;
    /* +6C */ float x6C;
    /* +70 */ float x70;
    /* +74 */ float x74;
    /* +78 */ float x78;
    /* +7C */ float x7C;
    /* +80 */ float x80;
    /* +84 */ float x84;
    /* +88 */ float x88;
    /* +8C */ float x8C;
    /* +90 */ int x90;
    /* +94 */ float specialairn_vel_x_div;
    /* +98 */ float x98;
    /* +9C */ float specialairn_vel_y;
    /* +A0 */ float xA0;
    /* +A4 */ float xA4;
    /* +A8 */ float xA8;
    /* +AC */ AbsorbDesc xAC;
} ftPe_DatAttrs;

union ftPe_MotionVars {
    struct ftPe_FloatAttackVars {
        /* fp+2340 */ bool x0;
    } floatattack;
    struct ftPe_SpecialSVars {
        /* fp+2340 */ bool x0;
    } specials;
    struct ftPe_SpecialHiVars {
        /* fp+2340 */ ItemKind kind;
    } specialhi;
    struct ftPe_SpecialNVars {
        /* fp+2340 */ int facing_dir;
    } specialn;
};

#endif
