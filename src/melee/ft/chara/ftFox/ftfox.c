#include <melee/ft/chara/ftFox/ftfox.h>

BOOL func_800E5534(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*)gobj->user_data;
    
    return fp->sa.fox.x222C_blasterGObj ? TRUE : FALSE;
}

void ftFox_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*)gobj->user_data;
    
    fp->sa.fox.x222C_blasterGObj = 0;
    func_80074A4C(gobj, 0, 0);
}

void func_800E5588(HSD_GObj* gobj)
{
    ftFox_RemoveBlaster(gobj);
}

void ftFox_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftFox_OnItemInvisible(HSD_GObj* gobj) 
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFox_OnItemVisible(HSD_GObj* gobj) 
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFox_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftFox_OnLoadForFalco(Fighter* fp) 
{
    PUSH_ATTRS(fp, ftFoxAttributes);
}

void ftFox_OnLoad(HSD_GObj* gobj) {

    Fighter* fp = gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftFoxAttributes);
    
    {
        ftFoxAttributes *fox_attr = fp->x2D4_specialAttributes;
        func_8026B3F8(item_list[0], fox_attr->x1C_FOX_BLASTER_SHOT_ITKIND);
        func_8026B3F8(item_list[1], fox_attr->x20_FOX_BLASTER_GUN_ITKIND);
        func_8026B3F8(item_list[2], It_Kind_Fox_Illusion);
    }
}

void ftFox_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftFoxAttributes);
}

extern f32 lbl_804D9244;  ///0.0f

void ftFox_OnKnockbackEnter(HSD_GObj* gobj) {
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFox_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
    ftAnim_ApplyPartAnim(fighter_gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(fighter_gobj, 4, 2, 0.0f); 
}

//// End of File
