#include "ftMh_FingerGun3.h"

#include "ftMh_Wait1_2.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"

#include "ftMasterHand/forward.h"

#include "pl/player.h"

void ftMh_FingerGun3_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_FingerGun3_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_FingerGun3_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_FingerGun3_Coll(HSD_GObj* gobj) {}

void ftMh_MS_366_80153820(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_BackAirplane1, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
