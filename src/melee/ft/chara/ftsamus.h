#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"

typedef struct _ftSamusAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;

    f32 x10;
    f32 x14;
    f32 x18;
    s32 x1C;

    s32 x20;

    u8 data_filler_10[0xD1 - 0x24];
} ftSamusAttributes;

