#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_8015236C(void)
{
    return;
}

void ftMasterHand_80152370(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

static void ftMasterHand_8015247C(HSD_GObj* fighter_gobj);

void ftMasterHand_801523BC(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

        ftMasterHand_8015247C(fighter_gobj);
        fp->x2348_stateVar3 = ext_attr->xA0;
    }
}

void ftMasterHand_80152414(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80152458(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80152478(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_8015247C(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

static void ftMasterHand_801525E0(HSD_GObj* fighter_gobj);

void ftMasterHand_801524C8(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    Fighter* fp = fighter_gobj->user_data;

    if (!--fp->x2348_stateVar3)
        ftMasterHand_801525E0(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }
}

void ftMasterHand_80152544(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80152588(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    ftData* ftdata = ((Fighter*) fighter_gobj->user_data)->x10C_ftData;
    MasterHandAttributes* ext_attr = ftdata->ext_attr;

    func_80085134(fighter_gobj);
    ftbosslib_8015C010(fighter_gobj, ext_attr->xA4);
    ftbosslib_8015C190(fighter_gobj);
}

void ftMasterHand_801525DC(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_801525E0(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    ((Fighter*) fighter_gobj->user_data)->x80_self_vel.x = 0.0F;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x165, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}
