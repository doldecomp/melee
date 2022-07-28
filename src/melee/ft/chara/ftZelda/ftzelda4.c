#include "ftzelda.h"

// 8013B638 - 8013B6D8 (0xA0 bytes)
// https://decomp.me/scratch/QnXK1
void ftZelda_SpecialS_StartAction(HSD_GObj* fighterObj) {
    f32 temp_f1;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes;
    Fighter* fighter2;
    s32 unused[7];

    temp_f1 = 0;
    fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0, NULL, temp_f1, 1.0, temp_f1);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter2 = fighterObj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2340_stateVar1 = (s32) attributes->x10;
    fighter2->x2344_stateVar2_s32 = (s32) attributes->x14;
    fighter2->x2348_stateVar3_s32 = (s32) attributes->x18;
    fighter2->sa.zelda.x222C = 0;
    fighter2->x234C_stateVar4_s32 = (s32) attributes->x1C;
    fighter2->cb.x21E4_callback_OnDeath2 = 0;
    fighter2->cb.x21DC_callback_OnTakeDamage = 0;
    func_8006EBA4(fighterObj);
}

// 8013B6D8 - 8013B780 (0xA8 bytes)
// https://decomp.me/scratch/F0dW9
void ftZelda_SpecialAirS_StartAction(HSD_GObj* fighterObj) {
    f32 temp_f1;
    Fighter* fighter;
    ftZeldaAttributes* attributes;
    Fighter* fighter2;
    s32 unused[7];

    temp_f1 = 0;
    fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15A, 0, NULL, temp_f1, 1.0, temp_f1);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x80_self_vel.y = (f32) 0;
    fighter2 = fighterObj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2340_stateVar1 = (s32) attributes->x10;
    fighter2->x2344_stateVar2_s32 = (s32) attributes->x14;
    fighter2->x2348_stateVar3_s32 = (s32) attributes->x18;
    fighter2->sa.zelda.x222C = 0;
    fighter2->x234C_stateVar4_s32 = (s32) attributes->x1C;
    fighter2->cb.x21E4_callback_OnDeath2 = 0;
    fighter2->cb.x21DC_callback_OnTakeDamage = 0;
    func_8006EBA4(fighterObj);
}

// 8013B780 - 8013B89C (0x11C bytes)
// https://decomp.me/scratch/g2bK5
// u32 func_802C3BAC(HSD_GObj*, Point3d*, f32, f32);   /* extern */
// extern void ftZelda_801393AC();
void ftZelda_8013B780(HSD_GObj* fighterObj) {
    Point3d sp24;
    f32 temp_f1;
    f32 temp_f2;
    u32 temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r30
    f32 unused[6];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if (((u32) fighter->x2200_ftcmd_var0 == 1U) && ((u32) fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp24);
        sp24.z = 0;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fighter->x2C_facing_direction) + sp24.x;
        sp24.y += attributes->x24;
        temp_r3 = func_802C3BAC(fighterObj, &sp24, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3;
        if (temp_r3 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        temp_f1 = 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x158, 0, NULL, temp_f1, 1.0, temp_f1);
        fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    }
}

