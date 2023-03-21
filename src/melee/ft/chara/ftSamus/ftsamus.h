#ifndef MELEE_FT_CHARA_FTSAMUS_FTSAMUS_H
#define MELEE_FT_CHARA_FTSAMUS_FTSAMUS_H

#include "ef/eflib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/code_8027CF30.h"
#include "it/item.h"
#include "lb/lbvector.h"

void ftSamus_80128428(HSD_GObj* gobj);
void ftSamus_80129048(HSD_GObj* gobj);
void ftSamus_801290A4(HSD_GObj* gobj);
void ftSamus_801291F0(HSD_GObj* gobj);
void ftSamus_8012A168(HSD_GObj* gobj, Vec3* spawnlocation);
void ftSamus_8012A074(HSD_GObj* gobj);
void ftSamus_8012B570(HSD_GObj* gobj);
void ftSamus_8012B5F0(HSD_GObj* gobj);
void ftSamus_8012B668(HSD_GObj* gobj);

void ftSamus_80128C04(HSD_GObj*);
void ftSamus_80128D3C(HSD_GObj*);
void ftSamus_80128E88(HSD_GObj*);
void ftSamus_80128F60(HSD_GObj*);
void ftSamus_80128CA0(HSD_GObj*);
void ftSamus_80128E68(HSD_GObj*);
void ftSamus_80128EF8(HSD_GObj*);
void ftSamus_80128FD4(HSD_GObj*);
void ftSamus_80129684(HSD_GObj*);
void ftSamus_80129B18(HSD_GObj*);
void ftSamus_80129C88(HSD_GObj*);
void ftSamus_80129D48(HSD_GObj*);
void ftSamus_80129774(HSD_GObj*);
void ftSamus_80129B1C(HSD_GObj*);
void ftSamus_80129CA8(HSD_GObj*);
void ftSamus_80129DC8(HSD_GObj*);
void ftSamus_80129940(HSD_GObj*);
void ftSamus_80129C78(HSD_GObj*);
void ftSamus_80129CC8(HSD_GObj*);
void ftSamus_80129E68(HSD_GObj*);
void ftSamus_801299D0(HSD_GObj*);
void ftSamus_80129C7C(HSD_GObj*);
void ftSamus_80129CE8(HSD_GObj*);
void ftSamus_80129EE8(HSD_GObj*);
void ftSamus_80129A14(HSD_GObj*);
void ftSamus_80129C80(HSD_GObj*);
void ftSamus_80129D08(HSD_GObj*);
void ftSamus_80129F68(HSD_GObj*);
void ftSamus_80129A98(HSD_GObj*);
void ftSamus_80129C84(HSD_GObj*);
void ftSamus_80129D28(HSD_GObj*);
void ftSamus_80129FE8(HSD_GObj*);
void ftSamus_8012A380(HSD_GObj*);
void ftSamus_8012A3F8(HSD_GObj*);
void ftSamus_8012A400(HSD_GObj*);
void ftSamus_8012A468(HSD_GObj*);
void ftSamus_8012A4E0(HSD_GObj*);
void ftSamus_8012A558(HSD_GObj*);
void ftSamus_8012A560(HSD_GObj*);
void ftSamus_8012A5C8(HSD_GObj*);
void ftSamus_8012A3BC(HSD_GObj*);
void ftSamus_8012A3FC(HSD_GObj*);
void ftSamus_8012A420(HSD_GObj*);
void ftSamus_8012A4A4(HSD_GObj*);
void ftSamus_8012A51C(HSD_GObj*);
void ftSamus_8012A55C(HSD_GObj*);
void ftSamus_8012A580(HSD_GObj*);
void ftSamus_8012A604(HSD_GObj*);
void ftSamus_8012A81C(HSD_GObj*);
void ftSamus_8012A96C(HSD_GObj*);
void ftSamus_8012AB0C(HSD_GObj*);
void ftSamus_8012AC00(HSD_GObj*);
void ftSamus_8012A8C4(HSD_GObj*);
void ftSamus_8012AA3C(HSD_GObj*);
void ftSamus_8012ABB4(HSD_GObj*);
void ftSamus_8012ACF8(HSD_GObj*);
void ftSamus_8012B150(HSD_GObj*);
void ftSamus_8012B358(HSD_GObj*);
void ftSamus_8012B3A8(HSD_GObj*);
void ftSamus_8012B488(HSD_GObj*);
void ftSamus_8012B264(HSD_GObj*);
void ftSamus_8012B3A4(HSD_GObj*);
void ftSamus_8012B41C(HSD_GObj*);
void ftSamus_8012B4FC(HSD_GObj*);
void func_800C3D6C(HSD_GObj*);
void func_800C4384(HSD_GObj*);
void func_800C438C(HSD_GObj*);
void func_800C447C(HSD_GObj*);
void func_800C4380(HSD_GObj*);
void func_800C4388(HSD_GObj*);
void func_800C4438(HSD_GObj*);
void func_80082B78(HSD_GObj*);

static inline void ftSamus_updateDamageDeathCBs(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftSamus_80128428;
    fp->cb.x21E4_callback_OnDeath2 = &ftSamus_80128428;
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
            func_802B5974(x222C);
            fp->fv.ss.x222C = NULL;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

#endif
