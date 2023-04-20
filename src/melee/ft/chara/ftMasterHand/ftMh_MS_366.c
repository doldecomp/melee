#include "ftMh_MS_366.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"

void ftMh_MS_366_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_366_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_366_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_366_Coll(HSD_GObj* gobj) {}

void ftMh_MS_366_80153820(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Jet_StartMotion, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}