// 8013B89C - 8013BA04 (0x168 bytes)
// https://decomp.me/scratch/uGOsz
void ftZelda_8013B89C(HSD_GObj* fighterObj) {
    Point3d sp20;
    ftZeldaAttributes* attributes;
    Fighter* fighter; // r30
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_r3;
    u32 temp_r3_u32;
    f32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if ((fighter->x2200_ftcmd_var0 == 1U) && (fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp20);
        sp20.z = 0;
        temp_f2 = attributes->x20;
        sp20.x = (temp_f2 * fighter->x2C_facing_direction) + sp20.x;
        sp20.y += attributes->x24;
        temp_r3_u32 = func_802C3BAC(fighterObj, &sp20, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3_u32;
        if (temp_r3_u32 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    temp_r3 = fighter->x2340_stateVar1;
    if (temp_r3 != 0) {
        fighter->x2340_stateVar1 = (s32) (temp_r3 - 1);
    }
    temp_r3 = fighter->x2344_stateVar2_s32;
    if (temp_r3 != 0) {
        fighter->x2344_stateVar2_s32 = (s32) (temp_r3 - 1);
    }
    temp_r3_u32 = fighter->sa.zelda.x222C;
    if (temp_r3_u32 == 0) {
        if ((fighter->x2340_stateVar1 <= 0) && (fighter->x2344_stateVar2_s32 <= 0)) {
            temp_f1 = 0;
            Fighter_ActionStateChange_800693AC(fighterObj, 0x159, 0, NULL, temp_f1, 1.0, temp_f1);
        }
    } else {
        temp_r3 = func_802C3AF0(fighter->sa.zelda.x222C);
        if (temp_r3 != (u32) fighterObj) {
            fighter->sa.zelda.x222C = 0;
        }
    }
}

// 8013BA04 - 8013BA8C (0x88 bytes)
// https://decomp.me/scratch/TSoo9
void ftZelda_8013BA04(HSD_GObj* fighterObj) {
    Fighter* fighter;
    ftZeldaAttributes* attributes;

    fighter = getFighter(fighterObj);

    func_8007592C(fighter, 0, 0);
    
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter = getFighter(fighterObj);
        attributes = getFtSpecialAttrs(fighter);
        
        fighter->x2340_stateVar1 = (s32) attributes->x10;
        fighter->x2344_stateVar2_s32 = (s32) attributes->x14;
        fighter->x2348_stateVar3_s32 = (s32) attributes->x18;
        fighter->sa.zelda.x222C = 0;
        fighter->x234C_stateVar4_s32 = (s32) attributes->x1C;
        fighter->cb.x21E4_callback_OnDeath2 = 0;
        fighter->cb.x21DC_callback_OnTakeDamage = 0;
        
        func_8008A2BC(fighterObj);
    }
}

// 8013BA8C - 8013BBA8 (0x11C bytes)
// https://decomp.me/scratch/9hYY3
// u32 func_802C3BAC(HSD_GObj*, Point3d*, f32, f32);   /* extern */
void ftZelda_8013BA8C(HSD_GObj* fighterObj) {
    Point3d sp24;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_cr0_eq;
    u32 temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r30
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if (((u32) fighter->x2200_ftcmd_var0 == 1U) && ((u32) fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp24);
        sp24.z = 0;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fighter->x2C_facing_direction) + sp24.x;
        sp24.y += attributes->x24;
        temp_r3 = func_802C3BAC(fighterObj, &sp24, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3;
        if (temp_r3 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        temp_f1 = 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x15B, 0, NULL, temp_f1, 1.0, temp_f1);
        fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    }
}

// 8013BBA8 - 8013BD10 (0x168 bytes)
// https://decomp.me/scratch/llKUS
// u32 func_802C3AF0();                                /* extern */
// u32 func_802C3BAC(HSD_GObj*, Point3d*, f32, f32);   /* extern */
void ftZelda_8013BBA8(HSD_GObj* fighterObj) {
    Point3d sp20;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_r3_s32;
    u32 temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r30
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    
    if (((u32) fighter->x2200_ftcmd_var0 == 1U) && ((u32) fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp20);
        sp20.z = 0;
        temp_f2 = attributes->x20;
        sp20.x = (temp_f2 * fighter->x2C_facing_direction) + sp20.x;
        sp20.y += attributes->x24;
        temp_r3 = func_802C3BAC(fighterObj, &sp20, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3;
        if (temp_r3 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    temp_r3_s32 = fighter->x2340_stateVar1;
    if (temp_r3_s32 != 0) {
        fighter->x2340_stateVar1 = (s32) (temp_r3_s32 - 1);
    }
    temp_r3_s32 = fighter->x2344_stateVar2_s32;
    if (temp_r3_s32 != 0) {
        fighter->x2344_stateVar2_s32 = (s32) (temp_r3_s32 - 1);
    }
    if ((u32) fighter->sa.zelda.x222C == 0U) {
        if (((s32) fighter->x2340_stateVar1 <= 0) && ((s32) fighter->x2344_stateVar2_s32 <= 0)) {
            temp_f1 = 0;
            Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0, NULL, temp_f1, 1.0, temp_f1);
        }
    } else {
        temp_r3 = func_802C3AF0(fighter->sa.zelda.x222C);
        if (temp_r3 != (u32) fighterObj) {
            fighter->sa.zelda.x222C = 0;
        }
    }
}

// 8013BD10 - 8013BDD0 (0xC0 bytes)
// https://decomp.me/scratch/fsXpu
void ftZelda_8013BD10(HSD_GObj* fighterObj) {
    Fighter* fighter;
    f32 temp_f2;
    ftZeldaAttributes* attributes; // r31
    ftZeldaAttributes* attributes2;
    f32 unused[3];

    fighter = getFighter(fighterObj);
    attributes = fighter->x2D4_specialAttributes;
    
    func_8007592C(fighter, 0, 0);
    
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter = getFighter(fighterObj);
        attributes2 = getFtSpecialAttrs(fighter);
        fighter->x2340_stateVar1 = (s32) attributes2->x10;
        fighter->x2344_stateVar2_s32 = (s32) attributes2->x14;
        fighter->x2348_stateVar3_s32 = (s32) attributes2->x18;
        fighter->sa.zelda.x222C = 0;
        fighter->x234C_stateVar4_s32 = (s32) attributes2->x1C;
        fighter->cb.x21E4_callback_OnDeath2 = 0;
        fighter->cb.x21DC_callback_OnTakeDamage = 0;
        
        if (0 == attributes->x34) {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 0, 1, 1.0, attributes->x34);
    }
}

void ftZelda_8013BDD0(HSD_GObj* fighterObj) {}

// 8013BDD4 - 8013BE50 (0x7C bytes)
// https://decomp.me/scratch/MaYEA
void ftZelda_8013BDD4(HSD_GObj* fighterObj) {
    f32 temp_f1;
    s32 var_r0;
    Fighter* fighter;

    fighter = fighterObj->user_data;
    fighter->x234C_stateVar4_s32 = (s32) (fighter->x234C_stateVar4_s32 - 1);
    
    if ((s32) fighter->x234C_stateVar4_s32 <= 0) {
        fighter->x234C_stateVar4_s32 = 0;
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    
    if ((var_r0 == 1) && !(fighter->input.x65C & 0x200)) {
        temp_f1 = 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x159, 0, NULL, temp_f1, 1.0, temp_f1);
    }
}

void ftZelda_8013BE50(HSD_GObj* fighterObj) {}
void ftZelda_8013BE54(HSD_GObj* fighterObj) {}

// 8013BE58 - 8013BED4 (0x7C bytes)
// https://decomp.me/scratch/Zxkmg
void ftZelda_8013BE58(HSD_GObj* fighterObj) {
    f32 temp_f1;
    s32 var_r0;
    Fighter* fighter;

    fighter = fighterObj->user_data;
    fighter->x234C_stateVar4_s32 = (s32) (fighter->x234C_stateVar4_s32 - 1);
    
    if ((s32) fighter->x234C_stateVar4_s32 <= 0) {
        fighter->x234C_stateVar4_s32 = 0;
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if ((var_r0 == 1) && !(fighter->input.x65C & 0x200)) {
        temp_f1 = 0;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0, NULL, temp_f1, 1.0, temp_f1);
    }
}

void ftZelda_8013BED4(HSD_GObj* fighterObj) {}

// 8013BED8 - 8013BF30 (0x20 bytes)
void ftZelda_8013BF10(HSD_GObj* arg0) {
    func_80084F3C(arg0);
}

// 8013BF30 - 8013BF50 (0x20 bytes)
void ftZelda_8013BF30(HSD_GObj* arg0) {
    func_80084F3C(arg0);
}

// 8013BF50 - 8013BFB0 (0x60 bytes)
// https://decomp.me/scratch/suE14
void ftZelda_8013BF50(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 temp_r3;
    ftZeldaAttributes* charAttr;
    attr* fighterAttr;
    f32 aerialFriction;
    f32 unused[3];

    fighter = fighterObj->user_data;
    temp_r3 = fighter->x2348_stateVar3;
    charAttr = fighter->x2D4_specialAttributes;
    
    if (temp_r3 != 0) {
        fighter->x2348_stateVar3 = temp_r3 - 1;
    } else {
        fighterAttr = &fighter->x110_attr;
        func_8007D494(fighter, charAttr->x2C, fighterAttr->x170_TerminalVelocity);
    }
    aerialFriction = fighter->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter, aerialFriction);
}

// 8013BFB0 - 8013C010 (0x60 bytes)
// https://decomp.me/scratch/BxLXt
void ftZelda_8013BFB0(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 temp_r3;
    ftZeldaAttributes* charAttr;
    attr* fighterAttr;
    f32 aerialFriction;
    f32 unused[3];

    fighter = fighterObj->user_data;
    temp_r3 = fighter->x2348_stateVar3;
    charAttr = fighter->x2D4_specialAttributes;
    
    if (temp_r3 != 0) {
        fighter->x2348_stateVar3 = temp_r3 - 1;
    } else {
        fighterAttr = &fighter->x110_attr;
        func_8007D494(fighter, charAttr->x2C, fighterAttr->x170_TerminalVelocity);
    }
    aerialFriction = fighter->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter, aerialFriction);
}

// 8013C010 - 8013C070 (0x60 bytes)
// https://decomp.me/scratch/54a1x
void ftZelda_8013C010(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 temp_r3;
    ftZeldaAttributes* charAttr;
    attr* fighterAttr;
    f32 aerialFriction;
    f32 unused[3];

    fighter = fighterObj->user_data;
    temp_r3 = fighter->x2348_stateVar3;
    charAttr = fighter->x2D4_specialAttributes;
    
    if (temp_r3 != 0) {
        fighter->x2348_stateVar3 = temp_r3 - 1;
    } else {
        fighterAttr = &fighter->x110_attr;
        func_8007D494(fighter, charAttr->x2C, fighterAttr->x170_TerminalVelocity);
    }
    aerialFriction = fighter->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter, aerialFriction);
}

