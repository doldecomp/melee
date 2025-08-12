#include "vi0401.h"

#include "vi.h"

#include "baselib/forward.h"

#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

static GXColor erase_colors_vi0401;

static void vi0401_8031D18C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void vi0401_8031D1B0(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0401.r, erase_colors_vi0401.g,
                          erase_colors_vi0401.b, erase_colors_vi0401.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static void vi0401_8031D23C(HSD_GObj* gobj)
{
    HSD_AObj* aobj;
    HSD_CObj* cobj = GET_COBJ(gobj);

    HSD_CObjAnim(cobj);
    aobj = cobj->aobj;
    if (aobj->curr_frame == aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}
