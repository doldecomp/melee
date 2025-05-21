#include <placeholder.h>

#include <baselib/forward.h>

#include "vi/vi0102.h"

#include "gm/gm_1A36.h"
#include "lb/lb_00F9.h"
#include "lb/lbshadow.h"
#include "vi/vi.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/wobj.h>

static u8 erase_colors[4];
static struct un_804D6F60_t un_804D6F60;

/// #vi_8031CB00

void vi_8031CC68(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void vi_8031CC8C(HSD_GObj* gobj)
{
    PAD_STACK(8);
    lbShadow_8000F38C(0);
    vi_EraseScreen(gobj, erase_colors);
}

void vi_8031CD20(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (190.0f == cobj->eyepos->aobj->curr_frame) {
        vi_8031C9B4(33, 0);
    }
    if (cobj->eyepos->aobj->curr_frame == cobj->eyepos->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

/// #vi_8031CD94

void vi_8031D000(void)
{
    vi_8031CAAC();
}

void vi_8031D020(s8 arg0, s8 arg1)
{
    un_804D6F60.unk_0 = arg0;
    un_804D6F60.unk_1 = arg1;
}
