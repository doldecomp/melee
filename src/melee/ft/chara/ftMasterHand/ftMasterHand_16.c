#include "ftMasterHand_16.h"

#include "ftMasterHand_03.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"

// 8015377C 15035C
// https://decomp.me/scratch/003fu
void ftMasterHand_8015377C(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMasterHand_80151018(arg0);
    }
}

// 801537B8 150398
void ftMasterHand_801537B8(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 801537FC 1503DC
void ftMasterHand_801537FC(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 8015381C 1503FC
void ftMasterHand_8015381C(HSD_GObj* gobj)
{
    return;
}

// 80153820 150400
// https://decomp.me/scratch/d4xeU
void ftMasterHand_80153820(HSD_GObj* arg0)
{
    Fighter_ChangeMotionState(arg0, 0x16F, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
}
