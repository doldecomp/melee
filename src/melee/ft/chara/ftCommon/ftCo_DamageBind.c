#include "ftCo_DamageBind.h"

#include "ftCo_DamageFall.h"
#include "ftCo_Lift.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "pl/player.h"

#include <common_structs.h>

bool ftCo_800C44CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860_element == 12 && !fp->x2228_b2) {
        switch (fp->x2070.x2071_b0_3) {
        case 5:
        case 9:
        case 11:
        case 12:
            return false;
        default:
            ftCo_800C4550(gobj);
            return true;
        }
    }
    return false;
}

static void commonCall(Fighter* fp)
{
    ftCommon_InitGrab(
        fp, 0,
        (fp->dmg.x1830_percent * p_ftCommonData->x66C) +
            (p_ftCommonData->x65C *
                 (p_ftCommonData->x660 - Player_GetHandicap(fp->player_id)) +
             p_ftCommonData->x658 +
             p_ftCommonData->x664 * (p_ftCommonData->x668 -
                                     (Player_80033BB8(fp->player_id) + 1))));
}

void ftCo_800C4550(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    if (fp->ground_or_air == GA_Air) {
        ftCo_80090780(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageBind, Ft_MF_None, 0.0f,
                                  1.0f, 0.0f, NULL);
        commonCall(fp);
    }
}

void ftCo_DamageBind_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= p_ftCommonData->x670;
    ftCommon_8007DC08(fp, p_ftCommonData->x674);
    if (fp->grab_timer <= 0.0f) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_DamageBind_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageBind_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageBind_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}
