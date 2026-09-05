#ifndef MELEE_FT_CHARA_FTSAMUS_INLINES_H
#define MELEE_FT_CHARA_FTSAMUS_INLINES_H

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <stddef.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ef/eflib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftSamus/ftsamus.h>
#include <melee/ft/kinds/ftSamus/types.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itsamuschargeshot.h>

static inline void ftSamus_updateDamageDeathCBs(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftSs_Init_80128428;
    fp->death2_cb = ftSs_Init_80128428;
}

//// only used in ftsamus3 so far (maybe move to there)
static inline void ftSamus_SetAttrx2334(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->u.ss.x2234 = 0;
}

static inline void ftSamus_destroyAllEF(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->u.ss.x2234) {
            efLib_DestroyAll(gobj);
            fp->u.ss.x2234 = 0;
        }
    }
}

static inline void ftSamus_UnkAndDestroyAllEF(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = gobj->user_data;
        Item_GObj* x222C = fp->u.ss.x222C;
        if (x222C != NULL) {
            it_802B5974(x222C);
            fp->u.ss.x222C = NULL;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

#endif
