#include "vi/vi1201v1.static.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

#include "vi.h"

void un_8031F990(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031F9B4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

/// #un_8031F9D8

/// #fn_8031FAA8

/// #fn_8031FB90

/// #fn_8031FC30

/// #fn_8031FCBC

/// #un_8031FD18_OnEnter

void un_80320490_OnFrame(void)
{
    vi_8031CAAC();
}

void un_803204B0(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7038, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7038, u8*, 1) = arg1;
}
