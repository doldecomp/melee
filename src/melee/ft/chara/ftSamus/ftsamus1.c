#include <melee/ft/chara/ftSamus/ftsamus.h>

void ftSamus_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    func_80074A4C(fighter_gobj, 0, 0);
    fp->sa.samus.x222C = 0;
    fp->sa.samus.x2230 = 0;
    fp->sa.samus.x2238 = 0;
    fp->sa.samus.x2244 = 0;
    fp->sa.samus.x223C = 0;
    fp->sa.samus.x2240 = 0;
}

void ftSamus_OnLoad(HSD_GObj* fighter_gobj) {

    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSamusAttributes);
    
    func_8026B3F8(item_list[0], 0x5DU);
    func_8026B3F8(item_list[1], 0x5EU);
    func_8026B3F8(item_list[2], 0x5FU);
    func_8026B3F8(item_list[3], 0x60U);
}

void ftSamus_80128428(HSD_GObj* fighter_gobj) {
    ftSamus_80129258(fighter_gobj);
    ftSamus_8012A640(fighter_gobj);
    func_800D9C98(fighter_gobj);
}

void ftSamus_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 0);
}

void ftSamus_OnItemInvisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 0);
}

void ftSamus_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 0);
}

void ftSamus_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftSamus_80128628(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* attr = fp->x2D4_specialAttributes;
    s32 samus_x2230 = fp->sa.samus.x2230;
    if (samus_x2230 == attr->x18) {
        func_800BFFD0(fp, 0x35, 0);
    }
}

void ftSamus_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftSamusAttributes);
    if (fp->x34_scale.y != 1.0f) {                                        
        sA2->x8 *= fp->x34_scale.y;                                       
        sA2->x74_vec.y *= fp->x34_scale.y;    
        sA2->x54 *= fp->x34_scale.y;                                                                              
        sA2->x58 *= fp->x34_scale.y;    
        SCALE_HEIGHT_ATTRS(6);                                                                   
    }  
}

void ftSamus_80128770(HSD_AObj* fighter_gobj, f32 rate) {
    if (fighter_gobj && !(HSD_AObjGetFlags(fighter_gobj) & 0x20000000)) {
        HSD_AObjSetRate(fighter_gobj, rate);
    }
}

void ftSamus_801287C4(HSD_GObj* fighter_gobj, s32 index, f32 argf) {

    Fighter *fighter_copy;
    Vec scale;

    Fighter* fp = getFighter(fighter_gobj);
    void** item_list = fp->x10C_ftData->x48_items;
    struct UNK_SAMUS_S1* unkItemType = item_list[4];
    func_8007E620(fp, unkItemType->x0_joint); 
    
    scale.x = scale.y = scale.z = fp->x34_scale.y;
    HSD_JObjSetScale((fighter_copy = fp)->x20A0_accessory, &scale);  
    

    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory, unkItemType->x8_anim_joint, unkItemType->xC_matanim_joint, 0);
    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory, unkItemType->x4_anim_joints[index - 219], 0, 0);
    HSD_ForeachAnim(fighter_copy->x20A0_accessory, 6, 0xFB7F, &ftSamus_80128770, 1, argf);
    HSD_JObjReqAnimAll(fighter_copy->x20A0_accessory, 0.0f);
    HSD_JObjAnimAll(fighter_copy->x20A0_accessory);
    func_8000C2F8(fighter_copy->x20A0_accessory, fighter_copy->x5E8_fighterBones[51].x0_jobj);
}

