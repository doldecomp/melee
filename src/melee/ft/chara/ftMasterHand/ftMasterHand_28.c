#include "ftMasterHand_28.h"

#include "ftMasterHand_03.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ftCrazyHand/ftcrazyhand.h"

// 8015521C 151DFC
// https://decomp.me/scratch/veN50
void ftMh_MS_382_Anim(HSD_GObj* gobj)
{
    Fighter* fp;

    if ((ftBossLib_8015C31C() != 0) || (ftBossLib_8015C3A0() != 0) ||
        (!ftAnim_IsFramesRemaining(gobj)))
    {
        fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

// 80155290 151E70
void ftMh_MS_382_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 801552D4 151EB4
void ftMh_MS_382_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 801552F4 151ED4
void ftMh_MS_382_Coll(HSD_GObj* gobj)
{
    return;
}

// 801552F8 151ED8
// https://decomp.me/scratch/x0WJ4
void ftMh_MS_382_801552F8(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* gobj_2;

    fp = gobj->user_data;
    fp->x2204_ftcmd_var1 = 0;
    gobj_2 = ftBossLib_8015C3E8(0x1CU);

    if (ftBossLib_8015C31C() == 0) {
        ftCh_Init_8015A3F4(gobj_2);
    }

    fp->x1A5C = gobj_2;
    Fighter_ChangeMotionState(gobj, 0x17F, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}
