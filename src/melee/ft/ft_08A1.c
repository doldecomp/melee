#include "ft_0892.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ftCLink/ftCl_Init.h"
#include "ftCommon/ftCo_DownSpot.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftLink/ftLk_AttackAir.h"
#include "ftMasterHand/ftMh_Wait1_2.h"
#include "it/it_26B1.h"
#include "it/items/itpeachparasol.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

bool ft_8008A1FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.lstick.x * fp->facing_dir < 0.0F) ||
        (ABS(fp->input.lstick.x) < p_ftCommonData->x24))
    {
        return true;
    }
    return false;
}

static inline bool ft_8008A244_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r4 = GET_FIGHTER(gobj);
    f32 var_f2;

    var_f2 = temp_r4->input.lstick.x;
    if ((var_f2 * temp_r4->facing_dir < 0.0F) ||
        (ABS(var_f2) < p_ftCommonData->x24))
    {
        return true;
    }
    return false;
}

bool ft_8008A244(Fighter_GObj* gobj)
{
    if (ft_8008A244_inline(gobj)) {
        ft_8008A2BC(gobj);
        return true;
    }

    return false;
}

/// Seems to be called to end many actions if no frames are remaining
void ft_8008A2BC(HSD_GObj* gobj)
{
    if (ftLib_800872A4(gobj) == FTKIND_MASTERH) {
        ftMh_MS_389_80151018(gobj);
    } else if (ftLib_800872A4(gobj) == FTKIND_CREZYH) {
        ftCh_GrabUnk1_8015BC88(gobj);
    } else {
        ft_8008A348(gobj, 0);
    }
}

void ft_8008A324(HSD_GObj* gobj)
{
    ft_8008A348(gobj, -1.0f);
}

/// Transition state to ftCo_MS_Wait or otherwise neutral state
void ft_8008A348(Fighter_GObj* gobj, float anim_blend)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2224_b2) {
        ftCo_DownSpot_Enter(gobj);
        return;
    }
    if (ftCo_800C5240(gobj)) {
        ftCo_800C4ED8(gobj);
        return;
    }
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    if (fp->kind == FTKIND_PEACH) {
        if (fp->item_gobj != NULL &&
            itGetKind(fp->item_gobj) == It_Kind_Peach_Parasol)
        {
            it_802BDB94(fp->item_gobj);
        }
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_Wait, Ft_MF_None, 0.0f, 1.0f,
                              anim_blend, NULL);
    if (ftCo_8008A698(fp) && ftData_80085FD4(fp, ftCo_MS_DeadUpFall)->x8 != 0)
    {
        ftCo_8008A6D8(gobj, ftCo_MS_DeadUpFall);
    }
    ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
    switch (fp->kind) {
    case FTKIND_LINK:
        ftLk_AttackAir_800EB3BC(gobj);
        return;
    case FTKIND_CLINK:
        ftCl_Init_8014919C(gobj);
        return;
    default:
        return;
    }
}
