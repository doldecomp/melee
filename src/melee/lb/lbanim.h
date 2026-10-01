#ifndef GALE01_01E560
#define GALE01_01E560

#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dat_macros.h>
#include <sysdolphin/baselib/fobj.h>

struct FigaTrack {
    u16 length;
    u16 startframe;
    u8 obj_type;
    u8 frac_value;
    u8 frac_slope;
    u8 dummy0; ///< Set in the data, unused
    HSD_FObjData* ad_head DAT_COUNT(length);
};

struct FigaTree {
    int type;
    u32 flags;
    f32 frames;
    /// Tracks per joint, up to -1
    s8* nodes DAT_TERMINATED(-1);
    /// @todo As many as the sum of #nodes.
    FigaTrack* tracks DAT_EXTENT;
};

/* 01E60C */ HSD_FObj* fn_8001E60C(FigaTrack*, s8 frames);
void lbAnim_8001E6D8(HSD_JObj*, FigaTree*, FigaTrack*, s8 frames);
void lbAnim_8001E7E8(HSD_JObj*, FigaTree*, FigaTrack*, s8 frames);
float lbAnim_8001E8F8(FigaTree*);

#endif
