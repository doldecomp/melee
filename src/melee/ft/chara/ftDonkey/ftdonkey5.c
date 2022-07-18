#include "ftdonkey.h"

void ftDonkey_SetCallbacks(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->cb.x21DC_callback_OnTakeDamage = &ftDonkey_8010D774;
    fighter->cb.x21E4_callback_OnDeath2 = &ftDonkey_8010D774;
    fighter->cb.x21F0_callback = &ftDonkey_DestroyAllEffects;
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_UpdateGroundVel(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    fighter->xEC_ground_vel = fighter->x2C_facing_direction * (donkey_attr->x34 * fighter->x234C_stateVar4_s32);
}

void ftDonkey_SpecialN_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    if ( fighter->sa.dk.x222C == donkey_attr->x2C) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x175, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter->x2348_stateVar3 = 1;
        fighter->x234C_stateVar4 = fighter->sa.dk.x222C;
        fighter->sa.dk.x222C = 0;
    } else {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x171, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter->x2348_stateVar3 = 0;
        fighter->x234C_stateVar4 = 0;
    }
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = 0;
    fighter->x2344_stateVar2 = 0;
    fighter->x2354_stateVar6 = -1; 
    fighter->x2350_stateVar5_s32 = -1;
    func_8007D7FC(fighter);
    fighter->x80_self_vel.y = 0.0f;
    ftDonkey_SetCallbacks(fighterObj);
    func_8006EBA4(fighterObj);
}

void ftDonkey_SpecialAirN_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    if (fighter->sa.dk.x222C == donkey_attr->x2C) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x17A, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter->x2348_stateVar3 = 1;
        fighter->x234C_stateVar4 = fighter->sa.dk.x222C;
        fighter->sa.dk.x222C = 0;
    } else {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x176, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter->x2348_stateVar3 = 0;
        fighter->x234C_stateVar4 = 0;
    }
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = 0;
    fighter->x2344_stateVar2 = 0;
    fighter->x2354_stateVar6 = -1; 
    fighter->x2350_stateVar5_s32 = -1;

    ftDonkey_SetCallbacks(fighterObj);
    func_8006EBA4(fighterObj);
}