// 8013C070 - 8013C0DC (0x6C bytes)
// https://decomp.me/scratch/947er
void ftZelda_8013C070(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    if (func_80082708(arg0) == 0) {
        func_8007D5D4(temp_r31);
        Fighter_ActionStateChange_800693AC(arg0, 0x15A, 0x0C4C5082, NULL, temp_r31->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C0DC - 8013C148 (0x6C bytes)
// https://decomp.me/scratch/x1Nmd
void ftZelda_8013C0DC(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    if (func_80082708(arg0) == 0) {
        func_8007D5D4(temp_r31);
        Fighter_ActionStateChange_800693AC(arg0, 0x15B, 0x0C4C5080, NULL, temp_r31->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C148 - 8013C1B4 (0x6C bytes)
void ftZelda_8013C148(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    if (func_80082708(arg0) == 0) {
        func_8007D5D4(temp_r31);
        Fighter_ActionStateChange_800693AC(arg0, 0x15C, 0x0C4C5080, NULL, temp_r31->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C1B4 - 8013C220 (0x6C bytes)
void ftZelda_8013C1B4(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    if (func_80081D0C(arg0) != 0) {
        func_8007D7FC(temp_r31);
        Fighter_ActionStateChange_800693AC(arg0, 0x157, 0x0C4C5082, NULL, temp_r31->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C220 - 8013C28C (0x6C bytes)
void ftZelda_8013C220(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    if (func_80081D0C(arg0) != 0) {
        func_8007D7FC(temp_r31);
        Fighter_ActionStateChange_800693AC(arg0, 0x158, 0x0C4C5080, NULL, temp_r31->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C28C - 8013C2F8 (0x6C bytes)
void ftZelda_8013C28C(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    if (func_80081D0C(arg0) != 0) {
        func_8007D7FC(temp_r31);
        Fighter_ActionStateChange_800693AC(arg0, 0x159, 0x0C4C5080, NULL, temp_r31->x894_currentAnimFrame, 1.0, 0);
    }
}