#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/ft/ftanim.h>

void ftMasterHand_80152634(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_80152670(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801526B4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801526D4(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801526D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x166, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x2340_f32 = 0.0F;
}

void ftMasterHand_80152738(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80152774(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801527B8(HSD_GObj* fighter_gobj)
{
    f32 tmp;

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);

    tmp = ++fp->x2340_f32;

    if (tmp > ext_attr->xB0 && fp->x2340_f32 < ext_attr->xB4)
        ftbosslib_8015C010(fighter_gobj, ext_attr->xB8);
    else
        fp->x80_self_vel.x = 0.0F;

    ftbosslib_8015C190(fighter_gobj);
}
