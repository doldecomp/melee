#include "vi1101.static.h"

#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "vi.h"

extern GXColor un_804D5B08;

/// #un_8031F294

void fn_8031F548(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void fn_8031F56C(HSD_GObj* gobj)
{
    u8* colors;
    char pad[8];
    lbShadow_8000F38C(0);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = (u8*)&un_804D5B08;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        *(s32*)((char*)gobj + 0x20) = 0;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

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
