#include "vi0801.h"

#include "vi.h"

#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>

void fn_8031EFE4(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 1.0F || cobj->aobj->curr_frame == 30.0F) {
        vi_8031C9B4(0xC, 0);
    }
    if (cobj->aobj->curr_frame == 60.0F) {
        vi_8031C9B4(0x10, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031F274_OnFrame(void)
{
    vi_8031CAAC();
}
