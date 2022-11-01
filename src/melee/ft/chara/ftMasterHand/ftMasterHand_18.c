#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_801539EC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(fighter_gobj);
    }
}

void ftMasterHand_80153A30(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    ftbosslib_8015BF74(fighter_gobj, ext_attr->x58);
}

void ftMasterHand_80153A60(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80153A64(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x171, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->xB0_pos.x = ext_attr->x60;
    fp->xB0_pos.y = ext_attr->x64;
    fp->x80_self_vel.z = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->x80_self_vel.x = 0.0F;
}
