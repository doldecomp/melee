#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"


typedef struct _ftPikachuAttributes {
    u32 x0;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    u32 x14;
    u32 x18;
    u32 x1C_padding[48];
    u32 xDC;
    u32 final_padding[6];
} ftPikachuAttributes;