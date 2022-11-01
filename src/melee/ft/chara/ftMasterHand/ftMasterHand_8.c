#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

void ftMasterHand_80151C04(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80151C40(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80151C84(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80151CA4(void)
{
    return;
}

void ftMasterHand_80151CA8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->xB0_pos.y = ext_attr->x50.x; // TODO: The code matches, but is this right?
    fp->x80_self_vel.x = 0.0F;
}
