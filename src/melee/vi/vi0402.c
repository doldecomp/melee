#include "vi/vi0402.static.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 4D6F84 */ un_804D7004_t un_804D6F84;

void un_8031D6E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

/// #un_8031D708

/// #fn_8031D80C

/// #un_8031D858

/// #un_8031D9C4

void un_8031D9E4(s8 arg0, s8 arg1, s8 arg2)
{
    M2C_FIELD(&un_804D6F84, s8*, 0) = arg0;
    M2C_FIELD(&un_804D6F84, s8*, 1) = arg1;
    M2C_FIELD(&un_804D6F84, s8*, 3) = arg2;
}
