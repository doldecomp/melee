#include "vi/vi1201v2.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

void un_803204C0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_803204E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_803210EC_OnFrame(void)
{
    vi_8031CAAC();
}
