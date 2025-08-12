#include "ftMh_TagCrush.h"

#include "ftMh_Wait1_2.h"

#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ftCrazyHand/ftCh_Init.h"

#include "ftMasterHand/forward.h"

#include "pl/player.h"

void ftMh_TagCrush_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C31C() || ftBossLib_8015C3A0() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_TagCrush_IASA(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

void ftMh_TagCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_TagCrush_Coll(HSD_GObj* gobj) {}

void ftMh_MS_382_801552F8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[1] = 0;
    {
        HSD_GObj* gobj_2 = ftBossLib_8015C3E8(28);
        if (!ftBossLib_8015C31C()) {
            ftCh_Init_8015A3F4(gobj_2);
        }
        fp->x1A5C = gobj_2;
    }
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagApplaud, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