void ftDonkey_8010E7B4(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x172, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_NullCallbacks(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    fighter->cb.x21F0_callback = 0;
    fighter->cb.x21D4_callback_EnterHitlag = 0;
    fighter->cb.x21D8_callback_ExitHitlag = 0;
}


void ftDonkey_8010E840(HSD_GObj *fighterObj)
{
    Fighter *fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = fighter->x2D4_specialAttributes;
    if (0.0f == fighter->x894_currentAnimFrame) {
        fighter->sa.dk.x222C += 1;
        if (fighter->sa.dk.x222C >= donkey_attr->x2C) {
            Fighter *fighter2 = fighter;
            func_800BFFD0(fighter2, 0x39, 0);
            fighter2->sa.dk.x222C = donkey_attr->x2C;
            ftDonkey_NullCallbacks(fighterObj);
            func_8008A2BC(fighterObj);
        }
    }
}

void ftDonkey_8010E8E0(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftDonkey_NullCallbacks(fighterObj);
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010E930(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    
    if (fighter->x2200_ftcmd_var0) {
        if (fighter->x2348_stateVar3_s32 == 0) {
            fighter->x2348_stateVar3_s32++;
        }
    }
    if (fighter->x2348_stateVar3_s32 == 1) {
        fighter->x2348_stateVar3_s32++;
        if (fighter->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        }
    }
    if (fighter->x914[0].x0) {
        if (fighter->x2344_stateVar2_s32 == 0) {
            fighter->x2344_stateVar2_s32 = 1;
        }
        if (fighter->x2350_stateVar5_s32 == -1) {
            fighter->x2350_stateVar5_s32 = fighter->x914[0].xC; 
        }
        func_8007ABD0(&fighter->x914[0], fighter->x2350_stateVar5_s32 + (fighter->x234C_stateVar4_s32 * donkey_attr->x30), fighterObj);
        if (fighter->x2354_stateVar6_s32 == -1) {
            fighter->x2354_stateVar6_s32 = fighter->x914[1].xC;
        }
        func_8007ABD0(&fighter->x914[1], fighter->x2354_stateVar6_s32 + (fighter->x234C_stateVar4_s32 * donkey_attr->x30), fighterObj);
    }
    if (fighter->x2344_stateVar2_s32 == 1) {
        fighter->x2344_stateVar2_s32 = 2;
        ftDonkey_UpdateGroundVel(fighterObj);
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        fighter->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighterObj);
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010EB0C(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    
    if (fighter->x2200_ftcmd_var0) {
        if (fighter->x2348_stateVar3_s32 == 0) {
            fighter->x2348_stateVar3_s32++;
        }
    }
    if (fighter->x2348_stateVar3_s32 == 1) {
        fighter->x2348_stateVar3_s32++;
        if (fighter->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        }
    }
    if (fighter->x914[0].x0 && (fighter->x2344_stateVar2_s32 == 0)) {
        fighter->x2344_stateVar2_s32 = 1;
    }
    if (fighter->x2344_stateVar2_s32 == 1) {
        fighter->x2344_stateVar2_s32 = 2;
        ftDonkey_UpdateGroundVel(fighterObj);
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        fighter->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighterObj);
        func_8008A2BC(fighterObj);
    }
}

void ftDonkey_8010EC5C(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x177, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010ECE8(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = fighter->x2D4_specialAttributes;
    
    if (fighter->x894_currentAnimFrame == 0.0f) {
        fighter->sa.dk.x222C += 1;
        if (fighter->sa.dk.x222C >= donkey_attr->x2C) {
            Fighter *fighter2 = fighter;
            func_800BFFD0(fighter2, 0x39, 0);
            fighter->sa.dk.x222C = donkey_attr->x2C;
            ftDonkey_NullCallbacks(fighterObj);
            func_800CC730(fighterObj);
        }
    }
}

void ftDonkey_8010ED88(HSD_GObj* fighterObj) {
    s32 unsued[4]; 
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftDonkey_NullCallbacks(fighterObj);
        func_800CC730(fighterObj);
    }
}

void ftDonkey_8010EDD8(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    
    if (fighter->x2200_ftcmd_var0) {
        if (fighter->x2348_stateVar3_s32 == 0) {
            fighter->x2348_stateVar3_s32++;
        }
    }
    if (fighter->x2348_stateVar3_s32 == 1) {
        fighter->x2348_stateVar3_s32++;
        if (fighter->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        }
    }
    if (fighter->x914[0].x0) {

        if (fighter->x2350_stateVar5_s32 == -1) {
            fighter->x2350_stateVar5_s32 = fighter->x914[0].xC; 
        }
        func_8007ABD0(&fighter->x914[0], fighter->x2350_stateVar5_s32 + (fighter->x234C_stateVar4_s32 * donkey_attr->x30), fighterObj);
        if (fighter->x2354_stateVar6_s32 == -1) {
            fighter->x2354_stateVar6_s32 = fighter->x914[1].xC;
        }
        func_8007ABD0(&fighter->x914[1], fighter->x2354_stateVar6_s32 + (fighter->x234C_stateVar4_s32 * donkey_attr->x30), fighterObj);
    }

    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        fighter->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighterObj);
        if (donkey_attr->x38 == 0.0f) {
            func_800CC730(fighterObj);
        } else {
            func_80096900(fighterObj, 1, 0, 1, 1.0f, donkey_attr->x38);
        }
    }
}

void ftDonkey_8010EF7C(HSD_GObj* fighterObj) {
    Fighter *fighter = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fighter); 
    
    if (fighter->x2200_ftcmd_var0) {
        if (fighter->x2348_stateVar3_s32 == 0) {
            fighter->x2348_stateVar3_s32++;
        }
    }
    
    if (fighter->x2348_stateVar3_s32 == 1) {
        fighter->x2348_stateVar3_s32++;
        if (fighter->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighterObj, fighter->x5E8_fighterBones[0].x0_jobj, &fighter->x2C_facing_direction);
        }
    }
    
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        fighter->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighterObj);
        if (donkey_attr->x38 == 0.0f) {
            func_800CC730(fighterObj);
        } else {
            func_80096900(fighterObj, 1, 0, 1, 1.0f, donkey_attr->x38);
        }
    }
}

