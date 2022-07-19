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
    ftZelda_8013B5EC(fighterObj);
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

// 801396AC - 801396E0 (0x34 bytes)
// https://decomp.me/scratch/UHxFc
void ftZelda_801396AC(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftZelda_801396E0(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 801396E0 - 8013979C (0xBC bytes)
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

// 8013979C - 80139834 (0x98 bytes)
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

void ftZelda_801396AC(HSD_GObj*);
extern f32 lbl_804D9B98;
extern f32 lbl_804D9B9C;
extern f32 lbl_804D9BA0;
extern f32 lbl_804D9BA4;
extern f32 lbl_804D9BA8;

// 80139834 - 801398E8 (0xB4 bytes)
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
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 801398E8 - 801399B4 (0xCC bytes)
// https://decomp.me/scratch/9NUks
void ftZelda_SpecialAirHi_StartAction(HSD_GObj* fighterObj) {
    Point3d sp28;
    s32 unused[7];
    s32 boneIndex;
    Fighter* fighter = getFighter(fighterObj);
    HSD_JObj* jObj;
    ftZeldaAttributes* attributes = fighter->x2D4_specialAttributes;
        
    fighter->x80_self_vel.x = (f32) fighter->x80_self_vel.x / attributes->x38;
    fighter->x80_self_vel.y = (f32) fighter->x80_self_vel.y / attributes->x3C;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0, NULL, lbl_804D9BA4, lbl_804D9BA8, lbl_804D9BA4);
    func_8006EBA4(fighterObj);
    
    fighter = getFighter(fighterObj);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x234C_stateVar4 = 0;
    
    boneIndex = func_8007500C(fighter, 4);
    jObj = fighter->x5E8_fighterBones[boneIndex].x0_jobj;
    func_8000B1CC(jObj, NULL, &sp28);
    
    func_800119DC(&sp28, 0x78, lbl_804D9B98, lbl_804D9B9C, lbl_804D9BA0);
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 801399B4 - 801399F0 (0x3C bytes)
// https://decomp.me/scratch/wsgNa
void ftZelda_801399B4(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ftZelda_8013A058(arg0);
    }
}

// 801399F0 - 80139A2C (0x3C bytes)
// https://decomp.me/scratch/3f62U
void lbl_801399F0(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_8013A244(arg0);
    }
}

void ftZelda_80139A2C(HSD_GObj* arg0) {}
void ftZelda_80139A30(HSD_GObj* arg0) {}

// 80139A34 - 80139A54 (0x20 bytes)
void ftZelda_80139A34(HSD_GObj* arg0) {
    func_80084F3C(arg0);
}

// 80139A54 - 80139A98 (0x44 bytes)
// https://decomp.me/scratch/dA7X6
void ftZelda_80139A54(HSD_GObj* fighterObj) {
    f32 attrs[2];
    Fighter* fighter;
    ftZeldaAttributes* attributes;

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    attrs[0] = attributes->x40;
    attrs[1] = attributes->x44;
    
    func_8007D494(fighter, attrs[0], attrs[1]);
    func_8007CEF4(fighter);
}

// 80139A98 - 80139AD4 (0x3C bytes)
void ftZelda_80139A98(HSD_GObj* arg0) {
    if (func_80082708(arg0) == 0) {
        ftZelda_80139B44(arg0);
    }
}

//extern f32 lbl_804D9BA4;

// 80139AD4 - 80139B44 (0x70 bytes)
// https://decomp.me/scratch/btfXC
void ftZelda_80139AD4(HSD_GObj* fighterObj) {
    s32 result;
    f32 facingDirection;
    s32 ledgeGrabDir;
    Fighter* fighter = fighterObj->user_data;
    facingDirection = fighter->x2C_facing_direction;
    
    if (facingDirection < lbl_804D9BA4) {
        ledgeGrabDir = -1;
    }
    else {
        ledgeGrabDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(fighterObj, ledgeGrabDir) != 0) {
        ftZelda_80139BB0(fighterObj);
    } else {
        result = func_80081298(fighterObj);
        if (result == 0) {
            return;
        }
    }
}

// 80139B44 - 80139BB0 (0x6C bytes)
// https://decomp.me/scratch/XI2m5
void ftZelda_80139B44(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BA8, lbl_804D9BA4);
    fighter->cb.x21BC_callback_Accessory4 = ftZelda_801396AC;
}

// 80139BB0 - 80139C1C (0x6C bytes)
// https://decomp.me/scratch/KOA33
void ftZelda_80139BB0(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BA8, lbl_804D9BA4);
    fighter->cb.x21BC_callback_Accessory4 = ftZelda_801396AC;
}

// 80139C1C - 80139C58 (0x3C bytes)
// https://decomp.me/scratch/VCHRF
void ftZelda_80139C1C(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = getFighter(fighterObj);
    fighter->x2340_stateVar1 = (s32) (fighter->x2340_stateVar1 - 1);
    if ((s32) fighter->x2340_stateVar1 <= 0) {
        ftZelda_8013A6A8(fighterObj);
    }
}

// 80139C58 - 80139C94 (0x3C bytes)
// https://decomp.me/scratch/VCHRF
void ftZelda_80139C58(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = getFighter(fighterObj);
    fighter->x2340_stateVar1 = (s32) (fighter->x2340_stateVar1 - 1);
    if ((s32) fighter->x2340_stateVar1 <= 0) {
        ftZelda_8013A764(fighterObj);
    }
}

void ftZelda_80139C94(HSD_GObj* arg0) {}
void ftZelda_80139C98(HSD_GObj* arg0) {}

// 80139C9C - 80139CBC (0x20 bytes)
void ftZelda_80139C9C(HSD_GObj* arg0) {
    func_8007CB74(arg0);
}

void ftZelda_80139CBC(HSD_GObj* arg0) {}

// 80139CC0 - 80139D60 (0xA0 bytes)
// https://decomp.me/scratch/UKBQL
void ftZelda_80139CC0(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 envFlags;
    CollData* collData;

    fighter = fighterObj->user_data;
    collData = &fighter->x6F0_collData;
    
    if (func_80082708(fighterObj) == 0) {
        envFlags = collData->x134_envFlags;
        if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0)) {
            func_8007D60C(fighter);
            ftZelda_8013A764(fighterObj);
            return;
        }
        ftZelda_80139F6C(fighterObj);
    } else {
        envFlags = collData->x134_envFlags;
        if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0)) {
            ftZelda_8013A6A8(fighterObj);
        }
    }    
}

// 80139D60 -  ( bytes)
// https://decomp.me/scratch/OJ62l