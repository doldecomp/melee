#ifndef MELEE_FT_CHARA_FTCLINK_INLINES_H
#define MELEE_FT_CHARA_FTCLINK_INLINES_H

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/kinds/ftLink/types.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itclinkmilk.h>
#include <Runtime/platform.h>

static inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = gobj->user_data;
    if (fp != NULL && fp->u.lk.x18 != NULL) {
        it_802C8C34(fp->u.lk.x18);
        fp->u.lk.x18 = NULL;
    }

    if (gobj == NULL) {
        gobj == NULL;
    }
}

#endif
