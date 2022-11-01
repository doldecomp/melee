#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_801517B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (!Player_GetPlayerSlotType(fp->xC_playerID))
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801517F4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    fp->x80_self_vel.y += ext_attr->x150;
    fp->x80_self_vel.z += ext_attr->x158;
}

void ftMasterHand_80151824(void)
{
    return;
}

void ftMasterHand_80151828(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15A, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

static void ftMasterHand_80151918(HSD_GObj* fighter_gobj);

void ftMasterHand_80151874(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151918(fighter_gobj);
}

void ftMasterHand_801518B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (!Player_GetPlayerSlotType(fp->xC_playerID))
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801518F4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80151914(void)
{
    return;
}

static void ftMasterHand_80151918(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    fp->x234C_pos.x = (fp->xB0_pos.x - ext_attr->x3C);
    fp->x234C_pos.y = ext_attr->x38;
    fp->x234C_pos.z = 0.0F;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15B, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

static void ftMasterHand_80151AC8(HSD_GObj* fighter_gobj);

void ftMasterHand_8015198C(HSD_GObj* fighter_gobj)
{
    MasterHandAttributes* ext_attr;
    Fighter* fp;
    Fighter* r8_fp;
    Vec3 sp14;
    u32 unk[2];

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        fp = fighter_gobj->user_data;
        func_80054158(0, &sp14);

        if (fp->xB0_pos.x < sp14.x) {
            ftMasterHand_80151AC8(fighter_gobj);
            return;
        }

        r8_fp = fighter_gobj->user_data;
        ext_attr = r8_fp->x10C_ftData->ext_attr;

        r8_fp->x234C_pos.x = r8_fp->xB0_pos.x - ext_attr->x3C;
        r8_fp->x234C_pos.y = ext_attr->x38;
        r8_fp->x234C_pos.z = 0.0F;

        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15B, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }
}

void ftMasterHand_80151A44(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80151A88(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    ftbosslib_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80151AC4(void)
{
    return;
}

static void ftMasterHand_80151AC8(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}
