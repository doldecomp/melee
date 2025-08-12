#include <platform.h>

#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include "ftCo_AttackDash.h"

#include "ftCo_ItemThrow.h"
#include "ftCo_Wait.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftswing.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "ftKirby/ftKb_Init.h"
#include "it/it_26B1.h"

#include <common_structs.h>

/* 08B498 */ static void decideFighter(Fighter_GObj* gobj);
/* 08B4D4 */ static void doEnter(Fighter_GObj* gobj);

bool ftCo_AttackDash_CheckInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_PAD_A) {
        if (fp->item_gobj != NULL) {
            if (fp->input.held_inputs & HSD_PAD_LR ||
                it_8026B30C(fp->item_gobj) == 0)
            {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
                return true;
            }
            switch (it_8026B30C(fp->item_gobj)) {
            case 2:
                ftCo_Attack_800CCF58(gobj, 4);
                return true;
            }
        }
        decideFighter(gobj);
        return true;
    }
    return false;
}

static void decideFighter(Fighter_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->kind) {
    case FTKIND_KIRBY:
        ftKb_SpecialN_800F1F68(gobj);
        return;
    default:
        doEnter(gobj);
        return;
    }
}

static void doEnter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_AttackDash, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.attackdash.x0 = 0;
}

void ftCo_AttackDash_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_AttackDash_SetMv0(HSD_GObj* gobj)
{
    u8 _[4] = { 0 };
    GET_FIGHTER(gobj)->mv.co.attackdash.x0 = p_ftCommonData->x68;
}

void ftCo_AttackDash_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_800D8AE0(gobj) && fp->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackDash_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085030(gobj, p_ftCommonData->x50 * fp->co_attrs.gr_friction,
                fp->facing_dir);
}

void ftCo_AttackDash_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}
