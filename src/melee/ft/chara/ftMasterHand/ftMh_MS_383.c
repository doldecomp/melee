#include "ftMh_MS_383.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ftCrazyHand/ftCh_Init.h"

// 80155388 151F68
// https://decomp.me/scratch/6nLDB
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

// 8015541C 151FFC
void ftMh_MS_383_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 80155460 152040
void ftMh_MS_383_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80155480 152060
void ftMh_MS_383_Coll(HSD_GObj* gobj)
{
    return;
}

// 80155484 152064
// https://decomp.me/scratch/jsnxb
void ftMh_MS_383_80155484(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    gobj_2 = ftBossLib_8015C3E8(0x1CU);

    if (ftBossLib_8015C31C() == 0) {
        ftCh_Init_8015A560(gobj_2);
    }

    fp->x1A5C = gobj_2;
    Fighter_ChangeMotionState(gobj, 0x180, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}
