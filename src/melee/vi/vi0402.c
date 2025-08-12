#include "vi/vi0402.h"

#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"
#include "vi/vi.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

void un_8031D6E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

/// #un_8031D708

/// #vi_8031D80C
void vi_8031D80C(HSD_GObj* gobj)
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

/// #un_8031D858_OnEnter

void vi_8031D9C4_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031D9E4(int arg0, int arg1, int arg2)
{
    M2C_FIELD(&un_804D6F84, u8*, 0) = arg0;
    M2C_FIELD(&un_804D6F84, u8*, 1) = arg1;
    M2C_FIELD(&un_804D6F84, u8*, 3) = arg2;
}
