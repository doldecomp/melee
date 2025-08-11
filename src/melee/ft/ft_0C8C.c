#include <placeholder.h>

#include "ft/forward.h"

#include "ft/ft_0C8C.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_DownSpot.h"
#include "ftCommon/ftCo_Lift.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/ftMh_Damage_0.h"
#include "gm/gm_unsplit.h"
#include "lb/lbbgflash.h"
#include "pl/player.h"

bool ftCo_800C8C84(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2224_b2 && fp->x2225_b7 && fp->dmg.x18F0 == 0 &&
        Player_GetRemainingHPByIndex(fp->player_id, fp->x221F_b4) == 0)
    {
        fn_800C8E74(gobj);
        return true;
    }

    return false;
}

static inline void fn_800C8_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtSFX* ft_sfx = fp->ft_data->x4C_sfx;
    fp->x2224_b2 = true;
    Fighter_ResetInputData_80068854(gobj);
    ftCo_800BFFD0(fp, 0x7A, 0);
    fn_800C8E40(fp, ft_sfx);
    fp->x2225_b6 = true;
    lbBgFlash_80021C48(0xEU, 0U);
    gm_80167470(fp->player_id, fp->x221F_b4);
}

void ftCo_800C8D00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(!fp->x2224_b3);

    if (!fp->x2224_b2) {
        fn_800C8_inline(gobj);
    }

    {
        // inline? same as fn_800D290 without additional GET_FIGHTER
        Fighter_GObj* victim;

        ftCommon_8007DB58(gobj);
        ftCo_8009750C(gobj);

        victim = getFtVictim(fp);

        if (victim != NULL) {
            if (fp->x221B_b5) {
                ftCo_800DC750(victim);
            } else {
                Fighter_GObj* tmp = victim;
                ftCo_800DC750(gobj);
                ftCo_800DA698(tmp, false);
            }
            ftCommon_8007DB58(victim);
        }
    }

    if (fp->ground_or_air == GA_Air) {
        ftCo_80090780(gobj);
    } else {
        ftCo_DownSpot_Enter(gobj);
    }

    fp->x2224_b3 = false;
}

void fn_800C8E40(Fighter* fp, FtSFX* sfx)
{
    ft_PlaySFX(fp, fp->ft_data->x4C_sfx->xC, SFX_VOLUME_MAX, SFX_PAN_MID);
}

void fn_800C8E74(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_MASTERH || fp->kind == FTKIND_CREZYH) {
        if (fp->kind == FTKIND_MASTERH) {
            ftMh_MS_343_80151484(gobj);
        } else {
            ftCh_GrabUnk1_8015ADD0(gobj);
        }
        gm_80167470(fp->player_id, fp->x221F_b4);
        return;
    }

    fp->x2224_b3 = true;
    if (fp->dmg.kb_applied) {
        fn_800C8_inline(gobj);
    }
}

void ftCo_800C8F6C(void)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(HSD_JObjLoadJoint(Fighter_804D6504));
    HSD_MObj* mobj;
    HSD_Material* mat;

    if (dobj != NULL) {
        mobj = dobj->mobj;
    } else {
        mobj = NULL;
    }

    ft_804D6588 = mobj;
    mat = mobj->mat;
    if (mat != NULL) {
        mat->diffuse = p_ftCommonData->x7D8;
    }
}

void ftCo_800C8FC4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (Player_GetMoreFlagsBit0(fp->player_id)) {
        fp->x2034 = p_ftCommonData->x7DC;
        fp->x2038 = p_ftCommonData->x7E0;
        fp->x2227_b3 = true;
        ft_800C80A4(fp);
        ftCommon_80080460(fp);
    }
}

void ftCo_800C9034(Fighter_GObj* gobj)
{
    ftCo_800D4F24(gobj, 0);
}
