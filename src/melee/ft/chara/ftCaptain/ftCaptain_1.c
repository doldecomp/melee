#include "ftCaptain.h"

// func_800E2888
// OnRespawn/OnDeath (same function I've seen called differently)
// https://decomp.me/scratch/XZ1Jx
void ftCaptain_OnDeath(HSD_GObj* fighter_gobj)
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
void ftCFalcon_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

// ftCFalcon_OnItemInvisible
// OnMakeItemInvisible
// https://decomp.me/scratch/maRvM
void ftCFalcon_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

// ftCFalcon_OnItemVisible
// OnMakeInvisible
// https://decomp.me/scratch/95tCp
void ftCFalcon_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

// ftCFalcon_OnItemDrop
// Used for both OnItemRelease and OnUnknownItemRelated
// https://decomp.me/scratch/PCT5B
void ftCFalcon_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

// ftCaptain_OnLoadForGanon
// https://decomp.me/scratch/9AwRw
void ftCaptain_OnLoadForGanon(Fighter* fighter) {
    PUSH_ATTRS(fighter, CaptainAttr);
}

// func_800E2AEC
// OnLoad
// https://decomp.me/scratch/aZ4Wn
void ftCaptain_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fighter;
    CaptainAttr *sA2;

    fighter = (Fighter*)fighter_gobj->user_data;
    fighter->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fighter, CaptainAttr);
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