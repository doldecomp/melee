#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_SetCallbacks_SpecialN(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->cb.x21DC_callback_OnTakeDamage = &ftDonkey_8010D774;
    fp->cb.x21E4_callback_OnDeath2 = &ftDonkey_8010D774;
    fp->cb.x21F0_callback = &ftDonkey_DestroyAllEffects;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_UpdateDKVelocityAfterPunch(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    fp->xEC_ground_vel = fp->x2C_facing_direction * (donkey_attr->SpecialN.x34_PUNCH_HORIZONTAL_VEL * fp->x234C_stateVar4_s32);
}

void ftDonkey_SpecialN_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    if ( fp->sa.dk.x222C == donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->x2348_stateVar3 = 1;
        fp->x234C_stateVar4 = fp->sa.dk.x222C;
        fp->sa.dk.x222C = 0;
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x171, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->x2348_stateVar3 = 0;
        fp->x234C_stateVar4 = 0;
    }
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2340_stateVar1 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x2354_stateVar6 = -1; 
    fp->x2350_stateVar5_s32 = -1;
    func_8007D7FC(fp);
    fp->x80_self_vel.y = 0.0f;
    ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    func_8006EBA4(fighter_gobj);
}

void ftDonkey_SpecialAirN_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    if (fp->sa.dk.x222C == donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17A, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->x2348_stateVar3 = 1;
        fp->x234C_stateVar4 = fp->sa.dk.x222C;
        fp->sa.dk.x222C = 0;
    } else {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x176, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->x2348_stateVar3 = 0;
        fp->x234C_stateVar4 = 0;
    }
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2340_stateVar1 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x2354_stateVar6 = -1; 
    fp->x2350_stateVar5_s32 = -1;

    ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    func_8006EBA4(fighter_gobj);
}

void ftDonkey_8010E7B4(HSD_GObj* fighter_gobj) {
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x172, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_NullCallbacks(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    fp->cb.x21F0_callback = 0;
    fp->cb.x21D4_callback_EnterHitlag = 0;
    fp->cb.x21D8_callback_ExitHitlag = 0;
}


void ftDonkey_8010E840(HSD_GObj *fighter_gobj)
{
    Fighter *fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    if (0.0f == fp->x894_currentAnimFrame) {
        fp->sa.dk.x222C += 1;
        if (fp->sa.dk.x222C >= donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
            Fighter *fighter2 = fp;
            func_800BFFD0(fighter2, 0x39, 0);
            fighter2->sa.dk.x222C = donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS;
            ftDonkey_NullCallbacks(fighter_gobj);
            func_8008A2BC(fighter_gobj);
        }
    }
}

void ftDonkey_8010E8E0(HSD_GObj* fighter_gobj) {
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftDonkey_NullCallbacks(fighter_gobj);
        func_8008A2BC(fighter_gobj);
    }
}

void ftDonkey_8010E930(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    
    if (fp->x2200_ftcmd_var0) {
        if (fp->x2348_stateVar3_s32 == 0) {
            fp->x2348_stateVar3_s32++;
        }
    }
    if (fp->x2348_stateVar3_s32 == 1) {
        fp->x2348_stateVar3_s32++;
        if (fp->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        }
    }
    if (fp->x914[0].x0) {
        if (fp->x2344_stateVar2_s32 == 0) {
            fp->x2344_stateVar2_s32 = 1;
        }
        if (fp->x2350_stateVar5_s32 == -1) {
            fp->x2350_stateVar5_s32 = fp->x914[0].xC; 
        }
        func_8007ABD0(&fp->x914[0], fp->x2350_stateVar5_s32 + (fp->x234C_stateVar4_s32 * donkey_attr->SpecialN.x30_DAMAGE_PER_SWING), fighter_gobj);
        if (fp->x2354_stateVar6_s32 == -1) {
            fp->x2354_stateVar6_s32 = fp->x914[1].xC;
        }
        func_8007ABD0(&fp->x914[1], fp->x2354_stateVar6_s32 + (fp->x234C_stateVar4_s32 * donkey_attr->SpecialN.x30_DAMAGE_PER_SWING), fighter_gobj);
    }
    if (fp->x2344_stateVar2_s32 == 1) {
        fp->x2344_stateVar2_s32 = 2;
        ftDonkey_UpdateDKVelocityAfterPunch(fighter_gobj);
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighter_gobj);
        func_8008A2BC(fighter_gobj);
    }
}

