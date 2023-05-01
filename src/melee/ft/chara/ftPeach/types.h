#ifndef MELEE_FT_CHARA_FTPEACH_TYPES_H
#define MELEE_FT_CHARA_FTPEACH_TYPES_H

#include <platform.h>
#include "ft/forward.h"

struct ftPeach_FighterVars {
    /* fp+222C */ bool has_float;
    /* fp+2230 */ f32 x4;
    /* fp+2234 */ FtMotionId attacks4_motion_id;
    /* fp+2238 */ u32 xC;
    /* fp+223C */ u32 x10;
    /* fp+2240 */ u32 x14;
    /* fp+2244 */ u32 x18;
    /* fp+2248 */ u32 x20;
};

typedef struct ftPe_DatAttrs {
    f32 floatfallf_anim_start;
    f32 floatfallb_anim_start;
    f32 floatfall_anim_start_offset;
    f32 xC;
    u8 x10[0xB0];
} ftPe_DatAttrs;

union ftPe_MotionVars {
    struct ftPe_FloatAttackVars {
        /* fp+2340 */ bool x0;
    } floatattack;
};

#endif
