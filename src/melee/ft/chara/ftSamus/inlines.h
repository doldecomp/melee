#ifndef MELEE_FT_CHARA_FTSAMUS_INLINES_H
#define MELEE_FT_CHARA_FTSAMUS_INLINES_H

#include "ef/eflib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftSamus/ftSs_Init.h"
#include "it/it_27CF.h"

static inline void ftSamus_updateDamageDeathCBs(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = ftSs_Init_80128428;
    fp->cb.x21E4_callback_OnDeath2 = ftSs_Init_80128428;
}

//// only used in ftsamus3 so far (maybe move to there)
static inline void ftSamus_SetAttrx2334(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->fv.ss.x2234 = 0;
}

static inline void ftSamus_destroyAllEF(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.ss.x2234) {
            efLib_DestroyAll(gobj);
            fp->fv.ss.x2234 = 0;
        }
    }
}

static inline void ftSamus_UnkAndDestroyAllEF(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = gobj->user_data;
        HSD_GObj* x222C = fp->fv.ss.x222C;
        if (x222C != NULL) {
            it_802B5974(x222C);
            fp->fv.ss.x222C = NULL;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

#endif
