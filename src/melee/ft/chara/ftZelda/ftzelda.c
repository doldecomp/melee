#include "ftzelda.h"

void ftZelda_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
    fighter->sa.zelda.x222C = 0;
}

void ftZelda_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;
    
    PUSH_ATTRS(fighter, ftZeldaAttributes);
    
    func_8026B3F8(item_list[0], 0x6CU);
    func_8026B3F8(item_list[1], 0x6DU);
}

void ftZelda_801393AC(HSD_GObj* fighterObj) {
    func_8013B5EC(fighterObj);
}

void ftZelda_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftZelda_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftZelda_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftZelda_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}

void ftZelda_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftZeldaAttributes);
}

void ftZelda_801395C8(HSD_GObj* fighterObj) {
    s32 unused[2];
    s32 result = func_80074A74(fighterObj, 1);
    if (result == -1) {
        func_80074A4C(fighterObj, 1, 0);
    } else {
        func_80074A4C(fighterObj, 1, -1);
    }
}

void ftZelda_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}

void ftZelda_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
}

// https://decomp.me/scratch/UHxFc
void ftZelda_801396AC(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftZelda_801396E0(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// https://decomp.me/scratch/ZIrBS
void func_801396E0(HSD_GObj* fighterObj) {
    Point3d sp10;
    Fighter* fighter = getFighter(fighterObj);
    u8 flag = fighter->x2219_flag.bits.b0;
    
    if (flag == 0) {
        func_8000B1CC(fighter->x5E8_fighterBones[4].x0_jobj, NULL, &sp10);
        
        if ((s32) fighter->xE0_ground_or_air == 0) {
            ef_Spawn(0x4F6, fighterObj, fighter->x5E8_fighterBones->x0_jobj);
        } else {
            ef_Spawn(0x4F7, fighterObj, fighter->x5E8_fighterBones->x0_jobj);
        }
        fighter->x2219_flag.bits.b0 = 1L;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// https://decomp.me/scratch/yRI2F
void ftZelda_8013979C(HSD_GObj* fighterObj) {
    Point3d sp10;
    u8 flag;
    Fighter* fighter = getFighter(fighterObj);

    func_8000B1CC(fighter->x5E8_fighterBones[4].x0_jobj, NULL, &sp10);

    flag = fighter->x2219_flag.bits.b0;
    if (flag == 0) {
        ef_Spawn(0x505, fighterObj, &sp10);
        fighter->x2219_flag.bits.b0 = 1L;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

void lbl_801396AC(HSD_GObj*);
extern f32 lbl_804D9B98;
extern f32 lbl_804D9B9C;
extern f32 lbl_804D9BA0;
extern f32 lbl_804D9BA4;
extern f32 lbl_804D9BA8;
void lbl_801396AC(HSD_GObj*);
extern f32 lbl_804D9B98;
extern f32 lbl_804D9B9C;
extern f32 lbl_804D9BA0;
extern f32 lbl_804D9BA4;
extern f32 lbl_804D9BA8;

// https://decomp.me/scratch/Ie9jz
// https://decomp.me/scratch/52XE3
void ftZelda_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    Vec sp24;
    HSD_JObj* jObj;
    s32 arg1; // this is unused
    HSD_GObj* gObj;  // this is unused
    Fighter* fighter = getFighterPlus(fighterObj);

    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    fighter = getFighterPlus(fighterObj);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x234C_stateVar4 = 0;
    
    jObj = fighter->x5E8_fighterBones[func_8007500C(fighter, 4)].x0_jobj;
    
    func_8000B1CC(jObj, NULL, &sp24); 
    
    func_800119DC(&sp24, 0x78, lbl_804D9B98, lbl_804D9B9C, lbl_804D9BA0);
    fighter->cb.x21BC_callback_Accessory4 = &lbl_801396AC;
}