#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80154A78(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    fp->x2204_ftcmd_var1 = FALSE;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17A, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2222_flag.bits.b2 = TRUE;
    func_8007E2F4(fp, 0x1FFU);
    func_8007E2FC(fighter_gobj);
    ftMasterHand_80155B80(fp->x1A58_interactedFighter);

    fp->x234C_pos.x = ext_attr->x118_pos.x;
    fp->x234C_pos.y = ext_attr->x118_pos.y;
    fp->x234C_pos.z = 0.0F;
}

static void ftMasterHand_80154B2C_inline_1(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->x2204_ftcmd_var1 != 0) {
        func_8015C5F8(fighter_gobj);
        fp->x2204_ftcmd_var1 = 0;
    }
}

static void ftMasterHand_80154B2C_inline_2(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (((Fighter*) fighter_gobj->user_data)->sa.masterhand.x2250 == 0x17B)
            ftMasterHand_80154E78(fighter_gobj);
        else
            ftMasterHand_80155014(fighter_gobj);
    }
}

void ftMasterHand_80154B2C(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    ftMasterHand_80154B2C_inline_1(fighter_gobj);
    ftMasterHand_80154B2C_inline_2(fighter_gobj);
}

void ftMasterHand_80154BB0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80154BF4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);
    ftbosslib_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80154C54(HSD_GObj* fighter_gobj)
{
    u32 unused;

    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2358_stateVar7 == 0.0F) {
        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;
    }
}
