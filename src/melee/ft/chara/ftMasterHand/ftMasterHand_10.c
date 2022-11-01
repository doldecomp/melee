#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void lbl_80152138(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void lbl_80152174(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void lbl_801521B8(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void lbl_801521D8(void)
{
    return;
}

void lbl_801521DC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 unk[2];

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x162, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x2340_f32 = 107.0F;
}

void lbl_8015223C(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void lbl_80152278(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void lbl_801522BC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    MasterHandAttributes* ext_attr = ftdata->ext_attr;
    func_80085134(fighter_gobj);

    if ((--fp->x2340_f32 > ext_attr->x84) || (fp->x2340_f32 < 0.0F))
        fp->x80_self_vel.x = 0.0F;
    else
        ftbosslib_8015C010(fighter_gobj, ext_attr->x80);

    ftbosslib_8015C190(fighter_gobj);
}