void ftDonkey_8010EB0C(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    
    if (fp->x2200_ftcmd_var0) {
        if (fp->x2348_stateVar3_s32 == 0) {
            fp->x2348_stateVar3_s32++;
        }
    }
    if (fp->x2348_stateVar3_s32 == 1) {
        fp->x2348_stateVar3_s32++;
        if (fp->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        }
    }
    if (fp->x914[0].x0 && (fp->x2344_stateVar2_s32 == 0)) {
        fp->x2344_stateVar2_s32 = 1;
    }
    if (fp->x2344_stateVar2_s32 == 1) {
        fp->x2344_stateVar2_s32 = 2;
        ftDonkey_UpdateDKVelocityAfterPunch(fighter_gobj);
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighter_gobj);
        func_8008A2BC(fighter_gobj);
    }
}

void ftDonkey_8010EC5C(HSD_GObj* fighter_gobj) {
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x177, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010ECE8(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    
    if (fp->x894_currentAnimFrame == 0.0f) {
        fp->sa.dk.x222C += 1;
        if (fp->sa.dk.x222C >= donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS) {
            Fighter *fighter2 = fp;
            func_800BFFD0(fighter2, 0x39, 0);
            fp->sa.dk.x222C = donkey_attr->SpecialN.x2C_MAX_ARM_SWINGS;
            ftDonkey_NullCallbacks(fighter_gobj);
            func_800CC730(fighter_gobj);
        }
    }
}

void ftDonkey_8010ED88(HSD_GObj* fighter_gobj) {
    s32 unsued[4]; 
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftDonkey_NullCallbacks(fighter_gobj);
        func_800CC730(fighter_gobj);
    }
}

void ftDonkey_8010EDD8(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    
    if (fp->x2200_ftcmd_var0) {
        if (fp->x2348_stateVar3_s32 == 0) {
            fp->x2348_stateVar3_s32++;
        }
    }
    if (fp->x2348_stateVar3_s32 == 1) {
        fp->x2348_stateVar3_s32++;
        if (fp->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        }
    }
    if (fp->x914[0].x0) {

        if (fp->x2350_stateVar5_s32 == -1) {
            fp->x2350_stateVar5_s32 = fp->x914[0].xC; 
        }
        func_8007ABD0(&fp->x914[0], fp->x2350_stateVar5_s32 + (fp->x234C_stateVar4_s32 * donkey_attr->SpecialN.x30_DAMAGE_PER_SWING), fighter_gobj);
        if (fp->x2354_stateVar6_s32 == -1) {
            fp->x2354_stateVar6_s32 = fp->x914[1].xC;
        }
        func_8007ABD0(&fp->x914[1], fp->x2354_stateVar6_s32 + (fp->x234C_stateVar4_s32 * donkey_attr->SpecialN.x30_DAMAGE_PER_SWING), fighter_gobj);
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighter_gobj);
        if (donkey_attr->SpecialN.x38_LANDING_LAG == 0.0f) {
            func_800CC730(fighter_gobj);
        } else {
            func_80096900(fighter_gobj, 1, 0, 1, 1.0f, donkey_attr->SpecialN.x38_LANDING_LAG);
        }
    }
}

