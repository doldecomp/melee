#include "vi/vi1202.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

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

void un_803218E0_OnFrame(void)
{
    vi_8031CAAC();
}
