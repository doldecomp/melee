#include <placeholder.h>
#include "lb/forward.h"
#include "lb/lb_00F9.h"

/* 021A10 */ static void lbBgFlash_80021A10(f32 arg8);
/* 021C18 */ static UNK_RET fn_80021C18(UNK_PARAMS);
/* 021C48 */ void lbBgFlash_80021C48(u32, u32);

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

typedef struct {
    char pad[0x2C];
    void* x2C;
} BgFlashGlobal;

extern BgFlashGlobal* lbl_804D63E0;
extern struct Fighter_804D653C_t* lbl_804D63DC;

void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

/// #lbBgFlash_80021A18

/// #fn_80021B04

void fn_80021C18(void) {}

/// #fn_80021C1C

void lbBgFlash_80021C48(u32 arg0, u32 arg1)
{
    ColorOverlay* overlay = (ColorOverlay*)((u8*)lbl_804D63E0->x2C + 4);
    lb_800144C8(overlay, lbl_804D63DC, arg0, arg1);
}

/// #fn_80021C80
