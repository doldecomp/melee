#include "ftMh_MS_366.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"

// 8015377C 15035C
// https://decomp.me/scratch/003fu
void ftMh_MS_366_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 801537B8 150398
void ftMh_MS_366_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 801537FC 1503DC
void ftMh_MS_366_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 8015381C 1503FC
void ftMh_MS_366_Coll(HSD_GObj* gobj)
{
    return;
}

// 80153820 150400
// https://decomp.me/scratch/d4xeU
void ftMh_MS_366_80153820(HSD_GObj* arg0)
{
    Fighter_ChangeMotionState(arg0, 0x16F, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
}
