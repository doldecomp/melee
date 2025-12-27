#include <placeholder.h>

typedef struct BgFlashState {
    u8 active : 1;
    u8 mode : 7;
} BgFlashState;

typedef struct BgFlashData {
    BgFlashState state;
    u8 pad[3];
    int x4;
    int x8;
    int xC;
} BgFlashData;

extern BgFlashData lbl_80433658;

/* 021A10 */ static void lbBgFlash_80021A10(f32 arg8);
/* 021C18 */ static UNK_RET fn_80021C18(UNK_PARAMS);

/// #fn_8001FC08

/// #fn_8001FEC4

/// #fn_800204C8

/// #lbBgFlash_800205F0

/// #lbBgFlash_8002063C

/// #lbBgFlash_80020688

/// #lbBgFlash_800206D4

void fn_8002087C(int* arg0)
{
    lbl_80433658.state.active = 0;
    lbl_80433658.state.mode = 5;
    lbl_80433658.xC = *arg0;
}
/// #fn_800208B0

/// #lbBgFlash_800208EC

/// #lbBgFlash_800209F4

/// #fn_80020AEC

/// #lbBgFlash_80020E38

/// #fn_8002113C

/// #lbBgFlash_80021410

/// #fn_800219E4

f32 lbl_804D63D8;

void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

/// #lbBgFlash_80021A18

/// #fn_80021B04

void fn_80021C18(void) {}

/// #fn_80021C1C

/// #lbBgFlash_80021C48

/// #fn_80021C80
