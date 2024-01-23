#ifndef MELEE_FT_CHARA_FTCLINK_INLINES_H
#include "it/items/it_27CF.h"
#define MELEE_FT_CHARA_FTCLINK_INLINES_H

#include "ft/types.h"
#include "it/items/it_27CF.h"

static inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = gobj->user_data;
    if (fp != NULL && fp->fv.lk.x18 != NULL) {
        it_802C8C34(fp->fv.lk.x18);
        fp->fv.lk.x18 = NULL;
    }

    if (gobj == NULL) {
        gobj == NULL;
    }
}

#endif
