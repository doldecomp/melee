#include "lbmthp.h"

struct lbl_804333E0_t {
    /* +0 */ u8 _0[0x1D8];
};

/* 4333E0 */ static struct lbl_804333E0_t lbl_804333E0;

/// #lbMthp_8001E8F8

/// #fn_8001E910

/// #fn_8001EB14

/// #fn_8001EBF0

/// #fn_8001ECF4

/// #fn_8001EF5C

/// #fn_8001F06C

/// #fn_8001F13C

s32 fn_8001F294(void)
{
    return M2C_FIELD(&lbl_804333E0, s32*, 0x110);
}

/// #fn_8001F2A4

/// #lbMthp_8001F410

/// #lbMthp_8001F578

s32 lbMthp_8001F5C4(void)
{
    return M2C_FIELD(&lbl_804333E0, s32*, 0x84);
}

s32 lbMthp_8001F5D4(void)
{
    return M2C_FIELD(&lbl_804333E0, s32*, 0x134);
}

s32 lbMthp_8001F5E4(void)
{
    return M2C_FIELD(&lbl_804333E0, s32*, 0x108);
}

s32 lbMthp_8001F5F4(void)
{
    return M2C_FIELD(&lbl_804333E0, s32*, 0x10C);
}

s32 lbMthp_8001F604(void)
{
    return M2C_FIELD(&lbl_804333E0, s32*, 0x144);
}

void lbMthp_8001F614(s32 arg0)
{
    M2C_FIELD(&lbl_804333E0, s32*, 0x148) = arg0;
}

/// #lbMthp_8001F624

/// #lbMthp_8001F67C

/// #lbMthp_8001F800

/// #lbMthp_8001F87C

/// #lbMthp8001F890

/// #lbMthp8001F928

/// #lbMthp8001FAA0
