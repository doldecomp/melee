#include "ftMh_MS_379.h"

#include "ftMh_CaptureWaitMasterHand.h"
#include "ftMh_MS_372.h"
#include "ftMh_MS_376.h"
#include "ftMh_MS_378.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftMh_MS_379_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_379_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_379_Coll(HSD_GObj* gobj) {}

void ftMh_MS_379_80155014(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Grab_Unk1_MotionStart, 0, 0, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}
