#ifndef MELEE_FT_CHARA_FTCLINK_INLINES_H
#define MELEE_FT_CHARA_FTCLINK_INLINES_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <melee/ft/kinds/ftLink/types.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itclinkmilk.h>
#include <sysdolphin/baselib/gobj.h>

static inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = gobj->user_data;
    if (fp != NULL && fp->u.lk.milk_gobj != NULL) {
        it_802C8C34(fp->u.lk.milk_gobj);
        fp->u.lk.milk_gobj = NULL;
    }

#ifdef MUST_MATCH
    if (gobj == NULL) {
        gobj == NULL;
    }
#endif
}

#endif
