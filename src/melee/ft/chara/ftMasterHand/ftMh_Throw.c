#include <platform.h>

#include "ft/forward.h"
#include "ftMasterHand/forward.h"

#include "ftMh_Throw.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "pl/player.h"

void ftMh_Throw_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Throw_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_Throw_Coll(HSD_GObj* gobj) {}

void ftMh_MS_379_80155014(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Slam, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->cmd_vars[0] = 0;
}
