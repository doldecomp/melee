#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/ft/ftanim.h>

void ftMasterHand_8015377C(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_801537B8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801537FC(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_8015381C(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80153820(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16F, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}