void ftDonkey_8010EF7C(HSD_GObj* fighter_gobj) {
    Fighter *fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp); 
    
    if (fp->x2200_ftcmd_var0) {
        if (fp->x2348_stateVar3_s32 == 0) {
            fp->x2348_stateVar3_s32++;
        }
    }
    
    if (fp->x2348_stateVar3_s32 == 1) {
        fp->x2348_stateVar3_s32++;
        if (fp->xE0_ground_or_air == GA_Air) {
            ef_Spawn(0x4C9, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        } else {
            ef_Spawn(0x4C8, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, &fp->x2C_facing_direction);
        }
    }
    
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp->sa.dk.x222C = 0;
        ftDonkey_NullCallbacks(fighter_gobj);
        if (donkey_attr->SpecialN.x38_LANDING_LAG == 0.0f) {
            func_800CC730(fighter_gobj);
        } else {
            func_80096900(fighter_gobj, 1, 0, 1, 1.0f, donkey_attr->SpecialN.x38_LANDING_LAG);
        }
    }
}

void ftDonkey_8010F094(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F098(HSD_GObj* fighter_gobj) {
    s32 unused[2]; 
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (!func_8009917C(fighter_gobj)) {
        if ((fp->input.x668 & 0x200)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x174, 0, NULL, 0.0f, 1.0f, 0.0f);
            fp->x234C_stateVar4_s32 = fp->sa.dk.x222C;
            fp->sa.dk.x222C = 0;
            ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
            func_8006EBA4(fighter_gobj);
        }
        if ((fp->input.x668 & 0x80000000)) {
            fp->x2340_stateVar1 = 1;
        }
        if ((fp->x894_currentAnimFrame == 0.0f) && (fp->x2340_stateVar1)) {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x173, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
        }
    }
}

void ftDonkey_8010F1D8(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F1DC(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F1E0(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F1E4(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F1E8(HSD_GObj* fighter_gobj) {
    s32 unused[2]; 
    Fighter* fp = getFighterPlus(fighter_gobj);
    if ((fp->input.x668 & 0x200)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x179, 0, NULL, 0.0f, 1.0f, 0.0f);
        fp->x234C_stateVar4_s32 = fp->sa.dk.x222C;
        fp->sa.dk.x222C = 0;
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
        func_8006EBA4(fighter_gobj);
    }
    if ((fp->input.x668 & 0x80000000)) {
        fp->x2340_stateVar1 = 1;
    }
    if ((fp->x894_currentAnimFrame == 0.0f) && (fp->x2340_stateVar1)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x178, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F31C(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F320(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F324(HSD_GObj* fighter_gobj) {}

void ftDonkey_8010F328(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010F348(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010F368(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010F388(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010F3A8(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_8010F3C8(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}

void ftDonkey_8010F3E8(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}

void ftDonkey_8010F408(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}

void ftDonkey_8010F428(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}

void ftDonkey_8010F448(HSD_GObj* fighter_gobj) {
    func_80084EEC(fighter_gobj);
}


void ftDonkey_8010F468(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x176, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F50C(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x177, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F5B0(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (!func_80082708(fighter_gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x178, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F654(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_800827A0(fighter_gobj) == 0) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x179, 0x0C4D508E, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F6F8(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_800827A0(fighter_gobj) == 0) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17A, 0x0C4D508E, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F79C(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_80081D0C(fighter_gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x171, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010F840(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_80081D0C(fighter_gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x172, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}


void ftDonkey_8010F8E4(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_80081D0C(fighter_gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x173, 0x0C4C5080, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}


void ftDonkey_8010F988(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_80081D0C(fighter_gobj)) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x174, 0x0C4D508E, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_8010FA2C(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    if (func_80081D0C(fighter_gobj)) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0x0C4D508E, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialN(fighter_gobj);
    }
}

void ftDonkey_DestroyAllEffects(HSD_GObj* fighter_gobj) {
    efLib_DestroyAll(fighter_gobj);
}

void ftDonkey_DestroyAllEffectsPlus(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->sa.dk.x222C = 0;
    efLib_DestroyAll(fighter_gobj);
}
