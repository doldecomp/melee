#include "ftNess.h"

void ftNess_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.ness.x2240_flashGObj = NULL;
    ft->sa.ness.x2244_pkThunderGObj = NULL;
    ft->sa.ness.x2248_baseballBatGObj = NULL;
    ft->sa.ness.x222C_yoyoGObj = NULL;
    ft->sa.ness.x224C_thunderGFX = FALSE;
}

void ftNess_OnLoad(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;
    void** item_list = ft->x10C_ftData->x48_items;

    PUSH_ATTRS(ft, ftNessAttributes);

    func_8026B3F8(item_list[0], It_Kind_Ness_PKFire);
    func_8026B3F8(item_list[1], It_Kind_Ness_PKFire_Flame);
    func_8026B3F8(item_list[2], It_Kind_Ness_PKFlush);
    func_8026B3F8(item_list[8], It_Kind_Ness_PKFlush_Explode);
    func_8026B3F8(item_list[3], It_Kind_Ness_PKThunder);
    func_8026B3F8(item_list[4], It_Kind_Ness_PKThunder1);
    func_8026B3F8(item_list[5], It_Kind_Ness_PKThunder2);
    func_8026B3F8(item_list[6], It_Kind_Ness_PKThunder3);
    func_8026B3F8(item_list[7], It_Kind_Ness_PKThunder4);
    func_8026B3F8(item_list[9], It_Kind_Ness_Bat);
    func_8026B3F8(item_list[10], It_Kind_Ness_Yoyo);
}

void ftNess_OnDamage(HSD_GObj* gobj)
{
    ftNess_YoyoItemDespawn(gobj);
    ftNess_ItemPKFlushSetNULL(gobj);
    ftNess_SpecialHiTakeDamage(gobj);
    ftNess_ItemNessBatRemove(gobj);
}

void ftNess_OnAbsorb(HSD_GObj* gobj)
{
    ftNess_AbsorbThink_DecideAction(gobj);
}

f32 ftNess_GetAbsorbHeal(Fighter* ft)
{
    return ((ftNessAttributes*)ft->x2D4_specialAttributes)->x94_PSI_MAGNET_HEAL_MUL;
}

void ftNess_OnItemPickup(HSD_GObj* fighterObj, BOOL catchItemFlag) {
    Fighter_OnItemPickup(fighterObj, catchItemFlag, 1, 1);
}

void ftNess_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftNess_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftNess_OnItemDrop(HSD_GObj* gobj, BOOL dropItemFlag) {
    Fighter_OnItemDrop(gobj, dropItemFlag, 1, 1);
}

void ftNess_CopySpecialAttrs(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;
    
    ftNessAttributes* sA2 = (ftNessAttributes*)ft->x2D4_specialAttributes;
    ftNessAttributes* ext_attr = (ftNessAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
}

void ftNess_OnKnockbackEnter(HSD_GObj* gobj) // Change model's MatAnim frames to hurt textures //
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftNess_OnKnockbackExit(HSD_GObj* fighter_gobj) // Change model's MatAnim frames to normal textures //
{
    func_800704F0(fighter_gobj, 1, 0.0f);
    func_800704F0(fighter_gobj, 0, 0.0f);
}
