#include "ftmasterhandsweepwait.h"

#include "ftmasterhandwait12.h"

#include "forward.h"
#include <melee/ft/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftbosslib.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

void ftMh_SweepWait_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_SweepWait_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_SweepWait_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_SweepWait_Coll(HSD_GObj* gobj) {}

void ftMh_MS_348_80151BB8(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftMh_MS_Slap, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
