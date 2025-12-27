#include "lbmthp.static.h"

#include <melee/lb/lbanim.h>
#include <melee/lb/types.h>

/// #fn_8001E910

/// #fn_8001EB14

#define ALIGN_32(x) (((x) + 0x1F) & ~0x1F)

s32 fn_8001EBF0(THPDecComp* data)
{
    s32 size = 0;
    u32 width;
    u32 aligned_100;
    u32 height;
    u32 unk_104_val;
    u32 wh;
    u32 wh_div4;

    data->unk_104 = 0x20;

    /* Load width first */
    width = data->width;
    /* Load unk_100 */
    aligned_100 = data->unk_100;
    /* Load height */
    height = data->height;
    /* Load unk_104 */
    unk_104_val = data->unk_104;

    /* Align unk_100 */
    aligned_100 = ALIGN_32(aligned_100);

    /* Store width */
    data->unk_A0 = (u16)width;

    /* Multiply width * height */
    wh = width * height;

    /* Reload and store height */
    height = data->height;
    data->unk_A2 = (u16)height;

    /* size = aligned * unk_104 */
    size = aligned_100 * unk_104_val;

    /* Store 4 to unk_A4 */
    data->unk_A4 = 4;

    /* Zero unk_9C */
    data->unk_9C = 0;

    /* size += wh */
    size += wh;

    /* size += wh/4 twice */
    wh_div4 = wh >> 2;
    size += wh_div4;
    size += wh_div4;

    /* Call THPDec_8032FD40 with &unk_9C and height as u16 */
    size += THPDec_8032FD40(&data->unk_9C, (u16)data->height);

    /* Zero various fields */
    data->unk_7C = 0;
    data->unk_78 = 0;
    data->unk_84 = 0;
    data->unk_80 = 0;
    data->unk_90 = 0;
    data->unk_88 = 0;
    data->unk_94 = -1;
    data->unk_68 = 0;

    /* Copy width/height again */
    data->unk_A8 = (u16)data->width;
    data->unk_AA = (u16)data->height;
    data->unk_AC = 0;

    /* Add aligned sizes */
    size += ALIGN_32(data->unk_104 * 4);
    size += ALIGN_32(data->unk_40 * 4);

    return size;
}

/// #fn_8001ECF4

/// #fn_8001EF5C

/// #fn_8001F06C

/// #fn_8001F13C

s32 fn_8001F294(void)
{
    return lbl_804333E0.unk_110;
}

/// #fn_8001F2A4

/// #lbMthp_8001F410

/// #lbMthp_8001F578

s32 lbMthp_8001F5C4(void)
{
    return lbl_804333E0.unk_84;
}

s32 lbMthp_8001F5D4(void)
{
    return lbl_804333E0.unk_134;
}

s32 lbMthp_8001F5E4(void)
{
    return lbl_804333E0.unk_108;
}

s32 lbMthp_8001F5F4(void)
{
    return lbl_804333E0.unk_10C;
}

s32 lbMthp_8001F604(void)
{
    return lbl_804333E0.unk_144;
}

void lbMthp_8001F614(s32 arg0)
{
    lbl_804333E0.unk_148 = arg0;
}

/// #lbMthp_8001F624

/// #lbMthp_8001F67C

/// #lbMthp_8001F800

void lbMthp_8001F87C(void)
{
    lbl_804333E0.unk_14C = 0;
}

/// #lbMthp8001F890

/// #lbMthp8001F928

/// #lbMthp8001FAA0
