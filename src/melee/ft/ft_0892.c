#include "ft_0892.h"

#include "ft_0C88.h"
#include "ftcommon.h"
#include "ftdata.h"
#include "ftwaitanim.h"
#include "math.h"

#include "ft/chara/ftFox/ftFx_AppealS.h"
#include "ft/fighter.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ftCLink/ftCl_Init.h"
#include "ftCommon/ftCo_DownSpot.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftLink/ftLk_AttackAir.h"
#include "ftMasterHand/ftMh_Wait1_2.h"
#include "it/items/itpeachparasol.h"

#include <baselib/gobj.h>

/// #ft_800892D4

/// #ft_80089460

/// #ft_800895E0

/// #ft_80089768

/// #ft_80089824

union Struct2070* ft_80089884(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2070;
}

UnkPlBonusBits* ft_80089890(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d4;
}

u16 ft_8008989C(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->dmg.x18ec_instancehitby;
}

struct Struct2074* ft_800898A8(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2074;
}

ft_800898B4_t* ft_800898B4(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d8;
}

bool ft_800898C0(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->x2070.x2073 == 113 || ft->x2070.x2073 == 114 ||
         ft->x2070.x2073 == 99) ||
        ftFx_AppealS_CheckIfUsed(ft))
    {
        return true;
    }
    return false;
}

/// #ft_80089914

/// #fn_8008998C

/// #ft_80089B08

/// #ft_8008A1B8

/// #ft_8008A1FC

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

// Seems to be called to end many actions if no frames are remaining
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

// Transition state to ftCo_MS_Wait or otherwise neutral state
void ft_8008A348(Fighter_GObj* fighter_gobj, float anim_blend)
{
    Fighter* fighter;
    FighterKind kind;

    fighter = GET_FIGHTER((HSD_GObj*) fighter_gobj);
    if (fighter->x2224_b2 & 1) {
        ftCo_DownSpot_Enter(fighter_gobj);
        return;
    }
    if (ftCo_800C5240(fighter_gobj) != false) {
        ftCo_800C4ED8(fighter_gobj);
        return;
    }
    if (fighter->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fighter);
    }
    if (fighter->kind == FTKIND_PEACH) {
        if ((fighter->item_gobj != NULL) &&
            (itGetKind(fighter->item_gobj) == It_Kind_Peach_Parasol))
        {
            it_802BDB94(fighter->item_gobj);
        }
    }
    Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_Wait, Ft_MF_None, 0.0f,
                              1.0f, anim_blend, NULL);
    if ((ftCo_8008A698(fighter) != false) &&
        (((struct ftData_80085FD4_ret*) ftData_80085FD4(fighter,
                                                        ftCo_MS_DeadUpFall))
             ->x8 != 0U))
    {
        ftCo_8008A6D8(fighter_gobj, ftCo_MS_DeadUpFall);
    }
    ftCommon_8007EFC0(fighter, p_ftCommonData->x5F0);
    kind = fighter->kind;
    switch (kind) { /* irregular */
    case FTKIND_LINK:
        ftLk_AttackAir_800EB3BC((HSD_GObj*) fighter_gobj);
        return;
    case FTKIND_CLINK:
        ftCl_Init_8014919C((HSD_GObj*) fighter_gobj);
        return;
    }
}
