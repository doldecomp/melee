#include "lbbgflash.h"

#include <placeholder.h>

#include <baselib/gobj.h>
#include <melee/lb/lb_00F9.h>

/* 021A10 */ static void lbBgFlash_80021A10(f32 arg8);
/* 021C18 */ static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2);

/// #fn_8001FC08

/// #fn_8001FEC4

/// #fn_800204C8

/// #lbBgFlash_800205F0

/// #lbBgFlash_8002063C

/// #lbBgFlash_80020688

/// #lbBgFlash_800206D4

/// #fn_8002087C

/// #fn_800208B0

/// #lbBgFlash_800208EC

/// #lbBgFlash_800209F4

/// #fn_80020AEC

/// #lbBgFlash_80020E38

/// #fn_8002113C

/// #lbBgFlash_80021410

/// #fn_800219E4

f32 lbl_804D63D8;

static void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

/// #lbBgFlash_80021A18

/// #fn_80021B04

static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2) {}

/// #fn_80021C1C

/// #lbBgFlash_80021C48

void fn_80021C80(HSD_GObj* gobj)
{
    u8* user_data = gobj->user_data;

    while (lb_80014258(gobj, (ColorOverlay*)(user_data + 4), fn_80021C18)) {
        lb_80014498((ColorOverlay*)(user_data + 4));
    }
}
