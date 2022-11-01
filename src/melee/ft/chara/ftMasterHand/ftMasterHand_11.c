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

void ftMasterHand_8015247C(HSD_GObj* fighter_gobj);

void lbl_801523BC(HSD_GObj* fighter_gobj)
{
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;

    if (ftAnim_IsFramesRemaining(fighter_gobj)) {
        return;
    }
    r31_fp = fighter_gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    ftMasterHand_8015247C(fighter_gobj);
    r31_fp->x2348_stateVar3 = r30_attributes->xA0;
}

// 80152414 14EFF4
// https://decomp.me/scratch/u6Ii5
void lbl_80152414(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

void lbl_80152458(HSD_GObj* arg0)
{
    func_80085134(arg0);
}

void lbl_80152478(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_8015247C(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

// 801524C8 14F0A8
// https://decomp.me/scratch/zoAeT
void lbl_801524C8(HSD_GObj* gobj) {
    Fighter* temp_r4;
    u32 unk[2];

    temp_r4 = gobj->user_data;
    if (!--temp_r4->x2348_stateVar3) {
        func_801525E0(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
}



// 80152544 14F124
// https://decomp.me/scratch/nlkfy
void lbl_80152544(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80152588 14F168
// https://decomp.me/scratch/2eorR
void lbl_80152588(HSD_GObj* gobj) {
    ftData* r4_ftData;
    MasterHandAttributes* r31_attributes;
    u32 unk[2];

    r4_ftData = ((Fighter*) gobj->user_data)->x10C_ftData;
    r31_attributes = r4_ftData->ext_attr;
    func_80085134(gobj);
    func_8015C010(gobj, r31_attributes->xA4);
    func_8015C190(gobj);
}



// 801525DC 14F1BC
void lbl_801525DC(HSD_GObj* gobj) {
    return;
}


// 801525E0 14F1C0
// https://decomp.me/scratch/WHp9s
void func_801525E0(HSD_GObj* gobj) {
    u32 unk[2];

    ((Fighter*)gobj->user_data)->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x165, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}
