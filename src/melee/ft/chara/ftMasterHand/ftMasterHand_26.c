#include "ftMasterHand_26.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"

// 80154FAC 151B8C
void ftMasterHand_80154FAC(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftBossLib_8015BD20(arg0);
}

// 80154FF0 151BD0
void ftMasterHand_80154FF0(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80155010 151BF0
void ftMasterHand_80155010(HSD_GObj* gobj)
{
    return;
}

// 80155014 151BF4
// https://decomp.me/scratch/ZAwzc
void ftMasterHand_80155014(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x17C, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}
