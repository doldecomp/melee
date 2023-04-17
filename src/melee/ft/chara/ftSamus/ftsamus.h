#ifndef MELEE_FT_CHARA_FTSAMUS_FTSAMUS_H
#define MELEE_FT_CHARA_FTSAMUS_FTSAMUS_H

#include "ef/eflib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "it/item.h"
#include "lb/lbvector.h"

void ftSs_Init_80128428(HSD_GObj* gobj);
void ftSs_SpecialLw_80129048(HSD_GObj* gobj);
void ftSs_SpecialLw_801290A4(HSD_GObj* gobj);
void ftSs_SpecialN_801291F0(HSD_GObj* gobj);
void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation);
void ftSs_SpecialS_8012A074(HSD_GObj* gobj);
void ftSs_SpecialLw_8012B570(HSD_GObj* gobj);
void ftSs_SpecialLw_8012B5F0(HSD_GObj* gobj);
void ftSs_SpecialLw_8012B668(HSD_GObj* gobj);

void ftSs_SpecialLw_Anim(HSD_GObj*);
void ftSs_SpecialLw_IASA(HSD_GObj*);
void ftSs_SpecialLw_Phys(HSD_GObj*);
void ftSs_SpecialLw_Coll(HSD_GObj*);
void ftSs_SpecialAirLw_Anim(HSD_GObj*);
void ftSs_SpecialAirLw_IASA(HSD_GObj*);
void ftSs_SpecialAirLw_Phys(HSD_GObj*);
void ftSs_SpecialAirLw_Coll(HSD_GObj*);
void ftSs_SpecialNStart_Anim(HSD_GObj*);
void ftSs_SpecialNStart_IASA(HSD_GObj*);
void ftSs_SpecialNStart_Phys(HSD_GObj*);
void ftSs_SpecialNStart_Coll(HSD_GObj*);
void ftSs_SpecialNLoop_Anim(HSD_GObj*);
void ftSs_SpecialNLoop_IASA(HSD_GObj*);
void ftSs_SpecialNLoop_Phys(HSD_GObj*);
void ftSs_SpecialNLoop_Coll(HSD_GObj*);
void ftSs_SpecialNEnd_Anim(HSD_GObj*);
void ftSs_SpecialNEnd_IASA(HSD_GObj*);
void ftSs_SpecialNEnd_Phys(HSD_GObj*);
void ftSs_SpecialNEnd_Coll(HSD_GObj*);
void ftSs_SpecialNShoot_Anim(HSD_GObj*);
void ftSs_SpecialNShoot_IASA(HSD_GObj*);
void ftSs_SpecialNShoot_Phys(HSD_GObj*);
void ftSs_SpecialNShoot_Coll(HSD_GObj*);
void ftSs_SpecialAirNStart_Anim(HSD_GObj*);
void ftSs_SpecialAirNStart_IASA(HSD_GObj*);
void ftSs_SpecialAirNStart_Phys(HSD_GObj*);
void ftSs_SpecialAirNStart_Coll(HSD_GObj*);
void ftSs_SpecialAirNShoot_Anim(HSD_GObj*);
void ftSs_SpecialAirNShoot_IASA(HSD_GObj*);
void ftSs_SpecialAirNShoot_Phys(HSD_GObj*);
void ftSs_SpecialAirNShoot_Coll(HSD_GObj*);
void ftSs_SpecialS_Anim(HSD_GObj*);
void ftSs_SpecialS_IASA(HSD_GObj*);
void ftSs_SpecialS_Phys(HSD_GObj*);
void ftSs_SpecialS_Coll(HSD_GObj*);
void ftSs_SpecialSSmash_Anim(HSD_GObj*);
void ftSs_SpecialSSmash_IASA(HSD_GObj*);
void ftSs_SpecialSSmash_Phys(HSD_GObj*);
void ftSs_SpecialSSmash_Coll(HSD_GObj*);
void ftSs_SpecialAirS_Anim(HSD_GObj*);
void ftSs_SpecialAirS_IASA(HSD_GObj*);
void ftSs_SpecialAirS_Phys(HSD_GObj*);
void ftSs_SpecialAirS_Coll(HSD_GObj*);
void ftSs_SpecialAirSmash_Anim(HSD_GObj*);
void ftSs_SpecialAirSmash_IASA(HSD_GObj*);
void ftSs_SpecialAirSmash_Phys(HSD_GObj*);
void ftSs_SpecialAirSmash_Coll(HSD_GObj*);
void ftSs_SpecialHi_Anim(HSD_GObj*);
void ftSs_SpecialHi_IASA(HSD_GObj*);
void ftSs_SpecialHi_Phys(HSD_GObj*);
void ftSs_SpecialHi_Coll(HSD_GObj*);
void ftSs_SpecialAirHi_Anim(HSD_GObj*);
void ftSs_SpecialAirHi_IASA(HSD_GObj*);
void ftSs_SpecialAirHi_Phys(HSD_GObj*);
void ftSs_SpecialAirHi_Coll(HSD_GObj*);
void ftSs_SpecialLwBombEnd_Anim(HSD_GObj*);
void ftSs_SpecialLwBombEnd_IASA(HSD_GObj*);
void ftSs_SpecialLwBombEnd_Phys(HSD_GObj*);
void ftSs_SpecialLwBombEnd_Coll(HSD_GObj*);
void ftSs_SpecialAirLwBomb_Anim(HSD_GObj*);
void ftSs_SpecialAirLwBomb_IASA(HSD_GObj*);
void ftSs_SpecialAirLwBomb_Phys(HSD_GObj*);
void ftSs_SpecialAirLwBomb_Coll(HSD_GObj*);
void ftCo_Zair_Anim(HSD_GObj*);
void ftCo_Zair_IASA(HSD_GObj*);
void ftCo_Zair_Phys(HSD_GObj*);
void ftCo_Zair_Coll(HSD_GObj*);
void ftCo_ZairCatch_Anim(HSD_GObj*);
void ftCo_ZairCatch_IASA(HSD_GObj*);
void ftCo_ZairCatch_Phys(HSD_GObj*);
void ftCo_ZairCatch_Coll(HSD_GObj*);

static inline void ftSamus_updateDamageDeathCBs(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftSs_Init_80128428;
    fp->cb.x21E4_callback_OnDeath2 = &ftSs_Init_80128428;
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
