#include "vi1101.static.h"

#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "vi.h"

/// #un_8031F294

/// #fn_8031F548

/// #fn_8031F56C

void fn_8031F600(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);

    HSD_CObjAnim(cobj);

    if (un_804DE0E4 == cobj->aobj->curr_frame) {
        if (gm_80164840(7) != 0) {
            vi_8031C9B4(0xD, 0);
            lbAudioAx_800237A8(0x209, 0x7F, 0x40);
        }
    }

    if (un_804DE0E8 == cobj->aobj->curr_frame) {
        vi_8031C9B4(0xD, 0);
        lbAudioAx_800237A8(0x209, 0x7F, 0x40);
    }

    if (un_804DE0EC == cobj->aobj->curr_frame) {
        if (gm_80164840(7) != 0) {
            lbAudioAx_800237A8(0x20A, 0x7F, 0x40);
        }
    }

    if (un_804DE0F0 == cobj->aobj->curr_frame) {
        lbAudioAx_800237A8(0x20A, 0x7F, 0x40);
    }

    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

/// #un_8031F714_OnEnter

void un_8031F960_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031F980(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7004, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7004, u8*, 1) = arg1;
}
