#include "vi/vi0601.h"

#include "cm/camera.h"
#include "gm/gm_1A36.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "vi/vi.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/wobj.h>

GXColor erase_colors_vi0601 = { 0, 0, 0, 0 };

void vi_8031E6CC(void)
{
    vi_8031CAAC();
}

void vi_8031E6EC(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void vi0601_CameraCallback(HSD_GObj* gobj)
{
    HSD_CObj* cobj;
    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0601.r, erase_colors_vi0601.g,
                          erase_colors_vi0601.b, erase_colors_vi0601.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        Camera_800310A0(2);
        gobj->gxlink_prios = 0x9;
        HSD_GObj_80390ED0(gobj, 7);
        Camera_800310A0(1);
        gobj->gxlink_prios = 0x8;
        HSD_GObj_80390ED0(gobj, 7);
        Camera_800310A0(0);
        gobj->gxlink_prios = 0x8;
        HSD_GObj_80390ED0(gobj, 7);
        gobj->gxlink_prios = 0x8A1;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void vi0601_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (537.0f == cobj->aobj->curr_frame || 559.0f == cobj->aobj->curr_frame ||
        580.0f == cobj->aobj->curr_frame)
    {
        vi_8031C9B4(0x23, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void vi_8031ED50(void)
{
    vi_8031CAAC();
}
