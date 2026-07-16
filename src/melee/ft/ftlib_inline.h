#ifndef MELEE_FT_FTLIB_INLINE_H
#define MELEE_FT_FTLIB_INLINE_H

#include "ft/ftlib.h"

#include <baselib/gobj.h>

extern inline HSD_GObj* ftLib_GetItem(HSD_GObj* gobj)
{
    Fighter* fp = HSD_GObjGetUserData(gobj);
    return fp->item_gobj;
}

#endif