void ftDonkey_8010F094(HSD_GObj* fighterObj) {}

void ftDonkey_8010F098(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    Fighter* fighter = getFighterPlus(fighterObj);
    if (!func_8009917C(fighterObj)) {
        if ((fighter->input.x668 & 0x200)) {
            Fighter_ActionStateChange_800693AC(fighterObj, 0x174, 0, NULL, 0.0f, 1.0f, 0.0f);
            fighter->x234C_stateVar4_s32 = fighter->sa.dk.x222C;
            fighter->sa.dk.x222C = 0;
            ftDonkey_SetCallbacks(fighterObj);
            func_8006EBA4(fighterObj);
        }
        if ((fighter->input.x668 & 0x80000000)) {
            fighter->x2340_stateVar1 = 1;
        }
        if ((fighter->x894_currentAnimFrame == 0.0f) && (fighter->x2340_stateVar1)) {
            Fighter_ActionStateChange_800693AC(fighterObj, 0x173, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftDonkey_SetCallbacks(fighterObj);
        }
    }
}

void ftDonkey_8010F1D8(HSD_GObj* fighterObj) {}

void ftDonkey_8010F1DC(HSD_GObj* fighterObj) {}

void ftDonkey_8010F1E0(HSD_GObj* fighterObj) {}

void ftDonkey_8010F1E4(HSD_GObj* fighterObj) {}

void ftDonkey_8010F1E8(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    Fighter* fighter = getFighterPlus(fighterObj);
    if ((fighter->input.x668 & 0x200)) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x179, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter->x234C_stateVar4_s32 = fighter->sa.dk.x222C;
        fighter->sa.dk.x222C = 0;
        ftDonkey_SetCallbacks(fighterObj);
        func_8006EBA4(fighterObj);
    }
    if ((fighter->input.x668 & 0x80000000)) {
        fighter->x2340_stateVar1 = 1;
    }
    if ((fighter->x894_currentAnimFrame == 0.0f) && (fighter->x2340_stateVar1)) {
        Fighter_ActionStateChange_800693AC(fighterObj, 0x178, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F31C(HSD_GObj* fighterObj) {}

void ftDonkey_8010F320(HSD_GObj* fighterObj) {}

void ftDonkey_8010F324(HSD_GObj* fighterObj) {}

void ftDonkey_8010F328(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010F348(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010F368(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010F388(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010F3A8(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_8010F3C8(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftDonkey_8010F3E8(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftDonkey_8010F408(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftDonkey_8010F428(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}

void ftDonkey_8010F448(HSD_GObj* fighterObj) {
    func_80084EEC(fighterObj);
}


void ftDonkey_8010F468(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (!func_80082708(fighterObj)) {
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x176, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F50C(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (!func_80082708(fighterObj)) {
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x177, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F5B0(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (!func_80082708(fighterObj)) {
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x178, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F654(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_800827A0(fighterObj) == 0) {
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x179, 0x0C4D508E, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F6F8(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_800827A0(fighterObj) == 0) {
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x17A, 0x0C4D508E, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F79C(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_80081D0C(fighterObj) == 1) {
        func_8007D7FC(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x171, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010F840(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_80081D0C(fighterObj) == 1) {
        func_8007D7FC(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x172, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}


void ftDonkey_8010F8E4(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_80081D0C(fighterObj) == 1) {
        func_8007D7FC(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x173, 0x0C4C5080, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}


void ftDonkey_8010F988(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_80081D0C(fighterObj)) {
        func_8007D7FC(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x174, 0x0C4D508E, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_8010FA2C(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);
    if (func_80081D0C(fighterObj)) {
        func_8007D7FC(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x175, 0x0C4D508E, NULL, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks(fighterObj);
    }
}

void ftDonkey_DestroyAllEffects(HSD_GObj* fighterObj) {
    efLib_DestroyAll(fighterObj);
}