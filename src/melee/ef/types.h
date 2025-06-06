#ifndef MELEE_EF_TYPES_H
#define MELEE_EF_TYPES_H

#include <placeholder.h>

#include "ef/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include "sc/types.h"

struct ef_UnkStruct2 {
    /* +0 */ HSD_JObj* x0;
};

struct Effect {
    /*  +0 */ ef_UnkStruct2* x0;
    /*  +4 */ HSD_GObj* gobj;
    /*  +8 */ HSD_GObj* parent_gobj;
    /*  +C */ HSD_GObj* xC;
    /* +10 */ efLib_UnkCallback x10;
    /* +14 */ int x14;
    /* +18 */ int x18;
    /* +1C */ UNK_T x1C;
    /* +20 */ UNK_T x20;
    /* +24 */ u16 x24;
    /* +26 */ s8 x26;
    /* +27 */ s8 x27;
    /* +28 */ s8 x28;
    /* +29 */ u8 x29;
    /* +2A */ s8 x2A;
    /* +2B */ s8 x2B;
};

struct EffectDesc {
    /* +0 */ float x0;
    /* +4 */ StaticModelDesc model_desc;
};

struct ef_UnkStruct1 {
    /* +0 */ int x0;
    /* +4 */ int x4;
    /* +8 */ int x8;
    /* +C */ int xC;
};

#endif
