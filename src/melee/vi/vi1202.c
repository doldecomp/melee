#include "vi/vi1202.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"
#include "vi.h"

void un_8032110C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321130(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321154(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321294(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 1.0F) {
        vi_8031C9B4(0xe, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_803218E0_OnFrame(void)
{
    vi_8031CAAC();
}

extern char un_804A2F08[];
extern void* un_804D7050;

void un_80321900(void)
{
    HSD_GObj* gobj = GObj_Create(0x16, 0x17, 0);
    HSD_GObjProc_8038FD54(gobj, fn_803219AC, 0x13);
    un_804D7050 = un_804A2F08;
    un_80321950(un_804D7050);
}
