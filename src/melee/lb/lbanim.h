#ifndef GALE01_01E560
#define GALE01_01E560

#include <platform.h>
#include <placeholder.h>

#include <baselib/forward.h>

typedef struct FigaTrack {
    u16 length;
    u16 startframe;
    u8 obj_type;
    u8 frac_value;
    u8 frac_slope;
    u8* ad_head;
} FigaTrack;

typedef struct FigaTree {
    int type;
    u32 flags;
    f32 frames;
    void* nodes;
    FigaTrack** tracks;
} FigaTree;

/* 01E60C */ UNK_T lbAnim_8001E60C(UNK_T, s8);
void lbAnim_8001E6D8(HSD_JObj* jobj, FigaTree* tree, FigaTrack* track,
                     s8 frames);
/* 01E7E8 */ void lbAnim_8001E7E8(UNK_T, UNK_T, s32, s8);

#endif
