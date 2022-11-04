#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80151B14(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80151B50(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_80151B70(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80151BB4(void)
{
    return;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_80151BB8(HSD_GObj* fighter_gobj)
{
    u32 unused[2];
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15D, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}
