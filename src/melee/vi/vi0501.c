#include "vi0501.static.h"

#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "lb/lbaudio_ax.h"
#include "lb/lb_00F9.h"
#include "lb/lbshadow.h"
#include "vi/vi.h"

#include <dolphin/gx.h>
#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/wobj.h>

static GXColor erase_colors_vi0501;
extern un_804D7004_t un_804D6FA8;

/// #un_8031D9F8

void vi_8031DC80(HSD_GObj* gobj, int unused)
{
    PAD_STACK(8);
    lbShadow_8000F38C(0);
    vi_RunCamera(gobj, (u8*) &erase_colors_vi0501, 0x281);
}

void fn_8031DD14(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    f32 frame;

    HSD_CObjAnim(cobj);
    frame = cobj->aobj->curr_frame;

    if (un_804DE074 == frame || un_804DE078 == frame || un_804DE07C == frame) {
        vi_8031C9B4(0xC, 0);
        lbAudioAx_800237A8(0x222F9, 0x7F, 0x40);

        if (un_804DE074 == cobj->aobj->curr_frame) {
            lbAudioAx_800237A8(0x73, 0x7F, 0x40);
        }
        if (un_804DE078 == cobj->aobj->curr_frame) {
            lbAudioAx_800237A8(0x74, 0x7F, 0x40);
        }
        if (un_804DE07C == cobj->aobj->curr_frame) {
            lbAudioAx_800237A8(0x73, 0x7F, 0x40);
        }
    }

    frame = cobj->aobj->curr_frame;
    if (un_804DE080 == frame || un_804DE084 == frame || un_804DE088 == frame) {
        lbAudioAx_800237A8(0x22308, 0x7F, 0x40);
    }

    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}
/// #un_8031DE58_OnEnter

void vi_8031E0F0_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031E110(int arg0, int arg1, int arg2)
{
    M2C_FIELD(&un_804D6FA8, u8*, 0) = arg0;
    M2C_FIELD(&un_804D6FA8, u8*, 1) = arg1;
    M2C_FIELD(&un_804D6FA8, u8*, 3) = arg2;
}
