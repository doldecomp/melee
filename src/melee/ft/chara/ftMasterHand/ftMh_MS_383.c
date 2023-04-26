#include "ftMh_MS_383.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ftCrazyHand/ftCh_Init.h"

void ftMh_MS_383_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2204_ftcmd_var1 != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->x2204_ftcmd_var1 = 0;
    }

    /// @todo  inlined? possibly shared with ftMh_MS_382_Anim
    if ((ftBossLib_8015C31C() != 0) || (ftBossLib_8015C3A0() != 0) ||
        (!ftAnim_IsFramesRemaining(gobj)))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_383_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_383_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_383_Coll(HSD_GObj* gobj) {}

void ftMh_MS_383_80155484(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* gobj1 = ftBossLib_8015C3E8(28);
    if (ftBossLib_8015C31C() == 0) {
        ftCh_Init_8015A560(gobj1);
    }
    fp->x1A5C = gobj1;
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagRockPaper, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}
