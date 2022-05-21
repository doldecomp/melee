#include "ftCaptain.h"

// func_800E2888
// OnRespawn/OnDeath (same function I've seen called differently)
// https://decomp.me/scratch/XZ1Jx
void ftCFalcon_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = (Fighter*)fighter_gobj->user_data;
    func_80074A4C(fighter_gobj,0,0);
    fighter_data->sa.captain.x2230 = 0;
    fighter_data->sa.captain.x222C = 0;
}

// lbl_800E28C8
// https://decomp.me/scratch/IoniN
void lbl_800E28C8(HSD_GObj* fighter_gobj) {
    func_800E3278(fighter_gobj);
}

// func_800e28e8
// Used for both OnItemPickup and OnItemCatch
// https://decomp.me/scratch/MeDCx
void func_800E28E8(HSD_GObj* fighter_gobj, s32 unk_var)
{
    Fighter* fighter_data = fighter_gobj->user_data;
    s32 unused, unused2;//Only figured this out looking at Marth's

    if (func_8026B2B4(fighter_data->x1974_heldItem) == 0)
    {
        switch(func_8026B320(fighter_data->x1974_heldItem))
        {
            case 1: func_80070FB4(fighter_gobj, 1, 1); break;
            case 2: func_80070FB4(fighter_gobj, 1, 0); break;
            case 3: func_80070FB4(fighter_gobj, 1, 2); break;
            case 4: func_80070FB4(fighter_gobj, 1, 3); break;
        }

        if(unk_var != 0)
        {
            func_80070C48(fighter_gobj, 1);
        }
    }
}

// func_800E29C8
// OnMakeItemInvisible
// https://decomp.me/scratch/maRvM
void func_800E29C8(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = (Fighter*)fighter_gobj->user_data;
    if(func_8026B2B4(fighter_data->x1974_heldItem) == 0)
    {
        func_80070CC4(fighter_gobj, 1);
    }
}

// func_800E2A10
// OnMakeInvisible
// https://decomp.me/scratch/95tCp
void func_800E2A10(HSD_GObj* fighter_gobj)
{
    Fighter* ft = (Fighter*)fighter_gobj->user_data;
    if(func_8026B2B4(ft->x1974_heldItem) == 0)
    {
        func_80070C48(fighter_gobj, 1);
    }
}

// func_800E2A58
// Used for both OnItemRelease and OnUnknownItemRelated
// https://decomp.me/scratch/PCT5B
void func_800E2A58(HSD_GObj* fighter_gobj, s32 unk1)
{
    func_80070FB4(fighter_gobj, 1, -1);//Fighter_SetHoldKind
    if(unk1 != 0)
    {
        func_80070CC4(fighter_gobj, 1);//Fighter_ApplyHandAnim
    }
}

// func_800E2AAC
// https://decomp.me/scratch/9AwRw
void func_800E2AAC(Fighter* arg0) {
    CaptainAttr* sA2;
    CaptainAttr* ext_attr;

    sA2 = arg0->x2D8_specialAttributes2;
    ext_attr = arg0->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    arg0->x2D4_specialAttributes = sA2;
}

// func_800E2AEC
// OnLoad
// https://decomp.me/scratch/aZ4Wn
void ftCFalcon_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data;
    CaptainAttr *sA2;

    fighter_data = (Fighter*)fighter_gobj->user_data;
    fighter_data->x2224_flag.bits.b7 = 1;

    sA2 = (CaptainAttr*)fighter_data->x2D8_specialAttributes2;

    *(CaptainAttr*)fighter_data->x2D8_specialAttributes2 = *(CaptainAttr*)fighter_data->x10C_ftData->ext_attr;

    fighter_data->x2D4_specialAttributes = sA2;
}

// func_800E2B40
// ResetAttribute
// https://decomp.me/scratch/mKLYI
void func_800E2B40(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = fighter_gobj->user_data;
    CaptainAttr* restore_block = fighter_data->x10C_ftData->ext_attr;
    CaptainAttr* special_attributes = fighter_data->x2D4_specialAttributes;
    *special_attributes = *restore_block;
}